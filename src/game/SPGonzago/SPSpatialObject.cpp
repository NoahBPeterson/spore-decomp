// src/game/SPGonzago/SPSpatialObject.cpp -- migrated from slice(s) s01353d90, s00c89d60, s00c88e30, s00c87be0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpatialObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include "SP/cCommunity.h"
#include "SP/cGameData.h"
#include "SP/cISerializableObject.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern void*       kSpatialObjectSerializerList;  // 0x0157a1f8
#include <math.h>
#include <intrin.h>
#include <stddef.h>

// ---- items of slice s00c87be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*       kSpatialObjectSerializerList;  // 0x0157a1f8
struct VObj174 {
virtual void     v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void     v010();
virtual void v014();
virtual VObj174* v018();
virtual VObj174* v01c();
virtual VObj174* v020();
virtual void v024();
virtual void v028();
virtual float* v02c();
virtual void     v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void     v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual VObj174* v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void     v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void     v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void     v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual bool     v090(void** out);
virtual void v094();
virtual bool v098(void* r);
virtual void v09c();
virtual void     v0a0();
virtual void v0a4();
virtual void v0a8();
virtual unsigned int v0ac();
virtual void     v0b0();
virtual void v0b4();
virtual VObj174* v0b8(uint32_t id, uint32_t arg);
virtual bool     v0bc();
virtual void v0c0();
virtual void v0c4();
    void GetCameraLocationInfo(void* pos, void* a, void* b, void* c);   // 0x007c3d30
};
namespace EA {
namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pData, uint32_t nCount, int endian);  // 0x0093aa70
}
}
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    cVarListSerializer(void* pObject, void** pList, uint32_t version);  // 0x00692f90
    bool Serialize(void* pStream);                                      // 0x00692900
    bool Read(void* pStream);                                           // 0x00693e10
};
struct cSpatialObject {
    void Write(void* pStream);
};
// ---- items of slice s00c87be0 end

