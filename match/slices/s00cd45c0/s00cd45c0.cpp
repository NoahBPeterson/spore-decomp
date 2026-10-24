// Slice s00cd45c0 -- SP::cTribeModeStrategy and its tribe-mode helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define NOINLINE __declspec(noinline)
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------
extern void*  g_crew;                                         // 0x0169b2c8  _spInstance_cTribeModeStrategy
extern void*  g_appProps;                                     // 0x015fd918
extern void*  g_propList881288;                               // 0x01581288
extern void*  g_testSystem;                                   // 0x015fd928
extern uint32_t g_arr157f528[];                               // 0x0157f528
extern uint32_t g_arr14774d8[];                               // 0x014774d8
extern uint8_t  g_157f524;                                    // 0x0157f524
extern uint8_t  g_157f525;                                    // 0x0157f525
extern float    g_169b2cc, g_169b2d0, g_169b2d4;              // 0x0169b2cc Vector3
extern const float g_1485548;                                 // 0x01485548  1.5f
extern const float g_14774d0;                                 // 0x014774d0  2500.0f
extern const float g_1485720;                                 // 0x01485720
extern void*  g_vt14774c4;                                    // 0x014774c4
extern const float g_13eb8b0;                                 // 0x013eb8b0  sign-mask

struct cString {                                              // SP::cString (8 bytes)
    uint32_t mData[2];                                        // +0x00
    cString();                                                // 0x006b5060
    ~cString();                                               // 0x006b5240
    char* Load(int a, int b, int c);                          // 0x006b54b0
    const void* Get(int a, int b);                            // 0x006b55c0
};
void          FUN_00e806de0(void* w);                         // 0x00806de0

// ---------------------------------------------------------------------------------------------
// External callees
// ---------------------------------------------------------------------------------------------
void*         NounManager();                                  // 0x00b3d300
void*         GetCameraCtl();                                 // 0x00b3d280
void*         App();                                          // 0x0067dd10
void*         GetGameTerrainCursor();                         // 0x00b30d70
void*         GameTimeManager();                              // 0x00b3d380
void          FUN_00d48ae0();                                 // 0x00d48ae0

void*         __stdcall FUN_00b3d240(int fn);                 // 0x00b3d240
void*         FUN_00b3d3c0();                                 // 0x00b3d3c0



void          FUN_00b16270(void* p);                          // 0x00b16270
void          FUN_00b13bb0(void* a, void* b);                 // 0x00b13bb0
void*         FUN_00b6f0c0(int a);                            // 0x00b6f0c0
void          FUN_00b6e4b0(void* out, float, float, float, float, float); // 0x00b6e4b0
void          FUN_00b6f140(float, float, float);              // 0x00b6f140
void          FUN_00b6f180();                                 // 0x00b6f180
uint32_t      FUN_00b316c0();                                 // 0x00b316c0 (superseded by CTimeMgr)
void*         __stdcall FUN_0067de90(int a, void* b);         // 0x0067de90
struct CExt7ec160 { void* FUN_007ec160(); };                  // 0x007ec160 (thiscall)
struct CTimeMgr  { uint64_t FUN_00b316c0(); };                // 0x00b316c0 (thiscall)
void          FUN_00cd0260(void* p);                          // 0x00cd0260
void          FUN_00cd3ff0(int idx, void* p);                 // 0x00cd3ff0
int           FUN_00700c80(float* a, float* b, float* c, float d, int e); // 0x00700c80
float*        __fastcall FUN_0041ea70(void* prop);             // 0x0041ea70
float*        __fastcall FUN_0041e920(void* prop);             // 0x0041e920
uint32_t      FUN_00458a40(void* p);                          // 0x00458a40
void*         FUN_00f473a0(int size, const char* tag, int b, int c, int d, int e); // 0x00f473a0  EAAllocate
struct CWinMgr { void* FindWindowByID(int id); };              // 0x00e012b0
void*         FUN_00920090();                                 // 0x00920090
void*         SimTicker();                                    // 0x00b3d330
void          cTribe_FishingRegister(void* tribe);            // 0x00c9b6d0
uint64_t      __stdcall __aulldiv(uint64_t a, uint64_t b);     // 0x011e0970

void*         FUN_00883860();                                 // 0x00883860  EA::Messaging::GetServer
void*         FUN_00fe0000(void* a, void* b);                 // (unused)
void*         FUN_00fe0010(void* a);                          // (unused)
void*         FUN_00fe0020();                                 // (unused)

