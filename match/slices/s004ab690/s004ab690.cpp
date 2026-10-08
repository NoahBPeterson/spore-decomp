// Slice s004ab690 — cSPEditorModel teardown / block search helpers.
#include "types.h"

struct cSPEditorBlock {
    char pad0[0xdc8];
    uint32_t mFlags[4];  // +0xdc8
    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
};
struct cSPEditorModel;

extern void* g_vtbl_model_a;
extern void* g_vtbl_model_b;
extern void* g_vtbl_ability;

extern void FUN_004ad330();
extern void FUN_004fd940(void* p);
extern void WString_FreeBuffer(void* p);
extern void FUN_453540_Release(void* p);
extern void FUN_004453eb0_vector_dtor(void* p);

// @ 0x004aba00
void ModelDestructor(cSPEditorModel* self)
{
    *(void**)self = &g_vtbl_model_a;
    *(void**)((char*)self + 4) = &g_vtbl_model_b;
    FUN_004ad330();
    char* v = (char*)self + 0xc8;
    for (uint32_t i = *(uint32_t*)v; i < *(uint32_t*)(v + 4); i += 0x18) {
    }
    FUN_004fd940(v);
    WString_FreeBuffer((char*)self + 0x7c);
    WString_FreeBuffer((char*)self + 0x6c);
    WString_FreeBuffer((char*)self + 0x5c);
    void** rc = (void**)((char*)self + 0x30);
    if (*rc != 0) {
        FUN_453540_Release(*rc);
    }
    FUN_004453eb0_vector_dtor((char*)self + 0x18);
    *(void**)((char*)self + 4) = &g_vtbl_ability;
}

// @ 0x004abaf0
extern void FUN_00435be0(cSPEditorBlock* b);
extern void FUN_00449ed0();
extern void FUN_004541f0(void** p);
extern void FUN_004adfc0(int v);
void RemoveBlock(cSPEditorModel* self, cSPEditorBlock* block)
{
    if (block != 0) {
        cSPEditorBlock** begin = *(cSPEditorBlock***)((char*)self + 0x18);
        cSPEditorBlock** end = *(cSPEditorBlock***)((char*)self + 0x1c);
        cSPEditorBlock** it = begin;
        while (it != end && *it != block) {
            ++it;
        }
        if (it == end) {
            FUN_00435be0((cSPEditorBlock*)self);
            FUN_00449ed0();
            cSPEditorBlock* local = block;
            if (block != 0) {
                (*(void(**)(cSPEditorBlock*))(*(uint32_t*)block + 4))(block);
            }
            FUN_004541f0((void**)&local);
            if (local != 0) {
                (*(void(**)(cSPEditorBlock*))(*(uint32_t*)local + 8))(local);
            }
            FUN_004adfc0(1);
        }
    }
}

// @ 0x004abbc0
void* FUN_004abc50(void* self, void* a, void* b);
void* AddBlock(cSPEditorModel* self,
               float f1, float f2, float f3, unsigned int a,
               unsigned char b6, unsigned char b7, float g1, float g2, float g3)
{
    (void)f1; (void)f2; (void)f3; (void)a; (void)b6; (void)b7;
    (void)g1; (void)g2; (void)g3;
    FUN_004abc50(self, 0, 0);
    return self;
}

// @ 0x004ab690 — large routine (not reconstructed).
void* FUN_004ab690(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
    return self;
}

// @ 0x004abc50 is defined in s004ab690_find.cpp (SP::cSPEditorModel::FindClosestBlockPoint).

// @ 0x004ac480
extern double FUN_004a5bd0(cSPEditorBlock* b);
extern void* FUN_0041db10(void* out, void* p, void* arg);
extern double FUN_0040ae50(void* v);
extern float g_floatMax;
cSPEditorBlock* FindNearestFlag7Block(cSPEditorModel* self)
{
    float best = g_floatMax;
    cSPEditorBlock* result = 0;
    int count = (int)(*(uint32_t*)((char*)self + 0x1c) - *(uint32_t*)((char*)self + 0x18)) >> 2;
    for (int i = 0; i < count; ++i) {
        cSPEditorBlock* b = *(cSPEditorBlock**)(*(uint32_t*)((char*)self + 0x18) + i * 4);
        if (b->IsFlagSet(7)) {
            float d = (float)FUN_004a5bd0(b);
            float v[3];
            float* p = (float*)FUN_0041db10(v, (char*)b + 0x48, 0);
            float len = (float)FUN_0040ae50(p);
            float delta = len - d;
            if (delta < best) {
                result = b;
                best = delta;
            }
        }
    }
    return result;
}

// ===== 0x004abc50 =====
// Slice s004ab690, 0x004abc50: SP::cSPEditorModel closest-block-point search (2096 bytes, /Od /Ob1).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od module, no /EHsc).
//
// Scans every block of the model (skipping ignoreBlock, its partner and, optionally, everything
// reachable through ignoreBlock's chain) and returns the block position (point mode) or the
// bbox-weighted contact point (box mode) that is closest to / farthest from `point`.

struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : Vector3T(ax, ay, az) {}
    cSPVector3(const cSPVector3& o);                                     // 0x004098a0
    cSPVector3& operator=(const Vector3T& v) { Vector3T::operator=(v); return *this; }
};

