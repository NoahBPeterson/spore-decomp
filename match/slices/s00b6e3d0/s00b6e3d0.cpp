// slice s00b6e3d0 -- shared editor color table (palette map 0x156b0b8), color translator, color-set object.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>
#define F2I(x) ((int)(x))

void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);
void __cdecl EASTLFree(void* p);  // @ 0xF47380 operator delete[]

struct Vec3 { float x, y, z; };
struct Vec3F {
  float x, y, z;
  Vec3F() {}
  Vec3F& operator=(const Vec3F& v) { x = v.x; y = v.y; z = v.z; return *this; }
  Vec3F(const Vec3F& v) : x(v.x), y(v.y), z(v.z) {}
};

// ---- eastl rbtree pieces ----
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);  // @ 0x921580
void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, int side);  // @ 0x9216a0

// ---- eastl::wstring (16 bytes incl. allocator) ----
extern wchar_t kEmptyW[2];  // @ 0x1667bac
struct wstr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAlloc;
  wstr() : mpBegin(kEmptyW), mpEnd(kEmptyW), mpCapacity(kEmptyW + 1) {}
  ~wstr() {
    if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2 && mpBegin) EASTLFree(mpBegin);
  }
  wstr& assign(const wchar_t* b, const wchar_t* e);  // @ 0x423650
  wstr& append(const wchar_t* p);                    // @ 0x5c3d90
  wstr& operator=(const wstr& o);                    // @ 0x57cb60
  void RangeInitialize(const wchar_t* p);            // @ 0x579a90
};

// ---- string table object (UI string source) ----
struct cString {
  unsigned int pad[5];  // 0x14 bytes: the ctor writes bytes +0x10/+0x11
  cString();                                                                // @ 0x6b5060
  cString(unsigned int tbl, unsigned int key, const wchar_t* def);          // @ 0x6b5770
  void Load(unsigned int tbl, unsigned int key, const wchar_t* def);        // @ 0x6b54b0
  const wchar_t* GetText();                                                 // @ 0x6b55c0
  ~cString();                                                               // @ 0x6b5240
};

// ---- palette map: map<uint, Vec3>  (global @ 0x156b0b8) ----
struct ColorNode : rbtree_node_base {
  unsigned int key;  // +0x10
  Vec3 val;          // +0x14
};
struct ColorIter { ColorNode* n; ColorIter(ColorNode* p) : n(p) {} };
struct ColorMap {
  int mCompare;              // +0
  rbtree_node_base mAnchor;  // +4
  unsigned int mnSize;       // +0x14
  void DoNukeSubtree(ColorNode* p);                                        // @ 0x9a9600
  Vec3& Index(const unsigned int& key);   // original 0xb6ee40 map::operator[] (named so the checker can find it)
  void DoInsertValueImpl(ColorNode** out, ColorNode* parent, const void* v, bool left);  // @ 0xb6eb30
  void DoInsertValue(ColorNode** out, ColorIter parent, const void* v, bool left);       // @ 0xb6ed20
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
};
extern ColorMap g_colorMap;  // @ 0x156b0b8

// ---- string-map used by the color-set object: map<uint, wstring> ----
struct NameMap {
  int mCompare;
  rbtree_node_base mAnchor;
  unsigned int mnSize;
  void DoNukeSubtree(void* p);        // @ 0x801ef0
  NameMap() : mAnchor() { reset(); }
  ~NameMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNukeSubtree(mAnchor.mpNodeParent);
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  wstr& operator[](const unsigned int& key);  // @ 0x688ad0
};

// ---- translator object (string-token source) ----
struct PropList {
  virtual void v0();
  virtual void Release();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual bool HasProperty(unsigned int id);  // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void* GetProperty(unsigned int id);  // +0x28 (property record)
};
struct PropMgr {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual bool GetPropertyList(unsigned int id, PropList** out);  // +0x30
};
PropMgr* GetPropMgr();  // @ 0x67de30

struct cStringTokenTranslator {
  int mRefCount;
  cStringTokenTranslator();  // @ 0x6b5870
  virtual ~cStringTokenTranslator();
  virtual void AddRef();
  virtual void Release();
  virtual bool Translate(const wchar_t* token, wstr* out);
};
struct StrNode : rbtree_node_base {
  unsigned int key;
  const wchar_t* val;
};
struct StrMap {
  int mCompare;
  rbtree_node_base mAnchor;
  unsigned int mnSize;
  StrNode* find(const unsigned int& key);  // @ 0xe5c780
};
struct StringSetT {
  char pad[8];
  StrMap mMap;
  const wchar_t* Get(int idx);  // @ 0xb6a6e0
};
unsigned int FNV1_String16(const wchar_t* s, unsigned int basis, int lower);  // @ 0x932f30

