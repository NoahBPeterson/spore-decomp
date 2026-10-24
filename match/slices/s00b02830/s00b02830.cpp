// Slice s00b02830 -- Simulator / SPGonzago heap-sift helpers + cFruitGroup/cTreeData
// object code.  Range 0x00b02830..0x00b03818.  Module: SPGonzago/SPPlanet.obj
// (work/migrate/modmap.json anchor: Simulator::cFruitGroup::cFruitGroup 0x00b02ca0).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (see manifest.txt)
#include "types.h"
#include <intrin.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef signed int     int32;
typedef unsigned __int64 uint64;

// ---------------------------------------------------------------- callee decls
extern "C" void* __cdecl memset(void*, int, unsigned);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
#pragma intrinsic(memset, memcpy)

// unnamed retail callees and globals (address in the comment)
// vtables: taken by address, so declared as arrays => the compiler emits an
// external relocation for the symbol instead of folding a constant.
extern char gVtblFruitView[];         // 0x0145c6d0
extern char gVtblFruitGroup[];        // 0x0145c71c
extern char gVtblFruitGroup2[];       // 0x0145c748
extern char gVtblFruitGroup3[];       // 0x0145c738
extern char gVtblTreeData[];          // 0x0145c678
extern char gVtblTreeData2[];         // 0x0145c668
extern char gVtblContentValidationSummarizer[];  // 0x013ec458
extern char gVtblRegNodeSdtor[];                 // 0x0145c6c0

// helpers 0x0148xxxx matrix constant, 0x0167b554 identity matrix
extern float g_HK_REAL_ONE;       // 0x01485720
extern char  g_matrixIdentity[];  // 0x0167b554
extern float g_zero3a[];          // 0x0167af5c, 0x0167af60, 0x0167af64

// 0x00b014f0 sift-down continuation (EASTL __adjust_heap inner)
void __cdecl FUN_00b014f0(void* first, void* last, int holeIndex, void* top, float* pos);
void __cdecl FUN_00b015c0(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);
void __cdecl FUN_00b01690(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);

// 0x006271a0 translateTransform
void* __cdecl FUN_006271a0(void* out, void* a, void* b);
// 0x0059c190 Matrix3FromQuaternion
void* __cdecl FUN_0059c190(void* out, void* q);

// ---- thiscall callees: declared as methods of a throwaway stub, called as obj->M(...)
struct Op {
    void* M18660();                    // 0x00b18660 SP::cGameData::cGameData
    void  M03d0();                     // 0x00ac03d0 SP::cInteractionTarget::cInteractionTarget
    void  M8550(int v);               // 0x00b18550 cGameData SetGameDataOwner2
    void* M2a690(uint32 a, uint32 b, uint32 c);  // 0x00b2a690
    void* M90410();                    // 0x00b90410
    void* M2830();                     // 0x00ad2830
    void* M1cb40(const void* src);     // 0x0041cb40 Matrix3::Assign
    void  M0ccb0(void* o);            // 0x0040ccb0 ComposeTransforms
    void  M44040();                    // 0x00434040 XformMsg::XformMsg
    void* M01090();                    // 0x00401090 GetSetting9 (ignores args)
    void* Mdf440(const void* key);     // 0x004df440 GetPlantProfile
    int   Md9070();                    // 0x004d9070
    void* Md9010(void* a);            // 0x004d9010
    void* Mc3e790();                   // 0x00c3e790
    void  M5c780(void* out, void* key); // 0x00e5c780 eastl::rbtree find (out, key)
    void  Me92660();                   // 0x00e92660 ~cSpatialObjectView
    void  M92850();                    // 0x00692850
    void* M537dc0(const void* src);    // 0x00537dc0 cSPTransformOps::Assign
};

// 0x00b3d420 / 0x00b3d440 / 0x00b3d3b0: global getters (cdecl)
void* __cdecl FUN_00b3d420(void* self);
void* __cdecl FUN_00b3d440(void);
void* __cdecl FUN_00b3d3b0();          // returns the global singleton at 0x0167eb10
// 0x00401090 GetSetting9: cdecl, ignores its arguments and returns a global
void* __cdecl FUN_00401090();

