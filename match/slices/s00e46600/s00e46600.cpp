// Slice s00e46600 -- SPUI timeline / property-layout code (bundle of 9 functions).
//   FUN_00e46600  (0x00e46600)  Timeline member (property load / initialize)
//   FUN_00e46880  (0x00e46880)  Timeline member (layout update, recursive over children)
//   FUN_00e46d80  (0x00e46d80)  Timeline member (scrub / advance, recursive)
//   FUN_00e470a0  (0x00e470a0)  Timeline member (fetch normalised position)
//   FUN_00e47100  (0x00e47100)  Timeline member (query a named rect)
//   FUN_00e47180  (0x00e47180)  cSPUIPropertyLayout deleting destructor
//   FUN_00e471e0  (0x00e471e0)  cSPUIPropertyLayout constructor body
//   FUN_00e47300  (0x00e47300)  cSPUIPropertyLayout destructor body
//   FUN_00e47460  (0x00e47460)  Timeline member helper (recursive)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;

struct Property;            // opaque property instance (only offsets touched)

// ---------------------------------------------------------------------------
// external callees (retail VAs in comments; bodies live in other slices)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void* __cdecl operator_new(unsigned int n);                                  // ??2
void  __cdecl operator_delete(void* p);                                      // 0xf47380  ??3

// member-model externals (retail uses __thiscall with ecx == this)
struct CPL { void dtor(); };                                                 // 0x828670  ??1CPL
struct Helper4b { void dtor(); };                                            // 0x4b5440
struct EaVector { int dtor(); };                                             // 0xae6970
struct PropObj {
    u8* GetBool();      // 0x41e920  Property::GetBool
};
struct LayoutObj {                                                           // 0x167eb28 instance
    float* GetF1(void* a, void* b);   // 0xe40010
    float* GetF2(void* a);            // 0xe40080
};
struct GmeGlobal {                                                           // 0xe37f30 (thiscall, 1 arg, ret 4)
    float FUN_00e37f30(void* arg);
};

// SP::cString_s006b_47a0 (0x14 bytes)
struct CString {
    u32 a, b, c, d, e;
    void  ctor();                                        // 0x6b5060
    void  dtor();                                        // 0x6b5240
    int   Load(u32 a, u32 b, int c);                     // 0x6b54b0
    u16*  GetText();                                     // 0x6b55c0
};
struct WString {
    void Assign(const u16* begin, const u16* end);       // 0x423650
};

// SP property helpers
void* __cdecl SP_PropertyManager();                                          // 0x67de30
void  __cdecl SP_GetPropertyAsKeyInstance(void* pm, u32 key, void* out);     // 0x6a12a0
char  __cdecl SP_GetPropertyAsText(void* pm, u32 key, void* out);            // 0x6a1360
char  __cdecl SP_VectorReserve(void* pm, u32 key, void* out, void* out2);    // 0x6a0ae0
void* __cdecl SP_GlobalGet();                                                // 0xb3d410 (returns *(void**)0x167eb28)
void* __cdecl cSPUILayout_FindWindowByID(void* layout, u32 id, int b);       // 0x8105b0

struct Vec2 { float x, y; };

extern "C" __declspec(dllimport) double __cdecl ceil(double x);

// vtable / global data referenced directly
extern "C" void* PTR_AddRef_01482370;   // 0x1482370
extern "C" void* PTR_FUN_01482360;      // 0x1482360
extern "C" void* PTR_AddRef_014823a8;   // 0x14823a8
extern "C" void* PTR_FUN_01482398;      // 0x1482398
extern "C" void* PTR_AddRef_013ec458;   // 0x13ec458
extern "C" void* PTR_AddRef_013eb938;   // 0x13eb938

extern "C" float  DAT_013f4fd0;         // 0x13f4fd0
extern "C" float  DAT_013f6a30;         // 0x13f6a30
extern "C" float  DAT_01485720;         // 0x1485720
extern "C" float  DAT_01471064;         // 0x1471064
extern "C" float  DAT_013ec488;         // 0x13ec488
extern "C" float  DAT_013eb8b0;         // 0x13eb8b0 (sign-mask, used with xorps)
extern "C" void*  gEmptyString16;       // 0x1667bac
extern "C" u32    DAT_01667bae;         // 0x1667bae

