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

#include <QtQuick/QSGSimpleMaterial>
#include "state.h"

namespace LPVL
{
  class FadingGradientShader : public QSGSimpleMaterialShader<State>
  {
    public:
      static QSGMaterialShader* createShader();
      static QSGSimpleMaterialComparableMaterial<State>* createMaterial();

      const char* vertexShader() const override;
      const char* fragmentShader() const override;
      QList<QByteArray> attributes() const override;
      void updateState(const State* state, const State*) override;
      void resolveUniforms() override;

    private:
      int id_color;
  };
} // LPVL
