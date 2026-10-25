// Slice s00ee3800 -- 0x00ee3800..0x00ee41e0  (/O2 /MD /Gy /TP /fp:fast)
//
// More scenario-edit-mode behaviour UI handlers (same editor object as
// slices s00edcfc0 / s00ee2860).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int   DAT_0148a9c8[];
extern u32   DAT_0148a960[];                                            // 5 UI column ids

struct Mgrs;
struct Ctl;
struct L18;
struct L48;
struct Bee;
struct Hee;

struct Editor {
    char  pad00[0x74];
    Mgrs* mpMgr;                                                        // +0x74
    char  pad78[0xd4 - 0x78];
    Ctl*  mpCtl;                                                        // +0xd4
};
extern Editor* DAT_016c7aa4;

#define MGR()  (DAT_016c7aa4->mpMgr)
#define CTL()  (DAT_016c7aa4->mpCtl)

struct Ctl {
    bool IsBusy();                                                      // 0x00ef72a0
    void Notify(int, int);                                              // 0x00efbbe0
};

struct Mgrs {
    char pad00[0x10];
    int  f10;
    int  F3be60(int);                                                   // 0x00f3be60
    int  F45970();                                                      // 0x00f45970
    int  F45a80();                                                      // 0x00f45a80
    int  F427c0();                                                      // 0x00f427c0
    int  F3be30();                                                      // 0x00f3be30
    bool F3c750(void*, int);                                            // 0x00f3c750 (ret 8)
    bool F420d0(int, void*, int, int, int);                             // 0x00f420d0 (ret 0x14)
    int  F3e8a0(int);                                                   // 0x00f3e8a0 (ret 4)
    bool F40500(void*, int, int);                                       // 0x00f40500 (ret 0xc)
    bool F3e6d0(int, void*, int, int);                                  // 0x00f3e6d0 (ret 0x10)
};

// Object returned by Mgrs::F3e8a0 (the current selection).
struct SelObj {
    bool F25490();                                                      // 0x00f25490
    bool F25670();                                                      // 0x00f25670
};

// Stack selection context (ctor 0x00f2bd10, dtor 0x00dfbb60).
struct SelCtx {
    uint32_t pad[0x188 / 4];                                            // uint32_t pad: no /GS cookie
    SelCtx();                                                           // 0x00f2bd10
    ~SelCtx();                                                          // 0x00dfbb60
};

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))             VTP(p)[(off)/4])((void*)(p)))
#define VCP1(p,off,a)   (((void*(__thiscall*)(void*,int))         VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))     VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC5(p,off,a,b,c,d,e) (((int (__thiscall*)(void*,int,int,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d),(int)(e)))

struct L18 {
    char pad[4];
    void F3630(int);                                                    // 0x00ee3630
    void FCD30(int);                                                    // 0x00edcd30
    void F30D0();                                                       // 0x00ee30d0
    void F3710(int);                                                    // 0x00ee3710
};
struct L48 { char pad[4]; void FBDD0(int); void FBD30(int); };

extern "C" int  FUN_00efc8f0();
extern "C" void FUN_00edd810();
extern "C" int  FUN_00efc520();
extern "C" int  FUN_00efe5b0();
extern "C" int  FUN_00f3e8a0(int, int);
extern "C" int  FUN_00efc8c0(int);
extern "C" void* SP_MessageServer();
extern "C" int  FUN_00f25490();
extern "C" int  FUN_00f25670();
extern "C" void  EA_Messaging_RemoveHandler(int, int, int, int, int);
extern "C" int  FUN_00edcd30(int);
extern "C" void  FUN_00edbdd0();
extern "C" void  FUN_00edd310(void*, int, int);                      // 0x00edd310 (cdecl, 3 args)
extern "C" int   FUN_00eece20(int);                                  // 0x00eece20 (cdecl, 1 arg)

