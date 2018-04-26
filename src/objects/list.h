//! @brief  Doubly Linked List
//! @author Patrick Auernig
//! @date   2018-04-01
//! @file   list.h

#pragma once


#include <stdlib.h>
#include <stdbool.h>

#include <misc.h>


struct _DListNode;

struct _DList;

/// A single list node
typedef struct _DListNode* ListNode;

/// A doubly linked list
typedef struct _DList* List;

/// A function that can be used with `list_map`.
typedef Value (*FnListMap)(ListNode);

/// A function that can be used with `list_each`.
typedef void (*FnListEach)(ListNode);


/// Creates a new empty list.
/// @retval  List, nil
List list_new();

/// Destroys a list object.
/// @param  list  The list to destroy
/// @attention  Stored values will not be `free`'d
void list_drop(List list);

/// Removes elements from a list
/// @warning  This will `free` elements, do not use with non-`malloc`'d content.
void list_clear(List);

/// Inserts a value into a list.
/// @param  list  The list to insert into
/// @param  idx  The position to insert at
/// @param  val  The value to insert
void list_insert(List list, Index idx, Value val);

/// Inserts a value at the end of the list.
/// @param  list  The list to insert into
/// @param  val  The value to insert
void list_append(List list, Value val);

/// Inserts a value at the beginning of the list.
/// @param  list  The list to insert into
/// @param  val  The value to insert
void list_prepend(List list, Value val);

/// Deletes a value from a list.
/// @param  list  The list to delete from
/// @param  idx  The position to delete
/// @retval  Value
Value list_delete(List list, Index idx);

/// Deletes a value from the beginning of the list.
/// @param  list  The list to delete from
/// @retval  Value
Value list_shift(List list);

/// Deletes a value from the end of the list.
/// @param  list  The list to delete from
/// @retval  Value
Value list_pop(List list);

/// Fetches a value at the given position.
/// @param  list  The list to query
/// @param  idx  The position to get
/// @retval  Value
Value list_get(List list, Index idx);

/// Fetches the first value in the list.
/// @param  list  The list to query
/// @retval  Value
Value list_first(List list);

/// Fetches the last value in the list.
/// @param  list  The list to query
/// @retval  Value
Value list_last(List list);

/// Checks if the list is empty.
/// @param  list
/// @retval  bool
bool list_is_empty(List list);

/// Gets the current list size.
/// @param  list
/// @retval  Size
Size list_size(List list);

/// Extends a list with the contents of another one.
/// @param  list  The list to extend
/// @param  other  The list that gets copied
/// @retval  List  A pointer to `list`
List list_extend(List list, List other);

/// Iterate over each element in the list and apply a function to it.
/// @param  list  The list to iterate over
/// @param  func  The function to apply to every node
void list_each(List list, FnListEach func);

/// Iterate over each element in the list, apply a function to it, and return a modified list.
/// This will not modify the current list.
/// @param  list  The list to iterate over
/// @param  func  The function to apply to every node
/// @retval  List  The modified list
List list_map(List, FnListMap);
