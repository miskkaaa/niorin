#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

namespace niorin::cheats::all {

    struct cheat {
        std::string name;
        std::string desc;
        std::string author;

        bool enabled = false;
        int type = 0;
        // Use 1 when its a Level cheat
        // Use 2 when its a Global cheat
        std::function<void(bool)> callback;

        int index = 0;
    };
    std::vector<cheat>& get();
    cheat* find(const std::string& name);
    void toggle(const std::string& name, bool state);
    void init();

    void registerCheat(const cheat& c);
}