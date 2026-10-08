// slice s00687c20: SP directory registry (map<unsigned,wstring>), entry table
// (0x15fea00), EA::ArgScript cheat, message poster, ProfEnableAffinityMasks.
// Module flags: /O2 /MD /Gy /TP /EHsc /GS- (old-style EH prolog, no cookie).
#include "types.h"
#include <stdlib.h>   // atol, strtoul, wcstol (msvcr90 imports)
#include <ctype.h>    // tolower
#include <intrin.h>   // _ReadWriteBarrier

// ======================= external callees =======================
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
extern wchar_t* g_regPath;                            // 0x152b344 SOFTWARE\Electronic Arts\... subkey path
extern int g_maxAddonID;                              // 0x152b348

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);      // 0xf473a0 EA 6-arg operator new
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags,
                     const char* pFile, int line);    // matching placement delete (EH cleanup)

extern "C" int __cdecl FUN_00687bc0(int id);          // clamp id against table size (0x687bc0)
extern "C" void* FUN_006bb820();                      // 0x6bb820
extern "C" void* __cdecl FUN_009309b0(void* dest, const wchar_t* src, int a3, int a4);  // 0x9309b0
extern "C" wchar_t* eastl_search(const wchar_t* f1, const wchar_t* l1, const wchar_t* f2, const wchar_t* l2);  // 0x5e8ff0
extern "C" int FUN_006abc90(unsigned root, const wchar_t* subkey, struct WStrVec* out);   // 0x6abc90
extern "C" unsigned char FUN_006ab6c0(unsigned root, const wchar_t* path, const wchar_t* name, unsigned* out);  // 0x6ab6c0
extern "C" unsigned char FUN_006ab840(unsigned root, const wchar_t* path, const wchar_t* name, struct WStr* out);      // 0x6ab840
extern "C" void __cdecl WStr_Format(void* out, const wchar_t* fmt, ...);

