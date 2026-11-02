// src/game/SPCreatureAnim/creature_spore.cpp -- migrated from slice(s) s009ccfe0, s009cb3f0, s009ca4b0, s009c7ff0, s009cbee0, s009c9910, s009c8a90 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/creature_spore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "nSPCreatureAnim/creature_instance_data.h"
#include "checkerlib/vector_3.h"
#include "checkerlib/vector_4.h"
#include "checkerlib/matrix_3x3.h"
#include "nSPCreatureAnim/creature_body_static_data.h"
#include "nSPCreatureAnim/creature_static_data.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cIParser.h"
#include "nSPCreatureAnim/creature_effect.h"
#include <string.h>

// ---- items of slice s009c8a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef SPPV8
#undef SPPV4
#undef SPPV2
#undef SPPV
#undef SPVJOIN
#undef SPVJOIN_
namespace checkerlib {
class vector_3_s009c_8a90 { public:
    float x, y, z;
    vector_3_s009c_8a90& operator=(const vector_3_s009c_8a90& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
class vector_4_s009c_8a90 { public:
    float x, y, z, w;
};
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator+(const vector_3_s009c_8a90& a, const vector_3_s009c_8a90& b) { vector_3_s009c_8a90 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator-(const vector_3_s009c_8a90& a, const vector_3_s009c_8a90& b) { vector_3_s009c_8a90 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator*(const vector_3_s009c_8a90& a, float s) { vector_3_s009c_8a90 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
}
namespace checkerlib {
vector_3_s009c_8a90* QuaternionVectorTransform(vector_3_s009c_8a90* out, const vector_4_s009c_8a90* q, const vector_3_s009c_8a90* v);         // 0x0099c1a0
}
namespace checkerlib {
vector_3_s009c_8a90* QuaternionVectorTransformInverse(vector_3_s009c_8a90* out, const vector_4_s009c_8a90* q, const vector_3_s009c_8a90* v);  // 0x0099c310
}
namespace EA {
namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
}
}
struct BlockFlags;
void __cdecl FUN_009fc220(BlockFlags*);                                  // 0x009fc220
struct BlockDef;
checkerlib::vector_3_s009c_8a90* __cdecl ScaledOffset(checkerlib::vector_3_s009c_8a90* out, BlockDef* b, float t);      // 0x009b53f0
struct BlockDef {
    char      name[0x104];       // +0x000
    uint32_t  hash;              // +0x104
    uint32_t  pad_108;
    checkerlib::vector_3_s009c_8a90  center;            // +0x10c
    checkerlib::vector_4_s009c_8a90  orient;            // +0x118
    uint32_t  pad_128[(0x138 - 0x128) / 4];
    checkerlib::vector_3_s009c_8a90  half;              // +0x138
    checkerlib::vector_3_s009c_8a90  local;             // +0x144
    BlockFlags* flags() { return (BlockFlags*)((char*)this + 0x150); }
    uint32_t  pad_150[(0x1fc - 0x150) / 4];
    int       parent;            // +0x1fc
    uint32_t  pad_200;
    int       childMark;         // +0x204
    int       refCount;          // +0x208
    uint32_t  pad_20c[(0x330 - 0x20c) / 4];
    checkerlib::vector_3_s009c_8a90  offset;            // +0x330
    uint32_t  pad_33c[(0x344 - 0x33c) / 4];
    checkerlib::vector_3_s009c_8a90  parentLocal;       // +0x344
    checkerlib::vector_3_s009c_8a90  parentOffset;      // +0x350
    checkerlib::vector_3_s009c_8a90  scaled;            // +0x35c
    float     scaledLen;         // +0x368
    float     limit;             // +0x36c
    uint32_t  pad_370[(0x378 - 0x370) / 4];
    float     scale;             // +0x378
    uint32_t  pad_37c[(0x468 - 0x37c) / 4];
};
struct BlockOwner {
    uint32_t  pad_000[0x384 / 4];
    BlockDef* blocks;            // +0x384
};
struct CreatureCommandState {
    uint32_t     pad_000;
    int          count;          // +0x04
    uint32_t     pad_008[2];
    checkerlib::vector_3_s009c_8a90     anchor;         // +0x10
    checkerlib::vector_3_s009c_8a90     anchor2;        // +0x1c
    checkerlib::vector_3_s009c_8a90     boxMin;         // +0x28
    checkerlib::vector_3_s009c_8a90     boxMax;         // +0x34
    BlockDef*    block;          // +0x40
    BlockOwner*  owner;          // +0x44
};
__forceinline checkerlib::vector_3_s009c_8a90 QuaternionVectorTransformInverse(const checkerlib::vector_4_s009c_8a90& q, const checkerlib::vector_3_s009c_8a90& v)
{
    checkerlib::vector_3_s009c_8a90 r;
    float nxw = -(q.x * q.w), nzw = -(q.z * q.w), nxx = -(q.x * q.x);
    float yx = q.y * q.x, zy = q.z * q.y, yw = q.y * q.w, zx = q.z * q.x;
    float nyy = -(q.y * q.y), nzz = -(q.z * q.z);
    r.x = (((yx - nzw) * v.y + (zx + -yw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - -yw) * v.x) * 2.0f + v.z;
    return r;
}
namespace {

struct cBlockBlockCommand {
    uint32_t              pad_000[12];
    CreatureCommandState* mState;       // +0x30

    void OnEndBlock(bool bCancel);      // 0x009c8a90
};

}  // namespace
#define SPVJOIN_(a, b) a##b
#define SPVJOIN(a, b) SPVJOIN_(a, b)
#define SPPV virtual void SPVJOIN(vfn_, __COUNTER__)();
#define SPPV2 SPPV SPPV
#define SPPV4 SPPV2 SPPV2
#define SPPV8 SPPV4 SPPV4
namespace EA {
namespace ArgScript {
class cArguments_s009c_8a90 {
 public:
    char const* const* MainArguments(int count) const;          // 0x00838320
};
}
}
namespace EA {
namespace ArgScript {
class cIParser_s009c_8a90 {
 public:
    SPPV8 SPPV8 SPPV8 SPPV8 SPPV4 SPPV            // +0x00 .. +0x90
    virtual bool  ParseBool(const char* s);       // +0x94
    virtual float ParseFloat(const char* s);      // +0x98
    virtual int   ParseInt(const char* s);        // +0x9c
};
}
}
struct EffectEntryTable {
    unsigned long mCount;                                                          // +0x000
    unsigned char pad_004[0xa0];
    bool FUN_0099c4a0(unsigned long id, unsigned long value, float a, float b);    // 0x0099c4a0
};
struct EffectDef {
    char          mName[0x1c];                                 // +0x000
    checkerlib::vector_3_s009c_8a90      mVec01c;                                     // +0x01c
    unsigned char pad_028[0x118 - 0x028];
    float         mQuat[4];                                    // +0x118
    unsigned char pad_128[0x158 - 0x128];
    unsigned long mIds[0x20];                                  // +0x158
    unsigned char mFlags[0x20];                                // +0x1d8
    unsigned char pad_1f8[0x220 - 0x1f8];
    char          mName2[0x104];                               // +0x220
    checkerlib::vector_3_s009c_8a90      mVec324;                                     // +0x324
    checkerlib::vector_3_s009c_8a90      mVec330;                                     // +0x330
    unsigned char pad_33c[4];
    unsigned char mBool340;                                    // +0x340
    unsigned char pad_341[0x380 - 0x341];
    EffectEntryTable mEntries;                                 // +0x380
};
struct EffectCommandState {
    unsigned char pad_000[8];
    int           mCount;                                      // +0x008
    unsigned char pad_00c[4];
    checkerlib::vector_3_s009c_8a90      mVec10;                                      // +0x010
    checkerlib::vector_3_s009c_8a90      mVec1c;                                      // +0x01c
    checkerlib::vector_3_s009c_8a90      mVec28;                                      // +0x028
    checkerlib::vector_3_s009c_8a90      mVec34;                                      // +0x034
    EffectDef*    mpDef;                                       // +0x040
};
struct cEffectBlockCommand {
    unsigned char             pad_000[4];
    EA::ArgScript::cIParser_s009c_8a90*  mpParser;                        // +0x004
    unsigned char             pad_008[4];
    EffectCommandState*       mpState;                         // +0x00c

    void FUN_009c90d0(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c90d0
    void FUN_009c9130(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9130
    void FUN_009c9170(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9170
    void FUN_009c9200(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9200
    void FUN_009c9230(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9230
    void FUN_009c9260(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9260
    void FUN_009c92e0(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c92e0
    void FUN_009c9340(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9340
    void FUN_009c93c0(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c93c0
    void FUN_009c9460(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9460
    void FUN_009c94c0(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c94c0
    void FUN_009c95e0(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c95e0
    void FUN_009c9650(EA::ArgScript::cArguments_s009c_8a90* a);            // 0x009c9650
};
unsigned long __cdecl FeedbackLookupName(const char* name);     // 0x009fc0f0
namespace nSPCreatureAnim {
struct cMWModel_s009c_8a90;
}
namespace nSPCreatureAnim {
struct IUnknown {
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(unsigned long type);
};
}
namespace nSPCreatureAnim {
struct cIVisualEffect : IUnknown {};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_8a90 {
    int AddRef();                                               // 0x00a17060
    int Release();                                              // 0x009c4cc0
};
}
namespace nSPCreatureAnim {
struct IModelWorld {
    SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV4   // +0x000 ..
    virtual void DestroyModel(cMWModel_s009c_8a90* model, bool flag);                     // +0x170
};
}
namespace nSPCreatureAnim {
struct cMWModel_s009c_8a90 {
    IModelWorld*  mpWorld;                                      // +0x000
    unsigned long mFlags;                                       // +0x004
    unsigned char pad_008[0x40 - 0x008];
    int           mnRefCount;                                   // +0x040

    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        if (mnRefCount > 1) {
            mnRefCount = mnRefCount - 1;
            return mnRefCount;
        }
        mpWorld->DestroyModel(this, (bool)((mFlags >> 31) & 1));
        return 0;
    }
};
}
namespace nSPCreatureAnim {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};
}
namespace nSPCreatureAnim {
struct creature_effect_s009c_8a90 {
    unsigned long key;                                          // 0x000
    unsigned long id;                                           // 0x004
    unsigned long bidx;                                         // 0x008
    checkerlib::vector_3_s009c_8a90      local_pos;                                    // 0x00c
    checkerlib::vector_4_s009c_8a90      local_rot;                                    // 0x018
    bool          f28;                                          // 0x028
    bool          f29;                                          // 0x029
    unsigned char pad_2a[2];
    float         f2c;                                          // 0x02c
    bool          f30;                                          // 0x030
    unsigned char pad_31[3];
    unsigned long d34;                                          // 0x034
    unsigned long d38;                                          // 0x038
    unsigned long d3c;                                          // 0x03c
    unsigned long d40;                                          // 0x040
    unsigned long d44;                                          // 0x044
    union {
        long  i;                                                // 0x048
        float f;
    } data48;
    AutoRefCount<creature_instance_data_s009c_8a90> ref4c;                 // 0x04c
    AutoRefCount<creature_instance_data_s009c_8a90> ref50;                 // 0x050
    AutoRefCount<creature_instance_data_s009c_8a90> ref54;                 // 0x054
    unsigned long d58;                                          // 0x058
    unsigned long d5c;                                          // 0x05c
    unsigned long d60;                                          // 0x060
    checkerlib::vector_3_s009c_8a90      src_pos_rand;                                 // 0x064
    unsigned long d70;                                          // 0x070
    unsigned long d74;                                          // 0x074
    AutoRefCount<creature_instance_data_s009c_8a90> ref78;                 // 0x078
    unsigned long d7c;                                          // 0x07c
    checkerlib::vector_3_s009c_8a90      dst_pos_rand;                                 // 0x080
    AutoRefCount<cIVisualEffect> effect;                        // 0x08c
    AutoRefCount<cMWModel_s009c_8a90>       model;                         // 0x090
    unsigned long sound_id;                                     // 0x094
    checkerlib::vector_3_s009c_8a90      last_sound_pos;                               // 0x098
    AutoRefCount<IUnknown>       unknown;                       // 0x0a4
    unsigned long da8;                                          // 0x0a8

    void SetWorldState();                                       // 0x009c8890 (creature_mesh_instance_data)
    void Dispose();                                             // 0x009c8460 (creature_mesh_instance_data)
    void Clear(bool bAll);                                      // 0x009c96b0
    ~creature_effect_s009c_8a90();                                         // 0x009c9870
};
}
// ---- items of slice s009c8a90 end

// ---- items of slice s009c9910 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009c_9910 {
public:
    float x, y, z;
    vector_3_s009c_9910() {}
    vector_3_s009c_9910(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    vector_3_s009c_9910& operator*=(float s)
    {
        x *= s; y *= s; z *= s;
        return *this;
    }
};
}
namespace checkerlib {
class vector_4_s009c_9910 {
public:
    float x, y, z, w;
    vector_4_s009c_9910() {}
    vector_4_s009c_9910(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
}
namespace checkerlib {
class matrix_3x3_s009c_9910 {
public:
    float el[9];
};
}
namespace checkerlib {
inline vector_3_s009c_9910 operator+(const vector_3_s009c_9910& a, const vector_3_s009c_9910& b) { return vector_3_s009c_9910(a.x + b.x, a.y + b.y, a.z + b.z); }
}
namespace checkerlib {
__forceinline vector_3_s009c_9910 operator-(const vector_3_s009c_9910& a, const vector_3_s009c_9910& b) { return vector_3_s009c_9910(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace checkerlib {
inline vector_3_s009c_9910 operator*(float s, const vector_3_s009c_9910& a) { return vector_3_s009c_9910(s * a.x, s * a.y, s * a.z); }
}
namespace checkerlib {
inline float Length2(const vector_3_s009c_9910& a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
}
namespace checkerlib {
inline vector_4_s009c_9910 QuaternionConjugate(const vector_4_s009c_9910& q) { return vector_4_s009c_9910(-q.x, -q.y, -q.z, q.w); }
}
namespace checkerlib {
inline vector_4_s009c_9910 QuaternionProduct(const vector_4_s009c_9910& a, const vector_4_s009c_9910& b)
{
    vector_4_s009c_9910 r;
    r.x = ((b.x * a.w + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - b.x * a.x) - a.y * b.y) - b.z * a.z;
    return r;
}
}
namespace checkerlib {
vector_3_s009c_9910 QuaternionVectorTransform(const vector_4_s009c_9910& q, const vector_3_s009c_9910& v); // 0x0099c1a0
}
namespace checkerlib {
matrix_3x3_s009c_9910 QuaternionToMatrix(const vector_4_s009c_9910& q);                          // 0x009a46a0
}
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    checkerlib::vector_3_s009c_9910 pos;
    float scale;
    checkerlib::matrix_3x3_s009c_9910 rot;
    XformMsg(); // 0x00434040
    void SetPos(const checkerlib::vector_3_s009c_9910& v) { pos = v; flags |= 4; ++count; }
    void SetScale(float s) { scale = s; ++count; }
    void SetRot(const checkerlib::matrix_3x3_s009c_9910& m) { rot = m; flags |= 2; ++count; }
};
class IEffect {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual bool IsPlaying();              // +0x10
    virtual void v14();
    virtual void SetXform(XformMsg* msg);  // +0x18
    virtual void v1c();
    virtual void GetXform(XformMsg* msg);  // +0x20
};
struct XformTarget {
    uint32_t pad00[2];
    XformMsg msg; // +0x08
};
struct ReadyFlag {
    uint32_t pad00[3];
    bool mbReady; // +0x0c
};
typedef bool (*EffectCallback)(void* data, checkerlib::vector_3_s009c_9910* pos, checkerlib::matrix_3x3_s009c_9910* rot);
struct cAnimEffect {
    uint32_t pad00[2];
    uint32_t mBoneIndex;          // +0x08
    checkerlib::vector_3_s009c_9910 mOffset;             // +0x0c
    checkerlib::vector_4_s009c_9910 mRotation;           // +0x18
    uint8_t pad28;
    bool mbScaleWithCreature;     // +0x29
    uint8_t pad2a[2];
    float mScale;                 // +0x2c
    bool mbEventLocated;          // +0x30
    uint8_t pad31[3];
    uint32_t mEventFlags;         // +0x34
    uint32_t mLocFlags;           // +0x38
    uint32_t mLocFlags2;          // +0x3c
    uint32_t pad40;
    uint32_t mLocFlags3;          // +0x44
    uint32_t mEventValue;         // +0x48 (float bits)
    ReadyFlag* mpCreature;        // +0x4c
    ReadyFlag* mpCreature2;       // +0x50
    ReadyFlag* mpCreature3;       // +0x54
    uint32_t mBone;               // +0x58
    uint32_t mBone2;              // +0x5c
    uint32_t pad60;
    checkerlib::vector_3_s009c_9910 mDirection;          // +0x64
    int mOrientMode;              // +0x70
    int mScaleMode;               // +0x74
    ReadyFlag* mpColorCreature;   // +0x78
    uint32_t mColorBone;          // +0x7c
    checkerlib::vector_3_s009c_9910 mColor;              // +0x80
    IEffect* mpEffect;            // +0x8c
    XformTarget* mpXformTarget;   // +0x90
    uint32_t mSoundHandle;        // +0x94
    checkerlib::vector_3_s009c_9910 mLastSoundPos;       // +0x98
    void* mpCallbackData;         // +0xa4
    EffectCallback mpCallback;    // +0xa8
};
struct BoneStatic {
    uint8_t pad[0x154];
    uint8_t mFlags; // +0x154
};
class BoneAnimState {
public:
    void SetFloatParam(uint32_t id, int a, float value, float weight); // 0x0099c4a0
};
struct creature_bone {             // 700 bytes
    BoneStatic* mpStatic;          // +0x00
    uint32_t pad04[3];
    checkerlib::vector_3_s009c_9910 pos;                  // +0x10
    checkerlib::vector_4_s009c_9910 rot;                  // +0x1c
    uint32_t pad2c[(0xa0 - 0x2c) / 4];
    BoneAnimState mAnimState;      // +0xa0
    uint8_t padA1[700 - 0xa1];
};
bool IsSoundPlaying(uint32_t handle);                         // 0x009fbdd0
void SetSoundPosition(uint32_t handle, const checkerlib::vector_3_s009c_9910* pos);  // 0x009fbe50
float GetSoundValue(uint32_t handle);                         // 0x009fbe20
void SetEffectScale(IEffect* effect, float scale);            // 0x009fbd50
void SetEffectColor(IEffect* effect, const checkerlib::vector_3_s009c_9910* color);  // 0x009fbcd0
void SetEffectAlpha(IEffect* effect, float alpha);            // 0x009fbcf0
namespace nSPCreatureAnim {
bool ComputeEventLocationState(char randomize, uint32_t evFlags, uint32_t locFlags, uint32_t value,
                               void* owner, ReadyFlag* creature, uint32_t boneIdx, checkerlib::vector_3_s009c_9910* pos,
                               checkerlib::vector_3_s009c_9910* pos2, checkerlib::vector_4_s009c_9910* outQuat, float* outScalar,
                               checkerlib::vector_3_s009c_9910* outVec, checkerlib::vector_3_s009c_9910* dirIn, checkerlib::vector_3_s009c_9910* dirIn2, int p15); // 0x009a59e0
}
namespace nSPCreatureAnim {
class creature_instance_data_s009c_9910 {
public:
    uint32_t pad00[6];
    checkerlib::vector_3_s009c_9910 pos;                       // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009c_9910 rot;                       // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float scale;                        // +0x70
    uint32_t pad74[(0x2e4 - 0x74) / 4];
    creature_bone* mBonesBegin;         // +0x2e4
    creature_bone* mBonesEnd;           // +0x2e8

    uint32_t BoneCount() const { return (uint32_t)(mBonesEnd - mBonesBegin); }

    bool UpdateEffect(cAnimEffect* effect);  // 0x009c9910 (nSPCreatureAnim::creature_instance_data::UpdateEffect)
};
}
// ---- items of slice s009c9910 end

// ---- items of slice s009cbee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
struct creature_static_data_s009c_bee0;
}
namespace nSPCreatureAnim {
template <class T> static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
}
namespace nSPCreatureAnim {
struct StaticDataStub {
    void Clear(int);              // 0x9c1dc0 creature_static_data::Clear
};
}
namespace nSPCreatureAnim {
struct BodyStub {
    void Clear();                 // 0x9b3180 creature_body_static_data::Clear
};
}
namespace nSPCreatureAnim {
struct BodyVecStub {
    void resize(unsigned n);      // 0x9cb840 eastl::vector<creature_body_static_data>::resize
};
}
namespace nSPCreatureAnim {
struct WiggleVecStub {
    void resize(unsigned n);      // 0x9cb8f0 eastl::vector<creature_body_wiggle_static_data>::resize
};
}
struct PollenKey { uint32_t instance; uint32_t type; uint32_t group; };
const wchar_t* __cdecl GetAssetName(PollenKey* key);                         // 0x552580 SP::Pollen::GetAssetName
uint32_t __cdecl InitVerbCollection(uint32_t v);                             // 0x4bb860
int __cdecl Sprintf16(wchar_t* dst, const wchar_t* fmt, ...);                // 0x9399c0
int __cdecl appendW(wchar_t* dst, const wchar_t* src, int cap);              // 0x92cb90
void __cdecl WideToNarrow(const wchar_t* src, char* dst, int cap);           // 0x6b8db0
int __cdecl Snprintf8(char* dst, int cap, const char* fmt, ...);             // 0x9384e0
float* __cdecl matrix_to_quaternion(float* outQuat, float* inMat3x3);        // 0x9a4f10
void __cdecl NormalizeFlags(void* p);                                        // 0x9fc220 (on body+0x150)
float* __cdecl ComputeBodyVector(float* out, void* body, float scale);       // 0x9b53f0
void __cdecl FinishNoBranches(void* sd);                                     // 0x9cbdb0
char __cdecl PostProcess(void* sd);                                          // 0x9c4a30
namespace nSPCreatureAnim {
#define BF(o) at<float>(b, (o))
}
namespace nSPCreatureAnim {
#define BU(o) at<uint32_t>(b, (o))
}
// ---- items of slice s009cbee0 end

// ---- items of slice s009c7ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void AudioSetFlag(void* sound, char flag);               // 0x009fbd10
extern "C" void AudioSetListener2(void* param, char flag);          // 0x009fbd70
extern "C" int  AudioQueryB(void* param);                           // 0x009fbe00
#pragma intrinsic(fabs)
inline float Abs(float v) { return (float)fabs((double)v); }
typedef unsigned int  uint;
typedef unsigned long ulong;
#define VPAD(n) virtual void vpad##n()
struct IRefObj {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
VPAD(42);
VPAD(43);
VPAD(44);
VPAD(45);
VPAD(46);
VPAD(47);
VPAD(48);
VPAD(49);
VPAD(50);
VPAD(51);
VPAD(52);
VPAD(53);
VPAD(54);
VPAD(55);
VPAD(56);
VPAD(57);
VPAD(58);
VPAD(59);
VPAD(60);
VPAD(61);
VPAD(62);
VPAD(63);
VPAD(64);
VPAD(65);
VPAD(66);
VPAD(67);
VPAD(68);
VPAD(69);
VPAD(70);
VPAD(71);
VPAD(72);
VPAD(73);
VPAD(74);
VPAD(75);
VPAD(76);
VPAD(77);
VPAD(78);
VPAD(79);
VPAD(80);
VPAD(81);
VPAD(82);
VPAD(83);
VPAD(84);
VPAD(85);
VPAD(86);
VPAD(87);
VPAD(88);
VPAD(89);
VPAD(90);
    virtual void Release(int complete);          // +0x170
};
struct RefObject : IRefObj {
    unsigned char pad_004[0x3c];
    int RefCount;                                // +0x40
};
struct cMWModel : RefObject {
    unsigned char pad_044[0x68 - 0x44];
    unsigned short mModificationCount;           // +0x68
    unsigned char pad_06a[0x90 - 0x6a];
};
struct cIModelWorld {
virtual void v000();
virtual void v004();
virtual void v008();
    virtual void* CreateModelGroup(void* a, void* b, int idx);          // +0x0c (ret 0xc)
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
    virtual bool AssignKeyModel(void* key, void* desc);                 // +0x4c (ret 8)
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
    virtual void AssignModel(void* model, void* group, int idx);        // +0xa4 (ret 0xc)
};
struct Elem28 {
    uint  key;                                   // +0x00
    uint  idx;                                   // +0x04
    float f[8];                                  // +0x08
};
template <class T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned char mAllocatorSlot[8];

    ulong size()  const { return (ulong)(mpEnd - mpBegin); }
    bool  empty() const { return mpBegin == mpEnd; }
    T*    begin()       { return mpBegin; }
    T*    end()         { return mpEnd; }
    T&    operator[](ulong i) { return mpBegin[i]; }

    void SetBodyCount(ulong n);                  // 0x009c8170 (ret 4)
    void erase(T* first, T* last);               // 0x009c6d20
    void resize(T* end, ulong n, const T* v);    // 0x009c6d70
};
struct body_static_data {
    unsigned char pad_000[0x10c];
    float rx;                                    // +0x10c
    float ry;                                    // +0x110
    float rz;                                    // +0x114
    unsigned char pad_118[0x130 - 0x118];
    float c130;                                  // +0x130
    float c134;                                  // +0x134
    float c138;                                  // +0x138
    float c13c;                                  // +0x13c
    float c140;                                  // +0x140
    float rest_center[3];                        // +0x144
    ulong flags_150;                             // +0x150
    unsigned char pad_154[0x1f8 - 0x154];
    ulong f1f8;                                  // +0x1f8
    ulong f1fc;                                  // +0x1fc
    ulong f200;                                  // +0x200
    unsigned char pad_204[0x208 - 0x204];
    ulong f208;                                  // +0x208
    unsigned char pad_20c[0x21c - 0x20c];
    ulong bone_idx;                              // +0x21c
    unsigned char pad_220[0x324 - 0x220];
    float loc[3];                                // +0x324
};
struct creature_static_data {
    unsigned char pad_000[0x37c];
    ulong num_bones_with_mesh_parts;             // +0x37c
    bool  block_default_deforms_hack;            // +0x380
    unsigned char pad_381[3];
    body_static_data* BodiesBegin;               // +0x384
    body_static_data* BodiesEnd;                 // +0x388
};
struct creature_instance_data {
    creature_static_data* sd;                    // +0x00
    unsigned char pad_004[0x18 - 0x04];
    float pos[3];                                // +0x18
    unsigned char pad_024[0x34 - 0x24];
    unsigned char flags_34;                      // +0x34
    unsigned char pad_035[0x3c - 0x35];
    float quat[4];                               // +0x3c
    unsigned char pad_04c[0x70 - 0x4c];
    float scale;                                 // +0x70
    unsigned char pad_074[0x2e4 - 0x74];
    unsigned char* mpAnimsBegin;                 // +0x2e4 (0x2bc-byte records)
    unsigned char* mpAnimsEnd;                   // +0x2e8
};
struct bone { float m[12]; };                    // 0x30
struct body_mesh_data {                          // 0x14
    float     local_origin[3];                   // +0x00
    cMWModel* model;                             // +0x0c
    ulong     modcount;                          // +0x10
};
struct ResKey { ulong a, b, c; };
struct creature_mesh_instance_data {
    struct mesh_data {
        cMWModel*       model;                   // +0x00
        ulong           modcount;                // +0x04
        sp_vector<bone> posed_xforms;            // +0x08 (0x14 -> +0x1c)
        void Clear();                            // 0x009c6c30
        void Assign(cMWModel* m);                // 0x00478db0 (thiscall ret 4)
    };

    creature_instance_data* creature;            // +0x00
    cIModelWorld*           world;               // +0x04
    mesh_data               mesh_lo;             // +0x08
    bool  force_not_in_world;                    // +0x24
    bool  enable_auto_eye_lookat;                // +0x25
    unsigned short pad_26;                       // +0x26
    sp_vector<body_mesh_data> BodyMeshes;        // +0x28

    creature_mesh_instance_data* ctor();         // 0x009c8200
    __declspec(noinline) void Clear();            // 0x009c7ff0
    bool Bind(creature_instance_data* c, cIModelWorld* w, void* unused,
              ResKey* key, bool eye_lookat);     // 0x009c8050 (ret 0x14)
    void SetWorldState();                        // 0x009c8890
    bool Init(creature_instance_data* c, cIModelWorld* w, void* data); // 0x009c8230 (ret 0x10)
    void Dispose();                              // 0x009c8460
    void RefreshWorldState();                    // 0x009c8900

    static void MinClearance(float* minOut, creature_static_data* sd);        // 0x009c8630
    static void MinClearanceIdx(float* minOut, uint* idxOut, creature_static_data* sd); // 0x009c86e0
    static void BodyToWorld(float* out, uint* outIdx, body_static_data* b);     // 0x009c87e0
};
struct body_mesh_data;
struct Vec3 { float x, y, z; };
Vec3 QuaternionVectorTransform(const float* q, const float* v);       // 0x0099c1a0 (3-float sret, ret 8)
// ---- items of slice s009c7ff0 end

// ---- items of slice s009ca4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
inline void* operator new(unsigned int size, const char* name, int a, int b, int c, int d)
{
    return EAAllocate(size, name, a, b, c, d);
}
inline void* operator new(unsigned int, void* p) { return p; }
void __cdecl operator delete(void*);        // 0x00f47380
namespace EA {
namespace ArgScript {
struct cIParser_s009c_a4b0;
}
}
namespace EA {
namespace ArgScript {
struct cState_s009c_a4b0;
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s009c_a4b0;
}
}
namespace EA {
namespace ArgScript {
class cICommand_s009c_a4b0 { public:
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
    virtual void* Cast(unsigned long type);     // +0x08
    virtual void ParseLine(void* line);         // +0x0c
    virtual void Execute(cArguments_s009c_a4b0& args);     // +0x10
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s009c_a4b0 : public cICommand_s009c_a4b0 { public:
    cIParser_s009c_a4b0*   mParser;                // +0x04
    int         mRefCount;              // +0x08
    cCommandBase_s009c_a4b0();                     // 0x0083c800
};
}
}
namespace EA {
namespace ArgScript {
class cIBlockCommand_s009c_a4b0 : public cICommand_s009c_a4b0 { public:
    virtual cState_s009c_a4b0* GetChildState();    // +0x14
};
}
}
namespace EA {
namespace ArgScript {
class cBlockCommandBase : public cIBlockCommand_s009c_a4b0 { public:
    cIParser_s009c_a4b0*     mParser;              // +0x04
    int           mRefCount;            // +0x08
    cState_s009c_a4b0*       mChildState;          // +0x0c
    unsigned long mCommands[8];         // +0x10
    void OnRegister(cIParser_s009c_a4b0* parser, cState_s009c_a4b0* state);                  // 0x0083c780
    virtual void AddCommand(const char* keyword, cICommand_s009c_a4b0* command);  // +0x18
};
}
}
namespace EA {
namespace ArgScript {
template <typename T, typename Base> struct cCommandStateT_s009c_a4b0 : Base {
    T* mState;                          // block: +0x30, command: +0x0c
    cCommandStateT_s009c_a4b0() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cCommandT : public cCommandStateT_s009c_a4b0<T, cCommandBase_s009c_a4b0> { public:
    cCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cBlockCommandT : public cCommandStateT_s009c_a4b0<T, cBlockCommandBase> { public:
    cBlockCommandT() {}
};
}
}
using EA::ArgScript::cIParser_s009c_a4b0;
using EA::ArgScript::cState_s009c_a4b0;
using EA::ArgScript::cArguments_s009c_a4b0;
namespace {

struct cBlockBlockState;                        // the creature-block parser state (the +0x30 member)

struct cBlockBlockCommand_s009c_a4b0 : EA::ArgScript::cBlockCommandT<cBlockBlockState> {
    void OnRegister(cIParser_s009c_a4b0* parser, cState_s009c_a4b0* state);
};

// One sub-command class per block field; each only overrides Execute.
#define BLOCK_COMMAND(Name)                                                       \
    struct c##Name##Command : EA::ArgScript::cCommandT<cBlockBlockCommand_s009c_a4b0> {      \
        c##Name##Command() {}                                                      \
        virtual void Execute(cArguments_s009c_a4b0& args);                                   \
    };

BLOCK_COMMAND(Name)
BLOCK_COMMAND(InstanceId)
BLOCK_COMMAND(Version)
BLOCK_COMMAND(ParentIndex)
BLOCK_COMMAND(SymmetricIndex)
BLOCK_COMMAND(JointPosition)
BLOCK_COMMAND(SubmeshIndex)
BLOCK_COMMAND(LeftHanded)
BLOCK_COMMAND(Cal3DBoneName)
BLOCK_COMMAND(Cal3DOrigin)
BLOCK_COMMAND(Position)
BLOCK_COMMAND(EffectsOrigin)
BLOCK_COMMAND(Orientation)
BLOCK_COMMAND(BBoxMin)
BLOCK_COMMAND(BBoxMax)
BLOCK_COMMAND(Mass)
BLOCK_COMMAND(Scale)
BLOCK_COMMAND(SoundIDFoot)
BLOCK_COMMAND(SoundIDMouth)
BLOCK_COMMAND(SoundIDWeapon)
BLOCK_COMMAND(Cap)
BLOCK_COMMAND(Deform)
}  // namespace
namespace BlockKeywords {
extern const char* name;                    // 0x01550fe4 "name"
}
namespace BlockKeywords {
extern const char* instanceId;              // 0x01550fe8
}
namespace BlockKeywords {
extern const char* version;                 // 0x01551020
}
namespace BlockKeywords {
extern const char* parentIndex;             // 0x01550ff8
}
namespace BlockKeywords {
extern const char* symmetricIndex;          // 0x01551018
}
namespace BlockKeywords {
extern const char* jointPosition;           // 0x01550fdc
}
namespace BlockKeywords {
extern const char* submeshIndex;            // 0x01551014
}
namespace BlockKeywords {
extern const char* leftHanded;              // 0x0155101c
}
namespace BlockKeywords {
extern const char* cal3DBoneName;           // 0x01550fd0
}
namespace BlockKeywords {
extern const char* cal3DOrigin;             // 0x01550fd4
}
namespace BlockKeywords {
extern const char* position;                // 0x01550ffc
}
namespace BlockKeywords {
extern const char* effectsOrigin;           // 0x01551000
}
namespace BlockKeywords {
extern const char* orientation;             // 0x01550ff4
}
namespace BlockKeywords {
extern const char* bBoxMin;                 // 0x01550fc0
}
namespace BlockKeywords {
extern const char* bBoxMax;                 // 0x01550fbc
}
namespace BlockKeywords {
extern const char* mass;                    // 0x01550fe0
}
namespace BlockKeywords {
extern const char* scale;                   // 0x01551004
}
namespace BlockKeywords {
extern const char* soundIDFoot;             // 0x01551008
}
namespace BlockKeywords {
extern const char* soundIDMouth;            // 0x0155100c
}
namespace BlockKeywords {
extern const char* soundIDWeapon;           // 0x01551010
}
namespace BlockKeywords {
extern const char* cap;                     // 0x01550fc8
}
namespace BlockKeywords {
extern const char* deformChannel;           // 0x01550fd8
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_a4b0;
}
namespace nSPCreatureAnim {
struct cMWModel;
}
namespace nSPCreatureAnim {
template <class T> struct AutoRefCount_s009c_a4b0 {
    T* mpObject;
    AutoRefCount_s009c_a4b0() : mpObject(0) {}
    AutoRefCount_s009c_a4b0(T* p) : mpObject(p) {}
    AutoRefCount_s009c_a4b0& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};
}
namespace nSPCreatureAnim {
template <> struct AutoRefCount_s009c_a4b0<cMWModel> {
    cMWModel* mpObject;
    AutoRefCount_s009c_a4b0() : mpObject(0) {}
    AutoRefCount_s009c_a4b0(cMWModel* p) : mpObject(p) {}
    AutoRefCount_s009c_a4b0& operator=(cMWModel* p);       // 0x00478db0
    operator cMWModel*() const { return mpObject; }
};
}
namespace nSPCreatureAnim {
struct vector_3 {
    float x, y, z;
    vector_3() { z = 0.0f; y = 0.0f; x = 0.0f; }
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace nSPCreatureAnim {
struct vector_4 {
    float x, y, z, w;
    vector_4() { z = 0.0f; y = 0.0f; x = 0.0f; w = 1.0f; }
    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_a4b0 {
    int AddRef();                               // 0x00a17060
    int Release();                              // 0x009c4cc0
};
}
namespace nSPCreatureAnim {
struct creature_effect_s009c_a4b0 {
    unsigned long key;                                  // 0x000
    unsigned long id;                                   // 0x004
    unsigned long bidx;                                 // 0x008
    vector_3      local_pos;                            // 0x00c
    vector_4      local_rot;                            // 0x018
    bool          f28;                                  // 0x028
    bool          f29;                                  // 0x029
    unsigned char pad_2a[2];
    float         f2c;                                  // 0x02c
    bool          f30;                                  // 0x030
    unsigned char pad_31[3];
    unsigned long d34;                                  // 0x034
    unsigned long d38;                                  // 0x038
    unsigned long d3c;                                  // 0x03c
    unsigned long d40;                                  // 0x040
    unsigned long d44;                                  // 0x044
    union {
        long  i;                                        // 0x048
        float f;
    } data48;
    AutoRefCount_s009c_a4b0<creature_instance_data_s009c_a4b0> ref4c;         // 0x04c
    AutoRefCount_s009c_a4b0<creature_instance_data_s009c_a4b0> ref50;         // 0x050
    AutoRefCount_s009c_a4b0<creature_instance_data_s009c_a4b0> ref54;         // 0x054
    unsigned long d58;                                  // 0x058
    unsigned long d5c;                                  // 0x05c
    unsigned long d60;                                  // 0x060
    vector_3      src_pos_rand;                         // 0x064
    unsigned long d70;                                  // 0x070
    unsigned long d74;                                  // 0x074
    AutoRefCount_s009c_a4b0<creature_instance_data_s009c_a4b0> ref78;         // 0x078
    unsigned long d7c;                                  // 0x07c
    vector_3      dst_pos_rand;                         // 0x080
    AutoRefCount_s009c_a4b0<cIVisualEffect> effect;                // 0x08c
    AutoRefCount_s009c_a4b0<cMWModel>       model;                 // 0x090
    unsigned long sound_id;                             // 0x094
    vector_3      last_sound_pos;                       // 0x098
    AutoRefCount_s009c_a4b0<IUnknown>       unknown;               // 0x0a4
    unsigned long da8;                                  // 0x0a8

    creature_effect_s009c_a4b0();                                  // 0x009caac0
    ~creature_effect_s009c_a4b0();                                 // 0x009c9870
    creature_effect_s009c_a4b0& operator=(const creature_effect_s009c_a4b0& o);   // 0x009cabd0
    void Clear(bool bAll);                              // 0x009c96b0
    void Init(cIVisualEffect* p, unsigned long bidx, unsigned long id);        // 0x009caa40
    void Init(unsigned long soundId, unsigned long bidx, unsigned long id);    // 0x009caa90
};
}
namespace nSPCreatureAnim {
namespace eastl {
struct hashtable_iterator {
    void* mpNode;       // +0x00
    void* mpBucket;     // +0x04
};  // namespace eastl
}
}
namespace nSPCreatureAnim {
using eastl::hashtable_iterator;
}
namespace nSPCreatureAnim {
struct effect_node {
    unsigned long     key;                  // +0x00
    creature_effect_s009c_a4b0*  value;                // +0x04
    effect_node*      next;                 // +0x08
};
}
namespace nSPCreatureAnim {
struct effect_pair {
    unsigned long     first;                // key
    creature_effect_s009c_a4b0*  second;               // value
};
}
namespace nSPCreatureAnim {
struct RehashInfo {
    unsigned char doRehash;         // +0x00
    unsigned long newBucketCount;   // +0x04
};
}
namespace nSPCreatureAnim {
struct effect_rehash_policy {
    unsigned char bytes[0x0c];
    void insert(RehashInfo* out, unsigned long nBucketCount,
                unsigned long nElementCount, int bForce);   // 0x00921440
};
}
namespace nSPCreatureAnim {
struct effect_table {
    void*                 pad_00;           // +0x00
    void**                mpBucketArray;    // +0x04
    unsigned long         mnBucketCount;    // +0x08
    unsigned long         mnElementCount;   // +0x0c
    effect_rehash_policy  policy;           // +0x10
    void*                 mpFreeList;       // +0x1c
    unsigned char         pad_20[0x0c];     // +0x20
    unsigned long         mnNodeSize;       // +0x2c

    hashtable_iterator find(const unsigned long& key) const;            // 0x00645ed0
    hashtable_iterator* insert(hashtable_iterator* out, const effect_pair* v, bool bRehash);  // 0x009cae00
    void Rehash(unsigned long nNewBucketCount);                        // 0x00a22220
};
}
namespace nSPCreatureAnim {
struct EffectFreeList {
    creature_effect_s009c_a4b0** mpBegin;
    creature_effect_s009c_a4b0** mpEnd;
};
}
namespace nSPCreatureAnim {
extern EffectFreeList* g_EffectFreeList;    // 0x0166c068
}
namespace nSPCreatureAnim {
struct creature_instance_data_full : creature_instance_data_s009c_a4b0 {
    unsigned char pad_000[0x17a0];
    effect_table  effects;                              // +0x17a0

    int* LookupEffect(unsigned long key);                                       // 0x009cab60
    creature_effect_s009c_a4b0* AllocateEffect(unsigned long key, bool bFlag, hashtable_iterator* pOut);  // 0x009cb300
};
}
namespace nSPCreatureAnim {
namespace eastl {
static const char* const kAllocator = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
}
}
namespace nSPCreatureAnim {
namespace eastl {
struct BlockDef_s009c_a4b0 {
    unsigned char bytes[0x468];
};
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009b3e40(BlockDef_s009c_a4b0* dst, const BlockDef_s009c_a4b0* src);                    // copy-construct one
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009c0a70(BlockDef_s009c_a4b0* dst, unsigned long n, const BlockDef_s009c_a4b0* value); // fill_n
}
}
namespace nSPCreatureAnim {
namespace eastl {
void* FUN_009c84d0(const BlockDef_s009c_a4b0* first, const BlockDef_s009c_a4b0* last, BlockDef_s009c_a4b0* dst);  // copy -> dst+n
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009be710(void* a, void* b, void* c, void* d, void* e);
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009c8580(BlockDef_s009c_a4b0* dst, BlockDef_s009c_a4b0* first, BlockDef_s009c_a4b0* last);
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009ca480(BlockDef_s009c_a4b0* first, BlockDef_s009c_a4b0* last, const BlockDef_s009c_a4b0* value);
}
}
namespace nSPCreatureAnim {
namespace eastl {
struct BlockDefVec {
    BlockDef_s009c_a4b0* mpBegin;          // +0x00
    BlockDef_s009c_a4b0* mpEnd;            // +0x04
    BlockDef_s009c_a4b0* mpCapacity;       // +0x08

    void insert(BlockDef_s009c_a4b0* position, unsigned long n, const BlockDef_s009c_a4b0& value);    // 0x009caee0
};
}
}
namespace nSPCreatureAnim {
namespace eastl {
struct EffectItem {
    unsigned char bytes[0x28];
};
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009be750(EffectItem* dst, EffectItem* first, EffectItem* last);   // move-construct range
}
}
namespace nSPCreatureAnim {
namespace eastl {
void* FUN_009c8510(EffectItem* first, EffectItem* last, EffectItem* dst);   // copy -> dst+n
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009c89d0(EffectItem* first, unsigned long n, const EffectItem* value, EffectItem* pos);
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009c85c0(EffectItem* first, EffectItem* last);                    // destroy range
}
}
namespace nSPCreatureAnim {
namespace eastl {
void  FUN_009c8970(EffectItem* first, EffectItem* last, const EffectItem* value);  // fill
}
}
namespace nSPCreatureAnim {
namespace eastl {
struct EffectItemVec {
    EffectItem* mpBegin;        // +0x00
    EffectItem* mpEnd;          // +0x04
    EffectItem* mpCapacity;     // +0x08

    void insert(EffectItem* position, unsigned long n, const EffectItem& value);    // 0x009cb0d0
};
}
}
// ---- items of slice s009ca4b0 end

// ---- items of slice s009cb3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01485720;    // 1.0f
extern const float DAT_01471064;    // 0.5f
extern const float DAT_01470f1c;    // 2.0f
extern const float DAT_013eb960;    // 0.01f
extern const float DAT_01447408;    // 3.4028235e+38 (FLT_MAX)
extern const float DAT_0155123c;    // 3.4028235e+38
extern const char  DAT_013f5b98[];  // "%s"
extern const char  DAT_014478ac[];
extern const char  DAT_0144789c[];
int  __cdecl Snprintf8(char* dst, unsigned cap, const char* fmt, ...);   // 0x009384e0
void* __fastcall FUN_009b3cd0(void* self);                               // 0x009b3cd0 construct default element (ret 0)
void __cdecl FUN_009b4310(void* first, void* last, void* dst);           // 0x009b4310 eastl::move (0x468)
void __cdecl FUN_009bed40(void* first, void* last, void* dst);           // 0x009bed40 eastl::move (0x28)
void __cdecl FUN_009c8630(float* out, int data);                         // 0x009c8630
void __cdecl FUN_009c86e0(float* out, int* idx, int data);               // 0x009c86e0
void __cdecl FUN_009c87e0(void* out, int* idx, int elem);                // 0x009c87e0
namespace nSPCreatureAnim {
struct creature_effect_s009c_b3f0;
}
namespace nSPCreatureAnim {
struct effect_node_s009c_b3f0 {
    unsigned long    key;       // +0x00
    creature_effect_s009c_b3f0* value;     // +0x04
    effect_node_s009c_b3f0*     next;      // +0x08
};
}
namespace nSPCreatureAnim {
struct hashtable_iterator_s009c_b3f0 {
    effect_node_s009c_b3f0*  mpNode;       // +0x00
    effect_node_s009c_b3f0** mpBucket;     // +0x04
    hashtable_iterator_s009c_b3f0() {}
    hashtable_iterator_s009c_b3f0(effect_node_s009c_b3f0* n, effect_node_s009c_b3f0** b) { mpBucket = b; mpNode = n; }
    hashtable_iterator_s009c_b3f0(const hashtable_iterator_s009c_b3f0& o)
    { mpBucket = o.mpBucket; mpNode = o.mpNode; }
    hashtable_iterator_s009c_b3f0& operator=(const hashtable_iterator_s009c_b3f0& o)
    { mpNode = o.mpNode; mpBucket = o.mpBucket; return *this; }
};
}
namespace nSPCreatureAnim {
struct range_out {
    effect_node_s009c_b3f0*  first;        // +0x00
    effect_node_s009c_b3f0** firstBucket;  // +0x04
    effect_node_s009c_b3f0*  last;         // +0x08
    effect_node_s009c_b3f0** lastBucket;   // +0x0c
};
}
namespace nSPCreatureAnim {
struct effect_table_s009c_b3f0 {
    void*           pad_00;         // +0x00
    effect_node_s009c_b3f0**   mpBucketArray;  // +0x04
    unsigned long   mnBucketCount;  // +0x08
    unsigned long   mnElementCount; // +0x0c
    unsigned char   pad_10[0x0c];   // +0x10 rehash policy
    effect_node_s009c_b3f0*    mpFreeList;     // +0x1c
    unsigned char   pad_20[0x0c];   // +0x20
    effect_node_s009c_b3f0*    mpInlineNode;   // +0x30

    range_out* equal_range(range_out* out, const unsigned long* key);   // 0x009a6dd0
    hashtable_iterator_s009c_b3f0 erase(hashtable_iterator_s009c_b3f0 position);              // 0x00b51640
};
}
namespace nSPCreatureAnim {
struct effect_free_list {
    typedef creature_effect_s009c_b3f0* value_type;
    creature_effect_s009c_b3f0** mpBegin;      // +0x00
    creature_effect_s009c_b3f0** mpEnd;        // +0x04
    creature_effect_s009c_b3f0** mpCapacity;   // +0x08
    void DoInsertValue(creature_effect_s009c_b3f0** pos, creature_effect_s009c_b3f0* const& value);   // 0x00a80dd0
    void push_back(creature_effect_s009c_b3f0* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) value_type(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace nSPCreatureAnim {
extern effect_free_list* g_EffectFreeList_s009c_b3f0;      // 0x0166c068
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_b3f0;
}
namespace nSPCreatureAnim {
template <class T> struct AutoRefCount_s009c_b3f0 {
    T* mpObject;
    AutoRefCount_s009c_b3f0() : mpObject(0) {}
    AutoRefCount_s009c_b3f0(T* p) : mpObject(p) {}
    AutoRefCount_s009c_b3f0& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};
}
namespace nSPCreatureAnim {
template <> struct AutoRefCount_s009c_b3f0<cMWModel> {
    cMWModel* mpObject;
    AutoRefCount_s009c_b3f0() : mpObject(0) {}
    AutoRefCount_s009c_b3f0(cMWModel* p) : mpObject(p) {}
    AutoRefCount_s009c_b3f0& operator=(cMWModel* p);       // 0x00478db0
    operator cMWModel*() const { return mpObject; }
};
}
namespace nSPCreatureAnim {
struct float3 { float x, y, z; };
}
namespace nSPCreatureAnim {
struct float4 { float x, y, z, w; };
}
namespace nSPCreatureAnim {
struct creature_effect_s009c_b3f0 {
    unsigned long key;                                  // 0x000
    unsigned long id;                                   // 0x004
    unsigned long bidx;                                 // 0x008
    vector_3      local_pos;                            // 0x00c
    vector_4      local_rot;                            // 0x018
    bool          f28;                                  // 0x028
    bool          f29;                                  // 0x029
    unsigned char pad_2a[2];
    float         f2c;                                  // 0x02c
    bool          f30;                                  // 0x030
    unsigned char pad_31[3];
    unsigned long d34;                                  // 0x034
    unsigned long d38;                                  // 0x038
    unsigned long d3c;                                  // 0x03c
    unsigned long d40;                                  // 0x040
    unsigned long d44;                                  // 0x044
    union { long i; float f; } data48;                  // 0x048
    AutoRefCount_s009c_b3f0<creature_instance_data_s009c_b3f0> ref4c;         // 0x04c
    AutoRefCount_s009c_b3f0<creature_instance_data_s009c_b3f0> ref50;         // 0x050
    AutoRefCount_s009c_b3f0<creature_instance_data_s009c_b3f0> ref54;         // 0x054
    unsigned long d58;                                  // 0x058
    unsigned long d5c;                                  // 0x05c
    unsigned long d60;                                  // 0x060
    vector_3      src_pos_rand;                         // 0x064
    unsigned long d70;                                  // 0x070
    unsigned long d74;                                  // 0x074
    AutoRefCount_s009c_b3f0<creature_instance_data_s009c_b3f0> ref78;         // 0x078
    unsigned long d7c;                                  // 0x07c
    vector_3      dst_pos_rand;                         // 0x080
    AutoRefCount_s009c_b3f0<cIVisualEffect> effect;                // 0x08c
    AutoRefCount_s009c_b3f0<cMWModel>       model;                 // 0x090
    unsigned long sound_id;                             // 0x094
    vector_3      last_sound_pos;                       // 0x098
    AutoRefCount_s009c_b3f0<IUnknown>       unknown;               // 0x0a4
    unsigned long da8;                                  // 0x0a8

    void Clear(bool bAll);                              // 0x009c96b0
    creature_effect_s009c_b3f0& operator=(const creature_effect_s009c_b3f0& o);   // 0x009cabd0
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_b3f0 {
    int AddRef();                                       // 0x0099cab0
    int Release();  // 0x009c4cc0 (nSPCreatureAnim::creature_instance_data::Release)
    unsigned char pad_000[0x384];
    unsigned char bodyVec[0x0c];                        // 0x384 (begin/end/cap)
    unsigned char pad_390[0x3c8 - 0x390];
    unsigned long counter_3c8;                          // 0x3c8
    unsigned char pad_3cc[0x3f5 - 0x3cc];
    unsigned char flag_3f5;                             // 0x3f5
    unsigned char pad_3f6[0x17a0 - 0x3f6];
    effect_table_s009c_b3f0  effects;                              // 0x17a0

    bool UpdateEffect(creature_effect_s009c_b3f0* p);              // 0x009c9910

    creature_effect_s009c_b3f0* AllocateEffect(unsigned long key, bool bFlag,
                                    hashtable_iterator_s009c_b3f0* pOut);                  // 0x009cb300
    hashtable_iterator_s009c_b3f0 EraseEffect(hashtable_iterator_s009c_b3f0 position);        // 0x009cb3f0
    void RemoveEffect(creature_effect_s009c_b3f0* p);                                      // 0x009cb460
    void ClearAllEffects();                                                     // 0x009cb4f0
    void AttachEffect(hashtable_iterator_s009c_b3f0* out, creature_instance_data_s009c_b3f0* src,
                      effect_node_s009c_b3f0* node, effect_node_s009c_b3f0** bucket,
                      unsigned long bidx, hashtable_iterator_s009c_b3f0* pOut);            // 0x009cb5a0
};
}
namespace nSPCreatureAnim {
struct body_flags_150 {
    unsigned char flags;                // +0x00
    unsigned char pad_01[0xa7];
    void Set(unsigned long fourcc, int flag);   // 0x009b3090
};
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_b3f0 {
    char          name[0x104];          // 0x000
    unsigned long instance_id;          // 0x104
    unsigned long group_id;             // 0x108
    float3        rest_center;          // 0x10c
    float4        rest_orientation;     // 0x118
    unsigned char pad_128[0x138 - 0x128];
    float         f138;                 // 0x138
    float         f13c;                 // 0x13c
    float         f140;                 // 0x140
    unsigned char pad_144[0x150 - 0x144];
    body_flags_150 f150;                // 0x150
    unsigned long f1f8;                 // 0x1f8
    unsigned long f1fc;                 // 0x1fc
    unsigned long f200;                 // 0x200
    unsigned char pad_204[0x208 - 0x204];
    unsigned long f208;                 // 0x208
    unsigned char pad_20c[0x21c - 0x20c];
    unsigned long f21c;                 // 0x21c
    char          foot_name[0x104];     // 0x220
    unsigned char pad_324[0x350 - 0x324];
    float         out350;               // 0x350
    float         out354;               // 0x354
    float         out358;               // 0x358
    unsigned char pad_35c[0x36c - 0x35c];
    float         f36c;                 // 0x36c
    unsigned char pad_370[0x378 - 0x370];
    float         f378;                 // 0x378
    float         f37c;                 // 0x37c
    unsigned char pad_380[0x468 - 0x380];

    void Clear();                       // 0x009b3180
};
}
namespace nSPCreatureAnim {
struct body_static_vec {
    creature_body_static_data_s009c_b3f0* mpBegin;         // +0x00
    creature_body_static_data_s009c_b3f0* mpEnd;           // +0x04
    creature_body_static_data_s009c_b3f0* mpCapacity;      // +0x08

    void insert(creature_body_static_data_s009c_b3f0* position, unsigned long n,
                creature_body_static_data_s009c_b3f0* value);                          // 0x009caee0
    void resize(unsigned long n);                                       // 0x009cb840
};
}
namespace nSPCreatureAnim {
struct effect_item {
    unsigned char pad_00[0x0c];
    vector_3      a;            // 0x0c
    vector_4      b;            // 0x18
};
}
namespace nSPCreatureAnim {
struct effect_item_vec {
    effect_item* mpBegin;       // +0x00
    effect_item* mpEnd;         // +0x04
    effect_item* mpCapacity;    // +0x08

    void insert(effect_item* position, unsigned long n, effect_item* value);   // 0x009cb0d0
    void resize(unsigned long n);                                       // 0x009cb8f0
};
}
namespace {

struct cArguments {
    void* MainArguments(int n);                 // 0x00838320
};

struct cIParser {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
    virtual unsigned long GetBlockCount(unsigned long id);   // +0x9c
};

struct cBlockState;                             // the +0xc member's type
struct cNumBlocksCommand {
    cIParser*     mParser;      // +0x04
    int           mRefCount;    // +0x08
    cBlockState*  mState;       // +0x0c

    virtual void Execute(cArguments& args);      // 0x009cb9b0
};

}  // namespace
// ---- items of slice s009cb3f0 end

// ---- items of slice s009ccfe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) char* __cdecl fgets(char*, int, void*);
extern "C" __declspec(dllimport) int   __cdecl fclose(void*);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) int   __cdecl fprintf(void*, const char*, ...);
extern "C" __declspec(dllimport) void* __cdecl __iob_func(void);
extern unsigned long g_01550fe4;   // "crncmd" name entry
extern unsigned long g_01550fec;   // "isplant" name entry
extern unsigned long g_01550fcc;   // "cal3DRootBlockIndex" name entry
extern unsigned long g_01550ff0;   // "numBlocks" name entry
extern unsigned long g_01550fc4;   // "block" name entry
extern void* g_vtbl_crncmd;        // 0x014474f8
extern void* g_vtbl_isplant;       // 0x0144745c
extern void* g_vtbl_calrtblki;     // 0x01447474
extern void* g_vtbl_numblk;        // 0x0144748c
extern void* g_vtbl_blkblk;        // 0x014474a4
void  __cdecl FUN_009a9b70(const char* path, int cap, char* out, char** tail);   // 0x009a9b70
int   __cdecl nSPCreatureAnim_FinalizeCreature(void* creature);                  // 0x009c4a30
void  __cdecl FUN_009b3010(void* elem);                                          // 0x009b3010
void  __cdecl FUN_009cbdb0(char* instance);                                      // 0x009cbdb0
void  __cdecl FUN_009c1dc0(void* data, int bAll);                                // 0x009c1dc0 creature_static_data::Clear
void* __cdecl EA_ArgScript_CreateParser();                                       // 0x008408d0
void  __cdecl EA_ArgScript_cCommandBase_ctor(void* p);                           // 0x0083c800
void  __cdecl EA_ArgScript_AppPropsFields_ctor(void* p);                         // 0x0083cdd0
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct ulong_map {
    unsigned long* __thiscall get(const unsigned long* key); // 0x00a2e060
};
void* __cdecl map_node_free(void* node, void* key);                              // 0x009a9600
void  __cdecl operator_delete(void* p);                                          // 0x00f47380 ??3
extern "C" __declspec(dllimport) char* __cdecl strrchr_s009c_cfe0(const char*, int);
extern "C" __declspec(dllimport) char* __cdecl strstr_s009c_cfe0(const char*, const char*);
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_cfe0;             // retail size 0x468
}
namespace nSPCreatureAnim {
struct cArguments_s009c_cfe0 {
    unsigned long* __thiscall MainArguments(int n);          // 0x00838320
};
}
namespace nSPCreatureAnim {
struct cIParser_s009c_cfe0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
    virtual unsigned long GetBlockCount(unsigned long id);    // vtable +0x9c
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
    virtual void v44();
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009c_cfe0 {
    char  pad_000[0x208];
    char  name[0x104];                  // 0x208 (wide chars)
    char  pad_30c[0x384 - 0x30c];
    creature_body_static_data_s009c_cfe0* bodies_begin;   // 0x384
    creature_body_static_data_s009c_cfe0* bodies_end;     // 0x388
    creature_body_static_data_s009c_cfe0* bodies_cap;     // 0x38c
    char  pad_390[0x3c8 - 0x390];
    int   count_3c8;                    // 0x3c8
    char  pad_3cc[0x3f0 - 0x3cc];
    int   flag_3f0;                     // 0x3f0
};
}
namespace nSPCreatureAnim {
struct cParentIndexCommand {
    cIParser_s009c_cfe0* parser;                   // +4
    char      pad_08[4];
    char*     state;                    // +0xc
    virtual void Execute(cArguments_s009c_cfe0& args);          // 0x009ccfe0
};
}
namespace nSPCreatureAnim {
struct cBlockBlockCommand_s009c_cfe0 {
    cIParser_s009c_cfe0* parser;                   // +4
    char      pad_08[0x30 - 0x08];
    char*     state;                    // +0x30
    virtual void Execute(cArguments_s009c_cfe0& args);          // 0x009cd040
};
}
namespace nSPCreatureAnim {
struct body_clear_t {
    void __thiscall Clear0();                        // 0x009b3180
};
}
// ---- items of slice s009ccfe0 end

// @ 0x009c8460
void creature_mesh_instance_data::Dispose()
{
    void* sfx = (void*)*(void**)((char*)this + 0x94);
    if (sfx) {
        if (!*(char*)((char*)this + 0x30) ||
            (*(ulong*)((char*)this + 0x34) & 0x800020) != 0x800000) {
            char flag = 1;
            if (*(char*)((char*)this + 0x30) &&
                (*(unsigned char*)((char*)this + 0x34) & 0x10))
                flag = 0;
            AudioSetListener2(sfx, flag);
        }
        AudioQueryB(sfx);
        *(void**)((char*)this + 0x94) = 0;
    }
}

// @ 0x009c8510
void Elem28CopyFwd(Elem28* first, Elem28* last, Elem28* dst)
{
    if (first != last) {
        float* d = (float*)((char*)dst + 0x14);
        float* s = (float*)((char*)first + 0x14);
        do {
            if (dst) {
                dst->key = first->key;
                dst->idx = first->idx;
                d[-3] = s[-3]; d[-2] = s[-2]; d[-1] = s[-1];
                d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
            }
            first = (Elem28*)((char*)first + 0x28); s += 10;
            dst   = (Elem28*)((char*)dst + 0x28);   d += 10;
        } while (first != last);
    }
}

// @ 0x009c85c0
void Elem28CopyBack(Elem28* first, Elem28* last, Elem28* dstEnd)
{
    if (last != first) {
        float* d = (float*)((char*)dstEnd + 0x14);
        float* s = (float*)((char*)last + 0x14);
        do {
            last   = (Elem28*)((char*)last   - 0x28); s -= 10;
            dstEnd = (Elem28*)((char*)dstEnd - 0x28); d -= 10;
            dstEnd->key = last->key;
            dstEnd->idx = last->idx;
            d[-3] = s[-3]; d[-2] = s[-2]; d[-1] = s[-1];
            d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4];
        } while (last != first);
    }
}

// @ 0x009c8630
void creature_mesh_instance_data::MinClearance(float* minOut, creature_static_data* sd)
{
    int n = (int)((char*)sd->BodiesEnd - (char*)sd->BodiesBegin);
    n = n / 0x468;
    if (n > 0) {
        body_static_data* b = sd->BodiesBegin;
        do {
            if (b->flags_150 & 8) {
                float a0 = Abs(b->c130);
                float a1 = Abs(b->c134);
                float a2 = Abs(b->c138);
                float h = b->rz - ((b->c13c * a1 + b->c140 * a2) + b->c138 * a0);
                if (h < *minOut)
                    *minOut = h;
            }
            b = (body_static_data*)((char*)b + 0x468);
            --n;
        } while (n);
    }
}

// @ 0x009c86e0
void creature_mesh_instance_data::MinClearanceIdx(float* minOut, uint* idxOut, creature_static_data* sd)
{
    int n = (int)((char*)sd->BodiesEnd - (char*)sd->BodiesBegin);
    n = n / 0x468;
    int i = 0;
    if (n > 0) {
        body_static_data* base = sd->BodiesBegin;
        do {
            body_static_data* b = (body_static_data*)((char*)base + i * 0x468);
            if (b->f208 == 0 && (b->flags_150 & 2) && !(b->flags_150 & 4)) {
                float h = b->rz - ((b->c13c * Abs(b->c134)
                                  + b->c140 * Abs(b->c138))
                                 + Abs(b->c130) * b->c138);
                if (h < *minOut) {
                    *minOut = h;
                    *idxOut = (uint)i;
                }
            }
            ++i;
        } while (i < n);
    }
}

// @ 0x009c87e0
void creature_mesh_instance_data::BodyToWorld(float* out, uint* outIdx, body_static_data* b)
{
    if ((b->flags_150 & 0x60) == 0) {
        *outIdx = (uint)b->f1f8;
        Vec3 v = QuaternionVectorTransform((const float*)((const char*)b + 0x118),
                                           b->rest_center);
        out[0] = b->rx - v.x;
        out[1] = b->ry - v.y;
        out[2] = b->rz - v.z;
        return;
    }
    *outIdx = (uint)b->f1fc;
    out[0] = b->rx;
    out[1] = b->ry;
    out[2] = b->rz;
}

// @ 0x009c8890
void creature_mesh_instance_data::SetWorldState()
{
    void* sound = (void*)*(void**)((char*)this + 0x8c);
    if (!(*(char*)((char*)this + 0x30) &&
          (*(ulong*)((char*)this + 0x34) & 0x800020) == 0x800000)) {
        if (sound) {
            char flag = 1;
            if (*(char*)((char*)this + 0x30) &&
                (*(unsigned char*)((char*)this + 0x34) & 0x10))
                flag = 0;
            AudioSetFlag(sound, flag);
        }
    }
    void* obj = (void*)*(void**)((char*)this + 0x8c);
    if (obj) {
        *(void**)((char*)this + 0x8c) = 0;
        ((IRefObj*)obj)->vpad1();
    }
}

// @ 0x009c8900
void creature_mesh_instance_data::RefreshWorldState()
{
    void* sfx = (void*)*(void**)((char*)this + 0x94);
    if (sfx) {
        char flag = 1;
        if (*(char*)((char*)this + 0x30) &&
            (*(unsigned char*)((char*)this + 0x34) & 0x10))
            flag = 0;
        AudioSetListener2(sfx, flag);
    }
    sfx = (void*)*(void**)((char*)this + 0x8c);
    if (sfx) {
        char flag = 1;
        if (*(char*)((char*)this + 0x30) &&
            (*(unsigned char*)((char*)this + 0x34) & 0x10))
            flag = 0;
        AudioSetFlag(sfx, flag);
    }
}

// @ 0x009c8970
void Elem28ConstructRange(Elem28* first, Elem28* last, const Elem28* src)
{
    while (first != last) {
        first->key = src->key;
        first->idx = src->idx;
        const float* s = (const float*)((const char*)src + 0x8);
        float* d = (float*)((char*)first + 0x14);
        d[-3] = s[0]; d[-2] = s[1]; d[-1] = s[2];
        d[0] = s[3]; d[1] = s[4]; d[2] = s[5]; d[3] = s[6]; d[4] = s[7];
        ++first;
    }
}

// @ 0x009c89d0
void Elem28FillN(Elem28* dst, ulong n, const Elem28* src)
{
    if (!n)
        return;
    float* d = (float*)((char*)dst + 0x14);
    do {
        if (dst) {
            dst->key = src->key;
            dst->idx = src->idx;
            const float* s = (const float*)((const char*)src + 0x8);
            d[-3] = s[0]; d[-2] = s[1]; d[-1] = s[2];
            d[0] = s[3]; d[1] = s[4]; d[2] = s[5]; d[3] = s[6]; d[4] = s[7];
        }
        --n;
        dst = (Elem28*)((char*)dst + 0x28);
        d += 10;
    } while (n);
}

// @ 0x009c8a90
void cBlockBlockCommand::OnEndBlock(bool bCancel)
{
    if (bCancel)
        return;

    CreatureCommandState* s = mState;
    BlockDef* b = s->block;
    checkerlib::vector_3_s009c_8a90 tmp;
    checkerlib::vector_3_s009c_8a90 mid = (s->boxMax + s->boxMin) * 0.5f;

    const checkerlib::vector_3_s009c_8a90* r = checkerlib::QuaternionVectorTransform(&tmp, &b->orient, &mid);
    s = mState;
    checkerlib::vector_3_s009c_8a90 c = *r + s->anchor;
    b->center.x = c.x; b->center.y = c.y; b->center.z = c.z;

    checkerlib::vector_3_s009c_8a90 d = s->anchor - c;
    r = QuaternionVectorTransformInverse(&tmp, &b->orient, &d);
    b->local = *r;

    s = mState;
    b->half = (s->boxMax - s->boxMin) * 0.5f;
    if (b->half.x <= 0.0f) b->half.x = 0.5f;
    if (b->half.y <= 0.0f) b->half.y = 0.5f;
    if (b->half.z <= 0.0f) b->half.z = 0.5f;

    FUN_009fc220(b->flags());
    int parentIdx = b->parent;
    b->childMark = -1;
    b->refCount = 0;

    if (parentIdx != -1) {
        BlockDef* p = mState->owner->blocks + parentIdx;
        p->refCount++;
        s = mState;
        // anchor2 relative to the parent block / this block, rotated by that block's orientation
        checkerlib::vector_3_s009c_8a90 vp, vb;
        vp.x = s->anchor2.x - p->center.x; vp.y = s->anchor2.y - p->center.y; vp.z = s->anchor2.z - p->center.z;
        checkerlib::vector_3_s009c_8a90 rp = QuaternionVectorTransformInverse(p->orient, vp);
        b->parentOffset.x = rp.x; b->parentOffset.y = rp.y; b->parentOffset.z = rp.z;
        vb.x = s->anchor2.x - b->center.x; vb.y = s->anchor2.y - b->center.y; vb.z = s->anchor2.z - b->center.z;
        checkerlib::vector_3_s009c_8a90 rb = QuaternionVectorTransformInverse(b->orient, vb);
        b->parentLocal.x = rb.x; b->parentLocal.y = rb.y; b->parentLocal.z = rb.z;
        r = ScaledOffset(&tmp, b, 1.0f);
        b->scaled = *r;
        b->scaledLen = (float)sqrt(b->scaled.x * b->scaled.x + b->scaled.y * b->scaled.y
                                   + b->scaled.z * b->scaled.z);
    }

    b->limit = FLT_MAX;
    if (b->hash == (uint32_t)-1) {
        if (b->name[0] == '0' && b->name[1] == 'x')
            b->hash = strtol(b->name, 0, 16);
        else
            b->hash = EA::Hash::FNV1_String8(b->name, 0x811c9dc5, 1);
    }

    float sc = b->scale;
    CreatureCommandState* st = mState;
    b->offset.x = b->offset.x * sc;
    b->offset.y = sc * b->offset.y;
    b->offset.z = b->offset.z * sc;
    b->offset.x = b->local.x + b->offset.x;
    b->offset.y = b->local.y + b->offset.y;
    b->offset.z = b->local.z + b->offset.z;
    st->count++;
}

// @ 0x009c90d0
void cEffectBlockCommand::FUN_009c90d0(EA::ArgScript::cArguments_s009c_8a90* a)
{
    strcpy(mpState->mpDef->mName, *a->MainArguments(1));
}

// @ 0x009c9130
void cEffectBlockCommand::FUN_009c9130(EA::ArgScript::cArguments_s009c_8a90* a)
{
    a->MainArguments(1);
}

// @ 0x009c9170
void cEffectBlockCommand::FUN_009c9170(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec1c.x = mpParser->ParseFloat(v[0]);
    mpState->mVec1c.y = mpParser->ParseFloat(v[1]);
    mpState->mVec1c.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c9200
void cEffectBlockCommand::FUN_009c9200(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(1);
    mpState->mpDef->mBool340 = mpParser->ParseBool(v[0]);
}

// @ 0x009c9230
void cEffectBlockCommand::FUN_009c9230(EA::ArgScript::cArguments_s009c_8a90* a)
{
    strcpy(mpState->mpDef->mName2, *a->MainArguments(1));
}

// @ 0x009c9260
void cEffectBlockCommand::FUN_009c9260(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    {   // the destination subobject is re-bound (address taken) for every component
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec324;
        dst->x = mpParser->ParseFloat(v[0]);
    }
    {
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec324;
        dst->y = mpParser->ParseFloat(v[1]);
    }
    {
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec324;
        dst->z = mpParser->ParseFloat(v[2]);
    }
}

// @ 0x009c92e0
void cEffectBlockCommand::FUN_009c92e0(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec10.x = mpParser->ParseFloat(v[0]);
    mpState->mVec10.y = mpParser->ParseFloat(v[1]);
    mpState->mVec10.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c9340
void cEffectBlockCommand::FUN_009c9340(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    {
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec330;
        dst->x = mpParser->ParseFloat(v[0]);
    }
    {
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec330;
        dst->y = mpParser->ParseFloat(v[1]);
    }
    {
        checkerlib::vector_3_s009c_8a90* dst = &mpState->mpDef->mVec330;
        dst->z = mpParser->ParseFloat(v[2]);
    }
}

// @ 0x009c93c0
void cEffectBlockCommand::FUN_009c93c0(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(4);
    float q[4];
    q[0] = mpParser->ParseFloat(v[0]);
    q[1] = mpParser->ParseFloat(v[1]);
    q[2] = mpParser->ParseFloat(v[2]);
    q[3] = mpParser->ParseFloat(v[3]);
    float* dst = mpState->mpDef->mQuat;
    dst[0] = q[0];
    dst[1] = q[1];
    dst[2] = q[2];
    dst[3] = q[3];
}

// @ 0x009c9460
void cEffectBlockCommand::FUN_009c9460(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec28.x = mpParser->ParseFloat(v[0]);
    mpState->mVec28.y = mpParser->ParseFloat(v[1]);
    mpState->mVec28.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c94c0
void cEffectBlockCommand::FUN_009c94c0(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec34.x = mpParser->ParseFloat(v[0]);
    mpState->mVec34.y = mpParser->ParseFloat(v[1]);
    mpState->mVec34.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c95e0
void cEffectBlockCommand::FUN_009c95e0(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(2);
    if (mpState->mCount < 0x20) {
        mpState->mpDef->mIds[mpState->mCount] = FeedbackLookupName(v[0]);
        mpState->mpDef->mFlags[mpState->mCount] = (unsigned char)mpParser->ParseInt(v[1]);
        ++mpState->mCount;
    }
}

// @ 0x009c9650
void cEffectBlockCommand::FUN_009c9650(EA::ArgScript::cArguments_s009c_8a90* a)
{
    char const* const* v = a->MainArguments(2);
    mpState->mpDef->mEntries.FUN_0099c4a0(mpParser->ParseInt(v[0]), 0,
                                          mpParser->ParseFloat(v[1]), 1.0f);
}

// @ 0x009c96b0
namespace nSPCreatureAnim {
void creature_effect_s009c_8a90::Clear(bool bAll)
{
    if (!bAll) {
        SetWorldState();
        Dispose();
        model = 0;
        unknown = 0;
        da8 = 0;
    }
    id = 0;
    bidx = 0;
    f29 = false;
    f2c = 1.0f;
    f30 = false;
    d34 = 0;
    d40 = 0;
    d3c = 0;
    d38 = 0;
    data48.i = 0;
    ref54 = 0;
    ref50 = ref54.mpObject;
    ref4c = ref50.mpObject;
    d58 = d5c = d60 = 0xffffffff;
    ref78 = 0;
    d7c = 0xffffffff;
    local_pos.x = 0.0f;
    local_pos.y = 0.0f;
    local_pos.z = 0.0f;
    local_rot.x = 0.0f;
    local_rot.y = 0.0f;
    local_rot.z = 0.0f;
    local_rot.w = 1.0f;
    unknown = 0;
    da8 = 0;
    effect = 0;
    model = 0;
    sound_id = 0;
}
}  // namespace nSPCreatureAnim

// @ 0x009c9870
namespace nSPCreatureAnim {
creature_effect_s009c_8a90::~creature_effect_s009c_8a90()
{
    key = 0xffffffff;
    Clear(false);
}
}  // namespace nSPCreatureAnim

// @ 0x009c9910
namespace nSPCreatureAnim {
bool creature_instance_data_s009c_9910::UpdateEffect(cAnimEffect* effect)
{
    bool result = false;
    checkerlib::vector_3_s009c_9910 pos;

    if (effect->mbEventLocated) {
        if (effect->mpEffect && effect->mpEffect->IsPlaying())
            result = true;
        if (effect->mSoundHandle && IsSoundPlaying(effect->mSoundHandle))
            result = true;
        if ((effect->mpCreature && !effect->mpCreature->mbReady) ||
            (effect->mpCreature2 && !effect->mpCreature2->mbReady) ||
            (effect->mpCreature3 && !effect->mpCreature3->mbReady))
            result = false;
        if (effect->mpColorCreature && !effect->mpColorCreature->mbReady) {
            result = false;
            return result;
        }
        if (result) {
            float scalar = 1.0f;
            float alpha = 1.0f;
            bool bUsePos2;
            checkerlib::vector_3_s009c_9910 pos2;
            checkerlib::vector_4_s009c_9910 quat;
            checkerlib::vector_3_s009c_9910 colorPos;
            checkerlib::vector_3_s009c_9910 colorPos2;
            checkerlib::vector_4_s009c_9910 colorQuat;
            uint32_t flags = effect->mEventFlags;
            if (flags & 0x105800) {
                if ((flags & 0x8000) && effect->mOrientMode != 0)
                    bUsePos2 = false;
                else
                    bUsePos2 = true;
                ComputeEventLocationState(0, flags, effect->mLocFlags, effect->mEventValue, this,
                                          effect->mpCreature, effect->mBone, &pos,
                                          bUsePos2 ? &pos2 : 0,
                                          effect->mOrientMode == 0 ? &quat : 0,
                                          effect->mScaleMode == 0 ? &scalar : 0,
                                          &effect->mDirection, &pos, &pos2, 0);
                if (effect->mOrientMode == 1)
                    ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags2,
                                              effect->mEventValue, this, effect->mpCreature2,
                                              effect->mBone2, 0, bUsePos2 ? 0 : &pos2, &quat,
                                              effect->mScaleMode == 1 ? &scalar : 0, 0, &pos,
                                              &pos2, 0);
                if (effect->mScaleMode == 2)
                    ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags2,
                                              effect->mEventValue, this, effect->mpCreature2,
                                              effect->mBone2, 0, 0, 0, &scalar, 0, &pos, &pos2, 0);
            }
            if (effect->mEventFlags & 0x2000)
                ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags3,
                                          effect->mEventValue, this, effect->mpColorCreature,
                                          effect->mColorBone, &colorPos, &colorPos2, &colorQuat,
                                          &alpha, &effect->mColor, &colorPos, &colorPos2, 0);
            if (effect->mpEffect) {
                if (effect->mEventFlags & 0x104800) {
                    XformMsg msg;
                    effect->mpEffect->GetXform(&msg);
                    if (effect->mEventFlags & 0x800)
                        msg.SetPos(pos);
                    if (effect->mEventFlags & 0x4000) {
                        checkerlib::matrix_3x3_s009c_9910 rotMatrix = checkerlib::QuaternionToMatrix(checkerlib::QuaternionConjugate(quat));
                        msg.SetRot(rotMatrix);
                    }
                    if (effect->mEventFlags & 0x100000)
                        msg.SetScale(scalar);
                    effect->mpEffect->SetXform(&msg);
                }
                if (effect->mEventFlags & 0x1000)
                    SetEffectScale(effect->mpEffect, scalar);
                if (effect->mEventFlags & 0x2000) {
                    SetEffectColor(effect->mpEffect, &colorPos);
                    SetEffectAlpha(effect->mpEffect, 1.0f);
                }
            }
            if (effect->mSoundHandle) {
                if ((effect->mEventFlags & 0x800) &&
                    checkerlib::Length2(pos - effect->mLastSoundPos) >= 0.25f) {
                    SetSoundPosition(effect->mSoundHandle, &pos);
                    effect->mLastSoundPos.x = pos.x;
                    effect->mLastSoundPos.y = pos.y;
                    effect->mLastSoundPos.z = pos.z;
                }
                uint32_t evFlags = effect->mEventFlags;
                if ((evFlags & 0x400) && effect->mBone < BoneCount()) {
                    creature_bone& bone = mBonesBegin[effect->mBone];
                    if (bone.mpStatic->mFlags & 0x20) {
                        float weight = 1.0f;
                        if ((evFlags & 0x300) == 0x200)
                            weight = *(float*)&effect->mEventValue;
                        bone.mAnimState.SetFloatParam(0x4d5bf589, 1, GetSoundValue(effect->mSoundHandle), weight);
                    }
                }
            }
        }
    } else {
        checkerlib::vector_4_s009c_9910 q;
        if (effect->mBoneIndex < BoneCount()) {
            creature_bone& bone = mBonesBegin[effect->mBoneIndex];
            pos.x = effect->mOffset.x;
            pos.y = effect->mOffset.y;
            pos.z = effect->mOffset.z;
            if (effect->mbScaleWithCreature)
                pos *= scale;
            checkerlib::vector_3_s009c_9910 local = bone.pos + checkerlib::QuaternionVectorTransform(bone.rot, pos);
            pos = checkerlib::QuaternionVectorTransform(rot, local) + this->pos;
            q = checkerlib::QuaternionProduct(checkerlib::QuaternionProduct(rot, bone.rot), effect->mRotation);
        } else {
            pos = this->pos + checkerlib::QuaternionVectorTransform(rot, effect->mOffset);
            q = checkerlib::QuaternionProduct(rot, effect->mRotation);
        }
        checkerlib::matrix_3x3_s009c_9910 rotMatrix = checkerlib::QuaternionToMatrix(checkerlib::QuaternionConjugate(q));

        if (effect->mpEffect && effect->mpEffect->IsPlaying()) {
            result = true;
            XformMsg msg;
            effect->mpEffect->GetXform(&msg);
            msg.SetPos(pos);
            msg.SetRot(rotMatrix);
            if (effect->mbScaleWithCreature)
                msg.SetScale(scale * effect->mScale);
            effect->mpEffect->SetXform(&msg);
        }
        if (effect->mpCallbackData && effect->mpCallback &&
            effect->mpCallback(effect->mpCallbackData, &pos, &rotMatrix))
            result = true;
        if (effect->mSoundHandle && IsSoundPlaying(effect->mSoundHandle)) {
            result = true;
            if (checkerlib::Length2(pos - effect->mLastSoundPos) >= 0.25f) {
                SetSoundPosition(effect->mSoundHandle, &pos);
                effect->mLastSoundPos.x = pos.x;
                effect->mLastSoundPos.y = pos.y;
                effect->mLastSoundPos.z = pos.z;
            }
        }
        if (effect->mpXformTarget) {
            effect->mpXformTarget->msg.SetPos(pos);
            effect->mpXformTarget->msg.SetRot(rotMatrix);
            result = true;
        }
    }
    return result;
}
}  // namespace nSPCreatureAnim

// @ 0x009ca4b0
void cBlockBlockCommand_s009c_a4b0::OnRegister(cIParser_s009c_a4b0* parser, cState_s009c_a4b0* state)
{
    mState = (cBlockBlockState*)state;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);

#define REGISTER(Name, keyword) \
    AddCommand(BlockKeywords::keyword, new ("ArgScript/" #Name, 0, 0, 0, 0) c##Name##Command())

    REGISTER(Name, name);
    REGISTER(InstanceId, instanceId);
    REGISTER(Version, version);
    REGISTER(ParentIndex, parentIndex);
    REGISTER(SymmetricIndex, symmetricIndex);
    REGISTER(JointPosition, jointPosition);
    REGISTER(SubmeshIndex, submeshIndex);
    REGISTER(LeftHanded, leftHanded);
    REGISTER(Cal3DBoneName, cal3DBoneName);
    REGISTER(Cal3DOrigin, cal3DOrigin);
    REGISTER(Position, position);
    REGISTER(EffectsOrigin, effectsOrigin);
    REGISTER(Orientation, orientation);
    REGISTER(BBoxMin, bBoxMin);
    REGISTER(BBoxMax, bBoxMax);
    REGISTER(Mass, mass);
    REGISTER(Scale, scale);
    REGISTER(SoundIDFoot, soundIDFoot);
    REGISTER(SoundIDMouth, soundIDMouth);
    REGISTER(SoundIDWeapon, soundIDWeapon);
    REGISTER(Cap, cap);
    REGISTER(Deform, deformChannel);

#undef REGISTER
}

// @ 0x009caac0
namespace nSPCreatureAnim {
creature_effect_s009c_a4b0::creature_effect_s009c_a4b0()
: local_pos(), local_rot(), ref4c(), ref50(), ref54(),
      src_pos_rand(), ref78(), dst_pos_rand(), effect(), model(),
      last_sound_pos(), unknown()
{
    Clear(true);
}
}  // namespace nSPCreatureAnim

// @ 0x009cab60
namespace nSPCreatureAnim {
int* creature_instance_data_full::LookupEffect(unsigned long key)
{
    effect_table& t = effects;
    unsigned long k = key;
    hashtable_iterator it = t.find(k);
    if (it.mpNode != t.mpBucketArray[t.mnBucketCount])
        return *(int**)((char*)it.mpNode + 4);
    return 0;
}
}  // namespace nSPCreatureAnim

// @ 0x009cabb0
void __cdecl FUN_009cabb0(nSPCreatureAnim::creature_effect_s009c_a4b0* p)
{
    if (!p)
        return;
    p->~creature_effect_s009c_a4b0();
    operator delete(p);
}

// @ 0x009cabd0
namespace nSPCreatureAnim {
creature_effect_s009c_a4b0& creature_effect_s009c_a4b0::operator=(const creature_effect_s009c_a4b0& o)
{
    key = o.key;
    id = o.id;
    bidx = o.bidx;
    local_pos = o.local_pos;
    local_rot = o.local_rot;
    f28 = o.f28;
    f29 = o.f29;
    f2c = o.f2c;
    f30 = o.f30;
    d34 = o.d34;
    d38 = o.d38;
    d3c = o.d3c;
    d40 = o.d40;
    d44 = o.d44;
    data48.i = o.data48.i;
    data48.f = o.data48.f;
    ref4c = o.ref4c.mpObject;
    ref50 = o.ref50.mpObject;
    ref54 = o.ref54.mpObject;
    d58 = o.d58;
    d5c = o.d5c;
    d60 = o.d60;
    src_pos_rand = o.src_pos_rand;
    d70 = o.d70;
    d74 = o.d74;
    ref78 = o.ref78.mpObject;
    d7c = o.d7c;
    dst_pos_rand = o.dst_pos_rand;
    effect = o.effect.mpObject;
    model = o.model.mpObject;
    sound_id = o.sound_id;
    last_sound_pos = o.last_sound_pos;
    unknown = o.unknown.mpObject;
    da8 = o.da8;
    return *this;
}
}  // namespace nSPCreatureAnim

// @ 0x009cae00
namespace nSPCreatureAnim {
hashtable_iterator* effect_table::insert(hashtable_iterator* out, const effect_pair* v, bool)
{
    RehashInfo pr;
    policy.insert(&pr, mnBucketCount, mnElementCount, 1);
    if (pr.doRehash)
        Rehash(pr.newBucketCount);

    unsigned long n = v->first % mnBucketCount;

    effect_node* node;
    if (mpFreeList) {
        node = (effect_node*)mpFreeList;
        mpFreeList = *(void**)mpFreeList;
    } else {
        node = (effect_node*)EAAllocate(mnNodeSize, "EASTL", 0, 0,
            (int)"c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (node) {
        node->key = v->first;
        node->value = v->second;
    }
    node->next = 0;

    effect_node* bucket = (effect_node*)mpBucketArray[n];
    if (bucket) {
        effect_node* p = bucket;
        do {
            if (v->first == p->key) {
                node->next = p->next;
                p->next = node;
                goto done;
            }
            p = p->next;
        } while (p);
    }
    node->next = bucket;
    mpBucketArray[n] = node;
done:
    mnElementCount++;
    out->mpNode = node;
    out->mpBucket = &mpBucketArray[n];
    return out;
}
}  // namespace nSPCreatureAnim

// @ 0x009caee0
namespace nSPCreatureAnim { namespace eastl {
void BlockDefVec::insert(BlockDef_s009c_a4b0* position, unsigned long n, const BlockDef_s009c_a4b0& value)
{
    if ((unsigned long)(mpCapacity - mpEnd) / 0x468 < n) {
        unsigned long size = (unsigned long)(mpEnd - mpBegin) / 0x468;
        unsigned long newCap = size * 2;
        if (size == 0) newCap = 1;
        unsigned long want = size + n;
        if (want > newCap) newCap = want;
        BlockDef_s009c_a4b0* newBegin = newCap
            ? (BlockDef_s009c_a4b0*)EAAllocate(newCap * 0x468, "EASTL", 0, 0, (int)kAllocator, 0xd1) : 0;
        BlockDef_s009c_a4b0* mid = (BlockDef_s009c_a4b0*)FUN_009c84d0(mpBegin, position, newBegin);
        FUN_009c0a70(mid, n, &value);
        BlockDef_s009c_a4b0* newEnd = (BlockDef_s009c_a4b0*)FUN_009c84d0(position, mpEnd, mid + n);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = newBegin + newCap;
        return;
    }
    if (n == 0)
        return;
    BlockDef_s009c_a4b0 tmp;
    FUN_009b3e40(&tmp, &value);
    BlockDef_s009c_a4b0* oldEnd = mpEnd;
    unsigned long roomAtEnd = (unsigned long)(mpEnd - position) / 0x468;
    if (n < roomAtEnd) {
        BlockDef_s009c_a4b0* split = oldEnd - n;
        FUN_009be710(&tmp, oldEnd, oldEnd, split, &tmp);
        mpEnd += n;
        FUN_009c8580(position, split, oldEnd);
        FUN_009ca480(position, position + n, &tmp);
        return;
    }
    FUN_009c0a70(oldEnd, n - roomAtEnd, &tmp);
    mpEnd += (n - roomAtEnd);
    FUN_009be710(&tmp, position, oldEnd - n, oldEnd, &tmp);
    mpEnd += roomAtEnd;
    FUN_009ca480(position, oldEnd, &tmp);
}
}}  // namespace nSPCreatureAnim::eastl

// @ 0x009cb0d0
namespace nSPCreatureAnim { namespace eastl {
void EffectItemVec::insert(EffectItem* position, unsigned long n, const EffectItem& value)
{
    if ((unsigned long)(mpCapacity - mpEnd) / 0x28 < n) {
        unsigned long size = (unsigned long)(mpEnd - mpBegin) / 0x28;
        unsigned long newCap = size * 2;
        if (size == 0) newCap = 1;
        unsigned long want = size + n;
        if (want > newCap) newCap = want;
        EffectItem* newBegin = newCap
            ? (EffectItem*)EAAllocate(newCap * 0x28, "EASTL", 0, 0, (int)kAllocator, 0xd1) : 0;
        EffectItem* mid = (EffectItem*)FUN_009c8510(mpBegin, position, newBegin);
        FUN_009c89d0(mid, n, &value, position);
        EffectItem* newEnd = (EffectItem*)FUN_009c8510(position, mpEnd, mid + n);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = newBegin + newCap;
        return;
    }
    if (n == 0)
        return;
    EffectItem tmp;
    FUN_009be750(&tmp, (EffectItem*)&value, (EffectItem*)&value + 1);
    EffectItem* oldEnd = mpEnd;
    unsigned long roomAtEnd = (unsigned long)(mpEnd - position) / 0x28;
    if (n < roomAtEnd) {
        EffectItem* split = oldEnd - n;
        FUN_009be750(split, split, oldEnd);
        mpEnd += n;
        FUN_009c85c0(position, split);
        FUN_009c8970(position, split, &tmp);
        return;
    }
    FUN_009c89d0(oldEnd, n - roomAtEnd, &tmp, position);
    mpEnd += (n - roomAtEnd);
    FUN_009be750(position, oldEnd - n, oldEnd);
    mpEnd += roomAtEnd;
    FUN_009c8970(position, oldEnd, &tmp);
}
}}  // namespace nSPCreatureAnim::eastl

// @ 0x009cb300
namespace nSPCreatureAnim {
creature_effect_s009c_a4b0* creature_instance_data_full::AllocateEffect(unsigned long key, bool bFlag, hashtable_iterator* pOut)
{
    effect_table& t = effects;
    unsigned long k = key;
    hashtable_iterator it = t.find(k);
    if (!bFlag) {
        if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
            if (pOut) *pOut = it;
            return 0;
        }
    }
    EffectFreeList* fl = g_EffectFreeList;
    creature_effect_s009c_a4b0* p;
    if (fl->mpBegin == fl->mpEnd) {
        p = (creature_effect_s009c_a4b0*)EAAllocate(0xac, "Anim/cid/new_ce", 0, 0, 0, 0);
        if (p)
            p = new (p) creature_effect_s009c_a4b0();
        else
            p = 0;
    } else {
        p = *--fl->mpEnd;
    }
    effect_pair v;
    v.first = k;
    v.second = p;
    t.insert(&it, &v, false);
    if (pOut) *pOut = it;
    p->key = key;
    p->f28 = bFlag;
    return p;
}
}  // namespace nSPCreatureAnim

// @ 0x009cb3f0
namespace nSPCreatureAnim {
hashtable_iterator_s009c_b3f0 creature_instance_data_s009c_b3f0::EraseEffect(hashtable_iterator_s009c_b3f0 pos)
{
    g_EffectFreeList_s009c_b3f0->push_back(pos.mpNode->value);
    pos.mpNode->value->Clear(false);
    return effects.erase(pos);
}
}  // namespace nSPCreatureAnim

// @ 0x009cb460
namespace nSPCreatureAnim {
void creature_instance_data_s009c_b3f0::RemoveEffect(creature_effect_s009c_b3f0* p)
{
    if (!p)
        return;
    unsigned long key = p->key;
    effect_table_s009c_b3f0* t = &effects;
    range_out range;
    t->equal_range(&range, &key);
    if (range.first == t->mpBucketArray[t->mnBucketCount])
        return;
    effect_node_s009c_b3f0* node = range.first;
    effect_node_s009c_b3f0** bucket = range.firstBucket;
    if (node == range.last)
        return;
    while (node->value != p) {
        node = node->next;
        while (!node)
            node = *++bucket;
        if (node == range.last)
            return;
    }
    *(hashtable_iterator_s009c_b3f0*)&range = EraseEffect(hashtable_iterator_s009c_b3f0(node, bucket));
}
}  // namespace nSPCreatureAnim

// @ 0x009cb4f0
namespace nSPCreatureAnim {
void creature_instance_data_s009c_b3f0::ClearAllEffects()
{
    effect_node_s009c_b3f0** buckets = effects.mpBucketArray;
    effect_node_s009c_b3f0** bucket = buckets;
    effect_node_s009c_b3f0* node = *bucket;
    if (!node) {
        do {
            bucket++;
        } while (*bucket == 0);
        node = *bucket;
    }
    effect_node_s009c_b3f0* end = buckets[effects.mnBucketCount];
    if (node != end) {
        hashtable_iterator_s009c_b3f0 it;
        do {
            g_EffectFreeList_s009c_b3f0->push_back(node->value);
            node->value->Clear(false);
            it = effects.erase(hashtable_iterator_s009c_b3f0(node, bucket));
            node = it.mpNode;
            bucket = it.mpBucket;
        } while (node != end);
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009cb5a0
namespace nSPCreatureAnim {
void creature_instance_data_s009c_b3f0::AttachEffect(hashtable_iterator_s009c_b3f0* out, creature_instance_data_s009c_b3f0* src, effect_node_s009c_b3f0* node, effect_node_s009c_b3f0** bucket, unsigned long bidx, hashtable_iterator_s009c_b3f0* pOut)
{
    if (!src) {
        out->mpNode = 0;
        out->mpBucket = 0;
        return;
    }
    effect_node_s009c_b3f0** end = &src->effects.mpBucketArray[src->effects.mnBucketCount];
    if (node == *end)
        goto fail;
    {
        creature_effect_s009c_b3f0* old = node->value;
        if (!old)
            goto fail;
        creature_effect_s009c_b3f0* ne = AllocateEffect(old->key, old->f28, pOut);
        if (!ne)
            goto fail;
        *ne = *old;
        ne->bidx = bidx;
        if (ne->ref4c.mpObject == src) {
            ne->ref4c = this;
            ne->d58 = (ne->d58 == old->bidx) ? bidx : 1;
        }
        if (ne->ref50.mpObject == src) {
            ne->ref50 = this;
            ne->d5c = (ne->d5c == old->bidx) ? bidx : 1;
        }
        if (ne->ref54.mpObject == src) {
            ne->ref54 = this;
            ne->d60 = (ne->d60 == old->bidx) ? bidx : 1;
        }
        if (ne->ref78.mpObject == src) {
            ne->ref78 = this;
            ne->d7c = (ne->d7c == old->bidx) ? bidx : 1;
        }
        if (old->effect.mpObject) {
            cIVisualEffect* p = old->effect.mpObject;
            old->effect.mpObject = 0;
            p->Release();
        }
        old->model = 0;
        old->sound_id = 0;
        if (old->unknown.mpObject) {
            IUnknown* p = old->unknown.mpObject;
            old->unknown.mpObject = 0;
            p->Release();
        }
        *out = EraseEffect(hashtable_iterator_s009c_b3f0(node, bucket));
        return;
    }
fail:
    out->mpNode = *end;
    out->mpBucket = end;
}
}  // namespace nSPCreatureAnim

// @ 0x009cb760
namespace nSPCreatureAnim {
void __cdecl FUN_009cb760(creature_instance_data_s009c_b3f0* self)
{
    effect_table_s009c_b3f0& t = self->effects;
    effect_node_s009c_b3f0** buckets = t.mpBucketArray;
    effect_node_s009c_b3f0** bucket = buckets;
    effect_node_s009c_b3f0* node = *bucket;
    if (!node) {
        bucket++;
        node = *bucket;
        while (!node) {
            bucket++;
            node = *bucket;
        }
    }
    if (node != buckets[t.mnBucketCount]) {
        hashtable_iterator_s009c_b3f0 it;
        do {
            if (!node->value || !self->UpdateEffect(node->value)) {
                g_EffectFreeList_s009c_b3f0->push_back(node->value);
                node->value->Clear(false);
                it = t.erase(hashtable_iterator_s009c_b3f0(node, bucket));
                node = it.mpNode;
                bucket = it.mpBucket;
            } else {
                node = node->next;
                while (!node)
                    node = *++bucket;
            }
        } while (node != buckets[t.mnBucketCount]);
    }
}
}  // namespace nSPCreatureAnim

// @ 0x009cb840
namespace nSPCreatureAnim {
void body_static_vec::resize(unsigned long n)
{
    if (n > (unsigned long)(mpEnd - mpBegin)) {
        creature_body_static_data_s009c_b3f0 tmp;
        FUN_009b3cd0(&tmp);
        insert(mpEnd, n - (unsigned long)(mpEnd - mpBegin), &tmp);
        return;
    }
    creature_body_static_data_s009c_b3f0* p = mpBegin + n;
    FUN_009b4310(mpEnd, mpEnd, p);
    mpEnd -= mpEnd - p;
}
}  // namespace nSPCreatureAnim

// @ 0x009cb8f0
namespace nSPCreatureAnim {
void effect_item_vec::resize(unsigned long n)
{
    effect_item* begin = mpBegin;
    effect_item* end = mpEnd;
    if (n > (unsigned long)(end - begin)) {
        effect_item tmp;
        insert(end, n - (unsigned long)(end - begin), &tmp);
        return;
    }
    effect_item* p = begin + n;
    FUN_009bed40(end, end, p);
    mpEnd -= (end - p);
}
}  // namespace nSPCreatureAnim

// @ 0x009cb9b0
void cNumBlocksCommand::Execute(cArguments& args)
{
    void* p = args.MainArguments(1);
    unsigned long n = mParser->GetBlockCount(*(unsigned long*)p);
    ((nSPCreatureAnim::body_static_vec*)(*(unsigned long*)((char*)mState + 0x44) + 0x384))->resize(n);
}

// @ 0x009cb9f0
namespace nSPCreatureAnim {
void FUN_009cb9f0(float* pos, unsigned long* idx, char* instance)
{
    unsigned long base = *(unsigned long*)(instance + 0x384);
    unsigned long v = *(unsigned long*)(base + (*idx) * 0x468 + 0x200);
    long count = (long)(*(unsigned long*)(instance + 0x388) - base) / 0x468;
    long want = count + (v != 0xffffffff ? 1 : 0) + 1;

    ((body_static_vec*)(instance + 0x384))->resize((unsigned long)want);

    bool bVar6 = false;
    if ((long)count >= (long)want) {
        *(unsigned char*)(instance + 0x3f5) = 0;
        return;
    }
    unsigned long off = count * 0x468;
    do {
        creature_body_static_data_s009c_b3f0* e =
            (creature_body_static_data_s009c_b3f0*)(*(unsigned long*)(instance + 0x384) + off);
        e->Clear();
        Snprintf8(e->name, 0x104, DAT_013f5b98, DAT_014478ac);
        Snprintf8(e->foot_name, 0x104, DAT_0144789c, count);
        e->f378 = DAT_01485720;
        e->group_id = 0x40600000;
        e->instance_id = 0x6b2c0771;
        e->f1f8 = count;
        e->f21c = 0xffffffff;
        e->f37c = DAT_01471064;
        if (v == 0xffffffff) {
            e->f200 = 0xffffffff;
            e->f1fc = *idx;
        } else {
            e->f1fc = bVar6 ? v : *idx;
            e->f200 = bVar6 ? want - 2 : want - 1;
        }
        e->rest_center.x = pos[0];
        e->rest_center.y = pos[1];
        e->rest_center.z = pos[2];
        if (bVar6)
            e->rest_center.x = -pos[0];
        e->f138 = DAT_013eb960;
        e->f13c = DAT_013eb960;
        e->f140 = DAT_013eb960;
        e->f150.Set(0x746f6f66, 1);
        e->f36c = DAT_01447408;
        unsigned long pi = e->f1fc;
        creature_body_static_data_s009c_b3f0* par =
            (creature_body_static_data_s009c_b3f0*)(*(unsigned long*)(instance + 0x384) + pi * 0x468);
        par->f208 += 1;

        float dx = e->rest_center.x - par->rest_center.x;
        float dy = e->rest_center.y - par->rest_center.y;
        float dz = e->rest_center.z - par->rest_center.z;
        float qx = par->rest_orientation.x;
        float qy = par->rest_orientation.y;
        float qz = par->rest_orientation.z;
        float qw = par->rest_orientation.w;

        float t0 = (qy * qx - -(qz * qw)) * dy + (qz * qx + -(qy * qw)) * dz
                 + (-(qz * qz) + -(qy * qy)) * dx;
        float t1 = (-(qz * qz) + -(qx * qx)) * dy + (qz * qy - -(qx * qw)) * dz
                 + (qy * qx + -(qz * qw)) * dx;
        float t2 = (-(qy * qy) + -(qx * qx)) * dz + (qz * qy + -(qx * qw)) * dy
                 + (qz * qx - -(qy * qw)) * dx;
        e->out350 = t0 * DAT_01470f1c + dx;
        e->out354 = t1 * DAT_01470f1c + dy;
        e->out358 = t2 * DAT_01470f1c + dz;

        *(unsigned long*)(instance + 0x3c8) += 1;
        count++;
        off += 0x468;
        bVar6 = true;
    } while ((long)count < (long)want);
    *(unsigned char*)(instance + 0x3f5) = 0;
}
}  // namespace nSPCreatureAnim

// @ 0x009cbdb0
namespace nSPCreatureAnim {
void FUN_009cbdb0(char* instance)
{
    float best = DAT_01447408;
    float limit = DAT_01447408;
    int   index = -1;

    FUN_009c8630(&best, (int)instance);
    FUN_009c86e0(&limit, &index, (int)instance);
    float prev = limit;

    if (index == -1)
        return;
    do {
        if (best <= limit)
            return;
        if ((best - prev) * DAT_0155123c <= limit - prev)
            return;
        creature_body_static_data_s009c_b3f0* e =
            (creature_body_static_data_s009c_b3f0*)(*(unsigned long*)(instance + 0x384) + index * 0x468);
        index = -1;
        vector_3 p;
        if (e->f150.flags & 2) {
            FUN_009c87e0(&p, &index, (int)e);
            if (index != -1)
                FUN_009cb9f0(&p.x, (unsigned long*)&index, instance);
        }
        limit = DAT_01447408;
        index = -1;
        FUN_009c86e0(&limit, &index, (int)instance);
    } while (index != -1);
}
}  // namespace nSPCreatureAnim

// @ 0x009cbee0
namespace nSPCreatureAnim {
char InitCreatureStaticDataFromResource(creature_static_data_s009c_bee0* sdp, void* res)
{
    char* sd = (char*)sdp;
    uint8_t* r = (uint8_t*)res;
    uint32_t boneMap[255];

    ((StaticDataStub*)sd)->Clear(0);
    at<uint32_t>(sd, 0x318) = at<uint32_t>(r, 8);        // instance_id
    at<uint32_t>(sd, 0x31c) = at<uint32_t>(r, 0x10);     // group_id
    at<uint32_t>(sd, 0x320) = InitVerbCollection(at<uint32_t>(r, 0x18));  // type_id

    PollenKey key;
    key.instance = at<uint32_t>(r, 8);
    key.type = 0x30bdee3;
    uint32_t baseGroup = at<uint32_t>(r, 0x10) & 0xe0ffffff;
    key.group = baseGroup;
    const wchar_t* assetName = GetAssetName(&key);
    if (assetName) {
        const wchar_t* suffix = L"";
        if (baseGroup != at<uint32_t>(r, 0x10)) suffix = L" (baby)";
        Sprintf16((wchar_t*)sd, L"%s%s", assetName, suffix);
    } else {
        appendW((wchar_t*)sd, L"No Pollen Metadata", 0x104);
    }
    WideToNarrow((wchar_t*)sd, sd + 0x208, 0x100);  // filename

    // skin_colors[3] (vector_3 each) at +0x324
    {
        float* src = (float*)(r + 0x38);
        float* dst = (float*)(sd + 0x324);
        for (int i = 3; i != 0; --i) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            src += 3;
            dst += 3;
        }
    }

    int numBodies = (at<int>(r, 0x9c) - at<int>(r, 0x98)) / 0x8c;
    char* bodiesVec = sd + 0x384;  // eastl::vector<creature_body_static_data> Bodies (begin at +0x384, end at +0x388)
    ((BodyVecStub*)bodiesVec)->resize(numBodies);

    int meshBones = 0;  // num_bones_with_mesh_parts
    if (numBodies != 0) {
        short s = at<short>(at<char*>(r, 0x98), 4);
        if (s != -1) {
            meshBones = s;
            at<int>(sd, 0x3f0) = 1;
        }
    }
    at<int>(sd, 0x378) = meshBones;
    at<uint8_t>(sd, 0x380) = 0;
    at<uint8_t>(sd, 0x3f5) = at<uint8_t>(r, 0x110) & 1;

    {
        int srcOff = 0;
        for (int i = 0; i < numBodies; ++i) {
            char* sb = at<char*>(r, 0x98) + srcOff;  // source body record, stride 0x8c
            int bidx;
            if (i < meshBones)
                bidx = i + 1;
            else
                bidx = -(int)(i != meshBones) & i;
            char* b = at<char*>(bodiesVec, 0) + bidx * 0x468;
            ((BodyStub*)b)->Clear();
            BU(0x108) = at<uint32_t>(sb, 0x84);  // group_id
            uint32_t instId = at<uint32_t>(sb, 0x88);
            BU(0x104) = instId;                  // instance_id
            uint32_t grpId = BU(0x108);
            BU(0x1f8) = bidx;                    // caps.bidx
            BU(0x21c) = i;                       // source index
            Snprintf8(b, 0x104, "0x%08x!0x%08x.prop", grpId, instId);
            Snprintf8(b + 0x220, 0x104, "joint_b%d_n%d", bidx, (int)at<short>(sb, 2));
            BF(0x424) = 0.0f;                    // mHipHeight__SCALABLE
            BU(0x428) = 0;                       // foot_chain_foot_bidx
            at<uint8_t>(b, 0x42c) = 0;           // foot_chain_root_joint_bidx
            if (at<uint8_t>(sb, 8) & 0x20) BF(0x424) = at<float>(sb, 0x80);
            if (at<uint8_t>(sb, 8) & 0x40) BU(0x428) = at<uint32_t>(sb, 0x80);
            if (at<uint16_t>(sb, 8) & 0x400) at<uint8_t>(b, 0x42c) = 1;
            at<uint8_t>(b, 0x370) = (uint8_t)(~(uint8_t)(at<uint16_t>(sb, 8) >> 9) & 1);  // left_handed
            at<uint8_t>(b, 0x371) = (uint8_t)(at<uint16_t>(sb, 8) >> 0xb) & 1;
            BF(0x378) = at<float>(sb, 0x2c);     // local_joint_r.y
            BF(0x37c) = at<float>(sb, 0x6c);     // local_joint_r.z

            float cz = at<float>(sb, 0x5c);
            float cy = at<float>(sb, 0x58);
            float cx = at<float>(sb, 0x54);
            float scale = at<float>(sb, 0x2c);
            float e0 = at<float>(sb, 0x14) * scale;
            float e1 = at<float>(sb, 0x18) * scale;
            float e2 = at<float>(sb, 0x1c) * scale;
            float e3 = at<float>(sb, 0x20) * scale;
            float e4 = at<float>(sb, 0x24) * scale;
            float e5 = at<float>(sb, 0x28) * scale;

            float m[9];
            m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
            m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
            {
                int k = 0, k1;
                float* p = (float*)(sb + 0x38);
                do {
                    k1 = k + 1;
                    m[k] = p[-2];
                    m[k + 3] = p[-1];
                    m[k + 6] = p[0];
                    k = k1;
                    p += 3;
                } while (k1 < 3);
            }
            float qbuf[4];
            float* q = matrix_to_quaternion(qbuf, m);
            BF(0x118) = q[0];  // rest orientation quaternion
            BF(0x11c) = q[1];
            BF(0x120) = q[2];
            BF(0x124) = q[3];

            float qy = BF(0x11c);
            float hx = (e4 + e1) * 0.5f;
            float hy = (e3 + e0) * 0.5f;
            float hz = (e5 + e2) * 0.5f;
            float qw = BF(0x124);
            float qx = BF(0x118);
            float qyqw = qy * qw;
            float qxqw = qx * qw;
            float qz = BF(0x120);
            float qzqw = qz * qw;
            float nqxqx = -(qx * qx);
            float qzqx = qz * qx;
            float qzqy = qz * qy;
            float t = ((((-(qy * qy) + nqxqx) * hz + (qzqy + qxqw) * hx) + (qzqx - qyqw) * hy) * 2.0f + hz) + cz;
            float dz = cz - t;
            BF(0x114) = t;                       // rest_center.z
            t = ((((qzqx + qyqw) * hz + (qy * qx - qzqw) * hx) + (-(qz * qz) + -(qy * qy)) * hy) * 2.0f + hy) + cx;
            float dx = cx - t;
            float ty = ((((-(qz * qz) + nqxqx) * hx + (qzqy - qxqw) * hz) + (qy * qx + qzqw) * hy) * 2.0f + hx) + cy;
            BF(0x10c) = t;                       // rest_center.x
            BF(0x110) = ty;                      // rest_center.y
            float dy = cy - ty;

            qx = BF(0x118);
            qw = BF(0x124);
            float nxw = -(qx * qw);
            qy = BF(0x11c);
            float nyw = -(qy * qw);
            qz = BF(0x120);
            float nxx = -(qx * qx);
            float nzw = -(qz * qw);
            BF(0x144) = (((-(qz * qz) + -(qy * qy)) * dx + (qy * qx - nzw) * dy) + (qz * qx + nyw) * dz) * 2.0f + dx;
            BF(0x148) = (((qy * qx + nzw) * dx + (-(qz * qz) + nxx) * dy) + (qz * qy - nxw) * dz) * 2.0f + dy;
            BF(0x14c) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qz * qy + nxw) * dy) * 2.0f + dz;
            BF(0x138) = (e3 - e0) * 0.5f;
            BF(0x140) = (e5 - e2) * 0.5f;
            BF(0x13c) = (e4 - e1) * 0.5f;
            for (int k = 0x324; k < 0x330; ++k) at<uint8_t>(b, k) = 0;
            float sc = at<float>(sb, 0x2c);
            float px = at<float>(sb, 0x64);
            float py = at<float>(sb, 0x68);
            float* ext = &BF(0x138);
            float yx = BF(0x148);
            float yy = BF(0x14c);
            BF(0x330) = at<float>(sb, 0x60) * sc + BF(0x144);
            BF(0x334) = yx + px * sc;
            BF(0x338) = yy + py * sc;
            for (int k = 3; k != 0; --k) {
                if (*ext <= 0.0f) *ext = 0.1f;
                ++ext;
            }

            uint32_t nApp = at<uint8_t>(sb, 0x10);
            if (nApp != 0) {
                float* fp = &BF(0x158);
                uint32_t k = 0;
                do {
                    *fp = at<float*>(r, 0xac)[at<uint16_t>(sb, 0xc) + k];
                    uint8_t v = at<uint8_t*>(r, 0xc0)[at<uint16_t>(sb, 0xc) + k];
                    ++k;
                    at<uint8_t>(b, 0x1d6 + k) = v;
                    ++fp;
                } while (k < nApp);
            }
            NormalizeFlags(b + 0x150);
            if (BU(0x154) & 4) ++at<int>(sd, 0x3c8);

            uint32_t v = at<uint8_t>(sb, 0xa);
            if (v == 0) v = 0xffffffff;
            BU(0x33c) = v;
            at<uint8_t>(b, 0x340) = at<uint8_t>(sb, 9) & 1;

            uint32_t nMass = at<uint8_t>(sb, 0x11);
            BU(0x380) = (nMass > 8) ? 8 : nMass;
            if (at<uint8_t>(sb, 0x11) != 0) {
                float* fp = &BF(0x38c);
                uint32_t k = 0;
                do {
                    uint16_t base = at<uint16_t>(sb, 0xe);
                    fp[0] = at<float*>(r, 0xe8)[base + k];
                    fp[2] = at<float*>(r, 0xfc)[base + k];
                    float mass = at<float*>(r, 0xd4)[base + k];
                    fp[-2] = mass;
                    if (mass == 0.0f) at<uint8_t>(sd, 0x380) = 1;
                    ++k;
                    fp += 5;
                } while (k < at<uint8_t>(sb, 0x11));
            }

            short parent = at<short>(sb, 4);
            if (parent == -1) {
                BU(0x1fc) = 0xffffffff;
            } else {
                int pi = parent;
                if (pi < meshBones)
                    BU(0x1fc) = pi + 1;
                else
                    BU(0x1fc) = -(int)(pi != meshBones) & pi;
            }
            srcOff += 0x8c;
            BU(0x200) = (int)at<short>(sb, 6);
            BU(0x204) = 0xffffffff;
            BU(0x208) = 0;
            BU(0x36c) = 0x7f7fffffu;  // FLT_MAX
        }
    }

    // second pass: child offsets relative to parents
    if ((unsigned)numBodies != 0) {
        int off = 0;
        unsigned remaining = numBodies;
        do {
            char* begin = at<char*>(bodiesVec, 0);
            char* b = begin + off;
            char* sb = at<char*>(r, 0x98) + BU(0x21c) * 0x8c;
            if (BU(0x1fc) != 0xffffffff) {
                int poff = BU(0x1fc) * 0x468;
                char* pb = begin + poff;
                ++at<int>(pb, 0x208);  // num_children
                float px = at<float>(sb, 0x54);
                float py = at<float>(sb, 0x58);
                float pz = at<float>(sb, 0x5c);
                if (at<uint8_t>(sb, 0xb) == 5 && at<short>(sb, 4) > -1) {
                    char* ps = at<char*>(r, 0x98) + at<short>(sb, 4) * 0x8c;
                    py = (at<float>(ps, 0x58) + py) * 0.5f;
                    pz = (at<float>(ps, 0x5c) + pz) * 0.5f;
                    px = (px + at<float>(ps, 0x54)) * 0.5f;
                }
                float dy = py - at<float>(pb, 0x110);
                float dx = px - at<float>(pb, 0x10c);
                float qy = at<float>(pb, 0x11c);
                float dz = pz - at<float>(pb, 0x114);
                float qw = at<float>(pb, 0x124);
                float qx = at<float>(pb, 0x118);
                float nxw = -(qx * qw);
                float qz = at<float>(pb, 0x120);
                float nxx = -(qx * qx);
                float nzw = -(qz * qw);
                float qzqy = qz * qy;
                float nyw = -(qy * qw);
                at<float>(b, 0x350) = (((qy * qx - nzw) * dy + (qz * qx + nyw) * dz) + (-(qz * qz) + -(qy * qy)) * dx) * 2.0f + dx;
                at<float>(b, 0x354) = (((-(qz * qz) + nxx) * dy + (qzqy - nxw) * dz) + (qy * qx + nzw) * dx) * 2.0f + dy;
                at<float>(b, 0x358) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qzqy + nxw) * dy) * 2.0f + dz;

                float ex = px - at<float>(b, 0x10c);
                float cqy = at<float>(b, 0x124);
                float cqx = at<float>(b, 0x11c);
                float ey = py - at<float>(b, 0x110);
                float ez = pz - at<float>(b, 0x114);
                float cqw = at<float>(b, 0x118);
                float cqz = at<float>(b, 0x120);
                float ncqwy = -(cqw * cqy);
                float ncqzy = -(cqz * cqy);
                float ncqww = -(cqw * cqw);
                float ncqxy = -(cqx * cqy);
                at<float>(b, 0x344) = (((cqx * cqw - ncqzy) * ey + (cqz * cqw + ncqxy) * ez) + (-(cqz * cqz) + -(cqx * cqx)) * ex) * 2.0f + ex;
                at<float>(b, 0x348) = (((-(cqz * cqz) + ncqww) * ey + (cqz * cqx - ncqwy) * ez) + (cqx * cqw + ncqzy) * ex) * 2.0f + ey;
                at<float>(b, 0x34c) = (((-(cqx * cqx) + ncqww) * ez + (cqz * cqx + ncqwy) * ey) + (cqz * cqw - ncqxy) * ex) * 2.0f + ez;

                float tmp[4];
                float* out = ComputeBodyVector(tmp, b, 1.0f);
                at<float>(b, 0x35c) = out[0];
                at<float>(b, 0x360) = out[1];
                at<float>(b, 0x364) = out[2];
                at<float>(b, 0x368) = sqrtf(at<float>(b, 0x35c) * at<float>(b, 0x35c) +
                                                       at<float>(b, 0x360) * at<float>(b, 0x360) +
                                                       at<float>(b, 0x364) * at<float>(b, 0x364));
            }
            off += 0x468;
        } while (--remaining != 0);
    }

    if (at<int>(sd, 0x3c8) == 0 && at<int>(sd, 0x3f0) == 0) FinishNoBranches(sd);
    char ok = PostProcess(sd);
    if (at<uint8_t>(sd, 0x3f4) == 0) at<uint8_t>(sd, 0x3f5) = 0;

    if (ok != 0) {
        unsigned count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        for (unsigned i = 0; i < count; ++i) {
            // recompute each time like the original
            char* bb = at<char*>(bodiesVec, 0) + i * 0x468;
            uint32_t srcIdx = at<uint32_t>(bb, 0x21c);
            if (srcIdx < 0xff) boneMap[srcIdx] = at<uint32_t>(bb, 0x1f8);
            count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        }

        unsigned nWig = (at<int>(r, 0x118) - at<int>(r, 0x114)) / 0x38;
        char* wigVec = sd + 0x398;  // eastl::vector<creature_body_wiggle_static_data> mWiggles
        ((WiggleVecStub*)wigVec)->resize(nWig);
        if (nWig != 0) {
            int srcOff = 0;
            int dstOff = 0;
            do {
                float* w = (float*)(at<char*>(r, 0x114) + srcOff);  // source wiggle record, stride 0x38
                uint32_t bi = boneMap[((uint32_t*)w)[0]];
                char* e = at<char*>(wigVec, 0) + dstOff;           // dest wiggle, stride 0x28
                char* sb = at<char*>(r, 0x98) + ((uint32_t*)w)[0] * 0x8c;
                char* b = at<char*>(bodiesVec, 0);
                at<uint32_t>(e, 4) = bi;
                at<uint32_t>(e, 0) = ((uint32_t*)w)[1];
                at<float>(e, 8) = at<float>(sb, 0x2c);
                float sc = at<float>(sb, 0x2c);
                float w3 = w[3];
                float w4 = w[4];
                float by = at<float>(b, bi * 0x468 + 0x148);
                float bz = at<float>(b, bi * 0x468 + 0x14c);
                at<float>(e, 0xc) = at<float>(b, bi * 0x468 + 0x144) + sc * w[2];
                at<float>(e, 0x10) = by + w3 * sc;
                at<float>(e, 0x14) = bz + w4 * sc;

                float m[9];
                m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
                m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
                {
                    int k = 0, k1;
                    float* p = w + 7;
                    do {
                        k1 = k + 1;
                        m[k] = p[-2];
                        m[k + 3] = p[-1];
                        m[k + 6] = p[0];
                        k = k1;
                        p += 3;
                    } while (k1 < 3);
                }
                float qbuf[4];
                float* q = matrix_to_quaternion(qbuf, m);
                srcOff += 0x38;
                at<float>(e, 0x18) = q[0];
                dstOff += 0x28;
                at<float>(e, 0x1c) = q[1];
                --nWig;
                at<float>(e, 0x20) = q[2];
                at<float>(e, 0x24) = q[3];
            } while (nWig != 0);
        }
    }
    return ok;
}
}  // namespace nSPCreatureAnim

// @ 0x009ccfe0
void nSPCreatureAnim::cParentIndexCommand::Execute(cArguments_s009c_cfe0& args)
{
    unsigned long* av = args.MainArguments(1);
    int v = (int)parser->GetBlockCount(*av);
    if (v == -1) {
        *(int*)(*(int*)(state + 0x40) + 0x1fc) = -1;
        return;
    }
    unsigned long key = (unsigned long)v;
    unsigned long* r = ((ulong_map*)(state + 0x48))->get(&key);
    *(int*)(*(int*)(state + 0x40) + 0x1fc) = (int)*r;
}

// @ 0x009cd040
void nSPCreatureAnim::cBlockBlockCommand_s009c_cfe0::Execute(cArguments_s009c_cfe0& args)
{
    unsigned long* av = args.MainArguments(1);
    *(int*)(state + 8) = 0;
    *(int*)(state + 0x40) = *(int*)(state + 4) * 0x468
                          + *(int*)(*(int*)(state + 0x44) + 0x384);
    ((body_clear_t*)*(void**)(state + 0x40))->Clear0();
    *(int*)(*(int*)(state + 0x40) + 0x108) = 0x40626000;
    *(int*)(*(int*)(state + 0x40) + 0x104) = -1;
    *(int*)(*(int*)(state + 0x40) + 0x1f8) = *(int*)(state + 4);
    *(int*)(*(int*)(state + 0x40) + 0x200) = -2;
    unsigned long v = parser->GetBlockCount(*av);
    *(unsigned long*)(*(int*)(state + 0x40) + 0x21c) = v;
    char* cur = *(char**)(state + 0x40);
    unsigned long* r = ((ulong_map*)(state + 0x48))->get((unsigned long*)(cur + 0x21c));
    *r = *(unsigned long*)(cur + 0x1f8);
    (*(void(__thiscall**)(cIParser_s009c_cfe0*, void*))(*(char**)parser + 0x8c))(parser, this);
}

// @ 0x009cd110
int __cdecl FUN_009cd110(nSPCreatureAnim::creature_static_data_s009c_cfe0* param_1, const char* param_2)
{
    char local_679 = 0;
    void* fp;
    char local_610[16];
    char local_600[0x1c8];
    char acStack_438[1036];
    char local_674[0x400];
    void* local_628;
    void* local_620 = 0;
    int   local_61c = 0;
    int   local_618 = 0;

    fp = fopen(param_2, "r");
    if (fp == 0)
        return 0;
    fgets(local_610, 0xd, fp);
    fclose(fp);
    FUN_009c1dc0(param_1, 0);

    {
        char* s = (char*)param_2;
        char* d = param_1->name;
        char c;
        do { c = *s; d[(int)(s - (char*)param_2)] = c; ++s; } while (c != 0);
    }
    {
        char* tail;
        FUN_009a9b70(param_2, 0x200, local_600, &tail);
        char* dot = strrchr_s009c_cfe0(tail, '.');
        *dot = 0;
        char* d = param_1->name;
        while (tail != dot + 1) {
            *(short*)d = (short)*tail++;
            d += 2;
        }
    }

    // build the block manager object
    char* base = local_674;
    *(void**)(base + 0x00) = base;
    *(int*) (base + 0x0c) = 0x1ff0ee3;
    *(int*) (base + 0x10) = 0;
    *(int*) (base + 0x14) = 0;
    for (int i = 0; i < 12; ++i) *(int*)(base + 0x20 + i * 4) = 0;  // zero 12-float block
    *(void**)(base + 0x58) = param_1;
    *(void**)(base + 0x48) = base;              // local_624 = local_628
    *(void**)(base + 0x4c) = 0;                 // local_620
    *(int*) (base + 0x50) = 0;                  // local_61c
    *(int*) (base + 0x54) = 0;                  // local_618

    if (strstr_s009c_cfe0(local_610, "group blocks") == 0) {
        void* parser = EA_ArgScript_CreateParser();
        if (parser != 0)
            (*(void(__cdecl**)(void*))(*(char**)parser))(parser);
        (*(void(__cdecl**)(void*))(*(char**)parser + 8))(parser);
        (*(void(__cdecl**)(void*, void*))(*(char**)parser + 0x10))(parser, base + 0x0c);
        (*(void(__cdecl**)(void*, int, int))(*(char**)parser + 0x28))(parser, 4, 5);

        void* cmd;
        cmd = EAAllocate(0x10, "Anim/crncmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_crncmd; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fe4, cmd);

        cmd = EAAllocate(0x10, "Anim/isplantcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_isplant; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fec, cmd);

        cmd = EAAllocate(0x10, "Anim/calrtblkicmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_calrtblki; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fcc, cmd);

        cmd = EAAllocate(0x10, "Anim/numblkcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_numblk; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550ff0, cmd);

        cmd = EAAllocate(0x34, "Anim/blkblkcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_AppPropsFields_ctor(cmd); *(void**)cmd = g_vtbl_blkblk; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fc4, cmd);

        (*(void(__cdecl**)(void*))(*(char**)parser + 0x30))(parser);
        char ok = (*(char(__cdecl**)(void*, void*))(*(char**)parser + 0x48))(parser, local_674);
        local_679 = ok;
        if (ok == 0) {
            char* msg = (*(char*(__cdecl**)(void*))(*(char**)parser + 0x58))(parser);
            sprintf(acStack_438, "error occurred: '%s'\n", msg);
            fprintf((char*)__iob_func() + 0x40, "%s", acStack_438);
        }
        (*(void(__cdecl**)(void*, int))(*(char**)parser + 0x34))(parser, ok == 0);
        (*(void(__cdecl**)(void*))(*(char**)parser + 0xc))(parser);
        if (parser != 0)
            (*(void(__cdecl**)(void*))(*(char**)parser + 4))(parser);

        int bodyBytes = (int)((char*)param_1->bodies_end - (char*)param_1->bodies_begin);
        int n = bodyBytes / 0x468;
        if (n != 0) {
            int off = 0;
            do {
                int* p = (int*)((char*)param_1->bodies_begin + off + 0x200);
                if (*p != -2 && *p != -1) {
                    unsigned long* r = ((ulong_map*)base)->get((unsigned long*)p);
                    *p = (int)*r;
                }
                off += 0x468;
            } while (--n != 0);
            ok = 0;
            local_679 = ok;
        }
        if (ok != 0) {
            int bodyBytes2 = (int)((char*)param_1->bodies_end - (char*)param_1->bodies_begin);
            int n2 = bodyBytes2 / 0x468;
            if (n2 != 0) {
                int off2 = 0;
                do {
                    FUN_009b3010((char*)param_1->bodies_begin + off2 + 0x150);
                    if ((*(unsigned char*)((char*)param_1->bodies_begin + off2 + 0x154) & 4) != 0)
                        ++param_1->count_3c8;
                    off2 += 0x468;
                } while (--n2 != 0);
            }
            if (param_1->count_3c8 == 0 && param_1->flag_3f0 == 0)
                FUN_009cbdb0((char*)param_1);
            local_679 = (char)nSPCreatureAnim_FinalizeCreature(param_1);
        }
    }
    {
        void* node = local_620;
        while (node != 0) {
            map_node_free(node, (void*)base);
            void* next = *(void**)((char*)node + 4);
            operator_delete(node);
            node = next;
        }
    }
    return local_679;
}