// ---- items of slice s00c88e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   g_vtable1473758[]; // 0x01473758
extern uint32_t g_init1695310; // 0x01695310
struct Vec3 { float x, y, z; };
struct Transform;
struct cViewerShim {
    void GetCameraLocationInfo(Vec3* a, Vec3* b, Vec3* c, Vec3* d) const;   // 0x007c3d30
    void ProjectToScreen(Vec3* out, const Vec3* in) const;                  // 0x007c4180
};
struct cSPVector3_s00c8_8e30 {
    float x, y, z;
    cSPVector3_s00c8_8e30() {}
    cSPVector3_s00c8_8e30(const cSPVector3_s00c8_8e30& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00c8_8e30& operator=(const cSPVector3_s00c8_8e30& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quat { float x, y, z, w; };
struct BBox { Vec3 mn; Vec3 mx; };
struct Matrix3 { float m[9]; };
struct Transform {
    uint16_t flags;
    uint16_t version;
    Vec3     pos;
    float    scale;
    Matrix3  rot;
};
extern Vec3    g_vec1695248;   // 0x01695248
extern Quat    g_quat157a1c8;  // 0x0157a1c8
extern cSPVector3_s00c8_8e30 g_vec1695294;   // 0x01695294
extern Matrix3 g_mat16952ac;   // 0x016952ac
extern Vec3    g_vec1695304;   // 0x01695304
void*         FUN_00b3d3c0(void);                               // 0x00b3d3c0
struct Mgr { void Fn(void* p); };                               // 0x00b76ef0 (thiscall ret 4)
void          Matrix3FromQuaternion(Matrix3* m, Quat* q);       // 0x0059c190
struct Matrix3Shim { float m[9]; void Assign(const Matrix3* src) const; };  // 0x0041cb40
struct BBoxShim { Vec3 mn; Vec3 mx; void TransformBy(const Transform* t) const; };  // 0x00409dd0
float*        GetPropertyAsFloat(void* prop);                   // 0x0041ea70
void          SPUIHelpers_GetMainWindowArea(float* out);        // 0x00805ea0
struct AutoRef { void Assign(int a); };                         // 0x00478db0 (thiscall ret 4)
void*         App();                                            // 0x0067dd10
struct IUnk {
    virtual void AddRef();
    virtual void Release();
};
struct cSO;
#define VT(slot) (*(void***)this)[(slot) / 4]
struct cSO {
    void**   vt;            // +0x00
    Vec3     mPosition;     // +0x04
    Quat     mOrientation;  // +0x10
    BBox     mLocalExtents; // +0x20
    BBox     mWorldExtents; // +0x38
    uint32_t mFlags;        // +0x50
    uint32_t m54;           // +0x54
    uint32_t m58;           // +0x58
    float    m5c;           // +0x5c
    float    m60;           // +0x60
    float    f64;           // +0x64
    float    f68;           // +0x68
    uint8_t  b6c, b6d, b6e, b6f, b70, b71, b72, b73, b74, b75, b76, b77, b78;
    uint8_t  pad79[3];      // +0x79
    float    f7c;           // +0x7c
    float    f80;           // +0x80
    float    f84;           // +0x84
    float    f88;           // +0x88
    float    f8c;           // +0x8c
    uint32_t m90, m94, m98; // +0x90
    void*    mp9c;          // +0x9c  (mpModel)
    void*    mpA0;          // +0xa0  (mpModelWorld)
    uint8_t  bA4, bA5, bA6, bA7;
    uint32_t mA8, mAC, mB0;
    float    fB4;
    uint32_t mB8, mBC;
    void*    mpC0;          // +0xc0
    void*    mpC4;          // +0xc4
    uint32_t mC8;           // +0xc8

    bool funcE30();
    void func78h(cSPVector3_s00c8_8e30* out);
    void GetCommunityName(cSPVector3_s00c8_8e30* out);
    void SetLocalExtents(float* e, float scale);
    bool func9C();
    void func93F0(float* a, float* b);
    cSO();
    void LocalToWorldTransform(Transform* out);
    void SetModel(int a1, void* b);
    void funcA4h();
    bool func7Ch(char a4, float* out);
};
// ---- items of slice s00c88e30 end

// ---- items of slice s00c89d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_016952a0, DAT_016952a4, DAT_016952a8;   // direction basis
extern float DAT_016952f4, DAT_016952f8, DAT_016952fc;   // secondary basis
extern float DAT_01485720;                               // 1.0f
extern float DAT_01695248, DAT_0169524c, DAT_01695250;
extern char g_empty13ec47c;   // 0x13ec47c  empty-string sentinel
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct cSPVector3_s00c8_9d60 { float x, y, z; };
struct cSPBoundingBox_s00c8_9d60 { cSPVector3_s00c8_9d60 mMin; cSPVector3_s00c8_9d60 mMax; };
struct Matrix33 { float m[9]; };
struct SpatialXform {
    u16      mFlags;        // +0x00  bit 1 = ... , bit 2 = ... , bit 4 = payload valid
    u16      mVersion;      // +0x02  bumped on every payload write
    float    mPos[5];       // +0x04  position / direction payload
    Matrix33 mMatrix;       // +0x18
};
struct EffectInterface {
virtual void VS00();
virtual void VS04();
virtual void VS08();
virtual void VS0c();
virtual void VS10();
virtual void VS14();
    virtual void SetTransform(const SpatialXform* xf);   // +0x18
    virtual void VS1c();
    virtual void BuildTransform(SpatialXform* xf);       // +0x20
};
struct EffectElem {
    int   id;              // +0x00
    char  pad04[0x08 - 0x04];
    char  b08;             // +0x08  participates in the world-transform pass
    char  pad09[0x10 - 0x09];
    char  b10;             // +0x10  scale this->mf60 into the blend factor
    char  pad11[0x14 - 0x11];
    float f14;             // +0x14  blend factor
    float f18;             // +0x18  direction scale
    float f1c;             // +0x1c  local position x
    float f20;             // +0x20  local position y
    float f24;             // +0x24  local position z
    char  pad28[0x38 - 0x28];
    EffectInterface* p38;  // +0x38  effect interface
};
static inline void* vfn(void* obj, unsigned off);
struct Spatial {
    void** vt;                       // +0x00
    char   pad04[0x50 - 0x4];
    u32    mFlags50;                 // +0x50  attachment state bits
    char   pad54[0x5c - 0x54];
    float  mf5c;                     // +0x5c  cached scaled distance
    float  mf60;                     // +0x60  blend scale
    float  mf64;                     // +0x64  model scale
    char   pad68[0x90 - 0x68];
    void*  mNameData_90;             // +0x90  model-name string
    u32    mNameSize_94;             // +0x94
    u32    mNameCap_98;              // +0x98
    int*   p9c;                      // +0x9c  refcounted model holder
    int*   pa0;                      // +0xa0  model instance
    char   padA4[0xc0 - 0xa4];
    EffectElem* vecBegin;            // +0xc0
    EffectElem* vecEnd;              // +0xc4
    EffectElem* vecCap;              // +0xc8
    int    padCc;

    float* GetExtents() { return ((float* (__thiscall*)(Spatial*))vfn(this, 0x68))(this); }
};
static inline void* vfn(void* obj, unsigned off) { return ((void**)*(void***)obj)[off / 4]; }
static inline cSPVector3_s00c8_9d60 Rotate(const Matrix33* m, const cSPVector3_s00c8_9d60& v) {
    cSPVector3_s00c8_9d60 r;
    r.x = m->m[0] * v.x + m->m[3] * v.y + m->m[6] * v.z;
    r.y = m->m[1] * v.x + m->m[4] * v.y + m->m[7] * v.z;
    r.z = m->m[2] * v.x + m->m[5] * v.y + m->m[8] * v.z;
    return r;
}
void  __fastcall FUN_0041cb40(Matrix33* self, int, const void* src);  // 0x41cb40 matrix ctor
void  __fastcall FUN_00478db0(void* self, int, void* src);            // 0x478db0 ref assign
void* __cdecl    FUN_00b3d240();                                      // 0xb3d240 simulator
char  __fastcall FUN_00b33e10(void* self, int, u32 key);              // 0xb33e10
void* __cdecl    FUN_00401010();                                      // 0x401010 noun manager
void* __cdecl    FUN_0059c190(void* dst, void* src);                  // 0x59c190 matrix copy
void  __fastcall FUN_00b5f950(void* self, int, void* model);           // 0xb5f950 model attach
struct SpatialBaseDtor {
    void Destroy();  // 0x00c898f0
};
struct EffectVecDtor {
    void Destroy();  // 0x00c895f0
};
void __fastcall FUN_00c897e0(void* self, int, void* xf);   // 0xc897e0 local->world
void __fastcall FUN_00409dd0(void* self, int, void* xf);   // 0x409dd0 box transform
static EffectElem* FindEffect(Spatial* s, int id)
{
    for (EffectElem* p = s->vecBegin; p != s->vecEnd; ++p)
        if (p->id == id) return p;
    return 0;
}
static void InitXform(SpatialXform* xf)
{
    xf->mFlags = 0;
    xf->mVersion = 0;
    xf->mPos[0] = DAT_016952f4;
    xf->mPos[1] = DAT_016952f8;
    xf->mPos[2] = DAT_016952fc;
    xf->mPos[3] = DAT_01485720;
    xf->mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf->mMatrix, 0, (const void*)0x016952d0);
}
struct RefHolder {
    void**   mpObject;    // +0x00
    uint32_t mFlags;      // +0x04
    char     pad08[0x40 - 0x08];
    int32_t  mRefCount;   // +0x40
};
typedef void (__thiscall* RefReleaseFn)(void* self, void* holder, unsigned char del);
struct StrAssigner {
    void Assign(const void* first, const void* last);   // 0x454cb0
};
struct ModelDesc {                    // stack descriptor handed to the noun manager
    u32  mTag;                        // +0x00  0x2ea8fb98
    u16  mKind;                       // +0x04  4 = plain, 2 = ...
    u16  mPad06;
};
struct EffectElementRef {
    void**  mpObject;    // +0x00 finished object (size >= 0x170)
    u32     mFlags;      // +0x04 bit 31 = owned
};
struct SimFlags {
    char pad[0x10c];
    u8   mFlag10c;                    // 0x10c
    u8   mFlag10d;                    // 0x10d
};
struct ModelHolder {                  // refcounted model instance
    void** vt;                        // +0x00
    u32    mFlags04;                  // +0x04
    u16    mFlags08;                  // +0x08  dirty bits
    u16    mVersion0a;                // +0x0a  write counter
    float  mPos0c[3];                 // +0x0c
    float  mf18;                      // +0x18
    Matrix33 mMatrix1c;               // +0x1c
    int32_t mRefCount40;              // +0x40
    float  mf6c;                      // +0x6c
    float  mf70;                      // +0x70
};
// ---- items of slice s00c89d60 end

// ---- items of slice s01353d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void DefaultOffset();            // 0x00692ca0  Simulator::Attribute::DefaultOffset
typedef bool (*ReadFn)(void*, void*);
typedef bool (*WriteFn)(void*, void*);
typedef void (*ReadTextFn)(const void*, void*);
typedef void (*WriteTextFn)(char*, void*);
typedef bool (*UnkFn)();
typedef bool (*Unk2Fn)(void*, const char*, int);
struct Attribute;
typedef void* (*OffsetFn)(Attribute*);
void* DefaultOffset(Attribute*);                       // 0x692ca0
bool  rd_b6e3a0_P(void*, void*);
bool  wr_ac88c0_P(void*, void*);
void  rt_6930f0_P(const void*, void*);
void  wt_695010_P(char*, void*);
bool  uk_00b1fbf0_P();
bool  u2_acbba0_P(void*, const char*, int);
bool  rd_ae33d0_O(void*, void*);
bool  wr_ae3400_O(void*, void*);
void  rt_693120_O(const void*, void*);
void  wt_695040_O(char*, void*);
bool  uk_00b1fbf0_O();
bool  u2_ae5700_O(void*, const char*, int);
bool  rd_572810_D(void*, void*);
bool  wr_ac88f0_D(void*, void*);
void  rt_6930b0_D(const void*, void*);
void  wt_694fc0_D(char*, void*);
bool  uk_00b1fbf0_D();
bool  u2_acbb80_D(void*, const char*, int);
bool  rd_ac8750_B(void*, void*);
bool  wr_ac8780_B(void*, void*);
void  rt_693090_B(const void*, void*);
void  wt_694fa0_B(char*, void*);
bool  uk_00b1fbf0_B();
bool  u2_57ce00_B(void*, const char*, int);
bool  rd_572810_S(void*, void*);
bool  wr_572840_S(void*, void*);
void  rt_693090_S(const void*, void*);
void  wt_694f00_S(char*, void*);
bool  uk_00b1fbf0_S();
bool  u2_675ca0_S(void*, const char*, int);
bool  rd_ae3430_K(void*, void*);
bool  wr_ae3450_K(void*, void*);
void  rt_693150_K(const void*, void*);
void  wt_695080_K(char*, void*);
bool  uk_00b1fbf0_K();
bool  u2_ae5720_K(void*, const char*, int);
bool  rd_c88b60_E(void*, void*);
bool  wr_c88b80_E(void*, void*);
void  rt_c2e4e0_E(const void*, void*);
void  wt_692fb0_E(char*, void*);
bool  uk_00b1fbf0_E();
bool  u2_ac8050_E(void*, const char*, int);
struct Attribute {
  const char* name;
  uint32_t id;
  unsigned offset;
  int field_0C, field_10, field_14;
  void* pCurrentObject;
  int field_1C;
  OffsetFn offsetFunction;
  ReadFn readFunction;
  WriteFn writeFunction;
  ReadTextFn readTextFunction;
  WriteTextFn writeTextFunction;
  UnkFn field_34;
  Unk2Fn field_38;

  Attribute() {}
  __forceinline Attribute(const char* n, uint32_t i, unsigned o, ReadFn r, WriteFn w, ReadTextFn rt,
                          WriteTextFn wt, UnkFn u, Unk2Fn u2) {
    name = n;
    id = i;
    pCurrentObject = 0;
    field_1C = 0;
    offsetFunction = DefaultOffset;
    readFunction = r;
    writeFunction = w;
    readTextFunction = rt;
    writeTextFunction = wt;
    field_34 = u;
    field_38 = u2;
    offset = o;
  }
};
Attribute gSpatialObjectAttributes[25];
// ---- items of slice s01353d90 end

// @ 0x00c88a90
void cSpatialObject::Write(void* pStream)
{
    uint32_t type = 0x1186577;
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    EA::IO::WriteUint32(pIo, &type, 1, 0);
    cVarListSerializer serializer(this, &kSpatialObjectSerializerList, 0x1a80d26);
    serializer.Serialize(pStream);
}

// @ 0x00c88e30
bool cSO::funcE30()
{
    void* app = App();
    void* viewer = ((void*(__thiscall*)(void*))(*(void***)app)[0x58 / 4])(app);
    Vec3 camLoc;
    ((cViewerShim*)viewer)->GetCameraLocationInfo(&camLoc, 0, 0, 0);
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    float px = pos->x;
    float py = pos->y;
    float pz = pos->z;
    if ((g_init1695310 & 1) == 0) {
        g_init1695310 |= 1;
        g_vec1695304 = g_vec1695248;
    }
    float fVar5 = sqrtf(px * px + (py * py + pz * pz)) - 10.0f;
    float fVar6 = sqrtf(camLoc.x * camLoc.x + (camLoc.z * camLoc.z + camLoc.y * camLoc.y)) - 10.0f;
    if (fVar5 < fVar6)
        fVar6 = fVar5;
    float dz = pz - camLoc.z;
    float dy = py - camLoc.y;
    float c2z = camLoc.z - g_vec1695304.z;
    float c2y = camLoc.y - g_vec1695304.y;
    float dx = px - camLoc.x;
    float c2x = camLoc.x - g_vec1695304.x;
    float dp = (dx * c2x + dz * c2z) + dy * c2y;
    float dd = (dz * dz + dy * dy) + dx * dx;
    float disc = dp * dp - (((c2x * c2x + c2z * c2z) + c2y * c2y) - fVar6 * fVar6) * dd;
    if (0.0f > disc)
        return false;
    {
        float root = sqrtf(disc);
        if (0.0f > root - dp)
            return false;
        if (-dp - root > dd)
            return false;
        return true;
    }
}

// @ 0x00c89160
void cSO::SetLocalExtents(float* e, float scale)
{
    *(Vec3*)&mLocalExtents.mx = *(Vec3*)(e + 3);
    *(Vec3*)&mLocalExtents.mn = *(Vec3*)(e + 0);
    *(Vec3*)&mWorldExtents.mx = *(Vec3*)(e + 3);
    *(Vec3*)&mWorldExtents.mn = *(Vec3*)(e + 0);

    mWorldExtents.mn.x *= scale;
    mWorldExtents.mn.y *= scale;
    mWorldExtents.mn.z *= scale;
    mWorldExtents.mx.x *= scale;
    mWorldExtents.mx.y *= scale;
    mWorldExtents.mx.z *= scale;
    f64 = scale;
    f7c = scale;

    _ReadWriteBarrier();
    float cz = (mWorldExtents.mx.z + mWorldExtents.mn.z) * 0.5f;
    _ReadWriteBarrier();
    float cx = (mWorldExtents.mx.x + mWorldExtents.mn.x) * 0.5f;
    _ReadWriteBarrier();
    float cy = (mWorldExtents.mx.y + mWorldExtents.mn.y) * 0.5f;
    _ReadWriteBarrier();
    float hz = mWorldExtents.mx.z - cz;
    _ReadWriteBarrier();
    float hx = mWorldExtents.mx.x - cx;
    _ReadWriteBarrier();
    float hy = mWorldExtents.mx.y - cy;
    _ReadWriteBarrier();
    float nhx = mWorldExtents.mn.x - cx;
    _ReadWriteBarrier();
    float nhy = mWorldExtents.mn.y - cy;
    _ReadWriteBarrier();
    float nhz = mWorldExtents.mn.z - cz;
    float lenA = (float)sqrt((double)hz * hz + (double)(hx * hx) + (double)(hy * hy));
    float lenB = (float)sqrt((double)nhz * nhz + (double)(nhx * nhx) + (double)(nhy * nhy));

    void* m = mp9c;
    if (m != 0 && mpA0 != 0) {
        float v = ((float(__thiscall*)(void*, void*))(*(void***)mpA0)[0x5c / 4])(mpA0, m);
        m5c = v * scale;
    } else if (mFlags & 0x40) {
        m5c = *(float*)((char*)m + 0x6c) * scale;
    } else {
        m5c = (lenB > lenA) ? lenB : lenA;
    }

    float lenC = (float)sqrt((double)(hx * hx) + (double)(hy * hy));
    float lenD = (float)sqrt((double)(nhx * nhx) + (double)(nhy * nhy));
    m60 = (lenD > lenC) ? lenD : lenC;

    if (m != 0) {
        void* p = *(void**)((char*)m + 0x90);
        if (p != 0) {
            void** vt = *(void***)p;
            void* prop = 0;
            char ok = ((char(__thiscall*)(void*, unsigned int, void**))(vt[0x24 / 4]))(p, 0x0579ef6c, &prop);
            if (ok && prop != 0 && *(unsigned short*)((char*)prop + 0x12) == 0xd) {
                float* f = GetPropertyAsFloat(prop);
                m60 = *f;
            }
        }
    }
}

// @ 0x00c893b0
bool cSO::func9C()
{
    void* m = mp9c;
    if (m != 0) {
        unsigned int v = ((unsigned int*)m)[1];
        if (mFlags & 0x8000) {
            bool b14 = (v >> 14) & 1;
            bool b18 = (v >> 18) & 1;
            if (b14 && !b18)
                return true;
        } else {
            return (v >> 14) & 1;
        }
    }
    return false;
}

// @ 0x00c893f0
void cSO::func93F0(float* A, float* B)
{
    float dx = mLocalExtents.mx.x - mLocalExtents.mn.x;
    float dy = mLocalExtents.mx.y - mLocalExtents.mn.y;
    float dz = mLocalExtents.mx.z - mLocalExtents.mn.z;

    ((void(__thiscall*)(cSO*, float))VT(0x40))(this, 1.0f);

    float sLo = 1.0f;
    float sHi = 1.0f;
    if (dx > B[0]) { float t = B[0] / dx; if (t < sLo) sLo = t; }
    if (A[0] > dx) { float t = A[0] / dx; if (t > sHi) sHi = t; }
    if (dy > B[1]) { float t = B[1] / dy; if (t < sLo) sLo = t; }
    if (A[1] > dy) { float t = A[1] / dy; if (t > sHi) sHi = t; }
    if (dz > B[2]) { float t = B[2] / dz; if (t < sLo) sLo = t; }
    if (A[2] > dz) { float t = A[2] / dz; if (t > sHi) sHi = t; }

    if (sLo != 1.0f) {
        ((void(__thiscall*)(cSO*, float))VT(0x40))(this, sLo);
        return;
    }
    if (sHi != 1.0f) {
        for (int i = 0; i < 3; ++i) {
            float d[3]; d[0] = dx; d[1] = dy; d[2] = dz;
            if (d[i] * sHi > B[i]) {
                sHi = 1.0f;
                break;
            }
        }
        ((void(__thiscall*)(cSO*, float))VT(0x40))(this, sHi);
    }
}

// @ 0x00c89630
cSO::cSO()
{
    vt = g_vtable1473758;
    mPosition.x = g_vec1695248.x;
    mPosition.y = g_vec1695248.y;
    mPosition.z = g_vec1695248.z;
    mOrientation.x = g_quat157a1c8.x;
    mOrientation.y = g_quat157a1c8.y;
    mOrientation.z = g_quat157a1c8.z;
    mOrientation.w = g_quat157a1c8.w;
    mLocalExtents.mn.x = -0.5f;
    mLocalExtents.mn.y = -0.5f;
    mLocalExtents.mn.z = 0.0f;
    mLocalExtents.mx.x = 0.5f;
    mLocalExtents.mx.y = 0.5f;
    mLocalExtents.mx.z = 1.0f;
    mWorldExtents.mn.x = -0.5f;
    mWorldExtents.mn.y = -0.5f;
    mWorldExtents.mn.z = 0.0f;
    mWorldExtents.mx.x = 0.5f;
    mWorldExtents.mx.y = 0.5f;
    mWorldExtents.mx.z = 1.0f;
    mFlags = 0;
    m54 = 0;
    m58 = 0;
    m5c = 1.0f;
    m60 = 1.0f;
    f64 = 1.0f;
    f68 = 0.0f;
    b6c = 0; b6d = 0; b6e = 0;
    b6f = 1; b70 = 1; b71 = 1;
    b72 = 0; b73 = 0;
    b74 = 1; b75 = 1; b76 = 1; b77 = 1;
    b78 = 0;
    f7c = 1.0f;
    f80 = 12.0f;
    f84 = 5.0f;
    f88 = 0.0f;
    f8c = 1.0f;
    m90 = 0; m94 = 0; m98 = 0;
    mp9c = 0;
    mpA0 = 0;
    bA4 = 0; bA5 = 1; bA6 = 1; bA7 = 0;
    mA8 = 0;
    mAC = 0;
    mB0 = 1;
    fB4 = 0.0f;
    mB8 = 0;
    mA8 |= 2;
    mBC = 0;
    mpC0 = 0;
    mpC4 = 0;
    mC8 = 0;
}

// @ 0x00c897e0
void cSO::LocalToWorldTransform(Transform* out)
{
    out->rot = g_mat16952ac;
    out->scale = 1.0f;
    out->pos = g_vec1695248;
    out->flags = 0;
    out->version = 0;
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    out->pos = *pos;
    out->flags |= 4;
    out->version++;
    Quat* q = (Quat*)((void*(__thiscall*)(cSO*))VT(0x30))(this);
    Matrix3 m;
    Matrix3FromQuaternion(&m, q);
    out->flags |= 2;
    out->version++;
    out->rot = m;
}

// @ 0x00c89890
void cSO::SetModel(int a1, void* b)
{
    ((void(__thiscall*)(cSO*))VT(0xa4))(this);
    ((AutoRef*)&mp9c)->Assign(a1);
    void* old = mpA0;
    if (b != old) {
        if (b != 0)
            ((IUnk*)b)->AddRef();
        mpA0 = b;
        if (old != 0)
            ((IUnk*)old)->Release();
    }
}

// @ 0x00c898f0
void cSO::funcA4h()
{
    void* pMVar3 = mp9c;
    if (pMVar3 == 0)
        return;
    ((Mgr*)FUN_00b3d3c0())->Fn(pMVar3);
    pMVar3 = mp9c;
    {
        void* iface = *(void**)pMVar3;
        ((void(__thiscall*)(void*, void*, int))(*(void***)iface)[0x16c / 4])(iface, pMVar3, 0);
    }
    pMVar3 = mp9c;
    void* pOwner = *(void**)((char*)pMVar3 + 0x64);
    if (pOwner != 0) {
        *(void**)((char*)pMVar3 + 0x64) = 0;
        ((IUnk*)pOwner)->Release();
    }
    pMVar3 = mp9c;
    if (pMVar3 != 0) {
        mp9c = 0;
        int rc = *(int*)((char*)pMVar3 + 0x40);
        if (rc > 1) {
            *(int*)((char*)pMVar3 + 0x40) = rc - 1;
        } else {
            void* iface = *(void**)pMVar3;
            unsigned char b = (unsigned char)(((((unsigned int)*(int*)((char*)pMVar3 + 4)) >> 31) & 1) ? 1 : 0);
            ((void(__thiscall*)(void*, void*, unsigned int))(*(void***)iface)[0x170 / 4])(iface, pMVar3, b);
        }
    }
    if (mpA0 != 0) {
        void* p = mpA0;
        mpA0 = 0;
        ((IUnk*)p)->Release();
    }
    mFlags &= 0xffffff8f;
}

// @ 0x00c899a0
bool cSO::func7Ch(char a4, float* out)
{
    BBox box;
    box.mn.x = -0.5f;
    box.mn.y = -0.5f;
    box.mn.z = 0.0f;
    box.mx.x = 0.5f;
    box.mx.y = 0.5f;
    box.mx.z = 1.0f;

    bool computed;
    BBox* pB;
    if ((mFlags & 0x10) != 0 && (mFlags & 0x20) == 0) {
        computed = false;
        pB = &box;
    } else {
        computed = true;
        pB = (BBox*)((void*(__thiscall*)(cSO*))VT(0x68))(this);
    }
    float ext = pB->mx.z * 0.9f;
    Vec3* pos = (Vec3*)((void*(__thiscall*)(cSO*))VT(0x2c))(this);
    float px = pos->x, py = pos->y, pz = pos->z;
    Vec3 ctr;
    if (a4 != 0) {
        volatile float inv = 1.0f / sqrtf(px * px + (py * py + pz * pz));
        volatile float m;
        m = px * inv; m = m * ext; ctr.x = m + px;
        m = py * inv; m = m * ext; ctr.y = m + py;
        m = pz * inv; m = m * ext; ctr.z = m + pz;
    } else if (computed) {
        BBox* p = (BBox*)((void*(__thiscall*)(cSO*, void*))VT(0x6c))(this, &box);
        ctr.x = (p->mn.x + p->mx.x) * 0.5f;
        ctr.y = (p->mx.y + p->mn.y) * 0.5f;
        ctr.z = (p->mx.z + p->mn.z) * 0.5f;
    } else {
        Transform t;
        ((Matrix3Shim*)&t.rot)->Assign(&g_mat16952ac);
        t.pos = g_vec1695248;
        t.flags = 0;
        t.version = 0;
        t.scale = 1.0f;
        LocalToWorldTransform(&t);
        ((BBoxShim*)&box)->TransformBy(&t);
        ctr.x = (box.mx.x + box.mn.x) * 0.5f;
        ctr.y = (box.mx.y + box.mn.y) * 0.5f;
        ctr.z = (box.mx.z + box.mn.z) * 0.5f;
    }

    void* app = App();
    void* viewer = ((void*(__thiscall*)(void*))(*(void***)app)[0x58 / 4])(app);
    Vec3 v;
    ((cViewerShim*)viewer)->ProjectToScreen(&v, &ctr);

    const float* M = (const float*)((char*)viewer + 0x40);
    float t1 = ((((M[8] * ctr.z) + (M[4] * ctr.y)) + (M[0] * ctr.x)) + M[0xc]) * g_vec1695294.x;
    float t2 = ((((M[9] * ctr.z) + (M[5] * ctr.y)) + (M[1] * ctr.x)) + M[0xd]) * g_vec1695294.y;
    float t3 = ((((M[10] * ctr.z) + (M[6] * ctr.y)) + (M[2] * ctr.x)) + M[0xe]) * g_vec1695294.z;
    float d = (t3 + t2) + t1;
    if (0.0f > d)
        return false;
    if (funcE30())
        return false;
    float area[4];
    SPUIHelpers_GetMainWindowArea(area);
    out[0] = ((v.x + 1.0f) * area[2]) * 0.5f;
    out[1] = ((1.0f - v.y) * area[3]) * 0.5f;
    return true;
}

// @ 0x00c89d60
void __fastcall F89d60(Spatial* s, int, const SpatialXform* parent)
{
    if (s->vecBegin == s->vecEnd) return;

    float scale = ((float (__thiscall*)(Spatial*))vfn(s, 0x78))(s);

    SpatialXform xf;
    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mPos[0] = DAT_016952f4;
    xf.mPos[1] = DAT_016952f8;
    xf.mPos[2] = DAT_016952fc;
    xf.mPos[3] = DAT_01485720;
    xf.mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf.mMatrix, 0, (const void*)0x016952d0);
    xf.mMatrix = parent->mMatrix;
    xf.mFlags |= 2;
    xf.mVersion += 1;

    for (EffectElem* p = s->vecBegin; p != s->vecEnd; ++p) {
        EffectInterface* fx = p->p38;
        if (fx == 0) continue;
        if (p->b08 == 0) continue;

        float t = p->f18 * scale;
        cSPVector3_s00c8_9d60 v;
        v.x = p->f1c + DAT_016952a0 * t;
        v.y = p->f20 + DAT_016952a4 * t;
        v.z = p->f24 + DAT_016952a8 * t;
        cSPVector3_s00c8_9d60 r = Rotate(&parent->mMatrix, v);
        r.x += parent->mPos[0];
        r.y += parent->mPos[1];
        r.z += parent->mPos[2];

        float blend = p->f14;
        if (p->b10 != 0) blend *= s->mf60;
        if (blend != 0.0f) {
            fx->BuildTransform(&xf);
            blend = xf.mPos[4];
            xf.mVersion += 1;
        }

        xf.mFlags |= 4;
        xf.mPos[0] = r.x;
        xf.mPos[1] = r.y;
        xf.mPos[2] = r.z;
        xf.mPos[4] = blend;
        fx->SetTransform(&xf);
    }
}

// @ 0x00c8a020
void __fastcall F8a020(Spatial* s, int, int id, float val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->f14 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float blend = (p->b10 != 0) ? s->mf60 : DAT_01485720;
    blend *= val;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);
    xf.mPos[4] = blend;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// @ 0x00c8a110
void __fastcall F8a110(Spatial* s, int, int id, char val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->b10 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float blend = (val != 0) ? s->mf60 : DAT_01485720;
    blend *= p->f14;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);
    xf.mPos[4] = blend;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// @ 0x00c8a200
void __fastcall F8a200(Spatial* s, int, int id, float val)
{
    EffectElem* p = FindEffect(s, id);
    if (p == 0) return;
    p->f18 = val;
    EffectInterface* fx = p->p38;
    if (fx == 0) return;

    float scale = ((float (__thiscall*)(Spatial*))vfn(s, 0x78))(s) * p->f18;
    cSPVector3_s00c8_9d60 v;
    v.x = p->f1c + DAT_016952a0 * scale;
    v.y = p->f20 + DAT_016952a4 * scale;
    v.z = p->f24 + DAT_016952a8 * scale;

    SpatialXform xf;
    InitXform(&xf);
    fx->BuildTransform(&xf);

    cSPVector3_s00c8_9d60 r = Rotate(&xf.mMatrix, v);
    float* pos = ((float* (__thiscall*)(Spatial*))vfn(s, 0x2c))(s);
    xf.mPos[0] = r.x + pos[0];
    xf.mPos[1] = r.y + pos[1];
    xf.mPos[2] = r.z + pos[2];
    xf.mFlags |= 4;
    xf.mVersion += 1;
    fx->SetTransform(&xf);
}

// @ 0x00c8a420
void __fastcall F8a420(Spatial* s)
{
    s->vt = (void**)0x1473758;
    ((SpatialBaseDtor*)s)->Destroy();
    ((EffectVecDtor*)((char*)s + 0xc0))->Destroy();
    if (s->pa0 != 0) {
        void** vt = *(void***)s->pa0;
        ((void(__thiscall*)(int*))vt[4 / 4])(s->pa0);
    }
    RefHolder* p = (RefHolder*)s->p9c;
    if (p != 0) {
        if (p->mRefCount > 1) { p->mRefCount -= 1; return; }
        void** vt = *(void***)p->mpObject;
        ((RefReleaseFn)vt[0x170 / 4])(p->mpObject, p, (unsigned char)((p->mFlags >> 31) & 1));
    }
}

// @ 0x00c8a480
void __stdcall F8a480(StrAssigner* self)
{
    self->Assign(&g_empty13ec47c, &g_empty13ec47c);
}

// @ 0x00c8a4a0
cSPBoundingBox_s00c8_9d60* __fastcall GetWorldExtents(Spatial* s, int, cSPBoundingBox_s00c8_9d60* box)
{
    float* f = s->GetExtents();
    box->mMin.x = f[0];
    box->mMin.y = f[1];
    box->mMin.z = f[2];
    box->mMax.x = f[3];
    box->mMax.y = f[4];
    box->mMax.z = f[5];

    SpatialXform xf;
    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mPos[0] = DAT_01695248;
    xf.mPos[1] = DAT_0169524c;
    xf.mPos[2] = DAT_01695250;
    xf.mPos[3] = DAT_01485720;
    xf.mPos[4] = DAT_01485720;
    FUN_0041cb40(&xf.mMatrix, 0, (const void*)0x016952ac);

    FUN_00c897e0(s, 0, &xf);       // local -> world
    FUN_00409dd0(box, 0, &xf);     // transform the box
    return box;
}

// @ 0x00c8a550
bool __fastcall LoadModel(Spatial* s, void*, void* model)
{
    bool loaded = false;
    if (model == 0) goto finish;
    if (!((char (__thiscall*)(Spatial*))vfn(s, 0x90))(s)) goto finish;

    {
        EffectElementRef holder;
        holder.mpObject = 0;
        u32 key = s->mNameSize_94;
        if (key == 0x24682294 || key == 0x2399be55 || key == 0x476a98c7) {
            // Known key: describe the spatial and ask the noun manager.
            ModelDesc desc;
            desc.mTag = 0x2ea8fb98;
            desc.mKind = 4;
            desc.mPad06 = 0;
            if (((char (__thiscall*)(Spatial*))vfn(s, 0x58))(s)) desc.mKind = 2;

            SimFlags* sim = (SimFlags*)FUN_00b3d240();
            bool wantFlag = false;
            if (sim->mFlag10c != 0 &&
                FUN_00b33e10(sim, 0, s->mNameSize_94) != 0) {
                desc.mKind |= 0x100;
                wantFlag = true;
            }
            void* nouns = FUN_00401010();
            ((void (__thiscall*)(void*, void*, ModelDesc*))vfn(nouns, 0x4c))(
                nouns, (void*)&s->mNameData_90, &desc);
            holder.mpObject = (void**)((void* (__thiscall*)(void*, u32, u32, void*))vfn(model, 0x0c))(
                model, wantFlag ? 0x20u : 0u, s->mNameCap_98, s->mNameData_90);
            FUN_00478db0(&holder, 0, holder.mpObject);
            if (holder.mpObject != 0 && wantFlag &&
                ((SimFlags*)FUN_00b3d240())->mFlag10d != 0)
                holder.mFlags |= 0x2000;
        } else {
            // Unknown key: let the model build its own reference.
            holder.mpObject = (void**)((void* (__thiscall*)(void*, u32, u32, void*))vfn(model, 0x0c))(
                model, 0u, s->mNameCap_98, s->mNameData_90);
            FUN_00478db0(&holder, 0, holder.mpObject);
        }
        if (holder.mpObject != 0) {
        ModelHolder* h = (ModelHolder*)holder.mpObject;

        ((void (__thiscall*)(Spatial*))vfn(s, 0xa4))(s);
        FUN_00b5f950(&s->pa0, 0, model);
        FUN_00478db0(&s->p9c, 0, h);

        if (s->mFlags50 & 8) {
            ((void (__thiscall*)(void*, ModelHolder*))vfn(model, 0x58))(model, h);
            float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
            ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
        } else if (h->mFlags04 & 0x4000) {
            ((void (__thiscall*)(void*, ModelHolder*))vfn(model, 0x58))(model, h);
            float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
            ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
        } else {
            s->mFlags50 |= 0x10;
            if (h->mFlags04 & 0x20000) {
                s->mFlags50 |= 0x40;
                float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s) * h->mf6c;
                s->mf5c = f;
                s->mf60 = f;
            }
            if (((u8*)&h->mFlags04)[2] & 1) {
                float f = ((float (__thiscall*)(Spatial*))vfn(s, 0x34))(s);
                ((void (__thiscall*)(Spatial*, ModelHolder*, float))vfn(s, 0x64))(s, h, f);
            }
        }

        // Copy the live pose into the model.
        float* p = ((float* (__thiscall*)(Spatial*))vfn(s, 0x2c))(s);
        h->mPos0c[0] = p[0];
        h->mPos0c[1] = p[1];
        h->mPos0c[2] = p[2];
        h->mFlags08 |= 4;
        h->mVersion0a += 1;

        void* src = ((void* (__thiscall*)(Spatial*))vfn(s, 0x30))(s);
        Matrix33 tmp;
        FUN_0059c190(&tmp, src);
        h->mMatrix1c = tmp;
        h->mFlags08 |= 2;
        h->mVersion0a += 1;

        h->mf18 = s->mf64;
        h->mVersion0a += 1;
        loaded = true;
        }

        if (holder.mpObject != 0) {
            holder.mFlags |= 0x40000000;
            if (holder.mpObject != 0) {
                void** vt = *(void***)holder.mpObject;
                ((void (__thiscall*)(void*, EffectElementRef*, u32))vt[0x170 / 4])(
                    holder.mpObject, &holder, (holder.mFlags >> 31) & 1);
            }
        }
    }

finish:
    ((void (__thiscall*)(Spatial*, int))vfn(s, 0x8c))(s, 0);
    return loaded;
}

