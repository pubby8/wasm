#include "mark.h"

#include <stdlib.h>

enum mstate is_bold = mstate_off;
enum mstate is_italic = mstate_off;
enum mstate is_underline = mstate_off;
enum mstate is_code = mstate_off;
enum mstate mstack[NUM_STATES];
unsigned mstack_num = 0;

void mstate_toggle(enum mstate state) {
#define MARKUP_PUSH(x,c) case mstate_##x: if(!is_##x) puts(c); else goto err; is_##x = mstate_on; break;
  if(mstack_pos == NUM_STATES) {
    fprintf(stderr, "Markup stack overflow");
    exit(1);
  }
  if((mstack_pos && mstack[mstack_pos-1] != state) || mstack_pos == 0) {
    mstack[mstack_pos++] = state;
    switch(state) {
      MARKUP_PUSH(bold,"<b>");
      MARKUP_PUSH(italic,"<i>");
      MARKUP_PUSH(underline,"<u>");
      MARKUP_PUSH(code,"<code>");
      default: goto err;
    }
  }
  else {
    mstate_pop_to(mstack_pos - 1);
  }
  return;
  err:
  fprintf(stderr, "Markup invalid order");
  exit(1);
#undef MARKUP_PUSH
}

void mstate_pop_to(unsigned to) {
#define MARKUP_POP(x,c) case mstate_##x: puts(c); is_##x = mstate_off; break;
  if(to > mstack_pos) {
    fprintf(stderr, "Markup stack pop error, popping to %i", to);
    exit(1);
  }
  while(mstack_pos > to) {
    --mstack_pos;
    switch(mstack[mstack_pos]) {
      MARKUP_POP(bold,"</b>");
      MARKUP_POP(italic,"</i>");
      MARKUP_POP(underline,"</u>");
      MARKUP_POP(code,"</code>");
      default: 
        fprintf(stderr, "Markup invalid stack"); 
        exit(1);
    }
  }
#undef MARKUP_POP
}

void mark_char(char chr) {
#define TOGGLE(x) if(!is_code || mstate_##x == mstate_code) mstate_toggle(mstate_##x); break;
  switch(chr) {
    case '#':  TOGGLE(bold); break;
    case '~':  TOGGLE(italic); break;
    case '_':  TOGGLE(underline); break;
    case '`':  TOGGLE(code); break;
    case '\"': printf("&quot;"); break;
    case '&':  printf("&amp;"); break;
    case '\'': printf("&apos;"); break;
    case '<':  printf("&lt;"); break;
    case '>':  printf("&gt;"); break;
    default:   putchar(chr); break;
  }
#undef TOGGLE
}

void mark_string(char* str) { 
  while(*str != '\0') {
    mark_char(*str);
    ++str;
  }
}
