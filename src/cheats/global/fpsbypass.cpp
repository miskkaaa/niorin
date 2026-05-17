#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS

constexpr float MIN_FPS = 1.f;
constexpr float MAX_FPS = 96767.f;

namespace niorin::cheats::global::fps {

    static float fps = 60.f;
    static bool enabled = false;

    static bool appliedEnabled = false;
    static float appliedFps = 60.f;
    static bool lsKnownGood = true;

    static void applyfps() {
        auto* gm = GameManager::sharedState();
        if (!gm) return;

        float capped = std::clamp(fps, MIN_FPS, MAX_FPS);

        gm->m_customFPSTarget = capped;
        gm->setGameVariable(GameVar::UnlockFPS, enabled);

        float interval = 1.f / (enabled ? capped : 60.f);
        CCDirector::sharedDirector()->setAnimationInterval(interval);

        appliedEnabled = gm->getGameVariable(GameVar::UnlockFPS);
        appliedFps = gm->m_customFPSTarget;

        lsKnownGood =
            appliedEnabled == enabled &&
            std::abs(appliedFps - capped) < 0.01f;
    }

    static void fpscb(float v) {
        fps = std::clamp(v, MIN_FPS, MAX_FPS);

        auto* gm = GameManager::sharedState();
        if (!gm) return;

        if (enabled && gm->getGameVariable(GameVar::VerticalSync)) {
            gm->setGameVariable(GameVar::VerticalSync, false);
            AppDelegate::get()->toggleVerticalSync(false);

            niorin::global::vsync = false;

            auto* c = niorin::cheats::all::find("VSync");
            if (c) c->enabled = false;
        }

        applyfps();
    }

    static void togglecb(bool state) {
        enabled = state;
        auto* gm = GameManager::sharedState();
        if (!gm) return;

        if (enabled && gm->getGameVariable(GameVar::VerticalSync)) {
            gm->setGameVariable(GameVar::VerticalSync, false);
            AppDelegate::get()->toggleVerticalSync(false);

            niorin::global::vsync = false;

            auto* c = niorin::cheats::all::find("VSync");
            if (c) c->enabled = false;
        }
        applyfps();
    }
    
    static void validatefps() {
        auto* gm = GameManager::sharedState();
        if (!gm) return;

        float capped = std::clamp(fps, MIN_FPS, MAX_FPS);

        if (gm->m_customFPSTarget != capped ||
            gm->getGameVariable(GameVar::UnlockFPS) != enabled) {
            lsKnownGood = false;
        } else {
            lsKnownGood = true;
        }
    }

    bool _registerfps() {
        all::registerCheat({
            .name = "FPS Bypass",
            .desc = "game go vroom",
            .author = "miskaa",
            .type = 2,
            .thingy = 4,
            .value = 60.f,
            .callback = togglecb,
            .float_cb = fpscb,
            .index=3
        });

        return true;
    }

    bool registeredfps = _registerfps();
}

class $modify(niorinfpsgm, GameManager) {
    void setGameVariable(char const* key, bool value) {
        GameManager::setGameVariable(key, value);
        if (strcmp(key, GameVar::UnlockFPS) == 0) {
            niorin::cheats::global::fps::enabled = value;
            auto* c = niorin::cheats::all::find("FPS Bypass");
            if (c)
                c->enabled = value;
            if (value) {
                if (this->getGameVariable(GameVar::VerticalSync)) {
                    this->setGameVariable(GameVar::VerticalSync, false);

                    niorin::global::vsync = false;
                    auto* vs = niorin::cheats::all::find("VSync");
                    if (vs)
                        vs->enabled = false;

                    geode::queueInMainThread([] {
                        AppDelegate::get()->toggleVerticalSync(false);
                    });
                }
                niorin::cheats::global::fps::applyfps();
            }
        }

        if (strcmp(key, GameVar::VerticalSync) == 0) {
            niorin::global::vsync = value;
            auto* vs = niorin::cheats::all::find("VSync");
            if (vs)
                vs->enabled = value;

            AppDelegate::get()->toggleVerticalSync(value);
            if (value) {
                niorin::cheats::global::fps::enabled = false;

                auto* c = niorin::cheats::all::find("FPS Bypass");
                if (c)
                    c->enabled = false;

                CCDirector::sharedDirector()->setAnimationInterval(1.f / 60.f);
            }
        }
    }
};

#endif