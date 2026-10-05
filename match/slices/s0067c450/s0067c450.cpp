// Slice s0067c450: cUIHints hint-state machine (0x67c450..0x67ca8c), the D3D9
// global-state register helpers (0x67cc70..0x67d0c0), zlib shim allocators
// (0x67d230/0x67d260) and EA::IO zlib stream setters (0x67d280..0x67d54d).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ------------------------------------------------------------------ cUIHints

struct cHint;

struct HintVec {
  cHint** mpBegin;
  cHint** mpEnd;
  cHint** mpCapacity;
};

struct PtrVec {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  void DoInsertValue(void** pPos, void** pValue);
};

// Retail cHint (0x98 bytes); offsets confirmed against FUN_0067b150.
struct cHint {
  void* mpVtable;              // +0x00
  int mRefCount;               // +0x04
  unsigned int mTriggerID;     // +0x08
  unsigned int mPresentList[3];// +0x0c
  unsigned int mGap18[2];      // +0x18
  unsigned int mAbsentList[3]; // +0x20
  unsigned int mGap2c[2];      // +0x2c
  unsigned int mCancelList[3]; // +0x34
  unsigned int mGap40;         // +0x40
  unsigned int mGap44;         // +0x44
  float mPeriod;               // +0x48
  float mWait;                 // +0x4c
  float mLife;                 // +0x50
  float mPriority;             // +0x54
  float mFlash;                // +0x58
  unsigned int mType;          // +0x5c
  unsigned int mGap60[4];      // +0x60
  unsigned int mIcon;          // +0x70
  unsigned char mbHasTextA;    // +0x74
  unsigned char mbHasText;     // +0x75
  unsigned char mbHasTextB;    // +0x76
  unsigned char mGap77;        // +0x77
  unsigned int mText[5];       // +0x78 (SP::cString)
  unsigned int mTextColor;     // +0x8c
  int mState;                  // +0x90
  float mTimer;                // +0x94
};

class ConfigObj {
 public:
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void s20(); virtual void s24(); virtual void s28();
  virtual void vf2c(int, int);
  virtual int vf30(int);
};

class MsgObj {
 public:
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10();
  virtual void vf14(int, int, int);
};

class cUIHints {
 public:
  bool CheckConditions(cHint* pHint);       // @ 0x0067afd0
  bool CheckCancelList(unsigned int* pVec); // @ 0x0067af10
  bool SetVisibility(int bVisible, cHint* pHint);  // @ 0x0067bc30
  void UpdateVisibleHint(cHint* pHint, float dt);  // @ 0x0067ad00

  void UpdateHintTimers(float dt);   // @ 0x0067c450
  void ActivateHint(unsigned int id);// @ 0x0067c830
  void SetHintState(unsigned int id, bool active); // @ 0x0067c8c0
  void Update();                     // @ 0x0067c960
  void Refresh();                    // @ 0x0067c9b0
  void AddCondition(void* pCondition);// @ 0x0067ca50

  unsigned int mBase[3];             // +0x00
  PtrVec mConditionFunc;             // +0x0c
  unsigned int mGap18[2];            // +0x18
  HintVec mHintList;                 // +0x20
  unsigned int mGap2c[2];            // +0x2c
  float mLastUpdateTime;             // +0x34
  float mLastHintTime;               // +0x38
  unsigned int mGap3c[3];            // +0x3c
  unsigned int mAnimState;           // +0x48
  cHint* mCurrentlyVisible;          // +0x4c
};

extern "C" cUIHints* FUN_0067cac0();
extern "C" ConfigObj* FUN_0067dd30();
extern "C" MsgObj* FUN_0067dcc0();
extern "C" float SPUIHelpers_GetElapsedSeconds();
extern "C" void cUIHintsRefreshTarget();

