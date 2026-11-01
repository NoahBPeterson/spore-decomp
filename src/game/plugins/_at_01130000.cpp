// src/game/plugins/_at_01130000.cpp -- migrated from slice(s) s0113baf0, s0113a8b0, s011399e0, s011388f0 by tools/migrate/rewrite.py
// Object file: plugins/_at_01130000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/DecoderRegistry.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/TimerManager.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_one;                          // 0x01485720
extern void* g_p15bbb20;                           // 0x015bbb20
extern void* g_pTimerList;                         // 0x016e6288
extern void* g_pTimerList2;                        // 0x016e628c
extern "C" int  SNDSYS_restore(void);                          // 0x0113ef00
extern "C" void FUN_0112d590(void** a, void** b, float g, int c, int d, int e); // 0x0112d590
extern "C" void* FUN_011373c0(void);                           // 0x011373c0
extern "C" void* operator_new_arr(unsigned sz, int a, unsigned n); // 0x011e073e
extern "C" int strcmp(const char*, const char*);
#include <xmmintrin.h>
#include <math.h>
#include <string.h>

// ---- items of slice s011388f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned short u16;
template <class T> static inline T& A(void* p, int off) { return *(T*)((char*)p + off); }
static inline char* RING(void* sys) { return *(char**)((char*)sys + 0x20) + *(unsigned*)((char*)sys + 0xb4); }
namespace rw {
namespace audio {
namespace core {
class System_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class Decoder;
}
}
}
namespace rw {
namespace audio {
namespace core {
class DecoderRegistry_s0113_88f0;
}
}
}
namespace rw {
namespace audio {
namespace core {
class TimerHandle_s0113_88f0 { public:
    void* mItemHandle; void* mpCallback; void* mpContext; char* mpName;
    unsigned int mCpuTicks; unsigned char mStage; unsigned char mTimerVisibility; unsigned char pad16[2];
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class System_s0113_88f0 { public:
    char pad00[0x20]; char* mpCommandBuffer; char pad24[0x90]; unsigned int mCommandIndex; // +0xb4
void* Alloc(int size, const char* name, int align, int alloc);
void Free(void* p, int alloc);
void RemoveTimer(TimerHandle_s0113_88f0* t);
int Lock();
int Unlock();
DecoderRegistry_s0113_88f0* GetDecoderRegistry();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class Decoder { public:
    char pad00[0x20]; unsigned short mNumChannels;
char FUN_0114c8c0(char*, unsigned, int, int, void*, int);
void FUN_01133f40();
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class DecoderRegistry_s0113_88f0 {
    public: int FUN_01133ed0(int);
    Decoder* DecoderFactory(int, int, int, System_s0113_88f0*);  // 0x01133fc0 (rw::audio::core::DecoderRegistry::DecoderFactory)
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct AudioObj {
    void F_d00();              // 0x01138d00
    void F_000(int, int*);     // 0x01139000
    void F_0b0();              // 0x011390b0
    void F_2c0(int, int*);     // 0x011392c0
    void F_4b0();              // 0x011394b0
    void F_660(int, int*);     // 0x01139660
    void F_730();              // 0x01139730
    void F_820(int, int*);     // 0x01139820
    void F_8b0();              // 0x011398b0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class SubMix_s0113_88f0 { public:
    void FUN_01137420(int, int);   // 0x01137420
    void FUN_01137450(void*);      // 0x01137450
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct DelayLine {
    void Release();                // 0x0114d770
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class PlugIn_s0112_ce20 { public:
    PlugIn_s0112_ce20* Initialize_SndPlayer1();   // 0x0112dbb0
};
}
}
}
extern rw::audio::core::System_s0113_88f0* g_pSystem;         // 0x016e61a8
extern const float g_one;                          // 0x01485720
extern void* g_p15bbb20;                           // 0x015bbb20
extern void* g_pTimerList;                         // 0x016e6288
extern void* g_pTimerList2;                        // 0x016e628c
extern "C" int  SNDSYS_restore(void);                          // 0x0113ef00
extern "C" void FUN_0112d590(void** a, void** b, float g, int c, int d, int e); // 0x0112d590
extern "C" void* FUN_011373c0(void);                           // 0x011373c0
extern "C" void* operator_new_arr(unsigned sz, int a, unsigned n); // 0x011e073e
extern "C" int strcmp(const char*, const char*);
// ---- items of slice s011388f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern rw::audio::core::System_s0113_88f0* g_pSystem;         // 0x016e61a8

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace rw { namespace audio { namespace core { int __cdecl FUN_01139500(void* rec); }}}  // 0x01139500 (stays in the slice: not this object's)

// ---- items of slice s011399e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete__(void*);            // 0x00f47380
extern "C" void EA_Audio_sys_gui(void);              // 0x00c2e4e0
namespace rw {
namespace audio {
namespace core {
class DelayLine_s0113_99e0 { public:
    int  Init(int a, int b, int size);   // 0x0114d7b0  thiscall, ret 0xc
    void FUN_0114d730();                 // 0x0114d730  ctor
    void FUN_0114d770();                 // 0x0114d770  Release
    void FUN_0114d9d0(int);              // 0x0114d9d0  Reset, ret 4
    int  FUN_0114d840(int);              // 0x0114d840  Resize, ret 4
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class FastFirEngine { public:
    int  Reset();                                    // 0x0114e580
    int  Configure(int, int, int, int, int, int, int);// 0x0114e5e0
    int  FUN_0114e210(int, float);                   // 0x0114e210
    int  FUN_0114e230(int);                          // 0x0114e230
    int  FUN_0114e300();                             // 0x0114e300
    int  FUN_0114e340();                             // 0x0114e340
    int  FUN_0114e370(int, int);                     // 0x0114e370
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct RevObj {
    int    F_9e0(int, float);        // 0x011399e0
    bool   F_d60(float*);            // 0x01139d60
    RevObj* F_e10();                 // 0x01139e10
    void   F_eb0();                  // 0x01139eb0
    void   F_f20();                  // 0x01139f20
    int    F_fe0(void*);             // 0x01139fe0
    void   F_7a0(int);               // 0x0113a7a0
    RevObj* F_840(u8);               // 0x0113a840
};
}
}
}
// ---- items of slice s011399e0 end

// ---- items of slice s0113a8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_015bc9e4;                 // 0x15bc9e4  Pan3D default angle X (degrees)
extern float g_negmask;                  // 0x13eb8b0  sign-bit mask (0x80000000 x4); first lane = -0.0f
extern float g_real_one;                 // 0x1485720  _HK_REAL_ONE (1.0f)
extern float g_015bc9e8;                 // 0x15bc9e8  Pan3D default angle Y (degrees)
extern float g_015bc9ec;                 // 0x15bc9ec  Pan3D default spread mode
extern float g_015bcd9c;                 // 0x15bcd9c  rotator default angle X
extern float g_015bcda0;                 // 0x15bcda0  rotator default angle Y
extern uint8_t g_vtbl_014bc0fc[];        // 0x14bc0fc  shared base vtable (PlugIn-kind)
extern uint8_t g_vtbl_014b6b84[];        // 0x14b6b84  RawPuller2 vtable
extern uint8_t g_vtbl_014b7ee0[];        // 0x14b7ee0  Pause vtable
extern void* volatile g_015bc450;        // 0x15bc450
extern uint8_t g_015bc468[];             // 0x15bc468
#pragma function(memset)
#pragma function(memcpy)
uint32_t FUN_0113a770(uint32_t* rec);   // 0x113a770  ReverbIR1 reset handler
void     FUN_0113ae50(uint8_t* p);      // 0x113ae50  Pause timer callback
static inline uint8_t&  B(void* p, unsigned o) { return *(uint8_t*)((char*)p + o); }
static inline uint32_t& W(void* p, unsigned o) { return *(uint32_t*)((char*)p + o); }
static inline float&    F(void* p, unsigned o) { return *(float*)((char*)p + o); }
static inline void*&    P(void* p, unsigned o) { return *(void**)((char*)p + o); }
struct Ctx {
    uint8_t b[0x800];

    // --- real (callee) members, never defined here ---
    void     FastFirReset();                       // 0x114e580  FastFirEngine::Reset
    float    FastFirApply(int, int, int, int);     // 0x114e390  FastFirEngine::Apply
    void     ReverbConfigure(int);                 // 0x113a7a0  ReverbIR1 filter setup
    void*    SysAlloc(uint32_t, const char*, int, int); // 0x112c820 System::Alloc
    void     SysFree(void*, int);                  // 0x112c850  System::Free
    bool     AddTimer(void*, void*, void*, const char*, int, int); // 0x112d8e0 TimerManager::AddTimer
    void     RemoveTimer(void*);                   // 0x112dad0  System::RemoveTimer
    void     InitSndPlayer1();                     // 0x112dbb0  PlugIn::Initialize<SndPlayer1>
    void     Init16();                             // 0x114f4f0  PlugIn::Initialize<Pan3D> (zero 16 bytes)
    float    VoiceDecayRate();                     // 0x112e440  Voice decay / sample rate

    // --- slice functions (defined below) ---
    void     FUN_0113aa50(int, uint32_t*);
    void     FUN_0113ac60(int, uint32_t*);
    void     FUN_0113ae30();
    void     FUN_0113af90();
    void     FUN_0113b290(int, uint32_t*);
    void     FUN_0113b330();
    void     FUN_0113b750(int, float, float);
    void     FUN_0113b810();
    void     FUN_0113b9d0();
};
static inline void StoreBE(void* dst, uint32_t v)
{
    uint8_t* d = (uint8_t*)dst;
    d[0] = (uint8_t)(v >> 24);
    d[1] = (uint8_t)(v >> 16);
    d[2] = (uint8_t)(v >> 8);
    d[3] = (uint8_t)v;
}
static inline float NegF(float x)
{
    union { float f; uint32_t u; } v;
    v.f = x;
    v.u ^= 0x80000000u;
    return v.f;
}
#define XNEG(v) _mm_xor_ps(_mm_set_ss(v), _mm_set_ss(g_negmask))
// ---- items of slice s0113a8b0 end

// @ 0x01138d00
namespace rw { namespace audio { namespace core {
void AudioObj::F_d00()
{
    void* self = this;
    if (A<char>(self, 0x68) == 1)
        A<System_s0113_88f0*>(self, 4)->RemoveTimer((TimerHandle_s0113_88f0*)((char*)self + 0x24));
    SNDSYS_restore();
    int p = A<int>(self, 0x3c);
    if (p) g_pSystem->Free((void*)p, 0);
}
}}}  // namespace rw::audio::core

// @ 0x01138f70
namespace rw { namespace audio { namespace core {
void __cdecl FUN_01138f70(void)
{ g_p15bbb20 = (void*)0x15bbb38; }
}}}  // namespace rw::audio::core

// @ 0x01138f90
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01138f90(void* rec)
{
    int o = A<int>(rec, 4);
    *(double*)((char*)o + 0x28) = *(double*)((char*)rec + 8);
    A<u8>((void*)o, 0x3c) = 1;
    return 0x10;
}
}}}  // namespace rw::audio::core

// @ 0x01138fb0
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01138fb0(void* rec)
{
    A<u8>((void*)A<int>(rec, 4), 0x3c) = 0;
    return 8;
}
}}}  // namespace rw::audio::core

// @ 0x01138fd0
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_01138fd0(void* p)
{
    if (p) *(void**)p = (void*)0x14b0934;
    A<int>(p, 0xc) = (int)((char*)p + 0x30);
    A<u8>(p, 0x3c) = 0;
    A<float>(p, 0x38) = 0.0f; A<float>(p, 0x30) = 0.0f;
    return true;
}
}}}  // namespace rw::audio::core

