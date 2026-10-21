// Slice s00a83c00 -- EA::Swarm::cVisualEffect (ctor, IsRunning, params setters),
// the cComponentBase destructor, the cIComponent-subobject Shutdown, cEffectParams
// FloatStore/IntStore and the cVisualEffectDescription / cDescriptionRec IO helpers.
//
// Retail cVisualEffect layout = dev PDB layout minus the 0x10-byte
// mEffectID/mDescID/mStartTransition block (so everything from mDesc on is -0x10):
//   0x00/0x04/0x08 vptrs, 0x0c ?, 0x10 mRefCount, 0x14 mName(0x10), 0x24 mSimTime,
//   0x28 mDesc, 0x2c mFlags, 0x30 mWorldPosition, 0x3c mWorldUp, 0x48 mCurrentLOD,
//   0x4c mCurrentLODLerp, 0x50 mCurrentRange, 0x58 mLODDistanceScale,
//   0x5c mNotifyMessageID, 0x60 mNotifyMessageUserData, 0x64/0x9c/0xd4/0x10c the four
//   cTransforms, 0x144 mComponentRecs(0x14), 0x158 mRigidBone, 0x15c mod, 0x160 mSourceBone,
//   0x164 mod, 0x168 mLODSizeScale, 0x170 mSizeScaleLOD, 0x174 mWorld, 0x178 mGlobalParams,
//   0x17c mParams, 0x180 mSeed.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned int u32;

// ---------------------------------------------------------------- constant data
extern const float DAT_01677a2c, DAT_01677a30, DAT_01677a34;   // zero vector
extern const float DAT_01677a04, DAT_01677a08, DAT_01677a0c;   // "up" reference vector
extern const float DAT_016779fc, DAT_01677a00;                 // default range
extern const float DAT_01485720;                               // 1.0f
extern const float DAT_013eb1bc;                               // size scale default

struct Matrix3;
extern const Matrix3 DAT_01677ad8;                             // identity 3x3

// vtable address symbols (values masked by the byte matcher)
extern char g_vtbl_0x1457e50[];
extern char g_vtbl_0x1457e14[];
extern char g_vtbl_0x1457e10[];
extern char g_vtbl_0x13ef094[];
extern char g_vtbl_0x13f21d4[];
extern char g_vtbl_0x13f2194[];

// ---------------------------------------------------------------- Swarm types
struct Matrix3 {
    float m[9];
    Matrix3& operator=(const Matrix3& o);                      // 0x0041cb40
};

// eastl::vector<T, sp_vector_allocator>: 0x14 bytes
template <class T> struct SpVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAlloc[2];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void resize(int n);                                        // 0x004afc80 / 0x004cd3c0
};

struct cTransform {                                            // 0x38
    uint16_t mFlags;                                           // +0x00
    uint16_t mModCount;                                        // +0x02
    float    mOffset[3];                                       // +0x04
    float    mScale;                                           // +0x10
    float    mRotation[9];                                     // +0x14
};

struct cParamRec { uint16_t mOffset, mCount; };

struct cEffectParams {                                         // retail size 0xd8
    cParamRec mFloatParams[25];                                // +0x00
    SpVector<float> mFloatParamStorage;                        // +0x64
    cParamRec mIntParams[10];                                  // +0x78
    SpVector<int> mIntParamStorage;                            // +0xa0
    uint32_t  mUnknown[9];                                     // +0xb4

    cEffectParams();                                           // 0x007d55e0
    ~cEffectParams();                                          // 0x007d4ae0
    bool FloatStore(int index, const float* data, int count);  // 0x00a83fd0
    bool IntStore(int index, const int* data, int count);      // 0x00a84040
};

struct cComponentRec {                                         // 0x5c
    cTransform mLocalXform;                                    // +0x00
    void*      mComponent;                                     // +0x38
    uint32_t   mDescRecIndex;                                  // +0x3c
    float      mTimeScale;                                     // +0x40
    uint32_t   mFlags;                                         // +0x44
    uint32_t   mStateDescIndices[5];                           // +0x48
};

