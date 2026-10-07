// Slice s005ec030: name-generator helpers (SP::cSPNameGenerator, markov-chain name tables).
// Flags: /O2 /MD /Gy /TP /GS- (no EH frames or cookies anywhere in the original slice)
#include "types.h"

// ---- local stubs (retail layout) ----
void* operator new(unsigned int, const char*, int, int, int, int);               // @ 0x00f473a0
void* operator new(unsigned int, const char*, int, int, const char*, int);       // @ 0x00f473a0
void operator_delete_array(void* p);                                             // @ 0x00f47380 (operator delete[])
extern wchar_t g_EmptyWStr[2];                                                   // @ 0x01667bac
void* memcpy_thunk(void* d, const void* s, unsigned n);                          // @ 0x011e0744

// sp_vector_allocator free: delete[] only when the 4 bytes before the block are non-zero
static inline void SpFree(void* p) {
  if (p && ((int*)p)[-1] != 0) operator_delete_array(p);
}

struct WStr {  // eastl::basic_string<wchar_t>: begin, end, capacity, allocator (0x10 bytes)
  wchar_t* b;
  wchar_t* e;
  wchar_t* c;
  uint32_t alloc;
  void Init(const WStr& s);             // @ 0x0056e2d0 (copy constructor)
  void AllocateSelf(unsigned n);        // @ 0x00429760
  void push_back(wchar_t ch);           // @ 0x004f6510
  void make_lower();                    // @ 0x005e8e80
  void assign(const wchar_t*, const wchar_t*);  // @ 0x00423650
  void append(const wchar_t*, const wchar_t*);  // @ 0x00429580
  void Free() {
    if ((((int)c - (int)b) & ~1) > 2 && b) operator_delete_array(b);
  }
};
extern WStr g_EmptyWStrObj;  // @ 0x015f0a1c (shared empty string object)
void sprintfW(WStr* dst, const wchar_t* fmt, ...);  // @ 0x004e0850
const wchar_t* Search(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);  // @ 0x005e8ff0
void Normalize(WStr* s);  // @ 0x005e9320

struct WStr;
WStr* CopyWStrRange(WStr* first, WStr* last, WStr* dest);  // @ 0x0084ab40 (eastl::copy_impl::do_copy, cdecl)
struct StrVec {  // eastl::vector<wstring, sp_vector_allocator>
  WStr* b;
  WStr* e;
  WStr* c;
  void DoDestroyValues(WStr* first, WStr* last);   // @ 0x0084aad0
  // erase(first, last), inlined: move the tail down, destroy the leftovers, shrink
  void erase(WStr* first, WStr* last) {
    WStr* p = CopyWStrRange(last, e, first);
    DoDestroyValues(p, e);
    e -= (last - first);
  }
  void Insert(WStr* pos, WStr* first, WStr* last, int tag);  // @ 0x005ea200
};
struct StrSet {  // eastl::set<wstring>, anchor at +4, size at +0x14
  uint32_t cmp;
  uint32_t anchor[4];
  uint32_t size;
  void insert(WStr* first, WStr* last);  // @ 0x005e9f10
};

struct Random { uint32_t pad; };
extern Random g_MathRandom;  // @ 0x01601760
uint32_t RandomWeightedChoice(Random* r, uint32_t n, const float* w);  // @ 0x005e8ec0 (cdecl)
struct RandomLCG { uint32_t Uniform(uint32_t n); };                      // @ 0x00a68fb0
extern RandomLCG g_MathRandomLCG;                                       // @ 0x01601760

// ---- chain tables ----
struct NodeBase { NodeBase* right; NodeBase* left; NodeBase* parent; uint32_t color; };
void* RBTreeIncrement(void* n);  // @ 0x00921580

