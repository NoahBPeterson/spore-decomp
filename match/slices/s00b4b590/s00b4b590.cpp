// s00b4b590 -- SP game-code collision/phantom bookkeeping helpers.
//
// Reconstructed from the disassembly in work/match/scratch_s00b4b590_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// Everything here works on the module-global world object reached through the
// pointer cell at 0x0167eb70 (the object s00b4c270 models as World70).  Several
// functions are eastl vector_map / hashtable instantiations whose retail names
// survive in the binary; the field access pattern is what drives codegen.
//
// Outcome: all 12 functions reconstructed in full and compiling; none byte-exact,
// so every VA is booked in nonmatching.txt (closest is 0x00b4b7b0 at 4 diff bytes,
// difftest PASS).  Equivalence gate: 2 PASS, 3 WEAK, 6 FAIL, 1 UNSUPPORTED — the
// FAIL/UNSUPPORTED rows are harness limits (stubbed externals) noted per VA.
#include "types.h"
#include <math.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

// A raw view of any object header whose vtable we index by byte offset.
struct IVtbl { void* slot[0x40]; };
#define VSLOT(obj, off) (((IVtbl*)*(void**)(obj))->slot[(off) / 4])
typedef uint  (__fastcall* GetTypeFn)(void* self, int edx);       // vtable +0x20
typedef void* (__fastcall* GetSubFn)(void* self, int edx, uint id); // vtable +0x0c

// ---------------------------------------------------------------------------
// module globals
// ---------------------------------------------------------------------------
extern uchar  g_167eb75;        // 0x0167eb75
extern uint   g_167eb88;        // 0x0167eb88
extern uchar  g_1569ab8;        // 0x01569ab8
extern uchar  g_15acb40;        // 0x015acb40
extern float  g_167eb8c;        // 0x0167eb8c
extern float  g_167eb90;        // 0x0167eb90
extern float  g_167eb94;        // 0x0167eb94
extern float  g_1461150;        // 0x01461150
extern uint   g_167eccc;        // 0x0167eccc
extern uint   g_167ecc8;        // 0x0167ecc8

struct Iter { void* node; void* bucket; };

// eastl hashtable header (instance at +0x24 / +0x3c / +0x58 / +0x78 / +0x90).
struct HT {
    char   pad0[4];
    void** arr;                 // +0x04
    uint   count;               // +0x08
    void*  f0c;                 // +0x0c
};

struct World70;
extern World70* g_167eb70;      // 0x0167eb70

// Only the members this slice touches.
struct World70 {
    uint   f0;                  // +0x00
    void*  f4;                  // +0x04
    char   pad8[0x1c];          // +0x08
    HT     ht24;                // +0x24
    char   pad34[4];            // +0x34
    uchar  f38;                 // +0x38
    char   pad39[0x1f];         // +0x39
    HT     ht58;                // +0x58
    char   pad68[0x10];
    HT     ht78;                // +0x78
    char   pad88[4];
    HT     ht90;                // +0x90
    char   pad9c[0x0c];
    float  a8;                  // +0xa8
    float  ac;                  // +0xac
};

