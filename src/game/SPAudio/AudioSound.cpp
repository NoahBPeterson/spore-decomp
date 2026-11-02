// src/game/SPAudio/AudioSound.cpp -- migrated from slice(s) s00a1f2b0, s00a1d400, s00a1b480, s00a1a590, s00a36d60, s00a20060, s00a1e320, s00a1c460 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioSound.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IEmitter.h"
#include "EA/Audio/ISystem.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include <math.h>
#include <string.h>
#include "EA/Thread/Mutex.h"
#include "EA/Audio/Playlist.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/Audio/cEAPDVoiceManager.h"
#include "EA/Audio/Envelope.h"
#include "EA/Audio/ResourceInstrumentBank.h"
#include "EA/Audio/IMixable.h"
#include <ctype.h>
#include <new>
#include <intrin.h>
#include <xmmintrin.h>

// ---- items of slice s00a1c460 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
template<int N> inline void ScratchSlots() { u32 s[N]; }
void* operator_new(void* alloc, const char* name, int flags, int align, const char* file, int line);
struct CurveData {
    void SetFrom(void* arg, int zero);   // 0x00a1aad0 (thiscall)
};
struct BasicString {
    void assign(void* v);  // 0x006a4380
};
inline const float& FMin(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& FMax(const float& a, const float& b) { return (a < b) ? b : a; }
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    float LengthSq() const { return x * x + y * y + z * z; }
};
struct IPrim {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual float GetValue(int);              // +0x1c
    virtual bool v20(int);                    // +0x20
    virtual void v24();
    virtual void SetValue(float, int);        // +0x28
    virtual void SetEnabled(bool);            // +0x2c
};
template <class T> struct ARC {
    T* p;
    ARC() : p(0) {}
    ~ARC() { if (p) p->Release(); }
    void Reset() { if (p) { T* o = p; p = 0; o->Release(); } }
    ARC& operator=(T* o) {
        if (o != p) {
            T* old = p;
            if (o) o->AddRef();
            p = o;
            if (old) old->Release();
        }
        return *this;
    }
};
struct IEmitter {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18();
    virtual void SetFlag(int);                              // +0x1c
    virtual bool e20(int);                                  // +0x20
    virtual void e24(); virtual void e28();
    virtual void SetProperty(u32 key, float v, int one);    // +0x2c
    virtual bool GetProperty(u32 key, float* out);          // +0x30
    virtual void SetData(u32 key, void* data, u32 size);    // +0x34
};
struct PropNode { u32 key; float value; PropNode* next; };
struct PrimNode { u32 key; IPrim* prim; PrimNode* next; };
template <class N> struct HMap {
    N** mpBuckets;
    u32 mBucketCount;
    struct Iter {
        N* mpNode;
        N** mpBucket;
        void inc() {
            mpNode = mpNode->next;
            while (!mpNode)
                mpNode = *++mpBucket;
        }
    };
    Iter begin() {
        Iter it;
        it.mpBucket = mpBuckets;
        it.mpNode = *mpBuckets;
        if (!it.mpNode) {
            ++it.mpBucket;
            while (*it.mpBucket == 0)
                ++it.mpBucket;
            it.mpNode = *it.mpBucket;
        }
        return it;
    }
    N* end() { return mpBuckets[mBucketCount]; }
};
struct ConfigObj {
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24(); virtual void c28(); virtual void c2c();
    virtual void c30(); virtual void c34(); virtual void c38(); virtual void c3c();
    virtual void c40();
    virtual bool GetData(u32 key, int* size, void** data);       // +0x44
    virtual bool GetArray(u32 key, u32* count, u32** arr);       // +0x48
    u8 pad[0x10];
};
struct ISoundMix {                                       // second base at +4
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual void SetProp(u32 key, float v, int one);     // +0x0c
    virtual bool GetProp(u32 key, float* out);           // +0x10
    virtual void m14();
    virtual bool AddPrimitive(u32 key, IPrim* p);        // +0x18
};
struct RCurve {
    u8 mData[0x364];
    float GetOutputValue(float in);                      // 0xa1a110
};
struct LerpF { float Get(); };                           // 0xa1b020 (thiscall, returns float)
struct ISystem {
    virtual void s00();
    virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24(); virtual void s28();
    virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
    virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60(); virtual void s64();
    virtual void s68(); virtual void s6c(); virtual void s70(); virtual void s74(); virtual void s78();
    virtual Vec3* GetPosition(u32 handle);               // +0x7c
    virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c(); virtual void s90();
    virtual void s94(); virtual void s98(); virtual void s9c(); virtual void sa0(); virtual void sa4();
    virtual void sa8(); virtual void sac(); virtual void sb0(); virtual void sb4(); virtual void sb8();
    virtual void sbc(); virtual void sc0(); virtual void sc4(); virtual void sc8(); virtual void scc();
    virtual void sd0(); virtual void sd4(); virtual void sd8(); virtual void sdc(); virtual void se0();
    virtual bool GetPrimitive(u32 key, void* outArc);    // +0xe4
    virtual void se8(); virtual void sec(); virtual void sf0(); virtual void sf4(); virtual void sf8();
    virtual void sfc(); virtual void s100(); virtual void s104(); virtual void s108(); virtual void s10c();
    virtual void s110(); virtual void s114(); virtual void s118(); virtual void s11c(); virtual void s120();
    virtual void s124(); virtual void s128(); virtual void s12c(); virtual void s130(); virtual void s134();
    virtual void s138(); virtual void s13c(); virtual void s140(); virtual void s144(); virtual void s148();
    virtual void s14c(); virtual void s150(); virtual void s154(); virtual void s158(); virtual void s15c();
    virtual void s160(); virtual void s164(); virtual void s168(); virtual void s16c(); virtual void s170();
    virtual void s174(); virtual void s178(); virtual void s17c(); virtual void s180(); virtual void s184();
    virtual void s188(); virtual void s18c(); virtual void s190(); virtual void s194(); virtual void s198();
    virtual void s19c(); virtual void s1a0(); virtual void s1a4();
    virtual float GetSpeed(Vec3* pos);                   // +0x1a8
};
ISystem* GetSystemAT();                                  // 0x00a206f0 EA::Audio::GetSystemAT
struct PRespObj : IPrim {
    PRespObj(void* owner);
    void SetCurveData(void* data, int n);                // 0xa171c0 -> SetResponseCurveData(+0xc)
    void SetModSource(IPrim* src);                       // 0xa37080
    static void* operator new(size_t);                   // 0xa171e0 (fixed pool alloc)
    static void  operator delete(void*);
    u8 pad[0x38c - 4];
};
struct SoundV {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void Stop(int, int, float, int);
    virtual bool Query(int, int);
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c(float);
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78(bool);
    virtual void v7c();
    virtual void v80(int, int);
    virtual void v84();
    virtual bool v88(float);
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void SetPropValue(u32 key, float v);
    virtual void v9c();
    virtual void va0(void*);
    virtual void va4(void*);
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4(u32, u32, IPrim*);
};
struct Sound : SoundV, ISoundMix {
    u8   pad0[0x44 - 8];
    IEmitter* mpEmitter;      // +0x44
    float mDist;              // +0x48
    u8   pad1[0x54 - 0x4c];
    float mMaxDistance;       // +0x54
    float mGain;              // +0x58
    u8   pad2[0x60 - 0x5c];
    float mMaxGainChange;     // +0x60
    float mAttenGain;         // +0x64
    float mLastGain;          // +0x68
    u8   pad3[0x74 - 0x6c];
    float mLowPass;           // +0x74
    float mHighPass;          // +0x78
    float mDopplerPitch;      // +0x7c
    float mRandomPitch;       // +0x80
    float mPitch;             // +0x84
    float mSpeed;             // +0x88
    float mSmoothSpeed;       // +0x8c
    float mLastPitch;         // +0x90
    u8   pad4[0x9d - 0x94];
    u8   mb9d;                // +0x9d
    u8   mb9e;                // +0x9e
    u8   pad5;
    u8   mbDirect;            // +0xa0
    u8   pad6[3];
    u32  mPosHandle;          // +0xa4
    Vec3 mPos;                // +0xa8
    Vec3 mVelDelta;           // +0xb4
    u8   mMode;               // +0xc0
    u8   pad7[3];
    Vec3 mDirectPos;          // +0xc4
    u8   pad8[0xd8 - 0xd0];
    float mWetLevel;          // +0xd8
    u8   pad9[0xe4 - 0xdc];
    ConfigObj mConfig;        // +0xe4
    u8   pad10[0xfc - 0xe4 - sizeof(ConfigObj)];
    HMap<PropNode> mProps;    // +0xfc
    u8   pad11[0x320 - 0x104];
    u32  mSoundId;            // +0x320
    float mStartDelay;        // +0x324
    u8   pad12[0x32c - 0x328];
    float mElapsed;           // +0x32c
    u8   pad13[0x33c - 0x330];
    HMap<PrimNode> mPrims;    // +0x33c
    u8   pad14[0xc94 - 0x344];
    LerpF mFader;             // +0xc94
    u8   pad15[0xcd0 - 0xc95];
    float mFinishTime;        // +0xcd0
    u8   mbHasFinish;         // +0xcd4
    u8   pad16[0xce4 - 0xcd5];
    u32  mFlags;              // +0xce4
    u8   pad17[0xcec - 0xce8];
    RCurve mCurveA;           // +0xcec
    RCurve mCurveB;           // +0x1050
    RCurve mCurveC;           // +0x13b4
    RCurve mCurveD;           // +0x1718
    RCurve mCurveE;           // +0x1a7c
    u8   padF[0x1df0 - 0x1de0];
    float mFadeTo;            // +0x1df0
    float mFadeCur;           // +0x1df4
    float mFadeRate;          // +0x1df8
    char* mStrBegin;          // +0x1dfc
    char* mStrEnd;            // +0x1e00
    u8   pad18[0x1e0c - 0x1e04];
    int  mCount;              // +0x1e0c

    bool StrEmpty() { return mStrBegin == mStrEnd; }
    char* StrData() { return mStrBegin; }
    u32 StrSize() { return mStrEnd - mStrBegin; }
    void UpdatePropertiesFromPrimitives(bool all);   // 00a1cf60
    void CommitAllProperties();                      // 00a1d080
    void SetData(u32 id, void* arg, u32 arg4);       // 00a1d310
    int  TickInternal(int unused, float dt, bool force); // 00a1c710
    bool ConfigurePrimitives();                      // 00a1c460
};
struct NodePool {
    u8     pad0[0x1c];
    void*  mpFree;      // +0x1c
    u8     pad1[0xc];   // +0x20
    void*  mpAlloc;     // +0x2c

    void Insert(void* v);
};
// ---- items of slice s00a1c460 end

// ---- items of slice s00a1e320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  f_00921260(void* pool, unsigned size, unsigned buckets, unsigned align, unsigned n);
extern u32   f_00921340(int n);
extern unsigned f_009213c0(void* self, unsigned v);
extern void  f_00a22220(void* self, unsigned n);
extern void  f_00a1cdb0(void* self, void* a, void* b, void* c, void* d, void* e, void* f, void* g);
extern void  f_00a1ce60(void* self, void* a, void* b, void* c, void* d, void* e, void* f, void* g);
extern void* f_011e0744(void* dst, const void* src, unsigned bytes);
extern void  f_00f47380(void* p);
extern void* f_00a80dd0(void* pos, const void* value);
extern char  f_00a1b160(void* self, int a, int b, void* out);
extern float f_00a1ac70(void* self, float x);
extern void  f_00a24480(void* self, int a, int b);
extern void  f_00a1b6c0(void* self, int a, int b);
extern void* f_00a206f0(void);
extern void  f_00899480(unsigned* pos, const unsigned* value);
extern void  f_00a1b020(void);
extern "C" int __cdecl isalnum(int c);
extern "C" int __cdecl tolower(int c);
static void*  g_166d9bc;
static void*  g_166d9c0;
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)(obj))[(slot) / 4])

// EASTL fixed-pool / fixed-hashtable helpers used by the two Sound factory ctors.
struct FixedPoolBase {
    void* mpBuffer;         // +0x00  set by init(): aligned free-list buffer
    void* mpUnk04;          // +0x04
    void* mpBegin;          // +0x08  buffer handed to the hashtable pool
    void* mpEnd;            // +0x0c  begin + size
    u32   mnCount;          // +0x10  element count
    void* mpBuckets;        // +0x14  owner-embedded bucket array (copied to pool+0x14)
    void* mpUnk18;          // +0x18
    void init(void* p, u32 size, u32 count, u32 align, u32 offset);  // 0x00921260 (thiscall, ret 0x14)
};
struct HashtableCtor {      // eastl::hashtable<unsigned,EA::AutoRefCount<PrimitiveRegister>,...>
    // Only args 1 (bucket count) and 7 (pool descriptor) are consumed.
    void ctor(u32 buckets, void* a, void** b, void** c, void* d, void** e, void* pool); // 0x00a1cdb0 (thiscall, ret 0x1c)
};
struct HashtableCtor2 {     // same shape, larger fixed allocator
    void ctor(u32 buckets, void* a, void** b, void** c, void* d, void** e, void* pool); // 0x00a1ce60 (thiscall, ret 0x1c)
};
struct RehashCalc {         // bucket count for a load factor: ecx = &policy
    u32 calc(u32 n);        // 0x009213c0 (thiscall, ret 4)
};
struct SimpleVecPush {      // SP::SimpleVector<CellData*>
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCap;            // +0x08
    void Insert(void** pos, void** value);   // 0x00a80dd0 (thiscall, ret 8)
};
struct Vec4 {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCap;

    Vec4* assign_(const Vec4& other);
    void* DoAssign(unsigned n, void* first, void* last);   // external: vector range-assign helper
};
struct Sound74 {
    unsigned char m[0xd40];

