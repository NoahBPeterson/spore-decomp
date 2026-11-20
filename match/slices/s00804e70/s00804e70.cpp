// @ 0x00804e70

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13eb938[];
extern "C" char g_13ec458[];
extern "C" char g_1417790[];
extern "C" char g_1417804[];

#include "game/types.h"
#include "EA/Variant.h"
#include <intrin.h>

void MultiHeapDelete(void*); // 0x00951330

namespace UTFWin {
struct FrameSequencerState {
    void** vtable;
    float mTime;
    float mFrameTime;
    float mDuration;
    float mOOFrameCount;
    float mOOFrameCountPP;
    float mFrameDuration;
    float mOOFrameDuration;
    int mDirection;
    int mEndingMode;
    int mFrameCount;
    int mCurrentFrame;
    int mLoopCount;
    int mCurrentLoop;
    int mStateFlags;
    void* mpFS;
    void* mpVisitor;
    EA::Variant mContext;
};

struct cSPUIFrameSequencer {
    void** vtable;
    int mRefCount;
    FrameSequencerState mSequencer;

    void* DeletingDtor(char flags);
};

void* cSPUIFrameSequencer::DeletingDtor(char flags) {
    vtable = (void**)g_1417804;
    mSequencer.vtable = (void**)g_1417790;
    _ReadWriteBarrier();
    ((void (__thiscall*)(FrameSequencerState*, int))mSequencer.vtable[4])(&mSequencer, 0);
    mSequencer.mContext.~Variant();
    mSequencer.vtable = (void**)g_13eb938;
    vtable = (void**)g_13ec458;
    if (flags & 1)
        MultiHeapDelete(this);
    return this;
}
}
