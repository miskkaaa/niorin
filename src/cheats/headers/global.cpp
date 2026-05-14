#include "global.hpp"

namespace niorin::cheats::all {

    std::vector<cheat>& get() {
        static std::vector<cheat> instance;
        return instance;
    }

    void registerCheat(const cheat& c) {
        auto& v = get();
        cheat copy = c;
        copy.index = static_cast<int>(v.size());
        v.push_back(copy);
    }

    cheat* find(const std::string& name) {
        for (auto& v = get(); auto& c : v) {
            if (c.name == name) return &c;
        }
        return nullptr;
    }

    void toggle(const std::string& name, const bool state) {
        auto* c = find(name);
        if (!c) return;

        c->enabled = state;

        if (c->callback)
            c->callback(state);
    }

    void init() {
        log::info("cheats loaded: {}", get().size());
    }
}