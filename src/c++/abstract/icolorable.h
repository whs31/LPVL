#pragma once

#include <utility>
#include <QtGui/QColor>

namespace LPVL
{
  class IColorable
  {
    public:
      IColorable();
      explicit IColorable(QColor);

      [[nodiscard]] QColor color() const;
      virtual void setColor(const QColor&);

    protected:
      QColor m_color;
  };
} // LPVL

namespace LPVL
{
  inline IColorable::IColorable()
    : m_color(QColor()) {}

  inline IColorable::IColorable(QColor q)
    : m_color(std::move(q)) {}

  inline QColor IColorable::color() const { return m_color; }
  inline void IColorable::setColor(const QColor& q) { m_color = q; }
} // LPVL