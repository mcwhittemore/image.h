#pragma once

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
    Image();
    Image(int w, int h, int nc);
    Image(const Image &c);
    ~Image();
    unsigned char get(int x, int y, int c);
    void set(int x, int y, int c, unsigned char v);
};

/** Constructur **/
Image::Image() {}

Image::Image(int w, int h, int nc) : height(h), width(w), numChannels(nc), image(w*h*nc) {
  validate();
}

// copy constuctor
Image::Image(const Image &c) : height(c.height), width(c.width), numChannels(c.numChannels), image(c.image) {}

/** Deconstructor **/

Image::~Image() {
  // do I need to kill image?
}

/** PRIVATE - turn x, y, c into an pos in the underlaying array **/


void Image::validate() {
  if (height <= 0) throw "Invalid height value";
  if (width <= 0) throw "Invalid width value";
  if (numChannels !== 1 || numChannels != 3 || numChannels != 4) throw "Invalid numChannels value";
}

int Image::toPos(int x, int y, int c) {
  if (x >= width || x < 0) throw "X coordinate is out of range";
  if (y >= height || y < 0) throw "Y coordinate is out of range";
  if (c >= numChannels || c < 0) throw "Color channel is out of range";

  // TODO: should we let 0-3 work for numChannels at all times?
  return (y*width*numChannels)+(x*numChannels) + c;
}

/** PUBLIC **/

/**
 * @param: w {Int} - the width of the image
 * @param: h {Integer} - the height of the image
 * @param: nc {Integer} - the number of channels (1, 3, 4) in the image.
 * @param: img {std::vector<unsigned char>} - the raw data for the image.
 */
void Image::setup(int w, int h, int nc, std::vector<unsigned char> img) {
  width = w;
  height = h;
  numChannels = nc;
  image = img;
  validate();
}

unsigned char Image::get(int x, int y, int c) {
  int pos = toPos(x, y, c);
  return image[pos];
}

// Set a specific channel for one pixel
/**
 *
 */
void Image::set(int x, int y, int c, unsigned char v) {
  int pos = toPos(x, y, c);
  if (v > 255 || v < 0) throw "Color value is out of range";
  image[pos] = v;
}

}
