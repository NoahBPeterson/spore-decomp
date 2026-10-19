// src/game/SPMovie/SPMovieSystem.cpp -- migrated from slice(s) s00fd90c0, s00fd8190, s00fd71e0 by tools/migrate/rewrite.py
// Object file: SPMovie/SPMovieSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float kFloat_14007f4;
extern float kFloat_1486374;
extern float kFloat_1485720;
extern void* g_pMutexTag;                            // 0x01493900
#include <intrin.h>
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cCommandBase.h"

// ---- items of slice s00fd71e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IMessageServer {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0;
    virtual void PostMsg(int a, int b, int c) = 0;   // +0x14
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0;
    virtual void PostMsg2(int a, int b, int c) = 0;  // +0x2c
};
struct ICheatManager {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void RunCheat(const char* cmd) = 0;       // +0x1c
};
struct IHud {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0; virtual void v38() = 0;
    virtual void v3c() = 0; virtual void v40() = 0; virtual void v44() = 0;
    virtual void v48() = 0; virtual void v4c() = 0;
    virtual void ShowHudMessage(int) = 0;             // +0x50
};
struct IFeedback {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0;
    virtual void PostFeedback1(int a, int b) = 0;     // +0x14
    virtual void v18() = 0;
};
struct BlitArgs { int a, b, c, d; };
struct IMovieSystemMethods {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0;
    virtual bool IsPlaying() = 0;                      // +0x14
    virtual void v18() = 0; virtual void v1c() = 0;
    virtual void PauseMovie() = 0;                     // +0x20
};
struct IVideoOps {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0;
    virtual void Blit(const BlitArgs&) = 0;           // +0x38
    virtual void Blit2(const BlitArgs&) = 0;          // +0x3c
};
struct IAudioSystem {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0;
    virtual void v38_set(int) = 0;
    virtual void v3c() = 0;
    virtual void v40_call(int, int) = 0;
    virtual void v44() = 0;
    virtual void v48_call(int, void*) = 0;
    virtual void v4c_call(int, void*, int) = 0;
    virtual void v50() = 0; virtual void v54() = 0;
    virtual void v58() = 0;
    virtual void v5c() = 0; virtual void v60() = 0;
};
struct IUILayoutObj {
    virtual void v00_AddRef() = 0;
    virtual void v04_Release1(int) = 0;
    virtual void v08_Release0() = 0;
    virtual void v0c() = 0;
    virtual void Init(const void* key, bool, int) = 0;
    virtual void Ctor();                               // 0x00810000
};
struct IWindowCtl {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0; virtual void v38() = 0;
    virtual void v3c() = 0; virtual void v40() = 0;
    virtual void v44_call(int) = 0;                    // +0x44
};
struct EAMutex {
    uint32_t mData[0xc];
};
void EAMutex_ctor(void* p, int, int);              // 0x009222a0
void EAMutex_dtor(void* p);                        // 0x00922130
void EAMutex_Lock(void* p, void* tag);             // 0x009221b0
void EAMutex_Unlock(void* p);                      // 0x00922270
struct MoviePlayer {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0;
    virtual bool IsPlaying() = 0;                      // +0x38
    virtual void v3c() = 0;
    bool CanPlay();                                    // 0x00fcb470
    void Decode();                                     // 0x00fcb490
    void Render();                                     // 0x00fcb5e0
    void Play();                                       // 0x00fcb6e0
    void Stop();                                       // 0x00fcb710
    void Kill();                                       // 0x00fcb740
    void Shutdown();                                   // 0x00fcb860
};
class cMovieSystem {
public:
    void* mpVtbl0;               // +0x00
    void* mpVtbl1;               // +0x04
    void* mpVtbl2;               // +0x08
    void* mVideoDecoder;         // +0x0c
    void* mVideoOps;             // +0x10
    void* mAudioDecoder;         // +0x14
    void* mAudioRenderer;        // +0x18
    void* mMaterials[4];         // +0x1c
    void* mField2c;              // +0x2c
    void* mField30;              // +0x30
    MoviePlayer* mPlayer;        // +0x34
    int mField38;                // +0x38
    float mFadeInTime;           // +0x3c
    float mFadeOutTime;          // +0x40
    float mField44;              // +0x44
    float mField48;              // +0x48
    char mPad4c[4];
    void* mField50;              // +0x50
    void* mField54;              // +0x54
    void* mField58;              // +0x58
    float mField5c;              // +0x5c
    float mField60;              // +0x60
    void* mField64;              // +0x64
    void* mField68;              // +0x68
    EAMutex mRecordMutex;        // +0x70 (constructor uses +0x70)
    bool mRecording;             // +0xa0
    char mPadA1[3];
    void* mFieldA4;              // +0xa4
    void* mFieldA8;              // +0xa8
    void* mFieldAc;              // +0xac
    char mPadB0[4];
    int mWidth;                  // +0xb4
    int mHeight;                 // +0xb8
    float mFPS;                  // +0xbc
    float mFieldC0;              // +0xc0
    float mFieldC4;              // +0xc4
    float mFieldC8;              // +0xc8
    bool mAudio;                 // +0xcc
    bool mExcludeUI;             // +0xcd
    bool mFieldCe;               // +0xce
    char mPadCf;
    char mRecordStream[0x228];   // +0xd0
    int mField2fc;               // +0x2fc
    int mCapturedFrames;         // +0x300
    int mField304;               // +0x304
    int mField308;               // +0x308
    void* mField30c;             // +0x30c
    float mField310;             // +0x310
    float mField314;             // +0x314
    void* mLetterbox;            // +0x318
    void* mPacketList;           // +0x31c
    void* mPacketList2;          // +0x320
    char mPad324[4];
    bool mField328;              // +0x328
    char mPad329[3];
    bool mField32c;              // +0x32c
    bool mField32d;              // +0x32d

