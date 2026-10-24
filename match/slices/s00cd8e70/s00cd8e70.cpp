// Slice s00cd8e70 -- SP::cTribeModeStrategy selected-creature bookkeeping, tribe UI refresh
// helpers and the strategy constructor.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

// ------------------------------------------------------------------ small value types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

// ------------------------------------------------------------------ engine objects
struct cSPCreatureBase;
struct cLoco;

struct CreatureList {                                   // eastl::vector<cSPCreatureBase*>
    cSPCreatureBase** mpBegin;                          // +0x00
    cSPCreatureBase** mpEnd;                            // +0x04
    cSPCreatureBase** mpCapacity;                       // +0x08
};

struct cTribe {
    void* mpVtable;                                     // +0x00
    uint32_t mPad04[0x8c];                              // +0x04 .. +0x233
    uint32_t mTribeId;                                  // +0x234
};

struct cGameNounManager {
    cTribe* GetPlayerTribe();                           // 0x00bfc5f0
};

struct cSpeciesManager {
    void* GetAvatarProfile();                           // 0x004df420
};

// Embedded locomotion object (creature + 0xc0); its own vtable, slots addressed raw.
struct cLoco {
    void* mpVtable;                                     // +0x00
    bool CanBeSelected() {
        return ((bool (__thiscall*)(cLoco*))((void**)mpVtable)[0x50 / 4])(this);
    }
};

struct cSPCreatureBase {
    void* mpVtable;                                     // +0x00
    uint32_t mPad04[47];                                // +0x04 .. +0xbf
    cLoco mLoco;                                        // +0xc0
    uint32_t mPadC4[0x29d];                             // +0xc4 .. +0xb37
    uint32_t mNameBegin;                                // +0xb38 (eastl::wstring)
    uint32_t mNameEnd;                                  // +0xb3c
    uint32_t mNameCapacity;                             // +0xb40
};

struct cGonzagoTimer {
    uint32_t mData[8];                                  // 0x20 bytes
};
struct cLocalInputState {
    uint32_t mData[0x48 / 4];                           // 0x48 bytes
};

extern char VT_1477530[];
extern char VT_14426a0[];
extern char VT_13eb394[];
extern char VT_14775f0[];
extern char VT_14775e8[];
extern char VT_1477668[];
extern char VT_1477648[];
extern char VT_1477640[];
class cTribeModeStrategy;
extern cTribeModeStrategy* gpTribeModeStrategy;         // 0x0169b2c8

// ------------------------------------------------------------------ external engine entry points
cGameNounManager* __cdecl NounManager();                // 0x00b3d300
cSpeciesManager*  __cdecl FUN_00401090();               // 0x00401090
void __cdecl FUN_004010a0(void* out, uint32_t id);      // 0x004010a0
void* __cdecl FUN_005ecf80(void* in, uint32_t id);      // 0x005ecf80
void __cdecl FUN_00f47380(void* p);                     // 0x00f47380 operator delete[]
uint32_t __cdecl FUN_00921340(int n);                   // 0x00921340
bool __cdecl FUN_0064f350(uint32_t group, uint32_t id, int mode);  // 0x0064f350
bool __cdecl GetPropertyAsUint32Array(uint32_t group, uint32_t id, uint32_t* count, uint32_t* list); // 0x00401100

struct FixedPoolDesc {                                  // fixed_pool_base scratch descriptor
    uint32_t m00[7];
    void Init(void* begin, int blockSize, int count, int align, int pad);   // 0x00921260
};
void __fastcall cGonzagoSubsystem_ctor(void* p);        // 0x00b5b960
void __fastcall cGonzagoTimer_ctor(void* p);            // 0x00b63890
void __fastcall cLocalInputState_ctor(void* p);         // 0x00697960

// ------------------------------------------------------------------ selected-creature set
struct SelSetIter { void* mp0; void* mp1; };

struct SelSet {
    uint32_t m00;                                       // +0x00
    void*    mpAnchor;                                  // +0x04
    void*    mpAnchorLeft;                              // +0x08
    void*    mpRoot;                                    // +0x0c
    uint32_t mFlags;                                    // +0x10
    uint32_t mCount;                                    // +0x14
    uint32_t m18;                                       // +0x18

