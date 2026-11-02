// src/game/SPEngine/SPGraphicsRuntimeModel.cpp -- migrated from slice(s) s00774f80, s00773f60, s0076ed30, s01212800, s00775760 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRuntimeModel.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "rw/core/arena/Arena.h"
#include <xmmintrin.h>

// ---- items of slice s00775760 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(noinline) int FUN_00776320(int a, int b, int c, int d, int e);   // @ 0x00776320
void operator_delete_array(void* p);                       // 0x00f47380 (operator delete[])
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
void operator delete(void*, const char*, int, int, int, int) {}
struct RCObj { void** vptr; volatile long rc; };
inline void RC_AddRef(RCObj* o) { _InterlockedExchangeAdd(&o->rc, 1); }
struct GmeRefCount {
    volatile long rc;
    __forceinline GmeRefCount() { _InterlockedExchange(&rc, 0); }
    virtual ~GmeRefCount() {}
};
struct GmeObj : GmeRefCount {                                // sizeof 0x58
    int f08, f0c, f10, p14[2], f1c, f20, f24, p28[2], f30, f34, f38, p3c[2], f44, f48, f4c, p50[2];
    __forceinline GmeObj() {
        f08 = f0c = f10 = 0; f1c = f20 = f24 = 0; f30 = f34 = f38 = 0; f44 = f48 = f4c = 0;
    }
    virtual ~GmeObj() {}
};
inline void GmeRelease(GmeObj* o) {
    if (_InterlockedExchangeAdd(&o->rc, -1) == 1) {
        _InterlockedExchange(&o->rc, 1);
        delete o;                                            // vtable slot 0 (deleting dtor)
    }
}
struct IRefObj { virtual int AddRef() = 0; virtual int Release() = 0; virtual int v2() = 0; virtual void* GetSub(uint32_t type) = 0; };
struct IResMgr { virtual int v0() = 0; virtual int v1() = 0; virtual int v2() = 0;
                 virtual bool GetResource(const void* key, IRefObj** out, int a, int b, int c, int d) = 0; };
IResMgr* GetManager();                                        // 0x0067dcd0
struct ResPtr {
    IRefObj* p;
    ResPtr() : p(0) {}
    ~ResPtr() { if (p) p->Release(); }
    void reset() { IRefObj* t = p; if (t) { p = 0; t->Release(); } }
};
struct ResKey3 { uint32_t inst, type, group; };
struct Mesh : RCObj {
    char pad08[0x14]; char* part;                             // +0x1c: sub-part table
    int sub_572b10();                                         // part count
    bool sub_71dc90(int idx);                                 // ret 4
};
struct RefVec {                                               // vector of intrusive refs
    RCObj** b; RCObj** e; RCObj** cap;
    RefVec() : b(0), e(0), cap(0) {}
    ~RefVec() { sub_41eb80(); }
    void sub_41eb80();
    void sub_41ef20(GmeObj** p);                              // push_back(const intrusive_ptr<GmeObj>&)
    void sub_424430(RCObj** pos, RCObj** val);                // DoInsertValue, ret 8
};
__forceinline void PushBack(RefVec* v, RCObj** src) {
    RCObj** e = v->e;
    if (e < v->cap) {
        v->e = e + 1;
        if (e) { RCObj* x = *src; *e = x; if (x) RC_AddRef(x); }
    } else {
        v->sub_424430(e, src);
    }
}
struct FixBase { char* b; char* e; char* cap; uint32_t alloc; char* pool; uint32_t pad; };
struct FixA : FixBase { uint32_t buf[256]; void sub_4c0570(int n, int v);
    ~FixA() { if (b && b != pool) operator_delete_array(b); } };
struct FixB : FixBase { uint32_t buf[12 * 256]; void sub_774df0(int n);
    ~FixB() { if (b && b != pool) operator_delete_array(b); } };
struct FixC : FixBase { uint32_t buf[44 * 256]; void sub_774e50(int n);
    ~FixC() { if (b && b != pool) operator_delete_array(b); } };
struct FixD : FixBase { uint32_t buf[12 * 256]; void sub_774eb0(int n);
    ~FixD() { if (b && b != pool) operator_delete_array(b); } };