// @ 0x01139000
namespace rw { namespace audio { namespace core {
void AudioObj::F_000(int cmd, int* param)
{
    void* self = this;
    System_s0113_88f0* sys = A<System_s0113_88f0*>(self, 4);
    char* rec = RING(sys);
    if (cmd == 0) {
        sys->mCommandIndex += 0x10;
        A<int>(rec, 4) = (int)self;
        A<int>(rec, 0) = (int)&FUN_01138f90;
        A<int>(rec, 8) = param[0]; A<int>(rec, 0xc) = param[1];
        return;
    }
    sys->mCommandIndex += 8;
    A<int>(rec, 0) = (int)&FUN_01138fb0;
    A<int>(rec, 4) = (int)self;
}
}}}  // namespace rw::audio::core

// @ 0x011390b0
namespace rw { namespace audio { namespace core {
void AudioObj::F_0b0()
{
    void* self = this;
    SubMix_s0113_88f0* mix = (SubMix_s0113_88f0*)((char*)self + 0x30);
    if (A<char>(self, 0x40) == 0) { mix->FUN_01137450(0); return; }
    // The original keeps dst[] immediately below the six output floats, so an out-of-range
    // channel read (count > 6) aliases dst[6] onto out[0]; mirror that with one block.
    struct { void* dst[6]; float out[6]; } b;
    b.dst[0] = &b.out[0]; b.dst[1] = &b.out[1]; b.dst[2] = &b.out[2];
    b.dst[3] = &b.out[3]; b.dst[4] = &b.out[4]; b.dst[5] = &b.out[5];
    void* src[6];
    src[0] = (char*)self + 0x44; src[1] = (char*)self + 0x48; src[2] = (char*)self + 0x4c;
    src[3] = (char*)self + 0x50; src[4] = (char*)self + 0x54; src[5] = (char*)self + 0x58;
    FUN_0112d590(b.dst, src, 1.0f, (int)A<u8>(self, 0x40), (int)A<u8>(self, 0x20), 1);
    mix->FUN_01137450(b.dst[0]);
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x4c) = 0.0f; A<float>(self, 0x48) = 0.0f;
    A<float>(self, 0x50) = 0.0f; A<float>(self, 0x54) = 0.0f; A<float>(self, 0x58) = 0.0f;
}
}}}  // namespace rw::audio::core