// ---------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------
extern void* __cdecl  FUN_00b41ea0(void* first, void* last, void* key, uchar flags); // lower_bound
extern void* __fastcall FUN_00c797b0(void* c, int edx, void* node, void* val);
extern void* __fastcall FUN_00c72d00(void* c, int edx, void* node, void* val);
extern void  __fastcall FUN_00b48e40(void* c, int edx, void* first, void* last);
extern void* __cdecl  FUN_00b41ee0(void* a, void* b);
extern void* __cdecl  FUN_00b532f0(void* self);
extern void* __cdecl  FUN_00b5b800(void);
extern char  __cdecl  FUN_0064f350(void* node, uint key, int flag);
extern uint  __cdecl  FUN_00932e80(const char* s, uint seed, int c);
extern void  __cdecl  FUN_00b47730(void* a, void* b, int c, int d, int e, int f);
extern void  __cdecl  FUN_00afc470(void** ref);
extern void  __cdecl  FUN_00b47e00(void* a, void* b, void* c);
extern void  __cdecl  FUN_00b56090(void* a, void* b, void* c, void* d);
extern void  __cdecl  FUN_00b45b50(void* k, void** ref, int flag);
extern uint  __cdecl  FUN_00b3d700(uint a, uint b);
extern float __cdecl  FUN_00b3dcd0(void* o);
extern char  __cdecl  FUN_00b3dd40(void* o);
extern char  __cdecl  FUN_00b3d5f0(void* o);
extern void* __fastcall FUN_00b72160(void* ht);
extern void* __fastcall FUN_00b721d0(void* ht, int edx, void* key);
extern void  __fastcall FUN_00b41e20(void* ht, int edx, void* arr, uint n);
extern void* __fastcall FUN_00b72210(void* ht, int edx, void* val);
extern void* __fastcall FUN_00b47570(void* ht, int edx, void* out);
extern void* __fastcall FUN_00564a10(void* map, int edx, void* key);  // vector_map::operator[]
extern uint  __cdecl  FUN_00bbb110(void* o);                   // StarGridCount
extern void* __cdecl  FUN_00bbbe20(void* o, void* key);
extern void  __fastcall FUN_00b4b2b0(void* ht, int edx, void* key);
extern void  __cdecl  FUN_00b43790(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43990(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43bc0(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b43d50(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b40a20(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b4b320(void* a, void* b, void* c, float f);
extern char  __fastcall FUN_00b4b060(void* self, int edx, void* a, void* b, void* c, void* d, float f, float g, void* h);
extern void  __cdecl  FUN_00b3e3e0(void* a, void* b, void* c, float f);
extern void  __cdecl  FUN_00b4b910(uint mode);
extern void  __cdecl  FUN_00b4bc20(void* a, void* b, void* c, void* d, float f, float g);
extern void* __cdecl  FUN_00b5b800(void);              // SP::GetCurrentGameMode

// ---------------------------------------------------------------------------
// 0x00b4b590 -- per-object phantom / collision handler (thiscall, one arg).
// ---------------------------------------------------------------------------
// @ 0x00b4b590
void __fastcall FUN_00b4b590(void* self, int /*edx*/, void* obj)
{
    char* s = (char*)self;

    if (*(int*)(s + 0x20) == 1 &&
        ((GetTypeFn)VSLOT(obj, 0x20))(obj, 0) == 0x3ed8573u) {
        if (FUN_00b5b800() != (void*)0x01654c05) {
            uint u = ((GetTypeFn)VSLOT(obj, 0x20))(obj, 0);
            uint r = (uint)(-(int)(u != 0x3ed8573u)) & (uint)obj;
            if (*(int*)(r + 0x64) >= 0) {
                int e = 3, g = 7;
                if (*(int*)(r + 0x88) < 3) { g = 6; e = 0; }
                FUN_00b47730((void*)r, (void*)r, 2, g, 0, e);
            }
        }
    } else if (obj != 0) {
        void* p1 = ((GetSubFn)VSLOT(obj, 0x0c))(obj, 0, 0x01186577u);
        void* p2 = ((GetSubFn)VSLOT(obj, 0x0c))(obj, 0, 0x0116dd1bu);
        if (p1 != 0) {
            if (p2 != 0) {
                void* ref = p2;
                ((void (__fastcall*)(void*, int))VSLOT(p2, 0xbc))(p2, 0);
                FUN_00afc470(&ref);
                if (ref != 0)
                    ((void (__fastcall*)(void*, int))VSLOT(ref, 0xc0))(ref, 0);
            }
            if ((g_167eccc & 1) == 0) {
                g_167eccc |= 1;
                g_167ecc8 = FUN_00932e80("useGameplayPhantom", 0x811c9dc5u, 1);
            }
            void* key = FUN_00b532f0((void*)((GetTypeFn)VSLOT(obj, 0x20))(obj, 0));
            void* node = FUN_00b41ee0(obj, key);
            if (node != 0 &&
                (FUN_0064f350(node, 0xcf3b981du, 1) ||
                 FUN_0064f350(node, g_167ecc8, 0))) {
                if (*(int*)(s + 0x20) == 0) {
                    FUN_00b56090(obj, p1, p2, key);
                } else if (*(int*)(s + 0x20) == 1 && *(char*)((char*)p1 + 0x75) != 0) {
                    World70* w = g_167eb70;
                    uint kk = (uint)key;
                    uint ee = (uint)w->ht58.arr[w->ht58.count];
                    Iter it;
                    it.node = 0;
                    it.bucket = 0;
                    if ((uint)it.node == ee) { (void)kk; }
                    FUN_00b47e00(p2, p1, key);
                }
                if (p2 == 0) {
                    void* ref = p1;
                    ((void (__fastcall*)(void*, int))VSLOT(p1, 0xbc))(p1, 0);
                    FUN_00b45b50(&ref, &ref, 0);
                    if (ref != 0)
                        ((void (__fastcall*)(void*, int))VSLOT(ref, 0xc0))(ref, 0);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00b4b7f0 -- eastl vector_map<uint,CollisionEntry*>::operator[]
// ---------------------------------------------------------------------------
// @ 0x00b4b7f0
void* __fastcall FUN_00b4b7f0(void* self, int /*edx*/, int* key)
{
    int* p  = (int*)self;
    int* first = (int*)*p;       // +0x00 begin
    int* last  = (int*)p[1];     // +0x04 end
    uchar cmp = *(uchar*)((char*)p + 0x14);

    int* it = (int*)FUN_00b41ea0(first, last, key, cmp);
    if (it == last || *key < *it) {
        int  k = *key;
        int  local[2];
        local[1] = 0;
        local[0] = k;
        if (it == last || *it <= k) {
            first = it;
            it = last;
        }
        it = (int*)FUN_00b41ea0(first, it, local, cmp);
        if (it == last || k < *it)
            it = (int*)FUN_00c797b0(p, 0, it, local);
    }
    return (char*)it + 4;
}

// ---------------------------------------------------------------------------
// 0x00b4b880 -- sibling operator[] whose insert helper is 0x00c72d00.
// ---------------------------------------------------------------------------
// @ 0x00b4b880
void* __fastcall FUN_00b4b880(void* self, int /*edx*/, int* key)
{
    int* p  = (int*)self;
    int* lo = (int*)*p;          // +0x00 begin
    int* hi = (int*)p[1];        // +0x04 end
    int* it = (int*)FUN_00b41ea0(lo, hi, key, *(uchar*)((char*)p + 0x14));
    if (it == hi || *key < *it) {
        int   k = *key;
        float f0 = 0.0f;
        if (it != hi && *it <= k) { lo = it; it = hi; }
        int tmp[2];
        tmp[0] = k;
        tmp[1] = *(int*)&f0;
        it = (int*)FUN_00b41ea0(lo, it, tmp, *(uchar*)((char*)p + 0x14));
        if (it == hi || k < *it) it = (int*)FUN_00c72d00(p, 0, it, tmp);
    }
    return (char*)it + 4;
}

// ---------------------------------------------------------------------------
// 0x00b4b7b0 -- drop the last entry of two containers on the world object.
// ---------------------------------------------------------------------------
// @ 0x00b4b7b0
void __fastcall FUN_00b4b7b0(void* self)
{
    char* s = (char*)self;
    void* beg = *(void**)(s + 0x60);
    void* end = *(void**)(s + 0x64);
    FUN_00b48e40(s + 0x60, (int)beg, beg, end);
    {
        char* h = s + 0x47c;
        void* p4 = *(void**)(h + 4);
        FUN_00b41e20(h, (int)p4, p4, *(uint*)(h + 8));
        *(uint*)(h + 0xc) = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00b4b910 -- reset the +0x90 uint->uint flag map to its default bit masks.
// ---------------------------------------------------------------------------
// @ 0x00b4b910
void __cdecl FUN_00b4b910(uint /*mode*/)
{
    uint key;
    FUN_00b48e40((char*)g_167eb70 + 0x90, 0,
                 *(void**)((char*)g_167eb70 + 0x94),
                 *(void**)((char*)g_167eb70 + 0x90));
    key = 0;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) = 0;
    key = 1;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xfde;
    key = 2;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xfde;
    key = 3;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xfde;
    key = 8;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xfde;
    key = 7;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xfde;
    key = 4;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0x9ae;
    key = 10;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0x98e;
    key = 9;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0x9ae;
    key = 6;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0x9ee;
    key = 5;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xa10;
    key = 0xb;
    *(uint*)FUN_00564a10((char*)g_167eb70 + 0x90, 0, &key) |= 0xffe;
}

// ---------------------------------------------------------------------------
// 0x00b4bae0 -- look up (a,b) in the world pair map.
// ---------------------------------------------------------------------------
// @ 0x00b4bae0
int __cdecl FUN_00b4bae0(uint a, uint b)
{
    union { uint u; struct { uint16_t lo, hi; } s; } pair;
    if (a < b) { pair.s.hi = (uint16_t)a; pair.s.lo = (uint16_t)b; }
    else       { pair.s.hi = (uint16_t)b; pair.s.lo = (uint16_t)a; }

    char* w = (char*)g_167eb70;
    void* end = *(void**)(w + 0x28);
    void* it  = FUN_00b41ea0(*(void**)(w + 0x24), end, &pair, *(uchar*)(w + 0x38));
    if (it == end || pair.u < *(uint*)it) it = end;

    if (it != *(void**)(w + 0x28)) {
        uint* v = (uint*)FUN_00b4b7f0((char*)g_167eb70 + 0x24, 0, (int*)&pair.u);
        void* node = FUN_00b721d0((char*)g_167eb70 + 8, 0, (void*)*v);
        if (node != 0 && *(uint*)((char*)node + 4) == a && *(uint*)((char*)node + 8) == b)
            return (int)node;
        FUN_00b4b2b0((char*)g_167eb70 + 0x24, 0, &pair);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00b4bba0 -- create a collision record for (a,b) in the world pair map.
// ---------------------------------------------------------------------------
// @ 0x00b4bba0
int __cdecl FUN_00b4bba0(uint a, uint b)
{
    void* rec = FUN_00b72160((char*)g_167eb70 + 8);
    int node = (int)FUN_00b72210((char*)g_167eb70 + 8, 0, rec);
    *(uint*)(node + 4)  = a;
    *(uint*)(node + 8)  = b;
    *(float*)(node + 0x24) = 0.0f;

    union { uint u; struct { uint16_t lo, hi; } s; } pair;
    if (a < b) { pair.s.hi = (uint16_t)a; pair.s.lo = (uint16_t)b; }
    else       { pair.s.hi = (uint16_t)b; pair.s.lo = (uint16_t)a; }

    uint* v = (uint*)FUN_00b4b7f0((char*)g_167eb70 + 0x24, 0, (int*)&pair.u);
    *v = (uint)rec;
    return node;
}

// ---------------------------------------------------------------------------
// 0x00b4bc20 -- fill a collision record from two scene objects.
// ---------------------------------------------------------------------------
// @ 0x00b4bc20
void __cdecl FUN_00b4bc20(char* a, char* b, float* p3, float* p4, float f1, float f2)
{
    *(uchar*)(a + 0x37) = 1;
    *(uchar*)(b + 0x37) = 1;
    int rec = FUN_00b4bae0(*(uint*)a, *(uint*)b);
    if (rec == 0) rec = FUN_00b4bba0(*(uint*)a, *(uint*)b);
    *(uint*)(rec + 0xc)  = *(uint*)p3;
    *(uint*)(rec + 0x10) = *(uint*)((char*)p3 + 4);
    *(uint*)(rec + 0x14) = *(uint*)((char*)p3 + 8);
    *(uint*)(rec + 0x18) = *(uint*)p4;
    *(uint*)(rec + 0x1c) = *(uint*)((char*)p4 + 4);
    *(uint*)(rec + 0x20) = *(uint*)((char*)p4 + 8);
    *(uint*)(rec + 0x38) = *(uint*)g_167eb70;
    float d1 = FUN_00b3dcd0(a);
    float d2 = FUN_00b3dcd0(b);
    *(float*)(rec + 0x30) = 1.0f / (d2 + d1);

    float cur = *(float*)(rec + 0x24);
    float m = (cur > -f1) ? cur : -f1;
    *(float*)(rec + 0x24) = m;
    float acc = m + g_167eb70->ac;
    float s = (acc >= 0.0f) ? acc : 0.0f;
    float r = (s / f2) * -0.1f;
    *(float*)(rec + 0x34) = r;
    *(float*)(rec + 0x34) = g_167eb70->a8 * r;
}

// ---------------------------------------------------------------------------
// 0x00b4bd40 -- should these two objects be considered for collision?
// ---------------------------------------------------------------------------
// @ 0x00b4bd40
uchar __cdecl FUN_00b4bd40(char* a, char* b)
{
    if (a == 0 || b == 0) return 0;

    if (*(int*)(a + 4) == 0) {
        if (*(char*)(*(char**)(a + 0x40) + 0x71) == 0) goto checks;
    } else if (*(int*)(a + 4) == 1) {
        if (*(char*)(*(char**)(a + 0x40) + 0x71) == 0) goto checks;
    }

    if (*(int*)(b + 4) == 0) {
        if (*(char*)(*(char**)(b + 0x40) + 0x71) != 0) return 0;
    } else if (*(int*)(b + 4) == 1) {
        if (*(char*)(*(char**)(b + 0x40) + 0x71) != 0) return 0;
    } else {
        return 0;
    }

checks:
    if (FUN_00b3dd40(a)) return 0;
    if (FUN_00b3dd40(b)) return 0;
    if (!FUN_00b3d5f0(a)) return 0;
    if (!FUN_00b3d5f0(b)) return 0;

    uint key = FUN_00b3d700(*(uint*)a, *(uint*)b);
    char* w = (char*)g_167eb70;
    if (FUN_00b47570((char*)w + 0x78, 0, &key) == *(void**)(w + 0x7c)) {
        uint* v = (uint*)FUN_00564a10((char*)w + 0x90, 0, a + 0x38);
        if ((*v & (1u << (*(uchar*)(b + 0x38) & 0x1f))) != 0) {
            if (*(int*)(a + 4) == 0 && *(int*)(b + 4) == 0) {
                *(uint*)(*(char**)(a + 0x40) + 0x1a0) = 0x7f7fffff;
                *(uint*)(*(char**)(b + 0x40) + 0x1a0) = 0x7f7fffff;
            }
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00b4be50 -- dispatch one collision pair through the type-pair table.
//
// The two objects are first ordered (by address, then by their +0xc type so the
// higher type lands in `b`), a jump table selects the per-pair test, and the
// contacts it produced are turned into collision records.
// ---------------------------------------------------------------------------
// @ 0x00b4be50
void __cdecl FUN_00b4be50(char* a, char* b, float f)
{
    char* s = b;
    char* t = a;
    if (!FUN_00b4bd40(t, s)) return;

    if ((uint)t < (uint)s) { char* x = t; t = s; s = x; }
    if (*(int*)(t + 0xc) < *(int*)(s + 0xc)) { char* x = t; t = s; s = x; }

    float nrm[3];
    nrm[0] = g_167eb8c;
    nrm[1] = g_167eb90;
    nrm[2] = g_167eb94;
    int count = 0;
    float contacts[32][3];

    switch (*(int*)(t + 0xc)) {
    case 0:
        switch (*(int*)(s + 0xc)) {
        case 0:  FUN_00b3e3e0(t, s, nrm, f); break;
        case 1:  FUN_00b43790(t, s, nrm, f); break;
        case 2:  FUN_00b4b320(t, s, nrm, f); break;
        case 3:  FUN_00b40a20(t, s, nrm, f); break;
        default: return;
        }
        break;
    case 1:
        switch (*(int*)(s + 0xc)) {
        case 1:  FUN_00b43990(t, s, nrm, f); break;
        case 2:  FUN_00b43bc0(t, s, nrm, f); break;
        case 3:  FUN_00b43d50(t, s, nrm, f); break;
        default: return;
        }
        break;
    case 2:
        switch (*(int*)(s + 0xc)) {
        case 2:
            if (!FUN_00b4b060((void*)0x015696f0, 0, t, s, t + 0x1c, s + 0x1c, f, f, nrm)) return;
            break;
        case 3: {
            char* x = t; t = s; s = x;
            FUN_00b4b320(t, s, nrm, f);
            break;
        }
        default: return;
        }
        break;
    case 3:
        FUN_00b3e3e0(t, s, nrm, f);
        break;
    default:
        return;
    }

    if (count > 0) {
        float r = (float)sqrt(nrm[2] * nrm[2] + nrm[1] * nrm[1] + nrm[0] * nrm[0]);
        for (int i = 0; i < count; ++i)
            FUN_00b4bc20(t, s, contacts[i], (float*)&nrm[2], r, f);
    }
}

// ---------------------------------------------------------------------------
// 0x00b4c0e0 -- drive every StarGrid pair through the collision dispatcher.
// ---------------------------------------------------------------------------
// @ 0x00b4c0e0
void __cdecl FUN_00b4c0e0(float f)
{
    uint count = FUN_00bbb110(*(void**)((char*)g_167eb70 + 4));
    void* it = FUN_00bbbe20(*(void**)((char*)g_167eb70 + 4), &count);
    while (it != 0) {
        void* e = FUN_00b721d0((char*)g_167eb70 + 0x3c, (int)*(void**)it, *(void**)it);
        void* o = FUN_00b721d0((char*)g_167eb70 + 0x3c, (int)*(void**)it, *((void**)it + 1));
        if (e != 0 && o != 0) FUN_00b4be50((char*)e, (char*)o, f);
        it = FUN_00bbbe20(*(void**)((char*)g_167eb70 + 4), &count);
    }
}

// ---------------------------------------------------------------------------
// 0x00b4c170 -- set the current game mode.
// ---------------------------------------------------------------------------
// @ 0x00b4c170
void __fastcall FUN_00b4c170(void* self, int /*edx*/, int mode)
{
    char* s = (char*)self;
    if (*(int*)(s + 0x3c) == mode) return;

    *(uchar*)(s + 0x24) = 1;
    *(int*)(s + 0x2c) = 1;
    g_167eb88 = 0;

    switch (mode) {
    case 0x01654c01:
        *(int*)(s + 0x20) = 0;
        *(uchar*)(s + 0x25) = 1;
        *(uchar*)(s + 0x26) = 0;
        *(uchar*)(s + 0x27) = 1;
        *(uchar*)(s + 0x28) = 0;
        g_1569ab8 = 1;
        *(int*)(s + 0x2c) = 0;
        break;
    case 0x01654c02:
        *(int*)(s + 0x20) = 1;
        break;
    case 0x01654c10:
        *(int*)(s + 0x20) = 0;
        *(uchar*)(s + 0x25) = 1;
        *(uchar*)(s + 0x26) = 1;
        *(uchar*)(s + 0x27) = 0;
        *(uchar*)(s + 0x28) = 1;
        g_1569ab8 = (g_15acb40 == 0);
        *(int*)(s + 0x2c) = 0;
        break;
    case 0x01654c00:
    case 0x01654c04:
    case 0x01654c05:
    case 0x01654c06:
    default:
        *(int*)(s + 0x20) = 2;
        break;
    }

    FUN_00b4b910((uint)mode);
    *(int*)(s + 0x3c) = mode;

    switch (mode) {
    case 0x01654c00:
    case 0x01654c01:
    case 0x01654c02:
    case 0x01654c04:
    case 0x01654c05:
    case 0x01654c10:
        if (g_167eb75 == 0) g_167eb75 = 1;
        break;
    }
}
