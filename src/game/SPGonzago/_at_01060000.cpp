// src/game/SPGonzago/_at_01060000.cpp -- migrated from slice(s) s01064990, s01063a10 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01060000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s01063a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
void* __cdecl FUN_01002bd0();                          // 0x01002bd0 SP::SpaceGameGet
void* __cdecl FUN_00bfc5f0(void* self);                // 0x00bfc5f0 cGameData::SetGameDataOwner2
s32   __cdecl FUN_00fe4150(void* self, void* noun);    // 0x00fe4150 cSPBadgeManager::GetBadgeState
void* __cdecl FUN_00fe41c0(void* self, void* noun);    // 0x00fe41c0 cSPBadgeManager::GetReplacement
void* __cdecl FUN_00fe5520(void* self, void* a, void* b);     // 0x00fe5520 GetBadgeImageKey
float __cdecl FUN_00fe6690(void* self, void* noun);    // 0x00fe6690
u8    __cdecl FUN_00fe46a0(void* self, void* noun);    // 0x00fe46a0
u8    __cdecl FUN_00fe4180(void* self, void* noun);    // 0x00fe4180 DoInsertValue
void* __cdecl FUN_00e0a780(void* self, u32 id, u32 n); // 0x00e0a780
void* __cdecl FUN_00e09c90(void* self, u32 idx);       // 0x00e09c90
void* __cdecl FUN_00e18600(void* self, void* a, void* b);  // 0x00e18600
void* __cdecl FUN_008105b0(void);                     // 0x008105b0 cSPUILayout::FindWindowByID (2-arg thiscall)
void* __cdecl FUN_00575ea0(void* self);                // 0x00575ea0 GetDefaultIconDrawable
void* __cdecl FUN_00b3d3f0();                          // 0x00b3d3f0 returns pointer in eax
void  __cdecl FUN_00e30a60(void* self, void* a);       // 0x00e30a60
void  __cdecl FUN_00e30e20(void* a, void* b, u32 c, void* d, void* e);  // 0x00e30e20
void* __cdecl FUN_00662960(void* self, void* a);       // 0x00662960 FeedList::Find
void  __cdecl FUN_00666630(void* self, void* a, void* b);  // 0x00666630 CFeed::Reserve
void  __cdecl FUN_006666c0(void* self, void* a);       // 0x006666c0 CItem::Refresh
void* __cdecl FUN_004558a0(void* a, void* b, u32 n);   // 0x004558a0 VectorInsertU32
void* __cdecl FUN_00f14120(void* self, void* fmt, ...); // 0x00f14120
void* __cdecl FUN_010634b0(void* self, void* a, float b);  // 0x010634b0
void  __cdecl FUN_00807cb0(void* a, void* b, int c);   // 0x00807cb0
// ---- items of slice s01063a10 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall FUN_01063f70(void* self, void* /*edx*/);  // 0x01063f70 (stays in the slice: not this object's)

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
void memcpy_11e0744(void*, const void*, unsigned int);
void*  FUN_00b3d3d0();
class cString12;
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CFeedItem
{
public:
    void  Reserve_666630(int a, int b);
    void  Refresh_6666c0(const wchar_t* text);
    void  FUN_00666660(int a);
    bool  CheckFlag_666680(int a);
    void  Release();
};
class CFeedList
{
public:
    void  FUN_006628d0();
    void  FUN_00662920(int on);
    void* FUN_00662a20(int a);
    void  FUN_00662c10(void* item);
    void  FUN_00663350(int a);
    unsigned FUN_00664600();
    void* FUN_00664610(unsigned idx);
};
class cString12
{
public:
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCap;          // +0x08
    int   mFlag0c;        // +0x0c