struct SpVecW {  // vector<wchar_t, sp_vector_allocator> (0x14 bytes)
  wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc, pad;
  void DoInsertValue(wchar_t* pos, const wchar_t& v);  // @ 0x005e9a00
};
struct SpVecF {  // vector<float, sp_vector_allocator> (0x14 bytes)
  float* b; float* e; float* c; uint32_t alloc, pad;
  void push_back_slow(float* pos, const float& v);  // @ 0x00455660
};
struct ChainRow {
  SpVecW chars;
  SpVecF weights;
  ChainRow() { chars.b = 0; chars.e = 0; chars.c = 0; weights.b = 0; weights.e = 0; weights.c = 0; }
  ChainRow(const ChainRow& o);  // @ 0x005ea8f0
  ~ChainRow() { SpFree(weights.b); SpFree(chars.b); }
};
struct Key2 { wchar_t a, b; };
// eastl::less<eastl::pair<wchar_t, wchar_t> >
inline bool KeyLess(const Key2& x, const Key2& y) { return x.a < y.a || (!(y.a < x.a) && x.b < y.b); }
struct ChainNode : NodeBase { Key2 key; ChainRow row; };
struct ChainPair { Key2 key; ChainRow row; ChainPair(const Key2& k, const ChainRow& r) : key(k), row(r) {} };
struct ChainIter {
  ChainNode* node;
  ChainIter() {}
  ChainIter(const ChainIter& o) : node(o.node) {}
  explicit ChainIter(ChainNode* n) : node(n) {}
  ChainIter& operator=(const ChainIter& o) { node = o.node; return *this; }
  bool operator==(const ChainIter& o) const { return node == o.node; }
};
struct UniqueKeys {};  // eastl::true_type (has_unique_keys_type), passed by value
struct ChainMap {  // eastl::map<pair<wchar_t,wchar_t>, chainData>
  uint32_t cmp;
  NodeBase anchor;  // +4
  uint32_t size, alloc;
  ChainIter end() { return ChainIter((ChainNode*)&anchor); }
  void lower_bound(ChainIter* out, const Key2* k);
  ChainIter lower_bound_v(const Key2* k) { ChainIter r; lower_bound(&r, k); return r; }                              // @ 0x005e91c0
  void DoInsertValueHint(ChainIter* out, ChainIter pos, const ChainPair& v, UniqueKeys);
  ChainIter DoInsertValue_v(ChainIter pos, const ChainPair& v, UniqueKeys u) { ChainIter r; DoInsertValueHint(&r, pos, v, u); return r; }      // @ 0x005ebf10
  ChainRow* FUN_005ec030(const Key2* key);
};

struct Key3 { Key2 k2; wchar_t c; };
struct CountNode : NodeBase { Key3 key; int pad; int count; int pad2[2]; };
struct CountIter { CountNode* node; CountIter() {} CountIter(const CountIter& o) : node(o.node) {} };
struct CountMap {
  uint32_t cmp;
  NodeBase anchor;
  uint32_t size, alloc;
  void find(CountIter* out, const Key3* k);   // @ 0x005e93c0
  int* subscript(const Key3* k);              // @ 0x005ea040
  void DoNukeSubtree(NodeBase* n);            // @ 0x009a9600
};

struct NameGenData {  // 0x28 bytes
  int minLen;
  int maxLen;
  ChainMap chains;  // +8
};

// @ 0x005EC030
ChainRow* ChainMap::FUN_005ec030(const Key2* key) {
  // eastl::map::operator[]
  ChainIter itLower;
  itLower = lower_bound_v(key);
  if (itLower.node == (ChainNode*)&anchor || KeyLess(*key, itLower.node->key)) {
    ChainRow t;
    ChainPair v(*key, t);
    itLower = DoInsertValue_v(itLower, v, UniqueKeys());
  }
  return &itLower.node->row;
}

// ---- name generator ----
struct Property {
  uint8_t pad0[0x10];
  uint8_t flags;      // +0x10
  uint8_t pad1;
  uint16_t type;      // +0x12
  int* GetInt();      // @ 0x0041e990
};
struct PropList {
  virtual void v0();
  virtual void Release();   // +4
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void v7(); virtual void v8();
  virtual bool GetProperty(uint32_t id, Property** out);  // +0x24
};
struct PropMgr {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual void GetPropertyList(uint32_t group, uint32_t instance, PropList** out);  // +0x2c
};
PropMgr* PropertyManager();  // @ 0x0067de30
bool GetPropertyAsString16(PropList* l, uint32_t id, WStr* out);                         // @ 0x006a1400 (cdecl)
bool GetPropertyAsString16Array(PropList* l, uint32_t id, int* count, WStr** arr);       // @ 0x006a0bc0 (cdecl)

