// Slice s006f7430: cFilterChain render-state wrappers, uninitialized_copy of a 0x28-byte
// element and filter-chain teardown/registration helpers.
// Region 0x6f7430-0x6f8370. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_006f43e0(void* a, void* b, void* c);
// thiscall callees (ret 8 / this in ecx)
struct cRefPtrVec {
    void ReleaseRange(void* b, void* e);    // 0x0070f520
};
struct cFilterChainSelf {
    void RemoveCameraTextures();            // 0x006f6910
};
struct cHashtableStr {
    void DoFreeNodes(void* b, void* e);     // 0x00693230
};
struct cHashtableKey {
    void DoFreeNodes(void* b, void* e);     // 0x007611f0
};


struct cVecBool {
    void Assign(void* src);   // 0x6f6770
};

// @ 0x006f8140  (uninitialized_copy of 0x28-byte elements)
char* FUN_006f8140(char* first, char* last, char* dest) {
    if (first != last) {
        do {
            dest[0] = first[0];
            dest[1] = first[1];
            *(int*)(dest + 8) = *(int*)(first + 8);
            *(int*)(dest + 0xc) = *(int*)(first + 0xc);
            ((cVecBool*)(dest + 0x10))->Assign(first + 0x10);
            first += 0x28;
            dest += 0x28;
        } while (first != last);
    }
    return dest;
}

// @ 0x006f8190
void __fastcall FUN_006f8190(int self) {
    ((cFilterChainSelf*)self)->RemoveCameraTextures();
    int* v = (int*)(self + 0x78);
    unsigned i = 0;
    if ((*(int*)(self + 0x7c) - *v) >> 2 != 0) {
        do {
            int* p = (int*)(*v + i * 4);
            int obj = *p;
            if (obj != 0) {
                *p = 0;
                volatile long* rc = (volatile long*)(obj + 8);
                _InterlockedExchangeAdd(rc, -1);
                long c = _InterlockedExchangeAdd(rc, 0);
                if (c < 1) _InterlockedExchangeAdd(rc, 1);
            }
            i++;
        } while (i < (unsigned)(*(int*)(self + 0x7c) - *v >> 2));
    }
    int begin = *v;
    int end = *(int*)(self + 0x7c);
    void* r = FUN_006f43e0((void*)end, (void*)end, (void*)begin);
    ((cRefPtrVec*)v)->ReleaseRange(r, *(void**)(self + 0x7c));
    *(int*)(self + 0x7c) = *(int*)(self + 0x7c) + (end - begin >> 2) * -4;
    ((cHashtableStr*)(self + 0xc))->DoFreeNodes(*(void**)(self + 0x10), *(void**)(self + 0x14));
    *(void**)(self + 0x18) = 0;
    ((cHashtableKey*)(self + 0x2c))->DoFreeNodes(*(void**)(self + 0x30), *(void**)(self + 0x34));
    *(void**)(self + 0x38) = 0;
}


// ---- shared shapes for the cFilterChain parameter wrappers ---------------------------------
typedef unsigned long long u64;
inline void* operator new(unsigned, void* p) { return p; }

void __cdecl FreeBlock(void* p) throw();   // 0xf47380 operator delete[]

struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} Vec2(const Vec2& o) : x(o.x), y(o.y) {} };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };

// Lookup tables of the filter script (indexed by a script byte, 0xff = absent).
struct FilterTables {
    char   pad0[0x28];
    float* floats;   // +0x28
    char   pad1[0x10];
    Vec3*  vec3s;    // +0x3c
    char   pad2[0x10];
    Vec2*  vec2s;    // +0x50
    char   pad3[0x10];
    u64*   keys;     // +0x64
};
struct FilterOp {
    char                  pad[0x10];
    const unsigned char*  s;   // +0x10 script bytes
};

struct ShaderConsts {
    void __thiscall SetShConst(int index, float a, float b, float c, float d);  // 0x77ca20
};

// Stack fixed_vector<u64, 8>: header {begin,end,cap,pad,pool,alloc} then the inline buffer.
struct FixedVec64 {
    u64*     mpBegin;
    u64*     mpEnd;
    u64*     mpCap;
    uint32_t mPad;
    void*    mpPool;
    uint32_t mAlloc;
    __declspec(align(8)) u64 mBuf[8];

    FixedVec64() { mpPool = mBuf; mpBegin = mpEnd = mBuf; mpCap = mBuf + 8; }
    ~FixedVec64() {
        if (mpBegin && mpBegin != mpPool) FreeBlock(mpBegin);
    }
    void DoInsertValue(u64* pos, const u64& v);   // 0x595870
    void push_back(const u64& v) {
        u64 x = v;
        if (mpEnd < mpCap) { u64* p = mpEnd; mpEnd = p + 1; if (p) *p = x; }
        else DoInsertValue(mpEnd, x);
    }
};

