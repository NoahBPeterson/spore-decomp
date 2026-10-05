// Slice s00769f20: SP::cGraphicsResourceFactory async job setup / CanConvert /
// CreateResourceAsync helpers. /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void* __cdecl Node8F4d0(void);                                             // 0x68f4d0
void  __cdecl FUN_0068f9b0(void* p);
void  __cdecl FUN_006909b0(void* p);
void  __cdecl FUN_00691380(void* a, void* b);
void  __cdecl FUN_006913c0(void* a, void* b);
void* __cdecl FUN_0068f350(void* a, void* b);
void* __cdecl FUN_0067de70();                                              // 0x67de70
bool  __cdecl FUN_006af150(void* a, void* b, void* c);                     // 0x6af150
void  __cdecl FUN_0068f950(void* p);                                       // 0x68f950
void  __cdecl FUN_0068f9b0b(void* p);
char  __cdecl ReadResourceFromStreamStub(void* self, void* a, void* b, void* c); // 0x769d80
void* __cdecl FUN_00768370v(void* a, void* b, void* c, void* d, void* e);  // 0x768370
char  __cdecl FUN_007666a0v(void* a, void* b, void* c);                    // 0x7666a0
char  __cdecl FUN_00769d80v(void* a, void* b, void* c, void* d);           // 0x769d80
char  __cdecl FUN_00765b30v(void* a, void* b);                             // 0x765b30
char  __cdecl FUN_00765d30v(void* a, void* b);                             // 0x765d30
char  __cdecl FUN_007652c0v(void* a, void* b);                             // 0x7652c0
char  __cdecl FUN_007637d0v(void* a, void* b, int c, void* d);             // 0x7637d0
char  __cdecl FUN_007655f0b(void* a, void* b, void* c);   // 0x7655f0
bool  __fastcall ArmDecodeB(void* self, int, int);         // 0x7677c0
char  __cdecl FUN_0076a940v(void* a, void* b, void* c, void* d, void* e);   // 0x76a940
}

struct M69d80 { char Meth(int a, int b, int c); };
struct C69f { char pad0[0xfc]; int mFC; };
struct C69a9 { char pad0[0x10]; void* m10; char pad14[4]; int m18; char pad1c[0x18]; };

// ===========================================================================
// @ 0x00769f20  async job chain setup (3 sub-jobs + a callback job)
// ===========================================================================
bool __fastcall SetupJobChain(void* self, int, int unused) {
    (void)unused;
    C69f* s = (C69f*)self;
    s->mFC = 3;
    void* a = Node8F4d0();
    ((void(__thiscall**)(void*))*(void***)a)[8](a);
    void* b = Node8F4d0();
    if (b && !((bool(__thiscall**)(void*, int*))*(void***)b)[4](b, (int*)&b))
        return false;
    void* c = Node8F4d0();
    if (c && !((bool(__thiscall**)(void*, int*))*(void***)c)[4](c, (int*)&c))
        return false;
    void* d = Node8F4d0();
    if (d && !((bool(__thiscall**)(void*, int*))*(void***)d)[4](d, (int*)&d))
        return false;
    void* e = Node8F4d0();
    if (e && !((bool(__thiscall**)(void*, int*))*(void***)e)[4](e, (int*)&e))
        return false;
    FUN_0068f9b0(self);
    FUN_006909b0(self);
    return true;
}

// ===========================================================================
// @ 0x0076a300  load a "simple" async resource request
// ===========================================================================
char __fastcall Func76a300(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x18);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69d80*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// ===========================================================================
// @ 0x0076a340  SP::cGraphicsResourceFactory::ReadResource
// ===========================================================================
char __fastcall ReadResource(void* self, int, void* a1, void* a2, void* a3) {
    char* o = (char*)a1;
    void* p = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    // triplet copy
    int t0 = *(int*)p, t1 = *(int*)((char*)p + 4), t2 = *(int*)((char*)p + 8);
    *(int*)(o + 8) = t0;
    *(int*)(o + 0xc) = (int)(size_t)a3;
    *(int*)(o + 0x10) = t2;
    if ((size_t)a3 == 0x2f4e681c) {
        void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
        if (*(int*)((char*)q + 4) == 0x2f4e681b) {
            void* r = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
            void* u = (void*)((int(__thiscall**)(void*, void*, void*))*(void***)self)[7](self, a1, r);
            return FUN_007655f0b(u, a1, r);
        }
    }
    void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    void* t = *(void**)((char*)q + 4);
    void* u = (void*)((int(__thiscall**)(void*, void*, void**, void*))*(void***)self)[6](self, a1, &t, t);
    return FUN_00769d80v(u, a1, &t, t);
}

