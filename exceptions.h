#pragma once

#include <exception>

using namespace std; 

namespace pixicog {

class ImageMultipleSetupClass : public exception {
  virtual const char* what() const throw() {
    return "You cannot setup an image multiple times.";
  }
} ImageMultipleSetup;

class ImageNotSetupClass : public exception {
  virtual const char* what() const throw() {
    return "Image must be setup before interacting with it.";
  }
} ImageNotSetup;

class CommandMissingArgsClass : public exception {
  virtual const char* what() const throw() {
    return "The required arguments for this command are missing";
  }
} CommandMissingArgs;

class TestMissingArgs : public exception {
  virtual const char* what() const throw() {
    return "You must supply a filePath";
  }
} TestMissingArgs;

class ColorDimUnexpectedClass : public exception {
  virtual const char* what() const throw() {
    return "The color you provided has a different number of channels than expected";
  }
} ColorDimUnexpected;

}
