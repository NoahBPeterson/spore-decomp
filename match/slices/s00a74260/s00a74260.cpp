// Slice s00a74260: EA::Swarm::cEffectsManagerCheat::Execute (0x00a74260), the "effects" console cheat.
// It parses the command line and then runs every sub-command whose option bit is set in mOptionBits:
// listing worlds/effects/collections, stopping effects, toggling global params, loading collections.
// Class/field/method names other than Execute, ArgScript::Output/Sprintf and cArgumentSpec::Parse are
// Claude-coined from the format strings and call shapes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the locals with dtors get no EH frame).
#include "types.h"

extern "C" void* __cdecl memset(void* p, int c, unsigned int n);                // 0x011e073e
#pragma function(memset)

void operator delete[](void* p);                                                  // 0x00f47380

namespace EA { namespace ArgScript {
struct ArgParser;
struct Line;
void __cdecl Output(ArgParser* parser, const char* fmt, ...);                     // 0x00841000
} }
using EA::ArgScript::ArgParser;
using EA::ArgScript::Output;

// ---- eastl::string (16 bytes, empty string points at gEmptyString) ----
extern char gEmptyString[];                                                      // 0x01667bac
struct EAString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    EAString() { mpBegin = mpEnd = gEmptyString; mpCapacity = gEmptyString + 1; }
    ~EAString() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(char* p) { if (p) operator delete[](p); }
    const char* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
namespace EA { namespace ArgScript {
void __cdecl Sprintf(EAString* out, const char* fmt, ...);                        // 0x00840c20
} }

// ArgScript enum table lookup: returns the name whose value matches, or 0.
struct EnumName { const char* mpName; int mValue; };
const char* __cdecl GetEnumName(int value, const EnumName* table);               // 0x00840810
extern const EnumName kWorldStateNames[];                                         // 0x01554938 (active, paused, ...)
extern const char* const kComponentTypeNames[];                                   // 0x01456334 (kFXCmptVisualEffect, ...)
extern const char kAllWorlds[];                                                   // 0x01401b58 "*"

bool __cdecl OpenEffectFile(const char* path);                                    // 0x00a72f70

// ---- effects ----
struct cEffectStats {                       // 0x4c bytes, filled by IEffectStats::GetStats
    int m00;
    int mNumEffects;                        // +0x04
    int mNumComponents;                     // +0x08
    int m0c;
    int mNumQuads;                          // +0x10 (column "quad")
    int m14;
    int mNumModels;                         // +0x18
    int m1c;
    int m20;
    int mNumMeta;                           // +0x24 (column "meta")
    int mNumDecals;                         // +0x28
    int m2c;
    int mNumRibbons;                        // +0x30
    int pad[(0x4c - 0x34) / 4];
};
struct IEffectStats {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void GetStats(float t, float dt, cEffectStats* stats);               // +0x14
};
struct cVisualEffect {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Stop(int hard);                                                  // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool IsPaused();                                                      // +0x34
    virtual bool IsHidden();                                                      // +0x38
    IEffectStats mStats;                                                          // +0x04
    char pad8[0x10 - 8];
    int mRefCount;                                                                // +0x10
    char pad14[0x2c - 0x14];
    uint32_t mFlags;                                                              // +0x2c
    bool HasFlag(int bit) const { return (mFlags >> bit) & 1; }
};

struct cEffectInfo {                        // 0x24 bytes
    EAString mName;                         // +0x00
    EAString mDescription;                  // +0x10
    cVisualEffect* mpEffect;                // +0x20
    ~cEffectInfo();                                                               // 0x007e1a80
};
cEffectInfo* __cdecl CopyEffectInfos(cEffectInfo* first, cEffectInfo* last, cEffectInfo* dest);   // 0x00a6d8c0