struct SkelInfo { uint32_t pad[2]; int* ids; int count; };    // arena/rest-pose record
struct BakeRec { uint32_t pad[3]; SkelInfo* rec; int valid; };
struct SInfo {
    int M; int count; short w0, w1; IRefObj* ref;
    ~SInfo() { if (ref) ref->Release(); }
};
struct Drawer { void sub_740550(void* boneBuf); };            // ret 4
struct ArenaRes {                                             // GetArenaResource record
    char pad08[8];
    uint32_t keyInst, keyType, keyGroup;                      // +0x08, +0x0c, +0x10
};
struct Inst {
    char pad[0xf0]; Drawer* draw;
    bool sub_73eb90(RefVec* out);                             // GetMeshes, ret 4
    ArenaRes* sub_73d160();                                   // GetArenaResource
    void sub_73ba50(void (*fn)());                            // ret 4
};
struct Builder { void sub_775230(void** p); };                // ret 4
extern Builder g_builder_1630b68;
void FUN_007740f0();
int FUN_006ac0a0(int a, void* p);
bool FUN_00757d20(void* p);
void FUN_0072fff0(void* p, RefVec* out);
bool FUN_00774f80(Mesh* a, void* b);
int FUN_0071ddc0(void* m, int a, int b, int c, int d);
BakeRec* FUN_0076fb10(void* p);
bool FUN_0076fc20(SkelInfo* a, SkelInfo* b, FixA* idx);
void FUN_0076fc90(SkelInfo* a, void* idx, int n, int m, void* b, void* c, void* d);
void FUN_00720070(SInfo* s);
void FUN_00774110(SInfo* s, void* a, void* rec, int k);
bool FUN_0073a110(void* d, void* mesh, GmeObj* o);
void FUN_007754d0(void* a, void* b);
void FUN_007756b0(void* a, SInfo* s);
void SetKeyKind(ResKey3* key, int kind, int flags);           // 0x0068c6d0
// ---- items of slice s00775760 end

// ---- items of slice s0076ed30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int A_1630b68;   // 0x01630b68
extern int A_1630b6c;   // 0x01630b6c
extern int A_1630b70;   // 0x01630b70
extern int A_1630b74;   // 0x01630b74
extern int A_1630b78;   // 0x01630b78
extern int A_1630b7c;   // 0x01630b7c
extern int A_1630b80;   // 0x01630b80
struct __declspec(align(16)) Elem30 {
    __m128 v;        // +0x00
    float  f[6];     // +0x10
    Elem30& operator=(const Elem30& o);
};
Elem30& Elem30::operator=(const Elem30& o)
{
    v = o.v;
    for (int i = 0; i < 6; ++i) f[i] = o.f[i];
    return *this;
}
struct BaseResourceDescriptor { int mRef; int mFlags; BaseResourceDescriptor(); ~BaseResourceDescriptor(); };
struct ExportedObj { int mType; int mValue; int pad[4]; };
struct Arena {
    int  GetNumExportedObjects();                       // 0x011e23a0
    void GetExportedObjectByIndex(int i, ExportedObj* out);  // 0x011e28e0
};
struct FC20A { int pad0; int* mMap; int pad8; int mCount; };
struct FC20B { int pad0; int* mMap; };
void __cdecl AllocB0(int self, int zero, int size);    // 0x011e073e
// ---- items of slice s0076ed30 end

