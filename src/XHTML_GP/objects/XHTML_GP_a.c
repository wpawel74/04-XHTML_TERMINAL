#include "xhtml_gp.h"

struct XHTML_GP_OBJ_A {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

static const char* XHTML_GP_a_herf( node_t *xml_node ){
	int nb_attr = roxml_get_nb_attr( xml_node );
	int it;
	for( it = 0; it < nb_attr; it++ )
		if( ( strcmp( "herf", roxml_get_attr_nth(xml_node, it)) == 0 ) )
			return roxml_get_attr_val_nth(xml_node, it);
	return NULL;
}

static void XHTML_GP_a_DRAW_SON( GL *nGL, node_t *xml_node ){
	int it;
	for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(xml_node, it);

		ASSERT(bra);

		XHTML_GP_DRAW_NODE( nGL, bra );
	}
}

void XHTML_GP_a_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_A *obj = NULL;
	if( !xml_node->wme ){
		obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_A) );
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;
		for( it = 0; it < nb_attr; it++ )
			if( ( strcmp( "id", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				if( strstr( val, "softkey1" ) == 0 ){
				} else if ( strstr( val, "softkey2" ) == 0 ){
				} else if ( strstr( val, "softkey-back" ) == 0 ){
				}
			}
		obj->b.type = XHTML_GP_A;
		xml_node->wme = obj;
	}

	if( roxml_get_son_nb(xml_node) == 0 ){
		char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
		roxml_get_content(xml_node, text);

		_D((" ---> HYPERLINK %s (link to %s)", text, XHTML_GP_a_herf(xml_node) ));
		/* --------------------------------------------------
		 *           draw text on surface here
		 * --------------------------------------------------*/
		GL_drawText( nGL, text, strlen(text), &obj->b );

	} else
		XHTML_GP_a_DRAW_SON( nGL, xml_node );
	return;
}
