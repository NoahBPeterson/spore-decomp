// Spore retail 00c2f830..00c308aa -- SP creature / tribe / find mission classes:
// constructors, destructors, the mission text getters, and the property-list
// helpers around them.  Field access uses explicit byte/dword offsets because
// the retail layout extends past the 2008 dev-build PDB.
// Compile: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned int u32;
typedef unsigned char u8;

// ------------------------------------------------------------------ callees
#include <intrin.h>

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    T*& AsOutParam() { return mpObject; }
    operator T*() const { return mpObject; }
};

typedef void (__fastcall *VFn0)(void*);
typedef int  (__fastcall *VFnI)(void*);
typedef int* (__fastcall *VFnP)(void*);

// Callees whose first parameter is `this` (ECX) plus stack arguments cannot be
// declared as free functions; route them through a member-function stub whose
// name is irrelevant (relocations are masked on both sides when scoring).
struct ThiscallStub {
    void FUN_00c2ed20(int*, int*);      // 0x00c2ed20 load two AutoRefCount slots
    void FUN_00c2fd20(int);             // 0x00c2fd20 tutorial mission Init
    void FUN_00d00a10(int, int);
    int  FUN_00d00780();
    void FUN_00c8f3a0();
    char FUN_00c905a0();
    void FUN_00c7bbc0(int member, int param);
    void FUN_00c7a7d0(int member);
    void FUN_00ac9480(int* src);
    void* FUN_004df550();
    void FUN_00401090();
    void FUN_00ac9480();
    int  FUN_00d2e490();
};

// The base ctor/dtor are __thiscall (this in ECX). __fastcall puts its first
// argument in ECX too, which reproduces the original's calling sequence.
extern "C" void __fastcall FUN_00c46500(void*);  // base ctor
extern "C" void __fastcall FUN_00c45140(void*);  // base dtor

// ---------------------------------------------------------------------------
// Inline EA reference count (the `lock xadd` triple the engine's smart pointer
// release expands to).  A free helper so the pointer stays in a scratch
// register rather than ECX (the original keeps it in EAX).
// ---------------------------------------------------------------------------
struct RcBase {
    volatile long rc;                       // object +0x08
    void Release()
    {
        long v = _InterlockedExchangeAdd(&rc, -1);
        (void)_InterlockedExchangeAdd(&rc, 0);
        if (v < 1)
            _InterlockedExchangeAdd(&rc, 1);
        else
            _InterlockedExchangeAdd(&rc, 0);
    }
};

// Inlined refcount release: obj points at the object, its count is at obj+8.
static void ReleaseRef(int* obj)
{
    volatile long* p = (volatile long*)((int)obj + 8);
    (void)_InterlockedExchangeAdd(p, -1);
    long v = _InterlockedExchangeAdd(p, 0);
    if (v < 1)
        _InterlockedExchangeAdd(p, 1);
    else
        _InterlockedExchangeAdd(p, 0);
}

// The property manager: virtual GetProperty(obj, key, out) at vtable slot 0x2c.
struct PropMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void GetProperty(int obj, int key, int* out);   // +0x2c
};
// A 16-byte resource key passed by value to the resource manager.
struct ResKey { int f0, f1, f2, f3; };
struct ImageRes { void Set(void* img); };         // __thiscall 0x00576650

extern "C" void  operator_delete(void*);         // 0x00f47380 ??3@YAXPAX@Z
extern "C" void* SP_PropertyManager();           // 0x0067de30
extern "C" void* EA_ResourceMan_GetManager();    // 0x0067dcd0 ::EA::ResourceMan::GetManager
extern "C" void* __stdcall FUN_00401090(void*);  // species profile lookup (setting)
extern "C" void* FUN_004df550(void*);            // species profile lookup
extern "C" void* FUN_0067dd60();
extern "C" int   FUN_004e1c30(void*, int, int);   // 0x004e1c30 cTribeTool::GetTutorialToolPrice
extern "C" int   __fastcall SP_GetPlayerEmpireOrMinus1(void*);  // 0x00b1f9d0 ecx=obj
extern "C" void* SP_NounManager();
extern "C" void* SP_RelationshipManager();
extern "C" void* SP_cTribeModeStrategy_Instance();          // 0x00cd40b0
                                                            // 0x00ac9480 AutoRefCount assign (thiscall)
