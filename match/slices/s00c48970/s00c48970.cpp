// Slice s00c48970 - SP::cSPMission / Simulator::cGenericPressureEvent message and
// text helpers.  All functions are __thiscall with `this` in ecx.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
#include "types.h"
#include <wchar.h>
#include <string.h>
#include <xmmintrin.h>

typedef unsigned int  uint;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct WStr;
struct CStr;
struct SPObject;

// ---- external helpers (addresses in comments; call targets are relocated) ----
void __cdecl EAFree(void* p);                                    // 0x00f47380  operator delete[]
void* __cdecl MessageServer();                                   // 0x0067dcc0
extern "C" void __cdecl WStr3(WStr* out, const wchar_t* fmt, int a);         // 0x0041e050
extern "C" void __cdecl WStr4(WStr* out, const wchar_t* fmt, int a, float b);// 0x0041e050
void __cdecl FUN_00881730(int a, int b, int c, wchar_t* buf, int n, const wchar_t* fmt); // 0x00881730
void __cdecl FUN_00c48900(WStr* out);                            // 0x00c48900
void __cdecl FUN_00c48940(WStr* out);                            // 0x00c48940
void __cdecl FUN_00c486f0(WStr* out);                            // 0x00c486f0
void __cdecl FUN_00c48740(WStr* out);                            // 0x00c48740
void* __cdecl FUN_00bb9de0(void* p);                             // 0x00bb9de0
void __cdecl VecU32Insert(u32* pos, u32* value);                 // 0x004558a0

// ---- eastl-ish containers ---------------------------------------------------
struct Timer {
    char pad[0x20];
    void TimerCtor();                                            // 0x00b63890
};

struct CStr {
    char pad[0x14];
    const wchar_t* GetText();                                    // 0x006b55c0
    void CStrCtor();                                             // 0x006b5060
};

struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mpAllocator;

    WStr& append(const wchar_t* p);                              // 0x005c3d90
    WStr& assign(const wchar_t* first, const wchar_t* last);     // 0x00423650
    WStr& Append(const wchar_t* first, const wchar_t* last);     // 0x00429580
    void  RangeInitialize(const wchar_t* p);                     // 0x00579a90
};

struct Entry12 {                  // 12-byte eastl::vector<EA::ResourceMan::Key> element
    u32 mKey;
    u32 mField4;
    u32 mField8;
};

struct Vec12 {                    // eastl::sp_vector<EA::ResourceMan::Key>
    Entry12* mpBegin;
    Entry12* mpEnd;
    Entry12* mpCapacity;

    void Reserve(int n);                                         // 0x0041e4d0
    void DoInsertValue(Entry12* pos, const Entry12& value);       // 0x004e3e10

    void push_back(const Entry12& v) {
        if (mpEnd < mpCapacity) {
            Entry12* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
            return;
        }
        DoInsertValue(mpEnd, v);
    }
};

struct VecU32 {                   // eastl::vector<unsigned int>
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;

    void Insert(u32* pos, const u32& value);                     // 0x004558a0

    void push_back(const u32& v) {
        if (mpEnd < mpCapacity) {
            u32* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
            return;
        }
        Insert(mpEnd, v);
    }
};

struct Translator {
    char pad00[0x10];
    int  mField10;                                               // 0x10
    char pad14[0x2c];
    int  mField40;                                               // 0x40
};

