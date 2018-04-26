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

void list_drop(List);

void list_clear(List);

void list_insert(List, Index, Value);

void list_append(List, Value);

void list_prepend(List, Value);

Value list_delete(List, Index);

Value list_shift(List);

Value list_pop(List);

Value list_get(List, Index);

Value list_first(List);

Value list_last(List);

bool list_is_empty(List);

Size list_size(List);

List list_extend(List, List);

void list_each(List, FnListEach);

List list_map(List, FnListMap);
