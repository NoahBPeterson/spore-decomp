// Slice s0048fde0 (batch w1g0, slice 85), 0x0048fde0..0x004909c3.
// /Od editor-region code (likely /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-).
// No PDB names exist for these VAs; member offsets come from the disassembly,
// unknown gaps are char pad[]. Callees/globals are stubbed (masked relocs).

#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
};

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

struct BoundingBox {
    Vector3 mn;
    Vector3 mx;
    BoundingBox() {}
    bool Intersects(const BoundingBox& b) const;
};

struct Tracker {
    char pad0[0x33c];
    int field33c;                         // 0x33c
    void GetOffsetA(Vector3* out, int flag);
    void GetOffsetB(Vector3* out, int flag);
    void Place();
};

struct SubMgr {
    int Count();
    void* Get(int i);
};

struct ModelType {
    void** begin;                         // 0x00
    void** end;                           // 0x04
    bool GetResourceTypeX();              // 0x00526430, thiscall
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

    bool Test();                          // 0x0044f220
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c);
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c, Vector3* extra);
    void F(Tracker* t);                   // 0x00438700
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
float Acos(float x);                                                  // 0x011e08c8
void TransformCtor(void* self);                                       // 0x00409930
void TransformSetAngleAxis(void* self, float angle, Vector3* axis);   // 0x006baba0

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
    if (block->Test() != 0)
        return;
    void** begin = block->vecBegin;
    void** end = block->vecEnd;
    for (int i = 0; i < (int)(end - begin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)begin[i];
        Tracker* t = child->tracker;
        if (t != 0 && t->field33c == 0) {
            block->F(t);
            Vector3 a, b;
            t->GetOffsetA(&a, 1);
            t->GetOffsetB(&b, 1);
            t->Place();
        } else {
            FUN_0048fde0(child);
        }
    }
}

// @ 0x0048fee0
float FUN_0048fee0(cSPEditorBlock* p, ModelType* model, Vector3* out, float scale) {
    Vector3 tmp(p->position);
    *out = tmp;
    if (model->GetResourceTypeX())
        return -1.0f;
    if (((p->bits >> 0x1b) & 1) == 0)
        return -1.0f;

    BoundingBox bb1;
    Vector3 extra;
    BoundingBox* r = p->GetBBox(&bb1, 0, 0, 0, &extra);
    Vector3 ctr = BoundingBox_GetCenter(r);
    char arr[0x20];
    SomeCtor(arr, &ctr);

    void** mbegin = model->begin;
    void** mend = model->end;
    for (int i = 0; i < (int)(mend - mbegin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mbegin[i];
        BoundingBox bb2;
        Vector3 extra2;
        BoundingBox* r2 = child->GetBBox(&bb2, 0, 0, 0, &extra2);
        Vector3 c2 = BoundingBox_GetCenter(r2);
        float dy = c2.z - extra.z;
        Vector3 v(c2);
        v.z = v.z - dy;
        float ady = dy < 0 ? -dy : dy;
        if (0.2f * scale > ady) {
            Vector3 d;
            Vector3_Sub(&d, &c2, &ctr);
            float len = VectorLength(&d);
            float f = len * ady;
            Vector3 q(tmp);
            q.z = q.z + dy;
            SomePush(arr, &f);
            (void)q;
        }
    }
    SomeMethod(arr);
    if (SomeMethod(arr))
        SomeDtor(arr);
    return -1.0f;
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
    Vector3_Normalize(&n, &n);
    float d = v0.x * n.x + v0.y * n.y + v0.z * n.z;
    float ad = d < 0 ? -d : d;
    if (ad > 1.5258789e-05f) {
        Vector3 u, w, x;
        FUN_004909d0(&u, &n, &v1);
        Vector3_Normalize(&u, &u);
        FUN_004909d0(&w, &n, &v2);
        Vector3_Normalize(&w, &w);
        Cross(&x, &u, &w);
        Vector3_Normalize(&x, &x);
        v0 = x;
        v1 = u;
        v2 = w;
        out->Assign(&v0);
    } else {
        Vector3 p;
        FUN_004909d0(&p, &n, &v1);
        Vector3_Normalize(&p, &p);
        float c = p.x * v0.x + p.y * v0.y + p.z * v0.z;
        if (c < 0.0f)
            c = 0.0f;
        if (c > 1.0f)
            c = 1.0f;
        float ang = Acos(c);
        char tf[0x28];
        TransformCtor(tf);
        Vector3 arr[3];
        arr[0] = v0;
        arr[1] = v1;
        arr[2] = v2;
        *(uint16_t*)(tf + 0) = *(uint16_t*)(tf + 0) | 2;
        *(uint16_t*)(tf + 2) = *(uint16_t*)(tf + 2) + 1;
        TransformSetAngleAxis(tf, ang, &v1);
        out->Assign(&arr[0]);
    }
    return out;
}
