#pragma once
#include <klib/types.h>

namespace Drivers::IO {
  void outb(u16 port,  u8 data);
  void outw(u16 port, u16 data);
  void outd(u16 port, u32 data);

  u8  inb(u16 port);
  u16 inw(u16 port);
  u32 ind(u16 port);

  void wait();
}
