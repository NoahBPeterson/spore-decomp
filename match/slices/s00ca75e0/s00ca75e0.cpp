// Slice s00ca75e0 -- Simulator::cVehicle constructor/destructor cluster plus the
// angry-crowd-attack / continent helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"

// VF(obj, slot): the function pointer stored in slot `slot` of *obj's vtable.
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// helper types
// ---------------------------------------------------------------------------
struct cSPVector3 { float x, y, z; };
struct cSPVector4 { float x, y, z, w; };

// eastl::basic_string<wchar_t,eastl::allocator>  (size 0x10)
struct eWstring {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mAllocator;
    void FUN_00423650(const wchar_t* first, const wchar_t* last);  // 0x00423650 eastl::wstring::assign
    void FUN_0056e2d0(const void* other);                          // 0x0056e2d0 eastl::wstring copy-ctor
    void FUN_00579a90(const wchar_t* p);                           // 0x00579a90 eastl::wstring::range_initialize
};

// Deque64 iterator (mpCurrent, mpBegin, mpEnd, mpCurrentArrayPtr)
struct DeqIter {
    uint32_t*  mpCurrent;
    uint32_t*  mpBegin;
    uint32_t*  mpEnd;
    uint32_t** mpCurrentArrayPtr;
};

// eastl::deque<...,64>  (size 0x2c)
struct UIntDeque {
    uint32_t* mpPtrArray;      // +0x00
    uint32_t  mnPtrArraySize;  // +0x04
    DeqIter   mItBegin;        // +0x08
    DeqIter   mItEnd;          // +0x18
    uint32_t  mAllocator;      // +0x28

    void FUN_00996460();        // 0x00996460 deque::clear
    void FUN_0098b5e0();        // 0x0098b5e0 deque::~deque
    void FUN_01045370(const uint32_t* v);  // 0x01045370 deque::push_back slow path

    void push_back(const uint32_t& value) {
        uint32_t* cur = mItEnd.mpCurrent;
        uint32_t* nxt = cur + 1;
        if (nxt != mItEnd.mpEnd) {
            mItEnd.mpCurrent = nxt;
            if (cur) *cur = value;
        } else {
            FUN_01045370(&value);
        }
    }
};

// SP::cSPTimer / SP::cGonzagoTimer  (size 0x20)
struct cGonzagoTimer {
    void**  mpVtbl;        // +0x00
    uint8_t mData[0x1c];   // +0x04

    void FUN_00b63890();        // 0x00b63890 ctor
    void FUN_00b638b0();        // 0x00b638b0 dtor
    bool FUN_00feba90();        // 0x00feba90 IsRunning
    void FUN_00bc3130();        // 0x00bc3130 Restart
    void FUN_00bc3110();        // 0x00bc3110 Stop
};

// opaque sub-objects of cVehicle addressed through their leading vptr field
struct Opaque {
    void FUN_00b18660();   // 0x00b18660 SP::cGameData::cGameData
    void FUN_00b184c0();   // 0x00b184c0 SP::cGameData::~cGameData
    void FUN_00c43860();   // 0x00c43860 ctor at +0x34
    void FUN_00c432e0();   // 0x00c432e0 dtor at +0x34
    void FUN_00bfd4e0();   // 0x00bfd4e0 SP::cCombatant::cCombatant
    void FUN_00bfcd00();   // 0x00bfcd00 dtor at +0x508
    void FUN_00abfe50();   // 0x00abfe50 ctor at +0x5d0
    void FUN_00abfec0();   // 0x00abfec0 dtor at +0x5d0
    void FUN_00ac03d0();   // 0x00ac03d0 SP::cInteractionTarget::cInteractionTarget
    void FUN_00ac0520();   // 0x00ac0520 dtor at +0x638
    void FUN_00c7d700();   // 0x00c7d700 ctor at +0x650
    void FUN_00c7d650();   // 0x00c7d650 dtor at +0x650
    void FUN_00ca75a0();   // 0x00ca75a0 dtor at +0xb68
    void FUN_00ca43e0();   // 0x00ca43e0 dtor at +0xc64
    void FUN_00ae6930();   // 0x00ae6930 dtor at +0xb8c
    void FUN_00ca09f0(int); // 0x00ca09f0 deque init at +0xb2c
};
// but +0xb2c / +0xb68 / +0xc64 / +0xb8c take extra args
struct OpaqueInit { void FUN_00ca09f0(int n); };

