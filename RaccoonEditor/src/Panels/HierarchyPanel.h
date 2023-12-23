#pragma once 
#include <memory>
#include <Raccoon/Scene/Scene.h>
#include <Raccoon/Scene/Entity.h>
#include <Raccoon/Scene/Components.h>
#include <imgui.h>

namespace Raccoon
{
    class HierarchyPanel
    {
    public:
        HierarchyPanel() = default;
        HierarchyPanel(const std::shared_ptr<Scene> &scene);
        
        void SetScene(const std::shared_ptr<Scene> &scene) { m_Scene = scene; m_SelectedEntity = {entt::null, m_Scene.get()}; m_HoveredEntity = {entt::null, m_Scene.get()}; }

        void OnImGuiRender();
        Entity GetSelectedEntity() const { return m_SelectedEntity; }
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        static void Draw2DVector(const std::string &label, glm::vec2 &values, const glm::vec2 &resetValues = {0.f, 0.f}, float columnWidth = 100.f);
        static void DrawSlider(const std::string &label, float &value, float resetValue = 0.f, float columnWidth = 100.);
        static void DrawRGBAPicker();

        template<typename T>
		void DisplayAddComponent(const std::string& name)
        {
            if (!m_SelectedEntity.HasComponent<T>())
            {
                if (ImGui::MenuItem(name.c_str()))
                {
                    m_SelectedEntity.AddComponent<T>();
                    ImGui::CloseCurrentPopup();
                }
            }
        }
    private:
        std::shared_ptr<Scene> m_Scene;
        Entity m_SelectedEntity;
        Entity m_HoveredEntity;
    };
}