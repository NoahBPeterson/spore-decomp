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
#define VFN(o)        (*(void***)(o))

extern "C" void operator_delete_array(void*);   // 0x00f47380

// ---------------------------------------------------------------------------
// The cSPUIPosse shape (as seen by the posse-item code above): an 8-byte
// ref-pair vector at +0xa4, the ref list at +0x0c and the UI layout at +0x1bc.
// ---------------------------------------------------------------------------
struct cRefPair16;
struct cVec8_16;

class cSPUIPosse16 {
public:
    u8           pad00[0x0c];                             // +0x00 .. +0x0b
    cRefPair16*  mpRefsBegin;                             // +0x0c
    cRefPair16*  mpRefsEnd;                               // +0x10
    u8           pad14[0x90];                             // +0x14 .. +0xa3
    cRefPair16*  mpItemsBegin;                            // +0xa4
    cRefPair16*  mpItemsEnd;                              // +0xa8
    u8           padAc[0x110];                            // +0xac .. +0x1bb
    void*        mpLayoutPtr;                             // +0x1bc (address only)
    u8           pad1c0[0x14];                            // +0x1c0 .. +0x1d3
    u8           mDirty1d4;                               // +0x1d4
    u8           pad1d5[0x0b];                            // +0x1d5 .. +0x1df
    int          mField1e0;                               // +0x1e0
    u8           pad1e4[4];                               // +0x1e4 .. +0x1e7
    float        mField1e8;                               // +0x1e8
    u8           pad1ec[0x0c];                            // +0x1ec .. +0x1f7

    void*        find_item(u32 id);                       // 0x00e24ba0
    void         push_back(cRefPair16* value);            // 0x00e280e0
    char         AddItem(void* item);                     // 0x00e282d0
    char         RemoveItem(void* item, char removeRefs); // 0x00e285a0
    float*       FUN_00e286c0(float* out, u32 count, int param_4, float param_5);
    void         FUN_00e22b50(int flag);                  // 0x00e22b50
};

// 8-byte element of the +0xa4 vector: two ref-counted pointers.
struct cRefPair16 {
    void* mpFirst;                                        // +0x00
    void* mpSecond;                                       // +0x04
};

// Stack pair staged for the +0xa4 vector push (same shape).
struct cPair {
    void* mpFirst;                                        // +0x00
    void* mpSecond;                                       // +0x04
};

// Vector of 8-byte ref pairs (+0xa4 in cSPUIPosse).
struct cVec8_16 {
    cRefPair16* mpBegin;                                  // +0x00
    cRefPair16* mpEnd;                                    // +0x04
    cRefPair16* mpCap;                                    // +0x08

    void resize(u32 n);                                   // 0x00e28250
    void insert(cRefPair16* pos, cRefPair16* value);      // 0x00e26c80
    void eraseAt(cRefPair16* pos);                        // 0x00e26bf0
};

extern "C" {
    void  FUN_00e28130(cRefPair16* first, cRefPair16* last, void* fn);  // 0x00e28130
    void* FUN_00bf3420(void* vec, void* pos, int b);                    // 0x00bf3420
    void  FUN_00e26c40(cVec8_16* vec, void** value);                    // 0x00e26c40
    void  FUN_00e26bf0(cVec8_16* vec, void* pos);                       // 0x00e26bf0
    u32   FUN_00e23250();                                               // 0x00e23250
    void  FUN_00e26680_this(cSPUIPosse16* self);                        // 0x00e26680
    u8    FUN_00cca090_this(void* self);                                // 0x00cca090
    void* FUN_00cd40b0();                                               // 0x00cd40b0
    void  FUN_00cca0a0(void* self);                                     // 0x00cca0a0
    void  FUN_00e22760();                                               // 0x00e22760
    void  FUN_00e23c00();                                               // 0x00e23c00
    void* FUN_00b5b800();                                               // 0x00b5b800 GetCurrentGameMode
    void* FUN_00e27060(void* a, void* b, void* c, void* d);             // 0x00e27060
}

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

