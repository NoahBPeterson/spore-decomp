// Shared declarations for slice s00a53f90.
// EA::Audio::Eapd (EA's embedded Pure Data) fracplay object "play": Play (voice list +
// parameter map) plus the play_* atom classes.  Layouts taken from the 2008 dev PDB
// (Play 0xb8, t_play 0xec) and confirmed against the disassembly offsets.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct PgAllocator {
    virtual ~PgAllocator() {}                       // +0x00
    virtual void  v04();
    virtual void* Alloc(uint32_t size, uint32_t tag);  // +0x08
    virtual void  Free(void* p);                    // +0x0c
    void* mpCoreAllocator;                          // +0x04
    void* mpName;                                   // +0x08
};

// fixed pool / voice list (PDB fixed_list<unsigned>)
struct PgListLink {
    PgListLink* mpNext;      // +0x00
    PgListLink* mpPrev;      // +0x04
};
struct PgVoiceNode : PgListLink {
    unsigned  mValue;        // +0x08
};

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
struct PgVoiceList {
    PgListLink  mNode;               // +0x00 sentinel
    PgFixedPool mPool;               // +0x08
};

// parameter hash map
struct PgSymbol {
    uint32_t    mHash;       // +0x00
    const char* mpName;      // +0x04
};
inline bool operator==(const PgSymbol& a, const PgSymbol& b) { return a.mHash == b.mHash; }

struct PgAtom {
    int a_type;              // +0x00
    union {
        float    a_float;    // +0x04
        PgSymbol a_symbol;   // +0x04 (hash) / +0x08 (name)
    };
};

struct PgParamPair {         // 0x14
    PgSymbol first;          // +0x00
    int      a_type;         // +0x08
    union {
        float       a_float; // +0x0c
        const char* a_sym;
    };
    const char* a_sym2;      // +0x10
};

struct PgParamNode {
    PgParamPair mValue;      // +0x00
    PgParamNode* mpNext;     // +0x14
};

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

struct PgCallbackList;

struct Play {                // size 0xb8
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

    Play* Ctor(void* voiceManager, void* instance, uint32_t nameHash, const char* name,
               int steal, int updatePlaying, int stepRule, void* object);
    void  Start(float time);
    void  StartSelect(unsigned group, float time);
    void  Dolist(uint32_t selHash, const char* selName, void* at);   // 0xa53e60
    bool  Init(void* allocator, unsigned maxVoices, uint32_t ticks); // 0xa53b90
};

struct t_play {              // size 0xec
    uint32_t  object[0x28 / 4];   // +0x00
    Play      play;               // +0x28
    void*     pUpdateCallback;    // +0xe0
    void*     pDoneOutlet;        // +0xe4
    bool      bIsDynamic;         // +0xe8
};

struct PgClass;              // t_class

struct PgAtomArg {           // t_atom (12 bytes)
    int a_type;
    union {
        float    a_float;
        PgSymbol a_symbol;
    } a_w;
};

extern PgSymbol gPlaySymbol;      // 0x1675524
extern PgSymbol gStealSymbol;     // 0x1675544
extern PgSymbol gBlockSymbol;     // 0x167554c
extern PgSymbol gSetplayingSymbol;// 0x1675664
extern PgSymbol gSetnextSymbol;   // 0x167566c
extern PgSymbol gInorderSymbol;   // 0x167553c
extern PgSymbol gRandomSymbol;    // 0x1675534
extern PgSymbol gNorepeatSymbol;  // 0x167552c
extern PgSymbol gEmptySymbol;     // 0x167589c
extern PgSymbol gBangSymbol;      // 0x16758b4
extern uint32_t gUpdateTicks;     // 0x1675560
extern PgClass* gpPlayClass;      // 0x167555c
extern int      gOutletCount;     // 0x167545c

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
PgSymbol* gensym(PgSymbol* out, const char* s);              // 0xa675f0
void  play_free(t_play* x);                                  // 0xa53f90
struct t_play;
t_play* play_new(uint32_t nameHash, const char* name, void* unused3, int argc, PgAtomArg* argv); // 0xa54290
void  play_anything(t_play* x, uint32_t selHash, const char* selName, int argc, PgAtomArg* argv); // 0xa53fc0
void  play_start(t_play* x, float time);                     // 0xa54520
void  play_startselect(t_play* x, float group, float time);   // 0xa54560
bool  a_play_setup();                                        // 0xa545d0
void  play_stop(t_play* x);                                  // 0xa538d0
void  play_pause(t_play* x, int f);                          // 0xa53560
void  play_use(t_play* x, uint32_t hash, const char* name);  // 0xa53310
void  play_update(void* x);                                  // 0xa539d0
void  Play_Dtor(Play* p);                                    // 0xa53b20
void  EapdVoiceList_Init(char* dst, const char* name);       // 0xa53c90
void  EapdParamTable_Init(char* dst, const char* name);      // 0xa66260
void  AtomsToString(int argc, PgAtomArg* argv, char* buf, unsigned n); // 0xa46bc0

void* outlet_new(void* owner, PgSymbol s);                   // 0xa49d30
void  outlet_float(void* outlet, float f);                   // 0xa49570
PgClass* class_new(PgSymbol name, void* newmethod, void* freemethod, int size, int a1, int a2, int a3); // 0xa48e50
bool  class_addcreator(void* fn, PgSymbol name, int mkArg, int a);   // 0xa48e00
bool  class_addmethod0(PgClass* c, void* fn, PgSymbol name, int a);  // 0xa48a30
bool  class_addmethod1(PgClass* c, void* fn, PgSymbol name, int a1, int a2); // 0xa48a80
bool  class_addmethod2(PgClass* c, void* fn, PgSymbol name, int a1, int a2); // 0xa48ad0
bool  class_addmethod3(PgClass* c, void* fn, PgSymbol name, int a1, int a2, int a3); // 0xa48ad0 (4 args)
bool  class_addanything(PgClass* c, void* fn);               // 0xa47f90
void* pd_new(PgClass* c);                                    // 0xa49390
void  pd_free(void* x);                                      // 0xa493d0
void* GetVoiceManager();                                     // 0xa67d00
void* CanvasGetCurrentInstance();                            // 0xa4a450
void* System_GetAllocator();                                 // 0xa67cb0
void* Instance_GetGroup(void* a, uint32_t hash, const char* p);  // 0xa64cb0
void* Play_GetLocation(void* out);                           // 0xa649d0
unsigned Group_Size(void* group);                            // 0xa52bb0
void* Group_Sample(void* out, void* group, unsigned i);      // 0xa52bc0
void* Group_Location(void* out, void* group);                // 0xa529c0
void  Play_Dispatch(void* a, uint32_t hash, const char* name, float time); // 0xa53d20
unsigned eapd_rand(unsigned n);                              // 0xa5ec90
void* Play_GetUpdateManager();                               // 0xa67ce0
void  Play_RemoveCallback(void* mgr, void* fn);              // 0xa644e0

// The "update manager" returned by Play_GetUpdateManager() is a C++ object; its
// register/removal entry points are __thiscall (ecx = manager, args on stack).
struct PlayUpdateManager {
    void* AddCallback(void* obj, void* fn);   // 0xa643b0  __thiscall
    void  RemoveCallback(void* fn);           // 0xa644e0  __thiscall
};

// Play::~Play() lives at 0xa53b20 and takes only `this` (ecx); call it through a
// stub so the call site stays a __thiscall (ecx = &x->play).
struct PlayDtorStub {
    void Destroy();                           // 0xa53b20
};

}}}  // namespace
