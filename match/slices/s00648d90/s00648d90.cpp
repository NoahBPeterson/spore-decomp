// Slice s00648d90 -- SP::cSPUIAssetGrid::FilterGridEntries (0x00648d90).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// `this` is the asset browser (SPUIAssetBrowser.obj), retail layout.  Offsets
// named below are the retail ones this function reads/writes, matching the
// cSPUIAssetBrowser_s0064_acd0 stand-in used elsewhere in this module:
//   +0x20 dword, +0x24 byte, +0x2a byte, +0xbc grid, +0xc8 caller data,
//   +0xcc/+0xd0 ban vector (Elem stride 0x14), +0xe0 preload ref,
//   +0x138 handler map, +0x1a8 dword, +0x236 byte, +0x23d byte.
#include "types.h"

#define SV(n) virtual void v##n();

struct IObj;
struct IBanObj;
struct ViewSub;
struct IViewRef;

// --- 0x14-byte ban-list node --------------------------------------------
struct Elem {
  uint32_t  key0;     // +0x00
  uint32_t  key1;     // +0x04
  uint32_t  key2;     // +0x08
  IViewRef* mpView;   // +0x0c
  IBanObj*  mpObj;    // +0x10
};
struct Key3 { uint32_t a, b, c; };

// IUnknown-like node used for the "auto-ref" temporaries.
struct IObj {
  virtual int AddRef();
  virtual int Release();
};

// cSPUIAssetView: SetFirstUpdate at slot 50 (0x00657930).
struct IViewRef {
  virtual int AddRef();                 // slot 0
  virtual int Release();                // slot 1
  SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8) SV(9) SV(10)
  SV(11) SV(12) SV(13) SV(14) SV(15) SV(16) SV(17) SV(18) SV(19) SV(20)
  SV(21) SV(22) SV(23) SV(24) SV(25) SV(26) SV(27) SV(28) SV(29) SV(30)
  SV(31) SV(32) SV(33) SV(34) SV(35) SV(36) SV(37) SV(38) SV(39) SV(40)
  SV(41) SV(42) SV(43) SV(44) SV(45) SV(46) SV(47) SV(48) SV(49)
  virtual void SetFirstUpdate(int v);   // slot 50 -> 0x00657930
};
// keyed/typed sub-object at view+0x90.
struct ViewSub {
  SV(0) SV(1) SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8)
  virtual uint32_t GetTypeID();         // slot 9  (vtable+0x24)
  SV(10) SV(11) SV(12) SV(13) SV(14)
  virtual Key3*    GetKey();            // slot 16 (vtable+0x40)
  virtual int      AddRef();            // slot 17
  virtual int      Release();           // slot 18
};
// keyed object at Elem+0x10.
struct IBanObj {
  SV(0) SV(1) SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8) SV(9) SV(10)
  SV(11) SV(12) SV(13) SV(14) SV(15)
  virtual Key3* GetKey();               // slot 16
};

// --- eastl vector<0x14> --------------------------------------------------
struct Vec14 {
  Elem* mpBegin;     // +0x00
  Elem* mpEnd;       // +0x04
  Elem* mpCapacity;  // +0x08
  int size() const { return (int)(mpEnd - mpBegin); }
};
void __stdcall Vec14Reserve(Vec14* v, uint32_t n);     // 0x00646fc0
void __stdcall Vec14SwapInto(Vec14* v, Vec14* tmp);    // 0x00646c90
void __stdcall Vec14Make(Vec14* tmp, uint32_t n);      // 0x00646c00
void __stdcall GridVecErase(Vec14* v, Elem* pos);      // 0x00648af0
Elem* __stdcall GridVecInsert(Elem* first, Elem* last, uint32_t* key);  // 0x00648ce0
Elem* __stdcall ListInsertPos(Elem* first, Elem* last, uint32_t* key, uint8_t flag); // 0x00646030
Elem* __stdcall ListCopy(Elem* first, Elem* last, Elem* dst);           // 0x00646140
void  __stdcall ListDestroy(Elem* first, Elem* last);                   // 0x00645ff0
void  __stdcall ElemInit(Elem* e);                                      // 0x00645db0
void  __stdcall SpVecGrow(const uint32_t* val, uint32_t** end);         // 0x00630b30
void  __stdcall BlobInit(uint32_t* blob);                               // 0x006563c0
void  __stdcall BlobOneArg(int a, uint32_t* blob, int c);               // 0x006571e0
void  __stdcall BlobTwoArg(int a, uint32_t* blob, uint32_t* out);       // 0x00656c70
uint32_t* __stdcall MakeKey4(uint32_t* out, uint32_t* src, int c);      // 0x00805fe0
void  __cdecl  FreeBlock(void* p);                                      // 0x00f47380

