// Slice s00e23710 - cSPUIPosse / cSPUIPosseItem UI cluster.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

#define F10 float

// vtable-call signature typedefs (all thiscall)
typedef void   (__thiscall *TFv)(void*);
typedef void   (__thiscall *TFvi)(void*, int);
typedef void   (__thiscall *TFvp)(void*, void*);
typedef s32    (__thiscall *TFi)(void*);
typedef u32    (__thiscall *TFu)(void*);
typedef u8     (__thiscall *TFb)(void*);
typedef void*  (__thiscall *TFp)(void*);
typedef void*  (__thiscall *TFpi)(void*, u32);
typedef void*  (__thiscall *TFpii)(void*, u32, void*);
typedef u32    (__thiscall *TFui)(void*, u32);
typedef char   (__thiscall *TFci)(void*, int);
typedef u8     (__thiscall *TFuii)(void*, u32, void**);
typedef void*  (__thiscall *TFpp)(void*, void**);   // FUN_00e23e80(ecx, pair*)
typedef void   (__thiscall *TFvpp)(void*, void*, int);

// ---- external callees (address in comment) ------------------------------
u32    __cdecl FUN_008d2db0(void);                 // 0x008d2db0 GetModifierState
void   __cdecl FUN_008e2b20(void* self);           // 0x008e2b20 Vec2b::Free (thiscall)
void   __cdecl FUN_00f47380(void* p);              // 0x00f47380 operator_delete_array
void   __cdecl FUN_00811fe0(void* self);           // 0x00811fe0 cSPUILayout::~cSPUILayout
u8     __fastcall FUN_008120d0(void* self, void* dummy, u32 key, u32 a, u32 b); // 0x008120d0 cSPUILayout::Init(key) (thiscall)
u8     __cdecl FUN_00812160(void* self, void* a, int b, u32 c, u32 d);     // 0x00812160 cSPUILayout::Init(str)
void*  __cdecl FUN_008105b0(void* self, u32 id, int b); // 0x008105b0 cSPUILayout::FindWindowByID
struct SPUILayoutC {
  void* FindWindowByID(u32 id, int b);
  u8 Init(u32 key, int a, u32 b);
  u8 InitStr(void* name, int a, int b, u32 c);
};  // modeled thiscall targets (0x008105b0 / 0x008120d0 / 0x00812160)
struct SPUIPosseC { void SelectAll(u32 a); };                // modeled thiscall target (FUN_00e22b50)
struct CopyImplC { void Copy(void* src); };                 // modeled thiscall target (FUN_006237d0, ecx=0x15a5524)
struct Vec2bC { void Free(); };                             // modeled thiscall target (FUN_008e2b20)
struct LayoutDtorC { void Dtor(); };                        // modeled thiscall target (FUN_00811fe0)
struct PosseItemC { void SetBlinkerMotive(u32 a, u8 b); };  // modeled thiscall target (FUN_00e21cf0)
void*  __cdecl FUN_0067de30(void);                 // 0x0067de30 SP::PropertyManager
void   __cdecl FUN_006237d0(void* a);              // 0x006237d0 eastl::copy_impl cSPColorRGB
void   __cdecl FUN_00805080(void);                 // 0x00805080 SPUIHelpers::GetElapsedSeconds
float  __cdecl FUN_00805080_f(void);               // 0x00805080 SPUIHelpers::GetElapsedSeconds (float ret)
u32    __cdecl FUN_00e217c0(void* a, void* b);     // 0x00e217c0
void   __cdecl FUN_00e21cf0(void* self, u32 a, u8 b); // 0x00e21cf0 cSPUIPosseItem::set_blinker_motive
void*  __cdecl FUN_00e23250(void);                 // 0x00e23250 EA::Audio::GetSystem
void*  __cdecl FUN_00a206f0(void);                 // 0x00a206f0 EA::Audio::GetSystemAT
void   __cdecl FUN_00e21700(void);                 // 0x00e21700
void   __cdecl FUN_00e21720(void);                 // 0x00e21720
void   __cdecl FUN_00e22b50(void* self, u32 a);    // 0x00e22b50 (thiscall)

