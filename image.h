#pragma once

#include <vector>

namespace pixicog {

/**
 * The core data structure of pixicog.
 * @class Image
 * @param {Integer} [width]
 * @param {Integer} [height]
 * @param {Integer} [numChannels]
 * @example
 * // create an RGB image that is 10 pixels wide and 5 pixels tall
 * Image img(10, 5, 3);
 * @example
 * // create an RGBA image that is 10 pixels wide and 5 pixels tall
 * Image img(10, 5, 4);
 * @example
 * // create an image with no associated data
 * // you must call img.setup(...) before using
 * Image img();
 * 
 */

class Image {
  private:
    int toPos(int x, int y, int c);
    void validate();
/**
 * this is where all the pixel data is kept
 * @private
 * @instance
 * @memberof Image
 * @name pixels
 * @type {std::vector}
 */
    std::vector<unsigned char> pixels;
/**
 * the width of the image
 * @private
 * @instance
 * @memberof Image
 * @name width
 * @type {Integer}
 */
    int width;
/**
 * the height of the image
 * @private
 * @instance
 * @memberof Image
 * @name height
 * @type {Integer}
 */
    int height;
/**
 * the number of channels (1 = gray scale, 3 = RGB, 4 = RGBA)
 * @private
 * @instance
 * @memberof Image
 * @name numChannels
 * @type {Integer}
 */
    int numChannels;

  public:
    Image();
    Image(int w, int h, int nc);
    Image(const Image &c);
    ~Image();
    std::vector<int> getShape();
    void setup(int x, int y, int nc, std::vector<unsigned char>);
    unsigned char get(int x, int y, int c);
    void set(int x, int y, int c, unsigned char v);
};

Image::Image() {}

Image::Image(int w, int h, int nc) : height(h), width(w), numChannels(nc), pixels(w*h*nc) {
  validate();
}

Image::Image(const Image &c) : height(c.height), width(c.width), numChannels(c.numChannels), pixels(c.pixels) {}


Image::~Image() {
  // TODO: do I need to clear the std::vector?
}

/**
 * Makes sure the data of an image is valid
 * @memberof Image
 * @name validate
 * @throws {const char*}
 * @private
 */
void Image::validate() {
  if (height <= 0) throw "Invalid height value";
  if (width <= 0) throw "Invalid width value";
  if (numChannels != 1 && numChannels != 3 && numChannels != 4) throw "Invalid numChannels value";
}

/**
 * convert x, y and channel into an int for the position
 * @memberof Image
 * @name toPos
 * @return {Integer}
 * @private
 */
int Image::toPos(int x, int y, int c) {
  if (x >= width || x < 0) throw "X coordinate is out of range";
  if (y >= height || y < 0) throw "Y coordinate is out of range";
  if (c >= numChannels || c < 0) throw "Color channel is out of range";

  // TODO: should we let 0-3 work for numChannels at all times?
  return (y*width*numChannels)+(x*numChannels) + c;
}

/**
 * Returns the shape of the Image as a vector
 * @memberof Image
 * @name getShape
 * @public
 * @instance
 * @returns {std-vector<int>}
 */
std::vector<int> Image::getShape() {
  std::vector<int> shape(3); 
  shape[0] = width;
  shape[1] = height;
  shape[2] = numChannels;
  return shape;
};

/**
 * Overrides the internal data of a Image
 * @memberof Image
 * @name setup
 * @param {Integer} w - the width of the image, must be greater than 0
 * @param {Integer} h - the height of the image, must be greater than 0
 * @param {Integer} nc - the number of channels. Must be 1, 3, or 4.
 * @param {std::vector<unsigned-char>} pixs - the vector containing the data
 * @public
 * @instance
 * @returns {void}
 */
void Image::setup(int w, int h, int nc, std::vector<unsigned char> pixs) {
  width = w;
  height = h;
  numChannels = nc;
  pixels = pixs;
  validate();
}

/**
 * Gets the value of a single channel for a single pixel
 * @memberof Image
 * @name get
 * @param {Integer} x - the x coord
 * @param {Integer} y - the y coord
 * @param {Integer} c - the channel number
 * @public
 * @instance
 * @return {unsigned-char}
 */
unsigned char Image::get(int x, int y, int c) {
  int pos = toPos(x, y, c);
  return pixels[pos];
}

/**
 * Set a specific channel for one pixel
 * @memberof Image
 * @name set
 * @param {Integer} x - the x coord
 * @param {Integer} y - the y coord
 * @param {Integer} c - the channel number
 * @param {unsigned-char} v - the new value
 * @public
 * @instance
 * @return {void}
 */
void Image::set(int x, int y, int c, unsigned char v) {
  int pos = toPos(x, y, c);
  if (v > 255 || v < 0) throw "Color value is out of range";
  pixels[pos] = v;
}

}