// 0x00b02430 rbtree lower_bound-ish lookup (thiscall: ecx=container)
struct RbtLookup { void* Find(void* out, void* key); };
// 0x00b001b0
void __cdecl FUN_00b001b0(void* self);
// 0x00a887b0
void __cdecl FUN_00a887b0(uint32 a, float f);
// 0x0067ddd0 EffectsManagerPtr
void* __cdecl FUN_0067ddd0();
// 0x00921580 eastl::RBTreeIncrement
void* __cdecl FUN_00921580(void* node);
// 0x00f47380 operator delete
void __cdecl FUN_00f47380(void* p);
// 0x011e07ef lib_crt::atexit
void __cdecl FUN_011e07ef(void (*fn)());
// 0x011e08d0 lib_crt::aullshr
uint32 __cdecl FUN_011e08d0(uint32 hi, uint32 lo, int sh);
// 0x011e06e0 lib_crt::allshl
void  __cdecl FUN_011e06e0(uint32* out, int sh);   // returns edx:eax
// 0x0093aa70 EA::IO::WriteUint32
char __cdecl FUN_0093aa70(void* stream, const void* p, int n, int e);
// 0x0093ab10 WriteUint64
char __cdecl FUN_0093ab10(void* stream, const void* p, int n, int e);

// global for 0x0167bbdc / 0x0167bbc8
extern uint32 g_regNodeGuard;   // 0x0167bbdc
extern float g_seqMulConst;     // 0x01485548

// virtual call helper (double-indirected vtable fetch as emitted by the original)
typedef void (__cdecl* VtFn)(void*, uint8);
inline void VtCall(void* obj, int slot, uint8 arg)
{
    uint8* a = *(uint8**)obj;            // obj->vtbl
    uint8* b = *(uint8**)a;              // vtbl->[0]
    VtFn fn = *(VtFn*)(b + slot);
    fn(obj, arg);
}

// ---------------------------------------------------------------- element node
// The heap elements are pointers to objects carrying a position at +0x5c (big
// objects) or +0x10 (small objects).  A node only ever has its position read.
struct HeapNodeBig {
    uint32 pad00[0x5c / 4];
    float  x;           // +0x5c
    float  y;           // +0x60
    float  z;           // +0x64
};

struct HeapNodeSmall {
    uint32 pad00[0x10 / 4];
    float  x;           // +0x10
    float  y;           // +0x14
    float  z;           // +0x18
};

struct HeapNodePlain {
    float  x;           // +0x00
    float  y;           // +0x04
    float  z;           // +0x08
};

// ================================================================= 00b02830
// __adjust_heap variant over a fixed float[3] key, big-node position at +0x5c.
// @ 0x00b02830
void __cdecl FUN_00b02830(void** first, void* last, int n, int holeIndex, void* top,
                          float* pos)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    {
        float py = pos[1];
        float pz = pos[2];
        float px = pos[0];
        for (;;) {
            HeapNodeBig* left  = (HeapNodeBig*)first[child];
            HeapNodeBig* right = (HeapNodeBig*)first[child - 1];
            float dly = py - left->y;
            float dlx = px - left->x;
            float dlz = pz - left->z;
            float drx = px - right->x;
            float dry = py - right->y;
            float drz = pz - right->z;
            float dl = dlz * dlz + dlx * dlx + dly * dly;
            float dr = drz * drz + dry * dry + drx * drx;
            if (dl < dr)
                --child;
            first[holeIndex] = first[child];
            holeIndex = child;
            child = child * 2 + 2;
            if (child >= n)
                break;
        }
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b014f0(first, last, holeIndex, top, pos);
}

// ================================================================= 00b02930
// @ 0x00b02930
void __cdecl FUN_00b02930(void** first, void* last, int n, int holeIndex, void* top,
                          float px, float py, float pz)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    for (;;) {
        HeapNodeSmall* left  = (HeapNodeSmall*)first[child];
        HeapNodeSmall* right = (HeapNodeSmall*)first[child - 1];
        float dly = py - left->y;
        float dlx = px - left->x;
        float dlz = pz - left->z;
        float drx = px - right->x;
        float dry = py - right->y;
        float drz = pz - right->z;
        float dl = dlz * dlz + dlx * dlx + dly * dly;
        float dr = drz * drz + dry * dry + drx * drx;
        if (dl < dr)
            --child;
        first[holeIndex] = first[child];
        holeIndex = child;
        child = child * 2 + 2;
        if (child >= n)
            break;
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b015c0(first, last, holeIndex, top, px, py, pz);
}

// ================================================================= 00b02a40
// @ 0x00b02a40
void __cdecl FUN_00b02a40(void** first, void* last, int n, int holeIndex, void* top,
                          float px, float py, float pz)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    for (;;) {
        HeapNodePlain* left  = (HeapNodePlain*)first[child];
        HeapNodePlain* right = (HeapNodePlain*)first[child - 1];
        float dlz = pz - left->z;
        float dlx = px - left->x;
        float drx = px - right->x;
        float dly = py - left->y;
        float dry = py - right->y;
        float drz = pz - right->z;
        float dl = dlz * dlz;
        dl += dlx * dlx;
        dl += dly * dly;
        float dr = drz * drz;
        dr += dry * dry;
        dr += drx * drx;
        if (dl < dr)
            --child;
        first[holeIndex] = first[child];
        holeIndex = child;
        child = child * 2 + 2;
        if (child >= n)
            break;
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b01690(first, last, holeIndex, top, px, py, pz);
}

