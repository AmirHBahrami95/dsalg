#include "../hdr/libs.h"
#include "../hdr/linked_list.h"
#include "../hdr/stack.h"

void debug();

int main(int argc,char **argv){
	debug();
	return 0;
}

void debug(){
	#ifdef LLIST_DEBUG
		ll_test();
	#endif
	#ifdef STACK_DEBUG
		st_test();
	#endif
}
