// slice s00eff790 -- scenario checklist construction / surface and noun lookup helpers.
// Bodies are incomplete/approximate; see partial.txt.
//
// Module flags: /O2 /MD /Gy /TP /arch=SSE.
#include "types.h"

extern int*  g_016c7b88;   // 0x016c7b88
extern void* gSimulator;   // 0x016c7aa4

typedef int  (__thiscall *FN0_i)(void*);
typedef void (__thiscall *FN1_i)(void*, int);
typedef void (__thiscall *FN2_ii)(void*, int, int);

void* __cdecl FUN_00ff3f00(void*);
void* __cdecl FUN_00b3d300();
void* __cdecl FUN_00c680d0(void*, int);
void* __cdecl FUN_00c654e0(void*, float);
void* __cdecl FUN_00c65510(void*, float);
void* __cdecl FUN_00c654b0(void*, float);
void* __cdecl FUN_00c686d0(void*, int, void*, void*);
void* __cdecl FUN_00c662b0(void*, float);
void* __cdecl FUN_00c66310(void*, float);
void* __cdecl FUN_00c643a0(void*, int);
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __cdecl FUN_00fd9450(void*, int);

// @ 0x00eff790
void __cdecl FUN_00eff790()
{
    char* g = (char*)g_016c7b88;
    *(char*)(g + 0x64) = 1;
    *(int*)(g + 0x68) = 0;
    void* o = *(void**)(g + 8);
    if (o != 0) {
        *(void**)(g + 8) = 0;
        ((FN0_i)((*(void***)o)[1]))(o);
    }
    o = *(void**)(g + 4);
    if (o != 0) {
        *(void**)(g + 4) = 0;
        ((FN0_i)((*(void***)o)[1]))(o);
    }
    o = *(void**)(g + 0x10);
    if (o != 0) {
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)o)[1]))(o);
    }
    o = *(void**)(g + 0xc);
    if (o != 0) {
        *(void**)(g + 0xc) = 0;
        ((FN0_i)((*(void***)o)[1]))(o);
    }
    void* p = *(void**)g;
    *(void**)g = 0;
    if (p != 0)
        FUN_00f46410((void*)*(void**)((char*)gSimulator + 0x74), p, 0);
}

// @ 0x00f001b0
void* __cdecl FUN_00f001b0(int a, void* b)
{
    void* mgr = *(void**)((char*)gSimulator + 0x74);
    if (a == -2)
        return FUN_00ff3f00(mgr);
    return (void*)FUN_00ff3f00(mgr);
}

// @ 0x00f002d0
uint32_t* __cdecl FUN_00f002d0(uint32_t* p)
{
    char* mgr = (char*)*(void**)((char*)gSimulator + 0x74);
    uint32_t* r = (uint32_t*)FUN_00ff3f00(mgr);
    if (r == p)
        return p;
    char* base = *(char**)(mgr + 0x10);
    bool b = false;
    uint32_t* first = 0;
    uint32_t* e;
    if (*(uint32_t*)(base + 0x2c24) < 0x3fffffff)
        e = (uint32_t*)(*(uint32_t*)(base + 0x2c24) * 0x238 + *(int*)(base + 0x2c10));
    else
        e = *(uint32_t**)(base + 0x2c14);
    uint32_t* end = *(uint32_t**)(base + 0x2c14);
    if (end != e) {
        do {
            uint32_t* q = e + 1;
            if (e[1] == *p) {
                if (q == p) {
                    b = true;
                } else {
                    if (b)
                        return q;
                    if (first == 0)
                        first = q;
                }
            }
            uint32_t v;
            do {
                v = *e;
                e += 0x8e;
                if ((v >> 0x1e) & 1)
                    break;
            } while ((int)*e < 0);
        } while (end != e);
        if (first != 0)
            return first;
    }
    return p;
}

// @ 0x00f00380
int __cdecl FUN_00f00380()
{
    return 0;
}

// @ 0x00f004f0
int __cdecl FUN_00f004f0()
{
    return 0;
}
