// SP::cMovieSystem recording/playback entry points plus the anonymous-namespace
// "movie" cheat command.  Retail layout; flags /O2 /MD /Gy /TP /arch:SSE.
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
void* operator_new(unsigned int size, const char* group, int, int, int, int); // 0x00f473a0
void  operator_delete(void* p);
void* SP_MessageServer();                                   // 0x0067dcc0
void* FUN_0067dd50();                                       // 0x0067dd50
void* FUN_0067dda0();                                       // 0x0067dda0
void* EA_ResourceMan_GetManager();                          // 0x0067dcd0
void* EA_Audio_GetSystemAT();                               // 0x00a206f0
void* LockedAlloc(int,int,int,int,int,int);                 // 0x009289f0
void  MemPool_Free(void* thisp, void* p);                   // 0x009276c0
void* FUN_00fca2c0(void* p, int a);                         // 0x00fca2c0

extern void* g_pMutexTag;                                   // 0x01493900
extern void* g_defaultCameraRaster;                         // 0x015d0838
extern void* g_spMemPool;                                   // 0x016c8b44
extern void* g_appProperties;                               // 0x015fd918
extern float kFloat_13f0620;                                // 0x013f0620
extern float kFloat_1485720;                                // 0x01485720
extern float kFloat_1486374;                                // 0x01486374
extern float kFloat_14007f4;                                // 0x014007f4

// ---- cMovieSystem (retail offsets, see slice s00fd71e0) ---------------------
class cMovieSystem {
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

inline char* B(void* p) { return (char*)p; }

// @ 0x00fd8190
bool cMovieSystem::RecordMovie(int /*unused*/, int* pInfo)
{
    char* p = (char*)this;
    if (*(bool*)(p + 0xa0)) return false;
    if (!*(bool*)(p + 0xa1)) return false;

    void* mx = p + 0x70;
    ((EAMutex*)mx)->Lock((void*)0x01493900);

    void* sa = GetSaveArea((const char*)0x011ac197);
    int id = ((Fi0)Vt(sa)[0x28 / 4])(sa);

    wchar_t name[0x100];
    if (FUN_009309b0(name, (int)pInfo, id, 4) == 0) {
        ((EAMutex*)mx)->Unlock();
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
        ((EAMutex*)mx)->Unlock();
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
        void* au = EA_Audio_GetSystemAT();
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

    void* fb = FUN_0067dda0();
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
        void* hud = FUN_0067dd50();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)(p + 4), 0x25, 0);
    } else if (*(void**)(p + 0x34) == 0) {
        void* hud = FUN_0067dd50();
        ((F3)Vt(hud)[0x4c / 4])(hud, (int)(p + 4), 0x1b, 0);
    }

    ((EAMutex*)mx)->Unlock();
    ((F3)Vt(SP_MessageServer())[0x14 / 4])(SP_MessageServer(), 0x062ff413, 0, 0);
    ((EAMutex*)mx)->Lock((void*)0x01493900);
    ((EAMutex*)mx)->Unlock();
    return true;
}

// @ 0x00fd86f0
void cMovieSystem::SubmitFrame(int param)
{
    char* p = (char*)this;
    void* mx = p + 0x70;
    ((EAMutex*)mx)->Lock((void*)0x01493900);
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
        ((EAMutex*)mx)->Unlock();
        return;
    }
    MemPool_Free(*(void**)&g_spMemPool, (void*)param);
    ((EAMutex*)mx)->Unlock();
}

// @ 0x00fd87c0
bool cMovieSystem::PlayMovie(int /*unused*/, int* pInfo)
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
        if (EA_Audio_GetSystemAT() != 0) {
            *(bool*)(p + 0x20) = true;
        }
    } else {
        return false;
    }
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
