// Slice s00ecbb10 -- Sporepedia card data / asset helpers.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------
// Out-of-line callees.
// ---------------------------------------------------------------------------
void  __fastcall FUN_00641810(void* self);          // base reset/notify (ecx=this)
void  __fastcall FUN_005ed650(void* self);          // cSPPaletteItemRollover::Destroy
void* __fastcall FUN_0080ba10(void* self);          // returns new object in eax
void* __cdecl    FUN_00f473a0(unsigned size, const char* name, int a, int b, int c, int d);

struct VObj {
    virtual void slot0(int);
    virtual void slot1();
};

struct VObj0 {
    virtual void vt0();
};

// Open container with a 4-byte gap at +8: further members spill
// (pun: same layout, different member granularity).
struct Gap24 { char a[8]; int x; };
struct Amb {
    virtual void slot0(int);
    virtual void slot1();
    Gap24 g;
    int   y;
};

struct S80 {
    char pad0[0x80];
    int  m80;
    int  m84;
};

struct S920 {
    int   m00, m04, m08;
    union {
        int   m0c;
        struct { short m0c_lo, m0e; };
    };
    int   m10;
    float m14, m18;
    int   m1c, m20, m24;
};
struct S_c8 {
    char  pad0[0xc8];
    VObj* mC8;
};

// @ 0x00ecc530
void __fastcall FUN_00ecc530(S80* s)
{
    if (s->m80 == s->m84)
        FUN_00641810(s);
}

// ---------------------------------------------------------------------------
// Vtables / globals used by the container class.
// ---------------------------------------------------------------------------
extern void* vtbl_ecb_b0;    // 0x14893b0
extern void* vtbl_ecb_9c;    // 0x148939c
extern void* vtbl_ecb_8c;    // 0x148938c
extern void* vtbl_ec6_48;    // 0x1462748
extern void* vtbl_ec6_38;    // 0x1462738

void  __fastcall FUN_00642190(void* self);
void  __fastcall FUN_00641e10(void* self);
struct TC_93db80 { void Destruct(int unlink); };
struct TC_93dd80 { unsigned char Construct(unsigned short a, unsigned short b, const void* c, unsigned d, unsigned e); };
void* __fastcall Property_GetBool_0(void* prop);
void* __fastcall Property_GetInt_0(void* prop);
void  __fastcall FUN_00eed920(void* v);
void* __cdecl    FUN_0067de30();
void* __cdecl    FUN_006a0ae0(void* a, void* b, void* c);
void* __cdecl    FUN_00806230(void* a, void* b, int c, int d, int e);
void  __cdecl    FUN_00da1f10(int a, int b, int c);
struct TC_da1f10 { void FUN(int a, int b, int c); };
void  __cdecl    operator_delete(void* p);
void* __cdecl    FUN_00645ed0(void* retbuf, void* key);
// Member-function wrappers so the call is emitted with `this` in ecx and
// the remaining argument on the stack (ret 4 shape).
struct TC_680 { void* FUN_00ecc680(void* src); };
struct TC_780 { void* FUN_00ecc780(void* src); };

extern unsigned short eastl_gEmptyString16[];
extern unsigned short eastl_gEmptyString16_end[];

struct EastlStr16 {
    unsigned short* begin;
    unsigned short* end;
    unsigned short* cap;
};

struct CCard {
    char pad0[0x78];
    char m78;
    char pad78[3];
    int  m7c;
    EastlStr16 s80;   // +0x80
};

struct TC_620 { void* FUN_00ecc620(int flags); };

// @ 0x00ecc620
void* TC_620::FUN_00ecc620(int flags)
{
    CCard* s = (CCard*)this;
    *(void**)s = &vtbl_ecb_b0;
    *(void**)((char*)s + 0x10) = &vtbl_ecb_9c;
    *(void**)((char*)s + 0x14) = &vtbl_ecb_8c;
    unsigned short* b = s->s80.begin;
    if ((((int)((char*)s->s80.cap - (char*)b)) & -2) > 2 && b != 0) {
        operator_delete(b);
    }
    FUN_00642190(s);
    if (flags & 1) {
        operator_delete(s);
    }
    return s;
}

