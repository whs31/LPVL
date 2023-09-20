//
// Created by whs31 on 20.09.23.
//

#pragma once

namespace LPVL
{
  class Point1D
  {
    public:
      explicit Point1D() noexcept;
      explicit Point1D(float x) noexcept;

      [[nodiscard]] float x() const noexcept;   void setX(float) noexcept;
      [[nodiscard]] float& refX() noexcept;

    protected:
      float m_x;
  };
} // LPVL

namespace LPVL
{
  Point1D::Point1D() noexcept
    : m_x(0)
  {}

  Point1D::Point1D(float x) noexcept
    : m_x(x)
  {}

  float Point1D::x() const noexcept { return m_x; }
  void Point1D::setX(float q) noexcept { m_x = q; }
  float& Point1D::refX() noexcept { return m_x; }
} // LPVL