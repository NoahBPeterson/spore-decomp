// Slice s00769310: SP::cGraphicsResourceFactory game-model reader + dispatch
// helpers. /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void  __cdecl FUN_00700640(void* p);                                        // 0x700640
void  __cdecl FUN_007006d0(void* p);                                        // 0x7006d0
char  __cdecl FUN_007638a0(void* a, void* b, void* c, void* d);             // 0x7638a0
char  __cdecl FUN_00767170(void* a, void* b, void* c);                      // 0x767170
char  __cdecl ReadMaterialList(void* a, void* b, void* c);                  // 0x767c80
char  __cdecl FUN_00764ce0(void* a, void* b, void* c);                      // 0x764ce0
char  __cdecl FUN_007637d0(void* a, void* b, int c, void* d);               // 0x7637d0
char  __cdecl ReadResourcePCAWeights(void* a, void* b, void* c);            // 0x763950
char  __cdecl FUN_00769cf0(void* a, void* b, void* c);                      // 0x769cf0
char  __cdecl FUN_00769310b(void* a, void* b, void* c, void* d);            // 0x769310
void* __cdecl FUN_0093b530(int a, int b, void* c);                          // 0x93b530
}

// ===========================================================================
// @ 0x00769310  SP::cGraphicsResourceFactory::ReadResourceGameModel
// ===========================================================================
struct M69310 { char Meth(int a, int b, int c); };
char __stdcall ReadResourceGameModel(void* self, void* stream, void* a3, uint32_t a4) {
    (void)self; (void)stream; (void)a3; (void)a4;
    // ~2.4 KB vertex/index buffer + material reader; only the outer structure
    // is modelled here.
    return 0;
}

// ===========================================================================
// @ 0x00769cb0  forward to the game-model reader
// ===========================================================================
char __fastcall Func69cb0(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x2c);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69310*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// ===========================================================================
// @ 0x00769cf0  stream vcall header check, then two-phase read
// ===========================================================================
char __fastcall Func69cf0(void* self, int, void* stream, void* a2, void* a3) {
    (void)self;
    int local;
    if (((int(__thiscall**)(void*, int*, int))*(void***)stream)[12](stream, &local, 4) != 4)
        return 0;
    if ((uint32_t)(local - 8) > 1)
        return 0;
    FUN_007006d0(a2);
    if (!FUN_007638a0(stream, a3, a2, (void*)local))
        return 0;
    return FUN_00769310b(stream, a3, a2, (void*)local);
}

// ===========================================================================
// @ 0x00769d80  SP::cGraphicsResourceFactory::ReadResourceFromStream
// ===========================================================================
char __fastcall ReadResourceFromStream(void* self, int, int* obj1, int* obj2, void* a4) {
    (void)self;
    int* holder = 0;
    int local = 0;
    (void)holder; (void)local;
    if (obj1 && ((int(__thiscall**)(int*))*(void***)obj1)[3](obj1) == 0x34722300) {
        void* p = Alloc6(0x34, "Graphics", 0, 0, 0, 0);
        if (p)
            p = FUN_0093b530(0x2000, 0, obj1);
        if (p) {
            ((void(__thiscall**)(void*))*(void***)p)[1](p);
            holder = (int*)p;
        }
    }
    uint32_t type = *(uint32_t*)((char*)obj2 + 4);
    char r = 0;
    bool handled = true;
    if (type < 0x2cb4f30) {
        if (type == 0x2cb4f2f)
            r = ReadResourcePCAWeights(holder, obj2, obj1);
        else if (type == 0xe6bce5)
            r = FUN_00769cf0(holder, obj2, obj1);
        else if (type == 0x1c135da)
            r = ReadMaterialList(holder, obj2, obj1);
        else
            handled = false;
    } else if (type == 0x2f4e681b) {
        r = FUN_00764ce0(holder, obj2, obj1);
    } else if (type == 0x2f4e681c && (uint32_t)(size_t)a4 <= 0x2f7d0004) {
        if ((size_t)a4 == 0x2f7d0004)
            r = FUN_007637d0(holder, obj2, 4, obj1);
        else if ((size_t)a4 != 0x2f4e681b && (size_t)a4 == 0x2f4e681c)
            r = FUN_00767170(holder, obj2, obj1);
        else
            handled = false;
    } else {
        handled = false;
    }
    if (!handled) {
        if (holder)
            ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
        return 0;
    }
    if (holder)
        ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
    return r;
}
