#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::global::cbs {

    static void cbscb(bool value) {
        auto* gm = GameManager::sharedState();
        gm->setGameVariable(GameVar::ClickBetweenSteps, value);
        if (auto* gl = PlayLayer::get()) {
            gl->m_clickBetweenSteps = value;
        }

        niorin::global::cbs = value;
    }

    static bool _registercbs() {
        all::registerCheat({
            .name       = "Click between Steps",
            .desc       = "enable or disable CbS",
            .author     = "miskaa",
            .type       = 2,
            .thingy     = 1,
            .callback   = cbscb,
            .index      = 5
        });
        return true;
    }
    bool registeredcbs = _registercbs();
}

class $modify(niorincbsgm, GameManager) {
    void setGameVariable(char const* key, bool value) {
        GameManager::setGameVariable(key, value);
        if (strcmp(key, GameVar::ClickBetweenSteps) == 0) {
            niorin::global::cbs = value;
            auto* c = niorin::cheats::all::find("Click between Steps");
            if (c) {
                c->enabled = value;
            }
            if (auto* gl = PlayLayer::get()) {
                gl->m_clickBetweenSteps = value;
            }
        }
    }
};