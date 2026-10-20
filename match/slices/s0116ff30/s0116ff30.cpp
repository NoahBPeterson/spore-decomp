// rw::audio::core::HELPER_CMpegBase - MPEG audio (layer 2/3) helper base.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

// forward declarations of the real callees (absolute VAs)
struct RwSystem {
    void* Alloc(u32 size, const char* name, int align, int flags);   // 0x0112c820
    void  Free(void* p, int flags);                                  // 0x0112c850
};
extern "C" RwSystem* g_rwSystem;             // 0x016e61a8
extern "C" int   g_d_016f1840;               // 0x016f1840
extern "C" char  g_d_014daaa0;               // 0x014daaa0  vftable
extern "C" char  g_d_014dabd8;               // 0x014dabd8  vftable
extern "C" char  g_t_014dab04;               // 0x014dab04  sample-rate table (u16[])
extern "C" char  g_t_014daaf8;               // 0x014daaf8  bitrate table (s16[])
extern "C" char  g_s_014dabec;               // 0x014dabec  "PolySynthHistoryS"
extern "C" char  g_s_014ce518;               // 0x014ce518  "PolySynthHistoryF"

void* operator_new__(void* p, int v, u32 size);   // 0x011e073e
void  __cdecl operator_delete__(void* p);         // 0x00f47380

struct CMpegBase {
    void* vftable;          // 0x00
    int   mSampFreq;        // 0x04
    int   mRealSampFreq;    // 0x08
    int   mBitRate;         // 0x0c
    int   cFrameSize;       // 0x10
    u16   mFrameSamples;    // 0x14
    u8    mLayer;           // 0x16
    u8    pad17;            // 0x17
    u8*   mBufPtr;          // 0x18
    u8*   mBufPtrBase;      // 0x1c
    u8*   mBufPtrNext;      // 0x20
    u32   mShiftReg;        // 0x24
    int   mShiftRegBits;    // 0x28
    u8    mBandOffset0;     // 0x2c
    u8    mBandOffset1;     // 0x2d
    u8    mMPEG25;          // 0x2e
    u8    mLSF;             // 0x2f
    u8    sfreq;            // 0x30
    u8    pad31;            // 0x31
    u8    mVersion;         // 0x32
    u8    mErrorProt;       // 0x33
    u8    mBitRateIdx;      // 0x34
    u8    mSampFreqIdx;     // 0x35
    u8    mPadding;         // 0x36
    u8    mMode;            // 0x37
    u8    mModeExt;         // 0x38
    u8    mCopyright;       // 0x39
    u8    mOriginal;        // 0x3a
    u8    mOpened;          // 0x3b
    u8    mChannels;        // 0x3c
    u8    pad3d[3];         // 0x3d
    int   mHeader;          // 0x40
    void* mpHistory;        // 0x44

    CMpegBase* Ctor();                        // 0x01170210
    void   Seek(u8* p);                       // 0x01170120
    int    OpenSynth();                       // 0x01170230
    int    ProcessHeader(u32 h);              // 0x011702c0
    int    FUN_01170480();                    // 0x01170480
    int    OpenLayer();                       // 0x011704d0
    void   FUN_01170500();                    // 0x01170500
    int    FUN_01170510();                    // 0x01170510
    __declspec(noinline) void FUN_01170540(); // 0x01170540
    void*  ScalarDeletingDtor2(u8 flags);     // 0x01170570
    int    Open(int buf, int unused);         // 0x011705b0
    void*  ScalarDeletingDtor(u8 flags);      // 0x011700e0
};

float* CopyArr(void* dstBase, CMpegBase* src); // 0x0116ff30
int  CpuHasSSE();                             // 0x01170140

