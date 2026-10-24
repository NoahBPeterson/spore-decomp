// Slice s0048fde0 (batch w1g0, slice 85), 0x0048fde0..0x004909c3.
// /Od editor-region code (likely /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-).
// No PDB names exist for these VAs; member offsets come from the disassembly,
// unknown gaps are char pad[]. Callees/globals are stubbed (masked relocs).

#include "types.h"
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include <math.h>
#pragma intrinsic(acos)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
};

struct Matrix3 {
    float m[9];
    void Assign(const void* src);          // 0x0041cb40
};

struct Transform {
    uint16_t flags;                        // 0x00
    uint16_t field2;                       // 0x02
    uint8_t pad0[0x14 - 0x04];
    Matrix3 matrix;                        // 0x14
    void Init();                           // 0x00409930
    void SetAngleAxis(Vector3* axis, float angle); // 0x006baba0
};

struct BoundingBox {
    Vector3 mn;
    Vector3 mx;
    BoundingBox() {}
    bool Intersects(const BoundingBox& b) const;
    void GetCenter(Vector3* out) const;    // 0x00409b90
};

struct WeightedPoint {
    float weight;                          // 0x00
    Vector3 pos;                           // 0x04
};

struct VSet {
    WeightedPoint* begin;                  // 0x00
    WeightedPoint* end;                    // 0x04
    WeightedPoint* cap;                    // 0x08
    uint32_t alloc0;                       // 0x0c
    uint32_t alloc1;                       // 0x10
    VSet(const void* alloc);               // 0x00540470
    ~VSet();                               // 0x004748c0
    void push_back(const WeightedPoint& wp); // 0x004a9e40
    bool empty();                          // 0x00526430
};

struct Tracker {
    char pad0[0x33c];
    int field33c;                          // 0x33c
    char pad1[0x3a0 - 0x340];
    Vector3 dir;                           // 0x3a0
    Vector3 off;                           // 0x3ac
    void GetOffsetB(Vector3* out, char flag);               // 0x004381e0
    void GetTrianglePickDirection(Vector3* out, char flag); // 0x00438120
    void PlaceHandlesBaseOnPinning(Vector3 a, Vector3 b);   // 0x00437b00
};

struct SubMgr {
    int Count();
    void* Get(int i);
};

struct ModelType {
    void** begin;                         // 0x00
    void** end;                           // 0x04
    bool empty();                         // 0x00526430, thiscall
};

struct cSPEditorBlock {
    char pad0[0x28];
    SubMgr* mgr;                          // 0x28
    char pad1[0x48 - 0x2c];
    Vector3 position;                     // 0x48
    char pad2[0x33c - 0x54];
    int field33c;                         // 0x33c
    void** vecBegin;                      // 0x340
    void** vecEnd;                        // 0x344
    char pad3[0x3e0 - 0x348];
    Tracker* tracker;                     // 0x3e0
    void* field3e4;                       // 0x3e4
    char pad4[0xdc8 - 0x3e8];
    uint32_t bits;                        // 0xdc8

    int GetSymmetrySign();                // 0x0044f220
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c);
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c, Vector3* extra);
    void AddChild(Tracker* t);            // 0x00438700
    bool F1(cSPEditorBlock* c, int type); // 0x00438440
    bool F2(cSPEditorBlock* c);           // 0x00438420
};

struct PtrBag {
    void Insert(void** pp);               // 0x004541f0, thiscall
};

struct IRefCounted {
    virtual void Slot0();
    virtual void AddRef();
    virtual void Release();
};

