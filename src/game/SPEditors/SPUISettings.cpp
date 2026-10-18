// src/game/SPEditors/SPUISettings.cpp -- migrated from slice(s) s00604890, s00603820, s00602940, s00601fd0, s00600e80, s00600260, s005ff230 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUISettings.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAudioTab.h"
#include "SP/cGameTab.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinSlider.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/CustomWindow.h"
#include "EA/UTFWin/Message.h"
#include "SP/cGraphicsTab.h"
#include "SP/cOnlineTab.h"
#include "SP/cPropertyList.h"
#include "EA/Audio/IPrimitive.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "SP/cSPUISettings.h"
#include "SP/cSettingsTab.h"
#include <string.h>
#include "SP/cString.h"
#include <stdlib.h>
#include "cSPUIPropertyLayout.h"
#include "cSPVerbIconRollover.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(uint64_t* count);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

// ---- items of slice s005ff230 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(uint64_t* count);
extern "C" unsigned __int64 __rdtsc();
namespace EA {
template <typename T>
class AutoRefCount_s005f_f230 {
 public:
  T* mpObject;
  AutoRefCount_s005f_f230& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
class Stopwatch_s005f_f230 {
 public:
  enum Units { kUnitsCycles = 1 };
  uint64_t mnStartTime;           // +0x0
  uint64_t mnTotalElapsedTime;    // +0x8
  int mnUnits;                    // +0x10
  float mfCyclesToUnits;          // +0x14
  bool mbRunning;                 // +0x18

  static uint64_t GetCPUCycle() { return __rdtsc(); }
  static uint64_t GetStopwatchCycle() {
    uint64_t t;
    QueryPerformanceCounter(&t);
    return t;
  }
  void Reset() {
    mnStartTime = 0;
    mnTotalElapsedTime = 0;
  }
  void Restart() {
    Reset();
    if (mnUnits == kUnitsCycles)
      mnStartTime = GetCPUCycle();
    else
      mnStartTime = GetStopwatchCycle();
    mnTotalElapsedTime = 0;
    mbRunning = false;
  }
};
}
namespace EA {
class LimitStopwatch_s005f_f230 : public Stopwatch_s005f_f230 {
 public:
  void SetTimeLimit(int limit, bool bStartTimer);  // 0x0093a480 (EA::LimitStopwatch::SetTimeLimit)
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_f230;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_f230 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();                      // +0x1c
  PV(8) PV(9) PV(10)
  virtual uint32_t GetState();                          // +0x2c
  PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
  PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005f_f230* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_f230* proc);           // +0x108
  virtual IWindow_s005f_f230* GetNextChild(IWindow_s005f_f230* prev);         // +0x10c
  virtual bool IsMessageFrom(const void* message);      // +0x110
};
}
}
namespace EA {
namespace UTFWin {
class IButton {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s005f_f230* ToWindow();                          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  virtual uint32_t GetButtonStateFlags();               // +0x2c
};
}
}
namespace EA {
namespace UTFWin {
class ISlider {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s005f_f230* ToWindow();                          // +0x10
  PV(5) PV(6)
  virtual void SetValue(int value, bool notify);        // +0x1c
  PV(8) PV(9) PV(10) PV(11)
  virtual int GetMaxValue();                            // +0x30
};
}
}
namespace EA {
namespace UTFWin {
class IFloatValue {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual float GetValue();                             // +0x14
};
}
}
namespace EA {
namespace UTFWin {
class IColorable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetColor(uint32_t color);                // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_f230 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005f_f230 {
  IWindow_s005f_f230* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;     // +0x8
  uint32_t padC[2];
  int mValue;         // +0x14
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_f230 {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);         // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void RemoveHandler(IHandler_s005f_f230* handler, uint32_t messageID, int priority);  // +0x2c
};
}
}
using EA::UTFWin::IWindow_s005f_f230;
using EA::UTFWin::IWinProc_s005f_f230;
using EA::UTFWin::IButton;
using EA::UTFWin::ISlider;
using EA::UTFWin::Message_s005f_f230;
class cSPUILayout_s005f_f230 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  IWindow_s005f_f230* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool Init(uint32_t instanceID, uint32_t typeID, uint32_t groupID);  // 0x008120d0 (cSPUILayout::Init)
  void GetObjects();  // 0x008100c0 (cSPUILayout::GetObjects)
  void Shutdown(bool b);  // 0x00811ad0 (cSPUILayout::Shutdown)
  char pad[0x18 - 4];
};
class cSPUILayoutManager_s005f_f230 {
 public:
  void SetWorldVisibility(uint32_t worldID, bool visible);  // FUN_00810660
  void SetAllWorldsVisibility(bool visible);  // 0x008106a0 (cSPUILayoutManager::SetAllWorldsVisibility)
};
cSPUILayoutManager_s005f_f230* SPUILayoutManager();  // 0x80fee0
namespace SPUIHelpers {
void EndModal(IWindow_s005f_f230* window, int a, int b);
}
struct cRefCounted {
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void Close(int a);  // +0xc
};
void ReleaseObject(void* p, int a);        // FUN_00572020
void DestroyWindowTree(void* p);           // FUN_008076f0
uint32_t CreateSoundHandle();              // 0x435e90 (GetRecorderState)
void PlayUISound(uint32_t soundID, uint32_t handle);  // 0x435ed0
namespace SP {
EA::Messaging::IMessageServer* MessageServer();
}
namespace SP {
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, int value);  // +0x2c
  virtual int GetValue(uint32_t id);              // +0x30
};
}
namespace SP {
IConfigManager* ConfigManager();
}
namespace SP {
class IApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual uint32_t GetModeID();  // +0x38
};
}
namespace SP {
IApp* App();
}
namespace SP {
class ICanvas {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual bool IsFullscreen();  // +0x54
};
}
namespace SP {
ICanvas* Canvas();
}
namespace SP {
class cPropertyList_s005f_f230 {
 public:
  bool HasProperty(uint32_t id);  // 0x6a25a0
};
}
namespace SP {
extern cPropertyList_s005f_f230* gAppProperties;  // 0x15fd918
}
namespace SP {
namespace Audio {
class cAudioPreferences_s005f_f230 {
 public:
  bool IsMuted();  // 0x00a41280 (SP::Audio::cAudioPreferences::IsMuted)
  void Mute(bool mute);  // 0x00a415f0 (SP::Audio::cAudioPreferences::Mute)
  int GetSoundQuality();  // 0x00a41240 (SP::Audio::cAudioPreferences::GetSoundQuality)
  void SetSoundQuality(int quality);  // 0x00a41500 (SP::Audio::cAudioPreferences::SetSoundQuality)
  int GetSpeakerMode();  // 0x00a41200 (SP::Audio::cAudioPreferences::GetSpeakerMode)
  void SetSpeakerMode(int mode);  // 0x00a41410 (SP::Audio::cAudioPreferences::SetSpeakerMode)
  bool GetVolume(uint32_t id, float* volume);  // 0x00a411b0 (SP::Audio::cAudioPreferences::GetVolume)
  void SetVolume(uint32_t id, float volume);  // 0x00a412c0 (SP::Audio::cAudioPreferences::SetVolume)
};  // namespace Audio
}
}
namespace SP {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual Audio::cAudioPreferences_s005f_f230* GetPreferences();  // +0x3c
};
}
namespace SP {
IAudioSystem* AudioSystem();
}
namespace SP {
class IOnlinePrefs {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetLoginEnabled(bool b);  // +0x28
  virtual bool GetLoginEnabled();        // +0x2c
  PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual void Save();                   // +0x54
};
}
namespace SP {
IOnlinePrefs* OnlinePrefs();  // FUN_00607a60
}
namespace SP {
class cSettingsTab_s005f_f230 {
 public:
  virtual ~cSettingsTab_s005f_f230();
  virtual void Init(uint32_t layoutID, IWinProc_s005f_f230* winProc, uint32_t tabID);
  IWinProc_s005f_f230* mWinProc;     // +0x4
  cSPUILayout_s005f_f230 mLayout;    // +0x8
  uint32_t mTabID;        // +0x20
};
}
namespace SP {
class cAudioTab_s005f_f230 : public cSettingsTab_s005f_f230 {
 public:
  void Init(uint32_t layoutID, IWinProc_s005f_f230* winProc, uint32_t tabID);  // 0x005ffa30 (SP::cAudioTab::Init)
  void Shutdown();
  void RestoreSettingsFromEntry();  // 0x005ff2d0 (SP::cAudioTab::RestoreSettingsFromEntry)
  __forceinline void CheckButton(uint32_t id) {
    IWindow_s005f_f230* w = mLayout.FindWindowByID(id, true);
    if (w) {
      IButton* button = (IButton*)w->Cast(0x8ed27e7a);
      if (button) button->SetButtonStateFlag(4, true);
    }
  }
  bool DoMessageTab(IWindow_s005f_f230* window, const Message_s005f_f230* message);
  uint32_t mhSound;                 // +0x24
  int mInitialSoundQuality;         // +0x28
  float mInitialMasterVolume;       // +0x2c
  float mInitialSFXVolume;          // +0x30
  float mInitialMusicVolume;        // +0x34
  float mInitialAmbienceVolume;     // +0x38
  float mInitialVOXVolume;          // +0x3c
  float mInitialUIVolume;           // +0x40
  int mInitialSpeakerMode;          // +0x44
  bool mbInitialMuteAll;            // +0x48
};
}
namespace SP {
class cGameTab_s005f_f230 : public cSettingsTab_s005f_f230 {
 public:
  void Shutdown();  // 0x005ff630 (SP::cGameTab::Shutdown)
  bool DoMessageTab(IWindow_s005f_f230* window, const Message_s005f_f230* message);
  void RestoreSettingsFromEntry();
  bool mInitialTutorialsSettings;   // +0x24
  bool mInitialShowHints;           // +0x25
  bool mInitialMovieRes;            // +0x26
  bool mInitialPhotoRes;            // +0x27
  bool mInitialGameDifficulty;      // +0x28
};
}
namespace SP {
class cOnlineTab_s005f_f230 : public cSettingsTab_s005f_f230, public EA::Messaging::IHandler_s005f_f230 {
 public:
  void Shutdown();
  void RestoreSettingsFromEntry();
  char pad28[0x48 - 0x28];
  bool mInitial[8];                 // +0x48
};
}
namespace SP {
class cOptionTab : public cSettingsTab_s005f_f230 {
 public:
  void RestoreSettingsFromEntry();
  bool mInitialValue;               // +0x24
  uint32_t mPropertyID;             // +0x28
};
}
namespace SP {
struct cProfileEntry {
  void Shutdown();  // FUN_005fe320
  char pad[0x58];
};
}
namespace SP {
class cGraphicsTab_s005f_f230 : public cSettingsTab_s005f_f230 {
 public:
  void Shutdown();
  void UpdateFullscreenControls();
  cProfileEntry* mpBegin;           // +0x24
  cProfileEntry* mpEnd;             // +0x28
  char pad2c[0x48 - 0x2c];
  EA::AutoRefCount_s005f_f230<cRefCounted> mpA;  // +0x48
  EA::AutoRefCount_s005f_f230<IWindow_s005f_f230> mpWindow; // +0x4c
  EA::AutoRefCount_s005f_f230<cRefCounted> mpC;  // +0x50
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  cProfileEntry& operator[](uint32_t i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPUISettings_s005f_f230 {
 public:
  void BeginClose();  // 0x005ff700 (SP::cSPUISettings::BeginClose)
  void SaveOnlineSettings();  // 0x005ff850 (SP::cSPUISettings::SaveOnlineSettings)
  char pad0[0x14];
  EA::AutoRefCount_s005f_f230<cSPUILayout_s005f_f230> mpLayout;   // +0x14
  char pad18[0x1a9 - 0x18];
  bool mbInitialYouTubeLogin;               // +0x1a9
  char pad1aa[0x220 - 0x1aa];
  EA::AutoRefCount_s005f_f230<cRefCounted> mpModal;    // +0x220
  char pad224[4];
  EA::LimitStopwatch_s005f_f230 mLimitStopwatch;       // +0x228
};
}
struct cTimedObject {
  void RestartTimer();
  char pad[0x80];
  EA::Stopwatch_s005f_f230 mStopwatch;  // +0x80
};
static inline int FloatToInt(float f) { __asm cvtss2si eax, f }
// ---- items of slice s005ff230 end

// ---- items of slice s00600260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s0060_0260(n) virtual void _pv##n();
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void  operator delete(void* p); // 0x00f47380
inline void* operator new(size_t, void* p) throw() { return p; }
namespace EA {
namespace ResourceMan {
struct Key_s0060_0260 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s0060_0260& a, const Key_s0060_0260& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s0060_0260 {
  uint32_t operator()(const Key_s0060_0260& k) const;
};
}
}
using EA::ResourceMan::Key_s0060_0260;
namespace eastl {
struct allocator_s0060_0260 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
inline wchar_t* GetEmptyStringW() { return gEmptyString16; }
}
namespace eastl {
template <typename T>
class basic_string_s0060_0260 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s0060_0260 mAllocator;

