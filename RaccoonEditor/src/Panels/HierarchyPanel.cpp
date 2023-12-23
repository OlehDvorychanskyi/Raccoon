#include <Panels/HierarchyPanel.h>

#include <entt.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Raccoon/Core/Assert.h>

#include <type_traits>
#include <Raccoon/ImGui/Fonts.h>

namespace Raccoon
{
    HierarchyPanel::HierarchyPanel(const std::shared_ptr<Scene> &scene)
    {
        SetScene(scene);
    }

    void HierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene");
        if (m_Scene)
        {
            if (ImGui::MenuItem("+"))
                m_Scene->CreateEntity("Empty Entity");
                
            for (auto [entity] : m_Scene->m_Registry.GetRegistry().storage<entt::entity>().each())
            {
                DrawEntityNode({ entity , m_Scene.get() });
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectedEntity = {};

            // Right-click on blank space
			// if (ImGui::BeginPopupContextWindow(0, 1))
			// {

			// 	ImGui::EndPopup();
			// }
        }
        ImGui::End();

        ImGui::Begin("Inspector");
        if (m_SelectedEntity)
        {
            DrawComponents(m_SelectedEntity);
        }
        ImGui::End();
    }

    void HierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto &name = entity.GetComponent<NameComponent>().Name;
		
		ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedEntity = entity;
		}

        if (ImGui::IsItemHovered())
        {
            m_HoveredEntity = entity;
        }

        bool deleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                deleted = true;
            ImGui::EndPopup();
        }

        // Drag and drop source
        if (ImGui::BeginDragDropSource()) 
        {
            // Set payload data (you can use your own payload type)
            ImGui::SetDragDropPayload("ENTITY", &entity, sizeof(Entity));

            // Display the entity text
            ImGui::Text("Drag %s", name.c_str());

            ImGui::EndDragDropSource();
        }

        // Drag and drop target
        if (ImGui::BeginDragDropTarget()) 
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY")) 
            {
                Entity draggedEntity = *static_cast<Entity*>(payload->Data);
                std::size_t newPosition = m_Scene->GetEntityOrder(entity.m_ID);
                RE_CORE_INFO("Dragged Entity Name: {0}", draggedEntity.GetComponent<NameComponent>().Name);
                RE_CORE_INFO("Hovered Entity Name: {0}", entity.GetComponent<NameComponent>().Name);
                RE_CORE_INFO("New Position: {0}", newPosition);
                RE_CORE_INFO("Old Position: {0}", m_Scene->GetEntityOrder(draggedEntity.m_ID));
                m_Scene->ChangeEntityPosition(draggedEntity.m_ID, newPosition);
                

                // m_Scene->SwapEntities(draggedEntity.m_ID, m_HoveredEntity.m_ID);
            }

            ImGui::EndDragDropTarget();
        }

		if (opened)
		{
			ImGui::TreePop();
		}

        if (deleted)
        {
            m_Scene->DestroyEntity(entity);
            if (m_SelectedEntity == entity)
                m_SelectedEntity = {};
        }
    }

    template<typename T, typename Func>
    static void DrawComponent(const std::string &name, Entity entity, Func drawFunction)
    {
        if (entity.HasComponent<T>())
        {
            ImGuiIO& io = ImGui::GetIO();
            auto& component = entity.GetComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
            static ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = io.Fonts->Fonts[0]->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;
            ImGui::Separator();
            ImGui::PushFont(Fonts::GetFont("Bold"));
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopFont();
            ImGui::PopStyleVar();

            if (std::is_same<T, Transform2DComponent>() == false)
            {
                ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
                if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
                {
                    ImGui::OpenPopup("Component Settings");
                }

                bool deleted = false;
                if (ImGui::BeginPopup("Component Settings"))
                {
                    if (ImGui::MenuItem("Remove component"))
                        deleted = true;

                    ImGui::EndPopup();
                }

                if (deleted)
                    entity.RemoveComponent<T>();
            }

            if (open)
            {
                drawFunction(component);
                ImGui::TreePop();
            }
        }
    }

    void HierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<NameComponent>())
		{
			auto& name = entity.GetComponent<NameComponent>().Name;

			static char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy_s(buffer, sizeof(buffer), name.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
			{
				name = std::string(buffer);
			}
		}

        ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			DisplayAddComponent<OrthographicCameraComponent>("Camera2D");
            DisplayAddComponent<NativeScriptComponent>("Native Script");
			DisplayAddComponent<SpriteRendererComponent>("Sprite Renderer");
			DisplayAddComponent<ColorRendererComponent>("Color Renderer");
            DisplayAddComponent<EntityControllerComponent>("Entity Controller");

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

        DrawComponent<Transform2DComponent>("Transform", entity, [] (auto &component)
        {
            Draw2DVector("Position", component.Position);
            DrawSlider("Rotation", component.RotationAngle);
            Draw2DVector("Scale", component.Scale, {1.f, 1.f});
        });

        DrawComponent<OrthographicCameraComponent>("Camera2D", entity, [this, &entity] (auto &component)
        {
            bool primary = false;
            if (m_Scene->HasPrimaryCamera())
                primary = m_Scene->IsPrimaryCamera(&component.Camera);
    
            if (ImGui::Checkbox("Primary Camera", &primary))
            {
                if (primary == true)
                    m_Scene->SetPrimaryCamera(&component.Camera, &entity.GetComponent<Transform2DComponent>().GetTransform());
                else
                    m_Scene->SetPrimaryCamera(nullptr, nullptr);
            }

            ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);

            float OrthographicSize = component.Camera.GetOrthographicSize();
            if (ImGui::InputFloat("OrthographicSize", &OrthographicSize))
            {
                component.Camera.SetOrthographicSize(OrthographicSize);
            }

            float AspectRatio = component.Camera.GetAspectRatio();
            if (ImGui::InputFloat("AspectRatio", &AspectRatio))
            {
                component.Camera.SetAspectRatio(AspectRatio);
            }
        });

        DrawComponent<ColorRendererComponent>("Color", entity, [] (auto &component) // TODO: think about name 
        {
            ImGui::Columns(2, (const char*)0, false);
            ImGui::SetColumnWidth(0, 50.f);
            ImGui::Text("Color");
            ImGui::NextColumn();

            ImGui::PushItemWidth(ImGui::CalcItemWidth());
            ImGui::SameLine();
            ImGui::ColorEdit4("##", glm::value_ptr(component.Color));
            ImGui::PopItemWidth();

            ImGui::Columns(1);
        });

        DrawComponent<SpriteRendererComponent>("Sprite", entity, [] (auto &component)
        {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

            static char pathBuffer[256];
			// memset(pathBuffer, 0, sizeof(pathBuffer));

            ImGui::InputText("Path", pathBuffer, sizeof(pathBuffer));
			
			if (ImGui::Button("Texture", ImVec2(100.0f, 0.0f)))
            {
                std::string path = pathBuffer;
                std::shared_ptr<Texture2D> texture = Texture2D::Create(path);
                if (texture->IsLoaded())
                    component.Texture = texture;
                else
                    RE_WARN("Could not load texture {0}", path);
            }
			// if (ImGui::BeginDragDropTarget())
			// {4
            //     std::filesystem::path relativePath;
            //     const wchar_t* itemPath = relativePath.c_str();
            //     ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));

			// 	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			// 	{
			// 		const wchar_t* path = (const wchar_t*)payload->Data;
			// 		std::filesystem::path texturePath(path);
			// 	    std::shared_ptr<Texture2D> texture = Texture2D::Create(texturePath.string());
			// 		if (texture->IsLoaded())
			// 			component.Texture = texture;
			// 		else
			// 			RE_WARN("Could not load texture {0}", texturePath.filename().string());
			// 	}
			// 	ImGui::EndDragDropTarget();
			// }
        });

        DrawComponent<ZComponent>("ZIndex", entity, [] (auto &component)
        {
            int value = static_cast<int>(component.ZIndex);

            if (ImGui::InputInt("ZIndex", &value))
            {
                if (value < 0)
                    value = 0;
                component.ZIndex = static_cast<uint32_t>(value);
            }
        });


        // if (entity.HasComponent<Transform2DComponent>())
        // {
        //     if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        //     {
        //         auto &transform = entity.GetComponent<Transform2DComponent>();
        //         Draw2DVector("Position", transform.Position);
        //         DrawSlider("Rotation", transform.RotationAngle);
        //         Draw2DVector("Scale", transform.Scale, {1.f, 1.f});
        //         ImGui::TreePop();
        //     }
        // }

        // if (entity.HasComponent<OrthographicCameraComponent>())
        // {
        //     if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_DefaultOpen))
        //     {
        //         auto &camera = entity.GetComponent<OrthographicCameraComponent>();

        //         ImGui::Checkbox("Active Camera", &camera.ActiveCamera);
        //         ImGui::Checkbox("Fixed Aspect Ratio", &camera.FixedAspectRatio);
            
        //         ImGui::TreePop();
        //     }
        // }

        // if (entity.HasComponent<ColorRendererComponent>())
        // {
        //     if (ImGui::TreeNodeEx("Sprite", ImGuiTreeNodeFlags_DefaultOpen))
        //     {
        //         auto &color = entity.GetComponent<ColorRendererComponent>();

        //         ImGui::Columns(2, (const char*)0, false);
		//         ImGui::SetColumnWidth(0, 50.f);
        //         ImGui::Text("Color");
        //         ImGui::NextColumn();

        //         ImGui::PushItemWidth(ImGui::CalcItemWidth());
        //         ImGui::SameLine();
        //         ImGui::ColorEdit4("##", glm::value_ptr(color.Color));
        //         ImGui::PopItemWidth();

        //         ImGui::Columns(1);
        //         ImGui::TreePop();
        //     }
        // }
    }

    void HierarchyPanel::Draw2DVector(const std::string &label, glm::vec2 &values, const glm::vec2 &resetValues, float columnWidth)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushID(label.c_str());

        ImGui::Columns(2, (const char*)0, false);
		ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        // ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

        // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = io.Fonts->Fonts[0]->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushItemWidth(ImGui::CalcItemWidth());

        // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.9f, 0.1f, 0.1f, 1.0f });
		// ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 1.0f, 0.3f, 0.3f, 1.0f });
		// ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.9f, 0.1f, 0.1f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.9f, 0.1f, 0.1f, 1.0f });
        ImGui::PushFont(Fonts::GetFont("Bold"));
        if (ImGui::Button("X", buttonSize))
            values.x = resetValues.x;
        // ImGui::PopStyleColor(3);
        ImGui::PopFont();
        ImGui::PopStyleColor(1);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();

        // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.7f, 0.1f, 1.0f });
		// ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.9f, 0.3f, 1.0f });
		// ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.7f, 0.1f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.1f, 0.7f, 0.1f, 1.0f });
        ImGui::PushItemWidth(ImGui::CalcItemWidth());
        ImGui::PushFont(Fonts::GetFont("Bold"));
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValues.y;
        // ImGui::PopStyleColor(3);
        ImGui::PopFont();
        ImGui::PopStyleColor(1);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    void HierarchyPanel::DrawSlider(const std::string &label, float &value, float resetValue, float columnWidth)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushID(label.c_str());

        ImGui::Columns(2, (const char*)0, false);
		ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        float lineHeight = io.Fonts->Fonts[0]->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
        static float radians = 0.f;

        ImGui::PushItemWidth(ImGui::CalcItemWidth());

        if (ImGui::Button(u8"\x88", buttonSize))
        {
            value = resetValue;
            radians = resetValue;
        }

        ImGui::SameLine();
        // ImGui::DragFloat("##", &value, 1.f, -360.f, 360.f);
        
        if (ImGui::SliderAngle("##", &radians, -360.f, 360.f, "%.0f°"))
        {
            value = glm::degrees(radians);
        }
        ImGui::PopItemWidth();

        ImGui::Columns(1);

        ImGui::PopID();
    }
}