// @ 0x011391a0
namespace rw { namespace audio { namespace core {
int __cdecl FUN_011391a0(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((AudioObj*)self)->F_0b0();
    g_pTimerList = g_pTimerList2;
    for (void* p = FUN_011373c0(); p; p = FUN_011373c0()) {
        if (strcmp((char*)rec + 0xc, (char*)p + 0x4c) == 0) {
            ((SubMix_s0113_88f0*)((char*)self + 0x30))->FUN_01137420(A<int>(self, 8), (int)p);
            break;
        }
    }
    return A<int>(rec, 8);
}
}}}  // namespace rw::audio::core

// @ 0x01139230
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01139230(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((AudioObj*)self)->F_0b0();
    if (A<int>(rec, 8))
        ((SubMix_s0113_88f0*)((char*)self + 0x30))->FUN_01137420(A<int>(self, 8), A<int>(rec, 8));
    return 0xc;
}
}}}  // namespace rw::audio::core

// @ 0x01139260
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_01139260(void* p)
{
    if (p) { *(void**)p = (void*)0x14b0e5c; A<int>(p, 0x38) = 0; A<int>(p, 0x3c) = 0; A<u8>(p, 0x40) = 0; }
    A<float>(p, 0x5c) = g_one; A<float>(p, 0x28) = g_one;
    A<u8>(p, 0x60) = 0;
    A<int>(p, 0xc) = (int)((char*)p + 0x28);
    A<float>(p, 0x44) = 0.0f; A<float>(p, 0x48) = 0.0f; A<float>(p, 0x4c) = 0.0f;
    A<float>(p, 0x50) = 0.0f; A<float>(p, 0x54) = 0.0f; A<float>(p, 0x58) = 0.0f;
    return true;
}
}}}  // namespace rw::audio::core

