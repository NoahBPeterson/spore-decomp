#include "types.h"
#include <string.h>

// Slice s00669f50 - cSPUIFeedListItem helpers and comparators.

struct VObj { void** vt; };
struct CItem { char pad[0xc]; int* p; };
typedef int  (__thiscall *FnRetInt)(void*);
typedef long long (__thiscall *FnRetLL)(void*);
typedef bool (__thiscall *FnRetBool)(void*);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef int  (__thiscall *FnV2iR)(void*, int, int);
unsigned __cdecl FUN_006b8ea0(int, int, int);

// ------------------------------------------------------------------
// @ 0x0066a5c0
extern int g_ids24[24];
int FindIndex0066a5c0(int x) {
  int i = 0;
  do {
    if (x == g_ids24[i]) return i;
    ++i;
  } while (i < 0x18);
  return 0x18;
}

// ------------------------------------------------------------------
// @ 0x0066a5e0
struct FillBuf {
  int a0, a1, a2, a3, a4, a5, m18;
  bool m1c;
  void Set(unsigned char b, int p);
};
void FillBuf::Set(unsigned char b, int p) {
  memset(this, b, 0x18);
  m18 = p;
  m1c = false;
}

// ------------------------------------------------------------------
// @ 0x0066a610
struct Neger {
  int Neg(int a, int b);
};
int Neger::Neg(int a, int b) {
  return -((FnV2iR)((VObj*)this)->vt[5])(this, a, b);
}

// ------------------------------------------------------------------
// @ 0x0066a630
struct Switcher {
  int pad0; int pad1; int m8;
  unsigned Get();
};
unsigned Switcher::Get() {
  switch (m8) {
  case 0: return 0x2dfb4f9f;
  case 1: return 0xa28a67e8;
  case 2: return 0x5cd23f68;
  case 3: return 0x93b9d42e;
  case 4: return 0x38f64117;
  default: return 0;
  }
}

// ------------------------------------------------------------------
// @ 0x0066ad70
struct Switcher2 {
  int pad0; int pad1; int m8;
  unsigned Get();
};
unsigned Switcher2::Get() {
  switch (m8) {
  case 0: return 0x7ca87ec2;
  case 1: return 0x3019275;
  case 2: return 0x1d7707e0;
  default: return 0;
  }
}

// ------------------------------------------------------------------
// @ 0x0066a800
extern int* g_vecBegin15fb19c;
extern int* g_vecEnd15fb1a0;
int GetElem0066a800(int i) {
  if (i >= 0 && i < (int)(g_vecEnd15fb1a0 - g_vecBegin15fb19c))
    return g_vecBegin15fb19c[i];
  return 0;
}

// ------------------------------------------------------------------
// Lookup used by the comparators: object at arg+0xc has a subobject at
// +0x10 whose slot 3 returns a pointer for the given id.
__forceinline int* Lookup0066(void* a) {
  int* p = *(int**)((char*)a + 0xc);
  return p ? (int*)((FnV0i)((VObj*)((char*)p + 0x10))->vt[3])(
                 (VObj*)((char*)p + 0x10), 0x13d55dc8)
           : 0;
}

// ------------------------------------------------------------------
// @ 0x0066ab90
struct Cmp0c {
  unsigned operator()(int a, int b);
};
unsigned Cmp0c::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[3])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[3])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ac10
struct Cmp10 {
  unsigned operator()(int a, int b);
};
unsigned Cmp10::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[4])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[4])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aca0
struct Cmp70 {
  unsigned operator()(int a, int b);
};
unsigned Cmp70::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      unsigned char x = ((FnRetBool)((VObj*)p)->vt[28])(p);
      unsigned char y = ((FnRetBool)((VObj*)*(int**)(b + 0xc))->vt[28])(*(int**)(b + 0xc));
      if (y == x) return 0;
      return (y < x) ? 0xffffffffu : 1u;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ad10