// ---- items of slice s00774f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EASTL_allocator_deallocate(void* p);   // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, int c, int d);  // 0x00f473a0
extern "C" void eastl_sort_14(void* first, void* last, void* compare);  // 0x007749e0
extern "C" void* LessPage;   // 0x0076f540
extern "C" void* Model_findStream(void* m, int semantic, int usageIdx, int number, int type);  // 0x0071de40
extern "C" int   Model_findStreamEntry(void* m, int semantic, int usageIdx, int number, int type);  // 0x0071ddc0
extern "C" void  BuildIndexTable(void* m, void* out);        // 0x0076fdc0
extern "C" void  Obj15_200f0(void* buf);                     // 0x007200f0
extern "C" void  FUN_00774d90(int v);                        // 0x00774d90
extern int g_0140e5b4[];   // 0x0140e5b4 (channel mask table)
extern int g_0140e5c8[];   // 0x0140e5c8 (semantic list)
extern int g_0140e5d4[];   // 0x0140e5d4 (end of the semantic list)
struct Elem20 {
    int m0;              // +0x00 (copied from src+0x00)
    int m4;              // +0x04 (copied from src+0x04)
    unsigned short m8;   // +0x08
    unsigned short ma;   // +0x0a
    void* mpRef;         // +0x0c (copied start; full 0x20 layout below)
};
struct Vec20 {
    void push_back(const Elem20& value);
};
struct FixVec14 {
    int* mpBegin;     // +0x00
    int* mpEnd;       // +0x04
    int* mpCapacity;  // +0x08
    int* mpAlloc;     // +0x0c
    int* mpFixed;     // +0x10
    int mAux14;       // +0x14
    int mInline[0x140 / 4];   // +0x18 .. +0x158 inline storage (16 x 0x14 elements)
    void init_range(void* first, void* last);   // @ 0x00774f10
    ~FixVec14() {
        if (mpBegin != 0 && mpBegin != mpFixed)
            EASTL_allocator_deallocate(mpBegin);
    }
};
struct CellVec;
struct RuntimeModelBuilder {
    int m0;                  // +0x00
    int m4;                  // +0x04
    int mCount;              // +0x08  (number of meshes)
    int m_0c;                // +0x0c
    int m_10;                // +0x10
    int m_pRecA;             // +0x14  (0x8c-byte record array)
    int m_pRecB;             // +0x18
    int m_pMeshBegin;        // +0x1c  (0x8c-byte mesh records)
    int m_pMeshEnd;          // +0x20
    int m_24;                // +0x24
    int m_28;                // +0x28
    int m_2c;                // +0x2c
    int m_pFixBegin;         // +0x30  (0x14-byte fixed elements)
    int m_pFixEnd;           // +0x34
    void BuildCellArray(void** out);   // @ 0x00775230
};
struct CellArray {
    void ctor(CellVec* buffer, int count);
};
struct MeshSrc {
    unsigned char m00;        // +0x00
    char pad03[3];
    int m04;                  // +0x04
    int m08;                  // +0x08
    int m0c;                  // +0x0c
    float m10[4];             // +0x10..0x1c
    float m20[4];             // +0x20..0x2c
    float m30[4];             // +0x30..0x3c
    float m40[4];             // +0x40..0x4c
    float m50[4];             // +0x50..0x5c
    float m60[4];             // +0x60..0x6c
    float m70[4];             // +0x70..0x7c
    float m80[4];             // +0x80..0x8c
    int m90;                  // +0x90
    int m94;                  // +0x94
    int m98;                  // +0x98
    int m9c;                  // +0x9c
    int ma0;                  // +0xa0
    int ma4;                  // +0xa4
};
struct MeshRec {
    int m00;                  // +0x00
    int m04;                  // +0x04
    int m08;                  // +0x08
    int m0c;                  // +0x0c
    int m10;                  // +0x10
    int m14;                  // +0x14
    int m18;                  // +0x18
    int m1c;                  // +0x1c
    int m20;                  // +0x20
    int m24;                  // +0x24
    int m28;                  // +0x28
    int m2c;                  // +0x2c
};
struct CellRec {
    int m[0x28];              // 0xa0 bytes
};
struct Vec4i { int x, y, z, w; };
struct CellVec {
    CellRec* mpBegin;         // +0x00 (points at the inline array)
    CellRec* mpEnd;           // +0x04
    CellRec* mpCapacity;      // +0x08
    CellRec* mpAlloc;         // +0x0c
    CellRec* mpFixed;         // +0x10
    int m_14;                 // +0x14
    int m_18;                 // +0x18
    int m_1c;                 // +0x1c
    CellRec mInline[0x100];   // +0x20
    void reserve(int count);  // @ 0x00774d30
};
struct StreamBuf {
    int mCount;              // +0x00
    int mBase;               // +0x04 (data base pointer)
    unsigned short m08;      // +0x08
    unsigned short mStrideA; // +0x0a
};
struct MeshRecord8c {
    int m00;                 // +0x00
    int mStream;             // +0x04 (StreamBuf*)
    unsigned short m08;      // +0x08 (channel index)
    unsigned short mStride;  // +0x0a (variable stride)
};
struct IndexEntry {
    int mIndex;              // +0x00 (-1 = empty)
    int mColumn;             // +0x04
};
struct IndexTable {
    char mInline[0x10];       // +0x00 (inline header / self pointer)
    IndexEntry* mpEntries;    // +0x10
    int mCount;               // +0x14
    char mBuf[0x2000];        // +0x18 inline storage
    void* data() { return mBuf; }
    IndexEntry* entries() { return mpEntries; }
};
struct RefObject {
    virtual void AddRef();    // vtbl +0
    virtual void Release();   // vtbl +4
};
struct Elem20Full {
    int h0, h1, h2, h3;   // +0x00 +0x04 +0x08 +0x0c
    int m0;               // +0x10
    int m4;               // +0x14
    unsigned short m8;    // +0x18
    unsigned short ma;    // +0x1a
    void* mpRef;          // +0x1c
    ~Elem20Full() {
        if (mpRef != 0)
            ((RefObject*)mpRef)->Release();
    }
};
// ---- items of slice s00774f80 end