// ---- the mission / event object --------------------------------------------
struct SPObject {
    void*  mpVtbl0;            // 0x000
    void*  mpVtbl4;            // 0x004
    char   pad08[0x2c];        // 0x008
    void*  mpVtbl34;           // 0x034
    Timer  mTimer38;           // 0x038
    Timer  mTimer58;           // 0x058
    u32    mField78;           // 0x078
    u32    mField7C;           // 0x07c
    u32    mField80;           // 0x080
    u32    mGroup84;           // 0x084
    u8     mField88;           // 0x088
    char   pad89[3];           // 0x089
    int    mField8C;           // 0x08c
    u32    mField90;           // 0x090
    int    mField94;           // 0x094
    u32    mField98;           // 0x098
    u32    mField9C;           // 0x09c
    float  mFieldA0;           // 0x0a0
    u32    mStarClueA4;        // 0x0a4
    u32    mStarClueA8;        // 0x0a8
    u32    mStarClueAC;        // 0x0ac
    CStr   mStrB0;             // 0x0b0 (0x14)
    int    mFieldC4;           // 0x0c4
    float  mFieldC8;           // 0x0c8
    u32*   mArrCC;             // 0x0cc
    u32*   mArrD0;             // 0x0d0
    u32*   mArrD4;             // 0x0d4
    char   padD8[8];           // 0x0d8
    u32*   mArrE0;             // 0x0e0
    u32*   mArrE4;             // 0x0e4
    u32*   mArrE8;             // 0x0e8
    char   padEC[8];           // 0x0ec
    int    mFieldF4;           // 0x0f4
    int    mKindF8;            // 0x0f8
    int    mFieldFC;           // 0x0fc
    int    mField100;          // 0x100
    int    mField104;          // 0x104
    u32    mField108;          // 0x108
    u32    mField10C;          // 0x10c
    u32    mField110;          // 0x110
    char   pad114[8];          // 0x114
    Vec12  mVec11C;            // 0x11c
    char   pad128[8];          // 0x128
    u32    mFlags130;          // 0x130
    VecU32 mVec134;            // 0x134
    char   pad140[8];          // 0x140
    int    mField148;          // 0x148
    WStr   mStr14C;            // 0x14c (16 bytes)
    WStr   mStr15C;            // 0x15c (16 bytes)
    u32    mField16C;          // 0x16c
    u32    mField170;          // 0x170
    u32    mField174;          // 0x174
    u32    mField178;          // 0x178
    u32    mField17C;          // 0x17c
    void*  mpField180;         // 0x180
    int    mField184;          // 0x184
    u32    mField188;          // 0x188
    u8     mField18C;          // 0x18c
    char   pad18D[3];          // 0x18d
    u32    mField190;          // 0x190
    u32    mField194;          // 0x194
    u32    mField198;          // 0x198
    u32    mField19C;          // 0x19c
    char   pad1A0[8];          // 0x1a0
    u32    mField1A8;          // 0x1a8
    u32    mField1AC;          // 0x1ac
    u32    mField1B0;          // 0x1b0
    char   pad1B4[8];          // 0x1b4
    u32    mField1BC;          // 0x1bc
    u32    mField1C0;          // 0x1c0
    u32    mField1C4;          // 0x1c4
    char   pad1C8[8];          // 0x1c8
    VecU32 mVec1D0;            // 0x1d0
    char   pad1DC[8];          // 0x1dc
    u32    mField1E4;          // 0x1e4
    void*  mpTargetPlanet;     // 0x1e8

    // this-class helpers
    void BaseCtor();                                         // 0x00b18660  SP::cGameData::cGameData
    void GetText(u32 key, WStr* out);                        // 0x00c487d0
    void* GetCivData();                                      // 0x00c452a0
    void* GetOwnerEmpire();                                  // 0x00c451e0
    void  GetRewardsNames(WStr* out);                        // 0x00c48c20
    void  FUN_00c48970(int idx, WStr* out);                  // 0x00c48970
    void  FUN_00c48a90(WStr* out);                           // 0x00c48a90
    void  FUN_00c48ae0(WStr* out);                           // 0x00c48ae0
    void  FUN_00c48ba0(int arg);                             // 0x00c48ba0
    void  GetUITitle(WStr* out);                             // 0x00c48d40
    void  FUN_00c48db0(WStr* out);                           // 0x00c48db0
    void  FUN_00c48e00(WStr* out);                           // 0x00c48e00
    void  FUN_00c490e0(u32 arg);                             // 0x00c490e0
    void  FUN_00c49140(WStr* out);                           // 0x00c49140
    void  FUN_00c49180(WStr* out);                           // 0x00c49180
    int   GetTagString(u32 tag, WStr* out);                  // 0x00c491c0
    void  PickRewardUnlockTools();                           // 0x00c495c0
    void  FUN_00c49800(WStr* out);                           // 0x00c49800
    void  FUN_00c49840(WStr* out);                           // 0x00c49840
    void  FUN_00c49890(WStr* out);                           // 0x00c49890
    SPObject();                                              // 0x00c48e90
};