struct ContainerB68 { uint32_t m[5]; };  // size 0x14 (+0xb68)
struct ContainerC64 { uint32_t m[5]; };  // size 0x14 (+0xc64)
struct IntsB8C      { uint32_t m[3]; };  // size 0x0c (+0xb8c)

struct Base650 {
    void**  mpVtbl;        // +0x000
    uint8_t mRest[0x49c];  // +0x004
};

// serializer ("cListArchive")
class cListArchive {
public:
    virtual void  v00(const wchar_t* name);  // +0x00 begin list
    virtual void  v04(const wchar_t* name);  // +0x04 end list
    virtual void  v08();                     // +0x08
    virtual void  v0c();                     // +0x0c
    virtual void  v10();                     // +0x10
    virtual void  v14();                     // +0x14
    virtual void* v18();                     // +0x18
    virtual void* v1c();                     // +0x1c
    virtual void* v20();                     // +0x20
    virtual void  v24();                     // +0x24
    virtual void  v28();                     // +0x28
    virtual void  v2c(void* v);              // +0x2c
};

// SP::cPlanetModel
struct cPlanetModel {
    uint8_t pad0[0x64];
    int32_t mI64;                            // +0x64
    void* FUN_00b88590(cSPVector3* pos);     // 0x00b88590 GetContinent
};

// cCity
struct cCity {
    cSPVector3* FUN_00fa0e00();  // 0x00fa0e00 GetPositionPtr
    void*       FUN_00bd8210();  // 0x00bd8210 GetContinent
};

// ---------------------------------------------------------------------------
// external free functions / globals
// ---------------------------------------------------------------------------
extern "C" {
    void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0 operator_new
    void  __cdecl FUN_00f47380(void* p);                                                        // 0x00f47380 operator_delete_array
    void  __cdecl FUN_0093a780(void* stream, void* out, int n, int b);                          // 0x0093a780 ReadInt32
    void  __cdecl FUN_0093aa70(void* stream, void* out, int n, int b);                          // 0x0093aa70 WriteUint32
    void* __cdecl FUN_0093c5a0(void* out, int value, int unused);                               // 0x0093c5a0 EA::ConvertToString16
    void  __cdecl FUN_00ca44f0(void* begin, int i, int n, int i2);                              // 0x00ca44f0 heap sift-down
    void  __cdecl FUN_00ca4600(void* begin, void* end, cSPVector4 v);                           // 0x00ca4600 heap pop
    char  __cdecl FUN_00ac8050(void* archive, int key, void* elem);                             // 0x00ac8050 read list element
    void* __cdecl FUN_00b3d290(void* str, void* v);                                             // 0x00b3d290
    cPlanetModel* __cdecl FUN_00b3d350();                                                       // 0x00b3d350 SP::PlanetModel
    void* __cdecl FUN_00b5b800();                                                               // 0x00b5b800 SP::GetCurrentGameMode
    void* __cdecl FUN_01021300();                                                               // 0x01021300 SP::cSPLivingUniverse::GetPlayerEmpire
}

struct OrderMgr { void* FUN_00bcb2a0(); void FUN_00bcae90(); };  // 0x00bcb2a0 ctor / 0x00bcae90 dtor
struct RcObj    { void FUN_00ac65d0(); };                        // 0x00ac65d0

