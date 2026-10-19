// src/game/Spui/SPUIMessageBox.cpp -- migrated from slice(s) s00816d40 by tools/migrate/rewrite.py
// Object file: Spui/SPUIMessageBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIMessageBox.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void Dealloc(void*);

// ---- items of slice s00816d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct cSPUILayout_s0081_6d40 {
    char  pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Shutdown(int arg);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void  Init(u32 a, int b, int c, const wchar_t* s);  // 0x00812160 (cSPUILayout::Init)
    ~cSPUILayout_s0081_6d40();
};
struct MsgBoxA {
    char        pad_00[0x0c];
    cSPUILayout_s0081_6d40 layout;   // +0x0c
    void* scalarDtor(u8 flags);
};
extern "C" void Dealloc(void*);
struct Rect4 {
  float left, top, right, bottom;
  Rect4() {}
  Rect4(const Rect4& o) : left(o.left), top(o.top), right(o.right), bottom(o.bottom) {}
};
struct IBtn {                                  // IWinButton
  virtual void b0();
  virtual void b1();
  virtual void b2();
  virtual void b3();
  virtual void b4();
  virtual void SizeToCaption(int arg);          // +0x14
  virtual void b6();
  virtual void b7();
  virtual void b8();
  virtual void b9();
  virtual void SetButtonStateFlag(int flag, bool on);  // +0x28
};
struct IText {                                 // object returned by Cast(0xf15f4bd)
  virtual void t0();
  virtual void t1();
  virtual void t2();
  virtual void t3();
  virtual void t4();
  virtual void t5();
  virtual void t6();
  virtual void SetFlagX(bool on);               // +0x1c
};
struct IWin {                                  // IWindow (vtable offsets from the card)
  virtual void w0();
  virtual void w1();
  virtual void w2();
  virtual IBtn* Cast(u32 typeID);                // +0x0c
  virtual void w4();
  virtual void w5();
  virtual void w6();
  virtual void w7();
  virtual void w8();
  virtual void w9();
  virtual u32 GetFlags();                          // +0x28
  virtual void w11();
  virtual void w12();
  virtual void w13();
  virtual const Rect4* GetRealArea();              // +0x38
  virtual void w15();
  virtual void w16();
  virtual void w17();
  virtual void w18();
  virtual void w19();
  virtual void w20();
  virtual void w21();
  virtual void w22();
  virtual void w23();
  virtual void w24();
  virtual void w25();
  virtual void w26();
  virtual void SetLayoutArea(const Rect4& r);      // +0x6c
  virtual void SetLayoutLocation(float x, float y); // +0x70
  virtual void SetLayoutSize(float w, float h);    // +0x74
  virtual void w30();
  virtual void SetFlag(u32 flag, bool on);         // +0x7c
  virtual void SetCaption(const wchar_t* text);    // +0x80
  virtual void w33();
  virtual void w34();
  virtual void w35();
  virtual void Invalidate();                       // +0x90
  virtual void Revalidate();                       // +0x94
  virtual void w38();
  virtual void w39();
  virtual void w40();
  virtual void w41();
  virtual void w42();
  virtual void w43();
  virtual void w44();
  virtual void w45();
  virtual void w46();
  virtual void w47();
  virtual void w48();
  virtual void w49();
  virtual void w50();
  virtual void w51();
  virtual void w52();
  virtual void w53();
  virtual void w54();
  virtual void w55();
  virtual void w56();
  virtual void w57();
  virtual void w58();
  virtual void w59();
  virtual IWin* FindWindowByID(u32 id, bool recurse); // +0xf0
  virtual void w61();
  virtual void w62();
  virtual void w63();
  virtual void w64();
  virtual void AddWinProc(void* proc);             // +0x104
};
struct ResourceKeyW {
  u32 instanceID, typeID, groupID;
  ResourceKeyW() {}
  ResourceKeyW(u32 i, u32 t, u32 g) : instanceID(i), typeID(t), groupID(g) {}
};
struct cStr {                                   // SP::cString (0x14 bytes)
  u32 m[5];
  cStr();                                       // 0x006b5060
  ~cStr();                                      // 0x006b5240
  const wchar_t* GetText();                     // 0x006b55c0
};
struct Prop {                                   // Property
  char pad_00[0x12];
  unsigned short mType;                         // +0x12
  bool* GetBool();                              // 0x0041e920 (thiscall)
  u32* GetUInt();                               // 0x0041ea00 (thiscall)
};
struct PropList {                               // PropertyList
  virtual void p0();
  virtual void Release();                       // +0x04
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
  virtual bool GetProperty(u32 id, Prop*& out); // +0x24
};
struct PropListRef {                            // AutoRefCount<PropertyList>
  PropList* mp;
  PropListRef() : mp(0) {}
  ~PropListRef() { if (mp) mp->Release(); }
  PropList** operator&() {
    if (mp) { PropList* t = mp; mp = 0; t->Release(); }
    return &mp;
  }
};
struct PropMgr {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
  virtual void m10();
  virtual bool GetPropertyList(u32 instanceID, u32 groupID, PropList** out);  // +0x2c
};
struct ConfigMgr {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
  virtual int GetOption(u32 id);                // +0x30
};
struct IWinMgrObj { virtual void x0(); virtual void* GetMainWindowBase(); };   // slot 1 (+0x04)
struct MainWinW { void AddElem(void* elem); };  // 0x00815370 (thiscall, ret 4)
struct LimitStopwatchW { void SetTimeLimit(u32 ms, bool b); };   // 0x0093a480 (thiscall, ret 8)
IWinMgrObj* WindowManagerW();                   // 0x0067caa0
PropMgr*    PropertyManagerW();                 // 0x0067de30
ConfigMgr*  ConfigManagerW();                   // 0x0067dd30
bool __cdecl GetPropertyAsTextW(PropList* pl, u32 id, cStr* out);        // 0x006a1360
bool __cdecl GetPropertyAsKeyW(PropList* pl, u32 id, ResourceKeyW* out); // 0x006a1250
bool __cdecl TryGetUIntPropertyW(PropList* pl, u32 id, u32* out);        // 0x00410370
IBtn* __cdecl InterfaceCastButton(IWin* w);                              // 0x005ca960
void __cdecl AnchorWindowToWindowW(IWin* a, IWin* b, int flags, int zero); // 0x00807340
static inline void ReadBoolProp(PropList* pl, u32 id, bool& out) {
  Prop* p;
  if (pl && pl->GetProperty(id, p) && p->mType == 1) out = *p->GetBool();
}
static inline void ReadUIntProp(PropList* pl, u32 id, u32& out) {
  Prop* p;
  if (pl && pl->GetProperty(id, p) && p->mType == 10) out = *p->GetUInt();
}
struct cSPUILayoutW {
    char pad_00[0x0c];
    IWin* FindWindowByID(u32 id, bool recurse);   // 0x008105b0 (thiscall, ret 8)
    bool Init(const ResourceKeyW& key, bool b, u32 flags);   // 0x008120d0 (thiscall, ret 0xc)
};
static inline const float& MaxF(const float& a, const float& b) { return (a < b) ? b : a; }
static inline IWin* FindButtonWin(cSPUILayoutW* l, u32 index) { return l->FindWindowByID(index + 0x5107b17, true); }
struct cSPUIMessageBoxW {
    char         pad_00[0x0c];
    cSPUILayoutW mLayout;                          // +0x0c
    char         pad_18[0x24 - 0x18];
    u32          m24;                              // +0x24
    u32          m28;                              // +0x28
    bool         b2c;                              // +0x2c
    char         pad_2d[0x34 - 0x2d];
    u32          m34;                              // +0x34
    LimitStopwatchW mStopwatch;                    // +0x38
    char         pad_39[0x5c - 0x39];
    bool         b5c;                              // +0x5c
    char         pad_5d[0x60 - 0x5d];
    ResourceKeyW m60;                              // +0x60
    u32          m6c;                              // +0x6c
    bool         b70;                              // +0x70
    float AutoSizeButtons();                       // 0x00816d40
    bool Init(const ResourceKeyW* key, bool flag); // 0x00817040 (thiscall, ret 8)
    void Reset();                                  // 0x00816990 (thiscall)
    void SetButtonTextFromProperty(int id, PropList* pl);   // 0x00816b20 (thiscall, ret 8)
};
// ---- items of slice s00816d40 end

// @ 0x00816d40
float cSPUIMessageBoxW::AutoSizeButtons()
{
    float result = 0.0f;
    cSPUILayoutW* layout = &mLayout;
    IWin* w1 = layout->FindWindowByID(0x5107b17, true);
    if (w1 && (w1->GetFlags() & 1)) {
        IBtn* btn = w1->Cast(0x8ed27e7a);
        if (btn) btn->SizeToCaption(0);
    }
    IWin* w2 = layout->FindWindowByID(0x5107b18, true);
    if (w1 && w2 && (w2->GetFlags() & 1)) {
        IBtn* btn = w2->Cast(0x8ed27e7a);
        if (btn) {
            btn->SizeToCaption(0);
            w2->SetLayoutLocation(w1->GetRealArea()->right, w2->GetRealArea()->top);
        }
    }
    IWin* w3 = layout->FindWindowByID(0x5107b1a, true);
    if (w3 && (w3->GetFlags() & 1)) {
        IBtn* btn = w3->Cast(0x8ed27e7a);
        if (btn) {
            float oldRight = w3->GetRealArea()->right;
            btn->SizeToCaption(0);
            const Rect4* r = w3->GetRealArea();
            w3->SetLayoutLocation(r->left - (r->right - oldRight), r->top);
        }
    }
    IWin* w4 = layout->FindWindowByID(0x5107b19, true);
    if (w3 && w4 && (w4->GetFlags() & 1)) {
        IBtn* btn = w4->Cast(0x8ed27e7a);
        if (btn) {
            btn->SizeToCaption(0);
            const Rect4* r = w4->GetRealArea();
            float width = r->right - r->left;
            w4->SetLayoutLocation(w3->GetRealArea()->left - width, r->top);
        }
    }
    IWin* leftMost = 0;
    IWin* rightMost = 0;
    if (w2 && (w2->GetFlags() & 1))
        leftMost = w2;
    else if (w1 && (w1->GetFlags() & 1))
        leftMost = w1;
    if (w4 && (w4->GetFlags() & 1))
        rightMost = w4;
    else if (w3 && (w3->GetFlags() & 1))
        rightMost = w3;
    if (leftMost && rightMost) {
        result = MaxF(0.0f, leftMost->GetRealArea()->right - rightMost->GetRealArea()->left);
    }
    return result;
}

