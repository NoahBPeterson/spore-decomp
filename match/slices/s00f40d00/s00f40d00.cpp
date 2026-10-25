// slice s00f40d00 -- Space/terrain tool strategy helpers (0x00f40d00..0x00f41bb0).
//
// Operates on 0x238-byte "surface node" records of the scenario/SpaceTool
// system and on a per-node eastl hashtable.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern void*  g_15ad298;            // 0x015ad298 UI system object
extern void*  g_16c7aa4;            // 0x016c7aa4 Simulator*
extern int    DAT_016c87f8, DAT_016c87fc, DAT_016c8800;

// --- shared record / container shapes -------------------------------------
struct Iter8   { void* node; void* bucket; };                 // eastl hashtable iterator
struct NodeVec { void* begin; void* end; void* cap; };         // eastl vector of pointers
struct Vec4z   { float x, y, z; int w; };                     // 16-byte transform row

// --- free callees ---
void* __cdecl  operator_new(int, const char*, int, int, int, int);
void  __cdecl  operator_del(void*);
void  __cdecl  FUN_00f47380(void*);                         // 0x00f47380 free
void* __cdecl  FUN_00b3d300();                              // 0x00b3d300 noun manager
void* __fastcall FUN_00b1fdb0(void*, int);                  // 0x00b1fdb0 GetAvatar
void  __fastcall FUN_00b227c0(void*, int, int);             // 0x00b227c0 remove noun
void  __fastcall FUN_00b25fe0(void*, int);                  // 0x00b25fe0 remove refs
void  __fastcall FUN_00b22960(void*, int);                  // 0x00b22960 remove all
void  __fastcall FUN_00b225d0(void*, int, void*);           // 0x00b225d0 remove noun
void* __fastcall FUN_00b6ff20(void*, int, const void*);     // 0x00b6ff20 value slot
void* __fastcall FUN_00b474c0(void*, int, const void*);     // 0x00b474c0 value slot
void* __cdecl  FUN_00b18e00(int);                           // 0x00b18e00 info object
void  __fastcall FUN_00e25bd0(void*, int, void*, void*);    // 0x00e25bd0 vector erase
void  __fastcall FUN_00e1c7f0(void*, int, void*);           // 0x00e1c7f0 vector push
void  __fastcall FUN_00aea5d0(void*, int, void*, void*);    // 0x00aea5d0 vector insert
void* __cdecl  FUN_00f20d20(void*);                         // 0x00f20d20
void* __fastcall FUN_00f3d780(void*, int, void*);           // 0x00f3d780 noun of node
void  __fastcall FUN_00f3ecb0(void*, int, void*, void*, void*); // 0x00f3ecb0 node transform
char  __fastcall FUN_00f3f110(void*, int, void*, void*, void*, int); // 0x00f3f110
void* __cdecl  FUN_00ae66d0(void*);                         // 0x00ae66d0 cast
void  __fastcall FUN_00f3c120(void**, int, void*, int);     // 0x00f3c120 advance cursor
int   __fastcall FUN_00f3c160(int, int, int);               // thiscall(this, idx)
void  __fastcall FUN_00dfb850(int, int, int, int);          // thiscall(this, a, b)
char  __fastcall FUN_00f3ff70(int, int, int);               // thiscall(this, a)
char  __cdecl  FUN_00f3b420();
int   __cdecl  FUN_00eeca30(int);
void  __cdecl  FUN_00f3fd90(int*);
char  __fastcall FUN_00f3b9e0(int, int, int, int, int);     // thiscall(this, a, b, c)
void* __cdecl  EA_Messaging_GetServer();
char  __fastcall FUN_00f3bbd0(void*, int, void*, int);      // thiscall(this, noun, b)
char  __fastcall FUN_00edfde0(void*, int);                  // thiscall(this)
void  __fastcall FUN_00f3da90(void*, int, void*, int);      // thiscall(this, node, b)
void  __fastcall FUN_00f40bb0(void*, int, void*, void*);    // thiscall(this, node, v)
void* __cdecl  FUN_00efc910();
void* __cdecl  FUN_00efc520();
void* __cdecl  FUN_00f3fa20(void*, void*);
void  __fastcall FUN_00693230(void*, int, int, int);        // eastl buckets
void  __fastcall FUN_00961d60(void*, int, int, int);        // eastl nodes
void  __fastcall FUN_00645ed0(void*, int, Iter8*, const void*); // eastl find
void  __fastcall FUN_001068380(void*, int, void*, Iter8);   // eastl erase
void* __fastcall FUN_00473810(void*, int, int);             // vector resize
int   __cdecl  FUN_00ef1990(void*, void*, void*);           // vector assign
float __cdecl  FUN_00f3b440(float);                         // 0x00f3b440
char  __fastcall FUN_00f40500(void*, int, void*, int, int); // thiscall(this, a, b, c)
char  __fastcall FUN_00f25ed0(void*, int);                  // thiscall(this)
char  __fastcall FUN_00f3e6d0(void*, int, void*, void*, int, int); // thiscall
void* __fastcall FUN_006c0200(void*, int);                  // 0x006c0200 slot
void* __cdecl  FUN_00401090();
void* __fastcall FUN_004df550(void*, int, int);
void  __fastcall FUN_00c222f0(void*, int, void*);
void  __fastcall FUN_004df3e0(void*, int, void*);
void* __cdecl  FUN_00ac8960(void*);
void* __cdecl  FUN_00ae6760(void*);
void* __cdecl  FUN_00b67740(void*);
void* __cdecl  FUN_00b67720(void*);
void  __fastcall FUN_00c37180(void*, int, void*, int);
int   __cdecl  FUN_00c797b0(void*, void*);
void  __cdecl  FUN_00f3de30(int*);
void  __cdecl  FUN_00dfcb00(void*);
void  __cdecl  FUN_00dfb380();
bool  __fastcall FUN_00f40ed0(int, int, int, int, int, int);  // thiscall(this, a0..a3)
int   __fastcall FUN_00f3e8a0(int, int, int);       // thiscall(this, id)
void  __fastcall FUN_00f41890(int, int, int*);
int   __cdecl  eastl_lower_bound(void*, void*, void*, char);