extern "C" void* FUN_00c0c1a0();
extern "C" char  SP_GetPropertyAsText(int, int, void*);   // 0x006a1360
extern "C" float* __fastcall SP_GetPropertyAsFloat(void*); // 0x0041ea70
extern "C" int*  __fastcall Property_GetInt(void*);        // 0x0041e990
extern "C" u32*  __fastcall Property_GetUInt(void*);       // 0x0041ea00
extern "C" void  WString_Assign(void*, const wchar_t*, const wchar_t*);  // 0x00423650
extern "C" void  WString_Append(void*, const wchar_t*);   // 0x005c3d90
extern "C" void* __fastcall GetCurrentTerrainSphere(void*); // 0x00f67d90 ecx=obj, returns [ecx+0x74]
extern "C" void  GetImageResource(void*, void*);          // 0x00576650

// ------------------------------------------------------------------ vtables
#define VT_FIND              0x146b338
#define VT_FIND_2            0x146b328
#define VT_FIND_3            0x146b318
#define VT_SPECIES           0x146b420
#define VT_SPECIES_2         0x146b40c
#define VT_SPECIES_3         0x146b3fc
#define VT_TUTORIAL          0x146b0f8
#define VT_TUTORIAL_2        0x146b0e8
#define VT_TUTORIAL_3        0x146b0d8
#define VT_BASE              0x146aff0
#define VT_BASE_2            0x146afdc
#define VT_BASE_3            0x146afcc

