// Slice s00ed8490 -- resource/array lookup helpers and a small refcounted container.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);

// ================================================================ 0x00ed8490
int __cdecl FUN_00ed8490(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 3 && q[4] == 2)
                    return q[5];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b0) == 3) {
        return *(int*)(p + 0x4bc);
    }
    return -1;
}

// ================================================================ 0x00ed8500
int __cdecl FUN_00ed8500(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 4 && q[6] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b4) == 3) {
        return *(int*)(p + 0x4c0);
    }
    return -1;
}

// ================================================================ 0x00ed8570
int __cdecl FUN_00ed8570(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 7 && q[4] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b8) == 5) {
        return *(int*)(p + 0x4c4);
    }
    return -1;
}

// ================================================================ 0x00ed85e0
struct Obj85e0 { void* f(); };
void* Obj85e0::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a22c;
    *(int*)(s + 4) = 0;
    *(int*)(s + 8) = 0;
    *(int*)(s + 0xc) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    return s;
}

// ================================================================ 0x00ed8610
struct Obj8610 { void f(); };
void Obj8610::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a22c;
    int i = 2;
    char* e = s + 0x28;
    do {
        int* p = *(int**)(e - 4);
        e -= 4;
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
        i--;
    } while (i >= 0);
    i = 2;
    e = s + 0x1c;
    do {
        int* p = *(int**)(e - 4);
        e -= 4;
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
        i--;
    } while (i >= 0);
    if (*(int**)(s + 0xc)) ((FV_v)(*(void***)*(int**)(s + 0xc))[4 / 4])(*(int**)(s + 0xc));
    if (*(int**)(s + 8)) ((FV_v)(*(void***)*(int**)(s + 8))[4 / 4])(*(int**)(s + 8));
    if (*(int**)(s + 4)) ((FV_v)(*(void***)*(int**)(s + 4))[4 / 4])(*(int**)(s + 4));
}


// ================================================================ shared callees
void* __cdecl FUN_00b3d300(void);                 // SP::NounManager
void* __cdecl FUN_00b1f9b0(void*);                // cGameNounManager::GetAllNouns
void* __cdecl SP_EffectsManager(void);            // 0x67ddd0
int   __cdecl FUN_006c0200(void*);                // 0x6c0200
int   __cdecl FUN_00f40d00(void*);                // 0xf40d00
void* __cdecl FUN_013c8830(void);                 // atexit callback
extern int __cdecl atexit(void*);

typedef void  (__thiscall *FVf_v)(void*);
typedef void* (__thiscall *FVf_p)(void*);
typedef void  (__thiscall *FVf_i)(void*, int);
typedef void  (__thiscall *FVf_ii)(void*, int, int);
typedef void  (__thiscall *FVf_iip)(void*, int, int, void*);
typedef void  (__thiscall *FVf_if)(void*, int, float);

struct S_c8ad30 { void f(int, int); };
struct S_c8b210 { void f(int); };
struct S_c88a00 { void f(int, float); };
struct S_c8a200 { void f(int, float); };

// ================================================================ 0x00ed8690
void FUN_00ed8690(void)
{
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b1f9b0(nm);
    int* end = (int*)((char*)v - 0xc);
    int* it = (*v == 0) ? 0 : (int*)((char*)*v - 0xc);
    while (it != end) {
        int esi = 0;
        if (it != 0)
            esi = ((int(__thiscall*)(void*, int))(*(void***)it)[3])(it, 0x1186577);
        if (FUN_006c0200(it) != 0) {
            ((S_c8ad30*)(void*)esi)->f(0xd79308d, 0);
            ((S_c8ad30*)(void*)esi)->f(0x25e2b68, 0);
            ((S_c8ad30*)(void*)esi)->f(0xe1b86fea, 0);
            ((S_c8ad30*)(void*)esi)->f(0xfeacc46f, 0);
            ((S_c8ad30*)(void*)esi)->f(0xad89ad7d, 0);
            for (unsigned i = 0; i < 3; i++)
                ((S_c8ad30*)(void*)esi)->f((int)(0xcaf390f3u + i), 0);
        }
        int* nxt = (int*)it[3];
        it = (nxt == 0) ? 0 : (int*)((char*)nxt - 0xc);
    }
}

// ================================================================ 0x00ed8780
struct Obj8780 { void f(int b); };
static void grab(int id, int* field)
{
    int* em = (int*)SP_EffectsManager();
    int* old = *(int**)field;
    if (old != 0) {
        *(int**)field = 0;
        ((FVf_v)(*(void***)old)[4 / 4])(old);
    }
    ((FVf_iip)(*(void***)em)[0x2c / 4])(em, id, 0, field);
}
static void clear2(int* field)
{
    int* p = *(int**)field;
    if (p != 0) {
        ((FVf_i)(*(void***)p)[0xc / 4])(p, 0);
        int* q = *(int**)field;
        if (q != 0) {
            *(int**)field = 0;
            ((FVf_v)(*(void***)q)[4 / 4])(q);
        }
    }
}
void Obj8780::f(int b)
{
    char* s = (char*)this;
    if (b != 0) {
        grab(0x654889e6, (int*)(s + 4));
        grab(0x95354ff3, (int*)(s + 8));
        grab(0xcbe66649, (int*)(s + 0xc));
        for (int i = 0; i < 3; i++) {
            grab(0xe3a79142, (int*)(s + 0x10 + i * 4));
            grab(0xe3a79142, (int*)(s + 0x1c + i * 4));
        }
    } else {
        clear2((int*)(s + 4));
        clear2((int*)(s + 8));
        clear2((int*)(s + 0xc));
        for (int i = 0; i < 3; i++) {
            clear2((int*)(s + 0x10 + i * 4));
            clear2((int*)(s + 0x1c + i * 4));
        }
    }
}

// ================================================================ 0x00ed8950
void FUN_00ed8950(int a, int b)
{
    int* local = 0;
    int* local10 = 0;
    int cap = 0;
    FUN_00f40d00((void*)a);
    (void)local; (void)local10; (void)cap;
    // Placeholder: the real body iterates a noun vector and pushes float params.
}

// ================================================================ 0x00ed8a30 (approximate)
int __cdecl FUN_00ed8a30(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// ================================================================ 0x00ed9040
void* __cdecl FUN_00ed9040(int id, float* pos)
{
    float best = 3.402823466e+38f;
    int* found = 0;
    if (id == -1) return 0;
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b1f9b0(nm);
    int* end = (int*)((char*)v - 0xc);
    int* it = (*v == 0) ? 0 : (int*)((char*)*v - 0xc);
    while (it != end) {
        int esi = 0;
        if (it != 0)
            esi = ((int(__thiscall*)(void*, int))(*(void***)it)[3])(it, 0x1186577);
        float* p = (float*)((FVf_p)(*(void***)esi)[0x2c / 4])((void*)esi);
        float dx = p[0] - pos[0];
        float dy = p[1] - pos[1];
        float dz = p[2] - pos[2];
        float d = dx * dx + dy * dy + dz * dz;
        if (d < best) { best = d; found = (int*)esi; }
        int* nxt = (int*)it[3];
        it = (nxt == 0) ? 0 : (int*)((char*)nxt - 0xc);
    }
    return found;
}