    void* ctor_00a1e320(void* a1, void* a2);
    void* ctor_00a1e420(void* a1, void* a2);
    void AddCell(void* p);
    void ReleaseAllCells();
    void UpdateCells(int a, float* b);
    char ConfigureNote();
    void Teardown();
    void SubscribeToGroupsFromSymbol(const char* symbol);
};
// ---- items of slice s00a1e320 end

// ---- items of slice s00a20060 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0xf473a0
struct Sound_s00a2_0060;
struct IConfig {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08();
    virtual bool GetBool(u32 key, void* out);              // +0x24
    virtual void c0a();
    virtual bool GetInt(u32 key, void* out);               // +0x2c
    virtual bool GetFloat(u32 key, void* out);             // +0x30
    virtual void c0d();
    virtual void SetStr(u32 key, void* in);                // +0x38
    virtual void* GetPtr(u32 key);                         // +0x3c
    virtual void c10();
    virtual bool GetPair(u32 key, void* a, void* b);       // +0x44
    virtual bool GetList8(u32 key, void* a, void* b);      // +0x48
    virtual bool GetList12(u32 key, void* a, void* b);     // +0x4c
};
struct ResponseCurve {
    void InitFromConfiguration(IConfig* cfg, u32 key);       // 00a1a9d0
    void SetResponseCurveData(void* data, int count);        // 00a1a590
};
struct Playlist {                                             // [esi+0x2d8]
    int  Ok();                                                // 00a14690
    u32  Id();                                                // 00a146a0
};
struct BitVec {
    void Resize(int n);                                       // 0089cb60
};
struct GroupVec {
    u32* b; u32* e; u32* cap;
    void DoInsertValue(u32* pos, const u32& v);               // 00899480
    void push_back(const u32& v)
    {
        if (e < cap) {
            if (e) *e = v;
            ++e;
        } else {
            DoInsertValue(e, v);
        }
    }
};
struct Fx {                                                   // 0x1c bytes, vtable: AddRef/Release
    virtual void AddRef();
    virtual void Release();
    Fx(Sound_s00a2_0060* owner);                                         // 00a17100
    void  SetLevel(float v);                                  // 00a16fd0
    static void* operator new(unsigned size);                 // 00a17090
};
void* __cdecl memcpy_(void*, const void*, unsigned);          // 011e0744
struct ISys {                                                 // EA::Audio::System as seen by sounds
    void  Slot108(u32 id, void* a)  { ((void (__thiscall*)(void*, u32, void*))((*(void***)this)[0x108 / 4]))(this, id, a); }
    void* Slot11c(u32 id)           { return ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x11c / 4]))(this, id); }
    u32   Slot0f0(void* p)          { return ((u32 (__thiscall*)(void*, void*))((*(void***)this)[0xf0 / 4]))(this, p); }
    void  Slot160(u32 a, int b, int c, void* d) { ((void (__thiscall*)(void*, u32, int, int, void*))((*(void***)this)[0x160 / 4]))(this, a, b, c, d); }
};
ISys* GetSystemAT_s00a2_0060();                                          // 00a206f0
template<int Off> inline void VThis(void* self, u32 a)
{
    ((void (__thiscall*)(void*, u32))((*(void***)self)[Off / 4]))(self, a);
}
struct Rc {                                                   // refcounted object: vtbl, count at +4
    void* vt; int rc;
};
struct Sound_s00a2_0060 {
    void** vt;
    template<class T> T& at(int off) { return *(T*)((char*)this + off); }
    bool ConfigureSound();  // 0x00a20060 (Sound::ConfigureSound)
};
static inline u32 Id(u32 x) { return x; }
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s00a20060 end

// ---- items of slice s00a36d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
// ---- items of slice s00a36d60 end

// ---- items of slice s00a1a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
static __forceinline void** VtOf(void* p) { return *(void***)p; }
void* __cdecl FUN_00a206f0(void);                        // EA::Audio::GetSystemAT
double __cdecl pow(double, double);                      // CRT
struct Sound_s00a1_a590 {
    uint8_t  pad000[0x3c];
    uint32_t mInstanceId;          // +0x03c
    uint8_t  pad040[0x08];
    float    mf48;                 // +0x048
    uint8_t  pad04c[0x04];
    float    mf50;                 // +0x050
    float    mf54;                 // +0x054
    float    mf58;                 // +0x058
    float    mf5c;                 // +0x05c
    uint8_t  pad060[0x0c];
    float    mf6c;                 // +0x06c
    uint8_t  pad070[0x28];
    float    mf98;                 // +0x098
    uint8_t  mb9c;                 // +0x09c  (stop flags)
    uint8_t  pad09d[3];
    uint8_t  mba0;                 // +0x0a0
    uint8_t  pad0a1[0x1f];
    uint8_t  mbC0;                 // +0x0c0  (0xf == "running")
    uint8_t  pad0c1[0x07];
    double   mdC8;                 // +0x0c8
    uint8_t  pad0d0[0x0c];
    uint32_t mdDC;                 // +0x0dc
    uint8_t  pad0e0[0xbb4];
    uint8_t  mEnvelopeArea[0x050]; // +0xc94  (embed Envelope at +0xc94)
    uint32_t mFlagsCE4;            // +0xce4
    uint8_t  padCE8[0x1104];

    bool   PausedIgnoring(uint32_t idx);  // 0x00a1ae00 (Sound::PausedIgnoring)
    double RunningAttenuation();  // 0x00a1ae90 (Sound::RunningAttenuation)
    void   RequestStop(uint32_t reason, uint8_t flags);  // 0x00a1aef0 (Sound::RequestStop)
    bool   ShouldPauseForLowGain(float gain);  // 0x00a1af80 (Sound::ShouldPauseForLowGain)
    static double ComputeGainAttenuation(float a, float b, float c, float d, float e);  // 0x00a1afb0 (Sound::ComputeGainAttenuation)
    void   Tick(uint32_t a, float dt);  // 0x00a1b230 (Sound::Tick)

    bool   IsFlag1();
    bool   ClearFlag1();
    void   SetInstanceId(uint32_t id);
    bool   IsFlag2();
    bool   IsFlag80();
    double GetDoubleC8();
    double AttnHelper();
    uint8_t Bit3();
    bool   PauseStateAllowed(uint32_t idx, char flag);
};
struct Envelope {
    float    mEnvelope[6];  // +0x00
    int32_t  mPhase;        // +0x18
    uint8_t  mbStarted;     // +0x1c
    float    mElapsedTime;  // +0x20

    void Update(float dt);
};
struct CurveEval {
    float   mf[6];   // +0x00
    int32_t mMode;   // +0x18
    float   mf20;    // +0x20
    float   mf24;    // +0x24
    float   mf28;    // +0x28
    float   mf2c;    // +0x2c
    float   mf30;    // +0x30

    double Eval();
};
struct SoundGraph {
    uint8_t  pad000[0x2e0];
    void**   mList2e0;      // +0x2e0
    void**   mList2e4;      // +0x2e4
    uint8_t  pad2e8[0x38];
    void*    mFirst320;     // +0x320
    uint8_t  pad324[0x958];
    void**   mListC7c;      // +0xc7c
    void**   mListC80;      // +0xc80

    uint32_t Dispatch(uint32_t a, uint32_t b);   // 0xa1b1e0
    bool     Remove(void* target);               // 0xa1b320
    void     PopFront();                         // 0xa1b390
    bool     Contains(void* target);             // 0xa1b440
};
struct InstrumentZone {
    uint8_t mKeyLo;    // +0x18
    uint8_t mKeyHi;    // +0x19
    uint8_t mVelLo;    // +0x1a
    uint8_t mVelHi;    // +0x1b
    uint8_t pad[0x10];
    float   mParams[0xb];
};
struct ResourceInstrumentBank {
    uint8_t  pad00[0x18];
    InstrumentZone* mZonesBegin;  // +0x18
    InstrumentZone* mZonesEnd;    // +0x1c

    bool FindZone(int32_t key, int32_t vel, void* out);   // out receives a 0x2c-byte zone
};
// ---- items of slice s00a1a590 end

// ---- items of slice s00a1b480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_13eb95c;   // 0x013eb95c
void* GetSystemAT_s00a1_b480();                                    // 0x00a206f0
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct Vec3_s00a1_b480 { float x, y, z; };
struct LerpF_s00a1_b480 {
    float mTarget;   // +0
    float mCurrent;  // +4
    float mRate;     // +8
    __declspec(noinline) void Set(const float& value, float rate);   // 0x00a1b660
    float Get();                                 // 0x00a1b020
};
struct ConfigObj_s00a1_b480 { void* vptr; };
struct Sound_s00a1_b480 {
    void*  vptr;                       // 0x00
    void*  vptrMix;                    // 0x04
    void*  vptrRef;                    // 0x08
    u32    mRefCount;                  // 0x0c
    void*  mNodeNext;                  // 0x10
    void*  mNodePrev;                  // 0x14
    u8     pad00[0x38 - 0x18];         // 0x18
    u32    mSoundId;                   // 0x38
    u32    mInstanceId;                // 0x3c
    u32    mSampleId;                  // 0x40
    void*  mpEmitter;                  // 0x44
    float  mDistanceToListener;        // 0x48
    float  mLastDistance;              // 0x4c
    float  mMinDistance;               // 0x50
    float  mMaxDistance;               // 0x54
    float  mGain;                      // 0x58
    float  mMaxGainChange;             // 0x5c
    float  mAttenuatedGain;            // 0x60
    float  mEffectiveGain;             // 0x64
    float  mPauseGain;                 // 0x68
    float  mPriority;                  // 0x6c
    float  mWetLevel;                  // 0x70
    float  mLowPass;                   // 0x74
    float  mHighPass;                  // 0x78
    float  mDopplerPitch;              // 0x7c
    float  mRandomPitch;               // 0x80
    float  mPitch;                     // 0x84
    float  mAverageSpeed;              // 0x88
    float  mLastPitch;                 // 0x8c
    float  m90;                        // 0x90
    float  m94;                        // 0x94
    float  m98;                        // 0x98
    bool   mbHardStop;                 // 0x9c
    bool   mb9d;                       // 0x9d
    bool   mb9e;                       // 0x9e
    bool   mb9f;                       // 0x9f
    bool   mbDirect;                   // 0xa0
    u8     pad1[3];                    // 0xa1
    u32    mPosHandle;                 // 0xa4
    Vec3_s00a1_b480   mPos;                       // 0xa8
    Vec3_s00a1_b480   mVelDelta;                  // 0xb4
    u8     mMode;                      // 0xc0
    u8     pad2[3];                    // 0xc1
    Vec3_s00a1_b480   mDirectPos;                 // 0xc4
    float  mDirGain0;                  // 0xd0
    float  mDirGain1;                  // 0xd4
    float  mWetLevel2;                 // 0xd8
    int    mStopReason;                // 0xdc
    u32    mEmitterType;               // 0xe0
    ConfigObj_s00a1_b480 mConfig;                 // 0xe4
    u8     pad3[0xfc - 0xe4 - sizeof(ConfigObj_s00a1_b480)];  // 0xe8
    u8     mProps[0x320 - 0xfc];       // 0xfc (fixed_hash_map)
    u32    m320;                       // 0x320
    float  mStartDelay;                // 0x324
    float  m328;                       // 0x328
    float  mElapsed;                   // 0x32c
    u8     mPrims[0xc38 - 0x330];      // 0x330 (fixed_vector + hash)
    void*  mC38;                       // 0xc38
    u8     pad4[0xc7c - 0xc3c];        // 0xc3c
    u32    mC7c;                       // 0xc7c
    u32    mC80;                       // 0xc80
    u8     pad5[0xc90 - 0xc84];        // 0xc84
    void*  mC90;                       // 0xc90
    float  mC94;                       // 0xc94 (fader target; fader.mCurrent == mC98)
    float  mC98;                       // 0xc98
    u8     pad6[0xca8 - 0xc9c];        // 0xc9c
    float  mCA8;                       // 0xca8
    u32    mCAC;                       // 0xcac
    u8     mCB0;                       // 0xcb0
    u8     pad7[3];                    // 0xcb1
    float  mCB4;                       // 0xcb4
    u8     pad8[0xcc8 - 0xcb8];        // 0xcb8
    double mCC8;                       // 0xcc8
    float  mCD0;                       // 0xcd0
    u8     mCD4;                       // 0xcd4
    u8     mCD5;                       // 0xcd5
    u8     pad9[2];                    // 0xcd6
    u32    mCD8;                       // 0xcd8
    u8     pad10[0xce4 - 0xcdc];       // 0xcdc
    u32    mFlags;                     // 0xce4
    u8     pad11[0x1de0 - 0xce8];      // 0xce8 (response curves)
    int    mPauseCount;                // 0x1de0
    u8     mPauseCounts[8];            // 0x1de4
    u32    mNumPauseCounters;          // 0x1dec
    LerpF_s00a1_b480  mPauseFader;                // 0x1df0
    u8     pad12[0x1e0c - 0x1dfc];     // 0x1dfc
    int    mCount;                     // 0x1e0c

    // methods in this slice
    bool StartEmitter(float param);                  // 0x00a1b480
    bool Init();                                     // 0x00a1b730
    bool Start(double time);                         // 0x00a1b8a0
    bool Stop(int reason, bool force);               // 0x00a1bba0
    bool ShutdownImpl();                             // 0x00a1be10
    int  Pause(bool pause, u32 index, float fade, bool force); // 0x00a1bf50
    void UpdateGainAndDistance(float param);         // 0x00a1c120
    bool CalculateDistanceToListener();              // 0x00a1c290
    bool CreateEmitter();                            // 0x00a1c2f0
};
// ---- items of slice s00a1b480 end

