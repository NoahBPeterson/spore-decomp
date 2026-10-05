// Slice s007689a0: SP::cGraphicsResourceFactory game-model / dispatch writers.
// /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
bool  __cdecl BuildJob(void* self, void* a, void* b, unsigned char c);      // 0x767590
bool  __cdecl WriteRaster(void* self, int* stream);                         // 0x767ee0
bool  __cdecl WriteGameMeshes(void* self, int* stream);                     // 0x764f60
bool  __cdecl WriteRasterArena(void* self, int* stream);                    // 0x763a80
}

// ===========================================================================
// @ 0x007689a0  SP::cGraphicsResourceFactory::WriteResourceGameModel
// ===========================================================================
bool __stdcall WriteResourceGameModel(void* self, int* stream) {
    (void)self; (void)stream;
    // The original is a ~2.5 KB serializer over materials, index/vertex buffers,
    // skin data and a trailing key triple. Only the outer structure is modelled.
    return true;
}

// ===========================================================================
// @ 0x00769200  SP::cGraphicsResourceFactory::WriteResource (dispatch)
// ===========================================================================
struct IFactorySrc {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void* f6();   // +0x18
};
bool __fastcall WriteResourceDispatch(void* self, int, int* obj1, int* obj2, int* u3, int* u4) {
    (void)u3; (void)u4;
    int* p = (int*)((IFactorySrc*)obj1)->f6();
    if (p)
        ((void(__thiscall**)(int*))*(void***)p)[1](p);   // +0x4
    bool r = false;
    if (p) {
        uint32_t type = *(uint32_t*)((char*)obj2 + 0xc);
        if (type < 0x65ea4ed) {
            if (type == 0x65ea4ec)
                r = BuildJob(self, obj2, obj1, 0);
            else if (type == 0xe6bce5)
                r = WriteResourceGameModel(obj2, p);
            else if (type == 0x1c135da)
                r = WriteGameMeshes(obj2, p);
            else if (type == 0x46194d0)
                r = BuildJob(self, obj2, obj1, 1);
        } else {
            if (type == 0x2f4e681b)
                r = WriteRasterArena(obj2, p);
            else if (type == 0x2f4e681c)
                r = WriteRaster(obj2, p);
        }
        ((void(__thiscall**)(int*))*(void***)p)[2](p);   // +0x8
        return r;
    }
    return false;
}