  basic_string_s0060_0260() { AllocateSelf(); }
  basic_string_s0060_0260(const basic_string_s0060_0260& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s0060_0260() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    wchar_t* e = GetEmptyStringW();
    mpBegin = (T*)e;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) { if (p) mAllocator.deallocate(p); }
  void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin)); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd = mpEnd - (pLast - pFirst);
    }
    return pFirst;
  }
  basic_string_s0060_0260& assign(const T* pBegin, const T* pEnd);
  basic_string_s0060_0260& operator=(const basic_string_s0060_0260& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s0060_0260<wchar_t> string16_s0060_0260;
}
namespace eastl {
bool operator==(const basic_string_s0060_0260<wchar_t>& a, const basic_string_s0060_0260<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s0060_0260 {
  uint32_t operator()(const string16_s0060_0260& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s0060_0260 {
  bool operator()(const string16_s0060_0260& a, const string16_s0060_0260& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_0260 {
  T1 first;
  T2 second;
  pair_s0060_0260(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s0060_0260(const pair_s0060_0260& p) : first(p.first), second(p.second) {}
  ~pair_s0060_0260() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s0060_0260 {
  Value mValue;
  hash_node_s0060_0260* mpNext;
};
}
namespace eastl {
template <typename Node>
struct hashtable_iterator_base {
  Node* mpNode;
  Node** mpBucket;
  hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
template <typename T, typename Node>
struct hashtable_iterator : public hashtable_iterator_base<Node> {
  typedef hashtable_iterator_base<Node> base_type;
  hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : base_type(pNode, pBucket) {}
  explicit hashtable_iterator(Node** pBucket) : base_type(*pBucket, pBucket) {}
  hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  template <typename U>
  hashtable_iterator(const hashtable_iterator<U, Node>& x) : base_type(x.mpNode, x.mpBucket) {}
  void increment() {
    this->mpNode = this->mpNode->mpNext;
    while (this->mpNode == 0) this->mpNode = *++this->mpBucket;
  }
  void increment_bucket() {
    ++this->mpBucket;
    while (*this->mpBucket == 0) ++this->mpBucket;
    this->mpNode = *this->mpBucket;
  }
  bool operator!=(const hashtable_iterator& x) const { return this->mpNode != x.mpNode; }
  bool operator==(const hashtable_iterator& x) const { return this->mpNode == x.mpNode; }
  hashtable_iterator& operator++() { increment(); return *this; }
};
}
namespace eastl {
struct RehashResult { bool first; uint32_t second; };
}
namespace eastl {
struct prime_rehash_policy_s0060_0260 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
extern void* gEmptyBucketArray;   // 0x0154df28
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s0060_0260>
class hashtable_s0060_0260 {
 public:
  typedef hash_node_s0060_0260<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;
  typedef hashtable_iterator<const Value, node_type> const_iterator;
  struct insert_return_type {
    iterator first;
    bool second;
    insert_return_type(const iterator& i, bool b) : first(i), second(b) {}
  };

  Hash mHash;
  node_type** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  prime_rehash_policy_s0060_0260 mRehashPolicy;
  allocator_s0060_0260 mAllocator;

  hashtable_s0060_0260() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mRehashPolicy.mnNextResize = 0;
  }

  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  __forceinline node_type* DoFindNode(node_type* pNode, const KeyT& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (k == pNode->mValue.first) return pNode;
    return 0;
  }
  void DoFreeNode(node_type* pNode) { pNode->~node_type(); mAllocator.deallocate(pNode); }

  iterator find(const KeyT& k);
  pair_s0060_0260<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s0060_0260() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s0060_0260<V, K, H, E>::iterator hashtable_s0060_0260<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s0060_0260<typename hashtable_s0060_0260<V, K, H, E>::iterator, typename hashtable_s0060_0260<V, K, H, E>::iterator>
hashtable_s0060_0260<V, K, H, E>::equal_range(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext)
      if (!(k == p1->mValue.first)) break;
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair_s0060_0260<iterator, iterator>(first, last);
  }
  return pair_s0060_0260<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s0060_0260<string16_s0060_0260, Key_s0060_0260> NameKeyPair;
}
namespace eastl {
typedef pair_s0060_0260<Key_s0060_0260, string16_s0060_0260> KeyNamePair;
}
namespace eastl {
typedef hashtable_s0060_0260<NameKeyPair, string16_s0060_0260, hash_s0060_0260, equal_to_s0060_0260> NameKeyMap;
}
namespace eastl {
typedef hashtable_s0060_0260<KeyNamePair, Key_s0060_0260, EA::ResourceMan::KeyHash_s0060_0260> KeyNameMap;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID& a, const AssetGUID& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash {
  uint32_t operator()(const AssetGUID& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_0260<AssetGUID, Key_s0060_0260> GuidKeyPair;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_0260<Key_s0060_0260, AssetGUID> KeyGuidPair;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_0260<GuidKeyPair, AssetGUID, AssetGUIDHash> GuidKeyMap;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_0260<KeyGuidPair, Key_s0060_0260, EA::ResourceMan::KeyHash_s0060_0260> KeyGuidMap;
}
}
struct ConfigManagerStub {
  PV_s0060_0260(0) PV_s0060_0260(1) PV_s0060_0260(2) PV_s0060_0260(3) PV_s0060_0260(4) PV_s0060_0260(5) PV_s0060_0260(6) PV_s0060_0260(7) PV_s0060_0260(8) PV_s0060_0260(9) PV_s0060_0260(10)
  virtual void vt2c(uint32_t id, uint8_t v);       // +0x2c
  virtual uint8_t vt30(uint32_t id);               // +0x30
};
ConfigManagerStub* ConfigManager_s0060_0260();   // 0x0067dd30
struct LayoutStub {
  char pad[0x41];
  void* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0
};
struct WinWithIDStub {
  PV_s0060_0260(0) PV_s0060_0260(1) PV_s0060_0260(2)
  virtual void* vt0c(uint32_t id);                 // +0x0c
  PV_s0060_0260(4) PV_s0060_0260(5) PV_s0060_0260(6) PV_s0060_0260(7) PV_s0060_0260(8) PV_s0060_0260(9)
  virtual void vt28(int a, bool b);                // +0x28
};
struct OnlineTabStub {
  char pad0[8];
  LayoutStub mLayout;       // +0x8 (0x41 bytes)
  uint8_t mbFlag;           // +0x49
  void DoMessageTab();      // 0x00600260
};
// ---- items of slice s00600260 end

// ---- items of slice s00600e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s0060_0e80(n) virtual void _pv##n();
namespace EA {
namespace ResourceMan {
struct Key_s0060_0e80 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s0060_0e80& a, const Key_s0060_0e80& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s0060_0e80 {
  uint32_t operator()(const Key_s0060_0e80& k) const;
};
}
}
using EA::ResourceMan::Key_s0060_0e80;
namespace eastl {
struct allocator_s0060_0e80 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s0060_0e80 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s0060_0e80 mAllocator;

  basic_string_s0060_0e80() { AllocateSelf(); }
  basic_string_s0060_0e80(const basic_string_s0060_0e80& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s0060_0e80() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    wchar_t* e = GetEmptyStringW();
    mpBegin = (T*)e;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) { if (p) mAllocator.deallocate(p); }
  void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin)); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd = mpEnd - (pLast - pFirst);
    }
    return pFirst;
  }
  basic_string_s0060_0e80& assign(const T* pBegin, const T* pEnd);
  basic_string_s0060_0e80& operator=(const basic_string_s0060_0e80& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s0060_0e80<wchar_t> string16_s0060_0e80;
}
namespace eastl {
bool operator==(const basic_string_s0060_0e80<wchar_t>& a, const basic_string_s0060_0e80<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s0060_0e80 {
  uint32_t operator()(const string16_s0060_0e80& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s0060_0e80 {
  bool operator()(const string16_s0060_0e80& a, const string16_s0060_0e80& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_0e80 {
  T1 first;
  T2 second;
  pair_s0060_0e80(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s0060_0e80(const pair_s0060_0e80& p) : first(p.first), second(p.second) {}
  ~pair_s0060_0e80() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s0060_0e80 {
  Value mValue;
  hash_node_s0060_0e80* mpNext;
};
}
namespace eastl {
struct prime_rehash_policy_s0060_0e80 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s0060_0e80>
class hashtable_s0060_0e80 {
 public:
  typedef hash_node_s0060_0e80<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;
  typedef hashtable_iterator<const Value, node_type> const_iterator;
  struct insert_return_type {
    iterator first;
    bool second;
    insert_return_type(const iterator& i, bool b) : first(i), second(b) {}
  };

  Hash mHash;
  node_type** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  prime_rehash_policy_s0060_0e80 mRehashPolicy;
  allocator_s0060_0e80 mAllocator;

  hashtable_s0060_0e80() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mRehashPolicy.mnNextResize = 0;
  }

  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  __forceinline node_type* DoFindNode(node_type* pNode, const KeyT& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (k == pNode->mValue.first) return pNode;
    return 0;
  }
  void DoFreeNode(node_type* pNode) { pNode->~node_type(); mAllocator.deallocate(pNode); }

  iterator find(const KeyT& k);
  pair_s0060_0e80<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s0060_0e80() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s0060_0e80<V, K, H, E>::iterator hashtable_s0060_0e80<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s0060_0e80<typename hashtable_s0060_0e80<V, K, H, E>::iterator, typename hashtable_s0060_0e80<V, K, H, E>::iterator>
hashtable_s0060_0e80<V, K, H, E>::equal_range(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext)
      if (!(k == p1->mValue.first)) break;
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair_s0060_0e80<iterator, iterator>(first, last);
  }
  return pair_s0060_0e80<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s0060_0e80<string16_s0060_0e80, Key_s0060_0e80> NameKeyPair_s0060_0e80;
}
namespace eastl {
typedef pair_s0060_0e80<Key_s0060_0e80, string16_s0060_0e80> KeyNamePair_s0060_0e80;
}
namespace eastl {
typedef hashtable_s0060_0e80<NameKeyPair_s0060_0e80, string16_s0060_0e80, hash_s0060_0e80, equal_to_s0060_0e80> NameKeyMap_s0060_0e80;
}
namespace eastl {
typedef hashtable_s0060_0e80<KeyNamePair_s0060_0e80, Key_s0060_0e80, EA::ResourceMan::KeyHash_s0060_0e80> KeyNameMap_s0060_0e80;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s0060_0e80 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s0060_0e80& a, const AssetGUID_s0060_0e80& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s0060_0e80 {
  uint32_t operator()(const AssetGUID_s0060_0e80& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_0e80<AssetGUID_s0060_0e80, Key_s0060_0e80> GuidKeyPair_s0060_0e80;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_0e80<Key_s0060_0e80, AssetGUID_s0060_0e80> KeyGuidPair_s0060_0e80;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_0e80<GuidKeyPair_s0060_0e80, AssetGUID_s0060_0e80, AssetGUIDHash_s0060_0e80> GuidKeyMap_s0060_0e80;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_0e80<KeyGuidPair_s0060_0e80, Key_s0060_0e80, EA::ResourceMan::KeyHash_s0060_0e80> KeyGuidMap_s0060_0e80;
}
}
namespace SP {
namespace Thumbnail {
struct IMessageServerStub {
  PV_s0060_0e80(0) PV_s0060_0e80(1) PV_s0060_0e80(2) PV_s0060_0e80(3) PV_s0060_0e80(4) PV_s0060_0e80(5) PV_s0060_0e80(6) PV_s0060_0e80(7) PV_s0060_0e80(8) PV_s0060_0e80(9) PV_s0060_0e80(10)
  virtual void vt2c(void* p, uint32_t a, int b);   // +0x2c
};
}
}
namespace SP {
namespace Thumbnail {
IMessageServerStub* GetMessageServer();   // 0x0067dcc0
}
}
struct IRefCounted2 { virtual int AddRef(); virtual int Release(); };
struct IntrusivePtr2 {
  IRefCounted2* mpObject;
  IntrusivePtr2& operator=(const IntrusivePtr2& x) {
    IRefCounted2* const p = x.mpObject;
    IRefCounted2* const pOld = mpObject;
    if (p != pOld) {
      if (p) p->AddRef();
      mpObject = p;
      if (pOld) pOld->Release();
    }
    return *this;
  }
};
struct SubObj14 {
  uint32_t pad[5];
  SubObj14& operator=(const SubObj14&);
};
struct SettingsRecord {
  IntrusivePtr2 m0;          // +0x00
  uint32_t f4, f8;           // +0x04, +0x08
  eastl::string16_s0060_0e80 mName;     // +0x0c
  uint32_t f1c, f20, f24, f28, f2c, f30, f34, f38;   // +0x1c..+0x38
  SubObj14 m3c;              // +0x3c
  uint32_t f50, f54;         // +0x50, +0x54
  SettingsRecord& operator=(const SettingsRecord& o);
};
struct LayoutShutdown { void Shutdown(int a); };   // 0x00811ad0
struct SPUISettingsStub {
  char pad0[0x10];
  char mHandler[4];        // +0x10 (IHandler subobject passed to MessageServer)
  void* mpLayout;          // +0x14
  char pad18[0x20c - 0x18];
  uint32_t* mTabBegin;     // +0x20c
  uint32_t* mTabEnd;       // +0x210
  void RemoveTab(uint32_t id);   // 0x00601da0
  bool Shutdown();               // 0x00601e60
};
// ---- items of slice s00600e80 end

// ---- items of slice s00601fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
class IWinProc_s0060_1fd0;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_1fd0;
}
}
namespace EA {
namespace UTFWin {
struct Rect { float x1, y1, x2, y2; };
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_1fd0 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const Rect* GetArea();                        // +0x34
  PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24)
  virtual void SetLocation(float x, float y);           // +0x64
  PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  virtual void SetCaption(const wchar_t* caption);      // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
  PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s0060_1fd0* proc);              // +0x104
};
}
}
namespace EA {
namespace UTFWin {
class IButton_s0060_1fd0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class IColorable_s0060_1fd0 {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s0060_1fd0* ToWindow();                          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetColor(uint32_t color);                // +0x28
};
}
}
using EA::UTFWin::IWindow_s0060_1fd0;
using EA::UTFWin::IWinProc_s0060_1fd0;
using EA::UTFWin::IButton_s0060_1fd0;
using EA::UTFWin::IColorable_s0060_1fd0;
class cSPUILayout_s0060_1fd0 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  IWindow_s0060_1fd0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
  bool Init(uint32_t instanceID, uint32_t typeID, uint32_t groupID);   // 0x008120d0
  void GetObjects();                                      // 0x008100c0
  char pad[0x18 - 4];
};
struct WString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  WString() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void RangeInitialize(const wchar_t* pBegin);            // 0x00579a90
  void erase(uint32_t position, uint32_t n);              // 0x004228e0
};
const wchar_t* FindEnd(const wchar_t* a, const wchar_t* b, const wchar_t* c, const wchar_t* d);   // 0x005728f0
void operator_delete_array_00f47380(void* p);             // operator delete[]
namespace SP {
class cString_s0060_1fd0 {
 public:
  cString_s0060_1fd0();                                                            // 0x006b5060
  ~cString_s0060_1fd0();                                                           // 0x006b5240
  bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);   // 0x006b54b0
  const wchar_t* GetText();                                             // 0x006b55c0
 private:
  uint32_t mData[6];
};
}
namespace SP {
class ISaveArea {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual const wchar_t* GetPath();               // +0x28
};
}
namespace SP {
ISaveArea* GetSaveArea(uint32_t id);              // 0x006b1f90
}
namespace SP {
class IPathTarget {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void SetPath(const wchar_t* path, int flags);   // +0x34
};
}
namespace SP {
class IPathProvider {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IPathTarget* GetTarget();               // +0x20
};
}
namespace SP {
IPathProvider* FUN_0067de40();                    // 0x0067de40
}
namespace SP {
struct cPropertyListData { char pad[0x118]; int mField118; };
}
namespace SP {
class cPropertyList_s0060_1fd0 {
 public:
  bool GetDescription(uint32_t id);               // 0x006a25a0
  char pad[0x3c];
  cPropertyListData* mpData;                      // +0x3c
};
}
namespace SP {
extern cPropertyList_s0060_1fd0* gAppProperties_s0060_1fd0;             // 0x015fd918
}
namespace SP {
class cSettingsTab_s0060_1fd0 {
 public:
  virtual ~cSettingsTab_s0060_1fd0();
  virtual void Init(uint32_t layoutID, IWinProc_s0060_1fd0* winProc, uint32_t tabID);  // 0x005ff8e0 (SP::cSettingsTab::Init)
  IWinProc_s0060_1fd0* mWinProc;     // +0x4
  cSPUILayout_s0060_1fd0 mLayout;    // +0x8
  uint32_t mTabID;        // +0x20
};
}
namespace SP {
class cGameTab_s0060_1fd0 : public cSettingsTab_s0060_1fd0 {
 public:
  void Init(uint32_t layoutID, IWinProc_s0060_1fd0* winProc, uint32_t tabID);  // 0x00601fd0 (SP::cGameTab::Init)
  bool mInitialTutorialsSettings;   // +0x24
  bool mInitialShowHints;           // +0x25
  bool mInitialMovieRes;            // +0x26
  bool mInitialPhotoRes;            // +0x27
  bool mInitialGameDifficulty;      // +0x28
};
}
static __forceinline IButton_s0060_1fd0* ButtonOf(IWindow_s0060_1fd0* w) { return w ? (IButton_s0060_1fd0*)w->Cast(0x8ed27e7a) : 0; }
static __forceinline uint32_t RFind(WString& s, const wchar_t* lit) {
  const wchar_t* pEnd = lit;
  while (*pEnd) ++pEnd;
  uint32_t length = (uint32_t)(s.mpEnd - s.mpBegin);
  if (length) {
    const wchar_t* pSearchEnd = s.mpBegin + (length - 1) + 1;
    const wchar_t* r = FindEnd(pSearchEnd, s.mpBegin, lit, pEnd);
    if (r != s.mpBegin) return (uint32_t)(r - s.mpBegin) - 1;
  }
  return (uint32_t)-1;
}
// ---- items of slice s00601fd0 end

// ---- items of slice s00602940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyStr16[2];                          // 0x01667bac
    extern float gF1485720; // 0x01485720
    extern float gF151d728; // 0x0151d728
namespace EA {
namespace ResourceMan {
struct Key_s0060_2940 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s0060_2940& a, const Key_s0060_2940& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s0060_2940 {
  uint32_t operator()(const Key_s0060_2940& k) const;
};
}
}
using EA::ResourceMan::Key_s0060_2940;
namespace eastl {
struct allocator_s0060_2940 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s0060_2940 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s0060_2940 mAllocator;

  basic_string_s0060_2940() { AllocateSelf(); }
  basic_string_s0060_2940(const basic_string_s0060_2940& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s0060_2940() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    wchar_t* e = GetEmptyStringW();
    mpBegin = (T*)e;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) { if (p) mAllocator.deallocate(p); }
  void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin)); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd = mpEnd - (pLast - pFirst);
    }
    return pFirst;
  }
  basic_string_s0060_2940& assign(const T* pBegin, const T* pEnd);
  basic_string_s0060_2940& operator=(const basic_string_s0060_2940& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s0060_2940<wchar_t> string16_s0060_2940;
}
namespace eastl {
bool operator==(const basic_string_s0060_2940<wchar_t>& a, const basic_string_s0060_2940<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s0060_2940 {
  uint32_t operator()(const string16_s0060_2940& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s0060_2940 {
  bool operator()(const string16_s0060_2940& a, const string16_s0060_2940& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_2940 {
  T1 first;
  T2 second;
  pair_s0060_2940(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s0060_2940(const pair_s0060_2940& p) : first(p.first), second(p.second) {}
  ~pair_s0060_2940() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s0060_2940 {
  Value mValue;
  hash_node_s0060_2940* mpNext;
};
}
namespace eastl {
struct prime_rehash_policy_s0060_2940 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s0060_2940>
class hashtable_s0060_2940 {
 public:
  typedef hash_node_s0060_2940<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;
  typedef hashtable_iterator<const Value, node_type> const_iterator;
  struct insert_return_type {
    iterator first;
    bool second;
    insert_return_type(const iterator& i, bool b) : first(i), second(b) {}
  };

  Hash mHash;
  node_type** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  prime_rehash_policy_s0060_2940 mRehashPolicy;
  allocator_s0060_2940 mAllocator;

  hashtable_s0060_2940() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mRehashPolicy.mnNextResize = 0;
  }

  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  __forceinline node_type* DoFindNode(node_type* pNode, const KeyT& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (k == pNode->mValue.first) return pNode;
    return 0;
  }
  void DoFreeNode(node_type* pNode) { pNode->~node_type(); mAllocator.deallocate(pNode); }

  iterator find(const KeyT& k);
  pair_s0060_2940<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s0060_2940() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s0060_2940<V, K, H, E>::iterator hashtable_s0060_2940<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s0060_2940<typename hashtable_s0060_2940<V, K, H, E>::iterator, typename hashtable_s0060_2940<V, K, H, E>::iterator>
hashtable_s0060_2940<V, K, H, E>::equal_range(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext)
      if (!(k == p1->mValue.first)) break;
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair_s0060_2940<iterator, iterator>(first, last);
  }
  return pair_s0060_2940<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s0060_2940<string16_s0060_2940, Key_s0060_2940> NameKeyPair_s0060_2940;
}
namespace eastl {
typedef pair_s0060_2940<Key_s0060_2940, string16_s0060_2940> KeyNamePair_s0060_2940;
}
namespace eastl {
typedef hashtable_s0060_2940<NameKeyPair_s0060_2940, string16_s0060_2940, hash_s0060_2940, equal_to_s0060_2940> NameKeyMap_s0060_2940;
}
namespace eastl {
typedef hashtable_s0060_2940<KeyNamePair_s0060_2940, Key_s0060_2940, EA::ResourceMan::KeyHash_s0060_2940> KeyNameMap_s0060_2940;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s0060_2940 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s0060_2940& a, const AssetGUID_s0060_2940& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s0060_2940 {
  uint32_t operator()(const AssetGUID_s0060_2940& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_2940<AssetGUID_s0060_2940, Key_s0060_2940> GuidKeyPair_s0060_2940;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_2940<Key_s0060_2940, AssetGUID_s0060_2940> KeyGuidPair_s0060_2940;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_2940<GuidKeyPair_s0060_2940, AssetGUID_s0060_2940, AssetGUIDHash_s0060_2940> GuidKeyMap_s0060_2940;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_2940<KeyGuidPair_s0060_2940, Key_s0060_2940, EA::ResourceMan::KeyHash_s0060_2940> KeyGuidMap_s0060_2940;
}
}
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PV1 virtual void CAT(_pv, __COUNTER__)();
#define PV5 PV1 PV1 PV1 PV1 PV1
#define PV20 PV5 PV5 PV5 PV5
void __cdecl WStr_Format(void*, const wchar_t*, ...);   // 0x0041e050
struct WStr {
  wchar_t* b; wchar_t* e; wchar_t* c;
  WStr() { b = gEmptyStr16; e = gEmptyStr16; c = gEmptyStr16 + 1; }
  ~WStr() { if ((((char*)c - (char*)b) & ~1) > 2 && b) operator delete[](b); }
};
WStr* __cdecl ConvertToString16(WStr* out, int v);       // 0x0093c6d0 EA::ConvertToString16
namespace SP {
class cString_s0060_2940 {
 public:
  cString_s0060_2940();                                                    // 0x006b5060
  ~cString_s0060_2940();                                                   // 0x006b5240
  void Load(uint32_t table, uint32_t inst, const wchar_t* def); // 0x006b54b0
  const wchar_t* GetText();                                     // 0x006b55c0
  uint32_t pad[5];
};
}
struct IWin {
  virtual int AddRef();                                  // +0x00
  virtual int Release();                                 // +0x04
  PV1
  virtual IWin* QueryChild(uint32_t id);                 // +0x0c
  virtual IWin* GetSub();                                // +0x10
  virtual void SetValue(int v, int w);                   // +0x14
  PV1 PV1
  virtual int GetID(int a);                              // +0x20
  PV1
  virtual void SetState(int a, int b);                   // +0x28
  PV20                                                   // slots 11..30
  virtual void SetFlag(int flag, int on);                // +0x7c
  virtual void SetCaption(const wchar_t* text);          // +0x80
  PV20 PV1                                               // slots 33..53
  virtual void AddChildWin(IWin* child);                 // +0xd8
  PV5                                                    // slots 55..59
  virtual IWin* FindByID(uint32_t id, int recursive);    // +0xf0
  PV1 PV1 PV1 PV1                                        // slots 61..64
  virtual void SetWinProc(void* proc);                   // +0x104
};
struct IColorWin { PV5 PV5 virtual void SetColor(uint32_t c); };   // slot +0x28, one argument
class cSPUILayout_s0060_2940 {
 public:
  virtual void pv0();
  virtual int AddRef();
  virtual int Release();
  cSPUILayout_s0060_2940();                                                         // 0x00810000
  bool Init(const wchar_t* name, uint32_t key, int a, uint32_t b);       // 0x00812160
  void InitTab(const wchar_t* name, int a, uint32_t b);                  // 0x008120d0
  void GetObjects();                                                     // 0x008100c0
  IWin* FindWindowByID(uint32_t id, int recursive);                      // 0x008105b0
  uint32_t pad[4];
};
namespace SPUIHelpers {
void __cdecl SetWindowAreaToParent(IWin* w);                    // 0x00806bf0
}
namespace SPUIHelpers {
void __cdecl AutoSizeWindowForText(IWin* w, int a, int b);      // 0x00806e40
}
namespace SPUIHelpers {
void __cdecl ResetScrollFrameColor(IWin* w);                    // 0x00807040
}
namespace SPUIHelpers {
void __cdecl SetRotation(IWin* w, const float* q);              // 0x00808230 UI::cWindowTransform::SetRotation
}
IWin* __stdcall GetLayoutManager(uint32_t id);          // 0x00805070 (SPUIHelpers::GetLayoutManager)
struct cSPUILayoutManager_s0060_2940 { IWin* GetWorldMainWindow(); };  // 0x00810620
const float* __cdecl FUN_00805260(IWin* w);             // 0x00805260 -> float[4]
struct IMsgListener;
struct IMsgServer {
  PV5 PV1 PV1 PV1 PV1
  virtual void AddListener(IMsgListener* l, uint32_t id);   // +0x24
};
IMsgServer* __cdecl MessageServer_s0060_2940();                    // 0x0067dcc0
struct IConfigMgr {
  PV5 PV5 PV1 PV1
  virtual int GetValue(uint32_t id);                         // +0x30
};
IConfigMgr* __cdecl ConfigManager_s0060_2940();                         // 0x0067dd30
struct IUserName { PV5 PV5 PV1 PV1 PV1 virtual void SetName(const wchar_t* s, int a); };   // +0x34
struct IUserInfo { PV5 PV1 PV1 PV1 virtual IUserName* GetName(); };                        // +0x20
IUserInfo* __cdecl FUN_0067de40_s0060_2940();                                                         // 0x0067de40
struct IAuth {   // SP::Pollen::AuthManager (0x00607a60)
  PV5 PV1 PV1 PV1 PV1
  virtual int IsGuest();            // +0x24
  PV1
  virtual int GetStatus();          // +0x2c
  PV1 PV1
  virtual int GetUserID();          // +0x38
  PV5 PV1 PV1
  virtual int IsLoggedIn();         // +0x58
};
IAuth* __cdecl AuthManager();                                 // 0x00607a60
struct WinRef {
  IWin* p;
  WinRef(IWin* q) : p(q) { if (p) p->AddRef(); }
  ~WinRef() { if (p) p->Release(); }
  WinRef& operator=(IWin* q) {
    if (q != p) {
      if (q) q->AddRef();
      IWin* o = p;
      p = q;
      if (o) o->Release();
    }
    return *this;
  }
};
struct cGlobalA { char pad[0x3c]; struct { char pad[0x118]; int flag; }* sub; };
extern cGlobalA* g_015fd918;   // 0x015fd918
struct cSettingsTab_s0060_2940 {
  virtual void Init(const wchar_t* ui, void* winproc, uint32_t id);  // 0x005ff8e0 (cSettingsTab::Init)
  void* mWinProc;
  char mLayoutStorage[0x18];
  uint32_t mWinID;
  cSPUILayout_s0060_2940* L() { return (cSPUILayout_s0060_2940*)mLayoutStorage; }
};
struct cOnlineTab_s0060_2940 : cSettingsTab_s0060_2940 {
  void* mHandlerVptr;                  // +0x24
  char pad28[0x48 - 0x28];
  uint8_t b48, b49, b4a, b4b, b4c, b4d, b4e, b4f;
  virtual void Init(const wchar_t* ui, void* winproc, uint32_t id);   // 0x00603780
  void InitUIState(uint8_t b);                                         // 0x00602940
};
struct Handler13 {
  bool HandleMessage(uint32_t msg, int p3);
};
struct cTabVec {
  cSettingsTab_s0060_2940** mpBegin; cSettingsTab_s0060_2940** mpEnd; cSettingsTab_s0060_2940** mpCapacity;
  void DoInsertValue(cSettingsTab_s0060_2940** pos, cSettingsTab_s0060_2940* const& v);   // 0x00630b30
  void push_back(cSettingsTab_s0060_2940* const& v) {
    if (mpEnd < mpCapacity) {
      if (mpEnd) *mpEnd = v;
      ++mpEnd;
    } else {
      DoInsertValue(mpEnd, v);
    }
  }
};
struct cCreditsTab13 : cSettingsTab_s0060_2940 {
  char pad[0x9c - 0x24];
  int f9c;
  void FUN_00600c00();            // 0x00600c00
  void FUN_00600e80(int v);       // 0x00600e80
};
struct cSPUISettings_s0060_2940 {
  char pad0[0x14];
  cSPUILayout_s0060_2940* mpLayout;                                // +0x14
  char pad18[0x20 - 0x18];
  char tabs[0x20c - 0x20];                              // tab objects (0x20, 0xc0, 0x10c, ...)
  cTabVec mTabs;                                        // +0x20c
  void AddTab(cSettingsTab_s0060_2940* tab, const wchar_t* ui, uint32_t id);   // 0x006031c0
  bool Init(int a);                                     // 0x00603260
  bool OnModalWindowEnd(int a);                         // 0x006008c0 (on the tab at +0x1dc)
};
struct cLastTab { bool OnModalWindowEnd(int a); };   // 0x006008c0
struct cSPUISettings13 {
  virtual int AddRef();
  virtual int Release();
  cSPUISettings13();              // 0x00601790
  bool Init(int a);               // 0x00603260
  bool Shutdown();                // 0x00601e60
  bool Apply();                   // 0x00600ab0
  char pad[0x248 - 4];
};
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s00602940 end

// ---- items of slice s00603820 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s0060_3820(n) virtual void _pv##n();
namespace EA {
namespace ResourceMan {
struct Key_s0060_3820 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s0060_3820& a, const Key_s0060_3820& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s0060_3820 {
  uint32_t operator()(const Key_s0060_3820& k) const;
};
}
}
using EA::ResourceMan::Key_s0060_3820;
namespace eastl {
struct allocator_s0060_3820 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s0060_3820 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s0060_3820 mAllocator;

  basic_string_s0060_3820() { AllocateSelf(); }
  basic_string_s0060_3820(const basic_string_s0060_3820& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s0060_3820() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    wchar_t* e = GetEmptyStringW();
    mpBegin = (T*)e;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) { if (p) mAllocator.deallocate(p); }
  void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin)); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd = mpEnd - (pLast - pFirst);
    }
    return pFirst;
  }
  basic_string_s0060_3820& assign(const T* pBegin, const T* pEnd);
  basic_string_s0060_3820& operator=(const basic_string_s0060_3820& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s0060_3820<wchar_t> string16_s0060_3820;
}
namespace eastl {
bool operator==(const basic_string_s0060_3820<wchar_t>& a, const basic_string_s0060_3820<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s0060_3820 {
  uint32_t operator()(const string16_s0060_3820& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s0060_3820 {
  bool operator()(const string16_s0060_3820& a, const string16_s0060_3820& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_3820 {
  T1 first;
  T2 second;
  pair_s0060_3820(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s0060_3820(const pair_s0060_3820& p) : first(p.first), second(p.second) {}
  ~pair_s0060_3820() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s0060_3820 {
  Value mValue;
  hash_node_s0060_3820* mpNext;
};
}
namespace eastl {
struct prime_rehash_policy_s0060_3820 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s0060_3820>
class hashtable_s0060_3820 {
 public:
  typedef hash_node_s0060_3820<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;
  typedef hashtable_iterator<const Value, node_type> const_iterator;
  struct insert_return_type {
    iterator first;
    bool second;
    insert_return_type(const iterator& i, bool b) : first(i), second(b) {}
  };

  Hash mHash;
  node_type** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  prime_rehash_policy_s0060_3820 mRehashPolicy;
  allocator_s0060_3820 mAllocator;

  hashtable_s0060_3820() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mRehashPolicy.mnNextResize = 0;
  }

  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  __forceinline node_type* DoFindNode(node_type* pNode, const KeyT& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (k == pNode->mValue.first) return pNode;
    return 0;
  }
  void DoFreeNode(node_type* pNode) { pNode->~node_type(); mAllocator.deallocate(pNode); }

  iterator find(const KeyT& k);
  pair_s0060_3820<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s0060_3820() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s0060_3820<V, K, H, E>::iterator hashtable_s0060_3820<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s0060_3820<typename hashtable_s0060_3820<V, K, H, E>::iterator, typename hashtable_s0060_3820<V, K, H, E>::iterator>
hashtable_s0060_3820<V, K, H, E>::equal_range(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext)
      if (!(k == p1->mValue.first)) break;
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair_s0060_3820<iterator, iterator>(first, last);
  }
  return pair_s0060_3820<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s0060_3820<string16_s0060_3820, Key_s0060_3820> NameKeyPair_s0060_3820;
}
namespace eastl {
typedef pair_s0060_3820<Key_s0060_3820, string16_s0060_3820> KeyNamePair_s0060_3820;
}
namespace eastl {
typedef hashtable_s0060_3820<NameKeyPair_s0060_3820, string16_s0060_3820, hash_s0060_3820, equal_to_s0060_3820> NameKeyMap_s0060_3820;
}
namespace eastl {
typedef hashtable_s0060_3820<KeyNamePair_s0060_3820, Key_s0060_3820, EA::ResourceMan::KeyHash_s0060_3820> KeyNameMap_s0060_3820;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s0060_3820 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s0060_3820& a, const AssetGUID_s0060_3820& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s0060_3820 {
  uint32_t operator()(const AssetGUID_s0060_3820& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_3820<AssetGUID_s0060_3820, Key_s0060_3820> GuidKeyPair_s0060_3820;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s0060_3820<Key_s0060_3820, AssetGUID_s0060_3820> KeyGuidPair_s0060_3820;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_3820<GuidKeyPair_s0060_3820, AssetGUID_s0060_3820, AssetGUIDHash_s0060_3820> GuidKeyMap_s0060_3820;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s0060_3820<KeyGuidPair_s0060_3820, Key_s0060_3820, EA::ResourceMan::KeyHash_s0060_3820> KeyGuidMap_s0060_3820;
}
}
struct ConfigManagerStub14 {
  PV_s0060_3820(0) PV_s0060_3820(1) PV_s0060_3820(2) PV_s0060_3820(3) PV_s0060_3820(4) PV_s0060_3820(5) PV_s0060_3820(6) PV_s0060_3820(7) PV_s0060_3820(8) PV_s0060_3820(9) PV_s0060_3820(10) PV_s0060_3820(11) PV_s0060_3820(12) PV_s0060_3820(13) PV_s0060_3820(14)
  virtual void vt3c();                     // +0x3c
};
ConfigManagerStub14* ConfigManager_s0060_3820();      // 0x0067dd30
struct Sub10c { void Save(); };            // 0x00603de0
struct cSPUISettings14 {
  char pad0[0x10c];
  Sub10c mSub;                             // +0x10c
  void SaveOnlineSettings();               // 0x005ff850
  void SaveAllSettings();                  // 0x00604860
};
struct SubFC { char pad[4]; void A(); };    // 0x00603fe0
struct Sub1A0 { char pad[4]; void B(); };   // 0x00600180
struct SettingsForHandler {
  char pad0[0x14];
  void* mpLayout;                          // +0x14
  char pad18[0x10c - 0x18];
  SubFC mFC;                               // +0x10c
  char pad110[0x1b0 - 0x110];
  Sub1A0 m1A0;                             // +0x1b0 (settings-relative)
  bool Shutdown();                         // 0x00601e60
};
void EndModal(void* w, int a, int b);      // 0x00809c50
struct LayoutModal { void* FindWindowByID(uint32_t id, int rec); };
struct Handler14 {
  char pad0[4];
  void* mpLayout;                          // +0x4
  bool HandleMessage(uint32_t msg, void* unused);
};
// ---- items of slice s00603820 end

// ---- items of slice s00604890 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};
namespace EA {
namespace UTFWin {
class IWinProc_s0060_4890 {
 public:
  virtual ~IWinProc_s0060_4890() {}
  virtual void p0();
  virtual void p1();
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_4890 {
 public:
  virtual int AddRef();                  // +0x00 0
  virtual int Release();                 // +0x04 1
  PV(2)                                  // +0x08 2
  virtual void* Cast(uint32_t);          // +0x0c 3
  virtual IWindow_s0060_4890* GetParent10();        // +0x10 4
  PV(5) PV(6)                            // +0x14 5, +0x18 6
  virtual uint32_t GetControlID();       // +0x1c 7
  PV(8)                                  // +0x20 8
  virtual void SetState24(int v);        // +0x24 9
  virtual int GetFlag28();               // +0x28 10
  PV(11) PV(12) PV(13)                   // +0x2c 11, +0x30 12, +0x34 13
  virtual void* GetRect();               // +0x38 14
  PV(15) PV(16)                          // +0x3c 15, +0x40 16
  PV(17)                                 // +0x44 17
  PV(18) PV(19) PV(20) PV(21)            // +0x48..0x54
  PV(22) PV(23) PV(24) PV(25)            // +0x58..0x64
  PV(26)                                 // +0x68
  virtual void SetArea(float* rect);     // +0x6c 27
  PV(28) PV(29) PV(30)                   // +0x70..0x78
  virtual void SetFlag(int v, uint32_t a);  // +0x7c 31
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddChild(IWindow_s0060_4890* w);     // +0xd8 54
  virtual void RemoveChild(IWindow_s0060_4890* w);  // +0xdc 55
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s0060_4890* p);  // +0x104 65
  PV(66) PV(67)
};
}
}
using EA::UTFWin::IWinProc_s0060_4890;
using EA::UTFWin::IWindow_s0060_4890;
struct cSPUILayout_s0060_4890 {
  cSPUILayout_s0060_4890();  // 0x810000
  bool Init(const ResourceKey* pKey, int, uint32_t);   // 0x8120d0
  void GetObjects();                                   // 0x8100c0
  IWindow_s0060_4890* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x8105b0
  void Shutdown(int);                                  // 0x811ad0
  ~cSPUILayout_s0060_4890();                                      // 0x811fe0
  char pad[0x18];
};
// ---- items of slice s00604890 end

// @ 0x005ff230
void cTimedObject::RestartTimer()
{
  mStopwatch.mnStartTime = 0;
  mStopwatch.mnTotalElapsedTime = 0;
  if (mStopwatch.mnUnits == EA::Stopwatch_s005f_f230::kUnitsCycles)
    mStopwatch.mnStartTime = EA::Stopwatch_s005f_f230::GetCPUCycle();
  else
    mStopwatch.mnStartTime = EA::Stopwatch_s005f_f230::GetStopwatchCycle();
  mStopwatch.mnTotalElapsedTime = 0;
  mStopwatch.mbRunning = false;
}







// @ 0x005ff2a0
void SP::cAudioTab::Shutdown()
{
  if (mInitialSoundQuality) {
    ReleaseObject((void*)mInitialSoundQuality, 0);
    mInitialSoundQuality = 0;
  }
  mLayout.Shutdown(true);
}







// @ 0x005ff2d0
void SP::cAudioTab_s005f_f230::RestoreSettingsFromEntry()
{
  if (SP::AudioSystem()) {
    Audio::cAudioPreferences_s005f_f230* prefs = SP::AudioSystem()->GetPreferences();
    if (prefs) {
      prefs->Mute(mbInitialMuteAll);
      prefs->SetSoundQuality(mInitialSoundQuality);
      prefs->SetVolume(0xaded51d5, mInitialMasterVolume);
      prefs->SetVolume(0x3af239c4, mInitialSFXVolume);
      prefs->SetVolume(0x8bdd39ec, mInitialMusicVolume);
      prefs->SetVolume(0x09a0474a, mInitialVOXVolume);
      prefs->SetSpeakerMode(mInitialSpeakerMode);
    }
  }
}







// @ 0x005ff370
bool SP::cGameTab_s005f_f230::DoMessageTab(IWindow_s005f_f230* window, const Message_s005f_f230* message)
{
  if (message->mType == 0x287259f6) {
    switch (message->mpSource->GetControlID()) {
      case 0x462cb78: SP::ConfigManager()->SetValue(0x473b8cc, 3); return true;
      case 0x462cb58: SP::ConfigManager()->SetValue(0x473b8cc, 2); return true;
      case 0x462c820: SP::ConfigManager()->SetValue(0x473b8cc, 1); return true;
      case 0x462cba0: SP::ConfigManager()->SetValue(0x473b8cb, 1); return true;
      case 0x462cbb8: SP::ConfigManager()->SetValue(0x473b8cb, 3); return true;
      case 0x462cbb0: SP::ConfigManager()->SetValue(0x473b8cb, 2); return true;
    }
  }
  return false;
}







// @ 0x005ff460
void SP::cGameTab::RestoreSettingsFromEntry()
{
  ConfigManager()->SetValue(0x4ea96cb, mInitialTutorialsSettings);
  ConfigManager()->SetValue(0x5b5bb5e, mInitialShowHints);
  ConfigManager()->SetValue(0x636ec26, mInitialMovieRes);
  ConfigManager()->SetValue(0x473b8cb, mInitialGameDifficulty);
  ConfigManager()->SetValue(0x473b8cc, mInitialPhotoRes);
}







// @ 0x005ff4e0
void SP::cOnlineTab_s005f_f230::Shutdown()
{
  SP::MessageServer()->RemoveHandler(this, 0x44db12e, -9999);
  SP::MessageServer()->RemoveHandler(this, 0x5b96086, -9999);
  SP::MessageServer()->RemoveHandler(this, 0x5c5594a, -9999);
  mLayout.Shutdown(true);
}







// @ 0x005ff560
void SP::cOnlineTab_s005f_f230::RestoreSettingsFromEntry()
{
  SP::ConfigManager()->SetValue(0x5664a8b, mInitial[0]);
  SP::ConfigManager()->SetValue(0x5de7b4a, mInitial[1]);
  SP::ConfigManager()->SetValue(0x626f940, mInitial[2]);
  SP::ConfigManager()->SetValue(0x626f958, mInitial[3]);
  SP::ConfigManager()->SetValue(0x626f9c0, mInitial[4]);
  SP::ConfigManager()->SetValue(0x685a785, mInitial[5]);
  SP::ConfigManager()->SetValue(0x685a821, mInitial[6]);
  SP::ConfigManager()->SetValue(0x685a63c, mInitial[7]);
}







// @ 0x005ff630
void SP::cGameTab::Shutdown()
{
  mLayout.Shutdown(true);
}







// @ 0x005ff640
void SP::cOptionTab::RestoreSettingsFromEntry()
{
  SP::ConfigManager()->SetValue(mPropertyID, mInitialValue);
  SP::MessageServer()->PostMSG(0x679c40d, 0, 0);
}







// @ 0x005ff700
void SP::cSPUISettings_s005f_f230::BeginClose()
{
  IWindow_s005f_f230* window = mpLayout->FindWindowByID(0x43c8b98, true);
  if (window) {
    window->SetFlag(1, false);
    float closeTime = 0.0f;
    for (IWindow_s005f_f230* child = window->GetNextChild(0); child; child = window->GetNextChild(child)) {
      EA::UTFWin::IFloatValue* value = (EA::UTFWin::IFloatValue*)child->Cast(0x8f2b630b);
      if (value) {
        closeTime = value->GetValue();
        break;
      }
    }
    SPUIHelpers::EndModal(window, 0, 0);
    IWindow_s005f_f230* w = mpLayout->FindWindowByID(0x5c05d20, true);
    if (w) w->SetFlag(0x10, false);
    mLimitStopwatch.SetTimeLimit(FloatToInt(closeTime * 1000.0f), true);
  }
  if (mpModal) {
    mpModal->Close(0);
    mpModal = 0;
  }
  cSPUILayoutManager_s005f_f230* manager = SPUILayoutManager();
  manager->SetWorldVisibility(0x5b598f7, false);
  manager->SetWorldVisibility(0x5b598f6, false);
  manager->SetAllWorldsVisibility(true);
  SP::MessageServer()->PostMSG(0x4519b5a, 0, 0);
}







// @ 0x005ff850
void SP::cSPUISettings_s005f_f230::SaveOnlineSettings()
{
  SP::IOnlinePrefs* prefs = SP::OnlinePrefs();
  IWindow_s005f_f230* window = mpLayout->FindWindowByID(0x43b6428, true);
  if (window) {
    bool checked = (int)(window->GetState() & 4) > 0;
    if (checked != prefs->GetLoginEnabled()) {
      prefs->SetLoginEnabled(checked);
      prefs->Save();
    }
  }
  if (mbInitialYouTubeLogin != SP::ConfigManager()->GetValue(0x5de7b4a))
    SP::MessageServer()->PostMSG(0x5de7b4a, 0, 0);
}







// @ 0x005ff8e0
void SP::cSettingsTab_s005f_f230::Init(uint32_t layoutID, IWinProc_s005f_f230* winProc, uint32_t tabID)
{
  mTabID = tabID;
  mWinProc = winProc;
  mLayout.Init(layoutID, 0, 0x5b598fa);
  mLayout.GetObjects();
  mLayout.FindWindowByID(mTabID, true)->AddWinProc(mWinProc);
}







// @ 0x005ff940
void SP::cGraphicsTab_s005f_f230::Shutdown()
{
  if (mpWindow) mpWindow->RemoveWinProc(mWinProc);
  if (mpA) {
    DestroyWindowTree(mpA);
    mpA = 0;
    mpWindow = 0;
    mpC = 0;
  }
  // The original re-reads the vector's begin pointer for every element; a volatile
  // read reproduces that.
  for (uint32_t i = 0; i < size(); i++)
    (*(SP::cProfileEntry* volatile*)&mpBegin)[i].Shutdown();
  mLayout.Shutdown(true);
}







// @ 0x005ffa30
void SP::cAudioTab_s005f_f230::Init(uint32_t layoutID, IWinProc_s005f_f230* winProc, uint32_t tabID)
{
  SP::cSettingsTab_s005f_f230::Init(layoutID, winProc, tabID);
  SP::IAudioSystem* audio = SP::AudioSystem();
  if (!audio) return;
  Audio::cAudioPreferences_s005f_f230* prefs = audio->GetPreferences();
  if (!prefs) return;

  mbInitialMuteAll = prefs->IsMuted();
  IWindow_s005f_f230* w = mLayout.FindWindowByID(0x899eb157, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) button->SetButtonStateFlag(4, mbInitialMuteAll);
  }

  mInitialSoundQuality = prefs->GetSoundQuality();
  switch (mInitialSoundQuality) {
    case 1: CheckButton(0x48df982); break;
    case 2: CheckButton(0x48df96c); break;
    case 3: CheckButton(0x48df95d); break;
  }

  mInitialSpeakerMode = prefs->GetSpeakerMode();
  uint32_t mode = SP::App()->GetModeID();
  bool enabled;
  if (mode == 0x2ccd1d2 || mode == 0x42b4372)
    enabled = true;
  else
    enabled = false;

  w = mLayout.FindWindowByID(0xde52c409, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) {
      button->ToWindow()->SetFlag(2, enabled);
      button->SetButtonStateFlag(4, mInitialSpeakerMode == 2);
    }
  }
  w = mLayout.FindWindowByID(0xf24b36e0, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) {
      if (SP::gAppProperties->HasProperty(0x63ab656)) {
        button->ToWindow()->SetFlag(2, enabled);
        button->SetButtonStateFlag(4, mInitialSpeakerMode == 4);
      } else {
        button->ToWindow()->SetFlag(1, false);
        button->ToWindow()->SetFlag(2, false);
      }
    }
  }
  w = mLayout.FindWindowByID(0xaefd81a1, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) {
      if (SP::gAppProperties->HasProperty(0x63ab656)) {
        button->ToWindow()->SetFlag(2, enabled);
        button->SetButtonStateFlag(4, mInitialSpeakerMode == 5);
      } else {
        button->ToWindow()->SetFlag(1, false);
        button->ToWindow()->SetFlag(2, false);
      }
    }
  }

  float volume = 1.0f;
  w = mLayout.FindWindowByID(0xaded51d5, true);
  if (w) {
    w->SetFlag(2, true);
    ISlider* slider = (ISlider*)w->Cast(0xf00a8a0);
    if (slider && prefs->GetVolume(0xaded51d5, &volume)) {
      slider->SetValue((int)((float)slider->GetMaxValue() * volume), false);
      mInitialMasterVolume = volume;
    }
  }
  w = mLayout.FindWindowByID(0x3af239c4, true);
  if (w) {
    w->SetFlag(2, true);
    ISlider* slider = (ISlider*)w->Cast(0xf00a8a0);
    if (slider && prefs->GetVolume(0x3af239c4, &volume)) {
      slider->SetValue((int)((float)slider->GetMaxValue() * volume), false);
      mInitialSFXVolume = volume;
    }
  }
  w = mLayout.FindWindowByID(0x8bdd39ec, true);
  if (w) {
    w->SetFlag(2, true);
    ISlider* slider = (ISlider*)w->Cast(0xf00a8a0);
    if (slider && prefs->GetVolume(0x8bdd39ec, &volume)) {
      slider->SetValue((int)((float)slider->GetMaxValue() * volume), false);
      mInitialMusicVolume = volume;
    }
  }
  w = mLayout.FindWindowByID(0x09a0474a, true);
  if (w) {
    w->SetFlag(2, true);
    ISlider* slider = (ISlider*)w->Cast(0xf00a8a0);
    if (slider && prefs->GetVolume(0x09a0474a, &volume)) {
      slider->SetValue((int)((float)slider->GetMaxValue() * volume), false);
      mInitialVOXVolume = volume;
    }
  }
}







// @ 0x005ffee0
bool SP::cAudioTab_s005f_f230::DoMessageTab(IWindow_s005f_f230* window, const Message_s005f_f230* message)
{
  bool handled = false;
  SP::IAudioSystem* audio = SP::AudioSystem();
  Audio::cAudioPreferences_s005f_f230* prefs = 0;
  if (audio) {
    prefs = audio->GetPreferences();
    if (!prefs) return false;
  }
  switch (message->mType) {
    case 7:
      if (window) {
        ISlider* slider = (ISlider*)window->Cast(0xf00a8a0);
        if (slider && slider->ToWindow()->IsMessageFrom(message) && mhSound) {
          ReleaseObject((void*)mhSound, 0);
          mhSound = 0;
        }
      }
      break;
    case 6:
      if (window) {
        ISlider* slider = (ISlider*)window->Cast(0xf00a8a0);
        if (slider && slider->ToWindow()->IsMessageFrom(message)) {
          uint32_t id = window->GetControlID();
          uint32_t soundID;
          if (id == 0xaded51d5 || id == 0x8bdd39ec)
            soundID = 0x277ca83b;
          else if (id == 0x3af239c4)
            soundID = 0x1e710a73;
          else if (id == 0x09a0474a)
            soundID = 0x6ef5edb9;
          else
            break;
          mhSound = CreateSoundHandle();
          PlayUISound(soundID, mhSound);
        }
      }
      break;
    case 0x287259f6:
      switch (message->mpSource->GetControlID()) {
        case 0x48df982: prefs->SetSoundQuality(1); handled = true; break;
        case 0x48df96c: prefs->SetSoundQuality(2); handled = true; break;
        case 0x48df95d: prefs->SetSoundQuality(3); handled = true; break;
        case 0x899eb157:
          prefs->Mute((int)(message->mpSource->GetState() & 4) > 0);
          handled = true;
          break;
        case 0xf24b36e0: prefs->SetSpeakerMode(4); handled = true; break;
        case 0xde52c409: prefs->SetSpeakerMode(2); handled = true; break;
        case 0xaefd81a1: prefs->SetSpeakerMode(5); handled = true; break;
      }
      break;
    case 0xef00a884: {
      uint32_t id = message->mpSource->GetControlID();
      ISlider* slider = message->mpSource ? (ISlider*)message->mpSource->Cast(0xf00a8a0) : 0;
      float value = (float)message->mValue;
      value = value / (float)slider->GetMaxValue();
      prefs->SetVolume(id, value);
      handled = true;
      break;
    }
  }
  return handled;
}







// @ 0x00600180
void SP::cGraphicsTab_s005f_f230::UpdateFullscreenControls()
{
  bool fullscreen = SP::Canvas()->IsFullscreen();
  IWindow_s005f_f230* w = mLayout.FindWindowByID(0x5b591d8, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) {
      w->SetFlag(2, !fullscreen);
      w->SetFlag(0x10, fullscreen);
      button->SetButtonStateFlag(4, SP::ConfigManager()->GetValue(0x636ec26) != 0);
    }
  }
  w = mLayout.FindWindowByID(0x669ea05, true);
  if (w) {
    EA::UTFWin::IColorable* c = (EA::UTFWin::IColorable*)w->Cast(0xf15f4bd);
    if (c) c->SetColor(fullscreen ? 0x99999999 : 0xd6ffffff);
  }
}






// @ 0x00600260
void OnlineTabStub::DoMessageTab()
{
  ConfigManager_s0060_0260()->vt2c(0x5de7b4a, mbFlag);
  mbFlag = ConfigManager_s0060_0260()->vt30(0x5de7b4a);
  WinWithIDStub* w = (WinWithIDStub*)mLayout.FindWindowByID(0x5b1cc48, 1);
  if (w) {
    WinWithIDStub* p = (WinWithIDStub*)w->vt0c(0x8ed27e7a);
    if (p) p->vt28(4, mbFlag == 1);
  }
}






// @ 0x006002d0
void FUN_006002d0()
{}






// @ 0x006008c0
void FUN_006008c0()
{}






// @ 0x00600ab0
void FUN_00600ab0()
{}






// @ 0x00600c00
void FUN_00600c00()
{}






// @ 0x00600da0
void FUN_00600da0()
{}






// @ 0x00600df0
void FUN_00600df0()
{}





// @ 0x00600e80
void FUN_00600e80()
{}





// @ 0x006012e0
void FUN_006012e0()
{}





// @ 0x006016c0
void FUN_006016c0()
{}





// @ 0x00601730
void FUN_00601730()
{}





// @ 0x00601790
void FUN_00601790()
{}





// @ 0x00601930
void FUN_00601930()
{}





// @ 0x00601a70
void FUN_00601a70()
{}





// @ 0x00601c50
SettingsRecord& SettingsRecord::operator=(const SettingsRecord& o)
{
  m0 = o.m0;
  f4 = o.f4;
  f8 = o.f8;
  mName = o.mName;
  f1c = o.f1c; f20 = o.f20; f24 = o.f24; f28 = o.f28;
  f2c = o.f2c; f30 = o.f30; f34 = o.f34; f38 = o.f38;
  m3c = o.m3c;
  f50 = o.f50;
  f54 = o.f54;
  return *this;
}





// @ 0x00601e60
bool SPUISettingsStub::Shutdown()
{
  while ((mTabEnd - mTabBegin) != 0)
    RemoveTab(mTabBegin[(mTabEnd - mTabBegin) - 1]);
  if (mpLayout)
    ((LayoutShutdown*)mpLayout)->Shutdown(1);
  void* handler = (char*)this + 0x10;
  SP::Thumbnail::GetMessageServer()->vt2c(handler, 0x238de9c, 0xffffd8f1);
  SP::Thumbnail::GetMessageServer()->vt2c(handler, 0x62752d3, 0xffffd8f1);
  return true;
}





// @ 0x00601f00
void FUN_00601f00()
{}




// @ 0x00601fd0
void SP::cGameTab_s0060_1fd0::Init(uint32_t layoutID, IWinProc_s0060_1fd0* winProc, uint32_t tabID)
{
  mTabID = tabID;
  mWinProc = winProc;
  mLayout.Init(layoutID, 0, 0x5b598fa);
  mLayout.GetObjects();
  mLayout.FindWindowByID(mTabID, true)->AddWinProc(mWinProc);

  bool tutorials = SP::ConfigManager()->GetValue(0x4ea96cb) != 0;
  mInitialTutorialsSettings = tutorials;
  mInitialShowHints = SP::ConfigManager()->GetValue(0x5b5bb5e) != 0;
  mInitialMovieRes = SP::ConfigManager()->GetValue(0x636ec26) != 0;

  if (IButton_s0060_1fd0* b = ButtonOf(mLayout.FindWindowByID(0x4ea67b3, true)))
    b->SetButtonStateFlag(4, tutorials);
  if (IButton_s0060_1fd0* b = ButtonOf(mLayout.FindWindowByID(0x5b591a8, true)))
    b->SetButtonStateFlag(4, mInitialShowHints);
  IWindow_s0060_1fd0* movie = mLayout.FindWindowByID(0x5b591d8, true);
  if (movie) {
    if (IButton_s0060_1fd0* b = ButtonOf(movie)) {
      b->SetButtonStateFlag(4, mInitialMovieRes);
      if (!SP::Canvas()->IsFullscreen()) {
        movie->SetFlag(2, false);
        movie->SetFlag(0x10, true);
      }
      IWindow_s0060_1fd0* label = mLayout.FindWindowByID(0x669ea05, true);
      if (label) {
        IColorable_s0060_1fd0* c = (IColorable_s0060_1fd0*)label->Cast(0xf15f4bd);
        if (c) c->SetColor(SP::Canvas()->IsFullscreen() ? 0xd6ffffff : 0x99999999);
      }
    }
  }

  if (SP::gAppProperties_s0060_1fd0->mpData->mField118 != 0) {
    IWindow_s0060_1fd0* w = mLayout.FindWindowByID(0x5b591d8, true);
    if (w) w->SetFlag(2, false);
    w = mLayout.FindWindowByID(0x4ea67b3, true);
    if (w) w->SetFlag(2, false);
    w = mLayout.FindWindowByID(0x5b75578, true);
    if (w) w->SetFlag(1, false);
    w = mLayout.FindWindowByID(0x5b757b0, true);
    if (w) {
      const EA::UTFWin::Rect* area = w->GetArea();
      w->SetLocation(area->x1, area->y1 - 190.0f);
    }
    w = mLayout.FindWindowByID(0x5b75950, true);
    if (w) w->SetFlag(1, false);
    w = mLayout.FindWindowByID(0x5b75b28, true);
    if (w) w->SetFlag(1, true);
  }

  uint8_t photoRes = (uint8_t)SP::ConfigManager()->GetValue(0x473b8cc);
  mInitialPhotoRes = photoRes;
  mLayout.FindWindowByID(0x462c820, true);
  ButtonOf(mLayout.FindWindowByID(0x462c820, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cb58, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cb78, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cba0, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cbb0, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cbb8, true))->SetButtonStateFlag(4, false);

  uint32_t photoID;
  switch (photoRes) {
    case 1: photoID = 0x462c820; break;
    case 2: photoID = 0x462cb58; break;
    case 3: photoID = 0x462cb78; break;
    default:
      photoID = 0x462c820;
      SP::ConfigManager()->SetValue(0x473b8cc, 1);
      break;
  }
  if (IButton_s0060_1fd0* b = ButtonOf(mLayout.FindWindowByID(photoID, true)))
    b->SetButtonStateFlag(4, true);

  uint8_t difficulty = (uint8_t)SP::ConfigManager()->GetValue(0x473b8cb);
  mInitialGameDifficulty = difficulty;
  uint32_t diffID;
  switch (difficulty) {
    case 1: diffID = 0x462cba0; break;
    case 2: diffID = 0x462cbb0; break;
    case 3: diffID = 0x462cbb8; break;
    default:
      diffID = 0x462cba0;
      SP::ConfigManager()->SetValue(0x473b8cb, 1);
      break;
  }
  if (IButton_s0060_1fd0* b = ButtonOf(mLayout.FindWindowByID(diffID, true)))
    b->SetButtonStateFlag(4, true);

  SP::cString_s0060_1fd0 text;
  if (SP::gAppProperties_s0060_1fd0->GetDescription(0x61b67b6)) {
    text.Load(0xad7b2086, 0x6318d68, 0);
  } else {
    WString path;
    path.RangeInitialize(SP::GetSaveArea(0x11ac197)->GetPath());
    for (int i = 0; i < 2; ++i) {
      uint32_t length = (uint32_t)(path.mpEnd - path.mpBegin);
      uint32_t pos = RFind(path, L"\\");
      if (pos == (uint32_t)-1) pos = RFind(path, L"/");
      if (pos != (uint32_t)-1) {
        uint32_t count = length - pos;
        if (i) {
          --count;
          ++pos;
        }
        path.erase(pos, count);
      }
    }
    SP::FUN_0067de40()->GetTarget()->SetPath(path.mpBegin, 0);
    text.Load(0xad7b2086, 0x631825f, 0);
    if (((((uint32_t)path.mpCapacity) - ((uint32_t)path.mpBegin)) & ~1u) > 2 && path.mpBegin)
      operator_delete_array_00f47380(path.mpBegin);
  }

  IWindow_s0060_1fd0* w = mLayout.FindWindowByID(0x6317e08, true);
  if (w) {
    IColorable_s0060_1fd0* c = (IColorable_s0060_1fd0*)w->Cast(0xf15f4bd);
    if (c) c->ToWindow()->SetCaption(text.GetText());
  }
}




// @ 0x006026f0
bool cTerrainUILoadScriptFromGrid()
{
  return false;
}



// @ 0x00602940
void cOnlineTab_s0060_2940::InitUIState(uint8_t b)
{
  IAuth* auth = AuthManager();
  SP::cString_s0060_2940 sTitle, sMsg, sInfo;
  uint32_t color;
  if (auth->IsLoggedIn()) {
    if (!auth->IsGuest() && !b) {
      IUserName* un = FUN_0067de40_s0060_2940()->GetName();
      WStr tmp;
      un->SetName(ConvertToString16(&tmp, auth->GetUserID())->b, 0);
      sTitle.Load(0xad7b2086, 0x56528a8, 0);
      sMsg.Load(0xad7b2086, 0x565289d, 0);
      sInfo.Load(0xad7b2086, 0x56528a9, 0);
      color = 0xff00ff00;
    } else {
      sTitle.Load(0xad7b2086, 0x56528a6, 0);
      sMsg.Load(0xad7b2086, 0x565289e, 0);
      sInfo.Load(0xad7b2086, 0x56528a7, 0);
      color = 0xffffff00;
    }
  } else {
    sTitle.Load(0xad7b2086, 0x56528a4, 0);
    sMsg.Load(0xad7b2086, 0x565289f, 0);
    sInfo.Load(0xad7b2086, 0x56528a5, 0);
    color = 0xffff0000;
  }

  cSPUILayout_s0060_2940* lay = L();
  IWin* w = lay->FindWindowByID(0x46c1500, 1);
  if (w) {
    IWin* c = w->QueryChild(0xf15f4bd);
    if (c) {
      c->GetSub()->SetCaption(sTitle.GetText());
      ((IColorWin*)c)->SetColor(color);
    }
  }
  w = lay->FindWindowByID(0x5669738, 1);
  if (w) w->SetCaption(sMsg.GetText());
  w = lay->FindWindowByID(0x43b6178, 1);
  if (w) {
    w->SetCaption(sInfo.GetText());
    SPUIHelpers::AutoSizeWindowForText(w, 1, 0);
  }
  w = lay->FindWindowByID(0x43b6428, 1);
  if (w) {
    IWin* c = w->QueryChild(0x8ed27e7a);
    if (c) c->SetState(4, (uint8_t)auth->GetStatus());
  }

  if (g_015fd918->sub->flag == 0) {
    // desktop-only toggles
    w = lay->FindWindowByID(0x5b1cc48, 1);
    if (w) w->SetFlag(2, 0);
    w = lay->FindWindowByID(0x5b76718, 1);
    if (w) w->SetFlag(1, 0);
    b49 = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x5de7b4a);
  } else {
    uint8_t v;
    v = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x5de7b4a);
    bool on = (v == 1);
    b49 = v;
    w = lay->FindWindowByID(0x5b1cc48, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    v = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x626f940);
    on = (v == 1);
    b4a = v;
    w = lay->FindWindowByID(0x626f940, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    v = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x626f9c0);
    on = (v == 1);
    b4c = v;
    w = lay->FindWindowByID(0x626f9c0, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    b4b = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x626f958);
    IWin* o = lay->FindWindowByID(mWinID, 1)->FindByID(0x626f958, 1);
    WinRef ref(o ? o->QueryChild(0xaf062e1d) : 0);
    if (ref.p) {
      ref.p->SetValue(b4b, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4b);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x626f959, 1)->SetCaption(s.b);
    }

    v = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x685a785);
    on = (v == 1);
    b4d = v;
    w = lay->FindWindowByID(0x685a785, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    b4e = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x685a821);
    o = lay->FindWindowByID(mWinID, 1)->FindByID(0x685a821, 1);
    ref = o ? o->QueryChild(0xaf062e1d) : 0;
    if (ref.p) {
      ref.p->SetValue(b4e, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4e);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x685a822, 1)->SetCaption(s.b);
    }

    b4f = (uint8_t)ConfigManager_s0060_2940()->GetValue(0x685a63c);
    o = lay->FindWindowByID(mWinID, 1)->FindByID(0x685a63c, 1);
    ref = o ? o->QueryChild(0xaf062e1d) : 0;
    if (ref.p) {
      ref.p->SetValue(b4f, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4f << 8);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x685a63d, 1)->SetCaption(s.b);
    }
  }