// ---- items of slice s00a1d400 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* AllocObject(u32 size);                           // 0x00a17090
void* CtorHelper(void* obj, void* owner);              // 0x00a17100
struct Vec3_s00a1_d400 { float x, y, z; };
extern const u32 g_propKey14527fc;   // 0x014527fc
struct HTIter { void* node; void* bucket; };
struct Hashtable {
    u32    pad0;         // +0x00
    void** mpBuckets;    // +0x04
    u32    mnBuckets;    // +0x08
    u32    padC;         // +0x0c
    HTIter find(const u32& key) const;         // 0x00645ed0
    void   insert(void* pair, void* alloc, int flag);  // 0x00a26ce0
    HTIter erase(HTIter it);                   // 0x00d2c9f0
};
struct PropNode_s00a1_d400 { u32 key; float value; };
struct Sound_s00a1_d400 {
    void*  vptr;                       // 0x00
    void*  vptrMix;                    // 0x04
    void*  vptrRef;                    // 0x08
    u32    mRefCount;                  // 0x0c
    void*  mNodeNext;                  // 0x10
    void*  mNodePrev;                  // 0x14
    u8     pad00[0x38 - 0x18];         // 0x18
    u32    mSoundId;                   // 0x38
    u32    mInstanceId;                // 0x3c
    u32    mSampleId;                  // 0x40
    void*  mpEmitter;                  // 0x44
    float  mDistanceToListener;        // 0x48
    float  mLastDistance;              // 0x4c
    float  mMinDistance;               // 0x50
    float  mMaxDistance;               // 0x54
    float  mGain;                      // 0x58
    float  mMaxGainChange;             // 0x5c
    float  mAttenuatedGain;            // 0x60
    float  mEffectiveGain;             // 0x64
    float  mPauseGain;                 // 0x68
    float  mPriority;                  // 0x6c
    float  mWetLevel;                  // 0x70
    float  mLowPass;                   // 0x74
    float  mHighPass;                  // 0x78
    float  mDopplerPitch;              // 0x7c
    float  mRandomPitch;               // 0x80
    float  mPitch;                     // 0x84
    float  mAverageSpeed;              // 0x88
    float  mLastPitch;                 // 0x8c
    float  m90;                        // 0x90
    float  m94;                        // 0x94
    float  m98;                        // 0x98
    u8     mb9c;                       // 0x9c
    u8     mb9d;                       // 0x9d
    u8     mb9e;                       // 0x9e
    u8     mb9f;                       // 0x9f
    u8     mbDirect;                   // 0xa0
    u8     pad1[3];                    // 0xa1
    u32    mPosHandle;                 // 0xa4
    Vec3_s00a1_d400   mPos;                       // 0xa8
    Vec3_s00a1_d400   mVelDelta;                  // 0xb4
    u8     mMode;                      // 0xc0
    u8     pad2[3];                    // 0xc1
    Vec3_s00a1_d400   mDirectPos;                 // 0xc4
    u8     pad3[0xf4 - 0xd0];          // 0xd0
    u8     mPropF4[0x14];              // 0xf4 (property hashtable region)
    u8     pad4[0x320 - 0x108];        // 0x108
    u32    m320;                       // 0x320
    float  mStartDelay;                // 0x324
    float  m328;                       // 0x328
    float  mElapsed;                   // 0x32c
    u32    mPrimsCount;                // 0x330
    u8     mMap334[0x14];              // 0x334 (primitive map; +4 bucket, +8 count; 0x338 overlaps)
    u8     pad5[0x514 - 0x348];        // 0x348
    u8     mMap514[0x20];              // 0x514
    u8     pad6[0x888 - 0x534];        // 0x534
    u8     mMap888[0x20];              // 0x888
    u8     pad7a[0xc90 - 0x8a8];       // 0x8a8
    u32    mC90;                       // 0xc90
    u8     pad7b[0xcd0 - 0xc94];       // 0xc94
    float  mCD0;                       // 0xcd0
    u8     mCD4;                       // 0xcd4
    u8     mCD5;                       // 0xcd5
    u8     pad8[0xce4 - 0xcd6];        // 0xcd6
    u32    mFlags;                     // 0xce4
    u8     pad9[0x1e0c - 0xce8];       // 0xce8
    int    mCount;                     // 0x1e0c

    // methods in this slice
    bool GetPropertyInternal(u32 key, float* out);          // 0x00a1d400
    bool HasProperty(u32 key);                              // 0x00a1d6d0
    bool CompareProperties(void* other);                    // 0x00a1d710
    void SetProperty(u32 key, float value, u32 arg);        // 0x00a1d830
    void SetPropertyInternal(u32 key, float value, bool dummy);  // 0x00a1d9c0
    bool ConnectPrimitive(u32 key, void* prim);             // 0x00a1df20
    void DisconnectPrimitive(u32 key, void* prim);          // 0x00a1e140
    void Route(u32 a, u32 b, void* prim);                   // 0x00a1e1d0
};
// ---- items of slice s00a1d400 end

// ---- items of slice s00a1f2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* GetSystemAT_s00a1_f2b0();                                                    // 0x00a206f0
void  __stdcall VectorGrow(void* end, const void* value);               // 0x00899480
void  SetCurveGain(void* self, float v);                                // 0x00a16fd0
void* VecBool_DoInsertValue(void* a, void* b, u32 n);                   // 0x011e0744
void  VecBool_assign_(void* self, u32 n, void* p);                      // 0x00a69430
void  Vec4_assign_(void* self, const void* src);                        // 0x00a1e520
void  OperatorDelete(void* p);                                          // 0x00f47380
void  HTable28_Rehash(void* self, u32 n);                               // 0x00a22220
void  Pool_init(void* self, void* p, u32 a, u32 b, u32 c, u32 d);       // 0x00921260
u32   Pool_alloc(u32 n);                                                // 0x00921340
u32   Pool_next(u32 n);                                                 // 0x009213c0
void  HashMap_ctor(void* self, void* a, void* b, void* c, void* d, void* e, void* f); // 0x00a1cdb0
struct VecU32 {
    u32* mpBegin; u32* mpEnd; u32* mpCapacity;
    void push_back(u32 value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) u32(value);
        else
            VectorGrow(mpEnd, &value);
    }
};
struct VecPtr { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct COWVec { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct SubE4 {
    void ctor();   // 0x00a107a0
    void dtor();   // 0x00a10800
};
struct ResponseCurve_s00a1_f2b0 {
    void ctor();   // 0x00a1aa50
};
struct FixedVecCtor {
    void* ctor(void* a, void* b);   // 0x00a1e320
};
struct FixedVecCtor2 {
    void* ctor(void* a, void* b);   // 0x00a1e420
};
struct FixedHashMapCtor {
    void* ctor(void* a, void* b);   // 0x00a1fab0
};
struct FixedHash {
    u32   mPad00;        // +0x00
    void* mpBegin;       // +0x04
    u32   mnCount;       // +0x08
    u32   mnFlag;        // +0x0c
    u32   mPad10[3];     // +0x10..+0x1b
    void* mpFreeList;    // +0x1c
    u32   mPad20;        // +0x20
    void* mpInlineLo;    // +0x24
    void* mpInlineHi;    // +0x28
    u32   mPad2c;        // +0x2c
    void* mpInline;      // +0x30
    void DoFreeNodes(void* p, u32 n);   // 0x00a1b6c0
    void FreeBuckets(void* p, u32 n);   // 0x00a24480
};
static __forceinline void CopyFloat(float* dst, const float* src)
{
    _mm_store_ss(dst, _mm_load_ss(src));
}
static void TeardownFixedHash(FixedHash* h, bool buckets)
{
    if (buckets)
        h->FreeBuckets(h->mpBegin, h->mnCount);
    else
        h->DoFreeNodes(h->mpBegin, h->mnCount);

    h->mnFlag = 0;
    void* p = h->mpBegin;
    u32 n = h->mnCount;
    if (n > 1 && p != h->mpInline) {
        if ((char*)p < (char*)h->mpInlineLo || (char*)p >= (char*)h->mpInlineHi)
            OperatorDelete(p);
        else {
            *(void**)p = h->mpFreeList;
            h->mpFreeList = p;
        }
    }
}
struct Sound_s00a1_f2b0 {
    u8     pad0[0x2e0];
    VecU32 mGroups;                       // 0x2e0  eastl fixed_vector<u32,10>
    u8     pad1[0x2000 - 0x2e0 - 12];

