// Slice s00ec8d20 (bfs3 slice 22) -- editor behavior-dialog / tactile map helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct Ctx;
struct Pair { int key; int val; };

// ------------------------------------------------------------------ globals
extern int  g_14892a8[];      // 0x014892a8
extern int* g_16c75a0;        // current insert pointer
extern int* g_16c75a4;        // end
extern int* g_16c757c;        // main map object
extern int* g_16c7584;        // dialog object
extern int* g_16c759c;        // vector begin
extern int* g_16c7aa4;        // scene object

// ------------------------------------------------------------------ callees
void __cdecl FUN_00b534c0(void* at, void* val);        // vector push pair
void __cdecl FUN_00ec8780(int p);
void __cdecl FUN_00ec8370(int p);
void __cdecl FUN_00ec81b0(int p);
void __cdecl FUN_00ec7d00(void* end, unsigned n, void* val);
void __cdecl FUN_00ec7b90(int a, int b);
void __cdecl FUN_00ec7a80();
void __cdecl FUN_00ec6ea0();
int  __cdecl FUN_00ec6ea0_i(int a, void* b);
void __cdecl FUN_00ec8ff0(void* a, void* b, void* c, void* d);
void __cdecl FUN_00ec9750(void* a, void* b, void* c, void* d);
void __cdecl FUN_00ac20d0(int a, void* b);
void __cdecl FUN_00b93c60(int a, void* b);
void __cdecl FUN_0076ffd0(void* a, int b, int c, int d, void* e);
void*__cdecl FUN_0081b750(int a);
void __cdecl FUN_0081b7d0(int a);
void __cdecl FUN_00aea5d0(void* at, void* val);
void __cdecl FUN_00805310(void* a, int b, void* c);
void __cdecl FUN_01012f30(void* a);
void __cdecl RBTreeInsert(int node, int parent, int where, int dir);
void __cdecl FUN_00b93c60_n(int a, void* b);
void*__cdecl cSPUILayout_FindWindowByID(void* layout, int id, int b);

// generic nuke on a rbtree node
void __cdecl DoNukeSubtree(int node);

// ------------------------------------------------------------------ 0x00ec8d20
void FUN_00ec8d20(int param_1)
{
    int local_8 = 7;
    unsigned u = 0;
    do {
        int* p = *(int**)(param_1 + 4);
        int local_4 = g_14892a8[u / 4];
        if (p < *(int**)(param_1 + 8)) {
            *(int**)(param_1 + 4) = p + 2;
            if (p) { p[0] = local_8; p[1] = local_4; }
        } else {
            FUN_00b534c0(p, &local_8);
        }
        u += 4;
    } while (u < 0xc);
}

// ------------------------------------------------------------------ 0x00ec8d80
void FUN_00ec8d80(int param_1)
{
    int arr[8];
    arr[0] = 0x19; arr[1] = 0x32; arr[2] = 0x4b; arr[3] = 100;
    arr[4] = 0x4b; arr[5] = 0x32; arr[6] = 0x19;
    int local_2c = 5;
    unsigned u = 0;
    do {
        int* p = *(int**)(param_1 + 4);
        int local_28 = arr[u];
        if (p < *(int**)(param_1 + 8)) {
            *(int**)(param_1 + 4) = p + 2;
            if (p) { p[0] = local_2c; p[1] = local_28; }
        } else {
            FUN_00b534c0(p, &local_2c);
        }
        ++u;
    } while (u < 3);
    local_2c = 6;
    u = 0;
    do {
        int* p = *(int**)(param_1 + 4);
        int local_28 = arr[u + 3];
        if (p < *(int**)(param_1 + 8)) {
            *(int**)(param_1 + 4) = p + 2;
            if (p) { p[0] = local_2c; p[1] = local_28; }
        } else {
            FUN_00b534c0(p, &local_2c);
        }
        ++u;
    } while (u < 4);
}

