// Slice s00683f80: App/cConversationFactory + SP cube-coordinate helpers (0x00683f80-0x00684ca0).
//
// Module compiled /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-. The factory owns four
// int-keyed EASTL rbtree maps (value Obj2A10 / ObjY) plus a guarded byte buffer;
// the remaining helpers serialize those maps through the abstract reader/writer
// interfaces (vtable slot 0x30 = Read, 0x38 = Write).
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }
inline void* operator new(uint32_t, void* p) { return p; }

// ---- abstract streams (vtable slots) ----
struct IRd {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void Read(void* p, int n);                  // slot 12 (0x30)
};
struct IWrt {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void vA(); virtual void vB();
    virtual void vC(); virtual void vD();
    virtual void Write(const void* p, int n);           // slot 14 (0x38)
};

// ---- out-of-slice callees ----
extern "C" void  EASTL_dealloc(void*);
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t);
extern "C" char  g_emptyStr[];                          // 0x1667bac (empty string sentinel)
extern "C" void  WriteUint32(void*, void*, int, int);   // 0x093aa70
extern "C" void  ReadInt32(void*, void*, int, int);     // 0x093a780
extern "C" void* RBTreeIncrement(void*);                // 0x0921580
extern "C" void* RBTreeDecrement(void*);                // 0x09215c0
extern "C" void  RBTreeInsert(void*, void*, void*, int); // 0x09216a0
// free functions still referenced by the out-of-slice serializers below
extern "C" void  FUN_006841a0(void*, void*);
extern "C" void  FUN_00682ca0(void*, void*);
extern "C" void  FUN_00680fc0(void*, void*);
extern "C" void  FUN_006823f0(void*, void*);
extern "C" void  FUN_00682e90(void*, void*);
extern "C" void  FUN_00683ab0(void*, void*);
extern "C" void  FUN_00684740(void*, void*);
extern "C" void  FUN_00684a90(void*, void*);
extern "C" void  read_6840d0(void*, int*);
extern char g_1402d55[];

// ===========================================================================
// stub value/container types (layouts read from the disassembly)
// ===========================================================================

// 12-byte byte string; the empty state points at the static sentinel
struct S8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    S8() { mpBegin = g_emptyStr; mpEnd = g_emptyStr; mpCap = g_emptyStr + 1; }
    void Resize(int n, int ch);                     // 0x047bf30 (thiscall, ret 8)
};

// 20-byte vector with an 8-byte allocator header
struct V20 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    V20() { mpBegin = 0; mpEnd = 0; mpCap = 0; mAlloc[0] = 0; mAlloc[1] = 0; }
};

// vector of 0x48-byte entries (M5a0), 20 bytes
struct M5a0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    M5a0() { mpBegin = 0; mpEnd = 0; mpCap = 0; mAlloc[0] = 0; mAlloc[1] = 0; }
};

// vector of Obj1800 (0xc4 stride), 12 bytes
struct VV12 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    VV12() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
};

// guarded EASTL byte buffer: begin/end/cap + allocator word
struct Buf {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    Buf() { mpBegin = g_emptyStr; mpEnd = g_emptyStr; mpCap = g_emptyStr + 1; mAlloc = 0; }
    ~Buf() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};

struct Obj1700 {
    S8 mStr;                                        // +0x00
    uint32_t padC;                                  // +0x0c
    V20 mF0;                                        // +0x10
    V20 mF1;                                        // +0x24
};

struct Obj2A10 {
    S8 mStr;                                        // +0x00
    uint32_t padC;                                  // +0x0c
    uint8_t b10, b11, b12, b13, b14;                // +0x10
    uint8_t pad15[3];                               // +0x15
    uint32_t w[4];                                  // +0x18
    M5a0 mM;                                        // +0x28
    VV12 mVec;                                      // +0x3c
    Obj2A10() { padC = 0; b10 = b11 = b12 = b13 = b14 = 0;
                w[0] = w[1] = w[2] = w[3] = 0; }
};

// int-keyed rbtree with an Obj1700 value (node 0x50)
struct NodeA { NodeA* mpRight; NodeA* mpLeft; NodeA* mpParent; uint32_t mColor; int mKey; Obj1700 mVal; };
struct MapA {
    void* pad0; NodeA* mpAnchor; NodeA* mpBegin; NodeA* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    Obj1700* Idx(const int& key);                   // 0x0683d10 (out-of-slice)
};

