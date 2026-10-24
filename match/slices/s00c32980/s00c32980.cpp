// Slice s00c32980 (batch gold7, worker 0). Region 0x00c32980-0x00c33aa7.
// SP::cEmpire cluster: editor-property key rebind, the eastl heap helpers that
// sit next to the empire star list (adjust_heap / partition), cEmpire::GetColor,
// the STL sequence read/write templates for eastl::vector<AutoRefCount<cEmpire>>,
// cEmpire::~cEmpire and the SetSpecies / re-banner helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned int uintptr_t;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;

// ---- raw (__cdecl / __stdcall) callees -------------------------------------
void* __cdecl FUN_00b3d300(void);                              // 0x00b3d300  SP::NounManager
void* __cdecl FUN_00b3d2a0(void);                              // 0x00b3d2a0  SP::StarManager
void* __cdecl FUN_01021300(void);                              // 0x01021300  GetPlayerEmpire
void* __cdecl FUN_01002bd0(void);                              // 0x01002bd0  SpaceGameGet
void* __cdecl FUN_00b6f0c0(u32 id);                            // 0x00b6f0c0  cSPColorRGB::ColorFromID
bool  __cdecl FUN_005bf0e0(void* key, void** out);             // 0x005bf0e0  GetEditorPropertyList
bool  __cdecl FUN_006a1250(void* prop, u32 hash, void* out);   // 0x006a1250  SP::GetPropertyAsKey
void* __cdecl FUN_00f473a0(unsigned size, const char* name,
                           int a, int b, void* c, int d);      // 0x00f473a0  operator new
void  __cdecl FUN_00f47380(void* p);                           // 0x00f47380  operator delete
bool  __cdecl FUN_004232c0(void* a, void* b);                  // 0x004232c0  Vector3Equal
void  __cdecl FUN_00b2af00(void* a, void* b);                  // 0x00b2af00  swap
void  __cdecl FUN_0093aa70(void* io, const void* p, int n, int f);  // 0x0093aa70  EA::IO::WriteUint32
void  __cdecl FUN_0093a780(void* io, void* p, int n, int f);   // 0x0093a780  EA::IO::ReadInt32

extern float g_146b68c;    // 0x0146b68c  FLT_MAX
extern float g_13eb1bc;    // 0x013eb1bc  -1.0f
extern float g_13f1cac;    // 0x013f1cac
extern float g_1572b54;    // 0x01572b54
extern float g_1572b58;    // 0x01572b58
extern float g_1572b5c;    // 0x01572b5c
extern float g_1471064;    // 0x01471064  0.5f
extern float g_168de78;    // 0x0168de78
extern float g_168de7c;    // 0x0168de7c
extern float g_168de80;    // 0x0168de80
extern void* g_1667bac;    // 0x01667bac  eastl::gEmptyString16 begin
extern void* g_1667bae;    // 0x01667bae  eastl::gEmptyString16 end
extern char  g_13ebb38[];  // 0x013ebb38  eastl allocator name
extern char  g_13ef094[];  // 0x013ef094  base vtable
extern char  g_13eb938[];  // 0x013eb938  base vtable
extern char  g_146b768[];  // 0x0146b768
extern char  g_146b764[];  // 0x0146b764
extern char  g_146b748[];  // 0x0146b748

// ---- vtable slot helpers ----------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define ADDREF(o)   ((void(__thiscall*)(void*))VF(o, 0))(o)
#define RELEASE(o)  ((void(__thiscall*)(void*))VF(o, 4))(o)

// Reference-counted pointer temporary (EA::AutoRefCount).  AddRef()s on
// construction, Release()s on destruction, converts to the raw pointer.
struct P {
    void* p;
    P(void* o = 0) : p(o) { if (p) ADDREF(p); }
    P(const P& o) : p(o.p) { if (p) ADDREF(p); }
    ~P() { if (p) RELEASE(p); }
    P& operator=(const P& o) {
        void* n = o.p; void* const t = p;
        if (n != t) { if (n) ADDREF(n); p = n; if (t) RELEASE(t); }
        return *this;
    }
    operator void*() const { return p; }
};

