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
#include "os_compat.h"
#include "config.h"

static char __xhtml_buff[ XHTML_GP_BUFFER_SIZE ];
static node_t *__xhtml_node = NULL;

void XHTML_GP_load( const char *xhtml_gp ){
	if( strlen(xhtml_gp) > sizeof(__xhtml_buff) ){
		_D(("E: xhtml source size is too big! (%d bytes)\n", strlen(xhtml_gp)));
		return;
	}
	bzero( __xhtml_buff, sizeof(__xhtml_buff) );
	memcpy( __xhtml_buff, xhtml_gp, strlen(xhtml_gp) );
	__xhtml_node = roxml_load_buf( xhtml_gp );
}

void XHTML_GP_DRAW_NODE( GL *nGL, node_t *xml_node ){
	const char *name = roxml_get_name( xml_node );

	if( strcmp( name, "title" ) == 0 ){
		XHTML_GP_title_DRAW( nGL, xml_node );
	} else if( strcmp( name, "p" ) == 0 ){
		XHTML_GP_p_DRAW( nGL, xml_node );
	} else if( strcmp( name, "br" ) == 0 ){
		XHTML_GP_br_DRAW( nGL, xml_node );
	} else if( strcmp( name, "meta" ) == 0 ){
		XHTML_GP_meta_DRAW( nGL, xml_node );
	} else if( strcmp( name, "a" ) == 0 ){
		XHTML_GP_a_DRAW( nGL, xml_node );
	} else if( strcmp( name, "ul" ) == 0 ){
		XHTML_GP_ul_DRAW( nGL, xml_node );
	} else if( strcmp( name, "li" ) == 0 ){
		XHTML_GP_li_DRAW( nGL, xml_node );
	} else if( strcmp( name, "input" ) == 0 ){
		XHTML_GP_input_DRAW( nGL, xml_node );
	} else if( strcmp( name, "select" ) == 0 ){
		XHTML_GP_select_DRAW( nGL, xml_node );
	} else {
		int it;
		for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
			node_t	*bra = roxml_get_son_nth(xml_node, it);
			XHTML_GP_DRAW_NODE( nGL, bra );
		}
	}
}
