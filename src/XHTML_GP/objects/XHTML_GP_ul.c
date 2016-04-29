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

struct XHTML_GP_OBJ_UL {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

static void XHTML_GP_ul_DRAW_SON( GL *nGL, node_t *xml_node ){
	int it;
	for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(xml_node, it);

		ASSERT(bra);

		XHTML_GP_DRAW_NODE( nGL, bra );

		//GL_setNL( w );
	}
}
void XHTML_GP_ul_DRAW( GL *nGL, node_t *xml_node ){
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_UL *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_UL) );
		obj->b.type = XHTML_GP_UL;
		xml_node->wme = obj;
	}

	XHTML_GP_ul_DRAW_SON( nGL, xml_node );
	return;
}
