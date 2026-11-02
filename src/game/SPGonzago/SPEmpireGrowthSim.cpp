// src/game/SPGonzago/SPEmpireGrowthSim.cpp -- migrated from slice(s) s0138d560, s00fe8630, s00ad6960, s00fea240 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEmpireGrowthSim.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cPropertyList.h"
#include "SP/cStarManager.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern char sEmptyString;      // 0x013ec47c
extern char sGameModeSpace;                       // 0x01654c05
extern float g_TickRate;                           // 0x0145c19c
#include <stddef.h>
#include <string.h>
#include <new>
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cEmpire.h"
#include <math.h>

// ---- items of slice s00fea240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rule {
    float baseValue;        // +0x00
    float weights[10];      // +0x04
};
struct RuleVector {
    Rule* mpBegin;          // +0x00
    Rule* mpEnd;            // +0x04
    Rule* mpCapacity;       // +0x08
    uint32_t mAllocPad0;    // +0x0c
    Rule* mpBuffer;         // +0x10
    uint32_t mAllocPad1;    // +0x14
    Rule mBuffer[18];       // +0x18 (0x318 bytes)

    Rule* erase(Rule* first, Rule* last);
    void insert(Rule* pos, uint32_t n, const Rule* value);
    void resize(uint32_t newSize);
};
void* AllocateBlocks(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void FreeArray(void* p);                                                                          // 0x00f47380
Rule* CopyRange(Rule* first, Rule* last, Rule* dst);                                             // 0x00b3d890
void FillConstruct(Rule* dst, uint32_t n, const Rule* value);                                    // 0x00fe8df0
void UninitCopy(void* out, Rule* first, Rule* last, Rule* dst, Rule* tag);                        // 0x00fe8db0
void CopyBackward(Rule* first, Rule* last, Rule* dst);                                            // 0x00fe8f20
void DestroyRange(Rule* first, Rule* last, const Rule* value);                                    // 0x00fe8d80
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
void CopyStrings(void* src, void* end, void* dst); // 0x007c8b70
struct Property {
    void* mpData;        // +0x00
    uint32_t mPad04;
    uint32_t mCount;     // +0x08
    uint32_t mPad0c;
    uint16_t mFlags;     // +0x10
    uint16_t mType;      // +0x12
    int* GetInt();       // 0x0041e990
};
struct cPropertyList {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t key, Property** out); // +0x24
    uint32_t mPad04[11];       // +0x04..0x30
    int mModificationCount;    // +0x30
    int mDescriptionCount;     // +0x34
    int GetModificationCount(); // 0x006237a0
};
struct IPropertyManager {
    virtual void m00();
    virtual void m04();
    virtual void m08();
    virtual void m0c();
    virtual void m10();
    virtual void m14();
    virtual void m18();
    virtual void m1c();
    virtual void m20();
    virtual void m24();
    virtual void m28();
    virtual void m2c(uint32_t a, uint32_t b, cPropertyList** out); // +0x2c
};
bool TryGetUIntProperty(cPropertyList* pl, uint32_t key, void* out); // 0x00410370
namespace EA {
namespace ArgScript {
struct cCommandBase_s00fe_a240 {
    cCommandBase_s00fe_a240();                              // 0x0083c800
    virtual void Execute(void* args);            // slot 0
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    void* mpParser;      // +0x04
    void* mpState;       // +0x08
    uint32_t mRefCount;  // +0x0c
};
}
}
namespace EA {
namespace ArgScript {
struct cArgumentSpec_s00fe_a240 {
    uint8_t mData[0xc8];
    cArgumentSpec_s00fe_a240(bool flag);                              // 0x0083a9f0
    void Parse(void* args, void* parser);                  // 0x0083b9d0
};
}
}
void ConstructSpec(EA::ArgScript::cArgumentSpec_s00fe_a240* spec, const char* name, ...); // 0x0083bcd0
class BehaviorRule : public EA::ArgScript::cCommandBase_s00fe_a240 {
public:
    BehaviorRule();
    virtual void Execute(void* args);

    EA::ArgScript::cArgumentSpec_s00fe_a240 mArgSpec; // +0x10
    float mBaseValue;          // +0xd8
    float mNearMe;             // +0xdc
    float mNearEnemy;          // +0xe0
    float mNearNeutral;        // +0xe4
    float mNearAlly;           // +0xe8
    float mEmpireStars;        // +0xec
    float mEmpireColonies;     // +0xf0
    float mFriend;             // +0xf4
    float mEnemy;              // +0xf8
    float mRelationship;       // +0xfc
    float mPlayer;             // +0x100
    char* mActionName;         // +0x104
    char* mColorName;          // +0x108
};
struct Vec {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAlloc0;    // +0x0c
    uint32_t mAlloc1;    // +0x10
    void Reserve(uint32_t n);        // 0x004cd3c0
};
class cGonzagoSimulator {
public:
    cGonzagoSimulator();   // 0x00b5b6c0
    void* mpVtable0;       // +0x00
    uint32_t mPad04;       // +0x04
    void* mpVtable8;       // +0x08
    uint32_t mPad0c;       // +0x0c
};
struct StringVector {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    void StringVectorResize(uint32_t n); // 0x00553be0
};
class cEmpireGrowthSim : public cGonzagoSimulator {
public:
    cEmpireGrowthSim();
    void OnTick(uint32_t dtLo, uint32_t dtHi);
    void TakeTurn(uint32_t empireID);                 // 0x00fe9580
    bool IsPlayerProtected();                         // 0x00fe8990
    uint8_t FillOutBehaviorRules(uint32_t mode, StringVector* list);

