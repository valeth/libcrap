/// @brief  Doubly Linked List
/// @author Patrick Auernig
/// @date   2018-04-01
/// @file   list.h

#pragma once


#include <stdlib.h>
#include <stdbool.h>

#include <misc.h>


struct _DListNode;

struct _DList;

typedef struct _DListNode* ListNode;

typedef struct _DList* List;

typedef Value (*FnListMap)(ListNode);

typedef void (*FnListEach)(ListNode);


List list_new();

void list_drop(List list);

void list_clear(List list);

void list_insert(List list, Index idx, Value val);

void list_append(List list, Value val);

void list_prepend(List list, Value val);

Value list_delete(List list, Index idx);

Value list_shift(List list);

Value list_pop(List list);

Value list_get(List list, Index idx);

Value list_first(List list);

Value list_last(List list);

bool list_is_empty(List list);

Size list_size(List list);

List list_extend(List list, List other);

void list_each(List list, FnListEach func);

List list_map(List list, FnListMap func);
