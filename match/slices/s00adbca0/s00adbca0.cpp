// Slice s00adbca0: FUN_00adbca0, "where does this attached effect/object go": resolves the
// pose of the object named by the config (pos, orientation, three scales) from either a
// registered holder (found1) or the config's defaults, applies the config's offset
// (rotated by the orientation), and clamps to the planet surface.
//
// Retail layouts; offsets verified against the asm.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss, x87 call results; no EH frame).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Vector3 { float x, y, z; };
struct Quat { float x, y, z, w; Quat() {} Quat(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Box { float minX, minY, minZ, maxX, maxY, maxZ; };

struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& o);                       // 0x0041cb40
};

extern Vector3 g_DefaultPos1;                        // 0x0167a548
extern Vector3 g_DefaultPos2;                        // 0x0167a5a4
extern Matrix3 g_DefaultRot;                         // 0x0167a5b0
extern float   g_One;                                // 0x01485720 (1.0f)

struct Transform {
    uint16_t flags;
    uint16_t mod;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    Transform() : flags(0), mod(0), pos(g_DefaultPos2), scale(1.0f), rot(g_DefaultRot) {}
};

// Object found by id; vtable slots as used here.
class IPose {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual const Vector3* GetPosition();            // 0x2c
    virtual const Quat*    GetOrientation();         // 0x30
    virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40();
    virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
    virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
    virtual void s64();
    virtual const Box* GetBounds();                  // 0x68
    virtual void s6c();
    virtual float GetScaleB();                       // 0x70
    virtual float GetScaleA();                       // 0x74
    virtual void s78(); virtual void s7c(); virtual void s80(); virtual void s84();
    virtual void s88(); virtual void s8c(); virtual void s90(); virtual void s94();
    virtual void s98(); virtual void s9c(); virtual void sa0(); virtual void sa4();
    virtual void sa8(); virtual void sac(); virtual void sb0(); virtual void sb4();
    virtual void sb8(); virtual void sbc();
    virtual void Release();                          // 0xc0
};

class IPoseSource {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void GetTransform(Transform* out);       // 0x20
};

// Pose holder filled by Owner::Lookup (0x30 bytes).
struct Holder {
    Vector3 pos;
    Quat    rot;
    float   sc[4];
    IPose*  obj;
    Holder() : pos(g_DefaultPos1), rot(Quat(0.0f, 0.0f, 0.0f, 0.0f)), obj(0)
    {
        sc[0] = sc[1] = sc[2] = sc[3] = g_One;
    }
    ~Holder() { if (obj) obj->Release(); }
    Vector3* ad7b90(Vector3* out);                   // 0x00ad7b90
    Quat*    getOrientation();                       // 0x00ad7b70
};

struct Cfg {
    uint32_t pad00[4];
    uint32_t id;               // +0x10
    Vector3  ofs;              // +0x14
    Vector3  ofs2;             // +0x20
    bool     trackTarget;      // +0x2c
    bool     sendQuat;         // +0x2d
    uint8_t  pad2e;            // +0x2e
    bool     scaleXY;          // +0x2f
    bool     useB;             // +0x30
    bool     useC;             // +0x31
    uint8_t  pad32[2];
    uint32_t id2;              // +0x34
    int      mode;             // +0x38
    bool     extraCheck;       // +0x3c
    bool     useNotifyB;       // +0x3d
    uint8_t  pad3e[(0x5c - 0x3e)];
    bool     activeFlag;       // +0x5c
    uint8_t  pad5d[(0x80 - 0x5d)];
    Vector3  defPos;           // +0x80
};

struct TerrainMapSet {
    uint32_t pad00[0x34 / 4];
    float radius;              // +0x34
    float maxHeight;           // +0x38
    float waterHeight;         // +0x3c
    float GetHeightAt(const Vector3* p);             // 0x00f927c0
};
class TerrainProvider {
public:
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual TerrainMapSet* GetMapSet();              // 0xc
};
struct PlanetMdl {
    uint32_t pad00[0x24 / 4];
    TerrainProvider* terrain;  // +0x24
    bool     IsPositionBelowSurface(const Vector3* p);                  // 0x00b81f90
    Vector3* b81630(Vector3* out, const Vector3* p);                    // 0x00b81630
    Vector3* b82b40(Vector3* out, const Vector3* p, int k);             // 0x00b82b40
};
PlanetMdl* PlanetModel();                            // 0x00b3d350
int  GetUniverseContext();                           // 0x01021080
bool IsInvalidQuat(const Quat* q);                   // 0x00ad7170 (cdecl)
Matrix3* QuatToMatrix(Matrix3* out, const Quat* q);  // 0x004a9b40 (cdecl)
Quat* QuaternionFromMatrix33(Quat* out, const Matrix3* m, float k);     // 0x00472b80 (cdecl)

