// Slice s00c06630 - Simulator::cCreatureAnimal ctor + EASTL vector/heap helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void* P;
struct E32 { uint32_t d[8]; };

// 0x011e0744 is a jump thunk (memcpy/memmove-family); call it directly so the
// call is a direct E8 with a masked relocation (matching the original).
void __cdecl FUN_011e0744(void*, const void*, size_t);
#define memmove(d, s, n) FUN_011e0744((d), (s), (n))

// ---- external callees -------------------------------------------------
struct Pool { void __thiscall Alloc(void*); };                 // 0x00c06070
struct VObj { virtual void v0(); virtual void v1(); virtual void v2(); };
void __cdecl FUN_00c06120(P*, P*, P);                          // 0x00c06120
void __cdecl FUN_00c06160(P*, P*, P);                          // 0x00c06160
void __cdecl FUN_00c04960(P*, int, int, int, P, P);            // 0x00c04960
E32* __cdecl FUN_00c033a0(E32*, E32*, E32*);                   // 0x00c033a0
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl operator_delete__(void*);                        // 0xf47380
void  __cdecl FUN_00ac4190(int);                               // 0x00ac4190
void  __cdecl FUN_00d7ca90(void*);                             // 0x00d7ca90
void* __cdecl FUN_00b3d310();                                  // 0x00b3d310
void* __cdecl FUN_00c06000();                                  // 0x00c06000
void  __cdecl FUN_00c0d3a0(void*);                             // 0x00c0d3a0
void* __cdecl SP_GetCurrentGameMode();                         // 0x00b5b800
void* __cdecl FUN_00b18530(void*);                             // 0x00b18530
void* __cdecl FUN_00f3c0e0(void*);                             // 0x00f3c0e0
void  __cdecl FUN_00d9a290(void*, void*, void*);               // 0x00d9a290
void* __cdecl FUN_00ec1ff0(void*, void*);                      // 0x00ec1ff0
void  __cdecl FUN_00bc97f0(void*, int, int, float, int);       // 0x00bc97f0

struct BaseCtor   { void __thiscall ctor(); };                 // 0x00c1f8d0
struct Gonzago    { void __thiscall ctor(); };                 // 0x00b63890
struct SPTimer    { void __thiscall Restart(); };              // 0x00bc3130
struct Fn421b0    { void __thiscall f(void*); };               // 0x00c421b0
struct Fnbc9c10   { void __thiscall ctor(); };                 // 0x00bc9c10
struct Fn1fe80    { void __thiscall f(); };                    // 0x00c1fe80
struct Fn9de0     { void __thiscall f(int); };                 // 0x00bc9de0
struct Fn05ee0    { void __thiscall f(); };                    // 0x00c05ee0
struct Fn1c9f0    { void __thiscall f(int); };                 // 0x00c1c9f0
struct Fn3170     { void __thiscall f(); };                    // 0x00bc3170
struct Fnbfc470   { void __thiscall f(uint8_t); };             // 0x00bfc470
struct Fnbfc460   { void __thiscall f(int); };                 // 0x00bfc460
struct Fn8e7f80   { int  __thiscall f(); };                    // 0x008e7f80
struct Fnc0c0e0   { bool __thiscall f(int,int); };             // 0x00c0c0e0
struct Fnc12310   { void __thiscall f(int); };                 // 0x00c12310
struct Fnc06b10   { void __thiscall f(void*); };               // 0x00c06b10
struct Fnbcb660   { void __thiscall f(void*); };               // 0x00bcb660
struct Fnf25080   { bool __thiscall f(void*); };               // 0x00f25080
struct Fnc7dc20   { void __thiscall f(); };                    // 0x00c7dc20

#define ERASE_ALL(self, off) do { \
    P* end_ = *(P**)((char*)(self)+(off)+4); \
    P* beg_ = *(P**)((char*)(self)+(off)); \
    memmove(beg_, end_, (char*)end_ - (char*)end_); \
    int d_ = (int)end_ - (int)beg_; d_ >>= 2; d_ = -d_; d_ += d_; d_ += d_; \
    *(int*)((char*)(self)+(off)+4) += d_; } while(0)

