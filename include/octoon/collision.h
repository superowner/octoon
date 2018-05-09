#ifndef OCTOON_COLLISION_H_
#define OCTOON_COLLISION_H_

#include <octoon/contact_point.h>
#include <octoon/rigidbody_component.h>
#include <octoon/transform_component.h>

namespace octoon
{
    class Collision
    {
    public:
        std::weak_ptr<Collider> collider; // The Collider we hit (Read Only).
        ContactPoint contacts; // The contact points generated by the physics engine.
        std::weak_ptr<GameObject> gameObject; //The GameObject whose collider you are colliding with. (Read Only).
        math::float3 impulse; // The total impulse applied to this contact pair to resolve the collision.
        math::float3 relativeVelocity; // The relative linear velocity of the two colliding objects (Read Only).
        std::weak_ptr<Rigidbody> rigidbody; // The Rigidbody we hit (Read Only). This is null if the object we hit is a collider with no rigidbody attached.
        std::weak_ptr<TransformComponent> transform; // The Transform of the object we hit (Read Only).
    };
}

#endif // OCTOON_COLLISION_H_