#include "../../hdr/libs.h"
#include "../../hdr/stack.h"

Stack *st_init_full(const char *title,int cap){
	Stack *s=(Stack *)malloc(sizeof(Stack));
	s->size=0;
	s->cap=cap;
	strncpy(s->title,title,STACK_STR_SIZE-1);
	s->es=(STACK_E **)malloc(sizeof(STACK_E)*cap);
	return s;
}

void st_free(Stack *s){
	if(!s) return;
	for(int i=0;i<s->size;i++){
		memset(s->es[i],0,sizeof(STACK_E));
		st_free_e(s->es[i]);
	}
	memset(s,0,sizeof(STACK_E));
	free(s);
}

void st_print(const Stack *s){
	printf("%s:%d/%d\n",s->title,s->size,s->cap);
	for(int i=0; i<(s->cap); i++){
		if(s->es[i])
			printf("%d:'%s'\n",i,s->es[i]->val);
	}
	// printf("\n");
}

void st_resize(Stack *s,int new_cap){
	STACK_E **es=s->es; // remember old elems
	if(new_cap==s->cap) return; // won't do it, mate!
	s->cap=new_cap;
	if(new_cap<=0) new_cap=0;
	else s->es=(STACK_E **)malloc(sizeof(STACK_E)*(new_cap)); // allocate new
	if(s->size==0) return;

	// copy old ones into new elements (by ref)
	int num_es=( (s->size)>new_cap)?new_cap:s->size;
	int i=0;
	for(;i<num_es;i++) s->es[i]=es[i];
	
	// when shrinking
	if(new_cap<(s->size)){
		es=&es[i]; // move pointer forward
		for(i=0;es[i];i++){
			memset(es[i],0,sizeof(STACK_E));
			st_free_e(es[i]);
		}
	}

	// setting the size (not cap)
	s->size=num_es;
}	

void st_expand(Stack *s,int extra_space){
	if(extra_space<=0)return; // won't do it, mate!
	int new_cap=s->cap+extra_space;
	st_resize(s,new_cap);
}

int st_push(Stack *s,const char *v){
	if(s->size>=s->cap)return 0;
	int i=0;
	for(i=0; i<(s->cap-1) && s->es[i]; i++);
	s->es[i]=box_init(v);
	s->size++;
	return 1;
}

STACK_E *st_pop(Stack *s){
	if(s->size==0) return NULL;
	STACK_E *last=s->es[s->size-1];
	s->es[s->size-1]=NULL;
	s->size--;
	return last;
}

STACK_E *st_peak(const Stack *s){
	return s->size==0?NULL:s->es[s->size-1];
}

#ifdef STACK_DEBUG
static void st_populate_test(Stack *s,char *template,int num_elems,int do_output){
	
	// sample element
	char str[64];
	strcpy(str,template);
	int slen=strlen(template);

	// populating
	for(int i=0;i<num_elems;i++){
		if(!st_push(s,str)){
			if(do_output)
				fprintf(stderr,"couldn't push the fucker:'%s'\n",str);
		}
		str[slen-1]++;
	}

}

static void st_resize_test(Stack *s){

	st_populate_test(s,"initial0",20,0);
	printf("printing-0:\n");
	st_print(s);

	// resize to 0 (or negative)
	st_resize(s,0);
	st_populate_test(s,"zero0",20,0);
	printf(">>>>with-size-zero>>>>\n");
	st_print(s);

	// testing st_expand
	st_expand(s,8);
	st_populate_test(s,"expanded0",20,0);
	printf(">>>>printing-expanded>>>>\n");
	st_print(s);
	
	// testing shrinking the size
	st_resize(s,2);
	st_populate_test(s,"shrunk0",20,0);
	printf(">>>>shrinking>>>>\n");
	st_print(s);
}

static void st_op_test(Stack *s,int offset){

	STACK_E *e;

	// testing peak
	for(int i=0;i<((s->cap)+offset);i++) {
		e=st_peak(s);
		if(e) printf("%d:peak '%s'\n",i,e->val);
		else fprintf(stderr,"%d:couldn't peak from '%s'\n",i,s->title);
	}

	// testing pop
	for(int i=0;i<((s->cap)+offset);i++){
		if((e=st_pop(s))!=NULL)
			printf("%d:pop '%s'\n",i,e->val);
		else fprintf(stderr,"%d:couldn't pop\n",i);
	}
	printf(">>>>printing-after-pop>>>>\n");
	st_print(s);
}

void st_test(){
	printf("[-DSTACK_DEBUG]\n");
	Stack *s=st_init_full("test",8);
	
	printf("======={{ peak & pop should fail }}==============================\n");
	st_op_test(s,0);

	printf("======={{ should resize in following order:8->0->8->2 }}=========\n");
	st_resize_test(s);
	
	printf("======={{ should be able to peak and pop (up to 8) }}============\n");
	st_resize(s,8);
	st_populate_test(s,"dipshit-0",12,0);
	printf(">>>>after populting>>>>\n");
	st_print(s);
	st_op_test(s,2);
	
	st_free(s);
	s=NULL;
	st_free(s);
}
#endif
