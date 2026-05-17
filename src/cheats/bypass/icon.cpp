#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::bypass::icon {
    static void iconcb(bool value) {
        niorin::global::iconB = value;
    }

    static bool _registericon() {
        all::registerCheat({
            .name       = "Icon Hack",
            .desc       = "unlock every single Icon and Color in the icon kit or garage or whatever",
            .author     = "miskaa",
            .type       = 3,
            .thingy     = 1,
            .callback   = iconcb,
            .index      = 7
        });
        return true;
    }
    bool registeredicon = _registericon();
}

class $modify(niorinIcoH, GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (niorin::global::iconB) {
            if (GameManager::isIconUnlocked(id, type)) return true;
            if (id <= 0) return false;
            return true;
        } else {
            return GameManager::isIconUnlocked(id, type);
        }
    }
    bool isColorUnlocked(int id, UnlockType type) {
        if (niorin::global::iconB) {
            if (GameManager::isColorUnlocked(id, type)) return true;
            return true;
        } else {
            return GameManager::isColorUnlocked(id, type);
        }
    }
};