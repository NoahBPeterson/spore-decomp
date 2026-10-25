// Decompiled slice s00fc7430 -- rw::movie audio codec / stream helpers.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct Vtbl { void* p[64]; };

typedef int  (__thiscall* FnInt)(void*);
typedef void (__thiscall* FnVoid2)(void*, void*, int);

struct AudioSamples {
  int mTag;        // +0x00
  int mRate;       // +0x04
  int mChannels;   // +0x08
  int mBits;       // +0x0c
  int mCount;      // +0x10
};

// rw::movie::AudioDecoder_Snd9 (vtable 0x014916c0)
struct StreamA {
  Vtbl* mpVtable;      // +0x00
  void* mpField04;     // +0x04
  void* mpCallback08;  // +0x08
  void* mpErrorCb0c;   // +0x0c
  void* mpField10;     // +0x10
  int   mStreamHandle; // +0x14
  int   mField18;      // +0x18
  int   mField1c;      // +0x1c

  StreamA(void* arg);            // 0x00fc7dd0
  void  Shutdown();              // 0x00fc7ce0
  void  SetStreamTapHandle(void* stream, int requestId); // 0x00fc7d20
  int   FUN_00fc7e60();          // 0x00fc7e60
  unsigned FUN_00fc7e90();       // 0x00fc7e90
  unsigned FUN_00fc7eb0();       // 0x00fc7eb0
  void  FUN_00fc7ec0(AudioSamples* samples); // 0x00fc7ec0
};

struct Allocator {
  virtual void  v00();
  virtual void* Alloc(int a, const char* name, int b, int c, int d);
  virtual void  v08();
  virtual void  Release(void* p, int v);
};

struct StreamObj {
  void FUN_011e7cf0();
};

struct StreamParams {
  int mField0;
  int mField4;
  int mField8;
  int mFieldC;
};

// rw::movie::AudioDecoder_Snd9 (vtable 0x014917c0)
struct StreamB {
  Vtbl* mpVtable;      // +0x00
  void* mpField04;     // +0x04
  int   mField08;      // +0x08
  int   mField0c;      // +0x0c
  void* mpField10;     // +0x10
  void* mpPackedFile;  // +0x14
  int   mField18;      // +0x18
  int   mField1c;      // +0x1c
  float mGain20;       // +0x20

  StreamB();                     // 0x00fc8080
  float FUN_00fc7f90();          // 0x00fc7f90
  void  SetGain(float gain);     // 0x00fc8000
  void  FUN_00fc8040();          // 0x00fc8040
  void  FUN_00fc8060();          // 0x00fc8060
  void  FUN_00fc80b0();          // 0x00fc80b0
};

struct StreamC {
  Vtbl* mpVtable;      // +0x00
  int   mField04;      // +0x04
  int   mField08;      // +0x08
  int   mField0c;      // +0x0c
  int   mField10;      // +0x10
  int   mField14;      // +0x14
  int   mField18;      // +0x18
  int   mField1c;      // +0x1c

  StreamC();                     // 0x00fc7f30
};

struct StreamD {
  int mField00;        // +0x00
  int mField04;        // +0x04
  int mField08;        // +0x08
  int mField0c;        // +0x0c
  int mField10;        // +0x10
  int mField14;        // +0x14
  int mField18;        // +0x18
  int mField1c;        // +0x1c

  StreamD();                     // 0x00fc8350
};

struct StreamE {
  void* mpField00;     // +0x00
  void* mpField04;     // +0x04

  void Set(void* a, void* b);    // 0x00fc8370
};

struct StreamF {
  void* mpField00;     // +0x00

  void* Get();                   // 0x00fc8380
};

namespace rw { namespace movie {
struct BufferedWriter {
  uint8_t mPad00[8];   // +0x00
  void*   mpBuffer08;  // +0x08
  int     mSize0c;     // +0x0c
  int     mOffset10;   // +0x10

  void SetBuffer(void* buf, int size);  // 0x00fc8390
};
}}