// ======================================================================
// @ 0x00c06630  eastl partial_sort(first, middle, last, comp)
void __cdecl FUN_00c06630(P* base, P* first, P* last, P key) {
    FUN_00c06120(base, first, key);
    for (P* p = first; p < last; ++p) {
        if (*(float*)*base > *(float*)*p) {
            P cur = *p;
            *p = *base;
            FUN_00c04960(base, 0, (int)(first - base), 0, cur, key);
        }
    }
    FUN_00c06160(base, first, key);
}

// ======================================================================
// @ 0x00c066a0  pool node emplace (refcounted first field)
void* __cdecl FUN_00c066a0(char* c, P* value, float f, uint8_t b1, uint8_t b2) {
    int local_8 = 0, local_4 = 0;
    char local_14[12];
    int iVar2 = *(int*)(c + 0x18);
    if (iVar2 + 0x14 == *(int*)(c + 0x20)) {
        local_8 = 0; local_4 = 0;
        ((Pool*)c)->Alloc(local_14);
    } else {
        *(int*)(c + 0x18) = iVar2 + 0x14;
        if (iVar2 != 0) { *(int*)(iVar2 + 0xc) = 0; *(int*)(iVar2 + 0x10) = 0; }
    }
    iVar2 = *(int*)(c + 0x18);
    if (iVar2 == *(int*)(c + 0x1c)) iVar2 = *(int*)(*(int*)(c + 0x24) - 4) + 0xa0;
    void* old = *(void**)(iVar2 - 8);
    if (value != old) {
        if (value) ((VObj*)value)->v0();
        *(void**)(iVar2 - 8) = value;
        if (old) ((VObj*)old)->v1();
    }
    char* r = (char*)(iVar2 - 0x14);
    *(float*)r = f;
    r[4] = b1;
    r[5] = b2;
    (void)local_8; (void)local_4;
    return r;
}

// ======================================================================
// @ 0x00c06750  pool node emplace (ptr at +8, refcount at +0x10)
void* __cdecl FUN_00c06750(char* c, P value, float f, uint8_t b1, uint8_t b2) {
    int local_8 = 0, local_4 = 0;
    char local_14[12];
    int iVar2 = *(int*)(c + 0x18);
    if (iVar2 + 0x14 == *(int*)(c + 0x20)) {
        local_8 = 0; local_4 = 0;
        ((Pool*)c)->Alloc(local_14);
    } else {
        *(int*)(c + 0x18) = iVar2 + 0x14;
        if (iVar2 != 0) { *(int*)(iVar2 + 0xc) = 0; *(int*)(iVar2 + 0x10) = 0; }
    }
    iVar2 = *(int*)(c + 0x18);
    if (iVar2 == *(int*)(c + 0x1c)) iVar2 = *(int*)(*(int*)(c + 0x24) - 4) + 0xa0;
    char* r = (char*)(iVar2 - 0x14);
    *(void**)(r + 8) = value;
    *(float*)r = f;
    r[4] = b1;
    r[5] = b2;
    void* old = *(void**)(r + 0x10);
    if (value != old) {
        if (value) ((VObj*)value)->v0();
        *(void**)(r + 0x10) = value;
        if (old) ((VObj*)old)->v1();
    }
    (void)local_8; (void)local_4;
    return r;
}

// ======================================================================
struct VErase { P* mpBegin; P* mpEnd; P* mpCapacity;
    void** __thiscall erase(void** first, void** last); };
// @ 0x00c06bf0
void** __thiscall VErase::erase(void** first, void** last) {
    memmove(first, last, (char*)mpEnd - (char*)last);
    mpEnd = mpEnd - (last - first);
    return first;
}

// ======================================================================
// @ 0x00c06c30  vector insert with grow (32-byte elements)
struct V32 { E32* mpBegin; E32* mpEnd; E32* mpCapacity;
    void __thiscall push_back(E32* p);
    void __thiscall insert(E32* pos, E32* val); };
