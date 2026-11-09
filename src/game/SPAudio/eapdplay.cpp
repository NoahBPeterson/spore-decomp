// src/game/SPAudio/eapdplay.cpp -- migrated from slice(s) s00a53f90, s00a52ff0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdplay.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00a52ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
class Allocator { public:
    virtual ~Allocator() {}                       // +0x00
    virtual void  v04();                          // +0x04
    virtual void* v08(uint32_t n);                // +0x08
    virtual void  v0c(void* p);                   // +0x0c
    void* mpCoreAllocator;                        // +0x04
    void* mpNamePtr;                              // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedPool { public:
    Allocator mInitAllocator;                     // +0x00
    Allocator mOverflowAllocator;                 // +0x0c
    uint32_t  mnNodeSize;                         // +0x18
    void*     mpPoolBegin;                        // +0x1c
    void*     mpPoolEnd;                          // +0x20
    void*     mpHead;                             // +0x24
    uint32_t  mnCurrentSize;                      // +0x28
    uint32_t  mnPeakSize;                         // +0x2c
    // +0x30

    ~FixedPool();
    bool Init(uint32_t nodeSize, int count, struct InitAllocator* a1, struct InitAllocator* a2);
    void* Alloc();
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedHashtableAllocator : public FixedPool { public:
    uint32_t  mnBucketCount;                      // +0x30
    void*     mpBucketBuffer;                     // +0x34
    // +0x38

    ~FixedHashtableAllocator();
    bool InitBuckets(unsigned count, struct InitAllocator* a1, struct InitAllocator* a2);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ListLink {
    ListLink* mpNext;      // +0x00
    ListLink* mpPrev;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct VoiceNode : ListLink {
    unsigned  mValue;      // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct VoiceList {
    ListLink  mNode;       // +0x00 sentinel (8 bytes)
    FixedPool mPool;       // +0x08
    // +0x38

    ~VoiceList();
    void Clear();
    void PopFront();
    void PushBack(ListLink* anchor, const unsigned* value2);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Symbol { public:                 // 8 bytes
    unsigned    mHash;          // +0x00
    const char* mpName;         // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamPair {              // pair<Symbol const, _atom> = 0x14
    Symbol   first;             // +0x00
    unsigned a_type;            // +0x08
    union {
        float          a_float;   // +0x0c
        const char*    a_sym;     // +0x0c
    };
    const char* a_sym2;         // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamNode {
    ParamPair   mValue;         // +0x00
    ParamNode*  mpNext;         // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamTable {
    void*        mpVftable;       // +0x00
    ParamNode**  mpBucketArray;   // +0x04
    unsigned     mnBucketCount;   // +0x08
    unsigned     mnElementCount;  // +0x0c
    unsigned     pad10[3];        // +0x10 rehash policy
    FixedHashtableAllocator mAllocator;   // +0x1c (FixedPool at +0x1c)
    // +0x54

    ~ParamTable();
    void FreeBuckets(ParamNode** buckets, unsigned n);
    ParamNode* AllocNode(const ParamPair* v);
    void Bucket(void** out, const Symbol* key, void* a3, void* a4);
    unsigned Find(Symbol* key, ParamPair* out);
    ParamPair* LocateOrInsert(const Symbol* key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamIter {
    void*        mpVftable;      // +0x00
    ParamNode*   mpNode;         // +0x04
    ParamNode**  mpBucket;       // +0x08
    ParamNode*   mpLast;         // +0x0c
    ParamNode**  mpBucketEnd;    // +0x10
    ParamTable*  mpTable;        // +0x14
    // +0x18

    ParamIter(ParamTable* t);
    unsigned Next(Symbol* out, ParamPair* value);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Play { public:
    VoiceList   mVoices;         // +0x00
    ParamTable  mParameters;     // +0x38
    unsigned    mnBusyVoices;    // +0x8c
    unsigned    mnMaxVoices;     // +0x90
    unsigned    mnMaxParameters; // +0x94
    void*       mVoiceManager;   // +0x98
    void*       mInstance;       // +0x9c
    Symbol      mName;           // +0xa0
    bool        mbSteal;         // +0xa8
    bool        mbUpdatePlaying; // +0xa9
    bool        mbPaused;        // +0xaa
    int         mnStepRule;      // +0xac
    unsigned    mnLastGroupID;   // +0xb0
    void*       mpObject;        // +0xb4

    ~Play();
    bool Init(unsigned maxVoices, unsigned maxParams, void* a3, void* a4);
    void UpdatePlaying();
    void SetPlaying();
    void SetPaused(bool b);
    void StartVoice(void* a1, void* a2, float t);
    void ParamEvent(Symbol key, ParamPair* atom);
    unsigned GetParam(void* outAtom, Symbol key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct InitAllocator {
    void* vftable;         // +0x00
    void* field4;          // +0x04
    void* name;            // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float   GetVoiceStartTime(float t);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a649b0(void* out);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   FUN_00a649a0();
}
}
}
#define NOINLINE __declspec(noinline)
namespace EA {
namespace Audio {
namespace Eapd {
typedef void* VoiceManager;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
NOINLINE struct InstanceDesc {
    void* p0;   // +0x00
    void* p1;   // +0x04
    void* p2;   // +0x08
};
}
}
}
// ---- items of slice s00a52ff0 end

// ---- items of slice s00a53f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct PgAllocator {
    virtual ~PgAllocator() {}                       // +0x00
    virtual void  v04();
    virtual void* Alloc(uint32_t size, uint32_t tag);  // +0x08
    virtual void  Free(void* p);                    // +0x0c
    void* mpCoreAllocator;                          // +0x04
    void* mpName;                                   // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgListLink {
    PgListLink* mpNext;      // +0x00
    PgListLink* mpPrev;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgFixedPool {
    PgAllocator mInitAllocator;      // +0x00
    PgAllocator mOverflowAllocator;  // +0x0c
    uint32_t    mnNodeSize;          // +0x18
    void*       mpPoolBegin;         // +0x1c
    void*       mpPoolEnd;           // +0x20
    void*       mpHead;              // +0x24
    uint32_t    mnCurrentSize;       // +0x28
    uint32_t    mnPeakSize;          // +0x2c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgVoiceList {
    PgListLink  mNode;               // +0x00 sentinel
    PgFixedPool mPool;               // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgSymbol {
    uint32_t    mHash;       // +0x00
    const char* mpName;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const PgSymbol& a, const PgSymbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgParamPair {         // 0x14
    PgSymbol first;          // +0x00
    int      a_type;         // +0x08
    union {
        float       a_float; // +0x0c
        const char* a_sym;
    };
    const char* a_sym2;      // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgParamNode {
    PgParamPair mValue;      // +0x00
    PgParamNode* mpNext;     // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgParamTable {
    void*         mpVftable;      // +0x00
    PgParamNode** mpBucketArray;  // +0x04
    uint32_t      mnBucketCount;  // +0x08
    uint32_t      mnElementCount; // +0x0c
    uint32_t      pad10[3];       // +0x10
    PgFixedPool   mAllocator;     // +0x1c
    uint32_t      mnBucketCount2; // +0x4c
    void*         mpBucketBuffer; // +0x50
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Play_s00a5_3f90 { public:                // size 0xb8
    PgVoiceList   mVoices;        // +0x00
    PgParamTable  mParameters;    // +0x38
    unsigned      mnBusyVoices;   // +0x8c
    unsigned      mnMaxVoices;    // +0x90
    unsigned      mnMaxParameters;// +0x94
    void*         mVoiceManager;  // +0x98
    void*         mInstance;      // +0x9c
    PgSymbol      mName;          // +0xa0
    bool          mbSteal;        // +0xa8
    bool          mbUpdatePlaying;// +0xa9
    bool          mbPaused;       // +0xaa
    int           mnStepRule;     // +0xac
    unsigned      mnLastGroupID;  // +0xb0
    void*         mpObject;       // +0xb4

    enum { STEP_RANDOM = 0, STEP_INORDER = 1, STEP_NOREPEAT = 2 };

    Play_s00a5_3f90* Ctor(void* voiceManager, void* instance, uint32_t nameHash, const char* name,
               int steal, int updatePlaying, int stepRule, void* object);
    void  Start(float time);  // 0x00a540f0 (EA::Audio::Eapd::Play::Start)
    void  StartSelect(unsigned group, float time);  // 0x00a54200 (EA::Audio::Eapd::Play::StartSelect)
    void  Dolist(uint32_t selHash, const char* selName, void* at);   // 0xa53e60
    bool  Init(void* allocator, unsigned maxVoices, uint32_t ticks); // 0xa53b90
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_play {              // size 0xec
    uint32_t  object[0x28 / 4];   // +0x00
    Play_s00a5_3f90      play;               // +0x28
    void*     pUpdateCallback;    // +0xe0
    void*     pDoneOutlet;        // +0xe4
    bool      bIsDynamic;         // +0xe8
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgClass;              // t_class
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgAtomArg {           // t_atom (12 bytes)
    int a_type;
    union {
        float    a_float;
        PgSymbol a_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gPlaySymbol;      // 0x1675524
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gStealSymbol;     // 0x1675544
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gBlockSymbol;     // 0x167554c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gSetplayingSymbol;// 0x1675664
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gSetnextSymbol;   // 0x167566c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gInorderSymbol;   // 0x167553c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gRandomSymbol;    // 0x1675534
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gNorepeatSymbol;  // 0x167552c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gEmptySymbol;     // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gBangSymbol;      // 0x16758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gUpdateTicks;     // 0x1675560
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgClass* gpPlayClass;      // 0x167555c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* gensym(PgSymbol* out, const char* s);              // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_free(t_play* x);                                  // 0xa53f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_play;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_play* play_new(uint32_t nameHash, const char* name, void* unused3, int argc, PgAtomArg* argv); // 0xa54290
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_anything(t_play* x, uint32_t selHash, const char* selName, int argc, PgAtomArg* argv); // 0xa53fc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_start(t_play* x, float time);                     // 0xa54520
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_startselect(t_play* x, float group, float time);   // 0xa54560
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_stop(t_play* x);                                  // 0xa538d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_pause(t_play* x, int f);                          // 0xa53560
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_use(t_play* x, uint32_t hash, const char* name);  // 0xa53310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_update(void* x);                                  // 0xa539d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  EapdVoiceList_Init(char* dst, const char* name);       // 0xa53c90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  EapdParamTable_Init(char* dst, const char* name);      // 0xa66260
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* owner, PgSymbol s);                   // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgClass* class_new(PgSymbol name, void* newmethod, void* freemethod, int size, int a1, int a2, int a3); // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addcreator(void* fn, PgSymbol name, int mkArg, int a);   // 0xa48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod0(PgClass* c, void* fn, PgSymbol name, int a);  // 0xa48a30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod1(PgClass* c, void* fn, PgSymbol name, int a1, int a2); // 0xa48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod2(PgClass* c, void* fn, PgSymbol name, int a1, int a2); // 0xa48ad0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addmethod3(PgClass* c, void* fn, PgSymbol name, int a1, int a2, int a3); // 0xa48ad0 (4 args)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  class_addanything(PgClass* c, void* fn);               // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(PgClass* c);                                    // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_free(void* x);                                      // 0xa493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* GetVoiceManager();                                     // 0xa67d00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* CanvasGetCurrentInstance();                            // 0xa4a450
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* System_GetAllocator();                                 // 0xa67cb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* Instance_GetGroup(void* a, uint32_t hash, const char* p);  // 0xa64cb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* Play_GetLocation(void* out);                           // 0xa649d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned Group_Size(void* group);                            // 0xa52bb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* Group_Sample(void* out, void* group, unsigned i);      // 0xa52bc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* Group_Location(void* out, void* group);                // 0xa529c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  Play_Dispatch(void* a, uint32_t hash, const char* name, float time); // 0xa53d20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned eapd_rand(unsigned n);                              // 0xa5ec90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* Play_GetUpdateManager();                               // 0xa67ce0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PlayUpdateManager {
    void* AddCallback(void* obj, void* fn);   // 0xa643b0  __thiscall
    void  RemoveCallback(void* fn);           // 0xa644e0  __thiscall
};
}
}
}
// ---- items of slice s00a53f90 end

// @ 0x00a53d20
namespace EA { namespace Audio { namespace Eapd {
void Play::StartVoice(void* a1, void* a2, float time)
{
    SetPlaying();
    if (mnBusyVoices >= mnMaxVoices && !mbSteal)
        return;

    double start = GetVoiceStartTime(time);
    unsigned voiceId = 0;
    ParamIter it(&mParameters);
    InstanceDesc desc;
    desc.p1 = 0;
    desc.p2 = 0;
    FUN_00a649b0(&desc.p1);
    desc.p0 = FUN_00a649a0();

    VoiceManager vm = (VoiceManager)mVoiceManager;
    if (!((bool (__thiscall*)(VoiceManager, void*, void*, void*, double, ParamIter*, InstanceDesc, unsigned*))
          (*(void***)vm)[2])(vm, a1, a2, 0, start, &it, desc, &voiceId))
        return;

    if (mnBusyVoices == mnMaxVoices) {
        VoiceNode* first = (VoiceNode*)mVoices.mNode.mpNext;
        ((void (__thiscall*)(VoiceManager, unsigned))(*(void***)vm)[3])(vm, first->mValue);
        mVoices.PopFront();
        --mnBusyVoices;
    }
    mVoices.PushBack(&mVoices.mNode, &voiceId);
    ++mnBusyVoices;
    if (mbPaused) {
        unsigned last = ((VoiceNode*)mVoices.mNode.mpPrev)->mValue;
        ((void (__thiscall*)(VoiceManager, unsigned, int))(*(void***)vm)[4])(vm, last, 1);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54020
namespace EA { namespace Audio { namespace Eapd {
Play_s00a5_3f90* Play_s00a5_3f90::Ctor(void* voiceManager, void* instance, uint32_t nameHash, const char* name, int steal, int updatePlaying, int stepRule, void* object)
{
    EapdVoiceList_Init((char*)this, "EAPd/VoiceList");
    EapdParamTable_Init((char*)this + 0x38, "EAPd/ParameterMap");
    mVoiceManager = voiceManager;
    mInstance = instance;
    mName.mHash = nameHash;
    mName.mpName = name;
    mbSteal = (steal == 1);
    mnStepRule = stepRule;
    mnBusyVoices = 0;
    mnMaxVoices = 0;
    mnMaxParameters = 0;
    mbPaused = false;
    mpObject = object;
    mbUpdatePlaying = (updatePlaying == 0);
    mnLastGroupID = 0xffffffff;
    return this;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a540f0
namespace EA { namespace Audio { namespace Eapd {
void Play_s00a5_3f90::Start(float time)
{
    void* group = Instance_GetGroup(mInstance, mName.mHash, mName.mpName);
    PgSymbol name;
    if (!group) {
        name = *(PgSymbol*)Play_GetLocation(&name);
        gPlaySymbol = name;
        Play_Dispatch(mpObject, mName.mHash, mName.mpName, time);
        return;
    }
    unsigned n = Group_Size(group);
    unsigned idx = 0;
    if (n > 1) {
        if (mnStepRule == STEP_RANDOM) {
            idx = eapd_rand(n);
        } else if (mnStepRule == STEP_INORDER) {
            idx = (mnLastGroupID + 1) % n;
        } else if (mnStepRule == STEP_NOREPEAT) {
            idx = eapd_rand(n - 1);
            if (idx == mnLastGroupID)
                idx = n - 1;
        }
    }
    PgSymbol loc = *(PgSymbol*)Group_Location(&loc, group);
    gPlaySymbol = loc;
    name = *(PgSymbol*)Group_Sample(&name, group, idx);
    mnLastGroupID = idx;
    Play_Dispatch(mpObject, name.mHash, name.mpName, time);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54200
namespace EA { namespace Audio { namespace Eapd {
void Play_s00a5_3f90::StartSelect(unsigned group, float time)
{
    void* g = Instance_GetGroup(mInstance, mName.mHash, mName.mpName);
    if (!g)
        return;
    PgSymbol sample = *(PgSymbol*)Group_Sample(&sample, g, group);
    if (sample.mHash == gEmptySymbol.mHash)
        return;
    PgSymbol loc = *(PgSymbol*)Group_Location(&loc, g);
    gPlaySymbol = loc;
    Play_Dispatch(mpObject, sample.mHash, sample.mpName, time);
    mnLastGroupID = group;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54290
namespace EA { namespace Audio { namespace Eapd {
t_play* play_new(uint32_t nameHash, const char* name, void* unused3, int argc, PgAtomArg* argv)
{
    bool bDynamic = (nameHash != gPlaySymbol.mHash);
    PgSymbol firstSym = gEmptySymbol;
    int stepRule = 0;
    int updatePlaying = 0;
    int steal = 1;
    bool bHaveFirst = false;
    unsigned floatArg = 1;
    bool haveFloat = false;
    bool bStealSet = false;
    bool bSetSet = false;

    for (int i = 0; i < argc; ++i) {
        PgAtomArg* a = &argv[i];
        if (haveFloat) {
            if (bStealSet && bSetSet)
                break;
        } else {
            if (a->a_type == 1) {
                floatArg = (unsigned)(int)(__int64)a->a_w.a_float;
                haveFloat = true;
                continue;
            }
        }
        if (a->a_type == 2) {
            uint32_t sel = a->a_w.a_symbol.mHash;
            if (sel == gStealSymbol.mHash) {
                bStealSet = true;
                steal = 1;
            } else if (sel == gBlockSymbol.mHash) {
                steal = 0;
                bStealSet = true;
            } else if (sel == gSetplayingSymbol.mHash) {
                updatePlaying = 0;
                bSetSet = true;
            } else if (sel == gSetnextSymbol.mHash) {
                bSetSet = true;
                updatePlaying = 1;
            } else if (sel == gInorderSymbol.mHash) {
                stepRule = 1;
            } else if (sel == gRandomSymbol.mHash) {
                stepRule = 0;
            } else if (sel == gNorepeatSymbol.mHash) {
                stepRule = 2;
            } else if (i == 0) {
                bHaveFirst = true;
                firstSym = a->a_w.a_symbol;
            }
        }
    }

    if (!bHaveFirst && !bDynamic)
        return 0;

    void* allocator = System_GetAllocator();
    void* voiceMgr = GetVoiceManager();
    void* instance = CanvasGetCurrentInstance();
    t_play* x = (t_play*)pd_new(gpPlayClass);
    if (x) {
        x->play.Ctor(voiceMgr, instance, firstSym.mHash, firstSym.mpName,
                     steal, updatePlaying, stepRule, x);
    }
    if (!x->play.Init(allocator, floatArg, gUpdateTicks)) {
        pd_free(x);
        return 0;
    }
    x->pDoneOutlet = outlet_new(x, gBangSymbol);
    if (!x->pDoneOutlet) {
        pd_free(x);
        return 0;
    }
    x->bIsDynamic = bDynamic;
    x->pUpdateCallback = 0;
    return x;}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54520
namespace EA { namespace Audio { namespace Eapd {
void play_start(t_play* x, float time)
{
    x->play.Start(time);
    if (!x->pUpdateCallback) {
        PlayUpdateManager* mgr = (PlayUpdateManager*)Play_GetUpdateManager();
        x->pUpdateCallback = mgr->AddCallback(x, (void*)play_update);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54560
namespace EA { namespace Audio { namespace Eapd {
void play_startselect(t_play* x, float group, float time)
{
    x->play.StartSelect((unsigned)(__int64)group, time);
    if (!x->pUpdateCallback)
        x->pUpdateCallback = ((PlayUpdateManager*)Play_GetUpdateManager())->AddCallback(x, (void*)play_update);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a545d0
namespace EA {
namespace Audio {
namespace Eapd {
bool a_play_setup()
{
    PgSymbol s;
    bool ok;

    gPlaySymbol       = *gensym(&s, "play");
    gStealSymbol      = *gensym(&s, "steal");
    gBlockSymbol      = *gensym(&s, "block");
    gSetplayingSymbol = *gensym(&s, "setplaying");
    gSetnextSymbol    = *gensym(&s, "setnext");
    gInorderSymbol    = *gensym(&s, "inorder");
    gRandomSymbol     = *gensym(&s, "random");
    gNorepeatSymbol   = *gensym(&s, "norepeat");

    gpPlayClass = class_new(gPlaySymbol, (void*)play_new, (void*)play_free, 0xec, 0, 9, 0);
    ok = gpPlayClass != 0;
    ok &= class_addcreator((void*)play_new, *gensym(&s, "dplay"), 9, 0);
    ok &= class_addmethod2(gpPlayClass, (void*)play_start, *gensym(&s, "start"), 5, 0);
    ok &= class_addmethod3(gpPlayClass, (void*)play_startselect, *gensym(&s, "startselect"), 1, 5, 0);    ok &= class_addmethod0(gpPlayClass, (void*)play_stop, *gensym(&s, "stop"), 0);
    ok &= class_addmethod1(gpPlayClass, (void*)play_pause, *gensym(&s, "pause"), 1, 0);
    ok &= class_addmethod1(gpPlayClass, (void*)play_use, *gensym(&s, "use"), 2, 0);
    ok &= class_addanything(gpPlayClass, (void*)play_anything);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