// vtable helpers: retail loads the slot through the object's vtable pointer and
// calls it with `this` in ecx (an explicit pointer call, not a C++ virtual).
typedef char (__thiscall *FnChar)(void*);
typedef char (__thiscall *FnCharArg)(void*, int);
typedef void (__thiscall *FnVoid)(void*);
typedef void (__thiscall *FnVoidArg)(void*, int);
typedef void (__thiscall *FnVoid2)(void*, void*, int);

static inline char VT_F8(void* p) {
    return ((FnChar*)*(void**)p)[0xf8 / 4](p);
}
static inline char VT_154(void* p, int a) {
    return ((FnCharArg*)*(void**)p)[0x154 / 4](p, a);
}
static inline void VT_20(void* p, void* a, int b) {
    ((FnVoid2*)*(void**)p)[0x20 / 4](p, a, b);
}
static inline void VT_2C(void* p, void* a, int b, int c) {
    ((void (__thiscall*)(void*, void*, int, int))*((void***)*(void**)p + 0x2c / 4))(p, a, b, c);
}
static inline void VT_B4(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xb4 / 4))(p, out);
}
static inline void VT_CC(void* p, int a, WStr* out) {
    ((void (__thiscall*)(void*, int, WStr*))*((void***)*(void**)p + 0xcc / 4))(p, a, out);
}
static inline void VT_D0(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd0 / 4))(p, out);
}
static inline void VT_D4(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd4 / 4))(p, out);
}
static inline void VT_D8(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xd8 / 4))(p, out);
}
static inline void VT_DC(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xdc / 4))(p, out);
}
static inline void VT_E0(void* p, WStr* out) {
    ((void (__thiscall*)(void*, WStr*))*((void***)*(void**)p + 0xe0 / 4))(p, out);
}
static inline u32 VT_AC(void* p) {
    return ((u32 (__thiscall*)(void*))*((void***)*(void**)p + 0xac / 4))(p);
}

// =============================================================================
// @ 0x00c48970
void SPObject::FUN_00c48970(int idx, WStr* out)
{
    int v = (int)mArrE0[idx];
    if (v == 0)
        return;
    switch (mArrCC[idx]) {
    case 0:
        out->append(((CStr*)0x168ee08)->GetText());
        return;
    case 1:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee1c)->GetText());
        return;
    case 2:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee30)->GetText());
        return;
    case 3:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee44)->GetText());
        return;
    case 4:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee58)->GetText());
        return;
    case 5:
        (*(Translator**)0x16e0d08)->mField10 = v;
        out->append(((CStr*)0x168ee6c)->GetText());
        return;
    case 6:
        out->append(((CStr*)0x168ee80)->GetText());
        return;
    }
}

// ---------------------------------------------------------------------------
static inline u32 WStrLen(const wchar_t* s)
{
    const wchar_t* e = s;
    if (*e) {
        do {
            ++e;
        } while (*e);
    }
    return (u32)(e - s);
}

// @ 0x00c48a90
void SPObject::FUN_00c48a90(WStr* out)
{
    int i = mFieldFC;
    if (i >= 0 && i < 10) {
        const wchar_t* p = ((CStr*)(0x168ef48 + i * 0x14))->GetText();
        out->assign(p, p + WStrLen(p));
    }
}

// @ 0x00c48ae0
void SPObject::FUN_00c48ae0(WStr* out)
{
    switch (mKindF8) {
    case 0:
        out->append(((CStr*)0x168ee94)->GetText());
        break;
    case 1:
        out->append(((CStr*)0x168eea8)->GetText());
        return;
    case 2:
        out->append(((CStr*)0x168eebc)->GetText());
        return;
    case 3:
        out->append(((CStr*)0x168eed0)->GetText());
        return;
    case 4:
        out->append(((CStr*)0x168eee4)->GetText());
        return;
    case 5:
        out->append(((CStr*)0x168eef8)->GetText());
        return;
    }
}