// @ 0x0076fb10
int __cdecl BakeToArena(int baker)
{
    if (baker == 0)
        return 0;
    Arena* arena = *(Arena**)(baker + 0x18);
    int n = arena->GetNumExportedObjects();
    for (int i = 0; i < n; ++i) {
        ExportedObj obj = { 0, 0, { 0, 0, 0, 0 } };
        BaseResourceDescriptor arr[4];
        arr[0].mRef = 0;
        arr[0].mFlags = 1;
        arena->GetExportedObjectByIndex(i, &obj);
        if (obj.mType == 0x7000c)
            return obj.mValue;
    }
    return 0;
}

// @ 0x0076fc20
bool __cdecl HelperFC20(FC20A* a, FC20B* b, int** c)
{
    int i = 0;
    bool result = false;
    if (a->mCount < 1)
        return false;
    int* v = *c;
    do {
        int x = v[i];
        if (x >= 0) {
            int y = a->mMap[i];
            bool eq;
            result = true;
            if (y == -1) {
                eq = (b->mMap[x] == -1);
            } else {
                while (v[y] == -1) {
                    y = a->mMap[y];
                    if (y == -1)
                        return false;
                }
                if (y == -1)
                    return false;
                eq = (v[y] == b->mMap[x]);
            }
            if (!eq)
                return false;
        }
        ++i;
    } while (i < a->mCount);
    return result;
}

// @ 0x0076fc90
void __cdecl HelperFC90(int a1, int a2, int a3, int count, int a5, int a6, int a7)
{
    A_1630b68 = a1; A_1630b6c = a3; A_1630b70 = count; A_1630b74 = a2;
    A_1630b7c = a5; A_1630b80 = a6; A_1630b78 = a7;
    if (count <= 0)
        return;
    float m[13];
    m[0] = m[1] = m[2] = 0.0f;
    m[3] = m[4] = m[5] = m[6] = m[7] = m[8] = 1.0f;
    m[9] = m[10] = m[11] = 0.0f;
    m[12] = 1.0f;
    for (int i = count; i != 0; --i) {
        float* elem = (float*)((char*)a5 + 0x1c);
        elem[-7] = m[9]; elem[-6] = m[10]; elem[-5] = m[11]; elem[-4] = m[12];
        elem[-3] = m[0]; elem[-2] = m[1]; elem[-1] = m[2];
        elem[0] = m[3]; elem[1] = m[4]; elem[2] = m[5];
        char* obj = (char*)a6;
        AllocB0((int)obj, 0, 0xb0);
        *(float*)(obj + 0x90) = m[5];
        *(float*)(obj + 0x94) = m[6];
        *(float*)(obj + 0x98) = m[7];
        *obj = 0;
        a5 += 0x30;
        a6 += 0xb0;
    }
}

// @ 0x00774110
void FUN_00774110(int* param_1, unsigned param_2, int* param_3)
{
    (void)param_1;
    (void)param_2;
    (void)param_3;
}