struct DatabasePackedFile {
  int GetAccessFlags();          // 0x00ff0420
  int FUN_006c0200();            // 0x006c0200
};

struct ReleaseIface {
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void Release(void* p, int v);
};

struct Blob38 { uint32_t m[14]; };
struct Blob28 { uint32_t m[10]; };
struct Blob10 { uint32_t m[4]; };

typedef void (__cdecl* FnCB5)(int, int, int, int, int);

struct Writer {
  FnCB5 mpCallback;    // +0x00
  int   mField04;      // +0x04
  int   mField08;      // +0x08
  int   mField0c;      // +0x0c
  int   mField10;      // +0x10
  int   mField14;      // +0x14
  int   mField18;      // +0x18
  int   mField1c;      // +0x1c

  void Flush();        // 0x00fc83b0
};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void AudioLock();                                   // 0x01133450
void AudioUnlock();                                 // 0x01133460
void FUN_011335a0(int stream, void* out);           // 0x011335a0
void FUN_01133470(int value, void* out);            // 0x01133470
void FUN_011336b0(void* stream, int flag, float v); // 0x011336b0
void FUN_011339d0(void* stream, int flags);         // 0x011339d0
void FUN_01133a20(int handle, int flags);           // 0x01133a20
void rw_audio_core_SndStream_destroy(int handle);   // 0x01132a10
int  FUN_01133020(int a, int b);                    // 0x01133020
void FUN_01132fe0(void* p);                         // 0x01132fe0
int  FUN_01132fb0(void* stream, void* params, int a, int b, void* buf, int c); // 0x01132fb0
int  FUN_01132f90(int handle, int flag, int request); // 0x01132f90

// ===========================================================================
// 0x00fc7ce0 -- stop the stream and release the tap
// ===========================================================================
// @ 0x00fc7ce0
void StreamA::Shutdown()
{
  if (mStreamHandle >= 0)
    rw_audio_core_SndStream_destroy(mStreamHandle);

  if (mpField04 != 0 && mpField10 != 0) {
    ((ReleaseIface*)mpField04)->Release(mpField10, 0);
    mpField10 = 0;
  }
}

// ===========================================================================
// 0x00fc7d20 -- rw::movie::AudioDecoder_Snd9::SetStreamTapHandle
// ===========================================================================
// @ 0x00fc7d20
void StreamA::SetStreamTapHandle(void* stream, int requestId)
{
  mpCallback08 = stream;
  mpErrorCb0c = (void*)requestId;
  if (stream != 0) {
    int id = FUN_01133020(1, 0x1e);
    mpField10 = ((Allocator*)mpField04)->Alloc(id, "tapOverhead", 1, 0x10, 0);

    StreamParams params;
    FUN_01132fe0(&params);

    mStreamHandle = FUN_01132fb0(mpCallback08, &params, 1, 0x1e, mpField10, id);
    if (mStreamHandle < 0) {
      ((StreamObj*)mpCallback08)->FUN_011e7cf0();
      ((Allocator*)mpField04)->Release(mpField10, 0);
      mpField10 = 0;
    }
    if (mpErrorCb0c != 0)
      mField18 = FUN_01132f90(mStreamHandle, -1, (int)mpErrorCb0c);
  }
}

// ===========================================================================
// 0x00fc7dd0 -- rw::movie::AudioDecoder_Snd9 constructor
// ===========================================================================
// @ 0x00fc7dd0
StreamA::StreamA(void* arg)
{
  mpField04 = arg;
  mpCallback08 = 0;
  mpErrorCb0c = 0;
  mpField10 = 0;
  mpVtable = (Vtbl*)0x14916c0;
  mStreamHandle = -1;
  mField18 = -1;
}

// ===========================================================================
// 0x00fc7e60 -- frame count * bytes/sample * channels
// ===========================================================================
// @ 0x00fc7e60
int StreamA::FUN_00fc7e60()
{
  return ((FnInt)mpVtable->p[15])(this) * mField1c * mField18;
}