// ================================================================= 00b02b90
// cFruitGroup::GetFruitPosition-like; this +0x5c = attached UI object pointer chain.
// Local snapshot laid out like the source sub-object: 2 u16 header words, 3 floats,
// a 4th float, then a 0x24-byte transform matrix at +0x18.
struct TmpXform {
    uint16 a;             // +0x00
    uint16 b;             // +0x02
    float  x;             // +0x04
    float  y;             // +0x08
    float  z;             // +0x0c
    uint32 pad10;         // +0x10
    float  w;             // +0x14
    float  m00, m01, m02; // +0x18 transform matrix (9 floats, 0x24 bytes)
    float  m10, m11, m12;
    float  m20, m21, m22;
};

struct cFruitGroupSlots {
    uint32 pad00[0xc / 4];
    uint16 mW0;         // +0x0c
    uint16 mW1;         // +0x0e
    float  f10;         // +0x10
    float  f14;         // +0x14
    float  f18;         // +0x18
    float  f1c;         // +0x1c
    uint8  mTransform[0x38];  // +0x20
    uint32 pad58;
    uint32 p5c;
    void GetFruitPos(float* out, int idx);
};

// Model-world object (FUN_00ad2830 result): its per-piece transform array hangs
// off +0x6b8.
struct cModelWorld {
    uint32 pad00[0x6b8 / 4];   // +0x0000
    void*  mpPieces;           // +0x6b8  array, stride 0x38
};

// @ 0x00b02b90
void cFruitGroupSlots::GetFruitPos(float* out, int idx)
{
    void* r1 = FUN_00b3d420(&this->p5c);
    void* r2 = ((Op*)r1)->M90410();        // GetSpeciesFromID
    cModelWorld* mw = (cModelWorld*)((Op*)r2)->M2830();  // GetModelWorld
    TmpXform tmp;                          // local transform snapshot
    float x = f10;
    float y = f14;
    float z = f18;
    tmp.a = mW0;
    tmp.b = mW1;
    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    tmp.w = f1c;
    ((Op*)&tmp.m00)->M1cb40(this->mTransform);
    void* dst = (void*)((char*)mw->mpPieces + idx * 0x38);
    ((Op*)&tmp)->M0ccb0(dst);
    out[0] = tmp.x; out[1] = tmp.y; out[2] = tmp.z;
}

// ================================================================= 00b02c40
// Effect object header: +0x00 some ptr, +0x04 word with a low flag bit and a
// high "1" bit at position 31, +0x40 refcount.
struct ScopedDtorEffect {
    uint32 pad00;         // +0x00
    uint32 flags;         // +0x04 (bit 31 = "detach without release")
    uint32 pad08[0x38 / 4];  // +0x08 .. +0x3f
    int    refcount;      // +0x40
};

struct cFruitView {
    void*  vtbl;         // +0x00
    uint32 pad[0x30 / 4];
    ScopedDtorEffect* mpEffect;  // +0x34
    cFruitView* ScopedDtor(uint8 del);
};

