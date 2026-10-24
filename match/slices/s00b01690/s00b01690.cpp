// s00b01690 - Simulator tree/fruit cluster (Ghidra-reconstructed C++).
//
// Compiled with: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed int         i32;
typedef float              f32;

// ---------------------------------------------------------------------------
// external symbols / helpers
// ---------------------------------------------------------------------------
void* op_new(u32 size, const char* a, int b, int c, const char* d, int e); // 0x00f473a0
void  op_delete_array(void* p);                                          // 0x00f47380

void  Matrix3_Assign(void* dst, const void* src);                        // 0x0041cb40
// Matrix3 xform ctor: __thiscall (this = dst, 1 stack arg = src, callee cleanup).
struct CMatrix3Ops { void Assign(const void* src); };                    // 0x0041cb40
#define M3(p) ((CMatrix3Ops*)(p))
void  FUN_00c3f9b0(void);                                                // 0x00c3f9b0
void  FUN_00c3f9a0(u32);                                                 // 0x00c3f9a0
void  __stdcall FUN_00c3ff10(void*);                                    // 0x00c3ff10
void  __stdcall FUN_00c3fad0(void*);                                    // 0x00c3fad0
void  FUN_00ac0520(void);                                                // 0x00ac0520
void  FUN_00b184c0(void);                                                // 0x00b184c0
void* SP_cSpatialObjectView_ctor(void* p);                               // 0x00e92af0
void* SP_cInteractionTarget_ctor(void* p);                               // 0x00ac03d0
void* SP_EffectsManager(void);                                           // 0x0067ddd0
void* SP_GetCurrentGameMode(void);                                       // 0x00b5b800
void* SP_NounManager(void*);                                             // 0x00b3d300
void  FUN_00b3d320(void);                                                // 0x00b3d320
void* FUN_00b1daf0(void);                                                // 0x00b1daf0
void* SP_cGameNounManager_CreateNoun(void* key);                         // 0x00b20c60
void* SP_GetActiveTerrainSphere(void);                                   // 0x00f48aa0
void  SP_cHierGrid_Shutdown(void);                                       // 0x00704060
void  SP_cHierGrid_Init(void* self, const void* v, float f, int a, int b); // 0x00704260
u32   SP_cHierGrid_CreateEntry(void* self, const void* v, float f);      // 0x00703d50
void  SP_HierGridStub_Remove(void* self, u32 i);                         // 0x00702da0
void  FUN_00e5c780(void* tree, const u32* key, u32* out);               // 0x00e5c780 rbtree::find
// eastl rbtree find: __thiscall (this = tree, 2 stack args: key, out).
struct CRBTreeFind { void find(const u32* key, u32* out); };             // 0x00e5c780
#define RBF(p) ((CRBTreeFind*)(p))
void  FUN_00a887b0(u32 a, u32 b);                                        // 0x00a887b0
void  FUN_00a057f0(void* a, const void* b);                              // 0x00a057f0
void  XformMsg_ctor(void* p);                                            // 0x00434040
bool  EA_IO_WriteUint32(void* stream, const void* p, int n, int m);      // 0x0093aa70
void* SP_cVarListSerializer_ctor(void* self, const void* p, const void* q, const void* r); // 0x00692f90
bool  SP_cVarListSerializer_Serialize(void* self, void* stream);         // 0x00692900
void* cProperty_GetBool(void* p);                                        // 0x0041e920
void* cProperty_GetInt(void* p);                                         // 0x0041e990
void* cProperty_GetFloat(void* p);                                       // 0x0041ea70
void* Inst_00b01cb0(void* self, void* src);                              // 0x00b01cb0
void  GridRebuildProxy(void* self);                                      // 0x00b02120
void* CTransformOps_Assign(void* self, const void* src);                 // 0x00537dc0
// ecx-taking transform assign (this = target, 1 stack arg, callee cleanup).
struct CTransformAssignOps {
    void* Assign(const void* src);                    // 0x00537dc0
};
// globals
static f32 g_167af5c = 0.0f;             // 0x0167af5c
static f32 g_167af60 = 0.0f;             // 0x0167af60
static f32 g_167af64 = 0.0f;             // 0x0167af64
static u32 g_167b550 = 0;                // 0x0167b550
static f32 g_1567398 = 0.0f;             // 0x01567398
static f32 g_156739c = 0.0f;             // 0x0156739c
static f32 g_15673a0 = 0.0f;             // 0x015673a0
static u32 g_15673a4 = 0;                // 0x015673a4
static u32 g_15673c0 = 0, g_15673c4 = 0; // 0x015673c0 / 0x015673c4
static u32 g_15673c8 = 0, g_15673cc = 0; // 0x015673c8 / 0x015673cc