    void DrawLayer(int, int, int, int);              // 0x00fd7260
    char OnMovieMsg(int msg, int, int);              // 0x00fd74f0
    bool MovieIsPlaying();                           // 0x00fd75a0
    char PauseMovie2();                              // 0x00fd7610
    int RecordFrames(int nFrames);                   // 0x00fd7660
    bool Shutdown();                                 // 0x00fd7800
    bool StopMovie();                                // 0x00fd79e0
    void* GetSomething();                            // 0x00fd7a90
    cMovieSystem();                                  // 0x00fd7b30
    ~cMovieSystem();                                 // 0x00fd7cd0
    void StopRecordingMovie(unsigned int dtMs);      // 0x00fd7d80
    bool EndRecording();                             // 0x00fd7f80
};
struct cMovieLetterbox { void Init(); };             // 0x00fd7750
struct cContentValidationSummarizer { cContentValidationSummarizer* Init(); };// 0x00fd7ab0
IMessageServer* SP_MessageServer();                  // 0x0067dcc0
ICheatManager*  SP_CheatManager();                   // 0x0067de20
IHud*           FUN_0067dd50();                      // 0x0067dd50
IFeedback*      FUN_0067dda0();                      // 0x0067dda0
IAudioSystem*   EA_Audio_GetSystemAT();              // 0x00a206f0
void            Font_SetUserData(void* thisp, void* user); // 0x00fd9450
void            FileStream_ctor(void* p, int);       // 0x00931da0
void            FileStream_dtor(void* p);            // 0x00931e70
void*           operator_new(unsigned int size, const char* group, int, int, int, int); // 0x00f473a0
void            operator_delete(void* p);
extern float kFloat_14007f4;
extern float kFloat_1486374;
extern float kFloat_1485720;
extern void* g_pMutexTag;                            // 0x01493900
// ---- items of slice s00fd71e0 end

// ---- items of slice s00fd8190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_defaultCameraRaster;                         // 0x015d0838
extern void* g_spMemPool;                                   // 0x016c8b44
extern void* g_appProperties;                               // 0x015fd918
extern float kFloat_13f0620;                                // 0x013f0620
typedef void  (__thiscall *F0)(void*);
typedef void  (__thiscall *F1)(void*, int);
typedef void  (__thiscall *F2)(void*, int, int);
typedef void  (__thiscall *F3)(void*, int, int, int);
typedef void  (__thiscall *Fv)(void*, void*);
typedef void  (__thiscall *Fvv)(void*, void*, void*);
typedef int   (__thiscall *Fi0)(void*);
typedef void* (__thiscall *Fp0)(void*);
typedef void* (__thiscall *Fp1)(void*, int);
typedef void* (__thiscall *Fp7)(void*, int, int, int, int, int, int, int);
typedef int   (__thiscall *Fi2)(void*, int, int);
typedef void  (__thiscall *Ff1)(void*, float);
typedef int   (__thiscall *Fi4)(void*, int, int, int, int);
typedef void  (__thiscall *WAppendFn)(void*, const wchar_t*);
static inline void** Vt(void* o) { return *(void***)o; }
struct EAMutex_s00fd_8190 {  // 0x009221b0 / 0x00922270
    int Lock(void* tag);
    int Unlock();
};
void* GetSaveArea(const char* name);                        // 0x006b1f90
int   FUN_009309b0(void* buf, int a, int b, int c);         // 0x009309b0
void* GetDefaultAllocator();                                // 0x0041df40
void* SP_MessageServer_s00fd_8190();                                   // 0x0067dcc0
void* FUN_0067dd50_s00fd_8190();                                       // 0x0067dd50
void* FUN_0067dda0_s00fd_8190();                                       // 0x0067dda0
void* EA_ResourceMan_GetManager();                          // 0x0067dcd0
void* EA_Audio_GetSystemAT_s00fd_8190();                               // 0x00a206f0
void* LockedAlloc(int,int,int,int,int,int);                 // 0x009289f0
void  MemPool_Free(void* thisp, void* p);                   // 0x009276c0
void* FUN_00fca2c0(void* p, int a);                         // 0x00fca2c0
class cMovieSystem_s00fd_8190 {
public:
    char  mHead[0x64];          // +0x00
    void* mVideoEncoder;        // +0x64
    void* mAudioRenderer;       // +0x68
    char  mPad6c[4];            // +0x6c
    char  mRecordMutex[0x30];   // +0x70
    bool  mRecording;           // +0xa0
    bool  mFieldA1;             // +0xa1
    char  mPadA2[2];
    char  mPathString[0x10];    // +0xa4
    int   mWidth;               // +0xb4
    int   mHeight;              // +0xb8
    int   mFPS;                 // +0xbc
    float mFieldC0;             // +0xc0
    float mFieldC4;             // +0xc4
    float mFieldC8;             // +0xc8
    bool  mAudio;               // +0xcc
    bool  mExcludeUI;           // +0xcd
    char  mPadCe[2];
    char  mRecordStream[0x228]; // +0xd0
    int   mField2fc;            // +0x2fc
    int   mCapturedFrames;      // +0x300
    int   mField304;            // +0x304
    int   mField308;            // +0x308
    void* mFramePixels;         // +0x30c
    float mField310;            // +0x310
    float mField314;            // +0x314
    void* mLetterbox;           // +0x318
    void* mPacketList;          // +0x31c
    int   mAudioSampleRate;     // +0x328