// ---------------------------------------------------------------------------
// object layouts (offsets only)
// ---------------------------------------------------------------------------
struct Timeline;

// abstract vtable-bearing ref-counted base used for the toggle objects
struct RefObj {
    virtual void AddRef();
    virtual void Release();
};

struct Timeline {
    u8  pad00[0x10];
    void* p10;      // +0x10  layout A
    void* p14;      // +0x14  layout B
    u8  pad18[4];
    void* p1c;      // +0x1c
    void* p20;      // +0x20
    u8  pad24[0x44];
    u32 id68;       // +0x68
    u8  b6c;        // +0x6c
    u8  b6d;        // +0x6d
    u8  pad6e[2];
    float f70;      // +0x70
    float f74;      // +0x74
    float f78;      // +0x78
    float f7c;      // +0x7c
    float f80;      // +0x80
    float f84;      // +0x84
    void* p88;      // +0x88
    void* p8c;      // +0x8c
    u32   u90;      // +0x90
    u8  pad94[0x14];
    void* pa8;      // +0xa8
    u8  padac[0x14];
    void* pc0;      // +0xc0   vector begin
    void* pc4;      // +0xc4   vector end
    u32   ucc;      // +0xc8
    u8  padd0[8];
    u32   ud4;      // +0xd4
    u32   ud8;      // +0xd8
    float fdc;      // +0xdc
    u8  be0;        // +0xe0
    u8  pade1[3];
    u32   ue4;      // +0xe4
    u32   ue8;      // +0xe8
    u8  bec;        // +0xec
    u8  bed;        // +0xed
    u8  padee[2];
    u32   uf0;      // +0xf0
    u8  bf4;        // +0xf4
    u8  padf5[3];
    float ff8;      // +0xf8
    float ffc;      // +0xfc
    float f100;     // +0x100
    float f104;     // +0x104
    u8  b108;       // +0x108
    u8  b109;       // +0x109

    void FUN_00e46600(void* p2, int p3, u32 p4, u32 p5);
    void FUN_00e46880(int p2);
    void FUN_00e46d80(float a, float b, bool c, float d, float e, bool f);
    void* FUN_00e470a0(void* out);
    bool  FUN_00e47100(void* out);
    void  FUN_00e47460();
    float FUN_00e460d0();   // 0xe460d0
    void  FUN_00e48fa0(void* a, float b, u32 c, float d);   // 0xe48fa0
};

// cSPUIPropertyLayout object
struct SPUIPropertyLayout {
    void* vtbl0;    // +0x00
    void* vtbl1;    // +0x04
    u32   u08;      // +0x08
    u32   u0c;      // +0x0c
    u32   u10;      // +0x10
    u32   u14;      // +0x14
    u32   u18;      // +0x18
    u32   u1c;      // +0x1c
    u32   u20;      // +0x20
    u32   u24;      // +0x24
    u32   u28;      // +0x28
    u32   u2c;      // +0x2c
    u32   u30;      // +0x30
    u8    pad34[8];
    u32   u3c;      // +0x3c
    u32   u40;      // +0x40
    u32   u44;      // +0x44
    u8    pad48[8];
    u32   u50;      // +0x50
    u32   u54;      // +0x54
    u32   u58;      // +0x58
    u8    pad5c[8];
    u32   u64;      // +0x64
    u32   u68;      // +0x68
    u8    b6c;      // +0x6c
    u8    b6d;      // +0x6d
    u8    pad6e[2];
    float f70;      // +0x70
    float f74;      // +0x74
    u8    pad78[0x10];
    u32   u88;      // +0x88
    u32   u8c;      // +0x8c
    u32   u90;      // +0x90
    u8    pad94[4];
    u32   u98;      // +0x98
    u32   u9c;      // +0x9c
    u32   ua0;      // +0xa0
    u32   ua4;      // +0xa4
    u32   ua8;      // +0xa8
    u32   uac;      // +0xac
    u32   ub0;      // +0xb0
    u32   ub4;      // +0xb4
    u8    padb8[8];
    u32   uc0;      // +0xc0
    u32   uc4;      // +0xc4
    u32   uc8;      // +0xc8
    u8    padcc[8];
    u32   ud4;      // +0xd4
    u32   ud8;      // +0xd8
    float fdc;      // +0xdc
    u8    be0;      // +0xe0
    u8    pade1[3];
    u32   ue4;      // +0xe4
    u8    padf0[4];
    u8    bec;      // +0xec
    u8    bed;      // +0xed
    u8    padee[2];
    u32   uf0;      // +0xf0
    u8    bf4;      // +0xf4
    u8    padf5[0x13];
    u8    b108;     // +0x108
    u8    b109;     // +0x109

