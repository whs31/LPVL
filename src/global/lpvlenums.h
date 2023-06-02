#pragma once

#include "lpvlglobal.h"

namespace LPVL
{
    enum class LPVL_EXPORT Intersection : unsigned char
    {
        In,
        Out,
        Inside,
        NonIntersecting
    };
} // LPVL
