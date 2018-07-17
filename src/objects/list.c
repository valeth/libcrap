#include <check.h>
#include <debug.h>
#include "list.h"


static ListNode node_first(List list);
static ListNode node_next(ListNode node);


/// Iterate over the entire list from first to last.
/// @param LIST [List] The list to iterate over
/// @param CUR [ListNode] The current list node during the iteration
#define FOREACH(LIST, CUR)\
    for (ListNode CUR = node_first(LIST), TMP = node_next(CUR); CUR != nil; CUR = TMP, TMP = node_next(CUR))
    // ^ TMP is required to allow safe iteration when deleting nodes,
    //   otherwise we'll get invalid reads.


struct _DListNode {
    Value value;
    ListNode next;
    ListNode prev;
};

struct _DList {
    Size size;
    ListNode head;
    ListNode tail;
};


static ListNode node_new(Value val) {
    ListNode node = malloc(sizeof(*node));
    memcheck(node);
    node->value = val;
    node->prev = nil;
    node->next = nil;
    return node;
rescue:
    return nil;
}

static Value node_drop(ListNode node) {
    check(node, "Invalid list node");
    Value val = node->value;
    drop(node);
    return val;
rescue:
    return nil;
}

static void node_clear(ListNode node) {
    check(node, "Invalid list node");
    drop(node_drop(node));
rescue:
    return;
}

static ListNode node_at_index(List list, Index idx) {
    check(list, "Invalid list");

    if (idx == 0) {
        return list->head;
    } else if (idx < list_size(list)) {
        Index pos = 0;
        FOREACH(list, cur) {
            if (idx == pos) {
                return cur;
            }
            ++pos;
        }
    } else {
        return list->tail;
    }
rescue:
    return nil;
}

static ListNode node_next(ListNode node) {
    check(node, nil);
    return node->next;
rescue:
    return nil;
}

static ListNode node_first(List list) {
    check(list, "Invalid list");
    return list->head;
rescue:
    return nil;
}


List list_new() {
    List list = malloc(sizeof(*list));
    memcheck(list);

    list->size = 0;
    list->head = nil;
    list->tail = nil;

    return list;
rescue:
    return nil;
}

void list_drop(List list) {
    check(list, "Invalid list");
    list_map(list, node_drop);
    drop(list);
rescue:
    return;
}

void list_clear(List list) {
    check(list, "Invalid list");
    list_each(list, node_clear);
rescue:
    return;
}

void list_insert(List list, Index idx, Value val) {
    ListNode node = node_new(val);
    memcheck(node);

    check(list, "Invalid list");

    if (list_is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else if (0 == idx) {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    } else if (list_size(list) == idx || list_size(list) - 1 < idx) {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    } else {
        ListNode tmp = node_at_index(list, idx);
        check(tmp, "No node found at %d", idx);
        tmp->prev->next = node;
        node->prev = tmp->prev;
        tmp->prev = node;
        node->next = tmp;
    }

    list->size++;

    return;
rescue:
    drop(node);
    return;
}

void list_append(List list, Value val) {
    list_insert(list, list->size, val);
}

void list_prepend(List list, Value val) {
    list_insert(list, 0, val);
}

Value list_delete(List list, Index idx) {
    check(list, "Invalid list");
    check(!list_is_empty(list), nil);

    Value val = nil;

    if (list_size(list) == 1) {
        val = node_drop(list->head);
        list->head = nil;
        list->tail = nil;
    } else if (0 == idx) {
        list->head = list->head->next;
        val = node_drop(list->head->prev);
        list->head->prev = nil;
    } else if (list_size(list) - 1 == idx) {
        list->tail = list->tail->prev;
        val = node_drop(list->tail->next);
        list->tail->next = nil;
    } else {
        ListNode tmp = node_at_index(list, idx);
        check(tmp, "No node found at %d", idx);
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        val = node_drop(tmp);
    }

    list->size--;

    return val;
rescue:
    return nil;
}

Value list_shift(List list) {
    return list_delete(list, 0);
}

Value list_pop(List list) {
    return list_delete(list, list->size - 1);
}

Value list_get(List list, Index idx) {
    check(list, nil);
    ListNode node = node_at_index(list, idx);
    check(node, "Index out of range");
    return node->value;
rescue:
    return nil;
}

Value list_first(List list) {
    return list_get(list, 0);
}

Value list_last(List list) {
    return list_get(list, list->size);
}

bool list_is_empty(List list) {
    check(list, nil);
    return (list->size == 0);
rescue:
    return true;
}

Size list_size(List list) {
    check(list, nil);
    return list->size;
rescue:
    return 0;
}

List list_extend(List list, List other) {
    check(list, nil);
    check(list->tail, nil);
    check(other, nil);
    check(other->head, nil);

    FOREACH(other, cur) {
        list_append(list, cur->value);
    }

    return list;
rescue:
    return list;
}

void list_each(List list, FnListEach func) {
    check(list, nil);
    FOREACH(list, cur) {
        func(cur);
    }
rescue:
    return;
}

List list_map(List list, FnListMap func) {
    check(list, nil);
    List tmp = list_new();
    memcheck(tmp);
    FOREACH(list, cur) {
        list_append(tmp, func(cur));
    }
    return tmp;
rescue:
    return nil;
}
