#include "../../hdr/libs.h"
#include <stdio.h>
#include "../../hdr/linked_list.h"

static LLNode *llnode_init(const char *s,int ival,LLNode *prev,LLNode *next){
	LLNode *ln=(LLNode *)malloc(sizeof(LLNode));
	if(*s)strncpy(ln->val,s,STD_STR_SIZE-1); // -1 for the last '\0' truncation
	else strcpy(ln->val,"\0"); // just block the value
	ln->ival=ival;
	ln->prev=prev;
	ln->next=next;
	return ln;
}

LList *ll_init_full(const char *title){
	LList *ll=(LList *)malloc(sizeof(LList));
	ll->first=NULL;
	ll->last=NULL;
	ll->size=0;
	if(title) strcpy(ll->title,title);
	return ll;
}

void ll_free(LList *l){
	if(!l)return;
	LLNode *temp_next;
	for(LLNode *temp=l->first;temp;){
		temp_next=temp->next;
		memset(temp, 0, sizeof(LLNode));
		free(temp);
		temp=temp_next;
	}
	l->first=NULL;
	l->last=NULL;
	memset(l,0,sizeof(LList));
	free(l);
}

static void ll_add_node(LList *l,const char *s,int ival){
	LLNode *new_node=llnode_init(s,ival,NULL,NULL);
	LLNode *temp;
	for(temp=l->first;temp && temp->next;temp=temp->next);
	if(temp) temp->next=new_node;
	new_node->prev=temp;
	l->last=new_node;
	if(l->size==0) l->first=l->last;
	l->size=l->size+1;
}

void ll_print(const LList *l){
	if(!l){
		printf("[uninitialized]:LList *\n");
		return;
	}
	if(l->title)printf("%s\t",l->title);
	if(l->size>0)printf("size:%d",l->size);
	printf("\n");

	int i=0;
	for(LLNode *temp=l->first;temp;temp=temp->next){
		printf("%d:\t{%d,'%s'}\n",i,temp->ival,temp->val);
		++i;
	}
	printf("==================\n");
}

void ll_add(LList *l,const char *s){
	ll_add_node(l,s,0);
}

void ll_add_ival(LList *l,int ival){
	ll_add_node(l,"\0",ival);
}

int ll_delby_val(LList *l,const char *s){
	LLNode *temp;
	if(l->size==0) return 0; // empty list, nigger!
	for(LLNode *curr=l->first;curr;curr=curr->next){
		if(strcmp(curr->val,s)==0){
			// temp=curr->next;
			if(curr->prev) curr->prev->next=curr->next;
			if(curr->next) curr->next->prev=curr->prev;
			curr->next=NULL;
			curr->prev=NULL;
			free(curr);
			curr=NULL;
			return 1;
		}
	}
	return 0;
}

int ll_delby_ival(LList *l, int ival){
	LLNode *temp;
	if(l->size==0) return 0; // empty list, nigger!
	for(LLNode *curr=l->first;curr;curr=curr->next){
		if(ival==curr->ival){
			// temp=curr->next;
			if(curr->prev) curr->prev->next=curr->next;
			if(curr->next) curr->next->prev=curr->prev;
			curr->next=NULL;
			curr->prev=NULL;
			free(curr);
			curr=NULL;
			return 1;
		}
	}
	return 0;
}

LLNode *ll_fby_index(const LList *l,int idx){
	LLNode *temp=NULL;
	if(idx>l->size) return NULL;
	for(temp=l->first;temp && idx>0;temp=temp->next) idx--;
	return temp; // NULL included
}

LLNode *ll_fby_val(const LList *l,const char *val){
	for(LLNode *temp=l->first;temp;temp=temp->next)
		if(strcmp(temp->val,val)==0)return temp;
	return NULL;
}

LLNode *ll_fby_ival(const LList *l,int ival){
	for(LLNode *temp=l->first;temp;temp=temp->next)
		if(ival==temp->ival)return temp;
	return NULL;
}

#ifdef LLIST_DEBUG
void ll_test(){
	printf("[-DLLIST_DEBUG]\n");
	LList *l=ll_init_full("my_beech");

	ll_add(l,"1");
	ll_add_ival(l,1);
	ll_add(l,"1");
	ll_add(l,"2");
	ll_add_ival(l,2);
	ll_add(l,"3");
	ll_add_ival(l,3);
	ll_add(l,"4");
	ll_add_ival(l,4);
	ll_add_ival(l,5);
	ll_add_ival(l,6);
	ll_print(l);
	l=NULL;
	ll_free(l);
	ll_free(l);
	ll_print(l);
} 
#endif
