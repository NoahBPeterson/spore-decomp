// Slice s006f6430: cFilterChain helpers (camera-texture registration), small vector/hashtable
// helpers and state wrappers.
// Region 0x6f6430-0x6f7430. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---- external callees -------------------------------------------------------------------
void  __cdecl FUN_0077ca20(int a, float b, float c, float d, float e);
void  __cdecl FUN_00892970();
void  __cdecl FUN_006f4ff0(void* out, void* a, void* b);
void  __cdecl FUN_006f5170(void* b, void* e);
struct cHashtable {
    void FreeNodes(void* b, void* e);
};
void  __cdecl FUN_006ec390(void* p, void* v);
void  __cdecl FUN_00426730(void* p, void* v);
void  __cdecl FUN_006ec4a0(void* p, void* v);
void  __cdecl operator_delete_(void* p) throw();
void  __cdecl EASTL_allocator_deallocate(void* p);
void* __cdecl operator_new(unsigned sz, const char* name, int a, int b, int c, int d);
void* __cdecl FUN_0067dda0();
void* __cdecl FUN_0067dd40();
void* __cdecl FUN_0067dd50();
void* __cdecl SP_MessageServer();
void* __cdecl FUN_007c3f70();
void  __cdecl cSPEditorPhysicsWorld_Init(void* p, int a);
void  __cdecl FUN_00426950();

void __fastcall FUN_006f54a0_(void* self, int p2, int p3, int p4, int p5,
                               int p6, int p7, int p8, int p9, int p10);

// ---- small vector/hashtable helpers ------------------------------------------------------
struct cVecU16 {
    unsigned short* begin;   // +0
    unsigned short* end;     // +4
    unsigned short* cap;     // +8
    void Insert(unsigned short* pos, const unsigned short& val);   // 0x6f5bc0
    void push_back(const unsigned short& v);
};

// @ 0x006f66a0
void cVecU16::push_back(const unsigned short& v) {
    unsigned short* e = end;
    if (e < cap) {
        end = e + 1;
        if (e != 0) { *e = v; return; }
    } else {
        Insert(e, v);
    }
}

// @ 0x006f66d0
void __fastcall FUN_006f66d0(int* self) {
    void* p;
    p = (void*)self[0x19]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0x14]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0xf];  if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[10];   if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[5];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    ((cHashtable*)self)->FreeNodes((void*)self[0], (void*)self[1]);
    p = (void*)self[0];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
}

// eastl::hash_map<unsigned short,int>::operator[] (hashtable find, then DoInsertValue on miss)
struct cHNode { unsigned short first; int second; cHNode* mpNext; };
struct cHIter {
    cHNode* mpNode; cHNode** mpBucket;
    cHIter() {}
    cHIter(const cHIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};
struct cHPair { unsigned short first; int second; };
struct cHInsertResult { cHIter first; bool second; };
struct cTrue { cTrue() {} };
struct cHashMap16 {
    int pad0;
    cHNode** mpBucketArray;     // +4
    unsigned mnBucketCount;     // +8
    cHIter find(const unsigned short& k);                                           // 0x892970
    cHInsertResult DoInsertValue(const cHPair& v, cTrue);                    // 0x6f4ff0
    int& operator[](const unsigned short& k);
};
// @ 0x006f65d0
int& cHashMap16::operator[](const unsigned short& k) {
    cHNode* n;
    { cHIter it = find(k); n = it.mpNode; }
    if (n == mpBucketArray[mnBucketCount]) {
        cHPair v; v.first = k; v.second = 0;
        cHInsertResult r = DoInsertValue(v, cTrue());
        n = r.first.mpNode;
    }
    return n->second;
}

// ---- shared stubs for the state-wrapper family ----------------------------------------------
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

// @ 0x006f6430
void cState::ColorBE(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7) {
    float r = 1.0f, g = 1.0f, b = 1.0f;
    unsigned short i = d->idx[0];
    if (i != 0xff) {
        cVec3 v(t->vec3s[i]);
        r = v.x; g = v.y; b = v.z;
    }
    sh.SetShConst(0, r, g, b, 0.0f);
    F54a0(0xbe, p3, p4, p5, 0, 0, p6, p7);
}
// @ 0x006f6500
void cState::ColorDC(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7) {
    float x = 0.0f, y = 1.0f;
    unsigned short i = d->idx[0];
    if (i != 0xff) x = t->floats[i];
    unsigned short j = d->idx[1];
    if (j != 0xff) y = t->floats[j];
    sh.SetShConst(0, x, y, 0.0f, 0.0f);
    F54a0(0xdc, p3, p4, p5, 0, 0, p6, p7);
}
// ---- byte vector (eastl::vector<bool/uchar, fixed_vector_allocator>) assignment -----------------
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
struct cByteVec {
    unsigned char* mpBegin;   // +0
    unsigned char* mpEnd;     // +4
    unsigned char* mpCap;     // +8
    unsigned char* DoAllocateAndCopy(unsigned n, const unsigned char* f, const unsigned char* l);   // 0x426950
    void DoInsertValue(unsigned char* pos, const unsigned char& v);                                  // 0x426730
    cByteVec& operator=(const cByteVec& x);
    void erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, mpEnd - last);
        mpEnd -= (last - first);
    }
    void push_back(unsigned char v) {
        if (mpEnd < mpCap) { unsigned char* e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
// @ 0x006f6770
cByteVec& cByteVec::operator=(const cByteVec& x) {
    if (&x != this) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            unsigned char* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1]) operator_delete_(mpBegin);
            mpBegin = pNew;
            mpEnd = mpBegin + n;
            mpCap = pNew + n;
            return *this;
        }
        if (n > (unsigned)(mpEnd - mpBegin)) {
            memcpy(mpBegin, x.mpBegin, mpEnd - mpBegin);
            memcpy(mpEnd, x.mpBegin + (mpEnd - mpBegin), x.mpEnd - (x.mpBegin + (mpEnd - mpBegin)));
            mpEnd = mpBegin + n;
            return *this;
        }
        memcpy(mpBegin, x.mpBegin, x.mpEnd - x.mpBegin);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---- cFilterChain camera textures --------------------------------------------------------------
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

// @ 0x006f6830
bool cFilterChain::AddCameraTexture(unsigned short w, unsigned short h, int* pIndex) {
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

// @ 0x006f6910
void cFilterChain::RemoveCameraTextures() {
    if (rects.mpBegin != rects.mpEnd) {
        unsigned short n = (unsigned short)(rects.mpEnd - rects.mpBegin);
        int off = 0;
        for (unsigned short i = 0; i < n; ++i) {
            GetRttMgr()->Free(*(int*)((char*)rects.mpBegin + off), *(int*)((char*)rects.mpBegin + off + 4));
            off += 8;
        }
        rects.erase(rects.mpBegin, rects.mpEnd);
        flags.erase(flags.mpBegin, flags.mpEnd);
    }
}

// ---- cFilterChain init (state records + four viewers) ---------------------------------------
void* __cdecl operator new(unsigned sz, const char* tag, int a, int b, int c, int d);
void  __cdecl operator delete(void* p, const char* tag, int a, int b, int c, int d);
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

// @ 0x006f69c0
bool cFilterChainInit::Init() {
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
void cState::W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7) {
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
void cState::W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7) {
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
void cState::W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7) {
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
