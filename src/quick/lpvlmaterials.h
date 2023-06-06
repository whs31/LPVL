#pragma once

#include <LPVL/Global>
#include <QtGui/QColor>
#include <QtQuick/QSGSimpleMaterial>

struct LPVL_EXPORT State
{
    QColor color;
    int compare(const State* other) const;
};

namespace LPVL
{
    class LPVL_EXPORT RadialGradientShader : public QSGSimpleMaterialShader<State>
    {
        public:
            static QSGSimpleMaterialComparableMaterial<State>* createMaterial();

            const char* vertexShader() const override;
            const char* fragmentShader() const override;
            QList<QByteArray> attributes() const override;
            void updateState(const State* state, const State*) override;
            void resolveUniforms() override;

        private:
            static QSGMaterialShader* createShader();

        private:
            int id_color;
    };
} // LPVL
