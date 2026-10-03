// Entity-attached tracker helpers around 0x00437b00: local/world offset
// accessors and a placement test. Built without optimization:
// /Od /Ob1 /arch:SSE /fp:fast.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    void Assign(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Matrix3 { float m[3][3]; };
struct V3 { float x, y, z; };   // POD triple

Vector3 operator-(const Vector3& a, const Vector3& b);   // 0x0041db10
Vector3 operator*(const Vector3& a, const float& s);     // 0x0041dca0
Vector3 operator+(const Vector3& a, const Vector3& b);   // 0x0041dc10
Matrix3* __cdecl Transposed(Matrix3* out, const Matrix3* src); // 0x0041ded0
Vector3* __cdecl Transform(Vector3* out, const Vector3* v, const Matrix3* m); // 0x0041daf0
extern float kScale10;   // 10.0f at 0x01473c70

// bitset<60>: two words at the tail of Entity
struct Bits60 {
    uint32_t w[2];
    bool test(unsigned pos) const {
        if (pos < 60) {
            uint32_t word = w[pos >> 5];
            return (word & (1u << (pos % 32))) != 0;
        }
        return false;
    }
};
// bitset<32>: one word
struct Bits32 {
    uint32_t v;
    uint32_t& _Getword(unsigned pos) { return v; }
    bool test(unsigned pos) const {
        if (pos < 32) {
            uint32_t word = v;
            return (word & (1u << (pos % 32))) != 0;
        }
        return false;
    }
    void set(unsigned pos, bool val) {
        if (pos < 32) {
            if (val) _Getword(pos) |= (1u << (pos % 32));
            else     _Getword(pos) &= ~(1u << (pos % 32));
        }
    }
};

struct Model {
    char pad0[4];
    Bits32 flags;       // 4
    char pad1[8];
    void SetFlag(bool v);   // 0x00437f70
    bool GetFlag() { return flags.test(0); }
};

struct Entity {
    char pad0[0x10];
    Model* mModel;      // 0x10
    char pad1[0xdc8 - 0x14];
    Bits60 mFlags;      // 0xdc8
    Matrix3* GetRotation(Matrix3* out);   // 0x004361c0
    Model* GetModel() const { return mModel; }
    void Attach(struct Tracker* t);       // 0x00438700
};

struct Target;
struct Vec3List { V3* b; V3* e; V3* c; bool IsEmpty(); };   // 0x00526430

struct Alloc { Alloc() {} };
struct Cont { Cont(const Alloc& a); int x, y; };    // 0x00429360
struct QueryBase {
    int a, b, c;
    Cont cont;
    QueryBase(const Alloc& al) : a(0), b(0), c(0), cont(al) {}
};
struct Query : QueryBase {
    Query(const Alloc& al = Alloc()) : QueryBase(al) {}
    ~Query();                          // 0x00453eb0
    void Add(Entity** e);              // 0x004541f0
};
struct Target {
    char pad0[4];
    int mId;                            // 4
    int GetId() const { return mId; }
    bool Check(Entity* e, int part, bool flag);   // 0x004e9500
};
struct Hull { int a, b, c; };
struct Ctx { void ComputeHull(Hull* out); };      // 0x00440b90
bool __cdecl HullContains(Hull* h, V3* p);        // 0x004a9a90

Entity* __cdecl Raycast(Query* q, Vector3 from, Vector3 dir, Vector3* hitPos, Vector3* normal, int* part, bool* flag, int zero); // 0x004a4840

struct Tracker {
    char pad0[0x48];
    Vector3 mOrigin;            // 0x48
    char pad1[0x33c - 0x54];
    Entity* mEntity;            // 0x33c
    char pad2[0x378 - 0x340];
    Target* mTarget;     // 0x378
    char pad3[0x3a0 - 0x37c];
    Vector3 mOffsetA;           // 0x3a0
    Vector3 mOffsetB;           // 0x3ac
    char pad4[0x3c0 - 0x3b8];
    int mKind;                  // 0x3c0
    char pad5[0x3cc - 0x3c4];
    Vector3 mVecC;              // 0x3cc
    char pad6[0xa44 - 0x3d8];
    Vec3List mListA;            // 0xa44
    char pad7[0xb34 - 0xa50];
    Vec3List mListB;            // 0xb34

    Entity* GetEntity() const { return mEntity; }

