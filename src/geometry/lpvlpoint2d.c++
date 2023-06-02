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

namespace LPVL
{

Point2D::Point2D()
    : m_x(NaN())
    , m_y(NaN())
{}

Point2D::Point2D(const Point2D& other)
    : m_x(other.x())
    , m_y(other.y())
{}

Point2D::Point2D(float x, float y)
    : m_x(x)
    , m_y(y)
{}

Point2D::Point2D(const QPointF& other)
    : m_x(other.x())
    , m_y(other.y())
{}

Point2D::Point2D(const Vertex& other)
    : m_x(other.x)
    , m_y(other.y)
{}

Point2D::Point2D(const VertexT& other)
    : m_x(other.x)
    , m_y(other.y)
{}

bool Point2D::isValid() const noexcept { return not isNaN(x()) and not isNaN(y()); }
float Point2D::x() const { return m_x; }
float Point2D::y() const { return m_y; }
void Point2D::setX(float other) { m_x = other; }
void Point2D::setY(float other) { m_y = other; }
float Point2D::manhattanLengthToOrigin() const noexcept { return abs(x()) + abs(y()); }
Point2D Point2D::inverted() const noexcept { return Point2D(y(), x()); }

Point2D Point2D::atAngle(float angle, float radius) const noexcept
{
    return Point2D(x() + cos(angle) * radius, y() + sin(angle) * radius);
}

Vertex Point2D::toSimpleVertex() const noexcept { return Vertex(x(), y()); }
VertexT Point2D::toSimpleVertexT(float w, float h) const noexcept { return VertexT(x(), y(), x() / w, y() / h); }

QPointF Point2D::toQPointF() const noexcept { return QPointF(x(), y()); }
Point2D Point2D::fromQPointF(const QPointF& qt_point) noexcept { return Point2D(qt_point.x(), qt_point.y()); }

float Point2D::scalarProduct(const Point2D& first, const Point2D& second) noexcept
{
    return first.x() * second.x() + first.y() * second.y();
}

float Point2D::distanceBetween(const Point2D& first, const Point2D& second) noexcept
{
    return std::hypotf(second.x() - first.x(), second.y() - first.y());
}

float Point2D::angleBetween(const Point2D& first, const Point2D& second) noexcept
{
    return rad2deg(atan2(abs(second.y() - first.y()), abs(second.x() - first.x())));
}

Point2D& Point2D::operator+=(const Point2D& point)
{
    m_x += point.x();
    m_y += point.y();
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& point)
{
    m_x -= point.x();
    m_y -= point.y();
    return *this;
}

Point2D& Point2D::operator*=(float f)
{
    m_x *= f;
    m_y *= f;
    return *this;
}

Point2D& Point2D::operator/=(float f)
{
    m_x /= f;
    m_y /= f;
    return *this;
}

Point2D& Point2D::operator=(const Point2D& other)
{
    if(this == &other)
        return *this;

    m_x = other.x();
    m_y = other.y();
    return *this;
}

bool operator==(const Point2D& p1, const Point2D& p2)
{
    bool is_nan = isNaN(p1.x()) or isNaN(p1.y())
                  or isNaN(p2.x()) or isNaN(p2.y());
    return is_nan ? false : p1.x() == p2.x() and p1.y() == p2.y();
}

bool operator!=(const Point2D& p1, const Point2D& p2)
{
    return not (p1 == p2);
}

const Point2D operator+(const Point2D& p1, const Point2D& p2)
{
    return Point2D(p1.x() + p2.x(), p1.y() + p2.y());
}

const Point2D operator+(const Point2D& p) { return p; }
const Point2D operator-(const Point2D& p) { return Point2D(-p.x(), -p.y()); }
const Point2D operator*(float f, const Point2D& p) { return Point2D(p.x() * f, p.y() * f); }
const Point2D operator*(const Point2D& p, float f) { return Point2D(p.x() * f, p.y() * f); }
const Point2D operator/(const Point2D& p, float f) { return Point2D(p.x() / f, p.y() / f); }

QDebug operator<<(QDebug d, const Point2D& p)
{
    d.nospace() << "Point2D(" << p.x() << ", " << p.y() << ")";
    return d;
}

} // LPVL
