#include "../../hdr/libs.h"
#include "../../hdr/box.h"

Box *box_init_full(const char *val,int ival,int bval){
	Box *b=(Box *)malloc(sizeof(Box));
	strncpy(b->val,val,BOX_STR_SIZE-1);
	b->ival=ival;
	b->bval=bval;
	return b;
}

void box_free(Box *b){
	memset(b,0,sizeof(Box));
	free(b);
}
