#include <gtest/gtest.h>

#include <tuple>

#include "lib/lib.h"

class AddTest : public ::testing::TestWithParam<std::tuple<int, int, int>> {};

TEST_P(AddTest, AddFunction) {
  int a, b, expected;
  std::tie(a, b, expected) = GetParam();

  EXPECT_EQ(lib::Calculator::add(a, b), expected);
}

// Шаг 3: Регистрация тестовых данных
INSTANTIATE_TEST_SUITE_P(AddTestCases, AddTest,
                         ::testing::Values(std::make_tuple(1, 2, 3), std::make_tuple(-1, 1, 0),
                                           std::make_tuple(0, 0, 0)));