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

struct XHTML_GP_OBJ_TITLE {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

static const char* XHTML_GP_title( node_t *xml_node ){
	char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
	roxml_get_content(xml_node, text);
	return text;
}

void XHTML_GP_title_DRAW( GL *nGL, node_t *xml_node ){
	char * text = XHTML_GP_title( xml_node );
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_TITLE *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_TITLE) );
		obj->b.type = XHTML_GP_TITLE;
		xml_node->wme = obj;
	}
	//-------------------------------------
	//    Text should be in one line!!!
	//-------------------------------------
	GL_drawText( nGL, text, strlen(text), xml_node->wme );
	return;
}
