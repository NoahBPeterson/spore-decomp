// slice s00eec5c0 -- editor/creature resource-key and property helpers.
//
// Several very large dispatch/float routines are PARTIAL (marked below).  The smaller
// accessors are reproduced faithfully.
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

void  __cdecl   FUN_00eeca60(void* out, void* in);
void  __cdecl   FUN_00ddddf0_helper();
int   __cdecl   FUN_00efe5a0();
void  __cdecl   FUN_00b18530();
void  __cdecl   FUN_00bcd420();
void  __cdecl   operator_delete(void* p);
void  __cdecl   FUN_00407190();

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
// @ 0x00eecf10   hash dispatch (0x3a2511e case reads a bool property)
// ===========================================================================
int __cdecl f_00eecf10(int* param)
{
    int local_c, local_8, local_4;
    int result = 0xeb5c1d8e;
    FUN_00eeca60(&local_c, param);
    switch ((unsigned)local_8) {
    case 0x74e0069: return 0x8b8556d8;
    case 0x2a8fb3f: return 0x897f78ad;
    case 0x7b38ba7: return 0x8adff558;
    case 0x3a2511e: {
        int* pm = (int*)0;
        (void)pm;
        // property manager path; returns 0xf5032826/0x167b1f54 split based on GetBoolProperty
        result = 0x167b1f54;
        break;
    }
    }
    return result;
}

// ===========================================================================
// @ 0x00eed090
// ===========================================================================
void __cdecl f_00eed090()
{
    FUN_00ddddf0_helper();
}

// ===========================================================================
// @ 0x00eec5c0   rounding dispatch (PARTIAL)
// ===========================================================================
float __cdecl f_00eec5c0(int* param)
{
    (void)param;
    // Big switch over the resource-type dword: each arm rounds a scaled float.
    // x87 / cvtss2si + cmovb "ceil" sequence not transcribed.
    return 1.0f;
}

// ===========================================================================
// @ 0x00eec760   property reads into a 3-int key (PARTIAL)
// ===========================================================================
void __cdecl f_00eec760(void* obj, int* out)
{
    (void)obj; (void)out;
    // Reads three hashed properties via vtable slot 0x24 and stores the results.
    // Not transcribed.
}

// ===========================================================================
// @ 0x00eec9c0   0x20-byte struct copy loop (PARTIAL: x87 field copies)
// ===========================================================================
void __cdecl f_00eec9c0(void* begin, void* end, void* dst)
{
    (void)begin; (void)end; (void)dst;
    // __thiscall FUN_00eec2b0-adjacent 8-dword copy; not transcribed.
}

// ===========================================================================
// @ 0x00eed010   noun-property key fetch (PARTIAL)
// ===========================================================================
void* __cdecl f_00eed010(int* param)
{
    (void)param;
    return 0;
}

// ===========================================================================
// @ 0x00eeca60   resource type -> property key (PARTIAL)
// ===========================================================================
void __cdecl f_00eeca60(int* out, int* in)
{
    (void)out; (void)in;
}

// ===========================================================================
// @ 0x00eecba0 / 0x00eeccb0 / 0x00eed0b0 / 0x00eed280   (PARTIAL)
// ===========================================================================
int __cdecl f_00eecba0(int key) { (void)key; return -1; }
void __fastcall f_00eeccb0(void* self, int dummy) { (void)self; (void)dummy; }
bool __cdecl f_00eed0b0(int* key, float* a, float* b) { (void)key; (void)a; (void)b; return false; }
float __cdecl f_00eed280(int* key) { (void)key; return 1.0f; }
