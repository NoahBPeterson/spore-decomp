// slice s00eec5c0 -- editor/creature resource-key and property helpers.
#include "types.h"

struct IObj {
    virtual void  u0();
    virtual void  u1();
    virtual void  u2();
    virtual void* Query(int key);       // slot 3 (0x0c)
};

struct IObjQ {
    virtual void  q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void  q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void  q8();
    virtual bool  Test();               // 9 (0x24)
};

struct Mgr {
    void* FUN_00f3d780(int a);
    void* FUN_00f3e8a0(int key);
    void* FUN_00f3f950(int key);
    void  FUN_00f3e2b0(int a, int b, int c);
    void  FUN_00f3da90(int a, int b);
};
struct GlobalObj {
    char pad0[0x74];
    Mgr* f74;
};
extern GlobalObj* g_16c7aa4;

extern int g_015aca34;
extern int g_015aca40, g_015aca44, g_015aca48, g_015aca4c, g_015ac948;

int   __cdecl   FUN_00efe5a0();
void* __cdecl   FUN_00eeca60(void* out, void* in);

// ===========================================================================
// @ 0x00eec940
// ===========================================================================
void __cdecl f_00eec940(int** range, int param_2)
{
    Mgr* m = g_16c7aa4->f74;
    int* it = range[0];
    int* end = range[1];
    for (; it != end; it += 8) {
        m->FUN_00f3e2b0(it[0], 0, param_2);
        m->FUN_00f3da90(it[0], 0);
    }
}

// ===========================================================================
// @ 0x00eec990
// ===========================================================================
int __cdecl f_00eec990(int key)
{
    Mgr* m = g_16c7aa4->f74;
    void* p = m->FUN_00f3f950(key);
    if (p != 0)
        return *(int*)((char*)p + 0x4a8);
    return 2;
}

// ===========================================================================
// @ 0x00eeca30
// ===========================================================================
void* __cdecl f_00eeca30(int key)
{
    Mgr* m = g_16c7aa4->f74;
    IObj* p = (IObj*)m->FUN_00f3d780(key);
    if (p != 0)
        return p->Query(0x1186577);
    return 0;
}

// ===========================================================================
// @ 0x00eec820   (vtable slot 0x74 float, gate on slot 0xb8)
// ===========================================================================
struct IObj2 {
    virtual void  u0(); virtual void u1(); virtual void u2(); virtual void u3();
    virtual void  u4(); virtual void u5(); virtual void u6(); virtual void u7();
    virtual void  u8(); virtual void u9(); virtual void u10(); virtual void u11();
    virtual void  u12(); virtual void u13(); virtual void u14(); virtual void u15();
    virtual void  u16(); virtual void u17(); virtual void u18(); virtual void u19();
    virtual void  u20(); virtual void u21(); virtual void u22(); virtual void u23();
    virtual void  u24(); virtual void u25(); virtual void u26(); virtual void u27();
    virtual void  u28();
    virtual float GetFloat();           // 29 (0x74)
    virtual void  u30(); virtual void u31(); virtual void u32(); virtual void u33();
    virtual void  u34(); virtual void u35(); virtual void u36(); virtual void u37();
    virtual void  u38(); virtual void u39(); virtual void u40(); virtual void u41();
    virtual void  u42(); virtual void u43(); virtual void u44(); virtual void u45();
    virtual void* QueryB8(int key);     // 46 (0xb8)
};

float __cdecl f_00eec820(IObj2* p)
{
    float v = p->GetFloat();
    if (p->QueryB8(0x137e8e0) != 0)
        v = v * 2.0f;
    return v;
}

// ===========================================================================
// @ 0x00eec8e0
// ===========================================================================
struct X25 { char f_f25f60(); char f_f25580(); };

void __cdecl f_00eec8e0(int* key, char* p2, char* p3)
{
    *p3 = 1;
    *p2 = 1;
    Mgr* m = g_16c7aa4->f74;
    X25* p = (X25*)m->FUN_00f3e8a0(*key);
    if (p != 0) {
        *p3 = p->f_f25f60();
        *p2 = p->f_f25580();
        return;
    }
    if (*key == -2) {
        *p3 = 0;
        *p2 = 0;
    }
}