extern "C" void* FUN_0067caa0();                                     // WindowManager
extern "C" void* FUN_0067cac0();                                     // UIManager
extern "C" void* FUN_0080fee0();                                     // global at 0x0164cf5c
extern "C" void* FUN_00f473a0(int, const char*, int, int, int, int); // operator new
extern "C" void  FUN_00f47380(void*);                                // operator delete[]
extern "C" void  FUN_00dfd020();                                     // (declared as member below)
extern "C" void  FUN_00ee2860(void*, int, void*);                    // cdecl, 3 args
extern "C" void  FUN_00ee3230(void);                                 // handler callback address

// ------------------------------------------------------------ small helpers
struct Sub4 { void Destroy(); };                                        // 0x00f280f0

struct cString {                                                        // 0x14 bytes
    char pad[0x14];
    cString();                                                          // 0x006b5060
    ~cString();                                                         // 0x006b5240
};

struct UIMgr {
    void Select(int, int);                                             // 0x0067c8c0 (ret 8)
    void Show(int);                                                    // 0x0067c830 (ret 4)
};

struct LayoutObj {                                                      // 0x18-byte UI layout node
    LayoutObj* Ctor();                                                 // 0x00810000
    void Setup(int, int, int);                                         // 0x008120d0 (ret 0xc)
    LayoutObj* Child(int, int);                                        // 0x008105b0 (ret 8)
};

struct Global164 {
    LayoutObj* Get(int);                                               // 0x00810620 (ret 4)
};

struct Obj84 {                                                          // 0x84-byte script object
    Obj84* Ctor();                                                     // 0x00edeb20
    void Bind(void*);                                                  // 0x00edec50 (ret 4)
};
struct Obj50 {                                                          // 0x50-byte acts-bar object
    Obj50* Ctor();                                                     // 0x00edbe00
    void Bind(void*);                                                  // 0x00edbac0 (ret 4)
};
struct ObjC8 {                                                          // 0xc8-byte behaviour object
    ObjC8* Ctor();                                                     // 0x0081a1f0
    void SetHandlers(int, void*);                                      // 0x00817eb0 (ret 8)
};
struct ObjC0 { void* mpVtbl0; void* mpVtbl1; u32 m8; };

struct VecMgr {                                                         // embedded at Bee+0x4c
    char  pad[0x70];
    void  Init(void*, void*);                                          // 0x00e0a4c0 (ret 8)
    void  AddColumn(int, int);                                         // 0x00e0a780 (ret 8)
    int   Count();                                                     // 0x00e09c80
    void* At(int);                                                     // 0x00e09c90 (ret 4)
};

struct Bee {
    char    pad00[0x18];
    void*   mp18;                                                       // +0x18
    void*   mp1c;                                                       // +0x1c
    void*   mp20;                                                       // +0x20
    void*   mp24;                                                       // +0x24
    void*   mp28;                                                       // +0x28
    char    pad2c[0x40 - 0x2c];
    LayoutObj* mp40;                                                    // +0x40
    LayoutObj* mp44;                                                    // +0x44
    void*   mp48;                                                       // +0x48
    VecMgr  mVec;                                                       // +0x4c
    ObjC8*  mpBC;                                                       // +0xbc
    ObjC0*  mpC0;                                                       // +0xc0
    u8      mC4;                                                        // +0xc4
    u8      mC5;                                                        // +0xc5
    char    padC6[0xf0 - 0xc6];
    int     mF0;                                                        // +0xf0
    int     mF4;                                                        // +0xf4
    int     mF8;                                                        // +0xf8
    int     mFC;                                                        // +0xfc
    int     m100;                                                       // +0x100

    void F3E40(char);
    void F3F20(int);
    bool F3940();
    void F40F0();
    void F12C0();                                                       // 0x00ee12c0
    void F31D0();                                                       // 0x00ee31d0
    void RebuildLists();                                                // 0x00edda20
    void ApplyPick(void*);                                              // 0x00eddc50
};