// ---------------------------------------------------------------------------
// cSPUIPosse::AddItem / RemoveItem and the three-float enqueue routine.
//
// AddItem walks the posse window tree, deduplicates the incoming object by its
// COM identity (vtable +0xc4), pushes the {item, identity} pair onto the posse
// item vector, rebuilds the bar sort, and finally re-sorts the item vector.
// ---------------------------------------------------------------------------

// The posse item that lives at +0x7c of the incoming object: a UI layout whose
// FindWindowByID is vtable-free in the original (a plain member function at
// 0x008105b0 taking (id, recurse) with `this` = the layout address).
struct cLayoutView {
    void* FindWindowByID(u32 id, int recurse);            // 0x008105b0
};

// The incoming object as seen here: a COM-ish pointer (vtable slots) plus the
// embedded layout at +0x7c.
struct cItemView {
    u8* pad00;                                            // opaque
};

// Stack pair used to stage the {item, identity} entry.
struct cPair;

extern "C" {
    void  FUN_00e280e0(cVec8_16* vec, cPair* src);        // 0x00e280e0
    void  FUN_00e26de0(void* first, void* last, void* fn);  // 0x00e26de0
}
// Window-object slots reached through the layout.
#define VT(w, off)  ((void (__thiscall*)(void*))VFN(w)[(off) / 4])