// @ 0x0116ff30
float* CopyArr(void* dstBase, CMpegBase* src)
{
    float* v = (float*)dstBase;
    float* w = (float*)src;
    for (int i = 0; i < 0x900 / 0x120; ++i) {
        float* vv = v + i * 4;
        float* ww = w + i * 0x20;
        ww[0] = vv[0]; ww[1] = vv[1]; ww[2] = vv[2]; ww[3] = vv[3];
        ww[0x2] = vv[0x46]; ww[0x3] = vv[0x47]; ww[0x4] = vv[0x48]; ww[0x5] = vv[0x49];
        ww[0x6] = vv[0x8e]; ww[0x7] = vv[0x8f]; ww[0x8] = vv[0x90]; ww[0x9] = vv[0x91];
        ww[0xa] = vv[0xd6]; ww[0xb] = vv[0xd7]; ww[0xc] = vv[0xd8]; ww[0xd] = vv[0xd9];
        ww[0xe] = vv[0x11e]; ww[0xf] = vv[0x11f]; ww[0x10] = vv[0x120]; ww[0x11] = vv[0x121];
        ww[0x12] = vv[0x166]; ww[0x13] = vv[0x167]; ww[0x14] = vv[0x168]; ww[0x15] = vv[0x169];
        ww[0x16] = vv[0x1ae]; ww[0x17] = vv[0x1af]; ww[0x18] = vv[0x1b0]; ww[0x19] = vv[0x1b1];
        ww[0x1a] = vv[0x1f6]; ww[0x1b] = vv[0x1f7]; ww[0x1c] = vv[0x1f8]; ww[0x1d] = vv[0x1f9];
    }
    return w;
}

// @ 0x011700e0
void* CMpegBase::ScalarDeletingDtor(u8 flags)
{
    void* h = *(void**)((char*)this + 0x1c8);
    this->vftable = &g_d_014daaa0;
    if (h != 0)
        g_rwSystem->Free(h, 0);
    this->FUN_01170540();
    if ((flags & 1) != 0)
        operator_delete__(this);
    return this;
}

// @ 0x01170120
void CMpegBase::Seek(u8* p)
{
    this->mBufPtr = p;
    this->mBufPtrBase = p;
    this->mBufPtrNext = p;
    this->mShiftReg = 0;
    this->mShiftRegBits = 0;
}

// @ 0x01170140
int CpuHasSSE()
{
    int family, model, ecx_out, edx_out;
    __asm {
        mov eax, 1
        xor ecx, ecx
        cpuid
        mov family, eax
        mov model, ebx
        mov ecx_out, ecx
        mov edx_out, edx
    }
    if ((edx_out & 0x800000) == 0)
        return -256;
    __asm emms;
    return -255;
}

// @ 0x01170210
CMpegBase* CMpegBase::Ctor()
{
    CMpegBase* q = this;
    q->vftable = &g_d_014dabd8;
    q->mOpened = 0;
    q->mHeader = 0;
    return q;
}

// @ 0x01170230
int CMpegBase::OpenSynth()
{
    void* p;
    if (g_d_016f1840 != 0) {
        p = g_rwSystem->Alloc(9 * (u32)this->mChannels * 0x80, &g_s_014dabec, 0x10, 0);
        this->mpHistory = p;
        if (p == 0)
            return -1;
        operator_new__(p, 0, 9 * (u32)this->mChannels * 0x80);
        return 0;
    }
    p = g_rwSystem->Alloc(9 * (u32)this->mChannels * 0x100, &g_s_014ce518, 0x10, 0);
    this->mpHistory = p;
    if (p == 0)
        return -1;
    operator_new__(p, 0, 9 * (u32)this->mChannels * 0x100);
    return 0;
}

// @ 0x011702c0
int CMpegBase::ProcessHeader(u32 h)
{
    if ((h & 0xffe00000) != 0xffe00000)
        return -1;
    u8 layer = (u8)(4 - ((h >> 0x11) & 3));
    u8 pad = (u8)((h >> 9) & 1);
    this->mPadding = pad;
    u8 mode = (u8)((h >> 6) & 3);
    this->mMode = mode;
    this->mModeExt = (u8)((h >> 4) & 3);
    this->mLayer = layer;
    this->mCopyright = (u8)((h >> 3) & 1);
    this->mErrorProt = (u8)((h >> 0x10) & 1);
    this->mOriginal = (u8)((h >> 2) & 1);
    u8 brIdx = (u8)((h >> 0xc) & 0xf);
    this->mVersion = (u8)((h >> 0x13) & 1);
    this->mBitRateIdx = brIdx;
    if (layer == 4 || brIdx == 0xf)
        return -1;
    if ((h & 0x100000) != 0) {
        this->mLSF = (this->mVersion == 0);
        this->mMPEG25 = 0;
    } else {
        this->mLSF = 1;
        this->mMPEG25 = 1;
    }
    u8 sfIdx = (u8)((h >> 10) & 3);
    if (this->mMPEG25 == 0) {
        this->mSampFreqIdx = (u8)(this->mLSF * 3 + sfIdx);
        this->sfreq = (u8)(((this->mLSF != 0 ? 0 : 0xffffffffu) & 3) + sfIdx);
    } else {
        this->mSampFreqIdx = (u8)(sfIdx + 6);
    }
    this->mChannels = (u8)((mode != 3) + 1);
    u16 sr = *(u16*)((char*)&g_t_014dab04 + (u32)this->mSampFreqIdx * 2);
    this->mSampFreq = (u32)sr;
    this->mRealSampFreq = (u32)sr;
    if (((h >> 0xc) & 0xf) == 0)
        return -1;
    int br = (int)*(s16*)((char*)&g_t_014daaf8
             + (((u32)this->mLSF * 3 + (u32)layer) * 0x10 + (u32)brIdx) * 2);
    this->mBitRate = br;
    if (layer == 1) {
        this->cFrameSize = ((br * 12000) / this->mRealSampFreq + (u32)pad) * 4;
        this->cFrameSize += -4;
        return 0x180;
    }
    int fs = (br * 0x23280) / this->mRealSampFreq;
    int ret = 0x480;
    this->cFrameSize = fs;
    if (layer == 3 && this->mLSF != 0) {
        this->cFrameSize = fs >> 1;
        ret = 0x240;
    }
    if (pad != 0)
        this->cFrameSize += 1;
    this->cFrameSize += -4;
    return ret;
}