// ---------------------------------------------------------------------------
// @ 0x00c2f830
// ---------------------------------------------------------------------------
int* __fastcall cFindMission_ctor(int* self)
{
    FUN_00c46500(self);
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = VT_FIND;
    self[1] = VT_FIND_2;
    self[0xd] = VT_FIND_3;
    *(volatile int*)(self + 0x20) = 0;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00c2f890
// ---------------------------------------------------------------------------
void __fastcall FUN_00c2f890(int* self)
{
    int* p = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (p) {
        ((VFn0)(*(void***)p)[0])(p);
        ((VFn0)(*(void***)p)[1])(p);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00c2f8c0
// ---------------------------------------------------------------------------
int* __fastcall cCreatureSpeciesMission_ctor(int* self)
{
    FUN_00c46500(self);
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = VT_SPECIES;
    self[1] = VT_SPECIES_2;
    self[0xd] = VT_SPECIES_3;
    for (int i = 0x20; i < 0x30; ++i)
        self[i] = 0;
    *(u8*)(self + 0x31) = 0;
    self[0x32] = 0;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00c2f9c0
// ---------------------------------------------------------------------------
void __fastcall FUN_00c2f9c0(int* self)
{
    self[0] = VT_SPECIES;
    self[1] = VT_SPECIES_2;
    self[0xd] = VT_SPECIES_3;
    int* p = (int*)self[0x32];
    if (p != 0)
        ReleaseRef(p);
    if ((int*)self[0x2a] != 0) {
        int* q = (int*)self[0x2a];
        ((VFn0)(*(void***)q)[1])(q);
    }
    if ((int*)self[0x29] != 0) {
        int* q = (int*)self[0x29];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
}

// ---------------------------------------------------------------------------
// @ 0x00c2fa50
// ---------------------------------------------------------------------------
void __fastcall FUN_00c2fa50(int* self)
{
    int local8 = 0;
    int local4 = 0;
    ((ThiscallStub*)self)->FUN_00c2ed20(&local8, &local4);
    if (local8 != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0xa4);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(local8, 0x5267de50, slot);
    } else {
        int* slot = (int*)((char*)self + 0xa4);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
    if (local4 != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0xa8);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(local4, 0x5267de50, slot);
    } else {
        int* slot = (int*)((char*)self + 0xa8);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
}

// ---------------------------------------------------------------------------
// The member functions below are __thiscall (this in ECX, callee-pops stack
// arguments).  Grouping them in one class reproduces that calling convention.
// ---------------------------------------------------------------------------
struct cString {
    cString();                                                  // 0x006b5060
    cString(u32 table, u32 instance, const wchar_t* fallback);  // 0x006b5770
    ~cString();                                                 // 0x006b5240
    const wchar_t* c_str();                                     // 0x006b55c0
    u32 mTable; u32 mInstance; u32 pad08; u32 pad0c; u32 pad10;
};

struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
    void append(const wchar_t* s);                     // 0x005c3d90
};

struct Mission {
    char FUN_00c2fc00(int param);
    void FUN_00c2fc10();
    void FUN_00c2fc80();
    int* FUN_00c2fcc0(unsigned int flags);
    void FUN_00c2fd20(int id);
    char FUN_00c2fdd0(int param);
    void FUN_00c2fde0();
    void FUN_00c2fea0();
    int* FUN_00c2fb30();
    int* FUN_00c2ffb0();
    char FUN_00c30090(int param);
    int* FUN_00c300a0(unsigned int flags);
    void FUN_00c30100(int id);
    char FUN_00c30150(int param);
    void FUN_00c301c0(int src);
    void FUN_00c30270(int obj);
    void FUN_00c302b0(char* out);
    void FUN_00c30350(char* out);
    void GetTitleText(char* out);
    void GetBodyText(char* out);
    void GetSummaryText(char* out);
    void GetRewardText(char* out);
    void GetStatusText(char* out);
    void GetSubTitleText(char* out);
    void GetProgressText(char* out);
    void FUN_00c307f0(char* out);
    int* FUN_00c30820(int key);
    void FUN_00c30860(int param);
    void FUN_00c30890();
};

// @ 0x00c2fb30
int* Mission::FUN_00c2fb30()
{
    int* self = (int*)this;
    int edi = ((ThiscallStub*)self)->FUN_00d2e490();
    AutoRefCount<int> local;
    int* esi;
    int r = ((int(__fastcall*)(void*))(*(void***)self)[0x60 / 4])(self);
    if (r == 5 && self[0x28] == 6) {
        esi = (int*)self[0x29];
    } else if (((int(__fastcall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5) {
        esi = (int*)self[0x2a];
    } else {
        int* src;
        if (edi == 0) {
            if (self[0x29] == 0)
                goto fallback;
            src = self + 0x29;
        } else if (edi == 1) {
            if (self[0x2a] == 0)
                goto fallback;
            src = self + 0x2a;
        } else {
        fallback:
            if (self[0x29] != 0)
                src = self + 0x29;
            else if (self[0x2a] != 0)
                src = self + 0x2a;
            else
                return 0;
        }
        ((ThiscallStub*)&local)->FUN_00ac9480(src);
        esi = local.mpObject;
        goto done;
    }
    if (esi == 0)
        return 0;
    ((VFn0)(*(void***)esi)[0])(esi);
done:
    if (esi != 0)
        ((VFn0)(*(void***)esi)[1])(esi);
    return esi;
}

// @ 0x00c2fc00
char Mission::FUN_00c2fc00(int param)
{
    (void)param;
    FUN_00c2fa50((int*)this);
    return 1;
}

// @ 0x00c2fc10
void Mission::FUN_00c2fc10()
{
    int* self = (int*)this;
    int* prof = (int*)((ThiscallStub*)FUN_00401090((char*)self + 0x80))->FUN_004df550();
    if (prof != 0) {
        int b = prof[0x508 / 4];
        void* mgr = FUN_0067dd60();
        ResKey key;
        key.f0 = prof[0x504 / 4];
        key.f1 = 0x2f7d0004;
        key.f2 = prof[0x50c / 4];
        key.f3 = b & 0;   // zero, but keeps the 0x508 load live
        int img = ((int(__thiscall*)(void*, ResKey))(*(void***)mgr)[0x1c / 4])(mgr, key);
        ((ImageRes*)((char*)this + 0xc8))->Set((void*)img);
    }
}

// @ 0x00c2fc80
void Mission::FUN_00c2fc80()
{
    int* self = (int*)this;
    int* p = (int*)self[0x32];
    if (p != 0) {
        self[0x32] = 0;
        ReleaseRef(p);
    }
}

// @ 0x00c2fcc0
int* Mission::FUN_00c2fcc0(unsigned int flags)
{
    int* self = (int*)this;
    self[0] = VT_TUTORIAL;
    self[1] = VT_TUTORIAL_2;
    self[0xd] = VT_TUTORIAL_3;
    _ReadWriteBarrier();
    if ((int*)self[0x20] != 0) {
        int* q = (int*)self[0x20];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
    if (flags & 1)
        operator_delete(self);
    return self;
}

// @ 0x00c2fd20
void Mission::FUN_00c2fd20(int id)
{
    int* self = (int*)this;
    self[0x1e] = id;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
    int* po = (int*)*slot;
    if (po != 0) {
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)po)[0x24 / 4])(po, 0x393f7f7d, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 0xd) {
            float* fv = SP_GetPropertyAsFloat((void*)temp);
            *(float*)((char*)self + 0x88) = *fv;
        }
    }
    po = (int*)*slot;
    if (po != 0) {
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)po)[0x24 / 4])(po, 0x1ecff7aa, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 9) {
            int* iv = Property_GetInt((void*)temp);
            self[0x21] = *iv;
        }
    }
}

// @ 0x00c2fdd0
char Mission::FUN_00c2fdd0(int param)
{
    (void)param;
    int* self = (int*)this;
    ((Mission*)self)->FUN_00c2fd20(self[0x1e]);
    return 1;
}

// @ 0x00c2fde0
void Mission::FUN_00c2fde0()
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj != 0) {
        ((VFn0)(*(void***)obj)[0])(obj);
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)obj)[0x24 / 4])(obj, 0x6b15b5cb, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 0xa) {
            u32 val = *Property_GetUInt((void*)temp);
            *(u32*)((char*)*(int**)0x169e3e8 + 0x10) = val;
        }
    }
    u32 m = self[0x21];
    *(u32*)((char*)*(int**)0x169e3e8 + 0x20) = m;
    if (*(int**)0x169b41c != 0) {
        int r = FUN_004e1c30(*(void**)0x1581288, 0xb79e0065, 0x28);
        *(int*)((char*)*(int**)0x169b41c + 0xc) = r;
    }
    if (obj != 0)
        ((VFn0)(*(void***)obj)[1])(obj);
}