// @ 0x00c48ba0
void SPObject::FUN_00c48ba0(int arg)
{
    u32* p = mVec1D0.mpBegin;
    while (p != mVec1D0.mpEnd) {
        if ((int)*p == arg) {
            VT_2C(MessageServer(), (char*)this + 0x34, arg, -10000);
            u32* next = p + 1;
            if (next < mVec1D0.mpEnd)
                memcpy(p, next, (char*)mVec1D0.mpEnd - (char*)next);
            mVec1D0.mpEnd = (u32*)((char*)mVec1D0.mpEnd - 4);
        } else {
            p++;
        }
    }
}

// @ 0x00c48c20
void SPObject::GetRewardsNames(WStr* out)
{
    bool b3 = !(mStarClueA4 == *(u32*)0x168e844 &&
                mStarClueA8 == *(u32*)0x168e848 &&
                mStarClueAC == *(u32*)0x168e84c);
    bool b2 = mFieldA0 > 0.0f;
    if (b3) {
        WStr temp;
        temp.mpBegin = 0;
        temp.mpEnd = 0;
        temp.mpCapacity = 0;
        temp.RangeInitialize(mStrB0.GetText());
        out->Append(temp.mpBegin, temp.mpEnd);
        if (temp.mpCapacity - temp.mpBegin > 1 && temp.mpBegin)
            EAFree(temp.mpBegin);
        if (!b2)
            return;
        out->Append(L" %s ", ((CStr*)0x168ef0c)->GetText());
    }
    if (b2) {
        (*(Translator**)0x16e0d08)->mField40 = *(int*)&mFieldA0;
        const wchar_t* p = ((CStr*)0x168ef20)->GetText();
        out->assign(p, p + wcslen(p));
    }
}

// @ 0x00c48d40
void SPObject::GetUITitle(WStr* out)
{
    if (mStr14C.mpBegin == mStr14C.mpEnd) {
        if (VT_F8(this) == 0)
            GetText(0xaad9c0b3, out);
        else
            GetText(0x4e1f8fa8, out);
        if (out != &mStr14C)
            mStr14C.assign(out->mpBegin, out->mpEnd);
    } else if (out != &mStr14C) {
        out->assign(mStr14C.mpBegin, mStr14C.mpEnd);
    }
}

// @ 0x00c48db0
void SPObject::FUN_00c48db0(WStr* out)
{
    if (mGroup84 == 3) {
        if (VT_F8(this) == 0)
            GetText(0xd79a86a8, out);
        else
            GetText(0x81128ae1, out);
    }
}

// @ 0x00c48e00
void SPObject::FUN_00c48e00(WStr* out)
{
    if (mGroup84 == 3) {
        if (VT_F8(this) == 0)
            GetText(0x247d8d51, out);
        else
            GetText(0xba93258e, out);
    }
}

