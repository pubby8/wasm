#ifndef MARK_H
#define MARK_H

#include <stdio.h>

#define NUM_STATES 4

enum mstate {
  mstate_off = 0,
  mstate_on,
  mstate_bold,
  mstate_italic,
  mstate_underline,
  mstate_code,
} extern is_bold, is_italic, is_underline, is_code, mstack[NUM_STATES]; 
unsigned mstack_pos;

//to modify markup stack and print markup markup (html)
void mstate_toggle(enum mstate state);
void mstate_pop_to(unsigned to);

//to print markup text
void mark_char(char chr);
void mark_string(char* str);

#endif

