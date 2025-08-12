#pragma once
#include <klib/types.h>
#include <limine.h>

namespace Drivers::TTY {
  void init(struct limine_framebuffer *fb);
  bool initialized();
  void write(const char *msg, usize len=0);
  void clear();
}