// ---- shared shapes ----------------------------------------------------------
struct EVec {                       // eastl vector header (0x14 bytes in retail)
    void*    mBegin;                // +0x00
    void*    mEnd;                  // +0x04
    void*    mCapacity;             // +0x08
    uintptr_t mPad0c;               // +0x0c
    uintptr_t mPad10;               // +0x10

    uint32_t Size() const { return (uint32_t)(((char*)mEnd - (char*)mBegin) >> 2); }
};

struct Key { uint32_t instanceID, typeID, groupID; };   // 12-byte resource key

struct cSPColorRGB { float r, g, b; };

struct cSPIdentity {
    void*       mpVtbl;             // +0x00
    uint32_t    mIDColorID;         // +0x04
    uint8_t     mIDNameMap[0x1c];   // +0x08
    cSPColorRGB mColor;             // +0x24  cached colour
};

struct ListAnchor { void* mpNext; void* mpPrev; };

namespace SP {

struct cEmpire {
    void*       mpVtbl;                 // +0x00
    void*       mpVtbl2;                // +0x04
    uint32_t    mnRefCount;             // +0x08
    cSPIdentity mIdentity;              // +0x0c
    uint8_t     mEmpireName[0x14];      // +0x3c  eastl::wstring
    uint32_t    mFlags;                 // +0x50
    uint32_t    mTrait;                 // +0x54
    uint32_t    mArchetype;             // +0x58
    EVec        mEnemies;               // +0x5c
    EVec        mAllies;                // +0x70
    uint32_t    mPoliticalID;           // +0x84
    EVec        mStars;                 // +0x88
    EVec        mNextStarTowardsHome;   // +0x9c
    uint32_t    mHomeStar;              // +0xb0
    uint32_t    mHomePlanet;            // +0xb4
    Key         mUFOKey;                // +0xb8
    Key         mCaptainKey;            // +0xc4
    uint32_t    mEmpireMoney;           // +0xd0
    uint32_t    mTravelDistance;        // +0xd4
    uint32_t    mFieldD8;               // +0xd8
    float       mFieldDC;               // +0xdc
    float       mFieldE0;               // +0xe0
    float       mFieldE4;               // +0xe4
    float       mFieldE8;               // +0xe8
    float       mTurretHealth;          // +0xec
    EVec        mUFOHealth;             // +0xf0
    void*       mpCityMusic;            // +0x104
    uint8_t     mCultureSet[0x20];      // +0x108
    uint8_t     mDemandForTribute[0x20];// +0x128
    ListAnchor  mAdventureList;         // +0x148

    void RebindPropertyKey();                    // 0x00c32980
    cSPColorRGB GetColor();                      // 0x00c32cd0
    void  Destroy_33410();                       // 0x00c33410
    void  RefreshName_33580();                   // 0x00c33580
    void  SetSpecies(void* species);             // 0x00c33690
};

} // namespace SP

// ---- member-style external callees (thiscall originals) --------------------
struct MC {
    void* f_00ba6d80(u32 id);                   // 0x00ba6d80
    void* f_00bba500();                         // 0x00bba500
    void* f_00bb9b80();                         // 0x00bb9b80
    void* f_00bb9b90(void* a);                  // 0x00bb9b90
    int   f_00bb9ae0();                         // 0x00bb9ae0
    int   f_00885c90();                         // 0x00885c90
    void  f_00bb1080(void* a);                  // 0x00bb1080
    int   f_00b1fdb0();                         // 0x00b1fdb0  GetAvatar
    void* f_00ba9370(u32 id);                   // 0x00ba9370  GetEmpireByID
    void* f_005c65e0();                         // 0x005c65e0  GetCities
    void  f_00b6f380(void* s);                  // 0x00b6f380  cSPIdentity::SetName
    void  f_00bb9b90_(void* a);                 // 0x00bb9b90
    void  f_00bb5b50(void* s);                  // 0x00bb5b50
    void* f_00c30c80(float a, float b);         // 0x00c30c80
    void  f_00f67d90();                         // 0x00f67d90
    void* f_00f67d90v();                        // 0x00f67d90 (returns value)
    void  f_00c759a0();                         // 0x00c759a0
    void  f_00b638b0();                         // 0x00b638b0  ~cGonzagoTimer
    void  f_00ae6970();                         // 0x00ae6970  ~eastl::vector
    void  f_00b6edf0();                         // 0x00b6edf0  ~cSPIdentity
    void  f_009a9600(void* child);              // 0x009a9600  DoNukeSubtree
    float*f_00b6e4b0(void* out, float r, float g, float b);  // 0x00b6e4b0
};

