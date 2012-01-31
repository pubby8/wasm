#include "stringutil.h"

#include <stdio.h>
#include <stdlib.h>

#define STRING_CHUNK_SIZE 32

string string_alloc(size_t size) {
  string rstr;
  if(!(rstr.buf = rstr.end = malloc(size)))
    fprintf(stderr, "String allocation failed");
  rstr.size = size;
  return rstr;
}

string string_calloc(size_t size, char* str) {
  string rstr = string_alloc(size);
  while(*str != '\0') {
    if(!size--)
      fprintf(stderr, "String cstr allocation failed");
    *rstr.buf++ = *str++;
    ++rstr.end;
  }
  return rstr;
}

void string_free(string str) {
  free(str.buf);
}

string* string_cat(string* dest, string src) {
  if(dest->size < ((dest->end - dest->buf) + src.size)) {
    if(!(dest->buf = realloc(dest->buf, dest->size + src.size)))
      fprintf(stderr, "String reallocation during cat failed"); 
  }
  while(src.buf != src.end) {
    *dest->end++ = *src.buf++;
  }
  return dest;
}

string* string_ccat(string* dest, char* src) {
  while(*src != '\0') {
    if(dest->size == dest->end - dest->buf) {
      if(!(dest->buf = realloc(dest->buf, dest->size + STRING_CHUNK_SIZE)))
        fprintf(stderr, "String reallocation during cstr cat failed"); 
    }
    *dest->end++ = *src++;
    ++dest->size;
  }
  return dest;
}

string* string_rcat(string* dest, char* src, char chr, char* rep) {
#define REALLOC_ERR fprintf(stderr, "String reallocation during cstr cat failed")
  size_t rlen = strlen(rep);
  while(*src != '\0') {
    if(*src == chr) {
      if(dest->size == dest->end - dest->buf)
        if(!(dest->buf = realloc(dest->buf, dest->size + rlen + STRING_CHUNK_SIZE)))
          REALLOC_ERR;
      memcpy(dest->buf, rep, rlen);
      dest->end += rlen;
      ++src;
    }
    else {
      if(dest->size == dest->end - dest->buf)
        if(!(dest->buf = realloc(dest->buf, dest->size + STRING_CHUNK_SIZE)))
          REALLOC_ERR;
      *dest->end++ = *src++;
      ++dest->size;
    }
  }
  return dest;
#undef REALLOC_ERR
}

