// src/game/SPAudio/_at_00a50000.cpp -- migrated from slice(s) s00a5e0f0, s00a5d3c0, s00a5c460, s00a59690, s00a586d0, s00a576c0, s00a56460, s00a550e0, s00a53f90, s00a52ff0, s00a52080, s00a510e0 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a50000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s00a510e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
bool a_play_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool a_group_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool a_control_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" double exp(double);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static inline float expf_(float x) { return (float)exp((double)x); }
}
}
}
// ---- items of slice s00a510e0 end

// ---- items of slice s00a52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* spMtofClass;           // 0x167550c
extern void* spFtomClass;           // 0x1675500
extern void* spPowtodbClass;        // 0x1675504
extern void* spRmstodbClass;        // 0x1675510
extern void* spDbtopowClass;        // 0x1675514
extern void* spDbtormsClass;        // 0x1675508
extern void* spGroupClass;          // 0x1675520
extern int   gOutletDstA;           // 0x16758c8
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl pd_new(void* cls);                                   // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl pd_free(void* obj);                                  // 0xa493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl outlet_new(void* obj, t_symbol* s, int a);           // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl canvas_getcurrentinstance();                         // 0xa4a450
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl GetVoiceManager();                                   // 0xa67d00
}
}
}
struct VoiceManager {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
  virtual void s4();
  virtual char Add(int sym, int a, void* out);   // +0x14
  virtual void S18(int o, int a, int b, int c, int d);  // +0x18
  virtual void S19(int o, int a, int b);                // +0x1c
};
extern t_symbol gFloatSymbol;       // 0x16758c4
extern t_symbol gEmptySymbol;       // 0x167589c
struct CM_Hash { char pad[0x18]; int v18; int v1c; void* __thiscall GetPair(void* out); };
struct GroupHelp { int v0, v1, v2, dummy, v10, v14;
  void* __thiscall Init(int b);
};
struct GroupHelper {
  void __thiscall FreeGroup(int a, int b, int g);                 // 0xa65470
};
int   __cdecl FUN_00a65360(int, int, int, void*);
// ---- items of slice s00a52080 end

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
struct t_play {                 // PDB size 0xec
    unsigned  object[0x28 / 4]; // +0x00
    Play      play;             // +0x28
    void*     pUpdateCallback;  // +0xe0
    void*     pDoneOutlet;      // +0xe4
    bool      bIsDynamic;       // +0xe8
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
void   outlet_bang(void* outlet);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" void* g_eapdAlloc;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     FUN_00a65e40(void* a, void* b, void* c);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a3b2c0(void* out, const void* key);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    FUN_00a65bb0(void* table, void* key, void* a3);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    atom_string(void* a, char* buf, int n);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void artists_play_setpausedf(t_play* x, float f);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void artists_play_updateplaying(t_play* x);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int  artists_play_step(void* self);
}
}
}
#define NOINLINE __declspec(noinline)
namespace EA {
namespace Audio {
namespace Eapd {
extern void* const g_allocVftable;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef void* VoiceManager_s00a5_2ff0;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
NOINLINE struct PoolForCtor {
    void*  vftable0;   // +0x00
    void*  field4;     // +0x04
    void*  name0;      // +0x08
    void*  vftable1;   // +0x0c
    void*  field4b;    // +0x10
    void*  name1;      // +0x14
    uint32_t nodeSize; // +0x18
    void*  poolBegin;  // +0x1c
    void*  poolEnd;    // +0x20
    void*  head;       // +0x24
    uint32_t curSize;  // +0x28
    uint32_t peakSize; // +0x2c
};
}
}
}
void* const EA::Audio::Eapd::g_allocVftable = (void*)0x1454fac;
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
struct t_play_s00a5_3f90 {              // size 0xec
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
extern int      gOutletCount;     // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_free(t_play_s00a5_3f90* x);                                  // 0xa53f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_play_s00a5_3f90;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  play_anything(t_play_s00a5_3f90* x, uint32_t selHash, const char* selName, int argc, PgAtomArg* argv); // 0xa53fc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  AtomsToString(int argc, PgAtomArg* argv, char* buf, unsigned n); // 0xa46bc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* outlet, float f);                   // 0xa49570
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
namespace EA {
namespace Audio {
namespace Eapd {
struct PlayDtorStub {
    void Destroy();                           // 0xa53b20
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FAtomConnect {
    FAtomConnect* mpNext;    // +0x00
    void*         mpTo;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FAtomOutlet {
    void*         mpOwner;       // +0x00
    void*         mpNext;        // +0x04
    FAtomConnect* mpConnections; // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FAtom {
    uint32_t     mGobj[2];   // +0x00
    uint32_t     mBinbuf;    // +0x08
    FAtomOutlet* mpOutlet;   // +0x0c
    uint32_t     pad10[6];   // +0x10
    float        mF1;        // +0x28
    float        mF2;        // +0x2c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
static __forceinline void Broadcast(FAtom* x, float f)
{
    FAtomOutlet* outlet = x->mpOutlet;
    if (++gOutletCount < 1000) {
        for (FAtomConnect* oc = outlet->mpConnections; oc != 0; oc = oc->mpNext)
            outlet_float(oc->mpTo, f);
    }
    --gOutletCount;
}
}
}
}
// ---- items of slice s00a53f90 end

// ---- items of slice s00a550e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_0167545c;              // 0x0167545c  re-entrancy guard
extern "C" int DAT_016758c4;              // 0x016758c4
extern "C" int DAT_016758c8;              // 0x016758c8
extern "C" int DAT_016755d4;              // 0x016755d4  spSin class
extern "C" int DAT_016755a4;              // 0x016755a4  spCos class
extern "C" int DAT_016755cc;              // 0x016755cc  spTan class
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin)
#pragma intrinsic(cos)
namespace EA {
namespace Audio {
namespace Eapd {
int  __cdecl pd_new_s00a5_50e0(void* cls);                       // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int  __cdecl outlet_new(void* self, int a, int b);    // 0x00a49d30
}
}
}
struct tOutNode {
    void*         mpVtbl;                     // +0x00
    void*         mPad04;                     // +0x04
    void*         mPad08;                     // +0x08
    void*         mpOutlets;                  // +0x0c  -> binder
    unsigned char pad_10[0x18];               // +0x10..+0x27
    float         mValue;                     // +0x28
    float         mOperand;                   // +0x2c
};
struct Outlet { Outlet* mpNext; int mIndex; };
static __forceinline void nodeBroadcast(tOutNode* n, float f)
{
    void* binder = n->mpOutlets;            // fetched before the guard bump
    ++DAT_0167545c;
    if (DAT_0167545c < 1000) {
        for (Outlet* o = *(Outlet**)((char*)binder + 8); o; o = o->mpNext)
            EA::Audio::Eapd::outlet_float((void*)o->mIndex, f);
    }
    --DAT_0167545c;
}
// ---- items of slice s00a550e0 end

// ---- items of slice s00a56460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {             // 0x1c
    void*         o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_6460 {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_6460 gFloatSymbol_s00a5_6460;    // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spAtanClass;     // 0x167559c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spAtan2Class;    // 0x1675588
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSqrtClass;     // 0x16755e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spLogClass;      // 0x16755c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spExpClass;      // 0x16755ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spAbsClass;      // 0x167557c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spClipClass;     // 0x1675578
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     pd_new(t_class* c);                                          // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     floatinlet_new(void* owner, void* dest);                     // 0xa49a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     outlet_new(void* owner, t_symbol_s00a5_6460 s);                         // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
__forceinline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;
}
}
}
}
// ---- items of slice s00a56460 end

