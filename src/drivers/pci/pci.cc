#include <klib/types.h>
#include <drivers/pci.h>
#include <drivers/io.h>

u32 Drivers::PCI::Config::read32(u8 bus, u8 num, u8 function, u8 offset) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset);
  Drivers::IO::outd(0xCF8, address);
  return Drivers::IO::ind(0xCFC);
}

u16 Drivers::PCI::Config::read16(u8 bus, u8 num, u8 function, u8 offset) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset & 0xfc);
  Drivers::IO::outd(0xCF8, address);
  return (u16)((Drivers::IO::ind(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
}

u8 Drivers::PCI::Config::read8(u8 bus, u8 num, u8 function, u8 offset) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset);
  Drivers::IO::outd(0xCF8, address);
  return (u8)((Drivers::IO::ind(0xCFC) >> ((offset & 3)  * 8)) & 0xff);
}

void Drivers::PCI::Config::write32(u8 bus, u8 num, u8 function , u8 offset, u32 value) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset);
  Drivers::IO::outd(0xCF8, address);
  Drivers::IO::outd(0xCFC, value);
}

void Drivers::PCI::Config::write16(u8 bus, u8 num, u8 function , u8 offset, u32 value) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset & 0xfc);
  Drivers::IO::outd(0xCF8, address);
  Drivers::IO::outd(0xCFC, (Drivers::IO::ind(0xCFC) & ~(0xffff << ((offset & 2) * 8))) | (value << ((offset & 2) * 8)));
}

void Drivers::PCI::Config::write8(u8 bus, u8 num, u8 function , u8 offset, u8 value) {
  u32 address = (1 << 31) | (bus << 16) | (num << 11) | (function << 8) | (offset & 0xfc);
  Drivers::IO::outd(0xCF8, address);
  Drivers::IO::outd(0xCFC, ((Drivers::IO::ind(0xCFC) & ~(0xFF << (offset & 3))) | (value << ((offset & 3) * 8))));
}