// ---- stub external helpers -------------------------------------------------
void Vector3_CopyCtor(Vector3* dst, const Vector3* src);              // 0x004098a0
void Vector3_Normalize(Vector3* out, const Vector3* in);              // 0x00436ce0
Vector3* Cross(Vector3* out, const Vector3* a, const Vector3* b);     // 0x0044e460
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v); // 0x0041de40
Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b); // 0x0041db10
float VectorLength(const Vector3* v);                                 // 0x0040ae50
void ExpandBy(BoundingBox* b, float m);                               // 0x0044ad00
void SomeCtor(void* self, void* src);                                 // 0x00540470
void SomePush(void* self, void* v);                                   // 0x004a9e40
bool SomeMethod(void* self);                                          // 0x00526430
void SomeDtor(void* self);                                            // 0x004748c0
Vector3 BoundingBox_GetCenter(BoundingBox* b);                        // 0x00409b90 (approx.)

// @ 0x004909d0
Vector3* FUN_004909d0(Vector3* out, const Vector3* a, const Vector3* b) {
    float p30 = a->Dot(*b);
    Vector3 t29;
    Vector3 n12;
    Vector3* z = Vector3_Sub(&n12, a, Vector3_Scale(&t29, &p30, b));
    *out = *z;
    return out;
}

// @ 0x0048fde0
void FUN_0048fde0(cSPEditorBlock* block) {
    if (block == 0)
        return;
    if (block->GetSymmetrySign() != 0)
        return;
    void** begin = block->vecBegin;       // 0x340
    void** end = block->vecEnd;           // 0x344
    for (int i = 0; i < (int)(end - begin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)begin[i];
        Tracker* t = child->tracker;      // 0x3e0
        if (t != 0 && t->field33c == 0) {
            block->AddChild(t);
            Vector3 off;
            t->GetOffsetB(&off, 1);
            Vector3 dir;
            t->GetTrianglePickDirection(&dir, 1);
            t->PlaceHandlesBaseOnPinning(dir, off);
        } else {
            FUN_0048fde0(child);
        }
    }
}

