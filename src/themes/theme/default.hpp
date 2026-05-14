#pragma once
/*
 * the cool ass default theme :3
 */

#include <imgui-cocos.hpp>
#include "../helper.hpp"
#include "../color/colors.hpp"

namespace niorin::theme {
    static void _theme_default() {
        ImGui::StyleColorsClassic();

        auto& style = ImGui::GetStyle();

        // main
        style.WindowPadding         = ImVec2(20.f, 7.f);
        style.FramePadding          = ImVec2(4.f, 4.f);
        style.ItemSpacing           = ImVec2(8.f, 3.f);
        style.ItemInnerSpacing      = ImVec2(20.f, 4.f);
        style.TouchExtraPadding     = ImVec2(0.f, 0.f);

        style.IndentSpacing         = 25.f;
        style.GrabMinSize           = 15.f;

        // borders
        style.WindowBorderSize      = 1.f;
        style.ChildRounding         = 1.f;
        style.PopupRounding         = 1.f;
        style.FrameBorderSize       = 1.f;

        // rounding
        style.WindowRounding        = 12.0f;
        style.ChildRounding         = 3.0f;
        style.FrameRounding         = 20.0f;
        style.PopupRounding         = 4.0f;
        style.GrabRounding          = 12.0f;

        // scrollbar
        style.ScrollbarSize         = 13.0f;
        style.ScrollbarRounding     = 12.0f;
        style.ScrollbarPadding      = 4.0f;

        // tabs

        /*
         * we don't really need to touch this fucker since its default settings are already ok
         * not sure since this is the niorin default (now) theme
         */

        // windows
        style.WindowTitleAlign      = ImVec2(0.5f, 0.5f);
        style.WindowBorderHoverPadding = 4.f;
        style.WindowMenuButtonPosition = ImGuiDir_Right;

        // colors
        // i have created ../color/colors.hpp
        // helper defined as niorin::helper previously ffff

        const auto& col = color::Default;

        for (const auto& [idk1, idk2] : col.colors) {
            style.Colors[idk1] = idk2;
        }

        // widgets
        style.SeparatorTextAlign   = ImVec2(0.5f, 0.5f);
        style.SeparatorTextPadding = ImVec2(20.f, 6.f);
    }
}