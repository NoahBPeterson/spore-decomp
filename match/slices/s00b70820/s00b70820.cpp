// Slice s00b70820: 0x00b708d0, a tuning-struct loader that refreshes a static
// PropertyList (group = table[terrain index], instance = arg) and copies 50
// float/uint32 properties into the struct.
#include "types.h"

struct Property {
    uint32_t pad0[4];
    uint16_t pad10;
    uint16_t mnType;            // +0x12 (10 uint32, 13 float)
    uint32_t* GetUInt();        // 0x0041ea00
    float*    GetFloat();       // 0x0041ea70
};

struct PropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& out);  // +0x2c
};

cPropertyManager* PropertyManager();                     // 0x0067de30

struct cTerrainSphere { int GetIndex(); };               // 0x00c75420
struct cNounManager { cTerrainSphere* GetCurrentTerrainSphere(); };  // 0x00f67d90
cNounManager* NounManager();                             // 0x00b3d300

extern const uint32_t g_TerrainPropIDs[];                // 0x01464f04
extern PropertyList* g_TuningList;                       // 0x016879f8 (intrusive_ptr<PropertyList>)

static inline void ResetList(PropertyList*& sp)
{
    // eastl::intrusive_ptr::operator=(NULL)
    PropertyList* const pTemp = sp;
    if (pTemp) {
        sp = 0;
        pTemp->Release();
    }
}

// App::Property::GetFloat / GetUInt32 (static helpers, inlined)
static inline bool GetFloatProp(PropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd) {
        dst = *prop->GetFloat();
        return true;
    }
    return false;
}
static inline bool GetUIntProp(PropertyList* list, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xa) {
        dst = *prop->GetUInt();
        return true;
    }
    return false;
}
#define TF(id, dst) GetFloatProp(g_TuningList, id, dst)
#define TU(id, dst) GetUIntProp(g_TuningList, id, dst)

struct cTuning_b708d0 {
    float f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    uint32_t u68;
    float f6c;
    uint32_t u70;
    float f74;
    uint32_t u78;
    float f7c;
    uint32_t u80;
    float f84;
    uint32_t u88;
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8, fac, fb0, fb4, fb8, fbc, fc0, fc4, fc8;

    void Load(uint32_t instanceID);
};

// @ 0x00b708d0
void cTuning_b708d0::Load(uint32_t instanceID)
{
    int index = 1;
    if (NounManager()) {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere)
            index = sphere->GetIndex();
    }
    cPropertyManager* pm = PropertyManager();
    ResetList(g_TuningList);
    if (!pm->GetPropertyList(g_TerrainPropIDs[index], instanceID, g_TuningList))
        return;

    TF(0x015a2e6a, f04);
    TF(0x015a2e78, f00);
    TF(0x015a2e80, f08);
    TF(0x015a2e81, f0c);
    TF(0x015a2e82, f10);
    TF(0x015a2e83, f14);
    TF(0x046dc07f, f18);
    TF(0x046dc080, f1c);
    TF(0x046dc081, f20);
    TF(0x046dc082, f24);
    TF(0x046dc088, f28);
    TF(0x046dbf25, f34);
    TF(0x046dbf26, f38);
    TF(0x046dbf27, f3c);
    TF(0x015a2ea2, f2c);
    TF(0x046dc280, f30);
    TF(0x7105cce0, f40);
    TF(0xb1cb9c62, f44);
    TF(0x71dbb4ba, f48);
    TF(0x046dd2d0, f54);
    TF(0x046dd2d1, f58);
    TF(0x046dd2d2, f4c);
    TF(0x046dd2d3, f50);
    TF(0x7063d568, f5c);
    TF(0x70627ff6, f64);
    TU(0x90627ffa, u68);
    TF(0xd0627ffd, f6c);
    TU(0xd0628000, u70);
    TF(0x307b704e, f74);
    TU(0x907b7054, u78);
    TF(0x307b705a, f7c);
    TU(0x907b705e, u80);
    TF(0x30628002, f84);
    TU(0xd0628004, u88);
    TF(0x3063d320, f8c);
    TF(0xd063d3fb, f90);
    TF(0xf063d415, f94);
    TF(0xb063d44d, f98);
    TF(0xb063d417, f9c);
    TF(0xf063d418, fa0);
    TF(0xd063d44c, fa4);
    TF(0xb063d44d, fa8);
    TF(0xf063d44e, fac);
    TF(0x7063d44f, fb0);
    TF(0x3063d451, fb4);
    TF(0x7063d452, fb8);
    TF(0x1063d453, fbc);
    TF(0x1063d480, fc0);
    TF(0x1063d481, fc4);
    TF(0xd063d482, fc8);
    TF(0x9064f465, f60);
}

