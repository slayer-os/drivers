#include <drivers/fb_gfx.h>
#include <klib/string.h>

#define PIXEL_SIZE    6
#define HEIGHT_MULT   2

void draw_block(u32 x, u32 y, u32 color) {
  for (int i = 0; i < PIXEL_SIZE; i++) {
    for (int j = 0; j < PIXEL_SIZE; j++) {
      Drivers::fb::gfx::pixel(x + j, y + i, color);
    }
  }
}

void Drivers::fb::gfx::splash::ascii_logo(u32 x, u32 y, u32 scale, u32 color) {
  const char *logo[] = {
      "                                          ######   ",
      "                                         #*###**#  ",
      "                                        ##    #**# ",
      "                                        #      #**#",
      "                                                #*#",
      "                                               #**#",
      "                                          ####**#  ",
      "                       #                ##**##     ",
      "                     ##*#             ##*##        ",
      "                    #****#          ##*##          ",
      "                  #****##*#        #*##            ",
      "                ##***#   #*#     #**#              ",
      "               #***#      #*#  #**#                 ",
      "             #***#         #*#**#                    ",
      "           #***##          ##**#                     ",
      "  ###    ##**##           #**#**#                    ",
      "###     #***#           #**#  #**#                   ",
      "#*#   #***#            #**#    #**#                  ",
      "#**###**#            #**#        #*##                ",
      "#*****#            ##*##          #**#      #        ",
      " ##*##            #**#             ##**#    #        ",
      "                #**###################***####      ",
      "               #***************************#       ",
      nullptr
  };
  
  int x_scale = scale;
  int y_scale = scale * (Drivers::fb::gfx::screen::width() / Drivers::fb::gfx::screen::height());
  for (int row = 0; logo[row] != NULL; row++) {
    for (int col = 0; logo[row][col] != '\0'; col++) {
      if (logo[row][col] != ' ') {
        for (int i = 0; i < y_scale; i++) {
          for (int j = 0; j < x_scale; j++) {
            draw_block(x + col * PIXEL_SIZE * x_scale + j * PIXEL_SIZE, y + (row * HEIGHT_MULT + i) * PIXEL_SIZE, color);
          }
        }
      }
    }
  }
}

void Drivers::fb::gfx::splash::sevastolink(u8 perc) {
  const char *art[] = {
      "                                                                                                                                                                                                        ",
      "      =========        =========+    ====              =====  =====           ============================== ================  ====              ==========          ========       =++====             ",
      "    ====              ====+          =====           =====   =======       ======                 ====     =======       ==========              ==== ======        =========    ========               ",
      "   =====             ====             =====        ======  ==========     ====                   ====     ======          ========              ==== =========      ==================                  ",
      "   ================ ================== =====     ======  =====    ====    ================       ===+     ====           ========              ===== ===+ ======   ==============                       ",
      "    ==================================  ====    ======  =====     =====     ===============     =====     ====           ========              =========   ======  +===========                         ",
      "                ========                 ===========  ==================               ====     ===+     ====           ====+====              =========     ======================                     ",
      "              ==========                 =========  =====          =====             -=====    =====     =====        ===========             ==== =====       ============   ========                  ",
      " ===================================      ======   =====            ======================     ====      ================== ================= ==== ====          =========       =======                ",
      " ===============     ===============       ===     ===               ===================       ===         =============      =============== ===  ===             ==  ===          ===                 ",
      nullptr
  };
  
  const u32 screen_w = Drivers::fb::gfx::screen::width();
  const u32 screen_h = Drivers::fb::gfx::screen::height();

  usize maxcols = 0;
  for (int r = 0; art[r] != NULL; ++r) {
    usize len = strlen(art[r]);
    if (len > maxcols) maxcols = len;
  }

  const int glyph_w = 3;
  long total_px_x = (long)maxcols * glyph_w;
  long x0 = (total_px_x < (long)screen_w) ? ((long)screen_w - total_px_x) / 2 : 0;

  usize rows = 0;
  for (int r = 0; art[r] != NULL; ++r) ++rows;

  const int row_pixel_h = HEIGHT_MULT * 3;
  long total_px_y = (long)rows * row_pixel_h;
  long y0 = (total_px_y < (long)screen_h) ? (((long)screen_h - total_px_y) * 3 / 12) : 0;

  for (int row = 0; art[row] != NULL; ++row) {
    for (int col = 0; art[row][col] != '\0'; ++col) {
      if (art[row][col] != ' ') {
        draw_block(
          (u32)(x0 + col * glyph_w),
          (u32)(y0 + (row * row_pixel_h)),
          0x0CFF64
        );
      }
    }
  }

  int unit = glyph_w;
  int gap = unit * screen_h/13;
  int bar_x = (int)x0;
  int bar_h = unit * 6;
  int bar_y = (int)(screen_h - bar_h - gap);
  int bar_w = (int)total_px_x - bar_x/4;
  int inner_x = bar_x + unit;
  int inner_y = bar_y + unit;
  int inner_w = bar_w - 2 * unit;
  int inner_h = bar_h - 2 * unit;
  if (inner_w < 0) inner_w = 0;
  if (inner_h < 0) inner_h = 0;

  u32 outline = 0x0CFF64;
  u32 fill = 0x0CFF64;
  u32 unfilled = 0x1d2021;

  if (perc > 100) perc = 100;

  for (int xx = bar_x; xx < bar_x + bar_w; xx += unit) {
    draw_block((u32)xx, (u32)bar_y, outline);
  }
  for (int xx = bar_x; xx < bar_x + bar_w; xx += unit) {
    draw_block((u32)xx, (u32)(bar_y + bar_h - unit), outline);
  }
  for (int yy = bar_y; yy < bar_y + bar_h; yy += unit) {
    draw_block((u32)bar_x, (u32)yy, outline);
  }
  for (int yy = bar_y; yy < bar_y + bar_h; yy += unit) {
    draw_block((u32)(bar_x + bar_w - unit), (u32)yy, outline);
  }

  int filled_px = (inner_w * (int)perc) / 100;
  for (int ux = 0; ux < inner_w; ux += unit) {
    for (int uy = 0; uy < inner_h; uy += unit) {
      int fx = inner_x + ux;
      int fy = inner_y + uy;
      
      if (ux < filled_px) {
        draw_block((u32)fx, (u32)fy, fill);
      } else {
        draw_block((u32)fx, (u32)fy, unfilled);
      }
    }
  }
}
