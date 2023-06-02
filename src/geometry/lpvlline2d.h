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

class QLineF;
class QDebug;

namespace LPVL
{
    class Line2D
    {
        public:
            enum IntersectionType : unsigned char
            {
                None,
                Intersects,
                IntersectsOutOfBounds
            };

            Line2D();
            Line2D(const Line2D& other);
            Line2D(const Point2D&, const Point2D&);
            Line2D(float x1, float y1, float x2, float y2);
            Line2D(const QLineF&);

            QLineF toQLineF() const noexcept;

            bool isValid() const noexcept;

            Point2D first() const;
            Point2D second() const;
            void setFirst(const Point2D&) noexcept;
            void setSecond(const Point2D&) noexcept;

            Point2D center() const noexcept;

            float x1() const noexcept;
            float y1() const noexcept;
            float x2() const noexcept;
            float y2() const noexcept;

            //! @brief Returns m component of [y = mx + b] equation
            float slope() const noexcept;

            //! @brief Returns b component of [y = mx + b] equation
            float intercept() const noexcept;

            float width() const noexcept;
            float height() const noexcept;
            float length() const noexcept;
            void setLength(float);

            float angle() const noexcept;
            void setAngle(float) noexcept;
            float angleToLine(const Line2D&) const noexcept;

            IntersectionType intersects(const Line2D&) const noexcept;
            Point2D intersectsAt(const Line2D&, IntersectionType type = Intersects) const noexcept;

            Line2D normalVector() const noexcept;
            Line2D unitVector() const noexcept;
            Point2D point(float percentage) const;

            void translate(float dx, float dy);
            Line2D translated(float dx, float dy);

            bool operator==(const Line2D&) const;
            bool operator!=(const Line2D&) const;
            friend QDebug operator<<(QDebug d, const Point2D& p);

        public:
            static Line2D fromOrigin(float radius, float angle) noexcept;
            static Line2D fromQLineF(const QLineF&) noexcept;

        private:
            Point2D m_1;
            Point2D m_2;
    };
} // LPVL

#if defined QT_CORE_LIB
    #include <QMetaType>
    Q_DECLARE_METATYPE(LPVL::Line2D*);
#endif