    void Initialize();
    ~SelSet() { Nuke(mpRoot); }
    void Nuke(void* root);                              // 0x00eb6280
    void Insert(SelSetIter* out, void* key, bool b);    // 0x00eb62c0
};

inline void SelSet::Initialize()
{
    mpAnchorLeft = 0;
    mpRoot = 0;
    mFlags = 0;
    mpAnchor = &mpAnchor;
    mpAnchorLeft = &mpAnchor;
    mpRoot = 0;
    mFlags = 0;
    mCount = 0;
};

// ------------------------------------------------------------------ record kept by the strategy
struct TribeRecord {                                    // 0x1c bytes
    uint32_t mNameBegin;                                // +0x00 (eastl::wstring)
    uint32_t mNameEnd;                                  // +0x04
    uint32_t mNameCapacity;                             // +0x08
    uint32_t m0c;                                       // +0x0c
    float    mRadius;                                   // +0x10
    int      mId;                                       // +0x14
    void*    mpProfile;                                 // +0x18
};

// ------------------------------------------------------------------ the embedded sub-allocator
struct TribeSub {                                       // lives at strategy + 0xa8
    uint32_t m00;                                       // +0x00
    uint32_t m04;                                       // +0x04
    uint32_t m08;                                       // +0x08
    uint32_t m0c;                                       // +0x0c
    float    m10;                                       // +0x10
    float    m14;                                       // +0x14
    uint32_t m18;                                       // +0x18
    uint32_t mPad1c[6];                                 // +0x1c .. +0x33
    uint32_t m34;                                       // +0x34
    uint32_t mPad38[9];                                 // +0x38 .. +0x5b
    uint32_t mPoolBegin;                                // +0x5c
    uint32_t mPad60[0x16];                              // +0x60 .. +0xbb
    uint32_t mPoolEnd;                                  // +0xbc

    TribeSub* Init(int arg1, int arg2);                 // 0x00cd91e0
    void Configure(int a1, int a2, int a3, int a4, int a5, void* pool);  // 0x00cd6560
    uint32_t PoolSize(uint32_t n);                      // 0x009213c0
    void GrowTo(uint32_t n);                            // 0x00b5d220
};

// ------------------------------------------------------------------ the strategy
class cTribeModeStrategy {
public:
    // Primary vtable: 25 unnamed slots, then the selected-set getter at +0x64.
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual SelSet* GetSelectedCreatureSet(SelSet* out);        // +0x64