// @ 0x00e282d0  SP::cSPUIPosse::AddItem
char cSPUIPosse16::AddItem(void* item)
{
    if (item == 0)
        return 0;

    cLayoutView* layout = (cLayoutView*)((char*)this + 0x1bc);
    if (layout->FindWindowByID(0x3d98298, 1) == 0)
        return 0;

    void* idObj = ((void* (__thiscall*)(void*))VFN(item)[0xc4 / 4])(item);
    if (find_item((u32)idObj) != mpItemsEnd) {
        idObj = ((void* (__thiscall*)(void*))VFN(item)[0xc4 / 4])(item);
        if (idObj != 0)
            return 1;
    }

    cLayoutView* iLayout = (cLayoutView*)((char*)item + 0x7c);
    if (iLayout->FindWindowByID(0x3d98299, 1) == 0)
        ((void (__thiscall*)(void*, void*))VFN(item)[0xc8 / 4])(item, this);

    void* w1 = iLayout->FindWindowByID(0x3d98299, 1);
    if (w1 == 0)
        return 0;

    void* w2 = layout->FindWindowByID(0x3d98298, 1);
    void* sub = ((void* (__thiscall*)(void*, u32, int))VFN(w2)[0xf0 / 4])(w2, 0x3d982ff, 1);
    ((void (__thiscall*)(void*, void*))VFN(sub)[0xd8 / 4])(sub, w1);

    ((void (__thiscall*)(void*))VFN(item)[0x00 / 4])(item);

    idObj = ((void* (__thiscall*)(void*))VFN(item)[0xc4 / 4])(item);
    if (idObj != 0)
        ((void (__thiscall*)(void*))VFN(idObj)[0x00 / 4])(idObj);

    cPair tmp;
    tmp.mpFirst = idObj;
    if (idObj != 0)
        ((void (__thiscall*)(void*))VFN(idObj)[0x00 / 4])(idObj);
    tmp.mpSecond = item;
    ((void (__thiscall*)(void*))VFN(item)[0x00 / 4])(item);

    ((void (__thiscall*)(void*, cPair*))FUN_00e280e0)((void*)((char*)this + 0xa4), &tmp);

    if (tmp.mpSecond != 0)
        ((void (__thiscall*)(void*))VFN(tmp.mpSecond)[0x04 / 4])(tmp.mpSecond);
    if (tmp.mpFirst != 0)
        ((void (__thiscall*)(void*))VFN(tmp.mpFirst)[0x04 / 4])(tmp.mpFirst);
    if (idObj != 0)
        ((void (__thiscall*)(void*))VFN(idObj)[0x04 / 4])(idObj);

    ((void (__thiscall*)(void*))VFN(item)[0x04 / 4])(item);

    {
        cVec8_16* vec = (cVec8_16*)((char*)this + 0xa4);
        FUN_00e28130(vec->mpBegin, vec->mpEnd, (void*)0x00e23c00);
    }
    mDirty1d4 = 1;

    ((void (__thiscall*)(void*, int))VFN(item)[0xb8 / 4])(item, 1);

    if (FUN_00b5b800() == (void*)0x01654c02) {
        void* strat = FUN_00cd40b0();
        if (((void* (__thiscall*)(void*))VFN(strat)[0x6c / 4])(strat) != 0) {
            void* strat2 = FUN_00cd40b0();
            void* d = ((void* (__thiscall*)(void*))VFN(strat2)[0x6c / 4])(strat2);
            ((void (__thiscall*)(void*))FUN_00cca0a0)(d);
            goto done;
        }
    }

    {
        void* w3 = layout->FindWindowByID(0x3dae412, 1);
        if (w3 == 0)
            goto done;
        void* w4 = ((void* (__thiscall*)(void*, u32))VFN(w3)[0x0c / 4])(w3, 0x8ed27e7a);
        if (w4 == 0)
            goto done;

        char cond = 0;
        int a4;
        if (FUN_00b5b800() == (void*)0x01654c02) {
            void* strat = FUN_00cd40b0();
            if (((void* (__thiscall*)(void*))VFN(strat)[0x6c / 4])(strat) != 0) {
                void* strat2 = FUN_00cd40b0();
                void* d = ((void* (__thiscall*)(void*))VFN(strat2)[0x6c / 4])(strat2);
                cond = (char)((u8 (__thiscall*)(void*))FUN_00cca090_this)(d);            }
        } else {
            int e = (int)(mpItemsEnd - mpItemsBegin);
            cond = (((u32 (__thiscall*)(void*))FUN_00e23250)(this) == (u32)e) ? 1 : 0;
        }

        if (cond) {
            if ((((u32 (__thiscall*)(void*))VFN(w4)[0x20 / 4])(w4) & 4) != 0)
                goto done;
            a4 = 1;
        } else {
            if ((((u32 (__thiscall*)(void*))VFN(w4)[0x20 / 4])(w4) & 4) == 0)
                goto done;
            a4 = 0;
        }
        ((void (__thiscall*)(void*, int, int))VFN(w4)[0x28 / 4])(w4, 4, a4);
        ((void (__thiscall*)(void*))FUN_00e26680_this)(this);
    }

done:
    ((void (__thiscall*)(void*))VFN(item)[0x00 / 4])(item);
    {
        void* stage = item;
        ((void (__thiscall*)(void*, void**))FUN_00e26c40)((void*)((char*)this + 0x0c), &stage);
    }
    if (item != 0)
        ((void (__thiscall*)(void*))VFN(item)[0x04 / 4])(item);
    FUN_00e26de0(mpItemsBegin, mpItemsEnd, (void*)0x00e22760);
    return 1;
}

