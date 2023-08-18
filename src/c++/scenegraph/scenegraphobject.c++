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

#include "scenegraphobject.h"
#include <QtQuick/QSGNode>

namespace LPVL
{
  /**
   * \class ScenegraphObject
   * \brief Базовый класс для объектов Qt Quick Scenegraph.
   * \details Предоставляет более безопасный способ работы с
   * методом updatePaintNode класса QQuickItem, предоставляя
   * функции, вызываемые в строгом определенном порядке.
   *
   * Порядок вызова функций в цикле отрисовки:
   *    - createNode - вызывается один раз при создании объекта.
   *    - setupChildNodes - вызывается один раз при создании объекта.
   *    - setupNodeColors - вызывается каждый раз, когда перед циклом отрисовки была вызвана функция requireRecolor.
   *    - drawCall - вызывается каждый цикл отрисовки
   */

  /**
   * \brief Конструктор по умолчанию.
   * \details Устанавливает флаг **ItemHasContents** для QQuickItem, таким образом, сообщая, что
   * объект, наследуемый от этого класса, требует отрисовки на Scenegraph.
   * \param parent - родительский объект.
   */
  ScenegraphObject::ScenegraphObject(QQuickItem* parent)
    : QQuickItem(parent)
    , m_require_recolor(false)
  {
    this->setFlag(ItemHasContents);
  }

  QSGNode* ScenegraphObject::updatePaintNode(QSGNode* old_node, QQuickItem::UpdatePaintNodeData* x)
  {
    (void)x;
    if(old_node == nullptr)
    {
      old_node = createNode();
      setupChildNodes(old_node);
    }

    if(recolor())
      setupNodeColors(old_node);

    drawCall(old_node);

    for(int i = 0; i < old_node->childCount(); i++)
      old_node->childAtIndex(i)->markDirty(recolor() ? (QSGNode::DirtyGeometry |  QSGNode::DirtyMaterial) : QSGNode::DirtyGeometry);

    old_node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
    return old_node;
  }

  /**
   * \brief Создает корневую ноду.
   * \details Эту функцию не нужно переопределять в большинстве случаев.
   * Если наследуемый класс не будет содержать дочерних нод, то имеет смысл
   * переопределить этот метод таким образом:
   * \code {.cpp}
     class Derived : public LPVL::ScenegraphObject
     {
        // ...

        QSGNode* createNode() override
        {
            return static_cast<QSGNode*>(new QSGGeometryNode);
        }

        // ...
     }
   * \endcode
   * \return По умолчанию возвращает указатель на новый объект QSGNode.
   */
  QSGNode* ScenegraphObject::createNode() { return new QSGNode; }

  /**
   * \fn virtual void ScenegraphObject::setupChildNodes(QSGNode* node) = 0
   * \brief Создает дочерние ноды.
   * \details Вызывается один раз после создания корневой ноды.
   * Пример имплементации функции:
   * \code {.cpp}
     void setupChildNodes(QSGNode* node) override
     {
       tree()[BackgroundNode] = LPVL::utils::createSimpleGeometryNode(palette().background(), QSGGeometry::DrawTriangles);
       tree()[ProfileNode] = LPVL::utils::createSimpleGeometryNode(palette().overlay(), DrawQuadStrip);
       tree()[RouteNode] = LPVL::utils::createSimpleGeometryNode(palette().accent(), QSGGeometry::DrawLineStrip, ROUTE_LINE_WIDTH);
       tree()[MetricsNode] = LPVL::utils::createSimpleGeometryNode(palette().warn(), QSGGeometry::DrawLineStrip, METRICS_LINE_WIDTH);
       tree()[MetricsPointNode] = LPVL::utils::createSimpleGeometryNode(palette().warn(), QSGGeometry::DrawPoints, METRICS_ROUNDING_WIDTH);

       for(const auto&[key, value] : tree())
         node->appendChildNode(value);
     }
   * \endcode
   */

  /**
   * \fn virtual void ScenegraphObject::setupNodeColors(QSGNode* node) = 0;
   * \brief Задает цвета для материалов дочерних нод.
   * \details Вызывается каждый раз, когда перед циклом отрисовки была вызвана функция requireRecolor.
   * Пример имплементации:
   * \code {.cpp}
     void setupNodeColors(QSGNode* node) override
     {
       dynamic_cast<QSGFlatColorMaterial*>(tree()[BackgroundNode]->material())->setColor(palette().background());
       dynamic_cast<QSGFlatColorMaterial*>(tree()[ProfileNode]->material())->setColor(palette().overlay());
       dynamic_cast<QSGFlatColorMaterial*>(tree()[RouteNode]->material())->setColor(palette().accent());
       dynamic_cast<QSGFlatColorMaterial*>(tree()[MetricsNode]->material())->setColor(palette().warn());
       dynamic_cast<QSGFlatColorMaterial*>(tree()[MetricsPointNode]->material())->setColor(palette().warn());
     }
   * \endcode
   */

  /**
   * \fn virtual void ScenegraphObject::drawCall(QSGNode* node) = 0;
   * \brief Основная функция цикла отрисовки.
   * \details Вызывается каждый раз, когда запрошено обновление графики (например, через вызов QQuickItem::update).
   */

  /**
   * \brief Возвращает состояние флага на обновление материалов нод.
   * \return Значение флага на обновление материалов нод.
   */
  bool ScenegraphObject::recolor() const { return m_require_recolor; }

  /**
   * \brief Запрашивает обновление материалов в следующем цикле.
   * \note Вызов этой функции вызовет обновление всех нод - QQuickItem::update.
   */
  void ScenegraphObject::requireRecolor() { m_require_recolor = true; this->update(); }

  /**
   * \brief Сбрасывает флаг на обновление материалов.
   */
  void ScenegraphObject::fulfillRecolor() { m_require_recolor = false; }
} // LPVL