extern void* DAT_016ac278;

// ======================================================================
// helper views
// ======================================================================

// cSPUIPosseItem (+0x94 mState, +0xa1 mbSelected-ish, +0xa2 mFlag, +0xa8 mDistress[2],
//   +0xb0 mBlinkerFreq?, +0xc0 mBlinkerScaleFrom, +0xc4 mBlinkerScaleTo,
//   +0xc8 mBlinkerColorFrom, +0xcc?, +0xd0 mBlinkerFrequency, +0xd4 mLayout obj ptr,
//   +0x13c refptr)
// cSPUIPosse: +0xc mItemsBegin, +0x10 mItemsEnd, +0x5c..., +0x94 mState

typedef void* Ref;

// ======================================================================
// 0x00e23710 - cSPUIPosseItem::HandleClick-ish (object selection feedback).
// ======================================================================

// @ 0x00e23710
u8 __fastcall FUN_00e23710(void* self, void* dummy, void* hit, s32 mode) {
  (void)dummy;
  if (mode != 1) return 0;
  u32 modState = FUN_008d2db0();
  Ref mSel = *(Ref*)((char*)self + 0x13c);
  u8 bit = (u8)((modState >> 1) & 1);
  if (mSel == 0) return 0;
  void* layoutObj = *(void**)((char*)self + 0xd4);
  void* subObj = *(void**)((char*)layoutObj + 0x10);
  void* other = (void*)((TFpii)(*(void***)subObj)[0xf0 / 4])(subObj, 0x614a0c4, (void*)1);
  if (*(u8*)((char*)self + 0xa1)) {
    u8 sel = (hit == (void*)mSel || hit == other) ? (u8)1 : (u8)0;
    *(u8*)((char*)self + 0xa1) = sel;
  }
  switch (*(s32*)((char*)self + 0x94) - 1) {
    case 0:
      if ((hit != (void*)mSel && hit != other) || *(u8*)((char*)self + 0xa2) || bit) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 3);
      break;
    case 1:
      if ((hit != (void*)mSel && hit != other) || *(u8*)((char*)self + 0xa2) || bit) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 4);
      break;
    case 2:
      if (hit == 0) break;
      if (hit == (void*)mSel || hit == other) break;
      if (((TFu)(*(void***)hit)[0x1c / 4])(hit) == 0x4acfcaf) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 1);
      break;
    case 3:
      if (hit == 0) {
        ((TFvi)(*(void***)self)[0xb8 / 4])(self, 2);
        break;
      }
      if (hit == (void*)mSel || hit == other) break;
      if (((TFu)(*(void***)hit)[0x1c / 4])(hit) == 0x4acfcaf) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 2);
      break;
  }
  return 0;
}

// ======================================================================
// 0x00e23870 - destroy a range of AutoRefCount pairs (dtor each sub-ref).
// ======================================================================

// @ 0x00e23870
void __stdcall FUN_00e23870(void* begin, void* end) {
  for (void* p = begin; (u32)p < (u32)end; p = (char*)p + 8) {
    Ref b = *(Ref*)((char*)p + 4);
    if (b) ((TFv)(*(void***)b)[1])(b);
    Ref a = *(Ref*)((char*)p);
    if (a) ((TFv)(*(void***)a)[1])(a);
  }
}

// ======================================================================
// 0x00e238b0 - uninitialized_fill_n of AutoRefCount pairs (copy + AddRef).
// ======================================================================

// @ 0x00e238b0
void __cdecl FUN_00e238b0(void* dst, u32 n, void* src) {
  if (n == 0) return;
  do {
    if (dst) {
      Ref a = *(Ref*)src;
      *(Ref*)dst = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = *(Ref*)((char*)src + 4);
      *(Ref*)((char*)dst + 4) = b;
      if (b) ((TFv)(*(void***)b)[0])(b);
    }
    n--;
    dst = (char*)dst + 8;
  } while (n != 0);
}

// ======================================================================
// 0x00e23900 - copy range of AutoRefCount pairs.
// ======================================================================

