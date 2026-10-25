// Slice s00747920 (0x00747920..0x00748530): cModelWorld load-queue / model-group
// container helpers, EASTL heap instantiations and FilterModelSphere, /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

struct Vec3 { float x, y, z; };
struct cSPTransform {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};

// --- callees ---------------------------------------------------------------
// Retail thiscall helpers are modelled as extern "C" __fastcall(self, dummy, ...) so the
// emulator sees this in ecx and the dummy in edx (MSVC 2008 rejects __thiscall on free
// functions); the literal 0 dummy keeps the stack shape identical to the original.
void* operator_new(uint32_t n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator_delete_(void* p);
extern "C" void __fastcall FUN_007457a0(void* self, int dummy, int a, int b);   // 0x007457a0
void  RBTreeInsert(void* node, void* parent, void* anchor, int flag);
extern "C" void __fastcall cSPTransform_Assign(void* self, int dummy, const void* src);   // 0x00537dc0
extern "C" void __fastcall Matrix3_Assign(void* self, int dummy, const void* src);   // 0x0041cb40
extern "C" int  __fastcall cSPTransform_BackTransformPoint(void* self, int dummy, void* pt);   // 0x004ff6d0
extern "C" int  __fastcall cModelInstance_PickLine(void* self, int dummy, void* pos, float radius, void* v, int flag);   // 0x0073f540
void* FUN_00743fb0(void* p, float f, void* box);   // 0x00743fb0
void  FUN_00745e00(void* first, int top, int size, int pos, float vx, float vy, u32 cmp);   // 0x00745e00
void  FUN_00745e80(void* first, int top, int size, int pos, float vx, float vy, u32 cmp);   // 0x00745e80
void  adjust_heap_occluder(void* first, int top, int size, int pos, float a, float b, float c,
                           float d, float e, float f, void* cmp);
void  translateTransform(void* out, void* a, const void* b);   // 0x006271a0
extern float g_f162eb0c;   // 0x0162eb0c
extern float g_f162eb10;   // 0x0162eb10
extern float g_f162eb14;   // 0x0162eb14
extern float g_f162ec4c;   // 0x0162ec4c  Matrix3 identity source
extern float g_f1485720;   // 0x01485720  _HK_REAL_ONE

// refcounted object with refcount at +4 and releasing slot at vtable+4.
struct RCObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    int mRefCount;   // +4
};
static inline void AddRefObj(RCObj* o) { if (o) o->mRefCount++; }
static inline void RelObj(RCObj* o)
{
    if (o && --o->mRefCount == 0) {
        o->mRefCount = 1;
        (*(void(__thiscall**)(RCObj*, int))(*(void**)o))(o, 1);
    }
}

// ===========================================================================
struct Stub00747920 { void F(); };
// @ 0x00747920 : deque< cLoadQueueEntry >::pop_back
void Stub00747920::F()
{
    unsigned char* b = (unsigned char*)this;
    int beg = *(int*)(b + 0x18);
    int end = *(int*)(b + 0x1c);
    if (beg == end) {
        if (end) operator_delete_((void*)end);
        int* mapEnd = (int*)(*(int*)(b + 0x24) - 4);
        *(int**)(b + 0x24) = mapEnd;
        int blk = *mapEnd;
        *(int*)(b + 0x1c) = blk;
        *(int*)(b + 0x20) = blk + 0xe0;
        *(int*)(b + 0x18) = blk + 0xc4;
        if (*(int**)(blk + 200)) {
            RCObj* r = *(RCObj**)(blk + 200);
            (*(void(__thiscall**)(RCObj*, int))((char*)(*(void**)r) + 4))(r, 1);
        }
    } else {
        *(int*)(b + 0x18) = beg - 0x1c;
        RCObj* r = *(RCObj**)(beg - 0x18);
        if (r) (*(void(__thiscall**)(RCObj*, int))((char*)(*(void**)r) + 4))(r, 1);
    }
}

