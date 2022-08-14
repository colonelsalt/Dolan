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
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& script)
			{
				if (!script.Instance)
				{
					script.Instance = script.InstantiateScript();
					script.Instance->m_Entity = Entity{ entity, this };
					script.Instance->OnCreate();
				}

				script.Instance->OnUpdate(ts);
			});
		}

		// Find main camera
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (entt::entity entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				
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
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2d::DrawQuad(transform, sprite.Color);
			}

			Renderer2d::EndScene();
		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-fixed cameras
		auto view = m_Registry.view<CameraComponent>();
		for (entt::entity entity : view)
		{
			CameraComponent& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.IsAspectRatioFixed)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

}