struct V20 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
             virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
             virtual void q(); };                                      // +0x20 no arg
struct Vc { virtual void p0(); virtual void p1(); virtual void p2(); void f3e910(); };

// ecx receivers
struct Ecx { float f3e910(); char f3ff70(int); char f3b420(); int f3c160(int); int f314c0(); };

// generic vcalls
static inline void  vc0(void* o, int off) { ((void(__cdecl*)(void*))((void**)*(void***)o)[off/4])(o); }
static inline void* vcp0(void* o, int off) { return ((void*(__cdecl*)(void*))((void**)*(void***)o)[off/4])(o); }
static inline void  vcv1(void* o, int off, int a) { ((void(__cdecl*)(void*,int))((void**)*(void***)o)[off/4])(o,a); }
static inline void  vcv3(void* o, int off, int a, int b, int c) { ((void(__cdecl*)(void*,int,int,int))((void**)*(void***)o)[off/4])(o,a,b,c); }

// ecx-receiver vcalls (match retail: the object is the receiver, not an arg)
static inline char  vc_c(void* o, int off)  { return ((char (__fastcall*)(void*,int))(*(void***)o)[off/4])(o,0); }
static inline void  vc_v(void* o, int off)  { ((void (__fastcall*)(void*,int))(*(void***)o)[off/4])(o,0); }
static inline void* vc_p(void* o, int off)  { return ((void*(__fastcall*)(void*,int))(*(void***)o)[off/4])(o,0); }
static inline void* vc_p1(void* o, int off, int a) { return ((void*(__fastcall*)(void*,int,int))(*(void***)o)[off/4])(o,0,a); }

// ===========================================================================
// 0x00f40ea0 -- is a timer below one second?
// ===========================================================================
// @ 0x00f40ea0
int __fastcall FUN_00f40ea0(void* self, int dummy, int* arg) {
    (void)dummy;
    vc0(arg, 0x20);
    float f = ((Ecx*)self)->f3e910();
    if (f < 1.0f) return 1;
    return 0;
}

