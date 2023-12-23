#pragma once 
#include <Raccoon/Scene/Scene.h>
#include <Raccoon/FileSystem/FilePath.h>
#include <memory>

namespace Raccoon
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const std::shared_ptr<Scene> &scene);
        
        void SerializeText(const FilePath &filepath);
        void SerializeBinary(const FilePath &filepath);

        bool DeserializeText(const FilePath &filepath);
        bool DeserializeBinary(const FilePath &filepath);
    private:
        std::shared_ptr<Scene> m_Scene;
    };
}