// vtable fetch helper: reads the vtable pointer stored at the object's offset 0.
static inline void** vtbl(const void* p) { return *(void***)p; }
static inline u8*    at(void* p, int o)  { return (u8*)p + o; }
// vtable-slot call helpers (this = obj in ecx).
static inline void  vcall0(void* obj, int off) { (*(void(__thiscall**)(void*))((char*)vtbl(obj) + off))(obj); }
static inline void  vcall1(void* obj, int off, void* a) { (*(void(__thiscall**)(void*, void*))((char*)vtbl(obj) + off))(obj, a); }
static inline void  vcall1i(void* obj, int off, int a) { (*(void(__thiscall**)(void*, int))((char*)vtbl(obj) + off))(obj, a); }
static inline void* vcall0r(void* obj, int off) { return (*(void*(__thiscall**)(void*))((char*)vtbl(obj) + off))(obj); }

// ===========================================================================
// 0x00b01690 - sift-up heap insert of a float* keyed by squared distance
// ===========================================================================
// @ 0x00b01690
void FUN_00b01690(void** arr, int root, int hole, const f32* key, f32 kx, f32 ky, f32 kz)
{
    if (hole <= root) {
        arr[hole] = (void*)key;
        return;
    }
    f32 x0 = key[0], y0 = key[1], z0 = key[2];
    int parent;
    do {
        parent = (hole - 1) >> 1;
        const f32* p = (const f32*)arr[parent];
        f32 dx0 = kx - x0, dy0 = ky - y0, dz0 = kz - z0;
        f32 d0 = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
        f32 dx1 = kx - p[0], dy1 = ky - p[1], dz1 = kz - p[2];
        f32 d1 = dx1 * dx1 + dz1 * dz1 + dy1 * dy1;
        if (d0 <= d1) break;
        arr[hole] = (void*)p;
        hole = parent;
    } while (parent > root);
    arr[hole] = (void*)key;
}

// ===========================================================================
// 0x00b01770 - Simulator::cTreeData::cTreeData
// ===========================================================================
struct Simulator_cTreeData {
    void* vtbl;                      // +0x00
    void* vtbl8;                     // +0x04
    u32   f08;                       // +0x08
    u16   f0c;                       // +0x0c
    u16   f0e;                       // +0x0e
    f32   f10;                       // +0x10
    f32   f14;                       // +0x14
    f32   f18;                       // +0x18
    f32   f1c;                       // +0x1c
    u32   m20[10];                   // +0x20..0x48 (matrix33 + pad)
    u32   f48;                       // +0x48
    u32   f4c;                       // +0x4c
    u32   f50;                       // +0x50
    u32   f54;                       // +0x54
    u32   f58;                       // +0x58
    u32   f5c;                       // +0x5c
    u32   f60;                       // +0x60
    u32   f64;                       // +0x64
    u32   f68;                       // +0x68
    f32   f6c;                       // +0x6c
    f32   f70;                       // +0x70
    f32   f74;                       // +0x74
    u32   f78;                       // +0x78
    u8    f7c;                       // +0x7c
    Simulator_cTreeData();
};

// @ 0x00b01770
Simulator_cTreeData::Simulator_cTreeData()
{
    this->vtbl8 = (void*)0x013ec458;
    this->f08 = 0;
    this->vtbl = (void*)0x0145c678;
    this->vtbl8 = (void*)0x0145c668;
    this->f0e = 0;
    this->f0c = 0;
    this->f10 = g_167af5c;
    this->f14 = g_167af60;
    this->f18 = g_167af64;
    this->f1c = 1.0f;
    M3(&this->m20[0])->Assign((const void*)0x0167b554);
    this->f48 = 0;
    this->f4c = 0;
    this->f50 = 0;
    this->f54 = 0;
    this->f58 = 0x6d60a1cc;
    this->f5c = 0;
    this->f60 = 0;
    this->f64 = 0;
    this->f68 = 0;
    this->f7c = 0;
    this->f6c = 0.0f;
    this->f70 = 0.0f;
    this->f74 = 0.0f;
    this->f78 = 0xffffffff;
}