// ===========================================================================
// 0x00f410f0 -- recycle a surface-node record slot
// ===========================================================================
// @ 0x00f410f0
void __fastcall FUN_00f410f0(int* p, int dummy, int idx) {
    (void)dummy;
    int* e = (int*)(idx * 0x238 + *p);
    int v = (int)e[0x84];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    FUN_00dfb850((int)&e[0xb], 0, e[0xb], e[0xc]);
    v = e[0xb];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    *e = (*e & 0xc0000000) | (p[6] & 0x3fffffff) | 0x80000000;
    p[6] = idx;
    if (p[5] == idx) p[5] = FUN_00f3c160((int)p, 0, idx);
}

// ===========================================================================
// 0x00f41270 -- classify the current scenario state
// ===========================================================================
// @ 0x00f41270
char __fastcall FUN_00f41270(int self, int dummy, int* out) {
    (void)dummy;
    int v = 0;
    if (*(int*)((char*)g_16c7aa4 + 0xcc) == 1) {
        if (*(int*)(self + 0x18) == 0) {
            if (*(int*)(self + 0x8c) == 0) v = 2;
            else {
                if (((Ecx*)self)->f3ff70(*(int*)(self + 0x8c)) == 0) v = 3;
                else if (*(int*)(self + 0x4c) == *(int*)(self + 0x50)) v = 4;
                else {
                    if (((Ecx*)self)->f3b420() != 0 || *(char*)(self + 0x85) != 0) return 1;
                    v = 5;
                }
            }
        }
    } else v = 1;
    if (out) { *out = v; return 0; }
    return 0;
}

// ===========================================================================
// 0x00f41420 -- validate the node against the active scenario
// ===========================================================================
// @ 0x00f41420
char __fastcall FUN_00f41420(int self, int dummy, int a0, int a1, int a2, int a3) {
    (void)dummy;
    int r = FUN_00eeca30(a0);
    if (r) {
        if (FUN_00f3b9e0(self, 0, a0, r, 0) == 0) { *(uint32_t*)(a0 + 0x224) |= 0x10; return 0; }
        *(uint32_t*)(a0 + 0x224) &= 0xffffffef;
    }
    if (FUN_00f3ff70(self, 0, a0) == 0) { *(uint32_t*)(a0 + 0x224) |= 2; return 0; }
    *(uint32_t*)(a0 + 0x224) &= 0xfffffffd;
    if (FUN_00f40ed0(self, 0, a0, a1, a2, a3) == 0) { *(uint32_t*)(a0 + 0x224) |= 4; return 0; }
    *(uint32_t*)(a0 + 0x224) &= 0xfffffffb;
    return 1;
}

// ===========================================================================
// 0x00f41820 -- release one surface-node record
// ===========================================================================
// @ 0x00f41820
void __fastcall FUN_00f41820(int self, int dummy, int* node) {
    (void)dummy;
    int id = *node;
    FUN_00f3fd90(node);
    if (id == -2) {
        int w = *(int*)(self + 0x10);
        *(int*)(w + 0x150) = DAT_016c87f8;
        *(int*)(w + 0x154) = DAT_016c87fc;
        *(int*)(w + 0x158) = DAT_016c8800;
    } else {
        FUN_00f410f0(0, 0, node[0x8a]);
    }
    void* srv = EA_Messaging_GetServer();
    vcv3(srv, 0x14, 0x7311ff7, id, 0);
}

