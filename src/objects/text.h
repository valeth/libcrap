//! @brief  String abstraction
//! @author Patrick Auernig
//! @date   2018-04-26
//! @file   text.h

#pragma once


#include <stdlib.h>
#include <stdbool.h>

#include <misc.h>


struct _Text;

typedef struct _Text* Text;

typedef char* CString;

typedef char Char;


Text text_new();

Text text_from_cstring_unsafe(CString);

CString text_as_cstring(Text);

void text_drop(Text);

Char text_get(Text, Index);

bool text_is_empty(Text);

Size text_size(Text);

Text text_extend(Text, Text);