// =============================================================================
// @ 0x00c48e90
SPObject::SPObject()
{
    BaseCtor();
    mpVtbl34 = (void*)0x13eb384;
    mpVtbl0  = (void*)0x146d188;
    mpVtbl4  = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer38.TimerCtor();
    mTimer58.TimerCtor();
    mpVtbl0  = (void*)0x146d200;
    mpVtbl4  = (void*)0x146dfb4;
    mpVtbl34 = (void*)0x146fbf0;
    mField78 = 0;
    mField7C = 0;
    mField80 = 0;
    mGroup84 = 0;
    mField88 = 0;
    mField8C = -1;
    mField90 = 0;
    mField94 = -1;
    mField98 = 0;
    mField9C = 0;
    mFieldA0 = 0.0f;
    mStarClueA4 = *(u32*)0x168e844;
    mStarClueA8 = *(u32*)0x168e848;
    mStarClueAC = *(u32*)0x168e84c;
    mStrB0.CStrCtor();
    mFieldC4 = -1;
    mFieldC8 = 0.0f;
    mArrCC = 0;
    mArrD0 = 0;
    mArrD4 = 0;
    mArrE0 = 0;
    mArrE4 = 0;
    mArrE8 = 0;
    mFieldF4 = -1;
    mKindF8 = -1;
    mFieldFC = -1;
    mField100 = -1;
    mField104 = -1;
    mField108 = 0;
    mField10C = 0;
    mField110 = 0;
    mVec11C.mpBegin = 0;
    mVec11C.mpEnd = 0;
    mVec11C.mpCapacity = 0;
    mFlags130 = 0;
    mVec134.mpBegin = 0;
    mVec134.mpEnd = 0;
    mVec134.mpCapacity = 0;
    mField148 = -1;
    mStr14C.mpBegin = (wchar_t*)0x1667bac;
    mStr14C.mpEnd = (wchar_t*)0x1667bac;
    mStr14C.mpCapacity = (wchar_t*)0x1667bae;
    mStr15C.mpBegin = (wchar_t*)0x1667bac;
    mStr15C.mpEnd = (wchar_t*)0x1667bac;
    mStr15C.mpCapacity = (wchar_t*)0x1667bae;
    mField16C = 0;
    mField170 = 0;
    mField174 = 0;
    mField178 = 0;
    mField17C = 0;
    mpField180 = 0;
    mField184 = 0;
    mField188 = 0;
    mField18C = 0;
    mField190 = 0;
    mField194 = 0;
    mField198 = 0;
    mField19C = 0;
    mField1A8 = 0;
    mField1AC = 0;
    mField1B0 = 0;
    mField1BC = 0;
    mField1C0 = 0;
    mField1C4 = 0;
    mVec1D0.mpBegin = 0;
    mVec1D0.mpEnd = 0;
    mVec1D0.mpCapacity = 0;
    mField1E4 = 0;
    mpTargetPlanet = 0;
    mVec11C.Reserve(5);
    {
        u32* first = mVec134.mpBegin;
        u32* last  = mVec134.mpEnd;
        u32* end   = mVec134.mpEnd;
        memcpy(first, last, (char*)end - (char*)last);
        mVec134.mpEnd = end - (last - first);
    }
}

// @ 0x00c490e0
void SPObject::FUN_00c490e0(u32 arg)
{
    if (VT_154(this, arg) == 0) {
        VT_20(MessageServer(), (char*)this + 0x34, arg);
        mVec1D0.push_back(arg);
    }
}

// civ / empire data view shared by the two UI-title builders below
struct CivData {
    void  FUN_c30c80();                                          // 0x00c30c80
    int*  GetCities();                                           // 0x005c65e0
};

// @ 0x00c49140
void SPObject::FUN_00c49140(WStr* out)
{
    CivData* o = (CivData*)GetCivData();
    if (o) {
        o->FUN_c30c80();
        WStr3(out, (const wchar_t*)0x13f5c04, *o->GetCities());
    }
}

// @ 0x00c49180
void SPObject::FUN_00c49180(WStr* out)
{
    CivData* o = (CivData*)GetOwnerEmpire();
    if (o) {
        o->FUN_c30c80();
        WStr3(out, (const wchar_t*)0x13f5c04, *o->GetCities());
    }
}

// objects reached through the target planet pointer; only the used members are
// modelled here.
struct SorterObj {
    void* operator()();                                          // 0x00b8de30
    WStr* FUN_00bb9de0();                                        // 0x00bb9de0
};

struct PlanetObj {
    WStr* GetName();                                             // 0x00c707e0
};