    bool RecordMovie(int unused, int* pInfo);       // 0x00fd8190
    void SubmitFrame(int param);                    // 0x00fd86f0
    bool PlayMovie(int unused, int* pInfo);         // 0x00fd87c0
};
struct cArgumentSpec {
    char mData[0xc8];
    cArgumentSpec(int respectHelp);                             // 0x0083a9f0
    int  ConstructSpec(const char* name, const char* spec, ...); // 0x0083bcd0
    void ParseThrowing(int argc, const char** argv);            // 0x0083b9d0
};
struct cCommandBase {
    void** vtbl;            // +0x00
    void*  mParser;         // +0x04
    int    mRefCount;       // +0x08
    char   mPad0c[4];
    cCommandBase();                                             // 0x0083c800
};
inline void* operator new(unsigned int, void* p) { return p; }
void  ArgScript_Output(void* parser, const char* filler, ...);  // 0x00820f10
bool  PropList_Lookup(void* list, const void* name, void** out); // 0x0041e8d0
float* Prop_GetFloat(void* prop);                               // 0x0041ea70
int*   Prop_GetUInt(void* prop);                                // 0x0041ea00
bool*  Prop_GetBool(void* prop);                                // 0x0041e920
void  SPKeyFromName(void* key, const char* name, int, int);      // 0x0068d5a0
void  EA_ConvertToString16(void* out, const wchar_t* in, int len); // 0x0093c5a0
class cMovieCheat : public cCommandBase {
public:
    void* mpOwner;              // +0x10
    char  mSpecBuf[0xc8];       // +0x14  (cArgumentSpec)
    const char* mpRecordName;   // +0xdc
    void* mpFieldE0;            // +0xe0
    float mFieldE4;             // +0xe4
    float mFieldE8;             // +0xe8
    float mFieldEc;             // +0xec
    float mFieldF0;             // +0xf0
    bool  mFieldF4;             // +0xf4
    bool  mFieldF5;             // +0xf5
    char  mPadF6[2];
    int   mWidth;               // +0xf8
    int   mHeight;              // +0xfc
    float mFps;                 // +0x100
    float mTime;                // +0x104
    float mQuality;             // +0x108
    bool  mField10c;            // +0x10c
    bool  mField10d;            // +0x10d
    bool  mField10e;            // +0x10e

    cMovieCheat(void* pOwner);                                  // 0x00fd8c40
    void Execute(int argc);                                     // 0x00fd8d80
};
// ---- items of slice s00fd8190 end

