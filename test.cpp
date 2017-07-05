#include <iostream> 

#include "./exceptions.h"
#include "./image.h"
#include "./tap.h"

using namespace pixicog;

bool setPixelInRange() {
  Image img(5, 5, 3);
  // red
  img.set(0, 0, 0, 255);
  if (img.get(0, 0, 0) != 255) return false;
  // g
  img.set(3, 2, 1, 100);
  if (img.get(3, 2, 1) != 100) return false;
  // b
  img.set(4, 4, 2, 45);
  if (img.get(4, 4, 2) != 45) return false;
  return true;
};

bool setPixelOutOfRange() {
  // TODO: assert the error messages are valid
  Image img(4, 4, 4);

  // bad x
  try {
    img.set(5, 0, 0, 255);
    return false;
  }
  catch (const char* msg) {
  }

  // bad y
  try {
    img.set(0, 5, 0, 255);
    return false;
  }
  catch (const char* msg) {
  }

  // bad c
  try {
    img.set(0, 0, 5, 255);
    return false;
  }
  catch (const char* msg) {
  }

  // bad v
  try {
    img.set(0, 0, 5, 256);
    return false;
  }
  catch (const char* msg) {
  }

  
  return true;
};

bool createImage() {
  return false;
};

bool copyImge() {
  Image img(3, 3, 3);
  Image copy(img);

  return false;
}


int main(int argc, char * argv[]) {
  tap::start();
  tap::test("# creating the image object");
  tap::pass(createImage(), "creating should work");
  tap::pass(badCreateShouldThrow(), "bad create should throw");
  tap::pass(copyImage(), "copying should work");

  tap::test("# setting a pixels");
  tap::pass(setPixelInRange(), "set a pixel in range should work");
  tap::pass(setPixelOutOfRange(), "setting a pixel out of range should throw");
  return tap::end();
};

