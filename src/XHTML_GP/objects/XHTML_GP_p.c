#include "xhtml_gp.h"

#define STYLE_SET_ALIGN( s, a )				s = ((s & 0xfffc) | a);
#define STYLE_SET_FLOAT( s, f )				s = ((s & 0xffe3) | f);
#define STYLE_SET_MARGIN( s, m )			s = ((s & 0xf0ff) | m);
#define STYLE_SET_FONT( s, f )				s = ((s & 0xefff) | f);
#define STYLE_SET_DECOR( s, d )				s = ((s & 0x3fff) | d);

struct XHTML_GP_OBJ_P {
	struct XHTML_GP_BASE	b;
	GL_STYLE				style;
	node_t					*xml_node;
} ATTR_PACKED;

static void XHTML_GP_p_DRAW_SON( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_P *obj = (struct XHTML_GP_OBJ_P *)xml_node->wme;
	const char *_text = roxml_get_ptr_content( xml_node );
	char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
	int it;
	for( it = 0; it < roxml_get_son_nb(xml_node); it++ ){
		node_t	*bra = roxml_get_son_nth(xml_node, it);

		ASSERT(bra);
		memset( text, 0, sizeof(text) );

		if( ((unsigned int)bra->buf) + bra->pos - 1 - ((unsigned int)(_text)) > 0 ){
			strncpy( text, _text, ((unsigned int)bra->buf + bra->pos) - 1 - (unsigned int)_text );

			//_D((" ---> TEXT %s", text ));

			/* --------------------------------------------------
			 *           draw text on surface here
			 * --------------------------------------------------*/
			GL_setStyle( nGL, obj->style );
			GL_drawText( nGL, text, strlen(text), &obj->b );

		}
		_text = bra->buf + roxml_end_offset(bra);
		XHTML_GP_DRAW_NODE( nGL, bra );
	}
}

void XHTML_GP_p_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_P *obj = NULL;
	int it;

	if( !xml_node->wme ){
		obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_P) );
		int nb_attr = roxml_get_nb_attr( xml_node );

		STYLE_SET_ALIGN( obj->style, ALIGN_LEFT);

		for( it = 0; it < nb_attr; it++ ){
			if( ( strcmp( "style", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				if( strstr( val, "text-align:left" ) )
					STYLE_SET_ALIGN( obj->style, ALIGN_LEFT );
				if( strstr( val, "text-align:center" ) )
					STYLE_SET_ALIGN( obj->style, ALIGN_CENTER );
				if( strstr( val, "text-align:right" ) )
					STYLE_SET_ALIGN( obj->style, ALIGN_RIGHT );

				if( strstr( val, "text-decoration:none" ) )
					STYLE_SET_DECOR( obj->style, DECOR_NONE );
				if( strstr( val, "text-decoration:blink" ) )
					STYLE_SET_DECOR( obj->style, DECOR_BLINK );

				if( strstr( val, "margin:left" ) )
					STYLE_SET_MARGIN( obj->style, MARGIN_LEFT );
				if( strstr( val, "margin:center" ) )
					STYLE_SET_MARGIN( obj->style, MARGIN_CENTER );
				if( strstr( val, "margin:right" ) )
					STYLE_SET_MARGIN( obj->style, MARGIN_RIGHT );

				if( strstr( val, "font-weight:normal" ) )
					STYLE_SET_FONT( obj->style, FONT_NORMAL );
				if( strstr( val, "font-weight:bold" ) )
					STYLE_SET_FONT( obj->style, FONT_BOLD );

				if( strstr( val, "float:left" ) )
					STYLE_SET_FLOAT( obj->style, FLOAT_LEFT );
				if( strstr( val, "float:right" ) )
					STYLE_SET_FLOAT( obj->style, FLOAT_RIGHT );
			}
		}

		obj->xml_node = xml_node;
		obj->b.type = XHTML_GP_P;
		xml_node->wme = obj;
	} else
		obj = xml_node->wme;
	if( STYLE_GET_FLOAT( obj->style ) ){
		GL_setCursor(nGL, 0, GL_getCursor(nGL)->Y);
	}
	if( roxml_get_son_nb(xml_node) == 0 ){
		char text[ XHTML_CONTENT_TEXT_MAX_CHARS ];
		roxml_get_content(xml_node, text);

		//_D((" ---> TEXT %s", text ));
		/* --------------------------------------------------
		 *           draw text on surface here
		 * --------------------------------------------------*/
		GL_setStyle( nGL, obj->style );
		GL_drawText( nGL, text, strlen(text), &obj->b );

	} else
		XHTML_GP_p_DRAW_SON( nGL, xml_node );

	return;
}