// ===========================================================================
// 0x00f41a10 -- destroy every surface-node record for a noun
// ===========================================================================
// @ 0x00f41a10
void __fastcall FUN_00f41a10(int self, int dummy, int id) {
    (void)dummy;
    if (!FUN_00f3e8a0(self, 0, id)) return;
    int* piVar4 = *(int**)(self + 0xb4);
    int* piVar3 = (int*)*piVar4;
    if (!piVar3) {
        piVar4++;
        while (*piVar4 == 0) piVar4++;
        piVar3 = (int*)*piVar4;
    }
    int* piVar1 = *(int**)(*(int*)(self + 0xb4) + *(int*)(self + 0xb8) * 4);
    while (piVar3 != piVar1) {
        int base = *(int*)(*(int*)(self + 0x10) + 0x2c10);
        int* rec = (int*)(*piVar3 * 0x238 + 4 + base);
        if (*rec == id) FUN_00f41890(self, 0, rec);
        piVar3 = (int*)piVar3[2];
        while (!piVar3) { piVar4++; piVar3 = (int*)*piVar4; }
    }
}

// ===========================================================================
// 0x00f41aa0 -- ordered-map find-or-insert (returns value slot)
// ===========================================================================
// @ 0x00f41aa0
int* __fastcall FUN_00f41aa0(int* p, int dummy, int* key) {
    (void)dummy;
    int* b = (int*)*p;
    int* e = (int*)p[1];
    int* it = (int*)eastl_lower_bound(b, e, key, *(char*)((char*)p + 0x14));
    if (it == e || *key < *it) {
        int k = *key;
        int tmp[2]; tmp[1] = 0;
        int* lo; int* hi;
        if (it == e || *it <= (unsigned)k) { lo = it; hi = e; }
        else { lo = it; hi = e; }
        tmp[0] = k;
        it = (int*)eastl_lower_bound(lo, hi, tmp, *(char*)((char*)p + 0x14));
        if (it == e || (unsigned)k < *it) it = (int*)FUN_00c797b0(it, tmp);
    }
    return it + 1;
}

// ===========================================================================
// 0x00f41b30 -- swap or clear two records
// ===========================================================================
void __fastcall FUN_00f41b30(int* a, int dummy, int* b) {
    (void)dummy;
    int x = *a;
    int y = *b;
    if ((x == 0 || *(int*)(x - 4) != 0) && (y == 0 || *(int*)(y - 4) != 0)) {
        *a = y; *b = x;
        x = a[1]; a[1] = b[1]; b[1] = x;
        x = a[2]; a[2] = b[2]; b[2] = x;
        return;
    }
    FUN_00f3de30(a);
    FUN_00dfcb00(b);
    char buf[20];
    FUN_00dfcb00(buf);
    FUN_00dfb380();
}

// ===========================================================================
// 0x00f40d00 -- collect the live noun nodes belonging to one noun handle
// ===========================================================================
// @ 0x00f40d00
bool __fastcall FUN_00f40d00(int self, int dummy, void* id, NodeVec* vec) {
    (void)dummy;
    bool found = 0;
    FUN_00e25bd0(vec, 0, vec->begin, vec->end);
    if (id == (void*)0xfffffffe) {
        void* av = FUN_00b1fdb0(FUN_00b3d300(), 0);
        if (av && vc_c(av, 0x2c) == 0) {
            void* ref = av;
            vc_v(av, 0x00);
            FUN_00e1c7f0(vec, 0, &ref);
            if (ref) vc_v(ref, 0x04);
        }
        return 1;
    }
    int* mgr = *(int**)(self + 0x10);
    unsigned cnt = *(unsigned*)((char*)mgr + 0x2c24);
    unsigned char* endp = *(unsigned char**)((char*)mgr + 0x2c14);
    unsigned char* p = (cnt < 0x3fffffff)
        ? (unsigned char*)(cnt * 0x238 + *(int*)((char*)mgr + 0x2c10))
        : endp;
    if (p == endp) return found;
    for (;;) {
        if (*(void**)(p + 4) == id) {
            found = 1;
            void* n = FUN_00f3d780((void*)self, 0, p + 4);
            if (n) {
                void* w = vc_p1(n, 0x0c, 0x175cdc9);
                if (w && *(int*)((char*)w + 0x38) == 9) n = FUN_00f20d20(n);
            }
            if (n && vc_c(n, 0x2c) == 0) {
                void* ref = n;
                vc_v(n, 0x00);
                if (vec->end < vec->cap) {
                    void** slot = (void**)vec->end;
                    vec->end = slot + 1;
                    if (slot) { *slot = n; vc_v(n, 0x00); }
                } else {
                    FUN_00aea5d0(vec, 0, vec->end, &ref);
                    n = ref;
                }
                if (n) vc_v(n, 0x04);
            }
        }
        for (;;) {
            unsigned f = *(unsigned*)p;
            p += 0x238;
            if ((f >> 30) & 1) break;
            if ((*(unsigned*)p >> 31) & 1) continue;
            break;
        }
        if (p == endp) break;
    }
    return found;
}