// --- incoming message ----------------------------------------------------
struct FilterMsg {
  uint32_t  pad0[3];
  IViewRef* mpView;  // +0x0c
  uint8_t   b10;     // +0x10
  uint8_t   pad11[3];
  int       n14;     // +0x14
  uint8_t   b18;     // +0x18
  uint8_t   b19;     // +0x19
  uint8_t   pad1a[2];
};

// --- the browser (retail layout) ----------------------------------------
struct AssetGrid {
  int  IndexOfView(IViewRef* v);      // 0x0064f280
  Elem* GetEntry(int index);          // 0x0064f2c0
  int  FindFirstVisibleEntry();       // 0x00653b80
  int  FindLastVisibleEntry();        // 0x00653c40
  void UpdateStatsText();             // 0x006528f0
};
struct HandlerMap {
  uint32_t* FindOrInsert(uint32_t* key);   // 0x00646f40
};
struct cSPUIAssetBrowserR {
  uint8_t  pad00[0x20];
  uint32_t f20;             // +0x20
  uint8_t  b24;             // +0x24
  uint8_t  pad25[0x2a - 0x25];
  uint8_t  b2a;             // +0x2a
  uint8_t  pad2b[0xbc - 0x2b];
  AssetGrid* mpGrid;        // +0xbc
  uint8_t  padc0[0xc8 - 0xc0];
  uint32_t mpCallerData;    // +0xc8
  Vec14    mBan;            // +0xcc
  uint8_t  padf8[0xe0 - 0xd8];
  uint32_t mpPreloadRef;    // +0xe0
  uint8_t  padf8b[0x138 - 0xe4];
  HandlerMap mHandlers;     // +0x138
  uint8_t  pad13c[0x1a8 - 0x13c];
  uint32_t f1a8;            // +0x1a8
  uint8_t  pad1ac[0x236 - 0x1ac];
  uint8_t  b236;            // +0x236
  uint8_t  pad237[0x23d - 0x237];
  uint8_t  b23d;            // +0x23d

  void SetLargeCardVisibility(int b, uint32_t* data, int c);   // 0x006478c0
  void FilterGridEntries(FilterMsg* msg);                      // 0x00648d90
};

// retail view body: IObj at +0x24, keyed IObj at +0x28, ViewSub at +0x90.
struct ViewBody {
  uint8_t  pad00[0x24];
  IObj*    mp24;   // +0x24
  IObj*    mp28;   // +0x28
  uint8_t  pad2c[0x90 - 0x2c];
  ViewSub* mp90;   // +0x90
};

