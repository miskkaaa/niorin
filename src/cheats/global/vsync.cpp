#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
using namespace geode::prelude;
#ifdef GEODE_IS_WINDOWS

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::global {
    static void vsynccb(bool value) {
        GameManager::sharedState()->setGameVariable(GameVar::VerticalSync, value);
        AppDelegate::get()->toggleVerticalSync(value);
        niorin::global::vsync = value;
    }
    bool _register() {
        niorin::cheats::all::registerCheat({
            .name       = "VSync",
            .desc       = "enable or disable vsync",
            .author     = "miskaa",
            .type       = 2,
            .callback   = vsynccb
        });
        return true;
    } bool registered = _register();
}

class $modify(GameManager) {
    void setGameVariable(char const* key, bool value) {
        GameManager::setGameVariable(key, value);
        if (strcmp(key, "0030") == 0) { // we love stealing, dont we? anyways thank you eclipse menu
            niorin::global::vsync = value;
            auto* c = niorin::cheats::all::find("VSync");
            if (c) c->enabled = value;
            AppDelegate::get()->toggleVerticalSync(value);
        }
    }
};

#endif