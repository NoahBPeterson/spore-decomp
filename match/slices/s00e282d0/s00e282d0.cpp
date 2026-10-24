// Slice s00e282d0 -- Simulator UI-posse / property-adapter helpers around
// 0x00e282d0..0x00e28f2e: cSPUIPosse::AddItem/RemoveItem, the fixed-vector
// insert/erase helpers, a deleting destructor, and the EA::Variant property
// adapters that read a typed value out of a variant slot and forward it to the
// UI style setters.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell/Simulator TU).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Raw virtual-call / field helpers.
// ---------------------------------------------------------------------------
#define VS(o, off)             (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)         ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FU16(p, off)  (*(u16*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))

extern "C" void operator_delete_array(void*);   // 0x00f47380

// ---------------------------------------------------------------------------
// EA::Variant-ish property slot.  +0x10 flag byte (0x30 mask), +0x12 kind.
// ---------------------------------------------------------------------------
struct Variant {
    u32  mValue0;                    // +0x00 (inline value or pointer)
    u8   mPad_04[0xc];
    u8   mFlags;                     // +0x10
    u8   mPad_11;
    u16  mKind;                      // +0x12

    void SetInt(u32* v);             // 0x00427fd0
    void SetFloat(float* v);         // 0x00428060
};

// Vtables (address-only references).
extern void* g_vtbl_cPropertyDoc_14811f8;   // 0x014811f8
extern void* g_vtbl_IEventModifier_13ef094; // 0x013ef094

// ---------------------------------------------------------------------------
// The reference-counted UI object built by 0x00e28a10 (a 5-dword payload plus
// three ref-counted members at +0x8 / +0xc / +0x10).
// ---------------------------------------------------------------------------
struct cPropertyDoc {
    void* mVtbl;                     // +0x00
    u32   mField4;                   // +0x04
    void* mRef8;                     // +0x08  ref-counted (release slot +8)
    void* mRefc;                     // +0x0c  ref-counted (release slot +4)
    void* mRef10;                    // +0x10  owned, deleted via slot +0
    u32   mData[5];                  // +0x14  copied from the payload argument
    float mFloat28;                  // +0x28
    u32   mField2c;                  // +0x2c
    u32   mField30;                  // +0x30
    int   mField34;                  // +0x34

    cPropertyDoc* Init(void* a0, u32* a1);   // 0x00e28a10
    void          DtorBody();                // 0x00e28a80
    void*         DeletingDtor(u8 flags);    // 0x00e28ad0
};

// @ 0x00e28a10
cPropertyDoc* cPropertyDoc::Init(void* a0, u32* a1)
{
    mField4 = 0;
    mVtbl = &g_vtbl_cPropertyDoc_14811f8;
    mRef8 = a0;
    if (a0 != 0)
        VC0(void, a0, 4);
    mRefc = 0;
    mRef10 = 0;
    mField2c = 0;
    mField30 = 0;
    mFloat28 = 0.0f;
    mField34 = -1;
    mData[0] = a1[0];
    mData[1] = a1[1];
    mData[2] = a1[2];
    mData[3] = a1[3];
    mData[4] = a1[4];
    return this;
}

// @ 0x00e28a80
void cPropertyDoc::DtorBody()
{
    if (mRef10 != 0) {
        VC1(void, mRef10, 0, int, 1);
        mRef10 = 0;
    }

    void* p = mRef8;
    if (p != 0) {
        mRef8 = 0;
        VC0(void, p, 8);
    }

    void* q = mRefc;
    if (q != 0) {
        mRefc = 0;
        VC0(void, q, 4);
    }
}

