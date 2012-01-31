#ifndef MODE_H
#define MODE_H

#include "string.h"

enum mode {
  mode_normal,
  mode_code,
  mode_div,
} extern mode;

void mode_change(enum mode newmode);

#endif