// ---- items of slice s00a576c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_76c0 { uint32_t mHash; const char* mpName; };   // 8 bytes
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollNode {
    uint32_t  k0;          // +0x00
    uint32_t  k1;          // +0x04
    uint32_t  type;        // +0x08
    uint32_t  value;       // +0x0c
    uint32_t  sym;         // +0x10
    int32_t   count;       // +0x14
    uint32_t* items;       // +0x18
    CollNode* next;        // +0x1c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Pair { CollNode* node; CollNode** bucket; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct InsResult { CollNode* node; CollNode** bucket; bool ok; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RingNode {
    RingNode* next;        // +0x00
    RingNode* prev;        // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ListItem : RingNode {
    uint32_t type;         // +0x08
    uint32_t value;        // +0x0c
    uint32_t sym;          // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct OutletNode { OutletNode* next; void* target; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct OutletList { uint8_t pad[8]; OutletNode* head; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RehashResult { uint8_t grow; uint8_t pad[3]; uint32_t count; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class HashPolicy {
public:
    uint8_t pad[0x18];
    void Rehash(RehashResult* out, unsigned buckets, unsigned elems, int flag);  // 0x921440
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*  outlet_new(void* x, uint32_t s1, uint32_t s2);            // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void   outlet_list(void* x, uint32_t s1, uint32_t s2, int argc, void* argv);  // 0xa49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void   outlet_symbol(void* x, uint32_t a, uint32_t b);           // 0xa49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*  pd_findbyclass(unsigned a, unsigned b, unsigned c);       // 0xa671f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int    atom_getint(void* a, void* out);                          // 0xa46770
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_76c0  gListSymbol;        // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_76c0  gListSender;        // 0x16758b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t  gCollReadClass;     // 0x1675610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t  gCollWriteClass;    // 0x167561c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t  gCollClass;         // 0x16755f4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class CollIAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // vtable +0x08
    virtual void  Free(void* p);            // vtable +0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class CollTable {
public:
    uint32_t   pad0;                       // +0x00
    CollNode** mBuckets;                   // +0x04
    uint32_t   mBucketCount;               // +0x08
    uint32_t   mElems;                     // +0x0c
    HashPolicy mPolicy;                    // +0x10
    CollIAlloc mAlloc;                     // +0x28
    uint8_t    pad2c[8];                   // +0x2c
    uint32_t   mElemSize;                  // +0x34
    CollNode*  mBegin;                     // +0x38
    CollNode*  mEnd;                       // +0x3c
    CollNode*  mFree;                      // +0x40
    uint32_t   mCount;                     // +0x44
    uint32_t   mHigh;                      // +0x48
    uint32_t   mSpecialDwords;             // +0x4c
    CollNode*  mSpecial;                   // +0x50

    __forceinline unsigned HashOf(CollNode* n)
    {
        switch (n->type) {
        case 1:  return n->value & 0x7fffffff;
        case 2:  return n->value;
        default: return 0;
        }
    }
    void      FreeChains(unsigned count);                       // 0xa57900
    CollNode** NewBuckets(unsigned count);                      // 0xa57880
    CollNode* Find(CollNode* head, CollNode* key, unsigned h);  // 0xa579d0
    Pair*     Lookup(Pair* out, CollNode* key);                 // 0xa57a20
    CollNode* AllocNode(CollNode* src);                         // 0xa57aa0
    void      FreeList(CollNode** v, unsigned n);               // 0xa57af0
    Pair*     EraseNode(Pair* out, CollNode* key, CollNode** bucket);  // 0xa583e0
    InsResult* InsertIns(InsResult* out, CollNode* key, unsigned unused);  // 0xa58480
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollRecv {
    uint8_t    pad0[0x150];
    CollTable  mTable;                     // +0x150
    RingNode   mSentinel;                  // +0x1a4
    uint8_t    pad2[0x1b8 - 0x1a4 - sizeof(RingNode)];
    OutletList* mOutlets;                  // +0x1b8
    void*      mOutlets2;                  // +0x1bc

    bool LookupKey(uint32_t a0, uint32_t a1, uint32_t a2, int* outA, int* outB);      // 0xa57b60
    bool LookupIndex(uint32_t a0, uint32_t a1, uint32_t a2, int idx, void* out);      // 0xa57be0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollObject {
    uint8_t   pad0[0x28];
    uint32_t  mKeyA;                       // +0x28
    uint32_t  mKeyB;                       // +0x2c
};
}
}
}
// ---- items of slice s00a576c0 end

// ---- items of slice s00a586d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct Atom { uint32_t a, b, c; };                      // 12 bytes
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollNode_s00a5_86d0;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollIAlloc_s00a5_86d0 {
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);     // +0x08
    virtual void  Free(void* p);            // +0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollNode_s00a5_86d0 {
    CollNode_s00a5_86d0* prev;      // +0x00  all-entries list
    CollNode_s00a5_86d0* next;      // +0x04
    uint32_t  keyType;   // +0x08
    uint32_t  keyA;      // +0x0c
    uint32_t  keyB;      // +0x10
    uint32_t  count;     // +0x14
    void*     data;      // +0x18
    CollNode_s00a5_86d0* chain;     // +0x1c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Pair_s00a5_86d0 { CollNode_s00a5_86d0* node; CollNode_s00a5_86d0** bucket; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollPool {
    bool Init(int count, void* a, void* b);     // 0xa57750 thiscall ret 0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollTable_s00a5_86d0 {
    char        pad0[4];        // +0x00
    CollNode_s00a5_86d0**  mBuckets;       // +0x04
    unsigned    mBucketCount;   // +0x08
    unsigned    mElems;         // +0x0c
    unsigned    f10;            // +0x10
    unsigned    f14;            // +0x14
    unsigned    f18;            // +0x18
    char        pad1c[0xc];     // +0x1c .. +0x27
    CollIAlloc_s00a5_86d0  mAlloc;         // +0x28
    char        pad2c[0xc];     // +0x2c .. +0x37
    CollNode_s00a5_86d0*   mBegin;         // +0x38
    CollNode_s00a5_86d0*   mEnd;           // +0x3c
    CollNode_s00a5_86d0*   mFree;          // +0x40
    unsigned    mCount;         // +0x44
    unsigned    mHigh;          // +0x48
    unsigned    mSize;          // +0x4c
    CollNode_s00a5_86d0*   mSpecial;       // +0x50

    CollPool*     pool()        { return (CollPool*)((char*)this + 0x1c); }
    bool          Init(int count, void* a, void* b);             // 0xa58950
    void          Destroy();                                     // 0xa589e0
    Pair_s00a5_86d0*         Lookup(Pair_s00a5_86d0* out, CollNode_s00a5_86d0* key);              // 0xa57a20
    CollNode_s00a5_86d0*     AllocNode(CollNode_s00a5_86d0* src);                      // 0xa57aa0
    void          FreeList(CollNode_s00a5_86d0** v, unsigned n);            // 0xa57af0
    Pair_s00a5_86d0*         EraseNode(CollNode_s00a5_86d0* key, CollNode_s00a5_86d0** bucket, Pair_s00a5_86d0* out); // 0xa583e0
    void*         InsertIns(CollNode_s00a5_86d0* key, void* a, void* b);    // 0xa58480
    void          FreeChains(unsigned count);                    // 0xa57900
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FixedPool_s00a5_86d0 {
    char        pad0[0xc];      // +0x00
    CollIAlloc_s00a5_86d0  mAlloc;         // +0x0c
    char        pad10[0xc];     // +0x10 .. +0x1b
    void*       mBegin;         // +0x1c
    void*       mEnd;           // +0x20
    void*       mFree;          // +0x24
    unsigned    mCount;         // +0x28

    bool Init(unsigned size, int count, void* a, void* b);  // 0xa53210 thiscall ret 0x10
    void Destroy();                                         // 0xa531b0
    void* Alloc();                                          // 0xa532b0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollList {
    CollList* next;             // +0x00
    CollList* prev;             // +0x04
    void Destroy();             // 0x620230
    void FUN_00a58a70(CollList* other, Atom key);
    void FUN_00a58fa0(Atom key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct CollRecv_s00a5_86d0 {
    char        pad0[0x10];     // +0x00 (two fixed vectors)
    CollList    listA;          // +0x10
    char        pad18[0x78];    // +0x18 .. +0x8f
    CollList    listB;          // +0x90
    char        pad98[0x88];    // +0x98 .. +0x11f
    FixedPool_s00a5_86d0   mPool;          // +0x120
    CollTable_s00a5_86d0   mTable;         // +0x150
    CollList    mList;          // +0x1a4
    char        pad1ac[4];      // +0x1ac
    unsigned    mMaxA;          // +0x1ac
    unsigned    mMaxB;          // +0x1b0
    unsigned    mInitMax;       // +0x1b4

    void  FUN_00a586d0(Atom key);                                // erase one key
    void  FUN_00a587a0();                                        // clear
    bool  FUN_00a58950(int count, void* a, void* b);             // table init
    void  FUN_00a589e0();                                        // table destroy
    bool  FUN_00a58b00(unsigned a, unsigned b, void* alloc);
    void  FUN_00a58ba0(Atom key, unsigned count, void* data);
    void  FUN_00a59150();                                        // destructor
    CollRecv_s00a5_86d0* FUN_00a592f0(void* arg);                           // constructor
};
}
}
}
// ---- items of slice s00a586d0 end

// ---- items of slice s00a59690 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_9690 { void* s_name; void* s_name2; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* obj, void* a, void* b);                                      // 0x00a49d30
}
}
}
using EA::Audio::Eapd::t_symbol_s00a5_9690;
#define g_spPdintClass    (*(void**)0x0167562cu)
#define g_gFloatSymbol    (*(t_symbol_s00a5_9690*)0x016758c4u)
#define g_gFloatSymbol2   (*(void**)0x016758c8u)
#define g_gOutletCount    (*(int*)0x0167545cu)
struct PdObject
{
    uint32_t pad_00[3];     // +0x00
    void*    pOb;           // +0x0c  (points at a struct whose +0x08 is the outlet list head)
    uint32_t pad_10[6];     // +0x10
    uint32_t mAt28;         // +0x28
    uint32_t mAt2c;         // +0x2c
};
void* FUN_00a598f0(float f);
void  FUN_00a59940(PdObject* o);
void  FUN_00a599a0(PdObject* o, float v);
// ---- items of slice s00a59690 end