// @ 0x00ecc680
void* TC_680::FUN_00ecc680(void* src)
{
    void* self = this;
    char* s = (char*)self;
    char* d = (char*)src;
    *(void**)s = (void*)0x1403758;
    *(int*)(s + 4) = *(int*)(d + 4);
    *(int*)(s + 8) = *(int*)(d + 8);
    *(int*)(s + 0xc) = *(int*)(d + 0xc);
    *(void**)(s + 0x10) = (void*)0x13f1ab0;
    *(void**)(s + 0x14) = (void*)0x13ec458;
    *(int*)(s + 0x18) = 0;
    *(void**)s = (void*)0x13ff648;
    *(void**)(s + 0x10) = (void*)0x1462748;
    *(void**)(s + 0x14) = (void*)0x1462738;
    VObj0* p;
    p = *(VObj0**)(d + 0x1c);
    *(void**)(s + 0x1c) = p;
    if (p) p->vt0();
    VObj0* q;
    q = *(VObj0**)(d + 0x20);
    *(void**)(s + 0x20) = q;
    if (q) q->vt0();
    *(char*)(s + 0x24) = *(char*)(d + 0x24);
    *(char*)(s + 0x25) = *(char*)(d + 0x25);
    *(char*)(s + 0x26) = *(char*)(d + 0x26);
    *(int*)(s + 0x28) = *(int*)(d + 0x28);
    *(int*)(s + 0x2c) = *(int*)(d + 0x2c);
    *(int*)(s + 0x30) = *(int*)(d + 0x30);
    *(int*)(s + 0x34) = *(int*)(d + 0x34);
    *(int*)(s + 0x38) = *(int*)(d + 0x38);
    VObj0* r;
    r = *(VObj0**)(d + 0x3c);
    *(void**)(s + 0x3c) = r;
    if (r) r->vt0();
    char* v = s + 0x40;
    char* e = v + 0x18;
    *(void**)(v + 0x10) = e;
    *(void**)(v + 4) = e;
    *(void**)v = e;
    e += 0x14;
    *(void**)(v + 8) = e;
    ((TC_da1f10*)(s + 0x40))->FUN(*(int*)(d + 0x40), *(int*)(d + 0x44), (int)d);
    *(int*)(s + 0x6c) = *(int*)(d + 0x6c);
    VObj0* t;
    t = *(VObj0**)(d + 0x70);
    *(void**)(s + 0x70) = t;
    if (t) t->vt0();
    VObj0* u;
    u = *(VObj0**)(d + 0x74);
    *(void**)(s + 0x74) = u;
    if (u) u->vt0();
    return self;
}

// @ 0x00ecc780
void* TC_780::FUN_00ecc780(void* src)
{
    CCard* s = (CCard*)this;
    ((TC_680*)this)->FUN_00ecc680(src);
    s->m78 = 0;
    *(int*)((char*)s + 0x7c) = 0;
    *(void**)s = &vtbl_ecb_b0;
    *(void**)((char*)s + 0x10) = &vtbl_ecb_9c;
    *(void**)((char*)s + 0x14) = &vtbl_ecb_8c;
    s->s80.begin = eastl_gEmptyString16;
    s->s80.end = eastl_gEmptyString16;
    s->s80.cap = eastl_gEmptyString16_end;
    return s;}

struct TC_8b0 { void* FUN_00ecc8b0(unsigned short* str); };

// @ 0x00ecc8b0
void* TC_8b0::FUN_00ecc8b0(unsigned short* str)
{
    char* s = (char*)this;
    if (*(unsigned char*)(s + 0x10) & 4)
        ((TC_93db80*)s)->Destruct(1);
    if (str != 0) {
        unsigned short* q = str;
        unsigned short* base = q + 1;
        short c;
        do { c = (short)*q; q++; } while (c != 0);
        int n = ((int)((char*)q - (char*)base)) >> 1;
        ((TC_93dd80*)s)->Construct(3, 0x18, str, 2, n + 1);
        return s;
    }
    ((TC_93dd80*)s)->Construct(3, 0x20, 0, 2, 1);
    return s;
}

struct Iter { int* node; int pad; };
struct TC_645ed0 { Iter* find(Iter* out, int* key); };

