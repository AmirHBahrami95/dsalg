#ifndef __LINKED_LIST 
#define __LINKED_LIST 1

typedef struct ll_node_s{
	// use either the int or char val depending on your choice
	char val[32];
	int ival; // just in case
	struct ll_node_s *next;
	struct ll_node_s *prev;
} LLNode;

typedef struct ll_s{
	char title[32]; // for easy debugging
	LLNode *first;
	LLNode *last;
	int size;
} LList;

LList *ll_init_full(const char *title);
#define ll_init() ll_init_full("[unnamed]") 

void 	ll_free(LList *l);
void	ll_print(const LList *l);
void 	ll_add(LList *l,const char *s);
void 	ll_add_ival(LList *l,int ival);

int 	ll_delby_val(LList *l,const char *s);
int		ll_delby_ival(LList *l,int ival);

LLNode *ll_fby_index(const LList *l,int idx);
LLNode *ll_fby_val(const LList *l,const char *val);
LLNode *ll_fby_ival(const LList *l,int ival);

#ifdef LLIST_DEBUG
void ll_test();
#endif

#endif
