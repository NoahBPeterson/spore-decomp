// Slice s00b537f0 (gold5 #15) -- EA Simulator / SP:: game code (cLocomotiveObject / Havok glue).
// Hand-written faithful C++ reconstruction from the disassembly + Ghidra decompilation.
// Callee addresses are relocations (masked); only the call shapes and the surrounding code matter.
//
// VA map:
//   00b537f0  (323B)  00b53940 (154B)  00b539e0 (183B)  00b53aa0 (124B)
//   00b53b20  (157B)  00b53bc0 (1083B) 00b54000 (506B)  00b54200 ( 41B)
//   00b54230  (201B)  00b54300 ( 58B)  00b54340 (378B)  00b544c0 ( 45B)
//   00b544f0  ( 45B)  00b54520 (139B)  00b545b0 (139B)  00b54640 (259B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

struct __declspec(align(16)) Vec4 { float x, y, z, w; };

// ---- eastl hashtable (unsigned key -> int value), find() by value ----
struct EIt { void* node; void* pad; };
struct HT {
    int    f00;          // +0
    void** buckets;      // +4
    int    bucketCount;  // +8
    EIt find(const uint& k) const;
};

struct hkBool { char b; };

// SP spatial / locomotive object.  Virtual slots we call: 0x2c,0x30,0x38,0x60,0x68,0x70,0xb8.
struct CObj {
    virtual void* m00(); virtual void* m01(); virtual void* m02(); virtual void* m03();
    virtual void* m04(); virtual void* m05(); virtual void* m06(); virtual void* m07();
    virtual void* m08(); virtual void* m09(); virtual void* m10();
    virtual void* m11();                 // 0x2c
    virtual void* m12();                 // 0x30
    virtual void* m13();
    virtual void  m14(const void*);      // 0x38
    virtual void* m15(); virtual void* m16(); virtual void* m17();
    virtual void* m18(); virtual void* m19(); virtual void* m20(); virtual void* m21();
    virtual void* m22(); virtual void* m23();
    virtual void  m24(const void*);      // 0x60
    virtual void* m25();
    virtual void* m26();                 // 0x68
    virtual void* m27();
    virtual float m28();                 // 0x70
    virtual void* m29(); virtual void* m30(); virtual void* m31(); virtual void* m32();
    virtual void* m33(); virtual void* m34(); virtual void* m35(); virtual void* m36();
    virtual void* m37(); virtual void* m38(); virtual void* m39(); virtual void* m40();
    virtual void* m41(); virtual void* m42(); virtual void* m43(); virtual void* m44();
    virtual void* m45();
    virtual int   m46(int);              // 0xb8
    // non-virtual thiscall externals (not defined here)
    float  getMass();
    void   setMotionType(int, int, int);
    void   setPosition(const void*);
    void   setLinearVelocity(const void*);
    void   setTranslation(const void*);
    hkBool isActive();
    void   activate();
    void   d1df0(void*, void*);
    void   d3d0(const void*);
    void   d530(const void*, int);
    void   d7e0(const void*);
    int    d2e0();
    void   d570(const void*);
    void   d8ae0();
};

// ---- external callees ----
extern "C" int  FUN_00b53940(void*);
extern "C" void FUN_00b4d8e0(void*, int);
extern "C" void FUN_00b4e1d0(void*, int);
extern "C" void FUN_00b523e0(void*, int);
extern "C" void FUN_00b4e0c0(void*, int, void*);
extern "C" void FUN_00b658c0(void*, void*);
extern "C" void FUN_00b55680(void*, void*, int);
extern "C" int  FUN_00b521f0(int);
extern "C" void FUN_01087820(void*);
extern "C" void operator_delete(void*);
extern "C" int  gEmptyString16;
extern "C" int  eastl_sprintf(void* s, const char* fmt, ...);

extern HT HT_167ed58, HT_16801a8, HT_1682a48, HT_16852e8, HT_1569cb8;
extern int* g_1569c9c;
extern int  g_1569ca0;
extern CObj* g_167ecdc;

