#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <filesystem>
#include "core/ComponentPool.h"
#include "core/World.h"
#include "systems/MovementSystem.h"
#include "systems/SpriteRenderSystem.h"
#include "systems/CollisionSystem.h"
#include "components/CollisionComponent.h"
#include "components/RigidbodyComponent.h"
#include "utils/TextureManager.h"
#include "utils/Camera.h"
#include "utils/Logger.h"

static float worldWidth = 25.0f;
static float worldHeight = 14.0625f;

static float camX = 0.0f;
static float camY = 0.0f;
static float camZoom = 7.0f;

// Entity control window variables
static float posX = 0;
static float posY = 0;
static float velX = 0.0f;
static float velY = 0.0f;
static float radius = 1.0f;
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
Camera camera(7.0f, 16.0f);
TextureManager textureManager;
Logger logger;

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

	ImGui::SliderFloat("Pos X", &posX, -worldWidth, worldWidth);
	ImGui::SliderFloat("Pos Y", &posY, -worldHeight, worldHeight);
	ImGui::SliderFloat("Vel X", &velX, -100.0f, 100.0f);
	ImGui::SliderFloat("Vel Y", &velY, -100.0f, 100.0f);
	ImGui::SliderFloat("Radius", &radius, 0.0f, 10.0f);
	ImGui::SliderFloat("Mass", &mass, 0.0f, 100.0f);
	ImGui::SliderFloat("Bounce", &bounce, 0.0f, 1.0f);
	ImGui::ColorEdit4("Color", color);

	ImGui::Separator();

	ImGui::Text("FPS: %d", (int)averageFps);
	ImGui::Text("Entity Count: %d", world.getEntities().size());

	ImGui::Separator();

	if (ImGui::Button("Spawn Goblin"))
	{
		Entity newEntity = world.createEntity();

		newEntity.addComponent(PositionComponent(posX, posY));
		newEntity.addComponent(VelocityComponent(velX, velY));
		newEntity.addComponent<CollisionComponent>(CollisionComponent(radius));
		newEntity.addComponent<RigidbodyComponent>(RigidbodyComponent(mass, bounce));
		newEntity.addComponent(SpriteRenderComponent(textureManager.getTexture("goblin")));

		logger.logInfo("Spawning Goblin with Id: " + std::to_string(newEntity.getId()));
	}

	ImGui::End();

	ImGui::Begin("Camera Control");

	ImGui::SliderFloat("Cam X", &camX, -worldWidth / 2, worldWidth / 2);
	ImGui::SliderFloat("Cam Y", &camY, -worldHeight / 2, worldHeight / 2);
	ImGui::SliderFloat("Zoom", &camZoom, 1.0f, 14.0f);

	camera.position.x = camX;
	camera.position.y = camY;
	camera.orthoSize = camZoom;

	ImGui::End();
}

int main()
{
	logger.logInfo("Application start.");

	sf::RenderWindow window(sf::VideoMode(800, 450), "Moss Engine");
	window.setFramerateLimit(144);

	ImGui::SFML::Init(window);

	textureManager.loadTexture("goblin", "goblin.png");

	world.addSystem(std::make_unique<MovementSystem>());
	world.addSystem(std::make_unique<CollisionSystem>(sf::Vector2f(worldWidth, worldHeight)));
	world.addSystem(std::make_unique<SpriteRenderSystem>(window, camera));

	sf::Clock deltaClock;

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
