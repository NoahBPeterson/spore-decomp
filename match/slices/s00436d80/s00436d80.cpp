// Scene object helpers (module built /Od /Ob1 /Oi /fp:fast /arch:SSE).
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return ((float*)this)[i]; }
};

struct ModelPair { int b, a; };   // locals sharing one slot pair

struct Matrix3 {
    Vector3 row[3];
};

struct BasisFrame {
    Matrix3 basis;
    Vector3 pos;
};

struct Transform {
    Matrix3 rot;
    Vector3 pos;
    float extra[2];
};

Vector3 VectorScale(const Vector3& v, const float& s);           // 0x41DCA0
Vector3 VectorAdd(const Vector3& a, const Vector3& b);           // 0x41DC10
void MatrixApply(const Transform* t, Matrix3* m);                  // 0x49EF80 (cdecl)

template <class T>
struct PtrVector {
    T** begin_;
    T** end_;
    T** cap_;
    int size() const { return (int)(end_ - begin_); }
    T*& operator[](int i) { return *(begin_ + i); }
};

struct Item {
    uint32_t pad[0x2d];
    int linked;                  // +0xb4
    void Update();               // 0x482670
};

struct ModelData {
    uint32_t pad0[4];
    int fieldA;                  // +0x10
    uint32_t pad1;
    int fieldB;                  // +0x18
    int GetA() { return fieldA; }
    int GetB() { return fieldB; }
    Transform GetTransform();    // 0x4363D0
    int FindLinked();            // 0x43C3D0 lives on the owner, see SceneObject
};

struct Anchor {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void GetBasis(Matrix3* out);   // +0xc
    bool IsActive();                       // 0x4ADC40
};

struct SceneObject;

struct Physics {
    void Attach(ModelData* model, Anchor* anchor, Vector3 pos, void* a, void* b);   // 0x4E9050
    bool Check(ModelData* model, int id, bool flag);                                 // 0x4E9500
};

struct SceneObject {
    uint32_t pad0[10];
    Anchor* anchorPtr;                      // +0x28
    uint32_t pad1[0x48 / 4 - 0x2c / 4];
    char blockA[0xa8 - 0x48];               // +0x48
    char blockB[0x33c - 0xa8];              // +0xa8
    ModelData* model;                       // +0x33c
    uint32_t pad2[(0x378 - 0x340) / 4];
    Physics* physics;                       // +0x378
    uint32_t pad3[(0x3e0 - 0x37c) / 4];
    SceneObject* child;                     // +0x3e0
    uint32_t pad4[(0x6cc - 0x3e4) / 4];
    PtrVector<Item> items;                  // +0x6cc

    ModelData* GetModel() { return model; }
    SceneObject* GetChild() { return child; }
    int GetB() { return GetModel()->GetB(); }
    int GetA() { return GetModel()->GetA(); }
    Item* ItemAt(int i) { Item** p = items.begin_ + i; return *p; }

    void Fn4380a0(Vector3 v, int zero);     // 0x4380A0
    void Fn437ff0(Vector3 v, int zero);     // 0x437FF0
    void Fn438120(Vector3* v, int one);     // 0x438120
    void Fn4381e0(Vector3* v, int one);     // 0x4381E0
    void Fn437b00(Vector3 a, Vector3 b);    // 0x437B00
    Anchor* Fn4511f0();                     // 0x4511F0
    int Fn43c3d0(int x);                    // 0x43C3D0

    void SnapToAnchor(Anchor* anchor, Vector3 offset);                       // 0x436D80
    void MoveTo(int id, Vector3 a, Vector3 b, bool flag);                    // 0x436FA0
    void Reposition(Anchor* anchor, Vector3 a, Vector3 b, bool flag);        // 0x4370A0
    void UpdateOthers(int skip, bool flag);                                  // 0x437310
};

// @ 0x00436d80
void SceneObject::SnapToAnchor(Anchor* anchor, Vector3 offset)
{
    if (GetModel()) {
        BasisFrame f;
        anchor->GetBasis(&f.basis);
        MatrixApply(&GetModel()->GetTransform(), &f.basis);
        f.pos = VectorAdd(VectorAdd(VectorScale(f.basis.row[0], offset[0]),
                                    VectorScale(f.basis.row[1], offset[1])),
                          VectorScale(f.basis.row[2], offset[2]));
        physics->Attach(GetModel(), anchor, f.pos, blockA, blockB);
        Fn4380a0(f.pos, 0);
    }
}

// @ 0x00436fa0
void SceneObject::MoveTo(int id, Vector3 a, Vector3 b, bool flag)
{
    if (GetModel() && id > -1) {
        ModelPair r;
        r.b = GetB();
        r.a = GetA();
        if (physics->Check(GetModel(), id, flag)) {
            Reposition(Fn4511f0(), a, b, true);
        }
    }
}

// @ 0x004370a0
void SceneObject::Reposition(Anchor* anchor, Vector3 a, Vector3 b, bool flag)
{
    if (GetModel() && GetB() && GetA() && anchor) {
        physics->Attach(GetModel(), anchor, a, blockA, blockB);
        Fn4380a0(a, 0);
        Fn437ff0(b, 0);
        if (flag && anchorPtr && anchorPtr->IsActive() && GetChild() && GetChild()->GetModel()) {
            Vector3 p, q;
            Fn438120(&p, 1);
            p[0] *= -1.0f;
            Fn4381e0(&q, 1);
            q[0] *= -1.0f;
            GetChild()->Fn437b00(p, q);
        }
    }
}

// @ 0x00437310
void SceneObject::UpdateOthers(int skip, bool flag)
{
    int linked = -1;
    if (flag && skip != -1) {
        if (ItemAt(skip)->linked) {
            linked = Fn43c3d0(ItemAt(skip)->linked);
        }
    }
    for (int i = 0, n = items.size(); i < n; i++) {
        if (skip != i && linked != i) {
            Item* item = ItemAt(i);
            item->Update();
        }
    }
}
