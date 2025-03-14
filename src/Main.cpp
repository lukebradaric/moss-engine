#include <SFML/Graphics.hpp>
#include "ComponentPool.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include "World.h"
#include "MovementSystem.h"
#include "CircleRenderSystem.h"
#include "SpriteRenderSystem.h"
#include "CollisionSystem.h"
#include <iostream>
#include <filesystem>

// Entity control window variables
static float posX = 0.0f;
static float posY = 0.0f;
static float velX = 0.0f;
static float velY = 0.0f;
static float radius = 25.0f;
static float mass = 10.0f;
static float bounce = 0.75f;
static float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

// Average fps tracking
int constexpr FPS_SAMPLE_COUNT = 100;
float fpsSamples[FPS_SAMPLE_COUNT] = { 0 };
int fpsIndex = 0;
float averageFps = 0;

// ECS world
World world;

sf::Color toSfColor(const float color[4])
{
	return sf::Color(
		color[0] * 255.0f,
		color[1] * 255.0f,
		color[2] * 255.0f,
		color[3] * 255.0f
	);
}

void calculateAverageFps(float deltaTime)
{
	fpsSamples[fpsIndex % FPS_SAMPLE_COUNT] = 1.0f / deltaTime;
	fpsIndex++;
	float avgFps = 0.0f;
	for (int i = 0; i < FPS_SAMPLE_COUNT; ++i)
	{
		avgFps += fpsSamples[i];
	}
	avgFps /= FPS_SAMPLE_COUNT;

	averageFps = avgFps;
}

void renderImGui(World& world)
{
	ImGui::Begin("ECS Control");

	ImGui::Text("FPS: %d", (int)averageFps);

	ImGui::SliderFloat("Pos X", &posX, 0.0f, 800.0f);
	ImGui::SliderFloat("Pos Y", &posY, 0.0f, 600.0f);
	ImGui::SliderFloat("Vel X", &velX, -1000.0f, 1000.0f);
	ImGui::SliderFloat("Vel Y", &velY, -1000.0f, 1000.0f);
	ImGui::SliderFloat("Radius", &radius, 5.0f, 50.0f);
	ImGui::SliderFloat("Mass", &mass, 0.0f, 100.0f);
	ImGui::SliderFloat("Bounce", &bounce, 0.0f, 1.0f);
	ImGui::ColorEdit4("Color", color);

	if (ImGui::Button("Spawn Entity"))
	{
		Entity newEntity = world.createEntity();
		PositionComponent* posComp = newEntity.addComponent(PositionComponent(posX, posY));
		newEntity.addComponent(VelocityComponent(velX, velY));
		newEntity.addComponent(CircleRenderComponent(radius, toSfColor(color)));
		newEntity.addComponent<CollisionComponent>(CollisionComponent(radius));
		newEntity.addComponent<RigidbodyComponent>(RigidbodyComponent(mass, bounce));

		// SpriteComponent testing
		//auto* spriteComp = newEntity.addComponent(SpriteRenderComponent("sprite.png"));
		//if (!spriteComp->texture.getSize().x)
		//{  // Check if texture loaded
		//	std::cerr << "Texture failed to load, check file path and format" << std::endl;
		//}
	}

	ImGui::End();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 450), "Moss Engine");
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);

	world.addSystem(std::make_unique<MovementSystem>());
	world.addSystem(std::make_unique<CircleRenderSystem>(window));
	world.addSystem(std::make_unique<CollisionSystem>(window));
	world.addSystem(std::make_unique<SpriteRenderSystem>(window));

	sf::Clock deltaClock;

	// Initialize spawn pos as center of screen
	posX = window.getView().getSize().x / 2;
	posY = window.getView().getSize().y / 2;

	while (window.isOpen())
	{
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Time deltaTime = deltaClock.restart();
		ImGui::SFML::Update(window, deltaTime);
		calculateAverageFps(deltaTime.asSeconds());

		renderImGui(world);

		window.clear();
		world.update(deltaTime.asSeconds());
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}