// cIComponent vtable: slot 7 = SetFloatParams (+0x1c), slot 8 = SetIntParams (+0x20)
struct cIComponent {
    virtual void Init(void*, void*, void*);
    virtual void Shutdown();
    virtual void Start(int);
    virtual void Stop(int);
    virtual bool IsRunning();
    virtual void ApplyEffect(float, float, void*);
    virtual void SetTransforms(const cTransform&, const cTransform&);
    virtual bool SetFloatParams(u32, const float*, int);       // +0x1c
    virtual bool SetIntParams(u32, const int*, int);           // +0x20
};

struct cVisualEffectDescription;                               // 0x58
struct cDescriptionRec;                                        // 0x84

// ---------------------------------------------------------------- IO + helpers
struct IOStream;

bool WriteUint32(IOStream* s, const void* p, uint32_t n, int endian);     // 0x0093aa70
bool WriteUint16(IOStream* s, const void* p, uint32_t n, int endian);     // 0x0093a9d0
bool StreamWrite(IOStream* s, const void* p, uint32_t n);                 // 0x0093a9a0
bool ReadInt32(IOStream* s, void* p, uint32_t n, int endian);             // 0x0093a780
bool ReadUint16(IOStream* s, void* p, uint32_t n, int endian);            // 0x0093a700
bool ReadUint8(IOStream* s, void* p, uint32_t n);                         // 0x0093a6c0

