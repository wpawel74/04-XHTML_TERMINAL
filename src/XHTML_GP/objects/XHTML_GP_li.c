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

struct XHTML_GP_OBJ_LI {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

static void XHTML_GP_li_DRAW_SON( GL *nGL, node_t *xml_node ){
	int it;
	for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(xml_node, it);

		ASSERT(bra);

		XHTML_GP_DRAW_NODE( nGL, bra );
	}
}

void XHTML_GP_li_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_LI *obj = NULL;
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_LI *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_LI) );

		obj->b.type = XHTML_GP_LI;
		xml_node->wme = obj;
	} else
		obj = xml_node->wme;

	if( roxml_get_son_nb(xml_node) == 0 ){
		char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
		roxml_get_content(xml_node, text);

		//_D((" ---> TEXT %s", text ));
		/* --------------------------------------------------
		 *           draw text on surface here
		 * --------------------------------------------------*/
		GL_drawText( nGL, text, strlen(text), &obj->b );

		GL_setNL( nGL );

	} else
		XHTML_GP_li_DRAW_SON( nGL, xml_node );

	return;
}
