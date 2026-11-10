// Slice s00891950 -- destructor for the object whose vtable is 0x0142ea60.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include "types.h"

// ---- callees ---------------------------------------------------------------
struct Allocator_00891950;
typedef void (__thiscall *FreeFn_00891950)(Allocator_00891950* self, void* p, int bytes);

struct Allocator_00891950 {
    void** vtable;                                    // +0x00
};

struct SubObj_00891950 {                              // at this+0x168
    char pad[0x100];
    ~SubObj_00891950();                               // 0x0089f3c0
};

struct Container_00891950 {                           // at this+0x100
    char pad[0x04];
    void*    m104;                                    // +0x04
    unsigned m108;                                    // +0x08
    int      m10c;                                    // +0x0c
    char pad2[0x1c - 0x10];
    Allocator_00891950* m11c;                         // +0x1c
    void Clear(void* first, unsigned count);          // 0x00885e20
};

struct Base_00891950 {
    void* vptr;                                       // +0x00
    ~Base_00891950();                                 // 0x0088b560
};

struct Obj_00891950 : Base_00891950 {
    char pad[0x100 - 4];
    Container_00891950 mContainer;                    // +0x100
    char pad2[0x168 - 0x100 - sizeof(Container_00891950)];
    void Shutdown();                                  // 0x00891220
    ~Obj_00891950();
};

// @ 0x00891950
Obj_00891950::~Obj_00891950()
{
    vptr = (void*)0x0142ea60;
    Shutdown();
    ((SubObj_00891950*)((char*)this + 0x168))->~SubObj_00891950();

    Container_00891950* c = &mContainer;
    c->Clear(c->m104, c->m108);
    c->m10c = 0;
    if (c->m108 > 1) {
        Allocator_00891950* a = c->m11c;
        ((FreeFn_00891950)a->vtable[3])(a, c->m104, c->m108 * 4 + 4);
    }
}