// @ 0x011392c0
namespace rw { namespace audio { namespace core {
void AudioObj::F_2c0(int cmd, int* param)
{
    void* self = this;
    System_s0113_88f0* sys = A<System_s0113_88f0*>(self, 4);
    char* rec = RING(sys);
    if (cmd == 0) {
        sys->mCommandIndex += 0xc;
        A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139230; A<int>(rec, 8) = param[0];
        return;
    }
    char* name = (char*)param[0];
    char* e = name; while (*e) e++;
    unsigned len = (unsigned)(e - name) + 1;
    rec = RING(sys);
    unsigned rs = (len + 0x10) & ~3u;
    sys->mCommandIndex += rs;
    A<int>(rec, 0) = (int)&FUN_011391a0; A<int>(rec, 4) = (int)self; A<int>(rec, 8) = (int)rs;
    char* d = rec + 0xc;
    for (char* s = name; ; ) { char c = *s++; *d++ = c; if (!c) break; }
}
}}}  // namespace rw::audio::core

// @ 0x01139390
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01139390(void* rec)
{
    void* self = A<void*>(rec, 4);
    if (A<int>(self, 0x54)) {
        A<int>(self, 0x54) = 0;
        if (A<char>(self, 0x7e)) { A<System_s0113_88f0*>(self, 4)->RemoveTimer((TimerHandle_s0113_88f0*)((char*)self + 0x24)); A<char>(self, 0x7e) = 0; }
        A<float>(self, 0x40) = 0.0f;
    }
    return 8;
}
}}}  // namespace rw::audio::core

// @ 0x011393d0
namespace rw { namespace audio { namespace core {
void __cdecl FUN_011393d0(void* self)
{
    int p = A<int>(self, 0x70);
    if (p == 0) { operator_new_arr((unsigned)A<int>(self, 0x78), 0, (unsigned)A<int>(self, 0x6c)); p = A<int>(self, 0x6c); }
    void* a1 = (void*)A<int>(self, 0x78);
    void* a3 = (void*)A<int>(self, 0x58);
    // The null test keeps the callee live in ECX across the argument setup, matching the
    // original's `mov ecx,[esi+0x54]; call ecx` (LTCG codegen); a bare indirect call goes
    // through memory instead and leaves ECX stale at the generated call site.
    void (__cdecl *fn)(void*, int, void*) = (void (__cdecl *)(void*, int, void*))A<int>(self, 0x54);
    if (fn != 0) fn(a1, p, a3);
    A<int>(self, 0x70) = 0;
}
}}}  // namespace rw::audio::core

// @ 0x01139450
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_01139450(void* p)
{
    if (p) {
        *(void**)p = (void*)0x14b1788;
        ((PlugIn_s0112_ce20*)((char*)p + 0x24))->Initialize_SndPlayer1();
    }
    A<float>(p, 0x40) = 0.0f;
    A<int>(p, 0xc) = (int)((char*)p + 0x40);
    u16 u = (u16)((((int)p + 0x87) & 0xfffffff8) - (int)p);
    A<u16>(p, 0x74) = u;
    A<u8>(p, 0x7e) = 0; A<int>(p, 0x78) = 0; A<int>(p, 0x70) = 0; A<int>(p, 0x54) = 0;
    operator_new_arr((unsigned)((char*)p + u), 0, 0x90);
    return true;
}
}}}  // namespace rw::audio::core

// @ 0x011394b0
namespace rw { namespace audio { namespace core {
void AudioObj::F_4b0()
{
    void* self = this;
    if (A<int>(self, 0x54)) {
        A<int>(self, 0x54) = 0;
        if (A<char>(self, 0x7e)) { A<System_s0113_88f0*>(self, 4)->RemoveTimer((TimerHandle_s0113_88f0*)((char*)self + 0x24)); A<char>(self, 0x7e) = 0; }
        A<float>(self, 0x40) = 0.0f;
    }
    int b = A<int>(self, 0x78);
    if (b) A<System_s0113_88f0*>(self, 4)->Free((void*)b, 0);
}
}}}  // namespace rw::audio::core

// @ 0x01139660
namespace rw { namespace audio { namespace core {
void AudioObj::F_660(int cmd, int* param)
{
    void* self = this;
    System_s0113_88f0* sys = A<System_s0113_88f0*>(self, 4);
    if (cmd == 0) {
        char* rec = RING(sys);
        sys->mCommandIndex += 0x20;
        A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139500; A<int>(rec, 8) = 0x20;
        A<int>(rec, 0xc) = param[0]; A<int>(rec, 0x10) = param[1]; A<int>(rec, 0x14) = param[2];
        A<int>(rec, 0x18) = param[3]; A<int>(rec, 0x1c) = param[4];
        return;
    }
    if (cmd == 1) {
        char* rec = RING(sys);
        sys->mCommandIndex += 8;
        A<int>(rec, 0) = (int)&FUN_01139390; A<int>(rec, 4) = (int)self;
    }
}
}}}  // namespace rw::audio::core

// @ 0x01139730
namespace rw { namespace audio { namespace core {
void AudioObj::F_730()
{
    void* self = this;
    ((SubMix_s0113_88f0*)((char*)self + 0x24))->FUN_01137450((char*)self + 0x38);
    A<float>(self, 0x38) = 0.0f; A<float>(self, 0x3c) = 0.0f; A<float>(self, 0x40) = 0.0f;
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x48) = 0.0f; A<float>(self, 0x4c) = 0.0f;
}
}}}  // namespace rw::audio::core

