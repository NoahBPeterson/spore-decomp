// Spore decompilation - batch w2g6, slice s008019f0 (0x008019F0..0x00802A2F).
// cSPUICursorManager (cursor table + registration + Win32 cursor loads), the cursor
// map's EASTL rbtree instantiations, position persistence, and cSPUIDebugConsole.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (declared only)
// ---------------------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* f, int l);
void  __cdecl operator_delete(void* p);
extern "C" void __cdecl EASTL_allocator_deallocate(void* p);
void  __cdecl RBTreeIncrement(void* node);
void  __cdecl RBTreeErase(void* node, void* anchor);

void* __cdecl SP_PropertyManager();
float* __cdecl SP_GetPropertyAsFloat();
void* __cdecl SP_Canvas();
void* __cdecl Eapd_ObjectError();

extern "C" {
__declspec(dllimport) void* __stdcall LoadImageW(void* hinst, const wchar_t* name, unsigned type,
                                                 int cx, int cy, unsigned fuLoad);
__declspec(dllimport) int   __stdcall GetIconInfo(void* icon, void* iconInfo);
__declspec(dllimport) int   __stdcall DestroyCursor(void* cursor);
}

// methods of classes owned by other slices (declared only -> out-of-line calls)
struct Slice11 {
  void SetWindow(void* p);             // 0x008017f0
  void Move(float x, float y);         // 0x008016e0
  bool SetEnabled(bool v);             // 0x00801980
  bool Enable(int a);                  // 0x00801950
  bool Refresh();                      // 0x008027e0
};
struct CursorLayout {
  void Shutdown(bool recursive);       // cSPUILayout::Shutdown (0x811ad0)
  void* FindWindowByID(uint32_t id, int recursive);
};

struct IObject {
  virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3();
  virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7();
};
struct RCObj { virtual void r0(); virtual void Release(); };

// ---------------------------------------------------------------------------
// cSPUICursorManager (retail layout, larger than the dev PDB's 0x44)
// ---------------------------------------------------------------------------
struct CurMgr {
  char data[0x60];

  bool Sub_802580();            // 0x00802580
  bool Sub_802680();            // 0x00802680
  bool Sub_801b60(uint32_t k);  // 0x00801b60
  bool Sub_801bb0(uint32_t k);  // 0x00801bb0
  bool Sub_801c10(uint32_t k);  // 0x00801c10
  bool Sub_801c70(uint32_t k);  // 0x00801c70
  bool Sub_8024e0(uint32_t k);  // 0x008024e0
  void Sub_8027e0();            // 0x008027e0
  bool Sub_801950(int a);       // 0x00801950
  bool Sub_801980(bool v);      // 0x00801980
};

// @ 0x00801c70  secondary-base adjustor for Sub_801c10
bool CurMgr::Sub_801c70(uint32_t k) {
  return ((CurMgr*)((char*)this - 8))->Sub_801c10(k);
}

// @ 0x00801c10
bool CurMgr::Sub_801c10(uint32_t k) {
  void* it = 0;
  void* found = 0;
  // map (this+0xc).find(k)
  ((void(__thiscall*)(void*, uint32_t*, void**))0xe5c780)((char*)this + 0xc, &k, &it);
  found = (it == (char*)this + 0x10) ? 0 : (char*)it + 0x14;
  if (found != *(void**)((char*)this + 0x34)) {
    *(void**)((char*)this + 0x34) = found;
    this->Sub_8027e0();
  }
  return found != 0;
}

// @ 0x00801bb0
bool CurMgr::Sub_801bb0(uint32_t k) {
  void* it = 0;
  ((void(__thiscall*)(void*, uint32_t*, void**))0xe5c780)((char*)this + 0xc, &k, &it);
  if (it == (char*)this + 0x10)
    return false;
  void* found = (char*)it + 0x14;
  if (found && found != *(void**)((char*)this + 0x2c)) {
    *(void**)((char*)this + 0x2c) = found;
    this->Sub_8027e0();
  }
  return found != 0;
}

