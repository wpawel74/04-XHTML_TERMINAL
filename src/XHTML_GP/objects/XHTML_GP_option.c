#include "xhtml_gp.h"

struct XHTML_GP_OBJ_OPTION {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
	BOOLEAN					selected;
} ATTR_PACKED;

void XHTML_GP_option_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_OPTION *obj = NULL;
	if( !xml_node->wme ){
		obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_OPTION) );
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;
		for( it = 0; it < nb_attr; it++ )
			if( ( strcmp( "selected", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				if( strcmp( val, "selected" ) == 0 ){
					obj->selected = TRUE;
				}
			}
		obj->b.type = XHTML_GP_OPTION;
		xml_node->wme = obj;
	} else
		obj = xml_node->wme;

	if( obj->selected == TRUE ){
		char text[ XHTML_CONTENT_TEXT_MAX_CHARS ] = { '<' };
		roxml_get_content(xml_node, text + 1);
		text[ strlen(text) ] = '>';

		_D((" ---> SELECTED (*) %s", text ));
		/* --------------------------------------------------
		 *           draw text on surface here
		 * --------------------------------------------------*/
		GL_drawText( nGL, text, strlen(text), xml_node->wme );
	}
	return;
}