// ===========================================================================
// @ 0x0076a400  create a single async request job
// ===========================================================================
bool __fastcall CreateRequestJob(void* self, int, void* out) {
    void* n = Node8F4d0();
    int local = 0;
    (void)local;
    if (!((bool(__thiscall**)(void*, int*))*(void***)n)[4](n, &local))
        return false;
    char* lp = (char*)local;
    *(void**)(lp) = (void*)0;          // callback
    *(void**)(lp + 4) = self;
    *(int*)(lp + 0x18) = 1;
    FUN_0068f9b0(self);
    FUN_006909b0(lp);
    *(void**)out = lp;
    return true;
}

// ===========================================================================
// @ 0x0076a4d0  try-lock two jobs and chain a 4-step job
// ===========================================================================
bool __fastcall TryLockChain(void* self, int, int unused) {
    (void)unused;
    void* a = Node8F4d0();
    ((void(__thiscall**)(void*))*(void***)a)[8](a);
    void* b = Node8F4d0();
    if (!((bool(__thiscall**)(void*, int*))*(void***)b)[4](b, (int*)&b))
        return false;
    void* c = Node8F4d0();
    if (!((bool(__thiscall**)(void*, int*))*(void***)c)[4](c, (int*)&c))
        return false;
    int x = 0, y = 0;
    if (!FUN_0068f350(&x, &y))
        return false;
    FUN_0068f9b0(self);
    return true;
}

// ===========================================================================
// @ 0x0076a720  SP::cGraphicsResourceFactory::CanConvert
// ===========================================================================
bool __fastcall CanConvert(void* self, int, void* out) {
    C69a9* s = (C69a9*)self;
    void* a = Node8F4d0();
    ((void(__thiscall**)(void*))*(void***)a)[8](a);
    int holder = 0;
    int type = s->m18;
    char r;
    if (type < 0x2f4e681c) {
        if (type == 0x2f4e681b) r = FUN_00765b30v(self, &holder);
        else if (type == 0xe6bce5) r = SetupJobChain(self, 0, 0);
        else if (type == 0x1c135da) r = TryLockChain(self, 0, 0);
        else r = CreateRequestJob(self, 0, &holder);
    } else if (type == 0x2f4e681c) {
        void* p = (void*)((int(__thiscall**)(void*))*(void***)s->m10)[4](s->m10);
        uint32_t sub = *(uint32_t*)((char*)p + 4);
        if (sub < 0x2f7d0005) {
            if (sub == 0x2f7d0004) r = FUN_007652c0v(self, &holder);
            else if (sub == 0x2f4e681b) r = FUN_00765d30v(self, &holder);
            else if (sub == 0x2f4e681c) r = ArmDecodeB(self, 0, 0);
            else return false;
        } else if (sub == 0x2f7d0007) r = FUN_007652c0v(self, &holder);
        else return false;
    } else {
        r = CreateRequestJob(self, 0, &holder);
    }
    if (!r)
        return false;
    *(void**)out = (void*)holder;
    return true;
}

// ===========================================================================
// @ 0x0076a940  SP::cGraphicsResourceFactory::CreateConvertedResourceAsync
// ===========================================================================
bool __cdecl CreateConvertedResourceAsync(void* a, void* b, void* c, int* d, void* e) {
    if (!FUN_0067de70())
        return false;
    void* res = 0;
    int t = ((int(__thiscall**)(int*))*(void***)d)[4](d);
    if (!FUN_007666a0v(&res, e, *(void**)((char*)t + 4)))
        return false;
    void* job = Alloc6(0x338, "Graphics", 0, 0, 0, 0);
    if (job)
        job = FUN_00768370v(res, b, c, d, e);
    if (job)
        ((void(__thiscall**)(void*))*(void***)job)[0](job);
    ((void(__thiscall**)(int*))*(void***)d)[8](d);
    return true;
}

// ===========================================================================
// @ 0x0076ac30  SP::cGraphicsResourceFactory::CreateResourceAsync
// ===========================================================================
bool __fastcall CreateResourceAsync(void* self, int, void* out, int* param_4, void* p5, void* p6, int p7) {
    int* local = 0;
    if (p7 == 0)
        p7 = ((int(__thiscall**)(int*))*(void***)param_4)[4](param_4);
    char r = FUN_0076a940v(&local, self, (void*)p7, param_4, p6);
    if (!r) {
        if (local)
            ((void(__thiscall**)(int*))*(void***)local)[1](local);
        return false;
    }
    *(int**)out = local;
    (void)p5;
    return true;
}