struct Cmp38 {
  unsigned operator()(CItem& a, CItem& b);
};
unsigned Cmp38::operator()(CItem& a, CItem& b) {
  int* p = a.p;
  if (p) {
    if (b.p) {
      int x = ((FnRetInt)((VObj*)p)->vt[14])(p);
      int y = ((FnRetInt)((VObj*)b.p)->vt[14])(b.p);
      if (x == y) return 0;
      return (x <= y) ? 1u : 0xffffffffu;
    }
    if (a.p) return 0xffffffff;
  }
  return b.p != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aa40
struct Cmp28 {
  unsigned operator()(int a, int b);
};
unsigned Cmp28::operator()(int a, int b) {
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      long long x = ((FnRetLL)((VObj*)p)->vt[10])(p);
      long long y = ((FnRetLL)((VObj*)*(int**)(b + 0xc))->vt[10])(*(int**)(b + 0xc));
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// ------------------------------------------------------------------
// @ 0x0066aad0
struct Cmp94 {
  unsigned operator()(int a, int b);
};
unsigned Cmp94::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      long long x = ((FnRetLL)((VObj*)p)->vt[37])(p);
      long long y = ((FnRetLL)((VObj*)q)->vt[37])(q);
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// ------------------------------------------------------------------
// @ 0x0066a950
struct Cmp950 {
  unsigned operator()(int a, int b);
};
unsigned Cmp950::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) {
        if (((FnRetBool)((VObj*)q)->vt[30])(q)) {
          int x = ((FnRetInt)((VObj*)p)->vt[34])(p);
          int y = ((FnRetInt)((VObj*)q)->vt[34])(q);
          if (x == y) return 0;
          return (x <= y) ? 1u : 0xffffffffu;
        }
      }
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) return 0xffffffff;
      return ((FnRetBool)((VObj*)q)->vt[30])(q) != 0;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// ------------------------------------------------------------------
// @ 0x0066ada0
struct CmpAd {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
unsigned CmpAd::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 1) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 1) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = fa[0]; y = fb[0]; break;
    case 1: x = fa[1]; y = fb[1]; break;
    case 2: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}

typedef int (__thiscall *FnCmp2)(void*, void*, void*);