// ---------------------------------------------------------------------------------------------
// __thiscall callees (self in ecx): declared as members of declaration-only stub structs so
// MSVC emits a plain ecx-based thiscall `call` with no push/add-esp at the call site.
// ---------------------------------------------------------------------------------------------
struct CActor {                                               // SP::cNearNoun-ish
    void*  FUN_00c6cbf0();                                    // 0x00c6cbf0
    void*  GetPosition();                                     // 0x00c6acc0
    void*  FUN_00c6bdc0();                                    // 0x00c6bdc0
    void   FUN_00c69ff0(void* p);                             // 0x00c69ff0
    void*  FUN_00c22f50();                                    // 0x00c22f50
    void*  FUN_00c8e820(int idx);                             // 0x00c8e820
    void*  FUN_00c93a40();                                    // 0x00c93a40
    char   FUN_00cd0260();                                    // 0x00cd0260
    float  FUN_00cee380();                                    // 0x00cee380
    void*  FUN_00ce6260(void* a, int b);                      // 0x00ce6260
    void*  FUN_00bfc5f0();                                    // 0x00bfc5f0 (GetPlayerTribe)
    void   FUN_00b16270();                                    // 0x00b16270
};

struct CSub {                                                 // track subobject (own vfptr; vcall slot 0x54/0xac)
    void*    mpVtbl;                                          // +0x00
    uint32_t m04;                                             // +0x04 (state flags)
    uint32_t pad08[(0x5c - 0x08) / 4];
    uint8_t  m5c;                                             // +0x5c (kind)
};

struct CListNode {                                            // list node with an embedded CSub at +0xc0
    uint32_t pad00[0xc0 / 4];
    CSub     mSub;                                            // +0xc0
};

struct CTrackNode {                                           // list node with an embedded CSub at +0x34
    uint32_t pad00[0x34 / 4];
    CSub     mSub;                                            // +0x34
};

struct CInfoBlock {                                           // result payload (0x1c bytes) of FUN_00cd52e0
    int      m00;                                             // +0x00
    int      m04;                                             // +0x04
    int      m08;                                             // +0x08
    float    m0c;                                             // +0x0c
    float    m10;                                             // +0x10
    float    m14;                                             // +0x14
    int      m18;                                             // +0x18
};

struct CRetObj {                                              // object returned by FUN_007ec160
    uint32_t   pad00[0xc / 4];
    CInfoBlock* mpInfo;                                       // +0x0c
    void       FUN_007eb820(int n);                           // 0x007eb820
};


// helper for the vtable-call idiom: fetch slot N of the object's vtable
#define VSLOT(p, off)  ((*(void***)(p))[(off) / 4])
#define VTHIS(p, off)  ((void*(__fastcall*)(void*))VSLOT(p, off))(p)
#define VTHIS1(p, off, a) ((void*(__thiscall*)(void*, int))VSLOT(p, off))(p, (int)(a))
#define VTHIS0(p, off) ((void*(__thiscall*)(void*))VSLOT(p, off))(p)

// __thiscall callee types (self in ecx, extra args pushed) -- reproduces MSVC's `push arg;
// call eax` virtual-call shape where the __fastcall cast would put the arg in edx instead.
typedef void*  (__thiscall *TC1)(void*, int);
typedef char   (__thiscall *TC1b)(void*, int);
typedef void   (__thiscall *TC1v)(void*, int);
typedef void*  (__thiscall *TC2v)(void*, int, void*);
typedef char   (__thiscall *TC2b)(void*, int, int*);
typedef void   (__thiscall *TC2vv)(void*, int, int);
typedef void   (__thiscall *TCCv)(void*, char*);
typedef void   (__thiscall *TCvi)(void*, void*, int);
typedef void*  (__thiscall *TC4)(void*, int, int, int, int);

