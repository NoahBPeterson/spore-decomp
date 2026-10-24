// Slice s00fa3860 -- SP::cTerrainSphere::ApplyModelFootprint (0x00fa3c10, 1740 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as s00fa2a20.
//
// Applies the "footprint" terrain decals described by a model's property list to the planet:
//   - 0x3b28c1d / 0x3b28c1e / 0x442151e: a footprint decal (size vector, offset vector, image key)
//     rendered through cTerrainSphere::FUN_00f9d5c0,
//   - 0x3b28c1b / 0x3b28c1c: a second decal resource drawn through FUN_00fa01e0,
//   - 0x3abc381..0x3abc386: an optional colored decal (created with FUN_00fa2920) whose per-face
//     bounding boxes are returned in the caller's array, then tinted by the properties.
#include "types.h"
#include <intrin.h>
#include <string.h>

typedef unsigned char uint8;

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct ResKey { uint32_t instance, type, group; };

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    float mOffset[3];
    float mfScale;
    float mRotation[9];

    Transform(const Transform& src);   // 0x0040ce80
    void RotateY(float angle);         // 0x004099b0
    __forceinline void ScaleBy(float s)
    {
        mfScale = mfScale * s;
        mnFlags |= 1;
        mnTransformCount += 1;
    }
};

struct Property {
    char pad0[0x12];
    uint16_t mnType;                   // +0x12
    const bool* GetBool();             // 0x0041e920
    const float* GetFloat();           // 0x0041ea70
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};

bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResKey* value);           // 0x006a1250
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* value);      // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* value);      // 0x006a1110
bool GetPropertyAsColorRGB(cPropertyList* list, uint32_t id, float* rgb);         // 0x006a11b0
bool GetFloatProperty(cPropertyList* list, uint32_t id, float* value);            // 0x0040cf10

extern const float kPi;                // 0x015b1190
extern const float kLerpBase[3];       // 0x015b11ac..0x015b11b4

// Atomic intrusive refcount at +8 (decrement, re-read, restore on underflow), as inlined by the original.
static __forceinline void ReleaseRef(void* o)
{
    volatile long* c = (volatile long*)((char*)o + 8);
    _InterlockedExchangeAdd(c, -1);
    long n = _InterlockedExchangeAdd(c, 0);
    if (n < 1) _InterlockedExchangeAdd(c, 1);
    else _InterlockedExchangeAdd(c, 0);
}
static __forceinline void AddRef(void* o)
{
    _InterlockedExchangeAdd((volatile long*)((char*)o + 8), 1);
}

struct cImage;
struct cImgRes {
    cImage* mpImage;
    void GetImageResource(void* resource);   // 0x00576650
};
struct ImageRef {
    cImgRes r;
    ImageRef() { r.mpImage = 0; }
    ~ImageRef() { if (r.mpImage) ReleaseRef(r.mpImage); }
};

struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void* GetCurrentMode();   // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void* v50();              // +0x50
};
IApp* App();                          // 0x0067dd10

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18();
    virtual void* GetResource(ResKey key, int type);   // +0x1c
};
IResourceManager* GetResourceManager();   // 0x0067dd60

extern char gSpecialMode;                 // 0x01654c10

struct cTerrainSphereDecal {
    char pad0[0x40];
    float r, g, b, a;                     // +0x40 color / alpha
    bool GetBBoxForFace(int face, float* box);   // 0x00fad140
};

struct LightInfo {
    char pad[0x59c];
    float color[3];                       // +0x59c
};

// eastl-style SPVector<T>; DoInsertKey4 is the original's grow-and-insert helper.
template<class T> struct SPVector {
    T* begin;                              // +0x00
    T* end;                                // +0x04
    T* cap;                                // +0x08
    void DoInsertKey4(T* pos, const T& val);   // 0x00b96600
};

// 8-byte entry { object pointer, padding } used by the two +0x8b0 / +0x8c4 lists.
struct Entry8 { void* obj; void* pad; };

