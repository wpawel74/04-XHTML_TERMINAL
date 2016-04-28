#include "xhtml_gp.h"

struct XHTML_GP_OBJ_TITLE {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
} ATTR_PACKED;

static const char* XHTML_GP_title( node_t *xml_node ){
	char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
	roxml_get_content(xml_node, text);
	return text;
}

void XHTML_GP_title_DRAW( GL *nGL, node_t *xml_node ){
	char * text = XHTML_GP_title( xml_node );
	if( !xml_node->wme ){
		struct XHTML_GP_OBJ_TITLE *obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_TITLE) );
		obj->b.type = XHTML_GP_TITLE;
		xml_node->wme = obj;
	}
	//-------------------------------------
	//    Text should be in one line!!!
	//-------------------------------------
	GL_drawText( nGL, text, strlen(text), xml_node->wme );
	return;
}
