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

#include "LPVL/Global"
#include "LPVL/Point2D"

class QRectF;
class QDebug;

namespace LPVL
{
    class LPVL_EXPORT Rectangle
    {
        public:
            Rectangle();
            Rectangle(const Rectangle& other);
            Rectangle(const QRectF& other);
            Rectangle(const Point2D& top_left, const Point2D& bottom_right);
            Rectangle(const Point2D& top_left, float width, float height);

            QRectF toQRectF() const noexcept;

            float width() const noexcept;
            float height() const noexcept;
            float area() const noexcept;

            float top() const noexcept;
            float bottom() const noexcept;
            float left() const noexcept;
            float right() const noexcept;

            Point2D topLeft() const noexcept;
            Point2D topRight() const noexcept;
            Point2D bottomLeft() const noexcept;
            Point2D bottomRight() const noexcept;
            Point2D center() const noexcept;

            bool isValid() const noexcept;
            bool isSquare() const noexcept;
            bool contains(const Point2D& point) const noexcept;
            bool intersects(const Rectangle& rect) const noexcept;
            Rectangle intersection(const Rectangle& rect) const noexcept;

            void setTop(float) noexcept;
            void setBottom(float) noexcept;
            void setLeft(float) noexcept;
            void setRight(float) noexcept;

            void translate(float dx, float dy) noexcept;
            void scale(float dw, float dh) noexcept;
            void normalize() noexcept;
            void invert() noexcept;

            Rectangle normalized() const noexcept;
            Rectangle inverted() const noexcept;

            friend bool operator==(const Rectangle&, const Rectangle&);
            friend bool operator!=(const Rectangle&, const Rectangle&);
            friend QDebug operator<<(QDebug d, const Point2D& p);

        public:
            static Rectangle fromQRectF(const QRectF&) noexcept;

        private:
            Point2D points[4];
    };
} // LPVL
