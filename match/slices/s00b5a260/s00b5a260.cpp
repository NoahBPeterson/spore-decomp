// Slice s00b5a260 - the SP::Havok world manager (a singleton "simulation" service).
//
//   00b5a260  FUN_00b5a260  - (un)register one object: hand it to FUN_00b530e0, then (when the
//                            world is idle) resolve it through its +0xb8 vtbl slot and, if that
//                            yields a body, SP::Havok::CreateHavokEntityForObject()
//   00b5a2d0  FUN_00b5a2d0  - the same for every pointer in the object list at +0x60..+0x64,
//                            resolving the body through the +0x14c8 map instead
//   00b5a390  FUN_00b5a390  - tear the collision world down and reset the manager
//   00b5a410  FUN_00b5a410  - build an hkWorldCinfo, allocate + construct the hkWorld, register
//                            the agents, install the hkGroupFilter collision matrix, then create
//                            the editor-callback object stored at 0x0167ecdc
//
// Toolchain: VS2008 SP1 (cl 15.00) Spore game code; flags /O2 /MD /Gy /EHsc /TP (/arch:SSE
// /fp:fast for the float code in 00b5a410).
//
// Manager layout (offsets from the object base; `this` is in ECX):
//    +0x20  int    "busy" flag (0 == idle, entities may be created)
//    +0x30  uint8  enabled flag
//    +0x60  void** begin of the tracked-object list      +0x64  void** end
//    +0x14c8  map head   +0x14cc  table pointer   +0x14d0  table count
#include "types.h"

typedef uint32_t u32;

// ---------------------------------------------------------------------------------------------
// engine helpers modelled as members of dummy structs so that `this` lands in ECX
// ---------------------------------------------------------------------------------------------
struct HKWorldCinfo {
    uint8_t pad0[0x10];
    float   f10, f14, f18, f1c;     // +0x10
    uint8_t pad20[0x48];
    float   f68, f6c, f70;          // +0x68
    uint8_t pad74[0x20];
    uint8_t b94, b95;               // +0x94
    uint8_t pad96[0x10];

    void __thiscall ctor();                       // 0x010880e0
    void __thiscall setBroadPhaseWorldSize(float);  // 0x010881d0
};

// a one-byte by-value class, passed on the stack with the upper bytes undefined
struct hkBool {
    uint8_t v;
    hkBool(int x) { v = (uint8_t)x; }
};

struct hkWorld {
    uint8_t pad00[0x80];
    void*   field80;                // +0x80
    hkWorld* __thiscall CreateWorld(const HKWorldCinfo*, u32);      // 0x010840e0
    void __thiscall setCollisionFilter(void*, hkBool, int, int);    // 0x01086f80
};

struct hkGroupFilter {
    hkGroupFilter* __thiscall ctor();                    // 0x010c3cb0
    void __thiscall FUN_010c3c60(int, int);              // 0x010c3c60
    void __thiscall enableCollisionsBetween(int, int);   // 0x010c3c20
};

struct hkWorldObject {
    void __thiscall removeReference();                   // 0x0109ae60
};

struct AccessorDummy {
    void __thiscall FUN_01083110(void*, void*);          // 0x01083110
};

struct CacheDummy {
    void __thiscall FUN_00b520a0();                      // 0x00b520a0
};

typedef void  (__thiscall *VFn2)(void*, int);
typedef void* (__thiscall *VFnR1)(void*);
typedef void* (__thiscall *VFnR2)(void*, int);
typedef void* (__thiscall *VFnAlloc)(void*, int, int);

// free helpers
void  FUN_00b530e0(void*, void*);            // 0x00b530e0
void  FUN_00b57a50();                        // 0x00b57a50
void  FUN_00b54b80();                        // 0x00b54b80
void* FUN_00b3d310();                        // 0x00b3d310
void  FUN_00b53b20();                        // 0x00b53b20
void* FUN_006abeb0(int);                     // 0x006abeb0  factory(size)
void  CreateHavokEntityForObject(void*, void*, void*, void*);  // 0x00b56090
void  registerAllAgents(void*);              // 0x010c25a0
void  FUN_00b54890(void*, void*, void*);     // 0x00b54890
void  FUN_00b54970(void*, void*, void*);     // 0x00b54970
void  FUN_010834f0(void*, void*);            // 0x010834f0

