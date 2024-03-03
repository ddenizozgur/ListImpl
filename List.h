#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

typedef struct List
{
  void *data;
  struct List *next,*prev;
} List;

static List *List_Alloc(void *data)
{
  List *node=NULL;
  node=(List*)malloc(sizeof(List));
  node->next=node->prev=node;
  node->data=data;
  return node;
}

static int List_Size(List *root)
{//Returns cnt of nodes
  int size=0;
  if (root==NULL)
    return size;
  List *temp=root;
  do {
    size++;
    temp=temp->next;
  } while (temp!=root);
  return size;
}

static int List_Insert(List *pred,void *data)
{//Returns 0 on success, -1 on failure
  if (pred==NULL)
    return -1;
  List *node=List_Alloc(data);
  List *next=pred->next;
  pred->next=node;
  node->next=next;
  node->prev=pred;
  next->prev=node;
  return 0;
}

static void List_PushBack(List **_root,void *data)
{
  if (*_root==NULL) {
    *_root=List_Alloc(data);
    return;
  }
  List_Insert((*_root)->prev,data);
}

static void List_PushFront(List **_root,void *data)
{
  List *node=List_Alloc(data);
  if (*_root==NULL) {
    *_root=node;
    return;
  }
  List *tail=(*_root)->prev;
  tail->next=node;
  node->next=*_root;
  node->prev=tail;
  (*_root)->prev=node;
  *_root=node;
}

static int List_Remove(List **_link)
{//Returns 0 on success, -1 on failure
  if (*_link==NULL)
    return -1;
  if (*_link==(*_link)->next) {
    free(*_link);
    *_link=NULL;
    return 0;
  }
  List *next=(*_link)->next;
  List *prev=(*_link)->prev;
  free(*_link);
  *_link=NULL;
  prev->next=next;
  next->prev=prev;
  return 0;
}

static int List_PopBack(List **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  List_Remove(&(*_root)->prev);
  return 0;
}

static int List_PopFront(List **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  List *next=(*_root)->next;
  List_Remove(_root);
  *_root=next;
  return 0;
}

static int List_Delete(List **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  List *temp=*_root;
  do {
    List *next=temp->next;
    free(temp);
    temp=next;
  } while (temp!=*_root);
  *_root=NULL;
  return 0;
}
#endif//LIST_H