// @ 0x00774f80
bool CompareModelBuilders(RuntimeModelBuilder* a, RuntimeModelBuilder* b)
{
    // (m_pMeshEnd - m_pMeshBegin) / 0x8c, signed.
    int meshA = (int)(((char*)a->m_pMeshEnd - (char*)a->m_pMeshBegin)) / 0x8c;
    int meshB = (int)(((char*)b->m_pMeshEnd - (char*)b->m_pMeshBegin)) / 0x8c;
    if (meshA != meshB)
        return false;

    int fixA = (int)(((char*)a->m_pFixEnd - (char*)a->m_pFixBegin)) / 0x14;
    int fixB = (int)(((char*)b->m_pFixEnd - (char*)b->m_pFixBegin)) / 0x14;
    if (fixA != fixB)
        return false;

    FixVec14 vecA, vecB;
    vecA.init_range((void*)a->m_pFixBegin, (void*)a->m_pFixEnd);
    vecB.init_range((void*)b->m_pFixBegin, (void*)b->m_pFixEnd);

    eastl_sort_14(vecA.mpBegin, vecA.mpEnd, &LessPage);
    eastl_sort_14(vecB.mpBegin, vecB.mpEnd, &LessPage);

    const int n = (int)(((char*)vecA.mpEnd - (char*)vecA.mpBegin)) / 0x14;
    const int* pa = vecA.mpBegin;
    const int* pb = vecB.mpBegin;
    int i = 0;
    if (n > 0) {
        do {
            if (pa[0] != pb[0])
                return false;
            if (pa[1] != pb[1])
                return false;
            if (pa[2] != pb[2])
                return false;
            if (pa[3] != pb[3])
                return false;
            ++i;
            pa += 5;
            pb += 5;
        } while (i < n);
    }
    return true;
}

// @ 0x00775230
void RuntimeModelBuilder::BuildCellArray(void** out)
{
    CellVec vec;              // fixed 0x100-entry packed buffer (0xa000 bytes)

    vec.reserve(mCount);

    int idx = 0;
    if (mCount > 0) {
        int dstOff = 0;
        int recOff = 0;
        int elOff = 0;
        do {
            const MeshRec* rec = (const MeshRec*)(m_pRecA + recOff);
            const MeshSrc* el = (const MeshSrc*)(m_pRecB + elOff);
            CellRec* d = (CellRec*)((char*)vec.mpBegin + dstOff);
            int* o = d->m;

            o[0] = rec->m10;
            o[1] = rec->m14;
            o[2] = rec->m18;
            // rec[0..3] copied as one 16-byte block (original: movaps).
            *(Vec4i*)&o[4] = *(const Vec4i*)&rec->m00;
            o[8] = rec->m1c;
            o[9] = rec->m20;
            o[10] = rec->m24;
            o[0xb] = el->m90;
            o[0xc] = el->m94;
            o[0xd] = el->m98;
            *(unsigned char*)&o[0xe] = el->m00;
            o[0xf] = el->m04;
            o[0x10] = el->m08;
            o[0x11] = el->m0c;

            // 4x4 matrix product: out rows = A(m10,m20,m30,m40) * B(cols m50,m60,m70,m80).
            float* f = (float*)&o[0x14];
            f[0] = el->m10[0] * el->m50[0] + el->m20[0] * el->m50[1] + el->m30[0] * el->m50[2];
            f[1] = el->m10[1] * el->m50[0] + el->m20[1] * el->m50[1] + el->m30[1] * el->m50[2];
            f[2] = el->m10[2] * el->m50[0] + el->m20[2] * el->m50[1] + el->m30[2] * el->m50[2];
            f[3] = el->m10[3] * el->m50[0] + el->m20[3] * el->m50[1] + el->m30[3] * el->m50[2];
            f[4] = el->m10[0] * el->m60[0] + el->m20[0] * el->m60[1] + el->m30[0] * el->m60[2];
            f[5] = el->m10[1] * el->m60[0] + el->m20[1] * el->m60[1] + el->m30[1] * el->m60[2];
            f[6] = el->m10[2] * el->m60[0] + el->m20[2] * el->m60[1] + el->m30[2] * el->m60[2];
            f[7] = el->m10[3] * el->m60[0] + el->m20[3] * el->m60[1] + el->m30[3] * el->m60[2];
            f[8] = el->m10[0] * el->m70[0] + el->m20[0] * el->m70[1] + el->m30[0] * el->m70[2];
            f[9] = el->m10[1] * el->m70[0] + el->m20[1] * el->m70[1] + el->m30[1] * el->m70[2];
            f[10] = el->m10[2] * el->m70[0] + el->m20[2] * el->m70[1] + el->m30[2] * el->m70[2];
            f[11] = el->m10[3] * el->m70[0] + el->m20[3] * el->m70[1] + el->m30[3] * el->m70[2];
            f[12] = el->m10[0] * el->m80[0] + el->m20[0] * el->m80[1] + el->m30[0] * el->m80[2] + el->m40[0];
            f[13] = el->m10[1] * el->m80[0] + el->m20[1] * el->m80[1] + el->m30[1] * el->m80[2] + el->m40[1];
            f[14] = el->m10[2] * el->m80[0] + el->m20[2] * el->m80[1] + el->m30[2] * el->m80[2] + el->m40[2];
            f[15] = el->m10[3] * el->m80[0] + el->m20[3] * el->m80[1] + el->m30[3] * el->m80[2] + el->m40[3];
            o[0x24] = el->m9c;
            o[0x25] = el->ma0;
            o[0x26] = el->ma4;

            ++idx;
            dstOff += 0xa0;
            recOff += 0x30;
            elOff += 0xb0;
        } while (idx < mCount);
    }

    char* p = (char*)EASTL_allocator_allocate(0x10, "Graphics", 0, 0, 0, 0);
    char* result = 0;
    if (p == 0) {
        result = 0;
    } else {
        result = p;
        ((CellArray*)result)->ctor(&vec, mCount);
    }
    *(int*)(result + 4) += 1;   // refcount
    *out = result;
}

