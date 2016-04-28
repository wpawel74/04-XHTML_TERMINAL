#include <string.h>
#include "xhtml_gp.h"

typedef enum {
	XHTML_GP_INPUT_TEXT,
	XHTML_GP_INPUT_PASSWORD,
	XHTML_GP_INPUT_CHECKBOX,
	XHTML_GP_INPUT_RADIO,
	XHTML_GP_INPUT_SUBMIT,
	XHTML_GP_INPUT_HIDDEN
} XHTML_GP_INPUT_TYPE;

typedef enum {
	XHTML_GP_INPUT_M_TEXT,
	XHTML_GP_INPUT_M_DIGITS,
	XHTML_GP_INPUT_M_DIALPAD
} XHTML_GP_INPUT_MODE;

struct XHTML_GP_OBJ_INPUT {
	struct XHTML_GP_BASE	b;
	node_t					*xml_node;
	XHTML_GP_INPUT_TYPE		type;
	XHTML_GP_INPUT_MODE		mode;
	BOOLEAN					disabled;
	BOOLEAN					checked;
	int						max_len;
	char					value[100];
} ATTR_PACKED;

static const char* XHTML_GP_input_name( node_t *xml_node ){
	int nb_attr = roxml_get_nb_attr( xml_node );
	int it;
	for( it = 0; it < nb_attr; it++ )
		if( ( strcmp( "name", roxml_get_attr_nth(xml_node, it)) == 0 ) )
			return roxml_get_attr_val_nth(xml_node, it);
	return NULL;
}

void XHTML_GP_input_DRAW( GL *nGL, node_t *xml_node ){
	struct XHTML_GP_OBJ_INPUT *obj = NULL;
	if( !xml_node->wme ){
		int nb_attr = roxml_get_nb_attr( xml_node );
		int it;
		obj = XHTML_ALLOC( sizeof(struct XHTML_GP_OBJ_INPUT) );
		memset( obj, 0, sizeof(struct XHTML_GP_OBJ_INPUT) );

		for( it = 0; it < nb_attr; it++ ){
			if( ( strcmp( "type", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				if( strcmp( val, "text" ) == 0 ){
					obj->type = XHTML_GP_INPUT_TEXT;
				} else if ( strcmp( val, "password" ) == 0 ){
					obj->type = XHTML_GP_INPUT_PASSWORD;
				} else if ( strcmp( val, "checkbox" ) == 0 ){
					obj->type = XHTML_GP_INPUT_CHECKBOX;
				} else if ( strcmp( val, "radio" ) == 0 ){
					obj->type = XHTML_GP_INPUT_RADIO;
				} else if ( strcmp( val, "submit" ) == 0 ){
					obj->type = XHTML_GP_INPUT_SUBMIT;
				} else if ( strcmp( val, "hidden" ) == 0 ){
					obj->type = XHTML_GP_INPUT_HIDDEN;
				}
			}
			if( ( strcmp( "value", roxml_get_attr_nth(xml_node, it)) == 0 )){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				strncpy( obj->value, val, strlen(val) > sizeof(obj->value)? sizeof(obj->value): strlen(val) );
			}
			if( ( strcmp( "disabled", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				//const char *val = roxml_get_attr_val_nth(xml_node, it);
				obj->disabled = TRUE;
			}
			if( ( strcmp( "checked", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				//const char *val = roxml_get_attr_val_nth(xml_node, it);
				obj->checked = TRUE;
			}
			if( ( strcmp( "inputmode", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				if( strstr( val, "text" ) == 0 ){
					obj->mode = XHTML_GP_INPUT_M_TEXT;
				} else if ( strstr( val, "digits" ) == 0 ){
					obj->mode = XHTML_GP_INPUT_M_DIGITS;
				} else if ( strstr( val, "dialpad" ) == 0 ){
					obj->mode = XHTML_GP_INPUT_M_DIALPAD;
				}
			}
			if( ( strcmp( "maxlength", roxml_get_attr_nth(xml_node, it)) == 0 ) ){
				const char *val = roxml_get_attr_val_nth(xml_node, it);
				obj->max_len = atoi( val );
			}
		}
		obj->b.type = XHTML_GP_INPUT;
		xml_node->wme = obj;
	} else
		obj = xml_node->wme;

	if( obj->type == XHTML_GP_INPUT_TEXT ||
		obj->type == XHTML_GP_INPUT_PASSWORD ) {
		if( strlen( obj->value ) )
			GL_drawText( nGL, obj->value, strlen(obj->value), xml_node->wme );
	} else if( obj->type == XHTML_GP_INPUT_RADIO ){
		struct XHTML_GL_P *xml_gp = NULL;
		if( obj->checked ){
			const unsigned char radio_checked[] = {
				0x2c, //  ####
				0x42, // #    #
				0x81, //#      #
				0x99, //#  ##  #
				0x99, //#  ##  #
				0x81, //#      #
				0x42, // #    #
				0x2c, //  ####
			};
			drm_PutBitmap( nGL->drm, GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y, 8, 8, radio_checked );
		} else {
			const unsigned char radio_icon[] = {
				0x2c, //  ####
				0x42, // #    #
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0x42, // #    #
				0x2c, //  ####
			};
			drm_PutBitmap( nGL->drm, GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y, 8, 8, radio_icon );
		}
		GL_setCursor(nGL, GL_getCursor(nGL)->X + 8, GL_getCursor(nGL)->Y);
	} if( obj->type == XHTML_GP_INPUT_CHECKBOX ){
		struct XHTML_GL_P *xml_gp = NULL;
		if( obj->checked ){
			const unsigned char checkbox_checked[] = {
				0xfd, //###### #
				0x83, //#     ##
				0x46, // #   ##
				0x7d, // ##### #
				0x79, // ####  #
				0xb1, //# ##   #
				0xa1, //# #    #
				0xff, //########
			};
			drm_PutBitmap( nGL->drm, GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y, 8, 8, checkbox_checked );
		} else {
			const unsigned char checkbox_icon[] = {
				0xff, //########
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0x81, //#      #
				0xff, //########
			};
			drm_PutBitmap( nGL->drm, GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y, 8, 8, checkbox_icon );
		}
		GL_setCursor(nGL, GL_getCursor(nGL)->X + 8, GL_getCursor(nGL)->Y);
	}
	return;
}
