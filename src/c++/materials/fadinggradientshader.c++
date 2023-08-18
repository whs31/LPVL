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

#include "fadinggradientshader.h"

namespace LPVL
{
  QSGMaterialShader* FadingGradientShader::createShader() { return new FadingGradientShader; }
  QSGSimpleMaterialComparableMaterial<State>* FadingGradientShader::createMaterial() {
    return new QSGSimpleMaterialComparableMaterial<State>(FadingGradientShader::createShader);
  }

  const char* FadingGradientShader::vertexShader() const
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

  const char* FadingGradientShader::fragmentShader() const
  {
    return "uniform lowp float qt_Opacity;                  \n"
           "uniform lowp vec4 color;                        \n"
           "varying highp vec2 texCoord;                    \n"
           "void main () {                                  \n"
           "    gl_FragColor = qt_Opacity * min(1.3 -         "
           "    texCoord.y, 1.0) * color;                   \n"
           "}";
  }

  QList<QByteArray> FadingGradientShader::attributes() const { return QList<QByteArray>() << "aVertex" << "aTexCoord"; }
  void FadingGradientShader::updateState(const State* state, const State*) { program()->setUniformValue(id_color, state->color); }
  void FadingGradientShader::resolveUniforms() { id_color = program()->uniformLocation("color"); }
} // LPVL