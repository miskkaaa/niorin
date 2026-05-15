#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::global {

    static void coscb(bool value) {
        auto* gm = GameManager::sharedState();
        gm->setGameVariable(GameVar::ClickOnSteps, value);
        if (auto* gl = PlayLayer::get()) {
            gl->m_clickOnSteps = value;
        }

        niorin::global::cos = value;
    }

    static bool _registercos() {
        all::registerCheat({
            .name       = "Click on Steps",
            .desc       = "enable or disable CoS",
            .author     = "miskaa",
            .type       = 2,
            .thingy     = 1,
            .callback   = coscb,
            .index      = 4
        });
        return true;
    }
    bool registeredcos = _registercos();
}

class $modify(niorincosgm, GameManager) {
    void setGameVariable(char const* key, bool value) {
        GameManager::setGameVariable(key, value);
        if (strcmp(key, GameVar::ClickOnSteps) == 0) {
            niorin::global::cos = value;
            auto* c = niorin::cheats::all::find("Click on Steps");
            if (c) {
                c->enabled = value;
            }
            if (auto* gl = PlayLayer::get()) {
                gl->m_clickOnSteps = value;
            }
        }
    }
};