#pragma once
#include <klib/types.h>

namespace Drivers::PCI::Config {
  u32 read32(u8 bus, u8 num, u8 function, u8 offset);
  u16 read16(u8 bus, u8 num, u8 function, u8 offset);
  u8   read8(u8 bus, u8 num, u8 function, u8 offset);

  void write32(u8 bus, u8 num, u8 function , u8 offset, u32 value);
  void write16(u8 bus, u8 num, u8 function , u8 offset, u32 value);
  void  write8(u8 bus, u8 num, u8 function , u8 offset, u8  value);
}
