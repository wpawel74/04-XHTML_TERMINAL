/**
 * |----------------------------------------------------------------------
 * | Copyright (C) Pawel Wisniewski, 2016
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |----------------------------------------------------------------------
 */
#include "xhtml_gp.h"

struct XHTML_GP_OBJ_SELECT {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
	BOOLEAN					disabled;
} ATTR_PACKED;

static const char* XHTML_GP_select_name( node_t *xml_node ){
	int nb_attr = roxml_get_nb_attr( xml_node );
	int it;
	for( it = 0; it < nb_attr; it++ )
		if( ( strcmp( "name", roxml_get_attr_nth(xml_node, it)) == 0 ) )
			return roxml_get_attr_val_nth(xml_node, it);
	return NULL;
}

static void XHTML_GP_select_DRAW_SON( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_SELECT *obj = (struct XHTML_GP_OBJ_P *)xml_node->wme;
	int it;
	for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(xml_node, it);

		ASSERT(bra);

		XHTML_GP_option_DRAW( nGL, bra );
	}
}

void XHTML_GP_select_DRAW( GL *nGL, node_t *xml_node ){
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_SELECT *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_SELECT) );
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;
		for( it = 0; it < nb_attr; it++ )
			if( ( strcmp( "disabled", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				obj->disabled = TRUE;
			}
		obj->b.type = XHTML_GP_SELECT;
		xml_node->wme = obj;
	}
	XHTML_GP_select_DRAW_SON( nGL, xml_node );
	return;
}

struct XHTML_GP_OBJ_OPTION {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
	BOOLEAN					selected;
} ATTR_PACKED;

/*---------------------------------------------------
 *
 *---------------------------------------------------*/

void XHTML_GP_select_prev( struct XHTML_GP_OBJ_SELECT *obj ){
	struct XHTML_GP_OBJ_OPTION	*sele = NULL,
								*last = NULL;
	int it;
	for( it = 0; it < roxml_get_son_nb(obj->xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(obj->xml_node, it);
		struct XHTML_GP_OBJ_OPTION *option = (struct XHTML_GP_OBJ_OPTION *)bra->wme;

		if( strcmp( "option", roxml_get_name( bra ) ) != 0 )
			return;

		if( sele && last ){
			last->selected = TRUE;
			return;
		}
		if( bra->wme ){
			struct XHTML_GP_OBJ_OPTION *option = (struct XHTML_GP_OBJ_OPTION *)bra->wme;
			if( option->selected == TRUE ){
				sele = option;
				option->selected = FALSE;

			}
		}
		last = option;
	}
	if( last && sele )
		last->selected = TRUE;
}

void XHTML_GP_select_next( struct XHTML_GP_OBJ_SELECT *obj ){
	struct XHTML_GP_OBJ_OPTION	*sele = NULL,
								*first = NULL;
	int it;
	for( it = 0; it < roxml_get_son_nb(obj->xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(obj->xml_node, it);
		struct XHTML_GP_OBJ_OPTION *option = (struct XHTML_GP_OBJ_OPTION *)bra->wme;

		if( strcmp( "option", roxml_get_name( bra ) ) != 0 )
			return;

		if( it == 0 )
			first = option;

		if( sele ){
			option->selected = TRUE;
			return;
		}
		if( bra->wme ){
			struct XHTML_GP_OBJ_OPTION *option = (struct XHTML_GP_OBJ_OPTION *)bra->wme;
			if( option->selected == TRUE ){
				sele = option;
				option->selected = FALSE;

			}
		}
	}
	if( first )
		first->selected = TRUE;
}