// @ 0x00e23900
void* __cdecl FUN_00e23900(void* first, void* last, void* out) {
  if (first == last) return out;
  do {
    if (out) {
      Ref a = *(Ref*)first;
      *(Ref*)out = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = *(Ref*)((char*)first + 4);
      *(Ref*)((char*)out + 4) = b;
      if (b) ((TFv)(*(void***)b)[0])(b);
    }
    first = (char*)first + 8;
    out = (char*)out + 8;
  } while (first != last);
  return out;
}

// ======================================================================
// 0x00e23950 - destroy range, return end pointer.
// ======================================================================

// @ 0x00e23950
void* __cdecl FUN_00e23950(void* first, void* last, void* out) {
  if (first == last) return out;
  do {
    Ref b = *(Ref*)((char*)first + 4);
    if (b) ((TFv)(*(void***)b)[1])(b);
    Ref a = *(Ref*)first;
    if (a) ((TFv)(*(void***)a)[1])(a);
    first = (char*)first + 8;
    out = (char*)out + 8;
  } while (first != last);
  return out;
}

// ======================================================================
// 0x00e239a0 - cSPUIPosseItem::SetDistress.
// ======================================================================

// @ 0x00e239a0
void __fastcall FUN_00e239a0(void* self, void* dummy, s32 idx, s32 level) {
  (void)dummy;
  ((TFv)(*(void***)self)[0xd8 / 4])(self);
  *(s32*)((char*)self + 0xa8 + (idx - 1) * 4) = level;
  s32 distress0 = *(s32*)((char*)self + 0xa8);
  u8 flag = ((TFb)(*(void***)self)[0xb4 / 4])(self);
  u8 b3 = (u8)(distress0 == 2);
  if (flag) {
    ((PosseItemC*)self)->SetBlinkerMotive(1, (u8)(*(s32*)((char*)self + 0xa8) == 2));
  }
  u8 b4 = b3;
  if (!b3 && *(s32*)((char*)self + 0xa8) != 2) b4 = 0;
  ((PosseItemC*)self)->SetBlinkerMotive(0, (u8)(*(s32*)((char*)self + 0xa8) == 2));
  if (!b4) return;
  if (*(float*)((char*)self + 0xd0) == *(float*)0x1485378) {
    *(float*)((char*)self + 0xc8) = *(float*)0x13eb95c;
    *(float*)((char*)self + 0xd0) = FUN_00805080_f();
  }
  s32 st = *(s32*)((char*)self + 0x94);
  if (st == 1 || st == 2) {
    *(float*)((char*)self + 0xc0) = *(float*)0x1485544;
    *(float*)((char*)self + 0xc4) = *(float*)0x1485720;
    *(s32*)((char*)self + 0xb8) = 0x60ff0000;
    *(s32*)((char*)self + 0xbc) = (s32)0xd0ff0000;
  } else {
    *(float*)((char*)self + 0xc0) = *(float*)0x1485720;
    *(s32*)((char*)self + 0xb8) = -1;
    *(s32*)((char*)self + 0xbc) = 0xffff3f00;
    *(float*)((char*)self + 0xc4) = *(float*)0x13ec4b4;
  }
}

// ======================================================================
// 0x00e23ae0 - cSPUIPosseItem::init (key-based).
// ======================================================================

// @ 0x00e23ae0
s32 __fastcall FUN_00e23ae0(void* self, void* dummy, u32 id) {
  (void)dummy;
  void* pm = FUN_0067de30();
  if (DAT_016ac278) {
    void* old = DAT_016ac278;
    DAT_016ac278 = 0;
    ((TFv)(*(void***)old)[1])(old);
  }
  u8 ok = ((TFuii)(*(void***)pm)[0x30 / 4])(pm, 0x5c770db7, &DAT_016ac278);
  if (ok) {
    ((CopyImplC*)0x15a5524)->Copy(DAT_016ac278);
  }
  u8 r = ((SPUILayoutC*)((char*)self + 0x1bc))->Init(id, 1, 0x8d0f4fb);
  if (r) {
    if (((TFb)(*(void***)self)[0xcc / 4])(self)) return 1;
  }
  return 0;
}

// ======================================================================
// 0x00e23b70 - cSPUIPosseItem::init (string-based).
// ======================================================================