    void  UnsubscribeFromGroupsFromSymbol(const char* str);   // 0x00a1f2b0
    void  CreatePrimitive(u32 id);                            // 0x00a1f840
    void  CopyStateFrom(Sound_s00a1_f2b0* src);                          // 0x00a1f960
    Sound_s00a1_f2b0();                                                  // 0x00a1fbb0
    ~Sound_s00a1_f2b0();                                                 // 0x00a1f4d0
};
// ---- items of slice s00a1f2b0 end

// @ 0x00a1ac70
float FUN_00a1ac70(int a, int b)
{
    // Note -> frequency ratio: 440 * 2^((n - 69) * 0.0577623).
    double fa = 440.0 * pow(2.0, ((double)a - 69.0) * 0.0577623);
    double fb = 440.0 * pow(2.0, ((double)b - 69.0) * 0.0577623);
    return (float)(fa / fb);
}

// @ 0x00a1acd0
bool Sound_s00a1_a590::ClearFlag1()
{
    if ((mFlagsCE4 & 1) == 0)
        return false;
    mFlagsCE4 &= ~1u;
    ((void(__thiscall*)(void*))VtOf(this)[0x94 / 4])(this);
    return true;
}

// @ 0x00a1ad20
void Sound_s00a1_a590::SetInstanceId(uint32_t id)
{
    uint32_t flags = mFlagsCE4;
    mInstanceId = id;
    mFlagsCE4 = flags | 2u;
}

// @ 0x00a1ad40
bool Sound_s00a1_a590::IsFlag2()
{
    return (mFlagsCE4 & 2) == 2;
}

// @ 0x00a1adc0
bool Sound_s00a1_a590::PauseStateAllowed(uint32_t idx, char flag)
{
    if (flag != 0 && (mFlagsCE4 & 0x800) != 0)
        return false;
    if (idx < *(uint32_t*)((char*)this + 0x1dec))
        return *((uint8_t*)this + 0x1de4 + idx) > 0u;
    return *(uint32_t*)((char*)this + 0x1de0) != 0;
}

// @ 0x00a1ae00
bool EA::Audio::Sound::PausedIgnoring(unsigned int idx)
{
    return (int)*(uint32_t*)((char*)this + 0x1de0) - (int)*((uint8_t*)this + 0x1de4 + idx) > 0;
}

// @ 0x00a1ae20
bool Sound_s00a1_a590::IsFlag80()
{
    return (mFlagsCE4 & 0x80) == 0x80;
}

// @ 0x00a1ae40
double Sound_s00a1_a590::GetDoubleC8()
{
    return *(double*)((char*)this + 0xcc8);
}

// @ 0x00a1ae90
double Sound_s00a1_a590::RunningAttenuation()
{
    if (mbC0 == 0xf) {
        typedef double (__thiscall* AttnFn)(void*, float, float, float, float, float);
        return ((AttnFn)VtOf(this)[0xa8 / 4])(this, mf48, mf50, mf54, mf58, mf98);
    }
    return 1.0;
}

// @ 0x00a1aef0
void Sound_s00a1_a590::RequestStop(uint32_t reason, uint8_t flags)
{
    uint32_t mask = 0x80;
    if ((mFlagsCE4 & mask) == 0) {
        mFlagsCE4 |= mask;
        mdDC = reason;
        mb9c = flags;
        void* at = FUN_00a206f0();
        ((void(__thiscall*)(void*, int, uint32_t, uint32_t, uint32_t, void*))VtOf(at)[0x128 / 4])(
            at, 0x63e3de7, mInstanceId, reason, flags, this);
    }
}

// @ 0x00a1af50
uint8_t Sound_s00a1_a590::Bit3()
{
    uint8_t v = mbC0;
    v = v >> 3;
    v = v & 1;
    return v;
}

// @ 0x00a1af80
bool Sound_s00a1_a590::ShouldPauseForLowGain(float gain)
{
    return (mFlagsCE4 & 0x1000) == 0 && gain < mf6c;
}

// @ 0x00a1afb0
double Sound_s00a1_a590::ComputeGainAttenuation(float a, float b, float c, float d, float e)
{
    (void)d;
    if (e != 1.0f)
        a = (1.0f / e) * a;
    if (c > a)
        return 1.0;
    if (b == 0.0f)
        return 1.0;
    double t = ((double)a / (double)c) - 1.0;
    return 1.0 / (t * (double)b + 1.0);
}

// @ 0x00a1b020
double CurveEval::Eval()
{
    float f0 = mf[mMode];
    float f2;
    float f3;

    switch (mMode) {
    case 0:
    case 2:
        return 1.0;
    case 1:
        f2 = 1.0f;
        f3 = 0.0f;
        break;
    case 3:
        if (mf2c == 0.0f)
            mf2c = mf28;
        f2 = mf24;
        f3 = mf2c;
        break;
    case 4:
        return mf24;
    case 5:
        if (mf30 == 0.0f)
            mf30 = mf28;
        f3 = mf30;
        f2 = 0.0f;
        break;
    default:
        return 0.0;
    }

    if (f2 == 0.0f || f3 < 0.000000000001f)
        f3 = f2;

    if (f0 != 0.0f)
        f2 = ((f2 - f3) * mf20) / f0 + f3;

    mf28 = f2;
    return f2;
}

// @ 0x00a1b100
void EA::Audio::Envelope::Update(float dt)
{
    if (!mbStarted || mPhase == 0 || mPhase == 4 || mPhase == 6)
        return;

    mElapsedTime = mElapsedTime + dt;
    if (mPhase >= 6)
        return;

    for (;;) {
        int32_t p = mPhase;
        if (p == 4)
            return;
        if (mEnvelope[p] > mElapsedTime)
            return;
        if (mElapsedTime == mEnvelope[p])
            return;
        p = p + 1;
        mbStarted = 1;
        mElapsedTime = 0.0f;
        mPhase = p;
        if (p >= 6)
            return;
    }
}

// @ 0x00a1b160
bool ResourceInstrumentBank::FindZone(int32_t key, int32_t vel, void* out)
{
    int32_t n = (int32_t)(((char*)mZonesEnd - (char*)mZonesBegin) / 0x2c);
    for (int32_t i = 0; i < n; ++i) {
        InstrumentZone* z = (InstrumentZone*)((char*)mZonesBegin + i * 0x2c);
        if (key >= (int)z->mKeyLo && key <= (int)z->mKeyHi &&
            vel >= (int)z->mVelLo && vel <= (int)z->mVelHi) {
            const uint32_t* src = (const uint32_t*)z;
            uint32_t* dst = (uint32_t*)out;
            for (int k = 0; k != 0xb; ++k)
                dst[k] = src[k];
            return true;
        }
    }
    return false;
}

// @ 0x00a1b1e0
uint32_t SoundGraph::Dispatch(uint32_t a, uint32_t b)
{
    // `this` is an interior pointer: the vtable lives 4 bytes before it.
    char* vtableOwner = (char*)this - 4;
    if (((bool(__thiscall*)(void*, uint32_t, uint32_t))VtOf(vtableOwner)[0xac / 4])(vtableOwner, a, b))
        return 1;
    void* inner = *(void**)((char*)this + 0x40);
    if (inner != 0)
        return ((uint32_t(__thiscall*)(void*, uint32_t, uint32_t))VtOf(inner)[0x30 / 4])(inner, a, b);
    return 0;
}

// @ 0x00a1b230
void Sound_s00a1_a590::Tick(uint32_t a, float dt)
{
    *(float*)((char*)this + 0x324) = dt + *(float*)((char*)this + 0x324);
    ((Envelope*)((char*)this + 0xc94))->Update(dt);

    if ((mFlagsCE4 & 0x40) != 0) {
        if (*(int32_t*)((char*)this + 0xcac) == 6 ||
            ((bool(__thiscall*)(void*, uint32_t, int))VtOf(this)[0x20 / 4])(this, 0xffffffffu, 1)) {
            ((void(__thiscall*)(void*))VtOf(this)[0x8c / 4])(this);
            return;
        }
    }

    if (((bool(__thiscall*)(void*, float))VtOf(this)[0x70 / 4])(this, dt)) {
        float p = mf98;
        float gain = mf58;
        if (p != 1.0f)
            gain = gain * p;
        if (mbC0 == 0xf && gain < mf48 && mba0 == 0) {
            if (((bool(__thiscall*)(void*, int, int))VtOf(this)[0x20 / 4])(this, 2, 0))
                return;
        }
        ((void(__thiscall*)(void*, float, uint32_t, int))VtOf(this)[0x9c / 4])(this, dt, a, 0);
    }
    (void)a;
}

// @ 0x00a1b320
bool SoundGraph::Remove(void* target)
{
    void** it = mListC7c;
    while (it != mListC80) {
        if (*it == target) {
            ((void(__thiscall*)(void*, int))VtOf(target)[0xd4 / 4])(target, 0);
            void** last = mListC80 - 1;
            *it = *last;
            mListC80 = last;
            ((void(__thiscall*)(void*))VtOf(target)[4 / 4])(target);
            return true;
        }
        ++it;
    }
    return false;
}

// @ 0x00a1b390
void SoundGraph::PopFront()
{
    void** end = mListC80;
    void* item = *(end - 1);
    mListC80 = end - 1;

    ((void(__thiscall*)(void*))VtOf(item)[4 / 4])(item);

    for (void** it = mListC7c; it != mListC80; ++it)
        ((void(__thiscall*)(void*, void*))VtOf(*it)[0xd4 / 4])(*it, item);

    ((void(__thiscall*)(void*, void*))VtOf(item)[0xc8 / 4])(item, this);
}

// @ 0x00a1b440
bool SoundGraph::Contains(void* target)
{
    if (mFirst320 != 0 && target == mFirst320)
        return true;
    for (void** it = mList2e0; it != mList2e4; ++it) {
        if (*it == target)
            return true;
    }
    return false;
}

// @ 0x00a1b660
void LerpF_s00a1_b480::Set(const float& value, float rate)
{
    float v = value;
    mTarget = v;
    float d = (float)fabs(v - mCurrent);
    if (rate != 0.0f && !(1e-06 > d))
        mRate = d / rate;
    else
        mCurrent = value;
}

// @ 0x00a1bf50
int Sound_s00a1_b480::Pause(bool pause, u32 index, float fade, bool force)
{
    if (index < mNumPauseCounters) {
        if (pause) {
            if (force || mPauseCounts[index] == 0) {
                ++mPauseCount;
                ++mPauseCounts[index];
            }
            if (fade < 0.0f) {
                if (!((bool(__thiscall*)(Sound_s00a1_b480*, u32, float*))VTSLOT(this, 0xac))(this, 0xe8ab99b9, &fade))
                    fade = g_13eb95c;
            }
            if (mpEmitter == 0 || ((bool(__thiscall*)(void*))VTSLOT(mpEmitter, 0x20))(mpEmitter)) {
                fade = 0.0f;
            } else if (fade != 0.0f) {
                mFlags |= 0x800;
            } else {
                mFlags &= ~0x800u;
                ((void(__thiscall*)(void*, int))VTSLOT(mpEmitter, 0x1c))(mpEmitter, 1);
            }
            float zero = 0.0f;
            mPauseFader.Set(zero, fade);
            return mPauseCount;
        }

        if ((mFlags & 0x80) == 0 && mPauseCounts[index] > 0) {
            --mPauseCount;
            --mPauseCounts[index];
            if (mPauseCount == 0) {
                mFlags &= ~0x800u;
                if (index == 3 || index == 2) {
                    fade = 0.0f;
                } else if (fade < 0.0f) {
                    if (!((bool(__thiscall*)(Sound_s00a1_b480*, u32, float*))VTSLOT(this, 0xac))(this, 0xe8ab99b9, &fade))
                        fade = g_13eb95c;
                }
                float one = 1.0f;
                mPauseFader.Set(one, fade);
                if (mpEmitter != 0) {
                    ((void(__thiscall*)(void*, int))VTSLOT(mpEmitter, 0x1c))(mpEmitter, 0);
                    ((void(__thiscall*)(Sound_s00a1_b480*))VTSLOT(this, 0x7c))(this);
                    ((void(__thiscall*)(Sound_s00a1_b480*, float, float, int))VTSLOT(this, 0x9c))(this, 0.0f, 0.0f, 1);
                }
            }
        }
    }
    return mPauseCount;
}

// @ 0x00a1c290
bool Sound_s00a1_b480::CalculateDistanceToListener()
{
    void* e = mC90;
    if (e == 0)
        return false;
    ((void(__thiscall*)(void*, Sound_s00a1_b480*))VTSLOT(e, 0xbc))(e, this);
    if (!(mFlags & 0x10)) {
        ((void(__thiscall*)(Sound_s00a1_b480*))VTSLOT(this, 0))(this);
        mFlags |= 0x10;
    }
    if (!(mFlags & 8)) {
        void* sys = GetSystemAT_s00a1_b480();
        ((void(__thiscall*)(void*, Sound_s00a1_b480*))VTSLOT(sys, 0x70))(sys, this);
        mFlags |= 8;
    }
    return true;
}

// @ 0x00a1c460
bool Sound::ConfigurePrimitives()
{
    u32 count;
    u32* arr;
    if (!mConfig.GetArray(0x3da0a727, &count, &arr))
        return false;
    while (count != 0) {
        if (count < 2)
            return false;
        count -= 2;
        u32 c = 0;
        u32 a = *arr++;
        u32 b = *arr++;
        if (a == 0 || b == 0)
            return false;
        if (count != 0) {
            c = *arr++;
            --count;
            if (count != 0 && *arr == 0) {
                ++arr;
                --count;
            }
        }
        ARC<IPrim> prim;
        if (c != 0) {
            int size;
            void* data;
            if (mConfig.GetData(c, &size, &data)) {
                PRespObj* r = new PRespObj(this);
                if (r) prim = r;
                ((PRespObj*)prim.p)->SetCurveData(data, size / 2);
                prim.p->SetEnabled(true);
            }
        }
        ARC<IPrim> sysPrim;
        ISystem* sys = GetSystemAT();
        sysPrim.Reset();
        if (sys->GetPrimitive(b, &sysPrim)) {
            if (prim.p) {
                ((PRespObj*)prim.p)->SetModSource(sysPrim.p);
                prim.p->v10();
                sysPrim = prim.p;
            }
            if (!((ISoundMix*)this)->AddPrimitive(a, sysPrim.p)) {
                sysPrim.p->SetEnabled(false);
                return false;
            }
        } else {
            vb4(a, b, prim.p);
        }
    }
    return true;
}

// @ 0x00a1c710
int Sound::TickInternal(int unused, float dt, bool force)
{
    float tmp;
    if (!mpEmitter->GetProperty(0x893f8476, &mElapsed))
        mElapsed += dt;
    bool b1 = Query(-1, 1);
    v78(force);
    if (force)
        v5c(dt);
    if ((mFlags & 0x400) && !(mFlags & 0x80) && mStartDelay >= mFinishTime)
        v80(0, 0);
    if (mbHasFinish && !(mFlags & 0x80) && mpEmitter) {
        float a;
        float b;
        if (mpEmitter->GetProperty(0xd24d4aff, &a)) {
            ((ISoundMix*)this)->GetProp(0xe8ab99b9, &b);
            float rem = (a > b) ? a - b : 0.0f;
            if (mElapsed >= rem)
                v80(0, 0);
        }
    }
    if (mFadeCur != mFadeTo) {
        float diff = mFadeTo - mFadeCur;
        float sign = (diff >= 0.0f) ? 1.0f : -1.0f;
        float ad = (float)fabs(diff);
        float step = mFadeRate * dt;
        if (step > ad) step = ad;
        mFadeCur = step * sign + mFadeCur;
    }
    if ((mFlags & 0x800) && mFadeCur == 0.0f && mpEmitter) {
        mFlags &= ~0x800u;
        mpEmitter->SetFlag(1);
    }
    float pf = mFadeCur;
    float g = mAttenGain;
    float v = mFader.Get() * g * pf;
    if (!(mMode & 8) || mMode == 0xf) {
        if (v88(g)) {
            if (mb9d != 0) {
                if (!Query(2, 0))
                    Stop(1, 2, 0.0f, 1);
            } else {
                v80(3, 0);
            }
        } else if (Query(2, 0)) {
            Stop(0, 2, 0.0f, 1);
        }
    }
    if (mpEmitter && !b1) {
        float prev = mLastGain;
        if (v != prev) {
            float lim = mMaxGainChange;
            if (lim > 0.0f && prev >= 0.0f) {
                float d = v - prev;
                float ad = (float)fabs(d);
                if (ad > lim)
                    v = (d / ad) * lim + prev;
            }
            mpEmitter->SetProperty(0x25df0108, v, 1);
        }
        mLastGain = v;
        if (mb9e && mMode == 0xf) {
            ((ISoundMix*)this)->SetProp(0x8c37ecc7, mDist, 1);
            ((ISoundMix*)this)->SetProp(0xdb495023, GetSystemAT()->GetSpeed(&mPos), 1);
            if (mbDirect) {
                mpEmitter->SetProperty(0x50c5d67, mDirectPos.x, 1);
                mpEmitter->SetProperty(0x50c5d66, mDirectPos.y, 1);
                mpEmitter->SetProperty(0x50c5d65, mDirectPos.z, 1);
                mpEmitter->SetProperty(0x26341ede, mWetLevel, 1);
            } else {
                mpEmitter->SetProperty(0x50c5d67, mPos.x, 1);
                mpEmitter->SetProperty(0x50c5d66, mPos.y, 1);
                mpEmitter->SetProperty(0x50c5d65, mPos.z, 1);
            }
            float hp = 96000.0f;
            float dop = 0.0f;
            float lp = 0.0f;
            if (mCount >= 2) {
                float o1 = mCurveA.GetOutputValue(mDist);
                hp = FMin(mHighPass, o1);
                float o2 = mCurveB.GetOutputValue(mDist);
                dop = FMax(mDopplerPitch, o2);
                float o3 = mCurveC.GetOutputValue(mDist);
                lp = FMax(mLowPass, o3);
                if (mFlags & 0x4000) {
                    Vec3* p = GetSystemAT()->GetPosition(mPosHandle);
                    Vec3 d = *p - mPos;
                    Vec3 vv = d - mVelDelta;
                    mVelDelta = d;
                    float sp = (float)sqrt(vv.x * vv.x + vv.z * vv.z + vv.y * vv.y) / dt * 0.1f;
                    mSmoothSpeed = mSmoothSpeed * 0.9f + sp;
                    float sg = (0.0f > mSmoothSpeed) ? -1.0f : 1.0f;
                    mRandomPitch = mCurveD.GetOutputValue((float)fabs(mSmoothSpeed)) * sg + 1.0f;
                }
            }
            mpEmitter->SetProperty(0x647a7836, hp, 1);
            mpEmitter->SetProperty(0xa26a765f, dop, 1);
            mpEmitter->SetProperty(0x49eb68db, lp, 1);
        }
        if (mSpeed != mLastPitch) {
            float x = mPitch * mRandomPitch * mSpeed;
            mpEmitter->SetProperty(0x71bc3009, x, 1);
            mLastPitch = x;
        }
    }
    return 0;
}

// @ 0x00a1cf10
void NodePool::Insert(void* v)
{
    void* p = mpFree;
    if (p != 0) {
        mpFree = *(void**)p;
    } else {
        p = operator_new(mpAlloc, "EASTL", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (p != 0) {
        *(u32*)p = *(const u32*)v;
        *(u32*)((char*)p + 4) = *(const u32*)((char*)(v) + 4);
    }
    *(u32*)((char*)p + 8) = 0;
}

// @ 0x00a1cf60
void Sound::UpdatePropertiesFromPrimitives(bool all)
{
    ScratchSlots<1>();
    if (all) {
        HMap<PrimNode>::Iter it = mPrims.begin();
        PrimNode* end = mPrims.end();
        while (it.mpNode != end) {
            it.mpNode->prim->SetValue(0.0f, 0);
            it.inc();
        }
    }
    HMap<PrimNode>::Iter it = mPrims.begin();
    PrimNode* end = mPrims.end();
    while (it.mpNode != end) {
        u32 key = it.mpNode->key;
        IPrim* prim = it.mpNode->prim;
        if (all || prim->v20(0)) {
            // The retail body dispatches through this object's vtable slot 0x98 but hands the
            // node's key as the receiver and the iteration end as the first argument.
            typedef void (__thiscall* SetPropFn)(void* self, void* arg, float v);
            SetPropFn fn = *(SetPropFn*)((char*)*(void**)this + 0x98);
            fn((void*)key, (void*)end, prim->GetValue(1));
        }
        it.inc();
    }
}

// @ 0x00a1d080
void Sound::CommitAllProperties()
{
    if (!mpEmitter)
        return;
    HMap<PropNode>::Iter it = mProps.begin();
    PropNode* end = mProps.end();
    while (it.mpNode != end) {
        mpEmitter->SetProperty(it.mpNode->key, it.mpNode->value, 1);
        it.inc();
    }
    if (!(mMode & 8) && mCount >= 2) {
        if (mFlags & 0x8000) mpEmitter->SetProperty(0x647a7836, mHighPass, 1);
        if (mFlags & 0x10000) mpEmitter->SetProperty(0xa26a765f, mDopplerPitch, 1);
        if (mFlags & 0x20000) mpEmitter->SetProperty(0x49eb68db, mLowPass, 1);
    }
    if (mbDirect) {
        if (mMode & 1) mpEmitter->SetProperty(0x50c5d67, mDirectPos.x, 1);
        if (mMode & 2) mpEmitter->SetProperty(0x50c5d66, mDirectPos.y, 1);
        if (mMode & 4) mpEmitter->SetProperty(0x50c5d65, mDirectPos.z, 1);
    } else {
        if (mMode & 1) mpEmitter->SetProperty(0x50c5d67, mPos.x, 1);
        if (mMode & 2) mpEmitter->SetProperty(0x50c5d66, mPos.y, 1);
        if (mMode & 4) mpEmitter->SetProperty(0x50c5d65, mPos.z, 1);
    }
    if (mMode & 8) {
        mpEmitter->SetProperty(0xf616b72, mMaxDistance, 1);
        mpEmitter->SetProperty(0x3593710, mGain, 1);
    }
    mpEmitter->SetProperty(0x12d2a4d4, (mMode & 8) ? 1.0f : 0.0f, 1);
    mpEmitter->SetProperty(0x6df5822d, (float)mCount, 1);
    if (!StrEmpty())
        mpEmitter->SetData(0x2fe09c83, StrData(), StrSize());
}

// @ 0x00a1d310
void Sound::SetData(u32 id, void* arg, u32 arg4)
{
    void* target = 0;
    switch (id) {
    case 0x173c2710: target = &mCurveC; break;
    case 0x8adce22f: target = &mCurveB; break;
    case 0x9b3918c4: target = &mCurveE; break;
    case 0xbdc98ce5: target = &mCurveA; break;
    case 0x2fe09c83: {
        ((BasicString*)&mStrBegin)->assign(arg);
        ISystem* sys = GetSystemAT();
        mSoundId = ((u32 (__thiscall*)(void*, void*))((*(void***)sys)[0xf4 / 4]))(sys, arg);
        break;
    }
    case 0x14043549:
        va4(arg);
        return;
    case 0x7cb81a35:
    case 0xf58ca0be:
        va0(arg);
        return;
    default:
        break;
    }
    if (target != 0)
        ((CurveData*)target)->SetFrom(arg, 0);
    IEmitter* em = mpEmitter;
    if (em != 0 && arg != 0)
        em->SetData(id, arg, arg4);
}

// @ 0x00a1d400
bool Sound_s00a1_d400::GetPropertyInternal(u32 key, float* out)
{
    switch (key) {
    case 0x3593710:  *out = mGain;           return true;
    case 0x50c5d66:  *out = mPos.y;          return true;
    case 0x50c5d67:  *out = mPos.x;          return true;
    case 0x50c5d65:  *out = mPos.z;          return true;
    case 0xf616b72:  *out = mMaxDistance;    return true;
    case 0x2406a047: *out = mMinDistance;    return true;
    case 0x25df0108: *out = mMaxGainChange;  return true;
    case 0x49eb68db: *out = mLowPass;        return true;
    case 0x393f7f7d: *out = mWetLevel;       return true;
    case 0x6325c989: *out = mEffectiveGain;  return true;
    case 0x647a7836: *out = mHighPass;       return true;
    case 0x6df5822d: *out = (float)mCount;   return true;
    case 0xb1f42539:
        if (mFlags & 0x400) { *out = mCD0; return true; }
        break;
    case 0xa26a765f: *out = mDopplerPitch;   return true;
    case 0xbaf7f4f9: *out = (float)mPrimsCount; return true;
    case 0xc2d1f579: *out = mPauseGain;      return true;
    case 0x222b8006: *out = mb9c ? 1.0f : 0.0f; return true;
    case 0x12d2a4d4: *out = (mMode & 8) ? 1.0f : 0.0f; return true;
    case 0x29e8b9f8: *out = m328;            return true;
    default: break;
    }

    Hashtable* ht = (Hashtable*)((char*)this + 0xf8);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        *out = *(float*)((char*)it.node + 4);
        return true;
    }
    return false;
}

// @ 0x00a1d6d0
bool Sound_s00a1_d400::HasProperty(u32 key)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0xf4);
    void** buckets = ht->mpBuckets;
    u32 n = ht->mnBuckets;
    void* end = (void*)buckets[n];
    return ht->find(key).node != end;
}

// @ 0x00a1d710
bool Sound_s00a1_d400::CompareProperties(void* other)
{
    if (mFlags & 0x80)
        return false;
    Sound_s00a1_d400* o = (Sound_s00a1_d400*)other;
    if (o == 0 || o == this)
        return false;
    if (!(o->mFlags & 0x10))
        return false;
    if (o->mbDirect == 0 || o->mC90 != 0)
        return false;
    if (o->mSoundId != mSoundId)
        return false;

    void* sys = GetSystemAT();
    if (((int(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, 0x71bc3009) == 0) {
        if (fabs(o->mAverageSpeed - mAverageSpeed) > 0.2f)
            return false;
    } else {
        void* p1;
        {
            Hashtable* h1 = (Hashtable*)((char*)this + 0x338);
            HTIter it = h1->find(g_propKey14527fc);
            if (it.node == (void*)h1->mpBuckets[h1->mnBuckets])
                return true;
            p1 = *(void**)((char*)it.node + 4);
        }
        void* p2;
        {
            Hashtable* h2 = (Hashtable*)((char*)o + 0x338);
            HTIter it2 = h2->find(g_propKey14527fc);
            if (it2.node == (void*)h2->mpBuckets[h2->mnBuckets])
                return true;
            p2 = *(void**)((char*)it2.node + 4);
        }
        float f1 = ((float(__thiscall*)(void*))VTSLOT(p1, 0x1c))(p1);
        float f2 = ((float(__thiscall*)(void*))VTSLOT(p2, 0x1c))(p2);
        if (fabs(f1 - f2) > 0.2f)
            return false;
    }
    return true;
}

// @ 0x00a1d830
void EA::Audio::Sound::SetProperty(unsigned int key, float value, bool arg)
{
    // The original guards against NaN/inf values before doing anything.
    u32 bits = *(u32*)&value;
    if ((bits & 0x7fffffff) != 0) {
        u32 e = (bits + 0xff800000) & 0x7f800000;
        if (e >= 0x7f000000) {
            u32 m = (bits & 0x7fffffff) - 1;
            if (m >= 0x7fffff)
                return;
        }
    }

    void* sys = GetSystemAT();
    void* e = ((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, key);
    if (e == 0) {
        ((void(__thiscall*)(void*, u32, float, u32))VTSLOT(this, 0x98))(this, key, value, arg);
        return;
    }

    Hashtable* ht = (Hashtable*)((char*)static_cast<EA::Audio::IMixable *>(this) + 0x514);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* obj = *(void**)((char*)it.node + 4);
        if (obj != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(obj, 0xc))(obj, 0x4e73a43a);
            if (p != 0) {
                ((void(__thiscall*)(void*, u32))VTSLOT(p, 0x10))(p, key);
                return;
            }
        }
        // fall through: rebuild primitive aggregate
    }
    {
        void* agg = AllocObject(0x6c);
        void* obj = 0;
        if (agg != 0)
            obj = CtorHelper(agg, this);
        if (obj != 0)
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        ((void(__thiscall*)(void*, void*))0x00a16a90)(e, obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), e);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), obj);
        ((void(__thiscall*)(void*))VTSLOT(obj, 0x10))(obj);
        ((void(__thiscall*)(void*, int))VTSLOT(obj, 0x2c))(obj, 1);
        void* old = *(void**)((char*)it.node + 4);
        if (obj != old) {
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
            *(void**)((char*)it.node + 4) = obj;
            if (old != 0)
                ((void(__thiscall*)(void*))VTSLOT(old, 4))(old);
        }
        ((void(__thiscall*)(void*))VTSLOT(obj, 4))(obj);
    }
}

