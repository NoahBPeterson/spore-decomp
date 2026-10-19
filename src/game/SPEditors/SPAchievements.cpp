// src/game/SPEditors/SPAchievements.cpp -- migrated from slice(s) s0067a590, s00679630, s006755c0, s00674640 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAchievements.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern void EA_IO_WriteUint32(void* w, void* p, int n, int a); // 0x0093aa70
extern char g_1529330;   // [0x01529330]
#include <string.h>
#include <wchar.h>
#pragma intrinsic(strlen, wcscmp, wcslen)

// ---- items of slice s00674640 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void*  (__thiscall *FnVp0)(void*);
extern void EA_IO_WriteUint32(void* w, void* p, int n, int a); // 0x0093aa70
void WriteIntVal(int* io, int v) {
    int* o = (int*)((FnVp0)((VObj*)io)->vt[0x20 / 4])(io);
    void* w = (void*)((FnVp0)((VObj*)o)->vt[0x18 / 4])(o);
    EA_IO_WriteUint32(w, &v, 1, 0);
}
struct cVarListSerializer {
    char data[0x18];
    cVarListSerializer(void* owner, void* key, int id);  // 0x00692f90
    void Serialize(int* io);                             // 0x00692900
};
struct CVarList {
    char pad[0xc];
    int* mpBegin;  // +0xc
    int* mpEnd;    // +0x10
    void Serialize(int* io);
};
extern char g_1529330;   // [0x01529330]
// ---- items of slice s00674640 end

// ---- items of slice s00679630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
void DeleteObj(void* p);              // 0x00f47380
void* __cdecl MessageServer();        // 0x0067dcc0
void  __fastcall FUN_00929c60(char* p);
void  __fastcall FUN_00816990(char* p);
void  __fastcall FUN_00678f70(char* p);   // = 0x00678f70 (matched in s006783c0)
struct Elem {
    char data[0x134];
    void CopyFrom(Elem* other);   // 0x00679b40 (defined elsewhere)
    void AssignFrom(Elem* other); // 0x00679c90 (defined elsewhere)
};
struct Container {
    void Push(Elem* other);    // 0x00679ff0
    void Process(Elem* local); // 0x00679e50 (defined elsewhere)
    void Shutdown();           // 0x0067a090
};
struct PropUI2 { char Update(char* a); };
// ---- items of slice s00679630 end