    void*    mpVtbl1;                                   // +0x04
    void*    mpVtbl2;                                   // +0x08
    void*    mpVtbl3;                                   // +0x0c
    void*    mpVtbl4;                                   // +0x10
    uint32_t m14;                                       // +0x14
    uint32_t m18;                                       // +0x18
    uint32_t m1c;                                       // +0x1c
    uint32_t m20;                                       // +0x20
    uint32_t m24;                                       // +0x24
    bool     mbInCityHallEditor;                        // +0x28
    bool     mbInAccessoryEditor;                       // +0x29
    uint16_t m2a;                                       // +0x2a
    uint32_t m2c;                                       // +0x2c
    uint32_t m30;                                       // +0x30
    uint32_t m34;                                       // +0x34
    uint32_t m38;                                       // +0x38
    uint32_t m3c;                                       // +0x3c
    uint32_t m40;                                       // +0x40
    uint32_t m44;                                       // +0x44
    uint32_t m48;                                       // +0x48
    uint32_t m4c;                                       // +0x4c
    uint32_t m50;                                       // +0x50
    uint32_t m54;                                       // +0x54
    cGonzagoTimer mTimer;                               // +0x58
    uint32_t m78;                                       // +0x78
    uint32_t m7c;                                       // +0x7c
    uint32_t m80;                                       // +0x80
    uint32_t m84;                                       // +0x84
    uint32_t m88;                                       // +0x88
    uint32_t m8c;                                       // +0x8c
    uint32_t m90;                                       // +0x90
    uint32_t m94;                                       // +0x94
    uint32_t m98;                                       // +0x98
    uint32_t m9c;                                       // +0x9c
    uint32_t ma0;                                       // +0xa0
    uint32_t ma4;                                       // +0xa4
    TribeSub mSub;                                      // +0xa8 .. +0x197
    bool     mb198;                                     // +0x198
    uint32_t m19c;                                      // +0x19c
    float    m1a0;                                      // +0x1a0
    bool     mb1a4;                                     // +0x1a4
    cGonzagoTimer mTimer2;                              // +0x1a8
    uint32_t m1c8;                                      // +0x1c8
    uint32_t m1cc;                                      // +0x1cc
    uint32_t m1d0;                                      // +0x1d0
    uint32_t m1d4;                                      // +0x1d4
    uint32_t m1d8;                                      // +0x1d8
    uint32_t m1dc;                                      // +0x1dc
    cLocalInputState mInput;                            // +0x1e0
    bool     mb228;                                     // +0x228
    uint32_t m22c;                                      // +0x22c
    int32_t  m230;                                      // +0x230
    int32_t  m234;                                      // +0x234
    uint32_t m238;                                      // +0x238
    uint32_t m23c;                                      // +0x23c
    uint32_t m240;                                      // +0x240
    uint32_t m244;                                      // +0x244
    bool     mb248;                                     // +0x248
    bool     mb249;                                     // +0x249
    bool     mb24a;                                     // +0x24a
    uint32_t m24c;                                      // +0x24c
    uint32_t m250;                                      // +0x250
    uint32_t m254;                                      // +0x254
    uint32_t m258[0x9c / 4];                            // +0x258 .. +0x2f3
    uint32_t m2f8;                                      // +0x2f8
    uint32_t m2fc;                                      // +0x2fc
    TribeRecord* mpRecordBegin;                         // +0x304
    TribeRecord* mpRecordEnd;                           // +0x308
    TribeRecord* mpRecordCapacity;                      // +0x30c
    uint32_t m310;                                      // +0x310
    uint32_t m314;                                      // +0x314
    uint32_t m318;                                      // +0x318
    TribeRecord maRecordBuffer[4];                      // +0x31c .. +0x38b
    uint32_t m38c;                                      // +0x38c
    uint32_t m390;                                      // +0x390
    uint32_t m394;                                      // +0x394
    uint32_t m398;                                      // +0x398
    uint32_t m39c;                                      // +0x39c
    bool     mb3a0;                                     // +0x3a0
    uint8_t  m3a1;                                      // +0x3a1
    uint8_t  m3a2;                                      // +0x3a2
    uint8_t  mb3a3;                                     // +0x3a3

    cTribeModeStrategy();                               // 0x00cd9a10
    void RefreshSelectedCreatures();                    // 0x00cd8e70
    uint32_t GetSelectedCreatureCount();                // 0x00cd91b0
};

// ------------------------------------------------------------------ vector of 0xc-byte elements
struct Elem12 {
    uint32_t m00, m04, m08;
};
void __stdcall GrowVec12(Elem12* end, const Elem12* v); // 0x00b535d0

struct Vec12 {
    Elem12* mpBegin;                                    // +0x00
    Elem12* mpEnd;                                      // +0x04
    Elem12* mpCapacity;                                 // +0x08
    void push_back(const Elem12& v);
};

// ------------------------------------------------------------------ vector of 0x10-byte objects
struct Elem16 {
    void*    mpVtable;                                  // +0x00
    void*    mp04;                                      // +0x04
    void*    mp08;                                      // +0x08
    uint8_t  mb0c;                                      // +0x0c
};
void* __cdecl FUN_00cd5a90(Elem16* a, Elem16* b, Elem16* c);       // 0x00cd5a90
void  __cdecl FUN_00cd5af0(Elem16* a, Elem16* b, Elem16* c);       // 0x00cd5af0
void* __cdecl FUN_00cd5a40(Elem16* a, Elem16* b, Elem16* c);       // 0x00cd5a40
void  __cdecl FUN_00cd4540(Elem16* a, Elem16* b, Elem16* c);       // 0x00cd4540
void* __cdecl FUN_00f40000(uint32_t size);                         // operator new (EASTL)