// ---------------------------------------------------------------------------------------------
// Opaque external __thiscall callees. Declared as member functions (undefined externals) so
// MSVC emits a pure ecx-based thiscall `call` with no `xor edx,edx` padding at the call site.
// ---------------------------------------------------------------------------------------------
struct CTexPreload {                                          // 0x007b07e0
    void*  ctor(int a);                                       // 0x007b07e0
    void   clear();                                           // 0x007b1950
    void   preloadListVoid(void* a);                          // 0x007b1de0
    void   preloadListKey(void* a);                           // 0x007b1e90
};
struct CExt72880 { void* call(); };                           // 0x00b72880
struct CExt33ce0 { void* call(); };                           // 0x00b33ce0
struct cRefBase;
struct CRefHolder {                                           // cTribeViewHolder-ish
    void*     mpVtbl;                                         // +0x00
    void*     mp04;                                           // +0x04
    cRefBase* mp08;                                           // +0x08
    uint8_t   mb0c;                                           // +0x0c
    void* FUN_00cd4720(void* a, cRefBase* p);                 // 0x00cd4720
};
struct CIcon {                                                // tribe icon widget
    void FUN_00b13bb0(void* a);                               // 0x00b13bb0
    void FUN_00b16270();                                      // 0x00b16270
};
// cTribeModeStrategy: the FUN_* entries are its out-of-line members (self in ecx, `ret 4`).
struct CTribeMode {
    char FUN_00cd4c70(int a);                                 // 0x00cd4c70
    bool FUN_00cd54f0();                                      // 0x00cd54f0
    void FUN_00cd53e0();                                      // 0x00cd53e0
    void FUN_00cd50b0(int a, void* m);                        // 0x00cd50b0
};
struct CExt33cf0 { void* call(); };                           // 0x00b33cf0
struct CExtBC3170 { void call(); };                           // 0x00bc3170
struct CExtF67D90 { void* call(); };                          // 0x00f67d90
void*         __fastcall FUN_00f67d90(void* self, int);       // 0x00f67d90
struct CDisplayStrategy {                                     // SP::cTribeDisplayStrategy
    void  attach(void* a);                                    // 0x00ccc400
    void  SetNestIcon(void* icon, int b);                     // 0x00cc9640
    void  detach(void* a);                                    // 0x00ccbb60
};

// Object whose virtual slot +0x0c is a get-by-id returning a pointer (pointer-to-member idiom,
// so MSVC emits the __thiscall form `mov eax,[ecx]; mov edx,[eax+0xc]; push id; call edx`).
struct CIdLookup {
    virtual void  v00();                                      // +0x00
    virtual void  v04();                                      // +0x04
    virtual void  v08();                                      // +0x08
    virtual void* get(int id);                                // +0x0c
};

// ---------------------------------------------------------------------------------------------
// cRefBase -- object with AddRef()/Release()
// ---------------------------------------------------------------------------------------------
struct cRefBase {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};

struct PtrHolder {
    void* mp00;
    uint32_t pad04[(0x40 - 0x04) / 4];
    void** mpBegin;                                           // +0x40
    void** mpEnd;                                             // +0x44
};

struct IRefVec {                                              // begin/end int*
    int* mpBegin;
    int* mpEnd;
};

struct cTribeView {
    uint32_t pad00[(0x120) / 4];
    void*    mpSphere;                                        // +0x120
};

struct TerrainSphereView {
    float f10f0;                                              // +0x10f0
    float f10f4;                                              // +0x10f4
};

// ---------------------------------------------------------------------------------------------
// cTribeModeStrategy
// ---------------------------------------------------------------------------------------------
struct cTribeModeStrategy {
    uint32_t pad00[(0x68) / 4];
    void*    mpGridBegin;                                     // +0x68
    uint32_t pad6c;
    void*    mpGridEnd;                                       // +0x6c
    uint32_t pad70[(0x80 - 0x70) / 4];
    int      mDirtyFlag;                                      // +0x80
    uint8_t  pad84[(0x1a8 - 0x84)];
    uint32_t m1a8;                                            // +0x1a8
    uint32_t pad1ac[(0x1cc - 0x1ac) / 4];
    void*    mp1cc;                                           // +0x1cc
    void*    mp1d0;                                           // +0x1d0
    void*    mp1d4;                                           // +0x1d4
    void*    mp1d8;                                           // +0x1d8
    uint32_t m1dc;                                            // +0x1dc
    uint32_t pad1e0[(0x230 - 0x1e0) / 4];
    void*    mp230;                                           // +0x230
    void*    mp234;                                           // +0x234
    uint32_t pad238[(0x240 - 0x238) / 4];
    void*    mp240;                                           // +0x240
    uint8_t  mb249;                                           // +0x249
    uint8_t  mb24a;                                           // +0x24a
    uint32_t pad24b;
    void*    mp250;                                           // +0x250
    void*    mp254;                                           // +0x254
    uint32_t m258;                                            // +0x258
    uint32_t m25c;                                            // +0x25c
    uint32_t pad260[(0x2fc - 0x260) / 4];
    uint32_t m2fc;                                            // +0x2fc
    uint8_t  pad300[(0x3a1 - 0x300)];
    uint8_t  mb3a1;                                           // +0x3a1
    uint8_t  mb3a2;                                           // +0x3a2
};

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

