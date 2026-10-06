// Decompiled source for the Spore sim-movie module (bfs3 slice 40).
// SP::cMovieSystem methods; offsets are from the retail disassembly.
#include "types.h"

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
struct cContentValidationSummarizer { void Init(); };// 0x00fd7ab0

// callees
IMessageServer* SP_MessageServer();                  // 0x0067dcc0
ICheatManager*  SP_CheatManager();                   // 0x0067de20
IHud*           FUN_0067dd50();                      // 0x0067dd50
IFeedback*      FUN_0067dda0();                      // 0x0067dda0
IAudioSystem*   EA_Audio_GetSystemAT();              // 0x00a206f0
void            FUN_011330f0();                      // 0x011330f0
void            SetMaterialColor(void* thisp, const void* color); // 0x11eda00
bool            cViewer_Update(void* thisp);         // 0x007c4fd0
void            cViewer_PostFrame(void* thisp);      // 0x007c3c10
void            FUN_007c3c50(void* thisp, int);      // 0x007c3c50
void            Font_SetUserData(void* thisp, void* user); // 0x00fd9450
void            FileStream_ctor(void* p, int);       // 0x00931da0
void            FileStream_dtor(void* p);            // 0x00931e70
void*           operator_new(unsigned int size, const char* group, int, int, int, int);
void            operator_delete(void* p);
void            FillSpriteTexture(void* a, int b, int c); // 0x011f0440

extern float kFloat_14007f4;
extern float kFloat_1486374;
extern float kFloat_1485720;
extern float kFloat_1485378;
extern float kFloat_13f9428;
extern float kFloat_13f4fd0;
extern void* g_pMutexTag;                            // 0x01493900

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
void cContentValidationSummarizer::Init()
{
    char* p = (char*)this;
    *(void**)(p + 4) = (void*)0x13ec458;
    *(void**)(p + 8) = 0;
    *(void**)p = (void*)0x14939f4;
    *(void**)(p + 4) = (void*)0x14939e4;
    *(void**)(p + 0xc) = 0;
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

// @ 0x00fd7d80
void cMovieSystem::StopRecordingMovie(unsigned int dtMs)
{
    char* p = (char*)this;
    if (dtMs > 100)
        dtMs = 100;
    MoviePlayer* pl = *(MoviePlayer**)(p + 0x34);
    if (pl != 0) {
        float dt = (float)(int)dtMs;
        *(float*)(p + 0x60) = dt * kFloat_13f9428 + *(float*)(p + 0x60);
        if (pl->CanPlay())
            PauseMovie2();
    }
    if (!*(bool*)(p + 0xa0))
        return;
    EAMutex* mx = (EAMutex*)(p + 0x70);
    EAMutex_Lock(mx, g_pMutexTag);
    while (*(void**)(p + 0x31c) != p + 0x31c
           && EA_Audio_GetSystemAT() != 0) {
        void* n = *(void**)(p + 0x320);
        void* nn = *(void**)n;
        void* nn2 = *(void**)((char*)n + 4);
        *(void**)nn2 = nn;
        *(void**)((char*)nn + 4) = nn2;
        operator_delete(n);
        IAudioSystem* au = EA_Audio_GetSystemAT();
        au->v38_set(0x4640907);
        au->v40_call(0x4501144, 0x52de7b41);
        au->v48_call(0x45705b8, (void*)0xfd7730);
        
        au->v58();
    }
    EAMutex_Unlock(mx);
    float dt = (float)(int)dtMs;
    *(float*)(p + 0x310) = dt * kFloat_13f9428 + *(float*)(p + 0x310);
    float frame = *(float*)(p + 0xc0) * kFloat_13f9428 * dt + *(float*)(p + 0x314);
    *(float*)(p + 0x314) = frame;
    if (frame >= 1.0f) {
        int n = (int)frame;
        if (frame < (float)n) --n;
        n = RecordFrames(n);
        *(float*)(p + 0x314) = *(float*)(p + 0x314) - (float)n;
    }
    float t = *(float*)(p + 0xc4);
    if (t > 0.0f && t < *(float*)(p + 0x310)) {
        Shutdown();
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
