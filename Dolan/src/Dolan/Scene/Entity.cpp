#include "dnpch.h"
#include "Entity.h"

namespace Dolan {



	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene) {}



}