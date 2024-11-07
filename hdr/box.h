#ifndef __BOX_H
#define __BOX_H 1
#include "./libs.h"

#define BOX_STR_SIZE STD_STR_SIZE

/* just some common box to put in all collections for testing */
typedef struct struct_box{
	int ival;
	int bval; // boolean
	char val[BOX_STR_SIZE];
} Box;

Box *box_init_full(const char *val,int ival,int bval);
#define box_init( x ) box_init_full( (x) ,0 ,0)

void box_free(Box *b);

#endif
