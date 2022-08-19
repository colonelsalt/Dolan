#include "dnpch.h"
#include "SceneSerializer.h"

#include "Components.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& v)
		{
			Node node;
			node.push_back(v.x);
			node.push_back(v.y);
			node.push_back(v.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& v)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			v.x = node[0].as<float>();
			v.y = node[1].as<float>();
			v.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& v)
		{
			Node node;
			node.push_back(v.x);
			node.push_back(v.y);
			node.push_back(v.z);
			node.push_back(v.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& v)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			v.x = node[0].as<float>();
			v.y = node[1].as<float>();
			v.z = node[2].as<float>();
			v.w = node[3].as<float>();
			return true;
		}
	};

}

namespace Dolan {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << "739587394";

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			std::string& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			TransformComponent& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			CameraComponent& cameraComp = entity.GetComponent<CameraComponent>();
			SceneCamera& camera = cameraComp.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // SceneCamera

			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFov" << YAML::Value << camera.GetPerspVerticalFov();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthoNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthoFarClip();

			out << YAML::EndMap; // SceneCamera

			out << YAML::Key << "IsPrimary" << YAML::Value << cameraComp.IsPrimary;
			out << YAML::Key << "IsAspectRatioFixed" << YAML::Value << cameraComp.IsAspectRatioFixed;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			SpriteRendererComponent& spriteComp = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteComp.Color;

			out << YAML::EndMap; // SpriteRendererComponent
		}


		out << YAML::EndMap; // Entity
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](entt::entity entityId)
		{
			Entity entity = { entityId, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		DN_CORE_ASSERT(false, "Not implemented");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node data = YAML::LoadFile(filepath);
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		DN_CORE_TRACE("Deserialising scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				int64_t uuid = entity["Entity"].as<int64_t>();

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				DN_CORE_TRACE("Deserialising entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntity(name);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					// TransformComponent added automatically in CreateEntity() call above
					TransformComponent& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					CameraComponent& cc = deserializedEntity.AddComponent<CameraComponent>();

					auto& cameraProps = cameraComponent["Camera"];
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

					cc.Camera.SetPerspVerticalFov(cameraProps["PerspectiveFov"].as<float>());
					cc.Camera.SetPerspNearClip(cameraProps["PerspectiveNear"].as<float>());
					cc.Camera.SetPerspFarClip(cameraProps["PerspectiveFar"].as<float>());

					cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					cc.Camera.SetOrthoNearClip(cameraProps["OrthographicNear"].as<float>());
					cc.Camera.SetOrthoFarClip(cameraProps["OrthographicFar"].as<float>());

					cc.IsPrimary = cameraComponent["IsPrimary"].as<bool>();
					cc.IsAspectRatioFixed = cameraComponent["IsAspectRatioFixed"].as<bool>();
				}

				auto spriteComponent = entity["SpriteRendererComponent"];
				if (spriteComponent)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
					src.Color = spriteComponent["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		DN_CORE_ASSERT(false, "Not implemented");

		return false;
	}

}