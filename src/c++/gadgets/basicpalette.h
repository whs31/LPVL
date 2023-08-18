/* ---------------------------------------------------------------------
 * LPVL - Linear Algebra, Plotting and Visualisation Library
 * Copyright (C) 2023 whs31.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 * http://www.gnu.org/licenses.
 *
 * github.com/whs31/lpvl
 * ---------------------------------------------------------------------- */

#pragma once
#include <QtCore/QObject>
#include <QtGui/QColor>

namespace LPVL
{
  class BasicPalette
  {
    Q_GADGET
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(QColor overlay READ overlay WRITE setOverlay)
    Q_PROPERTY(QColor overlay2 READ overlay2 WRITE setOverlay2)
    Q_PROPERTY(QColor accent READ accent WRITE setAccent)
    Q_PROPERTY(QColor warn READ warn WRITE setWarn)
    Q_PROPERTY(QColor error READ error WRITE setError)
    Q_PROPERTY(QColor info READ info WRITE setInfo)

    public:
      BasicPalette();

      [[nodiscard]] QColor background() const; void setBackground(const QColor&);
      [[nodiscard]] QColor foreground() const; void setForeground(const QColor&);
      [[nodiscard]] QColor overlay() const; void setOverlay(const QColor&);
      [[nodiscard]] QColor overlay2() const; void setOverlay2(const QColor&);
      [[nodiscard]] QColor accent() const; void setAccent(const QColor&);
      [[nodiscard]] QColor warn() const; void setWarn(const QColor& color);
      [[nodiscard]] QColor error() const; void setError(const QColor& color);
      [[nodiscard]] QColor info() const; void setInfo(const QColor& color);

    private:
      QColor m_background;
      QColor m_foreground;
      QColor m_overlay;
      QColor m_overlay2;
      QColor m_accent;
      QColor m_warn;
      QColor m_error;
      QColor m_info;
  };
} // LPVL

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(LPVL::BasicPalette)
