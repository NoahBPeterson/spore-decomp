// Slice s00e5ae80: when a scene object's computed value is non-zero, look up its layer entry and
// select it in the level's list.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct SceneObject {
    void* m_vtbl;                               // +0x000
    char pad04[0xfc - 0x04];
    int mReady;                                 // +0x0fc
    char pad100[0x248 - 0x100];
    int mLoaded;                                // +0x248
};

struct cLayerRef00 {
    int mField00;                               // +0x00
    int mField04;                               // +0x04
    int mField08;                               // +0x08
};
typedef char cLayerRef00_size_check[(sizeof(cLayerRef00) == 0xc) ? 1 : -1];

struct cLayerEntry24 {
    char pad00[0x190];
    int mList;                                  // +0x190
};
typedef char cLayerEntry24_size_check[(sizeof(cLayerEntry24) > 0x190) ? 1 : -1];

struct cLayerHit {
    char pad00[0x24];
    cLayerEntry24* mEntry;                      // +0x24
};
typedef char cLayerHit_size_check[(sizeof(cLayerHit) == 0x28) ? 1 : -1];

struct cLayerHolder {
    char pad00[0xc0];
    int mId;                                    // +0xc0
};
typedef char cLayerHolder_size_check[(sizeof(cLayerHolder) == 0xc4) ? 1 : -1];

struct cLevelLookup {
    char pad00[0x168];
};

float FUN_00e5add0(SceneObject* o);              // 0x00e5add0

void __fastcall FUN_00743b50(cLayerRef00* ref, void* edx);  // 0x00743b50, ctor of the ref pair
cLayerHolder* __cdecl FUN_00e4ce40(cLayerRef00* ref);   // 0x00e4ce40
void __cdecl FUN_00e50b80(int* base, int* count, int* key, float* value);  // 0x00e50b80
cLayerHit* __cdecl FUN_00b72210(cLevelLookup* lookup, int id);  // 0x00b72210
void __fastcall FUN_00e82130(cLayerRef00* ref, void* edx);  // 0x00e82130, dtor of the ref pair

extern int gList_16b39e0;                        // 0x016b39e0
extern int gCap_16b3c18;                         // 0x016b3c18
extern cLevelLookup* gpLookup_16b3c08;           // 0x016b3c08

// @ 0x00e5ae80
void __cdecl FUN_00e5ae80(float value, SceneObject* o)
{
    if (FUN_00e5add0(o) == 0.0f)
        return;

    cLayerRef00 ref;
    FUN_00743b50(&ref, 0);
    cLayerHolder* pHolder = FUN_00e4ce40(&ref);
    float fEntry[2];
    fEntry[0] = 0.0f;
    fEntry[1] = value;
    FUN_00e50b80(&gList_16b39e0, &gCap_16b3c18, &pHolder->mId, fEntry);

    if (o->mLoaded != 0 && o->mReady != 0) {
        cLayerHit* pHit = FUN_00b72210(&gpLookup_16b3c08[0], pHolder->mId);
        cLayerEntry24* pEntry = pHit->mEntry;
        if (pEntry != 0) {
            int list = pEntry->mList;
            void** vtbl = *(void***)list;
            ((void (__thiscall*)(int, int, int))vtbl[0x40 / 4])(list, 0, 1);
        }
    }
    FUN_00e82130(&ref, 0);
}