// ---- items of slice s00fd90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_014007f4;
extern void* DAT_016e61a8;
extern void* DAT_016f4b10;
typedef unsigned char  u8;
typedef unsigned int   u32;
extern u32   DAT_01493980;
extern u32   DAT_01493990;
extern u8    DAT_013eb8a4[];  // "Graphics"
extern u8    DAT_013ebc58[];  // "App"
void* __cdecl  FUN_0067dd70();                       // SP::MaterialManager
void* __cdecl  FUN_0067dcc0();                       // SP::MessageServer
void* __cdecl  FUN_0067de20();                       // SP::CheatManager
void* __cdecl  FUN_00925cb0();                       // EA::Allocator::ICoreAllocator::GetDefaultAllocator
void* __cdecl  FUN_011e58c0();                       // 0x011e58c0
void  __cdecl  FUN_011e5cd0(void*);                  // 0x011e5cd0
void* __cdecl  FUN_00f473a0(int, const char*, int, int, int, int); // operator new
void* __cdecl  FUN_00d06400();                       // 0x00d06400
struct Ext {
    void* FUN_00fcd940(int);                  // 0x00fcd940 ctor helper
    void* FUN_00fd9680();                     // 0x00fd9680 ctor
    void* FUN_00fc7dd0(void*);                // 0x00fc7dd0 ctor
    void* FUN_00fc8080();                     // 0x00fc8080 ctor
    void* FUN_00fd95e0();                     // 0x00fd95e0 ctor
    void* FUN_00fcde80();                     // 0x00fcde80 ctor
    void* FUN_00fc7f30();                     // 0x00fc7f30 ctor
    void* FUN_011e64a0(int, void*);           // 0x011e64a0
    void  FUN_011ef880(void*);                // 0x011ef880
    void* FUN_00fd8c40(void*);                // 0x00fd8c40 cMovieCheat ctor
    void* FUN_00576650(void*);                // GetImageResource (0x00576650)
    void* FUN_00ae9390();                     // 0x00ae9390 -> char
    void  FUN_00e190c0(int);                  // 0x00e190c0
    void* FUN_00e18c70(void*);                // 0x00e18c70 -> char
    int   FUN_00bb9ae0();                     // 0x00bb9ae0
    void* FUN_00b1fdb0();                     // GetAvatar
    void  FUN_00d00a10(void*, int);           // returns float
    void* FUN_01040820();                     // returns float
    void* FUN_00c8b770();                     // cStar::GetSolarSystem
    void  FUN_00c86c70();                     // cSolarSystem::ActivateGraphics
    void  FUN_01034b90();                     // 0x01034b90
    void  FUN_00d06400();                     // 0x00d06400
    char  FUN_00d09660();                     // 0x00d09660 -> char
    void* FUN_01065e20();                     // 0x01065e20 -> char
    void  FUN_01067b60();                     // 0x01067b60
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
struct MovieSys {
    u8 raw[0x400];
    bool Init();
};
// ---- items of slice s00fd90c0 end

// @ 0x00fd7260
void cMovieSystem::DrawLayer(int, int, int, int arg3)
{
    char* p = (char*)this;
    MoviePlayer* pl = *(MoviePlayer**)(p + 0x30);
    if (pl != 0) {
        if (!*(bool*)(p + 0x328)) {
            *(bool*)(p + 0x328) = 1;
            SP_MessageServer()->PostMsg(0x49731a9, 0, 0);
        }
        if (!pl->CanPlay()) {
            pl->Decode();
            float one = kFloat_1485720;
            float v = one;
            if (*(float*)(p + 0x3c) > 0.0f) {
                float r = *(float*)(p + 0x5c) / *(float*)(p + 0x3c);
                float t = r < 0.0f ? 0.0f : (r > one ? one : r);
                v = t;
            }
            float acc = v;
            if (*(float*)(p + 0x40) > 0.0f) {
                int e = *(int*)((char*)pl + 0xb8);
                int b = *(int*)((char*)pl + 0xb4);
                int n = (e != 0) ? *(int*)((char*)e + 0x34) : 0;
                float x = (float)(b - n - 1) / *(float*)((char*)pl + 0xf0)
                          / *(float*)(p + 0x40);
                float t = x < 0.0f ? 0.0f : (x > one ? one : x);
                acc = acc * t;
            }
            (void)acc;
        }
    }
    void* mgr = *(void**)(p + 0xc);
    Font_SetUserData(mgr, (void*)arg3);
    if (pl != 0)
        pl->Render();
    Font_SetUserData(mgr, 0);
}

// @ 0x00fd74f0
char cMovieSystem::OnMovieMsg(int msg, int, int)
{
    char* p = (char*)this;
    MoviePlayer* pl = *(MoviePlayer**)(p + 0x34);
    if (msg == 0x1ee1008 || msg == 0x1ee100f || msg == 0x44edd9a) {
        if (pl != 0 && !*(bool*)(p + 0x325)) {
            pl->Play();
            *(bool*)(p + 0x325) = 1;
        }
        return 1;
    }
    if (msg == 0x1ee100e || msg == 0x44edd9c) {
        if (pl != 0 && *(bool*)(p + 0x325)) {
            pl->Stop();
            *(bool*)(p + 0x325) = 0;
        }
        return 1;
    }
    return 0;
}

// @ 0x00fd75a0
bool cMovieSystem::MovieIsPlaying()
{
    char* p = (char*)this;
    if (!((IMovieSystemMethods*)this)->IsPlaying())
        return false;
    float t = *(float*)(p + 0x48);
    if (!(t >= 0.0f))
        return false;
    void* d = *(void**)(p + 0x34);
    int e = *(int*)((char*)d + 0xb8);
    int n = (e != 0) ? *(int*)((char*)e + 0x34) : 0;
    if (t < (float)n / *(float*)((char*)d + 0xf0))
        return true;
    SP_MessageServer()->PostMsg(0x61d72de, 0, 0);
    ((IMovieSystemMethods*)this)->PauseMovie();
    return true;
}

// @ 0x00fd7610
char cMovieSystem::PauseMovie2()
{
    if (!((IMovieSystemMethods*)this)->IsPlaying())
        return 0;
    SP_MessageServer()->PostMsg(0x61d72de, 0, 0);
    ((IMovieSystemMethods*)this)->PauseMovie();
    return 1;
}

// @ 0x00fd7660
int cMovieSystem::RecordFrames(int nFrames)
{
    char* p = (char*)this;
    EAMutex* mx = (EAMutex*)(p + 0x70);
    EAMutex_Lock(mx, g_pMutexTag);
    if (*(int*)(p + 0x2fc) == 0) {
        EAMutex_Unlock(mx);
        return 0;
    }
    BlitArgs args;
    args.a = 3;
    args.b = *(int*)(p + 0xb8);
    args.c = *(int*)(p + 0xbc);
    args.d = *(int*)(p + 0x30c);
    float quality = *(float*)(p + 0xc0);
    if (quality < (float)nFrames)
        nFrames = (int)quality;
    int count = nFrames;
    if (nFrames > 0) {
        do {
            ((IVideoOps*)*(void**)(p + 0xb4))->Blit2(args);
            ++*(int*)(p + 0x300);
        } while (--nFrames != 0);
    }
    *(int*)(p + 0x2fc) = 0;
    EAMutex_Unlock(mx);
    return count;
}

// @ 0x00fd7730
void FUN_00fd7730(int a, IWindowCtl* w)
{
    if (w != 0)
        w->v44_call(a);
}

// @ 0x00fd7750
void cMovieLetterbox::Init()
{
    char* p = (char*)this;
    void* obj = operator_new(0x18, "Simulator", 0, 0, 0, 0);
    if (obj != 0)
        ((IUILayoutObj*)obj)->Ctor();
    else
        obj = 0;
    void* old = *(void**)(p + 0xc);
    if (obj != old) {
        if (obj != 0)
            ((IUILayoutObj*)obj)->v04_Release1(1);
        *(void**)(p + 0xc) = obj;
        if (old != 0)
            ((IUILayoutObj*)old)->v08_Release0();
    }
    uint32_t key[3];
    key[0] = 0x2edff72d;
    key[1] = 0x510a95b;
    key[2] = 0x40464100;
    ((IUILayoutObj*)*(void**)(p + 0xc))->Init(key, true, 0x5b598fa);
}

// @ 0x00fd7800
bool cMovieSystem::Shutdown()
{
    char* p = (char*)this;
    int self2 = (p != 0) ? (int)(p + 8) : 0;
    SP_MessageServer()->PostMsg2(self2, 0x1ee1008, -0x270f);
    SP_MessageServer()->PostMsg2(self2, 0x1ee100e, -0x270f);
    SP_MessageServer()->PostMsg2(self2, 0x1ee100f, -0x270f);
    SP_MessageServer()->PostMsg2(self2, 0x44edd9a, -0x270f);
    SP_MessageServer()->PostMsg2(self2, 0x44edd9c, -0x270f);
    void* lb = *(void**)(p + 0x318);
    if (lb != 0) {
        void* child = *(void**)((char*)lb + 0xc);
        if (child != 0) {
            ((IUILayoutObj*)child)->v0c();
            child = *(void**)((char*)lb + 0xc);
            if (child != 0) {
                *(void**)((char*)lb + 0xc) = 0;
                ((IUILayoutObj*)child)->v08_Release0();
            }
        }
        void* lb2 = *(void**)(p + 0x318);
        if (lb2 != 0) {
            *(void**)(p + 0x318) = 0;
            ((IUILayoutObj*)lb2)->v04_Release1(1);
        }
    }
    SP_CheatManager()->RunCheat("movie");
    return true;
}

// @ 0x00fd7a90
void* cMovieSystem::GetSomething()
{
    char* p = (char*)this;
    if (*(bool*)(p + 0xa0))
        return *(void**)(p + 0xa4);
    return 0;
}

// @ 0x00fd7ab0
cContentValidationSummarizer* cContentValidationSummarizer::Init()
{
    char* p = (char*)this;
    *(void**)(p + 4) = (void*)0x13ec458;
    _ReadWriteBarrier();
    *(void**)(p + 8) = 0;
    *(void**)p = (void*)0x14939f4;
    *(void**)(p + 4) = (void*)0x14939e4;
    *(void**)(p + 0xc) = 0;
    return this;
}

// @ 0x00fd7b30
cMovieSystem::cMovieSystem()
{
    char* p = (char*)this;
    *(void**)(p + 0x04) = (void*)0x13f1ab0;
    *(void**)(p + 0x08) = (void*)0x13eb394;
    *(void**)(p + 0x00) = (void*)0x1493a28;
    *(void**)(p + 0x04) = (void*)0x1493a18;
    *(void**)(p + 0x08) = (void*)0x1493a10;
    *(void**)(p + 0x0c) = 0;
    *(void**)(p + 0x10) = 0;
    *(void**)(p + 0x14) = 0;
    *(void**)(p + 0x18) = 0;
    *(void**)(p + 0x1c) = 0;
    *(bool*)(p + 0x20) = false;
    *(void**)(p + 0x34) = 0;
    *(void**)(p + 0x38) = 0;
    *(float*)(p + 0x3c) = 0.0f;
    *(float*)(p + 0x40) = 0.0f;
    *(float*)(p + 0x44) = 0.0f;
    *(float*)(p + 0x48) = 0.0f;
    *(bool*)(p + 0x4c) = false;
    *(bool*)(p + 0x4d) = true;
    *(void**)(p + 0x50) = (void*)0x1667bac;
    *(void**)(p + 0x54) = (void*)0x1667bac;
    *(void**)(p + 0x58) = (void*)0x1667bad;
    *(float*)(p + 0x60) = 0.0f;
    *(void**)(p + 0x64) = 0;
    *(void**)(p + 0x68) = 0;
    EAMutex_ctor(p + 0x70, 0, 1);
    *(bool*)(p + 0xa0) = false;
    *(bool*)(p + 0xa1) = true;
    *(void**)(p + 0xa4) = (void*)0x1667bac;
    *(void**)(p + 0xa8) = (void*)0x1667bac;
    *(void**)(p + 0xac) = (void*)0x1667bae;
    *(int*)(p + 0xb4) = 0;
    *(float*)(p + 0xc0) = kFloat_14007f4;
    *(float*)(p + 0xc4) = 0.0f;
    *(int*)(p + 0xb8) = 0x140;
    *(int*)(p + 0xbc) = 0xf0;
    *(float*)(p + 0xc8) = kFloat_1486374;
    *(bool*)(p + 0xcc) = true;
    *(bool*)(p + 0xcd) = false;
    *(bool*)(p + 0xce) = true;
    FileStream_ctor(p + 0xd0, 0);
    *(int*)(p + 0x2fc) = 0;
    *(int*)(p + 0x300) = 0;
    *(int*)(p + 0x304) = -1;
    *(int*)(p + 0x308) = -1;
    *(void**)(p + 0x30c) = 0;
    *(float*)(p + 0x310) = 0.0f;
    *(float*)(p + 0x314) = 0.0f;
    *(void**)(p + 0x318) = 0;
    *(void**)(p + 0x31c) = p + 0x31c;
    *(void**)(p + 0x320) = p + 0x31c;
    *(bool*)(p + 0x32c) = false;
    *(bool*)(p + 0x32d) = false;
    *(int*)(p + 0x328) = 0x5622;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x28) = 0;
    *(void**)(p + 0x2c) = 0;
    *(void**)(p + 0x30) = 0;
}

