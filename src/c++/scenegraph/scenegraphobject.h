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

#include <QtQuick/QQuickItem>

namespace LPVL
{
  class ScenegraphObject : public QQuickItem
  {
    Q_OBJECT

    public:
      explicit ScenegraphObject(QQuickItem* parent = nullptr);

    protected:
      virtual QSGNode* createNode();
      virtual void setupChildNodes(QSGNode* node) = 0;
      virtual void setupNodeColors(QSGNode* node) = 0;
      virtual void drawCall(QSGNode* node) = 0;

      [[nodiscard]] bool recolor() const;
      void requireRecolor();
      void fulfillRecolor();

    private:
      QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

    private:
      bool m_require_recolor;
  };
} // LPVL