// ===========================================================================
// 0x00f40ed0 -- test one node against every other live surface node
// ===========================================================================
// @ 0x00f40ed0
bool __fastcall FUN_00f40ed0(int self, int dummy, int a, int b, int c, int d) {
    (void)dummy;
    int flagB = (b != 0);
    int node = (int)FUN_00f3d780((void*)self, 0, (void*)a);
    if (!node) return 1;
    void* info = FUN_00b18e00(node);
    Vec4z xf; xf.w = 0;
    FUN_00f3ecb0((void*)self, 0, (void*)a, (void*)node, &xf);
    int cur = *(int*)(self + 0x8c);
    if (cur && a != cur && cur != b && ((char)c == 0 || *(char*)(cur + 0x208) == 0)) {
        char ok;
        if ((char)d == 0) {
            ok = FUN_00f3f110(info, 0, &xf, (void*)a, (void*)cur, flagB);
        } else {
            Vec4z xf2; xf2.w = 0;
            void* n2 = FUN_00f3d780((void*)self, 0, (void*)cur);
            void* i2 = FUN_00b18e00((int)n2);
            void* v = FUN_00ae66d0(i2);
            FUN_00f3ecb0((void*)self, 0, (void*)cur, v, &xf2);
            ok = FUN_00f3f110(i2, 0, &xf2, (void*)cur, (void*)a, flagB);
        }
        if (!ok) return 0;
    }
    if (!info) return 1;
    int* mgr = *(int**)(self + 0x10);
    unsigned cnt = *(unsigned*)((char*)mgr + 0x2c24);
    unsigned char* endp = *(unsigned char**)((char*)mgr + 0x2c14);
    unsigned char* cursor = (cnt < 0x3fffffff)
        ? (unsigned char*)(cnt * 0x238 + *(int*)((char*)mgr + 0x2c10))
        : endp;
    if (cursor == endp) return 1;
    for (;;) {
        unsigned char* np = cursor + 4;
        int skip = 0;
        if (a == (int)np || (int)np == b) skip = 1;
        else if ((char)c != 0 && *(char*)(np + 0x208) != 0) skip = 1;
        if (!skip) {
            char ok;
            if ((char)d == 0) {
                ok = FUN_00f3f110(info, 0, &xf, (void*)a, np, flagB);
            } else {
                Vec4z xf2; xf2.w = 0;
                void* n2 = FUN_00f3d780((void*)self, 0, np);
                void* i2 = FUN_00b18e00((int)n2);
                void* v = FUN_00ae66d0(i2);
                FUN_00f3ecb0((void*)self, 0, np, v, &xf2);
                if ((char)c != 0 && *(char*)(np + 0x208) != 0) ok = 1;
                else ok = FUN_00f3f110(i2, 0, &xf2, np, (void*)a, flagB);
            }
            if (!ok) return 0;
        }
        void* old;
        FUN_00f3c120((void**)&cursor, 0, &old, 0);
        if (endp == cursor) break;
    }
    return 1;
}