// @ 0x00e23b70
s32 __fastcall FUN_00e23b70(void* self, void* dummy, void* name, int id) {
  (void)dummy;
  void* pm = FUN_0067de30();
  if (DAT_016ac278) {
    void* old = DAT_016ac278;
    DAT_016ac278 = 0;
    ((TFv)(*(void***)old)[1])(old);
  }
  u8 ok = ((TFuii)(*(void***)pm)[0x30 / 4])(pm, 0x5c770db7, &DAT_016ac278);
  if (ok) {
    ((CopyImplC*)0x15a5524)->Copy(DAT_016ac278);
  }
  u8 r = ((SPUILayoutC*)((char*)self + 0x1bc))->InitStr(name, id, 1, 0x8d0f4fb);
  if (r) {
    if (((TFb)(*(void***)self)[0xcc / 4])(self)) return 1;
  }
  return 0;
}

// ======================================================================
// 0x00e23c00 - comparator by control-value key.
// ======================================================================

// @ 0x00e23c00
u32 __cdecl FUN_00e23c00(void** a, void** b) {
  s32 x, y;
  if (*a) x = (s32)((TFpi)(*(void***)*a)[0xc / 4])(*a, 0x137e8e0);
  else x = 0;
  if (*b) y = (s32)((TFpi)(*(void***)*b)[0xc / 4])(*b, 0x137e8e0);
  else y = 0;
  if (x && y) return (u32)FUN_00e217c0((void*)x, (void*)y);
  if (*a) x = (s32)((TFpi)(*(void***)*a)[0xc / 4])(*a, 0x4f176642);
  else x = 0;
  if (*b) y = (s32)((TFpi)(*(void***)*b)[0xc / 4])(*b, 0x4f176642);
  else y = 0;
  if (x && y) return (u32)(*(u32*)((char*)x + 0x24) < *(u32*)((char*)y + 0x24));
  return (u32)((u32)*a < (u32)*b);
}

// ======================================================================
// 0x00e23ca0 - cSPUIPosse::init.
// ======================================================================

// @ 0x00e23ca0
u8 __fastcall FUN_00e23ca0(void* self, void* dummy) {
  (void)dummy;
  void* layout = (char*)self + 0x1bc;
  void* w;
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae410, 1);
  ((TFvi)(*(void***)w)[0xac / 4])(w, 0);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae411, 1);
  ((TFvi)(*(void***)w)[0xac / 4])(w, 0);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3d98298, 1);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae412, 1);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  ((SPUIPosseC*)self)->SelectAll(0);
  return 1;
}

// ======================================================================
// 0x00e23d50 - cSPUIPosse::toggle_select_all.
// ======================================================================

// @ 0x00e23d50
void __fastcall FUN_00e23d50(void* self, void* dummy) {
  (void)dummy;
  void* sys = FUN_00e23250();
  void** vt = *(void***)self;
  void (*cb)(void) = FUN_00e21720;
  if (sys != 0) cb = FUN_00e21700;
  ((TFvpp)vt[0xa0 / 4])(self, (void*)cb, 0);
  void* at = FUN_00a206f0();
  u32 uVar3 = 0;
  if (at != 0) uVar3 = ((TFu)(*(void***)at)[0x20 / 4])(at);
  at = FUN_00a206f0();
  if (at) {
    ((TFvi)(*(void***)at)[0x38 / 4])(at, 0x3475365);
    ((TFvp)(*(void***)at)[0x40 / 4])(at, (void*)(u32)0xa715736e);
    ((TFvp)(*(void***)at)[0x40 / 4])(at, (void*)uVar3);
    ((TFv)(*(void***)at)[0x58 / 4])(at);
  }
}

// ======================================================================
// 0x00e23de0 - clear transient items from the list.
// ======================================================================

// @ 0x00e23de0
void __fastcall FUN_00e23de0(void* self, void* dummy) {
  (void)dummy;
  void* end = *(void**)((char*)self + 0x10);
  void* begin = *(void**)((char*)self + 0xc);
  while ((u32)end > (u32)begin) {
    end = (char*)end - 4;
    void* item = *(void**)end;
    if (((TFi)(*(void***)item)[0xbc / 4])(item) == 3) {
      ((TFv)(*(void***)item)[0xa8 / 4])(item);
    } else if (((TFi)(*(void***)item)[0xbc / 4])(item) == 4) {
      ((TFv)(*(void***)item)[0xa8 / 4])(item);
    }
  }
}

