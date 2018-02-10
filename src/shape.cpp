#include "heimdall/shape.h"

HEIMDALL_NAMESPACE_BEGIN

Shape::Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, bool reverseOrientation)
    : ObjectToWorld(ObjectToWorld), WorldToObject(WorldToObject), 
      reverseOrientation(reverseOrientation), transformSwapsHandedness(ObjectToWorld->SwapsHandedness()) {}

Bounds3f Shape::WorldBounds() const {
    return (*ObjectToWorld)(ObjectBounds());
}

HEIMDALL_NAMESPACE_END