// @ 0x0067c450
void cUIHints::UpdateHintTimers(float dt) {
  unsigned int uBest = 0;
  cHint* pBest = 0;
  unsigned int bestType = 0xffffffff;
  cHint** pCurrent = mHintList.mpBegin;
  cHint** pRangeEnd = mHintList.mpEnd;
  if (pCurrent != pRangeEnd) {
    do {
      cHint* pHint = *pCurrent;
      switch (pHint->mState) {
        case 1:
          pHint->mTimer += dt;
          if (pHint->mTimer > pHint->mPeriod && pHint->mTimer != pHint->mPeriod) {
            if (CheckConditions(pHint)) pHint->mState = 2;
            pHint->mTimer = 0;
          }
          break;
        case 2:
          pHint->mTimer += dt;
          if (pHint->mTimer > pHint->mWait && pHint->mTimer != pHint->mWait) {
            pHint->mState = CheckConditions(pHint) ? 3 : 1;
            pHint->mTimer = 0;
          }
          break;
        case 3:
          if (((pHint->mCancelList[1] - pHint->mCancelList[0]) & 0xfffffffcU) != 0 &&
              CheckCancelList(pHint->mCancelList)) {
            pHint->mState = (pHint->mIcon != 0x1f9e21e8);
            pHint->mTimer = 0;
          }
          break;
        case 4:
          pHint->mTimer += dt;
          if (pHint->mTimer > pHint->mPriority && pHint->mTimer != pHint->mPriority) {
            pHint->mState = 5;
            pHint->mTimer = 0;
          }
          break;
        case 5:
          pHint->mTimer += dt;
          if (pHint->mTimer > pHint->mFlash && pHint->mTimer != pHint->mFlash) {
            pHint->mState = (pHint->mIcon != 0x1f9e21e8);
            SetVisibility(0, pHint);
            pHint->mTimer = 0;
          }
          break;
        case 6:
          pHint->mTimer += dt;
          if (pHint->mTimer > pHint->mFlash && pHint->mTimer != pHint->mFlash) {
            pHint->mState = (pHint->mIcon == 0x4527c498);
            SetVisibility(0, pHint);
            pHint->mTimer = 0;
          }
          break;
        case 7:
          pHint->mTimer += dt;
          {
            float threshold = pHint->mLife;
            if (pHint->mTimer > threshold && threshold != 0.0f) {
              pHint->mState = 7;
              pHint->mTimer = 0;
            } else if (((pHint->mCancelList[1] - pHint->mCancelList[0]) & 0xfffffffcU) != 0 &&
                       CheckCancelList(pHint->mCancelList)) {
              pHint->mState = 6;
              pHint->mTimer = 0;
            }
          }
          break;
        default:
          break;
      }
      if (mAnimState == 0 || pHint->mbHasText != 0) {
        unsigned int uType = pHint->mIcon;
        if (uType == 2) {
          if (uBest == 2) {
            if (pHint->mType > bestType) {
              bestType = pHint->mType;
              uBest = uType;
              pBest = pHint;
            }
          } else {
            bestType = pHint->mType;
            uBest = uType;
            pBest = pHint;
          }
        } else if (uBest != 2) {
          if (pHint->mType > bestType) {
            bestType = pHint->mType;
            uBest = uType;
            pBest = pHint;
          }
        }
      }
      ++pCurrent;
    } while (pCurrent != pRangeEnd);

    if (pBest != 0) {
      if (pBest->mIcon == 0x1f9e21e8 || mLastUpdateTime - 20.0f > mLastHintTime) {
        cHint* pVisible = mCurrentlyVisible;
        if (pVisible != 0 && pVisible != pBest) {
          pVisible->mState = 3;
          SetVisibility(0, pVisible);
        }
        if (pBest->mState == 3) {
          pBest->mState = 4;
          SetVisibility(1, pBest);
          pBest->mTimer = 0;
          mLastHintTime = mLastUpdateTime;
        }
      }
      UpdateVisibleHint(pBest, dt);
    }
  }
}

// @ 0x0067c790
void FUN_0067c790() {
  cUIHints* pThis = FUN_0067cac0();
  if (pThis->mAnimState <= 2) {
    cHint* pVisible = pThis->mCurrentlyVisible;
    pThis->mAnimState = 2;
    if (pVisible != 0) {
      pThis->mCurrentlyVisible->mState =
          (pThis->mCurrentlyVisible->mIcon == 0x1f9e21e8) ? 0 : 1;
      pThis->mCurrentlyVisible->mTimer = 0.0f;
      pThis->SetVisibility(0, pThis->mCurrentlyVisible);
    }
    pThis->mCurrentlyVisible = 0;
  }
  pThis = FUN_0067cac0();
  pThis->mAnimState = 3;
  FUN_0067dd30()->vf2c(0x4ea96cb, 0);
  FUN_0067dcc0()->vf14(0x670eccd, 0, 0);
}