// colour helpers (all cdecl-ish, plain funcs)
float* __cdecl FUN_00b6e4b0(void* out, float r, float g, float b);  // 0x00b6e4b0
void   __cdecl FUN_00b6f140(float r, float g, float b);             // 0x00b6f140
void   __cdecl FUN_00b6f180(void);                                  // 0x00b6f180
bool   __cdecl FUN_00b6e1e0(u32 idx);                               // 0x00b6e1e0
void   __cdecl FUN_00b6f380(void* ident, void* name);               // 0x00b6f380  cSPIdentity::SetName
void   __cdecl FUN_009a9600(void* root);                            // 0x009a9600  DoNukeSubtree
void   __cdecl FUN_00b6edf0(void* self);                            // 0x00b6edf0  ~cSPIdentity
void*  __cdecl FUN_00e5c780(void* self, void* key);                 // 0x00e5c780  rbtree::find
void   __cdecl FUN_005c3d90(void* str, const wchar_t* s);           // 0x005c3d90  eastl::wstring::append
void   __cdecl FUN_00423650(void* str, const wchar_t* f, const wchar_t* l); // 0x00423650 assign
void   __cdecl FUN_004da330(void* species, void* out);              // 0x004da330  GetUiName

// rbtree node for the identity name map (key at +0x10, value ptr at +0x14)
struct RBNode {
    RBNode* mpLeft;      // +0x00
    RBNode* mpRight;     // +0x04
    RBNode* mpParent;    // +0x08
    uint8_t pad0c[0x4];  // +0x0c
    u32     mKey;        // +0x10
    void*   mpValue;     // +0x14
};

// ===========================================================================
// 0x00c32980 -- cEmpire::RebindPropertyKey
// ===========================================================================
// @ 0x00c32980
void SP::cEmpire::RebindPropertyKey()
{
    Key key = mCaptainKey;
    void* prop = 0;
    for (;;) {
        if (prop) {
            void* old = prop;
            prop = 0;
            RELEASE(old);
        }
        if (!FUN_005bf0e0(&key, &prop)) break;
        mCaptainKey = key;
        if (!FUN_006a1250(prop, 0xd8a4bc9, &key)) break;
    }
    MC* nm = (MC*)FUN_00b3d300();
    MC* te = (MC*)nm->f_00f67d90v();
    te->f_00c759a0();
    if (prop) RELEASE(prop);
}

// ===========================================================================
// 0x00c32a60 -- eastl::adjust_heap<AutoRefCount<cStarRecord>*,int,
//               AutoRefCount<cStarRecord>,DistanceToHome>
// ===========================================================================
struct DistanceToHome { float x, y, z; };

void __cdecl promote_heap_stars(P* first, int top, int pos, P value, DistanceToHome home); // 0x00c32160

// @ 0x00c32a60
void __cdecl FUN_00c32a60(P* first, int top, int heap, int position, P value, DistanceToHome home)
{
    int child = 2 * position + 2;
    while (child < heap) {
        float* a = (float*)((MC*)first[child].p)->f_005c65e0();
        float ax = a[0] - home.x, ay = a[1] - home.y, az = a[2] - home.z;
        float* b = (float*)((MC*)first[child - 1].p)->f_005c65e0();
        float bx = b[0] - home.x, by = b[1] - home.y, bz = b[2] - home.z;
        if (ax * ax + ay * ay + az * az < bx * bx + by * by + bz * bz) --child;
        first[position] = first[child];
        position = child;
        child = 2 * child + 2;
    }
    if (child == heap) {
        first[position] = first[child - 1];
        position = child - 1;
    }
    promote_heap_stars(first, top, position, value, home);
}

