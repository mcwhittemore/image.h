#include <iostream> 

#include "./exceptions.h"
#include "./image.h"
#include "./tap.h"

using namespace pixicog;

bool setPixelInRange() {
  // r
  // g
  // b
  // a
  return false;
};

bool setPixelOutOfRange() {
  // bad x
  // bad y
  // bad c
  return false;
};

bool createImage() {
  return false;
};

bool createImageWithArgs() {
  return false;
}


int main(int argc, char * argv[]) {
  tap::start();
  tap::test("# creating the image object");
  tap::pass(createImage(), "with no arguments");
  tap::pass(createImageWithArgs(), "with all arguments");

  tap::test("# setting a pixels");
  tap::pass(setPixelInRange(), "set a pixel in range should work");
  tap::pass(setPixelOutOfRange(), "setting a pixel out of range should throw");
  return tap::end();
};