// ======================================================================
// 0x00e23e30 - eastl::lower_bound (pair*, pair, pred).
// ======================================================================

// @ 0x00e23e30
void* __cdecl FUN_00e23e30(void* first, void* last, void* val, u8(__cdecl* pred)(void*, void*)) {
  s32 n = (s32)((char*)last - (char*)first) >> 3;
  while (n > 0) {
    s32 half = n >> 1;
    void* mid = (char*)first + half * 8;
    if (pred(mid, val)) {
      first = (char*)mid + 8;
      n = n - half - 1;
    } else {
      n = half;
    }
  }
  return first;
}

// ======================================================================
// 0x00e23e80 - move-assign an AutoRefCount pair.
// ======================================================================

// @ 0x00e23e80
void* __fastcall FUN_00e23e80(void* self, void* dummy, void** src) {
  (void)dummy;
  Ref old0 = *(Ref*)self;
  Ref new0 = *(Ref*)src;
  if (new0 != old0) {
    if (new0) ((TFv)(*(void***)new0)[0])(new0);
    *(Ref*)self = new0;
    if (old0) ((TFv)(*(void***)old0)[1])(old0);
  }
  Ref new1 = *(Ref*)((char*)src + 4);
  Ref old1 = *(Ref*)((char*)self + 4);
  if (new1 != old1) {
    if (new1) ((TFv)(*(void***)new1)[0])(new1);
    *(Ref*)((char*)self + 4) = new1;
    if (old1) ((TFv)(*(void***)old1)[1])(old1);
  }
  return self;
}

// ======================================================================
// 0x00e23ee0 - lower_bound by u32 key (stride 16).
// ======================================================================

// @ 0x00e23ee0
void __cdecl FUN_00e23ee0(void* first, void* last, u32* key) {
  s32 n = (s32)((char*)last - (char*)first) >> 4;
  while (n > 0) {
    s32 half = n >> 1;
    void* mid = (char*)first + half * 16;
    if (*(u32*)mid < *key) {
      first = (char*)mid + 16;
      n = n - half - 1;
    } else {
      n = half;
    }
  }
}

// ======================================================================
// 0x00e23f30 - insertion sort (move variant) over AutoRefCount pairs.
// ======================================================================

// @ 0x00e23f30
void __cdecl FUN_00e23f30(void* first, void* last, u8(__cdecl* pred)(void*, void*)) {
  if (first == last) return;
  for (void* cur = (char*)first + 8; cur != last; cur = (char*)cur + 8) {
    Ref local0 = *(Ref*)cur;
    if (local0) ((TFv)(*(void***)local0)[0])(local0);
    Ref local1 = *(Ref*)((char*)cur + 4);
    if (local1) ((TFv)(*(void***)local1)[0])(local1);
    void* hole = cur;
    while (hole != first) {
      void* prev = (char*)hole - 8;
      if (!pred(&local0, prev)) break;
      /* shift prev into hole */
      Ref os0 = *(Ref*)hole;
      Ref ns0 = *(Ref*)prev;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)hole = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref os1 = *(Ref*)((char*)hole + 4);
      Ref ns1 = *(Ref*)((char*)prev + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)hole + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
      hole = prev;
    }
    /* place local into hole */
    Ref d0 = *(Ref*)hole;
    if (local0 != d0) {
      if (local0) ((TFv)(*(void***)local0)[0])(local0);
      *(Ref*)hole = local0;
      if (d0) ((TFv)(*(void***)d0)[1])(d0);
    }
    Ref d1 = *(Ref*)((char*)hole + 4);
    if (local1 != d1) {
      if (local1) ((TFv)(*(void***)local1)[0])(local1);
      *(Ref*)((char*)hole + 4) = local1;
      if (d1) ((TFv)(*(void***)d1)[1])(d1);
    }
    if (local1) ((TFv)(*(void***)local1)[1])(local1);
    if (local0) ((TFv)(*(void***)local0)[1])(local0);
  }
}

