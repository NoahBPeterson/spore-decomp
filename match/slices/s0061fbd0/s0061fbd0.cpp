// SP::Pollen registration dialog + cancel-confirmation dialog (Spore.com login flow) and two
// Pollinator work-item helpers. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "s0061fbd0.h"

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);

namespace EA {
namespace UTFWinExtras {
class cXHTMLFrameSet {
 public:
  cXHTMLFrameSet(void* pCallback);  // 0x00996cc0
  virtual int AddRef();
  virtual int Release();
  void Shutdown();                                       // 0x00997140
  void SetEventIDs(int a, int b, int c, int d);          // 0x00996280
  bool Attach(EA::UTFWin::IWindow* pWindow, uint32_t id);  // 0x009979f0
  void HandleLocationChange(int a, const wchar_t* url, void* p, int b);  // 0x00997730
  uint32_t pad[24];
};
}  // namespace UTFWinExtras
}  // namespace EA
using EA::AutoRefCount;
using EA::UTFWinExtras::cXHTMLFrameSet;

struct UIRootState {
  uint8_t pad[0x118];
  int mbModalCursor;  // +0x118
};
struct UIRoot {
  uint8_t pad[0x3c];
  UIRootState* mpState;  // +0x3c
};
extern UIRoot* gpUIRoot;  // 0x015fd918
void FUN_00809930(bool b);
void FUN_00809950(EA::UTFWin::IWindow* w);
extern const wchar_t* gParamUserName;    // 0x01520a10
extern const wchar_t* gParamScreenName;  // 0x01520a14
extern const wchar_t* gParamPassword;    // 0x01520a18
extern void* gLocationChangeParam;       // 0x01520a0c
void FormParamCallbackDummy();