    Vec mStarColorWeights;            // +0x10
    Vec mStarRelationshipModifier;    // +0x24
    uint64_t mElapsedTimeSinceLastTick; // +0x38
    uint64_t mElapsedTimeInContext;     // +0x40
    uint8_t mbPaused;                 // +0x48
    uint8_t mbTickPaused;             // +0x49
    uint16_t mPad4a;                  // +0x4a
    int mMinTimeMin;                  // +0x4c
    int mMaxTimeMin;                  // +0x50
    int mInitForcedTurnCount;         // +0x54
    int mForcedTurnCount;             // +0x58
    int mLastContext;                 // +0x5c
    Vec mEmpireStack;                 // +0x60
    uint32_t mPad74;                  // +0x74
    Vec mEmpireIDs;                   // +0x78
    uint32_t mPad8c;                  // +0x8c
    cPropertyList* mpPropList;        // +0x90
    int mPropListModCount;            // +0x94
    RuleVector mRuleSet[3];           // +0x98 (0x990 bytes)
};
void* GetCurrentGameMode();                       // 0x00b5b800
int GetUniverseContext();                         // 0x01021080
void* StarManager(void* arg);                     // 0x00b3d2a0
void* GetAvatar(void* record);                    // 0x00b1fdb0
void* GetEmpireByID(void* avatar);                // 0x00ba9370
void* GetPlayerEmpire();                          // 0x01021300
uint32_t GetItemInstanceID(void* item);           // 0x00c87040
void* MessageServer();                            // 0x0067dcc0
void InsertSet(Vec* set, void* out, void* value); // 0x00554020
void FUN_00d04080(void* rp);                       // 0x00d04080
void* RelationshipManager(Vec* set);               // 0x00b3d2c0
void DestroyRecordList(void* p);                   // 0x00ae6970
void FUN_00555bc0(void* a, void* b, void* c);      // 0x00555bc0
void FUN_007c81c0(void* a, void* b, void* c);      // 0x007c81c0
void* CreateParser();                              // 0x008408d0
void* AllocateBehaviorRule(uint32_t size);         // 0x006abeb0
void PlayoutBehavior(BehaviorRule* rule, const char* text);              // 0x00fe8b90
IPropertyManager* PropertyManager();                    // 0x0067de30
struct StarQuery {
    void* FUN_00c8b360();                          // 0x00c8b360
};
StarQuery* FUN_01021230(void* out, void* params);  // 0x01021230
struct cStarManager {
    void* GetStarRecords();                        // 0x00bb1080
};
struct IMessageServer {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14(uint32_t id, int a, int b);   // +0x14
};
struct IParser {
    virtual void Reset();                          // 0x00
    virtual void Destroy();                        // 0x04
    virtual void s08();                            // 0x08
    virtual void s0c();                            // 0x0c
    virtual void s10();                            // 0x10
    virtual void s14(const char* name, BehaviorRule* rule, void* extra); // 0x14
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34(uint32_t flag);               // 0x34
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual bool s50(const char* text);            // 0x50
};
// ---- items of slice s00fea240 end

// ---- items of slice s00ad6960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete(void* p);                              // 0xf47380
typedef unsigned char  byte;
struct CArgCmd2 {
    void FUN_00ad6960(void* a);
    void FUN_00ad6bc0(void* a);
    void* FUN_00ad6ec0(byte flags);
    void* FUN_00ad6f10(byte flags);
};
struct ArgSpecDtor { void dtor(); };                                  // 0x405050
struct CmdBaseDtor { void dtor(); };                                  // 0x83c750
// ---- items of slice s00ad6960 end

