// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <vector>

// local
#include "romea_core_common/containers/grid/GridIndexMapping.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
GridIndexMapping<Scalar, DIM>::GridIndexMapping()
: cellResolution_(0.),
  numberOfCellsAlongAxes_(),
  flooredMinimalPositionAlongAxes_(),
  cellCentersPositionAlongAxes_(DIM)
{
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
GridIndexMapping<Scalar, DIM>::GridIndexMapping(
  const IntervalType & extrimities,
  const Scalar & cellResolution)
: cellResolution_(cellResolution),
  numberOfCellsAlongAxes_(),
  flooredMinimalPositionAlongAxes_(),
  cellCentersPositionAlongAxes_(DIM)
{
  flooredMinimalPositionAlongAxes_.array() = cellResolution_ * (
    floor((extrimities.lower().array() / cellResolution_)) - 0.5);

  numberOfCellsAlongAxes_.array() = (ceil(extrimities.upper().array() / cellResolution_) -
    floor(extrimities.lower().array() / cellResolution_) + 1).template cast<size_t>();


  for (size_t dim = 0; dim < DIM; dim++) {
    const size_t & numberOfCellsAlongAxis = numberOfCellsAlongAxes_[dim];
    const Scalar & flooredMinimalPositionAlongAxis = flooredMinimalPositionAlongAxes_[dim];
    std::vector<Scalar> & cellCentersPositionAlongAxis = cellCentersPositionAlongAxes_[dim];

    cellCentersPositionAlongAxis.resize(numberOfCellsAlongAxis);
    for (size_t n = 0; n < numberOfCellsAlongAxis; ++n) {
      cellCentersPositionAlongAxis[n] =
        flooredMinimalPositionAlongAxis + (n + Scalar(0.5)) * cellResolution_;
    }
  }
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
GridIndexMapping<Scalar, DIM>::GridIndexMapping(
  const Scalar & maximalRange,
  const Scalar & cellResolution)
: GridIndexMapping(IntervalType(PointType::Constant(-maximalRange),
    PointType::Constant(maximalRange)), cellResolution)
{
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
const Scalar & GridIndexMapping<Scalar, DIM>::getCellResolution()const
{
  return cellResolution_;
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
const typename GridIndexMapping<Scalar, DIM>::CellIndexes &
GridIndexMapping<Scalar, DIM>::getNumberOfCellsAlongAxes()const
{
  return numberOfCellsAlongAxes_;
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
typename GridIndexMapping<Scalar, DIM>::CellIndexes
GridIndexMapping<Scalar, DIM>::computeCellIndexes(const PointType & point)const
{
  return ((point - flooredMinimalPositionAlongAxes_) / cellResolution_).template cast<size_t>();
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
typename GridIndexMapping<Scalar, DIM>::PointType
GridIndexMapping<Scalar, DIM>::computeCellCenterPosition(const CellIndexes & cellIndexes) const
{
  PointType point;
  for (size_t dim = 0; dim < DIM; dim++) {
    point(dim) = cellCentersPositionAlongAxes_[dim][cellIndexes(dim)];
  }

  return point;
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
const std::vector<Scalar> &
GridIndexMapping<Scalar, DIM>::getCellCentersPositionAlong(const size_t & axisDIM) const
{
  return cellCentersPositionAlongAxes_[axisDIM];
}

template class GridIndexMapping<float, 2>;
template class GridIndexMapping<float, 3>;
template class GridIndexMapping<double, 2>;
template class GridIndexMapping<double, 3>;

}  // namespace romea