// SP::cSPUIFeedListItem::Init stubs (retail layout; offsets from the disassembly)
extern wchar_t g_EmptyW[2];                 // 0x01667bac (eastl shared empty string)
void __cdecl operator_delete_array(void* p);  // 0x00f47380
void* __cdecl operator_new_tag(unsigned size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0

struct FStr {                               // eastl::basic_string<wchar_t> (16 bytes)
  wchar_t* mb;
  wchar_t* me;
  wchar_t* mc;
  int mAlloc;
  FStr() { mb = g_EmptyW; me = g_EmptyW; mc = g_EmptyW + 1; }
  FStr(const FStr& o);                      // 0x0056e2d0
  ~FStr() { Dealloc(); }
  void Append(const wchar_t* p);            // 0x005c3d90
  void AppendStr(const FStr* o);            // 0x00667c40
  int FindA(const wchar_t* p, int pos);     // 0x00630630
  int FindB(const wchar_t* p, int pos);     // 0x00608340
  FStr* Substr(FStr* out, int pos, int n);  // 0x00453d20 (ret 0xc)
  void MakeLower();                         // 0x005e8e80
  void Dealloc();                           // 0x00933960
};
struct CStr {                               // SP::cString (0x14 bytes)
  char d[0x14];
  CStr();                                   // 0x006b5060
  ~CStr();                                  // 0x006b5240
  wchar_t* GetText();                       // 0x006b55c0
};
struct Prop {
  char pad[0x12];
  unsigned short type;
  bool* GetBool();                          // 0x0041e920
  unsigned* GetUInt();                      // 0x0041ea00
};
struct NarrowStr {
  void Assign(const void* o);               // 0x00579c60 basic_string<char>::operator=
};
struct Obj5467 {
  int F5467e0();                            // 0x005467e0
};

bool __cdecl GetPropertyAsText(void* pl, unsigned key, CStr* out);        // 0x006a1360
void __cdecl GetPropertyAsKeyInstance(void* pl, unsigned key, unsigned* out);  // 0x006a12a0
void __cdecl GetPropertyAsKey(void* pl, unsigned key, unsigned* out);     // 0x006a1250
void __cdecl GetPropertyAsUint32(void* pl, unsigned key, unsigned* out);  // 0x004af210
void __cdecl GetBoolProp(void* pl, unsigned key, bool* out);              // 0x00407190
void* PropertyManager();                    // 0x0067de30
void* ConfigManager();                      // 0x0067dd30
void* MessageServer();                      // 0x0067dcc0
void* AuthManager();                        // 0x00607a60
struct LayoutObj {
  LayoutObj* Ctor();                        // 0x00810000 (cConnectionDialog ctor)
  void Init(unsigned* key, int a, unsigned b);        // 0x008120d0
  void SetParentWin(int win, int a, unsigned b);      // 0x008121b0
  void SetReloadCallback(void* cb, void* self);       // 0x00810090
};
void __cdecl ReloadCallback(void* self, void* layout, int flag);   // 0x00669430
extern unsigned g_1527824;                  // 0x01527824
extern unsigned g_140041c;                  // 0x0140041c
extern unsigned g_Keys24[24];               // 0x01400480
extern unsigned g_MsgIds[2];                // 0x014003a0

#define VTS(o, off) ((*(void***)(o))[(off) / 4])

struct FeedItemInit {
  char pad0[4];
  char sub4[0x10];
  bool b14;                 // +0x14
  char pad15;
  bool b16;                 // +0x16
  char pad17;
  FStr s18;                 // +0x18
  FStr s28;                 // +0x28
  unsigned u38, u3c;        // +0x38
  FStr s40;                 // +0x40
  NarrowStr s50;            // +0x50
  char pad54[0x60 - 0x54];
  int count60;              // +0x60
  char pad64[0x78 - 0x64];
  unsigned key78;           // +0x78
  char pad7c[0x90 - 0x7c];
  void* ref90;              // +0x90
  void* layout94;           // +0x94
  void* ref98;              // +0x98
  void* ref9c;              // +0x9c
  char pada0[0xc0 - 0xa0];
  bool bc0;                 // +0xc0
  char padc1[0x114 - 0xc1];
  void* ahServer;           // +0x114
  void* ahHandler;          // +0x118
  void* ahIds;              // +0x11c
  int ahCount;              // +0x120
  int ahPrio;               // +0x124
  unsigned u128, u12c;      // +0x128
  int i130;                 // +0x130
  int i134;                 // +0x134
  unsigned u138;            // +0x138
  int i13c;                 // +0x13c
  bool b140;                // +0x140
  bool b141;                // +0x141
  char pad142[2];
  unsigned u144, u148, u14c, u150, u154;   // +0x144
  bool flags158[24];        // +0x158
  unsigned u170;            // +0x170
  char pad174[4];
  unsigned typeKey;         // +0x178
  unsigned propId;          // +0x17c
  void* propList;           // +0x180
  char pad184[4];
  unsigned u188;            // +0x188
  void* GetAssetList(void* vec);            // 0x00668d90 (ret 4)
  bool Init(void* a1, void* a2, unsigned a3, void* a4, int a5);
};

struct AssetVec { char* b; char* e; char* c; };

// @ 0x00669f50
bool FeedItemInit::Init(void* a1, void* a2, unsigned a3, void* a4, int a5) {
  (void)a5;
  Prop* prop;
  {   // AutoRefCount assignments
    void* old = ref98;
    if (a1 != old) {
      if (a1) ((void(__thiscall*)(void*))VTS(a1, 0))(a1);
      ref98 = a1;
      if (old) ((void(__thiscall*)(void*))VTS(old, 4))(old);
    }
  }
  {
    void* old = ref9c;
    if (a2 != old) {
      if (a2) ((void(__thiscall*)(void*))VTS(a2, 0))(a2);
      ref9c = a2;
      if (old) ((void(__thiscall*)(void*))VTS(old, 4))(old);
    }
  }
  propId = a3;
  {
    void* old = ref90;
    if (a4 != old) {
      if (a4) ((void(__thiscall*)(void*))VTS(a4, 8))(a4);
      ref90 = a4;
      if (old) ((void(__thiscall*)(void*))VTS(old, 0xc))(old);
    }
  }
  b14 = true;
  void* pm = PropertyManager();
  if (propList != 0) {
    void* old = propList;
    propList = 0;
    ((void(__thiscall*)(void*))VTS(old, 4))(old);
  }
  ((void(__thiscall*)(void*, unsigned, unsigned, void**))VTS(pm, 0x2c))(pm, propId, 0x4e5892eb, &propList);
  if (propList != 0) {
    void* cm = ConfigManager();
    int cfg = ((int(__thiscall*)(void*, unsigned))VTS(cm, 0x30))(cm, 0x5de7b4a);
    if (cfg == 1 && propList != 0 &&
        ((bool(__thiscall*)(void*, unsigned, Prop**))VTS(propList, 0x24))(propList, 0x6397993, &prop) &&
        prop->type == 1 && *prop->GetBool() == false)
      return false;
    if (propList != 0 &&
        ((bool(__thiscall*)(void*, unsigned, Prop**))VTS(propList, 0x24))(propList, 0x6678df3, &prop) &&
        prop->type == 10)
      u188 = *prop->GetUInt();
    GetPropertyAsKeyInstance(propList, 0x744717c3, &typeKey);
    if (typeKey != 0xffffffff) {
      CStr text1;
      if (GetPropertyAsText(propList, 0x744717c5, &text1))
        s18.Append(text1.GetText());
      CStr text2;
      if (GetPropertyAsText(propList, 0x5af1baf, &text2))
        s40.Append(text2.GetText());
      GetBoolProp(propList, 0x74b839b7, &b16);
      GetBoolProp(propList, 0x744717c8, &bc0);
      GetPropertyAsKey(propList, 0xf4906970, &key78);
      GetBoolProp(propList, 0xb5135387, &b141);
      GetPropertyAsKeyInstance(propList, 0x5e90865, &u150);
      GetPropertyAsKeyInstance(propList, 0x5e9086c, &u154);
      unsigned k = typeKey;
      if (k == 0x11f44f6b || k == 0xe8104769 || k == 0x48a6f111) {
        int i = 0;
        do {
          if (propList != 0 &&
              ((bool(__thiscall*)(void*, unsigned, Prop**))VTS(propList, 0x24))(propList, g_Keys24[i], &prop) &&
              prop->type == 1)
            flags158[i] = *prop->GetBool();
          i++;
        } while (i < 0x18);
        GetPropertyAsKeyInstance(propList, g_140041c, &u170);
      }
      switch (typeKey) {
      case 0xe8104769:
        GetPropertyAsKeyInstance(propList, 0x56b8d5e, &u144);
        break;
      case 0xaabe8769:
        GetPropertyAsKeyInstance(propList, 0x144d7575, &u14c);
        break;
      case 0x984b7145:
        GetPropertyAsKeyInstance(propList, 0x58b92cd, &u12c);
        break;
      case 0x11f44f6b: {
        GetPropertyAsKeyInstance(propList, 0x744717c6, &u138);
        int* b = (int*)a2;
        if (b != 0) {
          int v = b[0x10];
          i130 = v & ((v < 0) - 1);
          s28.Append((const wchar_t*)b[0]);
          u38 = b[4];
          u3c = b[5];
          i13c = b[0x1a];
          i134 = ((Obj5467*)b)->F5467e0();
          s50.Assign(b + 0x15);
          void* am = AuthManager();
          long long id = ((long long(__thiscall*)(void*))VTS(am, 0x40))(am);
          unsigned lo = (unsigned)id, hi = (unsigned)(id >> 32);
          if ((unsigned)b[4] == lo && (unsigned)b[5] == hi)
            b140 = 1;
          else
            b140 = 0;
          int kind = b[0x1a];
          if (kind == 2) {
            s18.Append((const wchar_t*)b[0]);
            {
              FStr tmp(s18);
              tmp.MakeLower();
              if (tmp.FindB(L"maxis", 0) != -1)
                key78 = 0xf29655f5;
            }
          } else if (kind == 3) {
            FStr tmp;
            tmp.Append((const wchar_t*)b[6]);
            if (tmp.FindA(L"Assets tagged", 0) != -1) {
              FStr sub;
              s18.AppendStr(tmp.Substr(&sub, 0xf, (int)(tmp.me - tmp.mb) - 0x10));
            }
          } else {
            s18.Append((const wchar_t*)b[6]);
          }
        }
        break;
      }
      case 0x793a246b:
        GetPropertyAsKeyInstance(propList, 0x744717c4, &u128);
        break;
      case 0x48a6f111:
        GetPropertyAsUint32(propList, 0x71d9ed4, &u148);
        break;
      default:
        break;
      }
    }
  }
  AssetVec av;
  av.b = 0; av.e = 0; av.c = 0;
  GetAssetList(&av);
  int cnt = (int)(av.e - av.b) >> 4;
  if (av.b != 0 && *(int*)(av.b - 4) != 0)
    operator_delete_array(av.b);
  count60 = cnt;
  LayoutObj* lay;
  void* mem = operator_new_tag(0x18, "Sporepedia", 0, 0, 0, 0);
  if (mem != 0)
    lay = ((LayoutObj*)mem)->Ctor();
  else
    lay = 0;
  {
    void* old = layout94;
    if ((void*)lay != old) {
      if (lay) ((void(__thiscall*)(void*))VTS(lay, 4))(lay);
      layout94 = lay;
      if (old) ((void(__thiscall*)(void*))VTS(old, 8))(old);
    }
  }
  struct Key3 { unsigned a, b, c; } key3;
  key3.c = g_1527824;
  key3.a = 0xc1966e00;
  key3.b = 0x510a95b;
  ((LayoutObj*)layout94)->Init((unsigned*)&key3, 1, 0x5b598fa);
  ((LayoutObj*)layout94)->SetParentWin((int)ref98, 1, 0x5b598fa);
  ((LayoutObj*)layout94)->SetReloadCallback((void*)ReloadCallback, this);
  ReloadCallback(this, layout94, 1);
  void* handler = sub4;
  void* srv = MessageServer();
  ahServer = srv;
  ahHandler = handler;
  ahIds = g_MsgIds;
  ahCount = 2;
  ahPrio = 0;
  if (srv != 0 && handler != 0) {
    for (unsigned u = 0; u < 8; u += 4)
      ((void(__thiscall*)(void*, void*, unsigned))VTS(srv, 0x24))(srv, handler, *(unsigned*)((char*)g_MsgIds + u));
  }
  return true;
}

// @ 0x0066a830
struct Sorter830 {
  int pad0, pad1, pad2;   // +0x0..+0xc
  int* mC;                // +0xc
  int* m10;               // +0x10
  char pad14[0xc];
  bool m20;               // +0x20
  bool operator()(void* pa, void* pb);
};
bool Sorter830::operator()(void* pa, void* pb) {
  unsigned char* a = (unsigned char*)pa;
  unsigned char* b = (unsigned char*)pb;
  bool r = b[0x1c] < a[0x1c];
  if (b[0x1c] != a[0x1c]) return r;
  unsigned char a1 = a[0x1d];
  unsigned char av = 0, bv = 0;
  if (a1 == 0 && *(void**)(a + 4) != 0 && *(char*)((char*)*(void**)(a + 4) + 0xf4) != 0) av = 1;
  if (b[0x1d] == 0 && *(void**)(b + 4) != 0 && *(char*)((char*)*(void**)(b + 4) + 0xf4) != 0) bv = 1;
  r = bv < av;
  if (bv != av) return r;
  r = b[0x1d] < a1;
  if (b[0x1d] != a1) return r;
  int n = (int)(m10 - mC);
  for (int i = 0; i < n; ++i) {
    int* obj;
    int slot;
    if (i == 0 && m20) { obj = (int*)*mC; slot = 6; }
    else { obj = (int*)mC[i]; slot = 5; }
    int res = ((FnCmp2)((VObj*)obj)->vt[slot])(obj, pa, pb);
    if (res != 0) return res < 0;
  }
  unsigned x = *(unsigned*)a, y = *(unsigned*)b;
  r = x < y;
  if (x == y) {
    if (a[4] == b[4] && a[8] == b[8]) return false;
    if (a[8] != b[8]) return a[8] < b[8];
    return a[4] < b[4];
  }
  return r;
}
// @ 0x0066af20
struct Vec3 { int* begin; int* end; int* cap; };
void vec_cctor(void*, int, void*);
void FUN_01022c60(void*, void*, void*, void*, void*);
struct CtorAf {
  void* vt;              // +0
  int m4;                // +4
  int m8;                // +8
  Vec3 mC;               // +0xc
  char pad18[8];
  bool m20;              // +0x20
  bool m21;              // +0x21
  int m24, m28, m2c, m30;
  CtorAf(int p2, Vec3* p3);
};
CtorAf::CtorAf(int p2, Vec3* p3) {
  m4 = 0;
  vt = (void*)0x1400620;
  m8 = p2;
  vec_cctor(&mC, (int)(p3->end - p3->begin), (void*)((char*)p3 + 0xc));
  int v = p2;
  void* out;
  FUN_01022c60(&v, p3->begin, p3->end, mC.begin, &out);
  mC.end = (int*)v;
  m20 = false;
  m24 = 0;
  m21 = true;
  m28 = 0;
  m2c = 0;
  m30 = 0;
}

// @ 0x0066a680
struct CmpA680 {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
unsigned CmpA680::operator()(int a, int b) {
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 0) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 0) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = (*(int*)fa == 1) ? 1.0f : 0.0f; y = (*(int*)fb == 1) ? 1.0f : 0.0f; break;
    case 1: x = (*(int*)fa == 2) ? 1.0f : 0.0f; y = (*(int*)fb == 2) ? 1.0f : 0.0f; break;
    case 2: x = (*(int*)fa == 3) ? 1.0f : 0.0f; y = (*(int*)fb == 3) ? 1.0f : 0.0f; break;
    case 3: x = fa[1]; y = fb[1]; break;
    case 4: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}