// ===========================================================================
// 0x00c32cd0 -- SP::cEmpire::GetColor
// ===========================================================================
// @ 0x00c32cd0
cSPColorRGB SP::cEmpire::GetColor()
{
    u32 id = mIdentity.mIDColorID;
    if (id - 0x53dbcf3 <= 0xb) {
        float* c = (float*)FUN_00b6f0c0(id);
        cSPColorRGB r; r.r = c[0]; r.g = c[1]; r.b = c[2];
        return r;
    }
    SP::cEmpire* pe = (SP::cEmpire*)FUN_01021300();
    if (pe != this) {
        if (((mFlags >> 6) & 1) != 0) {
            MC* banner = 0;
            if (mUFOKey.groupID != 0xffffffff) {
                banner = (MC*)((MC*)FUN_00b3d2a0())->f_00ba6d80(mUFOKey.groupID);
            }
            if (banner && banner->f_00bb9ae0() == 5 && mIdentity.mIDColorID == 0x53dbcf1) {
                if (FUN_004232c0(&mIdentity.mColor, &g_168de78)) {
                    MC* sph = (MC*)((MC*)this)->f_00c30c80(0.5f, 0.5f);
                    float* src = (float*)((char*)sph + 0x4ec);
                    float* res = FUN_00b6e4b0(&mIdentity.mColor, src[0], src[1], src[2]);
                    mIdentity.mColor.r = res[0];
                    mIdentity.mColor.g = res[1];
                    mIdentity.mColor.b = res[2];
                }
                return mIdentity.mColor;
            }
        }
        MC* sm = (MC*)FUN_00b3d2a0();
        if (sm->f_00885c90() == (int)mPoliticalID) {
            cSPColorRGB r;
            r.r = g_1572b54; r.g = g_1572b58; r.b = g_1572b5c;
            return r;
        }
        float slots[12];
        for (u32 i = 0; i < 12; ++i)
            slots[i] = FUN_00b6e1e0(i) ? 0.0f : g_146b68c;
        {
            Key key = mUFOKey;
            u32 pad34 = 0, pad38 = 0, pad3c = 0;
            int arr0 = 0, arr1 = 0, arr2 = 0;
            int f48 = 0x1fff;
            int f4c = 0x20;
            float f50 = 0.0f;
            float f54 = g_13eb1bc;
            float f58 = g_13f1cac;
            float f5c = g_13eb1bc;
            int f60 = 0;
            (void)pad34; (void)pad38; (void)pad3c;
            void* banner = 0;
            if (key.groupID != 0xffffffff) {
                banner = ((MC*)FUN_00b3d2a0())->f_00ba6d80(key.groupID);
            }
            ((MC*)banner)->f_005c65e0();
            // the array header passed to GetCities is an eastl vector header
            struct { int* b; int* e; int* c; int pad; } list;
            list.b = &arr0; list.e = &arr0; list.c = &arr0;
            (void)f48; (void)f4c; (void)f50; (void)f54; (void)f58; (void)f5c; (void)f60;
            MC* sm2 = (MC*)FUN_00b3d2a0();
            sm2->f_00bb1080(&list);
            for (int* it = list.b; it != list.e; ++it) {
                MC* star = (MC*)*it;
                int av = star->f_00b1fdb0();
                if (av == -1) continue;
                int av2 = star->f_00b1fdb0();
                MC* sm3 = (MC*)FUN_00b3d2a0();
                MC* emp = (MC*)sm3->f_00ba9370(av2);
                if (!emp) continue;
                u32 ci = (u32)(*(u32*)((char*)emp + 0x10) - 0x53dbcf3);
                if (ci > 0xb) continue;
                void* b1 = 0;
                if (*(u32*)((char*)emp + 0xb0) != 0xffffffff) {
                    b1 = ((MC*)FUN_00b3d2a0())->f_00ba6d80(*(u32*)((char*)emp + 0xb0));
                }
                void* b2 = 0;
                if (mUFOKey.groupID != 0xffffffff) {
                    b2 = ((MC*)FUN_00b3d2a0())->f_00ba6d80(mUFOKey.groupID);
                }
                float* p1 = (float*)((MC*)b2)->f_005c65e0();
                float* p2 = (float*)((MC*)b1)->f_005c65e0();
                float dx = p1[0] - p2[0], dy = p1[1] - p2[1], dz = p1[2] - p2[2];
                float d = dx * dx + dy * dy + dz * dz;
                if (d < slots[ci] || d == slots[ci]) slots[ci] = d;
            }
        }
        float best = 0.0f;
        int bestIdx = 0;
        for (u32 i = 0; i < 12; ++i) {
            if (slots[i] > best) { bestIdx = (int)i; best = slots[i]; }
        }
        u32 newID = (u32)bestIdx + 0x53dbcf3;
        if ((u32)bestIdx >= 0xc) newID = 0x53dbcf3;
        mIdentity.mIDColorID = newID;
        float* c = (float*)FUN_00b6f0c0(newID);
        cSPColorRGB r; r.r = c[0]; r.g = c[1]; r.b = c[2];
        return r;
    }
    if (mIdentity.mIDColorID != 0x53dbcf1) {
        int hs = (int)((SP::cEmpire*)FUN_01021300())->mHomeStar;
        MC* spec = 0;
        if (hs != -1) {
            MC* b = (MC*)((MC*)FUN_00b3d2a0())->f_00ba6d80((u32)hs);
            if (b) spec = (MC*)b->f_00bba500();
        }
        float* src = (float*)((char*)spec + 0x4ec);
        float* res = FUN_00b6e4b0(&mIdentity.mColor, src[0], src[1], src[2]);
        FUN_00b6f140(res[0], res[1], res[2]);
        FUN_00b6f180();
        mIdentity.mColor.r = res[0];
        mIdentity.mColor.g = res[1];
        mIdentity.mColor.b = res[2];
        mIdentity.mIDColorID = 0x53dbcf1;
    }
    if (mIdentity.mColor.r == g_168de78 && mIdentity.mColor.g == g_168de7c && mIdentity.mColor.b == g_168de80) {
        float* c = (float*)FUN_00b6f0c0(mIdentity.mIDColorID);
        mIdentity.mColor.r = c[0];
        mIdentity.mColor.g = c[1];
        mIdentity.mColor.b = c[2];
    }
    float* c = (float*)FUN_00b6f0c0(mIdentity.mIDColorID);
    cSPColorRGB r; r.r = c[0]; r.g = c[1]; r.b = c[2];
    return r;
}