// @ 0x00ecc100
int __cdecl FUN_00ecc100(int key)
{
    Iter it;
    Iter* r = ((TC_645ed0*)0x15abdd4)->find(&it, &key);
    int* node = *(int**)r;
    if (node != *(int**)(*(char**)0x15abdd8 + *(int*)0x15abddc * 4))
        return node[1];
    return 0;
}

// @ 0x00ecc920
void __fastcall FUN_00ecc920(S920* s)
{
    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0c = 0;
    s->m0e = 0;
    s->m10 = 0;
    s->m14 = 0.0f;
    s->m18 = 0.0f;
    s->m1c = 0xfffff;
    s->m20 = -1;
    s->m24 = -1;
}

// @ 0x00ecc840
bool __fastcall FUN_00ecc840(S_c8* s)
{
    void* p = FUN_00f473a0(0x5394, (const char*)0x13f6b3c, 0, 0, 0, 0);
    s->mC8 = (VObj*)(p != 0 ? FUN_0080ba10(p) : 0);
    return 1;
}

// @ 0x00ecc880
bool __fastcall FUN_00ecc880(S_c8* s)
{
    VObj* p = s->mC8;
    if (p != 0) {
        p->slot0(1);
        s->mC8 = 0;
    }
    FUN_005ed650(s);
    return 1;
}

// @ 0x00ecc7d0
void* __cdecl FUN_00ecc7d0(void* a1)
{
    if (a1 != 0) {
        char* o = (char*)a1 + 0x10;
        void** vt = *(void***)o;
        void* tgt = vt[3];
        void* r = (*(void* (__thiscall*)(void*, int))tgt)(o, 0x13d55dc8);
        if (r != 0) {
            void* mem = FUN_00f473a0(0x90, "Sporepedia/AssetData/cSPScenarioCaptainAssetData", 0, 0, 0, 0);
            void* obj = (mem != 0) ? ((TC_780*)mem)->FUN_00ecc780(r) : 0;
            (*(void(__thiscall**)(void*))(*(char**)obj + 0x50))(obj);
            return obj;
        }
    }
    return 0;
}

// @ 0x00ecc550
void __fastcall FUN_00ecc550(void* self)
{
    char* s = (char*)self;
    FUN_00641e10(self);
    char* p = *(char**)(s + 0x20);
    if (p == 0)
        return;
    void** vt = *(void***)p;
    (*(void(__thiscall**)(char*))vt[0])(p);
    int* out = 0;
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int**))(vt + 9))(p, 0xec2942cd, &out);
    if (ok && *(short*)((char*)out + 0x12) == 1) {
        char* b = (char*)Property_GetBool_0(out);
        if (*b) {
            *(unsigned char*)(s + 0x78) = 1;
            void* r = (*(void*(__thiscall*)(char*, char*))(*(char**)s + 0x40))(s, s + 0x80);
            FUN_00eed920(r);
        }
    }
    ok = (*(unsigned char(__thiscall*)(char*, int, int**))(vt + 9))(p, 0x5888ef41, &out);
    if (ok && *(short*)((char*)out + 0x12) == 9) {
        int* v = (int*)Property_GetInt_0(out);
        *(int*)(s + 0x7c) = *v;
    }
    (*(void(__thiscall**)(char*))(*((char**)p) + 1))(p);
}

// ---------------------------------------------------------------------------
// cSPPaletteItemUI::DoMessage dispatch (0x00ecbb10) and the layout
// initialiser that follows it (0x00ecc140).  Vtables are walked through the
// small call-shape typedefs below; every field is a named struct member.
// ---------------------------------------------------------------------------
struct V2  { float x, y; };
struct Key { uint32_t m0, m1, m2; };

// UTFWin::Message members consulted by the handler.
struct Msg {
    uint32_t m00;       // 0x00
    uint32_t m04;       // 0x04
    int      mType;     // 0x08  message type
    union {
        float m0c;      // 0x0c  message payload x  (types 6/8)
        int   m0ci;     // 0x0c  request code         (type 10)
    };
    float    m10;       // 0x10  message payload y
    uint32_t m14;       // 0x14
    union {
        uint32_t mSub;  // 0x18  sub-type / request id
        void*    mObj;  // 0x18  payload window        (type 10)
    };
};

