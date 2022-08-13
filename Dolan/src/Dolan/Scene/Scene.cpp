#include "dnpch.h"
#include "Scene.h"

#include "Components.h"
#include "Dolan/Renderer/Renderer2d.h"

#include "Entity.h"

namespace Dolan {

	Scene::Scene()
	{



		entt::entity entity = m_Registry.create();

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		TagComponent& tag = entity.AddComponent<TagComponent>();
		
		if (name.empty())
			tag.Tag = "Entity";
		else
			tag.Tag = name;

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Find main camera
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto group = m_Registry.view<TransformComponent, CameraComponent>();
			for (entt::entity entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);
				
				if (camera.IsPrimary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2d::BeginScene(*mainCamera, *cameraTransform);

			// All entities that have a Transform and SpriteRenderer component
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (entt::entity entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2d::DrawQuad(transform, sprite.Color);
			}

			Renderer2d::EndScene();
		}

	}

}