// ---- items of slice s00fe8630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gTypeTable[];                         // 0x15b46d0
extern "C" void operator_delete__(void* p);          // 0x00f47380
extern "C" void* __stdcall StarManagerTake(void* cities);        // 0x00b3d2a0
typedef unsigned int   u32;
struct RefObj { virtual void AddRef(); virtual void Release(); };
struct StarRecord : RefObj {
    int __thiscall GetAvatar();                  // 0xb1fdb0
};
struct Noun {
    int  __thiscall F801920();                   // 0x801920
    void* __thiscall GetCities();                // 0x5c65e0
    int  __thiscall GetAvatar();                 // 0xb1fdb0
    int  __thiscall GetType();                   // 0xbb9ae0
    u32  __thiscall GetItemInstanceID();         // 0xc87040
};
int __cdecl F_c6fe00(int v);                     // 0xc6fe00
struct Filter {                                  // argument of GetStarRecords
    u32 mask, kind, a, b;
    float two, minusOne;
    u32 z;
};
struct PtrVec {
    StarRecord** b; StarRecord** e; StarRecord** cap;
    PtrVec() : b(0), e(0), cap(0) {}
};
void __cdecl OperatorDeleteArray(void* p);       // 0xf47380 (operator delete[])
struct StarMgr {
    void __thiscall GetStarRecords(void* cities, Filter* f, PtrVec* out);   // 0xbb1080
};
StarMgr* __cdecl StarManager();                  // 0xb3d2a0
struct RelMgr {
    bool  __thiscall Rel1(int a, int b);         // 0xd01f20
    bool  __thiscall Rel2(int a, int b);         // 0xd01fb0
    float __thiscall Rel3(int a, int b, int c);  // 0xd00a10
};
RelMgr* __cdecl RelationshipManager();           // 0xb3d2c0
struct TerrainSphere {
    bool __thiscall Check();                     // 0xc77410
};
struct NounMgr {
    int __thiscall GetPlayerEmpireOrMinus1();    // 0xb1f9d0
    TerrainSphere* __thiscall GetCurrentTerrainSphere();   // 0xf67d90
};
NounMgr* __cdecl NounManager();                  // 0xb3d300
struct SimUniverse {
    int __thiscall EmpireKind(int empire);       // 0x10107b0
};
extern SimUniverse* gSimUniverse;                // 0x16dc798
struct Planet { char pad0[0x58]; int typeIdx; char pad1[0x84 - 0x5c]; int empire; };
struct Wt { float v[11]; };
struct Ent { char pad[0x98]; Wt* w; char pad2[0x330 - 0x9c]; };
static inline const float& MinRef(const float& a, const float& b) { return (b < a) ? b : a; }
static __forceinline float Score(const Wt* w, const float* f, float p4, float p5)
{
    return w->v[7] * f[6] + w->v[8] * f[7] + w->v[6] * f[5] + w->v[5] * f[4] + w->v[4] * f[3]
         + w->v[3] * f[2] + w->v[2] * f[1] + w->v[1] * f[0] + w->v[10] * p5 + w->v[9] * p4 + w->v[0];
}
struct Scorer {
    char pad[0];
    Ent* ents() { return (Ent*)this; }
    void __thiscall Contribute(int idx, int m, int k, float* feats, float* out, int* typeOut);   // 0xfe8cb0
    float __thiscall Evaluate(Noun* item, Planet* pl, int* typeOut, int arg4, int arg5);          // 0xfe8f70
};
struct Brush;                       // fwd (the rule-set is shared with the brush code)
struct RefCounted { virtual void rc00(); virtual void rc04(); };
struct Ent330 {                      // a 0x330-byte rule block
    void* mpBuffer;                  // +0x00
    char  pad04[0x10 - 0x04];
    void* mpCap;                     // +0x10
    char  pad14[0x330 - 0x14];
};
struct cEmpireGrowthSim_s00fe_8630 {
    void*       mpVtbl0;             // +0x00   primary vtable
    u32         pad04[1];
    void*       mpVtbl8;             // +0x08   secondary vtable
    u32         pad0c[1];
    void*       mpBlock10;           // +0x10   refcounted block (count at [p-4])
    char        pad14[0x24 - 0x14];
    void*       mpBlock24;           // +0x24   refcounted block (count at [p-4])
    char        pad28[0x60 - 0x28];
    void*       mpBlock60;           // +0x60
    char        pad64[0x78 - 0x64];
    void*       mpBlock78;           // +0x78
    char        pad7c[0x90 - 0x7c];
    RefCounted* mpRef90;             // +0x90
    char        pad94[0x98 - 0x94];
    Ent330      mBlocks[3];          // +0x98   three rule blocks, stride 0x330

    void  SetWeightsForAction(int rule, int row, int index, const Brush* src);   // 0x00fe8b00
    void  ExpandRules(int row, char* action);                                    // 0x00fe8b90
    ~cEmpireGrowthSim_s00fe_8630();                                                         // 0x00fe8e20
};
struct StarMgr2 { void __thiscall FUN_00bb1200(); };             // 0x00bb1200
struct CivData { void* __thiscall GetCities(float a, void* b); };// 0x005c65e0
struct StarList { char* mBegin; char* mEnd; };
struct cEmpire {
    StarList* __thiscall GetStars();                             // 0x00c308d0
};
void __cdecl FUN_00fe8c50(void* self, int extra, int scale);      // 0x00fe8c50
struct Brush {
    unsigned char b00;                  // +0x00
    char  pad01[3];
    float f04, f08, f0c, f10, f14, f18, f1c, f20;
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    bool __thiscall ShouldGrow();        // 0x00fe8990
    char __thiscall ReadBrush(void* stream);   // 0x00fe8880
    void __thiscall DeriveFields();            // 0x00fe8450
};
extern "C" unsigned FNVHash(const char* s, unsigned seed, int init);  // 0x00932e80
// ---- items of slice s00fe8630 end