// @ 0x00e285a0  SP::cSPUIPosse::RemoveItem
char cSPUIPosse16::RemoveItem(void* item, char removeRefs)
{
    if (item == 0)
        return 0;

    void* idObj = ((void* (__thiscall*)(void*))VFN(item)[0xc4 / 4])(item);
    cRefPair16* found = (cRefPair16*)find_item((u32)idObj);
    if (found != mpItemsEnd) {
        void* pSecond = found->mpSecond;
        if (removeRefs != 0)
            ((void (__thiscall*)(void*))VFN(pSecond)[0xcc / 4])(pSecond);

        // Remove every ref-list entry that points at the pair's second object.
        {
            u32* it = (u32*)mpRefsBegin;
            u32* end = (u32*)mpRefsEnd;
            while (it != end && *it != (u32)pSecond)
                ++it;
            if (it != end) {
                ((void (__thiscall*)(void*, void*))FUN_00bf3420)((void*)((char*)this + 0x0c), it);
                FUN_00e26de0(mpRefsBegin, mpRefsEnd, (void*)0x00e22760);
            }
        }

        ((void (__thiscall*)(void*, void*))FUN_00e26bf0)((void*)((char*)this + 0xa4), (void*)found);
        FUN_00e28130(mpItemsBegin, mpItemsEnd, (void*)0x00e23c00);
        mDirty1d4 = 1;
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Local eastl-style vector with a 32-element inline buffer, used to stage the
// posse item refs while the +0xa4 vector is resized.
// ---------------------------------------------------------------------------
struct SavedVec8 {
    cRefPair16* mpBegin;                                  // +0x00
    cRefPair16* mpEnd;                                    // +0x04
    cRefPair16* mpCapacity;                               // +0x08
    void*       mpUnused0c;                               // +0x0c
    void*       mpPool;                                   // +0x10
    u8          pad14[4];                                 // +0x14
    cRefPair16  mBuffer[32];                              // +0x18

    void insertRange(cRefPair16* first, cRefPair16* last, void* extra); // 0x00e27170
    void FUN_00e23870(void* first, void* last);                          // 0x00e23870
};

// SSE min/max clamp helper (the retail shape uses maxss/minss with the
// operands spilled to plain stack slots).
inline float Clamp16(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// @ 0x00e286c0  enqueue three-float record
float* cSPUIPosse16::FUN_00e286c0(float* out, u32 count, int param_4, float param_5)
{
    if (count == 0 || mpItemsBegin == mpItemsEnd) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 0.0f;
        return out;
    }

    int   old1e0 = mField1e0;
    float old1e8 = mField1e8;

    SavedVec8 saved;
    saved.mpBegin = saved.mBuffer;
    saved.mpEnd = saved.mBuffer;
    saved.mpCapacity = saved.mBuffer + 32;
    saved.mpPool = saved.mBuffer;
    saved.insertRange(mpItemsBegin, mpItemsEnd, (void*)old1e0);

    mField1e0 = param_4;
    if (param_5 > 0.0f) {
        float x = param_5;
        float lo = 0.25f;
        float hi = 1.0f;
        mField1e8 = Clamp16(x, lo, hi);
    }

    cVec8_16* items = (cVec8_16*)((char*)this + 0xa4);
    if ((u32)(mpItemsEnd - mpItemsBegin) > count) {
        items->resize(count);
    } else {
        while ((u32)(mpItemsEnd - mpItemsBegin) < count) {
            cRefPair16* last = mpItemsEnd - 1;
            if (mpItemsEnd < items->mpCap) {
                cRefPair16* dst = mpItemsEnd;
                items->mpEnd = dst + 1;
                if (dst != 0) {
                    dst->mpFirst = last->mpFirst;
                    if (dst->mpFirst != 0)
                        ((void (__thiscall*)(void*))VFN(dst->mpFirst)[0]) (dst->mpFirst);
                    dst->mpSecond = last->mpSecond;
                    if (dst->mpSecond != 0)
                        ((void (__thiscall*)(void*))VFN(dst->mpSecond)[0]) (dst->mpSecond);
                }
            } else {
                items->insert(mpItemsEnd, last);
            }
        }
    }

    mDirty1d4 = 1;
    FUN_00e22b50(1);

    float vec4[4];
    ((void (__thiscall*)(void*, float*))VFN(this)[0x9c / 4])(this, vec4);

    mField1e8 = old1e8;
    mField1e0 = old1e0;
    ((cSizedVec8*)items)->FUN_00e28660(&saved);

    mDirty1d4 = 1;
    FUN_00e22b50(0);

    out[0] = vec4[0];
    out[1] = vec4[1];
    out[2] = vec4[2];
    out[3] = vec4[3];

    saved.FUN_00e23870(saved.mpBegin, saved.mpEnd);
    if (saved.mpBegin != 0 && saved.mpBegin != (cRefPair16*)saved.mpPool)
        operator_delete_array(saved.mpBegin);
    return out;
}