// Decompiled slice s00d38930 -- SP::cCreatureModeStrategy tutorial / cinematic
// plumbing plus a handful of engine container and trigger helpers.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// tutorial / terrain reference: three words {noun, 0, magic-hash}
// ---------------------------------------------------------------------------
struct TTutorialRef {
  int mNoun;                                              // +0x00
  int mUnused04;                                          // +0x04
  int mMagic;                                             // +0x08
};

namespace SP {

struct cSPUIEventLog;
struct cGameNounManager;
struct cGameTimeManager;
struct cTriggerMgr;
struct TSphere;
struct cSPCreatureBase;

cSPUIEventLog* __stdcall EventLog(int a, int b, int c);   // 0x00b3d3e0
cGameNounManager* NounManager();                          // 0x00b3d300
cGameTimeManager* GameTimeManager();                      // 0x00b3d380
cTriggerMgr* GetTriggerMgr();                             // 0x00b3d4d0

struct cSPUIEventLog {
  void RemoveAllEventsOfSameType();                       // 0x00dd7620
};

struct cGameNounManager {
  TSphere*         GetCurrentTerrainSphere();             // 0x00f67d90
  cSPCreatureBase* GetAvatar();                           // 0x00b1fdb0
};

struct TSphere {
  void FUN_00c78420(TTutorialRef* ref);                   // 0x00c78420
  char FUN_00c77c50(TTutorialRef* ref);                   // 0x00c77c50
};

struct cGameTimeManager {
  void DecPauseGate(int gate);                            // 0x00b32250
};

struct cTriggerMgr {
  int PostTrigger(int a1, int a2, int a3, int a4, int a5, int a6);  // 0x00ae0930
};

struct cSPCreatureBase {
  void StartIndependentSound(const char* name, int param, int** list);  // 0x00c1db40
  static double GetTime();                                // 0x00c0e480
};

}  // namespace SP

// ---------------------------------------------------------------------------
// The engine's audio system, reached through EA::Audio::GetSystemAT; only the
// four vtable slots the locating-call response drives are named.
// ---------------------------------------------------------------------------
struct CAudioSystem {
  virtual void mSlot00(); virtual void mSlot01(); virtual void mSlot02(); virtual void mSlot03();
  virtual void mSlot04(); virtual void mSlot05(); virtual void mSlot06(); virtual void mSlot07();
  virtual void mSlot08(); virtual void mSlot09(); virtual void mSlot10(); virtual void mSlot11();
  virtual void mSlot12(); virtual void mSlot13();
  virtual void SetLocatingEvent(int eventId);             // +0x38
  virtual void mSlot15();
  virtual void PostLocatingEvent(int eventId, int param);  // +0x40
  virtual void mSlot17(); virtual void mSlot18(); virtual void mSlot19(); virtual void mSlot20();
  virtual void mSlot21();
  virtual void FinishLocatingCall();                      // +0x58
};

namespace EA { namespace Audio { CAudioSystem* GetSystemAT(); } }  // 0x00a206f0

// A global flat array of locating-call slots plus the one-shot latch and the
// timestamp taken when the response fires.
int*   g_locatingSlotsBegin;                              // 0x0169e2a8
int*   g_locatingSlotsEnd;                                // 0x0169e2ac
double g_locatingCallTime;                                // 0x0169e2c0
int    g_locatingCallDone;                                // 0x0169e2c8

// ---------------------------------------------------------------------------
// @ 0x00d38cc0
// One-shot "the creature answered a locating call" response: fires the audio
// system's locating events for every registered slot, starts the looped call
// sound, then latches the timestamp of the avatar at the time.
void FUN_00d38cc0(SP::cSPCreatureBase* param_1, int param_2)
{
  if (g_locatingCallDone != 1) {
    uint32_t n = (uint32_t)(g_locatingSlotsEnd - g_locatingSlotsBegin);
    for (uint32_t i = 0; i < n; ++i) {
      int           slot = g_locatingSlotsBegin[i];
      CAudioSystem* sys  = EA::Audio::GetSystemAT();
      if (sys != 0) {
        sys->SetLocatingEvent(0x347536b);
        sys->PostLocatingEvent(0x3475385, slot);
        sys->PostLocatingEvent(0x34753a0, 1);
        sys->FinishLocatingCall();
      }
    }
    param_1->StartIndependentSound("vsoc_matecall_2_loop", param_2, &g_locatingSlotsBegin);
  }
  g_locatingCallDone = 1;
  SP::cGameNounManager* manager = SP::NounManager();
  manager->GetAvatar();
  g_locatingCallTime = SP::cSPCreatureBase::GetTime();
}

