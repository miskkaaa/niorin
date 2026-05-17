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
        int thingy = 0;
        // use 1 when checkbox, use 2 when textbox, use 3 if float slider idk what else i honestly forgot oh and 4 if you want a float textbox

        float value = 0.f;

        std::function<void(bool)> callback;
        std::function<void(float)> float_cb;
        int index = 0;
    };
    std::vector<cheat>& get();
    cheat* find(const std::string& name);
    void toggle(const std::string& name, bool state);
    void init();

    void registerCheat(const cheat& c);
}

namespace niorin::cheats::safe::sp {
    extern bool enabled;
    extern std::vector<StartPosObject*> spos;
    extern int current;
    void next();
    void prev();
    void startpos(bool state);
    bool detect();
}