// Object reached through cSPPaletteItemUI::m2c; it owns the anchor object
// (the position/offset layout) at +0x14.
struct PLay {
    uint32_t m00, m04, m08, m0c, m10;
    void*    m14;       // 0x14
};

// Source record passed as Init's first argument; only the two property
// handles are consulted here.
struct PSrc {
    uint32_t m00, m04, m08;
    void*    mKey0c;    // 0x0c
    uint32_t m10;       // 0x10
    void*    mKey14;    // 0x14
};

// cString storage (built / torn down through its own helpers).
struct CStr {
    uint32_t w[9];
    const unsigned short* FUN_006b55c0(int, int);
};

struct TC_layout {                                  // cSPUILayout (ecx)
    unsigned char FUN_008120d0(const Key&, int, unsigned);
    void          FUN_00811ad0(unsigned);
    unsigned char FUN_008121b0(void*, int, unsigned);
    void*         FUN_008105b0(unsigned, int);
};
struct TC_8283a0 { void FUN_008283a0(float, float, float, float); };
struct TC_b474c0 { void* FUN_00b474c0(void* key); };
struct TC_eff600 { void FUN_00eff600(void*); };
struct TC_5c6ca0 { void FUN_005c6ca0(void*, void*, void*, void*); };

// Full cSPPaletteItemUI object.  The IWinProc sub-object starts at +0x0c and
// that is the `this` DoMessage is entered with.
struct PIUI {
    void*    mVtbl;         // 0x00
    void*    m04;           // 0x04
    uint32_t m08;           // 0x08
    void*    mIWinProc;     // 0x0c  IWinProc sub-object (its vtable)
    uint32_t m10;           // 0x10
    uint32_t m14;           // 0x14
    uint32_t m18;           // 0x18
    void*    m1c;           // 0x1c  model object (has a vtable)
    uint32_t m20;           // 0x20
    void*    m24;           // 0x24  AutoRefCount - palette item
    void*    m28;           // 0x28  AutoRefCount - cSPUILayout
    void*    m2c;           // 0x2c  AutoRefCount / PLay*
    Key      mKey30;        // 0x30
    Key      mKey3c;        // 0x3c
    Key      mKey48;        // 0x48
    uint32_t m54;           // 0x54
    V2       m58;           // 0x58
    V2       m60;           // 0x60
    uint8_t  mUseDefaults;  // 0x68  primary key missing -> defaults
    uint8_t  mDragArmed;    // 0x69  position drag started (type 6)
    uint8_t  mDragActive;   // 0x6a  mouse drag in progress (type 6)
    uint8_t  pad6b;         // 0x6b
    float    m6c;           // 0x6c
    float    m70;           // 0x70
    float    m74;           // 0x74
    void FUN_00ecc140(void*, void*, void*, void*);  // layout init
    float FUN_00ecb7a0(float);
    float FUN_00ecb830(float);
};

// DoMessage is dispatched through the IWinProc sub-object, which MSVC places
// 0x0c bytes into the enclosing object; recover the owner from `this`.
static inline PIUI* OwnerOf(void* iwinproc)
{
    return (PIUI*)((char*)iwinproc - 0x0c);
}

static inline void** VTable(void* obj) { return *(void***)obj; }

typedef void*         (__thiscall *VRet0)(void*);
typedef void*         (__thiscall *VRet1p)(void*, void*);
typedef void          (__thiscall *VCall0v)(void*);
typedef void          (__thiscall *VTake1p)(void*, void*);
typedef void          (__thiscall *VTake2i)(void*, int, int);
typedef void          (__thiscall *VTake2f)(void*, float, float);
typedef void          (__thiscall *VTake3)(void*, void*, void*, void*);
typedef void          (__thiscall *VTakeU1p)(void*, unsigned, void*);
typedef unsigned char (__thiscall *VQueryProp)(void*, void*, void*, void**);
typedef V2*           (__thiscall *VRetV2)(void*, V2*, V2);

