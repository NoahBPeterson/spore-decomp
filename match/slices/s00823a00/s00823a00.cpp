// Slice s00823a00 -- SP::cSPUIPropertyEditor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct IMessageServer;
struct cPropertyUI;

// ---- cSPUILayout (+0x44 inside cPropertyUI) ------------------------------
struct cSPUILayout {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  int pad8;                   // +0x8
  void SetVisibility(bool b);
};

// ---- cPropertyUI ---------------------------------------------------------
struct cPropertyUI {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  char pad0[8];               // +0x4 .. +0xb
  int mCurrentGroupID;        // +0xc
  int mCurrentInstanceID;     // +0x10
  char pad1[0x44 - 0x14];     // +0x14 .. +0x43
  cSPUILayout mLayout;        // +0x44
  char padEnd[0x190 - 0x44 - sizeof(cSPUILayout)];
  cPropertyUI();
  bool Init(const wchar_t* name, unsigned int flags);
  void PopulateGroupsGrid();
};

// ---- AutoRefCount --------------------------------------------------------
template <class T>
struct AutoRefCount {
  T* mpObject;
  T* operator->() const { return mpObject; }
  AutoRefCount& operator=(T* p) {
    T* old = mpObject;
    if (p != old) {
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
};

// ---- message server ------------------------------------------------------
struct IMessageServer {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void AddMessageHandler(void* handler, int id);  // slot 8 (+0x20)
};
IMessageServer* MessageServer();

// ---- _sAppProperties global ---------------------------------------------
struct AppPropsInner { char pad[0x54]; int f54; };
struct AppPropsOuter { char pad[0x3c]; AppPropsInner* p3c; };
extern AppPropsOuter* g_sAppProperties;

// ---- editor --------------------------------------------------------------
struct cSPUIPropertyEditor {
  virtual bool HandleMessage(int msg, void* arg);   // slot 0
  char pad0[8];                                     // +0x4 .. +0xb
  AutoRefCount<cPropertyUI> mPropUI;                // +0xc
  bool mInitialized;                                // +0x10
  void Init();
};

// 6-arg EA placement operator new.
void* operator new(unsigned int size, const char* name, int, int, int, int);

// ===========================================================================
// 00823a00  SP::cSPUIPropertyEditor::Init
// ===========================================================================
void cSPUIPropertyEditor::Init() {
  if (mInitialized) return;
  mPropUI = new ("UI/SPUIPropertyEditor/mPropUI", 0, 0, 0, 0) cPropertyUI();
  if (mPropUI->Init(L"PropertyEditor", 0x40464100)) {
    mPropUI->PopulateGroupsGrid();
    mInitialized = true;
    IMessageServer* ms = MessageServer();
    if (ms) {
      ms->AddMessageHandler(this, 0x15bbbf3);
      ms->AddMessageHandler(this, 0x16af8d8);
    }
  } else {
    mPropUI = 0;
  }
}

// ===========================================================================
// 00823ac0  SP::cSPUIPropertyEditor::HandleMessage
// ===========================================================================
bool cSPUIPropertyEditor::HandleMessage(int msg, void* arg) {
  switch (msg) {
    case 0x15bbbf3:
      if (((AppPropsInner*)g_sAppProperties->p3c)->f54 != 0) {
        if (mInitialized) {
          mPropUI->PopulateGroupsGrid();
          mPropUI->mLayout.SetVisibility(true);
          return true;
        }
        Init();
        mPropUI->mLayout.SetVisibility(true);
        return true;
      }
      mPropUI->mLayout.SetVisibility(false);
      return true;
    case 0x16af8d8:
      if (mPropUI->mCurrentGroupID != 0 && mPropUI->mCurrentInstanceID != 0)
        return true;
      return false;
  }
  return false;
}

// 0x00823b50  SP::cPropertyUI::ProcessTextChange -- not reconstructed (partial.txt)