// @ 0x01139770
namespace rw { namespace audio { namespace core {
int __cdecl FUN_01139770(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((SubMix_s0113_88f0*)((char*)self + 0x24))->FUN_01137450((char*)self + 0x38);
    A<float>(self, 0x38) = 0.0f; A<float>(self, 0x3c) = 0.0f; A<float>(self, 0x40) = 0.0f;
    A<float>(self, 0x44) = 0.0f; A<float>(self, 0x48) = 0.0f; A<float>(self, 0x4c) = 0.0f;
    if (A<int>(rec, 8)) {
        ((SubMix_s0113_88f0*)((char*)self + 0x24))->FUN_01137420(A<int>(self, 8), A<int>(rec, 8));
        A<u8>(self, 0x50) = (u8)(int)A<float>(rec, 0xc);
        A<u8>(self, 0x51) = (u8)(int)A<float>(rec, 0x10);
        A<u8>(self, 0x52) = (u8)(int)A<float>(rec, 0x14);
    }
    return 0x18;
}
}}}  // namespace rw::audio::core

// @ 0x011397e0
namespace rw { namespace audio { namespace core {
bool __cdecl FUN_011397e0(void* p)
{
    if (p) { *(void**)p = (void*)0x14b1c8c; A<int>(p, 0x2c) = 0; A<int>(p, 0x30) = 0; A<u8>(p, 0x34) = 0; }
    A<float>(p, 0x38) = 0.0f; A<float>(p, 0x3c) = 0.0f; A<float>(p, 0x40) = 0.0f;
    A<float>(p, 0x44) = 0.0f; A<float>(p, 0x48) = 0.0f; A<float>(p, 0x4c) = 0.0f;
    return true;
}
}}}  // namespace rw::audio::core

// @ 0x01139820
namespace rw { namespace audio { namespace core {
void AudioObj::F_820(int cmd, int* param)
{
    void* self = this;
    System_s0113_88f0* sys = A<System_s0113_88f0*>(self, 4);
    char* rec = RING(sys);
    sys->mCommandIndex += 0x18;
    A<int>(rec, 4) = (int)self; A<int>(rec, 0) = (int)&FUN_01139770;
    A<int>(rec, 8) = param[0]; A<int>(rec, 0xc) = param[1];
    A<int>(rec, 0x10) = param[2]; A<int>(rec, 0x14) = param[3];
}
}}}  // namespace rw::audio::core

// @ 0x011398b0
namespace rw { namespace audio { namespace core {
void AudioObj::F_8b0()
{
    void* self = this;
    for (int i = 0; i < 6; i++)
        ((DelayLine*)((char*)self + 0x2b4 + i * 0x3c))->Release();
    for (int i = 0; i < (int)A<u8>(self, 0x439); i++)
        ((DelayLine*)((char*)self + 0x88 + i * 0x3c))->Release();
    if (A<char>(self, 0x43a))
        g_pSystem->RemoveTimer((TimerHandle_s0113_88f0*)((char*)self + 0x13c));
}
}}}  // namespace rw::audio::core

// @ 0x01139eb0
namespace rw { namespace audio { namespace core {
void RevObj::F_eb0()
{
    void* p = this;
    for (int i = 5; i >= 0; i--) ((DelayLine_s0113_99e0*)((char*)p + 0x2b4 + i * 0x3c))->FUN_0114d770();
    EA_Audio_sys_gui();
    for (int i = 2; i >= 0; i--) ((DelayLine_s0113_99e0*)((char*)p + 0x88 + i * 0x3c))->FUN_0114d770();
    *(void**)p = (void*)0x14bc0fc;
}
}}}  // namespace rw::audio::core

// @ 0x0113a770
namespace rw { namespace audio { namespace core {
int __cdecl FUN_0113a770(void* rec)
{
    void* self = A<void*>(rec, 4);
    ((FastFirEngine*)((char*)self + 0x50))->Reset();
    A<int>(self, 0x4c) = 0;
    A<int>(self, 0xe8) = 0;
    return 8;
}
}}}  // namespace rw::audio::core

// @ 0x0113a7a0
namespace rw { namespace audio { namespace core {
void RevObj::F_7a0(int idx)
{
    void* p = this;
    char* i1 = (char*)p + idx * 0x28;
    if (A<int>(p, 0x4c + idx * 0x28) != 0)
        ((FastFirEngine*)((char*)p + 0x50 + idx * 0x94))->Reset();
    int i2 = A<int>(p, 0x24) + 0x30;
    A<int>(i1, 0x4c) = i2;
    ((FastFirEngine*)((char*)p + 0x50 + idx * 0x94))->Configure(
        0x100, A<int>(i1, 0x3c), A<int>(i1, 0x40), A<int>(i1, 0x44),
        A<int>(i1, 0x30), A<int>(i1, 0x34), i2);
    float f = (float)(A<int>(i1, 0x3c) - 0x100);
    A<float>(p, 0x14) = f;
    f = (float)A<int>(i1, 0x34) + f;
    A<float>(A<void*>(p, 8), 0x28) = (f - A<float>(p, 0x18)) + A<float>(A<void*>(p, 8), 0x28);
    A<float>(p, 0x18) = f;
}
}}}  // namespace rw::audio::core