// ===========================================================================
// 0x00c332a0 -- SP::WriteSTLSequenceT<eastl::vector<AutoRefCount<cEmpire>>>
// ===========================================================================
// list header: mpNext at +0x00, mpPrev at +0x04, node value at +0x08.
typedef void* (__thiscall *TFVP)(void*);
struct ListNode { ListNode* mpNext; ListNode* mpPrev; u32 mValue; };
// @ 0x00c332a0
void __cdecl FUN_00c332a0(void* stream, ListAnchor* list)
{
    int count = 0;
    for (void* n = list->mpNext; n != (void*)list; n = *(void**)n) ++count;
    int c = count;
    void* io = ((TFVP)((*(void***)stream)[8]))(stream);
    void* w = ((TFVP)((*(void***)io)[6]))(io);
    FUN_0093aa70(w, &c, 1, 0);
    for (void* n = list->mpNext; n != (void*)list; n = *(void**)n) {
        void* io2 = ((TFVP)((*(void***)stream)[8]))(stream);
        int v = (int)((ListNode*)n)->mValue;
        void* w2 = ((TFVP)((*(void***)io2)[6]))(io2);
        FUN_0093aa70(w2, &v, 1, 0);
    }
    ((TFVP)((*(void***)stream)[7]))(stream);
}

