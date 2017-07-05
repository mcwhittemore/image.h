#pragma once

#include "./exceptions.h"
#include <vector>

namespace pixicog {

class Image {
  private:
    std::vector<unsigned char> image;
    int width;
    int height;
    int numChannels;
    int toPos(int x, int y, int c);

  public:
    Image(int w, int h, int nc);
    Image(const Image &c);
    ~Image();
    unsigned char get(int x, int y, int c);
    void set(int x, int y, int c, unsigned char v);
};

/** Constructur **/

Image::Image(int w, int h, int nc) : height(h), width(w), numChannels(nc), image(w*h*nc) {
  if (height <= 0) throw "Invalid height value";
  if (width <= 0) throw "Invalid width value";
  if (numChannels < 3 || numChannels > 4) throw "Invalid numChannels value";
}

// copy constuctor
Image::Image(const Image &c) : height(c.height), width(c.width), numChannels(c.numChannels), image(c.image) {}

/** Deconstructor **/

Image::~Image() {
  // do I need to kill image?
}

/** PRIVATE - turn x, y, c into an pos in the underlaying array **/

int Image::toPos(int x, int y, int c) {
  return (y*width*numChannels)+(x*numChannels) + c;
}

/** PUBLIC **/

unsigned char Image::get(int x, int y, int c) {
  int pos = toPos(x, y, c);
  return image[pos];
}

// Set a specific channel for one pixel
void Image::set(int x, int y, int c, unsigned char v) {
  if (x >= width || x < 0) throw "X coordinate is out of range";
  if (y >= height || y < 0) throw "Y coordinate is out of range";
  if (c >= numChannels || c < 0) throw "Color channel is out of range";
  if (v > 255 || v < 0) throw "Color value is out of range";
  int pos = toPos(x, y, c);
  image[pos] = v;
}

}