// int-keyed rbtree with an ObjY value (node 0x3c); ObjY == the {buffer,map} record
struct Map2 {
    void* pad0; void* mpAnchor; void* mpBegin; void* mpRoot; uint32_t mColor; uint32_t mnSize;
    Map2() { pad0 = 0; mpAnchor = &mpAnchor; mpBegin = &mpAnchor; mpRoot = 0; mColor = 0; mnSize = 0; }
    void FreeNodes(void* p);                        // 0x0681480 (out-of-slice)
    ~Map2() { FreeNodes(mpRoot); }
};
struct ObjY {
    Buf mVec;                                       // +0x00
    Map2 mMap;                                      // +0x10
    ObjY() {}
    ObjY(const ObjY& o);                            // 0x0683670 (out-of-slice)
};
struct NodeC { NodeC* mpRight; NodeC* mpLeft; NodeC* mpParent; uint32_t mColor; int mKey; ObjY mVal; };
struct MapC {
    void* pad0; NodeC* mpAnchor; NodeC* mpBegin; NodeC* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    NodeC* CreateNode(const void* pair);                        // 0x0684420
    void InsertPair(NodeC** out, NodeC* pos, const void* pair, char flag);   // 0x06844a0
    void InsertUnique(void* pairOut, const void* pair, char flag);           // 0x0684500
    void InsertHint(NodeC** out, NodeC* hint, const void* pair, char flag);  // 0x0684890
    ObjY* Idx(const int& key);                                  // 0x0684980
    void FreeChain(NodeC* p);                                   // 0x0683160 (out-of-slice)
    ~MapC() { FreeChain(mpRoot); }
};

// int-keyed rbtree with an Obj2A10 value (node 0x5c)
struct NodeB { NodeB* mpRight; NodeB* mpLeft; NodeB* mpParent; uint32_t mColor; int mKey; Obj2A10 mVal; };
struct MapB {
    void* pad0; NodeB* mpAnchor; NodeB* mpBegin; NodeB* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    NodeB* CreateNode(const void* pair);                        // 0x0683480
    void InsertPair(NodeB** out, NodeB* pos, const void* pair, char flag);   // 0x0683500
    void InsertUnique(void* pairOut, const void* pair, char flag);           // 0x0683560
    void InsertHint(NodeB** out, NodeB* hint, const void* pair, char flag);  // 0x0684330
    Obj2A10* Idx(const int& key);                               // 0x0684610
    void FreeNodes(NodeB* p);                                   // 0x0682800 (out-of-slice)
    ~MapB() { FreeNodes(mpRoot); }
};

// generic int-keyed map whose chain is freed by 0x0681500
struct MapC0 {
    void* pad0; void* mpAnchor; void* mpBegin; void* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    void FreeChain2(void* p);                       // 0x0681500 (out-of-slice)
    ~MapC0() { FreeChain2(mpRoot); }
};

// guarded byte buffer with an explicit erase step (destructor of the +0x6c member)
struct BufM {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    void Erase(void* begin, void* end);             // 0x0680b70 (thiscall, ret 8)
    ~BufM() {
        Erase(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_dealloc(mpBegin);
    }
};

// ===========================================================================
// the factory object (member layout from the destructor)
// ===========================================================================
struct GmeEditorResBase {
    void* vtbl;
    ~GmeEditorResBase() { vtbl = (void*)0x13eb938; }   // ??_7GmeEditorResBase@@6B@
};

struct Factory : GmeEditorResBase {
    char pad04[0x14];                               // +0x04 .. +0x18
    MapB m18;                                       // +0x18
    MapC0 m34;                                      // +0x34
    MapC m50;                                       // +0x50
    BufM m6c;                                       // +0x6c
    ~Factory();

    char Create(int* mgr, int** out, int a, int b);
    void ReadMapA(MapA* map, IRd* r);
    void WriteMapC(MapC* map, IWrt* w);
    void ReadMapB(MapB* map, IRd* r);

