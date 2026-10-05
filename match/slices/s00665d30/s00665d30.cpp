#include "types.h"

// Shared stubs for slice s00665d30 (SP::cSPUIFeedList* family, retail era).
// Offsets come from the disassembly; classes are hand-stubbed.

struct Obj184 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  char padA[5];
  bool b9;
  bool bA;
  void SomeMethod();
  void SetKey(const float* v, int a);
  void GetKey(float* out);
};

struct cSPUILayout {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  void Shutdown(int);
  void Init(const void* p, int a, uint32_t id);
  void SetParentWin(void* w, int a, uint32_t id);
};

// Action 0x00664550 on the object at +0x90
struct Obj90 {
  bool Method(int);
};

// Generic feed object for this family.
struct CFeed {
  char pad00[0x14];
  bool m14;              // +0x14
  char pad15[0x4b];      // 0x15..0x60
  void* m60;             // +0x60
  void* m64;             // +0x64  cSPUILayout*
  float m68, m6c, m70, m74;  // +0x68..+0x78
  char pad78[0xc];       // 0x78..0x84
  bool  m84;             // +0x84
  char pad85[7];         // 0x85..0x8c
  float m8c;             // +0x8c
  void* m90;             // +0x90
  void* m94;             // +0x94
  char pad98[0xc];       // 0x98..0xa4
  void* ma4;             // +0xa4
  void* ma8;             // +0xa8
  char padAC[8];         // 0xac..0xb4
  void* mb4;             // +0xb4
  char padB8[0x5c];      // 0xb8..0x114
  void* m114;            // +0x114
  int m118, m11c, m120, m124;  // +0x118
  char pad128[0x14];     // 0x128..0x13c
  int m13c;              // +0x13c
  char pad140[0x38];     // 0x140..0x178
  int m178;              // +0x178
  int m17c;              // +0x17c
  void* m180;            // +0x180
  Obj184* m184;          // +0x184

  bool IsKnownID() const;
  bool IsKnownState() const;
  void SetDefault(int unused);
  void Teardown();
  void SetIconKey(const float* v);
  float* GetIconKey(float* out);
  void Reserve(int a, int b);
  bool CheckFlag(bool b);
  bool Action(int* p);
};

// @ 0x00666420
bool CFeed::IsKnownID() const {
  uint32_t v = (uint32_t)m178;
  return v == 0x11f44f6b || v == 0xe8104769 || v == 0x48a6f111;
}

// @ 0x00666450
bool CFeed::IsKnownState() const {
  uint32_t v = (uint32_t)m13c;
  return v == 1 || v == 2 || v == 3 || v == 0xb;
}

// @ 0x00666490
void CFeed::SetDefault(int unused) {
  (void)unused;
  m84 = true;
  m8c = 2.0f;
}

void FUN_00829d30();
void RemoveHandler(int a, int b, int c, int d, int e);
void vec_reserve(int a, uint32_t id, int b, int c);

// @ 0x006664f0
void CFeed::Teardown() {
  if (m184) {
    m184->SomeMethod();
    Obj184* p = m184;
    if (p) { m184 = 0; p->v2(); }
  }
  if (m94) {
    ((cSPUILayout*)m94)->Shutdown(1);
    cSPUILayout* p = (cSPUILayout*)m94;
    if (p) { m94 = 0; p->v2(); }
  }
  if (m114) {
    int p = (int)m114;
    m114 = 0;
    RemoveHandler(p, m118, m11c, m120, m124);
  }
}

// @ 0x00666590
void CFeed::SetIconKey(const float* v) {
  if (m184 && (m184->b9 || m184->bA)) {
    m184->SetKey(v, 1);
    return;
  }
  m68 = v[0];
  m6c = v[1];
  m70 = v[2];
  m74 = v[3];
}

// @ 0x006665e0
float* CFeed::GetIconKey(float* out) {
  if (m184 && (m184->b9 || m184->bA)) {
    m184->GetKey(out);
    return out;
  }
  out[0] = m68;
  out[1] = m6c;
  out[2] = m70;
  out[3] = m74;
  return out;
}