// ===========================================================================
// 0x00b01890 - cFruitView factory (ecx-taking, ret 4 => member with 1 arg)
// ===========================================================================
struct cFruitViewFactory {
    void* Create(void* owner);
};
// @ 0x00b01890
void* cFruitViewFactory::Create(void* owner)
{
    void* v;
    if (owner == 0) {
        v = 0;
    } else {
        v = (*(void*(__thiscall**)(void*, u32))((char*)vtbl(owner) + 0xc))(owner, 0x02c9cc8e);
    }
    void* sub = at(v, 0x34);
    if ((*(void*(__thiscall**)(void*))((char*)vtbl(sub) + 0xac))(sub) == 0) {
        return 0;
    }
    u8* o = (u8*)op_new(0x38, "Simulator/cFruitView", 0, 0, 0, 0);
    if (o != 0) {
        SP_cSpatialObjectView_ctor(o);
        *(void**)o = (void*)0x0145c6d0;
        *(u32*)(o + 0x34) = 0;
        (*(void(__thiscall**)(void*, void*))((char*)vtbl(o) + 0x24))(o, owner);
        return o;
    }
    (*(void(__thiscall**)(void*))((char*)vtbl((void*)0) + 0x24))((void*)0);
    return 0;
}

// ===========================================================================
// 0x00b01910 - Simulator::cFruit::cFruit
// ===========================================================================
struct Simulator_cFruit {
    void* vtbl;      // +0x00
    void* vtbl4;     // +0x04
    u32   m08[0xb];  // +0x08
    void* vtbl34;    // +0x34
    u32   m38[0x10]; // +0x38
    u32   f84;       // +0x84
    u32   f88;       // +0x88
    u8    f8c[0x19]; // +0x8c
    u8    fa5;       // +0xa5
    u32   m108;      // +0x108
    u8    pad10c[0x44];
    u32   f148;      // +0x148
    u32   f150;      // +0x150
    u32   f154;      // +0x154
    u32   f158;      // +0x158
    u32   f15c;      // +0x15c
    u32   f160;      // +0x160
    u32   f164;      // +0x164
    u32   f168;      // +0x168
    u32   f16c;      // +0x16c
    u8    m130[0x18];
    Simulator_cFruit();
};

// @ 0x00b01910
Simulator_cFruit::Simulator_cFruit()
{
    FUN_00c3f9b0();
    SP_cInteractionTarget_ctor((u8*)this + 0x130);
    *(void**)this = (void*)0x0145c5c8;
    this->vtbl4 = (void*)0x0145c5b4;
    this->vtbl34 = (void*)0x0145c4f0;
    *(void**)((u8*)this + 0x130) = (void*)0x0145c4d0;
    this->f148 = 0;
    FUN_00c3f9a0(4);
    this->f88 = 6;
    this->f84 |= 0x200;
    this->fa5 = 0;
    this->f158 = 0x6d60a1cc;
    this->f15c = 0xffffffff;
    this->f160 = 0xffffffff;
    this->f164 = 0xffffffff;
    this->f150 = 0xffffffff;
    this->f154 = 0;
    this->f168 = 0;
    if (this->f16c != 6) {
        void* p = (void*)this->m108;
        if (p != 0) {
            this->m108 = 0;
            vcall0(p, 4);
        }
        this->f16c = 6;
    }
}

// ===========================================================================
// 0x00b019d0 - cFruit::Enable (member, 1 arg, ret 4)
// ===========================================================================
struct cFruitOps1 {
    void Enable(void* arg);
};
// @ 0x00b019d0
void cFruitOps1::Enable(void* arg)
{
    FUN_00c3ff10(arg);
    *(u32*)((u8*)this + 0x148) |= 2;
    *(u8*)((u8*)this + 0xa5) = 1;
    *(u32*)((u8*)this + 0x16c) = 3;
}

// ===========================================================================
// 0x00b01a00 - cFruit::Disable (member, 1 arg, ret 4)
// ===========================================================================
struct cFruitOps2 {
    void Disable(void* arg);
};
// @ 0x00b01a00
void cFruitOps2::Disable(void* arg)
{
    FUN_00c3fad0(arg);
    *(u32*)((u8*)this + 0x148) &= 0xfffffffd;
    if (*(u32*)((u8*)this + 0x16c) != 2) {
        *(u32*)((u8*)this + 0x168) = 0;
        *(u32*)((u8*)this + 0x16c) = 2;
    }
}

// ===========================================================================
// 0x00b01a40 - cFruitGroup destructor
// ===========================================================================
struct Simulator_cFruitGroup {
    void* vtbl;       // +0x00
    void* vtbl4;      // +0x04
    u32   m08[0xb];   // +0x08
    void* vtbl34;     // +0x34
    u32   m38[5];     // +0x38
    u32   f4c;        // +0x4c
    u32   f50;        // +0x50
    u32   f54;        // +0x54
    u8    pad58[0x48];
    u32   fa0;        // +0xa0
    u32   fa4;        // +0xa4
    u8    padA8[0xf4];
    u32   f19c;       // +0x19c
    u8    pad1a0[0x24];
    u32   f1c4;       // +0x1c4
    u8    pad1c8[8];
    u32   f1d0;       // +0x1d0
    ~Simulator_cFruitGroup();
};