// @ 0x0113a840
namespace rw { namespace audio { namespace core {
RevObj* RevObj::F_840(u8 flags)
{
    void* p = this;
    ((FastFirEngine*)((char*)p + 0x50))->FUN_0114e340();
    *(void**)p = (void*)0x14bc0fc;
    if (flags & 1) operator_delete__(p);
    return this;
}
}}}  // namespace rw::audio::core

// @ 0x0113a8b0
uint32_t FUN_0113a8b0(uint32_t* rec)
{
    uint8_t* self = (uint8_t*)rec[1];
    uint32_t* p = (uint32_t*)rec[2];

    W(self, 0x24) = rec[2];
    for (int i = 0; i < 9; i++)
        StoreBE(self + 0x28 + i * 4, p[i]);
    W(self, 0xe4) = (uint32_t)(p + 8);

    float res = ((Ctx*)(self + 0x50))->FastFirApply(W(self, 0x34), W(self, 0x3c), W(self, 0x40), 0x100);

    float* thr = (float*)P(self, 8);
    if (*thr < res) {
        float v = res * (1.0f / 3.0f);
        thr[0] = v;
        thr[1] = v;
        thr[2] = v;
    }

    ((Ctx*)self)->ReverbConfigure(0);
    W(self, 0xe8) = 1;
    return 0xc;
}

// @ 0x0113aa50
void Ctx::FUN_0113aa50(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint32_t* q = (uint32_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0xc;
        q[0] = (uint32_t)&FUN_0113a8b0;
        q[1] = (uint32_t)this;
        q[2] = param_3[0];
    } else {
        W(sys, 0xb4) = off + 8;
        q[0] = (uint32_t)&FUN_0113a770;
        q[1] = (uint32_t)this;
    }
}

// @ 0x0113aae0
uint32_t FUN_0113aae0(uint8_t* p)
{
    return (uint32_t)B(p, 8) * 8 + 0x50;
}

// @ 0x0113aaf0
bool FUN_0113aaf0(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    F(p, 0x28) = 1.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = -1.0f;
    F(p, 0x34) = 1.0f;
    F(p, 0x38) = 1.0f;
    W(p, 0x44) = 0x10000;
    W(p, 0x48) = 0;
    memset(p + 0x50, 0, (uint32_t)B(p, 0x21) * 8);
    return true;
}

// @ 0x0113abb0
void FUN_0113abb0()
{
    void* p = g_015bc468;
    g_015bc450 = p;
}

// @ 0x0113abd0
uint32_t FUN_0113abd0(uint8_t* rec)
{
    uint8_t* self = (uint8_t*)P(rec, 4);
    if (F(self, 0x2c) != F(rec, 0xc) || B(self, 0x35) != (uint8_t)(int)F(rec, 8))
        B(self, 0x34) = 1;
    B(self, 0x35) = (uint8_t)(int)F(rec, 8);
    F(self, 0x2c) = F(rec, 0xc);
    W(self, 0x28) = W(rec, 0x10);
    W(self, 0x24) = W(rec, 0x14);
    return 0x18;
}

// @ 0x0113ac20
uint32_t FUN_0113ac20(uint8_t* rec)
{
    W((uint8_t*)P(rec, 4), 0x24) = 0;
    return 8;
}

// @ 0x0113ac40
bool FUN_0113ac40(uint8_t* p)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014b6b84;
    W(p, 0x24) = 0;
    W(p, 0x30) = 0;
    B(p, 0x34) = 1;
    return true;
}

// @ 0x0113ac60
void Ctx::FUN_0113ac60(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint8_t* q = (uint8_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0x18;
        W(q, 4) = (uint32_t)this;
        W(q, 0) = (uint32_t)&FUN_0113abd0;
        W(q, 8) = param_3[0];
        W(q, 0xc) = param_3[1];
        W(q, 0x10) = param_3[2];
        W(q, 0x14) = param_3[3];
    } else {
        W(sys, 0xb4) = off + 8;
        W(q, 0) = (uint32_t)&FUN_0113ac20;
        W(q, 4) = (uint32_t)this;
    }
}

// @ 0x0113ae30
void Ctx::FUN_0113ae30()
{
    if (B(this, 0x59) == 1)
        ((Ctx*)P(this, 4))->RemoveTimer((char*)this + 0x34);
}

// @ 0x0113ae50
void FUN_0113ae50(uint8_t* p)
{
    // The original keeps the product and the +1.0 in x87 extended precision and rounds once,
    // when it stores the float (fstp dword).  /arch:SSE is needed only for the cvttss2si
    // conversion, so the arithmetic stays x87; the addend is the image's own 1.0f constant
    // (0x1485720) so the relocation lands on the same address the original uses.
    float fv = ((Ctx*)P(p, 8))->VoiceDecayRate() * F((uint8_t*)P(p, 4), 0xc0) + g_real_one;
    // The original's `cvtss2si eax, [esp+8]` rounds to nearest-even (MXCSR), while our xmm-free
    // conversion is `cvttss2si` (truncate); on half-integer inputs the two differ (e.g. -1.5 -> -2
    // vs -1).  Use the rounding SSE convert, which reproduces the original instruction exactly.
    F(p, 0x4c) = fv;
    *(int*)(p + 0x4c) = _mm_cvt_ss2si(_mm_load_ss(&F(p, 0x4c)));
}