    // out-of-slice helpers
    void ReadVecU32(V20* v, IRd* r);                // 0x0681250
    void LoadEntries(M5a0* v, IRd* r);              // 0x06812c0
    void LoadObj1800(VV12* v, IRd* r);              // 0x0683700
    void WriteMap1700(Map2* map, IWrt* w);          // 0x0681f10
};

// ===========================================================================
// @ 0x00683F80  ~Factory (member teardown, base vptr store last)
// ===========================================================================
Factory::~Factory() {}

// ===========================================================================
// @ 0x00684040  factory Create (thiscall, ret 0x10)
// ===========================================================================
struct CPropList { void* ctor(); };                 // 0x0683e90

char Factory::Create(int* mgr, int** out, int a, int b)
{
    int* obj = (int*)EASTL_alloc6(0x80, (void*)"App/cConversationFactory", 0, 0, 0, 0);
    if (obj) obj = (int*)((CPropList*)obj)->ctor();
    int* v = (int*)((void* (__thiscall*)(void*))VT(mgr)[4])(mgr);
    obj[2] = v[0];
    obj[3] = v[1];
    obj[4] = v[2];
    if (((char (__thiscall*)(void*, int*, int*, int, int))VT(this)[9])(this, mgr, obj, a, b)) {
        *out = obj;
        ((void (__thiscall*)(void*))VT(obj)[0])(obj);
        return 1;
    }
    ((void (__thiscall*)(void*, int))VT(obj)[2])(obj, 1);
    return 0;
}

// ===========================================================================
// @ 0x006840D0  load map<int, Obj1700> (thiscall, ret 8)
// ===========================================================================
void Factory::ReadMapA(MapA* map, IRd* r)
{
    uint32_t count;
    r->Read(&count, 4);
    for (uint32_t i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        Obj1700* val = map->Idx(key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            val->mStr.Resize(len, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        ReadVecU32(&val->mF0, r);
        ReadVecU32(&val->mF1, r);
    }
}

// ===========================================================================
// @ 0x006841A0  store map<int, ObjY> (thiscall, ret 8, EH)
// ===========================================================================
void Factory::WriteMapC(MapC* map, IWrt* w)
{
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    NodeC* anchor = (NodeC*)&map->mpAnchor;
    for (NodeC* p = map->mpBegin; p != anchor; p = (NodeC*)RBTreeIncrement(p)) {
        int key = p->mKey;
        ObjY tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mVec.mpEnd - tmp.mVec.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mVec.mpBegin, len);
        WriteMap1700(&tmp.mMap, w);
    }
}

// ===========================================================================
// @ 0x006842C0  serialize app object (complete-ish)
// ===========================================================================
// stub receiver: the original gets the factory `this` in ECX; ret 0x10 = 4 stack args (last two unused)
struct FactSer {
    int __thiscall ser_6842c0(int* a, int* b, int c, int d);
};

int FactSer::ser_6842c0(int* a, int* b, int c, int d)
{
    (void)c; (void)d;
    int i = a ? ((int (__thiscall*)(void*, int))VT(a)[0xc / 4])(a, 0x355d6f5) : 0;
    void* u = ((void* (__thiscall*)(void*))VT(b)[0x18 / 4])(b);
    FUN_006841a0((void*)(i + 0x50), u);
    FUN_00682ca0((void*)(i + 0x18), u);
    FUN_00680fc0((void*)(i + 0x34), u);
    FUN_006823f0((void*)(i + 0x6c), u);
    return 1;
}

// ===========================================================================
// @ 0x00684330  MapB insert with hint (thiscall, ret 0x10)
// ===========================================================================
void MapB::InsertHint(NodeB** out, NodeB* hint, const void* pair, char flag)
{
    (void)flag;
    NodeB* anchor = (NodeB*)&mpAnchor;
    int* key = (int*)pair;
    if (hint == mpAnchor || hint == anchor) {
        if (mnSize == 0 || *key <= mpAnchor->mKey)
            goto UNIQUE;
        {
            int bIns = (mpAnchor == anchor || *key < mpAnchor->mKey) ? 0 : 1;
            NodeB* n = CreateNode(pair);
            RBTreeInsert(n, mpAnchor, anchor, bIns);
            ++mnSize;
            *out = n;
            return;
        }
    } else {
        NodeB* next = (NodeB*)RBTreeIncrement(hint);
        if (*key <= hint->mKey || next->mKey <= *key)
            goto UNIQUE;
        if (hint->mpRight == 0) {
            InsertPair(out, hint, pair, 0);
            return;
        }
        {
            NodeB* n = CreateNode(pair);
            RBTreeInsert(n, next, anchor, 0);
            ++mnSize;
            *out = n;
            return;
        }
    }
UNIQUE:
    {
        void* p[2];
        p[0] = 0;
        InsertUnique(p, pair, 0);
        *out = (NodeB*)p[0];
    }
}

// ===========================================================================
// @ 0x006844A0  rbtree insert wrapper (member)
// ===========================================================================
struct Map844 {
    char pad0[4];
    void* head;    // +0x04
    void* tail;    // +0x08
    char padc[8];
    int count;     // +0x14
    void* allocNode(int* key);   // FUN_00684420
    void insert(void** out, void* at, int* key, char flag);
};

void Map844::insert(void** out, void* at, int* key, char flag)
{
    int f = (!flag && at != (char*)this + 4 && *key >= *(int*)((char*)at + 0x10)) ? 1 : 0;
    void* node = allocNode(key);
    RBTreeInsert(node, at, (char*)this + 4, f);
    count += 1;
    *out = node;
}

// ===========================================================================
// @ 0x00684500  MapC insert-unique (thiscall, ret 0xc) -> pair<iter,bool>
// ===========================================================================
void MapC::InsertUnique(void* pairOut, const void* pair, char flag)
{
    (void)flag;
    const int* key = (const int*)pair;
    NodeC* anchor = (NodeC*)&mpAnchor;
    NodeC* pos = anchor;
    bool bLess = true;
    NodeC* n = mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpLeft : n->mpRight;
        } while (n);
    }
    NodeC* found = pos;
    if (bLess) {
        if (pos == mpBegin) {
            int bIns = (pos != anchor && *key >= pos->mKey) ? 1 : 0;
            NodeC* nn = CreateNode(pair);
            RBTreeInsert(nn, pos, anchor, bIns);
            ++mnSize;
            ((void**)pairOut)[0] = nn;
            *((uint8_t*)pairOut + 4) = 1;
            return;
        }
        pos = (NodeC*)RBTreeDecrement(pos);
    }
    if (pos->mKey >= *key) {
        ((void**)pairOut)[0] = pos;
        *((uint8_t*)pairOut + 4) = 0;
        return;
    }
    {
        int bIns = (found != anchor && *key >= found->mKey) ? 1 : 0;
        NodeC* nn = CreateNode(pair);
        RBTreeInsert(nn, found, anchor, bIns);
        ++mnSize;
        ((void**)pairOut)[0] = nn;
        *((uint8_t*)pairOut + 4) = 1;
    }
}