// @ 0x00c491c0
int SPObject::GetTagString(u32 tag, WStr* out)
{
    wchar_t buf[64];

    if (tag == 0xa593874e) {
        if (mpTargetPlanet) {
            void* sorter = *(void**)((char*)mpTargetPlanet + 0x13c);
            if (sorter) {
                void* r = ((SorterObj*)sorter)->operator()();
                if (r) {
                    WStr* w = ((SorterObj*)r)->FUN_00bb9de0();
                    out->assign(w->mpBegin, w->mpEnd);
                }
            }
        }
        return 1;
    }

    if (tag == 0xa499e2f0) {
        if (mpTargetPlanet) {
            WStr* name = ((PlanetObj*)mpTargetPlanet)->GetName();
            if (name != out)
                out->assign(name->mpBegin, name->mpEnd);
        }
        return 1;
    }

    if (tag == 0xcaf36e4a) { FUN_00c48900(out); return 1; }
    if (tag == 0x8b0eb564) { FUN_00c48940(out); return 1; }
    if (tag == 0x200cc87d) { VT_B4(this, out);  return 1; }
    if (tag == 0xe3224d84) { GetRewardsNames(out); return 1; }
    if (tag == 0x68e2e9c6) { FUN_00c49140(out); return 1; }
    if (tag == 0xc2efec3f) { FUN_00c486f0(out); return 1; }
    if (tag == 0xfb301e72) { FUN_00c49180(out); return 1; }

    if (tag != 0x4434801b) {
        if (tag == 0x85f50ff7) {
            if ((mFlags130 >> 1) & 1) { VT_CC(this, 0, out); return 1; }
        }
        else if (tag == 0x85f50ff4) {
            if ((mFlags130 >> 1) & 1) { VT_CC(this, 1, out); return 1; }
        }
        else if (tag == 0x3eae770b) {
            if ((mFlags130 >> 1) & 1) { VT_D0(this, out); return 1; }
        }
        else if (tag == 0x4bf8f3dc) {
            if ((mFlags130 >> 1) & 1) { VT_D4(this, out); return 1; }
        }
        else {
            if (tag != 0x53f90032) {
                if (tag == 0xd1c3d278) {
                    if ((mFlags130 >> 2) & 1) { VT_DC(this, out); return 1; }
                }
                else {
                    if (tag != 0x39e8da5f) {
                        if (tag == 0xd1ce9de3) {
                            u32 ms = VT_AC(this);
                            u32 total = ms / 1000;
                            FUN_00881730(0, (int)(total / 60), (int)(total % 60), buf, 0x40,
                                         (const wchar_t*)0x146d3c4);
                            out->append(buf);
                            return 1;
                        }
                        if (tag == 0x22e33d08) {
                            (*(Translator**)0x16e0d08)->mField40 = (float)mField184;
                        }
                        else {
                            if (tag != 0xad9e5ea2 && tag != 0xc22d2221)
                                return 0;
                            (*(Translator**)0x16e0d08)->mField40 = (float)mField188;
                        }
                        out->append(((CStr*)0x168ef20)->GetText());
                        return 1;
                    }
                    if ((mFlags130 >> 2) & 1) { VT_E0(this, out); return 1; }
                }
                out->append(L"ERROR: PLANET NAME IS NOT HIDDEN");
                return 1;
            }
            if ((mFlags130 >> 1) & 1) { VT_D8(this, out); return 1; }
        }
        out->append(L"ERROR: STAR NAME IS NOT HIDDEN");
        return 1;
    }
    FUN_00c48740(out);
    return 1;
}

// ---------------------------------------------------------------------------
// Reward-tool picking.  The retail function walks the resource-manager property
// system through a tool-set object stored at +0x180; the call sequence below is
// reconstructed from the decompilation.
struct ToolSet {
    char  HasTag(u32 tag) {                                      // vtable +0x1c
        return ((char (__thiscall*)(void*, u32))*((void***)*(void**)this + 0x1c / 4))(this, tag);
    }
    char  GetEntry(u32 tag, void* out) {                         // vtable +0x24
        return ((char (__thiscall*)(void*, u32, void*))*((void***)*(void**)this + 0x24 / 4))(this, tag, out);
    }
    void* GetList(u32 tag) {                                     // vtable +0x28
        return ((void* (__thiscall*)(void*, u32))*((void***)*(void**)this + 0x28 / 4))(this, tag);
    }
};

struct Property {
    int* GetInt();                                               // 0x0041e990
};

struct UnlockEntry {                // 0x18-byte record written by ToolSet::GetEntry
    Property* mpProperty;           // 0x00
    u32    mField4;
    u32    mField8;
    u32    mFieldC;
    u16    mField10;
    u16    mField12;                // must equal 9
    u16    mField14;
    u16    mField16;
};

struct KeyList {                    // list returned by ToolSet::GetList
    Entry12* mpData;                // 0x00
    u32    mField4;                 // 0x04
    int    mCount;                  // 0x08
    u16    mFieldC;                 // 0x0c
    u16    mFieldE;                 // 0x0e
    u16    mFlags10;                // 0x10  (bit 0x30 set => vector payload)
    u16    mField12;                // 0x12
};