// ======================================================================
// 0x00e240b0 - insertion sort variant 2.
// ======================================================================

// @ 0x00e240b0
void __cdecl FUN_00e240b0(void* first, void* last, u8(__cdecl* pred)(void*, void*)) {
  for (void* cur = first; cur != last; cur = (char*)cur + 8) {
    Ref local0 = *(Ref*)cur;
    if (local0) ((TFv)(*(void***)local0)[0])(local0);
    Ref local1 = *(Ref*)((char*)cur + 4);
    if (local1) ((TFv)(*(void***)local1)[0])(local1);
    void* hole = (char*)cur - 8;
    u8 go = pred(&local0, hole);
    while (go) {
      Ref os0 = *(Ref*)cur;
      Ref ns0 = *(Ref*)hole;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)cur = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref os1 = *(Ref*)((char*)cur + 4);
      Ref ns1 = *(Ref*)((char*)hole + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)cur + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
      cur = hole;
      hole = (char*)hole - 8;
      go = pred(&local0, hole);
    }
    Ref d0 = *(Ref*)cur;
    if (local0 != d0) {
      if (local0) ((TFv)(*(void***)local0)[0])(local0);
      *(Ref*)cur = local0;
      if (d0) ((TFv)(*(void***)d0)[1])(d0);
    }
    Ref d1 = *(Ref*)((char*)cur + 4);
    if (local1 != d1) {
      if (local1) ((TFv)(*(void***)local1)[0])(local1);
      *(Ref*)((char*)cur + 4) = local1;
      if (d1) ((TFv)(*(void***)d1)[1])(d1);
    }
    if (local1) ((TFv)(*(void***)local1)[1])(local1);
    if (local0) ((TFv)(*(void***)local0)[1])(local0);
  }
}

// ======================================================================
// 0x00e24220 - fill range with a pair (copy-assign).
// ======================================================================