// @ 0x01170480
int CMpegBase::FUN_01170480()
{
    int r;
    if (this->mBufPtr == 0) {
        int h = this->mHeader;
        void** vt = *(void***)this;
        r = ((int (__thiscall*)(CMpegBase*, int))vt[1])(this, h);
    } else {
        u32 w = this->mBufPtr[1] + ((u32)this->mBufPtr[0] << 8);
        w = (w << 8) + this->mBufPtr[2];
        w = (w << 8) + this->mBufPtr[3];
        void** vt = *(void***)this;
        r = ((int (__thiscall*)(CMpegBase*, u32))vt[1])(this, w);
    }
    return (r + 1 != 0) - 1;
}

// @ 0x011704d0
int CMpegBase::OpenLayer()
{
    this->mFrameSamples = 0x480;
    if (this->mLSF != 0)
        this->mFrameSamples = 0x240;
    this->mBandOffset0 = 1;
    this->mBandOffset1 = 1;
    return 0;
}

// @ 0x01170500
void CMpegBase::FUN_01170500()
{
    this->mBufPtrNext = this->mBufPtr;
    this->mShiftReg = 0;
    this->mShiftRegBits = 0;
}

// @ 0x01170510
int CMpegBase::FUN_01170510()
{
    if (this->mOpened != 0) {
        this->mHeader = 0;
        this->mOpened = 0;
        if (this->mpHistory != 0)
            g_rwSystem->Free(this->mpHistory, 0);
    }
    return 0;
}

// @ 0x01170540
void CMpegBase::FUN_01170540()
{
    this->vftable = &g_d_014dabd8;
    if (this->mOpened != 0) {
        this->mHeader = 0;
        this->mOpened = 0;
        if (this->mpHistory != 0)
            g_rwSystem->Free(this->mpHistory, 0);
    }
}

// @ 0x01170570
void* CMpegBase::ScalarDeletingDtor2(u8 flags)
{
    this->vftable = &g_d_014dabd8;
    if (this->mOpened != 0) {
        this->mHeader = 0;
        this->mOpened = 0;
        if (this->mpHistory != 0)
            g_rwSystem->Free(this->mpHistory, 0);
    }
    if ((flags & 1) != 0)
        operator_delete__(this);
    return this;
}

// @ 0x011705b0
int CMpegBase::Open(int buf, int unused)
{
    if (this->mOpened != 0) {
        void* h = this->mpHistory;
        this->mHeader = 0;
        this->mOpened = 0;
        if (h != 0)
            g_rwSystem->Free(h, 0);
    }
    this->mOpened = 1;
    this->mBufPtr = (u8*)buf;
    this->mBufPtrBase = (u8*)buf;
    if (buf == 0)
        return -1;
    if (this->FUN_01170480() != 0)
        return -1;
    if (this->OpenSynth() < 0)
        return -1;
    ((void (__thiscall*)(CMpegBase*))(*(void***)this)[0x10 / 4])(this);
    this->mBufPtrNext = this->mBufPtr;
    this->mShiftReg = 0;
    this->mShiftRegBits = 0;
    return 0;
}