// Message-handler subobject sitting at Bee+0x10.
struct Hee {
    char  pad00[8];
    L18*  mp18;                                                         // this+8  (= Bee+0x18)
    char  pad0c[0xb4 - 0x0c];
    u8    mC4;                                                          // this+0xb4 (= Bee+0xc4)
    char  padB5[0x300];
    bool  F3F60(int, void*);                                            // 0x00ee3f60 (ret 8)
};

// ============================================================ 0x00ee3f20
// @ 0x00ee3f20
void Bee::F3F20(int param)
{
    char* t = (char*)this;
    ((L18*)*(void**)(t + 0x18))->F3630(param);
    ((L48*)*(void**)(t + 0x48))->FBDD0(param);
    void* p24 = *(void**)(t + 0x24);
    if (p24 != 0)
        ((int(__thiscall*)(void*,int,bool))VTP(p24)[0x7c/4])(p24, 2, *(char*)(t + 0xc5) == 0);
}

// ============================================================ 0x00ee3e40
// @ 0x00ee3e40
void Bee::F3E40(char param)
{
    char* t = (char*)this;
    int ebx = (int)param;
    if (param == 0) {
        FUN_00edd810();
        int h = *(int*)(t + 0xf0);
        if (h != 0) {
            *(int*)(t + 0xf0) = 0;
            EA_Messaging_RemoveHandler(h, *(int*)(t + 0xf4), *(int*)(t + 0xf8), *(int*)(t + 0xfc), *(int*)(t + 0x100));
        }
        ((L18*)*(void**)(t + 0x18))->F30D0();
    } else {
        int b2 = (this != 0) ? (int)(t + 0x10) : 0;
        void* ms = SP_MessageServer();
        *(void**)(t + 0xf0) = ms;
        *(int*)(t + 0xf4) = b2;
        *(void**)(t + 0xf8) = (void*)DAT_0148a9c8;
        *(int*)(t + 0xfc) = 10;
        *(int*)(t + 0x100) = 0;
        if (ms != 0 && b2 != 0) {
            for (unsigned u = 0; u < 0x28; u += 4)
                VC2(ms, 0x24, b2, *(int*)((char*)DAT_0148a9c8 + u));
        }
        F31D0();
    }
    ((L18*)*(void**)(t + 0x18))->FCD30(ebx);
    ((L48*)*(void**)(t + 0x48))->FBD30(ebx);
    *(char*)(t + 0xc4) = param;
}

// ============================================================ 0x00ee3800
// @ 0x00ee3800
bool __cdecl f00ee3800(int a1, int a2, int a3, int a4)
{
    bool ok = false;

    int* state = (int*)FUN_00efc8f0();
    if (state != 0) {
        uint32_t flags = (uint32_t)state[0x224 / 4];
        if ((flags & 0x10) != 0 || (flags & 0x2) != 0 || (flags & 0x4) != 0)
            return false;
    }

    Mgrs* mgr = MGR();

    if (a3 != 0) {
        SelCtx ctx;
        FUN_00edd310(&ctx, a3, a1);
        if (mgr->F3c750(&ctx, -1))
            return false;
        if (mgr->F420d0(FUN_00efc520(), &ctx, a4, 0, 0))
            return false;
    }

    SelObj* obj = (SelObj*)mgr->F3e8a0(a1);
    if (a2 != 0x867a9ee9) {
        if (obj == 0)
            goto done;
        if (FUN_00eece20((int)obj) != a2)
            goto done;
    }
    if (obj != 0 && !obj->F25490())
        return false;
    ok = true;
    if (obj == 0)
        goto done;
    uint8_t* entry = (uint8_t*)(*(int*)((char*)obj + 0x70) + FUN_00efc520() * 0x4e0);
    if (entry[0] == 0)
        return false;
    if (entry[2] == 0)
        goto done;
    if (obj->F25670())
        goto done;
    return false;

done:
    return ok;
}

// ============================================================ 0x00ee3940

