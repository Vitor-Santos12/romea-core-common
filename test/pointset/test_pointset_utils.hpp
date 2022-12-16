// std
#include <fstream>
#include <string>
#include <vector>

// romea
#include "romea_core_common/pointset/algorithms/Correspondence.hpp"
#include "romea_core_common/pointset/algorithms/NormalAndCurvatureEstimation.hpp"

//-----------------------------------------------------------------------------
template < class PointType>
romea::PointSet<PointType>
loadScan(const std::string & filename)
{
  std::string path = std::string(TEST_DIR);
  std::ifstream data(path +filename);
  //  ASSERT_FALSE(data.is_open());

  romea::PointSet<PointType> scan;
  if (romea::PointTraits<PointType>::DIM == 2)
  {
    PointType p;
    scan.reserve(1081);
    while (!data.eof())
    {
      data >> p[0] >> p[1];
      scan.push_back(p);
    }
  } else {
    PointType p;
    scan.reserve(100000);
    while (!data.eof())
    {
      data >> p[0] >> p[1] >> p[2];
      scan.push_back(p);
    }
  }

  return scan;
}

//-----------------------------------------------------------------------------
template < class PointType>
romea::PointSet<PointType>
projectScan(const romea::PointSet<PointType> & sourceScan,
            const Eigen::Transform<typename PointType::Scalar,
            romea::PointTraits<PointType>::DIM, Eigen::Affine> & tranformation)
{
  romea::PointSet<PointType> targetScan(sourceScan.size());
  for (size_t n = 0; n < sourceScan.size(); n++)
  {
    targetScan[n] = tranformation* sourceScan[n];
  }

  return targetScan;
}

//-----------------------------------------------------------------------------
template < class PointType>
romea::NormalSet<PointType>
computeNormals(const romea::PointSet<PointType> & scan)
{
  romea::NormalSet<PointType> normals(scan.size());
  romea::NormalAndCurvatureEstimation<PointType> normalEstimation(20);
  normalEstimation.compute(scan, normals);
  return normals;
}

//-----------------------------------------------------------------------------
std::vector<romea::Correspondence> fakeCorrespondences(size_t numberOfCorrespondences)
{
  std::vector<romea::Correspondence> correspondences(numberOfCorrespondences);

  for (size_t n=0; n < numberOfCorrespondences; n++)
  {
    correspondences[n].sourcePointIndex = n;
    correspondences[n].targetPointIndex = n;
    correspondences[n].squareDistanceBetweenPoints = 0;
  }
  
  return correspondences;
}
