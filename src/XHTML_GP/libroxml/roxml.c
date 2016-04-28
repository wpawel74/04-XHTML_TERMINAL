/** \file roxml.c
 *  \brief source for libroxml.so
 *         
 * This is the source file for lib libroxml.so
 * \author blunderer <blunderer@blunderer.org>
 * \date 23 Dec 2008
 *
 * Copyright (C) 2009 blunderer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ROXML_C
#define ROXML_C

#include "roxml.h"

#define ROXML_ALLOC(x)			NULL
#define ROXML_FREE(x)			NULL

static char _val[300];
static char _arg[300];
static char _name[300];
unsigned int INDX;

node_t * roxml_parent_node(node_t *parent, node_t *n)
{
	if(parent)	{
		n->fat = parent;
		if(parent->son == NULL)	{
			parent->son = n;
		} else	{
			node_t *brother = parent->son;
			while(brother->bra != NULL)	{
				brother = brother->bra;
			}
			brother->bra = n;
		}
	}

	return n;
}

node_t * roxml_new_node(int pos, const char * buf, unsigned int * idx)
{
	node_t *n = (node_t*)ROXML_ALLOC(sizeof(node_t));
	n->idx = idx;
	n->buf = buf;
	n->pos = pos;
	n->end = pos;
	n->bra = NULL;
	n->son = NULL;
	n->fat = NULL;

	return n;
}

void roxml_close_node(node_t *n, node_t *close)
{
	n->end = close->pos;
	roxml_free_node(close);
}

void roxml_free_node(node_t *n)
{
	ROXML_FREE(n);
}

void roxml_parse_node(node_t *n, char *name, char * arg, char * value, int * num, int max)
{
	char c = 0;
	int len = 0;
	int count = 0;
	int mode = MODE_COMMENT_NONE;
	int state = STATE_NODE_NAME;

	PUSH(n)

	while((!ROXML_FEOF(n))&&(c != '>')&&((max >= 0)?(count < max+1):(1)))      {
		c = ROXML_FGETC(n);
		if(c == '"')	{
			if(mode == MODE_COMMENT_NONE)	{
				mode = MODE_COMMENT_DQUOTE;
			} else if(mode == MODE_COMMENT_DQUOTE)	{
				mode = MODE_COMMENT_NONE;
			}
			continue;
		} else if(c == '\'')	{
			if(mode == MODE_COMMENT_NONE)	{
				mode = MODE_COMMENT_QUOTE;
			} else if(mode == MODE_COMMENT_QUOTE)	{
				mode = MODE_COMMENT_NONE;
			}
			continue;
		}
		
		if(mode == MODE_COMMENT_NONE)	{
			if((c == ' ')||(c == '\t'))	{
				if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_ARG;
					len = 0;
				} else if(state == STATE_NODE_ARG)	{
					if(len > 0)	{
						len = 0;
						count++;
					}
				} else if(state == STATE_NODE_ARGVAL)     {
					if(len > 0)	{
						state = STATE_NODE_ARG;
						len = 0;
						count++;
					}
				}
			} else if(c == '=')	{
				if(state == STATE_NODE_ARG)	{
					state = STATE_NODE_ARGVAL;
					len = 0;
				}
			} else if(c == '/')	{
				;
			} else if(c == '>')	{
				if(state == STATE_NODE_ARG)	{
					if(len > 0)	{
						count++;
					}
				} else if(state == STATE_NODE_ARGVAL)	{
					if(len > 0)	{
						count++;
					}
				}
			} else if(state == STATE_NODE_NAME)    {
				if(name)	{
					name[len] = c;
					name[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARG)    {
				if(arg)	{
					arg[len] = c;
					arg[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARGVAL)    {
				if(value)	{
					value[len] = c;
					value[len+1] = '\0';
				}
				len++;
			}
		} else	{
			if(state == STATE_NODE_ARG)	{
				if(arg)	{
					arg[len] = c;
					arg[len+1] = '\0';
				}
				len++;
			} else if(state == STATE_NODE_ARGVAL)	{
				if(value)	{
					value[len] = c;
					value[len+1] = '\0';
				}
				len++;
			}
		}
	}

	if(num)	{
		*num = count;
	}

	POP(n)
}

int roxml_get_content(node_t *n, char *content)
{
	int num;
	int nbs;
	int len = 0, total = 0;
	char *content_ptr = content;
	long long int start = 0, end = 0;	

	nbs = roxml_get_son_nb(n);

	PUSH(n)

	for(num = 0; num < nbs+1; num++)	{
		char c = 0;
		node_t *son = roxml_get_son_nth(n, num);
		if(son)	{
			end = son->pos;
		} else	{
			end = n->end;
		}

		while((!ROXML_FEOF(n))&&(c != '>'))      {
			c = ROXML_FGETC(n);
		}
		if(c == '>')	{
			start = ROXML_FTELL(n);
			len = end - start - 1;
			if(len > 0)	{
				if(content_ptr)	{
					ROXML_FREAD(content_ptr, len, sizeof(char), n);
					content_ptr[len] = '\0';
					content_ptr += len;
				}
				total += len;
			} else	{
				len = 0;
				if(content_ptr)	{
					content_ptr[0] = '\0';
				}
			}
		} else {
			return -1;
		}
		if(son)	{
			ROXML_FSEEK(son, son->end);
		}
	}

	POP(n)
	return total;
}

int roxml_get_raw_content(node_t *n, char *content)
{
	char c = 0;
	int len = 0;
	long long int start = 0;	

	PUSH(n)
	
	while((!ROXML_FEOF(n))&&(c != '>'))      {
		c = ROXML_FGETC(n);
	}

	if(c == '>')	{
		start = ROXML_FTELL(n);
		len = n->end - start - 1;
		if(len > 0)	{
			if(content)	{
				ROXML_FREAD(content, len, sizeof(char), n);
				content[len] = '\0';
			}
		} else	{
			len = 0;
			if(content)	{
				content[0] = '\0';
			}
		}
	}

	POP(n)
	return len;
}

const char* roxml_get_ptr_content(node_t *n)
{
	char c = 0;
	const char *ret = NULL;
	int len = 0;
	long long int start = 0;

	PUSH(n)

	while((!ROXML_FEOF(n))&&(c != '>'))      {
		c = ROXML_FGETC(n);
	}

	if(c == '>')	{
		start = ROXML_FTELL(n);
		len = n->end - start - 1;
		if(len > 0)	{
			ret = n->buf + *(n->idx);
		}
	}

	POP(n)
	return ret;
}

int roxml_end_offset(node_t *n){
	char c = 0;
	unsigned int ret = 0;

	ret = n->end;

	do
		c = n->buf[ret++];
	while( ret<strlen(n->buf) && (c != '>') );
	return ret;
}

char * roxml_get_name(node_t *n)
{
//	char *name = (char*)ROXML_ALLOC(sizeof(char)*512);
	memset(_name, 0, sizeof(_name));

	if(n->fat == NULL)	{
		strcpy(_name,"root");
	} else	{
		roxml_parse_node(n, _name, NULL, NULL, NULL, 1);
	}
	return _name;
}

int ROXML_API roxml_get_nb_attr(node_t *n)
{
	int count;
	roxml_parse_node(n, NULL, NULL, NULL, &count, -1);
	return count;
}

char *roxml_get_attr_val_nth(node_t *n, int nb)
{
	//char * val = (char*)malloc(sizeof(char)*512);
	memset(_val, 0, sizeof(_val));
	
	roxml_parse_node(n, NULL, NULL, _val, NULL, nb);

	return _val;
}

char *roxml_get_attr_nth(node_t *n, int nb)
{
	//char * arg = (char*)malloc(sizeof(char)*512);
	memset(_arg, 0, sizeof(char)*sizeof(_arg));
	
	roxml_parse_node(n, NULL, _arg, NULL, NULL, nb);

	return _arg;
}

void roxml_close(node_t *n)
{
	node_t *root = n;
	if(root == NULL)	{
		return;
	}
	while(root->fat != NULL)	{
		root = root->fat;
	}
	roxml_del_tree(root->son);
	roxml_del_tree(root->bra);
	//??
	ROXML_FREE(root->idx);
	ROXML_FREE(root);
}

void roxml_del_tree(node_t *n)
{
	if(n == NULL)	{
		return;
	}
	roxml_del_tree(n->son);
	roxml_del_tree(n->bra);
	ROXML_FREE(n);
	return;
}

int roxml_get_son_nb(node_t *n)
{
	node_t *ptr = n;
	int nb = 0;
	if(ptr->son)	{
		ptr = ptr->son;
		nb++;
		while(ptr->bra)	{
			nb++;
			ptr = ptr->bra;
		}
	}
	return nb;
}

node_t *roxml_get_son_nth(node_t *n, int nb)
{
	int count = 0;
	node_t *ptr = n;
	if(nb == 0)	{
		return n->son;
	}
	ptr = n->son;
	while((ptr->bra)&&(nb > count)) {
		count++;
		ptr = ptr->bra;
	}
	if(nb > count)	{ return NULL; }
	return ptr;
}

node_t *roxml_get_parent(node_t *n)
{
	if(n->fat == NULL)	{
		return n;
	} else	{
		return n->fat;
	}
	return NULL;
}

node_t * roxml_load_buf(const char *buffer)
{
	unsigned int *_index = (unsigned int *) &INDX;//ROXML_ALLOC(sizeof(unsigned int));
	node_t *current_node = NULL;
	*_index = 0;
	current_node = roxml_new_node(0, buffer, _index);
	current_node = roxml_parent_node(NULL, current_node);
	return roxml_load(current_node, buffer);
}

node_t * roxml_load(node_t *current_node, const char *buffer)
{
	int state = STATE_NODE_NONE;
	int mode = MODE_COMMENT_NONE;
	node_t *candidat_node = NULL;

	while(!ROXML_FEOF(current_node))	{
		char c = ROXML_FGETC(current_node);

		if(state != STATE_NODE_CONTENT)	{
			if(c == '"')	{
				if(mode == MODE_COMMENT_NONE)	{
					mode = MODE_COMMENT_DQUOTE;
				} else if(mode == MODE_COMMENT_DQUOTE)	{
					mode = MODE_COMMENT_NONE;
				}
			} else if(c == '\'')	{
				if(mode == MODE_COMMENT_NONE)	{
					mode = MODE_COMMENT_QUOTE;
				} else if(mode == MODE_COMMENT_QUOTE)	{
					mode = MODE_COMMENT_NONE;
				}
			}
		}
		
		if(mode == MODE_COMMENT_NONE)	{
			if(c == '<')	{
				state = STATE_NODE_BEG;
				candidat_node = roxml_new_node(ROXML_FTELL(current_node), buffer, current_node->idx);
			} else if(c == '>')	{
				if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_CONTENT;
					current_node = roxml_parent_node(current_node, candidat_node);
				} else if(state == STATE_NODE_ATTR)	{
					state = STATE_NODE_CONTENT;
					current_node = roxml_parent_node(current_node, candidat_node);
				} else if(state == STATE_NODE_SINGLE)	{
					current_node = roxml_parent_node(current_node, candidat_node);
					current_node = current_node->fat;
				} else if(state == STATE_NODE_END)	{
					roxml_close_node(current_node, candidat_node);
					current_node = current_node->fat;
				}
			} else if(c == '/')	{
				if(state == STATE_NODE_BEG)	{
					state = STATE_NODE_END;
				} else if(state == STATE_NODE_NAME)	{
					state = STATE_NODE_SINGLE;
				} else if(state == STATE_NODE_ATTR)	{
					state = STATE_NODE_SINGLE;
				}
			} else if((c == ' ')||(c == '\t'))	{
				if(state == STATE_NODE_NAME)	state = STATE_NODE_ATTR;
			} else	{
				if(state == STATE_NODE_BEG)	state = STATE_NODE_NAME;
			}
		}
	}
	while(current_node->fat)	{ current_node = current_node->fat; }
	return current_node;
}

node_t ** roxml_exec_path(node_t *n, char * path, int *nb_ans)
{
	int index = 0;
	int nb_ans_internal = 0;
	node_t *starting_node = n;
	node_t **resulting_nodes = NULL;
	char * path_to_find;
	if(path[0] == '/')	{
		path_to_find = strdup(path+1);
		while(starting_node->fat)	{
			starting_node = starting_node->fat;
		}
	} else	{
		path_to_find = strdup(path);
	}

	/* two pass algorithm : first: how many node match */
	roxml_resolv_path(starting_node, path_to_find, &nb_ans_internal, NULL);
	if(nb_ans) { *nb_ans = nb_ans_internal; }
	if(nb_ans_internal == 0)	{
		return NULL;
	}

	/* two pass algorithm : then: copy them */
	index = 0;
	resulting_nodes = (node_t**)malloc(sizeof(node_t*)*nb_ans_internal);
	roxml_resolv_path(starting_node, path_to_find, &index, &resulting_nodes);

	return resulting_nodes;
}

void roxml_resolv_path(node_t *n, char * path, int *idx, node_t ***res)
{
	int i;
	int nb_son = 0;
	if(strlen(path) == 0)	{ return; }
	if(n == NULL)	{ return; }

	if(strncmp(path, "..", strlen("..")) == 0)	{
		char * new_path = path+strlen("..");
		if((strlen(new_path) > 0) && (strcmp(new_path,"/") != 0))	{
			roxml_resolv_path(n->fat, new_path+1, idx, res);
		} else	{
			if(res)	{ (*res)[*idx] = n->fat; }
			(*idx)++;
		}
	}

	nb_son = roxml_get_son_nb(n);
	for(i = 0; i < nb_son; i++)	{
		node_t *cur = roxml_get_son_nth(n, i);
		char *name = roxml_get_name(cur);

		if(strncmp(name, path, strlen(name)) == 0)	{
			char * new_path = path+strlen(name);
			if((strlen(new_path) > 0) && (strcmp(new_path,"/") != 0))	{
				roxml_resolv_path(cur, new_path+1, idx, res);
			} else	{
				if(res)	{ (*res)[*idx] = cur; }
				(*idx)++;
			}
		}
		ROXML_FREE(name);
	}
}

#endif /* ROXML_C */

