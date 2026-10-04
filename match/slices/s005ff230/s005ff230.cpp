// SP options screen (cSPUISettings) and its tabs: cSettingsTab, cAudioTab, cGameTab,
// cOnlineTab and two more tabs, plus an inlined EA::Stopwatch restart.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(uint64_t* count);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount& operator=(T* pObject) {
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

// Retail layout: 0x18 bytes plus a running flag at +0x18.
class Stopwatch {
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
class LimitStopwatch : public Stopwatch {
 public:
  void SetTimeLimit(int limit, bool bStartTimer);
};

namespace UTFWin {
class IWinProc;
class IWindow {
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
  virtual void AddWinProc(IWinProc* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc* proc);           // +0x108
  virtual IWindow* GetNextChild(IWindow* prev);         // +0x10c
  virtual bool IsMessageFrom(const void* message);      // +0x110
};
// Control interfaces reached through IWindow::Cast.
class IButton {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow* ToWindow();                          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  virtual uint32_t GetButtonStateFlags();               // +0x2c
};
class ISlider {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow* ToWindow();                          // +0x10
  PV(5) PV(6)
  virtual void SetValue(int value, bool notify);        // +0x1c
  PV(8) PV(9) PV(10) PV(11)
  virtual int GetMaxValue();                            // +0x30
};
class IFloatValue {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual float GetValue();                             // +0x14
};
class IColorable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetColor(uint32_t color);                // +0x28
};
class IWinProc {
 public:
  virtual int AddRef();
  virtual int Release();
};
struct Message {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;     // +0x8
  uint32_t padC[2];
  int mValue;         // +0x14
};
}  // namespace UTFWin

namespace Messaging {
class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);         // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void RemoveHandler(IHandler* handler, uint32_t messageID, int priority);  // +0x2c
};
}  // namespace Messaging
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::IButton;
using EA::UTFWin::ISlider;
using EA::UTFWin::Message;

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  bool Init(uint32_t instanceID, uint32_t typeID, uint32_t groupID);
  void GetObjects();
  void Shutdown(bool b);
  char pad[0x18 - 4];
};

class cSPUILayoutManager {
 public:
  void SetWorldVisibility(uint32_t worldID, bool visible);  // FUN_00810660
  void SetAllWorldsVisibility(bool visible);
};
cSPUILayoutManager* SPUILayoutManager();  // 0x80fee0

namespace SPUIHelpers {
void EndModal(IWindow* window, int a, int b);
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
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, int value);  // +0x2c
  virtual int GetValue(uint32_t id);              // +0x30
};
IConfigManager* ConfigManager();
class IApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual uint32_t GetModeID();  // +0x38
};
IApp* App();
class ICanvas {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual bool IsFullscreen();  // +0x54
};
ICanvas* Canvas();
class cPropertyList {
 public:
  bool HasProperty(uint32_t id);  // 0x6a25a0
};
extern cPropertyList* gAppProperties;  // 0x15fd918

namespace Audio {
class cAudioPreferences {
 public:
  bool IsMuted();
  void Mute(bool mute);
  int GetSoundQuality();
  void SetSoundQuality(int quality);
  int GetSpeakerMode();
  void SetSpeakerMode(int mode);
  bool GetVolume(uint32_t id, float* volume);
  void SetVolume(uint32_t id, float volume);
};
}  // namespace Audio
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual Audio::cAudioPreferences* GetPreferences();  // +0x3c
};
IAudioSystem* AudioSystem();

class IOnlinePrefs {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetLoginEnabled(bool b);  // +0x28
  virtual bool GetLoginEnabled();        // +0x2c
  PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual void Save();                   // +0x54
};
IOnlinePrefs* OnlinePrefs();  // FUN_00607a60

// ---------------------------------------------------------------------------
class cSettingsTab {
 public:
  virtual ~cSettingsTab();
  virtual void Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID);
  IWinProc* mWinProc;     // +0x4
  cSPUILayout mLayout;    // +0x8
  uint32_t mTabID;        // +0x20
};

class cAudioTab : public cSettingsTab {
 public:
  void Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID);
  void Shutdown();
  void RestoreSettingsFromEntry();
  __forceinline void CheckButton(uint32_t id) {
    IWindow* w = mLayout.FindWindowByID(id, true);
    if (w) {
      IButton* button = (IButton*)w->Cast(0x8ed27e7a);
      if (button) button->SetButtonStateFlag(4, true);
    }
  }
  bool DoMessageTab(IWindow* window, const Message* message);
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

class cGameTab : public cSettingsTab {
 public:
  void Shutdown();
  bool DoMessageTab(IWindow* window, const Message* message);
  void RestoreSettingsFromEntry();
  bool mInitialTutorialsSettings;   // +0x24
  bool mInitialShowHints;           // +0x25
  bool mInitialMovieRes;            // +0x26
  bool mInitialPhotoRes;            // +0x27
  bool mInitialGameDifficulty;      // +0x28
};

