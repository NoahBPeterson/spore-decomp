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
struct cLocalInputState { private:
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
  void Lock(unsigned int timeout); // 0x9221b0 (arg: pointer to an ms timeout; -1 = block)
  void Unlock();                   // 0x922270
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

// 0x1408228: the "infinite wait" flag EA::Thread::Mutex::Lock reads through its argument.
extern const unsigned int g_mutexInfiniteWait;  // 0x1408228 (holds 0xffffffff)

MutexLock::MutexLock(EA::Thread::Mutex* m) {
  mMutex = m;
  m->Lock((unsigned int)&g_mutexInfiniteWait);
}

// @ 0x00697b70
MutexLock::~MutexLock() { mMutex->Unlock(); }

}  // namespace SP

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace CommandLine {
class CommandLine {
 public:
  int FindSwitch(const wchar_t* s, int a, void* b, void* c);   // 0x92b300
};
}  // namespace CommandLine
}  // namespace EA
extern EA::CommandLine::CommandLine* g_15fd920;   // 0x15fd920 CommandLine singleton

namespace EA {
namespace Trace {
void SetTraceDialogEnabled(bool b);            // 0x9250c0

class Server {
 public:
  virtual void* v00(); virtual void* v04(); virtual void* v08(); virtual void* v0c();
  virtual void* v10(); virtual void* v14();
  virtual void* v18();                                     // +0x18
  char pad_04[0x34];                                       // +0x04..+0x38
  EA::Thread::Mutex mMutex;                                // +0x38
  char padMut[0x94 - 0x38 - sizeof(EA::Thread::Mutex)];    // ..+0x94
  bool mEnabled;                                           // +0x94
  bool IsFiltered(unsigned int category);                  // 0x923930
  int ShouldLog(unsigned int category);                    // 0x697b80
  void AssertControl();                                    // 0x697bb0
};

// @ 0x00697b80
int Server::ShouldLog(unsigned int category) {
  if (mEnabled) {
    if (!IsFiltered(category)) return 0;
  }
  return 1;
}

// @ 0x00697bb0
void Server::AssertControl() {
  SP::MutexLock lock(&mMutex);
  if (g_15fd920 != 0) {
    if (g_15fd920->FindSwitch(L"noAsserts", 0, 0, 0) != -1)
      SetTraceDialogEnabled(false);
  }
  v18();
}
}  // namespace Trace
}  // namespace EA

// ---------------------------------------------------------------------------------------------
void* __cdecl EAAllocate(unsigned int sz, const char* name, int a, int b, int c, int d); // 0xf473a0

namespace SP {
void* MessageServer();                          // 0x67dcc0

namespace LocaleLoad {
struct Node { Node* next; Node* prev; void* value; };   // 0xc-byte list node
struct Head { Node* next; Node* prev; };                 // list sentinel
struct WStr { wchar_t* mBegin; wchar_t* mEnd; wchar_t* mCap; void* mAlloc; };
struct KeyList { Node* next; Node* prev; void* alloc; unsigned size; };
struct Item;  // resource-manager item (vtable: +0x4 release, +0x30 count, +0x54 ...)

void* GetDefaultAllocator();
int GetLocaleInfoString(int, int, wchar_t*, int, const WStr*);
unsigned FNV1_String16(const wchar_t*, unsigned, bool);
bool GetProp(unsigned hash, WStr* out, bool dflt);
bool ReadPropRecords2(int idx, Item* item, void** out, int count, bool flag);
void ReadPropRecords(void* list, int idx);
Node* NewNode(void** value);
}  // namespace LocaleLoad

// dummy view types for the foreign objects reached through the manager/message-server vtables
struct CObj0c { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); };
struct CObj14 { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
                virtual void s10(); virtual void s14(unsigned v); };
struct CMsgSrv { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
                 virtual void s10(); virtual void s14(); virtual void s18(unsigned m, void* p, int a, int b); };
struct CLocaleChangeMessage { void* __thiscall Ctor(void* src); };  // 0x696350

// ---- helpers/types for SP::cLocaleManagerSetLocale (0x697710) ----
namespace eastl {
// eastl::fixed_string<wchar_t,16,1>: begin/end/cap pointers into an inline buffer at +0x14.
struct WStr16 {
  wchar_t* mBegin;       // +0x00
  wchar_t* mEnd;         // +0x04
  wchar_t* mCap;         // +0x08
  wchar_t* mAlloc;       // +0x0c
  wchar_t* mInline;      // +0x10
  wchar_t  mBuffer[16];  // +0x14
  void __thiscall Ctor(const WStr16& src);      // 0x696230
  WStr16* __thiscall Assign(const void* src);   // 0x696320
};
}  // namespace eastl

namespace EA { namespace Locale {
bool IsLocaleAvailable(int* locale);          // 0x87f5e0
bool SetLocale(void* locale, int a, int b);   // 0x882b30
}}  // namespace EA::Locale
namespace EA { namespace ResourceMan {
bool GetRecordName(const void* key, wchar_t* out);   // 0x8d68c0
}}  // namespace EA::ResourceMan
unsigned __cdecl FUN_0087fd10(int* a, int* b, char c);   // 0x87fd10
void* __cdecl FUN_008d5f40();                            // 0x8d5f40
void __cdecl opdel(void* p);                             // 0xf47380
void* GetManager();                                      // 0x67dcd0