// @ 0x00b01a40
Simulator_cFruitGroup::~Simulator_cFruitGroup()
{
    Simulator_cFruitGroup* self = this;
    *(void**)self = (void*)0x0145c748;
    self->vtbl4 = (void*)0x0145c738;
    self->vtbl34 = (void*)0x0145c71c;
    self->f4c = 0;
    self->f54 = 0;
    void* p1 = (void*)self->f1d0;
    if (p1 != 0) {
        vcall0(p1, 4);
    }
    void* p2 = (void*)self->f1c4;
    if (p2 != 0) {
        vcall0(p2, 4);
    }
    u32 a = self->f19c;
    if (a != 0 && *(u32*)(a - 4) != 0) {
        op_delete_array((void*)a);
    }
    u32 b = self->fa4;
    if (b != 0 && *(u32*)(b - 4) != 0) {
        op_delete_array((void*)b);
    }
    void* p3 = (void*)self->fa0;
    if (p3 != 0) {
        vcall0(p3, 4);
    }
    FUN_00ac0520();
    FUN_00b184c0();
}

// ===========================================================================
// 0x00b01b50 - cFruitGroup::SetSomething (member, 2 args, ret 8)
// ===========================================================================
struct cFruitGroupOps {
    void SetEffect(u32 mode, u8 force);
};
// @ 0x00b01b50
void cFruitGroupOps::SetEffect(u32 mode, u8 force)
{
    u8* self = (u8*)this;
    if (*((u32*)self + 0x1cc / 4) == mode && force == 0) {
        return;
    }
    if (mode > 2) {
        return;
    }
    u32* slot = (u32*)(self + 0x1d0);
    *(u32*)(self + 0x1cc) = mode;
    if (*slot != 0) {
        void* cur = (void*)*slot;
        (*(void(__thiscall**)(void*, int))((char*)vtbl(cur) + 0xc))(cur, 1);
        void* c2 = (void*)*slot;
        if (c2 != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(c2) + 4))(c2);
        }
    }
    if (*(u32*)(self + 0x1cc) == 1) {
        void* em = SP_EffectsManager();
        void* cur = (void*)*slot;
        if (cur != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(cur) + 4))(cur);
        }
        (*(void(__thiscall**)(void*, u32, u32, u32*))((char*)vtbl(em) + 0x2c))(em, g_15673c0, g_15673c4, slot);
    } else if (*(u32*)(self + 0x1cc) == 2) {
        void* em = SP_EffectsManager();
        void* cur = (void*)*slot;
        if (cur != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(cur) + 4))(cur);
        }
        (*(void(__thiscall**)(void*, u32, u32, u32*))((char*)vtbl(em) + 0x2c))(em, g_15673c8, g_15673cc, slot);
    }
    if (*slot != 0) {
        u8 msg[0x38];
        XformMsg_ctor(msg);
        *(u32*)(msg + 4) = *(u32*)(self + 0x5c);
        *(u32*)(msg + 8) = *(u32*)(self + 0x60);
        *(u32*)(msg + 0xc) = *(u32*)(self + 0x64);
        *(u16*)(msg + 2) = *(u16*)(msg + 2) + 1;
        *(u16*)(msg + 0) |= 4;
        f32 scale = *(f32*)(self + 0x68) * 1.5f;
        for (int i = 0; i < 9; i++) {
            *(u32*)(msg + 0x14 + i * 4) = *(u32*)(self + 0x6c + i * 4);
        }
        u16 w = *(u16*)(msg + 2);
        *(u16*)(msg + 0) |= 2;
        w = (u16)(w + 1);
        w = (u16)(w + 1);
        *(u16*)(msg + 2) = w;
        *(f32*)(msg + 0x10) = scale;
        void* target = (void*)*slot;
        (*(void(__thiscall**)(void*, u8*))((char*)vtbl(target) + 0x18))(target, msg);
        void* t2 = (void*)*slot;
        (*(void(__thiscall**)(void*, int))((char*)vtbl(t2) + 8))(t2, 0);
    }
}