extern float g_01473c70;   // 0x01473c70
extern float g_013ef568;   // 0x013ef568
extern float g_01485720;   // 0x01485720  _HK_REAL_ONE
extern float g_01470f1c;   // 0x01470f1c
extern float g_013eb1bc;   // 0x013eb1bc
extern float g_01699b08;   // 0x01699b08
extern float g_01699b0c;   // 0x01699b0c
extern float g_01699b10;   // 0x01699b10
extern char  g_01654c04;   // 0x01654c04
extern char  g_01667bac;   // 0x01667bac  ?gEmptyString16@eastl@@3PA_WA
extern char  g_01667bad;   // 0x01667bad
extern char  g_01667bae;   // 0x01667bae
extern const wchar_t g_01565b2c[];  // 0x01565b2c
extern const wchar_t g_01565b40[];  // 0x01565b40
extern const wchar_t g_01565b54[];  // 0x01565b54

namespace Simulator {

class cVehicle {
public:
    // +0x000
    void** mpVtbl000;
    void** mpVtbl004;
    uint8_t mPad008[0x2c];
    void** mpVtbl034;          // +0x034 locomotor sub-object vptr
    uint8_t mPad038[0x50];
    int32_t mI088;             // +0x088
    uint8_t mPad08C[0x7c];
    void** mpVtbl108;          // +0x108
    uint8_t mPad10C[0xd0];
    cSPVector3 mVec1DC;        // +0x1dc
    cSPVector3 mVec1E8;        // +0x1e8
    float mF1F4;               // +0x1f4
    float mF1F8;               // +0x1f8
    uint8_t mPad1FC[0x1c];
    float mF218;               // +0x218
    uint8_t mPad21C[0x88];
    int32_t mI2A4;             // +0x2a4
    uint8_t mPad2A8[0x244];
    uint32_t mU4EC;            // +0x4ec
    uint8_t mPad4F0[0x18];
    void** mpVtbl508;          // +0x508
    uint8_t mPad50C[5];
    uint8_t mB511;             // +0x511
    uint8_t mPad512[0x2e];
    float mF540;               // +0x540
    uint8_t mPad544[0x8c];
    void** mpVtbl5D0;          // +0x5d0
    uint8_t mPad5D4[0x64];
    void** mpVtbl638;          // +0x638
    uint8_t mPad63C[0x14];
    Base650 mBase650;          // +0x650
    void* mPaf0;               // +0xaf0
    uint8_t mBaf4;             // +0xaf4
    uint8_t mPadAF5[3];
    uint32_t mUaf8;            // +0xaf8
    uint8_t mBafc;             // +0xafc
    uint8_t mPadAFD[3];
    uint32_t mUb00;            // +0xb00
    uint32_t mUb04;            // +0xb04
    int32_t mIb08;             // +0xb08
    float mFb0c;               // +0xb0c
    float mFb10;               // +0xb10
    float mFb14;               // +0xb14
    float mFb18;               // +0xb18
    int32_t mIb1c;             // +0xb1c
    uint32_t mUb20;            // +0xb20
    uint32_t mUb24;            // +0xb24
    uint32_t mUb28;            // +0xb28
    UIntDeque mEvents;         // +0xb2c
    float mFb58;               // +0xb58
    void* mPb5c;               // +0xb5c
    void* mPb60;               // +0xb60
    void* mPb64;               // +0xb64
    ContainerB68 mContainerB68; // +0xb68
    void* mPb7c;               // +0xb7c
    float mFb80;               // +0xb80
    float mFb84;               // +0xb84
    float mFb88;               // +0xb88
    IntsB8C mB8C;              // +0xb8c
    uint8_t mPadB98[8];
    cGonzagoTimer mTimerBA0;   // +0xba0
    void* mPbc0;               // +0xbc0
    int32_t mIbc4;             // +0xbc4
    uint32_t mUbc8;            // +0xbc8
    uint8_t mBcc[6];           // +0xbcc
    uint8_t mPadBD2[6];
    cGonzagoTimer mTimerBD8;   // +0xbd8
    cGonzagoTimer mTimerBF8;   // +0xbf8
    cGonzagoTimer mTimerC18;   // +0xc18
    uint32_t mUc38;            // +0xc38
    uint8_t mPadC3C[0xc];
    float mFc48;               // +0xc48
    float mFc4c;               // +0xc4c
    float mFc50;               // +0xc50
    float mFc54;               // +0xc54
    float mFc58;               // +0xc58
    float mFc5c;               // +0xc5c
    float mFc60;               // +0xc60
    ContainerC64 mContainerC64; // +0xc64
    uint32_t mUc78;            // +0xc78
    uint32_t mUc7c;            // +0xc7c
    uint32_t mUc80;            // +0xc80
    uint32_t mUc84;            // +0xc84
    cGonzagoTimer mTimerC88;   // +0xc88
    cGonzagoTimer mTimerCA8;   // +0xca8
    eWstring mName;            // +0xcc8
    cGonzagoTimer mTimerCD8;   // +0xcd8
    uint8_t mPadCF8[4];
    void* mPcfc;               // +0xcfc
    void* mPd00;               // +0xd00
    uint32_t mUd04;            // +0xd04
    uint32_t mUd08;            // +0xd08
    uint32_t mUd0c;            // +0xd0c
    uint8_t mBd10;             // +0xd10
    uint8_t mPadD11[3];
    eWstring mWd14;            // +0xd14
    uint32_t mUd24;            // +0xd24
    uint8_t mPadD28[4];
    float mFd2c;               // +0xd2c
    int32_t mId30;             // +0xd30
    cSPVector3 mVecD34;        // +0xd34
    cSPVector3 mVecD40;        // +0xd40
    cSPVector3 mVecD4C;        // +0xd4c
    cSPVector3 mVecD58;        // +0xd58
    uint32_t mUd64;            // +0xd64
    float mFd68;               // +0xd68
    uint32_t mUd6c;            // +0xd6c
    uint32_t mUd70;            // +0xd70
    uint32_t mUd74;            // +0xd74
    uint32_t mUd78;            // +0xd78
    uint32_t mUd7c;            // +0xd7c
    uint32_t mUd80;            // +0xd80
    uint32_t mUd84;            // +0xd84
    uint32_t mUd88;            // +0xd88
    float mFd8c;               // +0xd8c
    float mFd90;               // +0xd90
    void* mPd94;               // +0xd94