// ---- items of slice s0067a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl ConfigManager();     // FUN_0067dd30
extern "C" void* __cdecl GetManager();        // FUN_00957f30
extern "C" void* __cdecl FUN_0067caf0();
extern "C" void __cdecl BeginModal(void*, int, int);   // SPUIHelpers::BeginModal
extern "C" void __cdecl EndModal(void*, int, int);     // SPUIHelpers::EndModal
static inline void** VT(void* p) { return *(void***)p; }
struct HM590;
struct Elem134 {
    char data[0x134];
    Elem134(Elem134* src);   // 679b40
    ~Elem134();              // 678f70
};
struct Sub10 {
    char p0[8];
    Elem134* begin;          // +8  (abs +0x18)
    char p1[0xc];
    Elem134* end;            // +0x18 (abs +0x28)
    void Release();          // 6792f0
};
struct Sub1fc {
    void method(int);        // 92a7a0
};
struct HM590 {
    char pad0[0x10];
    Sub10 sub;               // +0x10
    char pad1[0x1cc];
    void Start();            // 67a120
    bool Check(Elem134*);    // 67a1b0
    void Add(Elem134*);      // 679e50
    void possibly(char a, char b);
};
struct C_a590_fwd {
    void possibly(int a, int b);
};
struct C_a120_h {
    void f_67a120();
};
struct C_a6a0 {
    bool handle(int msg, void* data);
};
bool C_a6a0::handle(int msg, void* data)
{
    (void)data;
    if (msg == 0x670eccd) {
        void* cm = ConfigManager();
        if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
            ((C_a120_h*)((char*)this - 0xc))->f_67a120();
        return true;
    }
    return false;
}
struct Proc {
    virtual bool Evaluate(int conditionID) = 0;
};
struct VecU {
    int* begin;   // +0
    int* end;     // +4
};
struct C_af {
    char pad0[0xc];
    Proc** pbegin;   // +0xc
    Proc** pend;     // +0x10
    bool All(VecU* v);
    bool Any(VecU* v);
    bool Check(void* a);
};
bool C_af::Any(VecU* v)
{
    unsigned n = (unsigned)(v->end - v->begin) >> 2;
    for (unsigned i = 0; i < n; ++i) {
        if (pend != pbegin) {
            Proc* p = *(pend - 1);
            if (p->Evaluate(v->begin[i]))
                return false;
        }
    }
    return true;
}
bool C_af::Check(void* a)
{
    char* b = (char*)a;
    if (!All((VecU*)(b + 0xc)))
        return false;
    if (((*(int*)(b + 0x24) - *(int*)(b + 0x20)) & 0xfffffffc) != 0
        && !Any((VecU*)(b + 0x20)))
        return false;
    if (((*(int*)(b + 0x38) - *(int*)(b + 0x34)) & 0xfffffffc) != 0
        && All((VecU*)(b + 0x34)))
        return false;
    return true;
}
struct VecHM {
    void clear(int* begin, int* end);   // FUN_00a693f0
    int* begin;
    int* end;
    int* cap;
};
struct HM6e0 {
    char pad0[0xec];
    void* p_ec;          // +0xec
    char padF0[0x199 - 0xf0];
    char b199;           // +0x199
    char pad19a[0x1f4 - 0x19a];
    char sub1f4[4];      // +0x1f4
    bool handle(void* a, int* b);
};
// ---- items of slice s0067a590 end

// @ 0x006751c0
bool __stdcall FUN_006751c0(unsigned* p)
{
    switch ((*p >> 8) & 7) {
    case 0: return p[1] >= p[2];
    case 1: return p[1] > p[2];
    case 2: return p[1] == p[2];
    case 3: return p[1] < p[2];
    case 4: return p[1] <= p[2];
    case 5: return p[1] != p[2];
    default: return false;
    }
}

// @ 0x00675260
void CVarList::Serialize(int* io)
{
    WriteIntVal(io, 1);
    WriteIntVal(io, (mpEnd - mpBegin) >> 4);
    for (int* p = mpBegin; p != mpEnd; p += 4) {
        WriteIntVal(io, p[0]);
        WriteIntVal(io, p[2]);
    }
    cVarListSerializer s((void*)this, &g_1529330, 0x1a80d26);
    s.Serialize(io);
}

// @ 0x00675d70
void FUN_00675D70()
{}

// @ 0x006763e0
void FUN_006763E0()
{}

// @ 0x006764f0
void FUN_006764F0()
{}

// @ 0x0067a090
void Container::Shutdown()
{
    char* thisp = (char*)this;
    void* set = thisp ? thisp + 0xc : 0;
    void* srv = MessageServer();
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, set, 0x670eccd, -0x270f);
    FUN_00929c60(thisp + 0x1b4);
    FUN_00929c60(thisp + 0x1d8);
    FUN_00929c60(thisp + 0x1fc);
    int e = *(int*)(thisp + 0x18);
    if (e != *(int*)(thisp + 0x28)) {
        Elem local;
        local.CopyFrom((Elem*)e);
        char* lp = (char*)&local;
        if (*(void**)(lp + 0xac)) FUN_00816990(*(char**)(lp + 0xac));
        FUN_00678f70(lp);
    }
}

