#include "mode.h"

#include "stdio.h"

#include "mark.h"

enum mode mode = mode_normal;

void mode_change(enum mode newmode) {
  mstate_pop_to(0);
  switch (mode) {
    case mode_code:
      printf("</pre></div></div></div>");
      break;
    case mode_div:
      printf("</div>");
      break;
  }
  mode = newmode;
}
