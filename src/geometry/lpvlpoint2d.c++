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

#include "lpvlpoint2d.h"
#include <cmath>
#include <QtCore/QPointF>
#include <QtCore/QDebug>
#include "global/lpvlmath.h"

LPVL::Point2D::Point2D()
    : m_x(NaN())
    , m_y(NaN())
{}

LPVL::Point2D::Point2D(const Point2D& other)
    : m_x(other.x())
    , m_y(other.y())
{}

LPVL::Point2D::Point2D(float x, float y)
    : m_x(x)
    , m_y(y)
{}

LPVL::Point2D::Point2D(const QPointF& other)
    : m_x(other.x())
    , m_y(other.y())
{}

LPVL::Point2D::Point2D(const Vertex& other)
    : m_x(other.x)
    , m_y(other.y)
{}

LPVL::Point2D::Point2D(const VertexT& other)
    : m_x(other.x)
    , m_y(other.y)
{}

bool LPVL::Point2D::isValid() const noexcept { return not isNaN(x()) and not isNaN(y()); }
float LPVL::Point2D::x() const { return m_x; }
float LPVL::Point2D::y() const { return m_y; }
void LPVL::Point2D::setX(float other) { m_x = other; }
void LPVL::Point2D::setY(float other) { m_y = other; }
float LPVL::Point2D::manhattanLengthToOrigin() const noexcept { return abs(x()) + abs(y()); }
LPVL::Point2D LPVL::Point2D::inverted() const noexcept { return Point2D(y(), x()); }

LPVL::Point2D LPVL::Point2D::atAngle(float angle, float radius) const noexcept
{
    return Point2D(x() + cos(angle) * radius, y() + sin(angle) * radius);
}

LPVL::Vertex LPVL::Point2D::toSimpleVertex() const noexcept { return Vertex(x(), y()); }
LPVL::VertexT LPVL::Point2D::toSimpleVertexT(float w, float h) const noexcept
{
    return VertexT(x(), y(), x() / w, y() / h);
}

QPointF LPVL::Point2D::toQPointF() const noexcept { return QPointF(x(), y()); }
LPVL::Point2D LPVL::Point2D::fromQPointF(const QPointF& qt_point) noexcept
{
    return Point2D(qt_point.x(), qt_point.y());
}

float LPVL::Point2D::scalarProduct(const Point2D& first, const Point2D& second) noexcept
{
    return first.x() * second.x() + first.y() * second.y();
}

float LPVL::Point2D::distanceBetween(const Point2D& first, const Point2D& second) noexcept
{
    return std::hypotf(second.x() - first.x(), second.y() - first.y());
}

float LPVL::Point2D::angleBetween(const Point2D& first, const Point2D& second) noexcept
{
    return rad2deg(atan2(abs(second.y() - first.y()), abs(second.x() - first.x())));
}

LPVL::Point2D& LPVL::Point2D::operator+=(const LPVL::Point2D& point)
{
    m_x += point.x();
    m_y += point.y();
    return *this;
}

LPVL::Point2D& LPVL::Point2D::operator-=(const LPVL::Point2D& point)
{
    m_x -= point.x();
    m_y -= point.y();
    return *this;
}

LPVL::Point2D& LPVL::Point2D::operator*=(float f)
{
    m_x *= f;
    m_y *= f;
    return *this;
}

LPVL::Point2D& LPVL::Point2D::operator/=(float f)
{
    m_x /= f;
    m_y /= f;
    return *this;
}

bool LPVL::operator==(const LPVL::Point2D& p1, const LPVL::Point2D& p2)
{
    bool is_nan = LPVL::isNaN(p1.x()) or LPVL::isNaN(p1.y())
                  or LPVL::isNaN(p2.x()) or LPVL::isNaN(p2.y());
    return is_nan ? false : p1.x() == p2.x() and p1.y() == p2.y();
}

bool LPVL::operator!=(const LPVL::Point2D& p1, const LPVL::Point2D& p2)
{
    return not (p1 == p2);
}

const LPVL::Point2D operator-(const LPVL::Point2D& p1, const LPVL::Point2D& p2)
{
    return LPVL::Point2D(p1.x() - p2.x(), p1.y() - p2.y());
}

const LPVL::Point2D operator+(const LPVL::Point2D& p1, const LPVL::Point2D& p2)
{
    return LPVL::Point2D(p1.x() + p2.x(), p1.y() + p2.y());
}

const LPVL::Point2D operator+(const LPVL::Point2D& p) { return p; }
const LPVL::Point2D operator-(const LPVL::Point2D& p) { return LPVL::Point2D(-p.x(), -p.y()); }
const LPVL::Point2D operator*(float f, const LPVL::Point2D& p) { return LPVL::Point2D(p.x() * f, p.y() * f); }
const LPVL::Point2D operator*(const LPVL::Point2D& p, float f) { return LPVL::Point2D(p.x() * f, p.y() * f); }
const LPVL::Point2D operator/(const LPVL::Point2D& p, float f) { return LPVL::Point2D(p.x() / f, p.y() / f); }

QDebug operator<<(QDebug d, const LPVL::Point2D& p)
{
    d.nospace() << "Point2D(" << p.x() << ", " << p.y() << ")";
    return d;
}
