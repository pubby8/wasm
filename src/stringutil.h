#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include "string.h"

typedef struct {
  char* buf;
  char* end;
  size_t size;
} string;

string string_alloc(size_t size);
string string_calloc(size_t size, char* str);
void string_free(string str);
string* string_cat(string* dest, string src);
string* string_ccat(string* dest, char* src);
string* string_rcat(string* dest, char* src, char chr, char* rep);

#endif