    cVehicle();
    ~cVehicle();

    void FUN_00ca72a0();
    void FUN_00ca80e0(uint32_t v);
    void ContinueAngryCrowdAttack(bool force);
    void EndAngryCrowdAttack();
    void FUN_00ca81d0(cSPVector3* a, float b, float c, int d);
    bool FUN_00ca8340(cCity* city);
};

}  // namespace Simulator

// ===========================================================================
// free helpers
// ===========================================================================

// @ 0x00ca75e0
void* __cdecl FUN_00ca75e0(cListArchive* mgr, UIntDeque* q)
{
    q->FUN_00996460();
    uint32_t count;
    count = 0;
    void* s0 = mgr->v20();
    void* stream0 = ((cListArchive*)s0)->v18();
    FUN_0093a780(stream0, &count, 1, 0);
    for (uint32_t k = 0; k < count; ++k) {
        void* s1 = mgr->v20();
        void* stream1 = ((cListArchive*)s1)->v18();
        uint32_t v;
        FUN_0093a780(stream1, &v, 1, 0);
        q->push_back(v);
    }
    return mgr->v1c();
}

// @ 0x00ca7690
void __cdecl FUN_00ca7690(cListArchive* a, void** vec)
{
    uint32_t n = (uint32_t)(((char*)vec[1] - (char*)vec[0]) >> 2);
    void* s0 = a->v20();
    void* stream0 = ((cListArchive*)s0)->v18();
    FUN_0093aa70(stream0, &n, 1, 0);
    void** p = (void**)vec[0];
    void** e = (void**)vec[1];
    for (; p != e; ++p) {
        void* elem = *p;
        uint32_t r = 0;
        if (elem)
            r = ((uint32_t(__thiscall*)(void*, int))VF(elem, 0x5c / 4))(elem, 0x179c807);
        a->v2c((void*)r);
    }
    a->v1c();
}