// @ 0x00648d90
void cSPUIAssetBrowserR::FilterGridEntries(FilterMsg* msg)
{
  cSPUIAssetBrowserR* self = this;
  uint8_t  b41 = 0;   // msg->b10
  uint8_t  b42 = 0;   // msg->b18
  uint8_t  b43 = 0;   // msg->b19
  IViewRef* p34 = 0;  // msg->mpView
  uint32_t n30 = 0;   // msg->n14

  if (msg != 0) {
    b41 = msg->b10;
    p34 = msg->mpView;
    n30 = (uint32_t)msg->n14;
    b42 = msg->b18;
    b43 = msg->b19;
  }

  if (msg == 0 || b42 == 0) {
    // clear the ban list
    for (int i = 0; i < self->mBan.size(); i++) {
      if (self->mBan.mpBegin[i].mpView != 0)
        self->mBan.mpBegin[i].mpView->SetFirstUpdate(0);
    }
    Elem* b = self->mBan.mpBegin;
    Elem* e = self->mBan.mpEnd;
    Elem* d = ListCopy(e, e, b);
    ListDestroy(d, self->mBan.mpEnd);
    self->mBan.mpEnd = self->mBan.mpEnd - (int)((e - b) / 0x14);
  }

  if (p34 != 0 && ((ViewBody*)p34)->mp90 != 0) {
    ViewBody* v = (ViewBody*)p34;
    Key3 key;
    int  idx = -1;
    int  lim = -1;

    Key3* kp = v->mp90->GetKey();
    key.a = kp->a; key.b = kp->b; key.c = kp->c;

    if (self->mpGrid != 0)
      idx = self->mpGrid->IndexOfView(p34);

    if (b43 != 0 && self->mpGrid != 0 && idx >= 0) {
      int lo = self->mpGrid->FindFirstVisibleEntry();
      int hi = self->mpGrid->FindLastVisibleEntry();
      if (lo >= 0 && hi >= 0) {
        lim = (hi <= idx) ? hi : lo;
        if (lim >= 0) {
          int d = lim - idx;
          int sgn = d >> 31;
          Vec14Reserve(&self->mBan, (uint32_t)((d ^ sgn) - sgn) + (uint32_t)self->mBan.size());
        }
      }
    }

    do {
      if (self->mpGrid != 0 && idx >= 0) {
        Elem* hit = self->mpGrid->GetEntry(idx);
        if (hit != 0) {
          key.a = hit->key0;
          key.b = hit->key1;
          key.c = hit->key2;
          p34 = hit->mpView;
        }
      }
      if (key.a != 0 || key.b != 0 || key.c != 0) {
        Elem* b = self->mBan.mpBegin;
        Elem* e = self->mBan.mpEnd;
        Elem* inserted = ListInsertPos(b, e, (uint32_t*)&key, (uint8_t)self->mpPreloadRef);
        Elem* where = e;
        if (inserted != e) {
          bool before = key.a < inserted->key0;
          if (key.a == inserted->key0) {
            before = key.c < inserted->key2;
            if (key.c == inserted->key2)
              before = key.b < inserted->key1;
          }
          if (!before && (Elem*)((char*)inserted + 0x14) != inserted)
            where = inserted;
        }
        if (where == self->mBan.mpEnd) {
          p34->SetFirstUpdate(1);
          {
            IViewRef* held = p34;
            if (held != 0)
              held->AddRef();
            {
              ViewSub* sub = v->mp90;
              if (sub != 0)
                sub->AddRef();
              Elem tmpKey;
              tmpKey.key0 = key.a;
              tmpKey.key1 = key.b;
              tmpKey.key2 = key.c;
              tmpKey.mpView = held;
              tmpKey.mpObj = 0;
              Elem* node = GridVecInsert(self->mBan.mpBegin, self->mBan.mpEnd, (uint32_t*)&tmpKey);
              ElemInit(node);
              if (sub != 0)
                sub->Release();
            }
            if (held != 0)
              held->Release();
          }
        } else if (b42 != 0 && b43 == 0) {
          p34->SetFirstUpdate(0);
          GridVecErase(&self->mBan, where);
          p34 = 0;
        }
      }
      if (idx >= 0 && lim >= 0) {
        if (idx < lim) idx++;
        else if (lim < idx) idx--;
      }
    } while (b42 != 0 && b43 != 0 && lim >= 0 && idx != lim);
  }

  {
    // move the built vector into a temp, refill from keys.
    Vec14 tmp;
    tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
    Vec14SwapInto(&tmp, &self->mBan);
    Elem* oldB = self->mBan.mpBegin;
    Elem* oldE = self->mBan.mpEnd;
    self->mBan.mpBegin = tmp.mpBegin;
    self->mBan.mpEnd = tmp.mpEnd;
    self->mBan.mpCapacity = tmp.mpCapacity;
    ListDestroy(oldB, oldE);
    if (oldB != 0)
      FreeBlock(oldB);

    if (self->mpCallerData != 0) {
      Vec14 keys;
      keys.mpBegin = 0; keys.mpEnd = 0; keys.mpCapacity = 0;
      Vec14Make(&keys, (uint32_t)self->mBan.size());
      for (int i = 0; i < self->mBan.size(); i++) {
        uint32_t val = 0;
        if (keys.mpEnd < keys.mpCapacity) {
          *(uint32_t*)keys.mpEnd = val;
          keys.mpEnd = (Elem*)((char*)keys.mpEnd + 4);
        } else {
          SpVecGrow(&val, (uint32_t**)&keys.mpEnd);
        }
      }
      if (keys.mpBegin == keys.mpEnd) {
        BlobInit((uint32_t*)&tmp);
        BlobOneArg(0, (uint32_t*)&tmp, 0);
      } else {
        BlobInit((uint32_t*)&tmp);
        BlobTwoArg(1, (uint32_t*)&tmp, (uint32_t*)&keys);
      }
      if (keys.mpBegin != 0 && ((uint32_t*)keys.mpBegin)[-1] != 0)
        FreeBlock(keys.mpBegin);
    }
  }

  {
    uint32_t u1 = 0;
    uint32_t u12 = 0;
    ViewBody* v = (ViewBody*)p34;
    bool vis = false;
    if (b41 != 0 && p34 != 0 && v->mp90 != 0) {
      uint32_t typeId = v->mp90->GetTypeID();
      uint32_t* slot = self->mHandlers.FindOrInsert(&typeId);
      if (*slot != 0) {
        if (n30 != 0) {
          u12 = 1;
        } else if (self->b2a != 0 && v->mp28 != 0) {
          n30 = (uint32_t)(size_t)MakeKey4(&typeId, (uint32_t*)v->mp28, 0);
          u12 = 1;
        } else {
          n30 = 0;
          u12 = 1;
        }
        vis = true;
      }
    }
    if (!vis) {
      u1 = 0;
      n30 = 0;
      u12 = 0;
    }
    self->SetLargeCardVisibility((int)u12, &n30, (int)u1);
  }

  if (self->mpGrid != 0)
    self->mpGrid->UpdateStatsText();
}
