// Slice s0055beb0: SP::cFunctionalTestCheat, SP::cSPObjectTemplateDB and the
// Editor ObjectTemplateDB factory. Unoptimized /Od module.
#include "types.h"

void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);
void  operator delete(void* p);

namespace Editor {
class ObjectTemplateDB {
public:
    ObjectTemplateDB();
    uint32_t pad[0x270 / 4];
};
}

namespace SP {

// @ 0x0055BEB0
class cFunctionalTestCheat {
public:
    const char* Description(int index);
    bool IsEnabled();
};
const char* cFunctionalTestCheat::Description(int index) {
    if (index == 0)
        return "Used to debug OTDB parameters";
    else
        return "\n-get_key_params <SPID key name>\n   dump otdb parameters associated with the given file/key\n"
               "-get_id_params <SPID key name>\n   dump otdb parameters associated with the given server id.\n";
}

// @ 0x0055BEE0
bool cFunctionalTestCheat::IsEnabled() {
    return true;
}

// @ 0x0055C640  Editor::ObjectTemplateDB factory
Editor::ObjectTemplateDB* CreateObjectTemplateDB() {
    return new ("Editor/ObjectTemplateDB", 0, 0, 0, 0) Editor::ObjectTemplateDB();
}

// @ 0x0055C690
class cSPObjectTemplateDB {
public:
    uint32_t pad[1];
    void* AsInterface(int type);
};
void* cSPObjectTemplateDB::AsInterface(int type) {
    switch (type) {
    case 0x4ed03fd:
        return this;
    case 0x4ed5013:
        return this ? (void*)((char*)this + 4) : 0;
    case 0xee3f516e:
        return this;
    }
    return 0;
}

namespace W1G2_62 {

// @ 0x0055BF10 — partial: constructor storing embedded vtable pointers + atomic field
class c55bf10 {
public:
    c55bf10();
    uint32_t pad[1];
};
c55bf10::c55bf10() {
    pad[0] = 0;
}

// @ 0x0055BF50 — partial: constructor storing two vtable pointers
class c55bf50 {
public:
    c55bf50();
    uint32_t pad[1];
};
c55bf50::c55bf50() {
    pad[0] = 0;
}

// @ 0x0055BFB0 — partial: SP::cSPObjectTemplateDB::Shutdown (805 bytes)
class c55bfb0 {
public:
    uint32_t pad[0x200];
    void Shutdown();
};
void c55bfb0::Shutdown() {
}

// @ 0x0055C2E0 — partial
class c55c2e0 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55c2e0::sub() {
}

// @ 0x0055C3C0 — partial: SP::cSPObjectTemplateDB::HandleMessage (640 bytes)
class c55c3c0 {
public:
    uint32_t pad[0x200];
    void sub(int a, void* b);
};
void c55c3c0::sub(int a, void* b) {
}

// @ 0x0055C6F0 — partial
class c55c6f0 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55c6f0::sub() {
}

// @ 0x0055C9E0 — partial
class c55c9e0 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55c9e0::sub() {
}

// @ 0x0055CB50 — partial
class c55cb50 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55cb50::sub() {
}

// @ 0x0055CD90 — partial
class c55cd90 {
public:
    uint32_t pad[0x200];
    void sub();
};
void c55cd90::sub() {
}

}
}
