// Slice s00747920 (0x00747920..0x00748530): cModelWorld load-queue / model-group
// container helpers, EASTL heap instantiations and FilterModelSphere, /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>

struct Vec3 { float x, y, z; };
struct cSPTransform {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};

// --- callees ---------------------------------------------------------------
void* operator_new(uint32_t n, const char* name, int a, int b, const char* file, int line);
void  operator_delete_(void* p);
void  FUN_007457a0(int a, int b);
void  RBTreeInsert(void* node, void* parent, void* anchor, int flag);
void  cSPTransform_Assign(void* dst, const void* src);
void* FUN_00743fb0(void* p, float f, void* box);
void  FUN_00745e00(void* first, int top, int size, int pos, float vx, float vy, void* cmp);
void  FUN_00745e80(void* first, int top, int size, int pos, float vx, float vy, void* cmp);
void  adjust_heap_occluder(void* first, int top, int size, int pos, float a, float b, float c,
                           float d, float e, float f, void* cmp);
void  translateTransform(void* out, void* a, const void* b);
int   cModelInstance_PickLine(void* inst, void* pt, float r, void* xf, bool b);
int   cSPTransform_BackTransformPoint(const void* xf, void* pt);
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720;
void Matrix3_Assign(void* dst, const void* src);

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
// @ 0x00747920 : deque< cLoadQueueEntry >::pop_back
void FUN_00747920(int self);
void FUN_00747920(int self)
{
    unsigned char* b = (unsigned char*)self;
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

// @ 0x00747980 : deque< cLoadQueueEntry >::push_back
void FUN_00747980(int* d, int* entry)
{
    RCObj* o = (RCObj*)entry[1];
    if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
    if (d[1] <= (int)((unsigned)(d[9] - *d) >> 2) + 1)
        FUN_007457a0(1, 1);
    void* blk = operator_new(0xe0, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    *(void**)(d[9] + 4) = blk;
    int* slot = (int*)d[6];
    if (slot) {
        RCObj* o2 = (RCObj*)entry[1];
        slot[0] = entry[0];
        slot[1] = (int)o2;
        if (o2) (*(void(__thiscall**)(RCObj*))(*(void**)o2))(o2);
        slot[2] = entry[2];
        slot[3] = entry[3];
        slot[4] = entry[4];
        slot[5] = entry[5];
        slot[6] = entry[6];
    }
    int m = d[9];
    d[9] = m + 4;
    int nb = *(int*)(m + 4);
    d[7] = nb;
    d[8] = nb + 0xe0;
    d[6] = d[7];
    RelObj(o);
}

// @ 0x00747ac0 : copy of a 0x38-byte record (dwords + Matrix3 copy ctor)
struct Mat3 { float m[9]; Mat3() {} Mat3(const Mat3& o) { for (int i = 0; i < 9; ++i) m[i] = o.m[i]; } };
struct Rec38 {
    int a; short b, c; int d, e, f, g;
    Mat3 rot;   // +0x18
};
Rec38* FUN_00747ac0(Rec38* dst, Rec38* src)
{
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
void FUN_00747c90(E3C* dst, int n, E3C* value)
{
    for (; n != 0; --n, dst += 1) {
        dst->key = value->key;
        RCObj* o = value->obj;
        if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
        dst->obj = o;
        dst->a = value->a;
        dst->b = value->b;
        dst->d = value->d;
        dst->e = value->e;
        dst->f = value->f;
        dst->g = value->g;
        dst->h = value->h;
        dst->i = value->i;
        dst->j = value->j;
        dst->k = value->k;
        dst->l = value->l;
        dst->m = value->m;
    }
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
    Occluder4 temp(*(last - 1));
    *(last - 1) = *first;
    int n = (int)(last - first) - 1;
    if (n > 0)
        AdjustHeapOccluder((Occluder*)first, 0, n, 0, *(Occluder*)&temp, compare);
}
void SortHeapOccluder(Occluder4* first, Occluder4* last, OccluderCmp compare)
{
    for (; (last - first) > 1; --last)
        PopHeapOccluder(first, last, compare);
}

// @ 0x00748010 / 0x00748060 : make_heap / sort_heap for the 8-byte pair (greater)
struct FKP { float x, y; FKP() {} FKP(const FKP& v) { x = v.x; y = v.y; } };
struct CmpGt { bool operator()(const FKP& a, const FKP& b) const { return a.y > b.y; } };
struct CmpLt { bool operator()(const FKP& a, const FKP& b) const { return a.y < b.y; } };
void MakeHeapGt(FKP* first, FKP* last, CmpGt compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e00(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, &compare);
        } while (parentPosition != 0);
    }
}
void SortHeapGt(FKP* first, FKP* last, CmpGt compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e00(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, &compare);
    }
}
// @ 0x007480c0 / 0x00748110 : make_heap / sort_heap for the 8-byte pair (less)
void MakeHeapLt(FKP* first, FKP* last, CmpLt compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e80(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, &compare);
        } while (parentPosition != 0);
    }
}
void SortHeapLt(FKP* first, FKP* last, CmpLt compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e80(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, &compare);
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

// @ 0x00748280 : deque uninitialized_copy
void FUN_00748280(int* out, int* first, int* a, int* last, int* mapFirst, int* mapLast)
{
    (void)a; (void)mapFirst; (void)mapLast;
    int* dst = (int*)out[0];
    for (; first != last; first += 7) {
        int* o = dst;
        o[0] = first[0];
        RCObj* src = (RCObj*)first[1];
        RCObj* d = (RCObj*)o[1];
        if (src != d) {
            if (src) (*(void(__thiscall**)(RCObj*))(*(void**)src))(src);
            o[1] = (int)src;
            if (d) RelObj(d);
        }
        o[2] = first[2]; o[3] = first[3]; o[4] = first[4]; o[5] = first[5]; o[6] = first[6];
        dst = o + 7;
    }
    out[1] = (int)dst;
}

// @ 0x00748380 : deque copy_backward
void FUN_00748380(int* out, int* last)
{
    int* dst = (int*)out[0];
    while (dst != last) {
        int* s = dst;
        int* d = s - 7;
        d[0] = s[-7];
        RCObj* src = (RCObj*)s[-6];
        RCObj* old = (RCObj*)d[1];
        if (src != old) {
            if (src) (*(void(__thiscall**)(RCObj*))(*(void**)src))(src);
            d[1] = (int)src;
            if (old) RelObj(old);
        }
        d[2] = s[-5]; d[3] = s[-4]; d[4] = s[-3]; d[5] = s[-2]; d[6] = s[-1];
        dst = d;
    }
    out[1] = (int)dst;
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
    unsigned char pad10[0x4c - 0x10];
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
struct SphereArg {
    uint32_t a, b, c, d;
    int (__cdecl* cb)(void*);
    unsigned char e, f;
};
int FilterModelSphere(CullModel* model, float* pos, SphereArg* arg)
{
    if (!(model->mFlags & 1)) return 1;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 1;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 1;
    if (arg->cb != 0 && !arg->cb((char*)model + 8))
        return 1;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;
    cSPTransform local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float dx = pos[0] - local.mTranslation.x;
    float dy = pos[1] - local.mTranslation.y;
    float dz = pos[2] - local.mTranslation.z;
    float reach = model->mRadius * local.mScale;
    if (dx * dx + dy * dy + dz * dz < reach * reach) {
        if (b != 0 && model->mBoxMinX <= model->mBoxMaxX)
            return FUN_00743fb0(pos, 0.0f, &model->mBoxMinX) == 0;
    }
    return 1;
}
