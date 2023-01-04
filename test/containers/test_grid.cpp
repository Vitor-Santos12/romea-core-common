// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/containers/grid/GridIndexMapping.hpp"
#include "romea_core_common/containers/grid/WrappableGrid.hpp"
#include "romea_core_common/containers/grid/RayTracing.hpp"

class TestGridIndexMapping2d : public ::testing::Test
{
public:
  using PointType = romea::GridIndexMapping2d::PointType;
  using CellIndexes = romea::GridIndexMapping2d::CellIndexes;

  TestGridIndexMapping2d()
  : gridExtremities(PointType(-1, -2), PointType(1, 2)),
    gridMapping(gridExtremities, 1)
  {
  }

  romea::Interval2D<double> gridExtremities;
  romea::GridIndexMapping2d gridMapping;
};

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping2d, isNumberOfCellsOK)
{
  EXPECT_EQ(gridMapping.getNumberOfCellsAlongAxes().x(), 3);
  EXPECT_EQ(gridMapping.getNumberOfCellsAlongAxes().y(), 5);
}

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping2d, isComputeCellCenterPositionOK)
{
  PointType cellCenterPosition = gridMapping.computeCellCenterPosition(CellIndexes(0, 0));
  EXPECT_NEAR(cellCenterPosition.x(), -1, 0.01);
  EXPECT_NEAR(cellCenterPosition.y(), -2, 0.01);
}

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping2d, iscomputeCellIndexesOK)
{
  CellIndexes cellIndexes = gridMapping.computeCellIndexes(PointType(0.2, 0.2));
  EXPECT_EQ(cellIndexes.x(), 1);
  EXPECT_EQ(cellIndexes.y(), 2);
}


class TestGridIndexMapping3d : public ::testing::Test
{
public:
  using PointType = romea::GridIndexMapping3d::PointType;
  using CellIndexes = romea::GridIndexMapping3d::CellIndexes;

  TestGridIndexMapping3d()
  : gridExtremities(PointType(-1, -2, -3), PointType(1, 2, 3)),
    gridMapping(gridExtremities, 1)
  {
  }

  romea::Interval3D<double> gridExtremities;
  romea::GridIndexMapping3d gridMapping;
};

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping3d, isNumberOfCellsOK)
{
  EXPECT_EQ(gridMapping.getNumberOfCellsAlongAxes().x(), 3);
  EXPECT_EQ(gridMapping.getNumberOfCellsAlongAxes().y(), 5);
  EXPECT_EQ(gridMapping.getNumberOfCellsAlongAxes().z(), 7);
}

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping3d, isComputeCellCenterPositionOK)
{
  PointType cellCenterPosition = gridMapping.computeCellCenterPosition(CellIndexes(0, 0, 0));

  EXPECT_NEAR(cellCenterPosition.x(), -1, 0.01);
  EXPECT_NEAR(cellCenterPosition.y(), -2, 0.01);
  EXPECT_NEAR(cellCenterPosition.z(), -3, 0.01);
}

//-----------------------------------------------------------------------------
TEST_F(TestGridIndexMapping3d, iscomputeCellIndexesOK)
{
  CellIndexes cellIndexes = gridMapping.computeCellIndexes(PointType(0.2, 0.2, 0.2));

  EXPECT_EQ(cellIndexes.x(), 1);
  EXPECT_EQ(cellIndexes.y(), 2);
  EXPECT_EQ(cellIndexes.z(), 3);
}

//-----------------------------------------------------------------------------
class TestGrid2d : public ::testing::Test
{
public:
  using CellIndexes = romea::Grid<int, 2>::CellIndexes;

  TestGrid2d()
  : grid(CellIndexes(3, 3))
  {
  }

  void SetUp() override
  {
    int n = 0;
    for (size_t yi = 0; yi < 3; ++yi) {
      for (size_t xi = 0; xi < 3; ++xi) {
        grid(CellIndexes(xi, yi)) = n++;
      }
    }
  }

  romea::Grid<int, 2> grid;
};

//-----------------------------------------------------------------------------
TEST_F(TestGrid2d, checkDataBufferStorage)
{
  for (size_t n = 0; n < 9; ++n) {
    EXPECT_EQ(grid.getBuffer()[n], n);
  }
}

//-----------------------------------------------------------------------------
TEST_F(TestGrid2d, setDefaultValue)
{
  grid.setValue(1);

  for (const auto & cellValue : grid.getBuffer()) {
    EXPECT_EQ(cellValue, 1);
  }
}