    void* FUN_00e471e0();           // ctor body (returns this in eax)
    void  FUN_00e47300();           // dtor body
    void* FUN_00e47180(u8 flags);   // deleting destructor
};

// ---------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------
#define VTOBJ(o)  (*(void***)(o))

// @ 0x00e46600
void Timeline::FUN_00e46600(void* p2, int p3, u32 p4, u32 p5)
{
    void**  slot64 = (void**)((char*)this + 0x64);
    void*   old;
    void*   prop;
    u32     out1;
    u32     out2;
    float   tmp[4];
    CString cs;

    this->id68 = (u32)p3;

    old = *slot64;
    if (old != 0) {
        *slot64 = 0;
        void** vt = *(void***)old;
        ((void(__thiscall*)(void*))vt[1])(old);
    }

    this->ud4 = p4;
    this->ud8 = p5;

    old = this->p1c;
    if (p2 != old) {
        if (p2 != 0) {
            void** vt = *(void***)p2;
            ((void(__thiscall*)(void*))vt[0])(p2);
        }
        this->p1c = p2;
        if (old != 0) {
            void** vt = *(void***)old;
            ((void(__thiscall*)(void*))vt[1])(old);
        }
    }

    if (*slot64 == 0) {
        void* propmgr = SP_PropertyManager();
        old = *slot64;
        if (old != 0) {
            *slot64 = 0;
            void** vt = *(void***)old;
            ((void(__thiscall*)(void*))vt[1])(old);
        }
        void** vt = *(void***)propmgr;
        ((void(__thiscall*)(void*, int, u32, void**))vt[0x2c / 4])(propmgr, p3, 0xe1d7164f, slot64);
    }

    SP_GetPropertyAsKeyInstance(*slot64, 0x91ad064, (char*)this + 0xe4);

    {
        void* pm = *slot64;
        if (pm != 0) {
            void** vt = *(void***)pm;
            if (((char(__thiscall*)(void*, u32, void*))vt[0x24 / 4])(pm, 0xd53426dd, &prop)) {
                if (*(u16*)((char*)prop + 0x12) == 1) {
                    u8* b = (u8*)((PropObj*)prop)->GetBool();
                    this->bed = *b;
                }
            }
        }
    }

    {
        void* pm = *slot64;
        if (pm != 0) {
            void** vt = *(void***)pm;
            if (((char(__thiscall*)(void*, u32, void*))vt[0x24 / 4])(pm, 0x60bc73a, &prop)) {
                if (*(u16*)((char*)prop + 0x12) == 1) {
                    u8* b = (u8*)((PropObj*)prop)->GetBool();
                    this->bec = *b;
                }
            }
        }
    }

    {
        void* pm = *slot64;
        if (pm != 0) {
            void** vt = *(void***)pm;
            if (((char(__thiscall*)(void*, u32, void*))vt[0x24 / 4])(pm, 0x65e6c46, &prop)) {
                if (*(u16*)((char*)prop + 0x12) == 1) {
                    u8* b = (u8*)((PropObj*)prop)->GetBool();
                    this->bf4 = *b;
                }
            }
        }
    }

    {
        SP_GetPropertyAsKeyInstance(*slot64, 0xd553f870, (char*)this + 0xe8);
        SP_GetPropertyAsKeyInstance(*slot64, 0x34e3b684, (char*)this + 0x18);
        SP_GetPropertyAsKeyInstance(*slot64, 0x89abe050, (char*)this + 0xf0);
    }

    cs.ctor();
    if (SP_GetPropertyAsText(*slot64, 0xd5624e29, &cs))
        this->b109 = 1;
    else if (SP_GetPropertyAsText(*slot64, 0xd5624e2a, &cs))
        this->b109 = 1;

    {
        void* r;
        r = SP_GlobalGet();
        {
            float* f = ((LayoutObj*)r)->GetF1(tmp, this);
            this->f74 = f[0];
        }
        r = SP_GlobalGet();
        {
            float* f = ((LayoutObj*)r)->GetF1(tmp, this);
            this->f70 = f[1];
        }
        r = SP_GlobalGet();
        {
            float* f = ((LayoutObj*)r)->GetF2(tmp);
            this->f78  = f[0];
            this->f7c  = f[1];
            this->f80  = f[2];
            this->f84  = f[3];
        }
    }

    {
        void* pm  = *(void**)((char*)this + 0x64);
        if (SP_VectorReserve(pm, 0x65263b4, &out1, &out2)) {
            void* c = this->p1c;
            if (c != 0 && out1 == 3) {
                void** vt = *(void***)c;
                float* f = (float*)((void* (*)(void*))vt[0x38 / 4])(c);
                this->f70 = f[3] - f[1];
            }
        }
    }

    this->b6c = 1;
    cs.dtor();
}