// ===========================================================================
// 0x00f41180 -- copy the record positions (and the current node) into a list
// ===========================================================================
// @ 0x00f41180
void __fastcall FUN_00f41180(int self, int dummy, NodeVec* out) {
    (void)dummy;
    int cur = *(int*)(self + 0x8c);
    int* mgr = *(int**)(self + 0x10);
    unsigned cnt = *(unsigned*)((char*)mgr + 0x2c24);
    int* endp = *(int**)((char*)mgr + 0x2c14);
    int* start = (cnt < 0x3fffffff)
        ? (int*)(cnt * 0x238 + *(int*)((char*)mgr + 0x2c10))
        : endp;
    int n = FUN_00ef1990(start, endp, out);
    FUN_00473810(out, 0, n + (cur != 0));
    int total = 0;
    int* p = (cnt < 0x3fffffff)
        ? (int*)(cnt * 0x238 + *(int*)((char*)mgr + 0x2c10))
        : endp;
    if (endp != p) {
        int off = 0;
        do {
            int* dst = (int*)((char*)out->begin + off);
            dst[0] = p[2];
            dst[1] = p[3];
            dst[2] = p[4];
            total++;
            off += 0x0c;
            for (;;) {
                unsigned f = (unsigned)p[0];
                p = (int*)((char*)p + 0x238);
                if ((f >> 30) & 1) break;
                if ((*(unsigned*)p >> 31) & 1) continue;
                break;
            }
        } while (endp != p);
    }
    if (cur) {
        int* dst = (int*)((char*)out->begin + total * 0x0c);
        dst[0] = *(int*)(cur + 0x04);
        dst[1] = *(int*)(cur + 0x08);
        dst[2] = *(int*)(cur + 0x0c);
    }
}

// ===========================================================================
// 0x00f41300 -- tear the surface down
// ===========================================================================
// @ 0x00f41300
void __fastcall FUN_00f41300(int self) {
    if (*(int*)((char*)g_16c7aa4 + 0xcc) == 1) {
        ((void(__fastcall*)(void*,int,int))(*(void***)g_15ad298)[0x20/4])(g_15ad298, 0, 0);
    }
    FUN_00693230((char*)self + 0x90, 0, *(int*)((char*)self + 0x94), *(int*)((char*)self + 0x98));
    *(int*)((char*)self + 0x9c) = 0;
    FUN_00961d60((char*)self + 0xb0, 0, *(int*)((char*)self + 0xb4), *(int*)((char*)self + 0xb8));
    *(int*)((char*)self + 0xbc) = 0;
    int node = *(int*)((char*)self + 0x8c);
    if (node) {
        int v = *(int*)(node + 0x20c);
        if (v && *(int*)(v - 4)) FUN_00f47380((void*)v);
        FUN_00dfb850(node + 0x28, 0, *(int*)(node + 0x28), *(int*)(node + 0x2c));
        v = *(int*)(node + 0x28);
        if (v && *(int*)(v - 4)) FUN_00f47380((void*)v);
        FUN_00f47380((void*)node);
        *(int*)((char*)self + 0x8c) = 0;
    }
    FUN_00b227c0(FUN_00b3d300(), 0, 0x0e9cb8ba);
    FUN_00b227c0(FUN_00b3d300(), 0, 0x074e0069);
    FUN_00b227c0(FUN_00b3d300(), 0, 0x07b38ba7);
    FUN_00b25fe0(FUN_00b3d300(), 0);
    FUN_00b22960(FUN_00b3d300(), 0);
}