// ===========================================================================
// 0x00fc7e90 -- (frame count * bytes/sample) / 8
// ===========================================================================
// @ 0x00fc7e90
unsigned StreamA::FUN_00fc7e90()
{
  return (unsigned)(((FnInt)mpVtable->p[15])(this) * mField1c) >> 3;
}

// ===========================================================================
// 0x00fc7eb0 -- quarter of the stream block size
// ===========================================================================
// @ 0x00fc7eb0
unsigned StreamA::FUN_00fc7eb0()
{
  return (unsigned)((FnInt)mpVtable->p[13])(this) >> 2;
}

// ===========================================================================
// 0x00fc7ec0 -- encode accepted audio samples
// ===========================================================================
// @ 0x00fc7ec0
void StreamA::FUN_00fc7ec0(AudioSamples* samples)
{
  if (samples->mTag == 1 && samples->mRate == mField18 &&
      samples->mChannels == mField1c) {
    unsigned size = (unsigned)(((FnInt)mpVtable->p[15])(this) *
                               samples->mBits * samples->mChannels) >> 3;
    if (mpCallback08 != 0) {
      ((void (__cdecl*)(int, unsigned, void*))mpCallback08)(
          samples->mCount, size, mpField10);
      return;
    }
  } else if (mpErrorCb0c != 0) {
    ((void (__cdecl*)(const char*, int))mpErrorCb0c)(
        "AudioEncoder_Pcm: the supplied AudioSamples object has the wrong sampling properties.",
        mStreamHandle);
  }
}

// ===========================================================================
// 0x00fc7f30 -- constructor (vtable 0x01491730)
// ===========================================================================
// @ 0x00fc7f30
StreamC::StreamC()
{
  mpVtable = (Vtbl*)0x1491730;
  mField04 = 0;
  mField08 = 0;
  mField0c = 0;
  mField18 = 0;
  mField1c = 0;
}

// ===========================================================================
// 0x00fc7f80 -- Simulator::cBuilding::GetCost
// ===========================================================================
// @ 0x00fc7f80
namespace Simulator {
struct cBuilding {
  float GetCost();
};
}

float Simulator::cBuilding::GetCost()
{
  return 0.0f;
}

// ===========================================================================
// 0x00fc7f90 -- query the current sample-format descriptor
// ===========================================================================
// @ 0x00fc7f90
struct StreamFrame {
  int mField0;
  int mField4;
  int mField8;
  int mFieldC;
  int mField10;
  int mField14;
  int mField18;
};

float StreamB::FUN_00fc7f90()
{
  StreamFrame frame;

  AudioLock();
  FUN_011335a0(mField08, &frame);
  FUN_01133470(frame.mField4, &frame.mFieldC);
  AudioUnlock();
  if (frame.mFieldC == 2)
    return (float)frame.mField10;
  return -1.0f;
}

// ===========================================================================
// 0x00fc8000 -- set the output gain
// ===========================================================================
// @ 0x00fc8000
void StreamB::SetGain(float gain)
{
  mGain20 = gain;
  AudioLock();
  FUN_011336b0((void*)mField08, -1, mGain20);
  AudioUnlock();
}

// ===========================================================================
// 0x00fc8040 -- flush with no extra flags
// ===========================================================================
// @ 0x00fc8040
void StreamB::FUN_00fc8040()
{
  AudioLock();
  FUN_011339d0((void*)mField08, 0);
  AudioUnlock();
}

// ===========================================================================
// 0x00fc8060 -- flush with the end-of-stream flag
// ===========================================================================
// @ 0x00fc8060
void StreamB::FUN_00fc8060()
{
  AudioLock();
  FUN_011339d0((void*)mField08, 0x1000);
  AudioUnlock();
}

// ===========================================================================
// 0x00fc8080 -- constructor (vtable 0x014917c0)
// ===========================================================================
// @ 0x00fc8080
StreamB::StreamB()
{
  mpVtable = (Vtbl*)0x14917c0;
  mpField04 = 0;
  mField08 = -1;
  mField0c = -1;
  mpField10 = 0;
  mpPackedFile = 0;
  mField18 = 0;
  mField1c = 0;
  mGain20 = 1.0f;
}