// @ 0x007754d0
bool BuildElementIndex(void* arg1, void* arg2)
{
    void* target = arg1;   // the mesh whose stream/index we build
    void* source = arg2;   // the mesh we read values from
    void* stream = Model_findStream(target, 1, -1, 3, 0xe);
    if (((int*)stream)[1] == 0)
        return false;

    int handle = ((int*)stream)[0];
    FUN_00774d90(handle);

    IndexTable table;
    BuildIndexTable(target, &table);

    int* sem = g_0140e5c8;
    do {
        int i0 = Model_findStreamEntry(source, *sem, -1, 3, 0xe);
        int i1 = Model_findStreamEntry(target, *sem, -1, 3, 0xe);
        if (i0 >= 0 && i1 >= 0) {
            StreamBuf* dst = (StreamBuf*)(*(int*)((char*)target + 8) + i1 * 0x20 + 0x10);
            StreamBuf* src = (StreamBuf*)(*(int*)((char*)source + 8) + i0 * 0x20 + 0x10);
            Obj15_200f0(dst);

            int n = dst->mCount;
            if (table.mCount < n)
                n = table.mCount;

            IndexEntry* e = table.entries();
            for (int j = 0; j < n; ++j) {
                if (e[j].mIndex == -1)
                    continue;
                int col = e[j].mColumn;
                MeshRecord8c* rec = (MeshRecord8c*)(*(int*)((char*)source + 0x1c) + e[j].mIndex * 0x8c);
                if (rec->mStream != 0) {
                    unsigned int raw = *(unsigned int*)(rec->mStream + rec->mStride * col);
                    col = (int)(raw & (unsigned int)g_0140e5b4[rec->m08]);
                }
                float* srcv = (float*)(src->mBase + src->mStrideA * col);
                float* dstv = (float*)(dst->mBase + dst->mStrideA * j);
                dstv[0] = srcv[0];
                dstv[1] = srcv[1];
                dstv[2] = srcv[2];
            }
        }
        ++sem;
    } while (sem < g_0140e5d4);

    if (table.mpEntries != 0 && (void*)table.mpEntries != table.data())
        EASTL_allocator_deallocate(table.mpEntries);
    return true;
}

// @ 0x007756b0
void PushElem20(void* self, Elem20* src)
{
    Elem20Full tmp;
    tmp.h0 = 0x13;
    tmp.h1 = 0;
    tmp.h2 = 0xe;
    tmp.h3 = 5;
    tmp.m0 = src->m0;
    tmp.m4 = src->m4;
    tmp.m8 = src->m8;
    tmp.ma = src->ma;
    tmp.mpRef = src->mpRef;

    if (tmp.mpRef != 0)
        ((RefObject*)tmp.mpRef)->AddRef();

    ((Vec20*)((char*)self + 8))->push_back(*(const Elem20*)&tmp);
}