cSPVector3 operator-(const Vector3T& a, const Vector3T& b);               // 0x0041db10
cSPVector3 operator*(const Vector3T& a, const float& s);                  // 0x0041dca0
cSPVector3 operator/(const Vector3T& a, const float& s);                  // 0x00453880
cSPVector3& operator+=(cSPVector3& a, const cSPVector3& b);              // 0x0041ddb0
float VectorLength(const Vector3T& v);                                   // 0x0040ae50
// Removes the component of v along n: v - (v.n) n   (cdecl, sret)
Vector3T ProjectOffAxis(const Vector3T& v, const Vector3T& n);          // 0x004909d0
cSPVector3 ProjectOffAxis(const cSPVector3& v, const cSPVector3& n);           // 0x004909d0

extern const cSPVector3 kZeroVec;                                          // 0x015d6a28

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    cSPVector3 GetCorner(uint32_t mask) const;                           // 0x0043f290
};

namespace SP {
struct cSPEditorModel;

struct cSPEditorBlock {
    char pad0[0x48];
    Vector3T mPosition;                                                  // +0x48
    char pad1[0x33c - 0x54];
    cSPEditorBlock* mLink33c;                                            // +0x33c
    char pad2[0x3e0 - 0x340];
    cSPEditorBlock* mPartner;                                            // +0x3e0
    const Vector3T& GetPosition() { return mPosition; }
    cSPEditorBlock* GetPartner() { return mPartner; }
    bool IsInChain(cSPEditorBlock* other);                               // 0x0044a9a0
    cSPBoundingBox GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};

template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};

template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    int size() { return (int)(mpEnd - mpBegin); }
    T& operator[](int n) { return *(mpBegin + n); }
};

struct cSPEditorModel {
    char pad0[0x18];
    vector<AutoRefCount<cSPEditorBlock> > mBlockList;                                  // +0x18

    cSPVector3 FindClosestBlockPoint(cSPVector3 point, cSPEditorBlock* ignoreBlock, cSPVector3 axis,
                                   bool findNearest, bool usePositions, bool flatten, bool useChain);
};

// @ 0x004abc50
cSPVector3 cSPEditorModel::FindClosestBlockPoint(cSPVector3 point, cSPEditorBlock* ignoreBlock, cSPVector3 axis,
                                               bool findNearest, bool usePositions, bool flatten, bool useChain)
{
    cSPVector3 target(flatten ? ProjectOffAxis(point, axis) : point);
    float best = findNearest ? 1000000.0f : -1000000.0f;
    cSPVector3 bestPos(-1.0f, -1.0f, -1.0f);

    for (int i = 0, count = mBlockList.size(); i < count; i++) {
        cSPEditorBlock* blk = mBlockList[i];
        bool skip = false;
        if (useChain) {
            skip = ignoreBlock ? ignoreBlock->IsInChain(blk) : false;
            if (!skip) {
                if (ignoreBlock->GetPartner())
                    skip = ignoreBlock->GetPartner()->IsInChain(blk);
            }
        } else {
            skip = ignoreBlock == blk;
            if (!skip) {
                if (ignoreBlock->GetPartner())
                    skip = ignoreBlock->GetPartner() == blk;
            }
        }
        if (!skip) {
            if (usePositions) {
                Vector3T pos(blk->GetPosition());
                Vector3T posT(flatten ? ProjectOffAxis(pos, axis) : pos);
                float dist = VectorLength(posT - target);
                if (findNearest) {
                    if (best > dist) { best = dist; bestPos = pos; }
                } else {
                    if (dist > best) { best = dist; bestPos = pos; }
                }
            } else {
                cSPBoundingBox box = blk->GetBBox(0, true, false);
                float totalWeight = 0.0f;
                Vector3T center(blk->GetPosition());
                if (flatten)
                    center = ProjectOffAxis(center, axis);
                Vector3T toCenter(target - center);
                Vector3T extent(box.mMin - box.mMax);
                float reach = VectorLength(toCenter) + VectorLength(extent);
                float weights[8];
                for (int k = 0; k < 8; k++) {
                    cSPVector3 corner = box.GetCorner(k);
                    cSPVector3 cornerT(flatten ? ProjectOffAxis(corner, axis) : corner);
                    Vector3T rel(corner - center);
                    float w = -1.0f;
                    if (rel.x * toCenter.x + rel.y * toCenter.y + rel.z * toCenter.z > 0.0f) {
                        w = reach - VectorLength(cornerT - target);
                        totalWeight += w;
                    }
                    weights[k] = w;
                }
                cSPVector3 acc(kZeroVec);
                for (int k = 0; k < 8; k++) {
                    if (weights[k] > 0.0f) {
                        acc += box.GetCorner(k) * weights[k] / totalWeight;
                    }
                }
                cSPVector3 off = target - acc;
                float dist = VectorLength(off);
                if (findNearest) {
                    if (best > dist) { best = dist; bestPos = acc; }
                } else {
                    if (dist > best) { best = dist; bestPos = acc; }
                }
            }
        }
    }
    return bestPos;
}

}  // namespace SP
