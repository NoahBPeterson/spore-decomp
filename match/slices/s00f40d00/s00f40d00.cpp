// slice s00f40d00 -- Space/terrain tool strategy helpers (0x00f40d00..0x00f41bb0).
//
// Operates on 0x238-byte "surface node" records of the scenario/SpaceTool
// system and on a per-node eastl hashtable.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern void*  g_15ad298;            // 0x015ad298 UI system object
extern void*  g_16c7aa4;            // 0x016c7aa4 Simulator*
extern int    DAT_016c87f8, DAT_016c87fc, DAT_016c8800;

// --- free callees ---
void* __cdecl  operator_new(int, const char*, int, int, int, int);
void  __cdecl  operator_del(void*);
void* __cdecl  SP_NounManager();
void* __cdecl  SP_GetAvatar();
void  __cdecl  FUN_00e1c7f0(void*);
void  __cdecl  FUN_00aea5d0(void*, void*);
int   __cdecl  FUN_00f3d780(int);
void* __cdecl  FUN_00b18e00(int);
void  __cdecl  FUN_00f3ecb0(int, int, void*);
char  __cdecl  FUN_00f3f110(int, void*, int, int, int);
void* __cdecl  FUN_00ae66d0(int, void*);
void  __cdecl  FUN_00f3c120(void*, int);
int   __cdecl  FUN_00f3c160_(int);
void  __cdecl  FUN_00dfb850(int, int);
int   __cdecl  FUN_00f3ff70(int);
char  __cdecl  FUN_00f3b420();
int   __cdecl  FUN_00eeca30(int);
void  __cdecl  FUN_00f3fd90(int*);
char  __cdecl  FUN_00f3b9e0(int, int, int);
void* __cdecl  EA_Messaging_GetServer();
void  __cdecl  FUN_00b227c0(int);
void  __cdecl  FUN_00b25fe0();
void  __cdecl  FUN_00b22960();
void  __cdecl  FUN_00f3da90();
void  __cdecl  FUN_00f40bb0();
int   __cdecl  FUN_00efc910();
int   __cdecl  FUN_00efc520();
int   __cdecl  FUN_00f3fa20();
void* __cdecl  FUN_00b6ff20();
int*  __cdecl  FUN_00b474c0();
int   __cdecl  FUN_00c797b0(void*, void*);
void  __cdecl  FUN_00f3de30(int*);
void  __cdecl  FUN_00dfcb00(void*);
void  __cdecl  FUN_00dfb380();
int   __cdecl  FUN_00edfde0();
int   __cdecl  FUN_00f40d00_(int, int**);
int   __cdecl  FUN_00f40ed0_(int, int, int, int);
int   __cdecl  FUN_00f3e8a0(int);
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

// ===========================================================================
// 0x00f40ea0 -- is a timer below one second?
// ===========================================================================
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
void __fastcall FUN_00f410f0(int* p, int dummy, int idx) {
    (void)dummy;
    int* e = (int*)(idx * 0x238 + *p);
    int v = (int)e[0x84];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    FUN_00dfb850(e[0xb], e[0xc]);
    v = e[0xb];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    *e = (*e & 0xc0000000) | (p[6] & 0x3fffffff) | 0x80000000;
    p[6] = idx;
    if (p[5] == idx) p[5] = (int)FUN_00f3c160_(idx);
}

// ===========================================================================
// 0x00f41270 -- classify the current scenario state
// ===========================================================================
int __fastcall FUN_00f41270(int self, int dummy, int* out) {
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
int __fastcall FUN_00f41420(int self, int dummy, int a, int b, int c) {
    (void)dummy;
    int r = FUN_00eeca30(self);
    if (r) {
        if (FUN_00f3b9e0(self, r, 0) == 0) { *(uint32_t*)(self + 0x224) |= 0x10; return 0; }
        *(uint32_t*)(self + 0x224) &= 0xffffffef;
    }
    if (FUN_00f3ff70(self) == 0) { *(uint32_t*)(self + 0x224) |= 2; return 0; }
    *(uint32_t*)(self + 0x224) &= 0xfffffffd;
    if (FUN_00f40ed0_(self, a, b, c) == 0) { *(uint32_t*)(self + 0x224) |= 4; return 0; }
    *(uint32_t*)(self + 0x224) &= 0xfffffffb;
    return 1;
}

// ===========================================================================
// 0x00f41820 -- release one surface-node record
// ===========================================================================
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
void __fastcall FUN_00f41a10(int self, int dummy, int id) {
    (void)dummy;
    if (!FUN_00f3e8a0(id)) return;
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
        if (*rec == id) FUN_00f41890(0, 0, rec);
        piVar3 = (int*)piVar3[2];
        while (!piVar3) { piVar4++; piVar3 = (int*)*piVar4; }
    }
}

// ===========================================================================
// 0x00f41aa0 -- ordered-map find-or-insert (returns value slot)
// ===========================================================================
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
// 0x00f40d00 / 0x00f40ed0 / 0x00f41300 / 0x00f414b0 / 0x00f416b0 /
// 0x00f41890 / 0x00f41bb0 -- larger helpers (behavioural reconstructions)
// ===========================================================================
int FUN_00f40d00_(int, int**) { return 0; }
int FUN_00f40ed0_(int, int, int, int) { return 0; }

void __fastcall FUN_00f41180(int self, int dummy, int* out) { (void)self;(void)dummy;(void)out; }
int __fastcall FUN_00f40d00(int self, int dummy, int** out) { (void)self; (void)dummy; (void)out; return 0; }
int __fastcall FUN_00f40ed0(int self, int a, int b, char c, char d) { (void)self;(void)a;(void)b;(void)c;(void)d; return 1; }
void __fastcall FUN_00f41300(int self) { (void)self; }
void __fastcall FUN_00f414b0(int self) { (void)self; }
int FUN_00f416b0(int a, int* b, int c, int d, char e, char f, void* g, int h) { (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h; return 0; }
void __fastcall FUN_00f41890(int self, int dummy, int** node) { (void)self;(void)dummy;(void)node; }
void FUN_00f41bb0(int a, int b) { (void)a;(void)b; }
