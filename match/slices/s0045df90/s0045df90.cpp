// Slice s0045df90: string geometry buffer helpers plus a large mesh builder.
// /Od /Ob1 /MD /Gy /TP.
#include "types.h"

struct DStr {
    char* begin;
    char* end;
    char* cap;
    void  trim(char* first, char* last);            // 0x45f080
    void  append(unsigned int n, int value);        // 0x45efa0
    void  resize(unsigned int n);                   // 0x45ebd0 (defined below)
};

// =====================================================================
// @ 0x45ebd0  grow / shrink a byte buffer to `n` bytes
// =====================================================================
void DStr::resize(unsigned int n)
{
    unsigned int cur = (unsigned int)(end - begin);
    if (n < cur) {
        trim(begin + n, end);
    } else if (n > cur) {
        append(n - cur, 0);
    }
    return;
}

// =====================================================================
// @ 0x45eac0  build a Matrix44 from four 16-byte rows of an object
// =====================================================================
struct V4 {
    int a;
    int b;
    int c;
    int d;
};

struct Matrix44 {
    float m[16];
    Matrix44(const void* rows)
    {
        const int* p = (const int*)rows;
        for (int i = 0; i < 16; i = i + 1) {
            ((int*)m)[i] = p[i];
        }
    }
};

__forceinline void* operator new(unsigned int, void* p) { return p; }

V4* FUN_0045edf0(V4* out, const void* src, void* arg);   // 0x45edf0

Matrix44* BuildMatrix(Matrix44* out, int obj, void* arg)
{
    V4 r3;
    V4 r2;
    V4 r1;
    V4 r0;
    FUN_0045edf0(&r3, (const char*)obj + 0x30, arg);
    FUN_0045edf0(&r2, (const char*)obj + 0x20, arg);
    FUN_0045edf0(&r1, (const char*)obj + 0x10, arg);
    FUN_0045edf0(&r0, (const char*)obj, arg);

    int rows[16];
    rows[0] = r0.a; rows[1] = r0.b; rows[2] = r0.c; rows[3] = r0.d;
    rows[4] = r1.a; rows[5] = r1.b; rows[6] = r1.c; rows[7] = r1.d;
    rows[8] = r2.a; rows[9] = r2.b; rows[10] = r2.c; rows[11] = r2.d;
    rows[12] = r3.a; rows[13] = r3.b; rows[14] = r3.c; rows[15] = r3.d;

    return new (out) Matrix44((const void*)rows);
}

// =====================================================================
// @ 0x45ec30  mesh builder  (PARTIAL)
// =====================================================================
void FUN_0045ec30()
{
    return;
}