// @ 0x00801b60
bool CurMgr::Sub_801b60(uint32_t k) {
  void* it = 0;
  ((void(__thiscall*)(void*, uint32_t*, void**))0xe5c780)((char*)this + 0xc, &k, &it);
  void* found = (it == (char*)this + 0x10) ? 0 : (char*)it + 0x14;
  if (found != *(void**)((char*)this + 0x30)) {
    *(void**)((char*)this + 0x30) = found;
    this->Sub_8027e0();
  }
  return found != 0;
}

// @ 0x00802580  clear the whole cursor map
bool CurMgr::Sub_802580() {
  if (*(int*)((char*)this + 0x20) != 0) {
    do {
      void* node = *(void**)((char*)this + 0x14);
      *(int*)((char*)this + 0x20) -= 1;
      RBTreeIncrement(node);
      RBTreeErase(node, (char*)this + 0x10);
      int a = *(int*)((char*)node + 0x14);
      if (((*(int*)((char*)node + 0x1c) - a) & 0xfffffffe) > 2 && a)
        EASTL_allocator_deallocate((void*)a);
      EASTL_allocator_deallocate(node);
    } while (*(int*)((char*)this + 0x20) != 0);
  }
  return true;
}

// @ 0x00802680
bool CurMgr::Sub_802680() {
  if (*(uint8_t*)((char*)this + 0x28)) {
    ((Slice11*)(void*)this)->SetWindow(0);
    this->Sub_802580();
    *(void**)((char*)this + 0x38) = 0;
    *(void**)((char*)this + 0x34) = 0;
    *(void**)((char*)this + 0x2c) = 0;
    *(void**)((char*)this + 0x30) = 0;
    *(void**)((char*)this + 0x3c) = 0;
    *(uint8_t*)((char*)this + 0x28) = 0;
  }
  return true;
}

// @ 0x008024e0
bool CurMgr::Sub_8024e0(uint32_t k) {
  void* it = 0;
  ((void(__thiscall*)(void*, uint32_t*, void**))0xe5c780)((char*)this + 0xc, &k, &it);
  if (it == (char*)this + 0x10)
    return false;
  void* info = (char*)it + 0x14;
  if (info == *(void**)((char*)this + 0x30)) *(void**)((char*)this + 0x30) = 0;
  if (info == *(void**)((char*)this + 0x2c)) *(void**)((char*)this + 0x2c) = 0;
  if (info == *(void**)((char*)this + 0x38)) *(void**)((char*)this + 0x38) = 0;
  if (info == *(void**)((char*)this + 0x34)) *(void**)((char*)this + 0x34) = 0;
  bool r = ((bool(__thiscall*)(void*, void*))0x8027a0)(this, it);
  // map erase(it)
  { void* out = 0; ((void(__thiscall*)(void*, void**, void*))0x801e90)((char*)this + 0xc, &out, it); }
  if (*(uint8_t*)((char*)this + 0x40) && *(void**)((char*)this + 0x38) != 0)
    this->Sub_8027e0();
  return r;
}

// @ 0x008027e0
void CurMgr::Sub_8027e0() {
  if (!*(uint8_t*)((char*)this + 0x40))
    return;
  void* info;
  if (*(int*)((char*)this + 0x58) < 1) {
    info = *(void**)((char*)this + 0x30);
    if (!info) {
      if (*(uint8_t*)((char*)this + 0x42)) info = *(void**)((char*)this + 0x2c);
      else info = *(void**)((char*)this + 0x34);
      if (!info) goto set;
    }
  } else {
    info = *(void**)((char*)this + 0x3c);
  }
  *(void**)((char*)this + 0x38) = info;
set:
  info = *(void**)((char*)this + 0x38);
  void* h = 0;
  if (info && (*(void**)((char*)info + 0x18) != 0 ||
               (*(void**)info != *(void**)((char*)info + 4) && Sub_8026e0_check(info)))) {
    h = *(void**)(*(void**)((char*)this + 0x38) + 0x18);
  }
  void* c = SP_Canvas();
  ((void(__thiscall*)(void*, void*))((*(void***)c)[0x80 / 4]))(c, h);
}
bool CurMgr::Sub_8026e0_check(void* info);

