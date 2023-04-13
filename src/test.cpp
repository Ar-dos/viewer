#include "gtest/gtest.h"
#include "model.h"

TEST(parser_test, s21_model) {
  char *filename = (char *)"../datasets/cube.obj";
  s21::Model test(filename);

  double eps = 0.000001;

  ASSERT_EQ(test.GetCountOfFacets(), 32);
  ASSERT_EQ(test.GetCountOfVertexes(), 8);

  ASSERT_DOUBLE_EQ(test.GetVertices()[0], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[1], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[2], 0.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[3], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[4], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[5], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[6], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[7], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[8], 0.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[9], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[10], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[11], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[12], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[13], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[14], 0.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[15], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[16], 0.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[17], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[18], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[19], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[20], 0.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[21], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[22], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[23], 1.0);

  ASSERT_EQ(test.GetIndices()[0], 0);
  ASSERT_EQ(test.GetIndices()[1], 1);
  ASSERT_EQ(test.GetIndices()[2], 1);
  ASSERT_EQ(test.GetIndices()[3], 3);
  ASSERT_EQ(test.GetIndices()[4], 3);
  ASSERT_EQ(test.GetIndices()[5], 2);
  ASSERT_EQ(test.GetIndices()[6], 2);
  ASSERT_EQ(test.GetIndices()[7], 0);

  ASSERT_EQ(test.GetIndices()[8], 0);
  ASSERT_EQ(test.GetIndices()[9], 2);
  ASSERT_EQ(test.GetIndices()[10], 2);
  ASSERT_EQ(test.GetIndices()[11], 6);
  ASSERT_EQ(test.GetIndices()[12], 6);
  ASSERT_EQ(test.GetIndices()[13], 4);
  ASSERT_EQ(test.GetIndices()[14], 4);
  ASSERT_EQ(test.GetIndices()[15], 0);

  ASSERT_EQ(test.GetIndices()[16], 6);
  ASSERT_EQ(test.GetIndices()[17], 4);
  ASSERT_EQ(test.GetIndices()[18], 4);
  ASSERT_EQ(test.GetIndices()[19], 5);
  ASSERT_EQ(test.GetIndices()[20], 5);
  ASSERT_EQ(test.GetIndices()[21], 7);
  ASSERT_EQ(test.GetIndices()[22], 7);
  ASSERT_EQ(test.GetIndices()[23], 6);

  ASSERT_EQ(test.GetIndices()[24], 5);
  ASSERT_EQ(test.GetIndices()[25], 1);
  ASSERT_EQ(test.GetIndices()[26], 1);
  ASSERT_EQ(test.GetIndices()[27], 3);
  ASSERT_EQ(test.GetIndices()[28], 3);
  ASSERT_EQ(test.GetIndices()[29], 7);
  ASSERT_EQ(test.GetIndices()[30], 7);
  ASSERT_EQ(test.GetIndices()[31], 5);

  test.XPos(1.0);
  test.YPos(1.0);
  test.ZPos(1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[0], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[1], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[2], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[3], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[4], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[5], 2.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[6], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[7], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[8], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[9], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[10], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[11], 2.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[12], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[13], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[14], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[15], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[16], 1.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[17], 2.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[18], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[19], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[20], 1.0);

  ASSERT_DOUBLE_EQ(test.GetVertices()[21], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[22], 2.0);
  ASSERT_DOUBLE_EQ(test.GetVertices()[23], 2.0);

  test.RotX(1.0);
  test.RotY(1.0);
  test.RotZ(1.0);

  ASSERT_TRUE(test.GetVertices()[0] + 1.00772150 < eps);
  ASSERT_TRUE(test.GetVertices()[1] - 1.00419 < eps);
  ASSERT_TRUE(test.GetVertices()[2] - 1.00419 < eps);

  ASSERT_TRUE(test.GetVertices()[3] - 1.47015 < eps);
  ASSERT_TRUE(test.GetVertices()[4] - 1.8252 < eps);
  ASSERT_TRUE(test.GetVertices()[5] + 0.712267 < eps);

  ASSERT_TRUE(test.GetVertices()[6] + 1.84494 < eps);
  ASSERT_TRUE(test.GetVertices()[7] - 0.684078 < eps);
  ASSERT_TRUE(test.GetVertices()[8] + 1.45884 < eps);

  ASSERT_TRUE(test.GetVertices()[9] + 2.30737 < eps);
  ASSERT_TRUE(test.GetVertices()[10] - 1.5213 < eps);
  ASSERT_TRUE(test.GetVertices()[11] + 1.166915 < eps);

  ASSERT_TRUE(test.GetVertices()[12] + 0.715795 < eps);
  ASSERT_TRUE(test.GetVertices()[13] - 1.442623 < eps);
  ASSERT_TRUE(test.GetVertices()[14] + 1.84566 < eps);

  ASSERT_TRUE(test.GetVertices()[15] + 1.17822 < eps);
  ASSERT_TRUE(test.GetVertices()[16] - 2.27985 < eps);
  ASSERT_TRUE(test.GetVertices()[17] + 1.553737 < eps);

  ASSERT_TRUE(test.GetVertices()[18] + 1.553017 < eps);
  ASSERT_TRUE(test.GetVertices()[19] - 1.13873 < eps);
  ASSERT_TRUE(test.GetVertices()[20] + 2.30031 < eps);

  ASSERT_TRUE(test.GetVertices()[21] + 2.01544 < eps);
  ASSERT_TRUE(test.GetVertices()[22] - 1.97595 < eps);
  ASSERT_TRUE(test.GetVertices()[23] + 2.008386 < eps);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