// @ 0x00cd45c0
NOINLINE void FUN_00cd45c0(char* self, int flags)
{
    if (!self)
        return;
    VTHIS1(self, 0x28, flags);
    char* child = (char*)VTHIS1(self, 0xb8, 0x17f243b);
    char* node = (char*)VTHIS1(g_crew, 0x70, child);
    char al = ((CActor*)node)->FUN_00cd0260();
    char bl = al & (char)flags;
    CSub* sel = (CSub*)VTHIS(self, 0xac);
    if (!sel)
        return;
    if (bl) {
        sel->m04 |= 8;
        sel->m5c = (uint8_t)((self[0x6e] == 0) ? 2 : 1);
    } else {
        sel->m04 &= 0xfffffff7u;
    }
    if (!child)
        return;
    if ((*(int(__thiscall**)(char*))(*(int*)child + 0x20))(child) != 0x629bafe)
        return;
    void** vec = *(void***)(child + 0x10c);
    if (!vec)
        return;
    void** it = *(void***)((char*)vec + 0x210);
    void** end = *(void***)((char*)vec + 0x214);
    if (it == end)
        return;
    do {
        CTrackNode* n = (CTrackNode*)*it;
        CSub* s = &n->mSub;
        if (VTHIS0(s, 0xac)) {
            CSub* t = (CSub*)VTHIS0(s, 0xac);
            t->m5c = sel->m5c;
            CSub* q = (CSub*)VTHIS0(s, 0xac);
            uint32_t* pf = &q->m04;
            if (bl)
                *pf |= 8;
            else
                *pf &= 0xfffffff7u;
        }
        ++it;
    } while (it != end);
}

// @ 0x00cd46d0
NOINLINE bool FUN_00cd46d0(void** self)
{
    int* dp = *(int**)((char*)self[0] + 0x64);
    if (dp) {
        int* child = (int*)((TC1)VSLOT(dp, 0x0c))(dp, 0x17f243b);
        if (child && (*(int(__fastcall**)(int*))(*(int*)child + 0x20))(child) == 0x2e72cae) {
            int* sub = *(int**)((char*)child + 0x24c);
            if (sub && (*(int(__fastcall**)(int*))(*(int*)sub + 0x20))(sub) == 0x18ebadc)
                return false;
        }
    }
    return true;
}

// @ 0x00cd4720
void* CRefHolder::FUN_00cd4720(void* a, cRefBase* p)
{
    mpVtbl = &g_vt14774c4;
    mp08 = 0;
    mp04 = a;
    cRefBase* old = *(cRefBase* volatile*)&mp08;
    if (p != old) {
        if (p)
            p->AddRef();
        mp08 = p;
        if (old)
            old->Release();
    }
    mb0c = 0;
    return this;
}

// @ 0x00cd49a0
NOINLINE void FUN_00cd49a0()
{
    FUN_00d48ae0();
    int* pi = *(int**)((char*)g_crew + 0x19c);
    if (pi) {
        *(void**)((char*)g_crew + 0x19c) = 0;
        (*(void(__fastcall**)(int*))(*(int*)pi + 4))(pi);
    }
}

// @ 0x00cd4b70
NOINLINE void __fastcall FUN_00cd4b70(char* self, int, int v)
{
    void* cam = GetCameraCtl();
    char b;
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        b = 0;
    else
        b = (char)v;
    self[0x24a] = b;
    if (!b) {
        cRefBase* p = *(cRefBase**)(self + 0x250);
        if (p) {
            *(void**)(self + 0x250) = 0;
            p->Release();
        }
    }
}

// @ 0x00cd4bc0
NOINLINE void __fastcall FUN_00cd4bc0(char* self, int, char v)
{
    void* cam = GetCameraCtl();
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        v = 0;
    self[0x249] = v;
    if (!v)
        return;
    char* tribe = (char*)((CActor*)NounManager())->FUN_00bfc5f0();
    void* ui = App();
    ui = (*(void*(__fastcall**)(void*))(*(int*)ui + 0x50))(ui);
    ui = ((TC1)VSLOT(ui, 0x40))(ui, 0xe3057616);
    if (!ui)
        return;
    char* icon = (char*)((TC1)VSLOT(ui, 0x0c))(ui, 0x11966ed);
    if (!icon || !tribe)
        return;
    void* sp = ((TC1)VSLOT(tribe + 0x120, 0x2c))(tribe + 0x120, 0);
    ((CIcon*)icon)->FUN_00b13bb0(sp);
    if (g_157f524 && !icon[0x168])
        ((CIcon*)icon)->FUN_00b16270();
}

