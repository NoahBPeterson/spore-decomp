// Slice s00c45140: constructor of a small multiple-vtable object.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

extern void* vtbl_0146d188[];
extern void* vtbl_0146d174[];
extern void* vtbl_0146d164[];
extern void* vtbl_013eb394[];

struct Base { void ctor(); };                     // 0x00b184c0

// Sub-object with a 0x20-byte body whose constructor is 0x00b638b0.
struct Sub {
    char pad[0x20];
    void ctor();                       // 0x00b638b0
};

struct C45140 {
    void* vt0;                         // +0x00
    void* vt4;                         // +0x04
    char  pad_08[0x34 - 0x08];
    void* vt34;                        // +0x34
    Sub   a;                           // +0x38
    Sub   b;                           // +0x58
    void ctor();
};

// @ 0x00c45140
void C45140::ctor()
{
    vt0  = vtbl_0146d188;
    vt4  = vtbl_0146d174;
    vt34 = vtbl_0146d164;
    b.ctor();
    a.ctor();
    vt34 = vtbl_013eb394;
    ((Base*)this)->ctor();
}
