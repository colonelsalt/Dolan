#include "dnpch.h"
#include "Scene.h"

#include "Components.h"
#include "Dolan/Renderer/Renderer2d.h"

namespace Dolan {

	Scene::Scene()
	{



		entt::entity entity = m_Registry.create();

	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2d::DrawQuad(transform, sprite.Color);
		}

	}

}