// @ 0x0067c830
void cUIHints::ActivateHint(unsigned int id) {
  cHint** pCurrent = mHintList.mpBegin;
  cHint** pRangeEnd = mHintList.mpEnd;
  cHint* pHint = 0;
  while (pCurrent != pRangeEnd) {
    pHint = *pCurrent;
    if (pHint->mTriggerID == id && pHint != mCurrentlyVisible) break;
    ++pCurrent;
  }
  if (pCurrent == pRangeEnd) return;
  if (mCurrentlyVisible != 0) {
    mCurrentlyVisible->mState =
        (mCurrentlyVisible->mIcon == 0x1f9e21e8) ? 0 : 1;
    mCurrentlyVisible->mTimer = 0.0f;
    SetVisibility(0, mCurrentlyVisible);
  }
  mCurrentlyVisible = 0;
  pHint->mState = 3;
  pHint->mTimer = 0.0f;
}

// @ 0x0067c8c0
void cUIHints::SetHintState(unsigned int id, bool active) {
  cHint** pCurrent = mHintList.mpBegin;
  cHint** pRangeEnd = mHintList.mpEnd;
  cHint* pHint = 0;
  while (pCurrent != pRangeEnd) {
    pHint = *pCurrent;
    if (pHint->mTriggerID == id) break;
    ++pCurrent;
  }
  if (pCurrent == pRangeEnd) return;
  if (mCurrentlyVisible == pHint) {
    if (pHint != 0) {
      if (pHint->mIcon == 0x1f9e21e8) active = true;
      pHint->mState = (active == false);
      pHint->mTimer = 0.0f;
      SetVisibility(0, mCurrentlyVisible);
    }
    mCurrentlyVisible = 0;
    return;
  }
  pHint->mTimer = 0.0f;
  pHint->mState = (active == false);
}

// @ 0x0067c960
void cUIHints::Update() {
  float elapsed = SPUIHelpers_GetElapsedSeconds();
  float delta = elapsed - mLastUpdateTime;
  mLastUpdateTime = elapsed;
  if (mAnimState <= 1) {
    int n = FUN_0067dd30()->vf30(0x5b5bb5e);
    mAnimState = (n == 0);
    UpdateHintTimers(delta);
  }
}

// @ 0x0067c9b0
void cUIHints::Refresh() {
  cHint* pVisible = mCurrentlyVisible;
  if (pVisible != 0) {
    pVisible->mState = (pVisible->mIcon != 0x1f9e21e8);
    pVisible->mTimer = 0.0f;
    SetVisibility(0, pVisible);
  }
  mCurrentlyVisible = 0;
  cHint** pCurrent = mHintList.mpBegin;
  cHint** pRangeEnd = mHintList.mpEnd;
  do {
    if (pCurrent == pRangeEnd) return;
    cHint* pHint = *pCurrent;
    int state = pHint->mState;
    if (state == 1) {
      pHint->mTimer = 0.0f;
    } else if ((unsigned int)(state - 2) < 2) {
      pHint->mState = (pHint->mIcon != 0x1f9e21e8);
      pHint->mTimer = 0.0f;
    }
    ++pCurrent;
  } while (true);
}

// @ 0x0067ca40 (MI adjustor thunk to Refresh at this-0x10)
__declspec(naked) void FUN_0067ca40() {
  __asm {
    add dword ptr [ecx + 0x10], -4
    jmp cUIHintsRefreshTarget
  }
}

// @ 0x0067ca50
void cUIHints::AddCondition(void* pCondition) {
  PtrVec& vec = mConditionFunc;
  void** pSlot = vec.mpEnd;
  if (pSlot < vec.mpCapacity) {
    vec.mpEnd = pSlot + 1;
    if (pSlot != 0) {
      *pSlot = pCondition;
      Refresh();
      return;
    }
  } else {
    vec.DoInsertValue(pSlot, &pCondition);
  }
  Refresh();
}