namespace SP {
namespace Pollen {
using namespace EA;
using namespace EA::UTFWin;

class cRegistrationDialog : public IWinProc,
                            public EA::Messaging::IHandler,
                            public IModalWindowCallback,
                            public EA::RefCountVTemplate<int> {
 public:
  cRegistrationDialog();
  virtual ~cRegistrationDialog();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  virtual void OnModalEnd(IWindow* pWindow, uint32_t id);

  void Show(bool b);              // 0x00620050
  void AutoSizeButtons();         // 0x006200c0
  void SetControlsEnabled(bool b);  // 0x00620110
  void SetButtonsEnabled(bool b);   // 0x006201a0
  __declspec(noinline) void End();  // 0x00620380
  void ConfirmLogin();            // 0x006205f0
  bool Show2(bool bEnterPressed);  // 0x006208c0
  static void FormParamCallback(const wchar_t* name, const wchar_t* value, cRegistrationDialog* self);

  cSPUILayout mLayout;                        // +0x14
  AutoRefCount<cXHTMLFrameSet> mpXHTMLFrameSet;  // +0x2c
  bool mbAutoExitAfterLogin;                  // +0x30
  string16 mUserName;                         // +0x34
  string16 mScreenName;                       // +0x44
  string16 mPassword;                         // +0x54
  bool mbEnterPressed;                        // +0x64
  bool mbFlag65;                              // +0x65
  int mState;                                 // +0x68
};

// @ 0x00620050
void cRegistrationDialog::Show(bool b) {
  IWindow* w = mLayout.FindWindowByID(0xffffffff, true);
  w->SetFlag(1, b);
  if (gpUIRoot->mpState->mbModalCursor) FUN_00809930(b);
  IWindow* w2 = mLayout.FindWindowByID(0xffffffff, true);
  if (b)
    SPUIHelpers::BeginModal(w2, 0, true);
  else
    SPUIHelpers::EndModal(w2, 0, false);
}

// @ 0x006200c0
void cRegistrationDialog::AutoSizeButtons() {
  IWindow* w = mLayout.FindWindowByID(0x519e168, true);
  if (w) {
    SPUIHelpers::AutoSizeWindowForText(w, true, false);
    IWindow* anchor = mLayout.FindWindowByID(0x519e308, true);
    if (anchor) SPUIHelpers::AnchorWindowToWindow(w, anchor, 0x820, 0);
  }
}

// @ 0x00620110
void cRegistrationDialog::SetControlsEnabled(bool b) {
  IWindow* w = mLayout.FindWindowByID(0x6555818, true);
  if (gpUIRoot->mpState->mbModalCursor) {
    if (w) w->SetFlag(1, false);
  } else {
    if (w) w->SetFlag(1, b);
  }
  IWindow* w2 = mLayout.FindWindowByID(0x519e168, true);
  if (w2) w2->SetFlag(1, b);
  IWindow* w3 = mLayout.FindWindowByID(0x519e308, true);
  if (w3) w3->SetFlag(1, b);
}

// @ 0x006201a0
void cRegistrationDialog::SetButtonsEnabled(bool b) {
  IWindow* w = mLayout.FindWindowByID(0x519d9b8, true);
  if (w) w->SetFlag(2, b);
  IWindow* w2 = mLayout.FindWindowByID(0x519e168, true);
  if (w2) w2->SetFlag(2, b);
  IWindow* w3 = mLayout.FindWindowByID(0xfffffff2, true);
  if (w3) w3->SetFlag(2, b);
  IWindow* w4 = mLayout.FindWindowByID(0x65d20a8, true);
  if (w4) w4->SetFlag(2, b);
}

// @ 0x00620380
void cRegistrationDialog::End() {
  Messaging::IHandler* h1 = static_cast<Messaging::IHandler*>(this);
  MessageServer()->RemoveListener(h1, 0x44db12e, -9999);
  Messaging::IHandler* h2 = static_cast<Messaging::IHandler*>(this);
  MessageServer()->RemoveListener(h2, 0x238de9c, -9999);
  if (mpXHTMLFrameSet.mpObject) {
    mpXHTMLFrameSet.mpObject->Shutdown();
    if (mpXHTMLFrameSet.mpObject) {
      cXHTMLFrameSet* p = mpXHTMLFrameSet.mpObject;
      mpXHTMLFrameSet.mpObject = 0;
      p->Release();
    }
  }
  IWindow* w = mLayout.FindWindowByID(0xffffffff, true);
  if (w) {
    if (gpUIRoot->mpState->mbModalCursor) {
      FUN_00809950(0);
      FUN_00809930(false);
    }
    w->RemoveWinProc(this);
    SPUIHelpers::EndModal(w, 0, true);
  }
  MessageServer()->PostMSG(0x5dd52c7, 0, 0);
  mLayout.Shutdown(true);
}

// @ 0x00620470
bool cRegistrationDialog::HandleMessage(uint32_t messageID, void* pMessage) {
  if (messageID == 0x44db12e) {
    if (mbAutoExitAfterLogin && pMessage) {
      End();
      return false;
    }
  } else if (messageID == 0x238de9c) {
    End();
  }
  return false;
}

// @ 0x006205f0
void cRegistrationDialog::ConfirmLogin() {
  IAuthManager* auth = AuthManager();
  auth->ShowLoginDialog(true);
  auth->SavePrefs();
  if (gpUIRoot->mpState->mbModalCursor) {
    FUN_00809950(0);
    FUN_00809930(false);
  }
  MessageServer()->PostMSG(0x5b98f52, 0, 0);
  End();
}

// @ 0x00620740
cRegistrationDialog::cRegistrationDialog() : mbAutoExitAfterLogin(true), mbEnterPressed(false), mbFlag65(false), mState(0) {}

// @ 0x006207f0
cRegistrationDialog::~cRegistrationDialog() {}

// @ 0x006208c0
bool cRegistrationDialog::Show2(bool bEnterPressed) {
  Messaging::IHandler* h1 = static_cast<Messaging::IHandler*>(this);
  MessageServer()->RegisterHandler(h1, 0x44db12e);
  Messaging::IHandler* h2 = static_cast<Messaging::IHandler*>(this);
  MessageServer()->RegisterHandler(h2, 0x238de9c);
  {
    ResourceKey key = ResourceKey::Make(0x34a6339e, 0x510a95b, 0x40464100);
    if (!mLayout.Init(key, 0, 0x5b598f7)) return false;
  }
  mbFlag65 = bEnterPressed;
  IWindow* w = mLayout.FindWindowByID(0xffffffff, true);
  if (!w) return false;
  w->AddWinProc(this);
  mpXHTMLFrameSet = new ("Pollinator", 0, 0, 0, 0) cXHTMLFrameSet((void*)0x623f40);
  mpXHTMLFrameSet.mpObject->SetEventIDs(0x1002, 0x1006, 0x1003, 0x1024);
  if (mpXHTMLFrameSet.mpObject->Attach(w, 0x451a4c0)) {
    MessageServer()->PostMSG(0x5bd6378, 0, 0);
    SPUIHelpers::BeginModal(w, 0, true);
    if (gpUIRoot->mpState->mbModalCursor) {
      FUN_00809950(w);
      FUN_00809930(true);
      IWindow* w2 = mLayout.FindWindowByID(0x6555818, true);
      if (w2) w2->SetFlag(1, false);
    }
    IWindow* w3 = mLayout.FindWindowByID(0x519d9b8, true);
    if (w3) w3->SetFlag(1, true);
    IWindow* w4 = mLayout.FindWindowByID(0x65d20a8, true);
    if (w4) w4->SetFlag(1, false);
    AutoSizeButtons();
    string16 url;
    GetURL(0x538766b, url);
    mpXHTMLFrameSet.mpObject->HandleLocationChange(0, url.mpBegin, gLocationChangeParam, 0);
    return true;
  }
  if (mpXHTMLFrameSet.mpObject) {
    cXHTMLFrameSet* p = mpXHTMLFrameSet.mpObject;
    mpXHTMLFrameSet.mpObject = 0;
    p->Release();
  }
  return false;
}

// @ 0x00620b30
void cRegistrationDialog::FormParamCallback(const wchar_t* name, const wchar_t* value, cRegistrationDialog* self) {
  if (name) {
    if (_wcsicmp(name, gParamUserName) == 0) {
      self->mUserName.assign(value);
    } else if (_wcsicmp(name, gParamScreenName) == 0) {
      self->mScreenName = value;
    } else if (_wcsicmp(name, gParamPassword) == 0) {
      self->mPassword = value;
    }
  }
}

}  // namespace Pollen
}  // namespace SP

