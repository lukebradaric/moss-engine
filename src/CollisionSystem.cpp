#include "CollisionSystem.h"
#include <vector>

void CollisionSystem::update(float deltaTime, World& world)
{
	const float windowWidth = static_cast<float>(_window.getSize().x);
	const float windowHeight = static_cast<float>(_window.getSize().y);

	const std::vector<Entity>& entities = world.getEntities();

	for (auto& entity : entities)
	{
		auto* position = entity.getComponent<PositionComponent>();
		auto* velocity = entity.getComponent<VelocityComponent>();
		auto* collision = entity.getComponent<CollisionComponent>();
		auto* rigidbody = entity.getComponent<RigidbodyComponent>();

		// If entity is missing one of required components, return
		if (!position || !velocity || !collision || !rigidbody)
		{
			continue;
		}

		velocity->dy += GRAVITY * deltaTime;

		// Handle collision with edges of sf::RenderWindow
		// Temporary collision for testing
		if (position->x - collision->radius < 0)
		{
			position->x = collision->radius;
			velocity->dx = -velocity->dx * rigidbody->bounce;
		}
		if (position->x + collision->radius > windowWidth)
		{
			position->x = windowWidth - collision->radius;
			velocity->dx = -velocity->dx * rigidbody->bounce;
		}
		if (position->y - collision->radius < 0)
		{
			position->y = collision->radius;
			velocity->dy = -velocity->dy * rigidbody->bounce;
		}
		if (position->y + collision->radius > windowHeight)
		{
			position->y = windowHeight - collision->radius;
			velocity->dy = -velocity->dy * rigidbody->bounce;
		}

	}

	// Handle collision between entities
	for (size_t i = 0; i < entities.size(); i++)
	{
		PositionComponent* pos1 = entities[i].getComponent<PositionComponent>();
		VelocityComponent* vel1 = entities[i].getComponent<VelocityComponent>();
		CollisionComponent* col1 = entities[i].getComponent<CollisionComponent>();
		RigidbodyComponent* rb1 = entities[i].getComponent<RigidbodyComponent>();

		for (size_t j = i + 1; j < entities.size(); j++)
		{
			PositionComponent* pos2 = entities[j].getComponent<PositionComponent>();
			VelocityComponent* vel2 = entities[j].getComponent<VelocityComponent>();
			CollisionComponent* col2 = entities[j].getComponent<CollisionComponent>();
			RigidbodyComponent* rb2 = entities[j].getComponent<RigidbodyComponent>();

			if (!pos2 || !vel2 || !col2 || !rb2)
			{
				continue;
			}

			float dx = pos2->x - pos1->x;
			float dy = pos2->y - pos1->y;
			float distance = std::sqrt(dx * dx + dy * dy);
			float minDistance = col1->radius + col2->radius;

			if (distance < minDistance && distance > 0.0001f)
			{
				float nx = dx / distance;
				float ny = dy / distance;
				float rvx = vel2->dx - vel1->dx;
				float rvy = vel2->dy - vel1->dy;
				float vNormal = rvx * nx + rvy * ny;

				// If Entities are already moving apart, continue
				if (vNormal > 0)
				{
					continue;
				}

				// Some Rigidbody math I found online frfr
				float e = (rb1->bounce + rb2->bounce) * 0.5f;
				float impulse = -(1.0f + e) * vNormal / (1.0f / rb1->mass + 1.0f / rb2->mass);
				float impulseX = impulse * nx;
				float impulseY = impulse * ny;

				vel1->dx -= impulseX / rb1->mass;
				vel1->dy -= impulseY / rb1->mass;
				vel2->dx += impulseX / rb2->mass;
				vel2->dy += impulseY / rb2->mass;

				// Overlap prevention
				float overlap = minDistance - distance;
				pos1->x -= overlap * nx * 0.5f;
				pos1->y -= overlap * ny * 0.5f;
				pos2->x += overlap * nx * 0.5f;
				pos2->y += overlap * nx * 0.5f;
			}
		}
	}
}