// ------------------------------------------------------------------ 0x00ec8e50
void FUN_00ec8e50(int param_1, int param_2)
{
    switch (param_1) {
    case 1: case 5: FUN_00ec8780(param_2); return;
    case 2: FUN_00ec8370(param_2); return;
    case 3: case 4: FUN_00ec81b0(param_2); return;
    case 6: FUN_00ec8d20(param_2); return;
    case 7: case 8: FUN_00ec8d80(param_2); break;
    }
}

// ------------------------------------------------------------------ 0x00ec8ed0
void FUN_00ec8ed0(int* v, unsigned n)
{
    int base = *v;
    if ((unsigned)(v[1] - base) >> 5 < n) {
        char tmp[0x20];
        for (int i = 0; i < 0x20; ++i) tmp[i] = 0;
        FUN_00ec7d00((void*)v[1], n - ((v[1] - base) >> 5), tmp);
        return;
    }
    // keep first n elements (copy_impl truncated)
    v[1] = base + n * 0x20;
}

// ------------------------------------------------------------------ 0x00ec8f40
void FUN_00ec8f40(int* p)
{
    int n = p[0x22a];
    for (;;) {
        if (n < 1)
            return;
        int* obj = (int*)FUN_0081b750(0);
        if (obj)
            ((void(__thiscall*)(void*))obj[0])(obj);
        if (g_16c75a0 < g_16c75a4) {
            int* nxt = g_16c75a0 + 1;
            if (g_16c75a0) {
                *g_16c75a0 = (int)obj;
                g_16c75a0 = nxt;
                if (obj)
                    ((void(__thiscall*)(void*))obj[0])(obj);
            }
        } else {
            FUN_00aea5d0(g_16c75a0, &obj);
        }
        if (obj)
            ((void(__thiscall*)(void*))((int*)obj[0])[1])(obj);
        FUN_0081b7d0(0);
        p[0x22f] = 0;
        *(char*)(p + 0x231) = 1;
        n = p[0x22a];
    }
}

// ------------------------------------------------------------------ 0x00ec90c0
void __fastcall FUN_00ec90c0(char* p)
{
    *(int*)(p + 4) = 0; *(int*)(p + 8) = 0; *(int*)(p + 0xc) = 0;
    *(int*)(p + 0x20) = 0; *(int*)(p + 0x24) = 0; *(int*)(p + 0x24) = 0;
    *(char*)(p + 0x28) = 0; *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x1c) = (int)(p + 0x1c);
    *(int*)(p + 0x20) = (int)(p + 0x1c);
    *(int*)(p + 0x3c) = 0; *(int*)(p + 0x40) = 0; *(int*)(p + 0x40) = 0;
    *(char*)(p + 0x44) = 0; *(int*)(p + 0x48) = 0;
    *(int*)(p + 0x38) = (int)(p + 0x38);
    *(int*)(p + 0x3c) = (int)(p + 0x38);
    *(int*)(p + 0x58) = 0; *(int*)(p + 0x5c) = 0; *(int*)(p + 0x54) = (int)(p + 0x54);
    *(int*)(p + 0x58) = (int)(p + 0x54);
    *(int*)(p + 0x5c) = 0; *(char*)(p + 0x60) = 0; *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x70) = (int)(p + 0x70);
    *(int*)(p + 0x74) = 0; *(int*)(p + 0x78) = 0; *(int*)(p + 0x7c) = 0;
    *(int*)(p + 0x74) = (int)(p + 0x70);
    *(int*)(p + 0x78) = 0; *(char*)(p + 0x7c) = 0; *(int*)(p + 0x80) = 0;
}

// ------------------------------------------------------------------ 0x00ec9140
void FUN_00ec9140(int param_1, int* param_2, int param_3, int* param_4, char param_5)
{
    unsigned dir;
    if (param_5 == 0 && param_3 != param_1 + 4 && *(int*)(param_3 + 0x10) <= *param_4)
        dir = 1;
    else
        dir = 0;
    int node = (int)operator new(0x28);
    if (node != -0x10)
        FUN_01012f30(param_4);
    RBTreeInsert(node, param_3, param_1 + 4, dir);
    *(int*)(param_1 + 0x14) += 1;
    *param_2 = node;
}

