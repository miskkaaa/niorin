#pragma once
/*
 * mobile friendly theme
 */

#include <imgui-cocos.hpp>
#include "../helper.hpp"
#include "../color/colors.hpp"

namespace niorin::theme {
    static void _theme_mobile() {
        ImGui::StyleColorsClassic();
        auto& style = ImGui::GetStyle();

        style.WindowPadding         = ImVec2(16.f, 16.f);
        style.FramePadding          = ImVec2(12.f, 10.f);
        style.ItemSpacing           = ImVec2(12.f, 12.f);
        style.ItemInnerSpacing      = ImVec2(10.f, 10.f);

        style.TouchExtraPadding     = ImVec2(6.f, 6.f);

        style.IndentSpacing         = 28.f;
        style.GrabMinSize           = 26.f;

        // borders
        style.WindowBorderSize      = 0.f;
        style.ChildBorderSize       = 0.f;
        style.PopupBorderSize       = 1.f;
        style.FrameBorderSize       = 0.f;

        // rounding
        style.WindowRounding        = 16.0f;
        style.ChildRounding         = 8.0f;
        style.FrameRounding         = 10.0f;
        style.PopupRounding         = 12.0f;
        style.GrabRounding          = 10.0f;

        // scrollbar
        style.ScrollbarSize         = 18.0f;
        style.ScrollbarRounding     = 12.0f;
        style.ScrollbarPadding      = 2.0f;

        // windows
        style.WindowTitleAlign      = ImVec2(0.5f, 0.5f);
        style.WindowBorderHoverPadding = 6.f;
        style.WindowMenuButtonPosition = ImGuiDir_Right;

        // widgets
        style.SeparatorTextAlign   = ImVec2(0.5f, 0.5f);
        style.SeparatorTextPadding = ImVec2(20.f, 12.f);
    }
}