// @ 0x00801950
bool CurMgr::Sub_801950(int a) {
  return ((Slice11*)(void*)this)->Enable(a);
}

// @ 0x00801980
bool CurMgr::Sub_801980(bool v) {
  return ((Slice11*)(void*)this)->SetEnabled(v);
}

// ---------------------------------------------------------------------------
// @ 0x008026b0  LoadImageW wrapper
// ---------------------------------------------------------------------------
bool __stdcall Sub_8026b0(const wchar_t* name, void* info) {
  void* h = LoadImageW(0, name, 2, 0, 0, 0x10);
  bool r = h != 0;
  *(void**)((char*)info + 0x14) = h;
  return r;
}

// @ 0x008027a0  destroy the cursor held by an entry
bool __thiscall Sub_8027a0(void* self, void* it) {
  if (it == (char*)self + 0x10)
    return false;
  void* h = *(void**)((char*)it + 0x2c);
  bool r = true;
  if (h)
    r = DestroyCursor(h) != 0;
  *(void**)((char*)it + 0x2c) = 0;
  return r;
}

// @ 0x00802850
bool __thiscall Sub_802850(void* self, void* it) {
  if (it == (char*)self + 0x10)
    return false;
  return ((bool(__stdcall*)(void*))Sub_8026e0)((char*)it + 0x14);
}
bool __stdcall Sub_8026e0(void* info);

// @ 0x00802870
unsigned __thiscall Sub_802870(unsigned arg) {
  if (arg != 0x2f009dd0)
    return 0;
  return ((unsigned)(this_ptr_check) != 4) ? (unsigned)this_ptr_value : 0;
}

// @ 0x008028e0
bool __fastcall Sub_8028e0(void* self) {
  if (*(void**)((char*)self + 0x28)) {
    ((CursorLayout*)((char*)self + 0x10))->Shutdown(true);
    RCObj* p = *(RCObj**)((char*)self + 0x28);
    if (p) {
      *(void**)((char*)self + 0x28) = 0;
      p->Release();
    }
  }
  return true;
}

