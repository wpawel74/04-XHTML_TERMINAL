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

struct XHTML_GP_OBJ_TEXTAREA {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
	char					text[200];
} ATTR_PACKED;

static const char* XHTML_GP_textarea_name( node_t *xml_node ){
	int nb_attr = roxml_get_nb_attr( xml_node );
	int it;
	for( it = 0; it < nb_attr; it++ )
		if( ( strcmp( "name", roxml_get_attr_nth(xml_node, it)) == 0 ) )
			return roxml_get_attr_val_nth(xml_node, it);
	return NULL;
}

void XHTML_GP_textarea_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_TEXTAREA *obj = NULL;
	if( !xml_node->wme ){
		obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_TEXTAREA) );
		obj->b.type = XHTML_GP_TEXTAREA;
		xml_node->wme = obj;
	} else
		obj = xml_node->wme;

	GL_drawText( nGL, obj->text, strlen(obj->text), xml_node->wme );
	return;
}
