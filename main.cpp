#include "tgaimage.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>

#define MAX_SIZE 100

constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void draw_line(TGAImage &framebuffer, TGAColor color, int ax, int ay, int bx,
               int by) {
  bool steep = std::abs(ay - by) > std::abs(ax - bx);

  if (steep) {
    std::swap(ax, ay);
    std::swap(bx, by);
  }

  if (ax > bx) {
    std::swap(ax, bx);
    std::swap(ay, by);
  }
  float y = ay;
  for (float x = ax; x <= bx; x++) {
    if (steep) {
      framebuffer.set(y, x, color);
    } else {
        framebuffer.set(x, y, color);
    }

    y += (by - ay) / static_cast<float>(bx-ax);
  }
}

void test_draw_line(TGAImage &framebuffer,int height,int width, int count) {
    std::srand(time({}));
    while(count-- > 0) {
        // std::cout << count << '\n';

        int ax = std::rand() % width;
        int ay = std::rand() % height;
        int bx = std::rand() % width;
        int by = std::rand() % height;

        // std::cout << count << " " << ax << " " << ay << " " << '\n';
        
        TGAColor color = { static_cast<uint8_t>(std::rand()%256), static_cast<uint8_t>(std::rand()%256),static_cast<uint8_t>(std::rand()%256),static_cast<uint8_t>(std::rand()%256)};
        
        draw_line(framebuffer, color, ax, ay, bx, by);
    }
}

int main(int argc, char **argv) {
  constexpr int width = 64;
  constexpr int height = 64;
  TGAImage framebuffer(width, height, TGAImage::RGB);

//   int ax = 7, ay = 3;
//   int bx = 12, by = 37;
//   int cx = 52, cy = 53;

//   draw_line(framebuffer, red, ax, ay, bx, by);
//   draw_line(framebuffer, green, bx, by, cx, cy);
//   draw_line(framebuffer, yellow, ax, ay, cx, cy);
//   draw_line(framebuffer, blue, cx, cy, ax, ay);

  test_draw_line(framebuffer,height,width, 16000000);

  framebuffer.write_tga_file("test.tga");
}