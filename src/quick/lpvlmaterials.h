#pragma once

#include <LPVL/Global>
#include <QtGui/QColor>
#include <QtQuick/QSGSimpleMaterial>

struct LPVL_EXPORT State
{
    QColor color;
    int compare(const State* other) const {
        if(color.rgba() == other->color.rgba())
            return 0;
        if(color.rgba() < other->color.rgba())
            return -1;
        return 1;
    }
};

namespace LPVL
{
    class LPVL_EXPORT RadialGradientShader : public QSGSimpleMaterialShader<State>
    {
        QSG_DECLARE_SIMPLE_COMPARABLE_SHADER(RadialGradientShader, State)

        public:
            const char* vertexShader() const override;
            const char* fragmentShader() const override;
            QList<QByteArray> attributes() const override;
            void updateState(const State* state, const State*) override;
            void resolveUniforms() override;

        private:
            int id_color;
    };
} // LPVL