struct ColorTranslator : cStringTokenTranslator {
  wstr mText0;        // +8
  wstr mText1;        // +0x18
  StringSetT* mSetA;  // +0x28
  StringSetT* mSetB;  // +0x2c
  StringSetT* mSetC;  // +0x30
  ColorTranslator() : mSetA(0), mSetB(0), mSetC(0) {}
  virtual ~ColorTranslator() {}
  virtual bool Translate(const wchar_t* token, wstr* out);
};
extern ColorTranslator* g_translator;  // @ 0x1687978

struct UIMgr {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void Register(ColorTranslator* t);    // +0x1c
  virtual void Unregister(ColorTranslator* t);  // +0x20
};
struct UIMgrHolder {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual UIMgr* GetMgr();  // +0x20
};
UIMgrHolder* GetUIHolder();  // @ 0x67de40

extern unsigned int g_x1687968;  // @ 0x1687968
extern unsigned int g_x156b018;  // @ 0x156b018
extern bool g_used[12];          // @ 0x168795c
extern Vec3F g_defaultColor;      // @ 0x168796c

void RGBToHSL(Vec3 rgb, float* h, float* s, float* l);                // @ 0x67ff30
Vec3* HSLToRGB(Vec3* out, float h, float s, float l);                 // @ 0x67fe30
struct SimTicker {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void Notify(void* who);  // +0x50
};
SimTicker* GetSimTicker();  // @ 0xb3d330

