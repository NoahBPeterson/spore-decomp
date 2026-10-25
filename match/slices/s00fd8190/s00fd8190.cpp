// SP::cMovieSystem recording/playback entry points plus the anonymous-namespace
// "movie" cheat command.  Retail layout; flags /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-.
#include "types.h"

// ---- calling-convention aliases for indirect (vtable) calls -----------------
typedef void  (__thiscall *F0)(void*);
typedef void  (__thiscall *F1)(void*, int);
typedef void  (__thiscall *F2)(void*, int, int);
typedef void  (__thiscall *F3)(void*, int, int, int);
typedef void  (__thiscall *F4)(void*, int, int, int, int);
typedef void  (__thiscall *Fv)(void*, void*);
typedef void  (__thiscall *Fvv)(void*, void*, void*);
typedef void  (__thiscall *Fvvv)(void*, void*, void*, void*);
typedef int   (__thiscall *Fi0)(void*);
typedef void* (__thiscall *Fp0)(void*);
typedef void* (__thiscall *Fp1)(void*, int);
typedef void* (__thiscall *Fp7)(void*, int, int, int, int, int, int, int);
typedef int   (__thiscall *Fi2)(void*, int, int);
typedef void  (__thiscall *Ff1)(void*, float);
typedef int   (__thiscall *Fi4)(void*, int, int, int, int);
typedef void  (__thiscall *WAppendFn)(void*, const wchar_t*);

static inline void** Vt(void* o) { return *(void***)o; }

// ---- external helpers (addresses recorded for symbol resolution) ------------
struct EAMutex { int Lock(void* tag); int Unlock(); };       // 0x009221b0 / 0x00922270
void* GetSaveArea(const char* name);                        // 0x006b1f90
int   FUN_009309b0(void* buf, int a, int b, int c);         // 0x009309b0
void  EAMutex_Lock_Unused(void* p, void* tag);
void  EAMutex_Unlock_Unused(void* p);
void* GetDefaultAllocator();                                // 0x0041df40
void* ICoreAllocator_GetDefaultAllocator();                 // 0x00925cb0
void* operator_new(unsigned int size, const char* group, int, int, int, int); // 0x00f473a0
void  operator_delete(void* p);
void* SP_MessageServer();                                   // 0x0067dcc0
void* FUN_0067dd50();                                       // 0x0067dd50
void* FUN_0067dda0();                                       // 0x0067dda0
void* EA_ResourceMan_GetManager();                          // 0x0067dcd0
void* EA_Audio_GetSystemAT();                               // 0x00a206f0
void* LockedAlloc(int,int,int,int,int,int);                 // 0x009289f0
void __fastcall MemPool_Free(void* thisp, int edx, void* p); // 0x009276c0 (edx = dummy)
void* FUN_00fca2c0(void* p, int a);                         // 0x00fca2c0

// eastl::basic_string<char>::sprintf(this, fmt, ...) — cdecl, `this` pushed first
void __cdecl eastl_basic_string_sprintf_char(void* self, const char* fmt, ...); // 0x00472fe0

extern void* g_pMutexTag;                                   // 0x01493900
extern void* g_defaultCameraRaster;                         // 0x015d0838
extern void* g_spMemPool;                                   // 0x016c8b44
extern void* g_appProperties;                               // 0x015fd918
extern void* g_audioConfig;                                 // 0x016e61a8
extern float kFloat_13f0620;                                // 0x013f0620
extern float kFloat_1485720;                                // 0x01485720
extern float kFloat_1486374;                                // 0x01486374
extern float kFloat_14007f4;                                // 0x014007f4

// ---- cMovieSystem (retail layout; see slice s00fd71e0) ----------------------
struct BasicString {
    void* mpBegin;              // +0x00
    void* mpEnd;                // +0x04
    void* mpCapacity;           // +0x08
};

struct MoviePlayerLayout {
    char          mPad00[0xac];
    unsigned int  mFieldAC;     // +0xac
    unsigned int  mFieldB0;     // +0xb0
};

struct MovieLetterbox {
    char  mPad00[0xc];
    void* mLayout;              // +0x0c
};

struct HudSourceRect {
    int mWidth;                 // +0x00
    int mHeight;                // +0x04
};

struct AudioConfig {
    char  mPad00[0xc0];
    float mFieldC0;             // +0xc0
};