template <int NEWIDX, int OLDIDX, class T>
static __forceinline void SpSet(T** slot, T* p)
{
    T* old = *slot;
    if (p == old)
        return;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[NEWIDX])(p);
    }
    *slot = p;
    if (old) {
        void** vt = *(void***)old;
        ((void(__thiscall*)(void*))vt[OLDIDX])(old);
    }
}

// subobject-at-+4 flavour: the ref-count interface hangs off the object's +4.
static __forceinline void SpSetC(void** slot, void* p)
{
    void* old = *slot;
    if (p == old)
        return;
    if (p) {
        void** vt = *(void***)((char*)p + 4);
        ((void(__thiscall*)(void*))vt[1])((char*)p + 4);
    }
    *slot = p;
    if (old) {
        void** vt = *(void***)((char*)old + 4);
        ((void(__thiscall*)(void*))vt[2])((char*)old + 4);
    }
}

// @ 0x00ee3940
bool Bee::F3940()
{
    void* active = VCP0(FUN_0067caa0(), 0x04);
    void* target = (char*)this + 8;

    {
        void* raw = FUN_00f473a0(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
        LayoutObj* p = raw ? ((LayoutObj*)raw)->Ctor() : 0;
        SpSet<1, 2>(&mp40, p);
        if (p)
            p->Setup(0x15ac658, 0, 0x5b598fa);
        LayoutObj* w = p ? p->Child(0x71725b0, 1) : 0;
        if (w)
            VC1(w, 0x104, target);
    }
    {
        void* raw = FUN_00f473a0(0x18, "UI/cSPUILayout", 0, 0, 0, 0);
        LayoutObj* p = raw ? ((LayoutObj*)raw)->Ctor() : 0;
        SpSet<1, 2>(&mp44, p);
        if (p)
            p->Setup(0x15ac664, 0, 0x5b598fa);
        LayoutObj* w = p ? p->Child(0x7172600, 1) : 0;
        if (w)
            VC1(w, 0x104, target);
    }

    SpSet<0, 1>((void**)&mp1c, (void*)((Global164*)FUN_0080fee0())->Get(0x2edd95ca));

    {
        void* raw = FUN_00f473a0(0x84, "Simulator/cScenarioEditModeBehaviorUI", 0, 0, 0, 0);
        Obj84* p = raw ? ((Obj84*)raw)->Ctor() : 0;
        SpSetC(&mp18, p);
        if (p)
            p->Bind(mp1c);
    }

    SpSet<0, 1>(&mp20, VCP2(active, 0xf0, 0x7466e50, 1));

    {
        void* raw = FUN_00f473a0(0x50, "Simulator/cScenarioEditModeScriptActsBarUI", 0, 0, 0, 0);
        Obj50* p = raw ? ((Obj50*)raw)->Ctor() : 0;
        SpSet<1, 2>((void**)&mp48, (void*)p);
        if (p)
            p->Bind(mp20);
    }
    if (mp20)
        VC1(mp20, 0x104, target);

    RebuildLists();

    SpSet<0, 1>(&mp24, VCP2(active, 0xf0, 0x757acb8, 1));

    {
        struct { int a, b, c; } tmp;
        tmp.a = 0; tmp.b = 0; tmp.c = 0;
        mVec.Init(mp24, &tmp);
        mVec.AddColumn(0x15ac688, 3);
    }
    if (mp24)
        VC1(mp24, 0x104, target);

    {
        void* raw = FUN_00f473a0(0xc, "Editor", 0, 0, 0, 0);
        ObjC0* p = raw ? (ObjC0*)raw : 0;
        if (p) {
            p->mpVtbl0 = (void*)0x13ec458;
            p->m8 = 0;
            p->mpVtbl0 = (void*)0x148a81c;
            p->mpVtbl1 = (void*)0x149bad8;
        }
        SpSet<0, 1>(&mpC0, p);
    }

    for (unsigned i = 0; i < (unsigned)mVec.Count(); ++i) {
        LayoutObj* w = ((LayoutObj*)mVec.At((int)i))->Child(0x715cde0, 1);
        if (!w)
            continue;
        VC1(w, 0x50, 0x715cde0 + i);
        for (unsigned j = 0; j < 5; ++j) {
            void* x = VCP2(w, 0xf0, DAT_0148a960[j], 1);
            VC1(x, 0x104, target);
            if (j < 3)
                VC1(x, 0x78, 0x747d67b);
        }
        void* y = VCP2(w, 0xf0, 0x7df4c98, 1);
        if (y)
            VC1(y, 0x104, mpC0);
    }

    SpSet<0, 1>(&mp28, VCP2(active, 0xf0, 0x7625680, 1));

    {
        void* raw = FUN_00f473a0(0xc8, "UI/cSPUIPieMenu", 0, 0, 0, 0);
        ObjC8* p = raw ? ((ObjC8*)raw)->Ctor() : 0;
        SpSet<0, 1>(&mpBC, p);
        if (p) {
            VC5(p, 0x20, 0x15ac694, 0x15ac6a0, 1, mp28, 1);
            p->SetHandlers((int)&FUN_00ee3230, this);
        }
    }
    if (mp28)
        VC1(mp28, 0x104, target);

    return true;
}

// ============================================================ 0x00ee3f60
// @ 0x00ee3f60
bool Hee::F3F60(int msg, void* param)
{
    switch (msg) {
    case 0x44ef2b8:
    case 0x7d11fe0:
    case (int)0xc9d86390:
    case (int)0xc9d86391:
        ((L18*)mp18)->F30D0();
        break;

    case 0x7465518:
        if (param) {
            int v = *(int*)param;
            ((L18*)mp18)->F3710(v);
            CTL()->Notify(0x46, 0x47);
            CTL()->Notify(0x5c, 0x5d);
        }
        break;

    case 0x65ff54a:
        {
            int* d = (int*)param;
            u32 k = (u32)d[6];
            if (d[4] == 0x40464100 &&
                (k == 0xd492676d || k == 0x8ddc5dac ||
                 k == 0x7250e3a1 || k == 0xd130efa6)) {
                u8 was = mC4;
                if (was)
                    ((Bee*)((char*)this - 0x10))->F3E40(0);
                Bee* b = (Bee*)((char*)this - 0x10);
                b->F12C0();
                b->F3940();
                if (was)
                    b->F3E40(1);
            }
        }
        break;

    case 0x72bdb11:
        {
            int n = MGR()->F3be30();
            if (FUN_00efc520() >= n)
                FUN_00efc8c0(MGR()->F3be30() - 1);
        }
        ((Bee*)((char*)this - 0x10))->F31D0();
        MGR()->F427c0();
        break;

    case 0x7311ff7:
    case 0x7311fe9:
    case 0x796d3a0:
        ((Bee*)((char*)this - 0x10))->F31D0();
        MGR()->F427c0();
        break;

    default:
        break;
    }
    return false;
}

// ============================================================ 0x00ee40f0

struct Key3 { u32 mInstance, mType, mGroup; };

struct UintVec {                                                        // eastl::vector<u32>
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;
    u32  mAllocator[2];
    UintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(u32* pos, const u32& v);                         // 0x004558a0 (ret 8)
    void push_back(const u32& v)
    {
        if (mpEnd < mpCapacity) {
            if (mpEnd)
                *mpEnd = v;
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct KeyVec {                                                         // eastl::vector<Key3>
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCapacity;
    u32   mAllocator[2];
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

struct IdQuery {
    void*   mpVtbl;                                                    // +0x00 (vtable 0x13eb394)
    UintVec mIds;                                                      // +0x04
    u32     mId;                                                       // +0x18
    IdQuery(u32 id, const UintVec& ids);                               // 0x00669360 (ret 8)
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void ResolveQuery(KeyVec*, IdQuery*, int);                 // +0x38
};
IResourceManager* GetManager();                                        // 0x0067dcd0

struct Rng {
    u32 RandomUint32Uniform(u32 n);                                    // 0x00a68fb0 (ret 4)
};
extern Rng sMathRandom;                                                // 0x01601760

static inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1])
        FUN_00f47380(p);
}

// @ 0x00ee40f0
void Bee::F40F0()
{
    UintVec ids;
    u32 tag = 0x96b21af3;
    ids.push_back(tag);

    IdQuery query(0xd87454e6, ids);
    KeyVec found;
    GetManager()->ResolveQuery(&found, &query, 0);

    u32 idx = sMathRandom.RandomUint32Uniform((u32)(found.mpEnd - found.mpBegin));
    ApplyPick(found.mpBegin + idx);

    // inlined destructors, in reverse construction order
    SpFree(found.mpBegin);
    SpFree(query.mIds.mpBegin);
    query.mpVtbl = (void*)0x13eb394;
    SpFree(ids.mpBegin);
}

// ============================================================ 0x00ee41e0
// @ 0x00ee41e0

struct Elem44 {                                                         // 0x44-byte list entry
    char  pad04[4];
};

struct FixedVec44 {                                                     // eastl::fixed_vector<Elem44, 5>
    Elem44* mpBegin;                                                   // +0x00
    Elem44* mpEnd;                                                     // +0x04
    Elem44* mpCapacity;                                                // +0x08
    u32     mHeader[3];                                                // +0x0c
    u8      mBuffer[0x154];                                            // +0x18
};

struct SData {
    u32         mType;                                                 // +0x000
    u32         mKeyA;                                                 // +0x004
    u32         mKeyB;                                                 // +0x008
    u32         m0c;                                                   // +0x00c
    u8          m10;                                                   // +0x010
    u8          pad11[3];
    u32         m14;                                                   // +0x014
    FixedVec44  mVec;                                                  // +0x018
    u32         mStatus;                                               // +0x184
    void CopyFrom(const SData& src);                                   // 0x00dfd020 (ret 4)
};

bool __cdecl f00ee41e0(SData* src, int value, int tag, int d, char e)
{
    bool ok = false;

    SData s;
    s.CopyFrom(*src);

    int* state = (int*)FUN_00efc8f0();
    if (state != 0) {
        u32 flags = (u32)state[0x224 / 4];
        if ((flags & 0x10) != 0 || (flags & 0x2) != 0 || (flags & 0x4) != 0) {
            s.mStatus = 0xd;
            goto tail;
        }
    }

    if (tag == 0x7394420)
        s.mKeyA = (u32)value;
    else
        s.mKeyB = (u32)value;

    {
        Mgrs* mgr = MGR();
        int t = FUN_00efc520();
        if (!mgr->F40500(&s, t, 0))
            goto tail;
        if (!mgr->F3e6d0(FUN_00efe5b0(), src, t, 0))
            goto tail;
        if (!mgr->F3c750(&s, d)) {
            s.mStatus = 0x17;
            goto tail;
        }
        if (mgr->F420d0(t, &s, d, 0, 0)) {
            s.mStatus = 0x18;
            goto tail;
        }
        ok = true;
    }

tail:
    {
        Ctl* ctl = CTL();
        if (!ctl->IsBusy() && e != 0) {
            cString str;
            ((UIMgr*)FUN_0067cac0())->Select(0x7e9a7f40, 0);
            FUN_00ee2860(&s, 0, &str);
            ((UIMgr*)FUN_0067cac0())->Show(0x7e9a7f40);
        }
    }

    // SData destructor (inlined): destroy each entry, then free the (possibly grown) buffer.
    {
        Elem44* b = s.mVec.mpBegin;
        for (Elem44* p = b; p != s.mVec.mpEnd; ++p)
            ((Sub4*)((char*)p + 4))->Destroy();
        SpFree(b);
    }
    return ok;
}
