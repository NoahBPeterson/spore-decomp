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
struct Vec4f;
struct cBlob {
    void F77ca20(int a, float b, float c, float d, float e);
    void F77ca20v(int a, Vec4f v);       // same function, Vec4 passed by value
};

struct RKey { unsigned lo, hi; };
struct Vec4f {
    float x, y, z, w;
    Vec4f(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4f(const Vec4f& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct cViewer {
    void SetRaster(const RKey* key, int a);   // 0x007c4be0
    void F3c50(int a);                        // 0x007c3c50
    bool Update();                            // 0x007c4fd0
    void F3c10();                             // 0x007c3c10
};
struct EmbState {                             // rw::graphics::EmbeddedState
    char pad0[0x10];
    unsigned char mDirty;                     // +0x10
    void SetRaster(int slot, void* raster);   // 0x011ee6b0
};
struct HtNode { void* mpNext; int mIdx; int mIdx2; };
struct HtIter { HtNode* mpNode; void* mpBucket; };
struct HtU16 {                                // hashtable keyed by a 16-bit id
    int mpad0;
    HtNode** mpBuckets;                       // +4
    unsigned mnBuckets;                       // +8
    HtIter* find(HtIter* out, const unsigned* key);   // 0x00892970
};
struct HtKey64 {                              // hashtable keyed by a 64-bit RKey
    int mpad0;
    HtNode** mpBuckets;
    unsigned mnBuckets;
    HtIter* find(HtIter* out, const void* key);        // 0x00a7bf40
};
struct TexRef {
    void* mpRaster;                           // +0
    unsigned mFlags;                          // +4
    void* GetRaster();                        // 0x0046f260
};
struct cRaster { char pad0[0xc]; unsigned short w, h; };
struct cStateObj {                            // per-state resource record (0x7c+ bytes)
    char pad0[8];
    unsigned short mDefaultKey;               // +0x08 (index into mKeys, 0xffff = none)
    HtU16 mById;                              // +0x0c
    char pad18[0x2c - 0x18];
    HtKey64 mByKey;                           // +0x2c
    char pad38[0x4c - 0x38];
    RKey* mKeys;                              // +0x4c
    char pad50[0x60 - 0x50];
    unsigned char* mSeen;                     // +0x60
    char pad64[0x74 - 0x64];
    unsigned char mKindSeen[4];               // +0x74
    TexRef** mTex;                            // +0x78
};
struct MatNode { int pad0; EmbState* mpState; };

struct cState {
    char pad00[0x10];
    char pad10[0x28 - 0x10];
    float* mColors;        // +0x28
    char pad2c[0x3c - 0x2c];
    char* mTbl;            // +0x3c
    char pad40[0x110 - 0x40];
    float mV[4];           // +0x110
    char pad120[0x138 - 0x120];
    cStateObj** mObjs;     // +0x138
    char pad13c[0x164 - 0x13c];
    void* mp164;           // +0x164
    void* mp168;           // +0x168

    void F54a0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, short a9);
    void Setup(EmbState* st, int n, Vec4f v);      // 0x006f4b90
    void W5f80(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6060(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W60f0(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6180(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6270(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
};

static inline void BlobCall(cState* self, int a, float b, float c, float d, float e) {
    ((cBlob*)((char*)self + 0x10))->F77ca20(a, b, c, d, e);
}

// ---- vtable-call helpers for the two interface objects at this+0x164 / this+0x168 -------
typedef void* (__thiscall *FnRes18)(void*, unsigned, unsigned);                      // mp164 +0x18
typedef void  (__thiscall *FnRes24)(void*, unsigned, unsigned, int*, int*, int*, int*); // mp164 +0x24
typedef void  (__thiscall *FnRes28)(void*, unsigned, unsigned, void*, void*);        // mp164 +0x28
typedef bool  (__thiscall *FnQ38)(void*);                                            // mp168 +0x38
typedef void* (__thiscall *FnQ50)(void*, int, int);                                  // mp168 +0x50
typedef void  (__thiscall *FnQA8)(void*, int, RKey*, int);                           // mp168 +0xa8
typedef void  (__thiscall *FnQDC)(void*, RKey*);                                     // mp168 +0xdc
typedef MatNode* (__thiscall *FnMat28)(void*, int);                                  // MaterialManager +0x28
typedef void  (__thiscall *FnMgr34)(void*, void*);                                   // manager at 0x67dd60 +0x34
static inline void** vtbl(void* p) { return *(void***)p; }

void* __cdecl MaterialManager();   // 0x0067dd70
void* __cdecl FUN_0067dd60();      // 0x0067dd60 (shares the 0x67dd.. singleton family)

// Uploads the raster whose key is (lo,hi) and sets the 4 size constants for shader const 2.
// The constants are (w, h, 1/w, 1/h).
static __forceinline void SetSizeConst(cState* self, float w, float h) {
    float iw = 1.0f / w;
    float ih = 1.0f / h;
    ((cBlob*)((char*)self + 0x10))->F77ca20v(2, Vec4f(w, h, iw, ih));
}

// @ 0x006f54a0
// render-state / texture slot binder
// a1 = material id, a3/a4 = 64-bit raster key (0 = default), a5 = state kind byte,
// a6 = table of 64-bit extra keys (a7 entries), a8 = viewer, a9 = state-object index.
void cState::F54a0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, short a9) {
    (void)a2;
    cViewer* viewer = (cViewer*)a8;
    RKey* table = (RKey*)a6;
    cStateObj* o = mObjs[(short)a9];
    unsigned char kind = (unsigned char)a5;

    if (kind == 1) {
        if (((FnQ38)vtbl(mp168)[0x38 / 4])(mp168)) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            ((FnQDC)vtbl(mp168)[0xdc / 4])(mp168, &key);
            viewer->SetRaster(&key, 1);
        }
    } else if ((unsigned char)(kind - 2) <= 3) {
        int n = kind - 2;
        void* r = ((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, n, 0);
        if (r) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            ((FnQA8)vtbl(mp168)[0xa8 / 4])(mp168, n, &key, 1);
            viewer->SetRaster(&key, 1);
            if (o->mKindSeen[n] == 0) {
                viewer->F3c50(1);
                o->mKindSeen[n] = 1;
            }
        }
    } else if (kind == 0x41) {
        if ((unsigned short)a9 == 0) {
            cStateObj* o1 = mObjs[1];
            RKey key;
            key.lo = key.hi = 0xffffffff;
            unsigned short d = o1->mDefaultKey;
            if (d != 0xffff)
                key = o1->mKeys[d];
            if (((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, key.lo, key.hi))
                viewer->SetRaster(&key, 1);
        }
    } else {
        unsigned kk = kind;
        HtIter itBuf;
        HtIter* it = o->mById.find(&itBuf, &kk);
        HtNode* node = it->mpNode;
        if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
            RKey* ent = &o->mKeys[node->mIdx];
            if (((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, ent->lo, ent->hi)) {
                viewer->SetRaster(ent, 1);
                if (o->mSeen[node->mIdx] == 0) {
                    viewer->F3c50(1);
                    o->mSeen[node->mIdx] = 1;
                }
            }
        }
    }

    if (!viewer->Update())
        return;

    FUN_00761dc0();
    void* mgr = MaterialManager();
    EmbState* st = ((FnMat28)vtbl(mgr)[0x28 / 4])(mgr, a1)->mpState;

    unsigned long long key64 = ((unsigned long long)(unsigned)a4 << 32) | (unsigned)a3;
    if ((a3 | a4) == 0) {
        if (st->mDirty & 1) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            unsigned short d = o->mDefaultKey;
            if (d != 0xffff)
                key = o->mKeys[d];
            void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, key.lo, key.hi);
            if (r) {
                int u, v, s1, s2;
                st->SetRaster(0, r);
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, key.lo, key.hi, &s2, &s1, &u, &v);
                SetSizeConst(this, (float)u, (float)v);
            }
        }
    } else if (key64 - 2 < 4) {
        if (st->mDirty & 1) {
            int n = (unsigned short)a3 - 2;
            cRaster* r = (cRaster*)((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, n, 0);
            RKey key2;
            key2.lo = key2.hi = 0xffffffff;
            ((FnQA8)vtbl(mp168)[0xa8 / 4])(mp168, n, &key2, 1);
            if (r) {
                st->SetRaster(0, r);
                SetSizeConst(this, (float)r->w, (float)r->h);
            }
        }
    } else {
        unsigned kk = (unsigned short)a3;
        HtIter itBuf;
        HtIter* it = o->mById.find(&itBuf, &kk);
        HtNode* node = it->mpNode;
        if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
            RKey* ent = &o->mKeys[node->mIdx];
            unsigned lo = ent->lo, hi = ent->hi;
            void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, lo, hi);
            if (r) {
                int u, v, s1, s2;
                st->SetRaster(0, r);
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, lo, hi, &s1, &s2, &u, &v);
                SetSizeConst(this, (float)u, (float)v);
            }
        } else {
            HtIter itBuf2;
            HtIter* it2 = o->mByKey.find(&itBuf2, &key64);
            HtNode* node2 = it2->mpNode;
            if (node2 != o->mByKey.mpBuckets[o->mByKey.mnBuckets]) {
                TexRef* t = o->mTex[node2->mIdx2];
                cRaster* r = (cRaster*)t->GetRaster();
                st->SetRaster(0, r);
                SetSizeConst(this, (float)r->w, (float)r->h);
            }
        }
    }

    unsigned count = (unsigned)a7;
    if (count - 1 < 4 && count > 0) {
        for (unsigned short k = 0; k < count; ++k) {
            RKey* e = &table[k];
            unsigned kk = (unsigned short)e->lo;
            HtIter itBuf;
            HtIter* it = o->mById.find(&itBuf, &kk);
            HtNode* node = it->mpNode;
            if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
                RKey* ent = &o->mKeys[node->mIdx];
                unsigned lo = ent->lo, hi = ent->hi;
                void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, lo, hi);
                int i0, i1, i2, i3, j0, j1;
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, lo, hi, &i0, &i1, &i2, &i3);
                ((FnRes28)vtbl(mp164)[0x28 / 4])(mp164, lo, hi, &j0, &j1);
                st->SetRaster(k + 1, r);
            } else {
                unsigned long long ek = *(unsigned long long*)e;
                if (ek > 1 && ek < 6) {
                    void* r = ((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, (int)kk - 2, 0);
                    if (r)
                        st->SetRaster(k + 1, r);
                } else {
                    HtIter itBuf2;
                    HtIter* it2 = o->mByKey.find(&itBuf2, e);
                    HtNode* node2 = it2->mpNode;
                    if (node2 != o->mByKey.mpBuckets[o->mByKey.mnBuckets]) {
                        TexRef* t = o->mTex[node2->mIdx2];
                        if (!(t->mFlags & 1)) {
                            void* m = FUN_0067dd60();
                            ((FnMgr34)vtbl(m)[0x34 / 4])(m, t);
                        }
                        st->SetRaster(k + 1, t->mpRaster);
                    }
                }
            }
        }
    }

    Setup(st, 2, Vec4f(mV[0], mV[1], mV[2], mV[3]));
    viewer->F3c10();
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