void __thiscall V32::insert(E32* pos, E32* val) {
    E32* end = mpEnd;
    if (end != mpCapacity) {
        if (pos <= val && val < end) val = val + 1;
        *end = *(end - 1);
        E32* q = end - 1;
        E32* d = end;
        while (q != pos) { --q; --d; *d = *q; }
        *pos = *val;
        mpEnd = end + 1;
        return;
    }
    int n = (int)(end - mpBegin);
    int cap;
    E32* buf;
    if (n <= 0) { cap = 1; }
    else { cap = n * 2; if (cap == 0) { buf = 0; goto haveBuf; } }
    buf = (E32*)operator_new(cap << 5, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
haveBuf:
    E32* r = FUN_00c033a0(mpBegin, pos, buf);
    if (r) *r = *val;
    E32* r2 = FUN_00c033a0(pos, mpEnd, r + 1);
    E32* old = mpBegin;
    if (old != 0 && *(int*)((char*)old - 4) != 0) operator_delete__(old);
    mpEnd = r2;
    mpBegin = buf;
    mpCapacity = (E32*)((char*)buf + (cap << 5));
}

// ======================================================================
// @ 0x00c06d60  depth-limited quicksort with median-of-three
void __cdecl FUN_00c06d60(P* first, P* last, int depth, P key) {
    while ((int)((char*)last - (char*)first) > 0x70) {
        if (depth <= 0) break;
        unsigned n = (unsigned)((char*)last - (char*)first);
        int mid = ((int)(n >> 2)) / 2;
        P* pm = first + mid;
        P* pl = last - 1;
        float a = *(float*)*first;
        float b = *(float*)*pm;
        float c = *(float*)*pl;
        P* pivot = pm;
        if (b > a) {
            if (c > b) pivot = pl;
            else if (c > a) pivot = first;
        } else {
            if (c > a) pivot = first;
            else if (c > b) pivot = pl;
        }
        P piv = *pivot;
        P* i = first;
        P* j = last;
        for (;;) {
            while (*(float*)*i <= *(float*)piv && *(float*)piv != *(float*)*i) ++i;
            do { --j; } while (*(float*)piv < *(float*)*j);
            if (i >= j) break;
            P t = *i; *i = *j; *j = t;
            ++i;
        }
        FUN_00c06d60(i, last, --depth, key);
        last = i;
    }
    if (depth == 0) FUN_00c06630(first, last, last, key);
}

// ======================================================================
// @ 0x00c06800  Simulator::cCreatureAnimal::cCreatureAnimal
struct CCAnimal { char pad[0x1700]; void __thiscall Ctor(); };
void __thiscall CCAnimal::Ctor() {
    char* self = (char*)this;
    ((BaseCtor*)self)->ctor();
    *(uint32_t*)(self + 0x000) = 0x146a0e0;
    *(uint32_t*)(self + 0x004) = 0x146a0cc;
    *(uint32_t*)(self + 0x034) = 0x146a088;
    *(uint32_t*)(self + 0x058) = 0x146a020;
    *(uint32_t*)(self + 0x0c0) = 0x1469f20;
    *(uint32_t*)(self + 0x194) = 0x1469f14;
    *(uint32_t*)(self + 0x590) = 0x1469ef8;
    *(uint32_t*)(self + 0x5a8) = 0x1469e90;
    *(uint32_t*)(self + 0x670) = 0x1469e74;
    self[0xfb8] = 0; self[0xfb9] = 0;
    ((Gonzago*)(self + 0xfc0))->ctor();
    ((Gonzago*)(self + 0xfe0))->ctor();
    *(float*)(self + 0x1000) = 0.0f;
    *(uint32_t*)(self + 0x1004) = 0;
    *(uint32_t*)(self + 0x1008) = 0;
    *(uint32_t*)(self + 0x100c) = 0;
    *(float*)(self + 0x1010) = *(float*)0x157126c;
    *(float*)(self + 0x1014) = *(float*)0x1571270;
    *(float*)(self + 0x1018) = *(float*)0x1571274;
    *(uint32_t*)(self + 0x101c) = 0;
    *(uint32_t*)(self + 0x1020) = 0;
    *(uint32_t*)(self + 0x1024) = 0;
    *(uint32_t*)(self + 0x1028) = 0;
    for (int i = 0; i < 0x28; i += 4) *(uint32_t*)(self + 0x1034 + i) = 0;
    FUN_00ac4190(0);
    for (int i = 0; i < 0x28; i += 4) *(uint32_t*)(self + 0x1060 + i) = 0;
    FUN_00ac4190(0);
    *(uint32_t*)(self + 0x108c) = (uint32_t)(self + 0x10a4);
    *(uint32_t*)(self + 0x1090) = (uint32_t)(self + 0x10a4);
    *(uint32_t*)(self + 0x1094) = (uint32_t)(self + 0x1124);
    *(uint32_t*)(self + 0x10a0) = 0;
    *(uint32_t*)(self + 0x1124) = (uint32_t)(self + 0x113c);
    *(uint32_t*)(self + 0x1128) = (uint32_t)(self + 0x113c);
    *(uint32_t*)(self + 0x112c) = (uint32_t)(self + 0x133c);
    *(uint32_t*)(self + 0x1138) = 0;
    *(uint32_t*)(self + 0x1350) = 0;
    *(uint32_t*)(self + 0x133c) = (uint32_t)(self + 0x1354);
    *(uint32_t*)(self + 0x1340) = (uint32_t)(self + 0x1354);
    *(uint32_t*)(self + 0x1344) = (uint32_t)(self + 0x13d4);
    *(uint32_t*)(self + 0x13d4) = (uint32_t)(self + 0x13ec);
    *(uint32_t*)(self + 0x13d8) = (uint32_t)(self + 0x13ec);
    *(uint32_t*)(self + 0x13dc) = (uint32_t)(self + 0x140c);
    *(uint32_t*)(self + 0x13e8) = 0;
    *(uint32_t*)(self + 0x140c) = (uint32_t)(self + 0x1424);
    *(uint32_t*)(self + 0x1410) = (uint32_t)(self + 0x1424);
    *(uint32_t*)(self + 0x1420) = 0;
    *(uint32_t*)(self + 0x1414) = (uint32_t)(self + 0x1624);
    *(uint32_t*)(self + 0x1624) = 0;
    ((Gonzago*)(self + 0x1628))->ctor();
    *(uint32_t*)(self + 0x1648) = 0;
    *(uint32_t*)(self + 0x164c) = 0;
    *(uint32_t*)(self + 0x1650) = 1;
    *(float*)(self + 0x1654) = 0.0f;
    *(float*)(self + 0x1658) = 0.0f;
    *(float*)(self + 0x165c) = 0.0f;
    *(float*)(self + 0x1660) = 0.0f;
    *(uint32_t*)(self + 0x1664) = 5;
    *(uint32_t*)(self + 0x1668) = 0;
    self[0x166d] = 0;
    *(uint32_t*)(self + 0x1670) = 0;
    *(uint32_t*)(self + 0x1674) = 0;
    *(uint32_t*)(self + 0x1678) = 0;
    *(float*)(self + 0x167c) = 0.0f;
    *(uint32_t*)(self + 0x1680) = 0;
    *(uint32_t*)(self + 0x1684) = 0;
    *(uint32_t*)(self + 0x1688) = 0;
    *(float*)(self + 0x168c) = 0.0f;
    *(float*)(self + 0x1690) = 0.0f;
    *(float*)(self + 0x1694) = 0.0f;
    *(uint32_t*)(self + 0x1698) = 0;
    *(float*)(self + 0x169c) = 0.0f;
    *(uint32_t*)(self + 0x2b0) = 0;
    void* eax = FUN_00b3d310();
    void* v = FUN_00c06000();
    ((Fn421b0*)(self + 0xc0))->f(v);
    (void)eax;
    void* mem = operator_new(0xe4, "Simulator/cAIMemory", 0, 0, 0, 0);
    if (mem != 0) { ((Fnbc9c10*)mem)->ctor(); }
    else mem = 0;
    FUN_00d7ca90(self);
    *(void**)(self + 0x1624) = mem;
    ((SPTimer*)(self + 0xfc0))->Restart();
}

// ======================================================================
// @ 0x00c06e50  Simulator::cCreatureBase::funcC4h
struct CCBeh { char pad[0x1700]; void __thiscall funcC4h(); };
void __thiscall CCBeh::funcC4h() {
    char* self = (char*)this;
    ((Fn1fe80*)self)->f();
    FUN_00c0d3a0(self);
    ((Fn9de0*)(self + 0x1624))->f(-1);
    ERASE_ALL(self, 0x108c);
    ERASE_ALL(self, 0x1124);
    ERASE_ALL(self, 0x133c);
    ERASE_ALL(self, 0x13d4);
    ERASE_ALL(self, 0x140c);
    ((Fn05ee0*)(self + 0x1034))->f();
    ((Fn05ee0*)(self + 0x1060))->f();
    (*(void(__thiscall**)(void*,int))((*(void***)self)[0x48/4]))(self, -1);
}

// ======================================================================
// @ 0x00c07400  Simulator::cCreatureBase::funcCCh
struct CCCh { char pad[0x1700]; void __thiscall funcCCh(int a); };
void __thiscall CCCh::funcCCh(int a) {
    char* self = (char*)this;
    ((Fn1c9f0*)self)->f(a);
    self[0xe38] = 0;
    ((SPTimer*)(self + 0xfc0))->Restart();
    ((Fn3170*)(self + 0xfe0))->f();
    *(float*)(self + 0x1000) = 0.0f;
    ERASE_ALL(self, 0x1020);
    *(uint32_t*)(self + 0x1678) = 0;
    *(uint32_t*)(self + 0x101c) = 0;
}

// ======================================================================
// @ 0x00c06f70  Simulator::cCreatureBase::Tick (tribe destroy tool)
struct CTick { char pad[0x1700]; void __thiscall Tick(); };
void __thiscall CTick::Tick() {
    char* self = (char*)this;
    if (((*(uint32_t*)(self + 0xb58) >> 9) & 1) != 0) return;
    void* ebp = 0;
    void* gm = SP_GetCurrentGameMode();
    if (gm == (void*)0x1654c10) {
        void* d = FUN_00b18530(self);
        if (d != 0) {
            void* p = *(void**)0x16c7aa4;
            void* q = *(void**)((char*)p + 0x74);
            int idx = (int)FUN_00f3c0e0(q);
            ebp = (char*)*(int*)((char*)d + 0x70) + idx * 0x4e0;
        }
    }
    void* g = *(void**)0x16c7aa4;
    void* a = *(void**)((char*)g + 0x78);
    void* edi = *(void**)((char*)a + 0xb8);
    void* vt = *(void**)self;
    int v;
    v = (*(int(__thiscall**)(void*,void*))((*(void***)(self + 0xc0))[0x2c/4]))((void*)(self + 0xc0), (void*)(self + 0x1648));
    FUN_00d9a290(edi, *(void**)(self + 0x18), (void*)v);
    edi = self + 0x5a8;
    ((Fnbfc470*)edi)->f(*(uint8_t*)((char*)ebp + 1));
    if (*(uint8_t*)((char*)ebp + 2) != 0) {
        if (((Fn8e7f80*)edi)->f() != 2) {
            float f = *(float*)(self + 0x5e0) + *(float*)0x1485720;
            (*(void(__thiscall**)(void*,float,int,int,void*,int))((*(void***)edi)[0x18/4]))(
                edi, f, -1, 2, (void*)0x168d8c4, 0);
            ((Fnbfc460*)edi)->f(2);
            bool b = ((Fnc0c0e0*)self)->f(-1, 1);
            ((Fnc12310*)self)->f((int)(0x5807346 - (b ? 1 : 0)));
            self[0xb5e] = 1;
        }
    } else {
        int n = *(int*)((char*)*(void**)((char*)*(void**)0x16c7aa4 + 0x78) + 0xb8);
        if (n > 0) {
            void* d = FUN_00b18530(self);
            if (d != 0 && *(uint8_t*)((char*)*(int*)((char*)d + 0x70) + n * 0x4e0 - 0x4de) == 1) {
                (*(void(__thiscall**)(void*,int))((*(void***)edi)[0x2c/4]))(edi, 0);
                self[0xb5e] = 0;
            }
        }
    }
    if (*(uint8_t*)((char*)ebp + 0x4c8) == 0) {
        int n = *(int*)((char*)*(void**)((char*)*(void**)0x16c7aa4 + 0x78) + 0xb8);
        if (n <= 0) {
            ((Fnc7dc20*)(self + 0x670))->f();
            void* fl = *(void**)(self + 0xb4c);
            bool b = ((Fnc0c0e0*)self)->f(-1, 1);
            *(int*)((char*)fl + 0x5fc) |= ((b ? -1 : 0) & 0x80);
        } else {
            void* d = FUN_00b18530(self);
            void* e = (char*)*(int*)((char*)d + 0x70) + n * 0x4e0 - 0x4e0;
            if (((Fnf25080*)ebp)->f(e)) {
                FUN_00bc97f0((char*)*(void**)(self + 0xb4c) + 8, 0x8000000, 0, *(float*)0x1469e30, 0);
            }
        }
    }
    void* fl = *(void**)(self + 0xb4c);
    *(int*)((char*)fl + 0x5fc) &= 0xfdfffff;
    fl = *(void**)(self + 0xb4c);
    *(int*)((char*)fl + 0x5fc) &= 0xfffdffff;
    if (*(uint8_t*)((char*)ebp + 0x4c8) == 0) {
        switch (*(int*)((char*)ebp + 0x4ac)) {
        case 1: *(int*)((char*)fl + 0x5fc) |= 0x10000000; break;
        case 2: *(int*)((char*)fl + 0x5fc) |= 0x40000000; break;
        case 3: *(int*)((char*)fl + 0x5fc) |= 0x80000000; break;
        case 4: *(int*)((char*)fl + 0x5fc) |= 0x200000; break;
        case 5: *(int*)((char*)fl + 0x5fc) |= 0x20000000; break;
        }
        if (*(int*)((char*)ebp + 0x4b8) == 1) {
            fl = *(void**)(self + 0xb4c);
            *(int*)((char*)fl + 0x5fc) |= 0x20000;
        }
    }
    int r = (*(int(__thiscall**)(void*))((*(void***)self)[0xd8/4]))(self);
    if (r > 4) {
        fl = *(void**)(self + 0xb4c);
        *(int*)((char*)fl + 0x5fc) |= 0x200;
    }
    (*(void(__thiscall**)(void*))((*(void***)(self + 0xc0))[0xf4/4]))((void*)(self + 0xc0));
    *(float*)(self + 0x32c) = *(float*)((char*)ebp + 0x484);
}

// ======================================================================
// @ 0x00c072b0
struct V32B { E32* mpBegin; E32* mpEnd; E32* mpCapacity;
    void __thiscall push_back(E32* p); };
void __thiscall V32B::push_back(E32* p) {
    E32* e = mpEnd;
    if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = *p; }
    else { ((V32*)this)->insert(e, p); }
}

// @ 0x00c072f0
struct V4Stub { P* a; P* b; P* c; void __thiscall insert(P*, P*); }; // 0x00b96600
struct V4 { P* mpBegin; P* mpEnd; P* mpCapacity;
    void __thiscall push_back(P* p); };
void __thiscall V4::push_back(P* p) {
    P* e = mpEnd;
    if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = *p; }
    else { ((V4Stub*)this)->insert(e, p); }
}

// ======================================================================
// @ 0x00c073a0
struct CSetId { char pad[0x1700]; void __thiscall set(int id); };
void __thiscall CSetId::set(int id) {
    char* self = (char*)this;
    *(int*)(self + 0xe8c) = id;
    if (id == -1) {
        *(int*)(self + 0xe90) = -1;
        *(float*)(self + 0xe94) = 0.0f;
        P* end = *(P**)(self + 0xe9c);
        P* beg = *(P**)(self + 0xe98);
        memmove(beg, end, (char*)end - (char*)end);
        int d = (int)end - (int)beg; d >>= 2; d = -d; d += d; d += d;
        *(int*)(self + 0xe9c) += d;
    }
}
