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
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2d::DrawQuad(transform, sprite.Color);
		}

	}

}