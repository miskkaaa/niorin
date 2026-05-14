#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

namespace niorin::global {
    inline auto* gm = GameManager::sharedState();

    inline bool vsync = gm->getGameVariable(GameVar::VerticalSync);
    inline bool unfps = gm->getGameVariable(GameVar::UnlockFPS);
    inline bool cbs   = gm->getGameVariable(GameVar::ClickBetweenSteps);
    inline bool cos   = gm->getGameVariable(GameVar::ClickOnSteps);
}