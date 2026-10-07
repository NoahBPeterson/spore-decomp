// Slice s005f16d0: SP::cSPSwatchPlanner / cSwatch3DView area.  Field offsets taken from the
// binary; the many small predicates are reconstructed exactly, large Init/DoMessage stubbed.
#include "types.h"
#include <new>

#define PV(n) virtual void _pv##n();

class cWriter {
 public:
  int GetBuffer();
};

class cObj2 {
 public:
  int Get();
};

class cRenderSomething {
 public:
  void Render(int arg);
};

int Fun_005a8ed0(int a, int b, int c, int d);

namespace SP {
class cSPSwatchPlanner {
 public:
  int m00;      // +0x00
  void* m04;    // +0x04
  int m08;      // +0x08
  int m0c;      // +0x0c
  char pad10[0x1c];
  void* m2c;    // +0x2c
  char pad30[0x64];
  float m94;    // +0x94
  char pad98[0x53];
  bool mEB;     // +0xeb
  char padEC[0x14];
  int m100;     // +0x100
  char pad104[0x5c];
  bool m160;    // +0x160
  char pad161[2];
  bool m163;    // +0x163
  char pad164[2];
  bool m166;    // +0x166
  char pad167[0x31];
  bool m198;    // +0x198

  int Check();
  void* Cast(uint32_t id);
  int CheckType();
  float GetDouble94();
  int Contains(const float* point);
  int GetBuffer();
};

// @ 0x005f2180
int cSPSwatchPlanner::Check() {
  if (mEB != 0) {
    if (m166 != 0 && m160 != 0 && m163 != 0)
      return 1;
    return 0;
  }
  if (m166 != 0 && m160 != 0)
    return 1;
  return 0;
}

// @ 0x005f22d0
int cSPSwatchPlanner::CheckType() {
  if (m198 != 0 && m100 == 0x71fa7d3f)
    return 1;
  return 0;
}

// @ 0x005f2310
float cSPSwatchPlanner::GetDouble94() {
  return m94 + m94;
}

// @ 0x005f2350
int cSPSwatchPlanner::Contains(const float* point) {
  const float* self = (const float*)this;
  return point[0] >= self[0] && point[1] >= self[1] && point[0] < self[2] && point[1] < self[3];
}

// @ 0x005f22a0
void* cSPSwatchPlanner::Cast(uint32_t id) {
  if (id == 0x3349c94)
    return this;
  if (id == 0xee3f516e)
    return this;
  if (id == 0x2f009dd0)
    return this;
  return id == 0x31e56741 ? this : 0;
}

// @ 0x005f2740
int cSPSwatchPlanner::GetBuffer() {
  if (m04)
    return ((cWriter*)m04)->GetBuffer();
  if (m2c)
    return ((cObj2*)m2c)->Get();
  return 0;
}

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// Real class model for the swatch planner's big functions (DoMessage, Init, SetModel, ...).
// ---------------------------------------------------------------------------------------------
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0

namespace SW {

template <typename T>
class ARC {  // EA::AutoRefCount with inline operator=
 public:
  T* mpObject;
  ARC() : mpObject(0) {}
  ARC& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
};

class IWinProc;
struct UIMessage;
template <typename T>
class ARCExt {  // EA::AutoRefCount<IWinText>: operator= stays out of line (0x00b5f950)
 public:
  T* mpObject;
  ARCExt& operator=(T* p);  // 0x00b5f950
};
typedef ARCExt<IWinProc> ARCText;
class IRC;

struct Key {
  uint32_t mInstance, mType, mGroup;
};

class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const float* GetArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30)
  virtual void SetFlag(int flag, bool value);    // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62)
  PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);  // +0x104
};

class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow* window, const UIMessage* message);  // +0x14
};

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();  // 0x00810000
  IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
  bool Init(const Key* key, bool b, uint32_t id);  // 0x008120d0
  void SetParentWin(IWindow* parent, bool b, uint32_t id);  // 0x008121b0
  char pad[0x18 - 4];
};

class Property {
 public:
  char pad[0x12];
  uint16_t mType;  // +0x12
  bool* GetBool();  // 0x0041e920
  int* GetInt();  // 0x0041e990
};

class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);                    // +0x1c
  PV(8)
  virtual bool GetProperty(uint32_t id, Property** result);  // +0x24
};

class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);  // +0x2c
};
IPropertyManager* PropertyManager();  // 0x0067de30

class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17)
  virtual IWindow* GetWindow(int which);  // +0x48
};
IWindowManager* WindowManager();