// ===========================================================================
// @ 0x00684610  MapB operator[] -> &value (thiscall, ret 4, EH)
// ===========================================================================
Obj2A10* MapB::Idx(const int& key)
{
    NodeB* anchor = (NodeB*)&mpAnchor;
    NodeB* pos = anchor;
    NodeB* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) cur = cur->mpRight;
        else { pos = cur; cur = cur->mpLeft; }
    }
    if (pos == anchor || key < pos->mKey) {
        struct { int k; Obj2A10 v; } p;
        p.k = key;
        NodeB* n;
        NodeB** out = &n;
        InsertHint(out, pos, &p.k, 0);
        return &(*out)->mVal;
    }
    return &pos->mVal;
}

// ===========================================================================
// @ 0x00684740  load map<int, Obj2A10> (thiscall, ret 8)
// ===========================================================================
void Factory::ReadMapB(MapB* map, IRd* r)
{
    uint32_t count;
    r->Read(&count, 4);
    for (uint32_t i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        Obj2A10* val = map->Idx(key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            val->mStr.Resize(len, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        r->Read(&val->b10, 1);
        r->Read(&val->b11, 1);
        r->Read(&val->b12, 1);
        r->Read(&val->b13, 1);
        r->Read(&val->b14, 1);
        r->Read(&val->w[0], 4);
        ReadInt32(r, &val->w[3], 1, 0);
        ReadInt32(r, &val->w[2], 1, 0);
        ReadInt32(r, &val->w[1], 1, 0);
        LoadEntries(&val->mM, r);
        LoadObj1800(&val->mVec, r);
    }
}

// ===========================================================================
// @ 0x00684890  MapC insert with hint (thiscall, ret 0x10)
// ===========================================================================
void MapC::InsertHint(NodeC** out, NodeC* hint, const void* pair, char flag)
{
    (void)flag;
    NodeC* anchor = (NodeC*)&mpAnchor;
    int* key = (int*)pair;
    if (hint == mpAnchor || hint == anchor) {
        if (mnSize == 0 || *key <= mpAnchor->mKey)
            goto UNIQUE;
        {
            int bIns = (mpAnchor == anchor || *key < mpAnchor->mKey) ? 0 : 1;
            NodeC* n = CreateNode(pair);
            RBTreeInsert(n, mpAnchor, anchor, bIns);
            ++mnSize;
            *out = n;
            return;
        }
    } else {
        NodeC* next = (NodeC*)RBTreeIncrement(hint);
        if (*key <= hint->mKey || next->mKey <= *key)
            goto UNIQUE;
        if (hint->mpRight == 0) {
            ((Map844*)this)->insert((void**)out, hint, key, 0);
            return;
        }
        {
            NodeC* n = CreateNode(pair);
            RBTreeInsert(n, next, anchor, 0);
            ++mnSize;
            *out = n;
            return;
        }
    }
UNIQUE:
    {
        void* p[2];
        p[0] = 0;
        InsertUnique(p, pair, 0);
        *out = (NodeC*)p[0];
    }
}

// ===========================================================================
// @ 0x00684980  MapC operator[] -> &value (thiscall, ret 4, EH)
// ===========================================================================
ObjY* MapC::Idx(const int& key)
{
    NodeC* anchor = (NodeC*)&mpAnchor;
    NodeC* pos = anchor;
    NodeC* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) cur = cur->mpRight;
        else { pos = cur; cur = cur->mpLeft; }
    }
    if (pos == anchor || key < pos->mKey) {
        struct { int k; ObjY v; } p;
        p.k = key;
        NodeC* n;
        NodeC** out = &n;
        InsertHint(out, pos, &p.k, 0);
        return &(*out)->mVal;
    }
    return &pos->mVal;
}