// refcounted load-queue element: object pointer at +4, trailing dwords at +0xc..+0x18.
struct LoadQueueEntry {
    int    f00;   // +0x00
    RCObj* obj;   // +0x04
    int    f08;   // +0x08
    int    f0c;   // +0x0c
    int    f10;   // +0x10
    int    f14;   // +0x14
    int    f18;   // +0x18
};
// 0x1c-byte deque element: two object words then five payload dwords.
struct LoadQueueSlot { RCObj* w0; RCObj* w1; int p0, p1, p2, p3, p4; };
struct LoadQueue {
    void** mMapBegin;   // +0x00
    int    mMapCap;     // +0x04
    unsigned char pad08[0x18 - 0x08];
    void*  mCur;        // +0x18
    void*  mNext;       // +0x1c
    void*  mEnd;        // +0x20
    void** mMapEnd;     // +0x24
    void FUN_00747980(LoadQueueEntry* e);
};
// @ 0x00747980 : deque< cLoadQueueEntry >::push_back
void LoadQueue::FUN_00747980(LoadQueueEntry* e)
{
    RCObj* o = e->obj;
    if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
    int c1 = e->f0c, c2 = e->f10, c3 = e->f14, c4 = e->f18;
    if ((int)(((char*)mMapEnd - (char*)mMapBegin) >> 2) + 1 >= mMapCap)
        FUN_007457a0(this, 0, 1, 1);
    void* blk = operator_new(0xe0, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    mMapEnd[1] = blk;
    LoadQueueSlot* slot = (LoadQueueSlot*)mCur;
    if (slot) {
        slot->w0 = e->obj;
        slot->w1 = e->obj;
        if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
        slot->p0 = c1;
        slot->p1 = c2;
        slot->p2 = c3;
        slot->p3 = c4;
        slot->p4 = c4;
    }
    mMapEnd = (void**)((char*)mMapEnd + 4);
    mNext = *mMapEnd;
    mEnd = (char*)*mMapEnd + 0xe0;
    mCur = mNext;
    if (o) (*(void(__thiscall**)(RCObj*))((char*)(*(void**)o) + 4))(o);
}

// copy of a 0x38-byte record (0x00747ac0) (dwords + Matrix3 copy ctor)
struct Mat3 { float m[9]; Mat3() {} Mat3(const Mat3& o) { for (int i = 0; i < 9; ++i) m[i] = o.m[i]; } };
struct Rec38 {
    int a; short b, c; int d, e, f, g;
    Mat3 rot;   // +0x18
};
struct Rec38Stub { Rec38* F(Rec38* src); };
// @ 0x00747ac0
Rec38* Rec38Stub::F(Rec38* src)
{
    Rec38* dst = (Rec38*)this;
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->e = src->e;
    dst->f = src->f;
    dst->g = src->g;
    new (&dst->rot) Mat3(src->rot);
    return dst;
}

// @ 0x00747b70 : uninitialized_copy of 0x3c-byte refcounted elements
struct E3C { int key; RCObj* obj; short a, b; int d, e, f, g, h, i, j, k, l, m; };
struct E3CResult { int cur; };
void FUN_00747b70(E3CResult* res, E3C* first, E3C* last, E3C* dst)
{
    res->cur = (int)dst;
    if (first != last) {
        for (; first != last; first += 1, dst += 1) {
            if (dst) {
                dst->key = first->key;
                RCObj* o = first->obj;
                if (o != dst->obj) {
                    if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
                    dst->obj = o;
                    if (dst->obj) RelObj(dst->obj);
                }
                dst->a = first->a;
                dst->b = first->b;
                dst->d = first->d;
                dst->e = first->e;
                dst->f = first->f;
                dst->g = first->g;
                dst->h = first->h;
                dst->i = first->i;
                dst->j = first->j;
                dst->k = first->k;
                dst->l = first->l;
                dst->m = first->m;
            }
        }
        res->cur = (int)dst;
    }
}

// @ 0x00747c90 : uninitialized_fill_n of 0x3c-byte elements
// The element is a plain POD: dword key, two words, then 13 floats (+8..+0x38).
struct Plain3C { u32 key; u16 a, b; float f[13]; };
void* FUN_00747c90(E3C* dst, int n, E3C* value)
{
    // the original only computes eax after the n>0 test, so an n==0 call returns
    // the caller's incoming eax unchanged
    u32 entryEax;
    __asm { mov entryEax, eax }
    if ((u32)n == 0)
        return (void*)entryEax;
    Plain3C* d = (Plain3C*)dst;
    Plain3C* v = (Plain3C*)value;
    for (u32 i = (u32)n; i != 0; --i, ++d) {
        if (d == 0) break;
        *d = *v;
    }
    // the original keeps the cursor pre-biased by +0x10 and hands it back in eax
    return (char*)d + 0x10;
}

// ===========================================================================
// @ 0x00747eb0 : eastl::make_heap<cOccluder*, Compare>
struct Occluder { float a, b, c, d, e, f; };
typedef bool (__cdecl* OccluderCmp)(const Occluder&, const Occluder&);
void AdjustHeapOccluder(Occluder* first, int top, int size, int pos, Occluder value, OccluderCmp cmp);
void MakeHeapOccluder(Occluder* first, Occluder* last, OccluderCmp compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            AdjustHeapOccluder(first, parentPosition, heapSize, parentPosition,
                               *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}

// @ 0x00747f30 : eastl::sort_heap<cOccluder*, Compare>
struct Occluder4 { float a, b, c, d, e, f; };
void PopHeapOccluder(Occluder4* first, Occluder4* last, OccluderCmp compare)
{
    for (; (last - first) > 1; --last) {
        Occluder4 temp(*(last - 1));
        *(last - 1) = *first;
        int n = (int)(last - first) - 1;
        AdjustHeapOccluder((Occluder*)first, 0, n, 0, *(Occluder*)&temp, compare);
    }
}
void SortHeapOccluder(Occluder4* first, Occluder4* last, OccluderCmp compare)
{
    PopHeapOccluder(first, last, compare);
}

// make_heap (0x00748010) / sort_heap (0x00748060) for the 8-byte pair (greater)
struct FKP { float x, y; FKP() {} FKP(const FKP& v) { x = v.x; y = v.y; } };
struct CmpGt { bool operator()(const FKP& a, const FKP& b) const { return a.y > b.y; } };
struct CmpLt { bool operator()(const FKP& a, const FKP& b) const { return a.y < b.y; } };
// @ 0x00748010
void MakeHeapGt(FKP* first, FKP* last, u32 compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e00(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, compare);
        } while (parentPosition != 0);
    }
}
// @ 0x00748060
void SortHeapGt(FKP* first, FKP* last, u32 compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e00(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, compare);
    }
}
// make_heap (0x007480c0) / sort_heap (0x00748110) for the 8-byte pair (less)
// @ 0x007480c0
void MakeHeapLt(FKP* first, FKP* last, u32 compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e80(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, compare);
        } while (parentPosition != 0);
    }
}
// @ 0x00748110
void SortHeapLt(FKP* first, FKP* last, u32 compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e80(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, compare);
    }
}

