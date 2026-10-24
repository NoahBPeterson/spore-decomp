// Decompiled source for the Spore sim-movie module (bfs3 slice 40).
// SP::cMovieSystem methods; offsets are from the retail disassembly.
#include "types.h"
#include <intrin.h>

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
    virtual void* v18_call(int a, int b) = 0;         // +0x18
};

struct IInputHandler {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0;
    virtual void v28_call(int, int) = 0;              // +0x28
    virtual void v2c() = 0; virtual void v30() = 0; virtual void v34() = 0;
    virtual void v38_call(int, int) = 0;              // +0x38
};

struct BlitArgs { int a, b, c, d; };

// Primary-vtable view (slots 0x14 / 0x20 used above).
struct IMovieSystemMethods {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0;
    virtual bool IsPlaying() = 0;                      // +0x14
    virtual void v18() = 0; virtual void v1c() = 0;
    virtual void PauseMovie() = 0;                     // +0x20
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0;
    virtual void ShutdownV() = 0;                      // +0x38
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

// Resource objects released by Shutdown: [0]=Release(int), [4]=Close(), [8]=Stop().
struct IMovieResource {
    virtual void Release(bool b) = 0;                  // +0x00
    virtual void Close() = 0;                          // +0x04
    virtual void Stop() = 0;                           // +0x08
};

// UI layout node whose child has a direct non-virtual Shutdown(uint) method.
struct UILayoutChild {
    void Shutdown(uint32_t);                           // 0x00811ad0 (thiscall)
};

struct UILayoutBox {
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0c() = 0;
    void* mField4;               // +0x04
    void* mField8;               // +0x08
    void* mChild;                // +0x0c
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
    uint32_t mData[0xb];    // 0x2c bytes (EA::Thread::Mutex)
    void Lock(void* tag);   // 0x009221b0 (thiscall, ret 4)
    void Unlock();          // 0x00922270 (thiscall)
    void Construct(void* params, bool b);  // 0x009222a0 (thiscall)
};
// A float slot whose second byte is a separate flag (-0x48 area).
struct Field48 {
    uint8_t mPad48;              // +0x48
    bool    mField49;            // +0x49
    uint8_t mPad4a[2];           // +0x4a
};
// A float slot whose second byte is a separate flag (+0xc8 area).
struct FieldC8 {
    uint8_t mPadC8;              // +0xc8
    bool    mFieldC9;            // +0xc9
    uint8_t mPadCa[2];           // +0xca
};
// A packed dword at +0x324 whose second byte is a flag.
struct Field324 {
    uint8_t mPad324;             // +0x324
    bool    mField325;           // +0x325
    uint8_t mPad326[2];          // +0x326
};
struct EAFileStream {
    uint8_t mData[0x228];
    void Construct(const char* path);      // 0x00931da0 (thiscall)
};
void EAMutex_ctor(void* p, int, int);              // 0x009222a0
void EAMutex_dtor(void* p);                        // 0x00922130
void EAMutex_Lock(void* p, void* tag);             // 0x009221b0
void EAMutex_Unlock(void* p);                      // 0x00922270

struct PlayerFieldB8 {
    uint8_t mPad00[0x34];
    int mField34;                                      // +0x34
};

struct MoviePlayer {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0;
    virtual void v0c() = 0; virtual void v10() = 0; virtual void v14() = 0;
    virtual void v18() = 0; virtual void v1c() = 0; virtual void v20() = 0;
    virtual void v24() = 0; virtual void v28() = 0; virtual void v2c() = 0;
    virtual void v30() = 0; virtual void v34() = 0;
    virtual bool IsPlaying() = 0;                      // +0x38
    virtual void v3c() = 0;
    uint8_t mPad04[0xb4 - 0x04];                       // +0x04
    int mWidth;                                        // +0xb4
    PlayerFieldB8* mFieldB8;                           // +0xb8
    uint8_t mPadBc[0xf0 - 0xbc];                       // +0xbc
    float mFps;                                        // +0xf0
    uint8_t mPadF4[0x40];                              // +0xf4
    bool CanPlay();                                    // 0x00fcb470
    void Decode();                                     // 0x00fcb490
    void Render();                                     // 0x00fcb5e0
    void Play();                                       // 0x00fcb6e0
    void Stop();                                       // 0x00fcb710
    void Kill();                                       // 0x00fcb740
    void Shutdown();                                   // 0x00fcb860
};

struct MaterialSlot {
    void* mField0;                                     // +0x0
    void* mState;                                      // +0x4 (EmbeddedState*)
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
    MoviePlayer* mDrawPlayer;    // +0x30 (player rendered by DrawLayer)
    int mPlayerIndex;            // +0x34 (index into mMaterials for the active player)
    int mField38;                // +0x38
    float mFadeInTime;           // +0x3c
    float mFadeOutTime;          // +0x40
    float mField44;              // +0x44
    Field48 mField48;            // +0x48
    char mPad4c[4];
    void* mField50;              // +0x50
    void* mField54;              // +0x54
    void* mField58;              // +0x58
    float mField5c;              // +0x5c
    float mField60;              // +0x60
    void* mField64;              // +0x64
    void* mField68;              // +0x68
    uint32_t mField6c;           // +0x6c (draw-thread lock word)
    EAMutex mRecordMutex;        // +0x70 (EA::Thread::Mutex, 0x2c bytes)
    bool mField9c;               // +0x9c (record overlay active)
    char mPad9d[3];              // +0x9d
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
    FieldC8 mFieldC8;            // +0xc8
    bool mAudio;                 // +0xcc
    bool mExcludeUI;             // +0xcd
    bool mFieldCe;               // +0xce
    char mPadCf;
    EAFileStream mRecordStream;  // +0xd0
    int mField2f8;               // +0x2f8 (record-frame counter)
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
    Field324 mField324;          // +0x324
    bool mField328;              // +0x328
    char mPad329[3];
    bool mField32c;              // +0x32c
    bool mField32d;              // +0x32d

