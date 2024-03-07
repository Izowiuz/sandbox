#include <cstdlib>
#include <functional>
#include <unordered_set>

#include "spdlog/spdlog.h"

template <typename Subject, typename StateTag>
class Observer final
{
public:
    using OnUpdate = std::function<void(Subject const& subject, StateTag property)>;

    explicit Observer(OnUpdate onUpdate)
        : mOnUpdate{ std::move(onUpdate) }
    {
    }

    virtual ~Observer() = default;

    void update(Subject const& subject, StateTag property)
    {
        mOnUpdate(subject, property);
    }

private:
    OnUpdate mOnUpdate;
};

class Foo
{
public:
    enum class StateChange { XChanged, YChanged };

    using FooObserver = Observer<Foo, Foo::StateChange>;

    bool attach(FooObserver* observer)
    {
        auto [pos, result] = mObservers.insert(observer);
        return result;
    }

    bool detach(FooObserver* observer)
    {
        return mObservers.erase(observer) > 0;
    }

    void notify(StateChange property)
    {
        for (auto it = begin(mObservers); it != end(mObservers);) {
            auto const pos = it++;
            (*pos)->update(*this, property);
        }
    }

    void setX(int x)
    {
        if (mX != x) {
            mX = x;
            notify(StateChange::XChanged);
        }
    }

    void setY(int y)
    {
        if (mY != y) {
            mY = y;
            notify(StateChange::YChanged);
        }
    }

    int x() const
    {
        return mX;
    }

    int y() const
    {
        return mY;
    }

private:
    int mX{ 0 };
    int mY{ 0 };

    std::unordered_set<FooObserver*> mObservers;
};

int main()
{
    Foo f;

    Observer<Foo, Foo::StateChange> xo{ [](Foo const& subject, Foo::StateChange property) {
        if (property == Foo::StateChange::XChanged) {
            spdlog::info("x changed, yo! - value: {}", subject.x());
        }
    } };

    Observer<Foo, Foo::StateChange> yo{ [](Foo const& subject, Foo::StateChange property) {
        if (property == Foo::StateChange::YChanged) {
            spdlog::info("y changed, yo! - value: {}", subject.y());
        }
    } };

    f.attach(&xo);
    f.attach(&yo);

    f.setX(1);
    f.setY(2);

    f.detach(&xo);
    f.detach(&yo);

    f.setX(3);
    f.setY(4);

    return EXIT_SUCCESS;
}
