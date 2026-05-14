#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../headers/global.hpp"

using namespace geode::prelude;

namespace niorin::cheats::safe {
    static bool enabled = true;

    void startpos(const bool state) {
        enabled = state;
        if (enabled)
            log::info("yes");
        else
            log::info("no");
    }

    bool detect() {
        const auto* playLayer = PlayLayer::get();
        if (!playLayer) return false;
        return playLayer->m_isTestMode;
    }

    bool _register() {
        all::registerCheat({
            .name="Start Position Switcher",
            .desc="start positions (replace later",
            .author="miskaa",
            .type=1,
            .callback=startpos,
            .index=2,
        });
        return true;
    }
    bool registered = _register();
}