struct cFilterChain {
    char         pad0[0x10];
    ShaderConsts mShader;            // +0x10
    char         pad1[0x127];
    float**      mpStrength;         // +0x138
    char         pad2[0x14];
    float        mOut150;            // +0x150
    char         pad3[4];
    float        mOut158;            // +0x158
    char         pad4[0x14];
    float        mf170;              // +0x170
    char         pad5[0x10];
    unsigned char mbOut184;          // +0x184
    char         pad6[0x1f];
    unsigned char mbF1a4;            // +0x1a4
    char         pad7[3];
    float        mOut1a8;            // +0x1a8
    char         pad8[0x10];
    unsigned char mbFlags[12];       // +0x1bc
    float        mVals[12];          // +0x1c8
    unsigned char mbLoaded;          // +0x1f8

    // 0x6f54a0: submit one filter pass with its key and the packed key array.
    void __thiscall Submit(u64 mode, int a, int b, int c, const u64* keys, int nKeys, int d, short e);
    float __thiscall GetDistanceToPlane();   // 0x6f4580
    float __thiscall DistanceQuery();        // 0x6f46f0
    float __thiscall GetPositionLength();    // 0x6f4930

    void Wrapper8c(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);   // 0x6f7430
    void Wrapper200(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);  // 0x6f7680
    void Dispatch(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);    // 0x6f79a0
    void ApplyStrengthFilter(FilterTables* t, FilterOp* op, int a, int b, int c, int d, short e); // 0x6f7f70
};