// @ 0x00ca77b0
void __cdecl FUN_00ca77b0(char* begin, char* end, cSPVector4 v)
{
    int n = (int)((end - begin) >> 2);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        void* elem = *(void**)(begin + i * 4);
        if (elem)
            ((void(__cdecl*)(void*, cSPVector4))VF(elem, 0x60 / 4))(elem, v);
        FUN_00ca44f0(begin, i, n, i);
    } while (i != 0);
}

// @ 0x00ca7830
void __cdecl FUN_00ca7830(char* begin, char* end, cSPVector4 v)
{
    for (int u = (int)(end - begin); 4 < (u & ~3); u -= 4) {
        FUN_00ca4600(begin, end, v);
        end -= 4;
    }
}

// helper: build the list-name wstring from a key (mirrors the inlined eastl code)
static void buildListName(eWstring* name, int key)
{
    if (key == 0) {
        eWstring tmp;
        tmp.mpBegin = 0;
        tmp.mpEnd = 0;
        tmp.mpCapacity = 0;
        tmp.FUN_00579a90(0);
        name->FUN_0056e2d0(&tmp);
        if (tmp.mpBegin
            && (int)(((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & ~1u) > 2)
            FUN_00f47380(tmp.mpBegin);
    } else {
        eWstring tmp;
        FUN_0093c5a0(&tmp, key, -1);
        name->FUN_0056e2d0(&tmp);
        if (tmp.mpBegin
            && (int)(((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & ~1u) > 2)
            FUN_00f47380(tmp.mpBegin);
    }
}

static void freeName(eWstring* name)
{
    if (name->mpBegin
        && (int)(((char*)name->mpCapacity - (char*)name->mpBegin) & ~1u) > 2)
        FUN_00f47380(name->mpBegin);
}

// @ 0x00ca8470
bool __cdecl FUN_00ca8470(cListArchive* a, int key, UIntDeque* d)
{
    if (d->mItBegin.mpCurrent == d->mItEnd.mpCurrent)
        return true;

    eWstring name;
    buildListName(&name, key);
    const wchar_t* nm = (name.mpBegin == name.mpCapacity) ? L"list" : (const wchar_t*)name.mpBegin;
    a->v00(nm);

    bool flag = true;
    uint32_t* cur = d->mItBegin.mpCurrent;
    uint32_t* blkEnd = d->mItBegin.mpEnd;
    uint32_t** blk = d->mItBegin.mpCurrentArrayPtr;
    uint32_t* end = d->mItEnd.mpCurrent;
    while (cur != end) {
        flag = (flag != 0);
        ++cur;
        if (cur == blkEnd) {
            ++blk;
            uint32_t* nb = *blk;
            cur = nb;
            blkEnd = nb + 64;
        }
    }

    a->v04(nm);
    freeName(&name);
    return flag;
}

// @ 0x00ca85c0
bool __cdecl FUN_00ca85c0(cListArchive* a, int key, void** v)
{
    if (v[0] == v[1])
        return true;

    eWstring name;
    buildListName(&name, key);
    const wchar_t* nm = (name.mpBegin == name.mpCapacity) ? L"list" : (const wchar_t*)name.mpBegin;
    a->v00(nm);

    bool ok = true;
    char* p = (char*)v[0];
    char* e = (char*)v[1];
    for (; p != e; p += 0x18) {
        if (ok)
            ok = FUN_00ac8050(a, 0, p) != 0;
    }

    a->v04(nm);
    freeName(&name);
    return ok;
}

// ===========================================================================
// Simulator::cVehicle
// ===========================================================================
using Simulator::cVehicle;

// @ 0x00ca78a0
Simulator::cVehicle::cVehicle()
{
    ((Opaque*)&mpVtbl000)->FUN_00b18660();
    ((Opaque*)&mpVtbl034)->FUN_00c43860();
    ((Opaque*)&mpVtbl508)->FUN_00bfd4e0();
    ((Opaque*)&mpVtbl5D0)->FUN_00abfe50();
    ((Opaque*)&mpVtbl638)->FUN_00ac03d0();
    ((Opaque*)&mBase650)->FUN_00c7d700();

    mpVtbl508  = (void**)0x1474d60;
    mpVtbl034  = (void**)0x1474c60;
    mpVtbl000  = (void**)0x1474c08;
    mpVtbl004  = (void**)0x1474bf8;
    mpVtbl108  = (void**)0x1474bf0;
    mpVtbl5D0  = (void**)0x1474b88;
    mpVtbl638  = (void**)0x1474b6c;
    mBase650.mpVtbl = (void**)0x1474b54;

    mPaf0 = 0;
    mBaf4 = 0;
    mUaf8 = 0;
    mBafc = 0;
    mUb00 = 0;
    mUb04 = 0;
    mIb08 = 1;
    mFb0c = 0.0f;
    mFb10 = 0.0f;
    mFb14 = 0.0f;
    mFb18 = g_01473c70;
    mIb1c = 0;
    mUb20 = 0;
    mUb24 = 0;
    mUb28 = 0;

    ((OpaqueInit*)&mEvents)->FUN_00ca09f0(0);

    mFb58 = 0.0f;
    mPb5c = 0;
    mPb60 = 0;
    mPb64 = 0;
    mContainerB68.m[0] = 0;
    mContainerB68.m[1] = 0;
    mContainerB68.m[2] = 0;
    mPb7c = 0;
    mFb80 = g_01699b08;
    mFb84 = g_01699b0c;
    mFb88 = g_01699b10;
    mB8C.m[0] = 0;
    mB8C.m[1] = 0;
    mB8C.m[2] = 0;

    mTimerBA0.FUN_00b63890();
    mPbc0 = 0;
    mIbc4 = 1;
    mUbc8 = 0;
    mBcc[0] = 0; mBcc[1] = 0; mBcc[2] = 0;
    mBcc[3] = 0; mBcc[4] = 0; mBcc[5] = 0;

    mTimerBD8.FUN_00b63890();
    mTimerBF8.FUN_00b63890();
    mTimerC18.FUN_00b63890();

    mFc48 = 0.0f;
    mFc4c = 0.0f;
    mFc50 = g_013ef568;
    mFc54 = g_013ef568;
    mFc58 = g_013ef568;
    mUc38 = 0;
    mFc5c = g_01485720;
    mFc60 = g_01485720;
    mContainerC64.m[0] = 0;
    mContainerC64.m[1] = 0;
    mContainerC64.m[2] = 0;
    mUc78 = 0;
    mUc7c = 0x7d0;
    mUc80 = 0x7d0;
    mUc84 = 0;

    mTimerC88.FUN_00b63890();
    mTimerCA8.FUN_00b63890();

    mName.mpBegin = &g_01667bac;
    mName.mpEnd = &g_01667bac;
    mName.mpCapacity = &g_01667bae;

    mTimerCD8.FUN_00b63890();

    mPcfc = 0;
    mPd00 = 0;
    mUd04 = 0;
    mUd08 = 0;
    mUd0c = 0;
    mBd10 = 0;

    mWd14.mpBegin = &g_01667bac;
    mWd14.mpEnd = &g_01667bac;
    mWd14.mpCapacity = &g_01667bad;

    mUd24 = 0;
    mFd2c = 0.0f;
    mId30 = 3;
    mVecD34.x = g_01699b08; mVecD34.y = g_01699b0c; mVecD34.z = g_01699b10;
    mVecD40.x = g_01699b08; mVecD40.y = g_01699b0c; mVecD40.z = g_01699b10;
    mVecD4C.x = g_01699b08; mVecD4C.y = g_01699b0c; mVecD4C.z = g_01699b10;
    mVecD58.x = g_01699b08; mVecD58.y = g_01699b0c; mVecD58.z = g_01699b10;
    mUd64 = 0;
    mFd8c = 0.0f;
    mFd90 = 0.0f;
    mFd68 = g_01485720;
    mUd6c = 0; mUd70 = 0; mUd74 = 0; mUd78 = 0;
    mUd7c = 0; mUd80 = 0; mUd84 = 0; mUd88 = 0;
    mPd94 = 0;
    mF218 = g_01470f1c;
    mI088 = 7;
    mF540 = g_013eb1bc;

    void* p = FUN_00f473a0(0x670, "Simulator/cBehaviorTreeData", 0, 0, 0, 0);
    mPaf0 = p ? ((OrderMgr*)p)->FUN_00bcb2a0() : 0;

    mB511 = 1;

    const wchar_t* nm = L"UNINITIALIZED VEHICLE NAME";
    const wchar_t* nme = nm;
    while (*nme)
        ++nme;
    mName.FUN_00423650(nm, nme);
}

// @ 0x00ca7ef0
Simulator::cVehicle::~cVehicle()
{
    void* order = mPaf0;

    mpVtbl000 = (void**)0x1474c08;
    mpVtbl004 = (void**)0x1474bf8;
    mpVtbl034 = (void**)0x1474c60;
    mpVtbl108 = (void**)0x1474bf0;
    mpVtbl508 = (void**)0x1474d60;
    mpVtbl5D0 = (void**)0x1474b88;
    mpVtbl638 = (void**)0x1474b6c;
    mBase650.mpVtbl = (void**)0x1474b54;

    if (order) {
        ((OrderMgr*)order)->FUN_00bcae90();
        FUN_00f47380(order);
    }

    void* pD94 = mPd94;
    if (pD94)
        ((void(__thiscall*)(void*))VF(pD94, 1))(pD94);

    if (mWd14.mpBegin
        && (int)((char*)mWd14.mpCapacity - (char*)mWd14.mpBegin) > 1)
        FUN_00f47380(mWd14.mpBegin);

    if (mPd00)
        ((void(__thiscall*)(void*))VF((char*)mPd00, 0))(mPd00);  // SP::cAnimatingCreature::Release

    void* pCfc = mPcfc;
    if (pCfc)
        ((void(__thiscall*)(void*))VF(pCfc, 1))(pCfc);

    mTimerCD8.FUN_00b638b0();

    if (mName.mpBegin
        && (int)(((char*)mName.mpCapacity - (char*)mName.mpBegin) & ~1u) > 2)
        FUN_00f47380(mName.mpBegin);

    mTimerCA8.FUN_00b638b0();
    mTimerC88.FUN_00b638b0();
    ((Opaque*)&mContainerC64)->FUN_00ca43e0();
    mTimerC18.FUN_00b638b0();
    mTimerBF8.FUN_00b638b0();
    mTimerBD8.FUN_00b638b0();

    void* pBc0 = mPbc0;
    if (pBc0)
        ((void(__thiscall*)(void*))VF(pBc0, 1))(pBc0);

    mTimerBA0.FUN_00b638b0();
    ((Opaque*)&mB8C)->FUN_00ae6930();

    void* pB7c = mPb7c;
    if (pB7c)
        ((void(__thiscall*)(void*))VF(pB7c, 0xc0 / 4))(pB7c);

    ((Opaque*)&mContainerB68)->FUN_00ca75a0();

    if (mPb64)
        ((void(__thiscall*)(void*))VF(mPb64, 2))(mPb64);
    if (mPb60)
        ((void(__thiscall*)(void*))VF(mPb60, 2))(mPb60);
    if (mPb5c)
        ((void(__thiscall*)(void*))VF(mPb5c, 1))(mPb5c);

    mEvents.FUN_0098b5e0();
    ((Opaque*)&mBase650)->FUN_00c7d650();
    ((Opaque*)&mpVtbl638)->FUN_00ac0520();
    ((Opaque*)&mpVtbl5D0)->FUN_00abfec0();
    ((Opaque*)&mpVtbl508)->FUN_00bfcd00();
    ((Opaque*)&mpVtbl034)->FUN_00c432e0();

    ((Opaque*)&mpVtbl000)->FUN_00b184c0();
}

// @ 0x00ca80e0
void Simulator::cVehicle::FUN_00ca80e0(uint32_t v)
{
    mEvents.push_back(v);
}

// @ 0x00ca8120
void Simulator::cVehicle::ContinueAngryCrowdAttack(bool force)
{
    if (mTimerBF8.FUN_00feba90() || force) {
        mTimerBF8.FUN_00bc3130();
        mEvents.push_back(0x1a);
    }
}

// @ 0x00ca8180
void Simulator::cVehicle::EndAngryCrowdAttack()
{
    mTimerBF8.FUN_00bc3110();
    mEvents.push_back(0x1b);
}

// @ 0x00ca81d0
void Simulator::cVehicle::FUN_00ca81d0(cSPVector3* a, float b, float c, int d)
{
    typedef cSPVector3* (__thiscall *GetPosFn)(void*);
    FUN_00ca72a0();

    cSPVector3* pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
    mVec1DC = *pos;
    mVec1E8 = *a;
    mF1F4 = b;
    mF1F8 = c;
    mI2A4 = 4;
    mVecD34 = *a;

    void* p = ((void*(__thiscall*)(void*, uint32_t))VF(this, 0xc / 4))(this, 0x17f243b);
    if (p) {
        FUN_01021300();
        ((void(__thiscall*)(void*))VF(p, 0x4c / 4))(p);
    }

    const wchar_t* nm;
    switch (mIb1c) {
    case 1:  nm = g_01565b2c; break;
    case 2:  nm = g_01565b40; break;
    default: nm = g_01565b54; break;
    }

    if (d)
        ((void(__thiscall*)(void*, float, int))VF(&mpVtbl034, 0xc4 / 4))(&mpVtbl034, 0.0f, 0);

    typedef void* (__thiscall *Slot2CFn)(void*, const cSPVector3*, float, float, void*, void*, int, uint32_t);
    void* r = ((Slot2CFn)VF(&mpVtbl034, 0x2c / 4))(
        &mpVtbl034, a, b, c, &mU4EC, &mpVtbl108, (mUbc8 == 1) ? 1 : 0, mUd24);

    void* r2 = FUN_00b3d290((void*)nm, r);
    ((RcObj*)r2)->FUN_00ac65d0();

    mUbc8 = 0;
    mTimerBA0.FUN_00bc3110();
}

// @ 0x00ca8340
bool Simulator::cVehicle::FUN_00ca8340(cCity* city)
{
    typedef cSPVector3* (__thiscall *GetPosFn)(void*);

    cPlanetModel* pm = FUN_00b3d350();
    if (!pm)
        return false;

    cSPVector3* pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
    uint8_t* cont = (uint8_t*)pm->FUN_00b88590(pos);

    int mode = mIb1c;
    if (mode == 0) {
        if (cont[pm->mI64] == 0) {
            FUN_00ca72a0();
            pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
            cont = (uint8_t*)pm->FUN_00b88590(pos);
        }
        return cont == city->FUN_00bd8210();
    }
    if (mode == 1) {
        if (cont[pm->mI64] != 0) {
            FUN_00ca72a0();
            pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
            cont = (uint8_t*)pm->FUN_00b88590(pos);
        }
        cSPVector3* cp = city->FUN_00fa0e00();
        if (cp->x == g_01699b08 && cp->y == g_01699b0c && cp->z == g_01699b10)
            return false;
        if (FUN_00b5b800() != &g_01654c04)
            return cont == pm->FUN_00b88590(city->FUN_00fa0e00());
        return true;
    }
    if (mode == 2)
        return true;
    return false;
}