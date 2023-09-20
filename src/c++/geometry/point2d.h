//
// Created by whs31 on 20.09.23.
//

#pragma once
#include "LPVL/Point1D"

namespace LPVL
{
  class Point2D : public Point1D
  {
    public:
      explicit Point2D() noexcept;
      explicit Point2D(float x, float y) noexcept;

      [[nodiscard]] float y() const noexcept;   void setY(float) noexcept;
      [[nodiscard]] float& refY() noexcept;

    protected:
      float m_y;
  };
} // LPVL

namespace LPVL
{
  inline Point2D::Point2D() noexcept
    : Point1D()
    , m_y(0)
  {}

  inline Point2D::Point2D(float x, float y) noexcept
    : Point1D(x)
    , m_y(y)
  {}

  inline float Point2D::y() const noexcept { return m_y; }
  inline void Point2D::setY(float q) noexcept { m_y = q; }
  inline float& Point2D::refY() noexcept { return m_y; }
} // LPVL