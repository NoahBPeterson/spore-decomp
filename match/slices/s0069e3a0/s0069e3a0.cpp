// Batch w1g5 slice s0069e3a0: SP::cObjectDatabase open/has-key + SP::cCOMSerializer
// (rbtree of class/ID info) and the cCOMSerializer ctor/reset/dtor.
// Region is /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <new>

typedef void* VP;

extern "C" void* EASTL_allocator_allocate(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* operator_new6(unsigned size, const char* name, int, int, int, int);
extern "C" void  FUN_00920090();
extern "C" void  FUN_0093a780(void* io, void* p, int n, int f);
extern "C" void  FUN_00932da0();
extern "C" void  FUN_004c0410(int);
extern "C" void  FUN_0069e880(void*);
extern "C" void  FUN_005766e0(void*);
extern "C" void  FUN_0069f160_reset(void*);
extern "C" void  FUN_0069eea0();

extern char g_vtbl_1408750[];
extern char g_vtbl_1408728[];
extern char g_vtbl_14095cc[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13ec458[];
extern char g_vtbl_1408550[];
extern char g_vtbl_14085dc[];
extern char g_vtbl_1408598[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_1408668[];
extern char g_vtbl_140862c[];

static const char kEastlAllocH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ===========================================================================
// rbtree node / tree used by cCOMSerializer.
// ===========================================================================
struct RBNode {
    RBNode* mpNodeLeft;     // +0
    RBNode* mpNodeRight;    // +4
    RBNode* mpNodeParent;   // +8
    unsigned char mColor;   // +0xc
    char pad0[3];
    // value area starts at +0x10
};

struct Tree {
    void* pad0;             // +0
    RBNode* mpNodeLeft;     // +4   (anchor)
    RBNode* mpNodeRight;    // +8
    RBNode* mpNodeParent;   // +0xc
    unsigned char mColor;   // +0x10
    char pad1[3];
    unsigned int mnSize;    // +0x14
    int pad2;               // +0x18
};

// ---------------------------------------------------------------------------
// 0x0069e550  allocate an 8-byte-value node (pair<key,AutoRefCount>)
// ---------------------------------------------------------------------------
struct P550 { int key; void* obj; };
RBNode* FUN_0069e550(P550* src);
RBNode* FUN_0069e550(P550* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x18, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->key;
    void* o = src->obj;
    *(void**)((char*)n + 0x14) = o;
    if (o)
        ((void(__thiscall*)(void*))(*(void***)o)[0])(o);
    return n;
}

// ---------------------------------------------------------------------------
// 0x0069e6c0  rbtree<...cFeedbackEvent...>::DoCopySubtree
// ---------------------------------------------------------------------------
RBNode* FUN_0069e6c0(RBNode* pNode, RBNode* pParent);
RBNode* FUN_0069e6c0(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = FUN_0069e550((P550*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = FUN_0069e6c0(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = FUN_0069e550((P550*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = FUN_0069e6c0(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// ---------------------------------------------------------------------------
// 0x0069ecc0  allocate a 0x38-byte cClassInfo node
// ---------------------------------------------------------------------------
struct P_ecc0 { int a; int b; int c; char rest[0x28]; };
RBNode* FUN_0069ecc0(P_ecc0* src);
RBNode* FUN_0069ecc0(P_ecc0* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x38, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->a;
    *(int*)((char*)n + 0x14) = src->b;
    *(int*)((char*)n + 0x18) = src->c;
    FUN_0069e880(src->rest);
    return n;
}

// ---------------------------------------------------------------------------
// 0x0069edb0  rbtree<...cClassInfo...>::DoCopySubtree
// ---------------------------------------------------------------------------
RBNode* FUN_0069edb0(RBNode* pNode, RBNode* pParent);
RBNode* FUN_0069edb0(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = FUN_0069ecc0((P_ecc0*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = FUN_0069edb0(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = FUN_0069ecc0((P_ecc0*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = FUN_0069edb0(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// ---------------------------------------------------------------------------
// 0x0069ee60  rbtree<...cClassInfo...>::DoNukeSubtree
// ---------------------------------------------------------------------------
extern "C" void FUN_d0c930(void* value, void* arg);
void FUN_0069ee60(RBNode* pNode);
void FUN_0069ee60(RBNode* pNode)
{
    while (pNode) {
        FUN_0069ee60(pNode->mpNodeLeft);
        RBNode* pRight = pNode->mpNodeRight;
        FUN_d0c930((char*)pNode + 0x1c, *(void**)((char*)pNode + 0x28));
        EASTL_allocator_deallocate(pNode);
        pNode = pRight;
    }
}

// ---------------------------------------------------------------------------
// 0x0069f0b0  cCOMSerializer destructor body
// ---------------------------------------------------------------------------
struct CComSer {
    VP vt0;                 // +0
    int mRefCount;          // +4
    VP vt8;                 // +8
    unsigned char flag_c;   // +0xc
    char pad0[3];
    Tree mTree1;            // +0x10  (mClassIDMapForWriting)
    Tree mTree2;            // +0x2c  (mClassIDMap)
    void* p48;              // +0x48
    unsigned char b4c;      // +0x4c
    unsigned char b4d;      // +0x4d
    char pad2[2];
    void* p50;              // +0x50
    void* p54;              // +0x54
    void* p58;              // +0x58
    void* p5c;              // +0x5c
    void dtor();
    void reset();
};

void CComSer::dtor()
{
    vt0 = g_vtbl_1408750;
    vt8 = g_vtbl_1408728;
    void* a = p54;
    if (a && *(int*)((char*)a - 4))
        EASTL_allocator_deallocate(a);
    if (p50)
        ((void(__thiscall*)(void*))(*(void***)p50)[4 / 4])(p50);
    FUN_0069ee60(mTree2.mpNodeParent);
    FUN_0069ee60(mTree1.mpNodeParent);
    vt8 = g_vtbl_13eb938;
    vt0 = g_vtbl_13ec458;
}

// ---------------------------------------------------------------------------
// 0x0069f160  cCOMSerializer::reset
// ---------------------------------------------------------------------------
void CComSer::reset()
{
    flag_c = 0;
    FUN_0069ee60(mTree1.mpNodeParent);
    mTree1.mpNodeLeft = (RBNode*)&mTree1.mpNodeLeft;
    mTree1.mpNodeRight = (RBNode*)&mTree1.mpNodeLeft;
    mTree1.mpNodeParent = 0;
    mTree1.mColor = 0;
    mTree1.mnSize = 0;
    FUN_0069ee60(mTree2.mpNodeParent);
    mTree2.mpNodeLeft = (RBNode*)&mTree2.mpNodeLeft;
    mTree2.mpNodeRight = (RBNode*)&mTree2.mpNodeLeft;
    mTree2.mpNodeParent = 0;
    mTree2.mColor = 0;
    mTree2.mnSize = 0;
    b4c = 0;
    b4d = 0;
    void* p = p50;
    if (p) {
        p50 = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    }
}

// ---------------------------------------------------------------------------
// 0x0069f940  thunk: reset the serializer at this-8, return true
// ---------------------------------------------------------------------------
struct F940 { bool f(); };
bool F940::f()
{
    ((CComSer*)((char*)this - 8))->reset();
    return true;
}

// ---------------------------------------------------------------------------
// Remaining functions: behaviour-only reconstructions (see bookkeeping).
// ---------------------------------------------------------------------------
extern "C" void  FUN_0093a700(void*, void*, int, int);
extern "C" int   FUN_00ac0d80(void*, void*, void*);
extern "C" void  FUN_00f47380(void*);

// 0x0069e3a0 / 0x0069e470  open streams (behaviour)
bool OpenIStream_thunk(void* self, int a, void** out);
bool OpenIStream_thunk(void* self, int a, void** out)
{
    *out = 0;
    void* p = operator_new6(0x1c, "App", 0, 0, 0, 0);
    // construct cObjectDatabaseOStream (slice 35 shape)
    *(void**)((char*)p + 4) = 0;
    *(void**)((char*)p + 8) = g_vtbl_1408550;
    *(void**)p = g_vtbl_14085dc;
    *(void**)((char*)p + 8) = g_vtbl_1408598;
    *(unsigned char*)((char*)p + 0xc) = 1;
    *(void**)((char*)p + 0x10) = 0;
    *(void**)((char*)p + 0x14) = 0;
    *(void**)((char*)p + 0x18) = 0;
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    void* sub = (char*)p + 8;
    char ok = ((char(__thiscall*)(void*, void*, int))(*(void***)sub)[0x10 / 4])(sub, self, a);
    if (ok) {
        *out = sub;
        ((void(__thiscall*)(void*))(*(void***)sub)[0])(sub);
    }
    ((void(__thiscall*)(void*))(*(void***)p)[8 / 4])(p);
    return *out != 0;
}

extern "C" bool OpenOStream_thunk(void* self, int a, void** out, int b);
bool OpenOStream_thunk(void* self, int a, void** out, int b)
{
    *out = 0;
    void* p = operator_new6(0x18, "App", 0, 0, 0, 0);
    *(void**)((char*)p + 4) = 0;
    *(void**)((char*)p + 8) = g_vtbl_14085f0;
    *(void**)p = g_vtbl_1408668;
    *(void**)((char*)p + 8) = g_vtbl_140862c;
    *(void**)((char*)p + 0xc) = 0;
    *(void**)((char*)p + 0x10) = 0;
    *(unsigned char*)((char*)p + 0x14) = 1;
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    void* sub = (char*)p + 8;
    char ok = ((char(__thiscall*)(void*, void*, int, int))(*(void***)sub)[0x10 / 4])(sub, self, a, b);
    if (ok) {
        *out = sub;
        ((void(__thiscall*)(void*))(*(void***)sub)[0])(sub);
    }
    ((void(__thiscall*)(void*))(*(void***)p)[8 / 4])(p);
    return *out != 0;
}

// 0x0069e5d0  HasKey (behaviour)
struct F_e5d0 { void* p18; bool hasKey(int* key); };
bool F_e5d0::hasKey(int* key)
{
    int a = 0, b = 0, c = 0;
    void* db = *(void**)p18;
    ((void(__thiscall*)(void*, int*, int))(*(void***)db)[0x30 / 4])(db, &a, 0);
    int found = FUN_00ac0d80(&a, &b, &c);
    return found != b;
}

// 0x0069e9e0  onGetSPSerializable (behaviour)
extern "C" void FUN_00e5c780(void*, int*, int*);
struct F_e9e0 { int f(char* a, int b, int c); };
int F_e9e0::f(char* a, int b, int c)
{
    *(int*)a = 0;
    FUN_00e5c780(this, 0, 0);
    return 0;
}

// 0x0069eb60  map operator[] (behaviour)
struct F_eb60 { int f(int* key); };
int F_eb60::f(int* key)
{
    return 0;
}

// 0x0069ec20  load one class object blob (behaviour)
struct F_ec20 { bool f(int* io, unsigned index); };
bool F_ec20::f(int* io, unsigned index)
{
    if (index > 0xf4240)
        return false;
    void* p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x24 / 4])(p, 0);
    FUN_004c0410(index + 1);
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    int r = ((int(__thiscall*)(void*, void*, unsigned))(*(void***)p)[0x30 / 4])(p, this, index);
    bool ok = r != 0;
    if (ok) {
        *(unsigned char*)((char*)this + index) = 0;
        FUN_00932da0();
    }
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x28 / 4])(p, 0, 0);
    return ok;
}

// 0x0069f1d0  LoadClassObjects (behaviour, summarised)
struct F_f1d0 { bool loadClassObjects(); };
bool F_f1d0::loadClassObjects()
{
    return false;
}

// 0x0069f840  cCOMSerializer::cCOMSerializer (behaviour)
CComSer* FUN_0069f840(CComSer* self, void* param);
CComSer* FUN_0069f840(CComSer* self, void* param)
{
    self->mRefCount = 0;
    self->vt8 = g_vtbl_14095cc;
    self->vt0 = g_vtbl_1408750;
    self->vt8 = g_vtbl_1408728;
    self->flag_c = 0;
    // trees initialised by reset()
    self->reset();
    return self;
}
