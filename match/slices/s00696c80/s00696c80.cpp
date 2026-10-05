// slice s00696c80 — SP::cLocalInputState and the cLocaleManager locale switch helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------------------------
// @ 0x00697960
void* __fastcall ZeroLocalInputState(void* p) {
  memset(p, 0, 0x48);
  return p;
}

// ---------------------------------------------------------------------------------------------
namespace SP {

// cLocalInputState layout: 0 mKeys[8], 0x20 mModifiers, 0x24 mMouseButtons[5],
// 0x2c mMouseX, 0x30 mMouseY, 0x34 mDragButton, 0x38 mMouseStartX, 0x3c mMouseStartY,
// 0x40 mMouseDownModifiers, 0x44 mScrollDelta. Size 0x48.
class cLocalInputState {
 public:
  unsigned int mKeys[8];         // +0x00
  unsigned int mModifiers;       // +0x20
  bool mMouseButtons[5];         // +0x24
  unsigned char pad29[3];        // +0x29
  float mMouseX;                 // +0x2c
  float mMouseY;                 // +0x30
  unsigned int mDragButton;      // +0x34
  float mMouseStartX;            // +0x38
  float mMouseStartY;            // +0x3c
  unsigned int mMouseDownModifiers;  // +0x40
  unsigned int mScrollDelta;     // +0x44

  void Reset();
  void ResetIf(bool commit);     // 0x697a10
  void UpdateModifiers();
  void OnKeyDown(unsigned int key, unsigned int unused);   // 0x697a50
  void OnKeyUp(unsigned int key, unsigned int unused);
  void OnMouseDown(unsigned int button, float x, float y, unsigned int modifiers);
  void OnMouseUp(unsigned int button, float x, float y, unsigned int unused);
  void AddScrollDelta(int delta, int b, int c, int d);  // 0x697b40
};

// @ 0x00697980
void cLocalInputState::Reset() {
  for (int i = 0; i < 8; ++i) mKeys[i] = 0;
  mModifiers = 0;
  for (int i = 0; i < 5; ++i) mMouseButtons[i] = false;
  mDragButton = 0;
  mMouseStartX = 0.0f;
  mMouseStartY = 0.0f;
  mMouseDownModifiers = 0;
}

// @ 0x00697a10
void cLocalInputState::ResetIf(bool commit) {
  if (!commit) {
    for (int i = 0; i < 8; ++i) mKeys[i] = 0;
    mModifiers = 0;
    for (int i = 0; i < 5; ++i) mMouseButtons[i] = false;
    mDragButton = 0;
    mMouseStartX = 0.0f;
    mMouseStartY = 0.0f;
    mMouseDownModifiers = 0;
  }
}

// @ 0x006979c0
inline bool KeyBit(const unsigned int* k, int index, int bit) {
  return (k[index] >> bit) & 1;
}

void cLocalInputState::UpdateModifiers() {
  mModifiers = 0;
  if (KeyBit(mKeys, 0, 0x10)) mModifiers = 1;
  if (KeyBit(mKeys, 0, 0x11)) mModifiers = mModifiers | 2;
  if (KeyBit(mKeys, 0, 0x12)) mModifiers = mModifiers | 4;
  if (KeyBit(mKeys, 7, 1)) mModifiers = mModifiers | 8;
  if (KeyBit(mKeys, 2, 0x1b)) mModifiers = mModifiers | 0x10;
}

// @ 0x00697a50
void cLocalInputState::OnKeyDown(unsigned int key, unsigned int unused) {
  (void)unused;
  if (key <= 0xff) {
    mKeys[key >> 5] |= 1u << (key & 0x1f);
    UpdateModifiers();
  }
}

// @ 0x00697a80
void cLocalInputState::OnKeyUp(unsigned int key, unsigned int unused) {
  (void)unused;
  if (key <= 0xff) {
    mKeys[key >> 5] &= ~(1u << (key & 0x1f));
    UpdateModifiers();
  }
}

// @ 0x00697ab0
void cLocalInputState::OnMouseDown(unsigned int button, float x, float y, unsigned int modifiers) {
  mMouseButtons[button - 1000] = true;
  mMouseX = x;
  mMouseY = y;
  if (mDragButton == 0) {
    mDragButton = button;
    mMouseDownModifiers = modifiers;
    mMouseStartX = x;
    mMouseStartY = y;
  }
}

// @ 0x00697af0
void cLocalInputState::OnMouseUp(unsigned int button, float x, float y, unsigned int unused) {
  (void)unused;
  mMouseButtons[button - 1000] = false;
  mMouseX = x;
  mMouseY = y;
  if (mDragButton == button) mDragButton = 0;
}

// @ 0x00697b40
void cLocalInputState::AddScrollDelta(int delta, int b, int c, int d) {
  (void)b;
  (void)c;
  (void)d;
  mScrollDelta += (unsigned int)delta;
}

}  // namespace SP

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace Thread {
class Mutex {
 public:
  void Lock(const char* name);    // 0x9221b0
  void Unlock();                  // 0x922270
};
}  // namespace Thread
}  // namespace EA

namespace SP {

// @ 0x00697b50
class MutexLock {
 public:
  EA::Thread::Mutex* mMutex;  // +0
  MutexLock(EA::Thread::Mutex* m);
  ~MutexLock();
};

MutexLock::MutexLock(EA::Thread::Mutex* m) {
  mMutex = m;
  m->Lock("EA::Thread::Mutex");
}

// @ 0x00697b70
MutexLock::~MutexLock() { mMutex->Unlock(); }

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// @ 0x00697b80
namespace EA {
namespace Trace {
class Server {
 public:
  char pad0[0x94];
  bool mEnabled;                             // +0x94
  bool IsFiltered(unsigned int category);    // 0x923930
  int ShouldLog(unsigned int category);      // 0x697b80
};

// @ 0x00697b80
int Server::ShouldLog(unsigned int category) {
  if (mEnabled) {
    if (!IsFiltered(category)) return 0;
  }
  return 1;
}
}  // namespace Trace
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// @ 0x00697650 (partial: skeleton)
namespace SP {
bool cLocaleManagerRefreshLocale(void* self, void* p) {
  (void)self;
  (void)p;
  return true;
}
}  // namespace SP

// @ 0x00696c80 (partial: skeleton)
namespace SP {
bool cLocaleManagerApplyLocale(void* self, void* arg) {
  (void)self;
  (void)arg;
  return true;
}
}  // namespace SP

// @ 0x00697710 (partial: skeleton)
namespace SP {
bool cLocaleManagerSetLocale(void* self, void* arg) {
  (void)self;
  (void)arg;
  return true;
}
}  // namespace SP

// @ 0x00697bb0 (partial: skeleton)
namespace SP {
void cLogServerAssert(void* self) {
  (void)self;
}
}  // namespace SP