// @ 0x00a1d9c0
void Sound_s00a1_d400::SetPropertyInternal(u32 key, float value, bool dummy)
{
    {
        Hashtable* ht = (Hashtable*)((char*)this + 0x888);
        HTIter it = ht->find(key);
        if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
            void* obj = *(void**)((char*)it.node + 4);
            ((void(__thiscall*)(void*, float))0x00a16fd0)(obj, value);
        }
    }

    bool changed = true;
    switch (key) {
    case 0x393f7f7d: mWetLevel = value; return;
    case 0x12d2a4d4:
        if (value == 0.0f) mMode &= ~8;
        else               mMode |= 8;
        goto done;
    case 0x50c5d66:  mPos.y = value; mMode |= 2; return;
    case 0x3593710:  mGain = value; goto done;
    case 0x50c5d65:  mPos.z = value; mMode |= 4; return;
    case 0x50c5d67:  mPos.x = value; mMode |= 1; return;
    case 0xf616b72:  mMaxDistance = value; goto done;
    case 0x25df0108: mMaxGainChange = value; return;
    case 0x222b8006: mb9c = (value != 0.0f); return;
    case 0x2406a047: mMinDistance = value; return;
    case 0x26341ede: {
        float prev = m94;
        m94 = value;
        changed = (prev != value);
        goto done;
    }
    case 0x29e8b9f8: m328 = value; return;
    case 0x71bc3009: mAverageSpeed = value; return;
    case 0x6dd08218: mb9d = (value != 0.0f); return;
    case 0x49eb68db: {
        float prev = mLowPass;
        mLowPass = value;
        mFlags |= 0x20000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0x647a7836: {
        float prev = mHighPass;
        mHighPass = value;
        mFlags |= 0x8000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0x6df5822d: {
        int iv = (int)value;
        changed = (mCount != iv);
        mCount = iv;
        goto done;
    }
    case 0xba134192: mbDirect = (value != 0.0f); return;
    case 0xa26a765f: {
        float prev = mDopplerPitch;
        mDopplerPitch = value;
        mFlags |= 0x10000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0xb1f42539: mCD0 = value; mFlags |= 0x400; return;
    case 0xb85523e5: {
        bool b = (value != 0.0f);
        ((int(__thiscall*)(Sound_s00a1_d400*, bool, u32, float, int))VTSLOT(this, 0x1c))(this, b, 4, 3.0f, 1);
        return;
    }
    case 0xbaf7f4f9: mPrimsCount = (u32)(long long)value; return;
    case 0xc57f4567: {
        float prev = mPos.x;
        mPos.x = value;
        changed = (prev != value);
        goto done;
    }
    default: break;
    }

    {
        Hashtable* ht = (Hashtable*)((char*)this + 0xf8);
        HTIter it = ht->find(key);
        if (it.node == (void*)ht->mpBuckets[ht->mnBuckets]) {
            PropNode_s00a1_d400 pair;
            pair.key = key;
            pair.value = value;
            ht->insert((void*)&pair, 0, 0);
        } else {
            float* pv = (float*)((char*)it.node + 4);
            changed = (*pv != value);
            *pv = value;
        }
    }

done:
    if (mpEmitter != 0 && changed) {
        if (!((bool(__thiscall*)(Sound_s00a1_d400*, int, int))VTSLOT(this, 0x20))(this, -1, 1)) {
            ((void(__thiscall*)(void*, u32, float, int))VTSLOT(mpEmitter, 0x2c))(mpEmitter, key, value, 1);
        }
    }
}

// @ 0x00a1df20
bool EA::Audio::Sound::ConnectPrimitive(unsigned int key, EA::Audio::IPrimitive * prim)
{
    Hashtable* ht = (Hashtable*)((char*)static_cast<EA::Audio::IMixable *>(this) + 0x334);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* e = *(void**)((char*)it.node + 4);
        if (e != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(e, 0xc))(e, 0x4e73a43a);
            if (p != 0) {
                if (((void*(__thiscall*)(void*))VTSLOT(e, 0x30))(e) == this) {
                    ((void(__thiscall*)(void*, void*))VTSLOT(p, 0x10))(p, prim);
                    return true;
                }
            }
        }
    }

    void* sys = GetSystemAT();
    void* e = ((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, key);
    if (e == 0)
        return false;

    void* obj = 0;
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* old = *(void**)((char*)it.node + 4);
        if (old != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(old, 0xc))(old, 0x4e73a43a);
            if (p != 0 && ((void*(__thiscall*)(void*))VTSLOT(old, 0x30))(old) == this) {
                ((void(__thiscall*)(void*, void*))VTSLOT(p, 0x10))(p, prim);
                return true;
            }
        }
    }

    {
        void* agg = AllocObject(0x6c);
        if (agg != 0)
            obj = CtorHelper(agg, this);
        if (obj != 0)
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        ((void(__thiscall*)(void*, void*))0x00a16a90)(e, obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(obj, 0x10))(obj, prim);
        ((void(__thiscall*)(void*, int))VTSLOT(obj, 0x2c))(obj, 1);
        void* old = *(void**)((char*)it.node + 4);
        if (obj != old) {
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
            *(void**)((char*)it.node + 4) = obj;
            if (old != 0)
                ((void(__thiscall*)(void*))VTSLOT(old, 4))(old);
        }
        ((void(__thiscall*)(void*))VTSLOT(obj, 4))(obj);
    }
    return true;
}

