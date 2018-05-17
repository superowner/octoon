#include <octoon/collider_component.h>
#include <PxPhysicsAPI.h>
#include "..\..\include\octoon\collider_component.h"

namespace octoon
{
	OctoonImplementSubInterface(Collider, GameComponent, "Collider")

	Collider::Collider() noexcept
		: shared_material(std::make_shared<PhysicsMaterial>())
		, shape(nullptr)
	{
	}

	Collider::~Collider()
	{
	}

	void
	Collider::OnCollisionEnter(Collision collision)
	{
	}

	void
	Collider::OnCollisionExit(Collision collision)
	{
	}

	void
	Collider::OnCollisionStay(Collision collision)
	{
	}

	void
	Collider::setSharedMaterial(PhysicsMaterial material) except
	{
		shared_material = std::make_shared<PhysicsMaterial>(material);
		if (shape)
		{
			physx::PxMaterial * material_list = shared_material->getMaterial();
			shape->setMaterials(&material_list, 1);
		}
	}

	std::shared_ptr<PhysicsMaterial>
	Collider::getSharedMaterial() except
	{
		return shared_material;
	}
}