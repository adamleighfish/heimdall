#include "heimdall/interaction.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Interaction method definitions
 */

Interaction::Interaction(const Point3f& p, const Normal3f& n, const Vec3f& error, const Vec3f& wo, float time)
    : p(p), n(n), error(error), wo(wo), time(time) {}

bool Interaction::isSurfaceInteraction() const {
    return n != Normal3f();
}

/**
 * \brief SurfaceInteraction method definitions
 */

SurfaceInteraction::SurfaceInteraction(const Point3f& p, const Vec3f& error, const Point2f& uv, 
        const Vec3f& wo, const Vec3f& dpdu, const Vec3f& dpdv, const Normal3f& dndu, const Normal3f& dndv, 
        float time, const Shape* shape)
    : Interaction(p, Normal3f(Normalize(Cross(dpdu, dpdv))), error, wo, time), uv(uv), 
      dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv), shape(shape) {

    /// Initalize shading geometry
    shading.n = n;
    shading.dpdu = dpdu;
    shading.dpdv = dpdv;
    shading.dndu = dndu;
    shading.dndv = dndv;

    /// Adjust normal based on orientation and handedness    
    if (shape and (shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
        n *= -1;
        shading.n *= -1;
    }
}

void SurfaceInteraction::SetShadingGeometry(const Vec3f& dpdus, const Vec3f& dpdvs, const Normal3f& dndus, 
    const Normal3f& dndvs, bool orientationIsAuthoritative) {
    
    /// Compute shading.n for SurfaceInteraction
    shading.n = Normal3f(Normalize(Cross(dpdus, dpdvs)));
    if (shape and (shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
        shading.n = -shading.n;
    }
    if (orientationIsAuthoritative) {
        n = Faceforward(n, shading.n);
    } else {
        shading.n = Faceforward(shading.n, n);
    }

    /// Initialize shading partial derivative values
    shading.dpdu = dpdu;
    shading.dpdv = dpdv;
    shading.dndu = dndu;
    shading.dndv = dndv;
}

HEIMDALL_NAMESPACE_END