// fixed retail globals
#define DAT_0167ecd0 (*(void**)0x0167ecd0)      // hkWorld*
#define DAT_0167ecd4 (*(void**)0x0167ecd4)      // hkWorldObject*
#define DAT_0167ecdc (*(void**)0x0167ecdc)      // editor callback object
#define DAT_016e4178 (*(void**)0x016e4178)      // hkMemory::s_instance
#define DAT_01569a94 (*(uint8_t*)0x01569a94)
#define DAT_01569a98 (*(float*)0x01569a98)
#define DAT_01569a9c (*(float*)0x01569a9c)
#define DAT_01569aa0 (*(float*)0x01569aa0)
#define DAT_0156b6ec (*(float*)0x0156b6ec)
#define DAT_013eb95c (*(float*)0x013eb95c)
#define DAT_01569ca4 (*(u32*)0x01569ca4)

struct Map14c8 {
    void*   head;       // +0x00
    int*    table;      // +0x04
    int     count;      // +0x08
    int* __thiscall FUN_00b41b30(void* out, void* key);   // 0x00b41b30
};

// ---------------------------------------------------------------------------------------------
// the singleton service object
// ---------------------------------------------------------------------------------------------
struct HavokSystem {
    uint8_t pad00[0x20];
    int     busy20;             // 0x20
    uint8_t pad24[0x0c];
    uint8_t b30;                // 0x30
    uint8_t pad31[0x2f];
    void**  begin;              // 0x60
    void**  end;                // 0x64
    uint8_t pad68[0x1460];
    Map14c8 map;                // 0x14c8

    void __thiscall FUN_00b5a260(void* p2, void* p3);
    void __thiscall FUN_00b5a2d0();
    void __thiscall FUN_00b5a390();
    void __thiscall FUN_00b5a410();
    int  __thiscall FUN_00b532f0(void* u);                // 0x00b532f0
};