// ===========================================================================
// 0x00c33410 -- cEmpire destructor body
// ===========================================================================
// @ 0x00c33410
void SP::cEmpire::Destroy_33410()
{
    mpVtbl = g_146b768;
    mpVtbl2 = g_146b764;
    mIdentity.mpVtbl = g_146b748;
    ListAnchor* anchor = &mAdventureList;
    void* n = anchor->mpNext;
    while (n != (void*)anchor) {
        void* cur = n;
        n = *(void**)n;
        FUN_00f47380(cur);
    }
    ((MC*)mDemandForTribute)->f_00b638b0();
    MC* culture = (MC*)mCultureSet;
    culture->f_009a9600(*(void**)((char*)culture + 0x0c));
    if (mpCityMusic) RELEASE(mpCityMusic);
    void* ufoHealth = mUFOHealth.mBegin;
    if (ufoHealth && *(int*)((char*)ufoHealth - 4) != 0) FUN_00f47380(ufoHealth);
    ((MC*)&mNextStarTowardsHome)->f_00ae6970();
    ((MC*)&mStars)->f_00ae6970();
    ((MC*)&mAllies)->f_00ae6970();
    ((MC*)&mEnemies)->f_00ae6970();
    void* nameBegin = *(void**)(mEmpireName + 0);
    void* nameCap = *(void**)(mEmpireName + 8);
    if ((int)(((char*)nameCap - (char*)nameBegin) & 0xfffffffe) > 2 && nameBegin) FUN_00f47380(nameBegin);
    ((MC*)&mIdentity)->f_00b6edf0();
    mpVtbl2 = g_13ef094;
    mpVtbl = g_13eb938;
}