// @ 0x00b02c40
cFruitView* cFruitView::ScopedDtor(uint8 del)
{
    cFruitView* s = this;
    s->vtbl = gVtblFruitView;
    _ReadWriteBarrier();
    ScopedDtorEffect* eff = s->mpEffect;
    if (eff != 0) {
        if (eff->refcount > 1) {
            eff->refcount = eff->refcount - 1;
        } else {
            uint8 flag = (uint8)((eff->flags >> 31) & 1);
            VtCall(eff, 0x170, flag);
        }
    }
    ((Op*)this)->Me92660();
    if (del & 1)
        FUN_00f47380(this);
    return this;
}
// ================================================================= 00b02ca0
// Simulator::cFruitGroup: retail layout.  Three vtables: its own at +0x00, a
// secondary at +0x04, and the embedded cInteractionTarget subobject at +0x34.
struct cFruitGroup {
    void*  vtbl00;           // +0x00  gVtblFruitGroup2
    void*  vtbl04;           // +0x04  gVtblFruitGroup3
    uint32 pad08[0x2c / 4];  // +0x08 .. +0x33
    void*  targetVtbl;       // +0x34  embedded cInteractionTarget vtable
    uint32 pad38[0x10 / 4];  // +0x38 .. +0x47
    uint32 m48;              // +0x48  low half of the 64-bit used-slot mask
    int    m4c;              // +0x4c  high half / -1 sentinel
    uint32 m50;              // +0x50  species key (init 0x3a8be428)
    int    m54;              // +0x54
    uint32 m58;              // +0x58  (low half m58, high half m5a)
    float  f5c;              // +0x5c  position x
    float  f60;              // +0x60  position y
    float  f64;              // +0x64  position z
    float  f68;              // +0x68  scale
    float  mRot[9];          // +0x6c  orientation matrix
    uint32 m90;              // +0x90  state flags
    uint32 m94;              // +0x94
    uint32 m98;              // +0x98
    uint32 m9c;              // +0x9c
    uint32 ma0;              // +0xa0
    void*  ma4;              // +0xa4  element cursor array base
    void*  ma8;              // +0xa8
    void*  mac;              // +0xac
    uint32 padb0[8 / 4];     // +0xb0 .. +0xb7
    uint32 mb8;              // +0xb8
    void*  mbc;              // +0xbc
    uint32 padc0[0xdc / 4];  // +0xc0 .. +0x19b
    void*  m19c;             // +0x19c  per-slot key array
    void*  m1a0;             // +0x1a0
    void*  m1a4;             // +0x1a4
    uint32 pad1a8[8 / 4];    // +0x1a8 .. +0x1af
    uint32 m1b0;             // +0x1b0
    void*  m1b4;             // +0x1b4
    uint32 pad1b8[0xc / 4];  // +0x1b8 .. +0x1c3
    uint32 m1c4;             // +0x1c4
    void*  m1c8;             // +0x1c8  tree pointer
    int    m1cc;             // +0x1cc  mode (1/2)
    void*  m1d0;             // +0x1d0  attached object handle
    void FillSlots(cFruitGroup* group);   // 0x00b033b0 (thiscall: ecx=this)
};

// @ 0x00b02ca0
void* __fastcall cFruitGroup_Ctor(cFruitGroup* self)
{
    ((Op*)self)->M18660();
    ((Op*)&self->targetVtbl)->M03d0();
    self->targetVtbl = gVtblFruitGroup;
    self->vtbl00 = gVtblFruitGroup2;
    self->vtbl04 = gVtblFruitGroup3;
    self->m4c = -1;
    self->m50 = 0x3a8be428;
    self->m54 = 0;
    self->m58 = 0;
    self->f5c = g_zero3a[0];
    self->f60 = g_zero3a[1];
    self->f64 = g_zero3a[2];
    self->f68 = g_HK_REAL_ONE;
    ((Op*)self->mRot)->M1cb40(g_matrixIdentity);
    self->m90 = 0;
    self->m94 = 0;
    self->m98 = 0;
    self->m9c = 0;
    self->ma0 = 0;
    char* p = (char*)&self->mbc;
    self->ma4 = p;
    self->ma8 = p;
    self->mb8 = 0;
    p += 0xe0;
    self->mac = p;
    p = (char*)&self->m1b4;
    self->m19c = p;
    self->m1a0 = p;
    self->m1b0 = 0;
    p += 0x10;
    self->m1a4 = p;
    self->m1c4 = 0;
    self->m1c8 = 0;
    self->m1cc = 0;
    self->m1d0 = 0;
    return self;
}

// ================================================================= 00b02dd0
// Resource-key immediates passed to the +0x2c vcall (EA resource ids).
extern uint32 g_kResA0;    // 0x015673c0
extern uint32 g_kResA1;    // 0x015673c4
extern uint32 g_kResB0;    // 0x015673c8
extern uint32 g_kResB1;    // 0x015673cc