// ---------------------------------------------------------------------------------------------
// 00b5a260
// ---------------------------------------------------------------------------------------------
// @ 0x00b5a260
void __thiscall HavokSystem::FUN_00b5a260(void* p2, void* p3)
{
    if (DAT_0167ecd0 != 0) {
        FUN_00b530e0(p2, p3);
        if (busy20 == 0) {
            void* sub = (p2 != 0) ? ((VFnR2)(*(void***)p2)[0xb8 / 4])(p2, 0x17f243b) : 0;
            void* u = ((VFnR1)(*(void***)sub)[0x20 / 4])(sub);
            int i = FUN_00b532f0(u);
            if (i != 0)
                CreateHavokEntityForObject(sub, p2, p3, (void*)i);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 00b5a2d0
// ---------------------------------------------------------------------------------------------
// @ 0x00b5a2d0
void __thiscall HavokSystem::FUN_00b5a2d0()
{
    if (DAT_0167ecd0 != 0) {
        void** it  = begin;
        void** fin = end;
        if (it != fin) {
            do {
                void* p = *it;
                void* sub = (p != 0) ? ((VFnR2)(*(void***)p)[0xb8 / 4])(p, 0x17f243b) : 0;
                FUN_00b530e0(p, p);
                if (busy20 == 0) {
                    void* u = ((VFnR1)(*(void***)sub)[0x20 / 4])(sub);
                    void* buf[2];
                    int* r = map.FUN_00b41b30(buf, &u);
                    if (*r != map.table[map.count]) {
                        int leaf = *r + 4;
                        if (leaf != 0)
                            CreateHavokEntityForObject(sub, p, p, (void*)leaf);
                    }
                }
                ++it;
            } while (it != fin);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 00b5a390
// ---------------------------------------------------------------------------------------------
// @ 0x00b5a390
void __thiscall HavokSystem::FUN_00b5a390()
{
    if (DAT_0167ecd0 != 0) {
        void* wo = DAT_0167ecd4;
        if (wo != 0) {
            ((hkWorldObject*)wo)->removeReference();
            void* wo2 = DAT_0167ecd4;
            if (wo2 != 0) {
                __declspec(align(16)) uint8_t buf;
                ((AccessorDummy*)*(void**)((uint8_t*)wo2 + 8))->FUN_01083110(&buf, wo2);
            }
            DAT_0167ecd4 = 0;
        }
        FUN_00b57a50();
        FUN_00b54b80();
        ((CacheDummy*)FUN_00b3d310())->FUN_00b520a0();
        if (DAT_01569ca4 != 0) {
            FUN_00b3d310();
            FUN_00b53b20();
        }
        *(uint8_t*)((uint8_t*)this + 0x30) = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// 00b5a410
// ---------------------------------------------------------------------------------------------
// @ 0x00b5a410
void __thiscall HavokSystem::FUN_00b5a410()
{
    HKWorldCinfo cinfo;
    uint8_t      buf[4];

    cinfo.ctor();
    cinfo.f10 = 0.0f;
    cinfo.f14 = 0.0f;
    cinfo.f18 = 0.0f;
    cinfo.f1c = 0.0f;
    cinfo.b94 = 1;
    cinfo.b95 = DAT_01569a94;
    cinfo.setBroadPhaseWorldSize(DAT_0156b6ec * DAT_013eb95c);
    cinfo.f70 = DAT_01569aa0;
    cinfo.f68 = DAT_01569a98;
    cinfo.f6c = DAT_01569a9c;

    void** memvt = *(void***)DAT_016e4178;
    void* block = ((VFnAlloc)memvt[0x10 / 4])(DAT_016e4178, 0x2f0, 0x2c);
    *(uint16_t*)((uint8_t*)block + 4) = 0x2f0;
    DAT_0167ecd0 = ((hkWorld*)block)->CreateWorld(&cinfo, 0x765c);
    registerAllAgents(*(void**)((uint8_t*)DAT_0167ecd0 + 0x80));

    void* raw = ((VFnAlloc)memvt[0x10 / 4])(DAT_016e4178, 0x9c, 0x24);
    *(uint16_t*)((uint8_t*)raw + 4) = 0x9c;
    hkGroupFilter* filter = ((hkGroupFilter*)raw)->ctor();
    filter->FUN_010c3c60(-2, -2);
    filter->enableCollisionsBetween(4, 4);
    filter->enableCollisionsBetween(4, 1);
    filter->enableCollisionsBetween(4, 2);
    filter->enableCollisionsBetween(4, 7);
    filter->enableCollisionsBetween(4, 8);
    filter->enableCollisionsBetween(4, 9);
    filter->enableCollisionsBetween(4, 5);
    filter->enableCollisionsBetween(4, 3);
    filter->enableCollisionsBetween(1, 4);
    filter->enableCollisionsBetween(1, 5);
    filter->enableCollisionsBetween(2, 2);
    filter->enableCollisionsBetween(2, 4);
    filter->enableCollisionsBetween(2, 7);
    filter->enableCollisionsBetween(2, 8);
    filter->enableCollisionsBetween(7, 4);
    filter->enableCollisionsBetween(7, 2);
    filter->enableCollisionsBetween(8, 8);
    filter->enableCollisionsBetween(8, 4);
    filter->enableCollisionsBetween(8, 5);
    filter->enableCollisionsBetween(8, 2);
    filter->enableCollisionsBetween(8, 3);
    filter->enableCollisionsBetween(9, 4);
    filter->enableCollisionsBetween(9, 5);
    filter->enableCollisionsBetween(10, 10);
    filter->enableCollisionsBetween(10, 4);
    filter->enableCollisionsBetween(10, 5);
    filter->enableCollisionsBetween(10, 2);
    filter->enableCollisionsBetween(10, 3);
    filter->enableCollisionsBetween(6, 8);
    filter->enableCollisionsBetween(6, 9);
    filter->enableCollisionsBetween(11, 3);
    filter->enableCollisionsBetween(11, 2);
    filter->enableCollisionsBetween(12, 1);
    filter->enableCollisionsBetween(12, 8);
    filter->enableCollisionsBetween(12, 9);
    filter->enableCollisionsBetween(3, 4);
    filter->enableCollisionsBetween(3, 8);
    filter->enableCollisionsBetween(5, 4);
    filter->enableCollisionsBetween(5, 1);
    filter->enableCollisionsBetween(5, 8);
    filter->enableCollisionsBetween(5, 9);
    ((hkWorld*)DAT_0167ecd0)->setCollisionFilter(filter, hkBool(1), 0, 1);

    void* obj = FUN_006abeb0(0x196c);
    if (obj != 0) {
        *(void**)obj = (void*)0x14614f4;
        FUN_00b54890((void*)((uint8_t*)obj + 4), buf, buf);
        FUN_00b54970((void*)((uint8_t*)obj + 0x1858), buf, buf);
    }
    DAT_0167ecdc = obj;
    FUN_010834f0(DAT_0167ecd0, obj);
}