// ---------------------------------------------------------------------------
// Motive-tuning object construction and the feedback-event map helpers.
// ---------------------------------------------------------------------------

void __fastcall FUN_00b5b6c0(void* self);                 // SP::cGonzagoSimulator ctor
void* __cdecl FUN_00f473a0(int size, const char* file, int line,
                           int flags, const char* name, int allocatorFlags);
void __cdecl FUN_00f47380(void* node);
void* __cdecl FUN_00921580(void* node);                   // RBTreeIncrement
void __cdecl FUN_00921880(void* node, void* anchor);      // RBTreeErase

#define VTFN(obj, slot) (*(void***)(obj))[slot]

struct MotiveObject
{
    void*  m_vtable0;            // +0x00
    int    m_pad4;
    void*  m_vtable8;            // +0x08
    int    m_pad0c;
    void*  m_vtable10;           // +0x10
    int    m_field14;            // +0x14
    int    m_field18;            // +0x18
    int    m_field1c;            // +0x1c
    int    m_pad20[3];           // +0x20
    void*  m_field2c;            // +0x2c
    int    m_field30;            // +0x30
    int    m_field34;            // +0x34
    float  m_field38;            // +0x38
    float  m_field3c;            // +0x3c
    int    m_field40;            // +0x40
    int    m_pad44[2];           // +0x44
    void*  m_field4c;            // +0x4c
    int    m_field50;            // +0x50
    int    m_field54;            // +0x54
    float  m_field58;            // +0x58
    float  m_field5c;            // +0x5c
    int    m_field60;            // +0x60
    int    m_pad64;              // +0x64
    int    m_field68;            // +0x68
    int    m_field6c;            // +0x6c
    unsigned char m_field70;     // +0x70
};

struct TreeNode
{
    TreeNode* m_left;            // +0x00
    TreeNode* m_right;           // +0x04
    int       m_pad8[2];         // +0x08
    void*     m_ref10;           // +0x10
    void*     m_ref14;           // +0x14
};

struct MapView
{
    int       m_pad0;            // +0x00
    TreeNode* m_end;             // +0x04 (sentinel address)
    TreeNode* m_begin;           // +0x08
};

struct EraseMap
{
    int       m_pad0[4];         // +0x00
    int       m_size;            // +0x14
};

struct MotiveTree
{
    unsigned char m_pad0[0x20];  // +0x00
    void*     m_end;             // +0x20
    void*     m_leftmost;        // +0x24
    void*     m_root;            // +0x28
    unsigned char m_pad2c;       // +0x2c
    unsigned char m_pad2d[3];
    int       m_size;            // +0x30
};

struct RefPair
{
    void* m_first;
    void* m_second;
};

struct NewNode
{
    int   m_pad0[4];             // +0x00..+0x0f
    void* m_ref10;               // +0x10
    void* m_ref14;               // +0x14
};

