#pragma once

#include "Dolan/Core/Base.h"
#include "Dolan/Core/Log.h"
#include "Dolan/Scene/Scene.h"
#include "Dolan/Scene/Entity.h"

namespace Dolan {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectedEntity; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectedEntity;
	};

}