class INotify;                                       // receiver at Placer+0x13c
class CamOwnerFields;                                // object at Placer+0x168

class Placer {
public:
    uint32_t pad00[0x13c / 4];
    INotify* notify;                                 // +0x13c
    uint32_t pad140[(0x168 - 0x140) / 4];
    CamOwnerFields* owner;                           // +0x168
    Cfg*     cfg;                                    // +0x16c

    bool Lookup(uint32_t id, Holder* h);             // 0x00adb2a0
    bool LookupSource(uint32_t id, IPoseSource** out);   // 0x00adb1b0
    void GetPose(Vector3* outPos, Quat* outRot, float* outA, float* outB, float* outC);   // 0x00adbca0
    bool UpdateTarget();                             // 0x00adc490
};

void Placer::GetPose(Vector3* outPos, Quat* outRot, float* outA, float* outB, float* outC)
{
    Holder h1;
    IPoseSource* src;
    bool found1 = Lookup(cfg->id, &h1);
    bool haveSrc = LookupSource(cfg->id, &src);
    Holder h2;
    bool found2 = false;
    if (cfg->id2 != 0)
        found2 = Lookup(cfg->id2, &h2);

    Vector3 tmp;
    if (found1) {
        const Vector3* p = h1.obj ? h1.obj->GetPosition() : &h1.pos;
        *outPos = *p;
        const Quat* q = h1.obj ? h1.obj->GetOrientation() : &h1.rot;
        *outRot = *q;
        *outA = h1.obj ? h1.obj->GetScaleA() : h1.sc[0];
        *outB = h1.obj ? h1.obj->GetScaleB() : h1.sc[1];
        if (h1.obj) {
            const Box* b = h1.obj->GetBounds();
            *outC = b->maxZ - b->minZ;
        } else {
            *outC = h1.sc[3];
        }
        if (found2) {
            *outA = h2.obj ? h2.obj->GetScaleA() : h2.sc[0];
            *outB = h2.obj ? h2.obj->GetScaleB() : h2.sc[1];
        }
        if (cfg->mode == 1) {
            *outPos = *h1.ad7b90(&tmp);
        } else if (cfg->mode == 2) {
            float x = outPos->x, y = outPos->y, z = outPos->z;
            float inv = (float)(1.0 / sqrt(z * z + x * x + y * y));
            tmp.x = inv * x;
            tmp.y = inv * y;
            tmp.z = z * inv;
            TerrainMapSet* ts = PlanetModel()->terrain->GetMapSet();
            float h = ts->GetHeightAt(outPos);
            float r = ts->waterHeight * ts->maxHeight + ts->radius;
            const float& m = (r < h) ? h : r;
            outPos->x = tmp.x * m;
            outPos->y = tmp.y * m;
            outPos->z = tmp.z * m;
        }
        if (cfg->mode != 2 && GetUniverseContext() == 0) {
            if (PlanetModel()->IsPositionBelowSurface(outPos))
                *outPos = *PlanetModel()->b81630(&tmp, outPos);
        }
    } else if (!haveSrc) {
        *outPos = cfg->defPos;
        Quat q(0.0f, 0.0f, 0.0f, 1.0f);
        *outRot = q;
    } else {
        PlanetMdl* pm = PlanetModel();
        Transform xf;
        src->GetTransform(&xf);
        *outPos = xf.pos;
        Quat qtmp;
        *outRot = *QuaternionFromMatrix33(&qtmp, &xf.rot, 0.0f);
        if (cfg->mode == 2 && pm && pm->terrain)
            *outPos = *pm->b82b40(&tmp, outPos, 0);
    }

    Cfg* c = cfg;
    float ox = c->ofs.x, oy = c->ofs.y, oz = c->ofs.z;
    if (c->scaleXY) {
        ox = *outA * ox;
        oy = *outA * oy;
    }
    if (c->useB && c->useC) {
        float b = *outB, cc = *outC;
        oz = ((b > cc) ? b : cc) * oz;
    } else if (c->useB) {
        oz = *outB * oz;
    } else if (c->useC) {
        oz = *outC * oz;
    }
    ox = c->ofs2.x + ox;
    oy = c->ofs2.y + oy;
    oz = c->ofs2.z + oz;
    if (!IsInvalidQuat(outRot)) {
        float mbuf[9];
        const float* M = QuatToMatrix((Matrix3*)mbuf, outRot)->m;
        outPos->y = outPos->y + ((M[7] * oz + M[4] * oy) + M[1] * ox);
        outPos->x = outPos->x + ((M[6] * oz + M[3] * oy) + M[0] * ox);
        outPos->z = outPos->z + ((M[8] * oz + M[5] * oy) + M[2] * ox);
    } else {
        outPos->x = outPos->x + ox;
        outPos->y = outPos->y + oy;
        outPos->z = outPos->z + oz;
    }
}