// @ 0x00e28ad0
void* cPropertyDoc::DeletingDtor(u8 flags)
{
    *(void* volatile*)this = &g_vtbl_cPropertyDoc_14811f8;
    void* q = *(void* volatile*)&mRefc;
    if (q != 0)
        VC0(void, q, 4);
    if (mRef8 != 0)
        VC0(void, mRef8, 8);
    mVtbl = &g_vtbl_IEventModifier_13ef094;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------
// Weighted index selection: given a weight array, a unit-scale %, an index
// out-parameter, a remaining-count out-parameter and a residual out-parameter.
// ---------------------------------------------------------------------------
extern float g_real4294967296_13f4fd0;     // 0x013f4fd0 (4294967296.0f)

// @ 0x00e28920
void FUN_00e28920(float param_1, u32* param_2, int* param_3, u32* param_4, float* param_5)
{
    u32 uVar4 = param_2[4] + param_2[3] + param_2[2] + param_2[1] + param_2[0];
    float fVar1 = (float)uVar4;
    float inv = 1.0f / fVar1;

    *param_5 = param_1;

    u32 uVar3 = (u32)(fVar1 * param_1);
    if (fVar1 * param_1 < (float)(int)uVar3)
        uVar3 = uVar3 - 1;
    *param_4 = uVar3;
    if (uVar3 == uVar4)
        *param_4 = uVar3 - 1;

    *param_3 = 0;
    if (param_2[0] <= *param_4) {
        do {
            *param_4 = *param_4 - param_2[*param_3];
            float fVar2 = (float)param_2[*param_3];
            *param_5 = *param_5 - fVar2 * inv;
            *param_3 = *param_3 + 1;
        } while (param_2[*param_3] <= *param_4);
    }

    float fVar3 = (float)param_2[*param_3];
    *param_5 = *param_5 / (fVar3 * inv);
}

// ---------------------------------------------------------------------------
// The EA::Variant property adapters.  Each one resolves one or more variant
// slots to a typed pointer and forwards the value to a UI style setter.
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

extern int   g_variantDefaultInt_15d1164;     // 0x015d1164
extern float g_variantDefaultFloat_15d1168;   // 0x015d1168

extern "C" void* FUN_006bb640();                       // 0x006bb640
extern "C" void* FUN_006bb600();                       // 0x006bb600
extern "C" u32   ColorRGBToU32(Vec3* v);               // 0x00458a40
extern "C" u32   __stdcall Color_Lerp(u32 a, u32 b, float t);   // 0x007f5eb0

// The style setters invoked by the property adapters are thiscall methods of
// the bound UI object (the adapters' first argument), so `ecx` stays live and
// the adapter's guard test keeps the object in a register.
struct cUIPropTarget {
    void  FUN_0082e340(float v, u32 target);             // 0x0082e340
    void  FUN_0082e380(const void* v, u32 target, int n);  // 0x0082e380
    float FUN_0082e360(u32 v);                           // 0x0082e360
    Vec3* FUN_0082e3f0(u32 v);                           // 0x0082e3f0
};

// @ 0x00e28b20
void FUN_00e28b20(void* param_1, Variant* param_2, Variant* param_3, Variant* param_4, float param_5)
{
    if (param_1 == 0)
        return;

    u32 value2;
    {
        void* p;
        u16 k = param_2->mKind;
        if (k == 0xa || k == 0x10) {
            if ((param_2->mFlags & 0x30) != 0)
                p = *(void**)param_2;
            else
                p = (void*)((k != 0) ? (u32)param_2 : 0);
        } else {
            p = (void*)&g_variantDefaultInt_15d1164;
        }
        value2 = *(u32*)p;
    }

    float f3;
    {
        u16 k = param_3->mKind;
        float* p;
        if (k == 0xd || k == 0x10) {
            if ((param_3->mFlags & 0x30) != 0)
                p = *(float**)param_3;
            else
                p = (float*)((k != 0) ? (u32)param_3 : 0);
        } else {
            p = (float*)&g_variantDefaultFloat_15d1168;
        }
        f3 = *p;
    }

    float f4;
    {
        u16 k = param_4->mKind;
        float* p;
        if (k == 0xd || k == 0x10) {
            if ((param_4->mFlags & 0x30) != 0)
                p = *(float**)param_4;
            else
                p = (float*)((k != 0) ? (u32)param_4 : 0);
        } else {
            p = (float*)&g_variantDefaultFloat_15d1168;
        }
        f4 = *p;
    }

    ((cUIPropTarget*)param_1)->FUN_0082e340((f4 - f3) * param_5 + f3, value2);
}

// @ 0x00e28be0
void FUN_00e28be0(void* param_1, Variant* param_2, Variant* param_3)
{
    if (param_1 == 0)
        return;

    void* p;
    u16 k = param_2->mKind;
    if (k == 0xa || k == 0x10) {
        if ((param_2->mFlags & 0x30) != 0)
            p = *(void**)param_2;
        else
            p = (void*)((k != 0) ? (u32)param_2 : 0);
    } else {
        p = (void*)&g_variantDefaultInt_15d1164;
    }
    u32 value = *(u32*)p;

    float f = ((cUIPropTarget*)param_1)->FUN_0082e360(value);
    param_3->SetFloat(&f);
}

// @ 0x00e28c40
void FUN_00e28c40(void* param_1, Variant* param_2, Variant* param_3, Variant* param_4, float param_5)
{
    if (param_1 == 0)
        return;

    u32 value2;
    {
        void* p;
        u16 k = param_2->mKind;
        if (k == 0xa || k == 0x10) {
            if ((param_2->mFlags & 0x30) != 0)
                p = *(void**)param_2;
            else
                p = (void*)((k != 0) ? (u32)param_2 : 0);
        } else {
            p = (void*)&g_variantDefaultInt_15d1164;
        }
        value2 = *(u32*)p;
    }

    u32 value3;
    {
        void* p;
        u16 k = param_3->mKind;
        if (k == 0xa || k == 0x10) {
            if ((param_3->mFlags & 0x30) != 0)
                p = *(void**)param_3;
            else
                p = (void*)((k != 0) ? (u32)param_3 : 0);
        } else {
            p = (void*)&g_variantDefaultInt_15d1164;
        }
        value3 = *(u32*)p;
    }

    u32 value4;
    {
        void* p;
        u16 k = param_4->mKind;
        if (k == 0xa || k == 0x10) {
            if ((param_4->mFlags & 0x30) != 0)
                p = *(void**)param_4;
            else
                p = (void*)((k != 0) ? (u32)param_4 : 0);
        } else {
            p = (void*)&g_variantDefaultInt_15d1164;
        }
        value4 = *(u32*)p;
    }

    u32 c = Color_Lerp(value3, value4, param_5);
    Vec3 rgb;
    rgb.x = (float)((c >> 0x10) & 0xff) * 0.003921569f;
    rgb.y = (float)((c >> 8) & 0xff) * 0.003921569f;
    rgb.z = (float)(c & 0xff) * 0.003921569f;
    ((cUIPropTarget*)param_1)->FUN_0082e380(&rgb, value2, 3);
}

// @ 0x00e28d60
void FUN_00e28d60(void* param_1, Variant* param_2, Variant* param_3)
{
    if (param_1 == 0)
        return;

    void* p;
    u16 k = param_2->mKind;
    if (k == 0xa || k == 0x10) {
        if ((param_2->mFlags & 0x30) != 0)
            p = *(void**)param_2;
        else
            p = (void*)((k != 0) ? (u32)param_2 : 0);
    } else {
        p = (void*)&g_variantDefaultInt_15d1164;
    }
    u32 value = *(u32*)p;

    Vec3* pv = ((cUIPropTarget*)param_1)->FUN_0082e3f0(value);
    Vec3 rgb;
    rgb.x = pv->x;
    rgb.y = pv->y;
    rgb.z = pv->z;
    u32 c = ColorRGBToU32(&rgb);
    param_3->SetInt(&c);
}

// ---------------------------------------------------------------------------
// cPropertyBinding (0x00e28df0 / 0x00e28e70): refreshes a cached int triple /
// float triple from a variant slot, reporting whether it changed.
// ---------------------------------------------------------------------------
struct Triple { int x, y, z; };

struct cPropertyBinding {
    void*  mVtbl;                        // +0x00
    u32    mField4;                      // +0x04
    u32    mField8;                      // +0x08
    union { int i[3]; float f[3]; Triple t; } mState;   // +0x0c

    bool RefreshInt(Variant* param_2);        // 0x00e28df0
    bool RefreshFloat(Variant* param_2);      // 0x00e28e70
};

// @ 0x00e28df0
bool cPropertyBinding::RefreshInt(Variant* param_2)
{
    if (VC2(char, param_2, 0x24, u32, mField4, void**, (void**)&param_2)) {
        int* p;
        u16 k = param_2->mKind;
        if (k == 0x20 || k == 0x10) {
            if ((param_2->mFlags & 0x30) != 0)
                p = *(int**)param_2;
            else
                p = (int*)((k != 0) ? (u32)param_2 : 0);
        } else {
            p = (int*)FUN_006bb640();
        }

        int a = p[0], b = p[1], c = p[2];
        if (mState.i[0] != a || mState.i[1] != b || mState.i[2] != c) {
            *(volatile int*)&mState.i[0] = a;
            *(volatile int*)&mState.i[1] = b;
            *(volatile int*)&mState.i[2] = c;
            return true;
        }
    }
    return false;
}

// @ 0x00e28e70
bool cPropertyBinding::RefreshFloat(Variant* param_2)
{
    if (VC2(char, param_2, 0x24, u32, mField4, void**, (void**)&param_2)) {
        float* p;
        u16 k = param_2->mKind;
        if (k == 0x32 || k == 0x10) {
            if ((param_2->mFlags & 0x30) != 0)
                p = *(float**)param_2;
            else
                p = (float*)((k != 0) ? (u32)param_2 : 0);
        } else {
            p = (float*)FUN_006bb600();
        }

        float a = p[0], b = p[1], c = p[2];
        if (mState.f[0] != a || mState.f[1] != b || mState.f[2] != c) {
            mState.f[0] = a;
            mState.f[1] = b;
            mState.f[2] = c;
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// Fixed-stride (8 byte element) vector: insert the element block of another
// vector at the end of this one.  The element payload is copied by the helper
// calls, so the 8-byte element is undone by subtracting count*8 from end.
// ---------------------------------------------------------------------------
struct cSizedVec8 {
    int mBegin;                       // +0x00
    int mEnd;                         // +0x04

    void* FUN_00e23870(void* a, int b);          // 0x00e23870
    void  FUN_00e27170(int a, int b, void* c);   // 0x00e27170
    void* FUN_00e28660(void* param_2);           // 0x00e28660
};

extern "C" void* FUN_00e24290(int a, int b, int c);   // 0x00e24290

// @ 0x00e28660
void* cSizedVec8::FUN_00e28660(void* param_2)
{
    if (this != (cSizedVec8*)param_2) {
        int iVar1 = mBegin;
        int iVar2 = mEnd;
        void* u = FUN_00e24290(iVar2, iVar2, iVar1);
        FUN_00e23870(u, mEnd);
        mEnd = mEnd + ((iVar2 - iVar1) >> 3) * -8;
        FUN_00e27170(*(int*)param_2, *((int*)param_2 + 1), param_2);
    }
    return this;
}