// @ 0x00fd7cd0
cMovieSystem::~cMovieSystem()
{
    char* p = (char*)this;
    char* head = p + 0x31c;
    *(void**)(p + 0x00) = (void*)0x1493a28;
    *(void**)(p + 0x04) = (void*)0x1493a18;
    *(void**)(p + 0x08) = (void*)0x1493a10;
    void* n = *(void**)head;
    while (n != head) {
        void* next = *(void**)n;
        operator_delete(n);
        n = next;
    }
    void* lb = *(void**)(p + 0x318);
    if (lb != 0)
        ((IUILayoutObj*)lb)->v04_Release1(1);
    FileStream_dtor(p + 0xd0);
    int e = *(int*)(p + 0xa4);
    int b = *(int*)(p + 0xac);
    if (((b - e) & 0xfffffffe) > 2 && e != 0)
        operator_delete((void*)e);
    EAMutex_dtor(p + 0x70);
    int s = *(int*)(p + 0x50);
    int ed = *(int*)(p + 0x58);
    if ((ed - s) > 1 && s != 0)
        operator_delete((void*)s);
    *(void**)(p + 0x08) = (void*)0x13eb394;
    *(void**)(p + 0x04) = (void*)0x13eb938;
    *(void**)(p + 0x00) = (void*)0x1403758;
}

// @ 0x00fd7f80
bool cMovieSystem::EndRecording()
{
    char* p = (char*)this;
    EAMutex* mx = (EAMutex*)(p + 0x70);
    EAMutex_Lock(mx, g_pMutexTag);
    if (!*(bool*)(p + 0xa0)) {
        EAMutex_Unlock(mx);
        return false;
    }
    if (!*(bool*)(p + 0xcd))
        FUN_0067dd50()->ShowHudMessage(0x25);
    else if (*(MoviePlayer**)(p + 0x34) == 0)
        FUN_0067dd50()->ShowHudMessage(0x1b);
    *(float*)(p + 0x310) = 0.0f;
    ((IVideoOps*)*(void**)(p + 0xb4))->v10();
    FUN_0067dda0()->PostFeedback1(*(int*)(p + 0x300), *(int*)(p + 0x304));
    *(int*)(p + 0x304) = -1;
    *(int*)(p + 0x308) = -1;
    operator_delete(*(void**)(p + 0x30c));
    *(void**)(p + 0x30c) = 0;
    if (*(bool*)(p + 0xcc)) {
        IAudioSystem* au = EA_Audio_GetSystemAT();
        if (au != 0) {
            ((IVideoOps*)*(void**)(p + 0x68))->v08();
            au->v38_set(0x4503efa);
            au->v40_call(0x4501144, 0x52de7b41);
            au->v58();
        }
    }
    if (*(void**)(p + 0xb4) != 0) {
        ((MoviePlayer*)*(void**)(p + 0xb4))->v08();
        ((MoviePlayer*)*(void**)(p + 0xb4))->v00();
        *(void**)(p + 0xb4) = 0;
    }
    while (*(void**)(p + 0x31c) != p + 0x31c) {
        void* n = *(void**)(p + 0x320);
        void* nn = *(void**)n;
        void* nn2 = *(void**)((char*)n + 4);
        *(void**)nn2 = nn;
        *(void**)((char*)nn + 4) = nn2;
        operator_delete(n);
        operator_delete(*(void**)((char*)n + 8));
    }
    *(bool*)(p + 0xa0) = false;
    EAMutex_Unlock(mx);
    SP_MessageServer()->PostMsg(0x62ff414, 0, 0);
    EAMutex_Lock(mx, g_pMutexTag);
    EAMutex_Unlock(mx);
    return true;
}

