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

#include "radialgradientshader.h"

/**
 * \class QSGSimpleMaterialShader
 * \extends QSGMaterialShader
 */

namespace LPVL
{
  QSGMaterialShader* RadialGradientShader::createShader() { return new RadialGradientShader; }
  QSGSimpleMaterialComparableMaterial<State>* RadialGradientShader::createMaterial() {
    return new QSGSimpleMaterialComparableMaterial<State>(RadialGradientShader::createShader);
  }

  const char* RadialGradientShader::vertexShader() const
  {
    return "attribute highp vec4 aVertex;           \n"
           "attribute highp vec2 aTexCoord;         \n"
           "uniform highp mat4 qt_Matrix;           \n"
           "varying highp vec2 texCoord;            \n"
           "void main() {                           \n"
           "    gl_Position = qt_Matrix * aVertex;  \n"
           "    texCoord = aTexCoord;               \n"
           "}";
  }

  const char* RadialGradientShader::fragmentShader() const
  {
    return "uniform lowp float qt_Opacity;                  \n"
           "uniform lowp vec4 color;                        \n"
           "varying highp vec2 texCoord;                    \n"
           "void main () {                                  \n"
           "    vec4 col = color * qt_Opacity;              \n"
           "    col.w = 1;                                  \n"
           "    gl_FragColor = 2 * col * min(max(sqrt(pow(    "
           "    texCoord.x - .5, 2.0)                         "
           "    + pow(texCoord.y - .5, 2.0))                  "
           "    , .3), 1.0);                                \n"
           "}";
  }

  QList<QByteArray> RadialGradientShader::attributes() const { return QList<QByteArray>() << "aVertex" << "aTexCoord"; }
  void RadialGradientShader::updateState(const State* state, const State*) { program()->setUniformValue(id_color, state->color); }
  void RadialGradientShader::resolveUniforms() { id_color = program()->uniformLocation("color"); }
} // LPVL