// @ 0x00cd4d50
NOINLINE char __fastcall FUN_00cd4d50(char* self, int)
{
    void* a = FUN_00b3d3c0();
    ((CExt72880*)a)->call();
    void* c = FUN_00b3d240(0xcd45c0);
    ((CExt33ce0*)c)->call();
    void* d = FUN_00b3d240(0xcd46d0);
    ((CExt33cf0*)d)->call();
    ((CExtBC3170*)(self + 0x1a8))->call();
    return 1;
}

// @ 0x00cd4d90
void __stdcall FUN_00cd4d90(void* a)
{
    char* tribe = (char*)a;
    void* o = FUN_00920090();
    char* obj = (char*)((TC4)VSLOT(o, 0x20))(o, 0x3098af98, 0x9098aeb2, 0, 0);
    ((CActor*)obj)->FUN_00ce6260(a, 0);
    char* old = *(char**)(tribe + 0x290);
    if (obj != old) {
        if (obj)
            (*(void(__fastcall**)(char*))(*(int*)obj + 4))(obj);
        *(char**)(tribe + 0x290) = obj;
        if (old)
            (*(void(__fastcall**)(char*))(*(int*)old + 8))(old);
    }
    void* ticker = SimTicker();
    ((TCCv)VSLOT(ticker, 0x50))(ticker, obj);
    cTribe_FishingRegister(tribe);
}

// @ 0x00cd4f90
NOINLINE void FUN_00cd4f90()
{
    if (!((CActor*)NounManager())->FUN_00bfc5f0())
        return;
    char* tribe = (char*)((CActor*)NounManager())->FUN_00bfc5f0();
    int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)tribe + 0x90))(tribe);
    int** it = (int**)v[0];
    if (it != (int**)v[1]) {
        do {
            CListNode* a = (CListNode*)*it;
            ((TC1v)VSLOT(&a->mSub, 0x54))(&a->mSub, 0);
            ++it;
        } while (it != (int**)v[1]);
    }
    void* c1 = GetGameTerrainCursor();
    (*(void(__fastcall**)(void*))(*(int*)c1 + 0x74))(c1);
    void* c2 = GetGameTerrainCursor();
    (*(void(__fastcall**)(void*))(*(int*)c2 + 0xc8))(c2);
}

// @ 0x00cd5010
NOINLINE void __fastcall FUN_00cd5010(char* self, int, char* obj)
{
    if (!*(void**)(self + 0x240))
        return;
    if (!obj)
        return;
    char* a = (char*)((CIdLookup*)obj)->get(0x4f176642);
    if (a) {
        ((CDisplayStrategy*)*(void**)(self + 0x240))->attach(a);
        return;
    }
    char* b = (char*)((CIdLookup*)obj)->get(0x1b92b27);
    if (b)
        ((CDisplayStrategy*)*(void**)(self + 0x240))->SetNestIcon(b, 1);
}

// @ 0x00cd5070
NOINLINE void __fastcall FUN_00cd5070(char* self, int, char* obj)
{
    if (!*(void**)(self + 0x240))
        return;
    if (!obj)
        return;
    char* a = (char*)((CIdLookup*)obj)->get(0x4f176642);
    if (a)
        ((CDisplayStrategy*)*(void**)(self + 0x240))->detach(a);
}

// @ 0x00cd50b0
NOINLINE void CTribeMode::FUN_00cd50b0(int, void* memberv)
{
    char* self = (char*)this;
    char* member = (char*)memberv;
    void* cam = GetCameraCtl();
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        return;
    if (!member)
        return;
    if (!((CActor*)member)->FUN_00c22f50())
        return;
    char* tribe = (char*)((CActor*)member)->FUN_00c22f50();
    int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)tribe + 0x90))(tribe);
    int n = (int)((v[1] - v[0]) >> 2);
    if (n <= 0)
        return;
    for (int i = 0; i < n; ++i) {
        if ((char*)((int*)v[0])[i] != member)
            continue;
        *(uint32_t*)((char*)g_crew + 0x2fc) = (uint32_t)i;
        void* ui = App();
        ui = (*(void*(__fastcall**)(void*))(*(int*)ui + 0x50))(ui);
        ui = ((TC1)VSLOT(ui, 0x40))(ui, 0xe3057616);
        if (ui) {
            char* icon = (char*)((TC1)VSLOT(ui, 0x0c))(ui, 0x11966ed);
            if (icon) {
                void* sp = ((TC1)VSLOT(member + 0xc0, 0x2c))(member + 0xc0, 0);
                ((CIcon*)icon)->FUN_00b13bb0(sp);
                if (g_157f525 && !icon[0x168])
                    ((CIcon*)icon)->FUN_00b16270();
            }
        }
        cRefBase* old = *(cRefBase**)(self + 0x250);
        if ((char*)old != member) {
            (*(void(__fastcall**)(char*))(*(int*)member))(member);
            *(char**)(self + 0x250) = member;
            if (old)
                old->Release();
        }
        FUN_00cd4b70((char*)g_crew, 0, 1);
    }
}