// One of the four 0x14-byte sphere-light vectors at +0x218.
struct SphereLightGroup {
    void* begin;                           // +0x00
    void* end;                             // +0x04
    void* cap;                             // +0x08
    int   pad0;                            // +0x0c
    int   pad1;                            // +0x10
};

// Entry held by a SphereLightGroup (flags word at +0xb8).
struct SphereGroupEntry { char pad0[0xb8]; unsigned mFlags; };

// 0x14-byte record copied by the vector helper at 0x00fa4730.
struct Rec20 { unsigned w0, w1, w2, w3, w4; };

struct cTerrainSphere {
    char pad0[0x20c];
    LightInfo* mpLight;                   // +0x20c
    char pad210[0x08];                    // +0x210
    SphereLightGroup mGroups[4];          // +0x218 (4 * 0x14)
    char pad268[0x50];                    // +0x268
    SPVector<unsigned> mVec2b8;           // +0x2b8 (free index list)
    char pad2c4[0x08];                    // +0x2c4
    int* mCur2cc;                         // +0x2cc
    int* mCur2d0;                         // +0x2d0
    char pad2d4[0x0c];                    // +0x2d4
    SPVector<unsigned> mVec2e0;           // +0x2e0 (owned object pointers)
    char pad2ec[0x08];                    // +0x2ec
    SPVector<unsigned> mVec2f4;           // +0x2f4 (sphere-light pointers)
    char pad300[0x484];                   // +0x300
    char* mRecBase;                       // +0x784 (0xac-byte terrain records)
    char* mRecEnd;                        // +0x788
    char pad78c[0x124];                   // +0x78c
    SPVector<Entry8> mVec8b0;             // +0x8b0
    char pad8bc[0x08];                    // +0x8bc
    SPVector<Entry8> mVec8c4;             // +0x8c4
    char pad8d0[0x0c];                    // +0x8d0
    void* mpFaceQuads;                    // +0x8dc

    void ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal);
    void DrawFootprint(Transform* xform, float z, cImage* img, const Vector2* off, bool flag, float* faceBoxes, void* a3);   // 0x00f9d5c0
    void DrawResource(Transform* xform, float z, void* res, void* a3);                                                // 0x00fa01e0
    cTerrainSphereDecal* CreateDecal(void* res, Transform* xform, float z, int layer);                                // 0x00fa2920

    void FUN_00fa3b30();                          // 0x00fa3b30
    int  FUN_00fa3ba0();                          // 0x00fa3ba0
    void FUN_00fa42e0(void* key);                 // 0x00fa42e0
    void FUN_00fa4360(void* key);                 // 0x00fa4360
    void Relevel(void* a2, char flag);            // 0x00fa43e0
    void FUN_00fa44d0(int key);                   // 0x00fa44d0
    int  FUN_00fa45c0(Vector3* p2, Vector3* p3, float p4);   // 0x00fa45c0
    void FUN_00fa4660(int key);                   // 0x00fa4660
    void DrawLayerRTT(void* viewer, void* a3);    // 0x00fa3860
    void FUN_00fa29b0(int key);                   // 0x00fa29b0
    void FUN_00f9e3a0();                          // 0x00f9e3a0
    void FUN_00f998f0();                          // 0x00f998f0
    void DrawAtmoQuads(void* viewer, void* a3);   // 0x00f98530
    void RefractionMapRender(void* viewer, void* a3);   // 0x00fa2a20
};

