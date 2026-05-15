#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>

#include "themes/listing.hpp"
#include "cheats/headers/global.hpp"

using namespace geode::prelude;

static ImFont* idk1 = nullptr;

$on_mod(Loaded) {
    niorin::cheats::all::init();

    static int ls = -1; // last style
    static int lc = -1; // last color

    ImGuiCocos::get()
        .setup([] {
            auto& io = ImGui::GetIO();

            ImGui::StyleColorsClassic();

            const auto fontPath = (
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

            niorin::theme::apply(niorin::theme::theme::Default, niorin::theme::color_t::Default);
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

            if (ImGui::IsKeyPressed(ImGuiKey_Q)) {
                niorin::cheats::safe::prev();
            }
            if (ImGui::IsKeyPressed(ImGuiKey_E)) {
                niorin::cheats::safe::next();
            }
            if (ImGui::Begin("Niorin", &open)) {
                ImGui::SeparatorText("Imporant :3");
                const auto text =
                    "Niorin - mod menu\n"
                    "Cool ass mod menu:tm: (not really tho)\n"
                    "A lot of source code has been taken from Eclipse (github.com/EclipseMenu/EclipseMenu), fpsbypass and startposition go to them";

                const float width  = ImGui::GetContentRegionAvail().x;
                const float twidth = ImGui::CalcTextSize(text).x;
                if (const float inden  = (width - twidth) * 0.5f; inden > 0.0f)
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

                if (ImGui::CollapsingHeader("Global")) {
                    auto& cheats = niorin::cheats::all::get();
                    using cheat_t =
                        std::remove_reference_t<decltype(niorin::cheats::all::get()[0])>;

                    cheat_t* cos = nullptr;
                    cheat_t* cbs = nullptr;

                    for (auto& c : niorin::cheats::all::get()) {
                        if (c.type != 2) continue;
                        if (c.name == "Click on Steps") {
                            cos = &c;
                            continue;
                        }

                        if (c.name == "Click between Steps") {
                            cbs = &c;
                            continue;
                        }

                        if (c.thingy == 1) {
                            if (ImGui::Checkbox(c.name.c_str(), &c.enabled)) {
                                if (c.callback) {
                                    c.callback(c.enabled);
                                }
                            }
                        }
                        else if (c.thingy == 4) {
                            if (ImGui::InputFloat(
                                c.name.c_str(),
                                &c.value,
                                0.f,
                                0.f,
                                "%.4f",
                                ImGuiInputTextFlags_EnterReturnsTrue
                            )) {
                                if (c.float_cb) {
                                    c.float_cb(c.value);
                                }
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

                    ImGui::SeparatorText("Input");

                    auto drawtoggle = [&](auto* c) {
                        if (!c) return;

                        if (ImGui::Checkbox(c->name.c_str(), &c->enabled)) {
                            if (c->callback) {
                                c->callback(c->enabled);
                            }
                        }

                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::Text("%s", c->desc.c_str());
                            ImGui::Separator();
                            ImGui::Text("made by %s", c->author.c_str());
                            ImGui::EndTooltip();
                        }
                    };

                    drawtoggle(cbs);
                    drawtoggle(cos);
                }
                ImGui::Separator();
                if (ImGui::CollapsingHeader("Level")) {
                    for (auto& c : niorin::cheats::all::get()) {
                        if (c.type != 1) continue;
                        if (c.thingy == 1) {
                            if (ImGui::Checkbox(c.name.c_str(), &c.enabled)) {
                                if (c.callback) {
                                    c.callback(c.enabled);
                                }
                            }
                        } else if (c.thingy == 4) {
                            if (ImGui::InputFloat(c.name.c_str(), &c.value, 0.f, 0.f, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue)) {
                                if (c.float_cb) {
                                    c.float_cb(c.value);
                                }
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
                //ImGui::Separator();
                const auto& safe = niorin::cheats::all::get();
                // bool debug = false; // replace later
                if (!safe.empty() && safe[0].index == 1) {
                    /*
                     you can detect some shit thats all, not rlly needed
                    */
                }

                ImGui::SetWindowFontScale(1.f);
            }

            ImGui::SeparatorText("Theme");
            if (ImGui::CollapsingHeader("Theme")) {
                static int style = 0;
                static int color = 0;

                const char* styles[] = {
                    "Default",
                    "ImGuiClassic"
                };

                const char* colors[] = {
                    "Default",
                    "Red",
                    "Purple"
                };

                ImGui::Combo("Style Theme", &style, styles, niorin::theme::tc);
                ImGui::Combo("Color Theme", &color, colors, niorin::theme::cc);
                const auto t = static_cast<niorin::theme::theme>(style);
                const auto c = static_cast<niorin::theme::color_t>(color);

                if (style != ls || color != lc) {
                    niorin::theme::apply(t, c);

                    ls = style;
                    lc = color;
                }
            }
            ImGui::End();
            ImGui::ShowDemoWindow();
        });
}