#include <gtest/gtest.h>
#include <iostream>

#include "vse.h"

TEST(vseAppTest, create_and_open_vse) {
  SVnodeSE    vse;
  SVSEOptions vseOpt;

  // Open the VSE
  if (vseOpen(&vse, &vseOpt) < 0) {
    // TODO
  }

  // Close the VSE
  vseClose(&vse);
}

TEST(vseAppTest, open_an_existing_vse) {
  // Just a start
  std::cout << "Hello, this is in vse app test!" << std::endl;
}