// ===========================================================================
// 0x00b01cb0 - AutoRefCount-holding record assign (member, 1 arg, ret 4)
// ===========================================================================
struct RefRecordOps {
    void* Assign(const void* src);
};
// @ 0x00b01cb0
void* RefRecordOps::Assign(const void* src)
{
    u8* self = (u8*)this;
    const u8* s = (const u8*)src;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0) = *(u32*)(s + 0);
    *(u32*)(self + 8) = *(u32*)(s + 8);
    *(u32*)(self + 0xc) = *(u32*)(s + 0xc);
    void* p1 = *(void**)(s + 0x10);
    void* old1 = *(void**)(self + 0x10);
    if (p1 != old1) {
        if (p1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p1) + 0))(p1);
        }
        *(void**)(self + 0x10) = p1;
        if (old1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old1) + 4))(old1);
        }
    }
    void* p2 = *(void**)(s + 0x14);
    void* old2 = *(void**)(self + 0x14);
    if (p2 != old2) {
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p2) + 0x34))(p2);
        }
        *(void**)(self + 0x14) = p2;
        if (old2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old2) + 0x38))(old2);
        }
    }
    *(u32*)(self + 0x18) = *(u32*)(s + 0x18);
    return self;
}

// ===========================================================================
// 0x00b01d30 - same assign without the zeroing prologue (member, 1 arg)
// ===========================================================================
struct RefRecordOps2 {
    void* Assign2(const void* src);
};
// @ 0x00b01d30
void* RefRecordOps2::Assign2(const void* src)
{
    u8* self = (u8*)this;
    const u8* s = (const u8*)src;
    *(u32*)(self + 0) = *(u32*)(s + 0);
    *(u32*)(self + 8) = *(u32*)(s + 8);
    *(u32*)(self + 0xc) = *(u32*)(s + 0xc);
    void* p1 = *(void**)(s + 0x10);
    void* old1 = *(void**)(self + 0x10);
    if (p1 != old1) {
        if (p1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p1) + 0))(p1);
        }
        *(void**)(self + 0x10) = p1;
        if (old1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old1) + 4))(old1);
        }
    }
    void* p2 = *(void**)(s + 0x14);
    void* old2 = *(void**)(self + 0x14);
    if (p2 != old2) {
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p2) + 0x34))(p2);
        }
        *(void**)(self + 0x14) = p2;
        if (old2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old2) + 0x38))(old2);
        }
    }
    *(u32*)(self + 0x18) = *(u32*)(s + 0x18);
    return self;
}

// ===========================================================================
// 0x00b01db0 - cAppModeEditorBase::HandleGameCommandMessage (member, 1 arg)
// ===========================================================================
struct cPropertyOps {
    bool GetP(void* out, u32 key);
};
struct cAppModeEditorBase {
    void HandleGameCommandMessage(void* arg);
};
// @ 0x00b01db0
void cAppModeEditorBase::HandleGameCommandMessage(void* arg)
{
    u8* self = (u8*)this;
    u32 key = (u32)arg;
    if (key == 0x01654c06) {
        key = (u32)SP_GetCurrentGameMode();
    }
    FUN_00b3d320();
    void* mgr = FUN_00b1daf0();
    void* src = SP_NounManager((void*)key);
    (void)src;
    void* inst = mgr;
    if (inst != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(inst) + 0))(inst);
    }
    bool flagEnter = false;
    if (inst != 0) {
        u32 out;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out, 0x3337809)
            && *(u16*)(out + 0x12) == 1) {
            flagEnter = *(bool*)cProperty_GetBool((void*)out);
        }
        u32 out2;
        bool b2 = false;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out2, 0x33385cd)
            && *(u16*)(out2 + 0x12) == 1) {
            b2 = *(bool*)cProperty_GetBool((void*)out2);
        }
        if (b2) {
            *(u32*)(self + 0x1ba18c) |= 8;
        } else {
            *(u32*)(self + 0x1ba18c) &= 0xfffffff7;
        }
        u32 out3;
        bool b3 = false;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out3, 0x62978be)
            && *(u16*)(out3 + 0x12) == 1) {
            b3 = *(bool*)cProperty_GetBool((void*)out3);
        }
        if (b3) {
            *(u32*)(self + 0x1ba18c) |= 0x20;
        } else {
            *(u32*)(self + 0x1ba18c) &= 0xffffffdf;
        }
        i32 oldv = *(i32*)(self + 0x1b8e10);
        i32 newv = 0;
        u32 out4;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out4, 0x339ddf2)
            && *(u16*)(out4 + 0x12) == 9) {
            newv = *(i32*)cProperty_GetInt((void*)out4);
            if (newv < 0 || newv > 1) {
                newv = 0;
            }
        }
        *(i32*)(self + 0x1b8e10) = newv;
        if (oldv != newv) {
            *(u32*)(self + 0x1ba18c) |= 4;
        }
        u32 out5;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out5, 0x302aa89)
            && *(u16*)(out5 + 0x12) == 0xd) {
            g_1567398 = *(f32*)cProperty_GetFloat((void*)out5);
        }
        u32 out6;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out6, 0x302aa8f)
            && *(u16*)(out6 + 0x12) == 0xd) {
            g_156739c = *(f32*)cProperty_GetFloat((void*)out6);
        }
        u32 out7;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out7, 0x302aa93)
            && *(u16*)(out7 + 0x12) == 0xd) {
            f32 v = *(f32*)cProperty_GetFloat((void*)out7) * 1000.0f;
            g_15673a4 = (u32)(i32)v;
        }
        u32 out8;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out8, 0x302aa9b)
            && *(u16*)(out8 + 0x12) == 0xd) {
            f32 v = *(f32*)cProperty_GetFloat((void*)out8) * 1000.0f;
            g_167b550 += (u32)(i32)v + g_15673a4;
        }
        u32 out9;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out9, 0x302aa97)
            && *(u16*)(out9 + 0x12) == 0xd) {
            g_15673a0 = *(f32*)cProperty_GetFloat((void*)out9);
        }
    }
    if (flagEnter) {
        *(u32*)(self + 0x1ba18c) |= 1;
    } else {
        *(u32*)(self + 0x1ba18c) &= 0xfffffffe;
    }
    if (inst != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(inst) + 4))(inst);
    }
}