// @ 0x00a1e1d0
void EA::Audio::Sound::Route(unsigned int a, unsigned int b, EA::Audio::PrimitiveTuning * prim)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0x888);
    HTIter it = ht->find(b);
    void* slot = 0;
    if (it.node == (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* alloc = AllocObject(0x1c);
        void* obj = 0;
        if (alloc != 0)
            obj = CtorHelper(alloc, this);
        ((void(__thiscall*)(void*, u32))0x00fccdd0)(obj, b);
        float f = 1.0f;
        if (!((bool(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4, b, &f))
            ((void(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4, b, &f);
        ((void(__thiscall*)(void*, float))0x00a16fd0)(obj, f);
        ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        PropNode_s00a1_d400 pair;
        pair.key = b;
        pair.value = *(float*)&obj;
        ht->insert((void*)&pair, 0, 0);
        slot = obj;
    } else {
        slot = *(void**)((char*)it.node + 4);
    }

    if (prim != 0) {
        ((void(__thiscall*)(void*, void*))0x00a37080)(prim, slot);
        ((void(__thiscall*)(void*))VTSLOT(prim, 0x10))(prim);
        slot = prim;
    }
    ((void(__thiscall*)(void*, u32, void*))VTSLOT((char*)this + 4, 0x18))((char*)this + 4, a, slot);
}

// @ 0x00a1e320
void* Sound74::ctor_00a1e320(void* a1, void* a2)
{
    u8* t = m;
    FixedPoolBase pool;
    pool.init(t + 0x8c, 0xf0, 0xc, 4, 0);
    pool.mpBegin = t + 0x8c;
    pool.mpEnd = t + 0x17c;
    pool.mnCount = 0xc;
    pool.mpBuckets = t + 0x34;
    u32 buckets = f_00921340(0x15);
    ((HashtableCtor*)t)->ctor(buckets, a1, &a2, &a2, a2, &a2, &pool);
    struct RehashPolicy { float mfMaxLoadFactor; float mfGrowthFactor; u32 mnBucketCount; };
    RehashPolicy policy = { 10000.0f, 2.0f, 0 };
    *(u32*)(t + 0x10) = 0x461c4000;
    *(u32*)(t + 0x14) = 0x40000000;
    *(u32*)(t + 0x18) = 0;
    u32 need = ((RehashCalc*)&policy)->calc(*(u32*)(t + 0x0c));
    if (need > *(u32*)(t + 8))
        f_00a22220(t, need);
    return this;
}

// @ 0x00a1e420
void* Sound74::ctor_00a1e420(void* a1, void* a2)
{
    u8* t = m;
    FixedPoolBase pool;
    pool.init(t + 0xdc, 0x1e0, 0xc, 4, 0);
    pool.mpBegin = t + 0xdc;
    pool.mpEnd = t + 0x2bc;
    pool.mnCount = 0xc;
    pool.mpBuckets = t + 0x34;
    u32 buckets = f_00921340(0x29);
    ((HashtableCtor2*)t)->ctor(buckets, a1, &a2, &a2, a2, &a2, &pool);
    struct RehashPolicy { float mfMaxLoadFactor; float mfGrowthFactor; u32 mnBucketCount; };
    RehashPolicy policy = { 10000.0f, 2.0f, 0 };
    *(u32*)(t + 0x10) = 0x461c4000;
    *(u32*)(t + 0x14) = 0x40000000;
    *(u32*)(t + 0x18) = 0;
    u32 need = ((RehashCalc*)&policy)->calc(*(u32*)(t + 0x0c));
    if (need > *(u32*)(t + 8))
        f_00a22220(t, need);
    return this;
}

// @ 0x00a1e520
Vec4* Vec4::assign_(const Vec4& other)
{
    if (&other == this) return this;
    unsigned n = (unsigned)(other.mpEnd - other.mpBegin);
    unsigned cap = (unsigned)(mpCap - mpBegin);
    if (n > cap) {
        unsigned* p = (unsigned*)DoAssign(n, other.mpBegin, other.mpEnd);
        unsigned* old = mpBegin;
        if (old != 0 && ((int*)old)[-1] != 0) f_00f47380(old);
        mpBegin = p;
        mpCap = p + n;
        mpEnd = p + n;
        return this;
    }
    unsigned m = (unsigned)(mpEnd - mpBegin);
    if (n > m) {
        f_011e0744(mpBegin, other.mpBegin, m * 4);
        char* src = (char*)other.mpBegin + m * 4;
        f_011e0744(mpEnd, src, (unsigned)((char*)other.mpEnd - src));
        mpEnd = mpBegin + n;
        return this;
    }
    f_011e0744(mpBegin, other.mpBegin, (unsigned)((char*)other.mpEnd - (char*)other.mpBegin));
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a1e5f0
void Sound74::AddCell(void* p)
{
    if (p == 0) return;
    VPTR(void, p, 0xd4, void*)(p, this);
    void** end = *(void***)(m + 0xc80);
    if (end < *(void***)(m + 0xc84)) {
        *(void***)(m + 0xc80) = end + 1;
        if (end != 0) *end = p;
    } else {
        ((SimpleVecPush*)(m + 0xc7c))->Insert(end, &p);
    }
    VPTR(void, p, 0)(p);
}

// @ 0x00a1e660
void Sound74::ReleaseAllCells()
{
    void** end = *(void***)(m + 0xc80);
    for (void** it = *(void***)(m + 0xc7c); it != end; ++it) {
        void* p = *it;
        VPTR(void, p, 0x80, int, int)(p, 3, 1);
        VPTR(void, p, 4)(p);
    }
    void** first = *(void***)(m + 0xc7c);
    void** last  = *(void***)(m + 0xc80);
    void** endp  = *(void***)(m + 0xc80);
    f_011e0744(first, last, (unsigned)((char*)endp - (char*)last));
    *(void***)(m + 0xc80) -= (last - first);
}

// @ 0x00a1e6d0
void Sound74::UpdateCells(int param_2, float* param_3)
{
    float* p = (float*)this;
    p[0x31] = p[0x2a];
    p[0x32] = p[0x2b];
    p[0x33] = p[0x2c];
    p[0x35] = 0.0f;
    p[0x34] = 0.0f;
    p[0x36] = 0.0f;
    (void)param_2;

    if ((*(u8*)(p + 0x339) & 0x20) == 0) return;

    float best = 0.0f;
    float sumW = 0.0f, accX = 0.0f, accY = 0.0f, accZ = 0.0f, accR = 0.0f, accN = 0.0f;
    int count = 0;

    {
        void* self = this;
        f_00a80dd0(g_166d9c0, &self);
    }

    float* begin = (float*)g_166d9bc;
    float* end = (float*)g_166d9c0;
    while (begin != end) {
        void* cell = *(void**)begin;
        if (cell != (void*)p) {
            int* ci = (int*)cell;
            f_00a1b020();
            float d = (float)((ci[0x2c] - param_3[2]) * (ci[0x2c] - param_3[2]) +
                              (ci[0x2b] - param_3[1]) * (ci[0x2b] - param_3[1]) +
                              (ci[0x2a] - param_3[0]) * (ci[0x2a] - param_3[0]));
            d = (d < 0.0f) ? -d : d;
            if (d < (float)ci[0x26] * (float)ci[0x16]) {
                float r = VPTR(float, cell, 0xa8, float, int, int, float, int)(
                    cell, d, ci[0x14], ci[0x15], (float)ci[0x16], ci[0x26]);
                if (!(r >= 1e-06f)) { /* skip */ }
                else {
                    if (d < best) best = d;
                    ++count;
                    float w = 1.0f / ((d / r) * (d / r) + 1e-12f);
                    sumW += w;
                    accX += (float)ci[0x2a] * w;
                    accY += (float)ci[0x2b] * w;
                    accZ += (float)ci[0x2c] * w;
                    accR += (float)ci[0x25] * w;
                    accN += (float)ci[0x26] * w;
                }
            }
        }
        ++begin;
    }

    g_166d9c0 = (char*)g_166d9c0 - 4;

    if (count != 0) {
        float inv = 1.0f / sumW;
        p[0x31] = inv * accX;
        p[0x32] = inv * accY;
        p[0x33] = inv * accZ;
        p[0x35] = (float)VPTR(float, this, 0xa8, int, int, int, int, float)(
            this, (int)best, ((int*)this)[0x14], ((int*)this)[0x15], ((int*)this)[0x16], inv * accN);
        p[0x34] = inv * accR;
        p[0x36] = inv * accN;
    }

    for (void** it = (void**)g_166d9bc; it != (void**)g_166d9c0; ++it)
        VPTR(void, *it, 0x8c)(*it);
    f_011e0744(g_166d9bc, g_166d9c0, 0);
}

// @ 0x00a1eb50
char Sound74::ConfigureNote()
{
    void* props = m + 4;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x66ef9aba)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0xe4dd1818)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x0cd928a9)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x07f28acc))
        *(u32*)(m + 0x334) = 0x556fea66;

    void* sys = f_00a206f0();
    void* zone = *(void**)(m + 0x2dc);
    if (zone != 0) {
        *(void**)(m + 0x2dc) = 0;
        VPTR(void, zone, 4)(zone);
    }
    if (!VPTR(char, sys, 0x18c, void*, void*)(sys, m + 0x1c, m + 0x2dc))
        return 0;

    float a = 0.0f, c = 0.0f;
    VPTR(void, this, 0xac, float*)(this, &a);
    VPTR(void, this, 0xac, float*)(this, &a);
    VPTR(void, this, 0xac, unsigned, float*)(this, 0x0cd928a9, &c);
    float scale = c * 0.001f;
    (void)scale;

    float out = 0.0f;
    if (!f_00a1b160(*(void**)(m + 0x2dc), (int)a, 0, &out))
        return 0;
    float v = 0.0f * 0.007874016f;
    float r = f_00a1ac70(this, v);
    (void)r;
    return 1;
}

// @ 0x00a1eef0
void Sound74::Teardown()
{
    unsigned char* t = m;

    // hashtable #1: iterate nodes, release matching owners, free nodes.
    {
        void** nodes = *(void***)(t + 0x33c);
        unsigned n = *(unsigned*)(t + 0x340);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            if (VPTR(void*, obj, 0x30)(obj) == (void*)t)
                VPTR(void, obj, 0x14)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a24480(t + 0x338, *(int*)(t + 0x340), *(int*)(t + 0x33c));
        *(int*)(t + 0x338 + 0x0c) = 0;
    }

    // hashtable #2
    {
        void** nodes = *(void***)(t + 0x51c);
        unsigned n = *(unsigned*)(t + 0x520);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            VPTR(void, obj, 0x14)(obj);
            VPTR(void, obj, 4)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a1b6c0(t + 0x518, *(int*)(t + 0x520), *(int*)(t + 0x51c));
        *(int*)(t + 0x518 + 0x0c) = 0;
    }

    // release vector at +0xbf8
    {
        void** end = *(void***)(t + 0xbfc);
        for (void** it = *(void***)(t + 0xbf8); it != end; ++it) {
            void* o = *it;
            VPTR(void, o, 0x14)(o);
            VPTR(void, o, 4)(o);
        }
        char* e = (char*)*(void***)(t + 0xbfc);
        char* b = (char*)*(void***)(t + 0xbf8);
        f_011e0744(b, e, 0);
        unsigned nn = (unsigned)(e - b) >> 2;
        *(int*)(t + 0xbfc) += (-(int)nn) * 4;
    }

    // hashtable #3
    {
        void** nodes = *(void***)(t + 0x88c);
        unsigned n = *(unsigned*)(t + 0x890);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            VPTR(void, obj, 0x14)(obj);
            VPTR(void, obj, 4)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a1b6c0(t + 0x888, *(int*)(t + 0x890), *(int*)(t + 0x88c));
        *(int*)(t + 0x888 + 0x0c) = 0;
    }

    // primary object at +0xc38
    if (*(void**)(t + 0xc38) != 0) {
        void** end = *(void***)(t + 0xc40);
        for (void** it = *(void***)(t + 0xc3c); it != end; ++it) {
            void* o = *it;
            void* sys = f_00a206f0();
            void* found = VPTR(void*, sys, 0x11c, void*)(sys, o);
            if (found != 0)
                VPTR(void, found, 0x1c, void*, void*)(found, *(void**)(t + 0xce8), *(void**)(t + 0xc38));
        }
        void* prim = *(void**)(t + 0xc38);
        VPTR(void, prim, 0x14)(prim);
        prim = *(void**)(t + 0xc38);
        if (prim != 0) {
            *(void**)(t + 0xc38) = 0;
            VPTR(void, prim, 4)(prim);
        }
    }
}

