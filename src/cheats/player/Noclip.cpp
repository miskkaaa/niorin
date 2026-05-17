#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::player::noclip {
    static void noclipcb(bool value) {
        niorin::global::nocli = value;
    }

    static bool _registernoclip() {
        all::registerCheat({
            .name       = "Noclip",
            .desc       = "no death",
            .author     = "miskaa",
            .type       = 4,
            .thingy     = 1,
            .callback   = noclipcb,
            .index      = 8
        });
        return true;
    }
    bool registerednoclip = _registernoclip();
}

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* plr, GameObject* obj) {
        bool shouldDestroy = !niorin::global::nocli;

        if (shouldDestroy) {
            PlayLayer::destroyPlayer(plr, obj);
        }
    }
};