// ======================= wide string (16 bytes) =======================
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void* mAllocUnused;   // stateless allocator member (never stored)

  WStr() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
  WStr(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  WStr(const WStr& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  WStr(const wchar_t* pBegin, const wchar_t* pEnd)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(pBegin, pEnd);
  }
  struct InlineTag { InlineTag() {} };
  // Same as the range ctor but with the allocation (EA operator new "App") expanded inline.
  __forceinline WStr(const wchar_t* pBegin, const wchar_t* pEnd, const InlineTag&)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const int n = (int)(pEnd - pBegin);
    const int cap = n + 1;
    if (cap > 1) {
      mpBegin = (wchar_t*)operator new(cap * 2, "App", 0, 0, g_allocFile, 0xd1);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyWString;
      mpCapacity = gEmptyWString + 1;
    }
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~WStr() {
    if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  WStr& operator=(const WStr& x);                  // 0x5c3d90
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                       // 0x4f6510
  void AllocateSelf(int n);                        // 0x429760
  void RangeInitialize(const wchar_t* p);          // 0x579a90
  void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    const int n = (int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
};

struct WStrRange { const wchar_t* begin; const wchar_t* end; };

// pair<unsigned const, wstring> (20 bytes)
struct PairUW {
  unsigned key;
  WStr str;
  PairUW(const unsigned* k, const WStr& src);
  PairUW(const PairUW& o);
};

// vector<wstring> as used here (begin/end/cap + stateless allocator)
struct WStrVec {
  WStr* mpBegin;
  WStr* mpEnd;
  WStr* mpCap;
  void* mAllocUnused;
  WStrVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  void push_back(const WStr& x);                // 0x553f10
  __forceinline ~WStrVec() {
    for (WStr* p = mpBegin; p < mpEnd; ++p) {
      if ((((char*)p->mpCapacity - (char*)p->mpBegin) & ~1) > 2 && p->mpBegin)
        EASTL_allocator_deallocate(p->mpBegin);
    }
    if (mpBegin && ((void**)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
};

// 8-byte insert result (iterator + flag), returned via hidden pointer
struct IterPair { void* first; void* second; };

// ======================= directory map =======================
struct DirMap {
  char pad0[4];
  void Find(void** out, const unsigned* key);   // 0xe5c780 (hidden out-ptr)
  WStr* OpBr(const unsigned* key);              // @ 0x688ad0
  IterPair Insert(void* pos, PairUW* p, int flags);  // 0x6889e0 (sret)
};
extern DirMap g_dirMap;                          // 0x152ba34

// ======================= entry table =======================
struct Entry40 {
  uint8_t b;
  uint8_t pad1[3];
  int a3;
  WStr name;      // +8
  WStr other;     // +0x18
};

struct EntryVec {                                // 0x15fea00
  Entry40* mpBegin;
  Entry40* mpEnd;
  void* mpCap;
  void Grow(int n);                              // 0x687ab0
};
extern EntryVec g_entryVec;                      // 0x15fea00

// ======================= ArgScript =======================
namespace EA { namespace ArgScript {
struct cArguments {
  int NumArguments();                            // 0x837f30
  char* operator[](int i);                       // 0x837f20
};
} }

// message server
struct MessageServer {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void PostMessage(unsigned id, void* data, int flags);  // slot 5 (+0x14)
};
extern MessageServer* MessageServer();           // 0x67dcc0 singleton getter

// registry entry set/get helpers ------------------------------------------------

// @ 0x006886e0
void __fastcall PairDestroy(PairUW* p) {
  p->str.~WStr();
}

// @ 0x006884f0
void EntrySet(int id, unsigned char b, int a3, const WStrRange* p4, const WStrRange* p5) {
  int res = FUN_00687bc0(id);
  if (res == id)
    g_entryVec.mpBegin[res].b = b;
  g_entryVec.mpBegin[id].a3 = a3;
  if (res == id && p4 != (const WStrRange*)&g_entryVec.mpBegin[res].name)
    g_entryVec.mpBegin[res].name.Assign(p4->begin, p4->end);
  if (p5 != (const WStrRange*)&g_entryVec.mpBegin[id].other)
    g_entryVec.mpBegin[id].other.Assign(p5->begin, p5->end);
}

// @ 0x006886b0
const wchar_t* GetDirFromID(unsigned key) {
  void* it;
  g_dirMap.Find(&it, &key);
  if (it != (char*)&g_dirMap + 4)
    return *(wchar_t**)((char*)it + 0x14);
  return 0;
}

// @ 0x00688830
bool GetDirString(unsigned key, WStr* out) {
  void* it;
  g_dirMap.Find(&it, &key);
  if (it != (char*)&g_dirMap + 4) {
    WStr* v = (WStr*)((char*)it + 0x14);
    if (v != out)
      out->Assign((const wchar_t*)v->mpBegin, (const wchar_t*)v->mpEnd);
    return true;
  }
  return false;
}

// @ 0x00688cb0
const wchar_t* GetDataDir() {
  unsigned key = 0xa02149;
  return g_dirMap.OpBr(&key)->mpBegin;
}

// @ 0x00688cd0
const wchar_t* GetDir4a214a() {
  unsigned key = 0xa0214a;
  return g_dirMap.OpBr(&key)->mpBegin;
}

// @ 0x00688cf0
const wchar_t* GetDir4a2150() {
  unsigned key = 0xa02150;
  return g_dirMap.OpBr(&key)->mpBegin;
}

// @ 0x00688d20
struct RefObj688d20 {
  virtual void Destroy(int flags);   // slot 0 vcall
  virtual unsigned Release();
  char pad[0x14];
  unsigned mCount;                   // +0x18
};

unsigned RefObj688d20::Release() {
  if (mCount > 1) {
    mCount = mCount - 1;
    return mCount;
  }
  FUN_006bb820();
  Destroy(1);
  return 0;
}

// @ 0x00688d50
struct Obj6bbc90 {
  Obj6bbc90(void* param);
  char pad[0x20];
};
void PostNewMessage6bbc90(void* param) {
  Obj6bbc90* p = new("App", 0, 0, 0, 0) Obj6bbc90(param);
  MessageServer()->PostMessage(0x24ce124, p, 0);
}

// ======================= ArgScript cheat =======================
// @ 0x00688570
struct cRendererCheat {
  virtual void Execute(EA::ArgScript::cArguments* args);
  WStr mStr;                     // +4
  char pad[0x20c - 0x14];
  EntryVec* mpEntries;           // +0x20c
  int mMode;                     // +0x210
};

void cRendererCheat::Execute(EA::ArgScript::cArguments* args) {
  if (mpEntries) {
    int n = args->NumArguments();
    if ((unsigned)(n - 4) <= 1) {
      int id = atol(args->operator[](1));
      int capped = FUN_00687bc0(id);
      EntryVec* vec = mpEntries;
      Entry40* e = vec->mpBegin + id;
      if (capped == id)
        e->b = 1;
      *(unsigned*)&e->a3 = strtoul(args->operator[](3), 0, 16);
      if (n == 5) {
        WStr tmp;
        WStr_Format(&tmp, L"", args->operator[](4));
        if (capped == id) {
          FUN_009309b0(&mStr, tmp.mpBegin, mMode, 4);
          e->name = mStr;
        }
      }
    }
  }
}

// @ 0x00688bb0
void RegisterDirectory(unsigned key, const wchar_t* path) {
  wchar_t buf[260];
  const wchar_t* src = path;
  if (FUN_009309b0(buf, path, 0, 4))
    src = buf;
  WStr s(src);
  int n = (int)((char*)s.mpEnd - (char*)s.mpBegin) >> 1;
  for (int i = 0; i < n; i++) {
    if (s.mpBegin[i] == 0x5c)
      s.mpBegin[i] = 0x2f;
  }
  if (*(wchar_t*)((char*)s.mpBegin + n * 2 - 2) != 0x2f)
    s.push_back(0x2f);
  WStr* v = g_dirMap.OpBr(&key);
  if ((WStrRange*)&s != (WStrRange*)v)
    v->Assign((const wchar_t*)s.mpBegin, (const wchar_t*)s.mpEnd);
}

// ======================= pair ctors =======================
// @ 0x00688700
PairUW::PairUW(const PairUW& o) : key(o.key), str(o.str.mpBegin, o.str.mpEnd) {}

// @ 0x00688760
PairUW::PairUW(const unsigned* k, const WStr& src) : key(*k), str(src.mpBegin, src.mpEnd) {}

// @ 0x006887c0
struct BigPair {
  char pad[0x10];
  PairUW pair;
  BigPair(const BigPair& o);
};
__declspec(noinline) BigPair::BigPair(const BigPair& o) : pair(o.pair) {}
BigPair* CloneBigPair(const BigPair& o) {
  return new("App", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) BigPair(o);
}

// ======================= map operator[] =======================
// @ 0x00688ad0
WStr* DirMap::OpBr(const unsigned* key) {
  void* anchor = (char*)this + 4;
  void* pos = anchor;
  void* n = *(void**)((char*)this + 0xc);
  if (n) {
    do {
      if (*(unsigned*)((char*)n + 0x10) < *(unsigned*)key)
        n = *(void**)n;
      else {
        pos = n;
        n = *(void**)((char*)n + 4);
      }
    } while (n);
  }
  if (pos == anchor || *key < *(unsigned*)((char*)pos + 0x10)) {
    WStr tmp;
    int flags = 0;
    PairUW p(key, tmp);
    *(unsigned char*)&flags = 0;
    IterPair res = Insert(pos, &p, flags);
    pos = res.first;
  }
  return (WStr*)((char*)pos + 0x14);
}

// ======================= ProfEnableAffinityMasks =======================
__forceinline int WStrLen(const wchar_t* p) {
  const wchar_t* q = p;
  while (*q)
    ++q;
  return (int)(q - p);
}

namespace SP {

// @ 0x00687c20
void ProfEnableAffinityMasks() {
  WStr sPath;          // "%ls\%ls" target
  WStr sDataDir;       // DataDir out
  WStr sProductKey;    // ProductKey out
  WStrVec vSub;
  WStrVec vBanned;
  WStrVec vRequired;
  {
    WStr t(L"spore_bp");
    vBanned.push_back(t);
  }
  {
    WStr t(L"spore creepy and cute parts pack");
    vBanned.push_back(t);
  }
  {
    WStr t(L"spore(tm) creepy & cute parts pack");
    vBanned.push_back(t);
  }
  {
    WStr t(L"spore bp");
    vBanned.push_back(t);
  }
  {
    WStr t(L"spore_ep");
    vRequired.push_back(t);
  }
  {
    WStr t(L"test");
    vRequired.push_back(t);
  }
  int nSub = FUN_006abc90(0x80000002, g_regPath, &vSub);
  if (nSub > 0) {
    const WStr* it = vSub.mpBegin;
    for (int c = nSub; c != 0; --c, ++it) {
      const wchar_t* sb = it->mpBegin;
      const wchar_t* se = it->mpEnd;
      WStr sub(sb, se, WStr::InlineTag());
      int n = (int)((char*)se - (char*)sb) >> 1;
      for (wchar_t* q = sub.mpBegin; q < (wchar_t*)sub.mpEnd; ++q) {
        wchar_t w = *q;
        if ((unsigned)w <= 0xff)
          *q = (wchar_t)tolower((unsigned char)w);
      }
      int hayLen = (int)((char*)sub.mpEnd - (char*)sub.mpBegin) >> 1;
      bool bBanned = false;
      {
        int cnt = (int)((char*)vBanned.mpEnd - (char*)vBanned.mpBegin) >> 4;
        const WStr* p = vBanned.mpBegin;
        for (; cnt != 0; --cnt, ++p) {
          const wchar_t* nb = p->mpBegin;
          int nn = (int)((char*)p->mpEnd - (char*)nb) >> 1;
          if ((unsigned)nn <= (unsigned)hayLen) {
            const wchar_t* r = eastl_search(sub.mpBegin, sub.mpEnd, nb, nb + nn);
            if (r != sub.mpEnd || nn == 0) {
              if (((int)((char*)r - (char*)sub.mpBegin) >> 1) != -1)
                bBanned = true;
            }
          }
        }
      }
      if (!bBanned) {
        bool bReq = false;
        {
          int cnt = (int)((char*)vRequired.mpEnd - (char*)vRequired.mpBegin) >> 4;
          const WStr* p = vRequired.mpBegin;
          for (; cnt != 0; --cnt, ++p) {
            const wchar_t* nb = p->mpBegin;
            int nn = (int)((char*)p->mpEnd - (char*)nb) >> 1;
            if ((unsigned)nn <= (unsigned)hayLen) {
              const wchar_t* r = eastl_search(sub.mpBegin, sub.mpEnd, nb, nb + nn);
              if (r != sub.mpEnd || nn == 0) {
                if (((int)((char*)r - (char*)sub.mpBegin) >> 1) != -1)
                  bReq = true;
              }
            }
          }
        }
        bool bValid = false;
        unsigned id = 0;
        if (bReq) {
          const wchar_t* lit = L"spore bp1";
          const wchar_t* le = lit;
          while (*le)
            ++le;
          int litLen = (int)(le - lit);
          int nMin1 = (n < 9) ? n : 9;
          int nMin2 = (nMin1 < litLen) ? nMin1 : litLen;
          int cmpResult;
          {
            const wchar_t* p1 = sub.mpBegin;
            const wchar_t* p2 = lit;
            int cnt = nMin2;
            if (cnt > 0) {
              do {
                if (*p1 != *p2) {
                  cmpResult = (*p1 < *p2) ? -1 : 1;
                  goto cmpDone;
                }
                ++p1;
                ++p2;
                --cnt;
              } while (cnt);
            }
            cmpResult = (nMin1 < litLen) ? -1 : (nMin1 > litLen);
          cmpDone:;
          }
          bool bIsBP1 = (cmpResult == 0);
          WStr_Format(&sPath, L"%ls\\%ls", g_regPath, sub.mpBegin);
          unsigned id = bIsBP1;
          bool bValid = FUN_006ab6c0(0x80000002, sPath.mpBegin, L"AddOnID", &id);
          if (!bValid) {
            WStr tmp;
            if (FUN_006ab840(0x80000002, sPath.mpBegin, L"AddOnID", &tmp)) {
              id = wcstol(tmp.mpBegin, 0, 16);
              bValid = ((unsigned)(id - 1) <= 998);
            }
          }
          if (bIsBP1 || bValid) {
            if (id < 1000) {
              int capped = (int)id;
              int bad = -1;
              if ((int)g_maxAddonID < (int)id) {
                g_entryVec.Grow((int)id + 1);
                g_maxAddonID = capped;
              }
              Entry40* eb = g_entryVec.mpBegin;
              if (capped == 2 || capped >= (int)((char*)g_entryVec.mpEnd - (char*)eb) / (int)sizeof(Entry40))
                capped = bad;
              if (capped == (int)id)
                eb[capped].b = 1;
              unsigned packID = 0;
              if (FUN_006ab6c0(0x80000002, sPath.mpBegin, L"PackID", &packID))
                g_entryVec.mpBegin[id].a3 = (int)packID;
              if (FUN_006ab840(0x80000002, sPath.mpBegin, L"DataDir", &sDataDir)) {
                if (capped == (int)id) {
                  WStr* dst = &g_entryVec.mpBegin[capped].name;
                  if (&sDataDir != dst)
                    dst->Assign((const wchar_t*)sDataDir.mpBegin, (const wchar_t*)sDataDir.mpEnd);
                }
              }
              if (FUN_006ab840(0x80000002, sPath.mpBegin, L"ProductKey", &sProductKey)) {
                WStr* dst = &g_entryVec.mpBegin[id].other;
                if (&sProductKey != dst)
                  dst->Assign((const wchar_t*)sProductKey.mpBegin, (const wchar_t*)sProductKey.mpEnd);
              }
            }
          }
        }
      }
    }
  }
}

}
