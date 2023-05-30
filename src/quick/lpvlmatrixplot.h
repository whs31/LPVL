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

#include "LPVL/Global"
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace LPVL
{
    class LPVL_EXPORT MatrixPlot : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(float tintRed READ tintRed WRITE setTintRed NOTIFY tintRedChanged)
        Q_PROPERTY(float tintGreen READ tintGreen WRITE setTintGreen NOTIFY tintGreenChanged)
        Q_PROPERTY(float tintBlue READ tintBlue WRITE setTintBlue NOTIFY tintBlueChanged)
        Q_PROPERTY(float brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
        Q_PROPERTY(bool grayscale READ grayscale WRITE setGrayscale NOTIFY grayscaleChanged)

        public:
            MatrixPlot(QQuickItem* parent = nullptr);
            virtual ~MatrixPlot() = default;

            Q_INVOKABLE void set(const vector<float>& array2d, int rows, int columns);
            Q_INVOKABLE void set(const vector<int> array2d, int rows, int columns);
            Q_INVOKABLE void set(const vector<uint8_t> array2d, int rows, int columns);
            Q_INVOKABLE void clean();

            float tintRed() const; void setTintRed(float);
            float tintGreen() const; void setTintGreen(float);
            float tintBlue() const; void setTintBlue(float);
            float brightness() const; void setBrightness(float);
            bool grayscale() const; void setGrayscale(bool);

            signals:
                void tintRedChanged();
                void tintGreenChanged();
                void tintBlueChanged();
                void brightnessChanged();
                void grayscaleChanged();

        protected:
            QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

        private:
            vector<vector<float>> data;
            float m_tintRed;
            float m_tintGreen;
            float m_tintBlue;
            float m_brightness;
            float current_max;
            bool m_grayscale;
    };
} // LPVL