    void  Assign_01064d80(const void* begin, const void* end);
    cString12* InsertRange_01064df0(const void* begin, const void* end);
    void  Swap_01065510(cString12* other);
    void  Resize_01065860(uint32_t n);
    void  Assign2_010652d0(const void* begin, const void* end);
    void  Reserve_01065270(uint32_t n);
    void  Init_6b5770(uint32_t a, int b, int c);
    const wchar_t* GetText_6b55c0();
};
class cEmpire;
struct Sub48
{
    void  Init_00e0a390();
    void  FUN_00e0a5c0();
    void  FUN_00e0a400();
    bool  FUN_00e0a780(int a, void* b);
    void* FUN_00e09c90(int a, int b, int c);
    char  mBody[0x70];
};
struct FilterNode
{
    FilterNode* mpNext;    // +0
    void*       mpPrev;    // +4
    void*       mpKey;     // +8
};
class cEmpire
{
public:
    void*       mpVtbl0;        // +0x00
    char        mPad04[4];      // +0x04
    void*       mpVtbl1;        // +0x08
    void*       mpVtbl2;        // +0x0c
    char        mPad10[4];      // +0x10
    int         m14;            // +0x14
    CLayout*    mpLayout;       // +0x18
    char        mPad1c[0x34 - 0x1c];
    FilterNode  mFilterHead;    // +0x34
    char        mb40;           // +0x40
    char        mPad41[3];
    void*       m44;            // +0x44
    Sub48       m48;            // +0x48
    void*       mpSFV;          // +0xb8
    void*       mpMsgServer;    // +0xbc
    void*       mpIdentity;     // +0xc0
    int         mMsgId;         // +0xc4
    int         mC8;            // +0xc8
    int         mCC;            // +0xcc
    CFeedList*  mpFeedList;     // +0xd0
    CFeedItem*  mpSelected;     // +0xd4

    void InitBase_00e18bb0();
    void OnWinProcAdd_010829f0(int arg);
    void BaseDestroy_00e18810();
    void BaseDestroy2_00e18980();
    void Show_00e18860(int arg);
    void SetText_00e18890(void* text);

    cEmpire();
    ~cEmpire();

    void Destroy_01064990();
    void OnWinProcAdd_01064a00(int arg);
    void PopulateLeft_01064b60();
    void Init_01064fd0();
    void PopulateFeed_010655a0();
    void Show_01065900(int arg);
};
// ---- items of slice s01064990 end

// @ 0x01064000
u8 __fastcall FUN_01064000(void* self, void* /*edx*/, s32 tag, void* arg2)
{
  char* p = (char*)self;
  if (tag == (s32)0xb3d53f95) {
    char* p19c = *(char**)(p + 0x19c);
    void* noun = *(void**)(p19c + 0x17c);
    char* mgr = (char*)FUN_00b3d3f0();
    FUN_00e30a60(*(void**)(mgr + 0x5c), noun);
    char* nd = *(char**)((char*)arg2 + 0x10);
    char* old = *(char**)(p + 0x19c);
    if (nd != old) {
      if (nd != 0) {
        (*(void(__thiscall**)(char*))(*(void***)nd + 0))(nd);
      }
      *(char**)(p + 0x19c) = nd;
      if (old != 0) {
        (*(void(__thiscall**)(char*))(*(void***)old + 1))(old);
      }
    }
    FUN_01063f70(p - 0xc, 0);
    return 1;
  }
  return (u8)(u32)FUN_00e18600(p, (void*)tag, arg2);
}

