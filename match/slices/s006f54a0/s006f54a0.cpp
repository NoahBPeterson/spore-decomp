// Slice s006f54a0: state-dispatcher helpers around the large FUN_006f54a0 routine, a
// state-struct constructor and two vector assignments.
// Region 0x6f54a0-0x6f6430. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---- external callees -------------------------------------------------------------------
void  __cdecl FUN_007c4be0(void* p, int a);
void  __cdecl FUN_007c3c50(int a);
void  __cdecl FUN_007c3c10();
void  __cdecl FUN_00761dc0();
void  __cdecl FUN_00892970();
void* __cdecl FUN_0067dd60();
void  __cdecl FUN_0070f520(void* b, void* e);
void  __cdecl operator_delete_(void* p);
int   __cdecl FUN_006f4f30(unsigned n, int a, int b);
int   __cdecl FUN_006f4f90(unsigned n, int a, int b);
void  __cdecl FUN_00b84c80(int a, int b, int c);
void  __cdecl FUN_00951740(void** a, int b, int c, int d, int e);
void  __cdecl FUN_00ac4440(int a, int b, int c);
void  __cdecl FUN_00714bc0(void** a, int b, int c, int d, int e);
void  __cdecl memmove_(void* d, const void* s, unsigned n);

struct cColorCtx {
    char pad0[0x10];
    unsigned char* mRGB;   // +0x10
    char pad14[0x28 - 0x14];
    float* mColors;        // +0x28
    char pad2c[0x3c - 0x2c];
    char*  mTbl;           // +0x3c
};
struct cBlob {
    void F77ca20(int a, float b, float c, float d, float e);
};

struct cState {
    char pad00[0x10];
    char pad10[0x28 - 0x10];
    float* mColors;        // +0x28
    char pad2c[0x3c - 0x2c];
    char* mTbl;            // +0x3c
    char pad40[0x100];

    void F54a0(int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10);
    void W5f80(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6060(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W60f0(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6180(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6270(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
};

static inline void BlobCall(cState* self, int a, float b, float c, float d, float e) {
    ((cBlob*)((char*)self + 0x10))->F77ca20(a, b, c, d, e);
}

// @ 0x006f54a0  (large state dispatcher; skeleton, see partial.txt)
void cState::F54a0(int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10) {
    (void)p2; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7; (void)p8; (void)p9; (void)p10;
}

// @ 0x006f5f80
void cState::W5f80(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)a0;
    unsigned char* p = ctx->mRGB;
    float a = 0.0f;
    float b = 1.0f;
    int mode = 0x32;
    if (p[2] != 0) mode = 0x33;
    if (p[0] != 0xff) a = ctx->mColors[p[0]];
    if (p[1] != 0xff) b = ctx->mColors[p[1]];
    BlobCall(this, 0, a, b, 0.0f, 0.0f);
    F54a0(mode, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6060
void cState::W6060(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)a0;
    float a = 1.0f;
    unsigned short c0 = ctx->mRGB[0];
    if (c0 != 0xff) a = ctx->mColors[c0];
    BlobCall(this, 0, a, 0.0f, 0.0f, 0.0f);
    F54a0(0x50, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f60f0
void cState::W60f0(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)a0;
    float a = 1.0f;
    unsigned short c0 = ctx->mRGB[0];
    if (c0 != 0xff) a = ctx->mColors[c0];
    BlobCall(this, 0, a, 0.0f, 0.0f, 0.0f);
    F54a0(0x5a, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6180
void cState::W6180(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)a0;
    unsigned char* p = ctx->mRGB;
    float b = 1.0f, g = 1.0f, r = 1.0f;
    unsigned short c0 = p[0];
    if (c0 != 0xff) r = ctx->mColors[c0];
    unsigned short c1 = p[1];
    if (c1 != 0xff) g = ctx->mColors[c1];
    unsigned short c2 = p[2];
    if (c2 != 0xff) b = ctx->mColors[c2];
    BlobCall(this, 0, r, g, b, 0.0f);
    F54a0(100, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6270
void cState::W6270(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)a0;
    unsigned char* p = ctx->mRGB;
    int mode = 0x6e;
    float v14 = 1.0f, v18 = 1.0f, v1c = 1.0f, v20 = 1.0f;
    float v4 = 1.0f, v8 = 1.0f, vc = 1.0f, v10 = 1.0f;
    if (p[0] != 0) mode = 0x6f;
    unsigned short c1 = p[1];
    if (c1 != 0xff) v14 = ctx->mColors[c1];
    int m2 = mode;
    if (p[2] != 0) m2 = mode + 2;
    char* tbl = ctx->mTbl;
    unsigned short c3 = p[3];
    if (c3 != 0xff) {
        v18 = *(float*)(tbl + c3 * 0xc);
        v1c = *(float*)(tbl + c3 * 0xc + 4);
        v20 = *(float*)(tbl + c3 * 0xc + 8);
    }
    unsigned short c4 = p[4];
    if (c4 != 0xff) {
        v4 = *(float*)(tbl + c4 * 0xc);
        v8 = *(float*)(tbl + c4 * 0xc + 4);
        vc = *(float*)(tbl + c4 * 0xc + 8);
    }
    unsigned short c5 = p[5];
    if (c5 != 0xff) v10 = ctx->mColors[c5];
    BlobCall(this, 0, v14, v18, v1c, v20);
    BlobCall(this, 1, v4, v8, vc, v10);
    F54a0(m2, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f5ed0
void __fastcall FUN_006f5ed0(int* self) {
    self[0] = 0;
    self[1] = 0;
    *(unsigned short*)(self + 2) = 0xffff;
    self[7] = 0x3f800000;
    self[8] = 0x40000000;
    self[5] = 1;
    self[4] = (int)(self + 4);
    self[6] = 0;
    self[9] = 0;
    self[0xf] = 0x3f800000;
    self[0x10] = 0x40000000;
    self[0xe] = 0;
    self[0x11] = 0;
    self[0xd] = 1;
    self[0xc] = (int)(self + 4);
    self[0x13] = 0;
    self[0x14] = 0;
    self[0x15] = 0;
    self[0x18] = 0;
    self[0x19] = 0;
    self[0x1a] = 0;
    self[0x1e] = 0;
    self[0x1f] = 0;
    self[0x20] = 0;
}

// ---- vector helpers: skeletons (see partial.txt) ----------------------------------------
// @ 0x006f5bc0
void FUN_006f5bc0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x006f5cd0
void* FUN_006f5cd0(void* self, void* other) { (void)other; return self; }
// @ 0x006f5e00
void* FUN_006f5e00(void* self, void* other) { (void)other; return self; }