// ===========================================================================
// @ 0x00eec870
// ===========================================================================
void* __cdecl f_00eec870(IObj* keyObj)
{
    int* base = (int*)FUN_00efe5a0();
    int saved = g_015ac948;
    void* q;
    if (keyObj != 0)
        q = keyObj->Query(0x1186577);
    else
        q = 0;
    if (*((char*)q + 0x6e) != 0)
        return (void*)g_015aca4c;
    if (*((char*)q + 0x78) != 0)
        return (void*)g_015aca48;
    if ((int*)keyObj == base)
        return (void*)g_015aca44;
    if (((IObjQ*)q)->Test())
        return (void*)g_015aca40;
    return (void*)saved;
}

// ===========================================================================
// @ 0x00eece20   hash dispatch
// ===========================================================================
struct RKey { int f0; unsigned f1; int f2; };

int __cdecl f_00eece20(int* param)
{
    RKey k;
    int r = 0x867a9ee9;
    FUN_00eeca60(&k, param);
    switch (k.f1) {
    case 0x7b38ba7:  r = 0x7998ce71; break;
    case 0x18c88e4:
    case 0x2a8fb3f:
    case 0x3a2511e:  r = 0x6031c03a; break;
    case 0x403df5c:  r = 0xc7fdcb1e; break;
    case 0x74e0069:  r = 0xe137ff08; break;
    case 0x2b978c46: r = 0xe34e8a60; break;
    case 0x2399be55: r = 0xb10e526f; break;
    case 0x24682294: r = 0x5b3d1d0d; break;
    case 0x476a98c7: r = 0xd37c1045; break;
    case 0xf0000001: r = 0xcf56099a; break;
    }
    return r;
}

// ===========================================================================
// Shared resource / property types used by the routines below.
// ===========================================================================
struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct IPropList {
    virtual void s0();
    virtual int  Release();                 // +0x04
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool Get(uint32_t hash, void** out);   // +0x24
    virtual void s10();
};

struct PropMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, IPropList** out);  // +0x2c
};

struct Property {
    char     pad[0x12];
    uint16_t mType;                         // +0x12
    int* GetUInt();
    int* GetInt();
};

struct IPropOwner {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8();
    virtual bool Get(uint32_t hash, void** out);   // 9 (0x24)
};

template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

PropMgr* __cdecl FUN_0067de30();
uint32_t __cdecl FUN_00932e80(const char* s, uint32_t basis, int a);
bool __cdecl GetPropertyAsKey(IPropList* list, uint32_t hash, ResourceKey* out);
bool __cdecl GetPropertyAsKeyInstance(IPropList* list, uint32_t hash, uint32_t* out);
bool __cdecl GetBoolProperty(IPropList* list, uint32_t hash, void* out);
bool __cdecl GetPropertyT(void* list, uint32_t hash, void* out);
float __cdecl FUN_004d12a0(void* x);
void* __cdecl FUN_00c028b0(void* p, int a);
float __cdecl FUN_00bcd420();

extern uint32_t g_16c78bc;
extern uint32_t g_16c78c0;
extern float g_16c79a4, g_16c79b4, g_16c79d4, g_16c79e4;
extern float g_16c7944, g_16c7964, g_15d96b8;

struct NounMgr { void* FUN_00b21000(uint32_t type, uint32_t inst); };
NounMgr* __cdecl NounManager();
struct NounB { int* FUN_00b18530(); };
struct B20      { char pad[0x56c]; float mF56c; };
struct ObjB20   { char pad[0xb20]; B20* mB20;  };
struct ObjB18   { char pad[0xb18]; float mB18;  };

// float -> int rounding up (the module's asm helper; cvtss2si + cmovb)
#pragma warning(disable:4035)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

