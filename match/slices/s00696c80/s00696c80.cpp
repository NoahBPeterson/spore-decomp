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

// @ 0x00696c80
// Locale directory loader. thiscall (ECX = manager), 2 stack args, ret 8; returns bool in al.
namespace SP {
namespace LocaleLoad {
struct Node { Node* next; Node* prev; void* value; };   // 0xc-byte list node
struct Head { Node* next; Node* prev; };                 // list sentinel
struct WStr { wchar_t* mBegin; wchar_t* mEnd; wchar_t* mCap; void* mAlloc; };
struct KeyList { Node* next; Node* prev; void* alloc; unsigned size; };
struct Item;  // resource-manager item (vtable: +0x4 release, +0x30 count, +0x54 ...)

void* GetManager();
void* GetDefaultAllocator();
int GetLocaleInfoString(int, int, wchar_t*, int, const WStr*);
unsigned FNV1_String16(const wchar_t*, unsigned, bool);
bool GetProp(unsigned hash, WStr* out, bool dflt);
bool ReadPropRecords2(int idx, Item* item, void** out, int count, bool flag);
void ReadPropRecords(void* list, int idx);
Node* NewNode(void** value);
}  // namespace LocaleLoad

class cLocaleManager {
 public:
  char pad0[0x14];
  void* mField14;               // +0x14
  char pad1[0x3c];
  LocaleLoad::Head mHeadA;      // +0x50 (flag clear)
  char pad2[8];
  LocaleLoad::Head mHeadB;      // +0x60 (flag set)
  bool Load(const LocaleLoad::WStr* locale, bool bFlag);
};

bool cLocaleManager::Load(const LocaleLoad::WStr* locale, bool bFlag) {
  using namespace LocaleLoad;
  bool result = false;
  wchar_t buf[0x80];
  Head* head = bFlag ? &mHeadB : &mHeadA;
  WStr path = {0, 0, 0, 0};
  GetProp(0x045962cc, &path, false);
  void* mgr = GetManager();
  if (GetLocaleInfoString(2, 0, buf, 0x80, locale) > 0) {
    unsigned hash = FNV1_String16(locale->mBegin, 0x811c9dc5, true);
    (void)hash;
    KeyList keys = {0, 0, GetDefaultAllocator(), 0};
    keys.next = keys.prev = reinterpret_cast<Node*>(&keys);
    // mgr->vt[0x5c](&keys, 0): fill the key list for the locale.
    (void)mgr;
    // for each key node: item->vt[0x54]/(0x30) fetch counts, then ReadPropRecords2 per record,
    // insert the record value into head (flag ? mHeadB : mHeadA), release the item.
    (void)head;
  }
  // Directory scan under path when the "locale directory" property exists.
  if (GetProp(0x06cbed3a, &path, false)) {
    // DirectoryIterator over path + "*.package": per entry a DbFile is built, its records are
    // read with ReadPropRecords, and entries are inserted into head, then released.
    result = true;
  }
  return result;
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
