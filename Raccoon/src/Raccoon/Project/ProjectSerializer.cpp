#include <Raccoon/Project/ProjectSerializer.h>
#include <Raccoon/Core/Assert.h>
#include <yaml-cpp/yaml.h>

#include <fstream>

namespace Raccoon
{
    ProjectSerializer::ProjectSerializer(const std::shared_ptr<Project> &project)
        : m_Project{project}
    {

    }

    bool ProjectSerializer::Serialize(const FilePath &path)
    {
        const auto& config = m_Project->GetConfig();

		YAML::Emitter out;
		{
			out << YAML::BeginMap; // Root
			out << YAML::Key << "Project" << YAML::Value;
			{
				out << YAML::BeginMap;// Project
				out << YAML::Key << "Name" << YAML::Value << config.Name;
				out << YAML::Key << "StartScene" << YAML::Value << config.StartScene.GetRelativePath();
				out << YAML::Key << "AssetDirectory" << YAML::Value << config.AssetDirectory.GetGlobalPath();
				out << YAML::EndMap; // Project
			}
			out << YAML::EndMap; // Root
		}

		std::string filePath;

		if (path.IsDirectory())
			filePath = path.GetGlobalPath() + "/" + config.Name + ".reproj";
		else
			filePath = path.GetGlobalPath();

		RE_CORE_INFO("{0}", filePath);
		std::ofstream fout(filePath);
		if (fout.is_open())
		{
			fout << out.c_str();
		}
		else
		{
			RE_CORE_ERROR("Couldn't open file {0}", filePath);
		}

		return true;
    }

    bool ProjectSerializer::Deserialize(const FilePath &path)
    {
        auto& config = m_Project->GetConfig();

		YAML::Node data;
		try
		{
			data = YAML::LoadFile(path.GetRelativePath());
		}
		catch (YAML::ParserException e)
		{
			RE_CORE_ERROR("Failed to load project file '{0}'\n     {1}", path.GetRelativePath(), e.what());
			return false;
		}

		auto projectNode = data["Project"];
		if (!projectNode)
			return false;

		config.Name = projectNode["Name"].as<std::string>();
		config.StartScene.SetPath(projectNode["StartScene"].as<std::string>());
		config.AssetDirectory.SetPath(projectNode["AssetDirectory"].as<std::string>());
		return true;
    }
}