class cMovieSystem {
public:
    void* mVtbl0;               // +0x00
    void* mVtbl1;               // +0x04
    void* mVtbl2;               // +0x08
    void* mVideoDecoder;        // +0x0c
    void* mVideoOps;            // +0x10
    void* mAudioDecoder;        // +0x14
    void* mAudioRenderer;       // +0x18
    void* mField1c;             // +0x1c
    bool  mField20;             // +0x20
    char  mPad21[3];
    void* mMaterials[4];        // +0x24
    void* mPlayer;              // +0x34
    int   mField38;             // +0x38
    float mFadeInTime;          // +0x3c
    float mFadeOutTime;         // +0x40
    float mField44;             // +0x44
    int   mField48;             // +0x48
    union {
        int mField4cWord;       // +0x4c
        struct {
            bool mField4c;      // +0x4c
            bool mField4d;      // +0x4d
            char mPad4e[2];
        };
    };
    BasicString mPath0;         // +0x50  (eastl::basic_string<char>)
    int   mField5c;             // +0x5c
    float mFadeAlpha;           // +0x60
    void* mVideoEncoder;        // +0x64
    void* mAudioOutput;         // +0x68
    int   mField6c;             // +0x6c
    char  mRecordMutex[0x30];   // +0x70
    bool  mRecording;           // +0xa0
    bool  mFieldA1;             // +0xa1
    char  mPadA2[2];
    BasicString mRecordName;    // +0xa4  (eastl::basic_string<wchar_t>)
    int   mFieldB0;             // +0xb0
    void* mRecorder;            // +0xb4
    int   mWidth;               // +0xb8
    int   mHeight;              // +0xbc
    float mFPS;                 // +0xc0
    float mFieldC4;             // +0xc4
    float mFieldC8;             // +0xc8
    bool  mAudio;               // +0xcc
    bool  mExcludeUI;           // +0xcd
    char  mPadCe[2];
    char  mRecordStream[0x228]; // +0xd0
    int   mField2f8;            // +0x2f8
    int   mField2fc;            // +0x2fc
    int   mCapturedFrames;      // +0x300
    int   mField304;            // +0x304
    int   mField308;            // +0x308
    void* mFramePixels;         // +0x30c
    float mField310;            // +0x310
    float mField314;            // +0x314
    void* mLetterbox;           // +0x318
    void* mPacketList;          // +0x31c
    void* mPacketListTail;      // +0x320
    int   mField324;            // +0x324
    int   mAudioSampleRate;     // +0x328
    bool  mField32c;            // +0x32c
    char  mPad32d[3];

    bool RecordMovie(int pName, int* pInfo);        // 0x00fd8190
    void SubmitFrame(int param);                    // 0x00fd86f0
    bool PlayMovie(int pMovieInfo, int* pPlayParams); // 0x00fd87c0
};

inline char* B(void* p) { return (char*)p; }

