#include "lpvlgeomath.h"
#include "LPVL/Math"
#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>
#include <cmath>

constexpr const double MAP_SCALE_RATIO = 156'543.03392;

double LPVL::Private::mqi_zoom_level(double latitude, float meters_per_pixel) noexcept
{
    if(not meters_per_pixel)
        return log(2, MAP_SCALE_RATIO * cos(latitude * M_PI / 180));
    return log(2, MAP_SCALE_RATIO * cos(latitude * M_PI / 180) / meters_per_pixel);
}

QPointF LPVL::Private::geo2webmercator(const QGeoCoordinate& geo, uint8_t zoom) noexcept
{
    return QPointF((1.0 - asinh(tan(geo.latitude() * M_PI / 180.0)) / M_PI) / 2.0 * (1 << zoom),
                   (geo.longitude() + 180.0) / 360.0 * (1 << zoom));
}
