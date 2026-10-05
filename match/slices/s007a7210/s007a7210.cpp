// slice s007a7210  --  SP::cGraphicsSystem::CreateBuiltinModels (2852 bytes).
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
//
// The original unrolls the creation of ~15 built-in meshes: for each entry it calls a
// mesh factory, wraps the result, allocates a 0x140-byte model with the "Graphics"
// EASTL allocator, push_backs it into mBuiltinModels, then calls the mesh's
// vtable[0xac] name/hash accessor followed by SP::RegisterModel(object, key, hash).
// The repeated blocks differ in factory address, hash constants and transform values.
// Only the entry sequence is reproduced here; the unrolled body is omitted.
#include "types.h"

extern "C" void  FUN_007658f0(void*, int);
extern "C" void* FUN_00715de0();
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  FUN_007004d0(void*);
extern "C" void  FUN_007a6ac0(void*, void*);
extern "C" void  FUN_0072c0a0(void*);
extern "C" void  SP_RegisterModel(void*, unsigned int, unsigned int);

struct ModelVector {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    char  pad0c[4];
};

struct cGraphicsSystem {
    char pad000[0x40];
    ModelVector mBuiltinModels;  // +0x40
    void* mSomething44;          // +0x50? (accessed as [this+0x44] = end of vector)

    void CreateBuiltinModels();
};

// @ 0x007a7210  SP::cGraphicsSystem::CreateBuiltinModels
void cGraphicsSystem::CreateBuiltinModels()
{
    // entry sequence only (the per-model unrolled blocks are not reconstructed)
    FUN_007658f0(&this->mBuiltinModels, 0x10);

    void* mesh = FUN_00715de0();
    if (mesh)
        (*(void(__thiscall**)(void*))mesh)(mesh);

    // ... 15 x { transform, factory, allocate(0x140,"Graphics"), ctor,
    //           push_back, Release, RegisterModel(..., key, hash) } ...
}