// @ 0x00817000
void* MsgBoxA::scalarDtor(u8 flags)
{
    *(void**)((char*)this + 0) = (void*)0x1418dd4;
    *(void**)((char*)this + 4) = (void*)0x1418dc4;
    layout.~cSPUILayout_s0081_6d40();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1) Dealloc(this);
    return this;
}

// @ 0x00817040
bool cSPUIMessageBoxW::Init(const ResourceKeyW* key, bool flag)
{
  Reset();
  b5c = flag;
  void* wm = WindowManagerW()->GetMainWindowBase();
  ((MainWinW*)(wm ? (char*)wm - 4 : 0))->AddElem(this);
  PropListRef props;
  PropMgr* pm = PropertyManagerW();
  bool ok = pm->GetPropertyList(key->instanceID, key->groupID, &props);
  if (ok) {
    ReadBoolProp(props.mp, 0x615a51a, b70);
    if (b70) ok = ConfigManagerW()->GetOption(0x4ea96cb) != 0;
    if (ok) {
      ReadBoolProp(props.mp, 0x5108509, b2c);
      ReadUIntProp(props.mp, 0xdb8b6bf2, m34);
      mStopwatch.SetTimeLimit(m34, false);
      cStr s1;
      cStr s2;
      bool hasText = GetPropertyAsTextW(props.mp, 0x6b8241c9, &s1);
      GetPropertyAsTextW(props.mp, 0x4629edb4, &s2);
      ReadUIntProp(props.mp, 0x615a45e, m6c);
      bool haveKey = GetPropertyAsKeyW(props.mp, 0x61594ab, &m60);
      if (haveKey)
        ok = mLayout.Init(ResourceKeyW(m60.instanceID, 0x510a95b, 0x40464100), b5c, 0x5b598f7);
      else
        ok = mLayout.Init(ResourceKeyW(0x798ed839, 0x510a95b, 0x40464100), b5c, 0x5b598f7);
      cSPUILayoutW* layout = &mLayout;
      if (ok) {
        IWin* dlg = layout->FindWindowByID(0x6318e78, true);
        if (dlg) {
          dlg->AddWinProc(this);
          float extra = 0.0f;
          if (b2c) {
            IWin* w = layout->FindWindowByID(0xfffffff1, true);
            if (w) w->SetFlag(1, true);
          } else {
            for (int id = 0x5107b17; id <= 0x5107b1a; ++id) SetButtonTextFromProperty(id, props.mp);
            extra = AutoSizeButtons();
            u32 idx = 0;
            if (TryGetUIntPropertyW(props.mp, 0x510a385, &idx)) {
              IWin* w = FindButtonWin(layout, idx);
              if (w) {
                IBtn* btn = InterfaceCastButton(w);
                if (btn) btn->SetButtonStateFlag(4, true);
              }
            }
            IWin* w;
            bool good = false;
            if (TryGetUIntPropertyW(props.mp, 0x55a7c85, &m24)) {
              u32 id = m24 + 0x5107b17;
              w = layout->FindWindowByID(id, true);
              if (w && (w->GetFlags() & 1)) good = true;
            }
            if (!good) m24 = 0xffffffff;
            good = false;
            if (TryGetUIntPropertyW(props.mp, 0x55a7c84, &m28)) {
              u32 id = m28 + 0x5107b17;
              w = layout->FindWindowByID(id, true);
              if (w && (w->GetFlags() & 1)) good = true;
            }
            if (!good) m28 = 0xffffffff;
          }
          IWin* label = layout->FindWindowByID(0x1510d08, true);
          if (label) {
            Rect4 rc = *label->GetRealArea();
            label->SetCaption(s2.GetText());
            ((IText*)label->Cast(0xf15f4bd))->SetFlagX(true);
            const Rect4* now = label->GetRealArea();
            float height = now->bottom - now->top;
            float wdt = rc.right - rc.left;
            wdt += extra;
            rc.right = wdt + rc.left;
            rc.bottom = rc.top + height;
            label->SetLayoutArea(rc);
            dlg->SetLayoutSize(rc.right - rc.left, rc.bottom - rc.top);
            dlg->Revalidate();
            dlg->Invalidate();
            AnchorWindowToWindowW(dlg, label, 0x300, 0);
          }
          if (hasText) {
            IWin* title = dlg->FindWindowByID(0x1510d07, true);
            if (title) {
              title->SetCaption(s1.GetText());
              IWin* w = layout->FindWindowByID(0x511f230, true);
              if (w) w->SetFlag(1, true);
            }
          }
        }
      }
    }
  }
  return ok;
}
