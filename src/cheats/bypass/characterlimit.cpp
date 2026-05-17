#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::bypass::charl {
    static void charcb(bool value) {
        niorin::global::bypCH = value;
    }

    static bool _registerchar() {
        all::registerCheat({
            .name       = "Character Bypass",
            .desc       = "special characters",
            .author     = "miskaa",
            .type       = 3,
            .thingy     = 1,
            .callback   = charcb,
            .index      = 5
        });
        return true;
    }
    bool registeredchar = _registerchar();
}

class $modify(niorinBypCH, CCTextInputNode) {
    void updateLabel(std::string p0) {
        if (niorin::global::bypCH) {
            this->setAllowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,-!?:;)(/\\\"\'`*= +-_%[]<>|@&^#{}%$~");
            CCTextInputNode::updateLabel(p0);
        } else {
            CCTextInputNode::updateLabel(p0);
        }
    }
};