// @ 0x00b02dd0
void __fastcall cFruitGroup_SetGameDataOwner(cFruitGroup* self)
{
    ((Op*)self)->M8550(0);
    self->m4c = -1;
    self->m54 = 0;
    memcpy(self->mRot, g_matrixIdentity, 0x24);
    self->f68 = g_HK_REAL_ONE;
    self->f5c = g_zero3a[0];
    self->f60 = g_zero3a[1];
    self->f64 = g_zero3a[2];
    self->m58 = 0;
    self->m90 = 0;
    self->m50 = 0x3a8be428;
    if (self->m1cc != 0) {
        void* p = self->m1d0;
        self->m1cc = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*, int))*(void**)(*(int*)p + 0xc))(p, 1);
            p = self->m1d0;
            if (p != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)p + 4))(p);
            }
        }
        int mode = self->m1cc;
        if (mode == 1) {
            void* em = FUN_0067ddd0();
            void* q = self->m1d0;
            if (q != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)q + 4))(q);
            }
            ((void(__thiscall*)(void*, uint32, uint32, void*))*(void**)(*(int*)em + 0x2c))
                (em, g_kResA0, g_kResA1, &self->m1d0);
        } else if (mode == 2) {
            void* em = FUN_0067ddd0();
            void* q = self->m1d0;
            if (q != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)q + 4))(q);
            }
            ((void(__thiscall*)(void*, uint32, uint32, void*))*(void**)(*(int*)em + 0x2c))
                (em, g_kResB0, g_kResB1, &self->m1d0);
        }
    }
    if (self->m1d0 != 0) {
        void* p = self->m1d0;
        self->m1d0 = 0;
        ((void(__thiscall*)(void*))*(void**)(*(int*)p + 4))(p);
    }
}

// ================================================================= 00b02fa0
// cFruitGroup::UpdateFruitForCreatureTree: walks the fruit pieces, builds the
// per-piece cSPTransform and pushes it into the fruit tree / shape map.
//
// SP::cSPTransform: translation + scale + 3x3 rotation.
struct cSPTransform {
    uint16 flags;         // +0x00
    uint16 modCount;      // +0x02
    float  tx, ty, tz;    // +0x04
    float  scale;         // +0x10
    float  rot[9];        // +0x14
};

// Object returned by the singleton getter FUN_00b3d3b0 (0x0167eb10); its +0x10
// slot points at the creature that owns this fruit group.
struct cModelHolder {
    uint32 pad00[0x10 / 4];
    void*  mpChild;       // +0x10
};

// Species profile (GetPlantProfile result), owner of the per-slot transforms.
struct cSpeciesProfile {
    uint32 pad00[0x6b8 / 4];       // +0x0000
    cSPTransform* mpTransforms;    // +0x6b8  array, stride 0x38
};

// Creature / creature-model / piece layout.
struct cPieceElem {
    uint32 pad00[0x10 / 4];    // +0x00
    float  x, y, z;            // +0x10
    float  quat[4];            // +0x1c
    uint8  rest[0x2bc - 0x2c]; // +0x2c ... element stride is 0x2bc
};
struct cCreatureModel {
    uint32 pad00[0x70 / 4];    // +0x00
    float  scale;              // +0x70
    uint32 pad74[0x270 / 4];   // +0x74 .. +0x2e3
    cPieceElem* mpElemBegin;   // +0x2e4
    cPieceElem* mpElemEnd;     // +0x2e8
};
struct cCreature {
    uint32 pad00[0x17c / 4];   // +0x00
    cCreatureModel* mpModel;   // +0x17c
};

// Slot record inside a fruit-tree node (stride 0x4c, cSPTransform first).
struct cTreeSlot {
    cSPTransform xform;        // +0x00
    uint32 extra[5];           // +0x38
};
// Fruit-tree node (eastl::rbtree keyed on the slot key).
struct cFruitTreeNode {
    uint32 pad00[0x18 / 4];    // +0x00
    uint32 key;                // +0x18
    uint32 pad1c[0x14 / 4];    // +0x1c .. +0x2f
    cTreeSlot* mpSlots;        // +0x30
};
// Fruit-tree root wrapper returned by FUN_00b3d440: the rbtree lives at +0x8080.
struct cFruitTreeRoot {
    uint32 pad00[0x8080 / 4];  // +0x0000
    uint32 mHeader;            // +0x8080  find entry (this)
    uint32 mEndNode;           // +0x8084  end sentinel
};