// ---------------------------------------------------------------------------
// The locating-call node built here: 0x80 bytes, refcounted through its vtable
// and driven through slot +0x1c.
// ---------------------------------------------------------------------------
struct CLocatingNode {
  CLocatingNode();
  virtual void mSlot00();
  virtual void AddRef();                                  // +0x04
  virtual void Release();                                 // +0x08
  virtual void mSlot0c();
  virtual void mSlot10();
  virtual void mSlot14();
  virtual void mSlot18();
  virtual void mSlot1c();                                 // +0x1c
  uint8_t mBody[0x7c];                                    // -> sizeof == 0x80
};

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);

struct CLocatingOwner {
  uint8_t       mUnused00[0xd0];
  CLocatingNode* mpNode;                                  // +0xd0

  void FUN_00d392f0();
};

// ---------------------------------------------------------------------------
// @ 0x00d392f0
// Rebuilds the owner's locating node and hands it the "begin" message.
void CLocatingOwner::FUN_00d392f0()
{
  CLocatingNode* node = new ("Simulator", 0, 0, 0, 0) CLocatingNode();
  CLocatingNode* old  = mpNode;
  if (node != old) {
    if (node != 0)
      node->AddRef();
    mpNode = node;
    if (old != 0)
      old->Release();
  }
  mpNode->mSlot1c();
}

// ---------------------------------------------------------------------------
// @ 0x00d38930
// Removes every tutorial event of the strategy's noun from the event log, then
// pokes the current terrain sphere with the noun/type/magic reference.
void __stdcall FUN_00d38930(int param_1)
{
  SP::cSPUIEventLog* log = SP::EventLog(param_1, 0, 0);
  log->RemoveAllEventsOfSameType();

  TTutorialRef ref;
  ref.mNoun      = param_1;
  ref.mUnused04  = 0;
  ref.mMagic     = 0x68dd6929;

  SP::cGameNounManager* editor = SP::NounManager();
  SP::TSphere*         sphere = editor->GetCurrentTerrainSphere();
  if (sphere != 0)
    sphere->FUN_00c78420(&ref);
}