    bool Place(Vector3 a, Vector3 b);            // 0x00437b00
    void SetOffsetA(Vector3 v, bool abs);        // 0x00437ff0
    void SetOffsetB(Vector3 v, bool abs);        // 0x004380a0
    Vector3 GetOffsetA(bool abs); // 0x00438120
    Vector3 GetOffsetB(bool abs); // 0x004381e0
    void SetVecC(Vector3 v);                     // 0x00438270
    bool HasRelevantPoints(Ctx* ctx);            // 0x004382a0
    bool HasRelevantPoints2(Ctx* ctx);           // 0x00438420
    void ApplyHit(int owner, Vector3 pos, Vector3 dir, bool f);  // 0x004370a0
    int GetKind() const { return mKind; }
};

// @ 0x00437b00
bool Tracker::Place(Vector3 a, Vector3 b)
{
    int hitId;
    Vector3 position;
    Vector3 nrm;
    Vector3 offset = Vector3(b - a * +kScale10);
    bool ok = false;
    bool hitFlag;
    Entity* owner;
    if (GetEntity()) {
        if (!GetEntity()->mFlags.test(10)) {
            if (GetEntity()->GetModel()) {
                bool restore = GetEntity()->GetModel()->GetFlag();
                GetEntity()->GetModel()->SetFlag(true);
                Query query;
                query.Add(&mEntity);
                int queryMode = (GetKind() != 0x9183dc9b) * 2 + 2;
                owner = Raycast(&query, offset, a, &position, &nrm, &hitId, &hitFlag, 0);
                if (owner) {
                    if (owner != GetEntity())
                        owner->Attach(this);
                    if (mTarget->Check(GetEntity(), hitId, hitFlag)) {
                        ApplyHit(mTarget->GetId(), position, a, false);
                        SetOffsetB(b, false);
                        ok = true;
                    }
                }
                GetEntity()->GetModel()->SetFlag(restore);
            }
        }
    }
    return ok;
}

// @ 0x00437f70
void Model::SetFlag(bool v)
{
    flags.set(0, v);
}

// @ 0x00437ff0
void Tracker::SetOffsetA(Vector3 v, bool abs)
{
    if (abs || !GetEntity()) {
        mOffsetA = v;
    } else {
        Matrix3 rot, inverse;
        Vector3 result;
        mOffsetA.Assign(*Transform(&result, &v, Transposed(&inverse, GetEntity()->GetRotation(&rot))));
    }
}

// @ 0x004380a0
void Tracker::SetOffsetB(Vector3 v, bool abs)
{
    if (abs) {
        mOffsetB = v;
    } else {
        mOffsetB.Assign(v - mOrigin);
    }
}

// @ 0x00438120
Vector3 Tracker::GetOffsetA(bool abs)
{
    if (!abs || !GetEntity()) {
        return mOffsetA;
    } else {
        Matrix3 rot;
        Vector3 result;
        return *Transform(&result, &mOffsetA, GetEntity()->GetRotation(&rot));
    }
}

// @ 0x004381e0
Vector3 Tracker::GetOffsetB(bool abs)
{
    if (!abs) {
        return mOffsetB;
    } else {
        return Vector3(mOffsetB + mOrigin);
    }
}

// @ 0x00438270
void Tracker::SetVecC(Vector3 v)
{
    mVecC = v;
}

// @ 0x004382a0
bool Tracker::HasRelevantPoints(Ctx* ctx)
{
    Vec3List* p = &mListA;
    bool a = false;
    if (p) {
        if (p->IsEmpty()) {
            a = true;
        } else {
            Hull h;
            ctx->ComputeHull(&h);
            for (int i = 0, n = (int)(p->e - p->b); i < n; i++) {
                V3 pt = p->b[i];
                if (HullContains(&h, &pt)) {
                    a = true;
                    break;
                }
            }
        }
    }
    bool b = false;
    p = &mListB;
    if (p) {
        if (p->IsEmpty()) {
            b = false;
        } else {
            Hull h;
            ctx->ComputeHull(&h);
            for (int i = 0, n = (int)(p->e - p->b); i < n; i++) {
                V3 pt = p->b[i];
                if (HullContains(&h, &pt)) {
                    b = true;
                    break;
                }
            }
        }
    }
    return (a && !b) ? 1 : 0;
}

// @ 0x00438420
bool Tracker::HasRelevantPoints2(Ctx* ctx)
{
    return HasRelevantPoints(ctx);
}