// view types reached through the manager / item / allocator vtables
struct IMgr {
  virtual void* s00(); virtual void* s04(); virtual void* s08();
  virtual bool  s0c(void* rec, void** out, int, int, int, int);   // +0x0c
  virtual void* s10(); virtual void* s14();
  virtual void* s18(void* rec, void* out, int, int, int);         // +0x18
  virtual void* s1c(); virtual void* s20(); virtual void* s24(); virtual void* s28();
  virtual void* s2c(); virtual void* s30(); virtual void* s34(); virtual void* s38();
  virtual void* s3c(); virtual void* s40(); virtual void* s44(); virtual void* s48();
  virtual void* s4c();
  virtual void* s50(int, void* item, void* ctx);                  // +0x50
};
struct IAlloc {
  virtual void* s00(); virtual void* s04(); virtual void* s08();
  virtual void* s0c(void* node, unsigned sz);                     // +0x0c
};
struct IItem {
  virtual void* s00(); virtual void* s04(); virtual void* s08(); virtual void* s0c();
  virtual void* s10();                                            // +0x10
};
struct ISub {
  virtual void* s00();
  virtual void* s04();                                            // +0x04
  virtual void* s08();
  virtual void* s0c(void* arg);                                   // +0x0c
};

class cLocaleManager {
 public:
  virtual void* v00(); virtual void* v04(); virtual void* v08(); virtual void* v0c();
  virtual void* v10(); virtual void* v14(); virtual void* v18(); virtual void* v1c();
  virtual void* v20();                          // +0x20
  char pad_04[8];                               // +0x04..+0x0c
  void* mField0c;                               // +0x0c
  void* mField14;                               // +0x14
  eastl::WStr16 mField18;                       // +0x18 (0x34 bytes)
  void* mField4c;                               // +0x4c
  LocaleLoad::Head mHeadA;                      // +0x50 (flag clear)
  void* mAlloc;                                 // +0x58
  char pad5c[4];                                // +0x5c..+0x60
  LocaleLoad::Head mHeadB;                      // +0x60 (flag set)
  void* GetDefaultLanguage();                   // 0x696a60
  void BuildRecordList(void* list, void* head); // 0x6960f0
  bool Load(const LocaleLoad::WStr* locale, bool bFlag);
  void BroadcastLocaleChange(unsigned int arg); // 0x697650
};

// @ 0x00697650
void cLocaleManager::BroadcastLocaleChange(unsigned int arg) {
  if (v20() != 0) {
    ((CObj14*)v20())->s14(arg);
  }
  if (mField4c != 0) ((CObj0c*)mField4c)->s0c();
  void* server = MessageServer();
  if (server != 0) {
    void* mem = EAAllocate(0x40, "App/cLocaleChangeMessage", 0, 0, 0, 0);
    void* msg = (mem == 0) ? 0 : ((CLocaleChangeMessage*)mem)->Ctor((void*)&mField18);
    ((CMsgSrv*)server)->s18(0x2800a7f, msg, 0, 0);
  }
}

// @ 0x00696c80
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

// @ 0x00697710
namespace SP {
// Switch the manager's active locale: validate, refresh the language, swap the
// locale string, rebuild the record lists and notify the message server.
bool __cdecl cLocaleManagerSetLocale(void* selfParam, void* locale) {
  cLocaleManager* self = (cLocaleManager*)selfParam;
  if (!EA::Locale::IsLocaleAvailable((int*)locale)) return false;
  self->GetDefaultLanguage();
  if (FUN_0087fd10((int*)locale, (int*)&self->mField18, 1) != 0) return true;
  if (!EA::Locale::SetLocale(locale, 0, 0)) return false;

  struct RefHdr { int refcount; };  // heap header of the record array (refcount at -4)

  eastl::WStr16 saved;              // keep the previous locale string
  saved.Ctor(self->mField18);
  self->mField18.Assign(locale);

  void* mgr = GetManager();
  void* rec[3] = {0, 0, 0};         // {begin, end, alloc} record array
  self->BuildRecordList(rec, &self->mHeadA);

  LocaleLoad::Node* head = (LocaleLoad::Node*)&self->mHeadA;
  while (head->next != head) {      // drain the locale's own list
    LocaleLoad::Node* node = head->prev;
    void* item = node->value;
    unsigned count = reinterpret_cast<unsigned>(((IItem*)item)->s10());
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node->value != 0) ((ISub*)((char*)node->value + 4))->s04();
    ((IAlloc*)self->mAlloc)->s0c(node, 0xc);
    if (count > 1) {
      void* key = ((ISub*)((char*)item + 4))->s0c((void*)0x226a1de);
      if (key != 0) {
        void* rm = FUN_008d5f40();
        if (rm != 0) EA::ResourceMan::GetRecordName(key, 0);
      }
      ((IMgr*)mgr)->s50(0, item, self->mField0c);
    }
  }

  if (self->Load((const LocaleLoad::WStr*)&self->mField18, false)) {
    for (char* r = (char*)rec[0]; r != (char*)rec[1]; r += 0xc) {
      void* out = 0;
      if (((IMgr*)mgr)->s0c(r, &out, 0, 0, 0, 0))
        ((IMgr*)mgr)->s18(r, out, 0, 0, 0);
      if (out != 0) ((ISub*)out)->s04();
    }
  }
  self->BroadcastLocaleChange(reinterpret_cast<unsigned>(&self->mField18));

  if (rec[0] != 0 && ((RefHdr*)((char*)rec[0] - sizeof(RefHdr)))->refcount != 0) opdel(rec[0]);
  if (((unsigned long)((char*)saved.mCap - (char*)saved.mBegin) & 0xfffffffeUL) > 2 &&
      saved.mBegin != 0 && saved.mBegin != saved.mInline)
    opdel(saved.mBegin);
  return true;
}
}  // namespace SP
