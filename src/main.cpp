#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>

#include "themes/listing.hpp"
#include "cheats/headers/safe.hpp"

using namespace geode::prelude;

static ImFont* idk1 = nullptr;

$on_mod(Loaded) {
    niorin::list::safe::init();

    ImGuiCocos::get()
        .setup([] {
            auto& io = ImGui::GetIO();

            ImGui::StyleColorsClassic();

            auto fontPath = (
                Mod::get()->getResourcesDir() / "DroidSans.ttf"
            ).string();

            io.Fonts->AddFontDefault();

            idk1 = io.Fonts->AddFontFromFileTTF(
                fontPath.c_str(),
                12.f,
                nullptr,
                io.Fonts->GetGlyphRangesJapanese()
            );

            io.FontDefault = idk1;

            niorin::theme::apply(niorin::theme::theme::Default);
        })

        .draw([] {
            static bool open     = true;
            static float size    = 18.f;
            static int selected  = 0;
            static bool checkbox = true;

            static char buf[256] = "typing box";

            if (!open) {
                ImGui::End();
                return;
            }

            if (ImGui::Begin("Niorin ImGui demo", &open)) {
                ImGui::SeparatorText("Imporant :3");
                const char* text =
                    "Niorin - mod menu\n"
                    "Cool ass mod menu:tm: (not really tho)\n"
                    "thank you prevter for letting me steal the source code of eclipses start position";

                float width  = ImGui::GetContentRegionAvail().x;
                float twidth = ImGui::CalcTextSize(text).x;
                float inden  = (width - twidth) * 0.5f;
                if (inden > 0.0f)
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + inden);
                ImGui::TextWrapped("%s",text);

                ImGui::SeparatorText("Misc");

                if (ImGui::CollapsingHeader("Misc")) {
                    ImGui::Separator();

                    ImGui::DragFloat(
                        "Size",
                        &size,
                        0.25f,
                        5.f,
                        100.f
                    );

                    const char* items[] = {
                        "Normal"
                    };

                    ImGui::Combo(
                        "Font",
                        &selected,
                        items,
                        IM_ARRAYSIZE(items)
                    );

                    ImFont* activeFont = nullptr;
                    if (selected == 0) activeFont = idk1;

                    if (activeFont) {
                        ImGui::PushFont(activeFont);
                    }

                    ImGui::SetWindowFontScale(size / 18.f);

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                    ImGui::InputText(
                        "Input",
                        buf,
                        sizeof(buf)
                    );

                    ImGui::Checkbox(
                        "Cool checkbox",
                        &checkbox
                    );

                    if (ImGui::Button("Show demo")) {
                        log::info("button pressed");
                    }

                    ImGui::SetWindowFontScale(1.f);

                    if (activeFont) {
                        ImGui::PopFont();
                    }
                }

                ImGui::SeparatorText("Cheats");

                if (ImGui::CollapsingHeader("Safe")) {
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Contains all of the safe mods/cheats that you can use mid gameplay");
                        ImGui::Separator();
                        ImGui::Text("Contains stuff as:\n   - Start Position Switcher");
                        ImGui::EndTooltip();
                    }

                    for (auto& c : niorin::list::safe::get()) {
                        if (ImGui::Checkbox(c.name.c_str(), &c.enabled)) {
                            if (c.callback) {
                                c.callback(c.enabled);
                            }
                        }

                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::Text("%s", c.desc.c_str());
                            ImGui::Separator();
                            ImGui::Text("made by %s", c.author.c_str());
                            ImGui::EndTooltip();
                        }
                    }
                }

                ImGui::Separator();

                auto& cheats = niorin::list::safe::get();
                if (!cheats.empty() && cheats[0].index == 1) {
                    if (cheats[0].enabled) {
                        ImGui::Text("Switcher is enabled");
                        ImGui::NewLine();

                        if (niorin::list::safe::detect()) {
                            ImGui::Text("you are in startpos");
                        } else {
                            ImGui::Text("you aren't in startpos");
                        }
                    }
                }

                ImGui::SetWindowFontScale(1.f);
            }

            ImGui::SeparatorText("Theme");
            if (ImGui::CollapsingHeader("Theme")) {
                static int style = 0;
                static int color = 0;

                const char* styles[] = {
                    "Default"
                };

                const char* colors[] = {
                    "Default",
                    "Red"
                };

                ImGui::Combo("Style Theme", &style, styles, niorin::theme::tc);
                ImGui::Combo("Color Theme", &color, colors, niorin::theme::cc);

                niorin::theme::apply(
                    static_cast<niorin::theme::theme>(style),
                    static_cast<niorin::theme::color_t>(color)
                );
            }
            ImGui::End();
            ImGui::ShowDemoWindow();
        });
}