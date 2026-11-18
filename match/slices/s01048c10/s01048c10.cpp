// Slice s01048c10 -- SP::cStarMap::FilterHelperRebuild.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cStarMap {
    uint8_t mPad00;                                          // +0x00
    uint8_t mRequestZoom;                                    // +0x01
    uint8_t mPad02[2];                                       // +0x02 .. +0x03
    int32_t mFilterStates[8];                                // +0x04 ..

    void FilterHelperRebuild(int32_t index);                 // 0x01048c10
    bool FilterEnabled(int32_t index);                       // inlined predicate
    void FilterHelperLayer(int32_t index, bool value);       // 0x01044a10
    void FilterHelperSpecial(bool value);                    // 0x01044df0
    void FilterHelperAdd(uint32_t which);                    // 0x01048aa0
    void FilterHelperRemove(int32_t index);                  // 0x01045c30
    void FilterHelper(int32_t index, int32_t mode);          // 0x01048b40
};

} // namespace SP

__forceinline bool SP::cStarMap::FilterEnabled(int32_t index)
{
    if (index < 0)
        return false;
    if ((uint32_t)index > 7)
        return false;
    return mFilterStates[index] == 1;
}

__forceinline void SP::cStarMap::FilterHelper(int32_t index, int32_t mode)
{
    const int32_t kFilterOff = 0;
    const int32_t kFilterOn = 1;
    const int32_t kFilterOnPreview = 3;
    const int32_t kFilterOffPreview = 4;

    bool changed = false;

    switch (mode) {
    case kFilterOff:
        if (mFilterStates[index] == kFilterOnPreview) {
            changed = true;
            mode = kFilterOn;
        }
        break;
    case kFilterOn:
        changed = true;
        if (mFilterStates[index] == kFilterOnPreview)
            mode = kFilterOnPreview;
        break;
    case 2:
        changed = true;
        if (mFilterStates[index] == kFilterOff) {
            mode = kFilterOffPreview;
        } else if (mFilterStates[index] == kFilterOn) {
            mode = kFilterOnPreview;
        } else {
            return;
        }
        break;
    }

    int32_t oldState = mFilterStates[index];
    mFilterStates[index] = mode;

    if (index >= 0) {
        if (index > 1) {
            if (index == 5)
                FilterHelperSpecial(changed);
        } else {
            FilterHelperLayer(index, changed);
        }
    }

    if (changed) {
        if (oldState == kFilterOff)
            FilterHelperAdd((uint32_t)index);
    } else {
        FilterHelperRemove(index);
    }
}

// @ 0x01048c10
void SP::cStarMap::FilterHelperRebuild(int32_t index)
{
    if (!FilterEnabled(index))
        return;

    FilterHelper(index, 0);
    FilterHelper(index, 1);
}