// @ 0x00fd8190
bool cMovieSystem_s00fd_8190::RecordMovie(int /*unused*/, int* pInfo)
{
    char* p = (char*)this;
    if (*(bool*)(p + 0xa0)) return false;
    if (!*(bool*)(p + 0xa1)) return false;

    void* mx = p + 0x70;
    ((EAMutex_s00fd_8190*)mx)->Lock((void*)0x01493900);

    void* sa = GetSaveArea((const char*)0x011ac197);
    int id = ((Fi0)Vt(sa)[0x28 / 4])(sa);

    wchar_t name[0x100];
    if (FUN_009309b0(name, (int)pInfo, id, 4) == 0) {
        ((EAMutex_s00fd_8190*)mx)->Unlock();
        return false;
    }

    int len = 0;
    while (name[len] != 0) ++len;
    if (len < 0xff) {
        const wchar_t* s = L".avi";
        wchar_t* d = name + len;
        wchar_t c;
        do { c = *s++; *d++ = c; } while (c != 0);
    }

    void* fs = p + 0xd0;
    int local;
    ((Fv)Vt(fs)[0x3c / 4])(fs, &local);
    if (!((Fi4)Vt(fs)[0x4c / 4])(fs, 0, 7, 2, 2)) {
        ((EAMutex_s00fd_8190*)mx)->Unlock();
        return false;
    }

    for (int i = 0; i < 6; ++i)
        ((int*)(p + 0xb8))[i] = pInfo[i];

    if (((char*)pInfo)[0x16] != 0) {
        char* cam = (char*)g_defaultCameraRaster;
        unsigned short h = *(unsigned short*)(cam + 0xc);
        unsigned short w = *(unsigned short*)(cam + 0xe);
        int x = pInfo[1] * h;
        int y = pInfo[0] * w;
        if (x < y)      *(int*)(p + 0xb8) = x / w;
        else if (x > y) *(int*)(p + 0xbc) = y / h;
    }

    void* enc = *(void**)(p + 0x64);
    int rate = (int)(*(float*)(p + 0xc8) * kFloat_13f0620);
    ((F1)Vt(enc)[0x44 / 4])(enc, rate);
    ((Ff1)Vt(enc)[0x34 / 4])(enc, *(float*)(p + 0xc0));
    ((F1)Vt(enc)[0x24 / 4])(enc, *(int*)(p + 0xb8));
    ((F1)Vt(enc)[0x2c / 4])(enc, *(int*)(p + 0xbc));
    ((Fv)Vt(enc)[0x04 / 4])(enc, GetDefaultAllocator());

    void* rec = operator_new(0x74, "Graphics", 0, 0, 0, 0);
    if (rec) rec = FUN_00fca2c0(rec, 0x4000);
    *(void**)(p + 0xb4) = rec;

    ((Fvv)Vt(rec)[0x1c / 4])(rec, (void*)0x00fd71e0, p + 0xd0);
    ((Fvv)Vt(rec)[0x14 / 4])(rec, (void*)"MovieEncoder", (void*)0x00c2e4e0);
    ((Fv)Vt(rec)[0x24 / 4])(rec, *(void**)(p + 0x64));

    if (*(bool*)(p + 0xcc)) {
        void* au = EA_Audio_GetSystemAT_s00fd_8190();
        if (au) {
            for (int i = 0; i < 200; ++i)
                ((void**)(p + 0x224))[i] = LockedAlloc(0, 0, 0, 0, 0, 0x800);
            ((F1)Vt(au)[0x38 / 4])(au, 0x04640907);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04501144, 0x52de7b41);
            ((F2)Vt(au)[0x4c / 4])(au, 0x04501150, 0);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x00fd7730, (void*)0x045705b8);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x00fd7730, this);
            ((F0)Vt(au)[0x58 / 4])(au);
            ((F1)Vt(au)[0x38 / 4])(au, 0x045010e7);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04501144, 0x52de7b41);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04502374, 0x800);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04597e49, *(int*)(p + 0x328));
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x00fd7730, (void*)0x045705b8);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x00fd7730, this);
            ((F0)Vt(au)[0x58 / 4])(au);

            void* ar = *(void**)(p + 0x68);
            ((Fv)Vt(ar)[0x04 / 4])(ar, GetDefaultAllocator());
            ((F1)Vt(ar)[0x24 / 4])(ar, *(int*)(p + 0x328));
            ((F1)Vt(ar)[0x2c / 4])(ar, 2);
            ((Fv)Vt(rec)[0x2c / 4])(rec, *(void**)(p + 0x68));
        }
    }

    {
        void* ar2 = *(void**)(p + 0x68);
        ((Fv)Vt(ar2)[0x04 / 4])(ar2, GetDefaultAllocator());
        ((Fv)Vt(rec)[0x04 / 4])(rec, GetDefaultAllocator());
    }

    void* fb = FUN_0067dda0_s00fd_8190();
    int probe[2];
    void* r = ((Fp7)Vt(fb)[0x10 / 4])(fb, (int)&probe,
                                      *(int*)(p + 0xb8), *(int*)(p + 0xbc),
                                      0x15, 0, -1, 0);
    (void)r;

    {
        int w2 = *(int*)(p + 0xbc) * *(int*)(p + 0xb8);
        *(void**)(p + 0x30c) = operator_new((unsigned)(w2 * 4), "Graphics", 0, 0, 0, 0);
    }
    *(int*)(p + 0x300) = 0;
    *(int*)(p + 0x2fc) = 0;
    ((F0)Vt(rec)[0x0c / 4])(rec);

    *(float*)(p + 0x310) = 0.0f;
    *(float*)(p + 0x314) = kFloat_1485720;
    *(int*)(p + 0x300) = 0;
    *(int*)(p + 0x2fc) = 0;
    *(bool*)(p + 0xa0) = true;

    // eastl::basic_string<wchar_t>::append(this+0xa4, info)
    ((WAppendFn)0x005c3d90)((void*)(p + 0xa4), (const wchar_t*)pInfo);

    if (!*(bool*)(p + 0xcd)) {
        void* hud = FUN_0067dd50_s00fd_8190();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)(p + 4), 0x25, 0);
    } else if (*(void**)(p + 0x34) == 0) {
        void* hud = FUN_0067dd50_s00fd_8190();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)(p + 4), 0x1b, 0);
    }

    ((EAMutex_s00fd_8190*)mx)->Unlock();
    ((F3)Vt(SP_MessageServer_s00fd_8190())[0x14 / 4])(SP_MessageServer_s00fd_8190(), 0x062ff413, 0, 0);
    ((EAMutex_s00fd_8190*)mx)->Lock((void*)0x01493900);
    ((EAMutex_s00fd_8190*)mx)->Unlock();
    return true;
}