void*         __cdecl    FUN_0067caa0();                 // SP::WindowManager
void*         __cdecl    FUN_0067dcc0();                 // MessageServer
unsigned      __cdecl    FUN_00435e90();                 // GetRecorderState
void          __cdecl    FUN_00435ed0(unsigned, unsigned);  // KillSetiEffects
unsigned char __cdecl    FUN_00efc9c0();
void          __fastcall FUN_005ed6c0(void*);            // cSPPaletteItemRollover::Hide
void*         __fastcall FUN_00810000(void*);            // layout constructor
void          __cdecl    FUN_00806bf0(void*);            // SetWindowAreaToParent
void          __cdecl    FUN_00806de0(void*, const unsigned short*);  // SetTooltipText
unsigned char __cdecl    FUN_00807cb0(void*, void*, int);
unsigned char __cdecl    FUN_006a1250(void*, unsigned, void*);  // GetPropertyAsKey
unsigned char __cdecl    FUN_004af210(void*, unsigned, void*);  // GetPropertyAsUint32
unsigned char __cdecl    FUN_006a10c0(void*, unsigned, void*);  // GetPropertyAsVector2
unsigned char __cdecl    FUN_0040cf10(void*, unsigned, void*);  // GetPropertyT<int>
unsigned char __cdecl    FUN_006a1360(void*, unsigned, void*);  // GetPropertyAsText
void          __fastcall FUN_006b5060(void*);            // cString ctor
void          __fastcall FUN_006b5240(void*);            // cString dtor

// Drag state shared through file-scope globals: all in .bss except the
// numeric constants, which live in the read-only data section.
extern float    gDragX0_16c75b0;         // 0x16c75b0
extern float    gDragY0_16c75b4;         // 0x16c75b4
extern uint32_t gDragSteps_16c75b8;      // 0x16c75b8
extern float    gDragStartX_16c75bc;     // 0x16c75bc
extern float    gDragStartY_16c75c0;     // 0x16c75c0
extern float    gDragEndX_16c75c4;       // 0x16c75c4
extern float    gDragEndY_16c75c8;       // 0x16c75c8
extern float    gDragHomeX_16c75cc;      // 0x16c75cc
extern float    gDragHomeY_16c75d0;      // 0x16c75d0
extern uint32_t gDragInitFlags_16c75d4;  // 0x16c75d4
extern const float    gHalf_1471064;     // 0.5f
extern const float    gOne_1485720;      // 1.0f
extern const float    gNegFive_15abdf4;  // -5.0f
extern const uint32_t gDragSpan_15abdf8; // 3
extern const float    gScaleX_140e964;   // 0.03125f
extern const float    gScaleY_1489380;   // -0.025f

struct TC_ecbb10 {
    unsigned char FUN_00ecbb10(void* win, Msg* msg);
    unsigned char FUN_005c6d70(void* win, Msg* msg);   // base cSPPaletteItemUI::DoMessage
};

