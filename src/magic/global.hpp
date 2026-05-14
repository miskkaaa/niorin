#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

namespace niorin::global {
    static auto vsync = GameManager::sharedState()->getGameVariable(GameVar::VerticalSync);
    static auto crfps = GameManager::sharedState()->getGameVariable(GameVar::UnlockFPS);
}