// @ 0x00e24220
void __cdecl FUN_00e24220(void* first, void* last, void* src) {
  for (; first != last; first = (char*)first + 8) {
    Ref ns0 = *(Ref*)src;
    Ref os0 = *(Ref*)first;
    if (ns0 != os0) {
      if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
      *(Ref*)first = ns0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref ns1 = *(Ref*)((char*)src + 4);
    Ref os1 = *(Ref*)((char*)first + 4);
    if (ns1 != os1) {
      if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
      *(Ref*)((char*)first + 4) = ns1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  }
}

// ======================================================================
// 0x00e24290 - copy range of pairs, return end.
// ======================================================================

// @ 0x00e24290
void* __cdecl FUN_00e24290(void* first, void* last, void* out) {
  if (first == last) return out;
  do {
    Ref ns0 = *(Ref*)first;
    Ref os0 = *(Ref*)out;
    if (ns0 != os0) {
      if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
      *(Ref*)out = ns0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref ns1 = *(Ref*)((char*)first + 4);
    Ref os1 = *(Ref*)((char*)out + 4);
    if (ns1 != os1) {
      if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
      *(Ref*)((char*)out + 4) = ns1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
    first = (char*)first + 8;
    out = (char*)out + 8;
  } while (first != last);
  return out;
}

// ======================================================================
// 0x00e24310 - fill_n via output-iterator (pointer) copy-assign.
// ======================================================================

// @ 0x00e24310
void* __cdecl FUN_00e24310(void** out, void* first, void* last, void* val) {
  *out = val;
  for (; first != last; first = (char*)first + 8) {
    Ref* dst = (Ref*)*out;
    if (dst) {
      Ref a = *(Ref*)first;
      dst[0] = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = *(Ref*)((char*)first + 4);
      dst[1] = b;
      if (b) ((TFv)(*(void***)b)[0])(b);
    }
    *out = (void*)((char*)*out + 8);
  }
  return out;
}

// ======================================================================
// 0x00e24370 - copy range backwards, return end.
// ======================================================================

// @ 0x00e24370
void* __cdecl FUN_00e24370(void* first, void* last, void* out) {
  if (last == first) return out;
  do {
    void* src = (char*)last - 8;
    void* dst = (char*)out - 8;
    last = src;
    out = dst;
    Ref ns0 = *(Ref*)src;
    Ref os0 = *(Ref*)dst;
    if (ns0 != os0) {
      if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
      *(Ref*)dst = ns0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref ns1 = *(Ref*)((char*)src + 4);
    Ref os1 = *(Ref*)((char*)dst + 4);
    if (ns1 != os1) {
      if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
      *(Ref*)((char*)dst + 4) = ns1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  } while (last != first);
  return out;
}

// ======================================================================
// 0x00e243f0 - sift-down / heap adjust.
// ======================================================================

// @ 0x00e243f0
void __cdecl FUN_00e243f0(void* base, s32 start, s32 pos, void* v0, void* v1, u8(__cdecl* pred)(void*, void*)) {
  s32 child;
  while (start < pos) {
    child = (pos - 1) >> 1;
    if (!pred((char*)base + child * 8, &v0)) break;
    {
      void* dst = (char*)base + pos * 8;
      Ref ns0 = *(Ref*)((char*)base + child * 8);
      Ref os0 = *(Ref*)dst;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)dst = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref ns1 = *(Ref*)((char*)base + child * 8 + 4);
      Ref os1 = *(Ref*)((char*)dst + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)dst + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
    }
    pos = child;
  }
  {
    void* dst = (char*)base + pos * 8;
    Ref os0 = *(Ref*)dst;
    if (v0 != os0) {
      if (v0) ((TFv)(*(void***)v0)[0])(v0);
      *(Ref*)dst = v0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref os1 = *(Ref*)((char*)dst + 4);
    if (v1 != os1) {
      if (v1) ((TFv)(*(void***)v1)[0])(v1);
      *(Ref*)((char*)dst + 4) = v1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  }
  if (v1) ((TFv)(*(void***)v1)[1])(v1);
  if (v0) ((TFv)(*(void***)v0)[1])(v0);
}

// ======================================================================
// 0x00e245c0 - swap two pairs via temporaries.
// ======================================================================

// @ 0x00e245c0
void __cdecl FUN_00e245c0(void* a, void* b) {
  Ref t0 = *(Ref*)a;
  if (t0) ((TFv)(*(void***)t0)[0])(t0);
  Ref t1 = *(Ref*)((char*)a + 4);
  if (t1) ((TFv)(*(void***)t1)[0])(t1);
  ((TFpp)FUN_00e23e80)(b, &t0);
  ((TFpp)FUN_00e23e80)(a, &t0);
  if (t1) ((TFv)(*(void***)t1)[1])(t1);
  if (t0) ((TFv)(*(void***)t0)[1])(t0);
}

// ======================================================================
// 0x00e24630 - cSPUIPosseItem::~cSPUIPosseItem.
// ======================================================================

// @ 0x00e24630
void __fastcall FUN_00e24630(void* self, void* dummy) {
  (void)dummy;
  *(void**)self = (void*)0x14805b8;
  *(void**)((char*)self + 4) = (void*)0x148059c;
  *(void**)((char*)self + 0xc) = (void*)0x148058c;
  Ref r = *(Ref*)((char*)self + 0x13c);
  if (r) ((TFv)(*(void***)r)[1])(r);
  void* arr = *(void**)((char*)self + 0x124);
  if (arr) FUN_00f47380(arr);
  ((Vec2bC*)((char*)self + 0x100))->Free();
  ((Vec2bC*)((char*)self + 0xd4))->Free();
  Ref s = *(Ref*)((char*)self + 0x9c);
  if (s) ((TFv)(*(void***)s)[1])(s);
  ((LayoutDtorC*)((char*)self + 0x7c))->Dtor();
  Ref m = *(Ref*)((char*)self + 0x50);
  if (m) ((TFv)(*(void***)m)[1])(m);
  *(void**)((char*)self + 0xc) = (void*)0x13eb394;
  *(void**)((char*)self + 4) = (void*)0x13eb938;
  *(void**)self = (void*)0x13eb938;
}
