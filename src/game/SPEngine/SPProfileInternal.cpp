// src/game/SPEngine/SPProfileInternal.cpp -- migrated from slice(s) s00687c20 by tools/migrate/rewrite.py
// Object file: SPEngine/SPProfileInternal.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
extern wchar_t* g_regPath;                            // 0x152b344 SOFTWARE\Electronic Arts\... subkey path
extern int g_maxAddonID;                              // 0x152b348
extern "C" wchar_t* eastl_search(const wchar_t* f1, const wchar_t* l1, const wchar_t* f2, const wchar_t* l2);  // 0x5e8ff0
extern "C" unsigned char FUN_006ab6c0(unsigned root, const wchar_t* path, const wchar_t* name, unsigned* out);  // 0x6ab6c0
extern "C" void __cdecl WStr_Format(void* out, const wchar_t* fmt, ...);
#include <stdlib.h>   // atol, strtoul, wcstol (msvcr90 imports)
#include <ctype.h>    // tolower
#include <intrin.h>   // _ReadWriteBarrier

// ---- items of slice s00687c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
extern wchar_t* g_regPath;                            // 0x152b344 SOFTWARE\Electronic Arts\... subkey path
extern int g_maxAddonID;                              // 0x152b348
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);      // 0xf473a0 EA 6-arg operator new
extern "C" wchar_t* eastl_search(const wchar_t* f1, const wchar_t* l1, const wchar_t* f2, const wchar_t* l2);  // 0x5e8ff0
extern "C" int FUN_006abc90(unsigned root, const wchar_t* subkey, struct WStrVec* out);   // 0x6abc90
extern "C" unsigned char FUN_006ab6c0(unsigned root, const wchar_t* path, const wchar_t* name, unsigned* out);  // 0x6ab6c0
extern "C" unsigned char FUN_006ab840(unsigned root, const wchar_t* path, const wchar_t* name, struct WStr* out);      // 0x6ab840
extern "C" void __cdecl WStr_Format(void* out, const wchar_t* fmt, ...);
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
// ---- items of slice s00687c20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" int FUN_006abc90(unsigned root, const wchar_t* subkey, struct WStrVec* out);   // 0x6abc90
extern "C" unsigned char FUN_006ab840(unsigned root, const wchar_t* path, const wchar_t* name, struct WStr* out);      // 0x6ab840
extern EntryVec g_entryVec;                      // 0x15fea00

// @ 0x00687c20
namespace SP {
void ProfEnableAffinityMasks()
{
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
}  // namespace SP