// ======================================================================
// gold7 batch (same slice id, different VAs): the simulator action-target
// update, the name-table insert, and the eastl hashtable / vector helpers
// used by that cluster.
// ======================================================================

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern void* __cdecl operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
extern void  __cdecl operator_delete(void* p);                                                                    // 0x00f47380

extern const char g_SimulatorName[];             // 0x013f09b4  "Simulator"
extern const char g_EastlAllocFile[];            // 0x013ebb38  allocator file name
extern Vector3    g_UnsetPos;                    // 0x0156649c  (FLT_MAX, FLT_MAX, FLT_MAX)
extern const unsigned char g_NotifyTargetA[];    // 0x0101b534
extern const unsigned char g_NotifyTargetB[];    // 0x0101b537

void __cdecl FUN_00ad7400(void** first, void** last, void** dest);              // 0x00ad7400
void __cdecl Vector3_Normalize(Vector3* out, const Vector3* in);               // 0x00436ce0

// Intrusive reference control block (vtable slot 0 = AddRef, slot 1 = Release).
// The name-table payloads carry the vptr at +0 and a slot id at +4; the vector
// elements carry the same block embedded at +8.
struct IRef {
    virtual void AddRef();                       // slot 0
    virtual void Release();                      // slot 1
    uint32_t mSlot;                              // +0x04
};
struct CountedObj {
    uint32_t f00;                                // +0x00
    uint32_t f04;                                // +0x04
    IRef     mRef;                               // +0x08
};

// ---- eastl hashtable (bucket array +4, bucket count +8, size +0xc) ----
struct SmallValue {                              // 12-byte payload (kept as scalars: no /GS cookie)
    uint32_t mA;                                 // +0x00
    uint32_t mB;                                 // +0x04
    uint32_t mC;                                 // +0x08
};
struct SmallNode {                               // 0x10-byte map node
    uint32_t   mKey;                             // +0x00
    SmallValue mValue;                           // +0x04
};
// find() writes a 12-byte pair<iterator, bool> through its out pointer.
struct FindSmallResult {
    SmallNode* mpNode;                           // +0x00
    void*      mpBucket;                         // +0x04
    uint32_t   mInserted;                        // +0x08
};
struct SimNode {                                 // name-table node
    uint32_t mKey;                               // +0x00
    IRef*    mpValue;                            // +0x04
    SimNode* mpNext;                             // +0x08
};
struct Iter  { SimNode*  mpNode; SimNode**  mpBucket; };

struct BigNode {                                 // 0x3c-byte payload node
    uint32_t mKey;                               // +0x00
    void*    mpVptrA;                            // +0x04  (first base vptr)
    uint32_t f08;                                // +0x08
    void*    mpVptrB;                            // +0x0c  (second base vptr)
    IRef*    mpRef;                              // +0x10
    uint8_t  pad14[0x38 - 0x14];
    BigNode* mpNext;                             // +0x38
};
struct IterA { BigNode* mpNode; BigNode** mpBucket; };

struct HTbl {
    uint32_t f00;                                // +0x00
    void*    mpBucketArray;                      // +0x04
    uint32_t mnBucketCount;                       // +0x08
    uint32_t mnSize;                             // +0x0c

    void   DoFreeNodes(void* nodes, unsigned count);                        // 0x007611f0
    void   FindSmall(FindSmallResult* out, const uint32_t* key);            // 0x00db4780
    void   InsertSmall(SmallNode** pos, const void* value, bool flag);      // 0x00ad9370
    void   insertEntry(void* out, const void* value, bool flag);            // 0x00ad9090
    Iter*  erase(Iter* out, SimNode* node, SimNode** bucket);               // 0x00adc970
    IterA* eraseA(IterA* out, BigNode* node, BigNode** bucket);             // 0x00adc9f0