// =====================================================================
// @ 0x45df90  rw::math::fpu::Inverse<float>(const Matrix44&, float& det)
// General 4x4 inverse: det = Determinant(m); a singular matrix returns an
// (uninitialized) default-constructed matrix, otherwise adj(m)/det built
// through the 16-float constructor.  /Od /Ob1 /arch:SSE.
// =====================================================================
namespace rw { namespace math { namespace fpu {

template <class T, int A>
struct Vector4Template {
    T mX, mY, mZ, mW;
    Vector4Template() {}
    Vector4Template(T x, T y, T z, T w) : mX(x), mY(y), mZ(z), mW(w) {}
    Vector4Template(const Vector4Template& v) : mX(v.mX), mY(v.mY), mZ(v.mZ), mW(v.mW) {}
};

template <class T, int A>
struct Matrix44Template {
    Vector4Template<T, A> xAxis, yAxis, zAxis, wAxis;
    Matrix44Template() {}
    Matrix44Template(T m00, T m01, T m02, T m03,
                     T m10, T m11, T m12, T m13,
                     T m20, T m21, T m22, T m23,
                     T m30, T m31, T m32, T m33)
        : xAxis(m00, m01, m02, m03), yAxis(m10, m11, m12, m13),
          zAxis(m20, m21, m22, m23), wAxis(m30, m31, m32, m33) {}
    // @ 0x45dca0: inline, but cl /Ob1 declines it (called out of line; its
    // reserved frame stays behind as a hole in each caller scope).
    Matrix44Template(const Matrix44Template& m)
    {
        xAxis = Vector4Template<T, A>(m.xAxis);
        yAxis = Vector4Template<T, A>(m.YAxis());
        zAxis = Vector4Template<T, A>(m.ZAxis());
        wAxis = Vector4Template<T, A>(m.WAxis());
    }
    const Vector4Template<T, A>& YAxis() const { return yAxis; }
    const Vector4Template<T, A>& ZAxis() const { return zAxis; }
    const Vector4Template<T, A>& WAxis() const { return wAxis; }
};

typedef Matrix44Template<float, 0> Matrix44f;

float Determinant(const Matrix44f& m);           // @ 0x45ec30

#define M(i) ((const float*)&m)[i]
Matrix44f Inverse(const Matrix44f& m, float& det)
{
    det = Determinant(m);
    if (det == 0.0f) {
        Matrix44f zero;
        return zero;
    } else {
        Matrix44f result(
            (((M(10) * M(15) - M(11) * M(14)) * M(5) + (M(13) * M(11) - M(9) * M(15)) * M(6)) + (M(9) * M(14) - M(13) * M(10)) * M(7)) / det,
            (((M(2) * M(15) - M(3) * M(14)) * M(9) + (M(3) * M(13) - M(1) * M(15)) * M(10)) + (M(1) * M(14) - M(2) * M(13)) * M(11)) / det,
            (((M(2) * M(7) - M(3) * M(6)) * M(13) + (M(3) * M(5) - M(1) * M(7)) * M(14)) + (M(1) * M(6) - M(2) * M(5)) * M(15)) / det,
            (((M(7) * M(10) - M(6) * M(11)) * M(1) + (M(5) * M(11) - M(7) * M(9)) * M(2)) + (M(6) * M(9) - M(5) * M(10)) * M(3)) / det,
            (((M(8) * M(15) - M(12) * M(11)) * M(6) + (M(12) * M(10) - M(8) * M(14)) * M(7)) + (M(11) * M(14) - M(10) * M(15)) * M(4)) / det,
            (((M(0) * M(15) - M(12) * M(3)) * M(10) + (M(12) * M(2) - M(0) * M(14)) * M(11)) + (M(3) * M(14) - M(2) * M(15)) * M(8)) / det,
            (((M(0) * M(7) - M(4) * M(3)) * M(14) + (M(4) * M(2) - M(0) * M(6)) * M(15)) + (M(3) * M(6) - M(2) * M(7)) * M(12)) / det,
            (((M(8) * M(7) - M(4) * M(11)) * M(2) + (M(4) * M(10) - M(8) * M(6)) * M(3)) + (M(6) * M(11) - M(7) * M(10)) * M(0)) / det,
            (((M(8) * M(13) - M(12) * M(9)) * M(7) + (M(9) * M(15) - M(13) * M(11)) * M(4)) + (M(12) * M(11) - M(8) * M(15)) * M(5)) / det,
            (((M(0) * M(13) - M(12) * M(1)) * M(11) + (M(1) * M(15) - M(3) * M(13)) * M(8)) + (M(12) * M(3) - M(0) * M(15)) * M(9)) / det,
            (((M(0) * M(5) - M(4) * M(1)) * M(15) + (M(1) * M(7) - M(3) * M(5)) * M(12)) + (M(4) * M(3) - M(0) * M(7)) * M(13)) / det,
            (((M(8) * M(5) - M(4) * M(9)) * M(3) + (M(7) * M(9) - M(5) * M(11)) * M(0)) + (M(4) * M(11) - M(8) * M(7)) * M(1)) / det,
            (((M(13) * M(10) - M(9) * M(14)) * M(4) + (M(8) * M(14) - M(12) * M(10)) * M(5)) + (M(12) * M(9) - M(8) * M(13)) * M(6)) / det,
            (((M(2) * M(13) - M(1) * M(14)) * M(8) + (M(0) * M(14) - M(12) * M(2)) * M(9)) + (M(12) * M(1) - M(0) * M(13)) * M(10)) / det,
            (((M(2) * M(5) - M(1) * M(6)) * M(12) + (M(0) * M(6) - M(4) * M(2)) * M(13)) + (M(4) * M(1) - M(0) * M(5)) * M(14)) / det,
            (((M(5) * M(10) - M(6) * M(9)) * M(0) + (M(8) * M(6) - M(4) * M(10)) * M(1)) + (M(4) * M(9) - M(8) * M(5)) * M(2)) / det);
        return result;
    }
}
#undef M

}}}
