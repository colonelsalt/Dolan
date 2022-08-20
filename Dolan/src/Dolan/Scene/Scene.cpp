#include "dnpch.h"
#include "Scene.h"

#include "Components.h"
#include "Dolan/Renderer/Renderer2d.h"

#include "Entity.h"

namespace Dolan {

	Scene::Scene()
	{
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

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2d::BeginScene(camera);

		// All entities that have a Transform and SpriteRenderer component
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (entt::entity entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2d::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2d::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
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
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (entt::entity entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				
				if (camera.IsPrimary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		// Render
		if (mainCamera)
		{
			Renderer2d::BeginScene(*mainCamera, cameraTransform);

			// All entities that have a Transform and SpriteRenderer component
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (entt::entity entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2d::DrawQuad(transform.GetTransform(), sprite.Color);
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

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (entt::entity entity : view)
		{
			const CameraComponent& camera = view.get<CameraComponent>(entity);
			if (camera.IsPrimary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, TransformComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, TagComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded(Entity entity, SpriteRendererComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded(Entity entity, NativeScriptComponent& component)
	{

	}
}