// @ 0x0067a120
void __fastcall FUN_0067a120(char* p)
{
    if (*(int*)(p + 0x18) == *(int*)(p + 0x28)) return;
    do {
        Elem local;
        char* elem = *(char**)(p + 0x18);
        local.CopyFrom((Elem*)elem);
        int n = (int)elem + 0x134;
        if (n == *(int*)(p + 0x20)) {
            FUN_00678f70(elem);
            if (*(int*)(p + 0x1c)) DeleteObj(*(void**)(p + 0x1c));
            int* q = (int*)(*(int*)(p + 0x24) + 4);
            *(int**)(p + 0x24) = q;
            int v = *q;
            *(int*)(p + 0x1c) = v;
            *(int*)(p + 0x20) = v + 0x4d0;
            *(int*)(p + 0x18) = *(int*)(p + 0x1c);
        } else {
            *(int*)(p + 0x18) = n;
            FUN_00678f70(elem);
        }
        ((Container*)p)->Process(&local);
        FUN_00678f70((char*)&local);
    } while (*(int*)(p + 0x18) != *(int*)(p + 0x28));
}

// @ 0x0067a1b0
char PropUI2::Update(char* a)
{ (void)a; return 0; }

// @ 0x0067a590
void HM590::possibly(char a, char b)
{
    (void)a;
    void* cm = ConfigManager();
    if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
        Start();
    if (b) {
        ((Sub1fc*)((char*)this + 0x1fc))->method(1);
        return;
    }
    if (sub.begin != sub.end) {
        Elem134 t(sub.begin);
        if (*(int*)((char*)&t + 0xac) != 0) {
            sub.Release();
            Add(&t);
        }
        while (sub.begin != sub.end) {
            if (Check(sub.begin))
                break;
            Elem134 t2(sub.begin);
            sub.Release();
            Add(&t2);
            t2.~Elem134();
        }
        t.~Elem134();
    }
}

// @ 0x0067a680
void __stdcall cb_67a680(void* unused, void* data)
{
    C_a590_fwd* r = (C_a590_fwd*)FUN_0067caf0();
    if (r)
        r->possibly((int)data, 1);
}

// @ 0x0067a6a0
bool HM6e0::handle(void* a, int* b)
{
    if (!p_ec)
        return false;
    int type = b[2];
    if (type != 8) {
        if (type != 6 && type != 0x287259f6)
            return false;
        if (a != p_ec)
            return false;
        b199 = 1;
        ((C_a590_fwd*)((char*)this - 8))->possibly(0, 0);
        ((VecHM*)((char*)this + 0x1f4))->clear(0, 0);
        return false;
    }
    float v0 = *(float*)((char*)b + 0xc);
    float v1 = *(float*)((char*)b + 0x10);
    float loc[2];
    loc[0] = v0;
    loc[1] = v1;
    float out[2];
    ((void (__thiscall*)(void*, float*, float, float))VT(a)[0xc0 / 4])(a, out, v0, v1);
    void* p2 = ((void* (__thiscall*)(void*))VT(a)[0x14 / 4])(a);
    void* p3 = ((void* (__thiscall*)(void*, float*))VT(p2)[0x44 / 4])(p2, loc);
    void* m = GetManager();
    int c = ((int (__thiscall*)(void*, void*))VT(m)[0x80 / 4])(m, p_ec);
    void* cur = p_ec;
    if (cur == a) {
        if (c == 0) {
            if (p3 != cur)
                return false;
            BeginModal(cur, 0, 0);
        } else {
            if (p3 == cur)
                return false;
            EndModal(cur, 0, 0);
        }
    } else {
        if (c != 0)
            return false;
        if (p3 != cur)
            return false;
        BeginModal(cur, 0, 0);
    }
    float saved = loc[1];
    for (int i = 0; i < 7; ++i)
        ((int*)loc)[i] = b[i];
    loc[0] = v1;
    loc[1] = out[0];
    void* m2 = GetManager();
    ((void (__thiscall*)(void*, int, int, float*))VT(m2)[0x18 / 4])(m2, 0, 0, loc);
    return true;
}

// @ 0x0067a850
void __cdecl cb_67a850(void* p)
{
    C_a590_fwd* o = (C_a590_fwd*)p;
    if (o)
        ((void (__thiscall*)(void*))VT(o)[1])(o);
    o->possibly(0, 0);
    if (o)
        ((void (__thiscall*)(void*))VT(o)[2])(o);
}
