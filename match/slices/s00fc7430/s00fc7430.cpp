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