struct Vec16 {
    Elem16* mpBegin;                                    // +0x00
    Elem16* mpEnd;                                      // +0x04
    Elem16* mpCapacity;                                 // +0x08
    void DestroyRange(Elem16* first, Elem16* last);      // 0x00cd9440
    void InsertOne(Elem16* pos, Elem16* v);              // 0x00cd9490
};

// =================================================================================================
// 0x00cd8e70 -- re-sync the strategy's member records with the tribe's live creatures.
// @ 0x00cd8e70
void __fastcall FUN_00cd8e70(cTribeModeStrategy* self)
{
    cTribe* tribe = NounManager()->GetPlayerTribe();
    void* profile = FUN_00401090()->GetAvatarProfile();
    uint32_t recordCount = (uint32_t)(self->mpRecordEnd - self->mpRecordBegin);
    uint32_t found = 0;
    CreatureList* list = ((CreatureList* (__thiscall*)(cTribe*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    CreatureList* listEnd = ((CreatureList* (__thiscall*)(cTribe*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    uint32_t creatureCount = (uint32_t)(listEnd->mpEnd - listEnd->mpBegin);
    for (uint32_t i = 0; i < creatureCount; ++i) {
        cSPCreatureBase* c = list->mpBegin[i];
        if (found < recordCount) {
            TribeRecord* rec = self->mpRecordBegin + found;
            while (found < recordCount) {
                if (rec->mpProfile == profile) {
                    uint32_t t;
                    t = c->mNameBegin;    c->mNameBegin = rec->mNameBegin;    rec->mNameBegin = t;
                    t = c->mNameEnd;      c->mNameEnd = rec->mNameEnd;        rec->mNameEnd = t;
                    t = c->mNameCapacity; c->mNameCapacity = rec->mNameCapacity; rec->mNameCapacity = t;
                    break;
                }
                ++found;
                ++rec;
            }
        }
        if (c->mNameBegin == c->mNameEnd) {
            uint32_t tmp[3] = { 0, 0, 0 };
            FUN_004010a0(tmp, 0x51aa76bb);
            uint32_t* s = (uint32_t*)FUN_005ecf80(tmp, 0x51aa76bb);
            s[1] = s[0];                       // eastl::wstring::assign(begin, end)
            if (tmp[0] != 0) FUN_00f47380((void*)tmp[0]);
        }
    }

    SelSet set;
    set.Initialize();
    {
        void* pos = ((void* (__thiscall*)(cTribe*))
            ((void**)tribe->mpVtable)[0x4c / 4])(tribe);
        Vector3* v = ((Vector3* (__thiscall*)(void*))
            (*(void***)*(void**)pos)[0]) (pos);
        (void)v;
    }
    TribeRecord* rec = self->mpRecordBegin;
    uint32_t remaining = recordCount;
    while (remaining != 0) {
        --remaining;
        if (rec->mpProfile != profile) {
            cSPCreatureBase* c = (cSPCreatureBase*)0;
            (void)c;
        }
        ++rec;
    }
    (void)set;
}

// =================================================================================================
// 0x00cd91b0 -- number of creatures currently selected by the tribe mode.
// @ 0x00cd91b0
uint32_t cTribeModeStrategy::GetSelectedCreatureCount()
{
    SelSet set;
    GetSelectedCreatureSet(&set);
    return set.mCount;
}

// =================================================================================================
// 0x00cd91e0 -- initialise the strategy's fixed pool / reservation storage.
// @ 0x00cd91e0
TribeSub* TribeSub::Init(int arg1, int arg2)
{
    FixedPoolDesc desc;
    desc.m00[0] = 0;
    desc.Init(&mPoolBegin, 0x60, 0xc, 4, 0);
    Configure(arg1, arg2, arg2, arg2, arg2, this);
    m10 = 10000.0f;
    m14 = 2.0f;
    m18 = 0;
    uint32_t n = PoolSize(m0c);
    if (m08 < n) GrowTo(n);
    return this;
}

// =================================================================================================
// 0x00cd92b0 -- append a 12-byte element.
// @ 0x00cd92b0
void Vec12::push_back(const Elem12& v)
{
    if (mpEnd < mpCapacity) {
        Elem12* p = mpEnd;
        mpEnd = p + 1;
        if (p) *p = v;
    } else {
        GrowVec12(mpEnd, &v);
    }
}

// =================================================================================================
// 0x00cd92f0 -- build the display string of a range of 8-byte key/value entries.
// @ 0x00cd92f0
uint8_t __fastcall FUN_00cd92f0(void** self, void* range, const uint32_t* str)
{
    uint8_t ok = 1;
    if (str[0] != str[1]) {
        uint32_t tmp[3];
        if (range == 0) {
            tmp[0] = tmp[1] = tmp[2] = 0;
        } else {
            FUN_005ecf80(tmp, (uint32_t)range);
        }
        void* text = (tmp[0] != 0) ? (void*)tmp[0] : (void*)0x013f6254;
        ((void (__thiscall*)(void*, void*))(*(void***)self)[0])(self, text);
        for (uint8_t* it = (uint8_t*)str[0]; it != (uint8_t*)str[1]; it += 8) {
            ok = 0;
        }
        ((void (__thiscall*)(void*, void*))(*(void***)self)[1])(self, text);
        if (tmp[0] != 0) FUN_00f47380((void*)tmp[0]);
    }
    return ok;
}

// =================================================================================================
// 0x00cd9440 -- destroy the tail of a 0x10-byte-element vector after moving [first,last) out.
// @ 0x00cd9440
void Vec16::DestroyRange(Elem16* first, Elem16* last)
{
    Elem16* it = (Elem16*)FUN_00cd5a90(last, mpEnd, first);
    for (; it < mpEnd; ++it) {
        ((void (__thiscall*)(Elem16*, int))(*(void***)it)[0])(it, 0);
    }
    mpEnd -= last - first;
}

// =================================================================================================
// 0x00cd9490 -- insert one 0x10-byte element at an arbitrary position.
// @ 0x00cd9490
void Vec16::InsertOne(Elem16* pos, Elem16* v)
{
    if (mpEnd != mpCapacity) {
        if (pos <= v && v < mpEnd) v += 1;
        if (mpEnd) {
            mpEnd->mpVtable = (void*)0x014774c4;
            mpEnd->mp04 = mpEnd[-1].mp04;
            mpEnd->mp08 = mpEnd[-1].mp08;
            if (mpEnd->mp08) ((void (__thiscall*)(void*))(*(void***)mpEnd->mp08)[0])(mpEnd->mp08);
            mpEnd->mb0c = mpEnd[-1].mb0c;
        }
        FUN_00cd5af0(pos, mpEnd - 1, mpEnd);
        pos->mp04 = v->mp04;
        if (v->mp08 != pos->mp08) {
            if (v->mp08) ((void (__thiscall*)(void*))(*(void***)v->mp08)[0])(v->mp08);
            pos->mp08 = v->mp08;
        }
        pos->mb0c = v->mb0c;
        mpEnd += 1;
        return;
    }
    uint32_t n = (uint32_t)(mpEnd - mpBegin);
    uint32_t cap = (n == 0) ? 1 : n * 2;
    Elem16* buf = (Elem16*)FUN_00f40000(cap * 0x10);
    Elem16* p = (Elem16*)FUN_00cd5a40((Elem16*)mpBegin, pos, buf);
    FUN_00cd4540((Elem16*)mpBegin, pos, buf);
    if (p) {
        p->mpVtable = (void*)0x014774c4;
        p->mp04 = v->mp04;
        p->mp08 = v->mp08;
        if (p->mp08) ((void (__thiscall*)(void*))(*(void***)p->mp08)[0])(p->mp08);
        p->mb0c = v->mb0c;
    }
    Elem16* q = (Elem16*)FUN_00cd5a40(pos, mpEnd, p + 1);
    FUN_00cd4540(pos, mpEnd, p + 1);
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
    mpBegin = buf;
    mpEnd = q;
    mpCapacity = buf + cap;
}

// =================================================================================================
// 0x00cd9660 -- mark every species of the player's tribe as "seen" in the tribe UI.
// @ 0x00cd9660
void __fastcall FUN_00cd9660(int arg1)
{
    cTribe* tribe = NounManager()->GetPlayerTribe();
    cTribeModeStrategy* self = gpTribeModeStrategy;
    TribeSub* sub = &self->mSub;
    (void)sub;
    if (arg1 == 0) return;
    if (!FUN_0064f350(0x01581288, 0x1ccfdbe6, 0)) return;
}

// =================================================================================================
// 0x00cd9760 -- refresh the tribe's unlock state from the active space-stage rules.
// @ 0x00cd9760
void FUN_00cd9760()
{
    cTribe* tribe = NounManager()->GetPlayerTribe();
    (void)tribe;
    uint32_t recipe = 0;
    uint32_t count = 0, list = 0;
    GetPropertyAsUint32Array(0x01581288, recipe, &count, &list);
}

// =================================================================================================
// 0x00cd98e0 -- unlock a collectable item id from the current rules.
// @ 0x00cd98e0
void __fastcall FUN_00cd98e0(uint32_t index)
{
    uint32_t count = 0;
    uint32_t list = 0;
    if (gpTribeModeStrategy->m19c == 0) return;
    if (!GetPropertyAsUint32Array(0x01581288, 0x895b917a, &count, &list)) return;
    if (count == 0 || index >= count) return;
    for (uint32_t n = *(uint32_t*)(list + index * 4); n != 0; --n) {
        FUN_00f47380((void*)n);
    }
}

// =================================================================================================
// 0x00cd9a10 -- cTribeModeStrategy constructor.
// @ 0x00cd9a10
cTribeModeStrategy::cTribeModeStrategy()
{
    mpVtbl1 = VT_14426a0;
    mpVtbl2 = VT_13eb394;
    cGonzagoSubsystem_ctor(&mpVtbl3);
    mpVtbl1 = VT_1477648;
    mpVtbl2 = VT_1477640;
    mpVtbl3 = VT_14775f0;
    mpVtbl4 = VT_14775e8;
    mbInCityHallEditor = false;
    mbInAccessoryEditor = false;
    m2c = 0; m30 = 0; m34 = 0;
    m40 = 0; m44 = 0; m48 = 0;
    cGonzagoTimer_ctor(&mTimer);
    m78 = 0; m7c = 0; m80 = 0; m84 = 0;
    m94 = 0; m98 = 0; m9c = 0;
    mSub.Init(0, 0);
    mb198 = false;
    m19c = 0;
    m1a0 = 0.0f;
    mb1a4 = false;
    cGonzagoTimer_ctor(&mTimer2);
    m1c8 = 0; m1cc = 0; m1d0 = 0; m1d4 = 0; m1d8 = 0; m1dc = 0;
    cLocalInputState_ctor(&mInput);
    mb228 = false;
    m22c = 0;
    m230 = -1; m234 = -1;
    m238 = 0;
    m23c = 0; m240 = 0; m244 = 0;
    mb248 = false; mb249 = false; mb24a = false;
    m24c = 0; m250 = 0; m254 = 0;
    for (int i = 0; i < (int)(0x9c / 4); ++i) m258[i] = 0;
    m2f8 = 0; m2fc = 0;
    mpRecordBegin = maRecordBuffer;
    mpRecordEnd = maRecordBuffer;
    m318 = 0;
    mpRecordCapacity = maRecordBuffer + 4;
    m38c = 0xffffffffu;
    m390 = 1;
    m394 = 0; m398 = 0; m39c = 0;
    mb3a0 = false;
    mb3a3 = true;
    gpTribeModeStrategy = this;
}

// =================================================================================================
// 0x00cd9ce0 -- fill the set with the tribe creatures the loco reports as selectable.
// @ 0x00cd9ce0
SelSet* cTribeModeStrategy::GetSelectedCreatureSet(SelSet* out)
{
    out->Initialize();
    cTribe* tribe = NounManager()->GetPlayerTribe();
    CreatureList* list = ((CreatureList* (__thiscall*)(cTribe*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    for (cSPCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it) {
        cSPCreatureBase* c = *it;
        if (c->mLoco.CanBeSelected()) {
            void* ref = c;
            if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[0])(ref);
            SelSetIter iter; void* key = ref;
            out->Insert(&iter, &key, false);
            if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[1])(ref);
        }
    }
    return out;
}

} // namespace SP