  b48 = ConfigManager_s0060_2940()->GetValue(0x5664a8b) != 0;
  w = lay->FindWindowByID(0x56648f8, 1);
  if (w) {
    IWin* c = w->QueryChild(0x8ed27e7a);
    if (c) c->SetState(4, b48 != 0);
  }
  SP::cString_s0060_2940 sLabel;
  sLabel.Load(0xad7b2086, 0x5664d28, (const wchar_t*)0x13ec468);
  lay->FindWindowByID(0x56648e8, 1)->SetCaption(sLabel.GetText());
}



// @ 0x00603170
bool Handler13::HandleMessage(uint32_t msg, int p3)
{
  if (msg != 0x44db12e && msg != 0x5b96086 && msg != 0x5c5594a) return false;
  uint8_t b = 0;
  if (msg == 0x44db12e && p3 == 0) b = 1;
  ((cOnlineTab_s0060_2940*)((char*)this - 0x24))->InitUIState(b);
  return true;
}



// @ 0x006031c0
void cSPUISettings_s0060_2940::AddTab(cSettingsTab_s0060_2940* tab, const wchar_t* ui, uint32_t id)
{
  tab->Init(ui, this, id);
  IWin* host = mpLayout->FindWindowByID(0x46967c0, 1);
  cSPUILayout_s0060_2940* tl = tab->L();
  host->AddChildWin(tl->FindWindowByID(tab->mWinID, 1));
  SPUIHelpers::SetWindowAreaToParent(tl->FindWindowByID(tab->mWinID, 1));
  mTabs.push_back(tab);
}



// @ 0x00603260
bool cSPUISettings_s0060_2940::Init(int a)
{
  bool rotated = false;
  cSPUILayout_s0060_2940* p = new ((const char*)0x13f6b3c, 0, 0, 0, 0) cSPUILayout_s0060_2940();
  if (p != mpLayout) {
    if (p) p->AddRef();
    cSPUILayout_s0060_2940* old = mpLayout;
    mpLayout = p;
    if (old) old->Release();
  }
  if (!mpLayout->Init(L"GameSettings", 0x40464100, 1, 0x5b598f7)) {
    cSPUILayout_s0060_2940* l = mpLayout;
    if (l) {
      mpLayout = 0;
      l->Release();
    }
    return false;
  }

  IWin* win = mpLayout->FindWindowByID(0x43c8b98, 1);
  IWin* main = ((cSPUILayoutManager_s0060_2940*)GetLayoutManager(0x5b598f7))->GetWorldMainWindow();
  float rot[4];
  rot[0] = 0.0f; rot[1] = gF1485720; rot[2] = 0.0f; rot[3] = gF151d728;
  const float* cur = FUN_00805260(main);
  if (cur[0] != 0.0f || cur[1] != 0.0f || cur[2] != gF1485720 || cur[3] != 0.0f) {
    SPUIHelpers::SetRotation(win, rot);
    rotated = true;
  }

  cCreditsTab13* tab0 = (cCreditsTab13*)((char*)this + 0x20);
  AddTab(tab0, (const wchar_t*)0x151d960, 0x463f008);
  AddTab((cSettingsTab_s0060_2940*)((char*)this + 0xc0), (const wchar_t*)0x151d96c, 0x437a960);
  AddTab((cSettingsTab_s0060_2940*)((char*)this + 0x10c),
         g_015fd918->sub->flag ? (const wchar_t*)0x151d984 : (const wchar_t*)0x151d978, 0x437a968);
  AddTab((cSettingsTab_s0060_2940*)((char*)this + 0x160), (const wchar_t*)0x151d990, 0x437a978);
  AddTab((cSettingsTab_s0060_2940*)((char*)this + 0x1b0), (const wchar_t*)0x151d99c, 0x46c1800);
  cLastTab* last = (cLastTab*)((char*)this + 0x1dc);
  AddTab((cSettingsTab_s0060_2940*)last, (const wchar_t*)0x151d9a8, 0x679e383);
  if (!last->OnModalWindowEnd(a)) {
    IWin* w = mpLayout->FindWindowByID(0x473ff98, 1);
    if (w) {
      w->SetFlag(2, 0);
      w->SetFlag(0x10, 1);
    }
  }
  tab0->FUN_00600c00();
  tab0->FUN_00600e80(tab0->f9c);
  if (rotated) SPUIHelpers::ResetScrollFrameColor(win);

  IWin* w = mpLayout->FindWindowByID(0x473ff78, 1);
  if (w) {
    w->QueryChild(0x8ed27e7a)->SetState(4, 1);
    IWin* x = mpLayout->FindWindowByID(w->GetID(1), 1);
    if (x) {
      x->SetFlag(2, 1);
      x->SetFlag(1, 1);
    }
  }
  if (g_015fd918->sub->flag) {
    w = mpLayout->FindWindowByID(0x473ff88, 1);
    if (w) {
      SP::cString_s0060_2940 s;
      s.Load(0xad7b2086, 0x473ef2e, L"*capture button*");
      w->SetCaption(s.GetText());
      win->SetFlag(1, 1);
    }
  }
  IMsgListener* h = (IMsgListener*)((char*)this + 0x10);
  MessageServer_s0060_2940()->AddListener(h, 0x238de9c);
  MessageServer_s0060_2940()->AddListener(h, 0x62752d3);
  return true;
}



// @ 0x006035d0
bool ShowSettingsWindow(int param)
{
  cSPUISettings13* p = new ((const char*)0x13f6b3c, 0, 0, 0, 0) cSPUISettings13();
  if (p) p->AddRef();
  if (p->Init(param)) {
    if (p->Apply()) {
      if (p) p->Release();
      return true;
    }
    p->Shutdown();
  }
  if (p) p->Release();
  return false;
}



// @ 0x00603780
void cOnlineTab_s0060_2940::Init(const wchar_t* ui, void* winproc, uint32_t id)
{
  mWinID = id;
  mWinProc = winproc;
  cSPUILayout_s0060_2940* lay = L();
  lay->InitTab(ui, 0, 0x5b598fa);
  lay->GetObjects();
  lay->FindWindowByID(mWinID, 1)->SetWinProc(mWinProc);
  InitUIState(0);
  IMsgListener* h = (IMsgListener*)((char*)this + 0x24);
  MessageServer_s0060_2940()->AddListener(h, 0x44db12e);
  MessageServer_s0060_2940()->AddListener(h, 0x5b96086);
  MessageServer_s0060_2940()->AddListener(h, 0x5c5594a);
}


// @ 0x00603820
void FUN_00603820()
{}


// @ 0x00603920
void FUN_00603920()
{}


// @ 0x00603a10
void FUN_00603a10()
{}


// @ 0x00603de0
void FUN_00603de0()
{}


// @ 0x00603f10
void FUN_00603f10()
{}


// @ 0x00603fe0
void FUN_00603fe0()
{}


// @ 0x006041f0
bool Handler14::HandleMessage(uint32_t msg, void* unused)
{
  if (msg == 0x238de9c) {
    if (mpLayout) {
      EndModal(((LayoutModal*)mpLayout)->FindWindowByID(0x43c8b98, 1), 0, 0);
    }
    ((SettingsForHandler*)((char*)this - 0x10))->Shutdown();
    return true;
  }
  if (msg == 0x62752d3) {
    ((SettingsForHandler*)((char*)this - 0x10))->mFC.A();
    ((SettingsForHandler*)((char*)this - 0x10))->m1A0.B();
    return true;
  }
  return false;
}


// @ 0x00604260
void FUN_00604260()
{}


// @ 0x006044b0
void FUN_006044b0()
{}


// @ 0x00604520
void FUN_00604520()
{}


// @ 0x006045c0
void FUN_006045c0()
{}


// @ 0x00604860
void cSPUISettings14::SaveAllSettings()
{
  mSub.Save();
  SaveOnlineSettings();
  if (ConfigManager_s0060_3820())
    ConfigManager_s0060_3820()->vt3c();
}

// @ 0x00604890
void FUN_00604890(int self, uint32_t resKey, uint32_t arg3, uint32_t winId)
{
  cSPUILayout_s0060_4890* const layout = (cSPUILayout_s0060_4890*)(self + 8);
  *(uint32_t*)(self + 4) = arg3;
  *(uint32_t*)(self + 0x20) = winId;
  layout->Init((const ResourceKey*)resKey, 0, 0x5b598fau);
  layout->GetObjects();
  IWindow_s0060_4890* const w = layout->FindWindowByID(winId, 1);
  if (w) w->AddWinProc((IWinProc_s0060_4890*)(*(uint32_t*)(self + 4)));
  *(uint32_t*)(self + 0x58) = 0;
  // The original walks the per-slot vector at +0x24 (element size 0x58), builds a
  // credits property list, then creates one icon/tooltip per element and finally
  // tears the sub-layout down.
  const int count = (*(int*)(self + 0x28) - *(int*)(self + 0x24)) / 0x58;
  for (int i = 0; i < count; ++i) {
    cSPUILayout_s0060_4890 sub;
    sub.Init((const ResourceKey*)0, 0, 0x5b598fau);
    IWindow_s0060_4890* const icon = sub.FindWindowByID(0x5dffa47u, 1);
    (void)icon;
    sub.Shutdown(1);
  }
  layout->Shutdown(1);
}

// @ 0x00604d40
uint32_t SP_cSPUISettings_DoMessage(int* self, int* param_2, int* param_3)
{
  // Only the message-dispatch skeleton is reproduced here.
  if (param_3 && ((param_3[2] == 0x287259f6) || (param_3[2] == (int)0xaf0b6441u))) {
    (void)self;
    return 1;
  }
  return 0;
}