// @ 0x00cd54c0
NOINLINE void __fastcall FUN_00cd54c0(char* self, int)
{
    cRefBase* p = *(cRefBase**)(self + 0x254);
    if (!p)
        return;
    ((CTexPreload*)p)->clear();
    p = *(cRefBase**)(self + 0x254);
    if (!p)
        return;
    *(void**)(self + 0x254) = 0;
    p->Release();
}

// @ 0x00cd4770
NOINLINE int FUN_00cd4770(char* self, void* other)
{
    if ((*(char(__fastcall**)(char*))(*(int*)self + 0x2c))(self))
        return 0;
    ((CActor*)self)->FUN_00c6cbf0();
    {
        char* od = (char*)other;
        float f1 = (*(float(__fastcall**)(char*))(*(int*)od + 0x60))(od) * g_1485548;
        float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(od + 0x120) + 0x2c))(od + 0x120);
        float* pf6 = (float*)((CActor*)self)->GetPosition();
        float* pf7 = (float*)((CActor*)self)->FUN_00c6bdc0();
        if ((pf7[0] != g_169b2cc || pf7[1] != g_169b2d0 || pf7[2] != g_169b2d4) &&
            FUN_00700c80(pf6, pf7, pf5, f1, 0))
            ((CActor*)self)->FUN_00c69ff0(&g_169b2cc);
        unsigned int kept = 0;
        if (((*(int*)(self + 0x6c) - *(int*)(self + 0x68)) / 0xc) != 0) {
            int off = 0;
            for (;;) {
                float* pp = (float*)(*(int*)(self + 0x68) + off);
                float d0 = pp[0] - pf6[0];
                float d1 = pp[1] - pf6[1];
                float d2 = pp[2] - pf6[2];
                float e0 = pf6[0] - pf5[0];
                float e1 = pf6[1] - pf5[1];
                float e2 = pf6[2] - pf5[2];
                float b = (d0 * e0 + d2 * e2) + d1 * e1;
                float aa = (d0 * d0 + d2 * d2) + d1 * d1;
                float cc = ((e0 * e0 + e2 * e2) + e1 * e1) - f1 * f1;
                float disc = b * b - cc * aa;
                float sq;
                if (disc < 0.0f || (sq = (float)sqrt((double)disc)) - b < 0.0f ||
                    aa < -b - sq) {
                    ++kept;
                    off += 0xc;
                } else {
                    int last = *(int*)(self + 0x6c);
                    pp[0] = *(float*)(last - 0xc);
                    pp[1] = *(float*)(last - 8);
                    pp[2] = *(float*)(last - 4);
                    *(int*)(self + 0x6c) = last - 0xc;
                    *(int*)(self + 0x80) = -1;
                }
                if (kept >= (unsigned int)((*(int*)(self + 0x6c) - *(int*)(self + 0x68)) / 0xc))
                    break;
            }
        }
    }
    return 0;
}

