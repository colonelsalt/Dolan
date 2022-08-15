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
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectedEntity;
	};

}