// @ 0x00c2fea0
void Mission::FUN_00c2fea0()
{
    int* self = (int*)this;
    int* edi = (int*)self[0x20];
    int ebp = 0x57e2f080;
    int empire = SP_GetPlayerEmpireOrMinus1(SP_NounManager());
    int rel = ((int(__thiscall*)(void*, int))(*(void***)edi)[0x4c / 4])(edi, empire);
    void* rm = SP_RelationshipManager();
    float f = ((float(__thiscall*)(void*, int, int, int))0xd00a10)(rm, rel, empire, 0);
    void* rm2 = SP_RelationshipManager();
    int kind = ((int(__thiscall*)(void*, float))0xd00780)(rm2, f);
    if (kind >= 2)
        ebp = 0x3d61df6c;
    if (!((int(__thiscall*)(void*))0xc8f3a0)((void*)self[0x20])) {
        if (((char(__thiscall*)(void*))0xc905a0)((void*)self[0x20]))
            ebp = 0xf1e0dd24;
        else
            goto notset;
    }
    if (ebp != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0x84);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(ebp, 0x5267de50, slot);
    } else {
notset:
        int* slot = (int*)((char*)self + 0x84);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
    PropMgr* pm2 = (PropMgr*)SP_PropertyManager();
    int* slot2 = (int*)((char*)self + 0x88);
    if (*slot2 != 0) {
        int* old = (int*)*slot2;
        *slot2 = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm2->GetProperty(0xf1e0dd24, 0x5267de50, slot2);
}

// @ 0x00c2ffb0
int* Mission::FUN_00c2ffb0()
{
    int* self = (int*)this;
    int* strat = (int*)SP_cTribeModeStrategy_Instance();
    int ebx = strat[0x390 / 4];
    int* p = (int*)self[0x20];
    AutoRefCount<int> local;
    int empire = SP_GetPlayerEmpireOrMinus1(SP_NounManager());
    int rel = ((int(__thiscall*)(void*, int))(*(void***)p)[0x4c / 4])(p, empire);
    void* rm = SP_RelationshipManager();
    float f = ((float(__thiscall*)(void*, int, int, int))0xd00a10)(rm, rel, empire, 0);
    void* rm2 = SP_RelationshipManager();
    int kind = ((int(__thiscall*)(void*, float))0xd00780)(rm2, f);
    int* esi;
    if (((int(__thiscall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5 && kind == 4) {
        esi = (int*)self[0x21];
    } else if (((int(__thiscall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5) {
        esi = (int*)self[0x22];
    } else if (ebx == 0) {
        esi = (int*)self[0x21];
    } else if (ebx == 1) {
        ((ThiscallStub*)&local)->FUN_00ac9480((int*)((char*)self + 0x88));
        esi = local.mpObject;
    } else {
        return 0;
    }
    if (esi == 0)
        return 0;
    ((VFn0)(*(void***)esi)[0])(esi);
    if (esi != 0)
        ((VFn0)(*(void***)esi)[1])(esi);
    return esi;
}

// @ 0x00c30090
char Mission::FUN_00c30090(int param)
{
    (void)param;
    ((Mission*)this)->FUN_00c2fea0();
    return 1;
}

// @ 0x00c300a0
int* Mission::FUN_00c300a0(unsigned int flags)
{
    int* self = (int*)this;
    self[0] = VT_FIND;
    self[1] = VT_FIND_2;
    self[0xd] = VT_FIND_3;
    _ReadWriteBarrier();
    if ((int*)self[0x20] != 0) {
        int* q = (int*)self[0x20];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
    if (flags & 1)
        operator_delete(self);
    return self;
}

// @ 0x00c30100
void Mission::FUN_00c30100(int id)
{
    int* self = (int*)this;
    self[0x1e] = id;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
}

// @ 0x00c30150
char Mission::FUN_00c30150(int param)
{
    (void)param;
    int* self = (int*)this;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
    return 1;
}

// @ 0x00c301c0
void Mission::FUN_00c301c0(int src)
{
    int* self = (int*)this;
    int* s = (int*)src;
    self[0x20] = s[0xb28 / 4];
    self[0x21] = s[0xb2c / 4];
    self[0x22] = s[0xb30 / 4];
    int* o = (int*)FUN_00c0c1a0();
    if (o != 0) {
        self[0x2b] = o[0x3fc / 4];
        self[0x2c] = o[0x400 / 4];
        self[0x2d] = o[0x404 / 4];
        self[0x2e] = o[0x408 / 4];
        self[0x2f] = o[0x40c / 4];
        self[0x25] = o[0x418 / 4];
        self[0x26] = o[0x420 / 4];
        self[0x30] = o[0x330 / 4];
        *(u8*)((char*)self + 0xc4) = *(u8*)((char*)o + 0x389);
    }
    FUN_00c2fa50(self);
}

// @ 0x00c30270
void Mission::FUN_00c30270(int obj)
{
    int* self = (int*)this;
    int* old = (int*)self[0x20];
    if (obj != (int)old) {
        if (obj != 0)
            ((VFn0)(*(void***)obj)[0])((void*)obj);
        self[0x20] = obj;
        if (old != 0)
            ((VFn0)(*(void***)old)[1])(old);
    }
    ((Mission*)self)->FUN_00c2fea0();
}

// @ 0x00c302b0
void Mission::FUN_00c302b0(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    char ok = SP_GetPropertyAsText((int)obj, 0x15e95780, &cs);
    if (!ok) {
        ((void(__thiscall*)(void*, char*))(*(void***)self)[0x8c / 4])(self, out);
        return;
    }
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c30350
void Mission::FUN_00c30350(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    char ok = SP_GetPropertyAsText((int)obj, 0xcbbe0580, &cs);
    if (!ok) {
        ((void(__thiscall*)(void*, char*))(*(void***)self)[0x98 / 4])(self, out);
        return;
    }
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c303f0
void Mission::GetTitleText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xa7696d50, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}
// @ 0x00c30460
void Mission::GetBodyText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xb6496990, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}
// @ 0x00c304d0
void Mission::GetSummaryText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xfc89a37e, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}
// @ 0x00c30540
void Mission::GetRewardText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xadf78285, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c305b0
void Mission::GetStatusText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    int kind = self[0x1f];
    switch (kind) {
    case 3: {
        cString cs;
        SP_GetPropertyAsText((int)obj, 0x34255d1e, &cs);
        ((WStr*)out)->append(cs.c_str());
        break;
    }
    case 5: {
        cString cs;
        SP_GetPropertyAsText((int)obj, 0xd2f7cd25, &cs);
        ((WStr*)out)->append(cs.c_str());
        break;
    }
    }
}

// @ 0x00c30630
void Mission::GetSubTitleText(char* out)
{
    int* self = (int*)this;
    void* prof = ((ThiscallStub*)FUN_00401090((char*)self + 0x80))->FUN_004df550();
    if (prof == 0)
        return;
    int* p = (int*)prof;
    int key = p[0x504 / 4];
    int key2 = p[0x508 / 4];
    int key3 = p[0x50c / 4];
    int holder = 0;
    void* mgr = EA_ResourceMan_GetManager();
    if (holder != 0) {
        int* o = (int*)holder;
        holder = 0;
        ((VFn0)(*(void***)o)[1])(o);
    }
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int))(*(void***)mgr)[0xc / 4])(mgr, &key, &holder, 0, 0);
    if (ok) {
        if (holder == 0)
            return;
        int* o = (int*)holder;
        int sub = ((int(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 0x30bdee3);
        if (sub != 0) {
            int r = ((int(__fastcall*)(void*))0x550880)((void*)sub);
            *(int*)(*(int**)0x169e3e8 + 0x28) = r;
            cString cs(0xad56080c, 0xb3daed77, L"~Unknown");
            const wchar_t* t = cs.c_str();
            ((WStr*)out)->append(t);
            cs.~cString();
        }
    } else {
        cString cs(0xad56080c, 0x73db4258, L"~Unknown");
        const wchar_t* t = cs.c_str();
        const wchar_t* e = t;
        while (*e) e++;
        ((WStr*)out)->assign(t, t + (e - t));
        cs.~cString();
    }
    if (holder != 0) {
        int* o = (int*)holder;
        ((VFn0)(*(void***)o)[1])(o);
    }
}

// @ 0x00c30780
void Mission::GetProgressText(char* out)
{
    int* self = (int*)this;
    unsigned int a = ((unsigned int(__fastcall*)(void*))(*(void***)self)[0x58 / 4])(self);
    unsigned int b = ((unsigned int(__fastcall*)(void*))(*(void***)self)[0x54 / 4])(self);
    if (b >= a)
        return;
    cString cs(0xad56080c, 0x53b644df, L"~Goal");
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c307f0
void Mission::FUN_00c307f0(char* out)
{
    int* self = (int*)this;
    int n = ((int(__fastcall*)(void*))(*(void***)self)[0xa4 / 4])(self);
    if (n > 0)
        ((Mission*)self)->GetRewardText(out);
}

// @ 0x00c30820
int* Mission::FUN_00c30820(int key)
{
    int* self = (int*)this;
    if (key == 0x179c807 || key == 0x1805e75)
        return self;
    if (key == 0x5593a1a && self != 0)
        return (int*)((char*)self + 0xc);
    return 0;
}

// @ 0x00c30860
void Mission::FUN_00c30860(int param)
{
    int member = ((int*)this)[0x21];
    void* sphere = GetCurrentTerrainSphere(SP_NounManager());
    ((ThiscallStub*)sphere)->FUN_00c7bbc0(member, param);
}

// @ 0x00c30890
void Mission::FUN_00c30890()
{
    int member = ((int*)this)[0x21];
    void* sphere = GetCurrentTerrainSphere(SP_NounManager());
    ((ThiscallStub*)sphere)->FUN_00c7a7d0(member);
}