// @ 0x00802890
void* __thiscall Sub_802890(void* self, void* want) {
  void* w = ((CursorLayout*)((char*)self + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return 0;
  if (((void* (__thiscall*)(void*))((*(void***)w)[0x1c / 4]))(w) == want)
    return w;
  return ((void* (__thiscall*)(void*, void*, int))((*(void***)w)[0xf0 / 4]))(w, want, 1);
}

// ---------------------------------------------------------------------------
// @ 0x008026e0  resolve cursor hotspots + handle
// ---------------------------------------------------------------------------
struct IconInfo { int f0; int f1; void* hbmColor; void* hbmMask; };
bool __stdcall Sub_8026e0(void* info) {
  *(void**)((char*)info + 0x18) = 0;
  IconInfo ii;
  ii.f0 = 0; ii.f1 = 0; ii.hbmColor = 0; ii.hbmMask = 0;
  void* obj = Eapd_ObjectError();
  void* a = *(void**)info;
  ((void(__thiscall*)(void*, int, int, void*, void*))((*(void***)obj)[0x78 / 4]))(
      obj, 0x2393756, 0x2393c07, &ii, 0);
  void* obj2 = Eapd_ObjectError();
  void* tmp = *(void**)((char*)info + 0x1c);
  if (tmp) {
    *(void*)((char*)info + 0x1c) = 0;
    ((RCObj*)tmp)->Release();
  }
  if (((uint8_t (__thiscall*)(void*, ...))((*(void***)obj2)[0xc / 4]))(obj2, a, 0, 0, 0, 0)) {
    void* hIcon = *(void**)((char*)a + 0x14);
    if (GetIconInfo(hIcon, &ii)) {
      *(int*)((char*)info + 0x10) = ii.f0;
      *(int*)((char*)info + 0x14) = ii.f1;
    }
    *(void**)((char*)info + 0x18) = hIcon;
  }
  bool r = *(void**)((char*)info + 0x18) != 0;
  void* q = *(void**)((char*)info + 0x1c);
  if (q)
    ((RCObj*)q)->Release();
  return r;
}

// ---------------------------------------------------------------------------
// @ 0x00801fd0  destructor of the cursor-manager base
// ---------------------------------------------------------------------------
extern char dc_a[], dc_b[], dc_c[], dc_d[];
void __fastcall Sub_801fd0(void* self) {
  *(void**)self = (void*)dc_a;
  *(void**)((char*)self + 8) = (void*)dc_b;
  RCObj* p;
  p = *(RCObj**)((char*)self + 0x54);
  if (p) ((void(__thiscall*)(void*))((*(void***)p)[8 / 4]))(p);
  p = *(RCObj**)((char*)self + 0x50);
  if (p) p->Release();
  p = *(RCObj**)((char*)self + 0x4c);
  if (p) p->Release();
  p = *(RCObj**)((char*)self + 0x48);
  if (p) p->Release();
  ((void(__thiscall*)(void*, void*))0x801ef0)((char*)self + 0xc, *(void**)((char*)self + 0x18));
  *(void**)((char*)self + 8) = (void*)dc_c;
  *(void**)self = (void*)dc_d;
}

// ---------------------------------------------------------------------------
// @ 0x008025e0  constructor of the cursor-manager base
// ---------------------------------------------------------------------------
extern char cc_a[], cc_b[], cc_c[];
void* __fastcall Sub_8025e0(void* self) {
  *(void**)self = (void*)cc_a;
  int z = 0;
  *(void**)((char*)self + 4) = 0;   // atomic xchg
  *(void**)((char*)self + 8) = (void*)cc_b;
  *(void**)self = (void*)cc_c;
  *(void**)((char*)self + 8) = (void*)0x1416fd4;
  *(void**)((char*)self + 0x14) = 0;
  *(void**)((char*)self + 0x18) = 0;
  *(void**)((char*)self + 0x1c) = 0;
  *(void**)((char*)self + 0x18) = 0;
  *(uint8_t*)((char*)self + 0x1c) = 0;
  *(void**)((char*)self + 0x20) = 0;
  *(void**)((char*)self + 0x10) = (char*)self + 0x10;
  *(void**)((char*)self + 0x14) = (char*)self + 0x10;
  *(uint8_t*)((char*)self + 0x28) = (uint8_t)z;
  *(void**)((char*)self + 0x2c) = 0;
  *(void**)((char*)self + 0x30) = 0;
  *(void**)((char*)self + 0x34) = 0;
  *(void**)((char*)self + 0x38) = 0;
  *(void**)((char*)self + 0x3c) = 0;
  *(uint8_t*)((char*)self + 0x40) = 1;
  *(uint8_t*)((char*)self + 0x41) = 1;
  *(uint8_t*)((char*)self + 0x42) = 1;
  *(uint8_t*)((char*)self + 0x43) = 0;
  *(uint8_t*)((char*)self + 0x44) = 0;
  *(void**)((char*)self + 0x48) = 0;
  *(void**)((char*)self + 0x4c) = 0;
  *(void**)((char*)self + 0x50) = 0;
  *(void**)((char*)self + 0x54) = 0;
  *(void**)((char*)self + 0x58) = 0;
  ((void(__fastcall*)(void*))0x8019f0)(self - 0);
  return self;
}

// ---------------------------------------------------------------------------
// @ 0x008019f0  read the two cursor offsets from the property database
// ---------------------------------------------------------------------------
extern float g_15435bc, g_15435c0;
void Sub_8019f0() {
  void* pm = SP_PropertyManager();
  void* obj = 0;
  if (pm) {
    // PropertyManager::Get(...); property "cursor offset x"
    int prop = 0;
    float* v = 0;
    if (((uint8_t(__thiscall*)(void*, int, void*, int))((*(void***)pm)[0x30 / 4]))(
            pm, 0x1bae779, &prop, 0) &&
        *(short*)((char*)&prop + 0x12) == 0xd) {
      v = SP_GetPropertyAsFloat();
      g_15435bc = *v;
    }
    if (((uint8_t(__thiscall*)(void*, int, void*, int))((*(void***)pm)[0x24 / 4]))(
            pm, 0x1bae783, &prop, 0) &&
        *(short*)((char*)&prop + 0x12) == 0xd) {
      v = SP_GetPropertyAsFloat();
      g_15435c0 = *v;
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00801ac0  factory create of the cursor manager resource
// ---------------------------------------------------------------------------
extern char fac_a[], fac_b[];
struct CursorMgrObj { char data[0x18]; };
int __thiscall Sub_801ac0(void* self, void* param_2, void* param_3, int param_4, int param_5) {
  if (param_5 != 0x2393756)
    return 0;
  CursorMgrObj* p = (CursorMgrObj*)operator_new(0x18, "App/cSPUICursorManager", 0, 0, 0, 0);
  CursorMgrObj* r = 0;
  if (p) {
    *(void**)p = (void*)fac_a;
    *(void**)((char*)p + 4) = 0;
    *(void**)((char*)p + 8) = 0;
    *(void**)((char*)p + 0xc) = 0;
    *(void**)((char*)p + 0x10) = 0;
    *(void**)p = (void*)fac_b;
    r = p;
  }
  void* v = ((void* (__thiscall*)(void*))((*(void***)param_2)[0x10 / 4]))(param_2);
  *(void**)((char*)r + 8) = *(void**)v;
  *(void**)((char*)r + 0xc) = *(void**)((char*)v + 4);
  *(void**)((char*)r + 0x10) = *(void**)((char*)v + 8);
  if (((uint8_t(__thiscall*)(void*, void*, void*, int, int))((*(void***)self)[0x24 / 4]))(
          self, param_2, r, param_4, 0x2393756)) {
    *(void**)((char*)self + 0) = r;
    ((void(__thiscall*)(void*))((*(void***)r)[0]))(r);
    return 1;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00801d80  save a cursor to a temporary file
// ---------------------------------------------------------------------------
int __cdecl f_932580(void* p, int a, int b, int c);
void __thiscall FileStream_ctor(void* s, void* path);
int  __cdecl FileStream_Open(void*, int, int, int, int);
void __cdecl FileStream_Write(void*, void*, int);
void __cdecl FileStream_Close(void*);
void __cdecl FileStream_dtor(void*);
void __cdecl File_Remove(const wchar_t*);
int  __cdecl f_686430(void*, void*);
int  __stdcall Sub_8026b0b(const wchar_t* name, void* info);
uint8_t __thiscall Sub_801d80(int* self, void* param_2, int param_3, int param_4) {
  uint8_t result = 0;
  if (param_4 == 0x2393756) {
    char pathbuf[520];
    char fs[0x100];
    f_932580(pathbuf, 0, 0, 0);
    FileStream_ctor(fs, pathbuf);
    if (FileStream_Open(fs, 2, 6, 1, 0)) {
      void* a = ((void* (__thiscall*)(int*))((*(int***)self)[0x18 / 4]))(self);
      int n = ((int(__thiscall*)(void*))((*(void***)a)[0x1c / 4]))(a);
      char buf[5];
      f_686430((void*)n, buf);
      ((void(__thiscall*)(void*, int, int))((*(void***)a)[0x30 / 4]))(a, n, n);
      FileStream_Write(fs, (void*)n, n);
      FileStream_Close(fs);
      result = (uint8_t)Sub_8026b0b((wchar_t*)pathbuf, param_2);
      File_Remove((wchar_t*)pathbuf);
      if (n && *(int*)(n - 4))
        operator_delete((void*)n);
    }
    FileStream_dtor(fs);
  }
  return result;
}

// ---------------------------------------------------------------------------
// @ 0x00801c80  rbtree<cCursorInfo>::DoCreateNode
// ---------------------------------------------------------------------------
void __thiscall String_AllocateSelf(void* s, int n);
void __thiscall String_DoInsertValue(void* s, void* dst, const void* src, unsigned n);
void* __thiscall Rbtree_DoCreateNode(void* self, void* arg) {
  void* node = (void*)operator_new(0x18, "EASTL/rbtree", 0, 0, 0, 0);
  *(void**)node = 0;
  *(void**)((char*)node + 4) = 0;
  *(void**)((char*)node + 8) = 0;
  const void* src = *(void**)arg;
  int n = (*(int*)((char*)arg + 4) - (int)src) >> 1;
  String_AllocateSelf(node, n + 1);
  void* dst = *(void**)node;
  String_DoInsertValue(node, dst, src, n * 2);
  void* end = (char*)dst + n * 2;
  *(void**)((char*)node + 4) = end;
  *(uint16_t*)end = 0;
  *(void**)((char*)node + 0x10) = *(void**)((char*)arg + 0x10);
  *(void**)((char*)node + 0x14) = *(void**)((char*)arg + 0x14);
  *(void**)((char*)node + 0x18) = *(void**)((char*)arg + 0x18);
  *(void**)((char*)node + 0x1c) = *(void**)((char*)arg + 0x1c);
  return node;
}

// ---------------------------------------------------------------------------
// @ 0x00801e90  rbtree<cCursorInfo>::erase
// ---------------------------------------------------------------------------
void __thiscall Rbtree_erase(void* tree, void** outIter, void* node) {
  *(int*)((char*)tree + 0x14) = *(int*)((char*)tree + 0x14) - 1;
  void* next = (void*)(uintptr_t)RBTreeIncrement(node);
  RBTreeErase(node, (char*)tree + 4);
  int a = *(int*)((char*)node + 0x14);
  if (((*(int*)((char*)node + 0x1c) - a) & 0xfffffffe) > 2 && a)
    operator_delete((void*)a);
  operator_delete(node);
  *outIter = next;
}

// ---------------------------------------------------------------------------
// @ 0x00801ef0  rbtree<cCursorInfo>::DoNukeSubtree
// ---------------------------------------------------------------------------
void __cdecl Rbtree_DoNukeSubtree(void* node) {
  while (node) {
    Rbtree_DoNukeSubtree(*(void**)node);
    int a = *(int*)((char*)node + 0x14);
    void* next = *(void**)((char*)node + 4);
    if (((*(int*)((char*)node + 0x1c) - a) & 0xfffffffe) > 2 && a)
      operator_delete((void*)a);
    operator_delete(node);
    node = next;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00802050  cSPUICursorManager::AddCursor
// ---------------------------------------------------------------------------
struct WideStr {
  char pad[0x10];
};
uint32_t __thiscall AddCursor(void* self, uint32_t id, WideStr* name, char load, int a, int b) {
  void* it = 0;
  ((void(__thiscall*)(void*, uint32_t*, void**))0xe5c780)((char*)self + 0xc, &id, &it);
  if (it == (char*)self + 0x10) {
    return 0;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00802160  cSPUICursorManager::AddStandardCursors
// ---------------------------------------------------------------------------
struct Str16 { const wchar_t* p; };
int __thiscall AddStandardCursors(void* self) {
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00802910  cSPUIDebugConsole::Clear
// ---------------------------------------------------------------------------
void __thiscall DebugConsole_Clear(void* self) {
}

// ---------------------------------------------------------------------------
// @ 0x00802950  cSPUIDebugConsole::Output
// ---------------------------------------------------------------------------
void __thiscall DebugConsole_Output(void* self, char* a, char* b) {
  (void)a; (void)b;
}