struct TreeIter { NodeBase* node; TreeIter() {} TreeIter(const TreeIter& o) : node(o.node) {} };
struct U16Set {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const uint32_t& k);          // @ 0x005e90a0
  void insert(uint32_t c);                   // @ 0x005e9890 (DoInsertValue)
  void DoNukeSubtree(void* n, void* x);      // @ 0x009a9600
};
struct WStrSetT {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const WStr& k);              // @ 0x005e96f0
};
struct NameNode : NodeBase { WStr key; int count; };  // count at +0x20
struct WStrMapT {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const WStr& k);              // @ 0x005e96f0
  int* subscript(const WStr& k);             // @ 0x005eae50
};

#define FLD(T, off) (*(T*)((char*)this + (off)))

struct cSPNameGenerator {
  bool FUN_005ebe90(PropList* l, uint32_t id, void* vec, bool flag);   // @ 0x005ebe90
  void FUN_005eba70(PropList* l, uint32_t id, void* vec);              // @ 0x005eba70
  void FUN_005eb440(NameGenData* d, PropList* l, uint32_t a, uint32_t b, uint32_t c, void* vec,
                    uint32_t hash);                                    // @ 0x005eb440
  void FUN_005ec130(StrVec* names, NameGenData* data);
  WStr* FUN_005ec370(WStr* out, NameGenData* data, StrSet* excluded, StrVec* subs, StrVec* fallback,
                     bool allowDup);
  void Init();  // @ 0x005ec7c0
};

// @ 0x005EC130
void cSPNameGenerator::FUN_005ec130(StrVec* names, NameGenData* data) {
  data->minLen = 100;
  data->maxLen = 0;
  CountMap counts;
  counts.anchor.right = &counts.anchor;
  counts.anchor.left = &counts.anchor;
  counts.anchor.parent = 0;
  counts.anchor.color = 0;
  counts.size = 0;
  for (WStr* s = names->b; s != names->e; s++) {
    int len = s->e - s->b;
    if (len <= 0) continue;
    if (len < data->minLen) data->minLen = len;
    if (len > data->maxLen) data->maxLen = len;
    wchar_t p2 = '^';
    wchar_t p1 = '^';
    for (wchar_t* p = s->b; p != s->e;) {
      wchar_t ch = *p;
      Key2 k2;
      k2.a = p2;
      k2.b = p1;
      data->chains.FUN_005ec030(&k2);
      Key3 k3;
      k3.k2 = k2;
      k3.c = ch;
      CountIter it;
      counts.find(&it, &k3);
      if (it.node == (CountNode*)&counts.anchor) *counts.subscript(&k3) = 1;
      else it.node->count++;
      p++;
      if (p == s->e) {
        Key3 e3;
        e3.k2.a = p1;
        e3.k2.b = ch;
        e3.c = '$';
        counts.find(&it, &e3);
        if (it.node == (CountNode*)&counts.anchor) *counts.subscript(&e3) = 1;
        else it.node->count++;
      }
      p2 = p1;
      p1 = ch;
    }
  }
  for (NodeBase* n = counts.anchor.left; n != &counts.anchor; n = (NodeBase*)RBTreeIncrement(n)) {
    CountNode* cn = (CountNode*)n;
    Key2 k2 = cn->key.k2;
    wchar_t c = cn->key.c;
    int cnt = cn->count;
    ChainRow* row = data->chains.FUN_005ec030(&k2);
    if (row->chars.e < row->chars.c) {
      if (row->chars.e) *row->chars.e = c;
      row->chars.e++;
    } else {
      row->chars.DoInsertValue(row->chars.e, c);
    }
    float w = (float)cnt;
    if (row->weights.e < row->weights.c) {
      if (row->weights.e) *row->weights.e = w;
      row->weights.e++;
    } else {
      row->weights.push_back_slow(row->weights.e, w);
    }
  }
  for (NodeBase* n = counts.anchor.parent; n;) {
    counts.DoNukeSubtree(n->right);
    NodeBase* nx = n->left;
    operator_delete_array(n);
    n = nx;
  }
}