// ===========================================================================
// 0x00b02060 - create/reuse a noun (member)
// ===========================================================================
struct NounCreator {
    void* GetOrCreate();
};
// @ 0x00b02060
void* NounCreator::GetOrCreate()
{
    u8* self = (u8*)this;
    i32 count = (i32)((*(u32*)(self + 0x1b9178) - *(u32*)(self + 0x1b9174)) >> 2);
    void* result = 0;
    if (count > 0) {
        u8* end = (u8*)*(u32*)(self + 0x1b9178);
        void* p = *(void**)(end - 4);
        if (p != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p) + 0))(p);
            result = p;
        }
        *(u32*)(self + 0x1b9178) = *(u32*)(self + 0x1b9178) - 4;
        void* q = *(void**)*(u32*)(self + 0x1b9178);
        if (q != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q);
        }
    } else {
        void* n = SP_cGameNounManager_CreateNoun((void*)0x2e96892);
        if (n != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(n) + 0))(n);
            result = n;
        }
    }
    if (result != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(result) + 4))(result);
    }
    return result;
}

// ===========================================================================
// 0x00b02120 - rebuild the debug hierarchical grid (no args)
// ===========================================================================
struct GridOwner {
    void Rebuild();
};
// @ 0x00b02120
void GridOwner::Rebuild()
{
    u8* self = (u8*)this;
    if (SP_GetActiveTerrainSphere() == 0) {
        return;
    }
    void* ts = SP_GetActiveTerrainSphere();
    if ((*(void*(__thiscall**)(void*))((char*)vtbl(ts) + 0xc))(ts) == 0) {
        return;
    }
    void* ts2 = SP_GetActiveTerrainSphere();
    void* s = (*(void*(__thiscall**)(void*))((char*)vtbl(ts2) + 0xc))(ts2);
    f32 r = (*(f32*)((u8*)s + 0x38) * *(f32*)((u8*)s + 0x54) + *(f32*)((u8*)s + 0x34)) + 50.0f;
    f32 x0 = g_167af5c - r, x1 = g_167af5c + r;
    f32 y0 = g_167af60 - r, y1 = g_167af60 + r;
    f32 z0 = g_167af64 - r, z1 = g_167af64 + r;
    f32 v[5];
    v[0] = x0;  v[1] = y0;  v[2] = z0;  v[3] = y1;  v[4] = z1;
    v[0] = x1;
    f32 dx = v[0] - x0;
    f32 dy = y1 - y0;
    f32 dz = z1 - z0;
    f32* p = &v[2];
    if (dy <= dx) {
        p = &v[1];
    }
    if (*p <= dz && dz != *p) {
        p = &v[3];
    }
    if (*(u32*)(*(u32*)(self + 0x16500) + 0x24) != *(u32*)(*(u32*)(self + 0x16500) + 0x28)) {
        SP_cHierGrid_Shutdown();
    }
    if (x0 <= x1) {
        f32 a = *p * 2.0f;
        f32 b = a * 9.999999f;
        f32 c = a * 0.01f;
        i32 ic = (i32)c;
        if ((f32)ic < c) {
            ic = ic + 1;
        }
        u32 uc = (u32)ic;
        i32 n1 = 0;
        while (uc != 0) {
            uc = uc >> 1;
            n1 = n1 + 1;
        }
        i32 ib = (i32)b;
        if ((f32)ib < b) {
            ib = ib + 1;
        }
        u32 ub = (u32)ib;
        i32 n2 = 0;
        while (ub != 0) {
            ub = ub >> 1;
            n2 = n2 + 1;
        }
        i32 a1 = n1 > 0 ? n1 : 0;
        i32 a2 = n2 < 7 ? n2 : 7;
        if (a2 < a1) {
            a2 = a1;
        }
        SP_cHierGrid_Init(*(void**)(self + 0x16500), &v[0], *p, a1, a2);
    }
}