// ---------------------------------------------------------------------------------------------
namespace eastl {
struct intrusive_list_node {
  intrusive_list_node* mpNext;
  intrusive_list_node* mpPrev;
};
struct intrusive_list_base {
  intrusive_list_node mAnchor;
  ~intrusive_list_base();
};
// @ 0x00620230
intrusive_list_base::~intrusive_list_base() {
  intrusive_list_node* p = mAnchor.mpNext;
  while (p != &mAnchor) {
    intrusive_list_node* pNext = p->mpNext;
    p->mpPrev = 0;
    p->mpNext = 0;
    p = pNext;
  }
  mAnchor.mpPrev = 0;
  mAnchor.mpNext = 0;
}
}  // namespace eastl

namespace SP {
namespace Pollen {
using namespace EA;
using namespace EA::UTFWin;

// ---- cancel-confirmation dialog (layout at +0xc) ------------------------------------------------
class cCancelConfirmationDialog : public CustomWinProc {
 public:
  cCancelConfirmationDialog();
  virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg);
  bool Init();                                   // 0x00620270
  void ShowModal(IModalWindowCallback* pCallback);  // 0x00620020
  cSPUILayout mLayout;                           // +0xc
};

// @ 0x00620020
void cCancelConfirmationDialog::ShowModal(IModalWindowCallback* pCallback) {
  IWindow* w = mLayout.FindWindowByID(0x65cf488, true);
  if (w) SPUIHelpers::BeginModal(w, pCallback, true);
}

// @ 0x00620270
bool cCancelConfirmationDialog::Init() {
  ResourceKey key = ResourceKey::Make(0x6b5d940, 0x510a95b, 0x40464100);
  if (!mLayout.Init(key, 1, 0x5b598f7)) return false;
  IWindow* wOk = mLayout.FindWindowByID(0xfffffff1, true);
  if (wOk) {
    SPUIHelpers::AutoSizeWindowForText(wOk, true, false);
    IWindow* wCancel = mLayout.FindWindowByID(0xfffffff2, true);
    if (wCancel) {
      SPUIHelpers::AutoSizeWindowForText(wCancel, false, false);
      const float* rc = wCancel->GetArea();
      float width = rc[2] - rc[0];
      const float* rcOk = wOk->GetArea();
      float x = rcOk[0] - width;
      wCancel->SetPosition(x, rc[1]);
    }
  }
  IWindow* w = mLayout.FindWindowByID(0x65cf488, true);
  if (w) {
    w->AddWinProc(this);
    return true;
  }
  mLayout.Shutdown(true);
  return false;
}

// @ 0x006204b0
cCancelConfirmationDialog::cCancelConfirmationDialog() {}

// @ 0x006204e0
bool cCancelConfirmationDialog::HandleUIMessage(IWindow* pWindow, const Message& msg) {
  if (pWindow->GetControlID() == 0x65cf488 && msg.mEventType == 0x287259f6) {
    if (msg.mpSource->GetControlID() == 0xfffffff1 || msg.mpSource->GetControlID() == 0xfffffff2) {
      IAuthManager* auth = AuthManager();
      if (msg.mpSource->GetControlID() == 0xfffffff1) {
        IWindow* w = mLayout.FindWindowByID(0x65cf570, true);
        if (w) auth->SetRememberPassword(!((w->GetFlags() >> 2) & 1));
      }
      if (msg.mpSource->GetControlID() == 0xfffffff2) auth->FinishLogin(true);
      IWindow* w2 = mLayout.FindWindowByID(0x65cf488, true);
      if (w2) {
        SPUIHelpers::EndModal(w2, msg.mpSource->GetControlID(), true);
        w2->RemoveWinProc(this);
      }
      mLayout.Shutdown(true);
      return true;
    }
  }
  return false;
}

// @ 0x00620660: compiler-generated scalar deleting destructor of cCancelConfirmationDialog

// ---- XHTML DOM helper -------------------------------------------------------------------------
struct DomHook {  // eastl::intrusive_list_node
  DomHook* mpNext;
  DomHook* mpPrev;
};
struct DomNodeBase {
  virtual void pv0();
};
struct DomElement;
struct DomNode : DomNodeBase, DomHook {  // hook at +4
  int Type();              // 0x00fc7e50 (EA::XHTML::DOM::Node::Type)
  DomElement* AsElement();  // 0x008e52f0
};
struct DomNodeList {
  uint32_t pad;
  DomHook mAnchor;  // +4 relative to the list at element+0x14
};
struct DomElement : DomNode {
  uint32_t pad1[(0x14 - 0xc) / 4];
  DomNodeList mChildren;  // +0x14
  uint32_t pad2[(0x28 - 0x20) / 4];
  int mTag;  // +0x28
};

struct XHTMLHandlerBase {
  XHTMLHandlerBase(void* a, void* b, void* c);  // 0x008e4400
  virtual ~XHTMLHandlerBase();
  uint32_t pad[0x44 / 4 - 1];
};
class cXHTMLRegistrationHandler : public XHTMLHandlerBase {
 public:
  cXHTMLRegistrationHandler(void* a, void* b, void* c);
  DomElement* FindFirstTaggedElement(DomElement* e);  // 0x00620690
  uint32_t mUnk44;  // +0x44
};

// @ 0x006206f0
cXHTMLRegistrationHandler::cXHTMLRegistrationHandler(void* a, void* b, void* c) : XHTMLHandlerBase(a, b, c), mUnk44(0) {}

// @ 0x00620690
DomElement* cXHTMLRegistrationHandler::FindFirstTaggedElement(DomElement* e) {
  if (e->mTag != 0x15) {
    DomNode* n = static_cast<DomNode*>(e->mChildren.mAnchor.mpNext);
    DomNode* end = (DomNode*)&e->mChildren;
    while (n != end) {
      if (n->Type() == 1) {
        DomElement* r = FindFirstTaggedElement(n->AsElement());
        if (r) return r;
      }
      n = static_cast<DomNode*>(n->mpNext);
    }
    return 0;
  }
  return e;
}

// ---- Pollinator work items ----------------------------------------------------------------------
struct WorkItem {
  void* mpFunc;     // +0
  void* mpContext;  // +4
  uint32_t pad[4];
  int mPriority;  // +0x18
  void SetCallback(void* fn, void* ctx) {
    mpFunc = fn;
    mpContext = ctx;
  }
  void Release();  // 0x00690120
  void Submit();   // 0x006909b0
};
struct IWorkScheduler {
  PV(0) PV(1) PV(2) PV(3)
  virtual bool CreateItem(WorkItem** ppItem);  // +0x10
};
IWorkScheduler* GetWorkScheduler();  // 0x0068f4d0
void SubmitWorkItem(WorkItem* p);    // 0x006b47a0
struct WorkItemRef {
  WorkItem* mp;
  WorkItemRef() : mp(0) {}
  ~WorkItemRef() {
    if (mp) mp->Release();
  }
  WorkItem*& AsOutParam() {
    if (mp) {
      WorkItem* p = mp;
      mp = 0;
      p->Release();
    }
    return mp;
  }
};
void WorkFn_61fad0();
void WorkFn_61fae0();

struct IPropertyValue {
  uint8_t pad[0x12];
  uint16_t mType;  // +0x12
  uint32_t* GetUInt();  // 0x0041ea00
};
struct IPropertyList {
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, IPropertyValue** ppValue);  // +0x24
};
struct IPropertyManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void GetPropertyList(uint32_t group, uint32_t id, IPropertyList** ppList);  // +0x2c
};
IPropertyManager* PropertyManager();  // 0x0067de30
bool FUN_00688830(uint32_t id, void* dst, int flag);

