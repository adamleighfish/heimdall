#pragma once

#include "heimdall/common.h"
#include "heimdall/geometry.h"
#include "heimdall/transform.h"
#include "heimdall/interaction.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * Shape class declarations  
 */

class Shape {
  public:
    /// Shape public data
    const Transform* ObjectToWorld;
    const Transform* WorldToObject;
    const bool reverseOrientation;
    const bool transformSwapsHandedness;

    /// Shape public methods
    Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, bool reverseOrientation);

    virtual Bounds3f ObjectBounds() const = 0;
    virtual Bounds3f WorldBounds() const;
    
    virtual bool Intersect(const Ray& r, float* tHit, SurfaceInteraction* isect, bool testSurfaceAlpha = true) const = 0;
    virtual bool IntersectTest(const Ray& r, bool testSurfaceAlpha = true) const = 0;
    virtual float Area() const = 0;
};

HEIMDALL_NAMESPACE_END