//-----------------------------------------------------------------------------
class TestGrid3d : public ::testing::Test
{
public:
  using CellIndexes = romea::Grid<int, 3>::CellIndexes;

  TestGrid3d()
  : grid(CellIndexes(3, 3, 3))
  {
  }

  void SetUp() override
  {
    int n = 0;
    for (size_t zi = 0; zi < 3; ++zi) {
      for (size_t yi = 0; yi < 3; ++yi) {
        for (size_t xi = 0; xi < 3; ++xi) {
          grid(CellIndexes(xi, yi, zi)) = n++;
        }
      }
    }
  }

  romea::Grid<int, 3> grid;
};

//-----------------------------------------------------------------------------
TEST_F(TestGrid3d, checkDataBufferStorage)
{
  for (size_t n = 0; n < 27; ++n) {
    EXPECT_EQ(grid.getBuffer()[n], n);
  }
}

//-----------------------------------------------------------------------------
TEST_F(TestGrid3d, setDefaultValue)
{
  grid.setValue(1);

  for (const auto & cellValue : grid.getBuffer()) {
    EXPECT_EQ(cellValue, 1);
  }
}

//-----------------------------------------------------------------------------
TEST(TestContainers, testCircularGrid2D)
{
  using CellIndexes = romea::WrappableGrid<int, 2>::CellIndexes;
  using CellIndexesOffset = romea::WrappableGrid<int, 2>::CellIndexesOffset;

  romea::WrappableGrid<int, 2> grid(CellIndexes(3, 3));

  int n = 0;
  for (size_t yi = 0; yi < 3; ++yi) {
    for (size_t xi = 0; xi < 3; ++xi) {
      grid(CellIndexes(xi, yi)) = n++;
    }
  }

  int deltax = 1;
  int deltay = -1;

  grid.translate(CellIndexesOffset(deltax, deltay));

  EXPECT_EQ(grid(CellIndexes(0, 1)), 1);
  EXPECT_EQ(grid(CellIndexes(1, 1)), 2);
  EXPECT_EQ(grid(CellIndexes(0, 2)), 4);
  EXPECT_EQ(grid(CellIndexes(1, 2)), 5);
}

//-----------------------------------------------------------------------------
class TestCircularGrid3D : public ::testing::Test
{
public:
  using CellIndexes = romea::WrappableGrid<int, 3>::CellIndexes;
  using CellIndexesOffset = romea::WrappableGrid<int, 3>::CellIndexesOffset;

  TestCircularGrid3D()
  : grid(CellIndexes(3, 3, 3))
  {
  }

  void SetUp() override
  {
    int n = 0;
    for (size_t zi = 0; zi < 3; ++zi) {
      for (size_t yi = 0; yi < 3; ++yi) {
        for (size_t xi = 0; xi < 3; ++xi) {
          grid(CellIndexes(xi, yi, zi)) = n++;
        }
      }
    }
  }

  romea::WrappableGrid<int, 3> grid;
};

//-----------------------------------------------------------------------------
TEST_F(TestCircularGrid3D, testGridValuesAfterTranslate)
{
  grid.translate(CellIndexesOffset(1, -1, 2));

  EXPECT_EQ(grid(CellIndexes(0, 1, 0)), 19);
  EXPECT_EQ(grid(CellIndexes(0, 2, 0)), 22);
  EXPECT_EQ(grid(CellIndexes(1, 1, 0)), 20);
  EXPECT_EQ(grid(CellIndexes(1, 2, 0)), 23);
}

//-----------------------------------------------------------------------------
TEST_F(TestCircularGrid3D, isGetIndexOffsetOK)
{
  grid.translate(CellIndexesOffset(1, -1, 4));

  EXPECT_EQ(grid.getIndexOffsetAlongAxes().x(), 1);
  EXPECT_EQ(grid.getIndexOffsetAlongAxes().y(), 2);
  EXPECT_EQ(grid.getIndexOffsetAlongAxes().z(), 1);
}

//-----------------------------------------------------------------------------
TEST_F(TestCircularGrid3D, hasEmptyValuesAfterTranslate)
{
  grid.translate(CellIndexesOffset(3, -3, 3));

  for (size_t zi = 0; zi < 3; ++zi) {
    for (size_t yi = 0; yi < 3; ++yi) {
      for (size_t xi = 0; xi < 3; ++xi) {
        EXPECT_DOUBLE_EQ(grid(CellIndexes(xi, yi, zi)), 0.);
      }
    }
  }
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