// ===========================================================================
// 0x00b02350 - grid entry add/remove (member, 2 args, ret 8)
// ===========================================================================
struct GridEntryOps {
    void SetEntry(void* obj, u8 add);
};
// @ 0x00b02350
void GridEntryOps::SetEntry(void* obj, u8 add)
{
    u8* self = (u8*)this;
    u8* o = (u8*)obj;
    if (o == 0) {
        return;
    }
    u32 grid = *(u32*)(self + 0x16500);
    if (grid == 0) {
        return;
    }
    if (*(u32*)(grid + 0x24) == *(u32*)(grid + 0x28)) {
        GridRebuildProxy(self);
    }
    if (add == 0) {
        i32 idx = *(i32*)(o + 0x78);
        if (idx < 0) {
            return;
        }
        u32 g = *(u32*)(self + 0x16500);
        if (*(u32*)(g + 0x24) != *(u32*)(g + 0x28)) {
            SP_HierGridStub_Remove((void*)g, (u32)idx);
        }
        *(u32*)(o + 0x78) = 0xffffffff;
    } else {
        if (*(i32*)(o + 0x78) != -1) {
            return;
        }
        u32 g = *(u32*)(self + 0x16500);
        if (*(u32*)(g + 0x24) == *(u32*)(g + 0x28)) {
            return;
        }
        u32 r = SP_cHierGrid_CreateEntry((void*)g, o + 0x10, *(f32*)(o + 0x6c));
        *(u32*)(o + 0x78) = r;
    }
}

// ===========================================================================
// 0x00b023d0 - rbtree lookup + apply (member, 3 args, ret 0xc)
// ===========================================================================
struct TreeApplyOps {
    void Apply(void* key, u32 id, u32 arg);
};
// @ 0x00b023d0
void TreeApplyOps::Apply(void* key, u32 id, u32 arg)
{
    if (key == 0 || id == 0xffffffff) {
        return;
    }
    u8* self = (u8*)this;
    u32 out;
    RBF(self + 0x8080)->find(&id, &out);
    if ((void*)out == (void*)(self + 0x8084)) {
        return;
    }
    u8* node = (u8*)out;
    if (*(u32*)(node + 0x30) == 0) {
        return;
    }
    if (*(u32*)(node + 0x18) <= id) {
        return;
    }
    FUN_00a887b0(*(u32*)(node + 0x2c), arg);
}

// ===========================================================================
// 0x00b02430 - lower_bound over a pair-keyed tree (member, 2 args, ret 8)
// ===========================================================================
struct PairTreeOps {
    void Find(void* out, const u32* key);
};
// @ 0x00b02430
void PairTreeOps::Find(void* out, const u32* key)
{
    u8* self = (u8*)this;
    u8* first = (u8*)(self + 4);
    u8* node = *(u8**)(self + 0xc);
    if (node != 0) {
        u32 k0 = key[0], k1 = key[1];
        do {
            u32 nk1 = *(u32*)(node + 0x14);
            u32 nk0 = *(u32*)(node + 0x10);
            if (nk1 > k1 || (nk1 == k1 && nk0 >= k0)) {
                first = node;
                node = *(u8**)(node + 4);
            } else {
                node = *(u8**)node;
            }
        } while (node != 0);
    }
    u32 outv;
    FUN_00a057f0(&outv, key);
    *(u32*)out = outv;
    *(u8**)((u8*)out + 4) = first;
}

// ===========================================================================
// 0x00b02480 - wrapper (member, 2 args, ret 8)
// ===========================================================================
struct RefRecordCtorStruct {
    void* Construct2(void* src);  // 0x00b01cb0
};
struct WrapperOps {
    void* Wrap(u32* src, void* inner);
};
// @ 0x00b02480
void* WrapperOps::Wrap(u32* src, void* inner)
{
    u8* self = (u8*)this;
    *(u32*)self = *src;
    ((RefRecordCtorStruct*)(self + 8))->Construct2(inner);
    return self;
}

