#pragma once
#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>
#include "../helper.hpp"

using namespace geode::prelude;

namespace niorin::theme::color {

    struct Palette {
        std::unordered_map<ImGuiCol, ImVec4> colors;
    };

    inline const Palette Default = {
        {
            { ImGuiCol_TitleBg,          helper::rgba(69, 69, 138, 255) },
            { ImGuiCol_TitleBgActive,    helper::rgba(82, 82, 161, 255) },
            { ImGuiCol_TitleBgCollapsed, helper::rgba(102, 102, 204, 143) },
            { ImGuiCol_WindowBg,         helper::rgba(29, 29, 29, 246) }
        }
    };
    inline const Palette Red = {
        {
            { ImGuiCol_TitleBg,          helper::rgba(255, 50, 39, 246) },
            { ImGuiCol_TitleBgActive,    helper::rgba(255, 80, 60, 246) },
            { ImGuiCol_TitleBgCollapsed, helper::rgba(180, 40, 30, 180) },
            { ImGuiCol_WindowBg,         helper::rgba(20, 20, 20, 246) },
            { ImGuiCol_Button,           helper::rgba(255, 60, 50, 255) },
            { ImGuiCol_ButtonHovered,    helper::rgba(255, 100, 90, 255) }
        }
    };
}