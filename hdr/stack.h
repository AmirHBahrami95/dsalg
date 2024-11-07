#ifndef __STACK_H
#define __STACK_H
#include "./libs.h"
#include "./box.h"

#define STACK_E Box
#define st_free_e box_free
#define STACK_STR_SIZE STD_STR_SIZE

typedef struct struct_stack{
	STACK_E **es; // elements
	int size;
	int cap;
	char title[STACK_STR_SIZE];
} Stack;

Stack *st_init_full(const char *title,int cap);
#define st_init(x) st_init_full( "[UNNAMED]" , (x) )

void st_free(Stack *s);
void st_print(const Stack *s);
void st_expand(Stack *s,int extra_space);
void st_resize(Stack *s,int new_size);

int st_push(Stack *s,const char *v);

STACK_E *st_pop(Stack *s);
STACK_E *st_peak(const Stack *s);

#ifdef STACK_DEBUG
void st_test();
#endif

#endif