// ---- items of slice s0138d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropertyDesc {
    unsigned int name;   // +0x00  const char* (VA)
    unsigned int hash;   // +0x04
    unsigned int size;   // +0x08  byte size of the value
    unsigned int unk0c;  // +0x0c  uninitialised in the original
    unsigned int unk10;  // +0x10  uninitialised in the original
    unsigned int unk14;  // +0x14  uninitialised in the original
    unsigned int fn0;    // +0x18
    unsigned int fn1;    // +0x1c
    unsigned int fn2;    // +0x20
    unsigned int fn3;    // +0x24
    unsigned int fn4;    // +0x28
    unsigned int fn5;    // +0x2c
    unsigned int fn6;    // +0x30
    unsigned int fn7;    // +0x34
    unsigned int fn8;    // +0x38
};
// ---- items of slice s0138d560 end

// @ 0x00ad6f10
void* CArgCmd2::FUN_00ad6f10(byte flags)
{
    void* self = this;
    ((ArgSpecDtor*)((char*)self + 0x10))->dtor();
    ((CmdBaseDtor*)self)->dtor();
    if (flags & 1) operator_delete(self);
    return self;
}

// @ 0x00fe8aa0
namespace SP {
int sIndexFromAction(char const *const id)
{
    unsigned h = FNVHash((const char*)id, 0x811c9dc5u, 1);
    switch (h) {
    case 0x599f0502u: return 3;
    case 0x0ac4aeedu: return 2;
    case 0x4edcc2bfu: return 1;
    case 0x92d53411u: return 0;
    case 0xd1476d98u: return 4;
    default:          return 0;
    }
}
}  // namespace SP

// @ 0x00fe8b00
void cEmpireGrowthSim_s00fe_8630::SetWeightsForAction(int rule, int row, int index, const Brush* src)
{
    float* dst = (float*)((char*)mBlocks[rule].mpBuffer + (index + row * 3) * 0x2c);
    dst[0]  = ((const float*)src)[0xd8 / 4];
    dst[1]  = ((const float*)src)[0xdc / 4];
    dst[2]  = ((const float*)src)[0xe0 / 4];
    dst[3]  = ((const float*)src)[0xe4 / 4];
    dst[4]  = ((const float*)src)[0xe8 / 4];
    dst[5]  = ((const float*)src)[0xf4 / 4];
    dst[6]  = ((const float*)src)[0xf8 / 4];
    dst[7]  = ((const float*)src)[0x100 / 4];
    dst[8]  = ((const float*)src)[0xfc / 4];
    dst[9]  = ((const float*)src)[0xec / 4];
    dst[10] = ((const float*)src)[0xf0 / 4];
}

// @ 0x00fe8c50
void __cdecl FUN_00fe8c50(void* self, int extra, int scale)
{
    StarList* stars = ((cEmpire*)self)->GetStars();
    int n = (int)(stars->mEnd - stars->mBegin) >> 2;
    for (unsigned i = 0; i < (unsigned)n; i++) {
        CivData* item = (CivData*)((void**)stars->mBegin)[i];
        void* cities = item->GetCities((float)scale, (void*)extra);
        StarMgr2* mgr = (StarMgr2*)StarManagerTake(cities);
        mgr->FUN_00bb1200();
    }
}

// @ 0x00fe8cb0
void Scorer::Contribute(int row, int index, int kind, float* feats, float* best, int* typeOut)
{
    const float* w = (const float*)((char*)((cEmpireGrowthSim_s00fe_8630*)this)->mBlocks[row].mpBuffer
                                     + (index + kind * 3) * 0x2c);
    float s = (((((((((w[10] * feats[9] + w[9] * feats[8]) + w[8] * feats[7]) + w[7] * feats[6])
                   + w[6] * feats[5]) + w[5] * feats[4]) + w[4] * feats[3]) + w[3] * feats[2])
                 + w[2] * feats[1]) + w[1] * feats[0]) + w[0];
    if (*best < s) {
        *best = s;
        *typeOut = kind;
    }
}

// @ 0x00fe8e20
cEmpireGrowthSim_s00fe_8630::~cEmpireGrowthSim_s00fe_8630()
{
    mpVtbl0 = (void*)0x01494498;
    mpVtbl8 = (void*)0x01494474;

    Ent330* p = mBlocks + 3;
    for (int i = 2; i >= 0; --i) {
        --p;
        void* buf = p->mpBuffer;
        if (buf != 0 && buf != p->mpCap)
            operator_delete__(buf);
    }

    if (mpRef90 != 0)
        mpRef90->rc04();

    if (mpBlock78 != 0)
        operator_delete__(mpBlock78);
    if (mpBlock60 != 0)
        operator_delete__(mpBlock60);

    if (mpBlock24 != 0 && *((int*)mpBlock24 - 1) != 0)
        operator_delete__(mpBlock24);
    if (mpBlock10 != 0 && *((int*)mpBlock10 - 1) != 0)
        operator_delete__(mpBlock10);

    mpVtbl8 = (void*)0x013eb938;
    mpVtbl0 = (void*)0x013ec458;
}

