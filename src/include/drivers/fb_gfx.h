#pragma once
#include <klib/types.h>

namespace Drivers::fb::gfx {

  void init();
  void pixel(u32 x, u32 y, u32 color);
  void line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
  void rect(u32 x, u32 y, u32 w, u32 h, u32 color);
  void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
  void fill(u32 color);
  
  namespace screen {
    u32 width();
    u32 height();
  }

  namespace splash {
    void ascii_logo(u32 x, u32 y, u32 scale, u32 color);
    void sevastolink(u8 perc);
  }
}