// ===========================================================================
// 0x00fc80b0 -- lazily resolve packed-file access flags, then reset
// ===========================================================================
// @ 0x00fc80b0
void StreamB::FUN_00fc80b0()
{
  if (mField08 < 0) {
    DatabasePackedFile* file = (DatabasePackedFile*)mpPackedFile;
    mField08 = file->GetAccessFlags();
    mField0c = file->FUN_006c0200();
  }
  AudioLock();
  FUN_01133a20(mField0c, 0);
  AudioUnlock();
}

// ===========================================================================
// 0x00fc80f0 -- read 8 bytes from the packet cursor
// ===========================================================================
// @ 0x00fc80f0
bool FUN_00fc80f0(uint32_t** src, uint32_t* remaining, uint32_t* dst)
{
  if (*remaining >= 8) {
    uint32_t* p = *src;
    dst[0] = p[0];
    dst[1] = p[1];
    *src += 2;
    *remaining -= 8;
    return true;
  }
  return false;
}

// ===========================================================================
// 0x00fc8120 -- read 4 bytes from the packet cursor
// ===========================================================================
// @ 0x00fc8120
bool FUN_00fc8120(uint32_t** src, uint32_t* remaining, uint32_t* dst)
{
  if (*remaining >= 4) {
    *dst = **src;
    *src += 1;
    *remaining -= 4;
    return true;
  }
  return false;
}

// ===========================================================================
// 0x00fc8150 -- read a 0x38-byte record
// ===========================================================================
// @ 0x00fc8150
bool FUN_00fc8150(uint8_t** src, uint32_t* remaining, Blob38* dst)
{
  if (*remaining >= 0x38) {
    *dst = *(Blob38*)*src;
    *src += 0x38;
    *remaining -= 0x38;
    return true;
  }
  return false;
}

// ===========================================================================
// 0x00fc8180 -- read a 0x28-byte record
// ===========================================================================
// @ 0x00fc8180
bool FUN_00fc8180(uint8_t** src, uint32_t* remaining, Blob28* dst)
{
  if (*remaining >= 0x28) {
    *dst = *(Blob28*)*src;
    *src += 0x28;
    *remaining -= 0x28;
    return true;
  }
  return false;
}

// ===========================================================================
// 0x00fc81b0 -- read a 0x10-byte record
// ===========================================================================
// @ 0x00fc81b0
bool FUN_00fc81b0(uint32_t** src, uint32_t* remaining, Blob10* dst)
{
  if (*remaining >= 0x10) {
    uint32_t* p = *src;
    dst->m[0] = p[0];
    dst->m[1] = p[1];
    dst->m[2] = p[2];
    dst->m[3] = p[3];
    *src += 4;
    *remaining -= 0x10;
    return true;
  }
  return false;
}

// ===========================================================================
// 0x00fc8330 -- test the high word of the first dword against a global
// ===========================================================================
// @ 0x00fc8330
uint16_t FUN_00fc8330(uint32_t* p)
{
  uint32_t v = *(volatile uint32_t*)p;
  uint16_t hi = (uint16_t)(v >> 16);
  hi = (uint16_t)((hi & 0xff00) |
                  (hi == *(uint16_t*)0x15b17e8));
  return hi;
}

// ===========================================================================
// 0x00fc8350 -- zero-fill constructor
// ===========================================================================
// @ 0x00fc8350
StreamD::StreamD()
{
  mField00 = 0;
  mField04 = 0;
  mField08 = 0;
  mField0c = 0;
  mField10 = 0;
  mField14 = 0;
  mField18 = 0;
  mField1c = 0;
}

// ===========================================================================
// 0x00fc8370 -- store two pointers
// ===========================================================================
// @ 0x00fc8370
void StreamE::Set(void* a, void* b)
{
  mpField00 = a;
  mpField04 = b;
}

