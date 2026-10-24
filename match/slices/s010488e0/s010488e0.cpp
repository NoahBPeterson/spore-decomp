// Slice s010488e0 -- SP::cStarMap helper rebuild (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cStarMap {
    uint8_t mPad00;                                          // +0x00
    uint8_t mRequestZoom;                                    // +0x01
    uint8_t mPad02[2];                                       // +0x02 .. +0x03
    int32_t mFilterStates[8];                                // +0x04 ..

    void FilterHelperRebuild(uint32_t index);                // 0x01048c10
    void FilterHelper();                                     // 0x01047000
    void FilterHelperRebuildAll();
    void FilterHelperAdd(uint32_t which);
    void FilterHelperEmpires(uint32_t which);                // 0x01047850
    void FilterHelperRelationships(uint32_t which);          // 0x01047440
    void FilterHelperVisited(uint32_t which);                // 0x01045f90
    void FilterHelperWormholes(uint32_t which);              // 0x010463b0
    void FilterHelperTravelTrail(uint32_t which);            // 0x01045c80
    void FilterHelperHome(uint32_t which);                   // 0x010488e0
    void FilterHelperSeti(uint32_t which);                   // 0x01046160
    void Helper468f0(uint32_t which);                        // 0x010468f0
    void Helper47300(uint32_t which);                        // 0x01047300
    void FilterHelperLayer(int32_t index, uint32_t value);   // 0x01044a10
    void FilterHelperSpecial(uint32_t value);                // 0x01044df0
    void FilterHelperRemove(int32_t index);                  // 0x01045c30
    void FilterHelper(int32_t index, int32_t mode);
};

} // namespace SP

extern "C" void GetUniverseContext();                        // 0x01021080 (thiscall)

// @ 0x01048aa0
void SP::cStarMap::FilterHelperAdd(uint32_t which)
{
    mRequestZoom = 1;
    switch (which) {
    case 0:
        FilterHelperEmpires(0);
        return;
    case 1:
        FilterHelperEmpires(1);
        return;
    case 2:
        FilterHelperRelationships(2);
        return;
    case 3:
        FilterHelperVisited(3);
        FilterHelperWormholes(3);
        return;
    case 4:
        FilterHelperTravelTrail(4);
        return;
    case 5:
        Helper468f0(5);
        return;
    case 6:
        FilterHelperHome(6);
        Helper47300(6);
        FilterHelperSeti(6);
        return;
    }
}

// @ 0x01048b40
void SP::cStarMap::FilterHelper(int32_t index, int32_t mode)
{
    const int32_t kFilterOff = 0;
    const int32_t kFilterOn = 1;
    const int32_t kFilterPreview = 2;
    const int32_t kFilterOnPreview = 3;
    const int32_t kFilterOffPreview = 4;

    bool changed = false;
    uint32_t value = 0;

    switch (mode) {
    case kFilterOff:
        if (mFilterStates[index] == kFilterOnPreview) {
            changed = true;
            value = 1;
            mode = kFilterOn;
        }
        break;
    case kFilterOn:
        changed = true;
        value = 1;
        if (mFilterStates[index] == kFilterOnPreview)
            mode = kFilterOnPreview;
        break;
    case kFilterPreview:
        changed = true;
        value = 1;
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
        if (index <= 1)
            FilterHelperLayer(index, value);
        else if (index == 5)
            FilterHelperSpecial(value);
    }

    if (changed) {
        if (oldState == kFilterOff)
            FilterHelperAdd((uint32_t)index);
    } else {
        FilterHelperRemove(index);
    }
}

// @ 0x01048ce0
void SP::cStarMap::FilterHelperRebuildAll()
{
    if (((void* (__thiscall*)(SP::cStarMap*))GetUniverseContext)(this)) {
        for (uint32_t i = 0; i < 7; ++i)
            FilterHelperRebuild(i);
        FilterHelper();
    }
}