// @ 0x00666630
void CFeed::Reserve(int a, int b) {
  void* v = m180;
  vec_reserve((int)v, 0x662081e, a, b);
}

// @ 0x00666680
bool CFeed::CheckFlag(bool b) {
  if (b) {
    return m14 && m90 && ((Obj90*)m90)->Method(1);
  }
  return m14;
}

// ---------------------------------------------------------------------------
// Generic virtual-call helpers (this passed in ecx).
// ---------------------------------------------------------------------------
struct VObj { void** vt; };
typedef void* (__thiscall *FnV0)(void*);
typedef void  (__thiscall *FnV1)(void*);
typedef void  (__thiscall *FnV1p)(void*, void*);
typedef void  (__thiscall *FnV1i)(void*, int);
typedef void  (__thiscall *FnV2i)(void*, int, int);
typedef void  (__thiscall *FnV2f)(void*, float, float);
typedef void  (__thiscall *FnV1f)(void*, float*);
typedef void  (__thiscall *FnV2b)(void*, int, bool);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef bool  (__thiscall *FnVb0)(void*);
typedef bool  (__thiscall *FnVb1i)(void*, int, void**);
typedef bool  (__thiscall *FnVb2i)(void*, int, int, void**);

struct IRef2 { virtual void AddRef(); virtual void Release(); };
struct CFull;
void ReloadCallback(CFull*, void*, char);
void SetRefSlot(void** slot, void* p) {
  if (p != *slot) {
    if (p) ((IRef2*)p)->AddRef();
    void* old = *slot;
    *slot = p;
    if (old) ((IRef2*)old)->Release();
  }
}

// ---- constructors -----------------------------------------------------
struct B0 { virtual void f0(); virtual void f1(); };
struct B1 { virtual void g0(); virtual void g1(); int m8; B1() : m8(0) {} };

struct WidA : B0, B1 {
  int mC; IRef2* m10; bool b14; bool b15;
  WidA(IRef2* p);
};
// @ 0x00666a60
WidA::WidA(IRef2* p) : mC(0), m10(p) {
  if (p) p->AddRef();
  b14 = false;
  b15 = false;
}

struct WidB : B0, B1 {
  int mC; int m10; bool b14; bool b15;
  WidB(int p);
};
// @ 0x00666af0
WidB::WidB(int p) : mC(p), m10(0), b14(false), b15(false) {}

// ---- 0x006668e0 -------------------------------------------------------
// Generic widget object with a vtable array.
struct Asset { char pad[0x18]; void* m18; };
Asset* AssetBrowser();
void GetFloatProperty(void* obj, uint32_t key, float* out);
void SPUIHelpers_SetWindowImage(void* w, void* img, int a);

struct CW {
  char pad[0x78];
  void* m78; void* m7c; void* m80;
  char pad84[0x20];      // 0x84..0xa4
  void* ma4;             // +0xa4
  char padA8[0xc];       // 0xa8..0xb4
  void* mb4;             // +0xb4
  void SetImg(void* img, int b, int c);
};

// @ 0x006668e0
void CW::SetImg(void* img, int b, int c) {
  if (!ma4 || !mb4) return;
  float f1 = ((float*)((FnV0)((VObj*)ma4)->vt[14])(ma4))[1];
  float f2 = ((float*)((FnV0)((VObj*)mb4)->vt[14])(mb4))[2];
  if (img) {
    m78 = img;
    m7c = (void*)b;
    m80 = (void*)c;
    SPUIHelpers_SetWindowImage(mb4, &img, 0);
    float v = 2.0f;
    if (AssetBrowser() && AssetBrowser()->m18)
      GetFloatProperty(AssetBrowser()->m18, 0x2beb75e, &v);
    ((FnV2f)((VObj*)ma4)->vt[28])(ma4, f2 + v, f1);
  } else {
    float v = 6.0f;
    if (AssetBrowser() && AssetBrowser()->m18)
      GetFloatProperty(AssetBrowser()->m18, 0xa05a01c6, &v);
    ((FnV2f)((VObj*)ma4)->vt[28])(ma4, v, f1);
  }
}