inline bool WriteV32(IOStream* s, uint32_t v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteV32(IOStream* s, int v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteF32(IOStream* s, float v) { return WriteUint32(s, &v, 1, 0); }
inline bool WriteV16(IOStream* s, uint16_t v) { return WriteUint16(s, &v, 1, 0); }
inline bool WriteBool(IOStream* s, bool v) { return StreamWrite(s, &v, 1); }

void  FUN_007d01f0(IOStream* s, void* v);                      // 0x007d01f0
void  FUN_007d0250(IOStream* s, void* v);                      // 0x007d0250

void* EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* FUN_011e0744(void* dst, const void* src, size_t n);       // memcpy thunk (0x11e0744)
void* EAAllocate(uint32_t size, const char* name, int a, int b,
                 const char* file, int line);                  // same, EASTL allocator form
void  operator delete(void* p);                                // 0x00f47380
void* operator new(size_t size, const char* name, int a, int b, int c, int d);
inline void* operator new(size_t, void* p) { return p; }
inline void  operator delete(void*, void*) {}

// thiscall target modelled as a member of a throwaway class so the compiler emits
// "push end; push begin; mov ecx,this; call" with no extra register setup.
struct Destr40980 { void __thiscall call(void* begin, void* end); };   // 0xa70980
struct ResizableVec { void __thiscall resize(int n); };                 // 0xa6f010
#define FUN_00a70980(v, b, e) (((Destr40980*)(v))->call((b), (e)))
void* FUN_00a71260(void* a, void* b, void* c);
void  FUN_00a6a2f0(void* dst, const void* src);
void  FUN_00a6a9c0(void* dst, void* a, void* b, void* c, void* d);
void  FUN_00a6eab0(void* a, void* b, void* c);
void* FUN_00a6e9a0(void* a, void* b, void* c);
void  FUN_00a6e460(void* a, void* b, void* c);
void  FUN_00a847f0(void* dst, u32 n, const void* src);
void  FUN_00a84820(void* a, void* b, void* c);
void  FUN_00a82500(void* self, int v);                         // SelectDescriptionState
void  FUN_00a82a10(void* self, const void* v);                 // ApplyCursorControl

// forward declarations for intra-slice calls
void* WriteTransform(IOStream* s, void* v);                    // 0x00a84460
void  WriteRec(IOStream* s, void* v);                          // 0x00a84510
void* WriteRecList(IOStream* s, void* v);                      // 0x00a846c0
void* WriteDescRec(IOStream* s, void* v);                      // 0x00a84720
void* ReadLODScales(IOStream* s, void* v);                     // 0x00a84850
void* ReadDescRec(IOStream* s, void* v);                       // 0x00a848d0
void  ResizeDescRecs(void* self, u32 n, const void* val, void* out); // 0x00a84a80

struct cVisualEffect {                                         // 0x188
    char raw[0x188];
    cVisualEffect* Construct();                                // 0x00a83c00
    int  IsRunning() const;                                    // 0x00a83ee0
    char SetFloatParams(u32 type, const float* data, int count);// 0x00a840c0
    char SetIntParams(u32 type, const int* data, int count);   // 0x00a84200
};

// cComponentBase subobject of cVisualEffect (this = cVisualEffect + 4)
struct cComponentBaseSub {
    char raw[0x184];
    void Destruct();                                           // 0x00a83f40
    void Shutdown();                                           // 0x00a84330
};

// ================================================================ ctor
// @ 0x00a83c00  EA::Swarm::cVisualEffect::cVisualEffect
cVisualEffect* cVisualEffect::Construct() {
    char* p = (char*)this;
    *(void**)(p + 0x08) = g_vtbl_0x13ef094;
    *(void**)(p + 0x0c) = 0;
    *(void**)(p + 0x04) = g_vtbl_0x13f21d4;
    *(void**)(p + 0x08) = g_vtbl_0x13f2194;
    *(void**)(p + 0x00) = g_vtbl_0x1457e50;
    *(void**)(p + 0x04) = g_vtbl_0x1457e14;
    *(void**)(p + 0x08) = g_vtbl_0x1457e10;
    *(int*)(p + 0x10) = 0;
    *(float*)(p + 0x24) = 0.0f;
    *(void**)(p + 0x28) = 0;
    *(uint32_t*)(p + 0x18) = 0xffffffffu;
    *(uint32_t*)(p + 0x1c) = 0xffffffffu;
    *(uint32_t*)(p + 0x20) = 0xffffffffu;
    *(uint32_t*)(p + 0x2c) = 0;
    *(float*)(p + 0x30) = DAT_01677a2c;
    *(float*)(p + 0x34) = DAT_01677a30;
    *(float*)(p + 0x38) = DAT_01677a34;
    *(float*)(p + 0x3c) = DAT_01677a04;
    *(float*)(p + 0x40) = DAT_01677a08;
    *(float*)(p + 0x44) = DAT_01677a0c;
    *(float*)(p + 0x4c) = 0.0f;
    *(uint32_t*)(p + 0x48) = 0;
    *(float*)(p + 0x50) = DAT_016779fc;
    *(float*)(p + 0x54) = DAT_01677a00;
    *(float*)(p + 0x58) = DAT_01485720;
    *(uint32_t*)(p + 0x5c) = 0;
    *(uint32_t*)(p + 0x60) = 0;

    *(uint16_t*)(p + 0x66) = 0;
    *(uint16_t*)(p + 0x64) = 0;
    *(float*)(p + 0x68) = DAT_01677a2c;
    *(float*)(p + 0x6c) = DAT_01677a30;
    *(float*)(p + 0x70) = DAT_01677a34;
    *(float*)(p + 0x74) = DAT_01485720;
    ((Matrix3*)(p + 0x78))->operator=(DAT_01677ad8);

    *(uint32_t*)(p + 0x9c) = 0;
    *(float*)(p + 0xa0) = DAT_01677a2c;
    *(float*)(p + 0xa4) = DAT_01677a30;
    *(float*)(p + 0xa8) = DAT_01677a34;
    *(float*)(p + 0xac) = DAT_01485720;
    ((Matrix3*)(p + 0xb0))->operator=(DAT_01677ad8);

    *(uint32_t*)(p + 0xd4) = 0;
    *(float*)(p + 0xd8) = DAT_01677a2c;
    *(float*)(p + 0xdc) = DAT_01677a30;
    *(float*)(p + 0xe0) = DAT_01677a34;
    *(float*)(p + 0xe4) = DAT_01485720;
    ((Matrix3*)(p + 0xe8))->operator=(DAT_01677ad8);

    *(uint32_t*)(p + 0x10c) = 0;
    *(float*)(p + 0x110) = DAT_01677a2c;
    *(float*)(p + 0x114) = DAT_01677a30;
    *(float*)(p + 0x118) = DAT_01677a34;
    *(float*)(p + 0x11c) = DAT_01485720;
    ((Matrix3*)(p + 0x120))->operator=(DAT_01677ad8);

    float s = DAT_013eb1bc;
    *(uint32_t*)(p + 0x144) = 0;
    *(uint32_t*)(p + 0x148) = 0;
    *(uint32_t*)(p + 0x14c) = 0;
    *(uint32_t*)(p + 0x158) = 0;
    *(uint32_t*)(p + 0x15c) = 0;
    *(uint32_t*)(p + 0x160) = 0;
    *(uint32_t*)(p + 0x164) = 0;
    *(float*)(p + 0x168) = s;
    *(float*)(p + 0x16c) = s;
    *(uint32_t*)(p + 0x174) = 0;
    *(uint32_t*)(p + 0x178) = 0;
    *(uint32_t*)(p + 0x17c) = 0;
    *(uint32_t*)(p + 0x180) = 0;
    *(float*)(p + 0x170) = s;
    return this;
}

// @ 0x00a83ee0  EA::Swarm::cVisualEffect::IsRunning
int cVisualEffect::IsRunning() const {
    u32 f = *(const u32*)((const char*)this + 0x2c);
    if (((f >> 9) & 1) == 0) {
        if (((f >> 13) & 1) == 0)
            return 0;
    }
    return 1;
}

// helpers for raw virtual calls on unknown ("void*") sub-objects
typedef void (__thiscall *VtblFn)(void*);
static inline void CallVtbl1(void* obj) { ((VtblFn*)(*(void***)obj))[1](obj); }
static inline void CallVtbl2(void* obj) { ((VtblFn*)(*(void***)obj))[2](obj); }
typedef void (__thiscall *VtblFnI)(void*, int);
static inline void CallVtbl3(void* obj, int a) { ((VtblFnI*)(*(void***)obj))[3](obj, a); }

// @ 0x00a83f40  EA::Swarm::cComponentBase::~cComponentBase (this = object+4)
void cComponentBaseSub::Destruct() {
    char* p = (char*)this;
    if (*(void**)(p + 0x160))
        CallVtbl2(*(void**)(p + 0x160));
    if (*(void**)(p + 0x158))
        CallVtbl2(*(void**)(p + 0x158));
    char* vec = p + 0x144;
    FUN_00a70980(vec, *(void**)vec, *(void**)(vec + 4));
    char* begin = *(char**)vec;
    if (begin && ((int*)begin)[-1] != 0) operator delete(begin);
    *(void**)(p + 0x04) = g_vtbl_0x13f21d4;
    *(void**)(p + 0x08) = g_vtbl_0x13ef094;
}

// @ 0x00a83fd0  EA::Swarm::cEffectParams::FloatStore
bool cEffectParams::FloatStore(int index, const float* data, int count) {
    int n = mFloatParams[index].mCount;
    if (n == 0) {
        int off = (int)((char*)mFloatParamStorage.mpEnd - (char*)mFloatParamStorage.mpBegin) >> 2;
        mFloatParams[index].mOffset = (uint16_t)off;
        mFloatParams[index].mCount = (uint16_t)count;
        mFloatParamStorage.resize(off + count);
    } else if (count != n) {
        return false;
    }
    FUN_011e0744(mFloatParamStorage.mpBegin + mFloatParams[index].mOffset, data, count * 4);
    return true;
}

// @ 0x00a84040  EA::Swarm::cEffectParams::IntStore
bool cEffectParams::IntStore(int index, const int* data, int count) {
    int n = mIntParams[index + 1].mCount;
    if (n == 0) {
        int off = (int)((char*)mIntParamStorage.mpEnd - (char*)mIntParamStorage.mpBegin) >> 2;
        mIntParams[index + 1].mOffset = (uint16_t)off;
        mIntParams[index + 1].mCount = (uint16_t)count;
        mIntParamStorage.resize(off + count);
    } else if (count != n) {
        return false;
    }
    FUN_011e0744(mIntParamStorage.mpBegin + mIntParams[index + 1].mOffset, data, count * 4);
    return true;
}

// @ 0x00a840c0  EA::Swarm::cVisualEffect::SetFloatParams
char cVisualEffect::SetFloatParams(u32 type, const float* data, int count) {
    char* p = (char*)this;
    if (*(void**)(p + 0x174) == 0) return 0;
    void** desc = *(void***)(p + 0x28);
    if (desc != 0 && ((*(const u32*)desc >> 7) & 1)) return 0;
    if (count < 1) return 0;
    if (type > 0x19) {
        if (type == 0x101) {
            *(float*)(p + 0x168) = data[1];
            *(float*)(p + 0x16c) = data[4];
        }
        return 0;
    }
    if (*(void**)(p + 0x17c) == 0) {
        void* mem = EAAllocate(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        if (mem) { new (mem) cEffectParams(); }
        *(void**)(p + 0x17c) = mem;
    }
    if (!((cEffectParams*)*(void**)(p + 0x17c))->FloatStore((int)type, data, count)) return 0;
    if (type == 0xb) {
        if ((*(const u32*)(p + 0x2c) >> 13) & 1) FUN_00a82a10(p, data);
    } else if (type == 0x13) {
        *(float*)(p + 0x58) = *data;
    }
    cComponentRec* rec = *(cComponentRec**)(p + 0x144);
    char changed = 0;
    if (rec != *(cComponentRec**)(p + 0x148)) {
        do {
            if (((rec->mFlags >> 5) & 1) == 0) {
                char r = ((cIComponent*)rec->mComponent)->SetFloatParams(type, data, count);
                if (r || changed) changed = 1;
            }
            rec = (cComponentRec*)((char*)rec + 0x5c);
        } while (rec != *(cComponentRec**)(p + 0x148));
    }
    return changed;
}

// @ 0x00a84200  EA::Swarm::cVisualEffect::SetIntParams
char cVisualEffect::SetIntParams(u32 type, const int* data, int count) {
    char* p = (char*)this;
    if (*(void**)(p + 0x174) == 0) return 0;
    void** desc = *(void***)(p + 0x28);
    if (desc != 0 && ((*(const u32*)desc >> 7) & 1)) return 0;
    if (count < 1) return 0;
    if (type > 0xa) return 0;
    if (*(void**)(p + 0x17c) == 0) {
        void* mem = EAAllocate(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        if (mem) { new (mem) cEffectParams(); }
        *(void**)(p + 0x17c) = mem;
    }
    if (!((cEffectParams*)*(void**)(p + 0x17c))->IntStore((int)type, data, count)) return 0;
    if (type == 3) FUN_00a82500(p, data[0]);
    cComponentRec* rec = *(cComponentRec**)(p + 0x144);
    char changed = 0;
    if (rec != *(cComponentRec**)(p + 0x148)) {
        do {
            if (((rec->mFlags >> 5) & 1) == 0) {
                char r = ((cIComponent*)rec->mComponent)->SetIntParams(type, data, count);
                if (r || changed) changed = 1;
            }
            rec = (cComponentRec*)((char*)rec + 0x5c);
        } while (rec != *(cComponentRec**)(p + 0x148));
    }
    return changed;
}

// @ 0x00a84330  EA::Swarm::cVisualEffect::Shutdown (this = object+4)
void cComponentBaseSub::Shutdown() {
    char* p = (char*)this;
    if ((*(const u32*)(p + 0x28) >> 9) & 1) {
        CallVtbl3(*(void**)(p - 4), 1);
    }
    void* params = *(void**)(p + 0x178);
    *(uint32_t*)(p + 0x170) = 0;
    *(uint32_t*)(p + 0x174) = 0;
    if (params != 0) {
        ((cEffectParams*)params)->~cEffectParams();            // 0x007d4ae0
        operator delete(params);
        *(uint32_t*)(p + 0x178) = 0;
    }
    *(uint32_t*)(p + 0x24) = 0;
    void* a = *(void**)(p + 0x154);
    if (a != 0) { *(uint32_t*)(p + 0x154) = 0; CallVtbl2(a); }
    void* b = *(void**)(p + 0x15c);
    if (b != 0) { *(uint32_t*)(p + 0x15c) = 0; CallVtbl2(b); }
    *(uint32_t*)(p + 0x14) = 0xffffffffu;
    *(uint32_t*)(p + 0x18) = 0xffffffffu;
    *(uint32_t*)(p + 0x1c) = 0xffffffffu;
    *(uint32_t*)(p + 0x28) &= ~0x800u;
    char* vec = p + 0x140;
    char* begin = *(char**)vec;
    char* end = *(char**)(vec + 4);
    for (char* rec = begin; rec < end; rec += 0x5c) {
        void* c = *(void**)(rec + 0x38);
        if (c != 0) CallVtbl1(c);
    }
    void* t = FUN_00a71260(end, end, begin);
    FUN_00a70980(vec, t, end);
    *(char**)(vec + 4) += (end - begin) * 0x9c / 0x5c - (end - begin);
}

// ================================================================ IO writers
// @ 0x00a84460  write a 0xc-stride array (3 floats each) from a {begin,end} range
void* WriteTransform(IOStream* s, void* v) {
    char* range = (char*)v;
    uint32_t n = (uint32_t)((*(char**)(range + 4) - *(char**)range) / 0xc);
    WriteV32(s, n);
    for (uint32_t i = 0; i < n; ++i) {
        char* e = *(char**)range + i * 0xc;
        WriteF32(s, ((float*)e)[0]);
        WriteF32(s, ((float*)e)[1]);
        WriteF32(s, ((float*)e)[2]);
    }
    return s;
}

// @ 0x00a84510  write one cDescriptionRec (0x84)
void WriteRec(IOStream* s, void* v) {
    char* p = (char*)v;
    WriteBool(s, *(bool*)p);                                   // mCmptType
    WriteV32(s, *(const uint32_t*)(p + 4));                    // mFlags (16:16)
    FUN_007d01f0(s, p + 8);                                    // mLocalXform
    WriteBool(s, *(bool*)(p + 0x40));                          // mLODBegin
    WriteBool(s, *(bool*)(p + 0x41));                          // mLODEnd
    WriteTransform(s, p + 0x44);                               // mLODScales
    WriteF32(s, *(float*)(p + 0x58));                          // mEmitScaleBegin
    WriteF32(s, *(float*)(p + 0x5c));                          // mEmitScaleEnd
    WriteF32(s, *(float*)(p + 0x60));                          // mMassScaleBegin
    WriteF32(s, *(float*)(p + 0x64));                          // mMassScaleEnd
    WriteF32(s, *(float*)(p + 0x68));                          // mSizeScaleBegin
    WriteF32(s, *(float*)(p + 0x6c));                          // mSizeScaleEnd
    WriteV32(s, *(const uint32_t*)(p + 0x70));                 // mAppFlags
    WriteV32(s, *(const uint32_t*)(p + 0x74));                 // mAppFlagsMask
    WriteV16(s, *(uint16_t*)(p + 0x78));                       // mSelectionGroup
    WriteV16(s, *(uint16_t*)(p + 0x7a));                       // mSelectionChance
    WriteF32(s, *(float*)(p + 0x7c));                          // mTimeScale
    WriteV32(s, *(const uint32_t*)(p + 0x80));                 // mDescIndex
}

// @ 0x00a846c0  write a vector of cDescriptionRec
void* WriteRecList(IOStream* s, void* v) {
    char* range = (char*)v;
    uint32_t n = (uint32_t)((*(char**)(range + 4) - *(char**)range) / 0x84);
    WriteV32(s, n);
    for (uint32_t i = 0; i < n; ++i)
        WriteRec(s, *(char**)range + i * 0x84);
    return s;
}

// stream "write raw bytes" virtual, slot +0x38
struct StreamW { virtual void v0();virtual void v1();virtual void v2();virtual void v3();
    virtual void v4();virtual void v5();virtual void v6();virtual void v7();
    virtual void v8();virtual void v9();virtual void v10();virtual void v11();
    virtual void v12();virtual void v13();virtual void write(const void* data, int size); };
// stream "read raw bytes" virtual, slot +0x30
struct StreamR { virtual void v0();virtual void v1();virtual void v2();virtual void v3();
    virtual void v4();virtual void v5();virtual void v6();virtual void v7();
    virtual void v8();virtual void v9();virtual void v10();virtual void v11();
    virtual void read(void* data, int size); };

// @ 0x00a84720  write one cVisualEffectDescription (0x58)
void* WriteDescRec(IOStream* s, void* v) {
    char* p = (char*)v;
    WriteV32(s, *(const uint32_t*)(p + 0x00));
    WriteV32(s, *(const uint32_t*)(p + 0x04));
    WriteV32(s, *(const uint32_t*)(p + 0x08));
    ((StreamW*)s)->write(p + 0x0c, 8);
    WriteF32(s, *(float*)(p + 0x14));
    WriteBool(s, *(bool*)(p + 0x18));
    FUN_007d0250(s, p + 0x1c);
    ((StreamW*)s)->write(p + 0x30, 0xc);
    WriteV32(s, *(const uint32_t*)(p + 0x40));
    return WriteRecList(s, p + 0x44);
}

// ================================================================ IO readers
// @ 0x00a84850  read a vector of 3-int LOD scales (0xc stride)
void* ReadLODScales(IOStream* s, void* v) {
    uint32_t n = 0;
    ReadInt32(s, &n, 1, 0);
    ((ResizableVec*)v)->resize((int)n);                        // 0x00a6f010
    for (uint32_t i = 0; i < n; ++i) {
        char* e = *(char**)v + i * 0xc;
        ReadInt32(s, e, 1, 0);
        ReadInt32(s, e + 4, 1, 0);
        ReadInt32(s, e + 8, 1, 0);
    }
    return s;
}

// @ 0x00a848d0  read one cDescriptionRec
void* ReadDescRec(IOStream* s, void* v) {
    char* p = (char*)v;
    char* q = p + 8;                                           // cached base (ebx)
    uint8_t b;
    ReadUint8(s, &b, 1);
    *(uint32_t*)p = b & 0xff;
    u32 w;
    ReadInt32(s, &w, 1, 0);
    *(uint32_t*)(p + 4) = w & 0x1ff;
    ReadUint16(s, q, 1, 0);
    ReadInt32(s, q + 0x10, 1, 0);
    ((StreamR*)s)->read(q + 0x14, 0x24);
    ((StreamR*)s)->read(q + 4, 0xc);
    ReadUint8(s, p + 0x40, 1);
    ReadUint8(s, p + 0x41, 1);
    ReadLODScales(s, p + 0x44);
    ReadInt32(s, p + 0x58, 1, 0);
    ReadInt32(s, p + 0x5c, 1, 0);
    ReadInt32(s, p + 0x60, 1, 0);
    ReadInt32(s, p + 0x64, 1, 0);
    ReadInt32(s, p + 0x68, 1, 0);
    ReadInt32(s, p + 0x6c, 1, 0);
    ReadInt32(s, p + 0x70, 1, 0);
    ReadInt32(s, p + 0x74, 1, 0);
    ReadUint16(s, p + 0x78, 1, 0);
    ReadUint16(s, p + 0x7a, 1, 0);
    ReadInt32(s, p + 0x7c, 1, 0);
    ReadInt32(s, p + 0x80, 1, 0);
    return s;
}

// @ 0x00a84a80  grow/insert into a vector of 0x84-byte elements
void ResizeDescRecs(void* self, u32 n, const void* val, void* out) {
    char* v = (char*)self;
    u32 cap = (u32)((*(char**)(v + 8) - *(char**)(v + 4)) / 0x84);
    if (cap < n) {
        char* begin = *(char**)v;
        char* end = *(char**)(v + 4);
        u32 have = (u32)((end - begin) / 0x84);
        u32 want = have * 2;
        if (want == 0) want = 1;
        u32 total = have + n;
        if (total > want) want = total;
        char* mem = want ? (char*)EAAllocate(want * 0x84, "EASTL", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                        : 0;
        void* first = (void*)FUN_00a6e9a0(begin, (void*)val, mem);
        FUN_00a6e460(begin, (void*)val, mem);
        FUN_00a847f0(first, n, val);
        void* mid = (void*)FUN_00a6e9a0((void*)val, end, (char*)first + n * 0x84);
        FUN_00a6e460((void*)val, end, (char*)first + n * 0x84);
        if (begin && ((int*)begin)[-1] != 0) operator delete(begin);
        *(char**)v = mem;
        *(char**)(v + 4) = (char*)mid;
        *(char**)(v + 8) = mem + want * 0x84;
        return;
    }
    if (n != 0) {
        FUN_00a6a2f0(out, val);
        char* end = *(char**)(v + 4);
        u32 have = (u32)((end - (char*)val) / 0x84);
        char* inserted;
        if (n < have) {
            char* last = end - n * 0x84;
            FUN_00a6a9c0(out, last, end, end, out);
            *(char**)(v + 4) += n * 0x84;
            FUN_00a6eab0((void*)val, last, end);
            inserted = (char*)val + n * 0x84;
        } else {
            FUN_00a847f0(end, n - have, out);
            *(char**)(v + 4) += (n - have) * 0x84;
            FUN_00a6a9c0(out, (void*)val, end, *(char**)(v + 4), out);
            *(char**)(v + 4) += have * 0x84;
            inserted = end;
        }
        FUN_00a84820((void*)val, inserted, out);
    }
}