struct PollTimerBase {
  void SetCallback(void* fn, void* obj, int flag);  // 0x00929da0
  void SetPeriod(uint32_t ms);                   // 0x00929bc0
  uint32_t pad[0x24 / 4];
};
class cPollinatorPoller : public PollTimerBase {
 public:
  bool Init();  // 0x0061fbd0
  void* mpSelf;       // +0x24
  void* mpCallback;   // +0x28
  uint32_t mUnk2c, mUnk30, mUnk34;
  uint32_t mHandler[(0x6c - 0x38) / 4];  // +0x38: IHandler subobject
  uint32_t mnTimeoutSecs;                 // +0x6c
  uint32_t mBuffer[4];                    // +0x70
};
void PollerCallback();  // 0x0061fbc0

// @ 0x0061fbd0
bool cPollinatorPoller::Init() {
  mpCallback = (void*)PollerCallback;
  mUnk2c = 0;
  mUnk30 = 0;
  mUnk34 = 0;
  mpSelf = this;
  SetCallback((void*)0x00ed1cf0, this, 0);
  AutoRefCount<IPropertyList> props;
  PropertyManager()->GetPropertyList(0x21d4b8c, 0x21403e6, &props.AsOutParam());
  if (props.mpObject) {
    IPropertyValue* value;
    if (props.mpObject->GetProperty(0x609d3a2, &value) && value->mType == 10) mnTimeoutSecs = *value->GetUInt();
  }
  uint32_t secs = 300;
  if (props.mpObject) {
    IPropertyValue* value;
    if (props.mpObject->GetProperty(0x609d3d5, &value) && value->mType == 10) secs = *value->GetUInt();
  }
  SetPeriod(secs * 1000);
  if (FUN_00688830(0x60ba02f, mBuffer, 0)) {
    EA::Messaging::IHandler* h = (EA::Messaging::IHandler*)mHandler;
    MessageServer()->AddListener(h, 0x44db12e);
    MessageServer()->AddListener(h, 0x60ba744);
    MessageServer()->AddListener(h, 0x685f4af);
    WorkItemRef item;
    if (GetWorkScheduler()->CreateItem(&item.AsOutParam())) {
      item.mp->mpFunc = (void*)WorkFn_61fad0;
      item.mp->mpContext = this;
      item.mp->mPriority = 4;
      SubmitWorkItem(item.mp);
      item.mp->Submit();
      return true;
    }
  }
  return false;
}