// @ 0x00fd8190
bool cMovieSystem::RecordMovie(int pName, int* pInfo)
{
    if (mRecording) return false;
    if (!mFieldA1) return false;

    EAMutex* mx = (EAMutex*)mRecordMutex;
    mx->Lock((void*)0x01493900);

    void* sa = GetSaveArea((const char*)0x011ac197);
    int id = ((Fi0)Vt(sa)[0x28 / 4])(sa);

    wchar_t name[0x100];
    if (FUN_009309b0(name, pName, id, 4) == 0) {
        mx->Unlock();
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

    void* fs = mRecordStream;
    ((Fv)Vt(fs)[0x3c / 4])(fs, (void*)name);
    if (!((Fi4)Vt(fs)[0x4c / 4])(fs, 2, 2, 7, 0)) {
        mx->Unlock();
        return false;
    }

    for (int i = 0; i < 6; ++i)
        ((int*)((char*)this + 0xb8))[i] = pInfo[i];

    if (((char*)pInfo)[0x16] != 0) {
        char* cam = (char*)g_defaultCameraRaster;
        unsigned short h = *(unsigned short*)(cam + 0xc);
        unsigned short w = *(unsigned short*)(cam + 0xe);
        int x = pInfo[1] * h;
        int y = pInfo[0] * w;
        if (x < y)      mWidth = x / w;
        else if (x > y) mHeight = y / h;
    }

    void* enc = mVideoEncoder;
    int rate = (int)(mFieldC8 * kFloat_13f0620);
    ((F1)Vt(enc)[0x44 / 4])(enc, rate);
    ((Ff1)Vt(enc)[0x34 / 4])(enc, mFPS);
    ((F1)Vt(enc)[0x24 / 4])(enc, mWidth);
    ((F1)Vt(enc)[0x2c / 4])(enc, mHeight);
    ((Fv)Vt(enc)[0x04 / 4])(enc, ICoreAllocator_GetDefaultAllocator());

    void* rec = operator_new(0x74, "Graphics", 0, 0, 0, 0);
    if (rec) rec = ((void* (__thiscall*)(void*, int))0x00fca2c0)(rec, 0x4000);
    mRecorder = rec;

    ((Fvv)Vt(rec)[0x1c / 4])(rec, (void*)0x00fd71e0, (void*)mRecordStream);
    ((Fvv)Vt(rec)[0x14 / 4])(rec, (void*)0x00c2e4e0, (void*)0x01493a70);
    ((Fv)Vt(rec)[0x24 / 4])(rec, mVideoEncoder);

    if (mAudio) {
        void* au = EA_Audio_GetSystemAT();
        if (au) {
            AudioConfig* cfg = (AudioConfig*)g_audioConfig;
            if (cfg) {
                int sr = (int)cfg->mFieldC0;
                if (sr > 0x5622) sr >>= 1;
                mAudioSampleRate = sr;
            }

            void* bufs[200];
            for (int i = 0; i < 200; ++i)
                bufs[i] = ((void* (__thiscall*)(void*, int, int, int, int, int, int))0x009289f0)
                          (g_spMemPool, 0x800, 0, 0, 0, 0, 0);

            ((F1)Vt(au)[0x38 / 4])(au, 0x04640907);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04501144, 0x52de7b41);
            ((F3)Vt(au)[0x4c / 4])(au, 0x04501150, (int)bufs, 0x320);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x045705b8, (void*)0x00fd7730);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x045706c7, (void*)this);
            ((F0)Vt(au)[0x58 / 4])(au);
            ((F1)Vt(au)[0x38 / 4])(au, 0x045010e7);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04501144, 0x52de7b41);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04502374, 0x800);
            ((F2)Vt(au)[0x40 / 4])(au, 0x04597e49, mAudioSampleRate);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x045705b8, (void*)0x00fd7730);
            ((Fvv)Vt(au)[0x48 / 4])(au, (void*)0x045706c7, (void*)this);
            ((F0)Vt(au)[0x58 / 4])(au);

            void* ar = mAudioOutput;
            ((Fv)Vt(ar)[0x04 / 4])(ar, ICoreAllocator_GetDefaultAllocator());
            ((F1)Vt(ar)[0x24 / 4])(ar, mAudioSampleRate);
            ((F1)Vt(ar)[0x2c / 4])(ar, 2);
            ((Fv)Vt(rec)[0x2c / 4])(rec, mAudioOutput);
        }
    }

    ((Fv)Vt(rec)[0x04 / 4])(rec, ICoreAllocator_GetDefaultAllocator());

    void* fb = FUN_0067dda0();
    int probe[2];
    int* ret = (int*)((Fp7)Vt(fb)[0x10 / 4])(fb, (int)&probe,
                                              mWidth, mHeight,
                                              0x15, 0, -1, 0);
    mField304 = ret[0];
    mField308 = ret[1];
    mFramePixels = operator_new((unsigned)(mHeight * mWidth * 4), "Graphics", 0, 0, 0, 0);
    mCapturedFrames = 0;
    mField2fc = 0;
    ((F0)Vt(rec)[0x0c / 4])(rec);

    mField310 = 0.0f;
    mField314 = 1.0f;
    mField2fc = 0;
    mRecording = true;

    ((void (__thiscall*)(void*, const wchar_t*))0x005c3d90)
        ((void*)&mRecordName, (const wchar_t*)pName);

    if (!mExcludeUI) {
        void* hud = FUN_0067dd50();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)&mVtbl1, 0x25, 0);
    } else if (mPlayer == 0) {
        void* hud = FUN_0067dd50();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)&mVtbl1, 0x1b, 0);
    }

    mx->Unlock();
    void* ms = SP_MessageServer();
    ((F3)Vt(ms)[0x14 / 4])(ms, 0x062ff413, 0, 0);
    mx->Lock((void*)0x01493900);
    mx->Unlock();
    return true;
}