// @ 0x00748170 : uninitialized_copy of 0x3c-byte plain (non-refcounted) elements
void FUN_00748170(int* first, int* last, int* dst)
{
    for (; first != last; first += 0xf, dst += 0xf) {
        if (dst) {
            dst[0] = first[0];
            *(short*)(dst + 1) = *(short*)(first + 1);
            *(short*)((char*)dst + 6) = *(short*)((char*)first + 6);
            dst[2] = first[2];
            dst[3] = first[3];
            dst[4] = first[4];
            dst[5] = first[5];
            dst[6] = first[6];
            dst[7] = first[7];
            dst[8] = first[8];
            dst[9] = first[9];
            dst[10] = first[10];
            dst[11] = first[11];
            dst[12] = first[12];
            dst[13] = first[13];
            dst[14] = first[14];
        }
    }
}

// deque iterator passed by value: {current, block begin, block end, map slot}
struct DequeIter { char* cur; char* begin; char* end; char** map; };
// 0x1c-byte refcounted element: key, object (+4), five dwords (+8..+0x18)
struct RCElem3C { u32 key; RCObj* obj; u32 f0, f1, f2, f3, f4; };
static inline void AddRefRaw(RCObj* o)
{
    if (o) (*(void(__thiscall**)(RCObj*))(*(void***)o)[0])(o);
}
static inline void ReleaseRaw(RCObj* o)
{
    if (o) (*(void(__thiscall**)(RCObj*))(*(void***)o)[1])(o);
}
static inline void CopyElem3C(RCElem3C* d, const RCElem3C* s)
{
    d->key = s->key;
    RCObj* o = s->obj;
    RCObj* old = d->obj;
    if (o != old) {
        AddRefRaw(o);
        d->obj = o;
        ReleaseRaw(old);
    }
    d->f0 = s->f0;
    d->f1 = s->f1;
    d->f2 = s->f2;
    d->f3 = s->f3;
    d->f4 = s->f4;
}