struct EffectAllocator {
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};
// eastl::vector<cEffectInfo>
struct EffectList {
    cEffectInfo* mpBegin;
    cEffectInfo* mpEnd;
    cEffectInfo* mpCapacity;
    EffectAllocator mAllocator;
    EffectList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~EffectList() {
        DoDestroyValues(mpBegin, mpEnd);
        DoFree(mpBegin);
    }
    void DoDestroyValues(cEffectInfo* first, cEffectInfo* last);                 // 0x007e2be0
    void DoFree(cEffectInfo* p) { if (p) mAllocator.deallocate(p); }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cEffectInfo* erase(cEffectInfo* first, cEffectInfo* last) {
        cEffectInfo* const pPosition = CopyEffectInfos(last, mpEnd, first);
        DoDestroyValues(pPosition, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// GetEffectFile result: two strings and a ref-counted object.
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
struct cEffectFileInfo {
    EAString mName;
    EAString mPath;
    IRefCounted* mpObject;
    cEffectFileInfo() : mpObject(0) {}
    ~cEffectFileInfo() { if (mpObject) mpObject->Release(); }
};

// ---- worlds (eastl::hash_map<uint32_t, cEffectsWorld*>) ----
struct cEffectsWorld {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void SetTarget(int v);                                                // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void GetEffects(EffectList* out, const char* filter, int mode);       // +0x44
    char pad4[0x20 - 4];
    int mState;                                                                   // +0x20
    char pad24[0x90 - 0x24];
    int mNumEffects;                                                              // +0x90
};
struct WorldNode {
    uint32_t mKey;
    cEffectsWorld* mpWorld;
    WorldNode* mpNext;
};
struct WorldIterator {
    WorldNode* mpNode;
    WorldNode** mpBucket;
    WorldIterator(WorldNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    bool operator!=(const WorldIterator& x) const { return mpNode != x.mpNode; }
};
struct WorldTable {
    uint32_t m0;
    WorldNode** mpBucketArray;                                                    // +0x04
    uint32_t mnBucketCount;                                                       // +0x08
    WorldIterator begin() {
        WorldIterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    WorldIterator end() { return WorldIterator(mpBucketArray + mnBucketCount); }
};

// ---- collections ----
struct PtrVector {                          // eastl::vector<T*>, 0x14 bytes
    void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct cEffectDescription { char data[0x58]; };
struct DescVector {                         // eastl::vector<cEffectDescription>
    cEffectDescription* mpBegin; cEffectDescription* mpEnd; cEffectDescription* mpCapacity; uint32_t mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct cCollection {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual bool IsCompiled();                                                    // +0x38
    char pad4[0xc - 4];
    PtrVector* mComponentDescriptions;                                            // +0x0c (begin of a vector<PtrVector>)
    char pad10[0x34 - 0x10];
    DescVector mEffectDescriptions;                                               // +0x34
};
// eastl::vector<cCollection*>
struct CollectionVector {
    cCollection** mpBegin;
    cCollection** mpEnd;
    cCollection** mpCapacity;
    uint32_t mAlloc[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    cCollection*& operator[](int i) { return mpBegin[i]; }
};
struct ResourceKey { uint32_t mInstance, mGroup; };
struct cCollectionDirectory {
    virtual void v0(); virtual void v1();
    virtual bool FindKey(int type, const char* name, ResourceKey* key);           // +0x08
};
struct IResource;
struct cResourceCache {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual IRefCounted* GetResource(ResourceKey key);                            // +0x10
};

struct cEffectsManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual cResourceCache* GetResourceCache();                                   // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual void SetQuality(float q, int which);                                  // +0x38
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void StartRecording(int id, const char* source);                      // +0x4c
    virtual void StopRecording(int id);                                           // +0x50
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void LoadCollection(IRefCounted* c);                                  // +0x64
    virtual bool UnloadCollection(IRefCounted* c);                                // +0x68
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
    virtual void v37();
    virtual void SetDebugMode(int mode, bool on);                                 // +0x98
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual const char* GetStatusString();                                        // +0xac
    virtual void v44();
    virtual void GetEffects(EffectList* out, const char* world, bool all);        // +0xb4
    virtual bool GetEffectFile(cEffectFileInfo* out, const char* world);          // +0xb8
    virtual void GetEffectNames(EffectList* out, const char* world);              // +0xbc
    char pad4[0x2c - 4];
    CollectionVector mCollections;                                                // +0x2c
    char pad40[0x48 - 0x40];
    cCollectionDirectory* mpDirectory;                                            // +0x48
    char pad4c[0x1e0 - 0x4c];
    uint8_t mParams[3];                                                           // +0x1e0
    char pad1e3[0x1e8 - 0x1e3];
    uint8_t mParam1e8;                                                            // +0x1e8
    char pad1e9[0x224 - 0x1e9];
    WorldTable mWorlds;                                                           // +0x224
    char pad230[0x244 - 0x230];
    cEffectsWorld* mpDefaultWorld;                                                // +0x244
    void StopAllEffects();                                                        // 0x00a6d480
    cEffectsWorld* FindWorld(const char* name);                                   // 0x00a6d840
};

namespace EA { namespace ArgScript {
struct cArgumentSpec {
    void Parse(const Line& line, ArgParser* parser);                              // 0x0083b9d0
};
} }

namespace EA { namespace Swarm {
class cEffectsManagerCheat {
public:
    virtual void v0();
    void Execute(const EA::ArgScript::Line& line);
    bool IsSet(int bit) const { return (mOptionBits >> bit) & 1; }

    ArgParser* mpParser;                    // +0x04
    char pad8[0x10 - 8];
    cEffectsManager* mpManager;             // +0x10
    EA::ArgScript::cArgumentSpec mArgSpec;  // +0x14
    char pad15[0x84 - 0x15];
    uint32_t mOptionBits;                   // +0x84
    char pad88[0xdc - 0x88];
    const char* mpWorldName;                // +0xdc
    uint8_t mParams[4];                     // +0xe0
    int mDebugMode;                         // +0xe4
    bool mDebugOn;                          // +0xe8
    float mQuality;                         // +0xec
    int mTarget;                            // +0xf0
    int mRecordId;                          // +0xf4
    const char* mpSource;                   // +0xf8
    const char* mpCollectionName;           // +0xfc
};

// @ 0x00a74260
void cEffectsManagerCheat::Execute(const EA::ArgScript::Line& line)
{
    mpWorldName = 0;
    mpCollectionName = 0;
    mRecordId = 0;
    mpSource = 0;
    mArgSpec.Parse(line, mpParser);

    if (IsSet(0))
        Output(mpParser, "%s\n", mpManager->GetStatusString());

    if (IsSet(3) || IsSet(4)) {
        EffectList effects;
        int mode = 0;
        if (IsSet(5))
            mode = 1;
        if (IsSet(6))
            mode = 2;
        WorldIterator it = mpManager->mWorlds.begin();
        WorldIterator itEnd = mpManager->mWorlds.end();
        for (; it != itEnd; it.increment()) {
            cEffectsWorld* world = it.mpNode->mpWorld;
            if (world->mState != 0 && !IsSet(4))
                continue;
            effects.clear();
            world->GetEffects(&effects, mpWorldName, mode);
            if (effects.mpBegin != effects.mpEnd || IsSet(4)) {
                Output(mpParser, "world 0x%08x [%s]%s:\n", it.mpNode->mKey,
                       GetEnumName(world->mState, kWorldStateNames),
                       world != mpManager->mpDefaultWorld ? "" : " [default]");
                Output(mpParser, " %-60.60s  %-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "effect name",
                       "sim_ms", "effects", "cmpts", "meta", "quad", "model", "decal", "ribbon");
            }
            for (uint32_t i = 0; i < effects.size(); i++) {
                cVisualEffect* effect = effects.mpBegin[i].mpEffect;
                cEffectStats stats;
                memset(&stats, 0, sizeof(stats));
                effect->mStats.GetStats(0.0f, 0.0f, &stats);
                const char* paused = "";
                const char* hidden = "";
                const char* stopping = "";
                const char* orphan = "";
                const char* kind = "";
                if (effect->IsPaused())
                    paused = "[Paused]";
                if (effect->IsHidden())
                    hidden = "[Hidden]";
                if (effect->HasFlag(10))
                    stopping = "[Stopping]";
                if (effect->mRefCount <= 2)
                    orphan = "[Orphan]";
                if (effect->HasFlag(6))
                    kind = "[Internal]";
                else if (effect->HasFlag(5))
                    kind = "[Child]";
                Output(mpParser, "  %-60.60s %1.3f %5d %5d %5d %5d %5d %5d %5d %s%s%s%s%s\n",
                       effects.mpBegin[i].mName.c_str(), 0.0, stats.mNumEffects, stats.mNumComponents,
                       stats.mNumMeta, stats.mNumQuads, stats.mNumModels, stats.mNumDecals, stats.mNumRibbons,
                       paused, hidden, stopping, orphan, kind);
            }
        }
    }

    if (IsSet(7) || IsSet(8)) {
        bool verbose = IsSet(8);
        EffectList effects;
        mpManager->GetEffectNames(&effects, mpWorldName);
        for (uint32_t i = 0; i < effects.size(); i++) {
            Output(mpParser, " %s\n", effects.mpBegin[i].mName.c_str());
            if (verbose && !effects.mpBegin[i].mDescription.empty())
                Output(mpParser, "    %s\n", effects.mpBegin[i].mDescription.c_str());
        }
        if (effects.size() > 1)
            Output(mpParser, "%d total effects\n", effects.size());
    }

    if (IsSet(9)) {
        cEffectFileInfo info;
        if (mpManager->GetEffectFile(&info, mpWorldName) && !info.mPath.empty() &&
            !OpenEffectFile(info.mPath.c_str()))
            Output(mpParser, "Couldn't open '%s'\n", info.mPath.c_str());
    }

    if (IsSet(1)) {
        if (mpWorldName == 0)
            mpManager->StopAllEffects();
        else {
            EffectList effects;
            mpManager->GetEffects(&effects, mpWorldName, true);
            for (uint32_t i = 0; i < effects.size(); i++)
                effects.mpBegin[i].mpEffect->Stop(1);
        }
    }

    if (IsSet(2)) {
        if (mpWorldName == 0)
            mpManager->StopAllEffects();
        else {
            EffectList all;
            EffectList inWorld;
            mpManager->GetEffects(&all, kAllWorlds, true);
            mpManager->GetEffects(&inWorld, mpWorldName, true);
            for (uint32_t i = 0; i < all.size(); i++) {
                bool found = false;
                for (uint32_t j = 0; j < inWorld.size(); j++) {
                    if (all.mpBegin[i].mpEffect == inWorld.mpBegin[j].mpEffect) {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    all.mpBegin[i].mpEffect->Stop(1);
            }
        }
    }

    if (IsSet(25))
        mpManager->mParams[0] = mParams[0];
    if (IsSet(26))
        mpManager->mParams[1] = mParams[1];
    if (IsSet(27))
        mpManager->mParams[2] = mParams[2];
    if (IsSet(24))
        mpManager->mParam1e8 = mParams[3];
    if (IsSet(12))
        mpManager->SetDebugMode(mDebugMode, mDebugOn);
    if (IsSet(13))
        mpManager->SetQuality(mQuality, 5);

    if (IsSet(15)) {
        WorldIterator it = mpManager->mWorlds.begin();
        WorldIterator itEnd = mpManager->mWorlds.end();
        for (; it != itEnd; it.increment()) {
            cEffectsWorld* world = it.mpNode->mpWorld;
            Output(mpParser, "world 0x%08x, %d effects, %s %s\n", it.mpNode->mKey, world->mNumEffects,
                   GetEnumName(world->mState, kWorldStateNames),
                   world != mpManager->mpDefaultWorld ? "" : "[default]");
        }
    }

    if (IsSet(11)) {
        cEffectsWorld* world = mpManager->FindWorld(mpSource);
        if (world)
            world->SetTarget(mTarget);
    }
    if (IsSet(16))
        mpManager->StartRecording(mRecordId, mpSource ? mpSource : "CommandLine");
    if (IsSet(17))
        mpManager->StopRecording(mRecordId);

    if (IsSet(18)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i]) {
                for (int type = 0; type < 64; type++) {
                    uint32_t count;
                    if (type >= 1)
                        count = mpManager->mCollections[i]->mComponentDescriptions[type - 1].size();
                    else if (type == 0)
                        count = mpManager->mCollections[i]->mEffectDescriptions.size();
                    else
                        count = 0;
                    if (count > 0) {
                        if ((uint32_t)type < 15)
                            Output(mpParser, "%-20.20s descriptions = %4d\n", kComponentTypeNames[type], count);
                        else
                            Output(mpParser, "cmpt%02d               descriptions = %4d\n", type, count);
                    }
                }
            }
        }
    }

    if (IsSet(19)) {
        EAString s;
        EA::ArgScript::Sprintf(&s, "Manager version: %d,  Script version: %d", 1, 1);
        Output(mpParser, "%s\n", s.c_str());
    }

    if (IsSet(20)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i] && mpManager->mCollections[i]->IsCompiled())
                Output(mpParser, "compiled 0x%08x\n", mpManager->mCollections[i]);
        }
    }

    if (IsSet(21)) {
        ResourceKey key;
        if (mpManager->mpDirectory && mpManager->mpDirectory->FindKey(0x11, mpCollectionName, &key)) {
            IRefCounted* collection = mpManager->GetResourceCache()->GetResource(key);
            if (collection) {
                collection->AddRef();
                mpManager->LoadCollection(collection);
                collection->Release();
            } else
                Output(mpParser, "Couldn't load effect collection: %s\n", mpCollectionName);
        } else
            Output(mpParser, "No such collection: %s\n", mpCollectionName);
    }

    if (IsSet(22)) {
        ResourceKey key;
        if (mpManager->mpDirectory && mpManager->mpDirectory->FindKey(0x11, mpCollectionName, &key)) {
            IRefCounted* collection = mpManager->GetResourceCache()->GetResource(key);
            if (collection) {
                collection->AddRef();
                if (!mpManager->UnloadCollection(collection))
                    Output(mpParser, "Collection not loaded: %s\n", mpCollectionName);
                collection->Release();
            } else
                Output(mpParser, "Couldn't unload collection: %s\n", mpCollectionName);
        } else
            Output(mpParser, "No such collection: %s\n", mpCollectionName);
    }

    if (IsSet(23)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i])
                Output(mpParser, "collection 0x%08x\n", mpManager->mCollections[i]);
        }
    }
}
} }