// @ 0x00fd86f0
void cMovieSystem::SubmitFrame(int param)
{
    EAMutex* mx = (EAMutex*)mRecordMutex;
    mx->Lock((void*)0x01493900);
    if (mRecording) {
        int vals[5];
        void* rec = mRecorder;
        vals[1] = mAudioSampleRate;
        vals[0] = 1;
        vals[2] = 2;
        vals[3] = 0x200;
        vals[4] = param;

        ((Fv)Vt(rec)[0x38 / 4])(rec, (void*)vals);

        int* head = (int*)&mPacketList;
        int* node = (int*)operator_new(0xc, "EASTL", 0, 0,
                                       (int)0x013ebb38, 0xd1);
        if (node + 2 != 0)
            node[2] = param;
        node[0] = (int)head;
        node[1] = head[1];
        *(int**)(head[1]) = node;
        head[1] = (int)node;
        mx->Unlock();
        return;
    }
    MemPool_Free(g_spMemPool, 0, (void*)param);
    mx->Unlock();
}

// @ 0x00fd87c0
bool cMovieSystem::PlayMovie(int pMovieInfo, int* pPlayParams)
{
    if (mPlayer != 0) return false;

    void* rm = EA_ResourceMan_GetManager();
    void* res = ((void* (__thiscall*)(void*, void*))Vt(rm)[0x58 / 4])(rm, (void*)pMovieInfo);
    if (res == 0) return false;

    int w = 0, h = 0;
    int type = ((int (__thiscall*)(void*))Vt(res)[0x0c / 4])(res);
    if (type == 0x034728492) {
        wchar_t wname[0x100];
        if (!((char (__thiscall*)(void*, int*, wchar_t*))Vt(res)[0x64 / 4])
                (res, (int*)pMovieInfo, wname))
            return false;
        const wchar_t* nm =
            ((const wchar_t* (__thiscall*)(void*))Vt(res)[0x28 / 4])(res);
        eastl_basic_string_sprintf_char((void*)&mPath0, "%ls%ls", nm, wname);
    } else {
        int out[4];
        if (!((char (__thiscall*)(void*, int*, int, int, int, int, int*))
                Vt(res)[0x34 / 4])(res, (int*)pMovieInfo, 0, 1, 6, 1, out))
            return false;
        if (out[3] != 0) return false;
        w = out[0];
        h = out[1];
        const wchar_t* nm =
            ((const wchar_t* (__thiscall*)(void*))Vt(res)[0x28 / 4])(res);
        eastl_basic_string_sprintf_char((void*)&mPath0, "%ls", nm);
    }

    void* alloc = ICoreAllocator_GetDefaultAllocator();
    void* player = operator_new(0x248, "Graphics", 0, 0, 0, 0);
    if (player)
        player = ((void* (__thiscall*)(void*, void*))0x00fca720)(player, alloc);
    mPlayer = player;

    int ptype = ((int*)pMovieInfo)[1];
    if (ptype == 0x041e19be) {
        ((void (__thiscall*)(void*, void*))0x00fca950)(player, (void*)0x00fc81f0);
        ((void (__thiscall*)(void*, void*))0x00fca970)(player, (void*)0x00fc8300);
        ((void (__thiscall*)(void*, void*))0x00fca990)(player, (void*)0x00fc8330);
    } else if (ptype == 0x0376840d7) {
        ((void (__thiscall*)(void*, void*))0x00fca950)(player, (void*)0x00fc85b0);
        ((void (__thiscall*)(void*, void*))0x00fca970)(player, (void*)0x00fc8620);
        ((void (__thiscall*)(void*, void*))0x00fca990)(player, (void*)0x00fc8640);
        if (EA_Audio_GetSystemAT() != 0) {
            ((void (__cdecl*)(int))0x01133120)(0);
            ((void (__cdecl*)(void))0x01133250)();
            ((void (__thiscall*)(void*, void*))0x00fca9d0)(player, mAudioRenderer);
            mField20 = true;
            ((void (__thiscall*)(void*, void*))0x00fcaa10)(player, mField1c);
        }
    } else {
        return false;
    }

    ((void (__thiscall*)(void*, void*))0x00fca9b0)(player, mVideoDecoder);
    ((void (__thiscall*)(void*, void*))0x00fca9f0)(player, mVideoOps);
    ((void (__thiscall*)(void*, void*))0x00fcaa40)(player, mAudioDecoder);

    int ok = ((int (__thiscall*)(void*, void*, unsigned __int64, unsigned __int64))
              0x00fcaa70)(player, mPath0.mpBegin,
                          (unsigned __int64)w, (unsigned __int64)h);
    if (ok != 0) {
        ((void (__thiscall*)(void*))0x00fcb740)(player);
        if (mPlayer != 0) {
            ((void (__thiscall*)(void*))0x00fcb860)(mPlayer);
            ((void (__cdecl*)(void*))0x00f47380)(mPlayer);
        }
        mPlayer = 0;
        return false;
    }

    ((void (__thiscall*)(void*, int, int))0x00fcab70)(player, 0x400000, 0);
    if (!((char (__thiscall*)(void*, int))0x00fcb920)(player, 1)) {
        ((void (__thiscall*)(void*))0x00fcb740)(player);
        if (mPlayer != 0) {
            ((void (__thiscall*)(void*))0x00fcb860)(mPlayer);
            ((void (__cdecl*)(void*))0x00f47380)(mPlayer);
        }
        mPlayer = 0;
        return false;
    }

    if (mFadeInTime > 0.0f) {
        ((void (__thiscall*)(void*, float))0x00fcb1b0)(player, mFadeInTime);
        ((void (__thiscall*)(void*, float))0x00fcb1e0)(player, mFadeInTime);
    } else {
        void* hud = FUN_0067dd50();
        HudSourceRect* src =
            (HudSourceRect*)((void* (__thiscall*)(void*))Vt(hud)[0x1c / 4])(hud);
        MoviePlayerLayout* pl = (MoviePlayerLayout*)player;
        float ratioY = (float)src->mHeight / (float)pl->mFieldB0;
        float ratioX = (float)src->mWidth / (float)pl->mFieldAC;
        float mn = (ratioX > ratioY) ? ratioY : ratioX;
        ((void (__thiscall*)(void*, float))0x00fcb1b0)(player, mn);
        ((void (__thiscall*)(void*, float))0x00fcb1e0)(player, ratioY);
        float r1 = (float)src->mWidth - (float)pl->mFieldAC * ratioY;
        if (r1 < 0.0f) r1 = 0.0f;
        ((void (__thiscall*)(void*, float))0x00fcb150)(player, r1 * 0.5f);
        float r2 = (float)src->mHeight - (float)pl->mFieldB0 * ratioY;
        if (r2 < 0.0f) r2 = 0.0f;
        ((void (__thiscall*)(void*, float))0x00fcb180)(player, r2 * 0.5f);
    }

    mField38 = pPlayParams[0];
    *(int*)&mFadeInTime = pPlayParams[1];
    *(int*)&mFadeOutTime = pPlayParams[2];
    *(int*)&mField44 = pPlayParams[3];
    mField48 = pPlayParams[4];
    mField4cWord = pPlayParams[5];

    if (mField4c) {
        if (mLetterbox == 0) {
            void* lb = operator_new(0x10, "App", 0, 0, 0, 0);
            if (lb) lb = ((void* (__thiscall*)(void*))0x00fd7ab0)(lb);
            ((void (__thiscall*)(void*, void*))0x00b5f950)(&mLetterbox, lb);
        }
        if (mLetterbox != 0) {
            ((void (__thiscall*)(void*))0x00fd7750)(mLetterbox);
            ((void (__thiscall*)(void*, int))0x00810590)
                (((MovieLetterbox*)mLetterbox)->mLayout, 1);
        }
    }

    ((void (__thiscall*)(void*, void*))0x00fccdd0)
        (mVideoOps, mMaterials[mField38]);

    void* hud = FUN_0067dd50();
    ((void (__thiscall*)(void*, void*, int, int))Vt(hud)[0x4c / 4])
        (hud, (void*)&mVtbl1, 0x1b, 0);
    if (mField4d) {
        hud = FUN_0067dd50();
        ((void (__thiscall*)(void*, int, int))Vt(hud)[0x5c / 4])(hud, 0x1b, 2);
    }

    mFadeAlpha = 0.0f;
    mField32c = false;
    return true;
}

// ===========================================================================
//  cMovieCheat (anonymous namespace): the "movie" cheat command.
// ===========================================================================
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