// ===========================================================================
// 0x00c33580 -- cEmpire::RefreshName_33580
// ===========================================================================
// @ 0x00c33580
void SP::cEmpire::RefreshName_33580()
{
    if ((int)mHomeStar == -1) return;
    MC* banner = (MC*)((MC*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
    if (!banner) return;
    int* p = (int*)banner->f_00bb9b80();
    Key kk = *(Key*)p;
    if (kk.instanceID == 0) return;
    if ((int)mHomeStar == -1) return;
    MC* b2 = (MC*)((MC*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
    if (!b2) return;
    MC* spec = (MC*)b2->f_00bba500();
    if (!spec) return;
    cSPColorRGB col = GetColor();
    (void)col;
    wchar_t* nameBuf[3];
    nameBuf[0] = (wchar_t*)g_1667bac;
    nameBuf[1] = (wchar_t*)g_1667bac;
    nameBuf[2] = (wchar_t*)g_1667bae;
    FUN_004da330(spec, nameBuf);
    ((MC*)&mIdentity)->f_00b6f380(nameBuf);
    int key = 2;
    RBNode** pp = (RBNode**)FUN_00e5c780(&mIdentity.mIDNameMap, &key);
    RBNode* node = *pp;
    FUN_005c3d90(mEmpireName, (const wchar_t*)node->mpValue);
    wchar_t* nb = nameBuf[0];
    wchar_t* ne = nameBuf[2];
    if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
}

// ===========================================================================
// 0x00c33690 -- SP::cEmpire::SetSpecies
// ===========================================================================
// @ 0x00c33690
void SP::cEmpire::SetSpecies(void* speciesp)
{
    void* pe = FUN_01021300();
    if (pe == (void*)this && speciesp) {
        wchar_t* nameBuf[3];
        void* g = g_1667bac;
        nameBuf[0] = (wchar_t*)g;
        nameBuf[1] = (wchar_t*)g;
        nameBuf[2] = (wchar_t*)g_1667bae;
        FUN_004da330(speciesp, nameBuf);
        ((MC*)FUN_00b3d2a0())->f_00bb5b50(nameBuf);
        wchar_t* nb = nameBuf[0];
        wchar_t* ne = nameBuf[2];
        if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
    }
    Key speciesKey = {0, 0, 0};
    if (speciesp) {
        speciesKey.instanceID = *(u32*)((char*)speciesp + 0x504);
        speciesKey.typeID     = *(u32*)((char*)speciesp + 0x508);
        speciesKey.groupID    = *(u32*)((char*)speciesp + 0x50c);
    }
    int n = (int)mStars.Size();
    for (int i = 0; i < n; ++i) {
        void* star = ((void**)mStars.mBegin)[i];
        ((MC*)star)->f_00bb9b90(&speciesKey);
    }
    if (speciesp) {
        cSPColorRGB col = GetColor();
        (void)col;
        wchar_t* nameBuf[3];
        void* g = g_1667bac;
        nameBuf[0] = (wchar_t*)g;
        nameBuf[1] = (wchar_t*)g;
        nameBuf[2] = (wchar_t*)g_1667bae;
        FUN_004da330(speciesp, nameBuf);
        ((MC*)&mIdentity)->f_00b6f380(nameBuf);
        RBNode* root = (RBNode*)mIdentity.mIDNameMap;
        RBNode* cur = root->mpParent;
        while (cur) {
            if (cur->mKey < 2u) cur = cur->mpRight;
            else { cur = cur->mpLeft; root = cur; }
        }
        // find() inlined rbtree lookup for key == 2
        RBNode* found = (RBNode*)FUN_00e5c780(mIdentity.mIDNameMap, (void*)2);
        const wchar_t* s = (const wchar_t*)found->mpValue;
        const wchar_t* e = s;
        while (*e) ++e;
        FUN_00423650(mEmpireName, s, e);
        (void)cur;
        wchar_t* nb = nameBuf[0];
        wchar_t* ne = nameBuf[2];
        if ((int)(((char*)ne - (char*)nb) & 0xfffffffe) > 2 && nb) FUN_00f47380(nb);
    }
}

// ===========================================================================
// 0x00c33820 -- SP::ReadSTLSequenceT<eastl::vector<AutoRefCount<cEmpire>>>
// ===========================================================================
// @ 0x00c33820
void __cdecl FUN_00c33820(void* stream, ListAnchor* list)
{
    void* n = list->mpNext;
    while (n != (void*)list) {
        void* cur = n;
        n = *(void**)n;
        FUN_00f47380(cur);
    }
    list->mpNext = list;
    list->mpPrev = list;
    int count = 0;
    void* io = ((TFVP)((*(void***)stream)[8]))(stream);
    void* w = ((TFVP)((*(void***)io)[6]))(io);
    FUN_0093a780(w, &count, 1, 0);
    u32 i = 0;
    while (i < (u32)count) {
        int v;
        void* io2 = ((TFVP)((*(void***)stream)[8]))(stream);
        void* w2 = ((TFVP)((*(void***)io2)[6]))(io2);
        FUN_0093a780(w2, &v, 1, 0);
        ListNode* node = (ListNode*)FUN_00f473a0(0xc, "Simulator", 0, 0, g_13ebb38, 0xd1);
        if ((char*)node + 8) node->mValue = (u32)v;
        node->mpNext = (ListNode*)list;
        node->mpPrev = (ListNode*)list->mpPrev;
        ((ListNode*)list->mpPrev)->mpNext = node;
        ++i;
        ((ListNode*)list)->mpPrev = node;
    }
    ((TFVP)((*(void***)stream)[7]))(stream);
}

// ===========================================================================
// 0x00c338f0 -- eastl::partition over AutoRefCount<cStarRecord>* by distance
// ===========================================================================
// @ 0x00c338f0
void** __cdecl FUN_00c338f0(void** first_, void** last_, void* pivotp, float px, float py, float pz)
{
    void** first = first_;
    void** last = last_;
    for (;;) {
        for (;;) {
            float* a = (float*)((MC*)*first)->f_005c65e0();
            float ax = a[0] - px, ay = a[1] - py, az = a[2] - pz;
            float* b = (float*)((MC*)pivotp)->f_005c65e0();
            float bx = b[0] - px, by = b[1] - py, bz = b[2] - pz;
            if (bx * bx + by * by + bz * bz <= ax * ax + ay * ay + az * az) break;
            ++first;
        }
        void* p;
        do {
            p = *(last - 1);
            --last;
            float* c = (float*)((MC*)pivotp)->f_005c65e0();
            float cx = c[0] - px, cy = c[1] - py, cz = c[2] - pz;
            float* d = (float*)((MC*)p)->f_005c65e0();
            float dx = d[0] - px, dy = d[1] - py, dz = d[2] - pz;
            if (!(cx * cx + cy * cy + cz * cz < dx * dx + dy * dy + dz * dz)) break;
        } while (true);
        if (last <= first) break;
        FUN_00b2af00(first, last);
        ++first;
    }
    if (pivotp) RELEASE(pivotp);
    return first;
}
