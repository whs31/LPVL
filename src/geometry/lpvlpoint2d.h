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
#include "lpvlglvertex.h"

class QPointF;
class QDebug;

namespace LPVL
{
    class LPVL_EXPORT Point2D
    {
        public:
            Point2D();
            Point2D(const Point2D& other);
            Point2D(float x, float y);
            Point2D(const QPointF& other);
            Point2D(const Vertex& other);
            Point2D(const VertexT& other);

            bool isValid() const noexcept;

            float x() const; void setX(float);
            float y() const; void setY(float);

            float manhattanLengthToOrigin() const noexcept;
            Point2D inverted() const noexcept;
            Point2D atAngle(float angle, float radius) const noexcept;

            Vertex toSimpleVertex() const noexcept;
            VertexT toSimpleVertexT(float w = 1, float h = 1) const noexcept;
            QPointF toQPointF() const noexcept;

            friend bool operator==(const Point2D&, const Point2D&);
            friend bool operator!=(const Point2D&, const Point2D&);
            friend const Point2D operator+(const Point2D&, const Point2D&);
            friend const Point2D operator-(const Point2D&, const Point2D&);
            friend const Point2D operator+(const Point2D&);
            friend const Point2D operator-(const Point2D&);
            friend const Point2D operator*(float, const Point2D&);
            friend const Point2D operator*(const Point2D&, float);
            friend const Point2D operator/(const Point2D&, float);
            Point2D& operator+=(const Point2D& point);
            Point2D& operator-=(const Point2D& point);
            Point2D& operator*=(float f);
            Point2D& operator/=(float f);
            Point2D& operator=(const Point2D& other);

            friend QDebug operator<<(QDebug d, const Point2D& p);

        public:
            static Point2D fromQPointF(const QPointF& qt_point) noexcept;
            static float scalarProduct(const Point2D& first, const Point2D& second) noexcept;
            static float distanceBetween(const Point2D& first, const Point2D& second) noexcept;
            static float angleBetween(const Point2D& first, const Point2D& second) noexcept;

        private:
            float m_x;
            float m_y;
    };
} // LPVL

#if defined QT_CORE_LIB
    #include <QMetaType>
    Q_DECLARE_METATYPE(LPVL::Point2D*);
#endif