// ===========================================================================
// @ 0x00684A90  read records (partial)
// ===========================================================================
void read_684a90(void* unused, int* stream)
{
    read_6840d0(unused, stream);
}

// ===========================================================================
// @ 0x00684B40  serialize factory (partial)
// ===========================================================================
int ser_684b40(int* a, int* b)
{
    int i = ((int (__thiscall*)(void*))VT(a)[0x1c / 4])(a);
    if (i) {
        i = ((int (__thiscall*)(void*, int))VT(*(void**)(i + 4))[0xc / 4])(*(void**)(i + 4), 0x226a1de);
        if (i) return 0;
    }
    void* u = ((void* (__thiscall*)(void*))VT(a)[0x18 / 4])(a);
    int j = b ? ((int (__thiscall*)(void*, int))VT(b)[0xc / 4])(b, 0x355d6f5) : 0;
    FUN_00684a90((void*)(j + 0x50), u);
    FUN_00684740((void*)(j + 0x18), u);
    FUN_00682e90((void*)(j + 0x34), u);
    FUN_00683ab0((void*)(j + 0x6c), u);
    return 1;
}

// ===========================================================================
// @ 0x00684BE0  float -> int
// ===========================================================================
int __cdecl TruncFloat_684be0(float p)
{
    return (int)p;
}

// ===========================================================================
// @ 0x00684BF0  SP::CoordToIndex
// ===========================================================================
int* __cdecl SP_CoordToIndex(int* out, int n, float* c)
{
    out[2] = ((int*)c)[2];
    int x = (int)((float)n * c[0]);
    out[0] = x;
    int y = (int)(c[1] * (float)n);
    out[1] = y;
    if (x == n)
        out[0] = x - 1;
    if (y == n)
        out[1] = y - 1;
    return out;
}

// ===========================================================================
// @ 0x00684C50  index -> coordinate
// ===========================================================================
int __cdecl IndexToCoord_684c50(float* out, int n, int* c)
{
    float inv = 1.0f / (float)n;
    out[0] = ((float)c[0] + 0.5f) * inv;
    out[2] = ((float*)c)[2];
    out[1] = ((float)c[1] + 0.5f) * inv;
    return (int)out;
}

// ===========================================================================
// @ 0x00684CA0  SP::WrapCubeFace
// ===========================================================================
int __cdecl SP_WrapCubeFace(int n, uint32_t* face, uint32_t* x, int* y, int* u, int* v)
{
    uint32_t p = *face & 1;
    uint32_t q = p ^ 1;
    int s = p * -2 + 1;
    uint32_t xv = *x;
    int ns = -s;
    if ((int)xv < 0) {
        *x = xv + n;
        uint32_t nm1 = n - 1;
        *x = *y * ns + nm1 * q;
        *y = nm1 * p + (xv + n) * s;
        *face = q + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * ns;
            *v = t * s;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    } else if ((int)xv < n) {
        int yv = *y;
        if (yv < 0) {
            *y = yv + n;
            uint32_t xc = *x;
            *x = (yv + n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2 + 1;
        } else if (yv < n) {
            return 0;
        } else {
            *y = yv - n;
            uint32_t xc = *x;
            *x = (yv - n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2;
        }
        if (!u)
            return 1;
        int t = *u;
        *u = *v * ns;
        *v = t * s;
        return 1;
    } else {
        *x = xv - n;
        uint32_t nm1 = n - 1;
        *x = *y * s + nm1 * p;
        *y = nm1 * q + (xv - n) * ns;
        *face = p + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * s;
            *v = t * ns;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    }
    return SP_WrapCubeFace(n, face, x, y, u, v) + 1;
}
