// Flags: /Od /Ob1 /Oi /MD /Gy /TP /arch:SSE /fp:fast /GS-
// Slice s00496d30 (batch w1g0, slice 94), 0x00496d30..0x004974d8.
// /Od editor-region code.

#include "types.h"

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

char FUN_004a7e60(void* p);
char FUN_0043bd80(void* self, float f, Matrix3 m);

struct X973 {
    char pad[0xdc8];
    uint32_t flags;                       // 0xdc8
};

// @ 0x004973f0
char FUN_004973f0(X973* p, void* mat, float f, char flag) {
    char result = 0;
    if (p != 0) {
        Matrix3 m;
        if (mat == 0) {
            const float* src = (const float*)((char*)p + 0xf0);
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        } else {
            const float* src = (const float*)mat;
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        }
        result = 0;
        char r = FUN_0043bd80(p, f, m);
        if (r) {
            if ((p->flags & 1) == 0) {
                result = 1;
            } else {
                if (FUN_004a7e60(p) || flag)
                    result = 1;
            }
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00496d30: a pair of opposed ray casts through the closest point of a line to the block position.
// ---------------------------------------------------------------------------
#include <math.h>
#pragma intrinsic(fabs)

struct W {                                         // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    W() {}
    W(const W& v);                                 // 0x004098a0 (out of line)
};
struct V3 : W {
    V3() {}
    V3(const V3& v) { x = v.x; y = v.y; z = v.z; }
    V3(const W& v) { x = v.x; y = v.y; z = v.z; }
};

W operator-(const W& a, const W& b);               // 0x0041db10
W operator+(const W& a, const W& b);               // 0x0041dc10
W operator*(const W& a, const float& s);           // 0x0041dca0
W operator-(const W& v);                           // 0x00422020
float Dot3(const W* a, const W* b);                // 0x00455cc0
float VectorLength(const V3& v);                   // 0x0040ae50

inline float Abs(float v) { return (float)fabs(v); }

struct RayQuery {                                  // 0x2c bytes
    V3 mOrigin;                                    // +0x00
    V3 mDir;                                       // +0x0c
    bool mHit;                                     // +0x18
    char pad19[3];
    W mPoint;                                      // +0x1c
    float mT;                                      // +0x28
    RayQuery(V3 origin, V3 dir);                   // 0x005b1080 (ret 0x18)
    ~RayQuery();                                   // 0x00c2e4e0 (empty)
    void Cast(void* a, void* b, W origin, W dir);  // 0x005b1870 (ret 0x20)
    bool IsHit() const { return mHit; }
    W GetPoint() const { return mPoint; }
};

struct EditorBlockRay {
    char pad00[0x28];
    void* mEditorModel;                            // +0x28
    char pad2c[0x48 - 0x2c];
    V3 mPosition;                                  // +0x48
    float GetRadius();                             // 0x0043f250
};

// @ 0x00496d30
void FUN_00496d30(EditorBlockRay* self, V3 A, V3 B, V3* out1, V3* out2) {
    float unused = self->mPosition.x;
    float s = Abs((A.z * 0.99f) / B.z);
    V3 P = A + B * s;
    V3 N = -B;
    V3 Q = self->mPosition - A;
    V3 R = B * Dot3(&Q, &B) + A;
    RayQuery r1(R, B);
    RayQuery r2(R, N);
    r1.Cast(self, self, R, B);
    r2.Cast(self, self, R, N);
    *out1 = A;
    *out2 = P;
    if (r1.IsHit() && r2.IsHit()) {
        V3 Hn = r1.GetPoint() - B * self->GetRadius();
        V3 H2 = r2.GetPoint() - N * self->GetRadius();
        float len1 = VectorLength(P - H2);
        float len2 = VectorLength(P - self->mPosition);
        float len3 = VectorLength(A - Hn);
        float len4 = VectorLength(A - self->mPosition);
        *out1 = Hn;
        *out2 = H2;
    }
}