// ===========================================================================
// @ 0x00eec5c0   resource-type -> rounded scaled value
// ===========================================================================
float __cdecl f_00eec5c0(void* p)
{
    int* cd = ((NounB*)p)->FUN_00b18530();
    void* entry = g_16c7aa4->f74->FUN_00f3f950((int)p);
    switch (*(uint32_t*)((char*)cd + 4)) {
    case 0x2b978c46: {
        if (!p)
            break;
        ObjB20* o = (ObjB20*)((IObj*)p)->Query(0xd0036e08);
        if (!o)
            break;
        if (!o->mB20)
            break;
        float v = FUN_004d12a0(FUN_00c028b0(o->mB20, 0)) + o->mB20->mF56c;
        v = v * *(float*)((char*)entry + 0x48c);
        return (float)CeilToInt(v);
    }
    case 0x2399be55: {
        float v = FUN_00bcd420() * *(float*)((char*)entry + 0x48c);
        return (float)CeilToInt(v);
    }
    case 0x24682294: {
        if (!p)
            break;
        ObjB18* o = (ObjB18*)((IObj*)p)->Query(0x137e8e0);
        if (!o)
            break;
        float v = o->mB18 * *(float*)((char*)entry + 0x48c);
        return (float)CeilToInt(v);
    }
    case 0x476a98c7: {
        float v = *(float*)((char*)entry + 0x48c) * 100.0f;
        return (float)CeilToInt(v);
    }
    }
    return 1.0f;
}

// ===========================================================================
// @ 0x00eec760   three hashed property reads into an int triple
// ===========================================================================
void __cdecl f_00eec760(void* obj, int* out)
{
    if (!obj)
        return;
    if (!out)
        return;
    int a = -1, b = 0x7fffffff;
    out[0] = a;
    out[1] = b;
    out[2] = b;
    IPropOwner* o = (IPropOwner*)obj;
    void* prop;
    if (o->Get(0x1f0372ed, &prop) && ((Property*)prop)->mType == 10)
        out[0] = *((Property*)prop)->GetUInt();
    if (o->Get(0xd6a4ff43, &prop) && ((Property*)prop)->mType == 9)
        out[1] = *((Property*)prop)->GetInt();
    if (o->Get(0xb55857d7, &prop) && ((Property*)prop)->mType == 9)
        out[2] = *((Property*)prop)->GetInt();
}

// ===========================================================================
// @ 0x00eec9c0   eastl::uninitialized_move<Entry32>
// ===========================================================================
struct Entry32 {
    uint32_t mA;
    float    mB, mC, mD, mE, mF, mG, mH;
    Entry32() {}
    __forceinline Entry32(const Entry32& x) {
        mB = x.mB;
        mA = x.mA;
        mC = x.mC;
        mD = x.mD;
        mE = x.mE;
        mF = x.mF;
        mG = x.mG;
        mH = x.mH;
    }
};

inline void* operator new(unsigned int, void* p) { return p; }

namespace eastl {
template <typename T>
T* uninitialized_move(T* first, T* last, T* dest)
{
    for (; first != last; ++first, ++dest)
        if (dest)
            ::new ((void*)dest) T(*first);
    return dest;
}
template Entry32* uninitialized_move<Entry32>(Entry32*, Entry32*, Entry32*);
}

// ===========================================================================
// @ 0x00eeca60   resource key -> property-derived key
// ===========================================================================
void* __cdecl FUN_00eeca60(void* outv, void* inv)
{
    ResourceKey* out = (ResourceKey*)outv;
    const ResourceKey* in = (const ResourceKey*)inv;
    ResourceKey k = *in;
    if (k.typeID == 0xb1b104) {
        IntrusivePtr<IPropList> ptr;
        PropMgr* pm = FUN_0067de30();
        if (pm->GetPropertyList(k.instanceID, k.groupID, &ptr)) {
            if ((g_16c78c0 & 1) == 0) {
                g_16c78c0 |= 1;
                g_16c78bc = FUN_00932e80("powerupType", 0x811c9dc5, 1);
            }
            if (ptr) {
                void* prop;
                if (((IPropList*)ptr)->Get(g_16c78bc, &prop) &&
                    *(uint16_t*)((char*)prop + 0x12) == 10) {
                    out->instanceID = 0;
                    out->typeID = 0xf0000001;
                    out->groupID = 0;
                    return out;
                }
                GetPropertyAsKey((IPropList*)ptr, 0x7106c14, &k);
            }
        }
    }
    *out = k;
    return out;
}

