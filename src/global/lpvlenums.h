#pragma once

#include "lpvlglobal.h"

namespace LPVL
{
    enum class Intersection : unsigned char
    {
        In,
        Out,
        Inside,
        None
    };

    enum class GeometryType : unsigned char
    {
        Flat,
        Colored,
        UV
    };
} // LPVL