// ------------------------------------------------------------------ D3D9 register helpers

typedef void (__stdcall *SRegFn)(void*, void*, void*, int);
struct SO { SRegFn* vt; };

extern SO* g_016f89d0;             // D3D9 device object (vtable owner)
extern void* g_016f6ed0;
extern void* g_016f6eb0;
extern void* g_016f6eb4;
extern float* g_016f6e74;
extern float* g_016f6e7c;
extern float* g_016f6e80;
extern float* g_016f6e98;
extern float* g_016f6eac;

// @ 0x0067cc70
void FUN_0067cc70(void* a, void* b, int c) {
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, g_016f6ed0, 3);
  else
    g_016f89d0->vt[109](g_016f89d0, a, g_016f6ed0, 3);
}

// @ 0x0067cca0
void FUN_0067cca0(void* a, void* b, int c) {
  if (g_016f6eb0) {
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, g_016f6eb0, 4);
    else
      g_016f89d0->vt[109](g_016f89d0, a, g_016f6eb0, 4);
  }
}

// @ 0x0067cce0
void FUN_0067cce0(void* a, void* b, int c) {
  if (g_016f6eb4) {
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, g_016f6eb4, 9);
    else
      g_016f89d0->vt[109](g_016f89d0, a, g_016f6eb4, 9);
  }
}

// @ 0x0067cd20
void FUN_0067cd20(void* a, void* b, int c) {
  if (g_016f6e74) {
    float values[4] = {1.0f, 1.0f, 1.0f, g_016f6e74[0]};
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, values, 1);
    else
      g_016f89d0->vt[109](g_016f89d0, a, values, 1);
  }
}

// @ 0x0067cd90
void FUN_0067cd90(void* a, void* b, int c) {
  if (g_016f6e7c) {
    float values[4] = {1.0f, 1.0f, 1.0f, g_016f6e7c[0]};
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, values, 1);
    else
      g_016f89d0->vt[109](g_016f89d0, a, values, 1);
  }
}

// @ 0x0067ce00
void FUN_0067ce00(void* a, void* b, int c) {
  float values[12] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  if (g_016f6e98) {
    for (int i = 0; i < 12; ++i) values[i] = g_016f6e98[i];
  }
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, values, 3);
  else
    g_016f89d0->vt[109](g_016f89d0, a, values, 3);
}

// @ 0x0067d020
void FUN_0067d020(void* a, void* b, int c) {
  float values[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  if (g_016f6e80) {
    values[0] = g_016f6e80[0];
  }
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, values, 1);
  else
    g_016f89d0->vt[109](g_016f89d0, a, values, 1);
}

// @ 0x0067d0c0
extern "C" void FUN_011f4270(int, void*, void*, void*, void*);
void FUN_0067d0c0() {
  FUN_011f4270(0x236, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067d020);
  *(unsigned int*)0x16327c8 = 4;
  FUN_011f4270(0x238, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0);
  *(unsigned int*)0x16327d0 = 1;
  FUN_011f4270(0x233, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cd20);
  *(unsigned int*)0x16327bc = 4;
  FUN_011f4270(0x235, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cd90);
  *(unsigned int*)0x16327c4 = 4;
  FUN_011f4270(0x23c, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067ce00);
  *(unsigned int*)0x16327e0 = 0x30;
  FUN_011f4270(0x241, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0);
  *(unsigned int*)0x16327f4 = 0x40;
  FUN_011f4270(0x242, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cca0);
  *(unsigned int*)0x16327f8 = 0x40;
  FUN_011f4270(0x243, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cce0);
  *(unsigned int*)0x16327fc = 0x90;
  FUN_011f4270(0x24a, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cc70);
  *(unsigned int*)0x1632818 = 0x30;
}

// ------------------------------------------------------------------ zlib shim allocators

extern unsigned int g_015fd88c;
struct Allocator {
  void* Alloc(unsigned int size, int a, int b, int c, int d, int e);
  void Free(void* p);
};
extern Allocator* g_16c8b44;

