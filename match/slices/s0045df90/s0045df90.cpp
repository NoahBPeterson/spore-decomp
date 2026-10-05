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
// @ 0x45df90  large mesh/skin builder  (PARTIAL)
// =====================================================================
void FUN_0045df90(int a, int b, void* out)
{
    (void)a; (void)b; (void)out;
    return;
}