// @ 0x00B6E3D0  find the palette entry nearest to a color; returns its key
unsigned int FindNearestColorKey(const Vec3* c) {
  static const unsigned int kMaxBits = 0x7f7fffff;
  float best = *(const float*)&kMaxBits;
  unsigned int bestKey = 0x53dbcf3;
  float x = c->x, y = c->y, z = c->z;
  for (rbtree_node_base* n = g_colorMap.mAnchor.mpNodeLeft; n != &g_colorMap.mAnchor; n = RBTreeIncrement(n)) {
    ColorNode* cn = (ColorNode*)n;
    Vec3 d;
    d.x = cn->val.x - x;
    d.y = cn->val.y - y;
    d.z = cn->val.z - z;
    float dist = (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    if (dist < best) {
      bestKey = cn->key;
      best = dist;
    }
  }
  return bestKey;
}

// @ 0x00B6E4B0  nudge near-gray colors off the gray axis, then clamp saturation/lightness
Vec3* AdjustColor(Vec3* out, float r, float g, float b, float minS, float minL) {
  out->x = r;
  out->y = g;
  out->z = b;
  if (fabs(r - g) < 0.1f && fabs(r - b) < 0.1f && fabs(g - b) < 0.1f) {
    if (r > g && r > b) {
      r = (1.0f - r) * 0.1f + r;
      g = g * 0.9f;
      b = b * 0.9f;
    } else if (g > r && g > b) {
      r = r * 0.9f;
      g = (1.0f - g) * 0.1f + g;
      b = b * 0.9f;
    } else {
      r = r * 0.9f;
      g = g * 0.9f;
      b = (1.0f - b) * 0.1f + b;
    }
  }
  float h, s, l;
  Vec3 rgb;
  rgb.x = r;
  rgb.y = g;
  rgb.z = b;
  RGBToHSL(rgb, &h, &s, &l);
  if (s <= minS) s = minS;
  if (1.0f <= s) s = 1.0f;
  if (l <= minL) l = minL;
  if (1.0f <= l) l = 1.0f;
  Vec3 tmp;
  *out = *HSLToRGB(&tmp, h, s, l);
  return out;
}

// @ 0x00B6E6D0  shut down the color manager
void ShutdownColorManager() {
  if (g_translator && g_colorMap.mnSize) {
    g_colorMap.DoNukeSubtree((ColorNode*)g_colorMap.mAnchor.mpNodeParent);
    g_colorMap.reset();
    GetUIHolder()->GetMgr()->Unregister(g_translator);
    ColorTranslator* t = g_translator;
    if (t) {
      g_translator = 0;
      t->Release();
    }
  }
}

// @ 0x00B6E7B0  ColorTranslator::Translate
bool ColorTranslator::Translate(const wchar_t* token, wstr* out) {
  unsigned int key;
  bool ok = true;
  switch (FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x24b3c25fu: out->append(mSetC->Get(1)); break;
    case 0x0e76b271u: out->append(mSetA->Get(0)); break;
    case 0x04603dc6u: out->append(mSetC->Get(0)); break;
    case 0x2bcf1d11u: key = 5; out->append(mSetC->mMap.find(key)->val); break;
    case 0x35dae791u: key = 0xf; out->append(mSetA->mMap.find(key)->val); break;
    case 0x5d7860fau: out->append(mSetB->Get(1)); break;
    case 0x5f960254u: {
      key = 5;
      const wchar_t* p = mSetB->mMap.find(key)->val;
      const wchar_t* e = p;
      while (*e) e++;
      out->assign(p, e);
      break;
    }
    case 0x9825819au: out->append(mSetC->Get(4)); break;
    case 0x94730909u: out->append(mSetA->Get(0x10)); break;
    case 0x7e5504edu: out->append(mSetB->Get(0)); break;
    case 0xa708d495u: out->append(mSetB->Get(4)); break;
    case 0xa9813ec0u: out->append(mSetC->Get(3)); break;
    case 0xaf5632a7u: out->append(mSetA->Get(2)); break;
    case 0xc4bee3d5u:
      if (&mText1 != out) out->assign(mText1.mpBegin, mText1.mpEnd);
      break;
    case 0xdd67ded2u: out->append(mSetC->Get(2)); break;
    case 0xcd335100u: out->append(mSetA->Get(0x11)); break;
    case 0xccd6c165u: out->append(mSetB->Get(3)); break;
    case 0xdf44b8c0u: *out = mText0; break;
    case 0xeaadf55bu: out->append(mSetA->Get(0xd)); break;
    case 0xf174ab9eu: key = 2; out->append(mSetB->mMap.find(key)->val); break;
    default: ok = false;
  }
  return ok;
}

// @ 0x00B6EB30  ColorMap::DoInsertValueImpl
void ColorMap::DoInsertValueImpl(ColorNode** out, ColorNode* parent, const void* v, bool bForceToLeft) {
  struct Pair { unsigned int first; Vec3 second; };
  const Pair& value = *(const Pair*)v;
  int side;
  if (bForceToLeft || (parent == (ColorNode*)&mAnchor) || (value.first < parent->key))
    side = 0;
  else
    side = 1;
  ColorNode* n = (ColorNode*)operator new(
      0x20, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (&n->key) {
    n->key = value.first;
    n->val = value.second;
  }
  RBTreeInsert(n, parent, &mAnchor, side);
  mnSize++;
  *out = n;
}

// @ 0x00B6EC50  load localized color/entity names into the translator
void LoadColorNames(wstr* out, unsigned int key, unsigned int idx, cString* str) {
  cString s;
  s.Load(0xcdf005ab, key, L"!!!Color Name");
  wstr tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCapacity = 0;
  tmp.RangeInitialize(s.GetText());
  if (&tmp != &g_translator->mText0) g_translator->mText0.assign(tmp.mpBegin, tmp.mpEnd);
  if (out != &g_translator->mText1) g_translator->mText1.assign(out->mpBegin, out->mpEnd);
  str->Load(0xcdf005ab, idx, L"!!!Entity Name");
}

// @ 0x00B6EDF0  ColorSet dtor body; @ 0x00B6F2E0 scalar deleting dtor (compiler generated)
// @ 0x00B6EE10  ColorSet::clear;  @ 0x00B6F280  ColorSet ctor
struct cColorSet {
  virtual ~cColorSet();
  unsigned int mKey;   // +4
  NameMap mNames;      // +8
  unsigned int mPad;   // +0x20
  Vec3F mDefault;      // +0x24
  cColorSet();
  void clear();
  void LoadNames(wstr* out);
  void NotifyTicker();
  unsigned int GetARGB();
};

// @ 0x00B6EDF0
cColorSet::~cColorSet() {}

void cColorSet::clear() { mNames.clear(); }

// @ 0x00B6F280
cColorSet::cColorSet() : mKey(0x53dbcf1) {
  mDefault = g_defaultColor;
}

// @ 0x00B6EE40  ColorMap::Index (eastl map::operator[])
Vec3& ColorMap::Index(const unsigned int& key) {
  ColorNode* parent = (ColorNode*)&mAnchor;
  ColorNode* n = (ColorNode*)mAnchor.mpNodeParent;
  while (n) {
    if (!(n->key < key)) {
      parent = n;
      n = (ColorNode*)n->mpNodeLeft;
    } else {
      n = (ColorNode*)n->mpNodeRight;
    }
  }
  if (parent == (ColorNode*)&mAnchor || key < parent->key) {
    struct Pair {
      unsigned int first; Vec3F second;
      Pair(const unsigned int& k, const Vec3F& s) : first(k), second(s) {}
    } v(key, Vec3F());   // eastl: value_type(key, T()); T() is an uninitialised temp, copied
    ColorNode* r;
    DoInsertValue(&r, ColorIter(parent), &v, false);
    return r->val;
  }
  return parent->val;
}

// @ 0x00B6EEE0  create the color manager: load palette from the property list and register the translator
void InitColorManager() {
  if (g_translator == 0 || g_colorMap.mnSize == 0) {
    PropList* list = 0;
    PropMgr* pm = GetPropMgr();
    if (list) {
      PropList* t = list;
      list = 0;
      t->Release();
    }
    if (pm->GetPropertyList(0x5c770db7, &list) && list->HasProperty(0x5515ffd)) {
      struct Prop {
        char* data;
        int pad[1];
        unsigned int count;
        int pad2;
        unsigned short flags;
        unsigned short has;
      };
      Prop* p = (Prop*)list->GetProperty(0x5515ffd);
      Vec3* d;
      unsigned int count;
      if (p->flags & 0x30) {
        d = (Vec3*)p->data;
        count = p->count;
      } else {
        d = (Vec3*)(-(unsigned int)(p->has != 0) & (unsigned int)p);
        count = (p->has != 0);
      }
      for (unsigned int i = 0; i < count; i++) {
        Vec3 v = d[i];
        unsigned int k = 0x53dbcf1 + i;
        g_colorMap.Index(k) = v;
      }
    }
    g_x1687968 = 0x53dbcf2;
    g_x156b018 = 0x53dbcf3;
    {
      cString nm(0xcdf005ab, 0x53dbcf2, L"!!!Color 0");
      ColorTranslator* t = new ("Simulator", 0, 0, 0, 0) ColorTranslator;
      ColorTranslator* old = g_translator;
      if (t != old) {
        if (t) t->AddRef();
        g_translator = t;
        if (old) old->Release();
      }
      GetUIHolder()->GetMgr()->Register(g_translator);
    }
    if (list) list->Release();
  }
}

// @ 0x00B6F0C0  palette lookup
Vec3& GetColor(unsigned int key) {
  return g_colorMap.Index(key);
}

// the original truncates in single precision with cvttss2si (mulss, no x87 round trip)
static __forceinline int F2IS(const float* p) {
  return _mm_cvtt_ss2si(_mm_mul_ss(_mm_load_ss(p), _mm_set_ss(255.0f)));
}
static __forceinline unsigned int PackARGB(const Vec3& c) {
  return (((F2IS(&c.x) | 0xffffff00u) << 8 | (F2IS(&c.y) & 0xff)) << 8) | (F2IS(&c.z) & 0xff);
}

// @ 0x00B6F0D0  palette color as 0xFFRRGGBB
unsigned int GetColorARGB(unsigned int key) {
  return PackARGB(g_colorMap.Index(key));
}

// @ 0x00B6F140  set the base palette entry
void SetBaseColor(Vec3 col) {
  if (g_translator && g_colorMap.mnSize) {
    unsigned int k = 0x53dbcf1;
    Vec3& c = g_colorMap.Index(k);
    c = col;
  }
}

// @ 0x00B6F180  mark the two palette entries nearest the base color
void MarkNearestColors() {
  g_used[0] = 0;
  g_used[4] = 0;
  g_used[8] = 0;
  *(unsigned int*)&g_used[0] = 0;
  *(unsigned int*)&g_used[4] = 0;
  *(unsigned int*)&g_used[8] = 0;
  unsigned int k0 = 0x53dbcf1;
  const Vec3& base = g_colorMap.Index(k0);
  for (int n = 2; n != 0; n--) {
    unsigned int found = 0xffffffff;
    float best = 0.25f;
    for (unsigned int i = 0; (int)i < 0xc; i++) {
      unsigned int k = i + 0x53dbcf3;
      if (!g_used[i]) {
        if (i > 0xb) k = 0x53dbcf3;
        const Vec3& c = g_colorMap.Index(k);
        float d = (c.x - base.x) * (c.x - base.x) + (c.y - base.y) * (c.y - base.y) + (c.z - base.z) * (c.z - base.z);
        if (d < best) {
          found = i;
          best = d;
        }
      }
    }
    if (found != 0xffffffff) g_used[found] = 1;
  }
}

// @ 0x00B6F310  ColorSet color as 0xFFRRGGBB
unsigned int cColorSet::GetARGB() {
  unsigned int k = mKey;
  return PackARGB(g_colorMap.Index(k));
}

// @ 0x00B6F380  ColorSet::LoadNames
void cColorSet::LoadNames(wstr* out) {
  cString s;
  s.Load(0xcdf005ab, mKey, L"!!!Color Name");
  wstr tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCapacity = 0;
  tmp.RangeInitialize(s.GetText());
  if (&tmp != &g_translator->mText0) g_translator->mText0.assign(tmp.mpBegin, tmp.mpEnd);
  if (out != &g_translator->mText1) g_translator->mText1.assign(out->mpBegin, out->mpEnd);
  for (unsigned int i = 0; i < 0x12; i++) {
    s.Load(0xcdf005ab, i, L"!!!Entity Name");
    const wchar_t* p = s.GetText();
    wstr& dst = mNames[i];
    const wchar_t* e = p;
    while (*e) e++;
    dst.assign(p, e);
  }
}

// @ 0x00B6F4C0
void cColorSet::NotifyTicker() {
  GetSimTicker()->Notify(this);
}