// @ 0x00b02fa0
void __fastcall FUN_00b02fa0(cFruitGroup* self)
{
    void* mgr = (void*)FUN_00b3d3b0();       // 0x0167eb10 singleton
    cModelHolder* ch = (cModelHolder*)((Op*)mgr)->M2a690(self->m50, self->m4c, self->m54);
    int owner = (ch != 0) ? (int)ch->mpChild : 0;
    if (owner == 0) {
        if ((self->m90 & 1) == 0)
            return;
        self->m90 &= 0xfffffffe;
    } else {
        self->m90 |= 1;
    }
    cSpeciesProfile* prof = (cSpeciesProfile*)((Op*)FUN_00401090())->Mdf440(&self->m94);
    if (prof == 0)
        return;
    if ((int)((Op*)prof)->Md9070() == 0)
        return;
    uint32 n = (uint32)((Op*)prof)->Md9070();
    if (n == 0)
        return;
    uint32 idx = 0;
    uint32 off = 0;
    do {
        cSPTransform* dst = (cSPTransform*)((char*)self->ma4 + off);
        if (self->m1c8 != 0) {
            cSPTransform tf;
            tf.flags = 0;
            tf.modCount = 0;
            tf.tx = g_zero3a[0];
            tf.ty = g_zero3a[1];
            tf.tz = g_zero3a[2];
            tf.scale = g_HK_REAL_ONE;
            ((Op*)tf.rot)->M1cb40(g_matrixIdentity);
            if (owner == 0) {
                ((Op*)&tf)->M537dc0((char*)prof->mpTransforms + off);
                tf.flags |= 4;
                ++tf.modCount;
            } else {
                cCreature* crea = (cCreature*)((Op*)(uintptr_t)owner)->Mc3e790();
                if (crea != 0 && crea->mpModel != 0) {
                    cCreatureModel* model = crea->mpModel;
                    int* pp = (int*)((Op*)prof)->Md9010(crea);
                    uint32 ei = *(uint32*)(*pp + idx * 4);
                    if ((uint32)(((char*)model->mpElemEnd - (char*)model->mpElemBegin) / 700) <= ei)
                        ei = 0;
                    cPieceElem* elem = &model->mpElemBegin[ei];
                    float mat[9];
                    FUN_0059c190(mat, elem->quat);
                    float inv = g_HK_REAL_ONE / model->scale;
                    tf.tx = elem->x * inv;
                    tf.ty = elem->y * inv;
                    tf.tz = elem->z * inv;
                    for (int k = 0; k < 9; ++k)
                        tf.rot[k] = mat[k];
                    tf.flags |= 6;
                    tf.modCount += 2;
                }
            }
            if (tf.tx != g_zero3a[0] || tf.ty != g_zero3a[1] || tf.tz != g_zero3a[2]) {
                cFruitTreeRoot* tree = (cFruitTreeRoot*)FUN_00b3d440();
                uint32 found[2];
                ((Op*)&tree->mHeader)->M5c780(found, &self->m1c8);
                cFruitTreeNode* node = (cFruitTreeNode*)found[0];
                if ((char*)node != (char*)&tree->mEndNode && node->mpSlots != 0) {
                    uint32 k2 = *(uint32*)((char*)self->m19c + idx * 4);
                    if (k2 < node->key) {
                        char tmp[0x38];
                        FUN_006271a0(tmp, &tf, &self->m58);
                        ((Op*)&node->mpSlots[k2])->M537dc0(tmp);
                    }
                }
                ((Op*)dst)->M537dc0(&tf);
            }
        }
        ++idx;
        off += 0x38;
    } while (idx < n);
}

// ================================================================= 00b03320
// cFruitGroup child-tree lookup: lower_bound at this+0x34, then walk `c` nodes
// forward and return *(node+0x18).
struct cFruitGroupOps {
    uint32 pad00[0x34 / 4];
    RbtLookup mLookup;          // +0x34
    uint32 FindNth(uint32 a, uint32 b, uint32 c);
};

// @ 0x00b03320
uint32 cFruitGroupOps::FindNth(uint32 a, uint32 b, uint32 c)   // a=m58, b=m50, c=m54
{
    uint32 key[2];
    key[0] = b;          // +0: m50 (species key)
    key[1] = a;          // +4: m58
    uint32 out[2];
    mLookup.Find(out, key);
    uint32 it = out[0];
    uint32 end = out[1];
    uint32 n = 0;
    while (it != end) {
        it = (uint32)FUN_00921580((void*)it);
        ++n;
    }
    if (c < n) {
        for (uint32 k = 0; k < c; ++k)
            out[0] = (uint32)FUN_00921580((void*)out[0]);
        return ((cFruitTreeNode*)(uintptr_t)out[0])->key;
    }
    return 0;
}

