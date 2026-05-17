#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

#include "../../magic/global.hpp"
#include "../headers/global.hpp"

namespace niorin::cheats::bypass::textlength {
    static void lengthcb(bool value) {
        niorin::global::infLE = value;
    }

    static bool _registerlength() {
        all::registerCheat({
            .name       = "Character Legnth",
            .desc       = "no text length limit",
            .author     = "miskaa",
            .type       = 3,
            .thingy     = 1,
            .callback   = lengthcb,
            .index      = 6
        });
        return true;
    }
    bool registeredlength = _registerlength();
}
class $modify(NiorinTextLength, CCTextInputNode) {
    void updateLabel(gd::string p0) {
        if (niorin::global::infLE) {
            this->m_maxLabelLength = -1;
            CCTextInputNode::updateLabel(p0);
        } else {
            CCTextInputNode::updateLabel(p0);
        }
    }
};