// @ 0x0113aeb0
bool FUN_0113aeb0(uint8_t* p)
{
    if (p != 0) {
        P(p, 0) = g_vtbl_014b7ee0;
        ((Ctx*)(p + 0x34))->InitSndPlayer1();
    }
    F(p, 0x28) = 0.0f;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    F(p, 0x30) = 1.0f;
    B(p, 0x57) = 2;
    B(p, 0x58) = 0;
    B(p, 0x59) = 0;
    W(p, 0x4c) = 0;
    W(p, 0x50) = 0;
    bool r = ((Ctx*)((char*)P(p, 4) + 0x60))->AddTimer((char*)p + 0x34, (void*)&FUN_0113ae50, p, "SndPlayer", 1, 1);
    if (r)
        return false;
    B(p, 0x59) = 1;
    return true;
}

// @ 0x0113af70
uint32_t FUN_0113af70(uint8_t* rec)
{
    W((uint8_t*)P(rec, 4), 0xbc) = 0;
    return 8;
}

// @ 0x0113af90
void Ctx::FUN_0113af90()
{
    if (W(this, 0x90) != 0) {
        ((Ctx*)P(this, 4))->SysFree((void*)W(this, 0x8c), 0);
        W(this, 0x90) = 0;
    }
}

// @ 0x0113afc0
uint32_t FUN_0113afc0(uint32_t* p)
{
    int v = 0;
    if (*p != 0)
        v = (int)F((uint8_t*)*p, 4);
    return (uint32_t)v * 0x50 + 0x138;
}

// @ 0x0113b000
uint32_t FUN_0113b000(uint8_t* rec)
{
    uint8_t* self = (uint8_t*)P(rec, 4);
    void* src = P(rec, 8);
    if (src != 0) {
        W(self, 0xa4) = 1;
        memcpy(P(self, 0x98), src, 0x22c);
        W(self, 0xbc) = 1;
        return 0xc;
    }
    W(self, 0xa4) = 0;
    W(self, 0xbc) = 0;
    return 0xc;
}

// @ 0x0113b290
void Ctx::FUN_0113b290(int param_2, uint32_t* param_3)
{
    uint8_t* sys = (uint8_t*)P(this, 4);
    uint32_t off = W(sys, 0xb4);
    uint32_t* q = (uint32_t*)(W(sys, 0x20) + off);
    if (param_2 == 0) {
        W(sys, 0xb4) = off + 0xc;
        q[0] = (uint32_t)&FUN_0113b000;
        q[1] = (uint32_t)this;
        q[2] = param_3[0];
    } else {
        W(sys, 0xb4) = off + 8;
        q[0] = (uint32_t)&FUN_0113af70;
        q[1] = (uint32_t)this;
    }
}

// @ 0x0113b330
void Ctx::FUN_0113b330()
{
    float a = F(this, 0x7c);
    F(this, 0x88) = (float)(cos(a) * 2.0);
    F(this, 0x13c) = (float)cos(a);
    F(this, 0x140) = (float)sin(a);
    _mm_store_ss((float*)((char*)this + 0x14c), XNEG(a));
    F(this, 0x150) = (float)sin(F(this, 0x14c));
    F(this, 0x14c) = (float)cos(F(this, 0x14c));
    float b = F(this, 0x80);
    F(this, 0x154) = (float)cos(b);
    F(this, 0x158) = (float)sin(b);
    _mm_store_ss((float*)((char*)this + 0x15c), XNEG(b));
    F(this, 0x160) = (float)sin(F(this, 0x15c));
    F(this, 0x15c) = (float)cos(F(this, 0x15c));
    F(this, 0x148) = 0.0f;
    F(this, 0x144) = 1.0f;

    float c1 = F(this, 0x13c), s1 = F(this, 0x140);
    float c2 = F(this, 0x14c), s2 = F(this, 0x150);
    float i1 = 1.0f / (c1 * s2 - s1 * c2);
    F(this, 0x8c) = i1 * c1;
    _mm_store_ss((float*)((char*)this + 0x90), XNEG(i1 * s1));
    F(this, 0x98) = i1 * s2;
    _mm_store_ss((float*)((char*)this + 0x94), XNEG(i1 * c2));

    float c3 = F(this, 0x154), s3 = F(this, 0x158);
    float i2 = 1.0f / (c3 * s1 - s3 * c1);
    F(this, 0xbc) = i2 * c3;
    _mm_store_ss((float*)((char*)this + 0xc0), XNEG(i2 * s3));
    _mm_store_ss((float*)((char*)this + 0xc4), XNEG(i2 * c1));
    F(this, 0xc8) = i2 * s1;

    float c4 = F(this, 0x15c), s4 = F(this, 0x160);
    float i3 = 1.0f / (c4 * s3 - s4 * c3);
    F(this, 0xac) = i3 * c4;
    _mm_store_ss((float*)((char*)this + 0xb0), XNEG(i3 * s4));
    _mm_store_ss((float*)((char*)this + 0xb4), XNEG(i3 * c3));
    F(this, 0xb8) = i3 * s3;

    float c2b = F(this, 0x14c), s2b = F(this, 0x150);
    float c3b = F(this, 0x15c), s3b = F(this, 0x160);
    float i4 = 1.0f / (c2b * s3b - s2b * c3b);
    F(this, 0x9c) = i4 * c2b;
    _mm_store_ss((float*)((char*)this + 0xa0), XNEG(i4 * s2b));
    _mm_store_ss((float*)((char*)this + 0xa4), XNEG(i4 * c3b));
    F(this, 0xa8) = i4 * s3b;
}