    void   clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnSize = 0; }
};

struct NameKeyValue {
    uint32_t mpKey;                              // +0x00
    IRef*    mpValue;                            // +0x04
};
struct NameTbl {
    uint8_t pad00[0x5c];
    HTbl    mMap;                                // +0x5c
    void Insert(uint32_t key, IRef* p, uint32_t slot);      // 0x00adc890
};

struct Sub10 {
    HTbl      mTable;                            // +0x00
    uint32_t* GetValue(uint32_t* key);           // 0x00adc900
};

struct NodeOwner {
    uint8_t pad00[0x10];
    HTbl    mTable;                              // +0x10
    void FreeNodes();                            // 0x00adcc90
};

struct AutoRefVec {
    CountedObj** mpBegin;                        // +0x00
    CountedObj** mpEnd;                          // +0x04
    CountedObj** mpCapacity;                     // +0x08
    void DoInsertValue(CountedObj** pos, CountedObj** value);   // 0x00adca90
};

// ---- receiver/owner interfaces used by Placer::UpdateTarget ----------
class INotify {
public:
    virtual void n00();
    virtual void send(const void* id, const Vector3* v);    // slot 4
};

class ICamOwnerBase {
public:
    virtual void o00(); virtual void o04(); virtual void o08(); virtual void o0c();
    virtual void o10(); virtual void o14(); virtual void o18(); virtual void o1c();
    virtual void o20(); virtual void o24(); virtual void o28(); virtual void o2c();
    virtual void o30(); virtual void o34(); virtual void o38(); virtual void o3c();
    virtual void o40(); virtual void o44(); virtual void o48(); virtual void o4c();
    virtual void o50(); virtual void o54(); virtual void o58();
    virtual Vector3* getLookPos(Vector3* out);              // 0x5c
};

struct CamOwnerFields : public ICamOwnerBase {
    uint8_t pad04[0x10b - 4];
    bool    flag10b;                             // +0x10b
    void    setQuat(Quat q);                     // 0x00eb30d0
    bool    blocked();                           // 0x00eb4040
};

// @ 0x00adc490
bool Placer::UpdateTarget()
{
    Cfg* c = cfg;
    if (!c)
        return true;
    if (!c->activeFlag)
        return true;

    Holder h;
    bool found = Lookup(c->id, &h);

    if (c->trackTarget) {
        Vector3 p = { 0.0f, 0.0f, 0.0f };
        if (owner) {
            Vector3 look;
            p = *owner->getLookPos(&look);
        }
        if (found && h.obj) {
            p = *h.obj->GetPosition();
            if (c->mode == 1) {
                Vector3 tmp;
                p = *h.ad7b90(&tmp);
            } else if (c->mode == 2) {
                Vector3 n;
                Vector3_Normalize(&n, &p);
                TerrainMapSet* ts = PlanetModel()->terrain->GetMapSet();
                float hgt = ts->GetHeightAt(&p);
                float lim = ts->waterHeight * ts->maxHeight + ts->radius;
                float m = (hgt > lim) ? hgt : lim;
                p.x = n.x * m;
                p.y = n.y * m;
                p.z = n.z * m;
            }
        }
        if (p.x == g_UnsetPos.x && p.y == g_UnsetPos.y && p.z == g_UnsetPos.z) {
            c->activeFlag = false;
            return true;
        }
        Quat q(0.0f, 0.0f, 0.0f, 1.0f);
        if (found && h.obj)
            q = *h.getOrientation();
        float mbuf[9];
        const Matrix3& m = *QuatToMatrix((Matrix3*)mbuf, &q);
        Vector3 w;
        w.x = p.x + ((m.m[3] * c->ofs.y + m.m[6] * c->ofs.z) + m.m[0] * c->ofs.x);
        w.y = p.y + ((m.m[4] * c->ofs.y + m.m[7] * c->ofs.z) + m.m[1] * c->ofs.x);
        w.z = p.z + ((m.m[5] * c->ofs.y + m.m[8] * c->ofs.z) + m.m[2] * c->ofs.x);
        owner->flag10b = false;
        if (c->useNotifyB)
            notify->send(g_NotifyTargetB, &w);
        else
            notify->send(g_NotifyTargetA, &w);
        if (c->sendQuat)
            owner->setQuat(q);
    }
    if (c->extraCheck && owner->blocked())
        return false;
    return true;
}