// ------------------------------------------------------------------ 0x00ec9250
void FUN_00ec9250(void)
{
    int* r = g_16c757c;
    if (r) {
        DoNukeSubtree(*(int*)(r + 0x78));
        DoNukeSubtree(*(int*)((char*)r + 0x5c));
        DoNukeSubtree(*(int*)((char*)r + 0x40));
        DoNukeSubtree(*(int*)((char*)r + 0x24));
        int v = *(int*)((char*)r + 4);
        if (v && *(int*)(v - 4) != 0)
            operator delete((void*)v);
        operator delete(r);
    }
}

// ------------------------------------------------------------------ 0x00ec92b0
void FUN_00ec92b0(void)
{
    FUN_00ec7a80();
    g_16c7584 = (int*)operator new(0x15c);
    if (g_16c7584 == 0) {
        g_16c7584 = 0;
    } else {
        *g_16c7584 = 0;
    }
    int local_c = (int)FUN_00ec6ea0_i(0, (void*)0);
    int* obj = g_16c7584;
    int local_8 = 0x510a95b;
    int local_4 = 0x40464100;
    int* src = *(int**)(*(int*)(*(int*)(*(int*)(g_16c7aa4 + 0x14) + 0x18) + 0x18) + 0x10);
    int* old = (int*)*g_16c7584;
    if (src != old) {
        if (src)
            ((void(__thiscall*)(void*))((int*)src[0])[1])(src);
        *obj = (int)src;
        if (old)
            ((void(__thiscall*)(void*))((int*)old[0])[2])(old);
    }
    (void)local_c;
    int* w = (int*)cSPUILayout_FindWindowByID((void*)*g_16c7584, 0x8de6960, 1);
    ((void(__thiscall*)(void*))((int*)w[0])[0x41])(w);
    w = (int*)cSPUILayout_FindWindowByID((void*)*g_16c7584, 0x8de6958, 1);
    ((void(__thiscall*)(void*,int,int))((int*)w[0])[0x1f])(w, 1, 0);
    w = (int*)cSPUILayout_FindWindowByID((void*)*g_16c7584, 0xcdfa1006, 1);
    int i5 = -0x3205e000;
    int i4 = 10;
    char st[0x18];
    do {
        FUN_00805310(st, 0xcdfa1000, st);
        i5 += 0x1000;
        --i4;
    } while (i4 != 0);
    (void)i5; (void)w;
}

// ------------------------------------------------------------------ 0x00ec94d0
void FUN_00ec94d0(void)
{
    FUN_00ec9250();
    if (g_16c759c)
        g_16c75a0 = g_16c759c;
    int* p = (int*)*g_16c7584;
    if (p) {
        *g_16c7584 = 0;
        ((void(__thiscall*)(void*))((int*)p[0])[2])(p);
    }
    p = g_16c7584;
    if (g_16c7584) {
        if ((int*)*g_16c7584)
            ((void(__thiscall*)(void*))((int*)*(int*)*g_16c7584)[2])((void*)*g_16c7584);
        operator delete(p);
    }
}

// ------------------------------------------------------------------ 0x00ec9530
int* FUN_00ec9530(int param_1, int* param_2)
{
    int* head = (int*)(param_1 + 4);
    int* parent = head;
    if (*(int**)(param_1 + 0xc)) {
        int* n = *(int**)(param_1 + 0xc);
        do {
            if (n[4] < *param_2)
                n = (int*)*n;
            else {
                parent = n;
                n = (int*)n[1];
            }
        } while (n);
    }
    if (parent == head || *param_2 < parent[4]) {
        int local_18 = *param_2;
        FUN_00ac20d0(0, param_2);
        FUN_0076ffd0(&param_2, 0, 0, 0, param_2);
        FUN_00ec8ff0(&param_2, parent, &local_18, param_2);
        parent = param_2;
    }
    return parent + 5;
}

