#ifndef XHTML_GP_H
#define XHTML_GP_H
#include "os_compat.h"
#include "roxml.h"
#include "GL.h"

#define XHTML_ALLOC(v)			NULL
#define XHTML_FREE(v)			NULL

typedef enum {
	XHTML_GP_A,
	XHTML_GP_BODY,
	XHTML_GP_BR,
	XHTML_GP_FORM,
	XHTML_GP_HEAD,
	XHTML_GP_HTML,
	XHTML_GP_INPUT,
	XHTML_GP_LI,
	XHTML_GP_META,
	XHTML_GP_OPTION,
	XHTML_GP_P,
	XHTML_GP_SELECT,
	XHTML_GP_TITLE,
	XHTML_GP_UL,
	XHTML_GP_TEXTAREA
} XHTML_GP_TYPE;

struct XHTML_GP_BASE;
struct XHTML_GL_P;
struct XHTML_GL_P {
	struct COORD			begin;
	struct COORD			end;
	struct XHTML_GL_P		*next;
	struct XHTML_GP_BASE	*xmle;
} ATTR_PACKED;

struct XHTML_GP_BASE {
	XHTML_GP_TYPE			type;
	struct XHTML_GL_P		*p_root;
	struct XHTML_GP_BASE	*parent;
	struct XHTML_GP_BASE	*next;
};

#define XHTML_CONTENT_TEXT_MAX_CHARS		60

void XHTML_GP_DRAW_NODE( GL *nGL, node_t *node );
void XHTML_GP_title_DRAW( GL *nGL, node_t *node );
void XHTML_GP_p_DRAW( GL *nGL, node_t *node );
void XHTML_GP_br_DRAW( GL *nGL, node_t *node );
void XHTML_GP_meta_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_a_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_ul_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_li_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_input_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_select_DRAW( GL *nGL, node_t *xml_node );
void XHTML_GP_option_DRAW( GL *nGL, node_t *xml_node );

struct XHTML_GP_OBJ_SELECT;
void XHTML_GP_select_prev( struct XHTML_GP_OBJ_SELECT *obj );
void XHTML_GP_select_next( struct XHTML_GP_OBJ_SELECT *obj );

#endif /* XHTML_GP_H */