// @ 0x00fe8f70
float __thiscall Scorer::Evaluate(Noun* item, Planet* pl, int* typeOut, int arg4, int arg5)
{
    *typeOut = 5;
    int idx = gTypeTable[pl->typeIdx];
    int m = F_c6fe00(item->F801920());
    int emp = pl->empire;
    void* cities = item->GetCities();
    float p4 = (float)arg4;
    float p5 = (float)arg5;
    float acc[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    Filter flt;
    flt.mask = 0x1fff; flt.kind = 0x20; flt.a = 0; flt.b = 0; flt.two = 2.0f; flt.minusOne = -1.0f; flt.z = 0;
    PtrVec recs;
    StarManager()->GetStarRecords(cities, &flt, &recs);
    int n = (int)(recs.e - recs.b);
    for (int i = 0; i < n; i++) {
        StarRecord* r = recs.b[i];
        if (r->GetAvatar() == emp) {
            acc[0] += 0.5f;
        } else if (RelationshipManager()->Rel1(emp, r->GetAvatar())) {
            acc[1] += 0.5f;
        } else if (RelationshipManager()->Rel2(emp, r->GetAvatar())) {
            acc[3] += 0.5f;
        } else {
            acc[2] += 0.5f;
        }
    }
    float f[10];
    float one = 1.0f;
    one = 1.0f; f[0] = MinRef(acc[0], one);
    one = 1.0f; f[1] = MinRef(acc[1], one);
    one = 1.0f; f[2] = MinRef(acc[2], one);
    one = 1.0f; f[3] = MinRef(acc[3], one);
    int owner = item->GetAvatar();
    int player = NounManager()->GetPlayerEmpireOrMinus1();
    bool isPlayer = (owner == player);
    if (owner == -1 || owner == emp) {
        f[4] = 0.0f;
        f[5] = 0.0f;
        f[7] = 0.0f;
    } else {
        f[4] = RelationshipManager()->Rel2(emp, owner) ? 1.0f : 0.0f;
        f[5] = RelationshipManager()->Rel1(emp, owner) ? 1.0f : 0.0f;
        f[7] = RelationshipManager()->Rel3(emp, owner, 0);
    }
    f[6] = isPlayer ? 1.0f : 0.0f;
    f[8] = p4;
    f[9] = p5;
    float result = 1.0f;
    int t = item->GetType();
    if (t == 1) {
        const Wt* w = ents()[idx].w + m;
        float s = Score(w, f, p4, p5);
        if (s > 1.0f) { *typeOut = 0; result = s; }
    } else if (item->GetType() == 5) {
        if (owner == emp) {
            if (item->GetItemInstanceID() & 0x100) {
                const Wt* w = ents()[idx].w + (m + 3);
                float s = Score(w, f, p4, p5);
                if (s > 1.0f) { *typeOut = 1; result = s; }
            }
        } else {
            bool go = true;
            if (isPlayer) {
                if (!NounManager()->GetCurrentTerrainSphere()->Check()) go = false;
                else {
                    int kind = gSimUniverse->EmpireKind(pl->empire);
                    if (kind < 2 || kind > 3) go = false;
                }
            }
            if (go) {
                u32 flags = item->GetItemInstanceID();
                if (!(flags & 0x200)) Contribute(idx, m, 2, f, &result, typeOut);
                Contribute(idx, m, 3, f, &result, typeOut);
                Contribute(idx, m, 4, f, &result, typeOut);
            }
        }
    }
    for (StarRecord** p = recs.b; p < recs.e; ++p)
        if (*p) (*p)->Release();
    if (recs.b && ((int*)recs.b)[-1] != 0) OperatorDeleteArray(recs.b);
    return result;
}

// @ 0x00fea240
Rule* RuleVector::erase(Rule* first, Rule* last)
{
    Rule* dst = first;
    Rule* src = last;
    Rule* const end = mpEnd;
    while (src != end)
        *dst++ = *src++;
    mpEnd += last - first;
    return first;
}

// @ 0x00fea2a0
void RuleVector::insert(Rule* pos, uint32_t n, const Rule* value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        int count = (int)(mpEnd - mpBegin);
        uint32_t newCap = (uint32_t)count * 2;
        if (count == 0)
            newCap = 1;
        uint32_t need = (uint32_t)count + n;
        if (need > newCap)
            newCap = need;
        Rule* buf = 0;
        if (newCap)
            buf = (Rule*)AllocateBlocks(newCap * 0x2c, "Simulator", 0, 0, kAllocFile, 0xd1);
        Rule* mid = CopyRange(mpBegin, pos, buf);
        FillConstruct(mid, n, value);
        Rule* end = CopyRange(pos, mpEnd, (Rule*)((char*)mid + n * 0x2c));
        Rule* old = mpBegin;
        if (old != 0 && old != mpBuffer)
            FreeArray(old);
        mpBegin = buf;
        mpEnd = end;
        mpCapacity = (Rule*)((char*)buf + newCap * 0x2c);
    } else if (n != 0) {
        Rule tmp = *value;
        Rule* oldEnd = mpEnd;
        uint32_t after = (uint32_t)(oldEnd - pos);
        if (after <= n) {
            uint32_t extra = n - after;
            FillConstruct(oldEnd, extra, &tmp);
            mpEnd = (Rule*)((char*)mpEnd + extra * 0x2c);
            UninitCopy(pos, pos, oldEnd, mpEnd, pos);
            mpEnd = (Rule*)((char*)mpEnd + after * 0x2c);
            DestroyRange(pos, oldEnd, &tmp);
        } else {
            Rule* split = (Rule*)((char*)oldEnd - n * 0x2c);
            UninitCopy(split, split, oldEnd, oldEnd, pos);
            mpEnd = (Rule*)((char*)mpEnd + n * 0x2c);
            CopyBackward(pos, split, oldEnd);
            DestroyRange(pos, (Rule*)((char*)pos + n * 0x2c), &tmp);
        }
    }
}