// ------------------------------------------------------------------ 0x00ec95f0 / 0x00ec9640
long long FUN_00ec95f0(int param_1, int param_2)
{
    if (param_2 != -1) {
        int x = *(int*)(*(int*)(g_16c757c + 4) + param_1 * 4);
        int* p = FUN_00ec9530((int)&x, (int*)&param_2);
        int iVar1 = *p;
        if (iVar1 != p[1]) {
            long long r;
            ((int*)&r)[0] = *(int*)(iVar1 + param_2 * 8);
            ((int*)&r)[1] = *(int*)(iVar1 + 4 + param_2 * 8);
            return r;
        }
    }
    return -1;
}

long long FUN_00ec9640(int param_1, int param_2)
{
    return FUN_00ec95f0(param_1, param_2);
}

// ------------------------------------------------------------------ 0x00ec9690 / 0x00ec96f0
void FUN_00ec9690(int param_1, int param_2)
{
    int x = *(int*)(*(int*)(g_16c757c + 4) + param_1 * 4);
    int* p = FUN_00ec9530((int)&x, &x);
    int iVar3 = *p;
    int i = 0;
    int n = (p[1] - iVar3) >> 3;
    while (i < n) {
        FUN_00ec7b90(param_2, iVar3 + i * 8);
        iVar3 = *p;
        ++i;
    }
}

void FUN_00ec96f0(int param_1, int param_2)
{
    FUN_00ec9690(param_1, param_2);
}

// ------------------------------------------------------------------ 0x00ec9820
int* FUN_00ec9820(int param_1, int* param_2)
{
    int* head = (int*)(param_1 + 4);
    int* parent = head;
    if (*(int**)(param_1 + 0xc)) {
        int* n = *(int**)(param_1 + 0xc);
        do {
            if (n[4] < *param_2)
                n = (int*)*n;
            else {
                parent = n;
                n = (int*)n[1];
            }
        } while (n);
    }
    if (parent == head || *param_2 < parent[4]) {
        int local_18 = *param_2;
        void* local_14 = 0;
        FUN_00b93c60(0, &local_14);
        FUN_00ec9750(&param_2, parent, &local_18, param_2);
        parent = param_2;
    }
    return parent + 5;
}

// ------------------------------------------------------------------ 0x00ec98d0
void FUN_00ec98d0(void)
{
    int* r = g_16c757c;
    int* v = (int*)r[1];
    v[0] = v[1];
    // clear one subtree then reset several maps to empty
    DoNukeSubtree(r[9]);
    r[8] = (int)(r + 7); r[9] = 0; *((char*)r + 0x28) = 0; r[0xb] = 0;
    r[7] = (int)(r + 7);
    DoNukeSubtree(r[0x10]);
    r[0xf] = (int)(r + 0xe); r[0x10] = 0; *((char*)r + 0x44) = 0; r[0x12] = 0;
    r[0xe] = (int)(r + 0xe);
    DoNukeSubtree(r[0x17]);
    r[0x16] = (int)(r + 0x15); r[0x17] = 0; *((char*)r + 0x60) = 0; r[0x19] = 0;
    r[0x15] = (int)(r + 0x15);
    DoNukeSubtree(r[0x1e]);
    r[0x1d] = (int)(r + 0x1c); r[0x1e] = 0; *((char*)r + 0x7c) = 0; r[0x20] = 0;
    r[0x1c] = (int)(r + 0x1c);
}

// ------------------------------------------------------------------ 0x00ec9a80
void FUN_00ec9a80(int param_1, int param_2)
{
    int x = param_2;
    int result;
    if (param_1 == -1 || param_2 == -1) {
        result = -1;
    } else {
        int id = *(int*)(*(int*)(g_16c757c + 4) + param_1 * 4);
        int* p = FUN_00ec9820((int)&id, (int*)&id);
        result = *(int*)(*p + x * 4);
    }
    FUN_00ec9530((int)&result, &result);
}

// ------------------------------------------------------------------ 0x00ec9ae0
int FUN_00ec9ae0(int param_1, int param_2)
{
    int id = *(int*)(*(int*)(g_16c757c + 4) + param_1 * 4);
    int* p = FUN_00ec9820((int)&id, &id);
    int* v = (int*)*p;
    int n = (p[1] - (int)v) >> 2;
    for (int i = 0; i < n; ++i)
        if (v[i] == param_2)
            return i;
    return 0;
}