class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);      // +0x24
};
IMessageServer* MessageServer();  // 0x0067dcc0

class cString {
 public:
  cString();  // 0x006b5060
  ~cString();  // 0x006b5240
  const wchar_t* GetText(const void* v, int a, const void* b, int c);  // 0x006b55c0
  char pad[0x10];
};

class cSPUITooltipWinProc : public IWinProc {
 public:
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text);  // 0x00835e30
};
void* TooltipAlloc(unsigned int size, unsigned int align, const char* name, void* allocator);  // 0x009512d0
void* GetUIAllocator();                                                                        // 0x009512c0
extern const float kTipOffsetX;  // 0x013ec4d0
extern const float kTipOffsetY;  // 0x013f9c6c
extern const char kTipFmt[];     // 0x013f9c04

struct Vec2 {
  float x, y;
  Vec2(float a, float b) : x(a), y(b) {}
};

class IRC {
 public:
  virtual int AddRef();
  virtual int Release();
};

// UI message object (ctor 0x005c1280, dtor 0x005c12c0): two vptrs, an id, a key and two refs.
class IMsgA {
 public:
  virtual void ma();
};
class IMsgB {
 public:
  IMsgB() : m08(0) {}
  virtual void mb();
  int m08;  // +0x8
};
class cSPMessage : public IMsgA, public IMsgB {
 public:
  cSPMessage();  // 0x005c1280
  ~cSPMessage();  // 0x005c12c0
  virtual void ma();
  virtual void mb();
  uint32_t mID;     // +0xc
  int m10;          // +0x10
  Key mKey;         // +0x14
  ARCExt<IRC> mRefA;  // +0x20
  ARC<IRC> mRefB;   // +0x24
};

class IPadBase {
 public:
  virtual void pa();
  int pad4;
};
class cSPPaletteItem : public IPadBase, public IRC {
 public:
  Key mKey;    // +0xc
};

class cISPPaletteItemUI {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void OnRolloverBegin();  // +0x1c
  virtual void OnRolloverEnd();    // +0x20
  cSPPaletteItem* mPaletteItem;    // +0x4
  int mInterfaceID;                // +0x8
};

struct UIMessage {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  int mType;          // +0x8
  int mArg;           // +0xc
  uint32_t pad10, pad14;
  IWindow* mArg2;     // +0x18
};

struct ShortMessage {
  uint32_t mData;
  int pad4;
  int mFlag;
  int padc;
  uint32_t mID;
};

class RefCountVT {
 public:
  RefCountVT() : mRefCount(0) {}
  virtual ~RefCountVT() {}
  virtual int AddRef();
  virtual int Release();
  int mRefCount;
};

class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public RefCountVT {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);  // 0x005c6d70
  void Init(cSPPaletteItem* info, IWindow* button, int a, void* b);  // 0x005c6ca0
  bool mIsRolledOver;     // +0x18
  ARC<IWindow> mWinRoot;  // +0x1c
};

bool IsWithin(IWindow* a, IWindow* b);  // 0x00805150
bool StartBanMode(int id);              // 0x008d2fb0
void SetWindowAreaToParent(IWindow* w);                              // 0x00806bf0
void SetWindowImage(IWindow* w, const Key* key, int flag);           // 0x00807bb0
bool GetPropertyAsKey(cPropertyList* pl, uint32_t id, Key* out);     // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList* pl, uint32_t id, uint32_t* out);  // 0x006a12a0
bool GetPropertyAsText(cPropertyList* pl, uint32_t id, cString* out);          // 0x006a1360
extern uint32_t g_ModelGroup;                                                   // 0x0151c614
void FUN_005a8ed0(Key key, cPropertyList*& out);
int RemapTypeId(int id);                                                       // 0x00432f10
void SetMoneyString(double v, wchar_t* buf, int size, const wchar_t* fmt, const wchar_t* sym);  // 0x008822e0

class cSPPaletteInfo {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[0xc];
  int m10;
  char pad14[4];
  uint16_t mSymbol;  // +0x18
};

// 0x005c6630: key-holder check; the item passed to Init carries keys at +0xc / +0x18
class cSwatchItemInfo {
 public:
  char pad[0xc];
  Key mModelKey;  // +0xc
  Key mImageKey;  // +0x18
  bool Check(int arg);  // 0x005c6630
};

