// src/game/SPMovie/audiodecoder_snd9.cpp -- migrated from slice(s) s00fc7430 by tools/migrate/rewrite.py
// Object file: SPMovie/audiodecoder_snd9.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* p[64]; };
struct AudioSamples {
  int mTag;        // +0x00
  int mRate;       // +0x04
  int mChannels;   // +0x08
  int mBits;       // +0x0c
  int mCount;      // +0x10
};
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
struct ReleaseIface {
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void Release(void* p, int v);
};
void rw_audio_core_SndStream_destroy(int handle);   // 0x01132a10
int  FUN_01133020(int a, int b);                    // 0x01133020
void FUN_01132fe0(void* p);                         // 0x01132fe0
int  FUN_01132fb0(void* stream, void* params, int a, int b, void* buf, int c); // 0x01132fb0
int  FUN_01132f90(int handle, int flag, int request); // 0x01132f90
// ---- items of slice s00fc7430 end

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
