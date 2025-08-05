#include <iostream>

#include "ComponentPool.h"
#include "Components/Transform.h"

void tempCode();

int main(int argc, char* argv[])
{
    std::cout << "Hello ECS";

    tempCode();
    
    return 0;
}

void tempCode()
{
    ComponentPool<Transform> transformPool;

    // Add component
    EntityId player = 1;
    transformPool.Add(player, Transform{ glm::vec3(0), glm::vec3(0), glm::vec3(1) });

    // Get component
    if (Transform* t = transformPool.Get(player)) {
        t->position += glm::vec3(1, 0, 0);
    }

    // Iterate through component
    for (size_t i = 0; i < transformPool.Size(); ++i) {
        EntityId id = transformPool.GetEntity(i);
        Transform& t = transformPool.GetByIndex(i);

        // e.g. move everyone
        t.position += glm::vec3(0, 0, -1);
    }

    // Delete component
    transformPool.Remove(player);
}