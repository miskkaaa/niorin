#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "../headers/global.hpp"

using namespace geode::prelude;

namespace niorin::cheats::safe {
    inline bool enabled = false;
    inline std::vector<StartPosObject*> spos;
    inline int current = -1;

    PlayLayer* getpl() {
        return PlayLayer::get();
    }

    int count() {
        return static_cast<int>(spos.size());
    }

    void reset(PlayLayer* pl, StartPosObject* obj) {
        pl->m_currentCheckpoint = nullptr;

        pl->setStartPosObject(obj);

        pl->m_isTestMode = obj != nullptr;

        if (pl->m_isPracticeMode)
            pl->resetLevelFromStart();
        else
            pl->resetLevel();

        pl->startMusic();
        pl->updateTestModeLabel();
    }

    void pick(int index) {
        auto* pl = getpl();

        if (!pl || spos.empty() || !enabled)
            return;

        int max = count();

        if (index >= max)
            index = -1;

        if (index < -1)
            index = max - 1;

        current = index;

        auto* obj =
            current >= 0
            ? spos[current]
            : nullptr;

        reset(pl, obj);

        log::info(
            "switched startpos: {}",
            current
        );
    }

    void next() {
        pick(current + 1);
    }

    void prev() {
        pick(current - 1);
    }

    void startpos(bool state) {
        enabled = state;

        log::info(
            "startpos {}",
            enabled
            ? "enabled"
            : "disabled"
        );
    }

    bool detect() {
        auto* pl = getpl();

        return pl && pl->m_isTestMode;
    }

    bool reg() {
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

    inline bool registered = reg();
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
        if (!CCMenu::init())
            return false;

        ignoreAnchorPointForPosition(false);

        auto size =
            CCDirector::sharedDirector()->getWinSize();

        setAnchorPoint({ 1.f, 0.5f });

        setPosition(
            size.width - 25.f,
            size.height / 2.f
        );

        auto* upSpr =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow_02_001.png"
            );

        auto* downSpr =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow_02_001.png"
            );

        if (!upSpr || !downSpr)
            return false;

        upSpr->setRotation(90.f);
        downSpr->setRotation(-90.f);

        upSpr->setScale(0.7f);
        downSpr->setScale(0.7f);

        auto* up =
            CCMenuItemSpriteExtra::create(
                upSpr,
                this,
                menu_selector(StartPosSwitcherNode::onNext)
            );

        auto* down =
            CCMenuItemSpriteExtra::create(
                downSpr,
                this,
                menu_selector(StartPosSwitcherNode::onPrev)
            );

        m_current =
            CCLabelBMFont::create(
                "0",
                "bigFont.fnt"
            );

        auto* slash =
            CCLabelBMFont::create(
                "/",
                "bigFont.fnt"
            );

        m_max =
            CCLabelBMFont::create(
                "0",
                "bigFont.fnt"
            );

        if (!m_current || !slash || !m_max)
            return false;

        up->setPosition(0.f, 24.f);
        down->setPosition(0.f, -24.f);

        m_current->setPosition(-18.f, 0.f);
        slash->setPosition(0.f, 0.f);
        m_max->setPosition(18.f, 0.f);

        m_current->setScale(0.55f);
        slash->setScale(0.5f);
        m_max->setScale(0.55f);

        addChild(up);
        addChild(down);

        addChild(m_current);
        addChild(slash);
        addChild(m_max);

        scheduleUpdate();

        addEventListener(
            geode::KeyboardInputEvent(),
            [this](geode::KeyboardInputData data) {
                using Action =
                    geode::KeyboardInputData::Action;

                if (
                    data.action != Action::Press ||
                    !niorin::cheats::safe::enabled
                ) {
                    return ListenerResult::Propagate;
                }

                // replace keybindings with them custom keybindings
                switch (data.key) {
                    case KEY_Q:
                        niorin::cheats::safe::prev();
                        break;

                    case KEY_E:
                        niorin::cheats::safe::next();
                        break;

                    default:
                        break;
                }

                return ListenerResult::Propagate;
            }
        );

        return true;
    }

    void onNext(CCObject*) {
        niorin::cheats::safe::next();
    }

    void onPrev(CCObject*) {
        niorin::cheats::safe::prev();
    }

    void update(float) override {
        using namespace niorin::cheats::safe;

        setVisible(enabled);

        int now = current + 1;
        int max = count();

        m_current->setCString(
            fmt::format(
                "{}",
                now <= 0
                ? 0
                : now
            ).c_str()
        );

        m_max->setCString(
            fmt::format("{}", max).c_str()
        );
    }

private:
    CCLabelBMFont* m_current = nullptr;
    CCLabelBMFont* m_max = nullptr;
};

class $modify(niorinsp, PlayLayer) {
    bool init(
        GJGameLevel* level,
        bool useReplay,
        bool dontCreateObjects
    ) {
        if (
            !PlayLayer::init(
                level,
                useReplay,
                dontCreateObjects
            )
        ) {
            return false;
        }

        using namespace niorin::cheats::safe;

        spos.clear();
        current = -1;

        if (auto* node = StartPosSwitcherNode::create()) {
            addChild(node);

            log::info("startpos ui added");
        }
        else {
            log::error("failed creating startpos ui");
        }

        return true;
    }

    void addObject(GameObject* obj) {
        PlayLayer::addObject(obj);

        if (obj->m_objectID == 31) {
            niorin::cheats::safe::spos.push_back(
                static_cast<StartPosObject*>(obj)
            );
        }
    }

    void createObjectsFromSetupFinished() {
        PlayLayer::createObjectsFromSetupFinished();

        using namespace niorin::cheats::safe;

        std::sort(
            spos.begin(),
            spos.end(),
            [](auto* a, auto* b) {
                return
                    a->getPositionX()
                    < b->getPositionX();
            }
        );

        if (!m_startPosObject)
            return;

        auto it =
            std::find(
                spos.begin(),
                spos.end(),
                m_startPosObject
            );

        if (it != spos.end()) {
            current =
                static_cast<int>(
                    std::distance(
                        spos.begin(),
                        it
                    )
                );
        }
    }
};