// @ 0x00e46880
void Timeline::FUN_00e46880(int param_2)
{
    float fStack_34 = this->ff8;
    float fVar10 = this->ffc;
    if (this->p20 != 0) {
        float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
        fStack_34 = pf[0];
        fVar10 = pf[1];
    }
    float fVar1 = (float)param_2;
    if (param_2 < 0)
        fVar1 = fVar1 + DAT_013f4fd0;
    float local_10 = 0.0f;
    if (0.0f <= fVar1 * DAT_013f6a30)
        local_10 = fVar1 * DAT_013f6a30;
    if (DAT_01485720 <= local_10)
        local_10 = DAT_01485720;
    fStack_34 = (this->ff8 - fStack_34) * local_10 + fStack_34;
    ceil((double)((this->ffc - fVar10) * local_10 + fVar10));
    ceil((double)fStack_34);
    float fStack_20 = this->ff8;
    float fStack_1c = this->ffc;
    if (this->p20 != 0) {
        ((void (*)(void*, float, float))VTOBJ(this->p20)[0x70 / 4])(this->p20, fStack_20, fStack_1c);
    }
    if (this->p10 != 0) {
        if (SP_GlobalGet() != 0) {
            void* piVar4 = cSPUILayout_FindWindowByID(this->p10, 0x55541be1, 1);
            if (this->p20 != 0) {
                if (piVar4 != 0) {
                    if (((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4) != 0) {
                        void* piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        ((void (*)(void*))VTOBJ(piVar5)[0xe8 / 4])(piVar5);
                        piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        int iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                        fStack_20 = *(float*)(iVar3 + 4);
                        float fStack_18 = *(float*)(iVar3 + 0xc);
                        float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
                        float unaff_EBX = pf[0];
                        float fStack_30 = pf[2];
                        pf = (float*)((void* (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                        fVar10 = pf[2];
                        fVar1 = pf[0];
                        local_10 = 0.0f;
                        float fStack_8 = fStack_18 - fStack_20;
                        float fStack_24 = (fStack_30 + unaff_EBX) * DAT_01471064;
                        void* uVar6 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        void* g = SP_GlobalGet();
                        float fVar9 = ((GmeGlobal*)g)->FUN_00e37f30(uVar6);
                        float fStack_14 = fStack_24 - (fVar10 - fVar1) * DAT_01471064 + fVar9;
                        float fStack_c = fStack_14 + (fVar10 - fVar1);
                        ((void (*)(void*, float*))VTOBJ(piVar4)[0x6c / 4])(piVar4, &fStack_14);
                        (void)fStack_c;
                    }
                }
            }
        }
    }
    if (this->p14 != 0) {
        void* piVar4 = cSPUILayout_FindWindowByID(this->p14, 0x355430a0, 1);
        if (this->p20 != 0) {
            if (((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20) != 0) {
                if (piVar4 != 0) {
                    if (((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4) != 0) {
                        if (SP_GlobalGet() != 0) {
                            void* piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            int iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                            fStack_1c = *(float*)(iVar3 + 4);
                            float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
                            local_10 = pf[0];
                            float fStack_8 = pf[2];
                            pf = (float*)((void* (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                            fVar10 = pf[2];
                            fVar1 = pf[0];
                            iVar3 = ((int (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                            fStack_34 = *(float*)(iVar3 + 0xc) - *(float*)(iVar3 + 4);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                            float fStack_24 = fStack_1c - *(float*)(iVar3 + 4);
                            fStack_20 = (fStack_8 + local_10) * DAT_01471064 - (fVar10 - fVar1) * DAT_01471064;
                            fStack_34 = fStack_20 + (fVar10 - fVar1);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            u32* puVar7 = (u32*)((void* (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc0 / 4])(piVar5, &local_10, fStack_20, fStack_24);
                            u32 uStack_2c = puVar7[0];
                            u32 uStack_28 = puVar7[1];
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            ((void (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc0 / 4])(piVar5, &fStack_1c, 0.0f, fStack_8);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            ((void (*)(void*, u32*, float, float))VTOBJ(piVar5)[0xc4 / 4])(piVar5, &uStack_28, 0.0f, fStack_34);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            iVar3 = ((int (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc4 / 4])(piVar5, &fStack_34, 0.0f, fVar10);
                            fStack_34 = *(float*)(iVar3 + 4);
                            ((void (*)(void*, float*))VTOBJ(piVar4)[0x6c / 4])(piVar4, &fStack_34);
                            (void)uStack_2c;
                        }
                    }
                }
            }
        }
    }
    {
        int iVar3 = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        for (int i = 0; i < iVar3; i++) {
            Timeline* c = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
            c->FUN_00e46880(param_2);
        }
    }
}

// @ 0x00e46d80
void Timeline::FUN_00e46d80(float a, float b, bool c, float d, float e, bool f)
{
    float fVar5;
    this->ff8 = a;
    if (this->p1c == 0) {
        fVar5 = 0.0f;
    } else {
        int iVar2 = ((int (*)(void*))VTOBJ(this->p1c)[0x38 / 4])(this->p1c);
        fVar5 = *(float*)(iVar2 + 0xc) - *(float*)(iVar2 + 4);
    }
    float fVar4 = this->FUN_00e460d0();
    u32 uVar1 = (u32)c;
    float fVar7 = *(float*)((char*)this + 0x70);
    float fVar6 = fVar7 * DAT_01471064;
    float fVar8 = fVar4 * fVar5 * DAT_01471064 + fVar5 * DAT_01471064 - fVar6;
    if (*(int*)((char*)this + 0xa8) == 0 || *(char*)((char*)this + 0xec) == 0) {
        this->ffc  = b;
        this->f100 = *(float*)((char*)this + 0x74) * DAT_01471064 + this->ff8;
        this->f104 = fVar6 + b;
    } else {
        this->f100 = *(float*)((char*)this + 0x74) * DAT_01471064 + this->ff8;
        this->f104 = fVar6 + fVar8;
        if (!f) {
            float t2 = (fVar5 - fVar7) - (*(float*)((char*)this + 0x84) - fVar7);
            float t1 = fVar8;
            float neg7c = -*(float*)((char*)this + 0x7c);
            if (t1 <= neg7c)
                t1 = neg7c;
            if (t2 <= t1)
                t1 = t2;
            this->ffc = t1;
        } else {
            this->ffc = fVar8;
        }
    }
    this->ff8 += d;
    this->ffc += e;
    if (c && this->p20 != 0) {
        ((void (*)(void*, float, float))VTOBJ(this->p20)[0x70 / 4])(this->p20, this->ff8, this->ffc);
    }
    if (*(int*)((char*)this + 0x68) == 0x6701aff5) {
        this->FUN_00e48fa0(&a, fVar4, uVar1, fVar8);
        return;
    }
    {
        int iVar2 = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        if (iVar2 > 0) {
            float fVar7b = (float)(iVar2 - 1) * DAT_01471064;
            float fVar7c = ((float)(iVar2 - 1) * -DAT_01471064) * *(float*)((char*)this + 0x70) + fVar8;
            float fVar8b = ((float)iVar2 - fVar7b) * *(float*)((char*)this + 0x70) + fVar8;
            float local_38 = 0.0f;
            if (0.0f <= fVar7c) {
                if (fVar5 < fVar8b)
                    local_38 = fVar5 - fVar8b;
            } else {
                local_38 = -fVar7c;
            }
            for (int i = 0; i < iVar2; i++) {
                Timeline* el = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
                el->FUN_00e46d80(a, b, c, 0.0f, ((float)i - fVar7b) * *(float*)((char*)this + 0x70) + local_38, true);
            }
        }
    }
}

// @ 0x00e470a0
void* Timeline::FUN_00e470a0(void* out)
{
    Vec2* o = (Vec2*)out;
    o->x = this->f100;
    o->y = this->f104;
    void* c = this->p1c;
    if (c != 0) {
        Vec2 v = *o;
        Vec2 tmp;
        ((void (__thiscall*)(void*, Vec2*, Vec2))(*(void***)c)[0xc0 / 4])(c, &tmp, v);
        *o = v;
    }
    return out;
}

// @ 0x00e47100
bool Timeline::FUN_00e47100(void* out)
{
    u32* o = (u32*)out;
    void* c = *(void**)((char*)this + 0x64);
    void* prop;
    if (c != 0
        && *(u32*)((char*)this + 0xa8) != 0
        && ((char (__thiscall*)(void*, u32, void*))(*(void***)c)[0x24 / 4])(c, 0xb5147b8c, &prop)
        && *(u16*)((char*)prop + 0x12) == 1
        && *((PropObj*)prop)->GetBool() != 0) {
        o[0] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0x10);
        o[2] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0x14);
        o[1] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0xc);
        return true;
    }
    return false;
}

// @ 0x00e47180
void* SPUIPropertyLayout::FUN_00e47180(u8 flags)
{
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_01482370;
    *(volatile void**)((char*)this + 4) = &PTR_FUN_01482360;
    _ReadWriteBarrier();
    void* c;
    c = *(void**)((char*)this + 0x80);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    c = *(void**)((char*)this + 0x7c);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    c = *(void**)((char*)this + 0x78);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    ((CPL*)this)->dtor();
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00e471e0
void* SPUIPropertyLayout::FUN_00e471e0()
{
    u32 z = 0;
    *(volatile void**)((char*)this + 4) = &PTR_AddRef_013ec458;
    _ReadWriteBarrier();
    *(u32*)((char*)this + 8) = z;
    *(void**)((char*)this + 0) = &PTR_AddRef_014823a8;
    *(void**)((char*)this + 4) = &PTR_FUN_01482398;
    *(u32*)((char*)this + 0x0c) = z;
    *(u32*)((char*)this + 0x10) = z;
    *(u32*)((char*)this + 0x14) = z;
    *(u32*)((char*)this + 0x18) = z;
    *(u32*)((char*)this + 0x1c) = z;
    *(u32*)((char*)this + 0x20) = z;
    *(u32*)((char*)this + 0x24) = z;
    *(u32*)((char*)this + 0x28) = z;
    *(u32*)((char*)this + 0x2c) = z;
    *(u32*)((char*)this + 0x30) = z;
    *(u32*)((char*)this + 0x3c) = z;
    *(u32*)((char*)this + 0x40) = z;
    *(u32*)((char*)this + 0x44) = z;
    *(u32*)((char*)this + 0x50) = z;
    *(u32*)((char*)this + 0x54) = z;
    *(u32*)((char*)this + 0x58) = z;
    *(u32*)((char*)this + 0x64) = z;
    *(u32*)((char*)this + 0x68) = z;
    *(u8*)((char*)this + 0x6c) = 1;
    *(u8*)((char*)this + 0x6d) = 0;
    *(float*)((char*)this + 0x70) = 0.0f;
    *(float*)((char*)this + 0x74) = 0.0f;
    *(u32*)((char*)this + 0x90) = (u32)&DAT_01667bae;
    *(void**)((char*)this + 0x88) = &gEmptyString16;
    *(void**)((char*)this + 0x8c) = &gEmptyString16;
    *(u32*)((char*)this + 0x98) = z;
    *(u32*)((char*)this + 0x9c) = z;
    *(u32*)((char*)this + 0xa0) = z;
    *(u32*)((char*)this + 0xa4) = z;
    *(u32*)((char*)this + 0xa8) = z;
    *(u32*)((char*)this + 0xac) = z;
    *(u32*)((char*)this + 0xb0) = z;
    *(u32*)((char*)this + 0xb4) = z;
    *(u32*)((char*)this + 0xc0) = z;
    *(u32*)((char*)this + 0xc4) = z;
    *(u32*)((char*)this + 0xc8) = z;
    *(u32*)((char*)this + 0xd4) = z;
    *(u32*)((char*)this + 0xd8) = z;
    *(float*)((char*)this + 0xdc) = 0.0f;
    *(u8*)((char*)this + 0xe0) = 0;
    *(u32*)((char*)this + 0xe4) = z;
    *(u8*)((char*)this + 0xec) = 0;
    *(u8*)((char*)this + 0xed) = 0;
    *(u32*)((char*)this + 0xf0) = z;
    *(u8*)((char*)this + 0xf4) = 0;
    *(u8*)((char*)this + 0x108) = 0;
    *(u8*)((char*)this + 0x109) = 0;
    return this;
}

// @ 0x00e47300
void SPUIPropertyLayout::FUN_00e47300()
{
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_014823a8;
    *(volatile void**)((char*)this + 4) = &PTR_FUN_01482398;
    ((EaVector*)((char*)this + 0xc0))->dtor();
    {
        u32 v = *(u32*)((char*)this + 0xac);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete((void*)v);
    }
    {
        void* c = *(void**)((char*)this + 0xa4);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0xa0);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 v = *(u32*)((char*)this + 0x9c);
        if (v != 0) {
            void* c = (void*)(v + 0x10);
            ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
        }
    }
    {
        void* c = *(void**)((char*)this + 0x98);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 a = *(u32*)((char*)this + 0x88);
        u32 b = *(u32*)((char*)this + 0x90);
        u32 d = (b - a) & 0xfffffffe;
        if ((int)d > 2 && a != 0)
            operator_delete((void*)a);
    }
    {
        void* c = *(void**)((char*)this + 0x64);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 v = *(u32*)((char*)this + 0x50);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete((void*)v);
    }
    ((EaVector*)((char*)this + 0x3c))->dtor();
    ((Helper4b*)((char*)this + 0x28))->dtor();
    {
        void* c = *(void**)((char*)this + 0x24);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x20);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x1c);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x14);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x10);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x0c);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_013eb938;
    _ReadWriteBarrier();
    *(volatile void**)((char*)this + 4) = &PTR_AddRef_013ec458;
}

// @ 0x00e47460
void Timeline::FUN_00e47460()
{
    CString cs;
    cs.ctor();
    u32 k = *(u32*)((char*)this + 0xe8);
    switch (k) {
    case 0x976f6445:
        cs.Load(0x8c509d6c, 0x555450a5, 0);
        break;
    case 0xb0ef13a6:
        cs.Load(0x8c509d6c, 0x555450a6, 0);
        break;
    }
    {
        u16* t = cs.GetText();
        u16* e = t;
        while (*e)
            e++;
        int n = (int)(e - t);
        ((WString*)((char*)this + 0x88))->Assign(t, t + n);
    }
    {
        int n = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        for (int i = 0; i < n; i++) {
            Timeline* c = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
            c->FUN_00e47460();
        }
    }
    cs.dtor();
}
