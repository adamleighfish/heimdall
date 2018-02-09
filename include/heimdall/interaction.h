#pragma once

#include "heimdall/common.h"
#include "heimdall/geometry.h"
#include "heimdall/shape.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Interaction class declarations
 */

class Interaction {
  public:
    /// Interaction public data
    Point3f p;
    Normal3f n;
    Vec3f error;
    Vec3f wo;
    float time;   

    /// Interaction public methods
    Interaction(const Point3f& p, const Normal3f& n, const Vec3f& error, const Vec3f& wo, float time);
    
    bool isSurfaceInteraction() const;
};

/**
 * \brief SurfaceInteraction class declarations
 */

class SurfaceInteraction: public Interaction {
  public:
    /// SurfaceInteraction public data
    Point2f  uv;
    Vec3f    dpdu, dpdv;
    Normal3f dndu, dndv;
    const Shape* shape = nullptr;

    /// Struct for shading geometry terms
    struct {
        Normal3f n;
        Vec3f    dpdu, dpdv;
        Normal3f dndu, dndv;
    } shading;

    /// SurfaceInteraction public methods
    SurfaceInteraction(const Point3f& p, const Vec3f& error, const Point2f& uv, const Vec3f& wo,
        const Vec3f& dpdu, const Vec3f& dpdv, const Normal3f& dndu, const Normal3f& dndv,
        float time, const Shape* shape);

    void SetShadingGeometry(const Vec3f& dpdus, const Vec3f& dpdvs, const Normal3f& dndus, const Normal3f& dndvs,
        bool orientationIsAuthoritative);
};

HEIMDALL_NAMESPACE_END