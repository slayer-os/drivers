#include <drivers/fb_gfx.h>
#include <bootloader/limine.h>
#include <klib/assert.h>
#include <klib/math.h>

struct limine_framebuffer *l_framebuffer;
void *fb_addr;

void Drivers::fb::gfx::pixel(u32 x, u32 y, u32 color) {
  u32 *pixel = (u32 *)(fb_addr + (y * l_framebuffer->pitch) + (x * 4));
  *pixel = color;
}

void Drivers::fb::gfx::line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  int xinc = dx / steps;
  int yinc = dy / steps;
  int x = x1;
  int y = y1;
  for (int i = 0; i <= steps; i++) {
    Drivers::fb::gfx::pixel(x, y, color);
    x += xinc;
    y += yinc;
  }
}

void Drivers::fb::gfx::rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
  Drivers::fb::gfx::line(x, y, x + w, y, color);
  Drivers::fb::gfx::line(x, y, x, y + h, color);
  Drivers::fb::gfx::line(x + w, y, x + w, y + h, color);
  Drivers::fb::gfx::line(x, y + h, x + w, y + h, color);
}

void Drivers::fb::gfx::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
  for (u32 i = 0; i < h; i++) {
    for (u32 j = 0; j < w; j++) {
      Drivers::fb::gfx::pixel(x + j, y + i, color);
    }
  }
}

void Drivers::fb::gfx::fill(u32 color) {
  for (u32 i = 0; i < l_framebuffer->height; i++) {
    for (u32 j = 0; j < l_framebuffer->width; j++) {
      Drivers::fb::gfx::pixel(j, i, color);
    }
  }
}

u32 Drivers::fb::gfx::screen::width() {
  return l_framebuffer->width;
}
u32 Drivers::fb::gfx::screen::height() {
  return l_framebuffer->height;
}

void Drivers::fb::gfx::init(){
  assert(boot_ctx.fb_info->framebuffer_count > 0, "No framebuffer found");
  l_framebuffer = boot_ctx.fb_info->framebuffers[0];
  fb_addr = (void *)l_framebuffer->address;
}