    void DrawLayer(int, int, int, int);              // 0x00fd7260
    char OnMovieMsg(int msg, int);                   // 0x00fd74f0
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

// callees
IMessageServer* SP_MessageServer();                  // 0x0067dcc0
ICheatManager*  SP_CheatManager();                   // 0x0067de20
IHud*           FUN_0067dd50();                      // 0x0067dd50
IFeedback*      FUN_0067dda0();                      // 0x0067dda0
IAudioSystem*   EA_Audio_GetSystemAT();              // 0x00a206f0
void            FUN_011330f0();                      // 0x011330f0
// Render-side object views used by DrawLayer (thiscall: object in ecx).
struct SPcViewer {
    void Clear(uint32_t);                       // 0x007c3c50 (thiscall)
    bool Update();                              // 0x007c4fd0 (thiscall)
    void PostFrame();                           // 0x007c3c10 (thiscall)
};
struct EmbeddedState {
    void SetMaterialColor(const void* color);   // 0x011eda00 (thiscall)
};
struct FontObj {
    void SetUserData(void* user);               // 0x00fd9450 (thiscall)
};
// D3D9 COM calls are __stdcall: the object is the first stack argument.
struct IComResource {
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08(void* self) = 0;           // +0x08
};
struct ID3DDevice9 {
    virtual void __stdcall v00()=0; virtual void __stdcall v04()=0;
    virtual void __stdcall v08()=0; virtual void __stdcall v0c()=0;
    virtual void __stdcall v10()=0; virtual void __stdcall v14()=0;
    virtual void __stdcall v18()=0; virtual void __stdcall v1c()=0;
    virtual void __stdcall v20()=0; virtual void __stdcall v24()=0;
    virtual void __stdcall v28()=0; virtual void __stdcall v2c()=0;
    virtual void __stdcall v30()=0; virtual void __stdcall v34()=0;
    virtual void __stdcall v38()=0; virtual void __stdcall v3c()=0;
    virtual void __stdcall v40()=0; virtual void __stdcall v44()=0;
    virtual void __stdcall v48(int, int, int, void**)=0;   // +0x48
    virtual void __stdcall v4c()=0; virtual void __stdcall v50()=0;
    virtual void __stdcall v54()=0; virtual void __stdcall v58()=0;
    virtual void __stdcall v5c()=0; virtual void __stdcall v60()=0;
    virtual void __stdcall v64()=0; virtual void __stdcall v68()=0;
    virtual void __stdcall v6c()=0; virtual void __stdcall v70()=0;
    virtual void __stdcall v74()=0; virtual void __stdcall v78()=0;
    virtual void __stdcall v7c()=0; virtual void __stdcall v80()=0;
    virtual void __stdcall v84()=0;
    virtual void __stdcall v88(void*, int, void*, int, int)=0;  // +0x88
};
struct IRasterSurf {
    virtual void __stdcall v00()=0; virtual void __stdcall v04()=0;
    virtual void __stdcall v08()=0; virtual void __stdcall v0c()=0;
    virtual void __stdcall v10()=0; virtual void __stdcall v14()=0;
    virtual void __stdcall v18()=0; virtual void __stdcall v1c()=0;
    virtual void __stdcall v20()=0; virtual void __stdcall v24()=0;
    virtual void __stdcall v28()=0; virtual void __stdcall v2c()=0;
    virtual void __stdcall v30()=0; virtual void __stdcall v34()=0;
    virtual void __stdcall v38()=0; virtual void __stdcall v3c()=0;
    virtual void __stdcall v40()=0; virtual void __stdcall v44()=0;
    virtual void __stdcall v48(int, void**)=0;  // +0x48
};
struct SpriteRaster {
    uint32_t mField0;           // +0x0
    uint32_t mField4;           // +0x4
    void*    mTexture;          // +0x8
    uint16_t mWidth;            // +0xc
    uint16_t mHeight;           // +0xe
    void FillSpriteTexture(int a, int b, int c);  // 0x011f0440 (thiscall)
};
extern SpriteRaster* g_pDefaultCameraRaster;        // 0x015d0838
extern ID3DDevice9*  g_pD3DDevice;                  // 0x016f89d0

void            FileStream_ctor(void* p, int);       // 0x00931da0
void            FileStream_dtor(void* p);            // 0x00931e70
void*           operator_new(unsigned int size, const char* group, int, int, int, int); // 0x00f473a0
void            operator_delete(void* p);

extern float kFloat_14007f4;
extern float kFloat_1486374;
extern float kFloat_1485720;
extern float kFloat_1485378;
extern float kFloat_13f9428;
extern float kFloat_13f4fd0;
extern void* g_pMutexTag;                            // 0x01493900
extern char g_MutexTagObj;                           // 0x01493900 (address is the tag)
struct PacketNode { PacketNode* next; PacketNode* prev; int payload; };

// @ 0x00fd71e0
void FUN_00fd71e0(int p1, int p2, int p3, int mode, IInputHandler* handler)
{
    int m;
    if (mode == 1) m = 0;
    else if (mode == 2) m = 2;
    else if (mode == 3) m = 1;
    else m = mode;
    handler->v28_call(p3, m);
    handler->v38_call(p1, p2);
}

// maxss/minss clamp: (min(max(0,x),1)), matching the original's NaN semantics.
static float Clamp01(float x)
{
    __m128 v = _mm_max_ss(_mm_setzero_ps(), _mm_set_ss(x));
    v = _mm_min_ss(v, _mm_set_ss(kFloat_1485720));
    return _mm_cvtss_f32(v);
}

// @ 0x00fd7260
void cMovieSystem::DrawLayer(int, int arg2, int viewerArg, int userData)
{
    SPcViewer** viewer = (SPcViewer**)viewerArg;
    MoviePlayer* pl = mDrawPlayer;
    if (pl != 0) {
        if (!mField328) {
            mField328 = true;
            SP_MessageServer()->PostMsg(0x49731a9, 0, 0);
        }
        if (!pl->CanPlay()) {
            pl->Decode();
            float one = kFloat_1485720;
            float color[4];
            color[0] = one;
            color[1] = one;
            color[2] = one;
            color[3] = one;
            if (mFadeInTime > 0.0f) {
                float r = mField5c / mFadeInTime;
                color[3] = Clamp01(r);
            }
            if (mFadeOutTime > 0.0f) {
                int n = (pl->mFieldB8 != 0) ? pl->mFieldB8->mField34 : 0;
                float x = (float)(uint32_t)(pl->mWidth - n - 1) / pl->mFps / mFadeOutTime;
                color[3] = color[3] * Clamp01(x);
            }
            if (mField48.mField49)
                (*viewer)->Clear(7);
            EmbeddedState* state = (EmbeddedState*)((MaterialSlot*)mMaterials[mPlayerIndex + 1])->mState;
            state->SetMaterialColor(color);
            if ((*viewer)->Update()) {
                ((FontObj*)mVideoDecoder)->SetUserData((void*)userData);
                pl->Render();
                ((FontObj*)mVideoDecoder)->SetUserData(0);
                (*viewer)->PostFrame();
            }
        }
    }
    EAMutex* drawMx = (EAMutex*)&mField6c;
    drawMx->Lock((void*)0x1493900);
    if (mField9c && (mFieldC8.mFieldC9 || arg2 == 0x25)) {
        SpriteRaster* raster = g_pDefaultCameraRaster;
        if ((uint32_t)raster->mWidth != (uint32_t)mWidth ||
            (uint32_t)raster->mHeight != (uint32_t)mHeight) {
            IFeedback* fb = FUN_0067dda0();
            SpriteRaster* nr = (SpriteRaster*)fb->v18_call(mCapturedFrames, mField304);
            void* tex = nr->mTexture;
            void* pA;
            void* pB;
            g_pD3DDevice->v48(0, 0, 0, &pA);
            ((IRasterSurf*)tex)->v48(0, &pB);
            g_pD3DDevice->v88(pA, 0, pB, 0, 2);
            ((IComResource*)pA)->v08(pA);
            ((IComResource*)pB)->v08(pB);
            raster = nr;
        }
        raster->FillSpriteTexture(mField308, mWidth * mHeight * 4, 0);
        ++mField2f8;
    }
    drawMx->Unlock();
}

// @ 0x00fd74f0
char cMovieSystem::OnMovieMsg(int msg, int)
{
    switch ((unsigned)msg) {
    case 0x1ee1008:
    case 0x1ee100f:
    case 0x44edd9a: {
        MoviePlayer* pl = (MoviePlayer*)mField2c;
        if (pl != 0 && !mField324.mField325) {
            pl->Play();
            mField324.mField325 = 1;
        }
        return 1;
    }
    case 0x1ee100e:
    case 0x44edd9c: {
        MoviePlayer* pl = (MoviePlayer*)mField2c;
        if (pl != 0 && mField324.mField325) {
            pl->Stop();
            mField324.mField325 = 0;
        }
        return 1;
    }
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
    EAMutex* mx = &mRecordMutex;
    mx->Lock((void*)0x1493900);
    if (mField2fc == 0) {
        mx->Unlock();
        return 0;
    }
    BlitArgs args;
    args.a = 3;
    args.b = mHeight;
    args.c = *(int*)&mFPS;
    args.d = (int)(intptr_t)mField30c;
    float quality = mFieldC0;
    if (quality < (float)nFrames)
        nFrames = _mm_cvtss_si32(_mm_set_ss(quality));
    int count = nFrames;
    if (nFrames > 0) {
        do {
            ((IVideoOps*)mWidth)->Blit2(args);
            ++mCapturedFrames;
        } while (--nFrames != 0);
    }
    mField2fc = 0;
    mx->Unlock();
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
    void* self2 = (void*)((char*)this + 8);
    SP_MessageServer()->PostMsg2((int)self2, 0x1ee1008, -0x270f);
    SP_MessageServer()->PostMsg2((int)self2, 0x1ee100e, -0x270f);
    SP_MessageServer()->PostMsg2((int)self2, 0x1ee100f, -0x270f);
    SP_MessageServer()->PostMsg2((int)self2, 0x44edd9a, -0x270f);
    SP_MessageServer()->PostMsg2((int)self2, 0x44edd9c, -0x270f);
    UILayoutBox* lb = (UILayoutBox*)mLetterbox;
    if (lb != 0) {
        UILayoutChild* child = (UILayoutChild*)lb->mChild;
        if (child != 0)
            child->Shutdown(1);
        IMovieResource* child2 = (IMovieResource*)lb->mChild;
        if (child2 != 0) {
            lb->mChild = 0;
            child2->Stop();
        }
        IMovieResource* lb2 = (IMovieResource*)mLetterbox;
        if (lb2 != 0) {
            mLetterbox = 0;
            lb2->Close();
        }
    }
    SP_CheatManager()->RunCheat("movie");
    ((IWindowCtl*)this)->v20();
    ((IWindowCtl*)this)->v38();
    IAudioSystem* au = EA_Audio_GetSystemAT();
    if (au != 0)
        au->v60();
    if (mVideoDecoder != 0) {
        ((IMovieResource*)mVideoDecoder)->Release(true);
        mVideoDecoder = 0;
        if (mVideoOps != 0)
            ((IMovieResource*)mVideoOps)->Release(true);
        mVideoOps = 0;
        if (mAudioDecoder != 0)
            ((IMovieResource*)mAudioDecoder)->Release(true);
        mAudioDecoder = 0;
    }
    if (mAudioRenderer != 0) {
        ((IMovieResource*)mAudioRenderer)->Release(true);
        mAudioRenderer = 0;
        if (mMaterials[0] != 0)
            ((IMovieResource*)mMaterials[0])->Release(true);
        mMaterials[0] = 0;
    }
    if (mField64 != 0) {
        ((IMovieResource*)mField64)->Stop();
        if (mField64 != 0)
            ((IMovieResource*)mField64)->Release(true);
        mField64 = 0;
    }
    if (mField68 != 0) {
        ((IMovieResource*)mField68)->Stop();
        if (mField68 != 0)
            ((IMovieResource*)mField68)->Release(true);
        mField68 = 0;
    }
    return true;
}

// @ 0x00fd79e0
bool cMovieSystem::StopMovie()
{
    char* p = (char*)this;
    MoviePlayer* pl = *(MoviePlayer**)(p + 0x34);
    if (pl == 0)
        return false;
    if (!*(bool*)(p + 0xa0) || !*(bool*)(p + 0xcd))
        FUN_0067dd50()->ShowHudMessage(0x1b);
    if (*(bool*)(p + 0x20) && EA_Audio_GetSystemAT() != 0)
        FUN_011330f0();
    pl->Kill();
    pl = *(MoviePlayer**)(p + 0x34);
    if (pl != 0) {
        pl->Shutdown();
        operator_delete(pl);
    }
    *(void**)(p + 0x34) = 0;
    *(float*)(p + 0x60) = 0.0f;
    void* lb = *(void**)(p + 0x318);
    if (lb != 0)
        ((IUILayoutObj*)*(void**)((char*)lb + 0xc))->v00_AddRef();
    SP_MessageServer()->PostMsg(0x49731ad, 0, 0);
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
// Original returns `this` in eax (constructor-style); the caller pushes it into
// AutoRefCount<IWinText>::operator=(ptr).
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
    mRecordMutex.Construct(0, true);
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
    mRecordStream.Construct(0);
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

// @ 0x00fd7d80
void cMovieSystem::StopRecordingMovie(unsigned int dtMs)
{
    char* p = (char*)this;
    if (dtMs > 100)
        dtMs = 100;
    MoviePlayer* pl = *(MoviePlayer**)(p + 0x34);
    if (pl != 0) {
        float dt = (float)dtMs;
        *(float*)(p + 0x60) = dt * kFloat_13f9428 + *(float*)(p + 0x60);
        if (pl->CanPlay())
            ((IMovieSystemMethods*)this)->PauseMovie();
    }
    if (!*(bool*)(p + 0xa0))
        return;
    EAMutex* mx = (EAMutex*)(p + 0x70);
    mx->Lock(&g_MutexTagObj);
    IAudioSystem* au = EA_Audio_GetSystemAT();
    while (*(void**)(p + 0x31c) != p + 0x31c && au != 0) {
        PacketNode* n = *(PacketNode**)(p + 0x320);
        int payload = n->payload;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        operator_delete(n);
        au->v38_set(0x4640907);
        au->v40_call(0x4501144, 0x52de7b41);
        au->v4c_call(0x4501150, &payload, 4);
        au->v48_call(0x45705b8, (void*)FUN_00fd7730);
        au->v48_call(0x45706c7, this);
        au->v58();
    }
    mx->Unlock();
    float dt = (float)dtMs;
    float frame = *(float*)(p + 0xc0) * kFloat_13f9428 * dt + *(float*)(p + 0x314);
    *(float*)(p + 0x310) = dt * kFloat_13f9428 + *(float*)(p + 0x310);
    *(float*)(p + 0x314) = frame;
    if (frame >= 1.0f) {
        float f = frame;
        int r;
        __asm {
            movss xmm0, f
            cvtss2si eax, xmm0
            mov r, eax
        }
        int n = (f < (float)r) ? r - 1 : r;
        n = RecordFrames(n);
        *(float*)(p + 0x314) = *(float*)(p + 0x314) - (float)n;
    }
    float t = *(float*)(p + 0xc4);
    if (t > 0.0f && t < *(float*)(p + 0x310)) {
        ((IMovieSystemMethods*)this)->ShutdownV();
        SP_MessageServer()->PostMsg(0x62ff415, 0, 0);
    }
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
// --- equivalence checker address annotations
    void operator_delete(...); // 0x00f47380
    void operator_new(...); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
