// src/game/SPEngine/SPGraphicsFilterChain.cpp -- migrated from slice(s) s006f7430, s006f6430 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFilterChain.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cFilterChain.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

// ---- items of slice s006f6430 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete_(void* p) throw();
struct cShConstBlock {
    void SetShConst(int idx, float a, float b, float c, float d);   // 0x77ca20 (thiscall)
};
struct cVec3 {
    float x, y, z;
    cVec3(float a, float b, float c) : x(a), y(b), z(c) {}
    cVec3(const cVec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cTables {                 // arg1 of the wrappers: lookup tables
    int pad0[10];
    float* floats;               // +0x28
    int pad1[4];
    cVec3* vec3s;                // +0x3c
    int pad2[4];
    float* vec2s;                // +0x50
    int pad3[4];
    float* vec2b;                // +0x64
};
struct cDesc {                   // arg2: descriptor, +0x10 -> byte array of table indices
    int pad0[4];
    unsigned char* idx;          // +0x10
};
struct cState {
    int pad0[4];
    cShConstBlock sh;            // +0x10 (embedded; the block's address is this+0x10)
    char pad1[0x170 - 0x14];
    float f170;                  // +0x170
    char pad2[0x188 - 0x174];
    float f188, f18c, f190;      // +0x188
    void ColorBE(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void ColorDC(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    float GetDist();             // 0x6f4580
    void F54a0(unsigned long long flags, int p3, int p4, int p5, void* ptr, int count, int p6, int p7);  // 0x6f54a0
};
inline void* operator new(unsigned, void* p) { return p; }
struct cVec2 { int a; int b; cVec2() {} cVec2(const cVec2& o) : a(o.a), b(o.b) {} };
struct cFixedVec2 {              // eastl::fixed_vector<cVec2, 8> with overflow allocation
    cVec2* mpBegin; cVec2* mpEnd; cVec2* mpCap;
    int pad0; void* mpPool; int pad1;
    __declspec(align(8)) cVec2 buf[8];
    cFixedVec2() { mpPool = buf; mpBegin = mpEnd = buf; mpCap = buf + 8; }
    ~cFixedVec2() { if (mpBegin && mpBegin != mpPool) operator_delete_(mpBegin); }
    void DoInsertValue(cVec2* pos, const cVec2& v);    // 0x595870
    void push_back(const cVec2& v) {
        if (mpEnd < mpCap) { cVec2* e = mpEnd++; if (e) ::new (e) cVec2(v); }
        else DoInsertValue(mpEnd, v);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
struct cByteVec {
    unsigned char* mpBegin;   // +0
    unsigned char* mpEnd;     // +4
    unsigned char* mpCap;     // +8
    unsigned char* DoAllocateAndCopy(unsigned n, const unsigned char* f, const unsigned char* l);   // 0x426950
    void DoInsertValue(unsigned char* pos, const unsigned char& v);                                  // 0x426730
    cByteVec& Assign(const cByteVec& x);           // operator= (named so the checker can find it)
    void erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, mpEnd - last);
        mpEnd -= (last - first);
    }
    void push_back(unsigned char v) {
        if (mpEnd < mpCap) { unsigned char* e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cRectID { int a; int b; };
struct cRttMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual int  Alloc(cRectID* out, int w, int h, int fmt, int p5, int p6, int p7);   // +0x10
    virtual void Free(int a, int b);                                                    // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void Register(int a, int b, const char* name);                              // +0x48
};
cRttMgr* __cdecl GetRttMgr();   // 0x67dda0 (FUN_0067dda0)
struct cRectVec {
    cRectID* mpBegin;     // +0x4c in the chain
    cRectID* mpEnd;
    cRectID* mpCap;
    void DoInsertValue(cRectID* pos, const cRectID& v);   // 0x6ec390
    void erase(cRectID* first, cRectID* last) {
        cRectID* e = mpEnd;
        cRectID* d = first;
        for (cRectID* src = last; src != e; ++src, ++d) *d = *src;
        mpEnd -= (last - first);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void push_back(const cRectID& v) {
        if (mpEnd < mpCap) { cRectID* e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cFilterChain {
    char pad0[0x4c];
    cRectVec rects;                  // +0x4c
    char pad1[0x60 - 0x58];
    cByteVec flags;                  // +0x60
    bool AddCameraTexture(unsigned short w, unsigned short h, int* pIndex);
    void RemoveCameraTextures();
};
void* __cdecl operator new(unsigned sz, const char* tag, int a, int b, int c, int d);
struct cStateRec {
    cStateRec();                       // 0x6f5ed0
    char pad0[0x74];
    int f74;
    char pad1[0x8c - 0x78];
};
struct cViewer174 {
    cViewer174();                      // 0x7c3f70
    void Init(int a);                  // 0x7c4dd0
    char pad[0x174];
};
struct cStatePtrVec {
    cStateRec** mpBegin; cStateRec** mpEnd; cStateRec** mpCap;
    void DoInsertValue(cStateRec** pos, cStateRec* const& v);   // 0x6ec4a0
    void push_back(cStateRec* const& v) {
        if (mpEnd < mpCap) { cStateRec** e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cSvc1 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void v5(); virtual void v6(); virtual void Reset(); };          // +0x1c
struct cMsgSrv { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                 virtual void v5(); virtual void v6(); virtual void v7(); virtual void Register(void* who, int msgId); };  // +0x20
cSvc1*   __cdecl GetSvc1();            // 0x67dd50
void*    __cdecl GetSvc2();            // 0x67dda0
void*    __cdecl GetSvc3();            // 0x67dd40
cMsgSrv* __cdecl GetMessageServer();   // 0x67dcc0
struct cVec3f {
    float x, y, z;
    cVec3f(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct cFilterChainInit {
    char pad0[4];
    int msgSlot;                       // +4 (address registered with the message server)
    char pad1[0x110 - 8];
    cVec3f color;                      // +0x110
    float alpha;                       // +0x11c
    char pad2[0x138 - 0x120];
    cStatePtrVec states;               // +0x138
    char pad3[0x164 - 0x144];
    void* svc2;                        // +0x164
    void* svc3;                        // +0x168
    char pad4[0x174 - 0x16c];
    cViewer174* viewers[4];            // +0x174
    char pad5[0x1b4 - 0x184];
    int stateIdx[2];                   // +0x1b4
    unsigned char bytes[12];           // +0x1bc
    float floats[12];                  // +0x1c8
    bool Init();
};
// ---- items of slice s006f6430 end

// ---- items of slice s006f7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned long long u64;
void __cdecl FreeBlock(void* p) throw();   // 0xf47380 operator delete[]
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} Vec2(const Vec2& o) : x(o.x), y(o.y) {} };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
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
struct cFilterChain_s006f_7430 {
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
// ---- items of slice s006f7430 end

// @ 0x006f6830
bool cFilterChain::AddCameraTexture(unsigned short w, unsigned short h, int* pIndex)
{
    cRectID id;
    GetRttMgr()->Alloc(&id, w, h, 0x15, 0, -1, 0);
    if (id.a != -1) {
        GetRttMgr()->Register(id.a, id.b, "FilterChain");
        rects.push_back(id);
        flags.push_back(0);
        *pIndex = rects.size() - 1;
        return true;
    }
    return false;
}

// @ 0x006f69c0
bool cFilterChainInit::Init()
{
    cStateRec* p;
    for (int i = 0; i < 2; ++i) {
        stateIdx[i] = -1;
        p = new ("Graphics", 0, 0, 0, 0) cStateRec();
        p->f74 = 0;
        states.push_back(p);
    }
    GetSvc1()->Reset();
    color = cVec3f(255.0f, 255.0f, 255.0f);
    alpha = 255.0f;
    svc2 = GetSvc2();
    svc3 = GetSvc3();
    viewers[0] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[0]->Init(0);
    viewers[1] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[1]->Init(0);
    viewers[2] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[2]->Init(0);
    viewers[3] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[3]->Init(0);
    for (unsigned i = 0; i < 12; ++i) {
        bytes[i] = 0;
        floats[i] = 0.0f;
    }
    GetMessageServer()->Register(&msgSlot, 0x44edd9c);
    return true;
}

// @ 0x006f6c30
void cState::W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float c0x = 1.0f, c0y = 1.0f, c0z = 1.0f, c0w = 0.5f;
    float c1x = 0.0f, c1y = 1.0f, c1z = 1.0f, c1w = 0.0f;
    float c3x = 0.0f, c3y = 0.0f;
    unsigned long long flags = 0x28;
    if (ix[0]) flags = 0x2a;
    else if (ix[1]) flags = 0x2c;
    else if (ix[2]) flags = 0x2e;
    else if (ix[6] != 0xff) flags = 0x30;
    if (ix[9]) { c1w = 1.0f; flags = 0xe8; }
    if (ix[3]) flags += 1;
    unsigned short u;
    u = ix[4]; if (u != 0xff) c0w = t->floats[u];
    u = ix[5]; if (u != 0xff) { cVec3 v(t->vec3s[u]); c0x = v.x; c0y = v.y; c0z = v.z; }
    u = ix[7]; if (u != 0xff) c1x = t->floats[u];
    u = ix[8]; if (u != 0xff) { c1y = ((float*)t->vec2s)[u * 2]; c1z = ((float*)t->vec2s)[u * 2 + 1]; }
    u = ix[10]; if (u != 0xff) { c3x = ((float*)t->vec2s)[u * 2]; c3y = ((float*)t->vec2s)[u * 2 + 1]; }
    sh.SetShConst(0, c0x, c0y, c0z, c0w);
    sh.SetShConst(1, c1x, c1y, c1z, c1w);
    sh.SetShConst(3, c3x, c3y, 0.0f, 0.0f);
    cFixedVec2 vec;
    u = d->idx[6]; if (u != 0xff) vec.push_back(((cVec2*)t->vec2b)[u]);
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f6f40
void cState::W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float a = 1.0f, b = 1.0f, c = 1.0f, e = 1.0f, g = 0.0f;
    unsigned long long flags = 0x3c;
    if (ix[2]) flags = 0x3e;
    if (ix[1]) flags += 1;
    unsigned short u;
    u = ix[3]; if (u != 0xff) a = t->floats[u];
    u = ix[4]; if (u != 0xff) b = t->floats[u];
    u = ix[5]; if (u != 0xff) { c = ((float*)t->vec2s)[u * 2]; e = ((float*)t->vec2s)[u * 2 + 1]; }
    u = ix[7]; if (u != 0xff) g = t->floats[u];
    sh.SetShConst(0, a, b, c, e);
    sh.SetShConst(1, g, 0.0f, 0.0f, 0.0f);
    cFixedVec2 vec;
    u = d->idx[0]; if (u != 0xff) vec.push_back(((cVec2*)t->vec2b)[u]);
    u = d->idx[6];
    if (u != 0xff) {
        cVec2 v = ((cVec2*)t->vec2b)[u];
        vec.push_back(v);
        flags += 4;
    }
    if (d->idx[8]) flags += 8;
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f71f0
void cState::W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float c0w = 0.5f;
    float c0x = 1.0f, c0y = 1.0f, c0z = 1.0f;
    unsigned long long flags = 0x46;
    float f2 = 0.5f;
    unsigned short u;
    u = ix[1]; if (u != 0xff) c0w = t->floats[u];
    u = ix[0]; if (u != 0xff) { cVec3 v(t->vec3s[u]); c0x = v.x; c0y = v.y; c0z = v.z; }
    cFixedVec2 vec;
    u = ix[2];
    if (u != 0xff) {
        vec.push_back(((cVec2*)t->vec2b)[u]);
        flags = 0x47;
        f2 = GetDist();
        if (f170 == 1.0f) f170 = 1.1f;
    } else if (ix[3]) {
        flags = 0x48;
    }
    sh.SetShConst(0, c0x, c0y, c0z, c0w);
    sh.SetShConst(1, f2, f170, 0.0f, 0.0f);
    sh.SetShConst(3, f188, f18c, f190, 0.0f);
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f7430
void cFilterChain_s006f_7430::Wrapper8c(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
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
void cFilterChain_s006f_7430::Wrapper200(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
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

// @ 0x006f79a0
void cFilterChain_s006f_7430::Dispatch(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
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

// @ 0x006f7f70
void cFilterChain_s006f_7430::ApplyStrengthFilter(FilterTables* t, FilterOp* op, int a, int b, int c, int d, short e)
{
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
