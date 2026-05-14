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
            // text
            { ImGuiCol_Text,                  helper::rgba(230, 230, 230, 255) },
            { ImGuiCol_TextDisabled,          helper::rgba(130, 130, 130, 255) },

            // window bg
            { ImGuiCol_WindowBg,              helper::rgba(15, 15, 15, 255) },
            { ImGuiCol_ChildBg,               helper::rgba(0, 0, 0, 0) },
            { ImGuiCol_PopupBg,               helper::rgba(20, 20, 20, 240) },

            // title
            { ImGuiCol_TitleBg,               helper::rgba(24, 24, 24, 255) },
            { ImGuiCol_TitleBgActive,         helper::rgba(54, 54, 54, 255) },
            { ImGuiCol_TitleBgCollapsed,      helper::rgba(24, 24, 24, 200) },

            // borders / separators / whatever
            { ImGuiCol_Border,                helper::rgba(60, 60, 60, 120) },
            { ImGuiCol_BorderShadow,          helper::rgba(0, 0, 0, 0) },
            { ImGuiCol_Separator,             helper::rgba(60, 60, 60, 180) },
            { ImGuiCol_SeparatorHovered,      helper::rgba(90, 90, 90, 255) },
            { ImGuiCol_SeparatorActive,       helper::rgba(120, 120, 120, 255) },

            // widgdts
            { ImGuiCol_FrameBg,               helper::rgba(30, 30, 30, 255) },
            { ImGuiCol_FrameBgHovered,        helper::rgba(40, 40, 40, 255) },
            { ImGuiCol_FrameBgActive,         helper::rgba(50, 50, 50, 255) },
            { ImGuiCol_CheckMark,             helper::rgba(200, 200, 200, 255) },
            { ImGuiCol_SliderGrab,            helper::rgba(120, 120, 120, 255) },
            { ImGuiCol_SliderGrabActive,      helper::rgba(160, 160, 160, 255) },

            // buttons or headers wtv
            { ImGuiCol_Button,                helper::rgba(45, 45, 45, 255) },
            { ImGuiCol_ButtonHovered,         helper::rgba(60, 60, 60, 255) },
            { ImGuiCol_ButtonActive,          helper::rgba(75, 75, 75, 255) },
            { ImGuiCol_Header,                helper::rgba(45, 45, 45, 255) },
            { ImGuiCol_HeaderHovered,         helper::rgba(65, 65, 65, 255) },
            { ImGuiCol_HeaderActive,          helper::rgba(85, 85, 85, 255) },

            // tabs
            { ImGuiCol_Tab,                   helper::rgba(30, 30, 30, 255) },
            { ImGuiCol_TabHovered,            helper::rgba(60, 60, 60, 255) },
            { ImGuiCol_TabActive,             helper::rgba(80, 80, 80, 255) },
            { ImGuiCol_TabUnfocused,          helper::rgba(25, 25, 25, 255) },
            { ImGuiCol_TabUnfocusedActive,    helper::rgba(45, 45, 45, 255) },

            // scroll
            { ImGuiCol_ScrollbarBg,           helper::rgba(10, 10, 10, 255) },
            { ImGuiCol_ScrollbarGrab,         helper::rgba(50, 50, 50, 255) },
            { ImGuiCol_ScrollbarGrabHovered,  helper::rgba(70, 70, 70, 255) },
            { ImGuiCol_ScrollbarGrabActive,   helper::rgba(90, 90, 90, 255) },

            // tables
            { ImGuiCol_TableHeaderBg,         helper::rgba(25, 25, 25, 255) },
            { ImGuiCol_TableBorderStrong,     helper::rgba(60, 60, 60, 255) },
            { ImGuiCol_TableBorderLight,      helper::rgba(40, 40, 40, 255) },
            { ImGuiCol_TableRowBg,            helper::rgba(0, 0, 0, 0) },
            { ImGuiCol_TableRowBgAlt,         helper::rgba(255, 255, 255, 5) },

            // misc
            { ImGuiCol_MenuBarBg,             helper::rgba(48, 48, 48, 255) },
            { ImGuiCol_ResizeGrip,            helper::rgba(80, 80, 80, 100) },
            { ImGuiCol_ResizeGripHovered,     helper::rgba(100, 100, 100, 160) },
            { ImGuiCol_ResizeGripActive,      helper::rgba(130, 130, 130, 200) },
            { ImGuiCol_PlotLines,             helper::rgba(200, 200, 200, 255) },
            { ImGuiCol_PlotLinesHovered,      helper::rgba(255, 100, 100, 255) },
            { ImGuiCol_PlotHistogram,         helper::rgba(200, 200, 200, 255) },
            { ImGuiCol_PlotHistogramHovered,  helper::rgba(255, 100, 100, 255) },
            { ImGuiCol_DragDropTarget,        helper::rgba(255, 255, 255, 200) },
            { ImGuiCol_NavHighlight,          helper::rgba(120, 120, 255, 255) },
            { ImGuiCol_NavWindowingHighlight, helper::rgba(255, 255, 255, 200) },
            { ImGuiCol_NavWindowingDimBg,     helper::rgba(0, 0, 0, 150) },
            { ImGuiCol_ModalWindowDimBg,      helper::rgba(0, 0, 0, 120) }
        }
    };

    inline const Palette Purple = {
        {
            { ImGuiCol_TitleBg,          helper::rgba(69, 69, 138, 255) },
            { ImGuiCol_TitleBgActive,    helper::rgba(82, 82, 161, 255) },
            { ImGuiCol_TitleBgCollapsed, helper::rgba(102, 102, 204, 143) },
            { ImGuiCol_WindowBg,         helper::rgba(29, 29, 29, 255) }
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