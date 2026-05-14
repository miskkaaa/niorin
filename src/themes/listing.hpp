#pragma once

#include "theme/default.hpp"
#include "theme/classic.hpp"
#include "color/colors.hpp"

namespace niorin::theme {
    enum class theme {
        Default,
        ImGuiClassic
    };

    enum class color_t {
        Default,
        Red,
        Purple
    };

    inline constexpr int tc = 2;
    inline constexpr int cc = 3;

    inline const char* name(const theme t) {
        switch (t) {
            case theme::Default: return "Default";
            case theme::ImGuiClassic: return "ImGuiClassic";
        }
        return "unknown";
    }

    inline const char* name(const color_t t) {
        switch (t) {
            case color_t::Default:  return "Default";
            case color_t::Red:      return "Red";
            case color_t::Purple:   return "Purple";
        }
        return "unknown";
    }

    inline const color::Palette& get(const color_t t) {
        switch (t) {
            case color_t::Default:
                return color::Default;
            case color_t::Red:
                return color::Red;
            case color_t::Purple:
                return color::Purple;
        }
        return color::Default;
    }

    inline void style_a(const theme t) {
        switch (t) {
            case theme::Default:
                _theme_default();
                break;
            case theme::ImGuiClassic:
                _theme_classic();
                break;
        }
    }

    inline void apply(const theme t, const color_t ct = color_t::Default) {
        style_a(t);

        const auto& c = get(ct);
        auto& style = ImGui::GetStyle();

        for (const auto& [idk1, idk2] : c.colors) {
            style.Colors[idk1] = idk2;
        }
    }
}