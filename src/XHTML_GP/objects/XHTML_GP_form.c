#include "xhtml_gp.h"

struct XHTML_GP_OBJ_FORM {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

void XHTML_GP_form_DRAW( GL *nGL, node_t *xml_node ){
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_FORM *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_FORM) );
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;
		for( it = 0; it < nb_attr; it++ ){
			if( ( strcmp( "action", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
			}
			if( ( strcmp( "method", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
			}
		}
		obj->b.type = XHTML_GP_FORM;
		xml_node->wme = obj;
	}
	return;
}