// @ 0x0048fee0
float FUN_0048fee0(cSPEditorBlock* p, ModelType* model, Vector3* out, float scale) {
    Vector3 tmp(p->position);             // 0x48
    *out = tmp;

    if (model->empty())                   // 0x00526430
        return -1.0f;
    if (((p->bits >> 0x1b) & 1) == 0)     // 0xdc8 bit 27
        return -1.0f;

    BoundingBox bb;
    Vector3 center;
    p->GetBBox(&bb, 0, 0, 0)->GetCenter(&center);

    char alloc;
    VSet vset(&alloc);                    // 0x00540470

    void** mbegin = model->begin;
    void** mend = model->end;
    for (int i = 0; i < (int)(mend - mbegin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mbegin[i];
        BoundingBox bb2;
        Vector3 center2;
        child->GetBBox(&bb2, 0, 0, 0)->GetCenter(&center2);

        float dy = center2.z - center.z;
        Vector3 v(center2);
        v.z = v.z - dy;
        float ady = (float)fabs((double)dy);
        if (0.2f * scale > ady) {
            Vector3 d;
            Vector3_Sub(&d, &center2, &center);
            float w = VectorLength(&d) * ady;
            Vector3 q(tmp);
            q.z = q.z + dy;
            WeightedPoint wp;
            wp.weight = w;
            wp.pos = q;
            vset.push_back(wp);           // 0x004a9e40
        }
    }

    if (vset.empty())                     // 0x00526430
        return -1.0f;

    float best = 1000000.0f;
    Vector3 q(tmp);
    for (int i = 0, n = (int)(vset.end - vset.begin); i < n; ++i) {
        if (best > vset.begin[i].weight) {
            best = vset.begin[i].weight;
            q = vset.begin[i].pos;
        }
    }
    *out = q;
    return best;
}

// @ 0x004902c0
bool FUN_004902c0(cSPEditorBlock* a, cSPEditorBlock* b) {
    if (b == 0)
        return false;
    BoundingBox bbB, bbA;
    b->GetBBox(&bbB, 0, 0, 0);
    a->GetBBox(&bbA, 0, 0, 0);
    ExpandBy(&bbB, 1.1f);
    return bbB.Intersects(bbA);
}

// @ 0x00490330
bool BoundingBox::Intersects(const BoundingBox& b) const {
    int r;
    if (mx.x < b.mn.x || b.mx.x < mn.x ||
        mx.y < b.mn.y || b.mx.y < mn.y ||
        mx.z < b.mn.z || b.mx.z < mn.z)
        r = 0;
    else
        r = 1;
    return r;
}

// @ 0x00490420
bool FUN_00490420(cSPEditorBlock* a, cSPEditorBlock* b, int type) {
    if (type == 0x1b || type == 0x1a || type == 0x35) {
        int p30 = b->field33c;
        int t29 = a->field33c;
        if (p30 == t29) {
            return true;
        } else {
            return false;
        }
    } else if (type == 0x1c || type == 0x1d) {
        int x = a->field33c;
        if (b == (cSPEditorBlock*)x) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

// @ 0x004904a0
void FUN_004904a0(cSPEditorBlock* self, void** vec, PtrBag* bag, int type) {
    if (self->mgr == 0)
        return;
    SubMgr* mgr = self->mgr;
    for (int i = 0, n = mgr->Count(); i < n; ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mgr->Get(i);
        if (child == self)
            continue;
        void** it = (void**)*vec;
        void** end = (void**)vec[1];
        while (it != end && *it != child)
            ++it;
        if (it == end) {
            if (self->F1(child, type) && FUN_00490420(self, child, type)) {
                cSPEditorBlock* tmp = child;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                bag->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            }
        }
    }
}

// @ 0x004905d0
void FUN_004905d0(cSPEditorBlock* self, void** vec, PtrBag* bag) {
    if (self->mgr == 0)
        return;
    SubMgr* mgr = self->mgr;
    for (int i = 0, n = mgr->Count(); i < n; ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mgr->Get(i);
        if (child == self)
            continue;
        void** it = (void**)*vec;
        void** end = (void**)vec[1];
        while (it != end && *it != child)
            ++it;
        if (it == end) {
            if (self->F2(child)) {
                cSPEditorBlock* tmp = child;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                bag->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            }
        }
    }
}

// @ 0x004906e0
Matrix3* FUN_004906e0(Matrix3* out, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
    Vector3 n;
    Cross(&n, &v3, &v4);
    Vector3 n2;
    Vector3_Normalize(&n2, &n);
    float d = v0.x * n2.x + v0.y * n2.y + v0.z * n2.z;
    float ad = (float)fabs((double)d);
    if (!(1.5258789e-05f >= ad)) {
        Vector3 u, w, x;
        FUN_004909d0(&u, &v1, &n2);
        Vector3_Normalize(&u, &u);
        FUN_004909d0(&w, &v2, &n2);
        Vector3_Normalize(&w, &w);
        Cross(&x, &u, &w);
        Vector3_Normalize(&x, &x);
        v0 = x;
        v1 = u;
        v2 = w;
        out->Assign(&v0);
    } else {
        Vector3 p;
        FUN_004909d0(&p, &n2, &v1);
        Vector3_Normalize(&p, &p);
        float c = p.x * v0.x + p.y * v0.y + p.z * v0.z;
        c = (c > -1.0f) ? c : -1.0f;
        c = (c < 1.0f) ? c : 1.0f;
        float ang = (float)acos((double)c);
        Transform tf;
        tf.Init();                        // 0x00409930
        tf.matrix.m[0] = v0.x;
        tf.matrix.m[1] = v0.y;
        tf.matrix.m[2] = v0.z;
        tf.matrix.m[3] = v1.x;
        tf.matrix.m[4] = v1.y;
        tf.matrix.m[5] = v1.z;
        tf.matrix.m[6] = v2.x;
        tf.matrix.m[7] = v2.y;
        tf.matrix.m[8] = v2.z;
        tf.flags = (uint16_t)(tf.flags | 2);
        tf.field2 = (uint16_t)(tf.field2 + 1);
        tf.SetAngleAxis(&v1, ang);        // 0x006baba0
        out->Assign(&tf.matrix);
    }
    return out;
}