// ---- items of slice s00a5c460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_c460 {
    int a;                              // 0x00
    int b;                              // 0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {                         // 12 bytes
    int a_type;                         // 0x00
    t_symbol_s00a5_c460 s;                         // 0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_alist {
    t_class* cls;                       // 0x00
    int count;                          // 0x04
    t_atom* atoms;                      // 0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int size, const char* name);                           // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void freebytes(void* p, int size);                                    // 0x00a49650
}
}
}
// ---- items of slice s00a5c460 end

// ---- items of slice s00a5d3c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_d3c0 {
    const char* s_name;     // +0x00
    void* s_thing;          // +0x04
};
}
}
}
using EA::Audio::Eapd::t_symbol_s00a5_d3c0;
void* pd_new(void* c);
void* outlet_new(void* x, const char* type, void* sel);
void* floatinlet_new(void* x, void* val);
void outlet_float(void* outlet, float f);
void* clock_new(void* owner, void* fn);
void clock_free(void* clk);
void clock_delay(void* clk, float del);
void* getbytes(int size, const char* tag);
void freebytes(void* ptr, int size);
void* g_makenoteClass_16756b8;
t_symbol_s00a5_d3c0 g_floatSymbol_16758c4;         // "float"
int g_outletCount_167545c;
void* makenote_new(float f1, float f2);
void makenote_free_all(void* x);
void makenote_float(void* x, float f);
void makenote_release_all(void* x);
void makenote_tick(void* t);
// ---- items of slice s00a5d3c0 end

// ---- items of slice s00a5e0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_e0f0 {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom_s00a5_e0f0 {
    int a_type;
    union {
        float    w_float;
        t_symbol_s00a5_e0f0 w_symbol;
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_e0f0 gFloatSymbol_s00a5_e0f0;               // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spPrintClass;               // 0x16756bc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spRandomClass;              // 0x16756c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_e0f0* gensym(t_symbol_s00a5_e0f0* out, const char* s);                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new7(t_symbol_s00a5_e0f0 name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2);               // 0xa48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addsymbol(t_class* c, void* fn);                              // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addlist(t_class* c, void* fn);                                // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addanything(t_class* c, void* fn);                            // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* owner, t_symbol_s00a5_e0f0 s);                              // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RandomLinearCongruential {
    char pad[0x2c];
    unsigned RandomUint32Uniform();            // 0x9360b0
    unsigned RandomUint32UniformN(unsigned n); // 0xa68fb0
    void     SetSeed(unsigned seed);           // 0x936090
    float    NextFloat();                      // 0xa69020 (thiscall)
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern RandomLinearCongruential sSystemRandom;   // 0x16756fc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void postargs(int argc, t_atom_s00a5_e0f0* argv, char* buf, int n);  // 0xa46bc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* print_new(t_symbol_s00a5_e0f0 s);                      // 0xa5eb50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  sys_gui(const char* cmd);                  // 0xc2e4e0
}
}
}
// ---- items of slice s00a5e0f0 end