// ===========================================================================
// 0x00b024a0 - SP::GetDefaultValue<cSPTransform,90607414>
// ===========================================================================
// @ 0x00b024a0
void* GetDefaultValue_A(void)
{
    if ((*(volatile u32*)0x0167bb88 & 1) == 0) {
        *(volatile u32*)0x0167bb88 |= 1;
        *(f32*)0x0167bb54 = g_167af5c;
        *(f32*)0x0167bb58 = g_167af60;
        *(u16*)0x0167bb52 = 0;
        *(f32*)0x0167bb5c = g_167af64;
        *(u16*)0x0167bb50 = 0;
        *(f32*)0x0167bb60 = 1.0f;
        M3((void*)0x0167bb64)->Assign((const void*)0x0167b554);
    }
    return (void*)0x0167bb50;
}

// ===========================================================================
// 0x00b02520 - SP::SetDefaultValue<cSPTransform,90607414>
// ===========================================================================
// @ 0x00b02520
void FUN_00b02520(void* obj)
{
    void* t = (*(void*(*)(void*))(*(void**)((char*)obj + 0x20)))(obj);
    void* d = GetDefaultValue_A();
    ((CTransformAssignOps*)t)->Assign(d);
}

// ===========================================================================
// 0x00b02590 - SP::GetDefaultValue<cSPTransform,79537323>
// ===========================================================================
// @ 0x00b02590
void* GetDefaultValue_B(void)
{
    if ((*(volatile u32*)0x0167bbc4 & 1) == 0) {
        *(volatile u32*)0x0167bbc4 |= 1;
        *(f32*)0x0167bb90 = g_167af5c;
        *(f32*)0x0167bb94 = g_167af60;
        *(u16*)0x0167bb8e = 0;
        *(f32*)0x0167bb98 = g_167af64;
        *(u16*)0x0167bb8c = 0;
        *(f32*)0x0167bb9c = 1.0f;
        M3((void*)0x0167bba0)->Assign((const void*)0x0167b554);
    }
    return (void*)0x0167bb8c;
}

// ===========================================================================
// 0x00b02610 - SP::SetDefaultValue<cSPTransform,79537323>
// ===========================================================================
// @ 0x00b02610
void FUN_00b02610(void* obj)
{
    void* t = (*(void*(*)(void*))(*(void**)((char*)obj + 0x20)))(obj);
    void* d = GetDefaultValue_B();
    ((CTransformAssignOps*)t)->Assign(d);
}

// ===========================================================================
// 0x00b02630 - serialize a vector of 0x19a8-byte records
// ===========================================================================
// @ 0x00b02630
void FUN_00b02630(void* stream, u8* range)
{
    u8* s = (u8*)stream;
    u8* first = *(u8**)range;
    u8* last = *(u8**)(range + 4);
    void* sub = (*(void*(__thiscall**)(u8*))((char*)vtbl(s) + 0x20))(s);
    i32 count = (i32)((u32)(last - first) / 0x19a8);
    int tmp = count;
    void* wr = (*(void*(__thiscall**)(void*))((char*)vtbl(sub) + 0x18))(sub);
    EA_IO_WriteUint32(wr, &tmp, 1, 0);
    u8* f = *(u8**)range;
    u8* l = *(u8**)(range + 4);
    if (f != l) {
        do {
            void* sub2 = (*(void*(__thiscall**)(u8*))((char*)vtbl(s) + 0x20))(s);
            tmp = *(i32*)f;
            void* wr2 = (*(void*(__thiscall**)(void*))((char*)vtbl(sub2) + 0x18))(sub2);
            EA_IO_WriteUint32(wr2, &tmp, 1, 0);
            (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
            u8 ser[0x2c];
            SP_cVarListSerializer_ctor(ser, f + 8, (const void*)0x01567428, (const void*)0x01a80d26);
            SP_cVarListSerializer_Serialize(ser, s);
            (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
            f += 0x19a8;
        } while (f != l);
    }
    (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
}

// ===========================================================================
// 0x00b02750 - binary lower_bound by 0x19a8-byte records
// ===========================================================================
// @ 0x00b02750
u8* FUN_00b02750(u8* first, u8* last, const u32* key)
{
    i32 n = (i32)(last - first) / 0x19a8;
    i32 half = 0;
    if (n > 0) {
        do {
            half = n >> 1;
            u8* mid = first + half * 0x19a8;
            if (*(u32*)mid < *key) {
                first = mid + 0x19a8;
                half = n + (-1 - half);
            }
            n = half;
        } while (half > 0);
    }
    return first;
}
