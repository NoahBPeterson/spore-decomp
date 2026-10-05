// Slice s006aa3f0 — SP::cPropertyManager property-name registration and related helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>

// ===========================================================================
// EASTL support types
// ===========================================================================

// eastl::basic_string<char> (16 bytes)
struct StrKey {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void* mAllocator;   // +0xc

    void assign(const char* first, const char* last);                 // 0x00454cb0
    void assign(const char* s) { assign(s, s + strlen(s)); }
};

// keyed hashtables (declared only: calls stay out-of-line like the original instantiations)
struct MapNameToID {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    int& operator[](const StrKey& key);       // 0x006a8340
};

struct MapIDToName {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    StrKey* operator[](const uint32_t& key);  // 0x006a8410
};

struct Vec32 {
    uint32_t* mpBegin;     // +0
    uint32_t* mpEnd;       // +4
    uint32_t* mpCapacity;  // +8

    void DoInsertValue(uint32_t* pos, const uint32_t* value);  // 0x004558a0
};

void EA_MakeCaseInsensitive(const char* src, StrKey* dst);   // 0x00840cc0

// ===========================================================================
// SP::cPropertyManager (retail member offsets; dev PDB shifted by +4 in places)
// ===========================================================================
struct cPropertyManager {
    char pad00[0x94];
    MapNameToID mPropertyNameToIDMap;      // +0x94
    char pad01[0x14];
    MapIDToName mPropertyIDToNameMap;      // +0xb4
    char pad02[0x14];
    MapNameToID mGroupNameToIDMap;         // +0xd4
    char pad03[0x14];
    MapIDToName mGroupIDToNameMap;         // +0xf4
    char pad04[0x14];
    Vec32 mGroupIDs;                       // +0x114
    char pad05[8];
    MapNameToID mLocalPropertyNameToIDMap; // +0x128
    char pad06[0x14];
    MapIDToName mLocalPropertyIDToNameMap; // +0x148
    char pad07[0x14];
    StrKey mLCName;                        // +0x168

    void RegisterPropertyName(const char* name, uint32_t id);
    void RegisterPropertyNameLocal(const char* name, uint32_t id);
    void Fun_006aa450(const char* name, uint32_t id);
    uint32_t Shutdown();
    void ParseAndAddProperty(uint32_t id, uint32_t arg2, uint32_t arg3);
};

// @ 0x006aa3f0
void cPropertyManager::RegisterPropertyName(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa5e0
void cPropertyManager::RegisterPropertyNameLocal(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mLocalPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mLocalPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa450
void cPropertyManager::Fun_006aa450(const char* name, uint32_t id)
{
    StrKey* s = mGroupIDToNameMap[id];
    s->assign(name);

    uint32_t* end = mGroupIDs.mpEnd;
    if (end < mGroupIDs.mpCapacity) {
        mGroupIDs.mpEnd = end + 1;
        if (end)
            *end = id;
    } else {
        mGroupIDs.DoInsertValue(end, &id);
    }
}

// @ 0x006aa7c0
uint32_t cPropertyManager::Shutdown()
{
    // TODO(partial): unregister from the message server/resource manager, unregister the
    // listProps/prop cheats, release mLine and tear down all property maps/vectors.
    return 1;
}

// @ 0x006aaa10
// SP::cPropertyManager::ParseAndAddProperty (partial)
void FUN_006aaa10(void* self, uint32_t id, uint32_t arg2, uint32_t arg3)
{
    // TODO(partial): parse a property line and add it to the base property list.
    (void)self; (void)id; (void)arg2; (void)arg3;
}

// ===========================================================================
// `anonymous namespace'::cPropertyCommand::Parse
// ===========================================================================
struct cPropertyCommand {
    char pad0[4];
    uint32_t mArg3;                 // +4
    char pad8[4];
    cPropertyManager* mManager;     // +0xc
    uint32_t mArg4;                 // +0x10

    bool Parse(void** param_2);
};

// @ 0x006aadb0
bool cPropertyCommand::Parse(void** param_2)
{
    mManager->ParseAndAddProperty(*(uint32_t*)param_2, mArg3, mArg4);
    return true;
}

// ===========================================================================
// Remaining slice functions (partial)
// ===========================================================================

// @ 0x006aa4c0
// eastl::rbtree<unsigned int, pair<const unsigned int, EA::Variant>>::insert
void FUN_006aa4c0(void* self, uint32_t key, int value)
{
    // TODO(partial): rbtree insert (find/yrotate/alloc node, copy EA::Variant).
    (void)self; (void)key; (void)value;
}

// `anonymous namespace'::cPropertyCommand::Execute
struct cPropertyCommandExec {
    void Execute(void* args);
};

// @ 0x006aa640
void cPropertyCommandExec::Execute(void* args)
{
    // TODO(partial): parse the command line, look the property up and print/set it.
    (void)args;
}

// @ 0x006aa780
void FUN_006aa780(void* self, void* args)
{
    // TODO(partial): group-name command handler (MainArguments + manager id/name maps).
    (void)self; (void)args;
}

// @ 0x006aa910
uint8_t FUN_006aa910(void* self, uint32_t arg2, int* arg3)
{
    // TODO(partial): append 0xc-stride entries into the bool vector and return non-empty.
    (void)self; (void)arg2; (void)arg3;
    return 0;
}

// @ 0x006aae30
void FUN_006aae30(void* self)
{
    // TODO(partial): ~rbtree<unsigned int, pair<const unsigned int, EA::Variant>>.
    (void)self;
}

// @ 0x006ab120
char FUN_006ab120(void* self, int* arg2, int* arg3)
{
    // TODO(partial): SP::cPropertyManager::ReadResource.
    (void)self; (void)arg2; (void)arg3;
    return 0;
}