// ------------------------------------------------------------------ 0x00ec9b30
int* FUN_00ec9b30(int* param_1, int* param_2)
{
    int* out = param_1;
    int id0 = *param_2;
    int* node = *(int**)(*(int*)(g_16c757c + 4) + id0 * 4);
    out[3] = (int)node;
    int iVar1 = param_2[1];
    int u4, u7;
    if (iVar1 == -1) {
        u7 = -1; u4 = -1;
    } else {
        int x = (int)node;
        int* p = FUN_00ec9530((int)&x, &x);
        int base = *p;
        if (base == p[1]) { u4 = -1; u7 = -1; }
        else { u4 = *(int*)(base + iVar1 * 8); u7 = *(int*)(base + 4 + iVar1 * 8); }
    }
    out[5] = u7;
    iVar1 = param_2[2];
    out[4] = u4;
    if (iVar1 == -1) { u4 = -1; u7 = -1; }
    else {
        int x = *(int*)(*(int*)(g_16c757c + 4) + id0 * 4);
        int* p = FUN_00ec9530((int)&x, &x);
        int base = *p;
        if (base == p[1]) { u4 = -1; u7 = -1; }
        else { u4 = *(int*)(base + iVar1 * 8); u7 = *(int*)(base + 4 + iVar1 * 8); }
    }
    out[6] = u4;
    iVar1 = *param_2;
    out[7] = u7;
    int iVar2 = param_2[3];
    if (iVar1 == -1 || iVar2 == -1) {
        u4 = -1;
    } else {
        int x = *(int*)(*(int*)(g_16c757c + 4) + iVar1 * 4);
        int* p = FUN_00ec9820((int)&x, &x);
        u4 = *(int*)(*p + iVar2 * 4);
    }
    int iVar3 = param_2[4];
    *out = u4;
    if (iVar3 != -1) {
        int x = *param_2;
        int y = param_2[3];
        int* p = (int*)&x;
        FUN_00ec9a80(x, y);
        (void)p;
        int* q = (int*)&y;
        (void)q;
    }
    out[1] = -1;
    out[2] = -1;
    return out;
}

// ------------------------------------------------------------------ 0x00ec9c70
void FUN_00ec9c70(int* param_1, int* param_2)
{
    int* a = param_1;
    int* b = param_2;
    if (*a != *b) {
        long long d10 = FUN_00ec95f0(*a, a[1]);
        long long d8 = FUN_00ec9640(*a, a[2]);
        int x = *(int*)(*(int*)(g_16c757c + 4) + *b * 4);
        int* p = FUN_00ec9530((int)&x, &x);
        b[1] = FUN_00ec6ea0_i((int)p, &d10);
        x = *(int*)(*(int*)(g_16c757c + 4) + *b * 4);
        p = FUN_00ec9530((int)&x, &x);
        b[2] = FUN_00ec6ea0_i((int)p, &d8);
        int iVar4 = a[3];
        int u3;
        if (*a == -1 || iVar4 == -1) u3 = -1;
        else {
            x = *(int*)(*(int*)(g_16c757c + 4) + *a * 4);
            int* q = FUN_00ec9820((int)&x, &x);
            u3 = *(int*)(*q + iVar4 * 4);
        }
        b[3] = FUN_00ec9ae0(*b, u3);
        int xi = *b;
        int yi = b[3];
        FUN_00ec9a80(xi, yi);
        b[4] = FUN_00ec6ea0_i(0, &d8);
        return;
    }
    if (a[3] == b[3])
        return;
    long long d8;
    int iVar1 = a[4];
    if (iVar1 != -1) {
        int* q = (int*)&iVar1;
        FUN_00ec9a80(*a, a[3]);
        (void)q;
    }
    ((int*)&d8)[0] = -1;
    ((int*)&d8)[1] = -1;
    int xi = *b, yi = b[3];
    FUN_00ec9a80(xi, yi);
    b[4] = FUN_00ec6ea0_i(0, &d8);
}