// ===========================================================================
// 0x00f414b0 -- re-validate every listed surface node
// ===========================================================================
// @ 0x00f414b0
bool __fastcall FUN_00f414b0(int self) {
    int cur = *(int*)(self + 0x8c);
    bool okAll = 1;
    if (cur && ((*(unsigned*)(cur + 0x224) >> 2) & 1)) {
        char ok = FUN_00f40ed0(self, 0, cur, 0, 0, 0);
        if (!ok) *(unsigned*)(cur + 0x224) |= 4;
        else *(unsigned*)(cur + 0x224) &= 0xfffffffb;
        void* n = FUN_00f3d780((void*)self, 0, (void*)cur);
        if (n) {
            char c = FUN_00edfde0((void*)cur, 0);
            FUN_00f3bbd0((void*)self, 0, n, c == 0);
        }
        okAll = ok;
    }
    int* mgr = *(int**)(self + 0x10);
    unsigned cnt = *(unsigned*)((char*)mgr + 0x2c24);
    unsigned char* endp = *(unsigned char**)((char*)mgr + 0x2c14);
    unsigned char* p = (cnt < 0x3fffffff)
        ? (unsigned char*)(cnt * 0x238 + *(int*)((char*)mgr + 0x2c10))
        : endp;
    if (p == endp) return okAll;
    for (;;) {
        unsigned flags = *(unsigned*)(p + 0x228);
        unsigned char* np = p + 4;
        if ((flags >> 2) & 1) {
            char ok = FUN_00f40ed0(self, 0, (int)np, 0, 0, 0);
            if (!ok) *(unsigned*)(np + 0x224) |= 4;
            else *(unsigned*)(np + 0x224) &= 0xfffffffb;
            void* a;
            if (np == (unsigned char*)*(int*)(self + 0x8c)) {
                a = FUN_00b1fdb0(FUN_00b3d300(), 0);
            } else {
                Iter8 it;
                FUN_00645ed0((char*)self + 0xb0, 0, &it, np + 0x228);
                a = (*(int*)((char*)self + 0xb4)
                     + *(int*)((char*)self + 0xb8) * 4 == (int)it.node) ? 0 : *(void**)((char*)it.node + 4);
            }
            if (a) {
                unsigned nf = *(unsigned*)(np + 0x224);
                int anyf = ((nf >> 4) & 1) || ((nf >> 1) & 1) || ((nf >> 2) & 1);
                void* info = FUN_00b18e00((int)a);
                *(char*)((char*)info + 0x6e) = anyf ? 1 : 0;
                void* w = vc_p(info, 0xac);
                if (w) {
                    if (!anyf) *(unsigned*)((char*)w + 4) &= 0xfffffff7;
                    else { *(unsigned*)((char*)w + 4) |= 8; *(char*)((char*)w + 0x5c) = 1; }
                }
            }
            okAll = (okAll && ok) ? 1 : 0;
        }
        for (;;) {
            unsigned f = *(unsigned*)p;
            p += 0x238;
            if ((f >> 30) & 1) break;
            if ((*(unsigned*)p >> 31) & 1) continue;
            break;
        }
        if (p == endp) break;
    }
    return okAll;
}

// ===========================================================================
// 0x00f416b0 -- pick the tool nodes that accept one surface node
// ===========================================================================
// @ 0x00f416b0
int __fastcall FUN_00f416b0(void* self, int dummy, int a1, int* a2, int a3, int a4,
                            int a5, int a6, int* a7, int a8) {
    (void)dummy;
    int count = 0;
    int bVar2;
    int t = *a2;
    if (t == 4 || t == 5 || t == 0x0b) bVar2 = 0;
    else {
        int n = FUN_00f3e8a0((int)self, 0, a3);
        if (n == 0 || *(char*)(a1 * 0x4e0 + 2 + *(int*)(n + 0x70)) == 0) bVar2 = 1;
        else bVar2 = 0;
    }
    if ((char)a5 == 0 && FUN_00f40500(self, 0, a2, a1, a8) == 0) return 0;
    int bVar1;
    {
        int n = FUN_00f3e8a0((int)self, 0, a3);
        if (n == 0 || FUN_00f25ed0((void*)n, 0) == 0 || (char)a6 != 0) bVar1 = 0;
        else bVar1 = 1;
    }
    NodeVec vec; vec.begin = 0; vec.end = 0; vec.cap = 0;
    bool found = FUN_00f40d00((int)self, 0, (void*)a3, &vec);
    if (a7) *(char*)a7 = found;
    int n = (int)((char*)vec.end - (char*)vec.begin) >> 2;
    if (n >= 1) {
        int i = 0;
        do {
            if (FUN_00f3e6d0(self, 0, ((void**)vec.begin)[i], a2, a1, a4)) {
                if (bVar1 && bVar2) { count = 0x7fffffff; break; }
                count++;
            }
            i++;
        } while (i < n);
    }
    for (void** q = (void**)vec.begin; q < (void**)vec.end; q++)
        if (*q) vc_v(*q, 0x04);
    if (vec.begin && *(int*)((char*)vec.begin - 4)) FUN_00f47380(vec.begin);
    return count;
}