// ---- 0x00666b20 -------------------------------------------------------
struct Prop {
  void** vt;
  float* AsVec();          // FUN_006bb610
};

// @ 0x00666b20
float* GetVec4(float* out, Prop* p, int key, float a, float b, float c, float d) {
  if (p) {
    Prop* q = p;
    bool ok = ((FnVb1i)p->vt[9])(p, key, (void**)&q);
    if (ok) {
      short type = *(short*)((char*)q + 0x12);
      float* src;
      if (type == 0x34 || type == 0x10) {
        if ((*(unsigned char*)((char*)q + 0x10) & 0x30) != 0)
          src = (float*)(*(void**)q);
        else
          src = (float*)q;
      } else {
        src = q->AsVec();
      }
      out[0] = src[0];
      out[1] = src[1];
      out[2] = src[2];
      out[3] = src[3];
      return out;
    }
  }
  out[0] = a;
  out[1] = b;
  out[2] = c;
  out[3] = d;
  return out;
}

// ---- 0x00666bc0 -------------------------------------------------------
void* PropertyManager();
void GetBoolProperty(void* prop, uint32_t key, bool* out);
void GetPropertyAsKeyInstance(void* prop, uint32_t key, void* out);
void* FUN_005c1cc0(void* a, void* b, void* c);

struct CB {
  void* m4; void* m8;
  char padC[8];
  int m18;               // +0x18
  bool Action(int* p);
};

// ---- 0x006666c0 : cSPUIFeedListItem::Refresh --------------------------
void* GetFloatProp2(void* obj, uint32_t key, float* out);
int wcscmp(const wchar_t*, const wchar_t*);

struct CItem {
  char pad[0xa4];
  float mActualHeight;   // +0xa4
  void* mBg;             // +0xa8
  void Refresh(unsigned short* s);
};

// @ 0x006666c0
void CItem::Refresh(unsigned short* s) {
  if (!mBg) return;
  VObj* o = (VObj*)mBg;
  unsigned short* p = (unsigned short*)((FnV0)o->vt[15])(o);
  if (wcscmp((const wchar_t*)p, (const wchar_t*)s) == 0) return;
  ((FnV1p)o->vt[32])(o, s);
  ((FnV2b)o->vt[31])(o, 1, s[0] != 0);
  float* a = (float*)((FnV0)o->vt[14])(o);
  float r0x = a[0], r0y = a[1], r0z = a[2], r0w = a[3];
  if (mBg) {
    void* x = ((FnV0i)o->vt[3])(o, 0xf15f4bd);
    if (x) ((FnV1i)((VObj*)x)->vt[5])(x, 0);
  }
  float* b = (float*)((FnV0)o->vt[14])(o);
  float rect[4];
  rect[0] = (r0z - b[2]) + b[0];
  rect[1] = r0y;
  rect[2] = r0z;
  rect[3] = b[3];
  ((FnV1p)o->vt[27])(o, rect);
  if (mActualHeight != 0.0f) {
    float h = 2.0f;
    if (AssetBrowser() && AssetBrowser()->m18)
      GetFloatProp2(AssetBrowser()->m18, 0xe5b5d7a8, &h);
    float* c = (float*)((FnV0)o->vt[14])(o);
    float rect2[4];
    rect2[0] = c[0]; rect2[1] = c[1]; rect2[2] = c[2]; rect2[3] = c[3];
    rect2[2] = (s[0] == 0 ? rect[2] : rect[0]) - h;
    ((FnV1p)o->vt[27])(o, rect2);
  }
}

// ---- 0x006661d0 : category initialiser --------------------------------
struct Dlg { int a, b, c, d, e, f; Dlg(); };
void* operator new(size_t, const char*, int, int, int, int);
void* PropertyManager();
void* ConfigManager();
void* MessageServer();
char* GetPropertyAsKeyArray();
void SetReloadCB(void* layout, void* cb, void* self);
void InitLayout(void* layout, void* arr, int a, uint32_t id);
void SetParentWinF(void* layout, void* w, int a, uint32_t id);
void SetRefSlot(void** slot, void* p);

struct CCat {
  char pad00[0x10];
  bool m10; bool m14; bool m15;
  char pad16[0x4a];      // to 0x60
  void* m60;             // +0x60
  void* m64;             // +0x64
  void* m68;             // +0x68
  void* m6c;             // +0x6c
  char pad70[0x44];      // to 0xb4
  void* mb4;             // +0xb4
  void* mb8;             // +0xb8
  char padBC[0x10];      // to 0xcc
  int mbc, mc0, mc4, mc8, mcc;
  bool Init(void* a, void* b, int c);
};

// @ 0x006661d0
bool CCat::Init(void* a, void* b, int c) {
  SetRefSlot(&m68, a);
  SetRefSlot(&m6c, b);
  void* pm = PropertyManager();
  if (mb8) {
    ((IRef2*)mb8)->Release();
    mb8 = 0;
  }
  ((FnVb2i)((VObj*)pm)->vt[11])(pm, c, 0x6b38241, &mb8);
  mb4 = (void*)c;
  SetRefSlot(&m60, a);
  m14 = true;
  m15 = true;
  int r = (int)((FnV0i)((VObj*)ConfigManager())->vt[12])(ConfigManager(), 0x5de7b4a);
  if (r == 1 && mb8) {
    void* tmp = 0;
    bool chk = ((FnVb1i)((VObj*)mb8)->vt[9])(mb8, 0x6397993, &tmp);
    if (chk && *(short*)((char*)tmp + 0x12) == 1) {
      if (*GetPropertyAsKeyArray() == 0) return false;
    }
  }
  Dlg* d = new("Sporepedia", 0, 0, 0, 0) Dlg();
  SetRefSlot(&m64, d);
  int arr[3];
  arr[0] = 0x5a71fb79; arr[1] = 0x510a95b; arr[2] = (int)0x1527554;
  InitLayout(m64, arr, 1, 0x5b598fa);
  SetParentWinF(m64, m68, 1, 0x5b598fa);
  SetReloadCB(m64, (void*)&ReloadCallback, this);
  ReloadCallback((CFull*)this, m64, 1);
  void* ms = MessageServer();
  mbc = (int)ms;
  mc0 = (int)this;
  mc4 = 0x1400244;
  mc8 = 1;
  mcc = 0;
  if (ms) ((FnV2i)((VObj*)ms)->vt[9])(ms, (int)this, 0xb3d53f95);
  return true;
}

// ---- 0x00665d30 : ReloadCallback --------------------------------------
void Populate(CFull* self);
void FUN_00805ef0(void* out, void* in);
void FUN_00829c50(void* a, void* b, void* c, void* d);
void vec_erase(void* vec, void* begin, void* end);
void* FindWindowByIDF(void* layout, uint32_t id, bool rec);

struct CFull {
  char pad00[0x18];
  int m18;
  char pad1c[0xc];
  float m28, m2c, m30, m34;
  float m38, m3c, m40, m44;
  float m48, m4c, m50, m54;
  float m58;
  char pad5c[4];
  void* m60;
  void* m64;
  void* m68;
  void* m6c;
  void* m70;
  void* m74;
  void* m78;
  void* m7c;
  void* m80;
  void* m84;
  void* m88;
  void* m8c;
  char pad90[0x44];
  void* md4;
};

