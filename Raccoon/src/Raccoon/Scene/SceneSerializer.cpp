#include <Raccoon/Scene/SceneSerializer.h>
#include <Raccoon/Scene/Entity.h>
#include <Raccoon/Scene/Components.h>
#include <Raccoon/Core/Assert.h>

#include <yaml-cpp/yaml.h>

#include <fstream>

namespace YAML
{
    template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Raccoon
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

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

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << 1;

		if (entity.HasComponent<NameComponent>())
		{
			out << YAML::Key << "NameComponent";
			out << YAML::BeginMap;

			auto& name = entity.GetComponent<NameComponent>().Name;
			out << YAML::Key << "Name" << YAML::Value << name;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<Transform2DComponent>())
		{
			out << YAML::Key << "Transform2DComponent";
			out << YAML::BeginMap;

			auto& tc = entity.GetComponent<Transform2DComponent>();
			out << YAML::Key << "Position" << YAML::Value << tc.Position;
			out << YAML::Key << "RotationAngle" << YAML::Value << tc.RotationAngle;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<ZComponent>())
		{
			out << YAML::Key << "ZComponent";
			out << YAML::BeginMap;

			auto& zComponent = entity.GetComponent<ZComponent>();
			out << YAML::Key << "ZIndex" << YAML::Value << zComponent.ZIndex;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<ColorRendererComponent>())
		{
			out << YAML::Key << "ColorRendererComponent";
			out << YAML::BeginMap;

			auto& color = entity.GetComponent<ColorRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << color.Color;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap;

			auto& sprite = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "TexturePath" << YAML::Value << sprite.Texture->GetPath().GetRelativePath();

			out << YAML::EndMap;
		}

		if (entity.HasComponent<EntityControllerComponent>())
		{
			out << YAML::Key << "EntityControllerComponent";
			out << YAML::BeginMap;

			auto& controller = entity.GetComponent<EntityControllerComponent>();
			out << YAML::Key << "MovementSpeed" << YAML::Value << controller.GetMovementSpeed();
			out << YAML::Key << "RotationSpeed" << YAML::Value << controller.GetRotationSpeed();
			out << YAML::Key << "EnableRotation" << YAML::Value << controller.IsRotationEnabled();

			out << YAML::EndMap;
		}

		if (entity.HasComponent<OrthographicCameraComponent>())
		{
			out << YAML::Key << "OrthographicCameraComponent";
			out << YAML::BeginMap;

			auto& camera = entity.GetComponent<OrthographicCameraComponent>();
			out << YAML::Key << "AspectRatio" << YAML::Value << camera.Camera.GetAspectRatio();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.Camera.GetOrthographicSize();;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << camera.FixedAspectRatio;;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

    SceneSerializer::SceneSerializer(const std::shared_ptr<Scene> &scene)
        : m_Scene{scene}
    {
    
    }
        
    void SceneSerializer::SerializeText(const FilePath &filepath)
    {
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (auto [entityID] : m_Scene->m_Registry.GetRegistry().storage<entt::entity>().each())
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath.GetRelativePath());
		fout << out.c_str();
    }

    void SceneSerializer::SerializeBinary(const FilePath &filepath)
    {

    }

    bool SceneSerializer::DeserializeText(const FilePath &filepath)
    {
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath.GetRelativePath());
		}
		catch (YAML::ParserException e)
		{
			RE_CORE_ERROR("Failed to load .re file '{0}'\n     {1}", filepath.GetGlobalPath(), e.what());
			return false;
		}

		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				std::string name;

				auto nameComponent = entity["NameComponent"];
				if (nameComponent)
					name = nameComponent["Name"].as<std::string>();

				Entity deserializedEntity = m_Scene->CreateEntity(name);

				auto transform2DComponent = entity["Transform2DComponent"];
				if (transform2DComponent)
				{
					auto& tc = deserializedEntity.GetComponent<Transform2DComponent>();
					tc.Position = transform2DComponent["Position"].as<glm::vec2>();
					tc.RotationAngle = transform2DComponent["RotationAngle"].as<float>();
					tc.Scale = transform2DComponent["Scale"].as<glm::vec2>();
				}

				auto zComponent = entity["ZComponent"];
				if (zComponent)
				{
					auto& z = deserializedEntity.AddComponent<ZComponent>();
					z.ZIndex = zComponent["ZIndex"].as<uint32_t>();
				}

				auto colorComponent = entity["ColorRendererComponent"];
				if (colorComponent)
				{
					auto& color = deserializedEntity.AddComponent<ColorRendererComponent>();
					color.Color = colorComponent["Color"].as<glm::vec4>();
				}

				auto spriteComponent = entity["SpriteRendererComponent"];
				if (spriteComponent)
				{
					auto& sprite = deserializedEntity.AddComponent<SpriteRendererComponent>();
					sprite.Texture = Texture2D::Create({spriteComponent["TexturePath"].as<std::string>()});
				}

				auto controllerComponent = entity["EntityControllerComponent"];
				if (controllerComponent)
				{
					auto& controller = deserializedEntity.AddComponent<EntityControllerComponent>();
					controller.SetMoveSpeed(controllerComponent["MovementSpeed"].as<float>());
					controller.SetRotationSpeed(controllerComponent["RotationSpeed"].as<float>());
					
					controller.SetEnableRotation(controllerComponent["EnableRotation"].as<bool>());
				}

				auto cameraController = entity["OrthographicCameraComponent"];
				if (cameraController)
				{
					auto& camera = deserializedEntity.AddComponent<OrthographicCameraComponent>();
					camera.Camera.SetAspectRatio(cameraController["AspectRatio"].as<float>());
					camera.Camera.SetOrthographicSize(cameraController["OrthographicSize"].as<float>());
					camera.FixedAspectRatio = cameraController["FixedAspectRatio"].as<bool>();
				}
			}
		}

		return true;
	}

    bool SceneSerializer::DeserializeBinary(const FilePath &filepath)
    {
        return false;
    }  
}