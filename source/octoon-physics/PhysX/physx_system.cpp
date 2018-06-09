#include <octoon/physics/Physx/physics_system.h>

#include <PxPhysicsAPI.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysxSystem, PhysicsSystem, "PhysxSystem")
        PhysxSystem::PhysxSystem() except
            :defaultErrorCallback(std::make_unique<physx::PxDefaultErrorCallback>()),
            defaultAllocatorCallback(std::make_unique<physx::PxDefaultAllocator>()),
            foundation(nullptr), pvd(nullptr),
            physics(nullptr), cooking(nullptr),
            dispatcher(nullptr)
        {
            foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, *defaultAllocatorCallback, *defaultErrorCallback);
            if (!foundation)
                throw runtime::runtime_error::create("PxCreateFoundation failed!");

            bool recordMemoryAllocations = true;

            pvd = physx::PxCreatePvd(*foundation);
            physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
            pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

            physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation,
                physx::PxTolerancesScale(), recordMemoryAllocations, pvd);
            if (!physics)
                throw runtime::runtime_error::create("PxCreatePhysics failed!");

            physx::PxTolerancesScale scale;
            scale.length = 1;
            scale.speed = 1;

            cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, physx::PxCookingParams(scale));
            if (!cooking)
                throw runtime::runtime_error::create("PxCreateCooking failed!");

            if (!PxInitExtensions(*physics, pvd))
                throw runtime::runtime_error::create("PxInitExtensions failed!");
        }
            
        PhysicsScenePtr createScene() except
        {
            physx::PxSceneDesc sceneDesc(physics->getTolerancesScale());
            Physics::setGravity(math::Vector3(0.f, -9.8f, 0.f));
            math::Vector3 g = Physics::getGravity();
            sceneDesc.gravity = physx::PxVec3(g.x, g.y, g.z);
            dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
            sceneDesc.cpuDispatcher = dispatcher;
            sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
            physicsScene = physics->createScene(sceneDesc);

            auto retval = std::make_shared<PhysxScene>();
            retval.setPhysicsScene(physicsScene);
            return retval;
        }

        virtual PhysicsRigidbodyPtr createRigidBody() except
        {
            if (body)return;
            auto physicsFeature = GameApp::instance()->getFeature<PhysicsFeature>();

            auto transform = this->getComponent<TransformComponent>();

            if (!transform) return;
            auto& translate = transform->getTranslate();
            auto& rotation = transform->getQuaternion();

            physx::PxTransform pose;
            pose.p = physx::PxVec3(translate.x, translate.y, translate.z);
            pose.q = physx::PxQuat(rotation.x, rotation.y, rotation.z, rotation.w);

            if (isKinematic)
            {
                body = physicsFeature->getSDK()->createRigidStatic(pose);
                if (!body)
                    throw  runtime::runtime_error::create("create body failed!");
            }
            else
            {
                body = physicsFeature->getSDK()->createRigidDynamic(pose);
                if (!body)
                    throw  runtime::runtime_error::create("create body failed!");

                physx::PxRigidBody* rigid_body = static_cast<physx::PxRigidBody*>(body);
                physx::PxRigidBodyExt::updateMassAndInertia(*rigid_body, mass);
            }

            physicsFeature->getScene()->addActor(*body);
        }

        PhysxSystem::~PhysxSystem() noexcept
        {

        }
    }
}