// @ 0x01064080
void __fastcall FUN_01064080(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  char* game = (char*)FUN_01002bd0();
  char* tribe = (char*)FUN_00bfc5f0(game);

  char* feed = (char*)((s32(__thiscall*)(void*, u32))FUN_00662960)(
      *(void**)(p + 0x1a4), 0x62146e6d);
  if (feed == 0) return;

  // Feed source: count + begin pointer of the tribe's badge-noun list.
  s32 cnt;
  u32* base;
  ((void(__thiscall*)(void*, s32*, u32**))FUN_00666630)(feed, &cnt, &base);

  // Selected nouns accumulate into a local eastl-style vector.
  u32* sel = 0;        // begin                 [esp+0x3c]
  u32* selEnd = 0;     // end                   [esp+0x40]
  u32* selCap = 0;     // allocation end        [esp+0x44]
  s32 kept = 0;        // count of active rows  [esp+0x2c]
  s32 i = 0;           // loop counter          [esp+0x20]
  if (cnt > 0) {
    s32 off = 0;
    do {
      u32 noun = *(u32*)((char*)base + off);
      s32 st = FUN_00fe4150(tribe, (void*)noun);
      u32* cur = sel;
      switch (st) {
        case 0:
        case 1:
          ++kept;
          if (FUN_00fe46a0(tribe, (void*)noun) == 0) break;
          if (cur < selCap) {
            sel = cur + 1;
            if (cur != 0) *cur = noun;
          } else {
            FUN_004558a0(&selEnd, &noun, 4);
            sel = selEnd;
          }
          break;
        case 2:
        case 3:
          if (cur < selCap) {
            sel = cur + 1;
            if (cur != 0) *cur = noun;
          } else {
            FUN_004558a0(&selEnd, &noun, 4);
            sel = selEnd;
          }
          break;
      }
      off += 0xc;
      ++i;
    } while (i < cnt);
  }

  u32 nsel = (u32)(sel - selEnd >= 0 ? sel - selEnd : 0);
  s32 nrows = ((char*)sel - (char*)selEnd) >> 2;
  (void)nsel;
  u8 anyInv = 0;
  if (FUN_00e0a780(p + 0x44, 0x15b8f70, nsel) != 0) {
    u32 defIcon = (u32)(u32*)FUN_00575ea0(tribe);
    for (s32 k = 0; k < nrows; ++k) {
      u32 noun = selEnd[k];
      void* repl = FUN_00fe41c0(tribe, (void*)noun);
      u8 isDefault = (noun == defIcon) ? 1 : 0;
      s32 st = FUN_00fe4150(tribe, (void*)noun);
      u8 isState3 = (st == 3) ? 1 : 0;
      float ratio;
      if (isState3) ratio = 0.0f;
      else ratio = FUN_00fe6690(tribe, (void*)noun);
      u8 owned = FUN_00fe4180(tribe, (void*)repl);
      u8 hidden2 = FUN_00fe46a0(tribe, (void*)noun);

      u8 show;
      if ((0.0f < ratio && ratio < 1.0f) || (owned != 0 && hidden2 == 0)) show = 1;
      else show = 0;

      u32 useRep;
      if (owned == 0 || hidden2 != 0) useRep = noun;
      else useRep = (u32)repl;

      // If the noun is present in the tree view's noun set, re-apply
      // default rows and raise an inventory message.
      char* tvRoot = *(char**)(tribe + 0x34);
      if (tvRoot != tribe + 0x34) {
        char* it = tvRoot;
        while (*(u32*)(it + 8) != useRep) {
          it = *(char**)it;
          if (it == tribe + 0x34) break;
        }
        if (it != tribe + 0x34) {
          u32 key = *(u32*)(feed + 0x14);
          anyInv = 1;
          char* mgr = (char*)FUN_00b3d3f0();
          FUN_00e30e20(mgr, (void*)noun, key, (void*)0xf45f7d78, 0);
        }
      }

      void* layout = FUN_00e09c90(p + 0x44, (u32)k);
      char* w = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5ee04c0, 1);
      (*(void(__thiscall**)(char*, u32))(*(void***)w + 0x50 / 4))(w, noun);
      (*(void(__thiscall**)(char*, u32))(*(void***)w + 0x54 / 4))(
          w, isState3 ? 0x51aff90 : 0);
      (*(void(__thiscall**)(char*, int, int))(*(void***)w + 0x7c / 4))(
          w, 2, (owned == 0 || isState3) ? 0 : 1);
      char* icon = (char*)(*(void* (__thiscall**)(char*, u32))(*(void***)w + 0xc / 4))(
          w, 0x8ed27e7a);
      (*(void(__thiscall**)(char*, int, s32))(*(void***)icon + 0x28 / 4))(
          icon, 4, kept);
      const void* imgKey;
      if (isState3) imgKey = (const void*)0x15b8f94;
      else imgKey = (const void*)(u32)FUN_00fe5520(tribe, (void*)useRep, 0);
      FUN_00807cb0(w, (void*)imgKey, 0);

      char* w2 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x63a8048, 1);
      if (w2 != 0) {
        (*(void(__thiscall**)(char*, u32))(*(void***)w2 + 0x5c / 4))(
            w2, 0xffffff00);
      }

      char* w3 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5fca190, 1);
      char* sub = (char*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x10 / 4))(w3);
      if (isDefault) {
        float* r = (float*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x38 / 4))(w3);
        float width = r[2] - r[0];
        float* r2 = (float*)(*(void* (__thiscall**)(char*))(*(void***)w3 + 0x38 / 4))(w3);
        (*(void(__thiscall**)(char*, float, float))(*(void***)w3 + 0x74 / 4))(
            w3, width * ratio, r2[3] - r2[1]);
      }
      (*(void(__thiscall**)(char*, int, int))(*(void***)sub + 0x7c / 4))(
          sub, 1, isDefault ? 1 : 0);

      char* w4 = (char*)((void* (__thiscall*)(void*, u32, int))FUN_008105b0)(
          layout, 0x5fca1f0, 1);
      if (isState3) {
        (*(void(__thiscall**)(char*, int, int))(*(void***)w4 + 0x7c / 4))(w4, 1, 0);
      } else {
        FUN_010634b0(w4, (void*)useRep, (float)show);
      }
    }
  }

  // Publish the feed pointer and refresh the list item's text.
  if (*(void**)(p + 0x1a8) == 0 && feed != *(char**)(p + 0x1a8)) {
    (*(void(__thiscall**)(char*))(*(void***)feed + 0))(feed);
    char* old = *(char**)(p + 0x1a8);
    *(char**)(p + 0x1a8) = feed;
    if (old != 0) {
      (*(void(__thiscall**)(char*))(*(void***)old + 1))(old);
    }
  }
  {
    u16 buf[64];
    buf[0] = 0;
    FUN_00f14120(buf, (void*)0x146e428, kept, cnt);
    FUN_006666c0(feed, buf);
    if (anyInv) {
      char* icon = *(char**)(feed + 0xa0);
      (*(void(__thiscall**)(char*, u32))(*(void***)icon + 0x50 / 4))(
          icon, *(u32*)(feed + 0x17c));
      char* mgr = (char*)FUN_00b3d3f0();
      FUN_00e30e20(mgr, (void*)*(u32*)(feed + 0x17c),
                   *(u32*)(p + 0x14), (void*)0x2c765c39, 0);
    }
  }
  (void)sel; (void)selCap;
}

