// Slice s004364a0: Vector3 constructor, Vector3 normalize, and a
// target-direction helper. Module is /Od /Ob1 /Oi /fp:fast /arch:SSE.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;

    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    Vector3(float ax, float ay, float az) throw();
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct Matrix3 {
    Vector3 rows[3];
};

// Result of Rotate(): two vectors; only the second is consumed below.
struct RotateResult {
    Vector3 first;
    Vector3 second;
};

// Basis frame with a leading scalar (copied from the holder) followed by three axes.
struct Frame {
    uint32_t extra;
    Vector3 rows[3];
};

struct PlaceTag {};
inline void* operator new(size_t, void* p, PlaceTag) { return p; }

// Out-of-line vector math helpers (cdecl, hidden result pointer first).
Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b);     // 0x0041DB10
Vector3* Vector3_Add(Vector3* out, const Vector3* a, const Vector3* b);     // 0x0041DC10
Vector3* Vector3_Mul(Vector3* out, const Vector3* a, const Vector3* b);     // 0x0041DCA0
Vector3* Vector3_Negate(Vector3* out, const Vector3* v);                    // 0x00422020
Vector3* Vector3_Combine2(Vector3* out, const Vector3* a, const Vector3* b);// 0x0041DAF0 (_Unchecked_idl0)
Vector3* Vector3_ToLocal(Vector3* out, const Vector3* a);                   // 0x0041DED0
Vector3  Vector3_Div(const Vector3& v, const float& s);                     // 0x00453880
void     Vector3_CopyCtor(Vector3* self, const Vector3* src);               // 0x004098A0 (thiscall)
void     Matrix_Store(void* a, Matrix3* m);                                  // 0x0049EF80
RotateResult Rotate(const Vector3 a, const Vector3 b, const Vector3 c);          // 0x00499F10
Vector3  Combine(const Vector3 a, const Vector3 b, const Vector3 c, const Vector3 d); // 0x00499B40

// @ 0x00436CA0
Vector3::Vector3(float ax, float ay, float az) throw()
{
    x = ax;
    y = ay;
    z = az;
}

// @ 0x00436CE0
Vector3* Vector3_Normalize(Vector3* out, const Vector3* v)
{
    float lenSq = v->x * v->x + v->y * v->y + v->z * v->z;
    float len = sqrtf(lenSq);
    *out = Vector3_Div(*v, len);
    return out;
}

// Stub declarations for the owner objects. Offsets follow the original layout.
struct TargetObject {
    uint32_t pad0[0x12];            // 0x00
    Vector3 position;               // 0x48
    Vector3* GetAxis(Vector3* out); // thiscall, 0x004361C0 (returns out)
};

struct OrientationSource {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void GetBasis(Matrix3* out);   // vtable slot 3
};

struct BasisHolder {
    uint32_t pad[6];
    uint32_t extraField;                   // 0x18
    uint32_t GetExtra() { return extraField; }
    void* GetMatrix(void* out);            // thiscall, 0x004363D0
};

struct BasisPair {
    BasisHolder* holder;                   // 0x00
    OrientationSource* source;             // 0x04
};

struct DirectionController {
    uint32_t pad0[0x12];                   // 0x00
    Vector3 position;                      // 0x48
    uint32_t pad1[(0x33c - 0x54) / 4];     // 0x54
    TargetObject* target;                  // 0x33C
    uint32_t pad2[(0x378 - 0x340) / 4];    // 0x340
    BasisPair* basis;                      // 0x378

    Vector3* ComputeDirection(Vector3* out);
};

extern const float kOne;       // 0x01485720
extern const float kThird;     // 0x013EC46C
extern const float kZero;      // 0x01485378
extern const float kMinusOne;  // 0x013EB1BC

// @ 0x004364A0
Vector3* DirectionController::ComputeDirection(Vector3* out)
{
    TargetObject* tgt = target;
    if (!tgt) {
        out->Vector3::Vector3(kMinusOne, kMinusOne, kMinusOne);
        return out;
    }
    OrientationSource* src;
    if (basis->holder && (src = basis->source) != 0) {
        Frame frame;
        frame.extra = basis->holder->GetExtra();
        basis->source->GetBasis((Matrix3*)frame.rows);
        uint32_t held[14];
        Matrix_Store(basis->holder->GetMatrix(held), (Matrix3*)frame.rows);

        Vector3 r0 = frame.rows[0];
        Vector3 r1 = frame.rows[1];
        Vector3 r2 = frame.rows[2];

        RotateResult rot = Rotate(r0, r1, r2);
        Vector3 comb = Combine(r0, r1, r2, position);
        float sum = comb.x + comb.y + comb.z;
        if (kOne < sum) {
            Vector3 third0(kThird, kThird, kThird);
            Vector3 third1(kThird, kThird, kThird);
            Vector3 third2(kThird, kThird, kThird);
            Vector3 t0, t1, t2, s1, s2, s3, s4;
            Vector3 avg = *Vector3_Add(&s4,
                              Vector3_Add(&s3, Vector3_Mul(&t2, &r0, &third2),
                                               Vector3_Mul(&t1, &r2, &third1)),
                              Vector3_Mul(&t0, &r1, &third0));
            Vector3 tmp;
            Vector3 toTarget = *Vector3_Sub(&tmp, &avg, Vector3_Add(&s1, &position, &rot.second));
            if (toTarget.x * rot.second.x + toTarget.y * rot.second.y + toTarget.z * rot.second.z == kZero)
                toTarget = *Vector3_Sub(&s2, &target->position, &position);
            Vector3 axis, local, nrm, res;
            *out = *Vector3_Combine2(&res, Vector3_Normalize(&nrm, &toTarget),
                                     Vector3_ToLocal(&local, target->GetAxis(&axis)));
            return out;
        }
        Vector3 neg;
        *out = *Vector3_Negate(&neg, &rot.second);
        return out;
    }
    Vector3 tmp, axis, local, nrm, d;
    d = *Vector3_Sub(&tmp, &target->position, &position);
    d = *Vector3_Combine2(&nrm, Vector3_Normalize(&local, &d),
                          Vector3_ToLocal(&axis, target->GetAxis(&tmp)));
    Vector3_CopyCtor(out, &d);
    return out;
}