// @ 0x00a52000
namespace EA { namespace Audio { namespace Eapd {
bool audio_objects_init()
{
    bool ok = true;
    ok &= a_play_setup();
    ok &= a_group_setup();
    ok &= a_control_setup();
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a52020
namespace EA { namespace Audio { namespace Eapd {
double mtof(float f)
{
    if (f <= -1500)
        return 0;
    else if (f > 1499) {
        double r = mtof(1499);
        return r;
    }
    else
        return expf_(0.0577622650f * f) * 8.17579891564f;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a52080
void* __cdecl FUN_00a52080()
{
  void* p = EA::Audio::Eapd::pd_new(spMtofClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52170
void* __cdecl FUN_00a52170()
{
  void* p = EA::Audio::Eapd::pd_new(spFtomClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52230
void* __cdecl FUN_00a52230()
{
  void* p = EA::Audio::Eapd::pd_new(spRmstodbClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a522f0
void* __cdecl FUN_00a522f0()
{
  void* p = EA::Audio::Eapd::pd_new(spPowtodbClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a523b0
void* __cdecl FUN_00a523b0()
{
  void* p = EA::Audio::Eapd::pd_new(spDbtopowClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52490
void* __cdecl FUN_00a52490()
{
  void* p = EA::Audio::Eapd::pd_new(spDbtormsClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52780
void __cdecl FUN_00a52780(char* obj)
{
  if (*(int*)(obj + 0x28) != (int)gEmptySymbol.s_name) {
    int r = ((VoiceManager*)EA::Audio::Eapd::GetVoiceManager())
              ->Add(*(int*)(obj + 0x28), *(int*)(obj + 0x2c), obj + 0x30);
    obj[0x34] = (char)r;
  }
}

// @ 0x00a527b0
void __cdecl FUN_00a527b0(char* obj, int sym, int a)
{
  obj[0x34] = 0;
  *(int*)(obj + 0x28) = sym;
  *(int*)(obj + 0x2c) = a;
  if (sym != (int)gEmptySymbol.s_name) {
    int r = ((VoiceManager*)EA::Audio::Eapd::GetVoiceManager())
              ->Add(*(int*)(obj + 0x28), *(int*)(obj + 0x2c), obj + 0x30);
    obj[0x34] = (char)r;
  }
}

// @ 0x00a52840
void __cdecl FUN_00a52840(char* obj, int a, int b, int argc, int* argv)
{
  if (argc == 1 && obj[0x34] != 0) {
    VoiceManager* vm = (VoiceManager*)EA::Audio::Eapd::GetVoiceManager();
    if (*argv == 1)
      vm->S19(*(int*)(obj + 0x30), a, b);
    else if (*argv == 2)
      vm->S18(*(int*)(obj + 0x30), a, b, argv[1], argv[2]);
  }
}

// @ 0x00a528b0
void __cdecl FUN_00a528b0(char* obj, int a, int b, int argc, int* argv)
{
  if (argc >= 1 && *argv == 2)
    FUN_00a52840(obj, argv[1], argv[2], argc - 1, argv + 3);
}

// @ 0x00a529c0
void* __thiscall CM_Hash::GetPair(void* out)
{
  int a = v18;
  *(int*)out = a;
  int b = v1c;
  *(int*)((char*)out + 4) = b;
  return out;
}

// @ 0x00a529e0
void* __cdecl FUN_00a529e0(int a, int b, int argc, int* argv)
{
  void* inst = EA::Audio::Eapd::canvas_getcurrentinstance();
  if (argc < 1 || *argv != 2)
    return 0;
  int v1 = argv[1];
  int v2 = argv[2];
  char* p = (char*)EA::Audio::Eapd::pd_new(spGroupClass);
  if (!p)
    return 0;
  void* out = EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  *(void**)(p + 0x28) = out;
  *(int*)(p + 0x2c) = v1;
  *(int*)(p + 0x30) = v2;
  int g = FUN_00a65360(v1, v2, argc - 1, argv + 3);
  *(int*)(p + 0x34) = g;
  *(void**)(p + 0x38) = inst;
  if (*(int*)(p + 0x28) != 0 && g != 0)
    return p;
  EA::Audio::Eapd::pd_free(p);
  return 0;
}

// @ 0x00a52a90
void __cdecl FUN_00a52a90(char* obj)
{
  if (*(int*)(obj + 0x34) != 0)
    ((GroupHelper*)*(void**)(obj + 0x38))
        ->FreeGroup(*(int*)(obj + 0x2c), *(int*)(obj + 0x30), *(int*)(obj + 0x34));
}

// @ 0x00a52f70
void* __thiscall GroupHelp::Init(int b)
{
  v0 = 0;
  v1 = 0;
  v2 = 0;
  dummy = 0x1454fac;
  v10 = *(int*)(b + 4);
  v14 = (int)"EAPd/Group";
  return this;
}

// @ 0x00a53450
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void VoiceList::Clear()
{
    VoiceNode* node = (VoiceNode*)mNode.mpNext;
    while (node != (VoiceNode*)&mNode) {
        VoiceNode* cur = node;
        node = (VoiceNode*)node->mpNext;
        --mPool.mnCurrentSize;
        if ((void*)cur >= mPool.mpPoolBegin && (void*)cur < mPool.mpPoolEnd) {
            *(void**)cur = mPool.mpHead;
            mPool.mpHead = cur;
        } else {
            mPool.mOverflowAllocator.v0c(cur);
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53490
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void ParamTable::FreeBuckets(ParamNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        ParamNode* node = buckets[i];
        while (node != 0) {
            ParamNode* cur = node;
            node = cur->mpNext;
            if (cur != (ParamNode*)mAllocator.mpBucketBuffer) {
                --mAllocator.mnCurrentSize;
                if ((void*)cur >= mAllocator.mpPoolBegin && (void*)cur < mAllocator.mpPoolEnd) {
                    *(void**)cur = mAllocator.mpHead;
                    mAllocator.mpHead = cur;
                } else {
                    mAllocator.mOverflowAllocator.v0c(cur);
                }
            }
        }
        buckets[i] = 0;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53500
namespace EA { namespace Audio { namespace Eapd {
void Play::SetPaused(bool b)
{
    if (mbPaused != b) {
        mbPaused = b;
        VoiceNode* n = (VoiceNode*)mVoices.mNode.mpNext;
        while (n != (VoiceNode*)&mVoices.mNode) {
            unsigned v = n->mValue;
            if (((bool (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned))(*(void***)mVoiceManager)[8])((VoiceManager_s00a5_2ff0)mVoiceManager, v))
                ((void (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned, bool))(*(void***)mVoiceManager)[4])((VoiceManager_s00a5_2ff0)mVoiceManager, v, b);
            n = (VoiceNode*)n->mpNext;
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53560
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void artists_play_setpausedf(t_play* x, float f)
{
    x->play.SetPaused(f != 0.0f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a535a0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void VoiceList::PopFront()
{
    VoiceNode* cur = (VoiceNode*)mNode.mpNext;
    cur->mpPrev->mpNext = cur->mpNext;
    cur->mpNext->mpPrev = cur->mpPrev;
    --mPool.mnCurrentSize;
    if ((void*)cur >= mPool.mpPoolBegin && (void*)cur < mPool.mpPoolEnd) {
        *(void**)cur = mPool.mpHead;
        mPool.mpHead = cur;
    } else {
        mPool.mOverflowAllocator.v0c(cur);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a535e0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE ParamNode* ParamTable::AllocNode(const ParamPair* v)
{
    ParamNode* node = (ParamNode*)mAllocator.mpHead;
    if (node != 0) {
        mAllocator.mpHead = node->mpNext;
    } else {
        node = (ParamNode*)mAllocator.mOverflowAllocator.v08(mAllocator.mnNodeSize);
    }
    if (node != 0) {
        ++mAllocator.mnCurrentSize;
        if (mAllocator.mnCurrentSize > mAllocator.mnPeakSize)
            mAllocator.mnPeakSize = mAllocator.mnCurrentSize;
        node->mValue = *v;
        node->mpNext = 0;
    }
    return node;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53640
namespace EA { namespace Audio { namespace Eapd {
NOINLINE ParamIter::ParamIter(ParamTable* t)
{
    mpTable = t;
    mpVftable = (void*)0x1454fdc;
    ParamNode** p = t->mpBucketArray;
    ParamNode* n = *p;
    mpNode = n;
    mpBucket = p;
    if (n == 0) {
        mpBucket = p + 1;
        ParamNode* m = p[1];
        while (m == 0) {
            mpBucket += 1;
            m = *mpBucket;
        }
        mpNode = *mpBucket;
    }
    ParamNode** end = t->mpBucketArray + t->mnBucketCount;
    mpLast = *end;
    mpBucketEnd = end;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a536a0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE unsigned ParamIter::Next(Symbol* out, ParamPair* value)
{
    ParamNode* node = mpNode;
    if (node == mpLast)
        return 0;
    *out = node->mValue.first;
    unsigned r;
    switch (node->mValue.a_type) {
    case 1:
        value->a_type = 0;
        value->a_float = node->mValue.a_float;
        r = 1;
        break;
    case 2:
        value->a_type = 1;
        value->a_float = node->mValue.a_float;
        value->a_sym2 = node->mValue.a_sym2;
        r = 1;
        break;
    default:
        r = 0;
        break;
    }
    ParamNode* next = node->mpNext;
    mpNode = next;
    while (next == 0) {
        mpBucket = mpBucket + 1;
        next = *mpBucket;
        mpNode = next;
    }
    return r;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53730
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void ParamTable::Bucket(void** out, const Symbol* key, void* a3, void* a4)
{
    (void)a3; (void)a4;
    ParamNode** base = mpBucketArray;
    unsigned idx = key->mHash % mnBucketCount;
    ParamNode** slot = base + idx;
    ParamNode* node = *slot;
    while (node != 0) {
        if (node->mValue.first.mHash == key->mHash) {
            out[0] = node;
            out[1] = slot;
            return;
        }
        node = node->mpNext;
    }
    slot = base + mnBucketCount;
    out[0] = *slot;
    out[1] = slot;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a537e0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void Play::UpdatePlaying()
{
    VoiceNode* node = (VoiceNode*)mVoices.mNode.mpNext;
    while (node != (VoiceNode*)&mVoices.mNode) {
        unsigned v = node->mValue;
        if (((bool (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned))(*(void***)mVoiceManager)[8])((VoiceManager_s00a5_2ff0)mVoiceManager, v))
            ((void (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned))(*(void***)mVoiceManager)[3])((VoiceManager_s00a5_2ff0)mVoiceManager, v);
        node = (VoiceNode*)node->mpNext;
        VoiceNode* cur = (VoiceNode*)node->mpPrev;
        cur->mpPrev->mpNext = cur->mpNext;
        cur->mpNext->mpPrev = cur->mpPrev;
        --mVoices.mPool.mnCurrentSize;
        if ((void*)cur >= mVoices.mPool.mpPoolBegin && (void*)cur < mVoices.mPool.mpPoolEnd) {
            *(void**)cur = mVoices.mPool.mpHead;
            mVoices.mPool.mpHead = cur;
        } else {
            mVoices.mPool.mOverflowAllocator.v0c(cur);
        }
    }
    mnBusyVoices = 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53860
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void Play::SetPlaying()
{
    VoiceNode* node = (VoiceNode*)mVoices.mNode.mpNext;
    while (node != (VoiceNode*)&mVoices.mNode) {
        bool playing = ((bool (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned))(*(void***)mVoiceManager)[8])
                           ((VoiceManager_s00a5_2ff0)mVoiceManager, node->mValue);
        node = (VoiceNode*)node->mpNext;
        if (!playing) {
            VoiceNode* cur = (VoiceNode*)node->mpPrev;
            cur->mpPrev->mpNext = cur->mpNext;
            cur->mpNext->mpPrev = cur->mpPrev;
            --mVoices.mPool.mnCurrentSize;
            if ((void*)cur >= mVoices.mPool.mpPoolBegin && (void*)cur < mVoices.mPool.mpPoolEnd) {
                *(void**)cur = mVoices.mPool.mpHead;
                mVoices.mPool.mpHead = cur;
            } else {
                mVoices.mPool.mOverflowAllocator.v0c(cur);
            }
            --mnBusyVoices;
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a538d0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void artists_play_updateplaying(t_play* x)
{
    x->play.UpdatePlaying();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53970
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void VoiceList_CopyCtor(VoiceList* dst, FixedPool* src)
{
    dst->mNode.mpNext = 0;
    dst->mNode.mpPrev = 0;
    *(void**)&dst->mPool.mInitAllocator = g_allocVftable;
    dst->mPool.mInitAllocator.mpCoreAllocator = src->mInitAllocator.mpCoreAllocator;
    dst->mPool.mInitAllocator.mpNamePtr = src->mInitAllocator.mpNamePtr;
    *(void**)&dst->mPool.mOverflowAllocator = g_allocVftable;
    dst->mPool.mOverflowAllocator.mpCoreAllocator = src->mOverflowAllocator.mpCoreAllocator;
    dst->mPool.mOverflowAllocator.mpNamePtr = src->mOverflowAllocator.mpNamePtr;
    dst->mPool.mnNodeSize = src->mnNodeSize;
    dst->mPool.mpPoolBegin = src->mpPoolBegin;
    dst->mPool.mpPoolEnd = src->mpPoolEnd;
    dst->mPool.mpHead = src->mpHead;
    dst->mPool.mnCurrentSize = src->mnCurrentSize;
    dst->mPool.mnPeakSize = src->mnPeakSize;
    dst->mNode.mpNext = &dst->mNode;
    dst->mNode.mpPrev = &dst->mNode;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a539d0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE int artists_play_step(void* self)
{
    int r = 0;
    if (self != 0) {
        t_play* x = *(t_play**)((char*)self + 0xc);
        if (x != 0) {
            ((Play*)((char*)x + 0x28))->SetPlaying();
            if (x->play.mnBusyVoices == 0) {
                x->pUpdateCallback = 0;
                outlet_bang(x->pDoneOutlet);
            } else {
                r = 1;
            }
        }
    }
    return r;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53a20
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void VoiceList::PushBack(ListLink* anchor, const unsigned* value2)
{
    VoiceNode* node = (VoiceNode*)mPool.mpHead;
    if (node != 0) {
        mPool.mpHead = node->mpNext;
    } else {
        node = (VoiceNode*)mPool.mOverflowAllocator.v08(mPool.mnNodeSize);
    }
    if (node != 0) {
        ++mPool.mnCurrentSize;
        if (mPool.mnCurrentSize > mPool.mnPeakSize)
            mPool.mnPeakSize = mPool.mnCurrentSize;
    }
    if (&node->mValue != 0)
        node->mValue = *value2;
    node->mpNext = anchor;
    node->mpPrev = anchor->mpPrev;
    anchor->mpPrev->mpNext = node;
    anchor->mpPrev = node;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53a80
namespace EA { namespace Audio { namespace Eapd {
NOINLINE unsigned Play::GetParam(void* outAtom, Symbol key)
{
    ParamNode* node = 0;
    mParameters.Bucket((void**)&node, &key, 0, 0);
    ParamPair* out = (ParamPair*)outAtom;
    if (node == (ParamNode*)mParameters.mpBucketArray[mParameters.mnBucketCount])
        return 0;
    if (node->mValue.a_type == 1) {
        out->a_type = 0;
        out->a_float = node->mValue.a_float;
        return 1;
    }
    if (node->mValue.a_type == 2) {
        out->a_type = 1;
        out->a_float = node->mValue.a_float;
        out->a_sym2 = node->mValue.a_sym2;
        return 1;
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53b90
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool Play::Init(unsigned maxVoices, unsigned maxParams, void* a3, void* a4)
{
    InitAllocator rec;
    rec.vftable = (void*)0x1454fac;
    rec.field4 = 0;
    rec.name = g_eapdAlloc;
    bool r = mVoices.mPool.Init(0xc, maxParams, &rec, &rec);
    if (r) {
        r = FUN_00a65e40(a4, (void*)maxVoices, &rec) != 0;
    }
    mnMaxParameters = maxVoices;
    mnMaxVoices = maxParams;
    return r;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53c20
namespace EA { namespace Audio { namespace Eapd {
NOINLINE ParamPair* ParamTable::LocateOrInsert(const Symbol* key)
{
    unsigned it[2];
    FUN_00a3b2c0(it, key);
    ParamNode* found = (ParamNode*)it[0];
    if (found == (ParamNode*)mpBucketArray[mnBucketCount]) {
        ParamPair tmp;
        tmp.first = *key;
        tmp.a_type = 0;
        tmp.a_float = 0.0f;
        tmp.a_sym2 = 0;
        FUN_00a65bb0(this, &tmp, 0);
    }
    return (ParamPair*)((char*)found + 8);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53c90
namespace EA { namespace Audio { namespace Eapd {
void* VoiceList_InitFromName(void* dst, void* name)
{
    PoolForCtor local;
    local.vftable0 = 0;
    local.field4 = 0;
    local.name0 = name;
    local.vftable1 = (void*)0;
    local.field4b = 0;
    local.name1 = name;
    local.nodeSize = 0;
    local.poolBegin = 0;
    local.poolEnd = 0;
    local.head = 0;
    local.curSize = 0;
    local.peakSize = 0;
    VoiceList_CopyCtor((VoiceList*)dst, (FixedPool*)&local);
    ((FixedPool*)&local)->~FixedPool();
    return dst;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53e60
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void Play::ParamEvent(Symbol key, ParamPair* atom)
{
    SetPlaying();
    if (mbUpdatePlaying && mnBusyVoices != 0) {
        VoiceManager_s00a5_2ff0 vm = (VoiceManager_s00a5_2ff0)mVoiceManager;
        unsigned last = ((VoiceNode*)mVoices.mNode.mpPrev)->mValue;
        bool ok;
        if (atom->a_type == 1) {
            ok = ((bool (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned, unsigned, const char*, float))
                  (*(void***)vm)[7])(vm, last, key.mHash, key.mpName, atom->a_float);
        } else if (atom->a_type == 2) {
            ok = ((bool (__thiscall*)(VoiceManager_s00a5_2ff0, unsigned, unsigned, const char*, float, const char*))
                  (*(void***)vm)[6])(vm, last, key.mHash, key.mpName, atom->a_float, atom->a_sym2);
        } else {
            char buf[1000];
            atom_string(atom, buf, 1000);
            return;
        }
        if (!ok || mParameters.mnElementCount >= mnMaxParameters) {
            char buf[1000];
            atom_string(atom, buf, 1000);
            return;
        }
    }
    ParamPair* slot = mParameters.LocateOrInsert(&key);
    slot->a_type = atom->a_type;
    slot->a_float = atom->a_float;
    slot->a_sym2 = atom->a_sym2;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53f90
namespace EA { namespace Audio { namespace Eapd {
void play_free(t_play_s00a5_3f90* x)
{
    PlayUpdateManager* mgr = (PlayUpdateManager*)Play_GetUpdateManager();
    if (x->pUpdateCallback)
        mgr->RemoveCallback(x->pUpdateCallback);
    ((PlayDtorStub*)&x->play)->Destroy();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53fc0
namespace EA { namespace Audio { namespace Eapd {
void play_anything(t_play_s00a5_3f90* x, uint32_t selHash, const char* selName, int argc, PgAtomArg* argv)
{
    char buf[1000];
    if (argc == 1)
        ((Play_s00a5_3f90*)((char*)x + 0x28))->Dolist(selHash, selName, argv);
    else
        AtomsToString(argc, argv, buf, 1000);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54890
namespace EA { namespace Audio { namespace Eapd {
void add_bang(FAtom* x)
{
    Broadcast(x, x->mF1 + x->mF2);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a548f0
namespace EA { namespace Audio { namespace Eapd {
void add_float(FAtom* x, float f)
{
    float v = x->mF2;
    x->mF1 = f;
    float r = v + f;
    Broadcast(x, r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a549b0
namespace EA { namespace Audio { namespace Eapd {
void sub_bang(FAtom* x)
{
    Broadcast(x, x->mF1 - x->mF2);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54a10
namespace EA { namespace Audio { namespace Eapd {
void sub_float(FAtom* x, float f)
{
    x->mF1 = f;
    Broadcast(x, f - x->mF2);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54ad0
namespace EA { namespace Audio { namespace Eapd {
void mul_bang(FAtom* x)
{
    Broadcast(x, x->mF1 * x->mF2);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54b30
namespace EA { namespace Audio { namespace Eapd {
void mul_float(FAtom* x, float f)
{
    float v = x->mF2;
    x->mF1 = f;
    float r = v * f;
    Broadcast(x, r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54bf0
namespace EA { namespace Audio { namespace Eapd {
void div_bang(FAtom* x)
{
    float d = x->mF2;
    float f = 0.0f;
    if (d != 0.0f)
        f = x->mF1 / d;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54c60
namespace EA { namespace Audio { namespace Eapd {
void div_float(FAtom* x, float f)
{
    float d = x->mF2;
    x->mF1 = f;
    if (d != 0.0f)
        f = f / d;
    else
        f = 0.0f;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54d30
namespace EA { namespace Audio { namespace Eapd {
void pow_bang(FAtom* x)
{
    float f;
    if (x->mF1 > 0.0f)
        f = (float)pow((double)x->mF1, (double)x->mF2);
    else
        f = 0.0f;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54db0
namespace EA { namespace Audio { namespace Eapd {
void pow_float(FAtom* x, float f)
{
    float d = x->mF2;
    x->mF1 = f;
    if (f > 0.0f)
        f = (float)pow((double)f, (double)d);
    else
        f = 0.0f;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54e80
namespace EA { namespace Audio { namespace Eapd {
void max_bang(FAtom* x)
{
    float f;
    if (x->mF1 > x->mF2)
        f = x->mF1;
    else
        f = x->mF2;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54ef0
namespace EA { namespace Audio { namespace Eapd {
void max_float(FAtom* x, float f)
{
    x->mF1 = f;
    float r;
    if (f > x->mF2)
        r = f;
    else
        r = x->mF2;
    Broadcast(x, r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a54fb0
namespace EA { namespace Audio { namespace Eapd {
void min_bang(FAtom* x)
{
    float f;
    if (x->mF1 < x->mF2)
        f = x->mF1;
    else
        f = x->mF2;
    Broadcast(x, f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a55020
namespace EA { namespace Audio { namespace Eapd {
void min_float(FAtom* x, float f)
{
    x->mF1 = f;
    float r;
    if (f < x->mF2)
        r = f;
    else
        r = x->mF2;
    Broadcast(x, r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a550e0
void __cdecl getEq(tOutNode* n)
{ nodeBroadcast(n, (float)(n->mValue == n->mOperand)); }

// @ 0x00a55150
void __cdecl setEq(tOutNode* n, float v)
{
    float rhs = n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)(v == rhs));
}

// @ 0x00a55220
void __cdecl getNe(tOutNode* n)
{ nodeBroadcast(n, (float)(n->mValue != n->mOperand)); }

// @ 0x00a55290
void __cdecl setNe(tOutNode* n, float v)
{
    float rhs = n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)(v != rhs));
}

// @ 0x00a55360
void __cdecl getGt(tOutNode* n)
{
    nodeBroadcast(n, (float)(n->mValue > n->mOperand));
}

// @ 0x00a553d0
void __cdecl setGt(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (v > n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a554a0
void __cdecl getGe(tOutNode* n)
{
    int r = (n->mOperand > n->mValue) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55510
void __cdecl setGe(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (n->mOperand > v) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a555e0
void __cdecl getLt(tOutNode* n)
{
    int r = (n->mValue >= n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55650
void __cdecl setLt(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (v >= n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55720
void __cdecl getLe(tOutNode* n)
{
    int r = (n->mOperand >= n->mValue) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55790
void __cdecl setLe(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (n->mOperand >= v) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55860
void __cdecl getBitAnd(tOutNode* n)
{
    nodeBroadcast(n, (float)((int)n->mOperand & (int)n->mValue));
}

// @ 0x00a558d0
void __cdecl setBitAnd(tOutNode* n, float v)
{
    n->mValue = v;
    nodeBroadcast(n, (float)((int)n->mOperand & (int)v));
}

// @ 0x00a55990
void __cdecl getDiv(tOutNode* n)
{
    int a = (int)n->mValue;
    nodeBroadcast(n, (float)((a != 0) && ((int)n->mOperand != 0)));
}

// @ 0x00a55a10
void __cdecl setDiv(tOutNode* n, float v)
{
    n->mValue = v;
    int a = (int)v;
    nodeBroadcast(n, (float)((a != 0) && ((int)n->mOperand != 0)));
}

// @ 0x00a55ae0
void __cdecl getBitOr(tOutNode* n)
{
    nodeBroadcast(n, (float)((int)n->mOperand | (int)n->mValue));
}

// @ 0x00a55b50
void __cdecl setBitOr(tOutNode* n, float v)
{
    n->mValue = v;
    nodeBroadcast(n, (float)((int)n->mOperand | (int)v));
}

// @ 0x00a55c10
void __cdecl getAndL(tOutNode* n)
{
    int a = (int)n->mValue;
    nodeBroadcast(n, (float)((a != 0) || ((int)n->mOperand != 0)));
}

// @ 0x00a55c80
void __cdecl setAndL(tOutNode* n, float v)
{
    n->mValue = v;
    int a = (int)v;
    nodeBroadcast(n, (float)((a != 0) || ((int)n->mOperand != 0)));
}

// @ 0x00a55d50
void __cdecl getShl(tOutNode* n)
{
    int r = (int)n->mValue << (int)n->mOperand;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55dc0
void __cdecl setShl(tOutNode* n, float v)
{
    int sh = (int)n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)((int)v << sh));
}

// @ 0x00a55e80
void __cdecl getShr(tOutNode* n)
{
    int r = (int)n->mValue >> (int)n->mOperand;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55ef0
void __cdecl setShr(tOutNode* n, float v)
{
    int sh = (int)n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)((int)v >> sh));
}

// @ 0x00a55fb0
void __cdecl getMod(tOutNode* n)
{
    int d = (int)n->mOperand;
    if (d == 0)
        d = 1;
    nodeBroadcast(n, (float)((int)n->mValue % d));
}

// @ 0x00a56030
void __cdecl setMod(tOutNode* n, float v)
{
    int d = (int)n->mOperand;
    n->mValue = v;
    if (d == 0)
        d = 1;
    nodeBroadcast(n, (float)((int)v % d));
}

// @ 0x00a56100
void __cdecl getFmod(tOutNode* n)
{
    int d = (int)n->mOperand;
    if (d < 0)
        d = -d;
    else if (d == 0)
        d = 1;
    int r = (int)n->mValue % d;
    if (r < 0)
        r += d;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a56180
void __cdecl setFmod(tOutNode* n, float v)
{
    n->mValue = v;
    getFmod(n);
}

// @ 0x00a561f0
void __cdecl getIntDiv(tOutNode* n)
{
    int d = (int)n->mOperand;
    int num = (int)n->mValue;
    if (d < 0)
        d = -d;
    else if (d == 0)
        d = 1;
    if (num < 0)
        num += (1 - d);
    nodeBroadcast(n, (float)(num / d));
}

// @ 0x00a56270
void __cdecl setIntDiv(tOutNode* n, float v)
{
    n->mValue = v;
    getIntDiv(n);
}

// @ 0x00a56290
int __cdecl spSinClassFactory()
{
    int r = EA::Audio::Eapd::pd_new_s00a5_50e0((void*)DAT_016755d4);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a56320
int __cdecl spCosClassFactory()
{
    int r = EA::Audio::Eapd::pd_new_s00a5_50e0((void*)DAT_016755a4);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a563b0
int __cdecl spTanClassFactory()
{
    int r = EA::Audio::Eapd::pd_new_s00a5_50e0((void*)DAT_016755cc);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a56460
namespace EA { namespace Audio { namespace Eapd {
void* atan_new()
{
    void* x = pd_new(spAtanClass);
    if (x) {
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a564f0
namespace EA { namespace Audio { namespace Eapd {
void* atan2_new()
{
    void* x = pd_new(spAtan2Class);
    if (x) {
        floatinlet_new(x, (char*)x + 0x28);
        *(float*)((char*)x + 0x28) = 0.0f;
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a56540
namespace EA { namespace Audio { namespace Eapd {
void atan2_float(void* x, float f)
{
    float r;
    if (f == 0.0f && *(float*)((char*)x + 0x28) == 0.0f)
        r = 0.0f;
    else
        r = (float)atan2((double)f, (double)*(float*)((char*)x + 0x28));
    outlet_cnt(*(t_outlet**)((char*)x + 0xc), r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a565d0
namespace EA { namespace Audio { namespace Eapd {
void* sqrt_new()
{
    void* x = pd_new(spSqrtClass);
    if (x) {
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a56670
namespace EA { namespace Audio { namespace Eapd {
void* log_new()
{
    void* x = pd_new(spLogClass);
    if (x) {
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a56720
namespace EA { namespace Audio { namespace Eapd {
void* exp_new()
{
    void* x = pd_new(spExpClass);
    if (x) {
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a567e0
namespace EA { namespace Audio { namespace Eapd {
void* abs_new()
{
    void* x = pd_new(spAbsClass);
    if (x) {
        outlet_new(x, gFloatSymbol_s00a5_6460);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a56870
namespace EA { namespace Audio { namespace Eapd {
void* clip_new(float f1, float f2)
{
    void* x = pd_new(spClipClass);
    if (x) {
        floatinlet_new(x, (char*)x + 0x28);
        floatinlet_new(x, (char*)x + 0x2c);
        outlet_new(x, gFloatSymbol_s00a5_6460);
        *(float*)((char*)x + 0x28) = f1;
        *(float*)((char*)x + 0x2c) = f2;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a568d0
namespace EA { namespace Audio { namespace Eapd {
void clip_float(void* x, float f)
{
    float lo = *(float*)((char*)x + 0x28);
    float r;
    if (lo > f) {
        r = lo;
    } else {
        float hi = *(float*)((char*)x + 0x2c);
        if (f > hi) r = hi;
        else r = f;
    }
    outlet_cnt(*(t_outlet**)((char*)x + 0xc), r);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a576c0
namespace EA { namespace Audio { namespace Eapd {
CollObject* CollReadNew(unsigned a, unsigned b)
{
    CollObject* x = (CollObject*)pd_new((void*)gCollReadClass);
    if (x) {
        x->mKeyA = a;
        x->mKeyB = b;
        outlet_new(x, gListSymbol.mHash, gListSender.mHash);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57700
namespace EA { namespace Audio { namespace Eapd {
void CollWriteNew(unsigned a, unsigned b)
{
    CollObject* x = (CollObject*)pd_new((void*)gCollWriteClass);
    if (x) {
        x->mKeyA = a;
        x->mKeyB = b;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57730
namespace EA { namespace Audio { namespace Eapd {
void CollSetKey(CollObject* x, unsigned a, unsigned b)
{
    x->mKeyA = a;
    x->mKeyB = b;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57900
namespace EA { namespace Audio { namespace Eapd {
void CollTable::FreeChains(unsigned count)
{
    CollNode** tmp = NewBuckets(count);
    for (unsigned i = 0; i < mBucketCount; ++i) {
        while (mBuckets[i]) {
            CollNode* node = mBuckets[i];
            mBuckets[i] = node->next;
            unsigned h = HashOf(node);
            node->next = tmp[h % count];
            tmp[h % count] = node;
        }
    }
    CollNode** old = mBuckets;
    if (mBucketCount > 1 && old != (CollNode**)mSpecial) {
        --mCount;
        if (old >= (CollNode**)mBegin && old < (CollNode**)mEnd) {
            *(CollNode**)old = mFree;
            mFree = (CollNode*)old;
        } else {
            mAlloc.Free(old);
        }
    }
    mBuckets = tmp;
    mBucketCount = count;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a579d0
namespace EA { namespace Audio { namespace Eapd {
CollNode* CollTable::Find(CollNode* head, CollNode* key, unsigned h)
{
    (void)h;
    if (head) {
        do {
            if (key->type == head->type) {
                if (key->type == 1) {
                    if (*(float*)&key->value == *(float*)&head->value)
                        return head;
                } else if (key->type == 2 && key->value == head->value) {
                    return head;
                }
            }
            head = head->next;
        } while (head);
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57aa0
namespace EA { namespace Audio { namespace Eapd {
CollNode* CollTable::AllocNode(CollNode* src)
{
    CollNode* p = mFree;
    if (p)
        mFree = *(CollNode**)p;
    else
        p = (CollNode*)mAlloc.Alloc(mElemSize);
    if (p) {
        ++mCount;
        if (mCount > mHigh)
            mHigh = mCount;
        p->k0 = src->k0;
        p->k1 = src->k1;
        p->type = src->type;
        p->value = src->value;
        p->sym = src->sym;
        p->count = src->count;
        p->items = src->items;
    }
    p->next = 0;
    return p;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57af0
namespace EA { namespace Audio { namespace Eapd {
void CollTable::FreeList(CollNode** v, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        CollNode* node = v[i];
        while (node) {
            CollNode* cur = node;
            node = cur->next;
            if (cur != mSpecial) {
                --mCount;
                if (cur < mBegin || cur >= mEnd) {
                    mAlloc.Free(cur);
                } else {
                    *(CollNode**)cur = mFree;
                    mFree = cur;
                }
            }
        }
        v[i] = 0;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57b60
namespace EA { namespace Audio { namespace Eapd {
bool CollRecv::LookupKey(uint32_t a0, uint32_t a1, uint32_t a2, int* outA, int* outB)
{
    CollNode key;
    key.k0 = 0;
    key.k1 = 0;
    key.type = a0;
    key.value = a1;
    key.sym = a2;
    Pair p;
    mTable.Lookup(&p, &key);
    if (mTable.mBuckets[mTable.mBucketCount] != p.node) {
        *outA = p.node->count;
        *outB = (int)p.node->items;
        return true;
    }
    return false;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57be0
namespace EA { namespace Audio { namespace Eapd {
bool CollRecv::LookupIndex(uint32_t a0, uint32_t a1, uint32_t a2, int idx, void* out)
{
    int count;
    int items;
    if (!LookupKey(a0, a1, a2, &count, &items))
        return false;
    if (idx <= 0)
        return false;
    if (idx > count)
        return false;
    uint32_t* src = (uint32_t*)items + (idx - 1) * 3;
    ((uint32_t*)out)[0] = src[0];
    ((uint32_t*)out)[1] = src[1];
    ((uint32_t*)out)[2] = src[2];
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57da0
namespace EA { namespace Audio { namespace Eapd {
void List_(void* x, t_symbol_s00a5_76c0 s, int argc, void* atoms)
{
    (void)s;
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    if (argc == 0) {
        ++gOutletCount;
        if (gOutletCount < 1000) {
            OutletNode* n = ((OutletList*)r->mOutlets2)->head;
            if (n) {
                float v = (float)(int)r->mTable.mElems;
                do {
                    outlet_float(n->target, v);
                    n = n->next;
                } while (n);
            }
        }
        --gOutletCount;
        return;
    }
    if (argc != 1)
        return;
    int local;
    uint32_t* a = (uint32_t*)atoms;
    if (r->LookupKey(a[0], a[1], a[2], &argc, &local)) {
        float v = (float)argc;
        ++gOutletCount;
        if (gOutletCount < 1000) {
            OutletNode* n = ((OutletList*)r->mOutlets2)->head;
            if (n) {
                do {
                    outlet_float(n->target, v);
                    n = n->next;
                } while (n);
            }
        }
        --gOutletCount;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57ea0
namespace EA { namespace Audio { namespace Eapd {
void DoInt(void* x, t_symbol_s00a5_76c0 s, int argc, void* atoms)
{
    (void)s;
    if (argc != 2)
        return;
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    uint32_t buf[3];
    int idx = atom_getint((char*)atoms + 0xc, buf);
    if (r->LookupIndex(a[0], a[1], a[2], idx, buf))
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, 1, buf);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a57f20
namespace EA { namespace Audio { namespace Eapd {
void Output(void* x)
{
    CollRecv* r = (CollRecv*)((char*)x + 0x30);
    RingNode* sentinel = &r->mSentinel;
    ListItem* n = (ListItem*)sentinel->next;
    while (n != (ListItem*)sentinel) {
        if (n->type == 2) {
            outlet_symbol(r->mOutlets, n->value, n->sym);
        } else {
            float v = *(float*)&n->value;
            ++gOutletCount;
            if (gOutletCount < 1000) {
                for (OutletNode* o = r->mOutlets->head; o; o = o->next)
                    outlet_float(o->target, v);
            }
            --gOutletCount;
        }
        CollNode key;
        key.k0 = 0;
        key.k1 = 0;
        key.type = n->type;
        key.value = n->value;
        key.sym = n->sym;
        int outA = 0, outB = 0;
        r->LookupKey(n->type, n->value, n->sym, &outA, &outB);
        outlet_list(r->mOutlets2, gListSymbol.mHash, gListSender.mHash, outA, (void*)outB);
        n = (ListItem*)n->next;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58040
namespace EA { namespace Audio { namespace Eapd {
void PdFloat_(void* x, float f)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* r = (CollRecv*)((char*)o + 0x30);
        uint32_t fbits = *(uint32_t*)&f;
        uint32_t unused;
        uint32_t u = *(volatile uint32_t*)&unused;
        int outA = 0, outB = 0;
        if (r->LookupKey(1, fbits, u, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                        gListSender.mHash, outA, (void*)outB);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a580d0
namespace EA { namespace Audio { namespace Eapd {
void PdSymbol_(void* x, uint32_t a, uint32_t b)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o) {
        CollRecv* r = (CollRecv*)((char*)o + 0x30);
        int outA = 0, outB = 0;
        if (r->LookupKey(2, a, b, &outA, &outB))
            outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                        gListSender.mHash, outA, (void*)outB);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58150
namespace EA { namespace Audio { namespace Eapd {
void PdLength(void* x, t_symbol_s00a5_76c0 s, int argc, void* atoms)
{
    (void)s;
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    OutletList* ol = *(OutletList**)((char*)x + 0xc);
    if (argc == 0) {
        ++gOutletCount;
        if (gOutletCount < 1000 && ol) {
            float v = (float)*(int*)((char*)o + 0x18c);
            for (OutletNode* n = ol->head; n; n = n->next)
                outlet_float(n->target, v);
        }
        --gOutletCount;
        return;
    }
    if (argc != 1)
        return;
    CollRecv* r = (CollRecv*)((char*)o + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    int count = 0, items = 0;
    if (r->LookupKey(a[0], a[1], a[2], &count, &items)) {
        ++gOutletCount;
        if (gOutletCount < 1000 && ol) {
            float v = (float)count;
            for (OutletNode* n = ol->head; n; n = n->next)
                outlet_float(n->target, v);
        }
        --gOutletCount;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58260
namespace EA { namespace Audio { namespace Eapd {
void PdNth(void* x, t_symbol_s00a5_76c0 s, int argc, void* atoms)
{
    (void)s;
    if (argc != 2)
        return;
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (!o)
        return;
    CollRecv* r = (CollRecv*)((char*)o + 0x30);
    uint32_t* a = (uint32_t*)atoms;
    uint32_t buf[3];
    int idx = atom_getint((char*)atoms + 0xc, buf);
    if (r->LookupIndex(a[0], a[1], a[2], idx, buf))
        outlet_list(*(void**)((char*)x + 0xc), gListSymbol.mHash,
                    gListSender.mHash, 1, buf);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a583e0
namespace EA { namespace Audio { namespace Eapd {
Pair* CollTable::EraseNode(Pair* out, CollNode* key, CollNode** bucket)
{
    CollNode* n = key->next;
    out->bucket = bucket;
    out->node = n;
    while (!n) {
        ++bucket;
        n = *bucket;
        out->node = n;
    }
    CollNode* head = *bucket;
    if (head == key) {
        *bucket = head->next;
    } else {
        CollNode* prev = head;
        CollNode* cur = head->next;
        while (cur != key) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
    }
    if (key != mSpecial) {
        --mCount;
        if (key >= mBegin && key < mEnd) {
            *(CollNode**)key = mFree;
            mFree = key;
            --mElems;
            return out;
        }
        mAlloc.Free(key);
    }
    --mElems;
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a586d0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void CollRecv_s00a5_86d0::FUN_00a586d0(Atom key)
{
    CollTable_s00a5_86d0* t = &mTable;
    CollNode_s00a5_86d0 k2;
    k2.prev = 0;
    k2.next = 0;
    k2.keyType = key.a;
    k2.keyA = key.b;
    k2.keyB = key.c;
    Pair_s00a5_86d0 p;
    t->Lookup(&p, &k2);
    if (p.node != t->mBuckets[t->mBucketCount]) {
        CollNode_s00a5_86d0* n = p.node;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->prev = 0;
        n->next = 0;
        void* data = n->data;
        --mPool.mCount;
        if (data >= mPool.mBegin && data < mPool.mEnd) {
            *(void**)data = mPool.mFree;
            mPool.mFree = data;
        } else {
            mPool.mAlloc.Free(data);
        }
        t->EraseNode(n, p.bucket, &p);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58890
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a58890(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    if (argc == 1) {
        Atom a = *argv;
        ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a586d0(a);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a588c0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a588c0(void* x)
{
    ((CollRecv_s00a5_86d0*)((char*)x + 0x30))->FUN_00a587a0();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a588d0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a588d0(void* x, uint32_t, const char*, int argc, Atom* argv)
{
    if (argc == 1) {
        void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                                 *(uint32_t*)((char*)x + 0x2c), gCollClass);
        if (o) {
            Atom a = *argv;
            ((CollRecv_s00a5_86d0*)((char*)o + 0x30))->FUN_00a586d0(a);
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a58920
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void FUN_00a58920(void* x)
{
    void* o = pd_findbyclass(*(uint32_t*)((char*)x + 0x28),
                             *(uint32_t*)((char*)x + 0x2c), gCollClass);
    if (o)
        ((CollRecv_s00a5_86d0*)((char*)o + 0x30))->FUN_00a587a0();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a598f0
void* FUN_00a598f0(float f)
{
    void* o = EA::Audio::Eapd::pd_new(g_spPdintClass);
    if (o != 0)
    {
        *(float*)((char*)o + 0x28) = f;
        EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2);
        EA::Audio::Eapd::floatinlet_new(o, (char*)o + 0x28);
    }
    return o;
}

// @ 0x00a59940
void FUN_00a59940(PdObject* o)
{
    float f = *(float*)&o->mAt28;
    int n = g_gOutletCount + 1;
    if (n >= 1000)
        return;
    g_gOutletCount = n;
    for (void* p = *(void**)((char*)o->pOb + 8); p != 0; p = *(void**)p)
        EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), (float)(int)f);
    --g_gOutletCount;
}

// @ 0x00a599a0
void FUN_00a599a0(PdObject* o, float v)
{
    o->mAt28 = *(uint32_t*)&v;
    int n = g_gOutletCount + 1;
    if (n >= 1000)
        return;
    g_gOutletCount = n;
    for (void* p = *(void**)((char*)o->pOb + 8); p != 0; p = *(void**)p)
        EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), (float)(int)v);
    --g_gOutletCount;
}

// @ 0x00a5c8e0
namespace EA { namespace Audio { namespace Eapd {
void alist_anything(t_alist* self, t_symbol_s00a5_c460 sel, int argc, t_atom* argv)
{
    if (self->atoms != 0)
        freebytes(self->atoms, self->count * sizeof(t_atom));
    self->atoms = (t_atom*)getbytes((argc + 1) * sizeof(t_atom), "EAPd/t_list_atoms");
    if (self->atoms == 0) {
        self->count = 0;
        return;
    }
    self->count = argc + 1;
    self->atoms[0].a_type = 2;
    self->atoms[0].s = sel;
    if (argc <= 0)
        return;
    for (int i = 0; i < argc; ++i)
        self->atoms[i + 1] = argv[i];
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5da60
void* makenote_new(float f1, float f2)
{
    void* x = pd_new(g_makenoteClass_16756b8);
    if (x != 0)
    {
        void* f2inlet = (char*)x + 0x2c;
        *(float*)((char*)x + 0x28) = f1;
        *(float*)f2inlet = f2;
        floatinlet_new(x, (char*)x + 0x28);
        floatinlet_new(x, f2inlet);
        *(void**)((char*)x + 0x30) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x34) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(int*)((char*)x + 0x38) = 0;
    }
    return x;
}

// @ 0x00a5dae0
void makenote_tick(void* t)
{
    void** tick = (void**)t;
    int* x = (int*)tick[3];

    g_outletCount_167545c++;
    if (g_outletCount_167545c < 1000)
    {
        for (void** o = *(void***)(x[0x34 / 4] + 8); o != 0; o = (void**)*o)
            outlet_float(o[1], 0.0f);
    }
    float value = ((float*)tick)[2];
    if (g_outletCount_167545c < 1000)
    {
        for (void** o = *(void***)(x[0x30 / 4] + 8); o != 0; o = (void**)*o)
            outlet_float(o[1], value);
    }
    g_outletCount_167545c--;

    void** prev = (void**)x[0x38 / 4];
    if (prev == tick)
    {
        x[0x38 / 4] = (int)tick[1];
    }
    else
    {
        for (void** cur = (void**)prev[1]; cur != 0; cur = (void**)cur[1])
        {
            if (cur == tick)
            {
                prev[1] = cur[1];
                break;
            }
            prev = cur;
        }
    }
    clock_free(tick[0]);
    freebytes(tick, 0x10);
}

// @ 0x00a5dbd0
void makenote_float(void* x, float f)
{
    float velocity = *(float*)((char*)x + 0x28);
    if (velocity != 0.0f)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x34) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], velocity);
        }
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], f);
        }
        g_outletCount_167545c--;

        void** tick = (void**)getbytes(0x10, "EAPd/t_hang");
        tick[1] = *(void**)((char*)x + 0x38);
        *(void***)((char*)x + 0x38) = tick;
        ((float*)tick)[2] = f;
        tick[3] = x;
        tick[0] = clock_new(tick, (void*)makenote_tick);

        float delay = *(float*)((char*)x + 0x2c);
        if (delay >= 0.0f)
            clock_delay(tick[0], delay);
        else
            clock_delay(tick[0], 0.0f);
    }
}

// @ 0x00a5dcf0
void makenote_release_all(void* x)
{
    void** tick = *(void***)((char*)x + 0x38);
    while (tick != 0)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x34) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], 0.0f);
        }
        float value = ((float*)tick)[2];
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], value);
        }
        g_outletCount_167545c--;

        *(void***)((char*)x + 0x38) = (void**)tick[1];
        clock_free(tick[0]);
        freebytes(tick, 0x10);
        tick = *(void***)((char*)x + 0x38);
    }
}

// @ 0x00a5ddc0
void makenote_free_all(void* x)
{
    void** tick = *(void***)((char*)x + 0x38);
    while (tick != 0)
    {
        *(void***)((char*)x + 0x38) = (void**)tick[1];
        clock_free(tick[0]);
        freebytes(tick, 0x10);
        tick = *(void***)((char*)x + 0x38);
    }
}

// @ 0x00a5eb50
namespace EA { namespace Audio { namespace Eapd {
void* print_new(t_symbol_s00a5_e0f0 s)
{
    char* x = (char*)pd_new(spPrintClass);
    if (x) {
        if (s.mpName[0] != '\0') {
            *(t_symbol_s00a5_e0f0*)(x + 0x28) = s;
        } else {
            t_symbol_s00a5_e0f0 sym;
            *(t_symbol_s00a5_e0f0*)(x + 0x28) = *gensym(&sym, "print");
        }
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ebb0
namespace EA { namespace Audio { namespace Eapd {
void print_anything(char* x, t_symbol_s00a5_e0f0 s, int argc, t_atom_s00a5_e0f0* argv)
{
    char buf[1000];
    postargs(argc, argv, buf, 1000);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ebe0
namespace EA { namespace Audio { namespace Eapd {
bool print_setup()
{
    t_symbol_s00a5_e0f0 s;
    t_symbol_s00a5_e0f0* sym;

    sym = gensym(&s, "print");
    spPrintClass = class_new7(*sym, (void*)print_new, (void*)0, 0x30, 0, 6, 0);
    bool ok = spPrintClass != 0;
    ok &= class_addbang(spPrintClass, (void*)sys_gui);
    ok &= class_doaddfloat(spPrintClass, (void*)sys_gui);
    ok &= class_addsymbol(spPrintClass, (void*)sys_gui);
    ok &= class_addlist(spPrintClass, (void*)print_anything);
    ok &= class_addanything(spPrintClass, (void*)print_anything);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ec90
namespace EA { namespace Audio { namespace Eapd {
unsigned random_uniform(unsigned n)
{
    return sSystemRandom.RandomUint32UniformN(n);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ecb0
namespace EA { namespace Audio { namespace Eapd {
void random_seed(unsigned seed)
{
    sSystemRandom.SetSeed(seed);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ece0
namespace EA { namespace Audio { namespace Eapd {
void* random_new(float f)
{
    char* x = (char*)pd_new(spRandomClass);
    if (x) {
        *(float*)(x + 0x28) = f;
        (*(RandomLinearCongruential*)(x + 0x2c)).SetSeed(sSystemRandom.RandomUint32Uniform());
        floatinlet_new(x, x + 0x28);
        outlet_new(x, gFloatSymbol_s00a5_e0f0);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd
