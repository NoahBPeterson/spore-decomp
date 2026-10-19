// Slice s00823a00 -- SP::cSPUIPropertyEditor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct IMessageServer;
struct cPropertyUI;

struct IWindow {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual IWindow* GetParent();          // slot 4 (+0x10)
  virtual void s5(); virtual void s6();
  virtual unsigned int GetID();    // slot 7 (+0x1c)
};

struct IPropertyEntry { char pad[0x12]; unsigned short mnType; };
struct IPropertyList {
  virtual int AddRef();   // slot 0
  virtual int Release();  // slot 1
  virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
  virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
  virtual IPropertyEntry* GetProperty(unsigned int id);   // slot 10 (+0x28)
};
struct IPropertyManager {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void s8(); virtual void s9(); virtual void s10();
  virtual void GetPropertyList(int inst, int group, IPropertyList** out);  // slot 11 (+0x2c)
};
IPropertyManager* PropertyManager();   // 0x0067de30

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
  char pad2[0x64 - 0x44 - sizeof(cSPUILayout)];
  void* mButtonBegin;         // +0x64
  char padEnd[0x190 - 0x68];
  cPropertyUI();
  bool Init(const wchar_t* name, unsigned int flags);
  void PopulateGroupsGrid();
  void ProcessTextChange(IWindow* w);
  void ModifyInt32(IWindow* w, bool b);
  void ModifyUInt32(IWindow* w, bool b);
  void ModifyFloat(IWindow* w, bool b);
  void ModifyString16(IWindow* w, bool b);
  void ModifyString(IWindow* w, bool b);
  void ModifyResourceKey(IWindow* w, bool b);
  void ModifyVec2(IWindow* w, bool b);
  void ModifyVec3(IWindow* w, bool b);
  void ModifyVec4(IWindow* w, bool b);
  void ModifyRGB(IWindow* w, bool b);
  void ModifyRGBA(IWindow* w, bool b);
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

// @ 0x00823b50
void cPropertyUI::ProcessTextChange(IWindow* w) {
  void* btn = mButtonBegin;
  IWindow* t = w->GetParent();
  IWindow* o = (t != (IWindow*)btn) ? w->GetParent() : w;
  unsigned int id = o->GetID();
  IPropertyList* list = 0;
  IPropertyManager* pm = PropertyManager();
  if (list) {
    IPropertyList* old = list;
    list = 0;
    old->Release();
  }
  pm->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, &list);
  unsigned short type = list->GetProperty(id)->mnType;
  if (type == 9) ModifyInt32(w, false);
  else if (type == 0xa) ModifyUInt32(w, false);
  else if (type == 0xd) ModifyFloat(w, false);
  else if (type == 0x13) ModifyString16(w, false);
  else if (type == 0x12) ModifyString(w, false);
  else if (type == 0x20) ModifyResourceKey(w, false);
  else if (type == 0x30) ModifyVec2(w->GetParent(), false);
  else if (type == 0x31) ModifyVec3(w->GetParent(), false);
  else if (type == 0x33) ModifyVec4(w->GetParent(), false);
  else if (type == 0x32) ModifyRGB(w->GetParent(), false);
  else if (type == 0x34) ModifyRGBA(w->GetParent(), false);
  else {
    unsigned int u = type;
    if (u == 0x80000009) ModifyInt32(w->GetParent(), true);
    else if (u == 0x8000000a) ModifyUInt32(w->GetParent(), true);
    else if (u == 0x8000000d) ModifyFloat(w->GetParent(), true);
    else if (u == 0x80000013) ModifyString16(w->GetParent(), true);
    else if (u == 0x80000012) ModifyString(w->GetParent(), true);
    else if (u == 0x80000020) ModifyResourceKey(w->GetParent(), true);
    else if (u == 0x80000030) ModifyVec2(w->GetParent(), true);
    else if (u == 0x80000031) ModifyVec3(w->GetParent(), true);
    else if (u == 0x80000033) ModifyVec4(w->GetParent(), true);
    else if (u == 0x80000032) ModifyRGB(w->GetParent(), true);
    else if (u == 0x80000034) ModifyRGBA(w->GetParent(), true);
  }
  if (list) list->Release();
}
