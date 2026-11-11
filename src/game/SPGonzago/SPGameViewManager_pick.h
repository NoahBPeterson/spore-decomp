// Retail pick-priority view used by SPGameViewManager.cpp. Original complete declarations are unavailable.
#ifndef SPGAMEVIEWMANAGER_PICK_H
#define SPGAMEVIEWMANAGER_PICK_H

#include "SP/cILayer.h"
#include "EA/Messaging/IHandler.h"
#include "SP/cGonzagoSubsystem.h"

namespace Simulator {

// Bounded retail view of the twelve-byte records used by the game-view picker.
struct PickPriority {
    unsigned mType;
    int mKind;
    int mPriority;
    PickPriority(unsigned type, int kind, int priority)
        : mType(type), mKind(kind), mPriority(priority) {}
};

struct PickPriorityVector {
    PickPriority* mpBegin;
    PickPriority* mpEnd;
    PickPriority* mpCapacity;
    unsigned mAllocator[2];

    // Imported eastl::vector assignment, 0x00b375f0; ECX=destination, ret4.
    PickPriorityVector& operator=(const PickPriorityVector& other);
};

// The complete manager continues beyond this bounded view.
struct cGameViewManager : SP::cILayer, EA::Messaging::IHandler, SP::cGonzagoSubsystem {
    virtual void func10h_();
    virtual void PrepareSimulator();
    virtual void func18h_();
    virtual void func1Ch_();
    virtual void func20h_();
    virtual void func24h_();
    virtual void func28h_();
    // Descriptive name; the original setter declaration has not been recovered.
    virtual void SetPickPriorities(const PickPriorityVector* other, bool renumber); // slot11

    unsigned mPad24[(0xac-0x24)/4];
    PickPriorityVector mPickPriorities; // +0xac; full20-byte vector
    bool mFlagC0;
    bool mViewsVisible;
};

} // namespace Simulator

#endif
