// Slice s00825930 -- SP::cPropertyUI row builders + destructor.
// Flags: /O2 /MD /Gy /EHsc /arch:SSE /fp:fast (set per-function in manifest.txt)
// Retail layout of cPropertyUI differs from the 2008 PDB (+0xc after the layout member, +4 per vector).
#include "types.h"
#include <stddef.h>
#include <new>

struct IWinW {
  virtual void AddRef();
  virtual void Release();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual unsigned GetID();  // slot 7
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void s12();
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void s16();
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual void SetA(unsigned a);  // slot 20
  virtual void SetB(unsigned b);  // slot 21
  virtual void s22();
  virtual void s23();
  virtual void SetArea(const float* r);  // slot 24
  virtual void SetPos(float x, float y);  // slot 25
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void SetText(const void* t);  // slot 32
  virtual void SetHash(unsigned h);  // slot 33
  virtual void s34();
  virtual void s35();
  virtual void V36();  // slot 36
  virtual void s37();
  virtual void s38();
  virtual void s39();
  virtual void s40();
  virtual void s41();
  virtual void s42();
  virtual void s43();
  virtual void s44();
  virtual void s45();
  virtual void s46();
  virtual void s47();
  virtual void s48();
  virtual void s49();
  virtual void s50();
  virtual void s51();
  virtual void s52();
  virtual void s53();
  virtual void AddChild(IWinW* w);  // slot 54
};
struct ITE {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual IWinW* GetWin();  // slot 4
  virtual void s5();
  virtual void V6(const void* s);  // slot 6
  virtual void s7();
  virtual void SetColor(int i, unsigned c);  // slot 8
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void V12(float f);  // slot 12
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void V16(int a);  // slot 16
  virtual void V17(int a, int b);  // slot 17
  virtual void s18();
  virtual void s19();
  virtual void s20();
  virtual void s21();
  virtual void s22();
  virtual void s23();
  virtual void s24();
  virtual void s25();
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void s32();
  virtual void s33();
  virtual void s34();
  virtual void s35();
  virtual void s36();
  virtual void V37(int a, int b);  // slot 37
  virtual void s38();
  virtual void s39();
  virtual void s40();
  virtual void s41();
  virtual void s42();
  virtual void s43();
  virtual void s44();
  virtual void s45();
  virtual void s46();
  virtual void s47();
  virtual void V48(int a);  // slot 48
};
struct IBtn {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual IWinW* GetWin();  // slot 4
};
struct IGrid {
  virtual void AddRef();  // slot 0
  virtual void Release();  // slot 1
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void s12();
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void s16();
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual void s20();
  virtual void s21();
  virtual void s22();
  virtual void s23();
  virtual void s24();
  virtual void s25();
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void s32();
  virtual void s33();
  virtual void s34();
  virtual void s35();
  virtual void s36();
  virtual void s37();
  virtual void s38();
  virtual void s39();
  virtual void s40();
  virtual void s41();
  virtual void s42();
  virtual void s43();
  virtual void s44();
  virtual void s45();
  virtual void s46();
  virtual void s47();
  virtual void s48();
  virtual void s49();
  virtual void s50();
  virtual void s51();
  virtual void s52();
  virtual void s53();
  virtual void s54();
  virtual void s55();
  virtual void s56();
  virtual void s57();
  virtual void s58();
  virtual void s59();
  virtual void s60();
  virtual void s61();
  virtual void s62();
  virtual void s63();
  virtual void s64();
  virtual void s65();
  virtual void s66();
  virtual void s67();
  virtual void s68();
  virtual void s69();
  virtual void s70();
  virtual void s71();
  virtual void s72();
  virtual void s73();
  virtual void s74();
  virtual void s75();
  virtual void s76();
  virtual void s77();
  virtual void s78();
  virtual void s79();
  virtual void s80();
  virtual void s81();
  virtual void s82();
  virtual void s83();
  virtual void s84();
  virtual void s85();
  virtual void s86();
  virtual void s87();
  virtual void s88();
  virtual void s89();
  virtual void s90();
  virtual void V91();  // slot 91
};

extern void* GetAllocator();                                                      // 0x009512c0
extern void* AllocAligned(unsigned size, int align, const char* name, void* a);   // 0x009512d0
extern IBtn* CreateDefaultButton(int a, int b, int c);                            // WinButton::CreateDefault
extern const char kTextEditName[];                                                // "UI/UI/WinTextEdit"
extern const char kStyleStr[];                                                    // 0x015a4361
extern const char kBtnTextA[];                                                    // 0x01419de8
extern const char kBtnTextB[];                                                    // 0x013faf54
extern const char kSprintfFmt[];                                                  // 0x013fcac8
extern const float kQuarter;                                                      // 0x013eb8a0
extern const float kRowAdvance;                                                   // 0x01419dd4 (210)
extern const float kRect2W, kRect2H;                                              // 0x13eecd8 / 0x1419d38
extern const float kRect1W;                                                       // 0x01419d40 (60)
extern const float kEditW, kEditH;                                                // 0x01477fbc / 0x013eecd8
extern const float kSpin80;                                                       // 0x014763c4
extern const float kBtn2Y;                                                        // 0x0140c7a4
extern const float kAdv30;                                                        // 0x014853bc
extern char kEmptyStr[2];                                                         // 0x01667bac

struct WinTextEdit;  // EA::UTFWinControls::WinTextEdit, 0x658 bytes; ITE sub-object at +0x20c
struct WinTextEditMem {
  WinTextEdit* Construct();  // 0x0098c110 (thiscall, returns this)
};

struct EString {  // eastl::string (narrow)
  char* b;
  char* e;
  char* cap;
  EString() : b(kEmptyStr), e(kEmptyStr), cap(kEmptyStr + 1) {}
  void sprintf(const char* fmt, ...);                                             // 0x00472fe0 (cdecl)
};
struct EString16 {  // eastl::string16
  char* b;
  char* e;
  char* cap;
  ~EString16() {
    if ((int)(((unsigned)cap - (unsigned)b) & 0xfffffffe) > 2 && b) operator delete(b);
  }
};
extern EString16* ConvertToString16(EString16* out, const EString* in);          // 0x0093c6d0

template <class T> struct SpVec {  // eastl::vector<T*, sp_vector_allocator>, 0x14 bytes
  T** b;
  T** e;
  T** cap;
  unsigned pad[2];
  unsigned size() const {
    if (b == e) return 0;
    return (unsigned)(e - b);
  }
  void Grow(T** pos, T** val);
  void push_back(T* v) {
    T* tmp = v;
    T** at = e;
    if (at < cap) {
      e = at + 1;
      if (at) *at = v;
    } else {
      Grow(at, &tmp);
    }
  }
  ~SpVec() {
    if (b && ((int*)b)[-1]) operator delete(b);
  }
};

template <class T> struct AutoRef {
  T* p;
  AutoRef& operator=(T* o) {
    if (p != o) {
      T* old = p;
      if (o) o->AddRef();
      p = o;
      if (old) old->Release();
    }
    return *this;
  }
  ~AutoRef() {
    if (p) p->Release();
  }
};

struct HashMapBase {  // eastl::hash_map<unsigned, T*>, 0x20 bytes
  unsigned pad0;
  void* buckets;      // +4
  unsigned nbuckets;  // +8
  unsigned count;     // +0xc
  unsigned pad[4];
  void DoFreeNodes(void* b, unsigned n);  // 0x00693230
  void clear() {
    DoFreeNodes(buckets, nbuckets);
    count = 0;
  }
  ~HashMapBase() {
    clear();
    if (nbuckets > 1) operator delete(buckets);
  }
};
struct TEMap : HashMapBase {
  ITE*& operator[](const unsigned& k);  // 0x00820af0
};
struct BtnMap : HashMapBase {};

struct cSPUILayout {
  unsigned pad[6];
  ~cSPUILayout();  // 0x00811fe0
};

struct IWinProc {
  virtual ~IWinProc() {}
  virtual void ip0();
  virtual void ip1();
  virtual void ip2();
};
struct RefCountVTemplate {
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  int mRefCount;
};