// @ 0x00fea460
void RuleVector::resize(uint32_t newSize)
{
    if (newSize > (uint32_t)(mpEnd - mpBegin)) {
        Rule empty;
        empty.baseValue = 0.0f;
        empty.weights[0] = 0.0f;
        empty.weights[1] = 0.0f;
        empty.weights[2] = 0.0f;
        empty.weights[3] = 0.0f;
        empty.weights[4] = 0.0f;
        empty.weights[5] = 0.0f;
        empty.weights[6] = 0.0f;
        empty.weights[7] = 0.0f;
        empty.weights[8] = 0.0f;
        empty.weights[9] = 0.0f;
        insert(mpEnd, newSize - (uint32_t)(mpEnd - mpBegin), &empty);
    } else {
        erase(mpBegin + newSize, mpEnd);
    }
}

// @ 0x00fea510
void cEmpireGrowthSim::OnTick(uint32_t dtLo, uint32_t dtHi)
{
    if (GetCurrentGameMode() != &sGameModeSpace)
        return;
    if (IsPlayerProtected() && mForcedTurnCount == 0)
        return;

    cPropertyList* pl = mpPropList;
    int mod = (pl->mModificationCount == 0) ? 0 : pl->GetModificationCount();
    int stamp = pl->mDescriptionCount + mod;
    if (stamp != mPropListModCount) {
        int mod2 = (pl->mModificationCount == 0) ? 0 : pl->GetModificationCount();
        mPropListModCount = pl->mDescriptionCount + mod2;
        TryGetUIntProperty(pl, 0x429d68c, &mMinTimeMin);
        TryGetUIntProperty(mpPropList, 0x429d69c, &mMaxTimeMin);
    }

    if (mEmpireStack.mpBegin != mEmpireStack.mpEnd) {
        uint32_t empireID = ((uint32_t*)mEmpireStack.mpEnd)[-1];
        mEmpireStack.mpEnd = (char*)mEmpireStack.mpEnd - 4;
        TakeTurn(empireID);
        uint32_t out;
        uint32_t value = empireID;
        InsertSet(&mEmpireIDs, &out, &value);
        return;
    }

    if (mEmpireIDs.mpBegin != mEmpireIDs.mpEnd) {
        void* rp = RelationshipManager(&mEmpireIDs);
        FUN_00d04080(rp);
        mEmpireIDs.mpEnd = mEmpireIDs.mpBegin;
    }

    int ctx = GetUniverseContext();
    uint32_t savedLo = 0;
    uint32_t savedHi = 0;
    if (!IsPlayerProtected()) {
        if ((mLastContext == 2) == (ctx == 2)) {
            mElapsedTimeSinceLastTick += ((uint64_t)dtHi << 32) | dtLo;
        } else {
            savedLo = (uint32_t)mElapsedTimeSinceLastTick;
            savedHi = (uint32_t)(mElapsedTimeSinceLastTick >> 32);
            mElapsedTimeSinceLastTick = 0;
            mLastContext = ctx;
        }
        mElapsedTimeInContext += ((uint64_t)dtHi << 32) | dtLo;
    }

    uint64_t saved = ((uint64_t)savedHi << 32) | savedLo;
    if ((ctx == 2 && (double)mMinTimeMin * (double)g_TickRate <= (double)(int64_t)saved) ||
        ((double)mMaxTimeMin * (double)g_TickRate <= (double)(int64_t)mElapsedTimeInContext) ||
        (mForcedTurnCount != 0)) {
        if (mForcedTurnCount != 0)
            mForcedTurnCount -= 1;

        mElapsedTimeSinceLastTick = 0;
        mElapsedTimeInContext = 0;

        uint8_t q0[0x18] = {0};
        uint8_t q1[0x18] = {0};
        StarQuery* q = FUN_01021230(&q1, &q0);
        void* ctxObj = q->FUN_00c8b360();
        cStarManager* sm = (cStarManager*)StarManager(ctxObj);
        struct StarRecordList {
            void* mpBegin;
            void* mpEnd;
            void* mpCapacity;
        }* recs = (StarRecordList*)sm->GetStarRecords();

        int count = (int)((char*)recs->mpEnd - (char*)recs->mpBegin) >> 2;
        for (int i = 0; i < count; ++i) {
            void* record = ((void**)recs->mpBegin)[i];
            void* avatar = GetAvatar(record);
            void* empire = GetEmpireByID(avatar);
            void* playerEmpire = GetPlayerEmpire();
            if (avatar != *(void**)((char*)playerEmpire + 0x84) &&
                (GetItemInstanceID(record) & 0x100) == 0 &&
                ((*(uint32_t*)((char*)empire + 0x50) >> 6) & 1) == 0) {
                uint32_t out;
                uint32_t value = (uint32_t)(size_t)record;
                InsertSet(&mEmpireIDs, &out, &value);
            }
        }

        if (mEmpireStack.mpBegin != mEmpireStack.mpEnd)
            ((IMessageServer*)MessageServer())->s14(0x609f3d9, 0, 0);
        DestroyRecordList(&q0);
    }
}

