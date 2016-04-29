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
#include "string.h"

struct XHTML_GP_OBJ_META {
	struct XHTML_GP_BASE	b;
	int						expires;
} ATTR_PACKED;

void XHTML_GP_meta_DRAW( GL *nGL, node_t *xml_node ){
	if( !xml_node->wme ) {
		struct XHTML_GP_OBJ_META *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_META) );
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;

		for( it = 0; it < nb_attr; it++ ){
			if( ( strcmp( "http_equiv", roxml_get_attr_nth(xml_node, it)) == 0 ) &&
				( strcmp( "expires", roxml_get_attr_val_nth(xml_node, it)) == 0 ) )
				for( it++; it < nb_attr; it++ )
					if( strcmp( "content", roxml_get_attr_nth(xml_node, it)) == 0 )
						scanf( roxml_get_attr_val_nth(xml_node, it), "%d", &obj->expires );
		}
		obj->b.type = XHTML_GP_META;
		xml_node->wme = obj;
	}
	return;
}