// @ 0x00fd86f0
void cMovieSystem_s00fd_8190::SubmitFrame(int param)
{
    char* p = (char*)this;
    void* mx = p + 0x70;
    ((EAMutex_s00fd_8190*)mx)->Lock((void*)0x01493900);
    if (*(bool*)(p + 0xa0)) {
        int vals[5];
        vals[0] = 1;
        vals[1] = *(int*)(p + 0x328);
        vals[2] = 2;
        vals[3] = 0x200;
        vals[4] = param;

        void* rec = *(void**)(p + 0xb4);
        ((Fv)Vt(rec)[0x38 / 4])(rec, (void*)vals);

        int* node = (int*)operator_new(0xc, "EASTL", 0, 0,
                                       (int)0x013ebb38, 0xd1);
        if (node + 2 != 0)
            node[2] = param;
        node[0] = (int)(p + 0x31c);
        node[1] = *(int*)(p + 0x320);
        *(int**)(*(void**)(p + 0x320)) = node;
        *(int**)(p + 0x320) = node;
        ((EAMutex_s00fd_8190*)mx)->Unlock();
        return;
    }
    MemPool_Free(*(void**)&g_spMemPool, (void*)param);
    ((EAMutex_s00fd_8190*)mx)->Unlock();
}

// @ 0x00fd87c0
bool cMovieSystem_s00fd_8190::PlayMovie(int /*unused*/, int* pInfo)
{
    char* p = (char*)this;
    if (*(void**)(p + 0x34) != 0) return false;

    void* rm = EA_ResourceMan_GetManager();
    void* res = ((Fp1)Vt(rm)[0x58 / 4])(rm, (int)pInfo);
    if (!res) return false;

    char namebuf[0x200];
    int n1 = 0, n2 = 0;
    if (((Fi0)Vt(res)[0x0c / 4])(res) == 0x034728492) {
        if (!((Fi2)Vt(res)[0x64 / 4])(res, (int)pInfo, (int)namebuf)) return false;
        ((Fp0)Vt(res)[0x28 / 4])(res);
    } else {
        if (!((Fi2)Vt(res)[0x34 / 4])(res, (int)pInfo, (int)namebuf)) return false;
        if (n1 != 0) return false;
        ((Fp0)Vt(res)[0x28 / 4])(res);
    }

    void* alloc = GetDefaultAllocator();
    void* player = operator_new(0x248, "Graphics", 0, 0, 0, 0);
    *(void**)(p + 0x34) = player;
    (void)alloc; (void)n2; (void)namebuf;
    if (!player) return false;

    if (((Fi0)Vt(res)[0x0c / 4])(res) == 0x041e19be) {
        ((F1)Vt(res)[0x0c / 4])(res, 0);
    } else if (((Fi0)Vt(res)[0x0c / 4])(res) == 0x0376840d7) {
        if (EA_Audio_GetSystemAT_s00fd_8190() != 0) {
            *(bool*)(p + 0x20) = true;
        }
    } else {
        return false;
    }
    return true;
}

// @ 0x00fd8c40
cMovieCheat::cMovieCheat(void* pOwner)
{
    *(void**)this = (void*)0x01493c24;
    mpOwner = pOwner;
    ::new((void*)mSpecBuf) cArgumentSpec(1);

    mpRecordName = 0;
    mpFieldE0 = 0;
    mFieldE4 = 0.0f;
    mFieldE8 = 0.0f;
    mFieldEc = 0.0f;
    mFieldF0 = 0.0f;
    mFieldF4 = false;
    mFieldF5 = true;
    mWidth = 0x140;
    mHeight = 0xf0;
    mFps = kFloat_14007f4;
    mTime = 0.0f;
    mQuality = kFloat_1486374;
    mField10c = true;
    mField10d = false;
    mField10e = true;

    ((cArgumentSpec*)mSpecBuf)->ConstructSpec(
        "Movie cheat",
        "-record^ <name:cstring> [<time:float>]",
        0, &mpRecordName, &mTime,
        "Record movie. Either give a time, or run 'movie' again with no arguments to stop.",
        "-size <width:int> <height:int>", &mWidth, &mHeight,
        "Set size for recorded movie",
        "-quality <float>", &mQuality,
        "Set quality for recorded movie, 0-1",
        "-fps <float>", &mFps,
        "Set FPS for recorded movie",
        "-noUI^", 4, "Don't record UI",
        "-noAudio^", 3, "Don't record audio",
        "-noCrop^", 6, "Don't crop capture size to be same aspect as source",
        0);
}