// ================================================================= 00b033b0
// @ 0x00b033b0
void cFruitGroup::FillSlots(cFruitGroup* group)
{
    cFruitGroup* node = (cFruitGroup*)(uintptr_t)((cFruitGroupOps*)this)->FindNth(
        group->m58, group->m50, group->m54);
    if (node == 0)
        return;
    // popcount of the high dword of the 64-bit "used slot" mask at +0x48/+0x4c
    uint32 hi = FUN_011e08d0(group->m4c, group->m48, 0x20);
    uint32 v = hi - (hi >> 1 & 0x55555555);
    v = (v >> 2 & 0x33333333) + (v & 0x33333333);
    uint32 count = ((v >> 4) + v & 0x0f0f0f0f) * 0x01010101 >> 24;
    for (uint32 i = 0; i < count; ++i) {
        uint64 mask;
        FUN_011e06e0((uint32*)&mask, (int)i);  // mask = 1 << i
        uint32 ml = (uint32)mask;
        uint32 mh = (uint32)(mask >> 32);
        if ((ml & group->m48) != 0 || (mh & group->m4c) != 0)
            continue;
        group->m48 |= ml;
        group->m4c |= mh;
        uint32 key = (uint32)(uintptr_t)node->m1c8;                       // find key
        uint32 v6  = *(uint32*)((char*)node->m19c + i * 4);               // slot key
        cFruitTreeRoot* r = (cFruitTreeRoot*)FUN_00b3d440();
        if (key != 0 && v6 != 0xffffffff) {
            uint32 found[2];
            ((Op*)&r->mHeader)->M5c780(found, &key);
            cFruitTreeNode* fn = (cFruitTreeNode*)found[0];
            if ((char*)fn != (char*)&r->mEndNode && fn->mpSlots != 0 && v6 < fn->key)
                FUN_00a887b0(v6, g_HK_REAL_ONE);
        }
    }
}

// ================================================================= 00b034f0
// Counts the rbtree nodes at or after `{key0,key1}` in `owner`; true iff the run
// length equals `count`.
// @ 0x00b034f0
uint8 __stdcall FUN_00b034f0(uint32* out, uint32 key0, uint32 key1, uint32 count, void* owner)
{
    uint32 pair[2];
    ((RbtLookup*)owner)->Find(pair, &key0);
    uint32 it = pair[0];
    uint32 end = pair[1];
    out[0] = it;
    out[1] = end;
    uint32 n = 0;
    if (it != end) {
        do {
            it = (uint32)FUN_00921580((void*)it);
            ++n;
        } while (it != end);
        if (n != 0 && n == count)
            return 1;
    }
    return 0;
}

// ================================================================= 00b03550
void __cdecl FUN_013c1e60();
// thiscall member: entry does `add ecx,-4` (this is the +4 subobject of a static).
// The static cRegNode object lives at 0x0167bbc8.
struct RegNode {
    void* vtbl;              // +0x00
    void* M92f60(void* a);   // 0x00692f60 Construct
    char  Ma30c0();          // 0x00ab30c0
    void  M92850();          // 0x00692850
};
extern RegNode g_regNode;    // 0x0167bbc8

struct RegNodeThunk {
    void  M001b0();          // 0x00b001b0 (thiscall)
    void  M3550();           // 0x00b03550 (thiscall; ecx = &subobject at +4)
};
// @ 0x00b03550
void RegNodeThunk::M3550()
{
    ((RegNodeThunk*)((char*)this - 4))->M001b0();
    if ((g_regNodeGuard & 1) == 0) {
        g_regNodeGuard |= 1;
        g_regNode.M92f60(0);
        g_regNode.vtbl = gVtblRegNodeSdtor;
        FUN_011e07ef(FUN_013c1e60);
    }
    if (g_regNode.Ma30c0() == 0)
        g_regNode.M92850();
}

// ================================================================= 00b035b0
// Serializes a fruit-key rbtree: writes the first key, then per node the
// {key0,key1} pair and the referenced object.
struct cSaveNode {
    uint32 pad00[4];     // +0x00
    uint32 key0;         // +0x10
    uint32 key1;         // +0x14
    void*  mpObj;        // +0x18
};
struct cSaveTreeHdr {
    uint32 pad00;        // +0x00
    void*  mpEnd;        // +0x04  (sentinel node address = hdr + 4)
    void*  mpFirst;      // +0x08
    uint32 pad0c[2];     // +0x0c
    uint32 firstKey;     // +0x14
};
// @ 0x00b035b0
void __cdecl FUN_00b035b0(void* ar, cSaveTreeHdr* hdr)
{
    uint32 key = hdr->firstKey;
    void* r = ((void*(__thiscall*)(void*))*(void**)(*(int*)ar + 0x20))(ar);
    void* st = ((void*(__thiscall*)(void*))*(void**)(*(int*)r + 0x18))(r);
    FUN_0093aa70(st, &key, 1, 0);
    cSaveNode* it  = (cSaveNode*)hdr->mpFirst;
    cSaveNode* end = (cSaveNode*)((char*)hdr + 4);
    for (; it != end; it = (cSaveNode*)FUN_00921580(it)) {
        r = ((void*(__thiscall*)(void*))*(void**)(*(int*)ar + 0x20))(ar);
        uint32 v0 = it->key0;
        uint32 v1 = it->key1;
        st = ((void*(__thiscall*)(void*))*(void**)(*(int*)r + 0x18))(r);
        FUN_0093ab10(st, &v0, 1, 0);
        ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
        void* p = it->mpObj;
        uint32 res = 0;
        if (p != 0)
            res = (uint32)((void*(__thiscall*)(void*, uint32))*(void**)(*(int*)p + 0xc))(p, 0x179c807);
        ((void(__thiscall*)(void*, uint32))*(void**)(*(int*)ar + 0x2c))(ar, res);
        ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
    }
    ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
}

