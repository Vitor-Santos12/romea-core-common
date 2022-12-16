#ifndef ROMEA_CORE_COMMON_CONTAINERS_GRID_GRID_HPP_
#define ROMEA_CORE_COMMON_CONTAINERS_GRID_GRID_HPP_

// std
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <vector>

// Eigen
#include <Eigen/Core>


namespace romea {

template <typename T , size_t DIM>
class Grid
{
public :

  using CellIndexes = Eigen::Matrix<size_t, DIM, 1>;

public :

  Grid();

  explicit Grid(const CellIndexes & numberOfCellsAlongAxes);

  virtual ~Grid() = default;

  void init(const CellIndexes & numberOfCellsAlongAxes);

public :

  std::vector<T> & getBuffer();

  const std::vector<T> & getBuffer() const;

  void setValue(const T & value);

public :

  virtual T & operator()(const CellIndexes & cellIndexes);

  virtual const T & operator()(const CellIndexes & cellIndexes)const;

  const CellIndexes & getNumberOfCellsAlongAxes() const ;

protected :

  virtual size_t computeCellLinearIndex_(const CellIndexes & CellIndexes) const;

protected :

  CellIndexes numberOfCellsAlongAxes_;
  CellIndexes indexCoefficients_;
  std::vector<T> buffer_;
};


//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
Grid<T, DIM>::Grid():
  numberOfCellsAlongAxes_(),
  indexCoefficients_(),
  buffer_()
{
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
Grid<T, DIM>::Grid(const CellIndexes & numberOfCellsAlongAxes):
  numberOfCellsAlongAxes_(),
  indexCoefficients_(),
  buffer_()
{
  init(numberOfCellsAlongAxes);
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
void Grid<T, DIM>::init(const CellIndexes & numberOfCellsAlongAxes)
{
  numberOfCellsAlongAxes_ = numberOfCellsAlongAxes;
  buffer_.resize(numberOfCellsAlongAxes_.array().prod());

  indexCoefficients_[0] = 1;
  indexCoefficients_[1] = numberOfCellsAlongAxes_[0];
  //TODO utiliser ici constexpr if
  if (DIM == 3) indexCoefficients_[2] = numberOfCellsAlongAxes_[1]*numberOfCellsAlongAxes_[0];

}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
std::vector<T> & Grid<T, DIM>::getBuffer()
{
  return buffer_;
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
const std::vector<T> & Grid<T, DIM>::getBuffer() const
{
  return buffer_;
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
size_t Grid<T, DIM>::computeCellLinearIndex_(const CellIndexes & cellIndexes) const
{
  assert((cellIndexes.array() < numberOfCellsAlongAxes_.array()).prod());
  return cellIndexes.dot(indexCoefficients_);
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
T & Grid<T, DIM>::operator()(const CellIndexes & cellIndexes)
{
  return buffer_[computeCellLinearIndex_(cellIndexes)];
}

//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
const T & Grid<T, DIM>::operator()(const CellIndexes & cellIndexes)const
{
  return buffer_[computeCellLinearIndex_(cellIndexes)];
}


//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
const typename Grid<T, DIM>::CellIndexes &
Grid<T, DIM>::getNumberOfCellsAlongAxes() const
{
  return numberOfCellsAlongAxes_;
}


//-----------------------------------------------------------------------------
template <typename T , size_t DIM>
void Grid<T, DIM>::setValue(const T & value)
{
  std::fill(std::begin(buffer_), std::end(buffer_), value);
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_GRID_GRID_HPP_
