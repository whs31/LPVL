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

#include "utils.h"
#include <QtQuick/QSGFlatColorMaterial>

/**
 * \brief Пространство имен для вспомогательных функций библиотеки LPVL.
 */
namespace LPVL::utils
{
  /**
   * \brief Создает новую ноду геометрии с простым материалом с указанными параметрами.
   * \param color - цвет отрисовки ноды.
   * \param drawing_mode - тип отрисовки ноды. См. QSGGeometry::DrawingMode.
   * \param mode - опция создания ноды. См. CreationMode.
   * \param line_width - толщина линии. <i>По умолчанию равно 1.</i>
   * \return Указатель на созданную ноду.
   */
  QSGGeometryNode* createSimpleGeometryNode(const QColor& color, unsigned int drawing_mode, CreationMode mode, float line_width)
  {
    auto ret = new QSGGeometryNode;
    if(mode == EmptyNode)
      goto returning;

    if(mode == GeometryAndMaterial or mode == OnlyMaterial)
    {
      auto* material = new QSGFlatColorMaterial;
      material->setColor(color);
      ret->setMaterial(material);
    }
    if(mode == GeometryAndMaterial or mode == OnlyGeometry)
    {
      auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
      geometry->setDrawingMode(drawing_mode);
      geometry->setLineWidth(line_width);
      ret->setGeometry(geometry);
    }
    ret->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    returning:
      return ret;
  }

  QSGGeometry::Point2D fromTexturedPoint2D(const QSGGeometry::TexturedPoint2D& q) { return QSGGeometry::Point2D({q.x, q.y}); }
  QSGGeometry::TexturedPoint2D fromPoint2D(const QSGGeometry::Point2D& q, float u, float v) { return QSGGeometry::TexturedPoint2D({q.x, q.y, u, v}); }
  QSGGeometry::TexturedPoint2D fromPoint2DBounded(const QSGGeometry::Point2D& q, double width, double height) {
    return QSGGeometry::TexturedPoint2D({q.x, q.y, q.x / static_cast<float>(width), q.y / static_cast<float>(height)});
  }
} // LPVL::utils