struct RandomLC {
    u32 RandomUint32Uniform(u32 n);                              // 0x00a68fb0
};

extern RandomLC gRandom;                                         // 0x01601760

// @ 0x00c495c0
void SPObject::PickRewardUnlockTools()
{
    int group = 0;
    void* empire = GetOwnerEmpire();
    if (empire)
        group = *(int*)((char*)empire + 0x54);

    ToolSet* tools = (ToolSet*)mpField180;
    if (!tools)
        return;

    u32 tag = 0x7895f232;
    if (group == 1) {
        u32 alt = 0xefc800f5;
        if (tools->HasTag(alt)) tag = alt;
    }
    else if (group == 2) {
        u32 alt = 0xb1fc43;
        if (tools->HasTag(alt)) tag = alt;
    }
    else if (group == 3) {
        u32 alt = 0xb3fef39a;
        if (tools->HasTag(alt)) tag = alt;
    }

    if (!tools->HasTag(tag))
        return;

    tools = (ToolSet*)mpField180;
    if (!tools)
        return;

    UnlockEntry entry;
    if (!tools->GetEntry(tag, &entry))
        return;
    if (entry.mField12 != 9)
        return;

    int* pCount = entry.mpProperty ? entry.mpProperty->GetInt() : 0;
    if (!pCount || *pCount < 1)
        return;

    u32 tag2 = 0x828f44dc;
    if (group == 1) {
        u32 alt = 0xeaaaac60;
        if (tools->HasTag(alt)) tag2 = alt;
    }
    else if (group == 2) {
        u32 alt = 0x8aa0ab86;
        if (tools->HasTag(alt)) tag2 = alt;
    }
    else if (group == 3) {
        u32 alt = 0x1625a62d;
        if (tools->HasTag(alt)) tag2 = alt;
    }

    if (!tools->HasTag(tag2))
        return;

    KeyList* list = (KeyList*)tools->GetList(tag2);
    if (!list)
        return;

    int n;
    Entry12* src;
    if ((list->mFlags10 & 0x30) == 0) {
        if (list->mField12 == 0)
            return;
        n = 1;
        src = (Entry12*)list;
    }
    else {
        n = list->mCount;
        if (n < 1)
            return;
        src = list->mpData;
    }

    int oldCount = (int)(mVec11C.mpEnd - mVec11C.mpBegin);
    for (int i = 0; i < n; ++i) {
        Entry12 e;
        e.mKey = src[i].mKey;
        e.mField4 = 0;
        e.mField8 = 0;
        mVec11C.push_back(e);
    }

    int rem = n - oldCount;
    for (int i = 0; i < rem; ++i) {
        int count = (int)(mVec11C.mpEnd - mVec11C.mpBegin);
        u32 idx = gRandom.RandomUint32Uniform((u32)count);
        if ((int)idx != count - 1) {
            Entry12* last = mVec11C.mpEnd - 1;
            mVec11C.mpBegin[idx] = *last;
        }
        mVec11C.mpEnd -= 1;
    }
}

// ---------------------------------------------------------------------------
static inline int Rt(const float& f)
{
    return _mm_cvt_ss2si(_mm_load_ss(&f));
}

// @ 0x00c49800
void SPObject::FUN_00c49800(WStr* out)
{
    float f = mFieldC8;
    int i = Rt(f);
    if ((float)i < f)
        i++;
    WStr3(out, (const wchar_t*)0x13f01bc, i);
}

// @ 0x00c49840
void SPObject::FUN_00c49840(WStr* out)
{
    float f = mFieldC8 - 0.5f;
    int i = Rt(f);
    WStr4(out, (const wchar_t*)0x13f01bc, i, mFieldC8 + 0.5f);
}

// @ 0x00c49890
void SPObject::FUN_00c49890(WStr* out)
{
    float f = mFieldC8 + 0.5f;
    int i = Rt(f);
    WStr3(out, (const wchar_t*)0x13f01bc, i);
}
