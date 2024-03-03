#ifndef CHARLIST_H
#define CHARLIST_H
#include <stdlib.h>

typedef struct CharList
{
  char ch;
  struct CharList *next,*prev;
} CharList;

static CharList *CharList_Alloc(char ch)
{
  CharList *node=(CharList*)malloc(sizeof(CharList));
  node->next=node->prev=node;
  node->ch=ch;
  return node;
}

static int CharList_Size(CharList *root)
{//Returns cnt of nodes
  int size=0;
  if (root==NULL)
    return size;
  CharList *temp=root;
  do {
    size++;
    temp=temp->next;
  } while (temp!=root);
  return size;
}

static int CharList_Insert(CharList *pred,char ch)
{//Returns 0 on success, -1 on failure
  if (pred==NULL)
    return -1;
  CharList *node=CharList_Alloc(ch);
  CharList *next=pred->next;
  pred->next=node;
  node->next=next;
  node->prev=pred;
  next->prev=node;
  return 0;
}

static void CharList_PushBack(CharList **_root,char ch)
{
  if (*_root==NULL) {
    *_root=CharList_Alloc(ch);
    return;
  }
  CharList_Insert((*_root)->prev,ch);
}

static void CharList_PushFront(CharList **_root,char ch)
{
  CharList *node=CharList_Alloc(ch);
  if (*_root==NULL) {
    *_root=node;
    return;
  }
  CharList *tail=(*_root)->prev;
  tail->next=node;
  node->next=*_root;
  node->prev=tail;
  (*_root)->prev=node;
  *_root=node;
}

static int CharList_Remove(CharList **_link)
{//Returns 0 on success, -1 on failure
  if (*_link==NULL)
    return -1;
  if (*_link==(*_link)->next) {
    free(*_link);
    *_link=NULL;
    return 0;
  }
  CharList *next=(*_link)->next;
  CharList *prev=(*_link)->prev;
  free(*_link);
  *_link=NULL;
  prev->next=next;
  next->prev=prev;
  return 0;
}

static int CharList_PopBack(CharList **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  CharList_Remove(&(*_root)->prev);
  return 0;
}

static int CharList_PopFront(CharList **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  CharList *next=(*_root)->next;
  CharList_Remove(_root);
  *_root=next;
  return 0;
}

static int CharList_Delete(CharList **_root)
{//Returns 0 on success, -1 on failure
  if (*_root==NULL)
    return -1;
  if (*_root==(*_root)->next) {
    free(*_root);
    *_root=NULL;
    return 0;
  }
  CharList *temp=*_root;
  do {
    CharList *next=temp->next;
    free(temp);
    temp=next;
  } while (temp!=*_root);
  *_root=NULL;
  return 0;
}
#endif//CHARLIST_H