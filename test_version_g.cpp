#include "lib.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>




TEST(testVersionGoogle, ValidVersion) {

  EXPECT_GT(version(), 0);
}

