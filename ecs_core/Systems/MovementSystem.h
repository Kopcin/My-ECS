#pragma once
#include "../Entities/Entity.h"
#include "../ComponentPool.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"

struct Velocity;
struct Transform;

class MovementSystem
{
public:
    static void Update(const float deltaTime, ComponentPool<Transform>& transforms, ComponentPool<Velocity>& velocities)
    {
        for (size_t i = 0; i < velocities.Size(); ++i)
        {
            const EntityId id = velocities.GetEntity(i);
            auto* transform = transforms.Get(id);
            auto& velocity = velocities.GetByIndex(i);

            if (transform)
            {
                transform->position += velocity.velocity * deltaTime;
            }
        }
    }
};