struct cPropertyUI : IWinProc, RefCountVTemplate {
  unsigned mCurrentGroupID;     // +0xc
  unsigned mCurrentInstanceID;  // +0x10
  float mCurrentX;              // +0x14
  float mCurrentY;              // +0x18
  float mCurrentWindowX;        // +0x1c
  float mCurrentWindowY;        // +0x20
  float mPreviousScrollVal;     // +0x24
  float mRefreshScrollVal;      // +0x28
  float mScrollRatio;           // +0x2c
  float mScrollHeight;          // +0x30
  unsigned mSpinnerButtonID;    // +0x34
  float mFloatIncrement;        // +0x38
  unsigned mIntIncrement;       // +0x3c
  bool returnPressed;           // +0x40
  cSPUILayout mLayout;          // +0x44
  AutoRef<IBtn> mEditorDialog;  // +0x5c
  AutoRef<IBtn> mChooserDialog; // +0x60
  AutoRef<IWinW> mHolderWindow; // +0x64
  AutoRef<IBtn> mScrollbar;     // +0x68
  AutoRef<IBtn> mTitleText;     // +0x6c
  SpVec<IBtn> mButton;          // +0x70
  SpVec<IBtn> mToggleButton;    // +0x84
  SpVec<IBtn> mComboBox;        // +0x98
  SpVec<IBtn> mGrid;            // +0xac
  SpVec<IBtn> mSpinner;         // +0xc0
  SpVec<IBtn> mSlider;          // +0xd4
  SpVec<IBtn> mText;            // +0xe8
  SpVec<ITE> mTextEdit;         // +0xfc
  SpVec<IWinW> mSubWindow;      // +0x110
  AutoRef<IBtn> mDialog;        // +0x124
  AutoRef<IGrid> mGroupsGrid;   // +0x128
  AutoRef<IGrid> mPropsGrid;    // +0x12c
  TEMap mPropToTextEditMap;     // +0x130
  TEMap mSpinnerToTextEditMap;  // +0x150
  BtnMap mPropToToggleButtonMap;// +0x170

  void ClearAll();  // 0x00824c20
  unsigned AddSpinnerRow(unsigned id, float value, IWinW* parent);                    // 0x00825930
  unsigned AddTextEditRowA(unsigned id, const void* text, IWinW* parent);             // 0x00825fc0
  unsigned AddTextEditRowB(unsigned id, const void* text, IWinW* parent);             // 0x00826290
  virtual ~cPropertyUI();                                                             // 0x00826560
};

typedef char chk_off_5c[offsetof(cPropertyUI, mEditorDialog) == 0x5c ? 1 : -1];
typedef char chk_off_70[offsetof(cPropertyUI, mButton) == 0x70 ? 1 : -1];
typedef char chk_off_fc[offsetof(cPropertyUI, mTextEdit) == 0xfc ? 1 : -1];
typedef char chk_off_128[offsetof(cPropertyUI, mGroupsGrid) == 0x128 ? 1 : -1];
typedef char chk_off_170[offsetof(cPropertyUI, mPropToToggleButtonMap) == 0x170 ? 1 : -1];
typedef char chk_off_14[offsetof(cPropertyUI, mCurrentX) == 0x14 ? 1 : -1];

// @ 0x00825930
unsigned cPropertyUI::AddSpinnerRow(unsigned id, float value, IWinW* parent) {
  unsigned idx = mTextEdit.size();
  unsigned n0 = mButton.size();
  unsigned n1 = (mButton.b == mButton.e) ? 1 : (unsigned)(mButton.e - mButton.b) + 1;
  IBtn* b1 = CreateDefaultButton(1, 0, 0);
  if (b1) b1->AddRef();
  IBtn* b2 = CreateDefaultButton(1, 0, 0);
  if (b2) b2->AddRef();
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kRect1W, kRect2W};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  EString s;
  s.sprintf(kSprintfFmt, (double)value);
  IWinW* tw = te->GetWin();
  {
    EString16 out16;
    tw->SetText(ConvertToString16(&out16, &s)->b);
  }
  te->V12(kQuarter);
  te->V37(0, 0);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  unsigned pid;
  unsigned* kp;
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
    te->GetWin()->SetB(id);
    kp = &id;
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    pid = parent->GetID();
    te->GetWin()->SetB(pid);
    kp = &pid;
  }
  mPropToTextEditMap[*kp] = te;
  te->GetWin()->V36();
  te->GetWin()->SetA(id);
  mCurrentX += kSpin80;
  float r2[4] = {0.0f, 0.0f, kRect2W, kRect2H};
  b1->GetWin()->SetArea(r2);
  b2->GetWin()->SetArea(r2);
  b1->GetWin()->SetHash(0xaf14b67e);
  b2->GetWin()->SetHash(0xaf14b67e);
  b1->GetWin()->SetText(kBtnTextA);
  b2->GetWin()->SetText(kBtnTextB);
  b1->GetWin()->SetA(0);
  b1->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te;
  ++mSpinnerButtonID;
  b2->GetWin()->SetA(0);
  b2->GetWin()->SetB(mSpinnerButtonID);
  mSpinnerToTextEditMap[mSpinnerButtonID] = te;
  ++mSpinnerButtonID;
  b1->GetWin()->SetPos(kSpin80, 0.0f);
  b2->GetWin()->SetPos(kSpin80, kBtn2Y);
  mCurrentX += kAdv30;
  mTextEdit.push_back(te);
  mButton.push_back(b1);
  mButton.push_back(b2);
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n0]->GetWin());
  mTextEdit.b[idx]->GetWin()->AddChild(mButton.b[n1]->GetWin());
  te->Release();
  b2->Release();
  b1->Release();
  return idx;
}