// ===========================================================================
// @ 0x00eecba0   resource lookup -> entry id
// ===========================================================================
struct IRes {
    virtual void s0();
    virtual void Release();
    virtual void s2();
    virtual void* Cast(uint32_t id);        // +0x0c
};
struct ResMgr {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual bool Find(void* p, IRes** out, int a, int b, int c, int d);   // +0x0c
};
ResMgr* __cdecl GetManager();

struct Ev { uint32_t a, b; int id; };

struct MetaE {
    virtual void v0();
    virtual void Release();                 // +0x04
    char pad8[0x18 - 8];
    void* FUN_5507a0();                     // returns this+0x18
};
struct MetaO {
    virtual void v0();
    virtual void Release();                 // +0x04
    char pad8[0x18 - 8];
    int  m18;                               // +0x18
};

int __cdecl f_00eecba0(void* p)
{
    int id = -1;
    IntrusivePtr<IRes> list;
    MetaE* e;
    ResMgr* mgr = GetManager();
    if (!mgr->Find(p, &list, 0, 0, 0, 0))
        goto tail;
    if (!list) {
        e = 0;
        goto rel_e;
    }
    e = (MetaE*)list->Cast(0x670da17);
    if (e) {
        e->v0();
        Ev* it = *(Ev**)e->FUN_5507a0();
        Ev* end = *(Ev**)((char*)e->FUN_5507a0() + 4);
        for (; it != end; ++it) {
            if (it->a == 0x2dc9d1e && it->b == 0x2e1a75d) {
                id = it->id;
                break;
            }
        }
    }
    if (id == -1) {
        MetaO* o = (MetaO*)list->Cast(0x3c609f8);
        if (o) {
            o->v0();
            id = o->m18;
            o->Release();
        }
    }
rel_e:
    if (e)
        e->Release();
tail:
    return id;
}

// ===========================================================================
// @ 0x00eeccb0   creature model state update
// ===========================================================================
struct SubC0  { void* vtbl; };
struct Sub5A8 { void* vtbl; void FUN_00f924e0(float f); };
struct B4cObj { void FUN_00bc97f0(int, float, int, int); };

struct SelfObj {
    void* vtbl;                                  // +0x000
    char  pad04[0xc0 - 0x04];
    SubC0 mC0;                                   // +0x0c0
    char  padc4[0x2a8 - 0xc4];
    float m2a8;                                  // +0x2a8
    char  pad2ac[0x5a8 - 0x2ac];
    Sub5A8 m5a8;                                 // +0x5a8
    char  pad5ac[0xb4c - 0x5ac];
    void* mB4cPtr;                               // +0xb4c
    char  padb50[0xb5e - 0xb50];
    char  mB5e;                                  // +0xb5e

    int  FUN_00c0b760();
    bool Flag388();
    void SetE84(void* p);
    void CheckCreatureModel(int a, int b);
    void FUN_00c0bbe0();
};

struct SpeciesMgr { void* GetSpeciesArchetype(int a, int b); };
SpeciesMgr* __cdecl FUN_00401090();

typedef void  (__thiscall *FnVI)(void*, int);
typedef float (__thiscall *FnVF)(void*);

void __cdecl f_00eeccb0(void* p)
{
    SelfObj* self = (SelfObj*)p;
    float f = ((FnVF)((void**)self->mC0.vtbl)[0x34 / 4])(&self->mC0);
    int state;
    if (g_16c7944 < f)
        state = (g_16c7964 < f) ? 2 : 1;
    else
        state = 0;

    char changed = 0;
    if ((state != 0) != self->FUN_00c0b760()) {
        ((FnVI)((void**)self->vtbl)[0xe8 / 4])(self, state != 0);
        ((B4cObj*)((char*)self->mB4cPtr + 8))->FUN_00bc97f0(0, 1.0f, 0x200000, 0);
        changed = 1;
    }
    if ((state == 2) != self->Flag388()) {
        void* arch;
        if (state == 2) {
            arch = FUN_00401090()->GetSpeciesArchetype(0xb3f34049, 0);
            self->SetE84(arch);
            ((FnVI)((void**)self->vtbl)[0xac / 4])(self, 1);
            self->m2a8 = g_15d96b8;
        } else {
            arch = FUN_00401090()->GetSpeciesArchetype(0x23c18d32, 0);
            self->SetE84(arch);
            ((FnVI)((void**)self->vtbl)[0xac / 4])(self, 1);
        }
        ((B4cObj*)((char*)self->mB4cPtr + 8))->FUN_00bc97f0(0, 1.0f, 0x200000, 0);
        changed = 1;
    }
    if (!self->mB5e) {
        Sub5A8* s = &self->m5a8;
        float v = ((FnVF)((void**)s->vtbl)[0x58 / 4])(s);
        s->FUN_00f924e0(v);
    }
    self->CheckCreatureModel(0, 1);
    if (changed)
        self->FUN_00c0bbe0();
}