// ================================================================= 00b03680
// cTreeData copy ctor (retail: two vtables at +0/+4, embedded cSPTransform at +0x0c)
struct cTreeData {
    void*  vtbl0;              // +0x00
    void*  vtbl1;              // +0x04
    uint32 m08;                // +0x08
    uint16 m0c;                // +0x0c
    uint16 m0e;                // +0x0e
    float  tx;                 // +0x10
    float  ty;                 // +0x14
    float  tz;                 // +0x18
    float  scale;              // +0x1c
    float  rot[9];             // +0x20 (matrix; 0x24 bytes)
    uint32 m44_unused;         // +0x44 (not copied by the ctor / operator=)
    uint32 m48;                // +0x48
    uint32 m4c;                // +0x4c
    uint32 m50;                // +0x50
    uint32 m54;                // +0x54
    uint32 m58;                // +0x58
    uint32 m5c;                // +0x5c
    uint32 m60;                // +0x60
    uint32 m64;                // +0x64
    void*  mp68;               // +0x68  refcounted
    float  f6c;                // +0x6c
    float  f70;                // +0x70
    float  f74;                // +0x74
    uint32 m78;                // +0x78
    uint8  m7c;                // +0x7c
    cTreeData(void* src);
    cTreeData& operator=(cTreeData const& rhs);
};

// @ 0x00b03680
cTreeData::cTreeData(void* src)
{
    cTreeData* p = (cTreeData*)src;
    this->vtbl1 = gVtblContentValidationSummarizer;
    this->m08 = 0;
    _ReadWriteBarrier();               // base-subobject vtable store is kept by the retail build
    this->vtbl0 = gVtblTreeData;
    this->vtbl1 = gVtblTreeData2;
    this->m0c = p->m0c;
    this->m0e = p->m0e;
    this->tx = p->tx;
    this->ty = p->ty;
    this->tz = p->tz;
    this->scale = p->scale;
    ((Op*)this->rot)->M1cb40(p->rot);
    this->m48 = p->m48;
    this->m4c = p->m4c;
    this->m50 = p->m50;
    this->m54 = p->m54;
    this->m58 = p->m58;
    this->m5c = p->m5c;
    this->m60 = p->m60;
    this->m64 = p->m64;
    this->mp68 = p->mp68;
    if (this->mp68 != 0)
        ((void(__thiscall*)(void*))(*(void***)this->mp68)[0])(this->mp68);
    this->f6c = p->f6c;
    this->f70 = p->f70;
    this->f74 = p->f74;
    this->m78 = p->m78;
    this->m7c = p->m7c;
}

// ================================================================= 00b03740
// @ 0x00b03740
cTreeData& cTreeData::operator=(cTreeData const& rhs)
{
    ((Op*)(void*)&this->m0c)->M537dc0(&((cTreeData&)rhs).m0c);
    this->m48 = rhs.m48;
    this->m4c = rhs.m4c;
    this->m50 = rhs.m50;
    this->m54 = rhs.m54;
    this->m58 = rhs.m58;
    this->m5c = rhs.m5c;
    this->m60 = rhs.m60;
    this->m64 = rhs.m64;
    void* np = rhs.mp68;
    if (np != this->mp68) {
        void* op68 = this->mp68;
        if (np != 0)
            ((void(__thiscall*)(void*))(*(void***)np)[0])(np);
        this->mp68 = np;
        if (op68 != 0)
            ((void(__thiscall*)(void*))((*(void***)op68)[1]))(op68);
    }
    this->f6c = rhs.f6c;
    this->f70 = rhs.f70;
    this->f74 = rhs.f74;
    this->m78 = rhs.m78;
    this->m7c = rhs.m7c;
    return *this;
}

// ================================================================= 00b037e0
// @ 0x00b037e0
void* __cdecl FUN_00b037e0(void* out, uint32 begin, uint32 end, uint32 value)
{
    *(uint32*)out = value;
    for (; begin != end; begin += 0x80) {
        if (*(uint32*)out != 0)
            ((cTreeData*)*(uint32*)out)->cTreeData::cTreeData((void*)begin);
        *(uint32*)out += 0x80;
    }
    return out;
}