// ---------------------------------------------------------------------------
// @ 0x00d38980
// True when the terrain sphere reports a matching tutorial event for the noun.
int __stdcall FUN_00d38980(int param_1)
{
  SP::cGameNounManager* editor = SP::NounManager();
  SP::TSphere*        sphere = editor->GetCurrentTerrainSphere();

  TTutorialRef ref;
  ref.mNoun     = param_1;
  ref.mUnused04 = 0;
  ref.mMagic    = 0x68dd6929;

  if (sphere != 0) {
    if (sphere->FUN_00c77c50(&ref) != 0)
      return 1;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00d389d0
// Runs the cinematic for the given noun: pokes the terrain sphere, then posts
// the standard "cinematic start" trigger through the trigger manager.
void __stdcall FUN_00d389d0(int param_1, int param_2)
{
  TTutorialRef ref;
  ref.mNoun     = param_2;
  ref.mUnused04 = 0;
  ref.mMagic    = 0x68dd6929;

  SP::cGameNounManager* editor = SP::NounManager();
  SP::TSphere*        sphere = editor->GetCurrentTerrainSphere();
  if (sphere != 0)
    sphere->FUN_00c78420(&ref);

  SP::GetTriggerMgr()->PostTrigger(param_1, 1, 1, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00d38ca0
// Releases one pause gate on the game time manager.
void FUN_00d38ca0(void)
{
  SP::cGameTimeManager* mgr = SP::GameTimeManager();
  mgr->DecPauseGate(0x4bf38a7);
}

// ---------------------------------------------------------------------------
// A state machine node: a mode word at +0x08 and an associated object at +0x14.
struct CStateNode {
  uint8_t mUnused00[0x08];
  int     mField08;                                       // +0x08
  uint8_t mUnused0c[0x08];
  int     mField14;                                       // +0x14

  bool FUN_00d38ec0(int type, void* src);
  void FUN_00d38e60(int reason);
};

// A source record whose payload word sits at +0x08.
struct CSourceRec {
  uint8_t mUnused00[0x08];
  int     mField08;                                       // +0x08
};

// ---------------------------------------------------------------------------
// @ 0x00d38ec0
// On one of two recognised event types, latch the node into its "started"
// state and copy the source record's payload word out of it.
bool CStateNode::FUN_00d38ec0(int type, void* src)
{
  if ((type == 0x6CA7A75 || type == 0xD3353639) && mField08 != 3) {
    mField08 = 1;
    mField14 = ((CSourceRec*)src)->mField08;
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------
// A pointer-range pair as passed to the search helper.
struct CPtrRange {
  int* mpBegin;                                           // +0x00
  int* mpEnd;                                             // +0x04
};

// A record whose key sits at +0x08.
struct CKeyedRec {
  uint8_t mUnused00[0x08];
  int     mKey;                                           // +0x08
};

// ---------------------------------------------------------------------------
// @ 0x00d397c0
// Linear scan of the pointer range: true when some element's key matches.
bool FUN_00d397c0(int key, CPtrRange* range)
{
  uint32_t count = (uint32_t)(range->mpEnd - range->mpBegin);
  int**    p     = (int**)range->mpBegin;
  for (uint32_t i = 0; i < count; ++i) {
    if (((CKeyedRec*)(*p))->mKey == key)
      return true;
    ++p;
  }
  return false;
}

// ---------------------------------------------------------------------------
// An 8-byte keyed pair used by the engine's sort/heap helpers.
struct CPair8 {
  int mKey;                                               // +0x00
  int mValue;                                             // +0x04
};

// ---------------------------------------------------------------------------
// @ 0x00d38bb0
// Insertion sort of [begin, end) keyed on the high word (eastl::insertion_sort).
void FUN_00d38bb0(CPair8* begin, CPair8* end)
{
  if (begin == end)
    return;
  CPair8* cur = begin;
  while ((cur = cur + 1) != end) {
    CPair8  v = *cur;
    CPair8* j = cur;
    while (j != begin && v.mValue > j[-1].mValue) {
      j[0] = j[-1];
      --j;
    }
    *j = v;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00d38c00
// Insertion sort variant that walks the moving hole with an int-stride cursor;
// the source has no explicit lower bound (the range carries a sentinel).
void FUN_00d38c00(int* begin, int* end)
{
  for (; begin != end; begin += 2) {
    int  k1   = begin[1];
    int  k0   = begin[0];
    int* j    = begin - 1;
    int* hole = begin;
    if (begin[-1] < k1) {
      do {
        hole[0] = hole[-2];
        hole[1] = hole[-1];
        j    -= 2;
        hole -= 2;
      } while (*j < k1);
    }
    hole[0] = k0;
    hole[1] = k1;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00d38c50
// Push-heap sift-up: moves the (key0,key1) pair up from `hole` while the parent
// ordering word is greater, stopping at `stop`.
void FUN_00d38c50(CPair8* base, int stop, int hole, int key0, int key1)
{
  int parent = (hole - 1) >> 1;
  while (hole > stop && base[parent].mValue > key1) {
    base[hole] = base[parent];
    hole   = parent;
    parent = (hole - 1) >> 1;
  }
  base[hole].mKey   = key0;
  base[hole].mValue = key1;
}

// ---------------------------------------------------------------------------
// An intrusive reference-counted interface (vtable: 0,1,2) held at +0x3c of an
// owner object, plus the thin pointer-slot wrapper that owns one.
struct IRefCounted {
  virtual void mSlot00();
  virtual void AddRef();
  virtual void Release();
};

struct CRefCounted {
  uint8_t     mUnused00[0x3c];
  IRefCounted mRef;                                       // +0x3c
};

struct CRefSlot {
  CRefCounted* mpObj;                                     // +0x00
  CRefSlot*    FUN_00d38b10(CRefCounted* other);
};

// ---------------------------------------------------------------------------
// @ 0x00d38b10
// Assigns the slot: add-refs the incoming owner and releases the old one.
CRefSlot* CRefSlot::FUN_00d38b10(CRefCounted* other)
{
  CRefCounted* old = mpObj;
  if (other != old) {
    if (other != 0)
      other->mRef.AddRef();
    mpObj = other;
    if (old != 0)
      old->mRef.Release();
  }
  return this;
}

// ---------------------------------------------------------------------------
// A globally held polymorphic object (four vtable slots) plus a latch byte.
struct CGObj {
  virtual void mSlot00();
  virtual void mSlot04();
  virtual void mSlot08();
  virtual void mSlot0c(int value);
};

CGObj* g_pModeObject;                                     // 0x0169e2d0
char   g_modeLatched;                                     // 0x0169e2cc

// ---------------------------------------------------------------------------
// @ 0x00d38d80
// Forwards the new mode flag to the global mode object and, when set, tears the
// object down; always latches the mode.
void FUN_00d38d80(char param_1)
{
  CGObj* obj = g_pModeObject;
  if (obj != 0) {
    obj->mSlot0c(param_1 != 0);
    if (param_1 != 0) {
      obj = g_pModeObject;
      if (obj != 0) {
        g_pModeObject = 0;
        obj->mSlot04();
      }
    }
  }
  g_modeLatched = 1;
}

// ---------------------------------------------------------------------------
// @ 0x00d38e60
// Posts the avatar-death cut-screen trigger matching the requested death cause.
void CStateNode::FUN_00d38e60(int reason)
{
  mField08 = 2;
  if (reason == 5) {
    SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied_Starvation", 1, 1, 0, 0, 0);
    return;
  }
  if (reason == 9) {
    SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied_SeaMonster", 1, 1, 0, 0, 0);
    return;
  }
  SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied", 1, 1, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// A collision-report noun: virtual type query at +0x20 and a payload fetch at
// +0x0c, plus the record it hands back (fields at +0x164/+0x16c) and the scatter
// manager its payload is ultimately placed into.
// ---------------------------------------------------------------------------
struct CCollisionNoun {
  virtual void mSlot00(); virtual void mSlot04(); virtual void mSlot08();
  virtual void* mSlot0c(int key);                         // +0x0c
  virtual void mSlot10(); virtual void mSlot14(); virtual void mSlot18(); virtual void mSlot1c();
  virtual int   mSlot20();                                // +0x20
};

struct CCollisionEntry {
  uint8_t mUnused000[0x164];
  int     mField164;                                      // +0x164
  int     mUnused168;                                     // +0x168
  int     mField16c;                                      // +0x16c
  void*   curEntry();                                     // 0x00b058a0
};

struct CScatterMgr {
  void PlaceIndexed(void* node, int idx, int zero);       // 0x00b09b80 (ret 0xC)
};

CScatterMgr* FUN_00b3d440();                               // 0x00b3d440

float g_collisionRadiusSq;                                 // 0x01582f38

// ---------------------------------------------------------------------------
// @ 0x00d38dd0
// When the separation vector's squared length clears the threshold, checks the
// second noun's type and places its current entry into the scatter manager.
void FUN_00d38dd0(int param_1, CCollisionNoun* param_2, int param_3, int param_4,
                  int param_5, int param_6, float* param_7)
{
  if (param_7[0] * param_7[0] + param_7[1] * param_7[1] + param_7[2] * param_7[2] > g_collisionRadiusSq) {
    if (param_2->mSlot20() == 0x2C9CC91) {
      CCollisionEntry* entry = (CCollisionEntry*)param_2->mSlot0c(0x2C9CC8E);
      if (entry != 0 && entry->mField16c == 0) {
        void* current = entry->curEntry();
        if (current != 0) {
          FUN_00b3d440()->PlaceIndexed(current, entry->mField164, 1);
        }
      }
    }
  }
}