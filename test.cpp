#include <iostream> 

#include "./image.h"
#include "./tap/tap.h"

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

bool copyImage() {
  Image img(3, 3, 4);
  img.set(0, 0, 0, 0);
  img.set(0, 0, 1, 1);
  img.set(0, 0, 2, 2);
  img.set(0, 0, 3, 3);

  Image copy(img);
  if (img.get(0, 0, 0) != copy.get(0, 0, 0)) return false;
  if (img.get(0, 0, 1) != copy.get(0, 0, 1)) return false;
  if (img.get(0, 0, 2) != copy.get(0, 0, 2)) return false;
  if (img.get(0, 0, 3) != copy.get(0, 0, 3)) return false;

  return true;
}

bool badCreateShouldThrow() {
  // TODO: Have tests confirm error messages
  // invalid size for vector
  try {
    Image img(-1, -1, -1);
    return false;
  }
  catch(std::exception& e){
  }

  // invalid width
  try {
    Image img(0, 1, 3);
    return false;
  }
  catch (const char* msg) {
  }

  // invalid height
  try {
    Image img(1, 0, 3);
    return false;
  }
  catch (const char* msg) {
  }

  // too few channels
  try {
    Image img(1, 1, 2);
    return false;
  }
  catch (const char* msg) {
  }

  // too many channels
  try {
    Image img(1, 1, 5);
    return false;
  }
  catch (const char* msg) {
  }

  return true;
}

bool throwFail(void (*fptr)()) {
  try {
    fptr();
    return true;
  }
  catch (const char* msg) {
    std::cout << msg << "\n";
    return false;
  }
}

void createViaSetup() {
  Image img;
  std::vector<unsigned char> vec(75);
  vec[0] = 255;
  vec[1] = 255;
  vec[2] = 255;
  img.setup(5, 5, 3, vec);
  if (255 != img.get(0, 0, 0)) throw "wrong red";
  if (255 != img.get(0, 0, 1)) throw "wrong green";
  if (255 != img.get(0, 0, 2)) throw "wrong blue";

  Image two;
  vec[0] = 42;
  two.setup(5, 5, 3, vec);
  // TODO: Break this?
  if (two.get(0, 0, 0) == img.get(0, 0, 0)) throw "they match but I do not expect them too";
}

int main(int argc, char * argv[]) {
  tap::start();
  tap::test("creating the image object");
  tap::pass(badCreateShouldThrow(), "bad create should throw");
  tap::throwFail(&createViaSetup, "create then call img.setup(...)");
  tap::pass(copyImage(), "copying should work");

  tap::test("# setting a pixel");
  tap::pass(setPixelInRange(), "set a pixel in range should work");
  tap::pass(setPixelOutOfRange(), "setting a pixel out of range should throw");

  return tap::end();
};

