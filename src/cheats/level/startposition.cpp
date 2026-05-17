#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../headers/global.hpp"

using namespace geode::prelude;

namespace niorin::cheats::safe {
    bool enabled = false;
    std::vector<StartPosObject*> spos;
    int current = -1;

    static void pick(PlayLayer* pl, int index) {
        if (!pl || spos.empty()) return;

        int count = static_cast<int>(spos.size());

        if (index >= count) index = -1;
        else if (index < -1) index = count - 1;

        current = index;
        auto* obj = (current >= 0) ? spos[current] : nullptr;

        pl->m_currentCheckpoint = nullptr;
        pl->setStartPosObject(obj);
        pl->m_isTestMode = (obj != nullptr);

        if (pl->m_isPracticeMode) {
            pl->resetLevelFromStart();
        } else {
            pl->resetLevel();
        }

        pl->startMusic();
        pl->updateTestModeLabel();

        log::info("startpos switched {}", current);
    }

    void next() {
        auto* pl = PlayLayer::get();
        if (!pl || !enabled) return;
        pick(pl, current + 1);
    }

    void prev() {
        auto* pl = PlayLayer::get();
        if (!pl || !enabled) return;
        pick(pl, current - 1);
    }

    void startpos(bool state) {
        enabled = state;
        log::info("startpos {}", enabled ? "enabled" : "disabled");
    }

    bool detect() {
        auto* pl = PlayLayer::get();
        return pl ? pl->m_isTestMode : false;
    }

    bool _registersp() {
        all::registerCheat({
            .name = "Start Position Switcher",
            .desc = "switch between start positions",
            .author = "miskaa",
            .enabled = false,
            .type = 1,
            .thingy = 1,
            .callback = startpos,
            .index = 2
        });
        return true;
    }

    bool registeredsp = _registersp();
}

class StartPosSwitcherNode : public CCMenu {
public:
    static StartPosSwitcherNode* create() {
        auto* ret = new StartPosSwitcherNode();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool init() override {
        if (!CCMenu::init()) return false;

        ignoreAnchorPointForPosition(false);
        setAnchorPoint({ 0.1f, 0.5f });

        auto size = CCDirector::sharedDirector()->getWinSize();
        setPosition(size.width, size.height);

        auto* upSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        auto* downSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
        if (!upSpr || !downSpr) return false;

        upSpr->setRotation(90.f);
        downSpr->setRotation(-90.f);
        upSpr->setScale(0.7f);
        downSpr->setScale(0.7f);

        auto* up = CCMenuItemSpriteExtra::create(upSpr, this, menu_selector(StartPosSwitcherNode::onNext));
        auto* down = CCMenuItemSpriteExtra::create(downSpr, this, menu_selector(StartPosSwitcherNode::onPrev));

        m_current = CCLabelBMFont::create("0", "bigFont.fnt");
        auto* slash = CCLabelBMFont::create(" / ", "bigFont.fnt");
        m_max = CCLabelBMFont::create("0", "bigFont.fnt");

        if (!m_current || !slash || !m_max) return false;

        up->setPosition(0.f, 24.f);
        m_current->setPosition(-20.f, 0.f);
        slash->setPosition(0.f, 0.f);
        m_max->setPosition(20.f, 0.f);
        down->setPosition(0.f, -24.f);

        m_current->setScale(0.55f);
        slash->setScale(0.5f);
        m_max->setScale(0.55f);

        addChild(up);
        addChild(m_current);
        addChild(slash);
        addChild(m_max);
        addChild(down);

        scheduleUpdate();
        return true;
    }

    void onNext(CCObject*) { niorin::cheats::safe::next(); }
    void onPrev(CCObject*) { niorin::cheats::safe::prev(); }

    void update(float) override {
        setVisible(niorin::cheats::safe::enabled);

        int current = niorin::cheats::safe::current + 1;
        int max = static_cast<int>(niorin::cheats::safe::spos.size());

        m_current->setCString(fmt::format("{}", current <= 0 ? 0 : current).c_str());
        m_max->setCString(fmt::format("{}", max).c_str());
    }

private:
    CCLabelBMFont* m_current = nullptr;
    CCLabelBMFont* m_max = nullptr;
};

class $modify(niorinsp, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        niorin::cheats::safe::spos.clear();
        niorin::cheats::safe::current = -1;

        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        if (auto* node = StartPosSwitcherNode::create()) {
            addChild(node, 999999);
            log::info("startpos ui added");
        } else {
            log::error("failed creating startpos ui");
        }

        return true;
    }

    void addObject(GameObject* obj) {
        PlayLayer::addObject(obj);

        if (obj->m_objectID == 31) {
            niorin::cheats::safe::spos.push_back(static_cast<StartPosObject*>(obj));
        }
    }

    void createObjectsFromSetupFinished() {
        PlayLayer::createObjectsFromSetupFinished();

        auto& v = niorin::cheats::safe::spos;
        std::sort(v.begin(), v.end(), [](auto* a, auto* b) {
            return a->getPositionX() < b->getPositionX();
        });

        if (m_startPosObject) {
            auto it = std::find(v.begin(), v.end(), m_startPosObject);
            if (it != v.end()) {
                niorin::cheats::safe::current = static_cast<int>(std::distance(v.begin(), it));
            }
        }
    }
};