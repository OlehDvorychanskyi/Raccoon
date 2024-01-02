#pragma once
#include <Raccoon/FileSystem/FilePath.h> 
#include <Raccoon/Core/Assert.h>
#include <memory>

namespace Raccoon
{
    struct ProjectConfig
    {
        std::string Name = "Untitled";

		FilePath StartScene;
		FilePath AssetDirectory;
    };

    class Project
    {
    public:
        static const FilePath& GetProjectDirectory()
		{
			RE_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->m_Directory;
		}

        ProjectConfig& GetConfig() { return m_Config; }
        static std::shared_ptr<Project> GetActive() { return s_ActiveProject; }

        static std::shared_ptr<Project> CopyActive();

        static std::shared_ptr<Project> New();
        static std::shared_ptr<Project> Load(const FilePath &path);
        static bool SaveActive(const FilePath &path);
        static bool Save(const std::shared_ptr<Project> project, const FilePath &path);
    private:
        ProjectConfig m_Config;
        FilePath m_Directory;

        inline static std::shared_ptr<Project> s_ActiveProject;
    };
}