// @ 0x00cd49d0
NOINLINE void FUN_00cd49d0(char* a, char* b, char* src)
{
    if (!src)
        return;
    if (!(*(int(__fastcall**)(char*))(*(int*)src + 8))(src))
        return;
    if (!a) {
        if (!b)
            return;
        int* v = (int*)(b + 0x40);
        int* it = (int*)v[0];
        if (it == (int*)v[1])
            return;
        int n = 0;
        do {
            int obj = *it;
            char* sp = (char*)(*(void*(__fastcall**)(char*))(*(int*)src + 8))(src);
            float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)sp + 0x2c))(sp);
            float* pf6 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(obj + 0xc0) + 0x2c))((char*)obj + 0xc0);
            float e0 = pf6[0] - pf5[0];
            float e1 = pf6[1] - pf5[1];
            float e2 = pf6[2] - pf5[2];
            float d = (e1 * e1 + e2 * e2) + e0 * e0;
            if (!(d > g_14774d0)) {
                FUN_00cd3ff0(n, (void*)(obj + 0xc0));
                ++n;
            }
            ++it;
        } while (it != (int*)v[1]);
        return;
    }
    {
        int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)a + 0x90))(a);
        int* it = (int*)v[0];
        if (it == (int*)v[1])
            return;
        int n = 0;
        do {
            int obj = *it;
            char* sp = (char*)(*(void*(__fastcall**)(char*))(*(int*)src + 8))(src);
            float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)sp + 0x2c))(sp);
            float* pf6 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(obj + 0xc0) + 0x2c))((char*)obj + 0xc0);
            float e0 = pf6[0] - pf5[0];
            float e1 = pf6[1] - pf5[1];
            float e2 = pf6[2] - pf5[2];
            float d = (e1 * e1 + e2 * e2) + e0 * e0;
            if (!(d > g_14774d0)) {
                FUN_00cd3ff0(n, (void*)(obj + 0xc0));
                ++n;
            }
            ++it;
        } while (it != (int*)v[1]);
    }
}

// @ 0x00cd4c70
char CTribeMode::FUN_00cd4c70(int)
{
    char* self = (char*)this;
    void* app = App();
    app = (*(void*(__fastcall**)(void*))(*(int*)app + 0x50))(app);
    ((TC2v)VSLOT(app, 0x20))(app, 0x4c6a8d6, (void*)0xbc36d0);
    void* server = FUN_00883860();
    void* h = self ? (void*)(self + 8) : 0;
    *(void**)(self + 0x1cc) = server;
    *(void**)(self + 0x1d0) = h;
    *(void**)(self + 0x1d4) = &g_arr14774d8;
    *(uint32_t*)(self + 0x1d8) = 0x15;
    *(uint32_t*)(self + 0x1dc) = 0;
    if (server && h) {
        unsigned int i = 0;
        do {
            int v = *(uint32_t*)((char*)g_arr14774d8 + i);
            ((TCvi)VSLOT(server, 0x24))(server, h, v);
            i += 4;
        } while (i < 0x54);
    }
    if (g_appProps) {
        int st;
        if (((TC2b)VSLOT(g_appProps, 0x24))(g_appProps, 0x64a44a8, &st)) {
            if (*(short*)(st + 0x12) == 1)
                self[0x3a1] = *(char*)FUN_0041e920((void*)st);
        }
    }
    self[0x3a2] = 0;
    return 1;
}

// @ 0x00cd4e10
NOINLINE void FUN_00cd4e10()
{
    char* tribe = (char*)((CActor*)NounManager())->FUN_00bfc5f0();
    if (!tribe)
        return;
    float f1 = 0.0f, f2 = 0.0f;
    if (g_propList881288) {
        int st = 0;
        if ((*(char(__fastcall**)(void*, int, int*))(*(int*)g_propList881288 + 0x24))(g_propList881288, 0xc899522, &st)) {
            if (*(short*)(st + 0x12) == 0xd)
                f1 = *(float*)FUN_0041ea70((void*)st);
        }
    }
    if (g_propList881288) {
        int st = 0;
        if ((*(char(__fastcall**)(void*, int, int*))(*(int*)g_propList881288 + 0x24))(g_propList881288, 0x91d15b, &st)) {
            if (*(short*)(st + 0x12) == 0xd)
                f2 = *(float*)FUN_0041ea70((void*)st);
        }
    }
    char* slot = (char*)((CActor*)tribe)->FUN_00c8e820(0);
    float x = *(float*)(slot + 0x4ec);
    float y = *(float*)(slot + 0x4f0);
    float z = *(float*)(slot + 0x4f4);
    float out[3];
    FUN_00b6e4b0(out, x, y, z, f1, f2);
    FUN_00b6f140(out[0], out[1], out[2]);
    FUN_00b6f180();
    *(uint32_t*)(tribe + 0x234) = 0x53dbcf1;
    ((CActor*)tribe)->FUN_00c93a40();
    *(float*)(tribe + 0x254) = out[0];
    *(float*)(tribe + 0x258) = out[1];
    *(float*)(tribe + 0x25c) = out[2];
}

