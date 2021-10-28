#include <gtest/gtest.h>
#include <iostream>

#include "vse.h"

TEST(vseAppTest, create_and_open_vse) {
  SVnodeSE *pVse;

  // Open the VSE
  if ((pVse = vseOpen(NULL)) == NULL) {
    // TODO
  }

  // Close the VSE
  vseClose(pVse);
}

TEST(vseAppTest, open_an_existing_vse) {
  // Just a start
  std::cout << "Hello, this is in vse app test!" << std::endl;
}