// @ 0x00fd8d80
void cMovieCheat::Execute(int argc)
{
    char* p = (char*)this;
    *(void**)(p + 0xdc) = 0;
    *(float*)(p + 0xe4) = 0.0f;
    *(float*)(p + 0xf0) = 0.0f;

    if (g_appProperties != 0) {
        void* prop = 0;
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f974, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 0xd)
            *(float*)(p + 0x104) = *Prop_GetFloat(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f975, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 0xa)
            *(int*)(p + 0xf8) = *Prop_GetUInt(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f976, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 0xa)
            *(int*)(p + 0xfc) = *Prop_GetUInt(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f977, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 0xd)
            *(float*)(p + 0x100) = *Prop_GetFloat(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f978, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 0xd)
            *(float*)(p + 0x108) = *Prop_GetFloat(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f979, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 1)
            *(bool*)(p + 0x10c) = *Prop_GetBool(prop);
        if (PropList_Lookup(g_appProperties, (const void*)0x0456f97a, &prop)
            && *(unsigned short*)((char*)prop + 0x12) == 1)
            *(bool*)(p + 0x10d) = *Prop_GetBool(prop);
    }

    ((cArgumentSpec*)(p + 0x14))->ParseThrowing(argc, *(const char***)(p + 4));

    unsigned int flags = *(unsigned int*)(p + 0x84);
    *(float*)(p + 0xec) = *(float*)(p + 0xe8);

    void* owner = *(void**)(p + 0x10);
    if ((flags & 1) == 0) {
        if ((flags >> 1) & 1) { ((F0)Vt(owner)[0x18 / 4])(owner); return; }
        if ((flags >> 2) & 1) { ((F0)Vt(owner)[0x1c / 4])(owner); return; }
        if (((Fi0)Vt(owner)[0x30 / 4])(owner)) {
            ((F0)Vt(owner)[0x34 / 4])(owner);
            ArgScript_Output(*(void**)(p + 4), (const char*)0x01493c6c);
            ((F0)Vt(owner)[0x38 / 4])(owner);
        }
        if (((Fi0)Vt(owner)[0x14 / 4])(owner)) {
            ((F0)Vt(owner)[0x20 / 4])(owner);
            ArgScript_Output(*(void**)(p + 4), (const char*)0x01493c54);
        }
        if (*(void**)(p + 0xdc) != 0) {
            *(bool*)(p + 0xf4) = ((flags >> 7) & 1) != 0;
            *(bool*)(p + 0xf5) = ((flags >> 5) & 1) != 0;
            int key[3] = {0, 0, 0};
            SPKeyFromName(key, *(const char**)(p + 0xdc), 0, 0);
            if (!((Fi2)Vt(owner)[0x10 / 4])(owner, (int)key, (int)(p + 0xe0)))
                ArgScript_Output(*(void**)(p + 4), (const char*)0x01493c3c);
        }
    } else {
        *(bool*)(p + 0x10e) = (((flags >> 6) & 1) == 0);
        *(bool*)(p + 0x10c) = (((flags >> 3) & 1) == 0);
        *(bool*)(p + 0x10d) = ((flags >> 4) & 1) != 0;

        struct EString { void* b; void* e; void* c; void* a; } str;
        EA_ConvertToString16(&str, (const wchar_t*)*(void**)(p + 0xdc), -1);
        ((F2)Vt(owner)[0x2c / 4])(owner, (int)str.b, (int)(p + 0xf8));
        if ((((char*)str.e - (char*)str.b) & 0xfffffffe) > 2 && str.b)
            operator_delete(str.b);
    }
}

// @ 0x00fd90c0
bool MovieSys::Init()
{
    void* mm = FUN_0067dd70();
    ((void(__thiscall*)(void*, u32, void*, void*))VTP(mm)[0x2c / 4])(
        mm, 4, &DAT_01493980, raw + 0x24);

    void* p;
    p = FUN_00f473a0(0x20, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fcd940(4) : 0;
    *(void**)(raw + 0x0c) = p;

    p = FUN_00f473a0(0x3c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd9680() : 0;
    *(void**)(raw + 0x10) = p;

    p = FUN_00f473a0(0x1c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fc7dd0(FUN_00925cb0()) : 0;
    *(void**)(raw + 0x18) = p;

    p = FUN_00f473a0(0x24, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fc8080() : 0;
    *(void**)(raw + 0x1c) = p;

    p = FUN_00f473a0(0x0c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd95e0() : 0;
    *(void**)(raw + 0x14) = p;

    if (DAT_016f4b10 == 0) {
        void* x = FUN_011e58c0();
        void* tmp;
        E(&tmp)->FUN_011e64a0(0, x);
        FUN_011e5cd0(&tmp);
    }

    p = FUN_00f473a0(0x3c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fcde80() : 0;
    *(void**)(raw + 0x64) = p;
    ((void(__thiscall*)(void*, float))VTP(p)[0x34 / 4])(p, DAT_014007f4);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x44 / 4])(*(void**)(raw + 0x64), 0x2328);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x24 / 4])(*(void**)(raw + 0x64), 0x140);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x2c / 4])(*(void**)(raw + 0x64), 0xf0);

    if (DAT_016e61a8 != 0) {
        u32 v = (u32)(int)*(float*)((char*)DAT_016e61a8 + 0xc0);
        *(u32*)(raw + 0x328) = v;
        if (v > 0x5622) *(u32*)(raw + 0x328) = v >> 1;
    }

    p = FUN_00f473a0(0x20, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    if (p) {
        E(p)->FUN_00fc7f30();
        *(void**)p = &DAT_01493990;
    }
    *(void**)(raw + 0x68) = p;
    void** vt = (void**)(*(void**)p) ;
    ((void(__thiscall*)(void*, void*))vt[1])(p, FUN_00925cb0());
    ((void(__thiscall*)(void*, u32))VTP(*(void**)(raw + 0x68))[0x24 / 4])(*(void**)(raw + 0x68), *(u32*)(raw + 0x328));
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x68))[0x2c / 4])(*(void**)(raw + 0x68), 2);

    p = FUN_00f473a0(0x110, (const char*)DAT_013ebc58, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd8c40(this) : 0;
    void* cheat = FUN_0067de20();
    ((void(__thiscall*)(void*, const char*, void*, int))VTP(cheat)[0x18 / 4])(
        cheat, "movie", p, 0);

    void* param = raw + 8;
    void* ms;
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee1008);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee100e);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee100f);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x44edd9a);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x44edd9c);
    return true;
}