// @ 0x00fea840
bool FUN_00fea840(cPropertyList* manager, uint32_t key, uint16_t type, Vec* dst)
{
    if (manager != 0) {
        Property* prop;
        if (manager->GetProperty(key, &prop) &&
            prop->mType == type &&
            (prop->mFlags & 0x10) != 0) {
            uint32_t count = (prop->mFlags & 0x30) ? prop->mCount
                                                   : (uint32_t)(prop->mType != 0);
            void* src = (prop->mFlags & 0x30) ? prop->mpData
                                              : (prop->mType != 0 ? (void*)prop : 0);
            dst->Reserve(count);
            memcpy(dst->mpBegin, src, count * 4);
            return true;
        }
    }
    return false;
}

// @ 0x00fea8d0
bool FUN_00fea8d0(cPropertyList* manager, uint32_t key, uint16_t type, StringVector* dst)
{
    if (manager != 0) {
        Property* prop;
        if (manager->GetProperty(key, &prop) &&
            prop->mType == type &&
            (prop->mFlags & 0x10) != 0) {
            uint32_t count = (prop->mFlags & 0x30) ? prop->mCount
                                                   : (uint32_t)(prop->mType != 0);
            void* src = (prop->mFlags & 0x30) ? prop->mpData
                                              : (prop->mType != 0 ? (void*)prop : 0);
            dst->StringVectorResize(count);
            CopyStrings(src, (char*)src + count * 16, dst->mpBegin);
            return true;
        }
    }
    return false;
}

// @ 0x00fea960
BehaviorRule::BehaviorRule()
: mArgSpec(true) {
    ConstructSpec(&mArgSpec,
                  "Behavior Definition",
                  "<value:float>",
                  &mBaseValue,
                  "base value",
                  "<action:cstring>",
                  &mActionName,
                  "action Type",
                  "-color <name:cstring>",
                  &mColorName,
                  "color of star to deal with",
                  "-nearMe <val:float>",
                  &mNearMe,
                  "value modifier for nearMe",
                  "-nearEnemy <val:float>",
                  &mNearEnemy,
                  "value modifier for nearEnemy",
                  "-nearNeutral <val:float>",
                  &mNearNeutral,
                  "value modifier for nearNeutral",
                  "-nearAlly <val:float>",
                  &mNearAlly,
                  "value modifier for nearAlly",
                  "-relationship <val:float>",
                  &mRelationship,
                  "multiplier for the actual relationship value",
                  "-ally <val:float>",
                  &mFriend,
                  "value modifier for Friendly Star",
                  "-enemy <val:float>",
                  &mEnemy,
                  "value modifier for Enemy Star",
                  "-empireStars <val:float>",
                  &mEmpireStars,
                  "value modifier for number of empire stars",
                  "-empireColonies <val:float>",
                  &mEmpireColonies,
                  "value modifier for number of empire colonies",
                  "-player <val:float>",
                  &mPlayer,
                  "value modifier for player",
                  0);
}

// @ 0x00feaa70
void BehaviorRule::Execute(void* args)
{
    void* parser = mpParser;
    mBaseValue = 0.0f;
    mNearEnemy = 0.0f;
    mNearNeutral = 0.0f;
    mNearAlly = 0.0f;
    mEmpireStars = 0.0f;
    mEmpireColonies = 0.0f;
    mNearMe = 0.0f;
    mFriend = 0.0f;
    mEnemy = 0.0f;
    mPlayer = 0.0f;
    mRelationship = 0.0f;
    mColorName = &sEmptyString;
    mArgSpec.Parse(args, parser);
}

