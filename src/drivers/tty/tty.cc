#include <drivers/tty.h>
#include <klib/string.h>
#include <flanterm.h>
#include <flanterm_backends/fb.h>

static u32 ANSI_COLORSCHEME[16] = {
  // normal
  0x928374, // gray
  0xcc241d, // red
  0x98971a, // green
  0xd79921, // yellow
  0x458588, // blue
  0xb16286, // magenta
  0x689d6a, // cyan
  0xa89984, // light-gray
  
  // bright
  0x282828, // black
  0xfb4934, // red
  0xb8bb26, // green
  0xfabd2f, // yellow
  0x83a598, // blue
  0xd3869b, // magenta
  0x8ec07c, // cyan
  0xebdbb2  // white
};

extern "C" const u8 tty_font[];

struct flanterm_context *ft_ctx = nullptr;

void Drivers::TTY::init(struct limine_framebuffer *fb) {
  u32 bg = 0x1d2021;
  u32 fg = 0xebdbb2;
  ft_ctx = flanterm_fb_init(
      NULL,
      NULL,
      (u32*)fb->address, fb->width, fb->height, fb->pitch,
      fb->red_mask_size, fb->red_mask_shift,
      fb->green_mask_size, fb->green_mask_shift,
      fb->blue_mask_size, fb->blue_mask_shift,
      NULL,
      ANSI_COLORSCHEME + 8, ANSI_COLORSCHEME,
      &bg, &fg,
      NULL, NULL,
      (void*)&tty_font, 8, 16, 0,
      0, 0,
      0
  );
}

bool Drivers::TTY::initialized() {
  return ft_ctx != nullptr;
}

void Drivers::TTY::write(const char *msg, usize len) {
  if (msg == nullptr) return;
  if (len<1) len = strlen(msg);
  
  flanterm_write(ft_ctx, msg, len);
}

void Drivers::TTY::clear() {
  flanterm_full_refresh(ft_ctx);
}