// @ 0x006f7430
void cFilterChain::Wrapper8c(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e) {
    const unsigned char* s = op->s;
    float f1 = 0.0f, f2 = 0.0f;
    float px = 0.0f, py = 0.0f;
    float qx = 1.0f, qy = 1.0f;
    float f3 = 10.0f;
    unsigned short i;
    i = s[1]; if (i != 0xff) f1 = t->floats[i];
    i = s[2]; if (i != 0xff) f2 = t->floats[i];
    i = s[3]; if (i != 0xff) f3 = t->floats[i];
    i = s[4]; if (i != 0xff) { Vec2 w = t->vec2s[i]; px = w.x; py = w.y; }
    i = s[5]; if (i != 0xff) { Vec2 w = t->vec2s[i]; qx = w.x; qy = w.y; }
    mShader.SetShConst(0, f1, f2, f3, f3);
    mShader.SetShConst(1, px, py, qx, qy);
    FixedVec64 v;
    i = op->s[0];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(0x8c, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f7680
void cFilterChain::Wrapper200(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e) {
    const unsigned char* s = op->s;
    float g1 = 1.0f, g2 = 1.0f;
    float px = 1.0f, py = 1.0f;
    float vx = 1.0f, vy = 1.0f, vz = 1.0f;
    float wx = 0.0f, wy = 0.0f;
    float g3 = 0.0f, g4 = 0.0f;
    u64 mode = 200;
    unsigned short i;
    i = s[1]; if (i != 0xff) g1 = t->floats[i];
    i = s[2]; if (i != 0xff) g2 = t->floats[i];
    i = s[7]; if (i != 0xff) g3 = t->floats[i];
    i = s[8]; if (i != 0xff) g4 = t->floats[i];
    i = s[3]; if (i != 0xff) { Vec2 w = t->vec2s[i]; px = w.x; py = w.y; }
    i = s[4];
    if (i != 0xff) {
        mode = 201;
        Vec3 w = t->vec3s[i];
        vx = w.x; vy = w.y; vz = w.z;
    }
    if (s[5]) mode++;
    i = s[6]; if (i != 0xff) { Vec2 w = t->vec2s[i]; wx = w.x; wy = w.y; }
    mShader.SetShConst(0, g1, g2, px, py);
    mShader.SetShConst(1, vx, vy, vz, 0.0f);
    mShader.SetShConst(3, wx, wy, g3, g4);
    FixedVec64 v;
    i = op->s[0];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(mode, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f7f70
void cFilterChain::ApplyStrengthFilter(FilterTables* t, FilterOp* op, int a, int b, int c, int d, short e) {
    const unsigned char* s = op->s;
    float scale = 1.0f;
    unsigned short i = s[0];
    if (i != 0xff) scale = t->floats[i];
    float strength = *mpStrength[e] / scale;
    if (s[1]) strength = 1.0f - strength;
    mShader.SetShConst(0, strength, 0.0f, 0.0f, 0.0f);
    mShader.SetShConst(1, 0.0f, 0.0f, 0.0f, 0.0f);
    mShader.SetShConst(3, 0.0f, 0.0f, 0.0f, 0.0f);
    FixedVec64 v;
    i = op->s[3];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(0xa399efc5ULL, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f79a0
void cFilterChain::Dispatch(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e) {
    float lo, hi;
    float f[12];
    f[0] = 0.0f;
    f[1] = 0.0f;
    f[2] = 0.0f;
    f[3] = 0.0f;
    f[4] = 0.0f;
    f[5] = 0.0f;
    f[6] = 0.0f;
    f[7] = 0.0f;
    f[8] = 0.0f;
    f[9] = 0.0f;
    f[10] = 0.0f;
    f[11] = 0.0f;
    u64 mode = 0;
    const unsigned char* s = op->s;
    unsigned short i = s[0];
    if (i != 0xff) mode = t->keys[i];
    for (int k = 0; k < 8; k++) {
        i = s[5 + k];
        if (i != 0xff) f[k] = t->floats[i];
    }
    if (s[0xf]) {
        f[8] = GetDistanceToPlane();
        if (mf170 == 1.0f) mf170 = 1.1f;
        f[9] = mf170;
    }
    if (op->s[0x10]) f[10] = DistanceQuery();
    if (op->s[0x11] && !mbLoaded) {
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 6; k++)
                if (mbFlags[j * 6 + k]) f[j * 6 + k] = mVals[j * 6 + k];
        mbLoaded = 1;
    }
    mShader.SetShConst(0, f[0], f[1], f[2], f[3]);
    mShader.SetShConst(1, f[4], f[5], f[6], f[7]);
    mShader.SetShConst(3, f[8], f[9], f[10], f[11]);
    FixedVec64 v;
    i = op->s[1];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[2];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[3];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[4];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    if (op->s[0xd]) {
        mbOut184 = 1;
        s = op->s;
        float x;
        i = s[0xe];
        if (i != 0xff) {
            x = t->floats[i];
        } else {
            lo = 500.0f; hi = 1800.0f;
            if (s[9] != 0xff) lo = f[4];
            if (s[0xa] != 0xff) hi = f[5];
            float r = (GetPositionLength() - lo) / hi;
            x = f[2] + r * (f[3] - f[2]);
        }
        mOut150 = x;
        if (!mbF1a4) mOut1a8 = f[0];
        mOut158 = f[1];
    }
    Submit(mode, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// ---- 0x006f8260: resolve a texture/resource key to an index in the chain's ref vector -------
struct HtIter { void* node; void** bucket; };
struct KeyHashtable {
    char     pad[4];
    void**   mpBuckets;     // +0x04
    unsigned mBucketCount;  // +0x08
    HtIter* find(HtIter* out, const unsigned short* key);   // 0x892970
};
struct ResRef {
    void* mp;
    ~ResRef();   // 0x576620
};
struct ResRefVec {
    ResRef* mpBegin;
    ResRef* mpEnd;
    void push_back(const ResRef& r);   // 0x420660
};
struct ResKey { unsigned lo, hi; };
struct KeyIndexMap {
    int* operator[](const ResKey& key);   // 0x6f6630
};

struct cFilterChain2 {
    char         pad0[0xc];
    KeyHashtable mTable;     // +0x0c
    char         pad1[0x14];
    KeyIndexMap  mIndex;     // +0x2c
    char         pad2[0x4b];
    ResRefVec    mRefs;      // +0x78

    bool __thiscall TryA(ResKey key, ResRef* out);   // 0x6f4500
    bool __thiscall TryB(ResKey key, ResRef* out);   // 0x6f44c0
    bool Resolve(ResKey key);                        // 0x6f8260
};

// @ 0x006f8260
bool cFilterChain2::Resolve(ResKey key) {
    if ((key.lo & key.hi) == 0xffffffffu)
        return false;
    unsigned short k = (unsigned short)key.lo;
    HtIter tmp;
    HtIter it = *mTable.find(&tmp, &k);
    HtIter e;
    e.bucket = mTable.mpBuckets + mTable.mBucketCount;
    e.node = *e.bucket;
    if (it.node == e.node) {
        ResRef ref;
        ref.mp = 0;
        if (!TryA(key, &ref) && !TryB(key, &ref))
            return false;
        mRefs.push_back(ref);
        *mIndex[key] = (int)(mRefs.mpEnd - mRefs.mpBegin) - 1;
    }
    return true;
}
// --- equivalence checker address annotations
    void Hashtable_DoFreeNodes(...); // 0x004554f0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
