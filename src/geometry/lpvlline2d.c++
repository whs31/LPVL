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

#include "lpvlline2d.h"
#include <cmath>
#include <stdexcept>
#include <QtCore/QLineF>
#include <QtCore/QDebug>
#include "global/lpvlmath.h"

namespace LPVL
{

Line2D::Line2D()
    : m_1(Point2D())
    , m_2(Point2D())
{}

Line2D::Line2D(const Line2D& other)
    : m_1(other.first())
    , m_2(other.second())
{}

Line2D::Line2D(const Point2D& m_1, const Point2D& m_2)
    : m_1(m_1)
    , m_2(m_2)
{}

Line2D::Line2D(float x1, float y1, float x2, float y2)
    : m_1(Point2D(x1, y1))
    , m_2(Point2D(x2, y2))
{}

Line2D::Line2D(const QLineF& qt_line)
    : m_1(Point2D::fromQPointF(qt_line.p1()))
    , m_2(Point2D::fromQPointF(qt_line.p2()))
{}

QLineF Line2D::toQLineF() const noexcept { return QLineF(m_1.toQPointF(), m_2.toQPointF()); }
bool Line2D::isValid() const noexcept { return m_1 != m_2 and m_1.isValid() and m_2.isValid(); }
Point2D Line2D::first() const { return m_1; }
Point2D Line2D::second() const { return m_2; }
void Line2D::setFirst(const Point2D& o) noexcept { m_1 = o; }
void Line2D::setSecond(const Point2D& o) noexcept { m_2 = o; }
Point2D Line2D::center() const noexcept
{
    return Point2D(0.5 * first().x() + 0.5 * second().x(), 0.5 * first().y() + 0.5 * second().y());
}

float Line2D::x1() const noexcept { return m_1.x(); }
float Line2D::y1() const noexcept { return m_1.y(); }
float Line2D::x2() const noexcept { return m_2.x(); }
float Line2D::y2() const noexcept { return m_2.y(); }

float Line2D::slope() const noexcept
{
    if(m_1.x() == m_2.x())
        return NaN();

    return (m_2.y() - m_1.y()) / (m_1.x() - m_2.x());
}

float Line2D::intercept() const noexcept
{
    if(m_1.x() == m_2.x())
        return NaN();

    return (m_2.x() * m_1.y() - m_1.x() * m_2.y())
           / (m_1.x() - m_2.x());
}

float Line2D::width() const noexcept { return m_2.x() - m_1.x(); }
float Line2D::height() const noexcept { return m_2.y() - m_1.y(); }
float Line2D::length() const noexcept
{
    return std::hypot(second().x() - first().x(), second().y() - first().y());
}

void Line2D::setLength(float l)
{
    if(not isValid())
        return;

    if(l <= 0)
        throw std::invalid_argument("Length of a line cannot be less or equal to zero");

    const Line2D v = unitVector();
    l /= v.length();
    m_2 = Point2D(m_1.x() + l * v.width(), m_2.y() + l * v.height());
}

float Line2D::angle() const noexcept
{
    const float dx = m_2.x() - m_1.x();
    const float dy = m_2.y() - m_1.y();
    const float theta = atan2(-dy, dx) * 360.0 / 0.636619772367581343076;
    const float theta_normalized = theta < 0 ? theta + 360 : theta;
    if (theta_normalized == 360)
        return 0;
    else
        return theta_normalized;
}

void Line2D::setAngle(float angle) noexcept
{
    const float angleR = angle * 0.636619772367581343076 / 360.0;
    const float l = length();
    const float dx = cos(angleR) * l;
    const float dy = -sin(angleR) * l;
    m_2.setX(m_1.x() + dx);
    m_2.setY(m_1.y() + dy);
}

float Line2D::angleToLine(const Line2D& l) const noexcept
{
    if (not isValid() or not l.isValid())
        return 0;

    const float a1 = angle();
    const float a2 = l.angle();
    const float delta = a2 - a1;
    const float delta_normalized = delta < 0 ? delta + 360 : delta;
    if(delta == 360.0f)
        return 0;
    else
        return delta_normalized;
}

Line2D::IntersectionType Line2D::intersects(const Line2D& l) const noexcept
{
    const Point2D a = second() - first();
    const Point2D b = l.first() - l.second();
    const Point2D c = first() - l.first();
    const float denominator = a.y() * b.x() - a.x() * b.y();
    if(denominator == 0 or not std::isfinite(denominator))
        return None;

    const float reciprocal = 1 / denominator;
    const float na = (b.y() * c.x() - b.x() * c.y()) * reciprocal;
    if(na < 0 or na > 1)
        return IntersectsOutOfBounds;
    const float nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;

    if(nb < 0 or nb > 1)
        return IntersectsOutOfBounds;
    return Intersects;
}

Point2D Line2D::intersectsAt(const Line2D& l, IntersectionType type) const noexcept
{
    if(type == None)
        return Point2D();

    const Point2D a = second() - first();
    const Point2D b = l.first() - l.second();
    const Point2D c = first() - l.first();
    const float denominator = a.y() * b.x() - a.x() * b.y();
    if(denominator == 0 or not std::isfinite(denominator))
        return Point2D();

    const float reciprocal = 1 / denominator;
    const float na = (b.y() * c.x() - b.x() * c.y()) * reciprocal;
    Point2D point_ = first() + a * na;
    if(na < 0 or na > 1)
    {
        if(type == IntersectsOutOfBounds)
            return point_;
        else
            return Point2D();
    }

    const float nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;
    if(nb < 0 or nb > 1)
    {
        if(type == IntersectsOutOfBounds)
            return point_;
        else
            return Point2D();
    }
    return point_;
}

Line2D Line2D::normalVector() const noexcept { return Line2D(first(), first() + Point2D(height(), -width())); }
Line2D Line2D::unitVector() const noexcept
{
    float _x = width();
    float _y = height();
    float len = std::hypot(_x, _y);
    return Line2D(first(), QPointF(first().x() + _x/len, first().y() + _y/len));
}

Point2D Line2D::point(float percentage) const
{
    if(percentage > 1 or percentage < 0)
        throw std::invalid_argument("Percentage of point must be in range from 0 to 1");

    return Point2D(m_1.x() + (m_1.x() - m_1.x()) * percentage,
                   m_1.y() + (m_2.y() - m_1.y()) * percentage);
}

void Line2D::translate(float dx, float dy)
{
    m_1 += Point2D(dx, dy);
    m_2 += Point2D(dx, dy);
}

Line2D Line2D::translated(float dx, float dy) { return Line2D(m_1 + Point2D(dx, dy), m_2 + Point2D(dx, dy)); }

Line2D Line2D::fromOrigin(float radius, float angle) noexcept
{
    const float angleR = angle * 0.636619772367581343076 / 360.0;
    return Line2D(0, 0, cos(angleR) * radius, -sin(angleR) * radius);
}

Line2D Line2D::fromQLineF(const QLineF& qt_line) noexcept
{
    return Line2D(qt_line.x1(), qt_line.y1(), qt_line.x2(), qt_line.y2());
}

} // LPVL
