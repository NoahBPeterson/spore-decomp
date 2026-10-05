// Slice s00559050: Editor ObjectTemplateDB / property-list destructor helpers.
// Unoptimized /Od module.
#include "types.h"

namespace Editor {

// @ 0x00559500  element refcount-style increment (field at this+0x10)
class cCounterHolder {
public:
    uint32_t pad[3];
    uint32_t mCount;
    int Increment();
};
int cCounterHolder::Increment() {
    uint32_t* v33 = (uint32_t*)((char*)this + 0xc);
    int len = (int)v33[1] + 1;
    v33[1] = v33[1] + 1;
    return len;
}

namespace W1G2_58 {

// @ 0x00559050 — partial: scalar deleting destructor for cPropertyList/cEditorResource
class c559050 {
public:
    uint32_t pad[0x40];
    void* Dtor(uint32_t flags);   // @ 0x00559050
};
void* c559050::Dtor(uint32_t) {
    return 0;
}

// @ 0x005590C0 — partial
class c5590c0 {
public:
    uint32_t pad[0x40];
    void sub(int a, int b, int c, int d);   // @ 0x005590C0
};
void c5590c0::sub(int a, int b, int c, int d) {
}

// @ 0x00559110 — partial: Editor::ObjectTemplateDB constructor (967 bytes)
class cObjectTemplateDB {
public:
    uint32_t pad[0x200];
    cObjectTemplateDB();
};
cObjectTemplateDB::cObjectTemplateDB() {
}

// @ 0x005594E0 — partial: constructor storing two vtable pointers
class c5594e0 {
public:
    c5594e0();
};
c5594e0::c5594e0() {
}

// @ 0x00559590 — partial
class c559590 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c559590::sub() {
}

}
}