class cSPPaletteSwatch {  // 0x1c8 bytes, ctor 0x005f7380
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void SetModelKey(const Key* k);  // +0x24
  PV(10) PV(11) PV(12) PV(13)
  virtual void SetShowCostV(bool b);       // +0x38
  cSPPaletteSwatch();  // 0x005f7380
  void Init(const Key* key, IWindow* w, int a, uint32_t id, cSwatchItemInfo* info, cSPPaletteInfo* pi, bool flag);  // 0x005f4310
  void SetShowCost(bool b);  // 0x005f49a0
  void FUN_005f2290(int a);  // 0x005f2290
  char padE[0x100 - 4];
  uint32_t m100;
};

class cSPSwatchPlannerReal : public cSPPaletteItemUI, public IHandler {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);
  void Init(cSwatchItemInfo* info, IWindow* parent, int a, cSPPaletteInfo* palInfo);
  IWindow* FindActiveButton();  // 0x005f14a0
  void SetImage(const Key* key);   // 0x005f1500
  void SetModelHelper();
  void FUN_005f10b0();
  void SetModel(cPropertyList*& out);
  ARC<cSPUILayout> mLayout;     // +0x24
  ARC<cSPPaletteSwatch> mSwatch;  // +0x28
  ARCText mLargeNewTooltip;     // +0x2c
  ARCText mNewTooltip;          // +0x30
  ARCText mEditTooltip;         // +0x34
  ARCText mLoadTooltip;         // +0x38
  uint32_t mModelType;          // +0x3c
  int mLockedLevel;             // +0x40
  bool mModelChosen;            // +0x44
  bool mShowCost;               // +0x45
  bool mFlag46;                 // +0x46
  bool mReadyForMessages;       // +0x47
  bool mHasModelKey;            // +0x48
  char pad49[3];
  Key mModelKey;                // +0x4c
  int mModelKind;               // +0x58
  char pad5c[8];
  ARC<cPropertyList> mPropList;  // +0x64
  ARC<cSPPaletteInfo> mInfo;     // +0x68
};

// @ 0x005f16d0
bool cSPSwatchPlannerReal::HandleUIMessage(IWindow* window, const UIMessage* message) {
  switch (message->mType) {
    case 0x1b:
      if (message->mArg == 1 && !mIsRolledOver) {
        IWindow* const area = FindActiveButton();
        if (!IsWithin(area, message->mArg2)) return true;
        const bool a = StartBanMode(0x3e8);
        const bool b = StartBanMode(0x3ea);
        const bool c = StartBanMode(0x3e9);
        if (a || b || c) return true;
        mIsRolledOver = true;
        OnRolloverBegin();
        return true;
      }
    // fall through
    case 0x287259f6:
      switch (message->mArg) {
        case 0x4a1cb6d: {
          cSPMessage msg;
          cSPPaletteItem* const item = mPaletteItem;
          msg.mID = 0x133b269e;
          msg.mKey = item->mKey;
          msg.mRefA = item;
          MessageServer()->PostMSG(msg.mID, &msg, 0);
          return true;
        }
        case 0x6443438: {
          cSPMessage msg;
          cSPPaletteItem* const item = mPaletteItem;
          msg.mID = 0xb2e18705;
          msg.mKey = item->mKey;
          msg.mRefA = item;
          MessageServer()->PostMSG(msg.mID, &msg, 0);
          return true;
        }
        case 0x4a1cb6b:
        case 0x4a1cb71: {
          ShortMessage m;
          m.mData = mModelType;
          m.mFlag = 0;
          m.mID = 0x4a314e6;
          MessageServer()->PostMSG(m.mID, &m, 0);
          return true;
        }
        case 0x4a1cb6c: {
          ShortMessage m;
          m.mData = mModelType;
          m.mFlag = 1;
          m.mID = 0x4a314e6;
          MessageServer()->PostMSG(m.mID, &m, 0);
          return true;
        }
      }
      break;
    case 0x1c:
      if (message->mArg == 1 && mIsRolledOver) {
        IWindow* const area = FindActiveButton();
        if (!IsWithin(area, WindowManager()->GetWindow(1))) {
          mIsRolledOver = false;
          OnRolloverEnd();
        }
      }
      break;
  }
  return cSPPaletteItemUI::HandleUIMessage(window, message);
}

// @ 0x005f21d0
void cSPSwatchPlannerReal::SetModel(cPropertyList*& out) {
  if (mModelKind == -1) {
    FUN_005a8ed0(mModelKey, out);
    return;
  }
  PropertyManager()->GetPropertyList(RemapTypeId(mModelKind), g_ModelGroup, out);
}