// @ 0x00a1f180
void Sound74::SubscribeToGroupsFromSymbol(const char* symbol)
{
    if (symbol == 0 || *symbol == 0) return;
    while (!isalnum((char)*symbol)) ++symbol;

    char c = *symbol;
    while (c != 0) {
        const char* wordEnd = symbol;
        if (isalnum((char)c)) {
            do { ++wordEnd; } while (isalnum((char)*wordEnd));
        }

        unsigned hash = 0x811c9dc5;
        while (symbol < wordEnd) {
            hash = hash * 0x1000193 ^ (unsigned)tolower((unsigned char)*symbol);
            ++symbol;
        }

        unsigned* end = *(unsigned**)(m + 0x2e4);
        if (end < *(unsigned**)(m + 0x2e8)) {
            unsigned* old = end;
            *(unsigned**)(m + 0x2e4) = old + 1;
            if (old != 0) *old = hash;
        } else {
            f_00899480(end, &hash);
        }

        void* sys = f_00a206f0();
        VPTR(void, sys, 0x108, unsigned, void*)(sys, hash, (void*)(m + 4));

        c = *symbol;
        if (c == 0) return;
        while (!isalnum((char)c)) {
            ++symbol;
            c = *symbol;
            if (c == 0) return;
        }
        c = *symbol;
    }
}

// @ 0x00a1f3e0
void Sound_AssignC7C(COWVec* self, COWVec* other)
{
    void* a = self->mpBegin;
    void* b = other->mpBegin;
    bool aShared = (a == 0) || (*(int*)((char*)a - 4) != 0);
    bool bShared = (b == 0) || (*(int*)((char*)b - 4) != 0);
    if (aShared && bShared) {
        self->mpBegin = b;
        other->mpBegin = a;
        void* t = self->mpEnd;      self->mpEnd      = other->mpEnd;      other->mpEnd      = t;
        t       = self->mpCapacity; self->mpCapacity = other->mpCapacity; other->mpCapacity = t;
        return;
    }

    COWVec tmp;
    int n = (int)((char*)self->mpEnd - (char*)self->mpBegin);
    VecBool_assign_(&tmp, (u32)n >> 2, (char*)self + 0xc);
    void* r = VecBool_DoInsertValue(&tmp, self->mpBegin, (u32)n);
    (void)r;
    Vec4_assign_(self, other);
    Vec4_assign_(other, &tmp);
    if (tmp.mpBegin != 0 && *(int*)((char*)tmp.mpBegin - 4) != 0)
        OperatorDelete(tmp.mpBegin);
}

// @ 0x00a1f4d0
EA::Audio::Sound::~Sound()
{
    // three vtable slots of the second vtable family.
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // file-name string at 0x1dfc: free when capacity-begin > 1.
    void* p = *(void**)((char*)this + 0x1dfc);
    if ((char*)this + 0x1e04 - (char*)p > 1 && p != 0)
        OperatorDelete(p);

    // the five ResponseCurve members, each a fixed_vector at offset +0x00
    // with its inline buffer at +0x10.
    void* q;
    q = *(void**)((char*)this + 0x1a7c);
    if (q != 0 && q != *(void**)((char*)this + 0x1a8c)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x1718);
    if (q != 0 && q != *(void**)((char*)this + 0x1728)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x13b4);
    if (q != 0 && q != *(void**)((char*)this + 0x13c4)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x1050);
    if (q != 0 && q != *(void**)((char*)this + 0x1060)) OperatorDelete(q);
    q = *(void**)((char*)this + 0xcec);
    if (q != 0 && q != *(void**)((char*)this + 0xcfc)) OperatorDelete(q);

    // mpConfiguration (0xc90): release the refcounted config object.
    void* cfg = *(void**)((char*)this + 0xc90);
    if (cfg != 0)
        ((void(__thiscall*)(void*))VTSLOT(cfg, 4))(cfg);

    // mRoutedInstanceIds (0xc7c): copy-on-write vector<bool>.
    void* cv = *(void**)((char*)this + 0xc7c);
    if (cv != 0 && *(int*)((char*)cv - 4) != 0)
        OperatorDelete(cv);

    // mAtmosphericResponse curve buffer (0xc3c), inline buffer at 0xc4c.
    q = *(void**)((char*)this + 0xc3c);
    if (q != 0 && q != *(void**)((char*)this + 0xc4c)) OperatorDelete(q);

    // mpAtmosphericResponse (0xc38): release.
    void* p38 = *(void**)((char*)this + 0xc38);
    if (p38 != 0)
        ((void(__thiscall*)(void*))VTSLOT(p38, 4))(p38);

    // mPrimitives (0xbf8): fixed_vector<IPrimitive*>, inline buffer 0xc08.
    q = *(void**)((char*)this + 0xbf8);
    if (q != 0 && q != *(void**)((char*)this + 0xc08)) OperatorDelete(q);

    // the inline fixed hashtables: mGroupMap (0x888), mSampleMap (0x518)
    // and mPropertySet (0x338, whose teardown uses PHTable::FreeBuckets).
    TeardownFixedHash((FixedHash*)((char*)this + 0x888), false);
    TeardownFixedHash((FixedHash*)((char*)this + 0x518), false);
    TeardownFixedHash((FixedHash*)((char*)this + 0x338), true);

    // mGroups (0x2e0): fixed_vector<u32,10>, inline buffer at 0x2f0.
    q = *(void**)((char*)this + 0x2e0);
    if (q != 0 && q != *(void**)((char*)this + 0x2f0)) OperatorDelete(q);

    // mpGroupSubscriptions (0x2dc): release.
    void* p2dc = *(void**)((char*)this + 0x2dc);
    if (p2dc != 0)
        ((void(__thiscall*)(void*))VTSLOT(p2dc, 4))(p2dc);

    // mpMixable (0x2d8): intrusive refcount.  On the last reference the
    // object is told Release(1) through vtable slot 0, then kept alive.
    void* p2d8 = *(void**)((char*)this + 0x2d8);
    if (p2d8 != 0) {
        int nRef = *(int*)((char*)p2d8 + 4) - 1;
        *(int*)((char*)p2d8 + 4) = nRef;
        if (nRef == 0) {
            *(int*)((char*)p2d8 + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(p2d8, 0))(p2d8, 1);
        }
    }

    // mNodeMap (0xf8): inline fixed hashtable.
    TeardownFixedHash((FixedHash*)((char*)this + 0xf8), false);

    // the embedded configuration object at 0xe4.
    ((SubE4*)((char*)this + 0xe4))->dtor();

    // mpEmitter (0x44): release.
    void* p44 = *(void**)((char*)this + 0x44);
    if (p44 != 0)
        ((void(__thiscall*)(void*))VTSLOT(p44, 4))(p44);

    // mSampleName (0x28): free the heap buffer when capacity-begin > 1.
    void* p28 = *(void**)((char*)this + 0x28);
    if ((char*)*(void**)((char*)this + 0x30) - (char*)p28 > 1 && p28 != 0)
        OperatorDelete(p28);

    // mName (0x18).
    void* p18 = *(void**)((char*)this + 0x18);
    if ((char*)*(void**)((char*)this + 0x20) - (char*)p18 > 1 && p18 != 0)
        OperatorDelete(p18);

    // the IEventModifier vtable slot is reset last.
    *(void**)((char*)this + 8) = (void*)0x13ef094;
}

