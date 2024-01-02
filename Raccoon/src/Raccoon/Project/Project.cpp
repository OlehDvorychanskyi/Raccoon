#include <Raccoon/Project/Project.h>
#include <Raccoon/Project/ProjectSerializer.h>

namespace Raccoon
{
    std::shared_ptr<Project> Project::New()
    {
        s_ActiveProject = std::make_shared<Project>();
        return s_ActiveProject;
    }

	std::shared_ptr<Project> Project::CopyActive()
	{
		std::shared_ptr<Project> copy = std::make_shared<Project>();
		copy->m_Config = s_ActiveProject->m_Config;
		copy->m_Directory = s_ActiveProject->m_Directory;
		
		return copy;
	}

    std::shared_ptr<Project> Project::Load(const FilePath &path)
    {
        std::shared_ptr<Project> project = std::make_shared<Project>();

		ProjectSerializer serializer(project);
		if (serializer.Deserialize(path))
		{
			project->m_Directory.SetPath(path.GetParentPath());
			s_ActiveProject = project;
			return s_ActiveProject;
		}

		return nullptr;
    }

    bool Project::SaveActive(const FilePath &path)
    {
		return Project::Save(s_ActiveProject, path);
    }

	bool Project::Save(const std::shared_ptr<Project> project, const FilePath &path)
	{
		ProjectSerializer serializer(project);
		if (serializer.Serialize(path))
		{
			project->m_Directory.SetPath(path.GetParentPath());
			return true;
		}

		return false;
	}
}