// @ 0x00825fc0
unsigned cPropertyUI::AddTextEditRowA(unsigned id, const void* text, IWinW* parent) {
  unsigned idx = (mTextEdit.b == mTextEdit.e) ? 0 : (unsigned)(mTextEdit.e - mTextEdit.b);
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kEditW, kEditH};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  te->GetWin()->SetText(text);
  te->V12(kQuarter);
  te->V37(0, 0);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  te->GetWin()->V36();
  te->GetWin()->SetA(id);
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    id = parent->GetID();
  }
  te->GetWin()->SetB(id);
  mPropToTextEditMap[id] = te;
  mTextEdit.push_back(te);
  mCurrentX += kRowAdvance;
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  te->Release();
  return idx;
}

// @ 0x00826290
unsigned cPropertyUI::AddTextEditRowB(unsigned id, const void* text, IWinW* parent) {
  unsigned idx = mTextEdit.size();
  void* mem = AllocAligned(0x658, 8, kTextEditName, GetAllocator());
  WinTextEdit* w = mem ? ((WinTextEditMem*)mem)->Construct() : 0;
  ITE* te = w ? (ITE*)((char*)w + 0x20c) : 0;
  if (te) te->AddRef();
  float r1[4] = {0.0f, 0.0f, kEditW, kEditH};
  te->GetWin()->SetArea(r1);
  te->SetColor(0, 0xff000000);
  te->SetColor(1, 0xffffffff);
  te->SetColor(2, 0xff777777);
  te->SetColor(3, 0xffffffff);
  te->SetColor(4, 0xffffffff);
  te->SetColor(5, 0xff43a2ff);
  te->SetColor(6, 0xff000000);
  te->SetColor(7, 0xff000000);
  te->V6(kStyleStr);
  te->V12(kQuarter);
  te->V37(0, 0);
  te->GetWin()->SetText(text);
  te->V17(0x54, 1);
  te->V16(0);
  te->V48(10);
  te->GetWin()->SetA(id);
  te->GetWin()->V36();
  mTextEdit.push_back(te);
  if (parent == mHolderWindow.p) {
    te->GetWin()->SetPos(mCurrentX, mCurrentY);
  } else {
    te->GetWin()->SetPos(mCurrentX, 0.0f);
    id = parent->GetID();
  }
  te->GetWin()->SetB(id);
  mPropToTextEditMap[id] = te;
  mCurrentX += kRowAdvance;
  parent->AddChild(mTextEdit.b[idx]->GetWin());
  te->Release();
  return idx;
}

// @ 0x00826560
cPropertyUI::~cPropertyUI() {
  if (mEditorDialog.p) mEditorDialog = 0;
  if (mScrollbar.p) mScrollbar = 0;
  if (mHolderWindow.p) mHolderWindow = 0;
  if (mChooserDialog.p) mChooserDialog = 0;
  if (mTitleText.p) mTitleText = 0;
  ClearAll();
  if (mGroupsGrid.p) {
    mGroupsGrid.p->V91();
    mGroupsGrid = 0;
  }
  if (mPropsGrid.p) {
    mPropsGrid.p->V91();
    mPropsGrid = 0;
  }
  if (mSpinnerToTextEditMap.count) mSpinnerToTextEditMap.clear();
  if (mPropToTextEditMap.count) mPropToTextEditMap.clear();
  if (mPropToToggleButtonMap.count) mPropToToggleButtonMap.clear();
}