// ===========================================================================
// @ 0x00eecf10   hash dispatch (0x3a2511e case reads a bool property)
// ===========================================================================
uint32_t __cdecl f_00eecf10(const void* p)
{
    ResourceKey k;
    uint32_t result = 0xeb5c1d8e;
    FUN_00eeca60(&k, (void*)p);
    switch (k.typeID) {
    case 0x74e0069: return 0x8b8556d8;
    case 0x2a8fb3f: return 0x897f78ad;
    case 0x7b38ba7: return 0x8adff558;
    case 0x3a2511e: {
        IntrusivePtr<IPropList> ptr;
        PropMgr* pm = FUN_0067de30();
        if (pm->GetPropertyList(k.instanceID, k.groupID, &ptr)) {
            bool b = 0;
            GetBoolProperty((IPropList*)ptr, 0x9cb898d3, &b);
            result = b ? 0x0b7e477a : 0x167b1f54;
        }
        break;
    }
    }
    return result;
}

// ===========================================================================
// @ 0x00eed010   noun-property key fetch
// ===========================================================================
uint32_t __cdecl f_00eed010(const ResourceKey* key)
{
    uint32_t result = 0;
    IntrusivePtr<IPropList> ptr;
    PropMgr* pm = FUN_0067de30();
    if (pm->GetPropertyList(key->instanceID, key->groupID, &ptr))
        GetPropertyAsKeyInstance(ptr, 0x5cd8beab, &result);
    return result;
}

// ===========================================================================
// @ 0x00eed090   helper thunk
// ===========================================================================
struct Obj15aca38 { void FUN_00ddddf0(uint32_t hash, int value); };
extern Obj15aca38 g_015aca38;

void __cdecl f_00eed090()
{
    g_015aca38.FUN_00ddddf0(0x55c0377, g_015aca34);
}

// ===========================================================================
// @ 0x00eed0b0   property pair read (bool)
// ===========================================================================
bool __cdecl f_00eed0b0(const ResourceKey* key, float* a, float* b)
{
    switch (key->typeID) {
    case 0xb1b104: {
        ResourceKey k;
        FUN_00eeca60(&k, (void*)key);
        if (k.typeID == 0x2a8fb3f || k.typeID == 0x3a2511e) {
            void* n = NounManager()->FUN_00b21000(k.typeID, k.instanceID);
            if (!n)
                return false;
            void* list = *(void**)((char*)n + 0xc);
            if (!GetPropertyT(list, 0x7611549, a))
                return false;
            if (!GetPropertyT(list, 0x761154f, b))
                return false;
            return true;
        } else if (k.typeID == 0x74e0069 || k.typeID == 0x7b38ba7) {
            IntrusivePtr<IPropList> ptr;
            PropMgr* pm = FUN_0067de30();
            if (pm->GetPropertyList(key->instanceID, key->groupID, &ptr)
                && GetPropertyT(ptr, 0x7611549, a)
                && GetPropertyT(ptr, 0x761154f, b))
                return true;
            return false;
        }
        return false;
    }
    case 0x2399be55:
        *a = g_16c79d4;
        *b = g_16c79e4;
        return true;
    case 0x24682294:
    case 0x476a98c7:
        *a = g_16c79a4;
        *b = g_16c79b4;
        return true;
    case 0x2b978c46:
        break;
    }
    return false;
}

// ===========================================================================
// @ 0x00eed280   property float read (not part of this slice)
// ===========================================================================
float __cdecl f_00eed280(int* key) { (void)key; return 1.0f; }