// @ 0x00cd5200
NOINLINE void FUN_00cd5200()
{
    char* ui = (char*)(*(void*(__fastcall**)(void*))(*(int*)g_crew + 0x6c))(g_crew);
    char* w1;
    {
        void* w = ((CWinMgr*)*(void**)(ui + 0x4c))->FindWindowByID(0x562a141);
        w1 = w ? (char*)(*(void*(__thiscall**)(void*, int))(*(int*)w + 0x0c))(w, 0x8ed27e7a) : 0;
    }
    char* w2;
    {
        void* w = ((CWinMgr*)*(void**)(ui + 0x4c))->FindWindowByID(0x562a0f7);
        w2 = w ? (char*)(*(void*(__thiscall**)(void*, int))(*(int*)w + 0x0c))(w, 0x8ed27e7a) : 0;
    }
    cString str;
    char al = (char)(*(int(__thiscall**)(char*))(*(int*)w1 + 0x20))(w1);
    int key;
    if ((al & 4) != 0) {
        (*(void(__thiscall**)(char*, int, int))(*(int*)w2 + 0x28))(w2, 4, 1);
        key = 0x615ffa8;
    } else {
        (*(void(__thiscall**)(char*, int, int))(*(int*)w2 + 0x28))(w2, 4, 0);
        key = 0x615ffa7;
    }
    str.Load(0xc0152a6d, key, 0);
    const void* txt = str.Get(-1, 1);
    char* w = (char*)(*(void*(__thiscall**)(char*, void*))(*(int*)w1 + 0x10))(w1, (void*)txt);
    FUN_00e806de0((void*)w);
}

// @ 0x00cd52e0
NOINLINE void* __stdcall FUN_00cd52e0(void* a, float b, float c, float d)
{
    void* result = 0;
    char* tr = (char*)((CActor*)NounManager())->FUN_00bfc5f0();
    if (tr) {
        CRetObj* r = (CRetObj*)((CExt7ec160*)FUN_0067de90(2, a))->FUN_007ec160();
        result = r;
        if (r) {
            r->FUN_007eb820(7);
            uint64_t t = ((CTimeMgr*)GameTimeManager())->FUN_00b316c0();
            r->mpInfo->m00 = (int)__aulldiv(t, 1000);
            r->mpInfo->m04 = (*(int(__fastcall**)(char*))(*(int*)tr + 0x74))(tr);
            float sp = ((CActor*)(tr + 0x20c))->FUN_00cee380();
            r->mpInfo->m08 = (uint32_t)sp;
            r->mpInfo->m0c = b;
            r->mpInfo->m10 = c;
            r->mpInfo->m14 = d;
            r->mpInfo->m18 = (int)FUN_00458a40(FUN_00b6f0c0(*(int*)(tr + 0x234)));
        }
    }
    return result;
}

// @ 0x00cd53e0
NOINLINE void CTribeMode::FUN_00cd53e0()
{
    char* self = (char*)this;
    if (((!g_testSystem || *(void**)((char*)g_testSystem + 0x70) == (char*)g_testSystem + 0x70) ||
         *(void**)(self + 0x230) != (void*)0x1654c08) &&
        *(void**)(self + 0x254) == 0) {
        void* p = FUN_00f473a0(0x34, "Simulator", 0, 0, 0, 0);
        void* tp = p ? (void*)((CTexPreload*)p)->ctor(-1) : 0;
        void* old = *(void**)(self + 0x254);
        if (tp != old) {
            if (tp)
                (*(void(__fastcall**)(void*))(*(int*)tp))(tp);
            *(void**)(self + 0x254) = tp;
            if (old)
                (*(void(__fastcall**)(void*))(*(int*)old + 4))(old);
        }
        ((CTexPreload*)*(void**)(self + 0x254))->preloadListVoid(g_propList881288);
        uint32_t keybuf[3];
        keybuf[1] = 0xefbda3ff;
        keybuf[2] = 0x40464100;
        uint32_t i = 0;
        do {
            keybuf[0] = *(uint32_t*)((char*)g_arr157f528 + i);
            ((CTexPreload*)*(void**)(self + 0x254))->preloadListKey(keybuf);
            i += 4;
        } while (i < 0x58);
    }
}

// @ 0x00cd54f0
NOINLINE bool CTribeMode::FUN_00cd54f0()
{
    char* self = (char*)this;
    char* sp = (char*)((CExtF67D90*)NounManager())->call();
    if (!sp || *(int*)(self + 0x40) == *(int*)(self + 0x44))
        return false;
    float* a = (float*)(sp + 0x10f0);
    float* b = (float*)(sp + 0x10f4);
    float* large = a;
    if (*a > *b)
        large = b;
    if (*large / *b < g_1485720)
        return 0;
    return 1;
}
