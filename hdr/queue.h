#ifndef __QUEUE_H
#define __QUEUE_H 1
#include "./linked_list.h"

/*
	This implementation just uses linked list as 
	the data holder simply because of similarities
*/
typedef LLNode QNode;
typedef LList Queue;
typedef Queue Q;

Q *q_init();

QNode *q_deq(Q *q);

void q_enq(Q *q);

int q_isempty(Q *q);

#endif