// @ 0x01065510
void cString12::Swap_01065510(cString12* other)
{
    if (&mFlag0c == &other->mFlag0c)
    {
        void* a = mpBegin; mpBegin = other->mpBegin; other->mpBegin = a;
        _ReadWriteBarrier();
        void* b = mpEnd;
        _ReadWriteBarrier();
        mpEnd   = other->mpEnd;   other->mpEnd   = b;
        _ReadWriteBarrier();
        void* c = mpCap;   mpCap   = other->mpCap;   other->mpCap   = c;
        return;
    }

    cString12 tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCap = 0;
    tmp.Assign_01064d80(mpBegin, mpEnd);
    if (other != this)
        Assign2_010652d0(other->mpBegin, other->mpEnd);
    if (&tmp != other)
        other->Assign2_010652d0(tmp.mpBegin, tmp.mpEnd);
}

// @ 0x010655a0
void cEmpire::PopulateFeed_010655a0()
{
    mpFeedList->FUN_00662920(1);
    void* list = mpFeedList->FUN_00662a20(0);
    if (list == 0)
        return;

    FUN_00b3d3d0();
    unsigned count = mpFeedList->FUN_00664600();
    for (unsigned i = 0; i < count; ++i)
    {
        CFeedItem* item = (CFeedItem*)mpFeedList->FUN_00664610(i);
        item->Reserve_666630(0, 0);
    }
    if (mpSelected != 0)
        mpFeedList->FUN_00662c10(mpSelected);
}

// @ 0x01065860
void cString12::Resize_01065860(uint32_t n)
{
    if (n != 0xffffffffu)
    {
        char* src = (char*)mpBegin;
        unsigned have = (unsigned)(((int)mpEnd - (int)src) >> 1);
        if (n > have)
        {
            char* dst = (char*)(have * 2);
            memcpy_11e0744(0, src, (unsigned)(int)dst);
            *(uint16_t*)dst = 0;
            mpEnd = dst;
            mpBegin = 0;
            mpCap = (void*)(n * 2);
            return;
        }
    }
    unsigned have = (unsigned)(((int)mpEnd - (int)mpBegin) >> 1);
    if (n < have)
        Reserve_01065270(n);

    cString12 tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCap = 0;
    tmp.Assign_01064d80(mpBegin, mpEnd);
    Swap_01065510(&tmp);
}
