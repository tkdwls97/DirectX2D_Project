#include "pch.h"
#include "MenuUI.h"


MenuUI::MenuUI()
    : UI("Menu", "##Menu")
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        Render_Update();

        ImGui::EndMainMenuBar();
    }
}

void MenuUI::Render_Update()
{
    if (ImGui::BeginMenu("File"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}


        ImGui::EndMenu();
    }
}