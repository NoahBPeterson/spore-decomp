// SP::GetRelationshipEvents: lazily fills a global vector<uint32_t> of event ids.
#include "types.h"

struct IdVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void reserve(int n);                          // FUN_00d01790
    void DoInsertValue(uint32_t* pos, const uint32_t& v);  // FUN_00b96600
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCapacity) { uint32_t* p = mpEnd++; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};

extern IdVec gRelationshipEvents;  // 0x169d410

// @ 0x00d026d0
IdVec* GetRelationshipEvents()
{
    uint32_t id;
    if (gRelationshipEvents.mpBegin == gRelationshipEvents.mpEnd) {
        gRelationshipEvents.reserve(0x40);
        id = 0x526e4e5; gRelationshipEvents.push_back(id);
        id = 0x526e4ee; gRelationshipEvents.push_back(id);
        id = 0x526e4f2; gRelationshipEvents.push_back(id);
        id = 0x526e4f5; gRelationshipEvents.push_back(id);
        id = 0x526e4f8; gRelationshipEvents.push_back(id);
        id = 0x526e4fb; gRelationshipEvents.push_back(id);
        id = 0x526e4fe; gRelationshipEvents.push_back(id);
        id = 0x526e501; gRelationshipEvents.push_back(id);
        id = 0x526e504; gRelationshipEvents.push_back(id);
        id = 0x526e50a; gRelationshipEvents.push_back(id);
        id = 0x526e50e; gRelationshipEvents.push_back(id);
        id = 0x526e512; gRelationshipEvents.push_back(id);
        id = 0x5adb0aa; gRelationshipEvents.push_back(id);
        id = 0x5776d99; gRelationshipEvents.push_back(id);
        id = 0x5da8036; gRelationshipEvents.push_back(id);
        id = 0x530cf00; gRelationshipEvents.push_back(id);
        id = 0x530cf01; gRelationshipEvents.push_back(id);
        id = 0x530cf02; gRelationshipEvents.push_back(id);
        id = 0x530cf03; gRelationshipEvents.push_back(id);
        id = 0x530cf04; gRelationshipEvents.push_back(id);
        id = 0x530cf05; gRelationshipEvents.push_back(id);
        id = 0x530cf06; gRelationshipEvents.push_back(id);
        id = 0x530cf07; gRelationshipEvents.push_back(id);
        id = 0x530cf08; gRelationshipEvents.push_back(id);
        id = 0x530cf09; gRelationshipEvents.push_back(id);
        id = 0x530cf0a; gRelationshipEvents.push_back(id);
        id = 0x530cf0b; gRelationshipEvents.push_back(id);
        id = 0x54eab4b3; gRelationshipEvents.push_back(id);
        id = 0x526e519; gRelationshipEvents.push_back(id);
        id = 0x526e51c; gRelationshipEvents.push_back(id);
        id = 0x526e51d; gRelationshipEvents.push_back(id);
        id = 0x526e51e; gRelationshipEvents.push_back(id);
        id = 0x526e51f; gRelationshipEvents.push_back(id);
        id = 0x526e521; gRelationshipEvents.push_back(id);
        id = 0x526e524; gRelationshipEvents.push_back(id);
        id = 0x5f8a1ad; gRelationshipEvents.push_back(id);
        id = 0x526e527; gRelationshipEvents.push_back(id);
        id = 0x526e52a; gRelationshipEvents.push_back(id);
        id = 0x667af08; gRelationshipEvents.push_back(id);
        id = 0x526e52d; gRelationshipEvents.push_back(id);
        id = 0x526e531; gRelationshipEvents.push_back(id);
        id = 0x526e535; gRelationshipEvents.push_back(id);
        id = 0x526e537; gRelationshipEvents.push_back(id);
        id = 0x526e53c; gRelationshipEvents.push_back(id);
        id = 0x526e542; gRelationshipEvents.push_back(id);
        id = 0x526e545; gRelationshipEvents.push_back(id);
        id = 0x526e56a; gRelationshipEvents.push_back(id);
        id = 0x526e5cf; gRelationshipEvents.push_back(id);
        id = 0x526e5d4; gRelationshipEvents.push_back(id);
        id = 0x526e5d8; gRelationshipEvents.push_back(id);
        id = 0x526e5dc; gRelationshipEvents.push_back(id);
        id = 0x526e5f3; gRelationshipEvents.push_back(id);
        id = 0x55165f5; gRelationshipEvents.push_back(id);
        id = 0x5590199; gRelationshipEvents.push_back(id);
        id = 0x55901b3; gRelationshipEvents.push_back(id);
        id = 0x5661a77; gRelationshipEvents.push_back(id);
        id = 0x5661a7c; gRelationshipEvents.push_back(id);
        id = 0x577909a; gRelationshipEvents.push_back(id);
        id = 0x577909b; gRelationshipEvents.push_back(id);
        id = 0x57b9100; gRelationshipEvents.push_back(id);
        id = 0x57b4514; gRelationshipEvents.push_back(id);
        id = 0x57e4fe3; gRelationshipEvents.push_back(id);
        id = 0x580e23b; gRelationshipEvents.push_back(id);
        id = 0x591f833; gRelationshipEvents.push_back(id);
        id = 0x594afff; gRelationshipEvents.push_back(id);
        id = 0x594b017; gRelationshipEvents.push_back(id);
        id = 0x5b6fcc9; gRelationshipEvents.push_back(id);
        id = 0x5b6fcd4; gRelationshipEvents.push_back(id);
        id = 0x5b942d0; gRelationshipEvents.push_back(id);
        id = 0x5b6cf09; gRelationshipEvents.push_back(id);
        id = 0x5f62736; gRelationshipEvents.push_back(id);
        id = 0x5b6ce81; gRelationshipEvents.push_back(id);
        id = 0x526e5f4; gRelationshipEvents.push_back(id);
        id = 0x5ff85b3; gRelationshipEvents.push_back(id);
        id = 0x5ff85b2; gRelationshipEvents.push_back(id);
        id = 0x601df2a; gRelationshipEvents.push_back(id);
        id = 0x68b2938; gRelationshipEvents.push_back(id);
        id = 0x68b2971; gRelationshipEvents.push_back(id);
    }
    return &gRelationshipEvents;
}