// @ 0x01353d90
void InitSpatialObjectAttributes()
{
  gSpatialObjectAttributes[0] = Attribute("mPosition", 0x2416c5e, 0x4, rd_b6e3a0_P, wr_ac88c0_P, rt_6930f0_P, wt_695010_P, uk_00b1fbf0_P, u2_acbba0_P);
  gSpatialObjectAttributes[1] = Attribute("mOrientation", 0x2416c60, 0x10, rd_ae33d0_O, wr_ae3400_O, rt_693120_O, wt_695040_O, uk_00b1fbf0_O, u2_ae5700_O);
  gSpatialObjectAttributes[2] = Attribute("mScale", 0x316f520, 0x64, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[3] = Attribute("mIsInvalid", 0xd24b464b, 0x6e, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[4] = Attribute("mIsRolledOver", 0xb1a64f7b, 0x6d, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[5] = Attribute("mIsSelected", 0x2416c61, 0x6c, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[6] = Attribute("mbPickable", 0x2416c62, 0x6f, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[7] = Attribute("mbIsTangible", 0x2416c63, 0x70, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[8] = Attribute("mBoundingRadius", 0x2416c64, 0x5c, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[9] = Attribute("mFootprintRadius", 0x49100ec, 0x60, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[10] = Attribute("mbIsBeingEdited", 0x2416c65, 0x72, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[11] = Attribute("mModelChanged", 0x2416c66, 0x73, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[12] = Attribute("mbTransformDirty", 0x2416c67, 0x74, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[13] = Attribute("mbFixed", 0x2416c68, 0x71, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[14] = Attribute("mbEnabled", 0x2416c69, 0x75, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[15] = Attribute("mbInView", 0x2416c6a, 0x76, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[16] = Attribute("mDistanceFromCamera", 0x2416c6b, 0x68, rd_572810_D, wr_ac88f0_D, rt_6930b0_D, wt_694fc0_D, uk_00b1fbf0_D, u2_acbb80_D);
  gSpatialObjectAttributes[17] = Attribute("mbSupported", 0x2416c6c, 0x77, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[18] = Attribute("mFlags", 0x2416c6d, 0x50, rd_572810_S, wr_572840_S, rt_693090_S, wt_694f00_S, uk_00b1fbf0_S, u2_675ca0_S);
  gSpatialObjectAttributes[19] = Attribute("mMaterialType", 0x2416c6e, 0x54, rd_572810_S, wr_572840_S, rt_693090_S, wt_694f00_S, uk_00b1fbf0_S, u2_675ca0_S);
  gSpatialObjectAttributes[20] = Attribute("mbKeepPinnedToPlanet", 0x445dc86, 0xa6, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
  gSpatialObjectAttributes[21] = Attribute("mModelKey", 0x47df70d, 0x90, rd_ae3430_K, wr_ae3450_K, rt_693150_K, wt_695080_K, uk_00b1fbf0_K, u2_ae5720_K);
  gSpatialObjectAttributes[22] = Attribute("mLocalExtents", 0x47df723, 0x38, rd_c88b60_E, wr_c88b80_E, rt_c2e4e0_E, wt_692fb0_E, uk_00b1fbf0_E, u2_ac8050_E);
  gSpatialObjectAttributes[23] = Attribute("mOriginalLocalExtents", 0x5e8faa8, 0x20, rd_c88b60_E, wr_c88b80_E, rt_c2e4e0_E, wt_692fb0_E, uk_00b1fbf0_E, u2_ac8050_E);
  gSpatialObjectAttributes[24] = Attribute("mbIsGhost", 0x771d7b4, 0x78, rd_ac8750_B, wr_ac8780_B, rt_693090_B, wt_694fa0_B, uk_00b1fbf0_B, u2_57ce00_B);
}