// @ 0x00feab10
uint8_t cEmpireGrowthSim::FillOutBehaviorRules(uint32_t mode, StringVector* list)
{
    IParser* parser = (IParser*)CreateParser();
    if (parser)
        parser->Reset();
    parser->s08();

    BehaviorRule* rule = (BehaviorRule*)AllocateBehaviorRule(0x10c);
    if (rule) {
        rule = new (rule) BehaviorRule();
        rule->v0c();
    }
    parser->s14("data", rule, 0);
    parser->s30();

    bool good = true;
    uint32_t count = (uint32_t)(((char*)list->mpEnd - (char*)list->mpBegin) >> 4);
    for (uint32_t i = 0; i < count; ++i) {
        char* text = *(char**)((char*)list->mpBegin + i * 16);
        if (good)
            good = parser->s50(text);
        PlayoutBehavior(rule, text);
    }

    parser->s34(good ? 1 : 0);
    parser->s0c();
    if (rule)
        rule->v10();
    parser->Destroy();
    return (uint8_t)good;
}

// @ 0x00feacd0
cEmpireGrowthSim::cEmpireGrowthSim()
{
    mpVtable0 = (void*)0x01494498;
    mpVtable8 = (void*)0x01494474;

    mStarColorWeights = Vec();
    mStarRelationshipModifier = Vec();
    mElapsedTimeSinceLastTick = 0;
    mElapsedTimeInContext = 0;
    mbPaused = 0;
    mbTickPaused = 0;
    mMinTimeMin = 0;
    mMaxTimeMin = 0;
    mInitForcedTurnCount = 0;
    mForcedTurnCount = 0;
    mLastContext = -1;
    mEmpireStack = Vec();
    mEmpireIDs = Vec();
    mpPropList = 0;

    for (int i = 0; i < 3; ++i) {
        RuleVector& r = mRuleSet[i];
        r.mpBuffer = r.mBuffer;
        r.mpBegin = r.mBuffer;
        r.mpEnd = r.mBuffer;
        r.mpCapacity = r.mBuffer + 18;
    }

    IPropertyManager* pm = (IPropertyManager*)PropertyManager();
    if (mpPropList) {
        mpPropList = 0;
    }
    pm->m2c(0x249e8357, 0x2ae0c7e, &mpPropList);

    int mod = (mpPropList->mModificationCount == 0) ? 0 : mpPropList->GetModificationCount();
    mPropListModCount = mpPropList->mDescriptionCount + mod;

    Property* prop = 0;
    if (mpPropList->GetProperty(0x429d68c, &prop) && prop->mType == 9)
        mMinTimeMin = *prop->GetInt();
    if (mpPropList->GetProperty(0x429d69c, &prop) && prop->mType == 9)
        mMaxTimeMin = *prop->GetInt();
    if (mpPropList->GetProperty(0x56e61e5, &prop) && prop->mType == 9)
        mInitForcedTurnCount = *prop->GetInt();

    mStarColorWeights.Reserve(3);
    mStarRelationshipModifier.Reserve(9);
    FUN_00fea840(mpPropList, 0x553cc31, 9, &mStarColorWeights);
    FUN_00fea840(mpPropList, 0x553cc32, 9, &mStarRelationshipModifier);

    for (int i = 0; i < 3; ++i)
        mRuleSet[i].resize(0x12);

    void* buf = AllocateBlocks(0xa0, "Simulator", 0, 0, kAllocFile, 0xd1);
    FUN_00555bc0(0, 0, buf);
    FUN_007c81c0(0, 0, buf);

    StringVector list = {};
    list.mpBegin = buf;
    list.mpEnd = buf;
    list.mpCapacity = (char*)buf + 0xa0;

    for (uint32_t i = 0; i < 3; ++i) {
        FUN_00fea8d0(mpPropList, 0x56e61e1 + i, 0x12, &list);
        FillOutBehaviorRules(i, &list);
    }

    if (buf)
        FreeArray(buf);
}

// @ 0x01396440
void init_15b47b8()
{
    static const PropertyDesc desc[6] = {
        { 0x1494838, 0x42a2fbd, 0x38,  0,0,0, 0,0,
          0x692ca0, 0xaff840, 0xaff870, 0x692fd0, 0x694ec0, 0xb1fbf0, 0x595a70 },
        { 0x149481c, 0x5a5bc48, 0x40,  0,0,0, 0,0,
          0x692ca0, 0xaff840, 0xaff870, 0x692fd0, 0x694ec0, 0xb1fbf0, 0x595a70 },
        { 0x1494808, 0x54ffe6e, 0x58,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x14947f8, 0x54ffe6d, 0x5c,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x14947ec, 0x57e1d98, 0x48,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x14947d8, 0x66b6169, 0x49,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15b47b8;
    for (int i = 0; i < 6; ++i)
        dst[i] = desc[i];
}