class cOnlineTab : public cSettingsTab, public EA::Messaging::IHandler {
 public:
  void Shutdown();
  void RestoreSettingsFromEntry();
  char pad28[0x48 - 0x28];
  bool mInitial[8];                 // +0x48
};

class cOptionTab : public cSettingsTab {
 public:
  void RestoreSettingsFromEntry();
  bool mInitialValue;               // +0x24
  uint32_t mPropertyID;             // +0x28
};

struct cProfileEntry {
  void Shutdown();  // FUN_005fe320
  char pad[0x58];
};
class cGraphicsTab : public cSettingsTab {
 public:
  void Shutdown();
  void UpdateFullscreenControls();
  cProfileEntry* mpBegin;           // +0x24
  cProfileEntry* mpEnd;             // +0x28
  char pad2c[0x48 - 0x2c];
  EA::AutoRefCount<cRefCounted> mpA;  // +0x48
  EA::AutoRefCount<IWindow> mpWindow; // +0x4c
  EA::AutoRefCount<cRefCounted> mpC;  // +0x50
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  cProfileEntry& operator[](uint32_t i) { return mpBegin[i]; }
};

class cSPUISettings {
 public:
  void BeginClose();
  void SaveOnlineSettings();
  char pad0[0x14];
  EA::AutoRefCount<cSPUILayout> mpLayout;   // +0x14
  char pad18[0x1a9 - 0x18];
  bool mbInitialYouTubeLogin;               // +0x1a9
  char pad1aa[0x220 - 0x1aa];
  EA::AutoRefCount<cRefCounted> mpModal;    // +0x220
  char pad224[4];
  EA::LimitStopwatch mLimitStopwatch;       // +0x228
};
}  // namespace SP

struct cTimedObject {
  void RestartTimer();
  char pad[0x80];
  EA::Stopwatch mStopwatch;  // +0x80
};

static inline int FloatToInt(float f) { __asm cvtss2si eax, f }

// ---------------------------------------------------------------------------
// @ 0x5ff230
void cTimedObject::RestartTimer() {
  mStopwatch.mnStartTime = 0;
  mStopwatch.mnTotalElapsedTime = 0;
  if (mStopwatch.mnUnits == EA::Stopwatch::kUnitsCycles)
    mStopwatch.mnStartTime = EA::Stopwatch::GetCPUCycle();
  else
    mStopwatch.mnStartTime = EA::Stopwatch::GetStopwatchCycle();
  mStopwatch.mnTotalElapsedTime = 0;
  mStopwatch.mbRunning = false;
}

using namespace SP;

// @ 0x5ff2a0
void cAudioTab::Shutdown() {
  if (mhSound) {
    ReleaseObject((void*)mhSound, 0);
    mhSound = 0;
  }
  mLayout.Shutdown(true);
}