// @ 0x00748280 : deque uninitialized_copy
// three iterators are passed by value: {current, block begin, block end, map slot}
DequeIter* FUN_00748280(DequeIter* out,
                        char* fcur, char* fbeg, char* fend, char** fmap,
                        char* lcur, char* lbeg, char* lend, char** lmap,
                        char* rcur, char* rbeg, char* rend, char** rmap)
{
    DequeIter first = { fcur, fbeg, fend, fmap };
    DequeIter last = { lcur, lbeg, lend, lmap };
    DequeIter result = { rcur, rbeg, rend, rmap };
    while (first.cur != last.cur) {
        CopyElem3C((RCElem3C*)result.cur, (const RCElem3C*)first.cur);
        result.cur += 0x1c;
        if (result.cur == result.end) {
            result.map += 1;
            char* nb = *result.map;
            result.cur = nb;
            result.begin = nb;
            result.end = nb + 0xe0;
        }
        first.cur += 0x1c;
        if (first.cur == first.end) {
            first.map += 1;
            char* nb = *first.map;
            first.cur = nb;
            first.begin = nb;
            first.end = nb + 0xe0;
        }
    }
    out->cur = result.cur;
    out->begin = result.begin;
    out->end = result.end;
    out->map = result.map;
    return out;
}

// @ 0x00748380 : deque copy_backward
DequeIter* FUN_00748380(DequeIter* out,
                        char* fcur, char* fbeg, char* fend, char** fmap,
                        char* lcur, char* lbeg, char* lend, char** lmap,
                        char* rcur, char* rbeg, char* rend, char** rmap)
{
    DequeIter first = { fcur, fbeg, fend, fmap };
    DequeIter src = { lcur, lbeg, lend, lmap };
    DequeIter dst = { rcur, rbeg, rend, rmap };
    if (src.cur != first.cur) {
        for (;;) {
            if (src.cur == src.begin) {
                src.map -= 1;
                char* nb = *src.map;
                src.begin = nb;
                src.end = nb + 0xe0;
                src.cur = src.end;
            }
            src.cur -= 0x1c;
            if (dst.cur == dst.begin) {
                dst.map -= 1;
                char* nb = *dst.map;
                dst.begin = nb;
                dst.end = nb + 0xe0;
                dst.cur = dst.end;
            }
            dst.cur -= 0x1c;
            CopyElem3C((RCElem3C*)dst.cur, (const RCElem3C*)src.cur);
            if (src.cur == first.cur) break;
        }
    }
    out->cur = dst.cur;
    out->begin = dst.begin;
    out->end = dst.end;
    out->map = dst.map;
    return out;
}