// @ 0x0113b5b0
bool FUN_0113b5b0(uint8_t* p, float* params)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    uint8_t al = B(p, 0x20);
    uint8_t* esi = p + 0x28;
    W(p, 0xc) = (uint32_t)esi;
    uint32_t edx = 5;
    if (al != 6)
        edx = al;
    W(p, 0xcc) = edx;
    uint8_t al2 = B(p, 0x21);
    uint32_t eax = 5;
    if (al2 != 6)
        eax = al2;
    W(p, 0xd0) = eax;

    const float K = 0.017453292f;
    float z;
    if (params != 0) {
        F(p, 0x7c) = params[0] * K;
        F(p, 0x80) = params[1] * K;
        z = params[2];
    } else {
        F(p, 0x7c) = g_015bc9e4 * K;
        F(p, 0x80) = g_015bc9e8 * K;
        z = g_015bc9ec;
    }
    if (z == 0.0f)
        F(p, 0x84) = 1.0f;
    else if (z == 1.0f)
        F(p, 0x84) = 1.0f / (float)edx;
    else if (z == 2.0f)
        F(p, 0x84) = 1.0f / sqrtf((float)edx);

    F(p, 0x60) = 0.0f;
    F(esi, 0) = 0.0f;
    F(p, 0x64) = 1.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0x68) = 1.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x6c) = 0.0f;
    F(p, 0x40) = 0.0f;
    F(p, 0x70) = 1.0f;
    F(p, 0x48) = 1.0f;
    F(p, 0x74) = 1.0f;
    F(p, 0x50) = 1.0f;
    F(p, 0x78) = 0.0f;
    F(p, 0x58) = 0.0f;
    ((Ctx*)p)->FUN_0113b330();
    return true;
}

// @ 0x0113b750
void Ctx::FUN_0113b750(int idx, float a, float b)
{
    float sa = (float)sin(a), ca = (float)cos(a);
    float sb = (float)sin(b), cb = (float)cos(b);
    float inv = 1.0f / (cb * sa - sb * ca);
    uint8_t* e = (uint8_t*)this + idx * 0x10;
    F(e, 0x7c) = inv * cb;
    F((uint8_t*)this + (idx + 8) * 0x10, 0) = NegF(inv * sb);
    F(e, 0x84) = NegF(inv * ca);
    F(e, 0x88) = inv * sa;
}

// @ 0x0113b810
void Ctx::FUN_0113b810()
{
    const float K = 0.017453292f;
    float a, b;
    if (B(this, 0xec) == 0) {
        a = g_015bcd9c * K;
        b = g_015bcda0;
    } else {
        a = F(this, 0x64) * K;
        b = F(this, 0x68);
    }
    F(this, 0x6c) = a;
    F(this, 0x70) = b * K;
    F(this, 0x74) = cos(a) * 2.0f;
    F(this, 0x78) = cos(3.1415927f - F(this, 0x70)) * 2.0f;

    float a2 = F(this, 0x6c);
    float b2 = F(this, 0x70);
    FUN_0113b750(0, NegF(a2), a2);
    FUN_0113b750(1, a2, b2);
    FUN_0113b750(2, b2, NegF(b2));
    FUN_0113b750(3, NegF(b2), NegF(a2));
}

// @ 0x0113b910
bool FUN_0113b910(uint8_t* p, float* params)
{
    if (p != 0)
        P(p, 0) = g_vtbl_014bc0fc;
    W(p, 0xc) = (uint32_t)(p + 0x28);
    if (params != 0) {
        F(p, 0x64) = params[0];
        F(p, 0x68) = params[1];
        B(p, 0xec) = 1;
    } else {
        B(p, 0xec) = 0;
    }
    F(p, 0x50) = 0.0f;
    F(p, 0x28) = 0.0f;
    F(p, 0x54) = 1.0f;
    F(p, 0x30) = 1.0f;
    F(p, 0x58) = 1.0f;
    F(p, 0x38) = 1.0f;
    F(p, 0x5c) = 1.0f;
    F(p, 0x40) = 1.0f;
    F(p, 0x60) = 0.0f;
    F(p, 0x48) = 0.0f;
    ((Ctx*)p)->FUN_0113b810();
    return true;
}

// @ 0x0113b9d0
void Ctx::FUN_0113b9d0()
{
    if (B(this, 0x169) != 0)
        ((Ctx*)P(this, 4))->RemoveTimer((char*)this + 0x30);
    uint32_t a = W(this, 0x48);
    if (a != 0)
        ((Ctx*)P(this, 4))->SysFree((void*)a, 0);
}

// @ 0x0113ba30
uint32_t FUN_0113ba30(uint8_t* p)
{
    return (uint32_t)B(p, 8) * 4 + 0x170;
}

// @ 0x0113baf0
uint32_t FUN_0113baf0(uint32_t* rec)
{
    uint8_t* self = (uint8_t*)rec[1];
    uint32_t v = rec[2];
    uint32_t* head = (uint32_t*)(self + 0x140);
    if (*head == 0) {
        head[0] = v;
        head[1] = v;
        W((uint8_t*)v, 0xc) = 0;
        return 0xc;
    }
    W((uint8_t*)head[1], 0xc) = v;
    head[1] = v;
    W((uint8_t*)v, 0xc) = 0;
    return 0xc;
}