// @ 0x005EC370
WStr* cSPNameGenerator::FUN_005ec370(WStr* out, NameGenData* data, StrSet* excluded, StrVec* subs,
                                     StrVec* fallback, bool allowDup) {
  if (data->maxLen < 1) {
    out->Init(g_EmptyWStrObj);
    return out;
  }
  WStr str;
  str.b = 0; str.e = 0; str.c = 0;
  str.AllocateSelf(data->maxLen + 2);
  *str.e = 0;
  bool accepted = false;
  int tries = 0;
  do {
    tries++;
    if (tries > 5000) {
      if (!accepted) {
        uint32_t idx = g_MathRandomLCG.Uniform(fallback->e - fallback->b);
        WStr* f = &fallback->b[idx];
        if (f != &str) str.assign(f->b, f->e);
      }
      break;
    }
    if (str.e != str.b) {
      *str.b = 0;
      str.e = str.b;
    }
    int exactCount = 0;
    int len = 0;
    if (data->maxLen >= 0) {
      wchar_t a = '^';
      wchar_t b = '^';
      do {
        Key2 k;
        k.a = a;
        k.b = b;
        ChainRow* row = data->chains.FUN_005ec030(&k);
        uint32_t idx = RandomWeightedChoice(&g_MathRandom, row->weights.e - row->weights.b, row->weights.b);
        wchar_t c = row->chars.b[idx];
        uint32_t c32 = c;
        if (c == '$') break;
        if (FLD(uint32_t, 0x3f0) != 0) {
          U16Set* ex = (U16Set*)((char*)this + 0x3dc);
          if (ex->find(c32).node != &ex->anchor) {
            exactCount++;
            if (exactCount > 1) break;
          }
        }
        str.push_back(c);
        len++;
        a = b;
        b = c;
      } while (len <= data->maxLen);
    }
    if (FLD(uint32_t, 0x3f0) == 0 || exactCount == 1) {
      int slen = str.e - str.b;
      if (slen >= data->minLen && slen <= data->maxLen) {
        bool rejected = false;
        bool check = true;
        if (!allowDup) {
          WStrMapT* used = (WStrMapT*)((char*)this + 0x3c0);
          rejected = used->find(str).node != &used->anchor;
          if (rejected) check = false;
        }
        if (check) {
          WStr lower;
          lower.b = 0; lower.e = 0; lower.c = 0;
          lower.AllocateSelf(slen + 1);
          memcpy_thunk(lower.b, str.b, slen * 2);
          lower.e = lower.b + slen;
          *lower.e = 0;
          lower.make_lower();
          WStrSetT* exs = (WStrSetT*)excluded;
          if (exs->find(lower).node == &exs->anchor) {
            for (WStr* sb = subs->b; sb != subs->e; sb++) {
              unsigned sl = sb->e - sb->b;
              unsigned ll = lower.e - lower.b;
              if (sl <= ll) {
                const wchar_t* pos = Search(lower.b, lower.e, sb->b, sb->b + sl);
                if ((pos != lower.e || sl == 0) && (pos - lower.b) != -1) {
                  rejected = true;
                  break;
                }
              }
            }
          } else {
            rejected = true;
          }
          lower.Free();
        }
        accepted = !rejected;
      }
    }
  } while (!accepted);
  Normalize(&str);
  WStrMapT* used = (WStrMapT*)((char*)this + 0x3c0);
  TreeIter res = used->find(str);
  if (res.node == &used->anchor) {
    *used->subscript(str) = 1;
  } else if (allowDup) {
    NameNode* nn = (NameNode*)res.node;
    int cnt = nn->count;
    if (cnt - 1 < (FLD(int, 0x3fc) - FLD(int, 0x3f8)) / 16) {
      nn->count = cnt + 1;
      WStr* suf = (WStr*)((char*)FLD(WStr*, 0x3f8) + (cnt - 1) * 16);
      str.append(suf->b, suf->e);
    } else {
      nn->count = cnt + 1;
      sprintfW(&str, L"%c%d", '-', cnt + 1);
    }
  }
  out->b = 0; out->e = 0; out->c = 0;
  const wchar_t* sb = str.b;
  const wchar_t* sp = sb;
  while (*sp) sp++;
  int n = sp - sb;
  unsigned cap = n + 1;
  if (cap < 2) {
    out->b = g_EmptyWStr; out->e = g_EmptyWStr; out->c = g_EmptyWStr + 1;
  } else {
    wchar_t* p = (wchar_t*)operator new(cap * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\internal\\string.h", 0xd1);
    out->b = p; out->e = p; out->c = p + cap;
  }
  wchar_t* ob = out->b;
  memcpy_thunk(ob, sb, n * 2);
  out->e = ob + n;
  *out->e = 0;
  str.Free();
  return out;
}

static inline void AutoRefAssignNull(PropList*& l) {
  PropList* old = l;
  if (old) { l = 0; old->Release(); }
}

static inline bool PropBool(PropList* l, uint32_t id, bool def) {
  Property* p;
  if (l && l->GetProperty(id, &p) && p->type == 1) {
    char* d = (char*)p;
    if (p->flags & 0x30) d = *(char**)p;
    return *d != 0;
  }
  return def;
}

// @ 0x005EC7C0
void cSPNameGenerator::Init() {
  PropList* list = 0;
  PropMgr* pm = PropertyManager();
  AutoRefAssignNull(list);
  pm->GetPropertyList(0x0fd9c1e3, 0x0461227d, &list);
  if (!list) return;
  FLD(bool, 0x3b8) = FUN_005ebe90(list, 0x026efc90, (char*)this + 0x00, false);
  FLD(bool, 0x3b9) = FUN_005ebe90(list, 0x026efc89, (char*)this + 0x14, false);
  FLD(bool, 0x3ba) = FUN_005ebe90(list, 0x026efc92, (char*)this + 0x28, false);
  FLD(bool, 0x3bb) = FUN_005ebe90(list, 0x1204a915, (char*)this + 0x3c, false);
  FLD(bool, 0x3bc) = FUN_005ebe90(list, 0x042c9060, (char*)this + 0x50, false);
  FLD(bool, 0x3bd) = FUN_005ebe90(list, 0x042c9065, (char*)this + 0x64, false);
  FLD(bool, 0x3be) = FUN_005ebe90(list, 0x05527d05, (char*)this + 0x78, false);
  FLD(bool, 0x3bf) = FUN_005ebe90(list, 0x05527d06, (char*)this + 0x8c, false);
  int lo = 0;
  Property* prop;
  if (list && list->GetProperty(0x0553c23a, &prop) && prop->type == 9) lo = *prop->GetInt();
  int hi = 100;
  if (list && list->GetProperty(0x0553c24b, &prop) && prop->type == 9) hi = *prop->GetInt();
  // mExactlyOneOf set: clear, then refill from the property string
  U16Set* exact = (U16Set*)((char*)this + 0x3dc);
  exact->DoNukeSubtree((void*)FLD(uint32_t, 0x3e8), 0);
  exact->anchor.right = &exact->anchor;
  exact->anchor.left = &exact->anchor;
  exact->anchor.parent = 0;
  exact->anchor.color = 0;
  exact->size = 0;
  WStr exStr;
  exStr.b = g_EmptyWStr; exStr.e = g_EmptyWStr; exStr.c = g_EmptyWStr + 1;
  if (GetPropertyAsString16(list, 0x059346d9, &exStr)) {
    int n = exStr.e - exStr.b;
    for (int i = 0; i < n; i++) exact->insert(exStr.b[i]);
  }
  // mDuplicateSuffixes: clear, then refill from the property array
  StrVec* dup = (StrVec*)((char*)this + 0x3f8);
  dup->erase(dup->b, dup->e);
  int cnt = 0;
  WStr* arr = 0;
  if (GetPropertyAsString16Array(list, 0x05944e2e, &cnt, &arr)) {
    int tag;
    dup->Insert(dup->b, arr, arr + cnt, tag);
  }
  FLD(bool, 0x244) = true;
  FLD(bool, 0x244) = PropBool(list, 0x0302842a, true);
  if (FLD(bool, 0x244)) {
    static const struct { int flag; int vec; int data; } T[8] = {
        {0x3b8, 0x00, 0x270}, {0x3b9, 0x14, 0x248}, {0x3ba, 0x28, 0x298}, {0x3bb, 0x3c, 0x2c0},
        {0x3bc, 0x50, 0x2e8}, {0x3bd, 0x64, 0x310}, {0x3be, 0x78, 0x338}, {0x3bf, 0x8c, 0x360}};
    for (int i = 0; i < 8; i++) {
      if (FLD(bool, T[i].flag)) {
        NameGenData* d = (NameGenData*)((char*)this + T[i].data);
        FUN_005ec130((StrVec*)((char*)this + T[i].vec), d);
        d->minLen = (lo < d->minLen) ? d->minLen : lo;
        d->maxLen = (d->maxLen < hi) ? d->maxLen : hi;
      }
    }
    FUN_005eba70(list, 0x046a3e66, (char*)this + 0x00);
    FUN_005eba70(list, 0x046a3e56, (char*)this + 0x14);
    FUN_005eba70(list, 0x046a4abf, (char*)this + 0x3c);
    FUN_005eba70(list, 0x046a3e75, (char*)this + 0x50);
    FUN_005eba70(list, 0x046a3e84, (char*)this + 0x64);
    FUN_005eba70(list, 0x05529c6a, (char*)this + 0x78);
    FUN_005eba70(list, 0x05529c6b, (char*)this + 0x8c);
    StrVec ex;
    ex.b = 0; ex.e = 0; ex.c = 0;
    FUN_005ebe90(list, 0x03028839, &ex, true);
    WStr* eb = ex.b;
    WStr* ee = ex.e;
    ((StrSet*)((char*)this + 0x388))->insert(eb, ee);
    FUN_005ebe90(list, 0x03028846, (char*)this + 0x3a4, true);
    if (!FLD(bool, 0x3b8)) FUN_005eb440((NameGenData*)((char*)this + 0x270), list, 0x046a3e6a, 0x046a3e6d, 0x046a3e71, (char*)this + 0xa0, 0x5f848353);
    if (!FLD(bool, 0x3b9)) FUN_005eb440((NameGenData*)((char*)this + 0x248), list, 0x04691528, 0x0469152e, 0x04691532, (char*)this + 0xdc, 0x21055651);
    if (!FLD(bool, 0x3bc)) FUN_005eb440((NameGenData*)((char*)this + 0x2e8), list, 0x046a3e78, 0x046a3e7d, 0x046a3e80, (char*)this + 0x118, 0xe44aea33);
    if (!FLD(bool, 0x3bd)) FUN_005eb440((NameGenData*)((char*)this + 0x310), list, 0x046a3e86, 0x046a3e8b, 0x046a3e8e, (char*)this + 0x154, 0xe7ca2d90);
    if (!FLD(bool, 0x3bb)) FUN_005eb440((NameGenData*)((char*)this + 0x2c0), list, 0x046a4ab3, 0x046a4ab7, 0x046a4abb, (char*)this + 0x190, 0x9ea3031a);
    if (!FLD(bool, 0x3be)) FUN_005eb440((NameGenData*)((char*)this + 0x338), list, 0x05529f2c, 0x05529f2d, 0x05529f2e, (char*)this + 0x1cc, 0x78bddf27);
    if (!FLD(bool, 0x3bf)) FUN_005eb440((NameGenData*)((char*)this + 0x360), list, 0x05529f3c, 0x05529f3d, 0x05529f3e, (char*)this + 0x208, 0xc710b6e9);
    ex.DoDestroyValues(eb, ee);
    SpFree(eb);
  }
  exStr.Free();
  if (list) list->Release();
}