// @ 0x00748470 : copy_backward of 0x1c-byte refcounted elements
int* FUN_00748470(int first, int last, int* dst)
{
    if (last == first) return dst;
    int* result = dst;
    int src = last - 0x1c;
    do {
        int* d = dst - 7;
        d[0] = *(int*)(src);
        RCObj* so = *(RCObj**)(src + 4);
        RCObj* old = (RCObj*)dst[-6];
        if (so != old) {
            if (so) (*(void(__thiscall**)(RCObj*))(*(void**)so))(so);
            dst[-6] = (int)so;
            if (old) RelObj(old);
        }
        d[1] = *(int*)(src + 8);
        d[2] = *(int*)(src + 0xc);
        d[3] = *(int*)(src + 0x10);
        d[4] = *(int*)(src + 0x14);
        d[5] = *(int*)(src + 0x18);
        result = d;
        dst = d;
        last = src;
        src = last - 0x1c;
    } while (last != first);
    return result;
}

// @ 0x00748530 : anonymous-namespace FilterModelSphere
struct CullModel {
    unsigned char pad0[0x0c];
    uint32_t mFlags;         // +0x0c
    unsigned char mXformSrc[0x4c - 0x10];  // +0x10  source transform copied into the local
    uint32_t mMaskA;         // +0x4c
    uint32_t mMaskB;         // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;       // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;           // +0x74
    float mBoxMinX;          // +0x78
    unsigned char pad7c[0x84 - 0x7c];
    float mBoxMaxX;          // +0x84
    unsigned char pad88[0x9c - 0x88];
    void* mInst1;            // +0x9c
    unsigned char pada0[0xac - 0xa0];
    void* mInst2;            // +0xac
    unsigned char padb0[0xe4 - 0xb0];
    unsigned char mTransform[0x38]; // +0xe4
};
// callback slot: the original loads `model+8` into ecx *and* pushes it as a stack argument,
// so model it as a __fastcall call whose this is `model+8` and whose first stack argument is
// also `model+8` (the literal 0 dummy occupies edx).
typedef bool (__fastcall *CbFn)(void* self, int dummy, void* arg);
struct SphereArg {
    uint32_t a, b, c, d;
    CbFn cb;
    unsigned char e, f;
};
bool FilterModelSphere(CullModel* model, float* pos, float radius, SphereArg* arg)
{
    cSPTransform local;
    local.mFlags = 0;
    local.mModificationCount = 0;
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, 0, &g_f162ec4c);
    if (!(model->mFlags & 1)) return 1;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskA & arg->a) != 0 || (model->mMaskB & arg->b) != 0))
        return 1;
    if ((model->mMaskA & arg->c) != 0 || (model->mMaskB & arg->d) != 0)
        return 1;
    if (arg->cb != 0 && !arg->cb((char*)model + 8, 0, (char*)model + 8))
        return 1;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;
    cSPTransform_Assign(&local, 0, model->mXformSrc);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float dx = pos[0] - local.mTranslation.x;
    float dy = pos[1] - local.mTranslation.y;
    float dz = pos[2] - local.mTranslation.z;
    float reach = model->mRadius * local.mScale + radius;
    if (reach * reach <= dx * dx + dy * dy + dz * dz) return 1;
    if (b >= 3 && model->mInst1 != 0 && *(int*)((char*)model->mInst1 + 0xcc) != 0) {
        Vec3 v;
        translateTransform(&v, model->mTransform, &local);
        return cModelInstance_PickLine(model->mInst1, 0, pos, radius, &v, b == 3) == 0;
    }
    if (b >= 2 && model->mInst2 != 0 && *(int*)((char*)model->mInst2 + 0xcc) != 0) {
        Vec3 v;
        translateTransform(&v, model->mTransform, &local);
        return cModelInstance_PickLine(model->mInst2, 0, pos, radius, &v, 1) == 0;
    }
    if (b >= 1 && model->mBoxMinX <= model->mBoxMaxX) {
        Vec3 v = *(Vec3*)pos;
        cSPTransform_BackTransformPoint(&local, 0, &v);
        float r = (local.mScale == g_f1485720) ? radius : radius / local.mScale;
        return FUN_00743fb0(&v, r, &model->mBoxMinX) == 0;
    }
    return 0;
}