// @ 0x0067d230
extern "C" void* __cdecl FUN_0067d230(void* opaque, unsigned int items, unsigned int size) {
  g_015fd88c += size;
  return g_16c8b44->Alloc(items * size, 0, 0, 0, 0, 0);
}

// @ 0x0067d260
extern "C" void __cdecl FUN_0067d260(void* opaque, void* p) {
  g_16c8b44->Free(p);
}

// ------------------------------------------------------------------ EA::IO zlib streams

struct z_stream_s {
  const uint8_t* next_in;
  uint32_t avail_in;
  uint32_t total_in;
  uint8_t* next_out;
  uint32_t avail_out;
  uint32_t total_out;
  char* msg;
  void* state;
  void* zalloc;
  void* zfree;
  void* opaque;
  int data_type;
  uint32_t adler;
  uint32_t reserved;
};

namespace EA {
namespace IO {

enum eCompressedFormat { kCompressedFormatZLib = 0, kCompressedFormatGZip = 1 };

extern "C" void* __cdecl eaAlloc(unsigned int size, const char* pGroup, int flags,
                                 unsigned debug, const char* pFile, int line);
extern "C" void __cdecl eaFree(void* p);

class StreamCompressionZLib {
 public:
  bool SetCompressedFormat(eCompressedFormat fmt);   // @ 0x0067d280
  bool SetBufferSize(unsigned int size);             // @ 0x0067d2a0
  bool SetCompressionHint(int hint);                 // @ 0x0067d2e0
  int GetAccessFlags() const;                        // @ 0x0067d300
  int GetState() const;                              // @ 0x0067d310
  bool InitPointers();                               // @ 0x0067d330
  unsigned int GetPosition(int positionType) const;  // @ 0x0067d3f0

  unsigned int mGap00[3];          // +0x00
  void* mpOutputStream;            // +0x0c
  bool mbOpen;                     // +0x10
  bool mbInited;                   // +0x11
  z_stream_s* mpZLibStream;        // +0x14
  eCompressedFormat mFormat;       // +0x18
  int mHint;                       // +0x1c
  unsigned char* mpOutputBuffer;   // +0x20
  unsigned int mnOutputBufferSize; // +0x24
  unsigned int mInputCRC;          // +0x28
  unsigned int mInputSize;         // +0x2c
};

class StreamDecompressionZLib {
 public:
  bool SetCompressedFormat(eCompressedFormat fmt);   // @ 0x0067d410
  bool SetBufferSize(unsigned int size);             // @ 0x0067d420
  int GetAccessFlags() const;                        // @ 0x0067d460
  int GetState() const;                              // @ 0x0067d470
  bool InitPointers();                               // @ 0x0067d490
  unsigned int GetPosition(int positionType) const;  // @ 0x0067d530