// ---- queueing a request object as a work item ----------------------------------------------------
struct PollEvent {
  uint32_t pad[4];
  uint8_t mFlags;  // +0x10 (bit 0x20: handled)
  uint8_t pad11;
  uint16_t mType;  // +0x12
};
struct RequestObj {  // 0x38 bytes
  uint32_t pad[(0x38 - 4) / 4];
  RequestObj(void* a1, PollEvent* ev);                            // 0x0061e250
  RequestObj(void* a1, void* a2, void* a3, PollEvent* ev);        // 0x0061e2c0
  virtual int AddRef();
  virtual int Release();
};
void __stdcall RegisterRequestObj(RequestObj* p);  // 0x0068f9b0
class cPollinatorJobHost {
 public:
  bool QueueEvent(void* a1, PollEvent* ev);                                // 0x0061fdb0
  bool QueueEvent4(void* a1, void* a2, void* a3, PollEvent* ev);           // 0x0061fee0
};

// @ 0x0061fdb0
bool cPollinatorJobHost::QueueEvent(void* a1, PollEvent* ev) {
  if (!(ev->mFlags & 0x20)) {
    switch (ev->mType) {
      case 0: case 2: case 3: case 4: case 0xf: case 0x10: case 0x11: case 0x14:
        break;
      default: {
        AutoRefCount<RequestObj> obj(new ("Pollinator", 0, 0, 0, 0) RequestObj(a1, ev));
        if (obj.mpObject) {
          WorkItemRef item;
          if (GetWorkScheduler()->CreateItem(&item.AsOutParam())) {
            RegisterRequestObj(obj.mpObject);
            item.mp->mpFunc = (void*)WorkFn_61fae0;
            item.mp->mpContext = this;
            item.mp->mPriority = 4;
            SubmitWorkItem(item.mp);
            item.mp->Submit();
            return true;
          }
        }
      }
    }
  }
  return false;
}

// @ 0x0061fee0
bool cPollinatorJobHost::QueueEvent4(void* a1, void* a2, void* a3, PollEvent* ev) {
  if (!(ev->mFlags & 0x20)) {
    switch (ev->mType) {
      case 0: case 2: case 3: case 4: case 0xf: case 0x10: case 0x11: case 0x14:
        break;
      default: {
        AutoRefCount<RequestObj> obj(new ("Pollinator", 0, 0, 0, 0) RequestObj(a1, a2, a3, ev));
        if (obj.mpObject) {
          WorkItemRef item;
          if (GetWorkScheduler()->CreateItem(&item.AsOutParam())) {
            RegisterRequestObj(obj.mpObject);
            item.mp->mpFunc = (void*)WorkFn_61fae0;
            item.mp->mpContext = this;
            item.mp->mPriority = 4;
            SubmitWorkItem(item.mp);
            item.mp->Submit();
            return true;
          }
        }
      }
    }
  }
  return false;
}
}  // namespace Pollen
}  // namespace SP
