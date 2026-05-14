#pragma once

#include <imgui-cocos.hpp>
#include "../helper.hpp"

namespace niorin::theme {

    static void dump() {
        ImGuiStyle& style = ImGui::GetStyle();
    }

    static void _theme_classic() {
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

        style.FontSizeBase = 0.0f;
        style.FontScaleMain = 1.0f;
        style.FontScaleDpi = 1.0f;

        style.Alpha = 1.0f;
        style.DisabledAlpha = 0.60f;

        style.WindowPadding = ImVec2(8, 8);
        style.WindowRounding = 0.0f;
        style.WindowBorderSize = 1.0f;
        style.WindowBorderHoverPadding = 4.0f;
        style.WindowMinSize = ImVec2(32, 32);
        style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_Left;

        style.ChildRounding = 0.0f;
        style.ChildBorderSize = 1.0f;

        style.PopupRounding = 0.0f;
        style.PopupBorderSize = 1.0f;

        style.FramePadding = ImVec2(4, 3);
        style.FrameRounding = 0.0f;
        style.FrameBorderSize = 0.0f;

        style.ItemSpacing = ImVec2(8, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.CellPadding = ImVec2(4, 2);

        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 21.0f;
        style.ColumnsMinSpacing = 6.0f;

        style.ScrollbarSize = 14.0f;
        style.ScrollbarRounding = 9.0f;
        style.ScrollbarPadding = 2.0f;

        style.GrabMinSize = 12.0f;
        style.GrabRounding = 0.0f;

        style.LogSliderDeadzone = 4.0f;
        style.ImageBorderSize = 0.0f;

        style.TabRounding = 5.0f;
        style.TabBorderSize = 0.0f;
        style.TabMinWidthBase = 1.0f;
        style.TabMinWidthShrink = 80.0f;
        style.TabCloseButtonMinWidthSelected = -1.0f;
        style.TabCloseButtonMinWidthUnselected = 0.0f;
        style.TabBarBorderSize = 1.0f;
        style.TabBarOverlineSize = 1.0f;

        style.TableAngledHeadersTextAlign = ImVec2(0.5f, 0.0f);

        style.TreeLinesFlags = ImGuiTreeNodeFlags_DrawLinesNone;
        style.TreeLinesSize = 1.0f;
        style.TreeLinesRounding = 0.0f;
        style.ColorButtonPosition = ImGuiDir_Right;

        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

        style.SeparatorTextBorderSize = 3.0f;
        style.SeparatorTextAlign = ImVec2(0.0f, 0.5f);
        style.SeparatorTextPadding = ImVec2(20.0f, 3.0f);

        style.DisplayWindowPadding = ImVec2(19, 19);
        style.DisplaySafeAreaPadding = ImVec2(3, 3);

        style.MouseCursorScale = 1.0f;

        style.AntiAliasedLines = true;
        style.AntiAliasedLinesUseTex = true;
        style.AntiAliasedFill = true;

        style.CurveTessellationTol = 1.25f;
        style.CircleTessellationMaxError = 0.30f;

        style.HoverStationaryDelay = 0.15f;
        style.HoverDelayShort = 0.15f;
        style.HoverDelayNormal = 0.40f;

        style.HoverFlagsForTooltipMouse =
            ImGuiHoveredFlags_Stationary |
            ImGuiHoveredFlags_DelayShort |
            ImGuiHoveredFlags_AllowWhenDisabled;

        style.HoverFlagsForTooltipNav =
            ImGuiHoveredFlags_NoSharedDelay |
            ImGuiHoveredFlags_DelayNormal |
            ImGuiHoveredFlags_AllowWhenDisabled;

        style._MainScale = 1.0f;
        style._NextFrameFontSizeBase = 0.0f;
        ImGui::StyleColorsDark(); // aall again abecause i can
    }
}