// ===========================================================================
// 0x00f41890 -- release one accepted surface node
// ===========================================================================
// @ 0x00f41890
void __fastcall FUN_00f41890(int self, int dummy, int* node) {
    (void)dummy;
    void* noun = (void*)FUN_00f3e8a0(self, 0, node[0]);
    *(float*)((char*)node + 0x20) = FUN_00f3b440(*(float*)((char*)node + 0x24));
    Iter8 it;
    FUN_00645ed0((void*)(self + 0xb0), 0, &it, (char*)node + 0x228);
    if (it.node == (void*)(*(int*)(self + 0xb4) + *(int*)(self + 0xb8) * 4)) return;
    if (FUN_00efc910() == (void*)node) {
        ((void(__fastcall*)(void*,int,int))(*(void***)g_15ad298)[0x20/4])(g_15ad298, 0, 0);
    }
    void* obj = *(void**)((char*)it.node + 4);
    if (obj) {
        void* a = vc_p1(obj, 0x0c, 0x175cdc9);
        if (a && *(void**)((char*)a + 0x54)) {
            FUN_00b225d0(FUN_00b3d300(), 0, *(void**)((char*)a + 0x54));
            void* n2 = *(void**)((char*)a + 0x54);
            if (n2) { *(int*)((char*)a + 0x54) = 0; vc_v(n2, 0x04); }
        }
    }
    Iter8 it2;
    FUN_00645ed0((void*)(self + 0x90), 0, &it2, &node);
    FUN_001068380((void*)(self + 0x90), 0, &it, it2);
    FUN_00b225d0(FUN_00b3d300(), 0, obj);
    void* r = FUN_00f3fa20(noun, FUN_00efc520());
    int* slot = (int*)FUN_00b6ff20((void*)(self + 0xb0), 0, (char*)node + 0x228);
    int old = *slot;
    if ((int)r != old) {
        if (r) vc_v(r, 0x00);
        *slot = (int)r;
        if (old) vc_v((void*)old, 0x04);
    }
    int* p = (int*)FUN_00b474c0((void*)(self + 0x90), 0, &it);
    *p = *(int*)((char*)node + 0x228);
    FUN_00f3da90((void*)self, 0, node, 1);
    FUN_00f40bb0((void*)self, 0, node, r);
}

// ===========================================================================
// 0x00f41bb0 -- dispatch a UI event to the object type it targets
// ===========================================================================
// (retail receives the dispatch object in EAX; reconstructed here as __fastcall)
// @ 0x00f41bb0
void __fastcall FUN_00f41bb0(void* self, int dummy, int unused, void* arg) {
    (void)dummy; (void)unused;
    if (self) {
        void* w = vc_p1(self, 0x0c, 0x175cdc9);
        if (w && *(int*)((char*)w + 0x38) == 9) return;
    }
    int id = (int)vc_p(self, 0x20);
    switch (id) {
    case 0x18eb45e: {
        void* o = FUN_00ac8960(self);
        void* p = FUN_004df550(FUN_00401090(), 0, (int)arg);
        if (!p) return;
        FUN_00c222f0(o, 0, p);
        if (!((*(unsigned*)((char*)o + 0xb58) >> 9) & 1)) return;
        FUN_004df3e0(FUN_00401090(), 0, p);
        return;
    }
    case 0x070703b3: {
        void* o = FUN_00b67720(self);
        void* sub = (char*)o + 0x34;
        ((void(__fastcall*)(void*,int,int))(*(void***)sub)[0x94/4])(sub, 0, (int)arg);
        return;
    }
    case 0x018c6de8: {
        void* o = FUN_00ae6760(self);
        void* sub = (char*)o + 0x34;
        ((void(__fastcall*)(void*,int,int))(*(void***)sub)[0x94/4])(sub, 0, (int)arg);
        return;
    }
    case 0x018ebadc: {
        void* o = FUN_00b67740(self);
        FUN_00c37180(o, 0, arg, 1);
        return;
    }
    default:
        break;
    }
    FUN_00f41890((int)arg, 0, (int*)FUN_006c0200(self, 0));
}