// @ 0x00665d30
void ReloadCallback(CFull* self, void* layout, char reload) {
  if (!reload) {
    int n = (int)(((int)self->m8c - (int)self->m88) >> 2);
    for (int i = 0; i < n; i++)
      ((CFeed*)((void**)self->m88)[i])->Teardown();
    vec_erase(&self->m88, self->m88, self->m8c);
    if (self->m7c) ((FnV1p)((VObj*)self->m7c)->vt[66])(self->m7c, (char*)self + 4);
    if (self->m74) ((FnV1p)((VObj*)self->m74)->vt[66])(self->m74, (char*)self + 4);
    if (self->m80) ((FnV1p)((VObj*)self->m80)->vt[66])(self->m80, (char*)self + 4);
    if (self->m84) ((FnV1p)((VObj*)self->m80)->vt[66])(self->m80, (char*)self + 4);
    if (self->md4) {
      FUN_00829d30();
      void** p = &self->md4;
      if (*p) { *p = 0; ((FnV1)((VObj*)*p)->vt[2])(*p); }
    }
    if (self->m70) { void* p = self->m70; self->m70 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m74) { void* p = self->m74; self->m74 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m78) { void* p = self->m78; self->m78 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m7c) { void* p = self->m7c; self->m7c = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m80) { void* p = self->m80; self->m80 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    if (self->m84) { void* p = self->m84; self->m84 = 0; ((FnV1)((VObj*)p)->vt[1])(p); }
    return;
  }
  SetRefSlot(&self->m70, FindWindowByIDF(layout, 0xf3c6dc19, true));
  SetRefSlot(&self->m74, FindWindowByIDF(layout, 0x684be28, true));
  SetRefSlot(&self->m78, FindWindowByIDF(layout, 0xb3c6efca, true));
  SetRefSlot(&self->m7c, FindWindowByIDF(layout, 0xf3c839e5, true));
  SetRefSlot(&self->m80, FindWindowByIDF(layout, 0xb3c6efc2, true));
  SetRefSlot(&self->m84, FindWindowByIDF(layout, 0xb48e2560, true));
  if (self->m78)
    ((FnV1i)((VObj*)self->m78)->vt[32])(self->m78, self->m18);
  if (self->m70) {
    float* a = (float*)((FnV0)((VObj*)self->m68)->vt[14])(self->m68);
    float rect[4];
    rect[0] = a[2] - a[0];
    rect[1] = a[3] - a[1];
    float* b = (float*)((FnV0)((VObj*)self->m70)->vt[14])(self->m70);
    rect[3] = b[3] - b[1];
    rect[2] = 0.0f;
    ((FnV1p)((VObj*)self->m70)->vt[24])(self->m70, rect);
    self->m28 = rect[0]; self->m2c = rect[1];
    self->m30 = rect[2]; self->m34 = rect[3];
  }
  if (self->m74) {
    float out[4];
    FUN_00805ef0(out, self->m74);
    self->m38 = out[0]; self->m3c = out[1];
    self->m40 = out[2]; self->m44 = out[3];
    self->m48 = self->m38; self->m4c = self->m3c;
    self->m50 = self->m40; self->m54 = self->m44;
    ((FnV1p)((VObj*)self->m74)->vt[65])(self->m74, (char*)self + 4);
  }
  if (self->m7c)
    ((FnV1p)((VObj*)self->m7c)->vt[65])(self->m7c, (char*)self + 4);
  if (self->m80) {
    float* a = (float*)((FnV0)((VObj*)self->m80)->vt[13])(self->m80);
    self->m58 = a[3] - a[1];
    ((FnV1p)((VObj*)self->m80)->vt[65])(self->m80, (char*)self + 4);
  }
  if (self->m84)
    ((FnV1p)((VObj*)self->m84)->vt[65])(self->m84, (char*)self + 4);
  Dlg* d = new("Sporepedia", 0, 0, 0, 0) Dlg();
  SetRefSlot(&self->md4, d);
  ((FnV1p)((VObj*)self->md4)->vt[66])(self->md4, self->m74);
  FUN_00829c50(self->md4, self->m74, self->m78, self->m6c);
  Populate(self);
}

// @ 0x00666bc0
bool CB::Action(int* p) {
  bool b = false;
  if (p[1] == 0xb1b104 && p[2] == m18) {
    void* prop = 0;
    void* pm = PropertyManager();
    bool ok = ((FnVb2i)((VObj*)pm)->vt[11])(pm, (int)p[0], p[2], &prop);
    if (ok) {
      GetBoolProperty(prop, 0x71efa6c, &b);
      if (b && m4 != m8) {
        void* key = 0;
        GetPropertyAsKeyInstance(prop, 0x5cd8beab, &key);
        void* r = FUN_005c1cc0(m4, m8, &key);
        if (r == m8) b = false;
      }
    }
    if (prop) ((IRef2*)prop)->Release();
  }
  return b;
}