// @ 0x00ecbb10
unsigned char TC_ecbb10::FUN_00ecbb10(void* win, Msg* msg)
{
    PIUI* o = OwnerOf(this);
    V2    tmp;

    // one-time lazy initialisation of the shared drag state
    if ((gDragInitFlags_16c75d4 & 1) == 0) gDragInitFlags_16c75d4 |= 1;
    if ((gDragInitFlags_16c75d4 & 2) == 0) gDragInitFlags_16c75d4 |= 2;
    if ((gDragInitFlags_16c75d4 & 4) == 0) gDragInitFlags_16c75d4 |= 4;
    if ((gDragInitFlags_16c75d4 & 8) == 0) gDragInitFlags_16c75d4 |= 8;

    void* wm = FUN_0067caa0();

    switch (msg->mType - 6) {
    case 0:                                             // type 6
        if (msg->mSub == 0x3ea) {
            if (((VRet0)VTable(win)[7])(win) == (void*)0x73933b8) {
                ((TC_eff600*)0x16c7c08)->FUN_00eff600(o);
                break;
            }
        }
        if (msg->mSub != 0x3e8)
            break;
        if (((VRet0)VTable(win)[7])(win) != (void*)0x73933b8)
            break;
        if (o->mDragArmed == 0) {
            FUN_00435ed0(0x4fc39619, FUN_00435e90());
            return 1;
        }
        {
            float* r = (float*)((VRet0)VTable(win)[14])(win);
            gDragHomeX_16c75cc  = r[0];
            gDragHomeY_16c75d0  = r[1];
            gDragEndX_16c75c4   = msg->m0c;
            gDragEndY_16c75c8   = msg->m10;
            gDragStartX_16c75bc = (r[2] + r[0]) * gHalf_1471064;
            gDragStartY_16c75c0 = (r[3] + r[1]) * gHalf_1471064;
            gDragSteps_16c75b8  = gDragSpan_15abdf8;

            void* q = ((VRet0)VTable(win)[4])(win);
            q = ((VRet0)VTable(q)[4])(q);
            q = ((VRet0)VTable(q)[4])(q);
            float* a = (float*)((VRet0)VTable(q)[14])(q);
            float* b = (float*)((VRet0)VTable(q)[14])(q);
            gDragX0_16c75b0 = b[0];
            gDragY0_16c75b4 = a[1];

            void* r2 = ((VRet0)VTable(q)[4])(q);
            V2 in;
            in.x = gDragX0_16c75b0;
            in.y = gDragY0_16c75b4;
            V2* res = ((VRetV2)VTable(r2)[48])(r2, &tmp, in);
            gDragX0_16c75b0 = res->x + gNegFive_15abdf4;
            gDragY0_16c75b4 = res->y;
            o->mDragActive = 1;
            ((VTakeU1p)VTable(wm)[22])(wm, 1, win);
            return 1;
        }

    case 1:                                             // type 7
        if (msg->mSub != 0x3e8)
            break;
        if (o->mDragActive != 0) {
            ((VTakeU1p)VTable(wm)[23])(wm, 1, win);
            ((VTake2f)VTable(win)[28])(win, gDragHomeX_16c75cc, gDragHomeY_16c75d0);
            o->mDragActive = 0;
        }
        return 1;

    case 2:                                             // type 8
        if (o->mDragActive == 0)
            break;
        {
            V2 in;
            in.x = msg->m0c;
            in.y = msg->m10;
            V2* r = ((VRetV2)VTable(win)[48])(win, &tmp, in);
            float lx = r->x;
            float ly = r->y;
            void* wmr = ((VRet0)VTable(wm)[1])(wm);
            ((VTake2i)VTable(win)[31])(win, 0x10, 1);
            void* got = ((VRet1p)VTable(wm)[5])(wm, &lx);
            unsigned char flag = 1;
            if (got == wmr && lx < gDragX0_16c75b0 && FUN_00efc9c0() != 0)
                flag = 0;
            ((VTake2i)VTable(win)[31])(win, 0x10, 0);
            if (flag == 0) {
                // drag cancelled: restore the home position
                ((VTakeU1p)VTable(wm)[23])(wm, 1, win);
                ((VTake2f)VTable(win)[28])(win, gDragHomeX_16c75cc, gDragHomeY_16c75d0);
                o->mDragActive = 0;
                void* ms = FUN_0067dcc0();
                ((VTake3)VTable(ms)[5])(ms, (void*)0x73e7eb7, o, 0);
                return this->FUN_005c6d70(win, msg);
            }
            // drag in progress: re-aim the cursor along the stored axis
            float ratio = (float)gDragSteps_16c75b8 / (float)gDragSpan_15abdf8;
            float cx = (gDragEndX_16c75c4 - gDragStartX_16c75bc) * ratio + gDragStartX_16c75bc;
            float cy = (gDragEndY_16c75c8 - gDragStartY_16c75c0) * ratio + gDragStartY_16c75c0;
            if (gDragSteps_16c75b8 != 0)
                gDragSteps_16c75b8--;
            void* obj = ((VRet0)VTable(win)[4])(win);
            V2 d;
            d.x = lx - cx;
            d.y = ly - cy;
            V2* out = ((VRetV2)VTable(obj)[49])(obj, &tmp, d);
            ((VTake2f)VTable(win)[28])(win, out->x, out->y);
            return this->FUN_005c6d70(win, msg);
        }

    case 4:                                             // type 10
        if (o->mDragArmed != 0)
            break;
        if (msg->m0ci != 1)
            break;
        if (((VRet0)VTable(win)[7])(win) != (void*)0x73933b8)
            break;
        if (msg->mObj != win) {
            PLay* pl = (PLay*)o->m2c;
            FUN_005ed6c0(pl->m14);
            return 1;
        }
        {
            PLay* pl = (PLay*)o->m2c;
            void* anchor = pl->m14;
            void* q = o->m04;
            ((VTake3)VTable(anchor)[10])(anchor, q, (char*)q + 0xc, o->m2c);
            void* M = o->m1c;
            float* r = (float*)((VRet0)VTable(M)[14])(M);
            V2 v;
            v.x = (r[2] - r[0]) * gHalf_1471064;
            v.y = (r[3] - r[1]) * gHalf_1471064;
            V2* out = ((VRetV2)VTable(M)[48])(M, &tmp, v);
            void* wmr = ((VRet0)VTable(wm)[1])(wm);
            float* r3 = (float*)((VRet0)VTable(wmr)[14])(wmr);
            ((TC_8283a0*)anchor)->FUN_008283a0(
                out->x, out->y,
                (r3[2] - r3[0]) * gScaleX_140e964,
                (r3[3] - r3[1]) * gScaleY_1489380);
            void* ms = FUN_0067dcc0();
            ((VTake3)VTable(ms)[5])(ms, (void*)0x78c406b, 0, 0);
            return 1;
        }
    }

    return this->FUN_005c6d70(win, msg);
}