// @ 0x00b70820
void* __fastcall FUN_00b70820(MotiveObject* self)
{
    FUN_00b5b6c0(self);

    self->m_vtable10 = (void*)0x013eb384;
    self->m_vtable0  = (void*)0x01464e18;
    self->m_vtable8  = (void*)0x01464df4;
    self->m_vtable10 = (void*)0x01464de4;

    self->m_field14 = 0;
    self->m_field18 = 0;
    self->m_field1c = 0;
    self->m_field38 = 1.0f;
    self->m_field3c = 2.0f;
    self->m_field34 = 0;
    self->m_field40 = 0;
    self->m_field30 = 1;
    self->m_field2c = (void*)0x0154df28;

    self->m_field58 = 1.0f;
    self->m_field5c = 2.0f;
    self->m_field54 = 0;
    self->m_field60 = 0;
    self->m_field50 = 1;
    self->m_field4c = (void*)0x0154df28;

    self->m_field68 = 0;
    self->m_field6c = 0;
    self->m_field70 = 1;
    return self;
}

// @ 0x00b71480
void __fastcall FUN_00b71480(cTuning_b708d0* self, uint32_t instanceID)
{
    self->Load(instanceID ? instanceID : 0xf71fa311u);
}

// @ 0x00b714a0
void __fastcall FUN_00b714a0(void* self, void* object)
{
    // Serializes the object's varlist; kept as a skeleton because the
    // serializer helpers use EA's private varint layout.
    (void)self;
    (void)object;
}

// @ 0x00b71510
bool __fastcall FUN_00b71510(void* self, void* event)
{
    (void)self;
    (void)event;
    return false;
}

// @ 0x00b71570
bool __cdecl FUN_00b71570(void* arg, MapView* map)
{
    TreeNode* const end = (TreeNode*)&map->m_end;
    for (TreeNode* node = map->m_begin; node != end;
         node = (TreeNode*)FUN_00921580(node)) {
        if (node->m_ref10 != 0)
            ((void (__thiscall*)(void*, void*))VTFN(node->m_ref10, 0x1c / 4))(node->m_ref10, arg);
        if (node->m_ref14 != 0)
            ((void (__thiscall*)(void*, void*))VTFN(node->m_ref14, 0x1c / 4))(node->m_ref14, arg);
    }
    return true;
}

// @ 0x00b715c0
void* __cdecl FUN_00b715c0(RefPair* pair)
{
    NewNode* node = (NewNode*)FUN_00f473a0(0x18, "Simulator", 0, 0, "allocator", 0xd1);
    if (node != 0) {
        node->m_ref10 = pair->m_first;
        if (node->m_ref10 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref10, 0xbc / 4))(node->m_ref10);

        node->m_ref14 = pair->m_second;
        if (node->m_ref14 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref14, 0))(node->m_ref14);
    }
    return node;
}

// @ 0x00b71680
void __fastcall FUN_00b71680(void* self, MotiveTree* map)
{
    // Map serialization skeleton; the iterator helpers are EASTL-internal.
    (void)self;
    (void)map;
}

// @ 0x00b71730
void __fastcall FUN_00b71730(EraseMap* self, TreeNode** out, TreeNode* node)
{
    self->m_size--;
    TreeNode* next = (TreeNode*)FUN_00921580(node);
    FUN_00921880(node, &self->m_pad0[1]);

    if (node->m_ref14 != 0)
        ((void (__thiscall*)(void*))VTFN(node->m_ref14, 4 / 4))(node->m_ref14);
    if (node->m_ref10 != 0)
        ((void (__thiscall*)(void*))VTFN(node->m_ref10, 0xc0 / 4))(node->m_ref10);

    FUN_00f47380(node);
    *out = next;
}

// @ 0x00b71790
void __fastcall FUN_00b71790(TreeNode* node)
{
    while (node != 0) {
        FUN_00b71790(node->m_left);
        TreeNode* next = node->m_right;

        if (node->m_ref14 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref14, 4 / 4))(node->m_ref14);
        if (node->m_ref10 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref10, 0xc0 / 4))(node->m_ref10);

        FUN_00f47380(node);
        node = next;
    }
}

// @ 0x00b71a30
void __fastcall FUN_00b71a30(MotiveTree* self)
{
    FUN_00b71790((TreeNode*)self->m_root);
    self->m_leftmost = (void*)&self->m_end;
    self->m_end = (void*)&self->m_end;
    self->m_root = 0;
    self->m_pad2c = 0;
    self->m_size = 0;
}