// @ 0x5ff2d0
void cAudioTab::RestoreSettingsFromEntry() {
  if (AudioSystem()) {
    Audio::cAudioPreferences* prefs = AudioSystem()->GetPreferences();
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

// @ 0x5ff370
bool cGameTab::DoMessageTab(IWindow* window, const Message* message) {
  if (message->mType == 0x287259f6) {
    switch (message->mpSource->GetControlID()) {
      case 0x462cb78: ConfigManager()->SetValue(0x473b8cc, 3); return true;
      case 0x462cb58: ConfigManager()->SetValue(0x473b8cc, 2); return true;
      case 0x462c820: ConfigManager()->SetValue(0x473b8cc, 1); return true;
      case 0x462cba0: ConfigManager()->SetValue(0x473b8cb, 1); return true;
      case 0x462cbb8: ConfigManager()->SetValue(0x473b8cb, 3); return true;
      case 0x462cbb0: ConfigManager()->SetValue(0x473b8cb, 2); return true;
    }
  }
  return false;
}

// @ 0x5ff460
void cGameTab::RestoreSettingsFromEntry() {
  ConfigManager()->SetValue(0x4ea96cb, mInitialTutorialsSettings);
  ConfigManager()->SetValue(0x5b5bb5e, mInitialShowHints);
  ConfigManager()->SetValue(0x636ec26, mInitialMovieRes);
  ConfigManager()->SetValue(0x473b8cb, mInitialGameDifficulty);
  ConfigManager()->SetValue(0x473b8cc, mInitialPhotoRes);
}

// @ 0x5ff4e0
void cOnlineTab::Shutdown() {
  MessageServer()->RemoveHandler(this, 0x44db12e, -9999);
  MessageServer()->RemoveHandler(this, 0x5b96086, -9999);
  MessageServer()->RemoveHandler(this, 0x5c5594a, -9999);
  mLayout.Shutdown(true);
}

// @ 0x5ff560
void cOnlineTab::RestoreSettingsFromEntry() {
  ConfigManager()->SetValue(0x5664a8b, mInitial[0]);
  ConfigManager()->SetValue(0x5de7b4a, mInitial[1]);
  ConfigManager()->SetValue(0x626f940, mInitial[2]);
  ConfigManager()->SetValue(0x626f958, mInitial[3]);
  ConfigManager()->SetValue(0x626f9c0, mInitial[4]);
  ConfigManager()->SetValue(0x685a785, mInitial[5]);
  ConfigManager()->SetValue(0x685a821, mInitial[6]);
  ConfigManager()->SetValue(0x685a63c, mInitial[7]);
}

// @ 0x5ff630
void cGameTab::Shutdown() {
  mLayout.Shutdown(true);
}

// @ 0x5ff640
void cOptionTab::RestoreSettingsFromEntry() {
  ConfigManager()->SetValue(mPropertyID, mInitialValue);
  MessageServer()->PostMSG(0x679c40d, 0, 0);
}

// @ 0x5ff700
void cSPUISettings::BeginClose() {
  IWindow* window = mpLayout->FindWindowByID(0x43c8b98, true);
  if (window) {
    window->SetFlag(1, false);
    float closeTime = 0.0f;
    for (IWindow* child = window->GetNextChild(0); child; child = window->GetNextChild(child)) {
      EA::UTFWin::IFloatValue* value = (EA::UTFWin::IFloatValue*)child->Cast(0x8f2b630b);
      if (value) {
        closeTime = value->GetValue();
        break;
      }
    }
    SPUIHelpers::EndModal(window, 0, 0);
    IWindow* w = mpLayout->FindWindowByID(0x5c05d20, true);
    if (w) w->SetFlag(0x10, false);
    mLimitStopwatch.SetTimeLimit(FloatToInt(closeTime * 1000.0f), true);
  }
  if (mpModal) {
    mpModal->Close(0);
    mpModal = 0;
  }
  cSPUILayoutManager* manager = SPUILayoutManager();
  manager->SetWorldVisibility(0x5b598f7, false);
  manager->SetWorldVisibility(0x5b598f6, false);
  manager->SetAllWorldsVisibility(true);
  MessageServer()->PostMSG(0x4519b5a, 0, 0);
}

// @ 0x5ff850
void cSPUISettings::SaveOnlineSettings() {
  IOnlinePrefs* prefs = OnlinePrefs();
  IWindow* window = mpLayout->FindWindowByID(0x43b6428, true);
  if (window) {
    bool checked = (int)(window->GetState() & 4) > 0;
    if (checked != prefs->GetLoginEnabled()) {
      prefs->SetLoginEnabled(checked);
      prefs->Save();
    }
  }
  if (mbInitialYouTubeLogin != ConfigManager()->GetValue(0x5de7b4a))
    MessageServer()->PostMSG(0x5de7b4a, 0, 0);
}

// @ 0x5ff8e0
void cSettingsTab::Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID) {
  mTabID = tabID;
  mWinProc = winProc;
  mLayout.Init(layoutID, 0, 0x5b598fa);
  mLayout.GetObjects();
  mLayout.FindWindowByID(mTabID, true)->AddWinProc(mWinProc);
}

// @ 0x5ff940
void cGraphicsTab::Shutdown() {
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
    (*(cProfileEntry* volatile*)&mpBegin)[i].Shutdown();
  mLayout.Shutdown(true);
}

// @ 0x5ffa30
void cAudioTab::Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID) {
  cSettingsTab::Init(layoutID, winProc, tabID);
  IAudioSystem* audio = AudioSystem();
  if (!audio) return;
  Audio::cAudioPreferences* prefs = audio->GetPreferences();
  if (!prefs) return;

  mbInitialMuteAll = prefs->IsMuted();
  IWindow* w = mLayout.FindWindowByID(0x899eb157, true);
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
  uint32_t mode = App()->GetModeID();
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
      if (gAppProperties->HasProperty(0x63ab656)) {
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
      if (gAppProperties->HasProperty(0x63ab656)) {
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

// @ 0x5ffee0
bool cAudioTab::DoMessageTab(IWindow* window, const Message* message) {
  bool handled = false;
  IAudioSystem* audio = AudioSystem();
  Audio::cAudioPreferences* prefs = 0;
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

// @ 0x600180
void cGraphicsTab::UpdateFullscreenControls() {
  bool fullscreen = Canvas()->IsFullscreen();
  IWindow* w = mLayout.FindWindowByID(0x5b591d8, true);
  if (w) {
    IButton* button = (IButton*)w->Cast(0x8ed27e7a);
    if (button) {
      w->SetFlag(2, !fullscreen);
      w->SetFlag(0x10, fullscreen);
      button->SetButtonStateFlag(4, ConfigManager()->GetValue(0x636ec26) != 0);
    }
  }
  w = mLayout.FindWindowByID(0x669ea05, true);
  if (w) {
    EA::UTFWin::IColorable* c = (EA::UTFWin::IColorable*)w->Cast(0xf15f4bd);
    if (c) c->SetColor(fullscreen ? 0x99999999 : 0xd6ffffff);
  }
}