// @ 0x00ecc140
void PIUI::FUN_00ecc140(void* a1, void* a2, void* a3, void* a4)
{
    // forward to the base implementation first
    ((TC_5c6ca0*)this)->FUN_005c6ca0(a1, a2, a3, a4);

    // this->m24 <- a3   (AddRef vt[0] / Release vt[1])
    if (a3 != this->m24) {
        void* old = this->m24;
        if (a3 != 0)
            ((VCall0v)VTable(a3)[0])(a3);
        this->m24 = a3;
        if (old != 0)
            ((VCall0v)VTable(old)[1])(old);
    }
    // this->m2c <- a4   (AddRef vt[1] / Release vt[2])
    if (a4 != this->m2c) {
        void* old = this->m2c;
        if (a4 != 0)
            ((VCall0v)VTable(a4)[1])(a4);
        this->m2c = a4;
        if (old != 0)
            ((VCall0v)VTable(old)[2])(old);
    }

    // build the layout object and install it in this->m28
    void* mem = FUN_00f473a0(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    void* lay = (mem != 0) ? FUN_00810000(mem) : 0;
    if (lay != this->m28) {
        void* old = this->m28;
        if (lay != 0)
            ((VCall0v)VTable(lay)[1])(lay);
        this->m28 = lay;
        if (old != 0)
            ((VCall0v)VTable(old)[2])(old);
    }

    Key key;
    key.m0 = 0xeb56d154;
    key.m1 = 0x0510a95b;
    key.m2 = 0x40464100;

    TC_layout* L = (TC_layout*)this->m28;
    if (!L->FUN_008120d0(key, 0, 0x5b598fa)) {
        L->FUN_00811ad0(1);                 // Shutdown
        void* l = this->m28;
        if (l != 0) {
            this->m28 = 0;
            ((VCall0v)VTable(l)[2])(l);
        }
        return;
    }

    L->FUN_008121b0(a2, 1, 0x5b598fa);      // SetParentWin
    void* w = L->FUN_008105b0(0x4a1cb6f, 1);
    if (w != 0)
        FUN_00806bf0(w);                    // SetWindowAreaToParent

    PSrc* src = (PSrc*)a1;
    void* props = 0;
    void* pm = FUN_0067de30();
    unsigned char ok = ((VQueryProp)VTable(pm)[11])(pm, src->mKey0c, src->mKey14, &props);
    if (ok && props != 0) {
        this->mUseDefaults = 0;
        if (!FUN_006a1250(props, 0x306c86ef, &this->mKey30)) {
            FUN_006a1250(props, 0xec087521, &this->mKey30);
            this->mUseDefaults = 1;
        }
        FUN_006a1250(props, 0xab2b50e4, &this->mKey3c);
        FUN_006a1250(props, 0x8cbd2d87, &this->mKey48);
        FUN_004af210(props, 0x5882a049, &this->m54);

        if (this->mUseDefaults != 0) {
            this->m6c = gHalf_1471064;
            this->m58.x = gHalf_1471064;
            this->m58.y = gHalf_1471064;
        } else if (!FUN_006a10c0(props, 0x8670bfc3, &this->m58)) {
            this->m6c = gHalf_1471064;
            this->m58.x = gHalf_1471064;
            this->m58.y = gHalf_1471064;
        } else {
            float f;
            if (!FUN_0040cf10(props, 0xeec97733, &f))
                this->m6c = gHalf_1471064;
            else
                this->m6c = this->FUN_00ecb7a0(f);
        }

        FUN_006a10c0(props, 0xe28cb159, &this->m60);
        {
            float f;
            if (!FUN_0040cf10(props, 0x72cb9221, &f))
                this->m70 = gHalf_1471064;
            else
                this->m70 = this->FUN_00ecb830(f);
        }

        this->m74 = gOne_1485720;
        FUN_0040cf10(props, 0x871de6a1, &this->m74);

        Key tk;
        tk.m0 = 0;
        tk.m1 = 0;
        tk.m2 = 0;
        if (FUN_006a1250(props, 0x3068d95c, &tk)) {
            void* w2 = L->FUN_008105b0(0x73933b8, 1);
            if (w2 != 0) {
                ((VTake1p)VTable(w2)[65])(w2, &this->mIWinProc);
                FUN_00807cb0(w2, &tk, 0);
                CStr cs;
                FUN_006b5060(&cs);
                if (FUN_006a1360(props, 0x3068d95d, &cs))
                    FUN_00806de0(w2, cs.FUN_006b55c0(-1, 1));
                FUN_006b5240(&cs);
            }
        }

        // publish the object in the global table keyed by its first key word
        uint32_t tkey = this->mKey30.m0;
        void* slot = ((TC_b474c0*)0x15abdd4)->FUN_00b474c0(&tkey);
        *(void**)slot = this;
    }

    if (props != 0)
        ((VCall0v)VTable(props)[1])(props);
}

// @ 0x00ecc960
void* __cdecl FUN_00ecc960(void** out)
{
    *out = 0;
    void* tmp = 0;
    char* pm = (char*)FUN_0067de30();
    if (tmp != 0) {
        char* t = (char*)tmp;
        tmp = 0;
        (*(void(__thiscall**)(char*))(*(char**)t + 4))(t);
    }
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int, void**))(*(char**)pm + 0x2c))(
        pm, *(int*)0x15abed8, *(int*)0x15abee0, &tmp);
    if (ok) {
        if (tmp == 0)
            goto cleanup;
        int a = 0, b = 0;
        if (FUN_006a0ae0(&a, &b, tmp)) {
            int n = a;
            if ((unsigned)b > (unsigned)n)
                goto cleanup;
            char* pv = (char*)*out;
            if (pv != 0) {
                *out = 0;
                (*(void(__thiscall**)(char*))(*(char**)pv + 4))(pv);
            }
            FUN_00806230((char*)&a, 0, -1, -1, 0);
        }
    }
cleanup:
    if (tmp != 0)
        (*(void(__thiscall**)(char*))(*(char**)tmp + 4))((char*)tmp);
    return *out;
}

// @ 0x00ecca30
void* __cdecl FUN_00ecca30()
{
    void* tmp = 0;
    char* pm = (char*)FUN_0067de30();
    if (tmp != 0) {
        char* t = (char*)tmp;
        tmp = 0;
        (*(void(__thiscall**)(char*))(*(char**)t + 4))(t);
    }
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int, void**))(*(char**)pm + 0x2c))(
        pm, *(int*)0x15abed8, *(int*)0x15abee0, &tmp);
    if (ok) {
        if (tmp == 0)
            goto cleanup;
        int a = 0, b = 0;
        if (FUN_006a0ae0(&a, &b, tmp)) {
            int n = b;
            if (a <= n)
                goto cleanup;
            char* v = *(char**)((char*)&a + (n + n * 2) * 0);
            (void)v;
        }
    }
cleanup:
    if (tmp != 0)
        (*(void(__thiscall**)(char*))(*(char**)tmp + 4))((char*)tmp);
    return 0;
}