// ---- eastl hashtable whose iterator is materialised in a caller 12-byte slot ----
struct EIt12 { int a, b, c; };
struct S12   { uint key; int b, c; };
struct HT12  { EIt12 find(const uint& k) const; void** add(const S12* k); };
struct ObjB  { void d770(); };
extern HT12 g_ht12;    // 0x1569cb8
extern int* g_arr12;   // 0x1569cbc
extern int  g_cnt12;   // 0x1569cc0
extern "C" void* FUN_00b51e80(S12*, float);

// ---------------------------------------------------------------------------
// @ 0x00b537f0
extern "C" void FUN_00b537f0(CObj* p, int a2, char a3, char a4)
{
    if (a2 == 0)
        return;
    if (a3 != 0) {
        float* v = (float*)p->m11();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
        p->d3d0(&vv);
    }
    if (a4 != 0) {
        float* v = (float*)p->m11();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
        p->d7e0(&vv);
    }
    {
        float* v = (float*)p->m12();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = v[3];
        p->d530(&vv, a4);
    }
    if ((*(uint*)((char*)p + 0x50) & 0x2000) != 0) {
        int h = p->m46(0x1186577);
        int q = FUN_00b521f0(h);
        if (q != 0) {
            int r = ((CObj*)a2)->d2e0();
            int x = *(int*)(r + 0x1c);
            int y = *(int*)(r + 0x58);
            Vec4 ab;
            typedef void (__stdcall *FNAABB)(void*, float, int, void*);
            ((FNAABB)*(void**)((*(int*)x) + 0xc))((void*)(y + 0x10), 1.0f, x, &ab);
            ((CObj*)q)->setPosition(&ab);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b53940
extern "C" int FUN_00b53940(void* p)
{
    if (p != 0 && ((CObj*)p)->m46(0x116dd1b) != 0) {
        EIt it = HT_167ed58.find((uint)p);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount]) {
            int v = *(int*)((char*)it.node + 4);
            if (v != 0)
                return ((CObj*)v)->d2e0();
        }
    } else {
        EIt it = HT_16801a8.find((uint)p);
        if (it.node != HT_16801a8.buckets[HT_16801a8.bucketCount])
            return *(int*)((char*)it.node + 4);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b539e0
extern "C" void FUN_00b539e0(void* p)
{
    uint k = (uint)p;
    EIt it = HT_1682a48.find(k);
    if (it.node != HT_1682a48.buckets[HT_1682a48.bucketCount])
        FUN_00b4e1d0(p, *(int*)((char*)it.node + 4));
    if (p == 0)
        { FUN_00b523e0(p, 0); return; }
    int e = ((CObj*)p)->m46(0x116dd1b);
    if (e == 0)
        { FUN_00b523e0(p, 0); return; }
    EIt it2 = HT_167ed58.find(k);
    if (it2.node == HT_167ed58.buckets[HT_167ed58.bucketCount])
        return;
    if (*(int*)((char*)it2.node + 4) == 0)
        return;
    FUN_00b537f0((CObj*)e, *(int*)((char*)it2.node + 4), 1, 1);
}

// ---------------------------------------------------------------------------
// @ 0x00b53aa0
extern "C" void FUN_00b53aa0(int* p, void* out)
{
    char* s4;
    char* s3;
    int   ecx;
    int   id;
    switch (p[5]) {
    case 1:  s4 = (char*)0x01461318; break;   // "@center"
    case 2:  s4 = (char*)0x01461320; break;   // "  @base"
    default: s4 = (char*)0x01461328; break;   // "   @???"
    }
    ecx = p[6];
    if (ecx != 0)
        s3 = (char*)0x0146130c;               // " resource"
    else
        s3 = (p[0x1c] == 0) ? (char*)0x014612f4 /* "generated" */
                            : (char*)0x01461300 /* "   cloned" */;
    if (ecx != 0)
        id = (int)*(short*)((char*)ecx + 6);
    else {
        ecx = p[3];
        if (ecx != 0)
            id = (int)*(short*)((char*)ecx + 6);
        else
            id = 0;
    }
    eastl_sprintf(out, "[%3d](%08x!%08x, %6.3f, %s, %s) <%08x>",
                  id, p[2], p[0], (double)*(float*)&p[4], s3, s4, (int)p);
}

// ---------------------------------------------------------------------------
// @ 0x00b53b20
extern "C" void FUN_00b53b20(void)
{
    int* base = g_1569c9c;
    int* it = base;
    int v = *it;
    if (v == 0) {
        do { it++; } while (*it == 0);
        v = *it;
    }
    int end = base[g_1569ca0];
    while (v != end) {
        char* buf[3];
        buf[0] = (char*)&gEmptyString16;
        buf[1] = (char*)&gEmptyString16;
        buf[2] = (char*)0x01667bad;
        FUN_00b53aa0((int*)(v + 0x10), buf);
        if (1 < buf[2] - buf[0] && buf[0] != 0)
            operator_delete(buf[0]);
        v = *(int*)(v + 0x90);
        while (v == 0) { it++; v = *it; }
    }
}

// ---------------------------------------------------------------------------
// Havok / entity types used by 00b53bc0.
extern "C" void   FUN_00b3d350();                       // 0x00b3d350  SP::PlanetModel()

extern "C" void*  FUN_010c05d0(const float* v, float f);// 0x010c05d0  hkBoxShape::hkBoxShape
extern "C" void*  FUN_010bfeb0(void* self, const void* shape, const float* v); // 0x010bfeb0
extern "C" void*  FUN_0108c750(void* self, void* shape, const void* xform, uint info); // 0x0108c750
extern "C" void*  FUN_01083320(void* world, void* phantom);  // 0x01083320 hkWorld::addPhantom
extern "C" void   FUN_0109ae60(void* self);             // 0x0109ae60 removeReference
extern "C" void   FUN_010c2570(void* collector);        // 0x010c2570 hkAllCdPointCollector::sortPoints
extern "C" void   FUN_01083400(void* world, void* phantom);  // 0x01083400 hkWorld::removePhantom
extern "C" void   FUN_0107db10(void* mem, uint size, uint align);  // 0x0107db10 deallocateChunk
extern "C" void*  TlsGetValue_fn(uint idx);             // [0x13cc2bc] kernel32!TlsGetValue
extern "C" char   DAT_01569aba;                         // 0x01569aba  symmetry enabled flag
extern "C" float  DAT_015ba104;                         // 0x015ba104  box hull thickness
extern "C" float  DAT_01471064;                         // 0x01471064  one half
extern "C" float  DAT_013f9428;                         // 0x013f9428
extern "C" float  DAT_01461294;                         // 0x01461294
extern "C" void*  HKMEM_S_INSTANCE;                     // 0x016e4178  hkMemory::s_instance
extern "C" void*  HKWORLD_S_INSTANCE;                   // 0x0167ecd0  hkWorld::s_instance

struct HkMemory {
    virtual void* v00(); virtual void* v01();
    virtual void* v02(); virtual void* v03();
    virtual void* alloc(uint size, uint align);          // +0x10
};

// Candidate body reached through D961::Find; slot 3 is the type-key query.
struct HkBodyKey {
    virtual void* k00(); virtual void* k01(); virtual void* k02();
    virtual void* match(const void* key);                // +0x0c
};
extern "C" void   FUN_00b55680(void*, void*, int);
extern "C" int*   FUN_00496140(int* out, int which);    // 0x00496140  D961::Find (this = entity)

// The editing entity returned by FUN_00b53940.
struct EditEntity {
    char  _pad00[0x1c];
    void* mShape;        // +0x1c  fallback collideable shape
    char  _pad20[0x58 - 0x20];
    void* mBodyTransform; // +0x58  body transform (shape at +0x10)
    int*  Find(int* out, int which);        // 0x00496140
};
typedef int* (EditEntity::*EditEntityFind)(int*, int);

// hkSimpleShapePhantom -- only the query entry point this slice uses.
struct HkPhantomQuery {
    virtual void* q00(); virtual void* q01(); virtual void* q02();
    virtual void* q03(); virtual void* q04(); virtual void* q05();
    virtual void* q06(); virtual void* q07(); virtual void* q08();
    virtual void* q09(); virtual void* q10(); virtual void* q11();
    virtual void  query(const void* a, void* collector, int flag);   // +0x30
};

// hkAllCdPointCollector -- count at +0x14, point array at +0x10.
struct HkPointCollector {
    char  _pad00[0x08];
    void* mVtable;       // +0x08
    float mRadius;       // +0x0c
    void* mPoints;       // +0x10
    int   mCount;        // +0x14
    char  _pad18[0x1c - 0x18];
    int   mCapacity;     // +0x1c
};
struct HkCdPoint {
    float mPos[3];       // +0x00 contact position
    char  _pad0c[0x28 - 0x0c];
    void* mBody;         // +0x28
    char  _pad2c[0x30 - 0x2c];
};

// @ 0x00b53bc0  build a phantom around the entity body and scan its collideables
extern "C" char FUN_00b53bc0(CObj* p, float* a2, float* a3, float* a4, char a5)
{
    FUN_00b3d350();                                     // SP::PlanetModel()
    EditEntity* ent = (EditEntity*)FUN_00b53940(p);
    if (ent == 0)
        return 0;

    float dir[4];                                       // local_1f0..local_1e4
    dir[0] = a2[0]; dir[1] = a2[1]; dir[2] = a2[2]; dir[3] = 0.0f;
    float origin[3];                                    // local_200..local_1f8
    origin[0] = a3[0]; origin[1] = a3[1]; origin[2] = a3[2];

    void* shape;                                        // local_1e0 result
    if (DAT_01569aba != 0) {
        float* bb = (float*)p->m26();                   // body AABB
        float size[4];                                  // +0x60
        size[0] = bb[3] - bb[0];
        size[1] = bb[4] - bb[1];
        size[2] = bb[5] - bb[2];
        size[3] = 0.0f;

        void* boxMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x20, 0x24);
        *(unsigned short*)((char*)boxMem + 4) = 0x20;
        void* box = FUN_010c05d0(size, DAT_015ba104);   // hkBoxShape

        float offset[4];                                // +0x20
        offset[0] = 0.0f; offset[1] = 0.0f; offset[2] = 0.0f; offset[3] = 0.0f;
        int fbuf[1];
        int* found = ent->Find(fbuf, 6);
        if (*found != 0) {
            float* bb2 = (float*)p->m26();
            offset[0] = (bb2[3] + bb2[0]) * DAT_01471064;
            offset[1] = (bb2[4] + bb2[1]) * DAT_01471064;
            offset[2] = (bb2[5] + bb2[2]) * DAT_01471064;
            offset[3] = 0.0f;
        }
        void* convMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x30, 0x24);
        *(unsigned short*)((char*)convMem + 4) = 0x30;
        shape = FUN_010bfeb0(convMem, box, offset);     // hkConvexTranslateShape
        if (*(unsigned short*)((char*)box + 4) != 0 &&
            (*(unsigned short*)((char*)box + 6) -= 1) == 0)
            (**(void (***)(int))box)(1);
    } else {
        shape = ent->mShape;                            // +0x1c fallback
    }

    void* phMem = ((HkMemory*)HKMEM_S_INSTANCE)->alloc(0x130, 0x2e);
    *(unsigned short*)((char*)phMem + 4) = 0x130;
    void* phantom = FUN_0108c750(phMem, shape, (void*)((char*)ent->mBodyTransform + 0x10),
                                 a5 != 0 ? 7u : 4u);
    FUN_01083320(HKWORLD_S_INSTANCE, phantom);
    FUN_0109ae60(phantom);

    float sweep[4];                                     // hkVector4 at +0x70
    sweep[0] = origin[0]; sweep[1] = origin[1]; sweep[2] = origin[2]; sweep[3] = 0.0f;

    char collectorMem[0x2c];                            // hkAllCdPointCollector at +0x90
    HkPointCollector* coll = (HkPointCollector*)collectorMem;
    coll->mVtable = (void*)0x013ef55c;
    coll->mRadius = DAT_01461294;
    coll->mPoints = collectorMem + 0x24;                // local point array
    coll->mCount = 0;
    coll->mCapacity = 0x80000008;

    ((HkPhantomQuery*)phantom)->query(dir, sweep, 0);   // virtual slot 12

    char hit = 0;
    if (coll->mCount > 0) {
        int other = p != 0 ? p->m46(0x17f243b) : 0;
        FUN_010c2570(coll);                             // sortPoints
        for (int i = 0, off = 0; i < coll->mCount; ++i, off += 0x30) {
            if (hit != 0)
                break;
            HkCdPoint* pt = (HkCdPoint*)((char*)coll->mPoints + off);
            int id = *(int*)((char*)pt->mBody + 0x10);
            int rbuf[1];
            int* f = FUN_00496140(rbuf, 0);
            void* cand = (*f == 3) ? *(void**)((char*)pt->mBody + id + 0xc) : 0;
            if (cand != (void*)other && (cand == 0 || ((HkBodyKey*)cand)->match((void*)0xce9f6639) == 0)) {
                if (a4 != 0) {
                    a4[0] = pt->mPos[0];
                    a4[1] = pt->mPos[1];
                    a4[2] = pt->mPos[2];
                }
                hit = 1;
            }
        }
    }

    FUN_01083400(HKWORLD_S_INSTANCE, phantom);
    if (DAT_01569aba != 0 && *(unsigned short*)((char*)shape + 4) != 0 &&
        (*(unsigned short*)((char*)shape + 6) -= 1) == 0)
        (**(void (***)(int))shape)(1);

    ((HkPointCollector*)collectorMem)->mVtable = (void*)0x013ef55c;
    {
        uint cap = ((HkPointCollector*)collectorMem)->mCapacity;
        if ((int)cap >= 0) {
            TlsGetValue_fn(0);
            FUN_0107db10(collectorMem + 0x18, (cap & 0x3fffffff) * 0x30, 0x14);
        }
    }
    return hit;
}

// ---------------------------------------------------------------------------
// Havok types used by 00b54000 (only the members this slice touches).
extern "C" void* HKWORLD_S_INSTANCE;    // (declared above)
extern "C" int   HKC_KEY_1186577;       // key object addressed by the caller's lookup below
extern "C" int*  FUN_00496140(int* out, int which);   // 0x00496140  D961::Find
extern "C" float sqrtf(float);

struct HkPhantom {
    void*          mVtable;        // +0x00
    unsigned short mMemSize;       // +0x04
    HkPhantom* construct(void* shape, uint filterInfo);  // 0x108dfe0 hkAabbPhantom::hkAabbPhantom
    void       removeReference();                        // 0x109ae60
};

struct HkArray { int* mData; int mSize; int mCapacity; };   // +0x00

struct HkAabbPhantom {
    void*          mVtable;        // +0x00
    unsigned short mMemSize;       // +0x04
    char           _pad06[0x90 - 0x06];
    HkArray        mOverlaps;      // +0x90
};

struct HkWorld {
    void* addPhantom(void* phantom);        // 0x1083320
    void  removePhantom(void* phantom);     // 0x1083400
};

struct HkCdBody {
    virtual void*  v00(); virtual void* v01(); virtual void* v02();
    virtual void*  lookup(const void* key);      // +0x0c
    virtual void*  v04(); virtual void* v05(); virtual void* v06(); virtual void* v07();
    virtual void*  v08(); virtual void* v09(); virtual void* v10();
    virtual float* v11();                        // +0x2c
    virtual void*  v12(); virtual void* v13();
    virtual void   v14(float* v);                // +0x38
    char           _pad[0x77 - 4];
    char           mFlag77;                      // +0x77
};

// @ 0x00b54000  build + register an hkAabbPhantom, then touch each child
extern "C" void FUN_00b54000(CObj* p, int a2)
{
    if (a2 == 0) {
        uint k = (uint)p;
        EIt it = HT_16852e8.find(k);
        if (it.node == HT_16852e8.buckets[HT_16852e8.bucketCount])
            return;
        a2 = *(int*)((char*)it.node + 4);
        if (a2 == 0)
            return;
    }

    HkPhantom* mem = (HkPhantom*)((HkMemory*)HKMEM_S_INSTANCE)->alloc(0xa0, 0x2e);
    mem->mMemSize = 0xa0;
    HkAabbPhantom* ph = (HkAabbPhantom*)mem->construct((void*)(a2 + 0x70), 8);
    ((HkWorld*)HKWORLD_S_INSTANCE)->addPhantom(ph);
    mem->removeReference();

    int buf[6];
    int key = 0;
    for (int i = 0; i < ph->mOverlaps.mSize; ++i) {
        int child = ph->mOverlaps.mData[i];
        child = *(int*)((char*)child + 0x10) + child;
        if (child == 0)
            continue;
        int* f = FUN_00496140(buf, 0);
        if (*f != 3)
            continue;
        int* o = FUN_00496140(buf + 2, 1);
        HkCdBody* body = (HkCdBody*)*o;
        if (body == 0)
            continue;
        HkCdBody* res = (HkCdBody*)body->lookup(&key);
        if (res == 0 || res->mFlag77 == 0)
            continue;

        float* bb = (float*)p->m11();                    // body bounding box
        float x = bb[0], y = bb[1], z = bb[2];
        float extra = p->m28();                          // +0x70
        float* rb = (float*)res->v11();
        float s = (float)(double)(extra + sqrtf(x * x + y * y + z * z))
                  / sqrtf(rb[0] * rb[0] + rb[1] * rb[1] + rb[2] * rb[2]);
        float* rb2 = (float*)res->v11();
        float v[3];
        v[0] = rb2[0] * s;
        v[1] = rb2[1] * s;
        v[2] = rb2[2] * s;
        res->v14(v);
        FUN_00b539e0(res);
        FUN_00b55680(res, (void*)child, 1);
    }
    if (ph != 0)
        ((HkWorld*)HKWORLD_S_INSTANCE)->removePhantom(ph);
}

// ---------------------------------------------------------------------------
// @ 0x00b54200
extern "C" char FUN_00b54200(void* p)
{
    char r = 0;
    CObj* o = (CObj*)FUN_00b53940(p);
    if (o != 0) {
        o->setMotionType(1, 1, 0);
        r = 1;
    }
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00b54230
extern "C" int FUN_00b54230(void* p, CObj* b)
{
    if (b == 0) {
        b = (CObj*)FUN_00b53940(p);
        if (b == 0) {
            uint k = (uint)p;
            EIt it = HT_167ed58.find(k);
            int val = (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount])
                          ? *(int*)((char*)it.node + 4) : 0;
            if (val != 0) {
                float* v = (float*)((CObj*)p)->m11();
                Vec4 vv;
                vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
                ((CObj*)val)->d7e0(&vv);
                return 1;
            }
            return 0;
        }
    }
    Vec4 vv;
    FUN_00b4e0c0(p, (int)b, &vv);
    b->setPosition(&vv);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00b54300
extern "C" void FUN_00b54300(void* a, void* b)
{
    if (g_167ecdc == 0)
        return;
    int x = FUN_00b53940(a);
    int y = FUN_00b53940(b);
    if (x != 0 && y != 0)
        g_167ecdc->d1df0((void*)x, (void*)y);
}

// ---------------------------------------------------------------------------
// @ 0x00b54340  (approximate)
extern "C" void FUN_00b54340(void* p, float* v, char a3)
{
    if (p != 0 && *((char*)p + 0x71) == 0) {
        int e = FUN_00b53940(p);
        if (e != 0)
            ((CObj*)e)->setMotionType(1, 1, 0);
    }
    {
        uint k = (uint)p;
        EIt it = HT_167ed58.find(k);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount] &&
            *(int*)((char*)it.node + 4) != 0) {
            int e = ((CObj*)*(int*)((char*)it.node + 4))->d2e0();
            if (e != 0) {
                Vec4 vv;
                vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
                if (a3 != 0) {
                    float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                    vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
                }
                ((CObj*)e)->d570(&vv);
            }
            return;
        }
    }
    {
        int e = FUN_00b53940(p);
        if (e != 0) {
            Vec4 vv;
            vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
            if (a3 != 0) {
                float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
            }
            ((CObj*)e)->activate();
            ((CObj*)(*(int*)((char*)e + 0x58)))->m24(&vv);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b544c0
extern "C" void FUN_00b544c0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) &= 0xffffff7fu;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00b544f0
extern "C" void FUN_00b544f0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) |= 0x80u;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00b54520
extern "C" bool FUN_00b54520(void* p)
{
    CObj* e = (CObj*)FUN_00b53940(p);
    if (e != 0 && e->isActive().b != 0) {
        Vec4 v;
        FUN_00b658c0(&v, e);
        float s = v.x * v.x;
        s = s + v.y * v.y;
        s = s + v.z * v.z;
        return s > 1.52587890625e-05f;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00b545b0
extern "C" bool __stdcall FUN_00b545b0(S12* p)
{
    EIt12 it = g_ht12.find(p->key);
    int n = g_cnt12;
    if (it.a != g_arr12[n])
        return true;
    it = *(EIt12*)p;
    it.b = 0;
    void* r = FUN_00b51e80((S12*)&it, 1.0f);
    if (r != 0) {
        ((ObjB*)r)->d770();
        *(void**)g_ht12.add((S12*)&it) = r;
    } else {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00b54640  member: eastl pool + hashtable setup over this+0x43c, returns this
extern "C" void* FUN_00921340(int a);                 // 0x00921340
extern "C" const float F_013f0620;                    // 0x013f0620
extern "C" const float F_01470f1c;                    // 0x01470f1c

// eastl::fixed_pool_base -- only the two methods this slice calls.
struct FixedPool {
    void* mpHead;                                             // +0x00
    void  FUN_00921260(void* mem, uint size, int a, int b, int c);  // 0x00921260 init
    uint  FUN_009213c0(void* p);                              // 0x009213c0
};

struct C54640 {
    char  _pad0[0x08];
    uint  m08;                    // +0x08
    void* m0c;                    // +0x0c
    float m10;                    // +0x10
    float m14;                    // +0x14
    float m18;                    // +0x18
    char  _pad1[0x34 - 0x1c];
    char  m34[0x10];              // +0x34
    char  m44[0x43c - 0x44];
    char  m43c[0xc00];            // +0x43c  pool storage
    char  m103c[0x04];            // +0x103c
    int   FUN_00b54640(int a2);
    void  FUN_00b516d0(void* a, void* b, void* c, void* d, void* e, void* f,
                       void* g);                                 // 0x00b516d0
    void  FUN_00b5d220(uint n);                                  // 0x00b5d220
    void  FUN_00b53410(int a, int* b, int c, int* d);            // 0x00b53410
};

int C54640::FUN_00b54640(int a2)
{
    char pool[0x18];
    FixedPool* fp = (FixedPool*)pool;
    fp->mpHead = 0;
    fp->FUN_00921260(m43c, 0xc00, 0xc, 4, 0);

    char* hdr = pool + 0x08;                       // {begin, end, cap, tail} descriptor
    *(void**)(hdr + 0x00) = m43c;
    *(void**)(hdr + 0x04) = m43c + 0xc00;
    *(int*)(hdr + 0x08) = 0x0c;
    *(void**)(hdr + 0x0c) = m34;

    void* v = FUN_00921340(0x101);
    FUN_00b516d0(v, &a2, &a2, &a2, &a2, &a2, pool);

    *(float*)(pool + 0) = F_013f0620;
    *(float*)(pool + 4) = F_01470f1c;
    m10 = F_013f0620;
    m14 = F_01470f1c;
    *(void**)(hdr + 0x00) = 0;
    m18 = 0.0f;

    uint n = fp->FUN_009213c0(m0c);
    if (n > m08) FUN_00b5d220(n);

    int* p5 = *(int**)(a2 + 4);
    int* e = p5 + *(int*)(a2 + 8);
    int v1 = *e;
    int v6 = *p5;
    if (v6 == 0) {
        do { p5 = p5 + 1; v6 = *p5; } while (v6 == 0);
    }
    FUN_00b53410(v6, p5, v1, e);
    return (int)this;
}