  unsigned int mGap00[3];          // +0x00
  void* mpInputStream;             // +0x0c
  eCompressedFormat mFormat;       // +0x10
  bool mbOpen;                     // +0x14
  bool mbEOF;                      // +0x15
  bool mbInited;                   // +0x16
  z_stream_s* mpZLibStream;        // +0x18
  unsigned char* mpInputBuffer;    // +0x1c
  unsigned int mnInputBufferSize;  // +0x20
};

// @ 0x0067d280
bool StreamCompressionZLib::SetCompressedFormat(eCompressedFormat fmt) {
  if (fmt != kCompressedFormatZLib && fmt != kCompressedFormatGZip) return false;
  mFormat = fmt;
  return true;
}

// @ 0x0067d2a0
bool StreamCompressionZLib::SetBufferSize(unsigned int size) {
  if (!mbOpen) {
    mnOutputBufferSize = size;
    if (mpOutputBuffer != 0) {
      eaFree(mpOutputBuffer);
      mpOutputBuffer = 0;
    }
    return true;
  }
  return false;
}

// @ 0x0067d2e0
bool StreamCompressionZLib::SetCompressionHint(int hint) {
  if ((unsigned int)(hint + 1) <= 0xa) {
    mHint = hint;
    return true;
  }
  return false;
}

// @ 0x0067d300
int StreamCompressionZLib::GetAccessFlags() const {
  return mbOpen ? 2 : 0;
}

// @ 0x0067d310
int StreamCompressionZLib::GetState() const {
  if (mbOpen && mpZLibStream != 0) return mpZLibStream->msg ? -1 : 0;
  return -2;
}

// @ 0x0067d330
bool StreamCompressionZLib::InitPointers() {
  bool result = true;
  if (mpOutputBuffer == 0 && mnOutputBufferSize > 0) {
    unsigned char* p = (unsigned char*)eaAlloc(
        mnOutputBufferSize, "StreamCompressionZLib/OutputBuffer", 0, 0, 0, 0);
    result = (p != 0);
    mpOutputBuffer = p;
    if (!result) goto done;
  }
  if (mpZLibStream == 0) {
    result = false;
    if (!mbInited) {
      mpZLibStream = (z_stream_s*)eaAlloc(
          0x38, "StreamCompressionZLib/z_stream_s", 0, 0, 0, 0);
      if (mpZLibStream != 0) {
        mpZLibStream->zalloc = (void*)&FUN_0067d230;
        mpZLibStream->zfree = (void*)&FUN_0067d260;
        mpZLibStream->next_in = 0;
        mpZLibStream->avail_in = 0;
        mpZLibStream->next_out = mpOutputBuffer;
        mpZLibStream->avail_out = mnOutputBufferSize;
        mpZLibStream->total_in = 0;
        result = true;
      }
    }
  }
done:
  mbInited = result;
  return result;
}

// @ 0x0067d3f0
unsigned int StreamCompressionZLib::GetPosition(int positionType) const {
  if (positionType == 0 && mbOpen && mpZLibStream != 0) return mpZLibStream->total_in;
  return 0xffffffff;
}

// @ 0x0067d410
bool StreamDecompressionZLib::SetCompressedFormat(eCompressedFormat fmt) {
  return fmt == kCompressedFormatZLib;
}

// @ 0x0067d420
bool StreamDecompressionZLib::SetBufferSize(unsigned int size) {
  if (!mbOpen) {
    mnInputBufferSize = size;
    if (mpInputBuffer != 0) {
      eaFree(mpInputBuffer);
      mpInputBuffer = 0;
    }
    return true;
  }
  return false;
}

// @ 0x0067d460
int StreamDecompressionZLib::GetAccessFlags() const {
  return mbOpen != false;
}

// @ 0x0067d470
int StreamDecompressionZLib::GetState() const {
  if (mbOpen && mpZLibStream != 0) return mpZLibStream->msg ? -1 : 0;
  return -2;
}

// @ 0x0067d490
bool StreamDecompressionZLib::InitPointers() {
  bool result = true;
  if (mpInputBuffer == 0 && mnInputBufferSize > 0) {
    unsigned char* p = (unsigned char*)eaAlloc(
        mnInputBufferSize, "StreamCompressionZLib/InputBuffer", 0, 0, 0, 0);
    result = (p != 0);
    mpInputBuffer = p;
    if (!result) goto done;
  }
  if (mpZLibStream == 0) {
    result = false;
    if (!mbInited) {
      mpZLibStream = (z_stream_s*)eaAlloc(
          0x38, "StreamCompressionZLib/z_stream_s", 0, 0, 0, 0);
      if (mpZLibStream != 0) {
        mpZLibStream->zalloc = (void*)&FUN_0067d230;
        mpZLibStream->zfree = (void*)&FUN_0067d260;
        mpZLibStream->next_in = mpInputBuffer;
        mpZLibStream->avail_in = 0;
        mpZLibStream->next_out = 0;
        mpZLibStream->avail_out = 0;
        mpZLibStream->total_out = 0;
        result = true;
      }
    }
  }
done:
  mbInited = result;
  return result;
}

// @ 0x0067d530
unsigned int StreamDecompressionZLib::GetPosition(int positionType) const {
  if (positionType == 0 && mbOpen && mpZLibStream != 0) return mpZLibStream->total_out;
  return 0xffffffff;
}

}  // namespace IO
}  // namespace EA