// @ 0x00fa3c10
void cTerrainSphere::ApplyModelFootprint(const Transform* modelXform, cPropertyList* props, void* a3, float* faceBoxes, bool bDecal)
{
    ResKey key = { 0, 0, 0 };
    bool bFootprintDone = false;
    bool bSpecial = (App()->GetCurrentMode() == (void*)&gSpecialMode);

    Vector3 fp = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsVector3(props, 0x3b28c1d, &fp)) {
        float width = fp.x;
        float angle = fp.y * kPi * 2.0f;
        float z = fp.z;
        Transform xform(*modelXform);
        bool flag = bSpecial;
        if (props) {
            Property* p;
            if (props->GetProperty(0x589e78c, p) && p->mnType == 1)
                flag = *p->GetBool();
        }
        Vector2 off = { 0.0f, 0.0f };
        GetPropertyAsVector2(props, 0x3b28c1e, &off);
        xform.RotateY(angle);
        xform.ScaleBy(width);
        cImgRes img;
        img.mpImage = 0;
        cImage* image = 0;
        if (GetPropertyAsKey(props, 0x442151e, &key)) {
            void* res = GetResourceManager()->GetResource(key, 2);
            img.GetImageResource(res);
            image = img.mpImage;
        }
        DrawFootprint(&xform, z, image, &off, flag, faceBoxes, a3);
        bFootprintDone = true;
        if (image) ReleaseRef(image);
    }

    Vector3 fp2 = { 10.0f, 0.0f, 0.1f };
    if (!bSpecial && GetPropertyAsKey(props, 0x3b28c1b, &key)) {
        GetPropertyAsVector3(props, 0x3b28c1c, &fp2);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            AddRef(res);
            float angle = fp2.y * kPi * 2.0f;
            float z = fp2.z;
            Transform xform(*modelXform);
            xform.RotateY(angle);
            xform.ScaleBy(fp2.x);
            DrawResource(&xform, z, res, a3);
            ReleaseRef(res);
        }
    }

    if (bDecal && GetPropertyAsKey(props, 0x3abc381, &key)) {
        Vector3 dv = { 10.0f, 0.0f, 1.0f };
        GetPropertyAsVector3(props, 0x3abc382, &dv);
        void* res = GetResourceManager()->GetResource(key, 2);
        if (res) {
            Transform xform(*modelXform);
            xform.ScaleBy(dv.x);   // scale first, as in the original
            float angle = dv.y * kPi * 2.0f;
            xform.RotateY(angle);
            cTerrainSphereDecal* decal = CreateDecal(res, &xform, 0.0f, 0);

            if (faceBoxes && !bFootprintDone) {
                for (int face = 0; face < 6; face++) {
                    float box[4];
                    if (decal->GetBBoxForFace(face, box)) {
                        faceBoxes[face * 4 + 0] = box[0];
                        faceBoxes[face * 4 + 1] = box[1];
                        faceBoxes[face * 4 + 2] = box[2];
                        faceBoxes[face * 4 + 3] = box[3];
                    }
                    else {
                        faceBoxes[face * 4 + 0] = 0.0f;
                        faceBoxes[face * 4 + 1] = 0.0f;
                        faceBoxes[face * 4 + 2] = 0.0f;
                        faceBoxes[face * 4 + 3] = 0.0f;
                    }
                }
            }

            float col[3] = { 1.0f, 1.0f, 1.0f };
            if (GetPropertyAsColorRGB(props, 0x3abc383, col)) {
                decal->r = col[0];
                decal->g = col[1];
                decal->b = col[2];
            }
            if (props) {
                Property* p;
                if (props->GetProperty(0x3abc384, p) && p->mnType == 0xd)
                    decal->a = *p->GetFloat();
                if (props->GetProperty(0x3abc385, p) && p->mnType == 1 && *p->GetBool() && mpLight) {
                    float t = 1.0f;
                    GetFloatProperty(props, 0x3abc386, &t);
                    LightInfo* li = mpLight;
                    decal->r = ((li->color[0] - kLerpBase[0]) * t + kLerpBase[0]) * decal->r;
                    decal->g = decal->g * ((li->color[1] - kLerpBase[1]) * t + kLerpBase[1]);
                    decal->b = decal->b * ((li->color[2] - kLerpBase[2]) * t + kLerpBase[2]);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Sphere-light / terrain-record bookkeeping (0x00fa3b30 .. 0x00fa4730).
// ---------------------------------------------------------------------------

struct cSPColorRGBA { float r, g, b, a; };

// Direct (non-virtual) calls into the viewer class used by DrawLayerRTT.
struct cViewer {
    void SetClearColor(const cSPColorRGBA& c);   // 0x007c3c20
    void Clear(unsigned mask);                   // 0x007c3c50
    bool Copy(cViewer* src, bool a, bool b);     // 0x007c50b0
    void SetRaster(int* raster, bool a);         // 0x007c4be0
    void SetTarget(void* raster);                // 0x007c3cb0
};

// The "property list" the light helpers query.
struct cDirectPropertyList {
    bool GetDescription(uint32_t id) const;      // 0x006a25a0
};

// 0x24-byte sphere light created by FUN_00fa45c0.
struct cTerrainSphereLight {
    int   mId;             // +0x00
    Vector3 mVec1;         // +0x04
    Vector3 mVec2;         // +0x10
    float mScalar;         // +0x1c
    unsigned char mFlag20; // +0x20
};

// Object held by the +0x2e0 list (plain key at +0, intrusive refcount at +0x1b8).
struct SphereChild {
    int   mKey;            // +0x00
    char  pad004[0x1ac];   // +0x04
    int   mField1b0;       // +0x1b0
    int   mField1b4;       // +0x1b4
    void* mField1b8;       // +0x1b8
    void FUN_00fa23d0(cTerrainSphereLight* light);   // 0x00fa23d0
    void FUN_00f9f1a0();                             // 0x00f9f1a0
};

// Object held by the +0x8b0 / +0x8c4 lists (released through vtable slot 4).
struct ReleasedObj {
    virtual void v00();
    virtual void v04();
};

// Manager returned by PropertyManager() (slot 0x2c).
struct PropertyMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool v2c(void* a, void* b, void** out);
};

// Manager returned by FUN_0067dda0() (slot 0x14).
struct DelMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void v14(void* a, void* b);
};

// 0xac-byte terrain record walked by Relevel.
struct TerrainRec {
    char   pad000[0x38];   // +0x00
    float  mFaceBoxes[0x18];   // +0x38
    void*  mField98;       // +0x98
    void*  mFieldA0;       // +0xa0
    unsigned mFlags;       // +0xa4
    char   pad0a8[4];      // +0xa8
};

// growable vector of 0x14-byte records (FUN_00fa4730).
struct VecRec20 {
    Rec20* begin;          // +0x00
    Rec20* end;            // +0x04
    Rec20* cap;            // +0x08
    void FUN_00fa1840(Rec20* pos, unsigned n, void* local);   // 0x00fa1840
    void resize(unsigned n);
};

extern int g_lightIdCounter;                       // 0x15b14e4

void* PropertyManager();                           // 0x0067de30
void* FUN_0067dda0();                              // 0x0067dda0
void* AllocNamed(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  FreeNamed(void* p);                          // 0x00f47380
void  FUN_00f9ae80(void* a, void* b, void* c);     // 0x00f9ae80
Rec20* copy_Rec20(const Rec20* a, const Rec20* b, Rec20* c);   // 0x00951bf0

// 0x00fa3b30: walk the four sphere-light groups and register every live entry.
// @ 0x00fa3b30
void cTerrainSphere::FUN_00fa3b30()
{
    int i = 0;
    SphereLightGroup* g = mGroups;
    do {
        unsigned n = (unsigned)((unsigned*)g->end - (unsigned*)g->begin);
        unsigned j = 0;
        if (n != 0) {
            do {
                unsigned* slot = (unsigned*)g->begin + j;
                unsigned elem = *slot;
                if (elem != 0) {
                    unsigned flags = ((SphereGroupEntry*)elem)->mFlags;
                    if ((flags >> 3) & 1)
                        FUN_00fa29b0((i << 0x18) | j);
                }
                j++;
            } while (j < (unsigned)((unsigned*)g->end - (unsigned*)g->begin));
        }
        i++;
        g++;
    } while (i < 4);
}

// 0x00fa3ba0: pop a freed index, or append a zero and return its index.
// @ 0x00fa3ba0
int cTerrainSphere::FUN_00fa3ba0()
{
    if (mCur2cc == mCur2d0) {
        SPVector<unsigned>& v = mVec2b8;
        unsigned* p = v.end;
        int idx = (int)(v.end - v.begin);
        unsigned local = 0;
        if (p < v.cap) {
            v.end = p + 1;
            if (p)
                *p = 0;
            return idx;
        }
        v.DoInsertKey4(p, local);
        return idx;
    }
    int val = mCur2d0[-1];
    mCur2d0--;
    return val;
}

// 0x00fa42e0: remove the +0x8b0 entry whose object equals key.
// @ 0x00fa42e0
void cTerrainSphere::FUN_00fa42e0(void* key)
{
    int n = (int)(mVec8b0.end - mVec8b0.begin);
    if (n <= 0)
        return;
    Entry8* base = mVec8b0.begin;
    int idx = 0;
    Entry8* p = base;
    while (p->obj != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    p = base + idx;
    if (p + 1 < mVec8b0.end)
        FUN_00f9ae80(p + 1, mVec8b0.end, p);
    mVec8b0.end = mVec8b0.end - 1;
    void* o = mVec8b0.end->obj;
    if (o)
        ((ReleasedObj*)o)->v04();
}

// 0x00fa4360: remove the +0x8c4 entry whose object equals key.
// @ 0x00fa4360
void cTerrainSphere::FUN_00fa4360(void* key)
{
    int n = (int)(mVec8c4.end - mVec8c4.begin);
    if (n <= 0)
        return;
    Entry8* base = mVec8c4.begin;
    int idx = 0;
    Entry8* p = base;
    while (p->obj != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    p = base + idx;
    if (p + 1 < mVec8c4.end)
        FUN_00f9ae80(p + 1, mVec8c4.end, p);
    mVec8c4.end = mVec8c4.end - 1;
    void* o = mVec8c4.end->obj;
    if (o)
        ((ReleasedObj*)o)->v04();
}

// 0x00fa43e0: rebuild the per-record property lists from the model description.
// @ 0x00fa43e0
void cTerrainSphere::Relevel(void* a2, char flag)
{
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    int count = (int)((mRecEnd - mRecBase) / 0xac);
    void* cur = 0;
    if (count <= 0)
        return;
    int off = 0;
    do {
        TerrainRec* rec = (TerrainRec*)(mRecBase + off);
        if (((rec->mFlags >> 0x1b) & 1) != 0 || flag != 0) {
            if (cur) {
                void* old = cur;
                cur = 0;
                ((ReleasedObj*)old)->v04();
            }
            void* out;
            bool ok = pm->v2c(rec->mField98, rec->mFieldA0, &out);
            cur = out;
            if (ok) {
                ApplyModelFootprint((const Transform*)rec, (cPropertyList*)out, a2, rec->mFaceBoxes, false);
                rec->mFlags &= 0xf7ffffff;
                cur = out;
            }
        }
        off += 0xac;
        count--;
    } while (count != 0);
    if (cur)
        ((ReleasedObj*)cur)->v04();
}

// 0x00fa44d0: destroy the +0x2e0 object whose key equals key.
// @ 0x00fa44d0
void cTerrainSphere::FUN_00fa44d0(int key)
{
    int n = (int)(mVec2e0.end - mVec2e0.begin);
    if (n <= 0)
        return;
    SphereChild** base = (SphereChild**)mVec2e0.begin;
    int idx = 0;
    SphereChild** p = base;
    while ((*p)->mKey != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    SphereChild* obj = *p;
    unsigned* dst = mVec2e0.begin + idx;
    unsigned* src = dst + 1;
    unsigned* end = mVec2e0.end;
    if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
    mVec2e0.end = end - 1;
    FUN_00fa29b0(obj->mKey);
    obj->mKey = 0;
    void* r = obj->mField1b8;
    if (r) {
        obj->mField1b8 = 0;
        ReleaseRef(r);
    }
    DelMgr* dm = (DelMgr*)FUN_0067dda0();
    dm->v14((void*)obj->mField1b0, (void*)obj->mField1b4);
    obj->FUN_00f9f1a0();
    FreeNamed(obj);
}

// 0x00fa45c0: create and register a sphere light; returns its id.
// @ 0x00fa45c0
int cTerrainSphere::FUN_00fa45c0(Vector3* p2, Vector3* p3, float p4)
{
    cTerrainSphereLight* l = (cTerrainSphereLight*)AllocNamed(0x24, "Terrain/Sphere/cTerrainSphereLight", 0, 0, 0, 0);
    int id = g_lightIdCounter;
    l->mId = id;
    g_lightIdCounter = id + 1;
    l->mVec1 = *p2;
    l->mVec2 = *p3;
    l->mScalar = p4;
    l->mFlag20 = 1;
    SPVector<unsigned>* v = &mVec2f4;
    unsigned* p = v->end;
    unsigned lu = (unsigned)l;
    if (p < v->cap) {
        v->end = p + 1;
        if (p)
            *p = (unsigned)l;
        return l->mId;
    }
    v->DoInsertKey4(p, lu);
    return ((cTerrainSphereLight*)lu)->mId;
}

// 0x00fa4660: notify every +0x2e0 object and destroy the sphere light with this id.
// @ 0x00fa4660
void cTerrainSphere::FUN_00fa4660(int key)
{
    int n = (int)(mVec2f4.end - mVec2f4.begin);
    if (n <= 0)
        return;
    unsigned* base = mVec2f4.begin;
    int idx = 0;
    unsigned* p = base;
    cTerrainSphereLight* light;
    while ((light = (cTerrainSphereLight*)*p)->mId != key) {
        idx++;
        p++;
        if (idx >= n)
            return;
    }
    int cnt = (int)(mVec2e0.end - mVec2e0.begin);
    for (int i = 0; i < cnt; i++)
        ((SphereChild*)(void*)mVec2e0.begin[i])->FUN_00fa23d0(light);
    unsigned* dst = mVec2f4.begin + idx;
    unsigned* src = dst + 1;
    unsigned* end = mVec2f4.end;
    if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
    mVec2f4.end = end - 1;
    FreeNamed(light);
}

// 0x00fa4730: resize the 0x14-byte record vector (shrink path).
// @ 0x00fa4730
void VecRec20::resize(unsigned n)
{
    Rec20* e = end;
    unsigned count = (unsigned)(e - begin);
    if (n > count) {
        Rec20 local;
        FUN_00fa1840(e, n - count, &local);
        return;
    }
    Rec20* dst = begin + n;
    copy_Rec20(e, e, dst);
    end -= (e - dst);
}

// ---------------------------------------------------------------------------
// DrawLayerRTT (0x00fa3860).
// ---------------------------------------------------------------------------

// cTerrainSphere itself must stay non-polymorphic (the committed functions rely
// on its field offsets), so its vtable is reached through this view.
struct TerrainVt {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void* v10();              // +0x10
};
struct ModeVt {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* v1c();              // +0x1c
};
struct FaceQuadVt {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void* vA0();              // +0xa0
};
struct FaceDrawVt {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(int a, int b, void** c, void* d);   // +0x0c
};
struct MgrVt {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(int* a, int* b, int* c, void* d);   // +0x60
};

struct SphereData {
    char  pad0[0x42c];
    float mColor[3];                  // +0x42c
};
struct RasterView {
    char pad0[0x12];
    char mLayerIndex;                 // +0x12
};

extern cDirectPropertyList* gAppProperties;       // 0x15fd918
extern unsigned g_rasterStageDirty;               // 0x16fa3a8
extern void** g_ppRaster16c9f58;                  // 0x16c9f58
extern int g_rasterCur16f9674;                    // 0x16f9674
extern void* g_rasterTable16f9650[17];            // 0x16f9650
extern unsigned g_16f9554;                        // 0x16f9554
extern int g_16fa1c4;                             // 0x16fa1c4
extern int g_16fa1c8;                             // 0x16fa1c8
extern int g_16fa1d4;                             // 0x16fa1d4
extern int g_16fa1d8;                             // 0x16fa1d8
extern int g_16fa1dc;                             // 0x16fa1dc
extern unsigned g_16fa3a0;                        // 0x16fa3a0
extern int g_16f9480;                             // 0x16f9480
extern cViewer g_viewer16c9f60;                   // 0x16c9f60
extern cViewer g_viewer16ca0d8;                   // 0x16ca0d8
extern int g_15b1200;                             // 0x15b1200
extern int g_15b1208;                             // 0x15b1208
extern int g_15b1210;                             // 0x15b1210

void* FUN_0067ddb0();                             // 0x0067ddb0
void  D3D9Sync();                                 // 0x011f21a0

// @ 0x00fa3860
void cTerrainSphere::DrawLayerRTT(void* viewer, void* a3)
{
    cDirectPropertyList* props = gAppProperties;
    bool b = props->GetDescription(0x1cb22fe0);
    if (b) {
        void* raster = *g_ppRaster16c9f58;
        g_rasterStageDirty |= 0x200;
        g_rasterCur16f9674 = 0;
        unsigned bit = 1;
        for (void** p = g_rasterTable16f9650; p < g_rasterTable16f9650 + 17; p++) {
            if (*p == raster) {
                g_rasterStageDirty |= bit;
                *p = 0;
            }
            bit = (bit << 1) | (bit >> 31);
        }
        SphereData* d = (SphereData*)((TerrainVt*)this)->v10();
        cSPColorRGBA col;
        col.r = d->mColor[0];
        col.g = d->mColor[1];
        col.b = d->mColor[2];
        col.a = 0.0f;
        g_viewer16c9f60.SetClearColor(col);
        for (int i = 0; i < 6; i++) {
            ((RasterView*)raster)->mLayerIndex = (char)i;
            g_viewer16c9f60.SetTarget(raster);
            g_viewer16c9f60.Clear(1);
        }
        g_rasterCur16f9674 = *(int*)g_ppRaster16c9f58;
        g_rasterStageDirty |= 0x200;
        g_16f9554 |= 0x73;
        g_16fa1c4 = 3;
        g_16fa1c8 = 3;
        g_16fa1d8 = 2;
        g_16fa1d4 = 2;
        g_16fa1dc = 2;
    }
    if (viewer == 0) {
        IApp* app = App();
        void* m = app->v50();
        viewer = ((ModeVt*)m)->v1c();
    }
    g_viewer16ca0d8.Copy((cViewer*)viewer, false, false);
    g_viewer16ca0d8.SetRaster(&g_15b1200, true);
    SphereData* d2 = (SphereData*)((TerrainVt*)this)->v10();
    cSPColorRGBA col2;
    col2.r = d2->mColor[0];
    col2.g = d2->mColor[1];
    col2.b = d2->mColor[2];
    col2.a = 0.0f;
    g_viewer16ca0d8.SetClearColor(col2);
    g_viewer16ca0d8.Clear(7);
    b = props->GetDescription(0x2be0cf8e);
    if (b)
        DrawAtmoQuads(&g_viewer16ca0d8, a3);
    b = props->GetDescription(0xe13ce337);
    if (b) {
        if (mpFaceQuads == 0)
            FUN_00f9e3a0();
        g_16fa3a0 |= 2;
        void* local = &g_viewer16ca0d8;
        g_16f9480 = 7;
        D3D9Sync();
        void* q = ((FaceQuadVt*)mpFaceQuads)->vA0();
        ((FaceDrawVt*)q)->v0c(0, 0x12, &local, a3);
        g_16fa3a0 |= 2;
        g_16f9480 = 0xf;
    } else {
        if (mpFaceQuads != 0)
            FUN_00f998f0();
    }
    b = props->GetDescription(0x3dcdb1d1);
    if (b)
        RefractionMapRender(&g_viewer16ca0d8, a3);
    b = gAppProperties->GetDescription(0x552b4af);
    if (b) {
        void* m = FUN_0067ddb0();
        ((MgrVt*)m)->v60(&g_15b1200, &g_15b1208, &g_15b1210, a3);
    }
}
