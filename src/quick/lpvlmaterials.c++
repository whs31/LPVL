#include "lpvlmaterials.h"

int State::compare(const State *other) const
{
    if(color.rgba() == other->color.rgba())
        return 0;
    if(color.rgba() < other->color.rgba())
        return -1;
    return 1;
}

namespace LPVL
{
const char *RadialGradientShader::vertexShader() const
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

const char *RadialGradientShader::fragmentShader() const
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

QList<QByteArray> RadialGradientShader::attributes() const
{
    return QList<QByteArray>() << "aVertex" << "aTexCoord";
}

void RadialGradientShader::updateState(const State *state, const State *)
{
    program()->setUniformValue(id_color, state->color);
}

void RadialGradientShader::resolveUniforms()
{
    id_color = program()->uniformLocation("color");
}

} // LPVL
