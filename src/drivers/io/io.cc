#include <klib/types.h>
#include <drivers/io.h>

void Drivers::IO::outb(u16 port, u8 value) {
  __asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

void Drivers::IO::outw(u16 port, u16 value) {
  __asm__ __volatile__ ("outw %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

void Drivers::IO::outd(u16 port, u32 value) {
  __asm__ __volatile__ ("outl %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

u8 Drivers::IO::inb(u16 port) {
  u8 ret;
  __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

u16 Drivers::IO::inw(u16 port) {
  u16 ret;
  __asm__ __volatile__ ("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

u32 Drivers::IO::ind(u16 port) {
  u32 ret;
  __asm__ __volatile__ ("inl %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void Drivers::IO::wait(void) {
  __asm__ __volatile__ ("outb %%al, $0x80" :: "a"(0));
}
