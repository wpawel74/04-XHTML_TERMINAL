#include "xhtml_gp.h"

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