// @ 0x00775760
int FUN_00775760(Inst* inst, RefVec* outMeshes, void** out3, void** out4, ResKey3 key, int arg8)
{
    if (!inst) return 1;
    key.type = 0x2f4e681b;
    ResPtr res;
    IResMgr* mgr = GetManager();
    res.reset();
    if (!mgr->GetResource(&key, &res.p, 0, 0, 0, 0)) return 1;
    FUN_006ac0a0(9, res.p);
    if (!res.p) return 1;
    IRefObj* sub = (IRefObj*)res.p->GetSub(0x2f4e681b);
    if (!sub) return 1;
    if (FUN_00757d20(sub)) return 2;

    RefVec v1;
    RefVec v2;
    FUN_0072fff0(sub, &v1);
    if (!inst->sub_73eb90(&v2)) return 3;
    int n = (int)(v2.e - v2.b);
    if (n != (int)(v1.e - v1.b)) return 4;

    for (int i = 0; i < n; ++i) {
        Mesh* a = (Mesh*)v2.b[i];
        Mesh* b = (Mesh*)v1.b[i];
        if (!FUN_00774f80(a, b)) return 5;
        int s1 = FUN_0071ddc0(a, 1, -1, 3, 0xe);
        int s2 = FUN_0071ddc0(b, 1, -1, 3, 0xe);
        if (s1 < 0 || s2 < 0) return 5;
        int parts = a->sub_572b10();
        uint32_t* q = (uint32_t*)(a->part + 0x44);
        for (int j = 0; j < parts; ++j, q += 0x23) {
            if (q[0] != q[1]) return 5;
            if (b->sub_71dc90(j)) return 5;
        }
    }

    BakeRec* r1 = FUN_0076fb10(sub);
    SkelInfo* rb = (r1 && r1->valid) ? r1->rec : 0;
    BakeRec* r2 = FUN_0076fb10(inst->sub_73d160());
    SkelInfo* arena;
    int N;
    if (r2 && r2->valid) {
        arena = r2->rec;
        N = arena ? arena->count : 0;
    } else {
        arena = 0;
        N = 0;
    }
    int M = rb ? rb->count : 0;

    FixA A; A.sub_4c0570(N, -1);
    FixB B; B.sub_774df0(M);
    FixC C; C.sub_774e50(M);
    FixD D; D.sub_774eb0(N);
    SInfo S;
    S.M = M; S.count = 0; S.w0 = 0x30; S.w1 = 0x30; S.ref = 0;
    *out4 = 0;
    if (arena) {
        if (rb) {
            for (int i = 0; i < N; ++i) {
                int id = arena->ids[i];
                int found = -1;
                for (int j = 0; j < M; ++j)
                    if (id == rb->ids[j]) found = j;
                ((int*)A.b)[i] = found;
            }
            if (!FUN_0076fc20(arena, rb, &A)) return 6;
            FUN_0076fc90(arena, A.b, N, M, B.b, C.b, D.b);
            inst->sub_73ba50(FUN_007740f0);
            g_builder_1630b68.sub_775230(out4);
            FUN_00720070(&S);
            FUN_00774110(&S, *out4, FUN_0076fb10(sub), arg8);
        } else {
            inst->draw->sub_740550(D.b);
        }
    }

    RefVec v3;
    for (int i = 0; i < n; ++i) {
        GmeObj* o = new ("Graphics", 0, 0, 0, 0) GmeObj();
        if (o) _InterlockedExchangeAdd(&o->rc, 1);
        if (arena && FUN_0073a110(D.b, v2.b[i], o)) {
            v3.sub_41ef20(&o);
        } else {
            PushBack(&v3, &v2.b[i]);
        }
        if (o) GmeRelease(o);
    }
    for (int i = 0; i < n; ++i) {
        void* m = v1.b[i];
        FUN_007754d0(v3.b[i], m);
        if (S.count) FUN_007756b0(m, &S);
    }
    for (int i = 0; i < n; ++i)
        PushBack(outMeshes, &v1.b[i]);
    sub->AddRef();
    *out3 = sub;
    return 0;
}

// @ 0x00776320
int FUN_00776320(int instArg, int outMeshesArg, int out3Arg, int out4Arg, int arg8)
{
    Inst* inst = (Inst*)instArg;
    if (inst) {
        ArenaRes* arena = inst->sub_73d160();
        if (arena) {
            ResKey3 key;
            key.inst = arena->keyInst;
            key.type = arena->keyType;
            key.group = arena->keyGroup;
            SetKeyKind(&key, 0x61, 0);
            return FUN_00775760(inst, (RefVec*)outMeshesArg, (void**)out3Arg, (void**)out4Arg, key, arg8);
        }
    }
    return 1;
}

// @ 0x007763b0
bool GetRuntimeMeshes(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    return FUN_00776320(param_1, param_2, param_3, param_4, param_5) == 0;
}

// @ 0x01213750
void __cdecl FUN_01213750()
{}