// @ 0x00adc890
void NameTbl::Insert(uint32_t key, IRef* p, uint32_t slot)
{
    if (!p)
        return;
    p->mSlot = slot;
    p->AddRef();
    NameKeyValue kv;
    kv.mpKey = key;
    kv.mpValue = p;
    p->AddRef();
    Iter it;
    bool rehash = false;
    mMap.insertEntry(&it, &kv, rehash);
    if (kv.mpValue)
        kv.mpValue->Release();
    p->Release();
}

// @ 0x00adc900
uint32_t* Sub10::GetValue(uint32_t* key)
{
    FindSmallResult it;
    mTable.FindSmall(&it, key);
    SmallNode** buckets = (SmallNode**)mTable.mpBucketArray;
    if (it.mpNode == buckets[mTable.mnBucketCount]) {
        bool rehash = false;
        SmallNode value = { *key };
        mTable.InsertSmall(&it.mpNode, &value, rehash);
    }
    return &it.mpNode->mValue.mA;
}

// @ 0x00adc970
Iter* HTbl::erase(Iter* out, SimNode* node, SimNode** bucket)
{
    out->mpBucket = bucket;
    out->mpNode = node->mpNext;
    while (!out->mpNode) {
        ++out->mpBucket;
        out->mpNode = *out->mpBucket;
    }
    if (*bucket == node) {
        *bucket = node->mpNext;
    } else {
        SimNode* prev = *bucket;
        while (prev->mpNext != node)
            prev = prev->mpNext;
        prev->mpNext = node->mpNext;
    }
    if (node->mpValue)
        node->mpValue->Release();
    operator_delete(node);
    --mnSize;
    return out;
}

// @ 0x00adc9f0
IterA* HTbl::eraseA(IterA* out, BigNode* node, BigNode** bucket)
{
    out->mpBucket = bucket;
    out->mpNode = node->mpNext;
    while (!out->mpNode) {
        ++out->mpBucket;
        out->mpNode = *out->mpBucket;
    }
    if (*bucket == node) {
        *bucket = node->mpNext;
    } else {
        BigNode* prev = *bucket;
        while (prev->mpNext != node)
            prev = prev->mpNext;
        prev->mpNext = node->mpNext;
    }
    node->mpVptrA = (void*)0x0145b2f8;
    node->mpVptrB = (void*)0x0145b2ec;
    if (node->mpRef)
        node->mpRef->Release();
    node->mpVptrB = (void*)0x013eb938;
    node->mpVptrA = (void*)0x013ef094;
    operator_delete(node);
    --mnSize;
    return out;
}

// @ 0x00adca90
void AutoRefVec::DoInsertValue(CountedObj** pos, CountedObj** value)
{
    if (mpEnd != mpCapacity) {
        CountedObj** src = value;
        if (value >= pos && value < mpEnd)
            src = value + 1;
        if (mpEnd) {
            CountedObj* last = mpEnd[-1];
            mpEnd[0] = last;
            if (last)
                last->mRef.AddRef();
        }
        FUN_00ad7400((void**)pos, (void**)(mpEnd - 1), (void**)mpEnd);
        CountedObj* nv = *src;
        CountedObj* ov = *pos;
        if (nv != ov) {
            if (nv)
                nv->mRef.AddRef();
            *pos = nv;
            if (ov)
                ov->mRef.Release();
        }
        ++mpEnd;
        return;
    }

    int n = (int)(mpEnd - mpBegin);
    unsigned newCap = (n > 0) ? (unsigned)(n * 2) : 1;
    CountedObj** buf;
    if (newCap == 0)
        buf = 0;
    else
        buf = (CountedObj**)operator new(newCap * 4, g_SimulatorName, 0, 0, g_EastlAllocFile, 0xd1);

    int off = (int)((char*)pos - (char*)mpBegin);
    CountedObj** newPos = (CountedObj**)memcpy(buf, mpBegin, off) + (off >> 2);
    if (newPos) {
        CountedObj* v = *value;
        *newPos = v;
        if (v)
            v->mRef.AddRef();
    }
    int tail = (int)((char*)mpEnd - (char*)pos);
    CountedObj** newEnd = (CountedObj**)memcpy(newPos + 1, pos, tail) + (tail >> 2);
    if (mpBegin && ((unsigned*)mpBegin)[-1])
        operator_delete(mpBegin);
    mpEnd = newEnd;
    mpBegin = buf;
    mpCapacity = buf + newCap;
}

// @ 0x00adcc90
void NodeOwner::FreeNodes()
{
    mTable.clear();
}
