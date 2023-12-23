#pragma once 
#include <Raccoon/Project/Project.h>
#include <Raccoon/FileSystem/FilePath.h>
#include <memory>

namespace Raccoon
{
    class ProjectSerializer
    {
    public:
        ProjectSerializer(const std::shared_ptr<Project> &project);

        bool Serialize(const FilePath &path);
        bool Deserialize(const FilePath &path);
    private:
        std::shared_ptr<Project> m_Project;
    };
}