// ===========================================================================
// 0x00fc8380 -- read the first pointer
// ===========================================================================
// @ 0x00fc8380
void* StreamF::Get()
{
  return mpField00;
}

// ===========================================================================
// 0x00fc8390 -- rw::movie::BufferedWriter::SetBuffer
// ===========================================================================
// @ 0x00fc8390
void rw::movie::BufferedWriter::SetBuffer(void* buf, int size)
{
  mpBuffer08 = buf;
  mSize0c = size;
  mOffset10 = 0;
}

// ===========================================================================
// 0x00fc83b0 -- flush the writer through its callback
// ===========================================================================
// @ 0x00fc83b0
void Writer::Flush()
{
  FnCB5 cb = mpCallback;
  if (cb == 0)
    return;

  int delta = mField1c;
  if (delta == mField14) {
    if (delta == 0) {
      cb(mField08, mField10, 0, 1, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    } else if (delta == mField18) {
      cb(mField08, mField10, 0, 2, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    } else {
      cb(mField08, mField10, 0, 3, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    }
  } else {
    cb(mField08, mField10, mField14 - delta, 3, mField04);
    delta = mField10;
    mField1c = mField14 + delta;
  }

  if (mField1c > mField18)
    mField18 = mField1c;
  mField14 = mField14 + delta;
  mField10 = 0;
}

// ===========================================================================
// cWeatherManager helpers -- 0x00fc7430 / 0x00fc7950 / 0x00fc7b30
// ===========================================================================
struct WeatherGrid {
  char   mPad00[8];      // +0x00
  int    mWidth;         // +0x08
  char   mPad0c[4];      // +0x0c
  float* mpData;         // +0x10
};

struct WeatherCell {
  char         mPad00[0x1c];   // +0x00
  WeatherGrid* mpGrid;         // +0x1c
};

struct RefGrid {
  virtual void vfn0(int a);
  volatile int mRefCount;   // +0x04
  int    mWidth;       // +0x08
  char   mPad0c[4];    // +0x0c
  float* mpData;       // +0x10
};

struct PtrVector {
  void* mBegin;                 // +0x00
  void* mEnd;                   // +0x04
  void* mCap;                   // +0x08
  void push_back(void** item);  // 0x00a7f430
};

struct PropWatcher {
  int  mMode;          // +0x00
  char mPad04[0x0c];   // +0x04
  bool Check();        // 0x007e66a0
};

struct WeatherWatched {
  unsigned char mFlag;         // +0x00
  char          mPad01[0x13];  // +0x01
  void FUN_00dea730();         // 0x00dea730
};

namespace SP {
  struct Vec3 { float x, y, z; };
}

struct XformMsg {
  unsigned short mFlags;      // +0x00
  unsigned short mCount;      // +0x02
  SP::Vec3       mPos;        // +0x04
  float          mW;          // +0x10
  unsigned       mMatrix[9];  // +0x14
  XformMsg();                 // 0x00434040
};

struct WeatherScalars {
  char  mPad00[0x18];    // +0x00
  float mField18;        // +0x18
  char  mPad1c[0x10];    // +0x1c
  float mField2c;        // +0x2c
  float mField30;        // +0x30
  float FUN_00fb8a00();  // 0x00fb8a00
  float FUN_00fb7b90();  // 0x00fb7b90
  float FUN_00fd9400();  // 0x00fd9400
};

struct TerrainEditorObj {
  char mPad00[4];        // +0x00
  bool FUN_00f678a0();   // 0x00f678a0
};

struct WeatherMgr {
  void**         mpVtable;        // +0x00
  void*          mpField04;       // +0x04
  int            mField08;        // +0x08
  void*          mpStream;        // +0x0c
  char           mPad10[0x64];    // +0x10
  void*          mpField74;       // +0x74
  char           mPad78[0x34];    // +0x78
  unsigned char  mFlagAC;         // +0xac
  unsigned char  mFlagAD;         // +0xad
  char           mPadAE[2];       // +0xae
  PropWatcher    mWatcher;        // +0xb0
  WeatherWatched mWatched;        // +0xc0
  void*          mpD4;            // +0xd4
  void*          mpD8;            // +0xd8
  int            mDC;             // +0xdc
  void*          mpE0;            // +0xe0
  WeatherScalars* mpE4;           // +0xe4
  WeatherCell*   mpE8;            // +0xe8
  float          mEC;             // +0xec
  float          mF0;             // +0xf0
  float          mF4;             // +0xf4
  float          mF8;             // +0xf8
  float          mFC;             // +0xfc
  char           mPad100[0x50];   // +0x100
  int            m150;            // +0x150
  int            m154;            // +0x154
  char           mPad158[8];      // +0x158
  unsigned       mCount160;       // +0x160
  RefGrid*       mp164;           // +0x164
  int            mIndex168;       // +0x168
  char           mPad16c[1];      // +0x16c
  unsigned char  mFlag16D;        // +0x16d
  char           mPad16e[2];      // +0x16e
  PtrVector      mVec170;         // +0x170
  char           mPad17c[0x18];   // +0x17c
  float          mField194;       // +0x194
  float          mField198;       // +0x198

  bool Shutdown();             // 0x00fc7950
  void UpdateEffects(int a);   // 0x00fc7b30
  void FUN_00fc7430();         // 0x00fc7430
  void FUN_00fc6d10();         // 0x00fc6d10
  void FUN_00fc5de0();         // 0x00fc5de0
  void FUN_00fc5f80();         // 0x00fc5f80
  void FUN_00fc3f30();         // 0x00fc3f30
  void FUN_00fc6950(int a);    // 0x00fc6950
  int  GetTerraClass();        // 0x00fc2f50
};

typedef void (__thiscall* WFn0)(void*);
typedef void (__thiscall* WFn1)(void*, int);
typedef void (__thiscall* WFn3)(void*, int, int, int);
typedef void (__thiscall* WFn1P)(void*, void*);
typedef void (__thiscall* WFn1C)(void*, const char*);
typedef void (__thiscall* WFn3A)(void*, int, void*, int);
typedef void (__thiscall* WFnPA)(void*, void*, int, int);
typedef int  (__thiscall* WFnI0)(void*);
typedef bool (__thiscall* WFnRead)(void*, void*, int, void**);

#define WVT(p) (*(void***)(p))

float* FUN_00df5f50(float* out, float* range);          // 0x00df5f50
void   FUN_00aa7fa0(int a, int b);                      // 0x00aa7fa0
void   SetCloudGlobal(int a, int b);                    // 0x00f58230
void*  FUN_0067de20();                                  // SP::CheatManager
void*  FUN_0067dd80();                                  // SP::ModelManager
void*  FUN_0067dcc0();                                  // MessageServer
void*  FUN_00f48a70();                                  // SP::TerrainEditor

namespace SP {
  Vec3* normalized_safe(Vec3* out, const Vec3* in);     // 0x00449c20
}

// ===========================================================================
// 0x00fc7430 -- advance the weather grid blend
// ===========================================================================
// @ 0x00fc7430
void WeatherMgr::FUN_00fc7430()
{
  WeatherGrid* a = mpE8->mpGrid;
  if (a != 0) {
    WeatherGrid* b = *(WeatherGrid**)0x16d7150;
    if (b != 0 && mFlagAC != 0) {
      float* src = a->mpData + a->mWidth * a->mWidth * mIndex168;
      int n = b->mWidth;
      float* dst = b->mpData + n * n * mIndex168;
      if ((unsigned)(((char*)mVec170.mEnd - (char*)mVec170.mBegin) >> 2) < mCount160) {
        float rnd[4];
        FUN_00df5f50(rnd, (float*)0x15b177c);
        SP::Vec3 nrm;
        SP::normalized_safe(&nrm, (const SP::Vec3*)rnd);
        void* obj = 0;
        if (((WFnRead)WVT(mpStream)[0x08 / 4])(mpStream, mpField74, 0, &obj)) {
          XformMsg msg;
          msg.mFlags = msg.mFlags | 4;
          msg.mCount = msg.mCount + 1;
          msg.mPos = nrm;
          ((WFn1P)WVT(obj)[0x18 / 4])(obj, &msg);
          ((WFn1)WVT(obj)[0x08 / 4])(obj, 0);
          int terra = GetTerraClass();
          ((WFn3A)WVT(obj)[0x48 / 4])(obj, 3, &terra, 1);
          mVec170.push_back(&obj);
        }
        if (obj != 0)
          ((WFn0)WVT(obj)[0x04 / 4])(obj);
      }
      if (n > 0) {
        for (int y = 0; y < n; ++y) {
          for (int x = 0; x < n; ++x) {
            float s = src[x];
            float v = dst[x] + mField194;
            dst[x] = v < s ? v : s;
          }
          src += n;
          dst += n;
        }
      }
    }
  }

  RefGrid* c = *(RefGrid**)0x16d714c;
  if (c != 0 && mp164 != 0) {
    int n = mp164->mWidth;
    float* pa = mp164->mpData + n * n * mIndex168 * 3;
    float* pb = c->mpData + c->mWidth * c->mWidth * mIndex168 * 3;
    if (n > 0) {
      for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
          float* ea = pa + x * 3;
          float* eb = pb + x * 3;
          eb[0] = (ea[0] - eb[0]) * mField198 + eb[0];
          eb[1] = (ea[1] - eb[1]) * mField198 + eb[1];
          eb[2] = (ea[2] - eb[2]) * mField198 + eb[2];
        }
        pa += n * 3;
        pb += n * 3;
      }
    }
  }

  mIndex168 = mIndex168 + 1;
  if (mIndex168 >= 6)
    mIndex168 = 0;
}

// ===========================================================================
// 0x00fc7950 -- shut the weather system down
// ===========================================================================
// @ 0x00fc7950
bool WeatherMgr::Shutdown()
{
  FUN_00fc6d10();
  if (mpStream != 0) {
    ((WFn0)WVT(mpStream)[0x34 / 4])(mpStream);
    ((WFn1)WVT(mpStream)[0x0c / 4])(mpStream, 2);
    ((WFn1)WVT(mpD8)[0x50 / 4])(mpD8, 0x3618bef);
    if (mpStream != 0) {
      void* p = mpStream;
      mpStream = 0;
      ((WFn0)WVT(p)[0x04 / 4])(p);
    }
  }
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16d8, *(int*)0x15b16dc, 0);
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16e8, *(int*)0x15b16ec, 0);
  ((WFn3)WVT(mpD8)[0x88 / 4])(mpD8, *(int*)0x15b16f0, *(int*)0x15b16f4, 0);
  FUN_00aa7fa0(6, 0);
  SetCloudGlobal(3, 0);
  void* cheat = FUN_0067de20();
  if (cheat != 0) {
    ((WFn1C)WVT(cheat)[0x1c / 4])(cheat, "weather");
    *(unsigned char*)0x16d70ec = 0;
  }
  void* model = FUN_0067dd80();
  ((WFn1)WVT(model)[0x18 / 4])(model, 0x611c912);
  ((WFn1)WVT(mpD4)[0x134 / 4])(mpD4, 0);
  if (mpD4 != 0) {
    void* p = mpD4;
    mpD4 = 0;
    ((WFn0)WVT(p)[0x04 / 4])(p);
  }
  mDC = 0;
  mpE4 = 0;
  mpE0 = 0;
  mpE8 = 0;
  mFlagAD = 0;
  mFlag16D = 0;
  if (mp164 != 0) {
    RefGrid* p = mp164;
    mp164 = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  if (*(RefGrid**)0x16d7150 != 0) {
    RefGrid* p = *(RefGrid**)0x16d7150;
    *(RefGrid**)0x16d7150 = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  if (*(RefGrid**)0x16d714c != 0) {
    RefGrid* p = *(RefGrid**)0x16d714c;
    *(RefGrid**)0x16d714c = 0;
    if (--p->mRefCount == 0) {
      p->mRefCount = 1;
      p->vfn0(1);
    }
  }
  void* server = FUN_0067dcc0();
  ((WFnPA)WVT(server)[0x2c / 4])(server, &mField08, 0xf62def, (int)0xffffd8f1);
  return true;
}

// ===========================================================================
// 0x00fc7b30 -- per-frame weather update
// ===========================================================================
// @ 0x00fc7b30
void WeatherMgr::UpdateEffects(int arg)
{
  bool flag;
  if (mWatcher.Check() || mFlagAC == 0)
    flag = true;
  else
    flag = false;

  mWatched.FUN_00dea730();
  if (mpE4 != 0 && mFlagAD != 0 && mWatched.mFlag != 0) {
    if (((WFnI0)WVT(mpE0)[0x20 / 4])(mpE0) != 4) {
      void* terrain = FUN_00f48a70();
      if (!((TerrainEditorObj*)terrain)->FUN_00f678a0()) {
        if (flag) {
          FUN_00fc6d10();
          FUN_00fc5de0();
          flag = true;
        }
        float a = mpE4->FUN_00fb8a00();
        float b = mpE4->FUN_00fb7b90();
        float c = mpE4->FUN_00fd9400();
        if (a != mEC || b != mF0 || c != mF4 || flag) {
          mFC = mF0;
          mF8 = mEC;
          mEC = a;
          mF0 = b;
          mF4 = c;
          FUN_00fc3f30();
        }
        if (b == 0.0f)
          FUN_00fc6d10();
        else
          FUN_00fc5f80();
        if (mWatcher.mMode == 2)
          FUN_00fc7430();
        FUN_00fc6950(arg);
        mF8 = mEC;
        m150 = m154;
        mFC = mF0;
      }
    }
  }
}

// ===========================================================================
// 0x00fc81f0 -- rw::movie::AVIStreamerParseFunc
// ===========================================================================
typedef bool (__cdecl* AviChunkCb)(unsigned* p, unsigned ctx);

// @ 0x00fc81f0
unsigned __cdecl AVIStreamerParseFunc(unsigned* p, unsigned size, unsigned a2,
                                      unsigned a3, AviChunkCb cb, unsigned ctx,
                                      unsigned* out)
{
  if (size < 4)
    return 0;
  if (cb != 0 && cb(p, ctx) == 0)
    return 0;
  if (size < 8)
    return 0;

  unsigned remaining = size;
  unsigned tag = 0;
  unsigned len = 0;
  do {
    if (remaining >= 8) {
      tag = p[0];
      len = p[1];
      p += 2;
      remaining -= 8;
    }
    if (tag == *(unsigned*)0x15b179c || tag == *(unsigned*)0x15b17a4) {
      if (remaining < 4)
        return 0;
      unsigned form = *p++;
      remaining -= 4;
      if (form == *(unsigned*)0x15b17c0) {
        *out = size - remaining;
        return 1;
      }
    } else if (tag == *(unsigned*)0x15b17d8) {
      return 2;
    } else {
      unsigned skip = (len + 1) & 0xfffffffeu;
      if (remaining < skip)
        return 0;
      unsigned short hi = (unsigned short)(tag >> 16);
      if (hi == *(unsigned short*)0x15b17dc || hi == *(unsigned short*)0x15b17e0 ||
          hi == *(unsigned short*)0x15b17e4 || hi == *(unsigned short*)0x15b17e8) {
        *out = skip + 8;
        return 1;
      }
      remaining -= skip;
      p = (unsigned*)((char*)p + skip);
    }
  } while (remaining >= 8);
  return 0;
}

// ===========================================================================
// 0x00fc8300 -- chunk-tag test used by the streamer
// ===========================================================================
// @ 0x00fc8300
bool FUN_00fc8300(unsigned* p)
{
  unsigned t = *p;
  unsigned short hi = (unsigned short)(t >> 16);
  return t == *(unsigned*)0x15b179c || hi == *(unsigned short*)0x15b17dc ||
         hi == *(unsigned short*)0x15b17e0;
}