// @ 0x005f1960
void cSPSwatchPlannerReal::Init(cSwatchItemInfo* info, IWindow* parent, int a, cSPPaletteInfo* palInfo) {
  if (!parent) return;
  mModelChosen = palInfo->m10 ? info->Check(palInfo->m10) : false;
  mInfo = palInfo;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  Key layoutKey;
  layoutKey.mInstance = 0x4f087663;
  layoutKey.mType = 0x510a95b;
  layoutKey.mGroup = 0x40464100;
  mLayout->Init(&layoutKey, true, 0x5b598fa);
  mLayout->SetParentWin(parent, true, 0x5b598fa);
  IWindow* const root = mLayout->FindWindowByID(0x4a1cb70, true);
  SetWindowAreaToParent(root);
  cSPPaletteItemUI::Init((cSPPaletteItem*)info, root, a, palInfo);
  const Key* const modelKey = &info->mModelKey;
  SetImage(&info->mImageKey);
  IPropertyManager* const pm = PropertyManager();
  if (pm->GetPropertyList(modelKey->mInstance, modelKey->mGroup, mPropList.AsOutParam())) {
    IWindow* const imageWin = mLayout->FindWindowByID(0x4a1cb6f, true);
    Key k;
    k.mInstance = 0;
    k.mType = 0;
    k.mGroup = 0;
    uint32_t propId = 0x133c3cad;
    if (mModelChosen) {
      if (mPropList->HasProperty(0x643d3e1)) propId = 0x643d3e1;
    }
    if (GetPropertyAsKey(mPropList.mpObject, propId, &k)) SetWindowImage(imageWin, &k, 0);
    const bool chosen = mModelChosen;
    IWindow* const lockWin = mLayout->FindWindowByID(0x641a080, true);
    IWindow* const costWin = mLayout->FindWindowByID(0x642bea8, true);
    if (lockWin) {
      lockWin->SetFlag(1, !chosen);
      if (GetPropertyAsKey(mPropList.mpObject, 0x133c3cab, &k)) SetWindowImage(lockWin, &k, 0);
    }
    if (costWin) {
      costWin->SetFlag(1, chosen);
      if (GetPropertyAsKey(mPropList.mpObject, 0x133c3cac, &k)) SetWindowImage(costWin, &k, 0);
    }
    GetPropertyAsKeyInstance(mPropList.mpObject, 0x5338876f, &mModelType);
    Property* prop;
    if (mPropList.mpObject && mPropList->GetProperty(0x56097656, &prop) && prop->mType == 1)
      mFlag46 = *prop->GetBool();
    if (mPropList.mpObject && mPropList->GetProperty(0x4adb304, &prop) && prop->mType == 1)
      mShowCost = *prop->GetBool();
    if (!GetPropertyAsKey(mPropList.mpObject, 0x55dca4c, &mModelKey))
      GetPropertyAsKey(mPropList.mpObject, 0x4294752, &mModelKey);
    if (mPropList.mpObject && mPropList->GetProperty(0x2166464, &prop) && prop->mType == 9)
      mLockedLevel = *prop->GetInt();
    const bool showLocked = !mModelChosen && mLockedLevel > 0;
    IWindow* const lvlWin = mLayout->FindWindowByID(0x642c9be, true);
    if (lvlWin) lvlWin->SetFlag(1, showLocked);
    if (showLocked) {
      IWindow* const priceWin = mLayout->FindWindowByID(0x642bd0b, true);
      if (priceWin) {
        wchar_t sym[2];
        sym[0] = palInfo->mSymbol;
        sym[1] = 0;
        wchar_t buf[0x20];
        SetMoneyString((double)mLockedLevel, buf, 0x20, L"%-F%-p", sym);
        priceWin->SetCaption(buf);
      }
    }
    mLayout->FindWindowByID(0x4a1cb71, true);
    IWindow* const w1 = mLayout->FindWindowByID(0x4a1cb6b, true);
    IWindow* const w2 = mLayout->FindWindowByID(0x4a1cb6c, true);
    IWindow* const w3 = mLayout->FindWindowByID(0x4a1cb6d, true);
    cString text;
    if (w1) {
      if (GetPropertyAsText(mPropList.mpObject, 0x5a9e402d, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mNewTooltip = tip;
        w1->AddWinProc(mNewTooltip.mpObject);
      }
    }
    if (w2) {
      if (GetPropertyAsText(mPropList.mpObject, 0x4ca3377, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mEditTooltip = tip;
        w2->AddWinProc(mEditTooltip.mpObject);
      }
    }
    if (w3) {
      if (GetPropertyAsText(mPropList.mpObject, 0x6081d87b, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mLoadTooltip = tip;
        w3->AddWinProc(mLoadTooltip.mpObject);
      }
    }
    IWindow* const swatchWin = mLayout->FindWindowByID(0x4a1cb6e, true);
    cSPPaletteSwatch* const swatch = new ("Editor", 0, 0, 0, 0) cSPPaletteSwatch();
    mSwatch = swatch;
    swatch->Init(&info->mModelKey, swatchWin, a, 0xb2e18705, info, palInfo, true);
    swatch->SetShowCost(mShowCost);
    swatch->SetShowCostV(mShowCost);
    swatch->FUN_005f2290(0);
    uint32_t kind = 0x71fa7d3f;
    uint32_t tmp;
    if (GetPropertyAsKeyInstance(mPropList.mpObject, 0x57fb25a, &tmp)) {
      kind = tmp;
      if (kind == 0x5e71ab9b) {
        swatch->m100 = 0x2ca33bdb;
      } else {
        swatch->m100 = kind;
      }
    } else {
      swatch->m100 = kind;
    }
    if (mModelKey.mInstance != 0) {
      mSwatch->SetModelKey(&mModelKey);
      mHasModelKey = true;
    }
    IWindow* const kindWin = mLayout->FindWindowByID(0x6443438, true);
    if (kindWin) {
      bool v;
      if (mModelChosen) v = false;
      else v = kind == 0x5e71ab9b;
      kindWin->SetFlag(1, v);
    }
  }
  FUN_005f10b0();
  MessageServer()->AddHandler(this, 0x4a344e9);
  MessageServer()->AddHandler(this, 0x3150c27);
  mReadyForMessages = true;
}


// ---------------------------------------------------------------------------------------------
// cSwatch3DView::Init (0x005f24e0) and the viewport helper (0x005f2390)
// ---------------------------------------------------------------------------------------------
struct FRect {
  float left, top, right, bottom;
};
struct Rect {
  int left, top, right, bottom;
};

class IArgObj {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void Set(IArgObj* o);  // +0x18
};

class IRefObj {  // generic virtual-refcounted object: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
};

class cSPUILayeredObject {  // AddRef slot 1, Release slot 2
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void FUN_0080dda0(IRefObj* renderer, int a);  // 0x0080dda0
  void FUN_0080d7d0(int a);                     // 0x0080d7d0
  void FUN_0080d790(int a, int b);              // 0x0080d790
  void FUN_0080d7c0(int a);                     // 0x0080d7c0
};

class cSPUIModelsAndEffectsRenderer {  // non-virtual AddRef/Release
 public:
  void AddRef();   // 0x0080df50
  void Release();  // 0x0080df80
  void FUN_0080fa00(uint32_t a, uint32_t b, int c);  // 0x0080fa00 (cSPUILayerManager)
  void FUN_0080d5c0(int a);                          // 0x0080d5c0
  int FUN_0080db70();                                // 0x0080db70
  IArgObj* FUN_0080db90();                           // 0x0080db90
  class cSwatchTarget* FUN_0080d5a0(class IWindowLike* w, int a, int b);  // 0x0080d5a0
};
class cSwatchTarget {
 public:
  void FUN_0080f360();  // 0x0080f360
};

class IWindowLike {  // the "CustomSwatchAnimWorld" window: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5)
  virtual void SetArg(IArgObj* o);  // +0x18
  virtual void SetArgs(int a, int b, int c, int d, int e);  // +0x1c
};

class IAnimWorldManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IWindowLike* GetWorld(const wchar_t* name);  // +0x20
};

class IEffectWorld {  // m28: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3)
  virtual void V10(char a);        // +0x10
  virtual void V14(int a);         // +0x14
  virtual void V18(int a, int b);  // +0x18
  PV(7) PV(8)
  virtual void V24();              // +0x24
  virtual void V28(int a);         // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15)
  virtual void V40();              // +0x40
  PV(17)
  virtual void V48(uint32_t id);   // +0x48
};

class IFactory;
class cBoundingBoxLike {
 public:
  PV(0)
  IFactory* GetFactory();  // 0x006c10e0
};
cBoundingBoxLike* AddBoundingBox();  // 0x0067cad0
cSPUIModelsAndEffectsRenderer* FUN_0080ed50();
cSPUILayeredObject* FUN_0080f730(cBoundingBoxLike* b);  // thiscall in orig? see below
IWindowLike* GetWorldFromAnimMgr();
class IFactory {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79) PV(80)
  virtual int Make(int a);  // +0x144
};

class cSwatch3DView {
 public:
  void Init(IRefObj* renderer, int a2, char a3, char a4);  // 0x005f24e0
  bool mVisible;                          // +0x0
  ARC<cSPUILayeredObject> mLayeredObject;  // +0x4
  char pad08[0x20 - 8];
  ARC<IWindowLike> mWindow;               // +0x20
  ARC<IRefObj> mRenderer;                 // +0x24
  ARC<IEffectWorld> mEffectWorld;         // +0x28
  ARC<cSPUIModelsAndEffectsRenderer> mModelRenderer;  // +0x2c
};

IAnimWorldManager* GetAnimWorldManager();             // 0x0067cb20
IEffectWorld* GetEffectWorld();                       // 0x0067ddc0

// @ 0x005f24e0
void cSwatch3DView::Init(IRefObj* renderer, int a2, char a3, char a4) {
  mRenderer = renderer;
  if (a3) {
    mModelRenderer = FUN_0080ed50();
    int h = AddBoundingBox()->GetFactory()->Make(0);
    mModelRenderer->FUN_0080fa00(0x13567133, 0x13567133, h);
    mModelRenderer->FUN_0080d5c0(a2);
    const int ebp = mModelRenderer->FUN_0080db70();
    mWindow = GetAnimWorldManager()->GetWorld(L"CustomSwatchAnimWorld");
    IArgObj* const o = mModelRenderer->FUN_0080db90();
    if (o) o->Set(0);
    mWindow->SetArg(o);
    mWindow->SetArgs(ebp, 1, 1, 0, 0);
    IWindowLike* const w = mWindow.mpObject;
    mModelRenderer->FUN_0080d5a0(w, 0xe, 0)->FUN_0080f360();
    if (a4) {
      mEffectWorld = GetEffectWorld();
      if (mEffectWorld.mpObject) {
        mEffectWorld->V40();
        mEffectWorld->V24();
        mEffectWorld->V14(0x1d);
        mEffectWorld->V10(a3);
        mEffectWorld->V18(ebp, 0);
        mEffectWorld->V48(0x5e5252a);
        mEffectWorld->V28(1);
      }
    } else {
      mEffectWorld = 0;
    }
  } else {
    mLayeredObject = FUN_0080f730(AddBoundingBox());
    mLayeredObject->FUN_0080dda0(renderer, 0);
    mLayeredObject->FUN_0080d7d0(0);
    mLayeredObject->FUN_0080d790(a2, 0);
    mLayeredObject->FUN_0080d7c0(0);
  }
  mVisible = false;
}

class cUIViewport {
 public:
  void FUN_007c4010();  // 0x007c4010
  void FUN_007c4a60(const Rect* r);  // 0x007c4a60
  void FUN_007c4b50(float aspect);   // 0x007c4b50
};
class cAppLike {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cUIViewport* GetScreenRect(Rect* out);  // +0x58
};
cAppLike* App();  // 0x0067dd10

// @ 0x005f2390
void SizeViewportToWindowAndRemainOnScreen(cUIViewport* viewport, IWindow* window, float scale, float cx, float cy) {
  if (viewport && window) {
    Rect screen;
    App()->GetScreenRect(&screen)->FUN_007c4010();
    const float* const area = window->GetArea();
    const float halfW = ((area[2] - area[0]) * scale) * 0.5f;
    const float halfH = ((area[3] - area[1]) * scale) * 0.5f;
    Rect r;
    r.left = (int)(cx - halfW);
    r.top = (int)(cy - halfH);
    r.right = (int)(cx + halfW);
    r.bottom = (int)(cy + halfH);
    if (r.left < screen.left) {
      const int d = screen.left - r.left;
      r.left = r.left + d;
      r.right = r.right + d;
    }
    if (r.right > screen.right) {
      const int d = screen.right - r.right;
      r.left = r.left + d;
      r.right = r.right + d;
    }
    if (r.top < screen.top) {
      const int d = screen.top - r.top;
      r.top = r.top + d;
      r.bottom = r.bottom + d;
    }
    if (r.bottom > screen.bottom) {
      const int d = screen.bottom - r.bottom;
      r.top = r.top + d;
      r.bottom = r.bottom + d;
    }
    viewport->FUN_007c4a60(&r);
    viewport->FUN_007c4b50(halfW / halfH);
  }
}

}  // namespace SW
