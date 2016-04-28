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