// @ 0x00a1f840
void Sound_s00a1_f2b0::CreatePrimitive(u32 id)
{
    float gain = 0.0f;
    char ok = ((char(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 0xe4, 0x30))((char*)this + 0xe4, id, &gain);
    if (!ok)
        return;

    void* sys = GetSystemAT_s00a1_f2b0();
    if (!((char(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, id)) {
        ((void(__thiscall*)(void*, u32, float*, int))VTSLOT((char*)this + 4, 0xc))((char*)this + 4, id, &gain, 1);
        return;
    }

    void* prim = AllocObject(0x1c);
    if (prim)
        prim = CtorHelper(prim, this);
    SetCurveGain(prim, gain);
    ((void(__thiscall*)(void*))VTSLOT(prim, 0))(prim);

    VecPtr* v = (VecPtr*)((char*)this + 0xbf8);
    if (v->mpEnd < v->mpCapacity)
        *(void**)v->mpEnd = prim, v->mpEnd = (char*)v->mpEnd + 4;
    else
        VectorGrow(v->mpEnd, &prim);

    ((void(__thiscall*)(void*, u32, void*))VTSLOT((char*)this + 4, 0x18))((char*)this + 4, id, prim);
}

// @ 0x00a1f960
void Sound_s00a1_f2b0::CopyStateFrom(Sound_s00a1_f2b0* src)
{
    ((void(__thiscall*)(void*, int))VTSLOT(this, 0xd4))(this, 0);

    void* se = *(void**)((char*)this + 0x44);
    void* oe = *(void**)((char*)src  + 0x44);
    if (se != oe) {
        if (oe)
            ((void(__thiscall*)(void*))VTSLOT(oe, 0))(oe);
        *(void**)((char*)this + 0x44) = oe;
        if (se)
            ((void(__thiscall*)(void*))VTSLOT(se, 4))(se);
    }
    void* se2 = *(void**)((char*)src + 0x44);
    if (se2) {
        *(void**)((char*)src + 0x44) = 0;
        ((void(__thiscall*)(void*))VTSLOT(se2, 4))(se2);
    }

    void* so = *(void**)((char*)src  + 0x2d8);
    void* mo = *(void**)((char*)this + 0x2d8);
    if (so != mo) {
        if (so)
            ++*(int*)((char*)so + 4);
        *(void**)((char*)this + 0x2d8) = so;
        if (mo && --*(int*)((char*)mo + 4) == 0) {
            *(int*)((char*)mo + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(mo, 0))(mo, 1);
        }
    }
    void* so2 = *(void**)((char*)src + 0x2d8);
    if (so2) {
        *(void**)((char*)src + 0x2d8) = 0;
        if (--*(int*)((char*)so2 + 4) == 0) {
            *(int*)((char*)so2 + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(so2, 0))(so2, 1);
        }
    }

    *(u32*)((char*)this + 0x1de0) = *(u32*)((char*)src + 0x1de0);
    VecBool_DoInsertValue((char*)this + 0x1de4, (char*)src + 0x1de4,
                          *(u32*)((char*)this + 0x1dec) * 4);
    Sound_AssignC7C((COWVec*)((char*)this + 0xc7c), (COWVec*)((char*)src + 0xc7c));

    void* e = *(void**)((char*)this + 0x44);
    if (e)
        ((void(__thiscall*)(void*, void*))VTSLOT(e, 0x38))(e, (char*)this + 0xe4);

    if (*(u32*)((char*)src + 0xce4) & 0x20)
        *(u32*)((char*)this + 0xce4) |= 0x20;
    else
        *(u32*)((char*)this + 0xce4) &= ~0x20u;

    void* sys = GetSystemAT_s00a1_f2b0();
    ((void(__thiscall*)(void*, void*))VTSLOT(sys, 0x70))(sys, this);
    *(u32*)((char*)this + 0xce4) |= 8;
    *(float*)((char*)this + 0x68) = -1.0f;
}

// @ 0x00a1fab0
void PrimHashTable_ctor(void* self, void* a, void* b)
{
    Pool_init((char*)self + 0x8c, (char*)self + 0x8c, 0xf0, 0xc, 4, 0);
    u32 n = Pool_alloc(0x15);
    HashMap_ctor(self, a, b, b, b, b, (char*)self + 0x8c);
    (void)n;
    *(float*)((char*)self + 0x10) = 1.0e4f;
    *(float*)((char*)self + 0x14) = 2.0f;
    *(u32*)((char*)self + 0x18) = 0;
    u32 want = Pool_next(*(u32*)((char*)self + 0xc));
    if (want > *(u32*)((char*)self + 8))
        HTable28_Rehash(self, want);
}

// @ 0x00a1fbb0
Sound_s00a1_f2b0::Sound_s00a1_f2b0()
{
    // first vtable family (ITickable / IMixable / IEventModifier).
    *(void**)((char*)this + 0) = (void*)0x144934c;
    *(void**)((char*)this + 4) = (void*)0x1449430;
    *(void**)((char*)this + 8) = (void*)0x13ef094;

    // atomic refcount at 0xc, then the intrusive-list links (0x14 before 0x10).
    _InterlockedExchange((long*)((char*)this + 0xc), 0);
    *(u32*)((char*)this + 0x14) = 0;
    *(u32*)((char*)this + 0x10) = 0;

    // second vtable family.
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // mName (+0x18) and mSampleName (+0x28) point at the shared empty string.
    *(void**)((char*)this + 0x18) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x20) = (void*)0x1667bad;
    *(void**)((char*)this + 0x28) = (void*)0x1667bac;
    *(void**)((char*)this + 0x2c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x30) = (void*)0x1667bad;

    // ids and the emitter handle.
    *(u32*)((char*)this + 0x38) = 0;
    *(u32*)((char*)this + 0x3c) = 0;
    *(u32*)((char*)this + 0x40) = 0;
    *(u32*)((char*)this + 0x44) = 0;

    // gain / distance / pitch tuning block (the original reads the shared
    // constants at 0x13eb1bc, 0x13f11c8 and 0x145284c).
    CopyFloat((float*)((char*)this + 0x68), (const float*)0x13eb1bc);
    CopyFloat((float*)((char*)this + 0x6c), (const float*)0x13f11c8);
    *(float*)((char*)this + 0x48) = 0.0f;
    *(float*)((char*)this + 0x4c) = 0.0f;
    *(float*)((char*)this + 0x50) = 1.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x5c) = 1.0f;
    *(float*)((char*)this + 0x60) = 0.0f;
    *(float*)((char*)this + 0x64) = 0.0f;
    *(float*)((char*)this + 0x70) = 1.0f;
    *(float*)((char*)this + 0x74) = 0.0f;
    CopyFloat((float*)((char*)this + 0x78), (const float*)0x145284c);
    *(float*)((char*)this + 0x7c) = 0.0f;
    *(float*)((char*)this + 0x80) = 1.0f;
    *(float*)((char*)this + 0x84) = 1.0f;
    *(float*)((char*)this + 0x88) = 1.0f;
    *(float*)((char*)this + 0x8c) = 0.0f;
    *(float*)((char*)this + 0x90) = 0.0f;
    *(float*)((char*)this + 0x94) = 0.0f;
    *(float*)((char*)this + 0x98) = 1.0f;

    // flags.
    *(u8*)((char*)this + 0x9c) = 0;
    *(u8*)((char*)this + 0x9d) = 0;
    *(u8*)((char*)this + 0x9e) = 0;
    *(u8*)((char*)this + 0x9f) = 1;
    *(u8*)((char*)this + 0xa0) = 0;
    *(u32*)((char*)this + 0xa4) = 0;

    // position / doppler vectors and the stop-reason block; the original
    // reloads the three shared runtime floats at 0x166d9e0/4/8 for each slot.
    CopyFloat((float*)((char*)this + 0xa8), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xac), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xb0), (const float*)0x166d9e8);
    CopyFloat((float*)((char*)this + 0xb4), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xb8), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xbc), (const float*)0x166d9e8);
    *(u8*)((char*)this + 0xc0) = 0;
    CopyFloat((float*)((char*)this + 0xc4), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xc8), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xcc), (const float*)0x166d9e8);
    *(float*)((char*)this + 0xd0) = 1.0f;
    *(float*)((char*)this + 0xd4) = 1.0f;
    *(float*)((char*)this + 0xd8) = 0.0f;
    *(u32*)((char*)this + 0xdc) = 0;
    *(u32*)((char*)this + 0xe0) = 0;

    // the embedded configuration object.
    ((SubE4*)((char*)this + 0xe4))->ctor();

    // mGroups (0xf8): inline fixed_vector<u32,10> (buffer at +0x184),
    // followed by the intrusive handles at 0x2d8/0x2dc and the mPrimitives
    // vector header pointing at its inline buffer at 0x2f8.
    char dummy = 0;
    ((FixedVecCtor*)((char*)this + 0xf8))->ctor(&dummy, &dummy);

    *(void**)((char*)this + 0x2d8) = 0;
    *(void**)((char*)this + 0x2dc) = 0;
    void* vec = (char*)this + 0x2f8;
    *(void**)((char*)this + 0x2f0) = vec;
    *(void**)((char*)this + 0x2e4) = vec;
    *(void**)((char*)this + 0x2e0) = vec;
    *(void**)((char*)this + 0x2e8) = (char*)vec + 0x28;

    // mPropertySet (0x338): inline fixed_hash_map with its policy fields.
    *(u32*)((char*)this + 0x320) = 0;
    *(float*)((char*)this + 0x324) = 0.0f;
    *(float*)((char*)this + 0x328) = 0.0f;
    *(float*)((char*)this + 0x32c) = 0.0f;
    *(u32*)((char*)this + 0x330) = 2;
    *(u32*)((char*)this + 0x334) = 0xee8347b0;
    ((FixedHashMapCtor*)((char*)this + 0x338))->ctor(&dummy, &dummy);

    // mGroupMap (0x518) and mSampleMap (0x888).
    ((FixedVecCtor2*)((char*)this + 0x518))->ctor(&dummy, &dummy);
    ((FixedVecCtor2*)((char*)this + 0x888))->ctor(&dummy, &dummy);

    // mPrimitives (0xbf8): fixed_vector<IPrimitive*>, inline buffer 0xc10.
    void* p = (char*)this + 0xc10;
    *(void**)((char*)this + 0xc08) = p;
    *(void**)((char*)this + 0xbfc) = p;
    *(void**)((char*)this + 0xbf8) = p;
    *(void**)((char*)this + 0xc00) = (char*)p + 0x28;
    *(void**)((char*)this + 0xc38) = 0;

    // mRoutedInstanceIds buffer chain (0xc3c): inline buffer 0xc54.
    p = (char*)this + 0xc54;
    *(void**)((char*)this + 0xc4c) = p;
    *(void**)((char*)this + 0xc40) = p;
    *(void**)((char*)this + 0xc3c) = p;
    *(void**)((char*)this + 0xc44) = (char*)p + 0x28;

    *(void**)((char*)this + 0xc7c) = 0;
    *(void**)((char*)this + 0xc80) = 0;
    *(void**)((char*)this + 0xc84) = 0;
    *(void**)((char*)this + 0xc90) = 0;

    // the atmospheric / filter / pitch block starting at 0xcb0.
    *(u8*)((char*)this + 0xcb0) = 0;
    *(float*)((char*)this + 0xcc0) = 0.0f;
    *(float*)((char*)this + 0xcc4) = 0.0f;
    *(u32*)((char*)this + 0xc94) = 0;
    *(u32*)((char*)this + 0xc98) = 0;
    *(u32*)((char*)this + 0xc9c) = 0;
    *(u32*)((char*)this + 0xca0) = 0;
    *(u32*)((char*)this + 0xca4) = 0;
    *(u32*)((char*)this + 0xca8) = 0;
    *(float*)((char*)this + 0xcb8) = 1.0f;
    *(float*)((char*)this + 0xcbc) = 0.0f;
    *(u32*)((char*)this + 0xcac) = 0;
    *(double*)((char*)this + 0xcc8) = 0.0;
    *(float*)((char*)this + 0xcd0) = 0.0f;
    *(u8*)((char*)this + 0xcd4) = 0;
    *(u8*)((char*)this + 0xcd5) = 0;
    *(u32*)((char*)this + 0xcd8) = 0xffffffff;
    *(u32*)((char*)this + 0xcdc) = 0;
    *(u32*)((char*)this + 0xce0) = 1;
    *(u32*)((char*)this + 0xce4) = 0;
    *(u32*)((char*)this + 0xce8) = 0x25df0108;

    // the five ResponseCurve members (0x364 bytes apart).
    ((ResponseCurve_s00a1_f2b0*)((char*)this + 0xcec))->ctor();
    ((ResponseCurve_s00a1_f2b0*)((char*)this + 0x1050))->ctor();
    ((ResponseCurve_s00a1_f2b0*)((char*)this + 0x13b4))->ctor();
    ((ResponseCurve_s00a1_f2b0*)((char*)this + 0x1718))->ctor();
    ((ResponseCurve_s00a1_f2b0*)((char*)this + 0x1a7c))->ctor();

    *(u32*)((char*)this + 0x1dec) = 5;
    *(void**)((char*)this + 0x1dfc) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1e00) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1e04) = (void*)0x1667bad;
    *(u32*)((char*)this + 0x1e0c) = 3;
    *(u32*)((char*)this + 0xce4) = 0;

    // let the configuration object refresh its listeners, then clear the
    // intrusive-list links once more (the stores happen before the call).
    void* pE4 = (char*)this + 0xe4;
    void* vtbl = *(void**)pE4;
    *(u32*)((char*)this + 0x14) = 0;
    *(u32*)((char*)this + 0x10) = 0;
    ((void(__thiscall*)(void*))((void**)vtbl)[0])(pE4);
}

// @ 0x00a20060
bool Sound_s00a2_0060::ConfigureSound()
{
    ((void (__thiscall*)(void*))(vt[0x94 / 4]))(this);
    ISys* sys = GetSystemAT_s00a2_0060();
    if (sys == 0)
        return false;
    IConfig* cfg = (IConfig*)((char*)this + 0xe4);
    at<u32>(0x40) = at<u32>(0x38);
    cfg->GetInt(0x51997db2, &at<u32>(0xcdc));
    cfg->GetInt(0xd9ec19d6, &at<u32>(0xce0));
    cfg->GetBool(0xfd9003a3, &at<u8>(0x9f));
    if (cfg->GetFloat(0xb1f42539, &at<u8>(0xcd0)))
        at<u32>(0xce4) |= 0x400;
    u8 flag;
    if (cfg->GetBool(0xd1daef42, &flag) && flag)
        at<u32>(0xce4) |= 0x1000;
    if (cfg->GetBool(0x6257eb2a, &flag) && flag)
        at<u8>(0xcd4) = 1;
    if (cfg->GetBool(0x3c10c7b9, &flag) && flag)
        at<u8>(0xcd5) = 1;
    VThis<0x74>(this, 0x2406a047);
    VThis<0x74>(this, 0x25df0108);
    VThis<0x74>(this, 0x0f616b72);
    VThis<0x74>(this, 0x03593710);
    VThis<0x74>(this, 0x29e8b9f8);
    VThis<0x74>(this, 0x8fc9308e);
    VThis<0x74>(this, 0x56e7c242);
    VThis<0x74>(this, 0x71bc3009);
    VThis<0x74>(this, 0x98ac8996);
    VThis<0x74>(this, 0xe8ab99b9);
    VThis<0x74>(this, 0x8fc9308e);
    VThis<0x74>(this, 0x393f7f7d);
    VThis<0x74>(this, 0x49eb68db);
    VThis<0x74>(this, 0x6eb7a717);
    VThis<0x74>(this, 0x9d554d95);
    VThis<0x74>(this, 0xc57f4567);
    u8 flag2;
    if (cfg->GetBool(0x12d2a4d4, &flag2)) {
        if (flag2)
            at<u8>(0xc0) |= 8;
        else
            at<u8>(0xc0) &= 0xf7;
    }
    cfg->GetBool(0x6dd08218, &at<u8>(0x9d));
    cfg->GetBool(0xba134192, &at<u8>(0xa0));
    cfg->GetInt(0xbaf7f4f9, &at<u32>(0x330));
    cfg->SetStr(0x07f28acc, &at<u32>(0x334));
    cfg->GetInt(0xed1f36d5, &at<u32>(0xa4));
    cfg->GetInt(0x6610c2bd, &at<u32>(0xe0));
    cfg->GetFloat(0xc742ceb8, &at<u32>(0x60));
    {
        u32 l18, l20;
        if (cfg->GetList12(0x701ed91e, &l20, &l18)) {
            Rc*& pl = at<Rc*>(0x2d8);
            Rc* old = pl;
            if (old) {
                pl = 0;
                int n = (*(volatile int*)&old->rc += -1);
                if (n == 0) {
                    old->rc = 1;
                    ((void (__thiscall*)(void*, int))(((void***)old)[0][0]))(old, 1);
                }
            }
            sys->Slot160(at<u32>(0x38), (int)l18, (int)l20, &pl);
        } else {
            cfg->SetStr(0x701ed91e, &at<u32>(0x2d8));
        }
    }
    static u32 kA = Id(0x0f70317c);
    static u32 kB = Id(0x09d0b38e);
    at<ResponseCurve>(0xcec).InitFromConfiguration(cfg, kA);
    at<ResponseCurve>(0x1050).InitFromConfiguration(cfg, kB);
    at<ResponseCurve>(0x13b4).InitFromConfiguration(cfg, 0x173c2710);
    {
        int cnt; void* data;
        if (cfg->GetPair(0x9bfc37ac, &data, &cnt)) {
            at<u32>(0xce4) |= 0x4000;
            at<ResponseCurve>(0x1718).SetResponseCurveData(data, cnt >> 1);
        }
    }
    if (at<Playlist*>(0x2d8)) {
        if (at<Playlist*>(0x2d8)->Ok())
            at<u32>(0x40) = at<Playlist*>(0x2d8)->Id();
    }
    {
        u32 count; u32* arr;
        if (cfg->GetList12(0x7cb81a35, &count, &arr) && count) {
            GroupVec& groups = at<GroupVec>(0x2e0);
            while (count) {
                --count;
                u32 id = arr[0];
                arr += 3;
                sys->Slot108(id, (char*)this + 4);
                groups.push_back(id);
            }
        }
    }
    {
        u32 count; u32* arr;
        if (cfg->GetList8(0xa095ea05, &count, &arr)) {
            at<BitVec>(0xc3c).Resize(count);
            memcpy_(*(void**)&at<BitVec>(0xc3c), arr, count * 4);
            cfg->GetInt(0xa25a9f30, &at<u32>(0xce8));
            at<ResponseCurve>(0x1a7c).InitFromConfiguration(cfg, 0x9b3918c4);
            Fx* fx = new Fx(this);
            Fx* old = at<Fx*>(0xc38);
            if (fx != old) {
                if (fx) fx->AddRef();
                at<Fx*>(0xc38) = fx;
                if (old) old->Release();
            }
            at<Fx*>(0xc38)->SetLevel(1.0f);
            while (count--) {
                u32 id = *arr++;
                void* o = GetSystemAT_s00a2_0060()->Slot11c(id);
                if (o)
                    ((void (__thiscall*)(void*, u32, void*))((*(void***)o)[0x18 / 4]))(o, at<u32>(0xce8), at<Fx*>(0xc38));
            }
        }
    }
    void* p = cfg->GetPtr(0x2fe09c83);
    if (p)
        at<u32>(0x320) = GetSystemAT_s00a2_0060()->Slot0f0(p);
    ((void (__thiscall*)(void*))(vt[0xb0 / 4]))(this);
    return true;
}

// @ 0x00a37c10
int EA::Audio::Sound::Release()
{
    char* base = (char*)this + 8;
    volatile long* rc = (volatile long*)(base + 4);
    int n = (int)_InterlockedDecrement(rc);
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (base) {
            void** vt = *(void***)base;
            ((void (__thiscall*)(void*, int))vt[0])(base, 1);
        }
        return 0;
    }
    return n;
}
