// Spore decompilation - batch w2g6, slice s008019f0 (0x008019F0..0x00802A2F).
// cSPUICursorManager (cursor table + registration + Win32 cursor loads), the cursor
// map's EASTL rbtree instantiations, position persistence, and cSPUIDebugConsole.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include <new>
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (declared only)
// ---------------------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* f, int l);
void  __cdecl operator_delete(void* p);
extern "C" void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
unsigned __cdecl RBTreeIncrement(void* node);
void  __cdecl RBTreeErase(void* node, void* anchor); // 0x00921880

void*  __cdecl SP_PropertyManager();
float* __cdecl SP_GetPropertyAsFloat();
void*  __cdecl SP_Canvas();
void*  __cdecl Eapd_ObjectError();

bool __stdcall Sub_8026b0(const wchar_t* name, void* info);
bool __stdcall Sub_8026e0(void* info);

// the cursor map's rbtree interface (external instantiations)
struct MapBase {
  void Find(uint32_t* key, void** outIter);   // 0x00E5C780
  void Erase(void** outIter, void* node);     // 0x00801E90
  void NukeSubtree(void* node);               // 0x00801EF0
};

// the wide-string allocator used by the node value
struct WStr {
  void AllocateSelf(int n);                              // 0x00429760
  void DoInsertValue(void* dst, const void* src, unsigned n);  // 0x011E0744
};

// node construction (this = destination node)
struct RbtreeNode { void* DoCreateNode(void* value); };  // 0x00801C80

extern "C" {
__declspec(dllimport) void* __stdcall LoadImageW(void* hinst, const wchar_t* name, unsigned type,
                                                 int cx, int cy, unsigned fuLoad);
__declspec(dllimport) int   __stdcall GetIconInfo(void* icon, void* iconInfo);
__declspec(dllimport) int   __stdcall DestroyCursor(void* cursor);
}

struct RCObj { virtual void r0(); virtual void Release(); };

// methods of classes owned by slice s007ffc70 (declared only -> out-of-line calls)
struct Slice11 {
  void SetWindow(void* p);
  bool SetEnabled(bool v);
  bool Enable(int a);
};

// ---------------------------------------------------------------------------
// cSPUICursorManager (retail layout, larger than the dev PDB's 0x44)
// ---------------------------------------------------------------------------
struct CurMgr {
  char data[0x60];
  bool Clear();                    // 0x00802580
  bool Shutdown();                 // 0x00802680
  bool FindLocal(uint32_t k);      // 0x00801bb0
  bool FindGlobal(uint32_t k);     // 0x00801b60
  bool FindCanvas(uint32_t k);     // 0x00801c10
  bool FindCanvasAdj(uint32_t k);  // 0x00801c70
  bool Remove(uint32_t k);         // 0x008024e0
  void Refresh();                  // 0x008027e0
  bool DestroyEntry(void* it);     // 0x008027a0
  bool CheckEntry(void* it);       // 0x00802850
};

// @ 0x00802580  clear the whole cursor map
bool CurMgr::Clear() {
  if (*(int*)((char*)this + 0x20) != 0) {
    do {
      void* node = *(void**)((char*)this + 0x14);
      *(int*)((char*)this + 0x20) -= 1;
      RBTreeIncrement(node);
      RBTreeErase(node, (char*)this + 0x10);
      int a = *(int*)((char*)node + 0x14);
      int sz = (*(int*)((char*)node + 0x1c) - a) & 0xfffffffe;
      if (sz > 2 && a)
        EASTL_allocator_deallocate((void*)a);
      EASTL_allocator_deallocate(node);
    } while (*(int*)((char*)this + 0x20) != 0);
  }
  return true;
}

// @ 0x00802680
bool CurMgr::Shutdown() {
  if (*(uint8_t*)((char*)this + 0x28)) {
    ((Slice11*)(void*)this)->SetWindow(0);
    this->Clear();
    *(void**)((char*)this + 0x38) = 0;
    *(void**)((char*)this + 0x34) = 0;
    *(void**)((char*)this + 0x2c) = 0;
    *(void**)((char*)this + 0x30) = 0;
    *(void**)((char*)this + 0x3c) = 0;
    *(uint8_t*)((char*)this + 0x28) = 0;
  }
  return true;
}

// @ 0x00801c70  secondary-base adjustor for FindCanvas
bool CurMgr::FindCanvasAdj(uint32_t k) {
  return ((CurMgr*)((char*)this - 8))->FindCanvas(k);
}

// @ 0x00801c10
bool CurMgr::FindCanvas(uint32_t k) {
  void* it = 0;
  ((MapBase*)((char*)this + 0xc))->Find(&k, &it);
  void* found = (it == (char*)this + 0x10) ? 0 : (char*)it + 0x14;
  if (found != *(void**)((char*)this + 0x34)) {
    *(void**)((char*)this + 0x34) = found;
    if (found)
      this->Refresh();
  }
  return found != 0;
}

// @ 0x00801bb0
bool CurMgr::FindLocal(uint32_t k) {
  void* it = 0;
  ((MapBase*)((char*)this + 0xc))->Find(&k, &it);
  if (it == (char*)this + 0x10)
    return false;
  void* found = (char*)it + 0x14;
  if (found && found != *(void**)((char*)this + 0x2c)) {
    *(void**)((char*)this + 0x2c) = found;
    this->Refresh();
  }
  return found != 0;
}

// @ 0x00801b60
bool CurMgr::FindGlobal(uint32_t k) {
  void* it = 0;
  ((MapBase*)((char*)this + 0xc))->Find(&k, &it);
  void* found = (it == (char*)this + 0x10) ? 0 : (char*)it + 0x14;
  if (found != *(void**)((char*)this + 0x30)) {
    *(void**)((char*)this + 0x30) = found;
    if (found)
      this->Refresh();
  }
  return found != 0;
}

// @ 0x008027e0
void CurMgr::Refresh() {
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
               (*(void**)info != *(void**)((char*)info + 4) && Sub_8026e0(info)))) {
    h = *(void**)((char*)(*(void**)((char*)this + 0x38)) + 0x18);
  }
  void* c = SP_Canvas();
  ((void(__thiscall*)(void*, void*))((*(void***)c)[0x80 / 4]))(c, h);
}

// @ 0x008024e0
bool CurMgr::Remove(uint32_t k) {
  void* it = 0;
  ((MapBase*)((char*)this + 0xc))->Find(&k, &it);
  if (it == (char*)this + 0x10)
    return false;
  void* info = (char*)it + 0x14;
  if (info == *(void**)((char*)this + 0x30)) *(void**)((char*)this + 0x30) = 0;
  if (info == *(void**)((char*)this + 0x2c)) *(void**)((char*)this + 0x2c) = 0;
  if (info == *(void**)((char*)this + 0x38)) *(void**)((char*)this + 0x38) = 0;
  if (info == *(void**)((char*)this + 0x34)) *(void**)((char*)this + 0x34) = 0;
  bool r = this->DestroyEntry(it);
  void* out = 0;
  ((MapBase*)((char*)this + 0xc))->Erase(&out, it);
  if (*(uint8_t*)((char*)this + 0x40) && *(void**)((char*)this + 0x38) != 0)
    this->Refresh();
  return r;
}

// @ 0x008027a0
bool CurMgr::DestroyEntry(void* it) {
  if (it == (char*)this + 0x10)
    return false;
  void* h = *(void**)((char*)it + 0x2c);
  bool r = true;
  if (h)
    r = DestroyCursor(h) != 0;
  *(void**)((char*)it + 0x2c) = 0;
  return r;
}

// @ 0x00802850
bool CurMgr::CheckEntry(void* it) {
  if (it == (char*)this + 0x10)
    return false;
  return Sub_8026e0((char*)it + 0x14);
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

// @ 0x00802870
struct C_802870 { unsigned f(unsigned arg); };
unsigned C_802870::f(unsigned arg) {
  if (arg != 0x2f009dd0)
    return 0;
  return ((char*)this - 4) ? (unsigned)(unsigned)this : 0u;
}

// @ 0x008028e0
struct CursorLayout {
  void Shutdown(bool recursive);
  void* FindWindowByID(uint32_t id, int recursive);
};
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
struct C_802890 { void* f(void* want); };
void* C_802890::f(void* want) {
  void* w = ((CursorLayout*)((char*)this + 0x10))->FindWindowByID(0x14a4606, 1);
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
    *(void**)((char*)info + 0x1c) = 0;
    ((RCObj*)tmp)->Release();
  }
  if (((uint8_t (__thiscall*)(void*, void*, int, int, int, int))((*(void***)obj2)[0xc / 4]))(
          obj2, a, 0, 0, 0, 0)) {
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
  _ReadWriteBarrier();
  RCObj* p;
  p = *(RCObj**)((char*)self + 0x54);
  if (p) ((void(__thiscall*)(void*))((*(void***)p)[8 / 4]))(p);
  p = *(RCObj**)((char*)self + 0x50);
  if (p) p->Release();
  p = *(RCObj**)((char*)self + 0x4c);
  if (p) p->Release();
  p = *(RCObj**)((char*)self + 0x48);
  if (p) p->Release();
  void* root = *(void**)((char*)self + 0x18);
  MapBase* map = (MapBase*)((char*)self + 0xc);
  map->NukeSubtree(root);
  *(void**)((char*)self + 8) = (void*)dc_c;
  *(void**)self = (void*)dc_d;
}

// ---------------------------------------------------------------------------
// @ 0x008025e0  constructor of the cursor-manager base
// ---------------------------------------------------------------------------
extern char cc_a[], cc_b[], cc_c[];
void Sub_8019f0();
void* __fastcall Sub_8025e0(void* self) {
  *(void**)self = (void*)cc_a;
  *(void**)((char*)self + 4) = 0;
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
  *(uint8_t*)((char*)self + 0x28) = 0;
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
  Sub_8019f0();
  return self;
}

// ---------------------------------------------------------------------------
// @ 0x008019f0  read the two cursor offsets from the property database
// ---------------------------------------------------------------------------
extern float g_15435bc, g_15435c0;
void Sub_8019f0() {
  void* pm = SP_PropertyManager();
  if (pm) {
    struct Prop { int v[8]; } prop;
    prop.v[0] = 0;
    if (((uint8_t(__thiscall*)(void*, int, void*, int))((*(void***)pm)[0x30 / 4]))(
            pm, 0x1bae779, &prop, 0) &&
        *(short*)((char*)&prop + 0x12) == 0xd) {
      g_15435bc = *SP_GetPropertyAsFloat();
    }
    if (((uint8_t(__thiscall*)(void*, int, void*, int))((*(void***)pm)[0x24 / 4]))(
            pm, 0x1bae783, &prop, 0) &&
        *(short*)((char*)&prop + 0x12) == 0xd) {
      g_15435c0 = *SP_GetPropertyAsFloat();
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00801ac0  factory create of the cursor manager resource
// ---------------------------------------------------------------------------
extern char fac_a[], fac_b[];
struct C_801ac0 { int f(void* p2, void* p3, int p4, int p5); };
int C_801ac0::f(void* param_2, void* param_3, int param_4, int param_5) {
  if (param_5 != 0x2393756)
    return 0;
  void* p = operator_new(0x18, "App/cSPUICursorManager", 0, 0, 0, 0);
  void* r = 0;
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
  if (((uint8_t(__thiscall*)(void*, void*, void*, int, int))((*(void***)this)[0x24 / 4]))(
          this, param_2, r, param_4, 0x2393756)) {
    *(void**)((char*)param_3 + 0) = r;
    ((void(__thiscall*)(void*))((*(void***)r)[0]))(r);
    return 1;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00801d80  save a cursor to a temporary file
// ---------------------------------------------------------------------------
struct FileStream {
  void Ctor(void* path);                  // 0x00??????
  int  Open(int a, int b, int c, int d);
  void Write(void* data, int n);
  void Close();
  void Dtor();
};
int  __cdecl f_932580(void* p, int a, int b, int c);
void __cdecl File_Remove(const wchar_t*);
int  __cdecl f_686430(void*, void*);
struct C_801d80 { uint8_t f(void* param_2, int param_3, int param_4); };
uint8_t C_801d80::f(void* param_2, int param_3, int param_4) {
  uint8_t result = 0;
  if (param_4 == 0x2393756) {
    char pathbuf[520];
    char fs[0x100];
    f_932580(pathbuf, 0, 0, 0);
    ((FileStream*)fs)->Ctor(pathbuf);
    if (((FileStream*)fs)->Open(2, 6, 1, 0)) {
      void* a = ((void* (__thiscall*)(void*))((*(void***)this)[0x18 / 4]))(this);
      int n = ((int(__thiscall*)(void*))((*(void***)a)[0x1c / 4]))(a);
      char buf[5];
      f_686430((void*)n, buf);
      ((void(__thiscall*)(void*, int, int))((*(void***)a)[0x30 / 4]))(a, n, n);
      ((FileStream*)fs)->Write((void*)n, n);
      ((FileStream*)fs)->Close();
      result = (uint8_t)Sub_8026b0((wchar_t*)pathbuf, param_2);
      File_Remove((wchar_t*)pathbuf);
      if (n && *(int*)(n - 4))
        operator_delete((void*)n);
    }
    ((FileStream*)fs)->Dtor();
  }
  return result;
}

// ---------------------------------------------------------------------------
// @ 0x00801c80  rbtree<cCursorInfo>::DoCreateNode
// ---------------------------------------------------------------------------
void* RbtreeNode::DoCreateNode(void* arg) {
  void* node = this;
  *(void**)node = 0;
  *(void**)((char*)node + 4) = 0;
  *(void**)((char*)node + 8) = 0;
  const void* src = *(void**)arg;
  int n = (*(int*)((char*)arg + 4) - (int)src) >> 1;
  ((WStr*)node)->AllocateSelf(n + 1);
  void* dst = *(void**)node;
  ((WStr*)node)->DoInsertValue(dst, src, n * 2);
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
void MapBase::Erase(void** outIter, void* node) {
  void* tree = this;
  *(int*)((char*)tree + 0x14) = *(int*)((char*)tree + 0x14) - 1;
  void* next = (void*)(unsigned)RBTreeIncrement(node);
  RBTreeErase(node, (char*)tree + 4);
  int a = *(int*)((char*)node + 0x14);
  int sz = (*(int*)((char*)node + 0x1c) - a) & 0xfffffffe;
  if (sz > 2 && a)
    operator_delete((void*)a);
  operator_delete(node);
  *outIter = next;
}

// ---------------------------------------------------------------------------
// @ 0x00801ef0  rbtree<cCursorInfo>::DoNukeSubtree
// ---------------------------------------------------------------------------
void MapBase::NukeSubtree(void* node) {
  while (node) {
    this->NukeSubtree(*(void**)node);
    int a = *(int*)((char*)node + 0x14);
    void* next = *(void**)((char*)node + 4);
    int sz = (*(int*)((char*)node + 0x1c) - a) & 0xfffffffe;
    if (sz > 2 && a)
      operator_delete((void*)a);
    operator_delete(node);
    node = next;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00802050  cSPUICursorManager::AddCursor  (behavioural approximation)
// ---------------------------------------------------------------------------
struct CursorTable {
  uint32_t AddCursor(void* self, uint32_t id, const wchar_t* name, char load, int a, int b);
  int AddStandardCursors();
};
uint32_t CursorTable::AddCursor(void* self, uint32_t id, const wchar_t* name, char load, int a, int b) {
  void* it = 0;
  uint32_t key = id;
  ((MapBase*)((char*)self + 0xc))->Find(&key, &it);
  if (it != (char*)self + 0x10)
    return 0;
  (void)name; (void)load; (void)a; (void)b;
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00802160  cSPUICursorManager::AddStandardCursors
// ---------------------------------------------------------------------------
int CursorTable::AddStandardCursors() {
  AddCursor(this, 0x1001, L"STD_None", 1, 0, 0);
  AddCursor(this, 0x1005, L"STD_Center", 0, 0, 0);
  AddCursor(this, 0x1004, L"STD_IBeam", 0, 0, 0);
  AddCursor(this, 0x1006, L"cursor_link", 0, 0, 0);
  AddCursor(this, 0x1007, L"STD_Help", 0, 0, 0);
  AddCursor(this, 0x1008, L"STD_SizeNS", 0, 0, 0);
  AddCursor(this, 0x1009, L"STD_SizeWE", 0, 0, 0);
  AddCursor(this, 0x100a, L"STD_SizeNWSE", 0, 0, 0);
  AddCursor(this, 0x100b, L"STD_SizeNESW", 0, 0, 0);
  AddCursor(this, 0x100c, L"STD_SizeAll", 0, 0, 0);
  AddCursor(this, 0x100d, L"cursor-dragselect", 1, 0, 0);
  AddCursor(this, 0x1002, L"cursor-default", 1, 0, 0);
  AddCursor(this, 0x1011, L"cursor-default-debug", 1, 0, 0);
  AddCursor(this, 0x1003, L"cursor-wait", 1, 0, 0);
  AddCursor(this, 0x1024, L"cursor-active-wait", 1, 0, 0);
  AddCursor(this, 0x100e, L"cursor-magicwand", 1, 0, 0);
  AddCursor(this, 0x100f, L"cursor-paint", 1, 0, 0);
  AddCursor(this, 0x1010, L"cursor-eyedropper", 1, 0, 0);
  AddCursor(this, 0x1012, L"cursor-default-alpha01", 1, 0, 0);
  AddCursor(this, 0x1013, L"cursor-default-alpha02", 1, 0, 0);
  AddCursor(this, 0x1014, L"cursor-default-alpha03", 1, 0, 0);
  AddCursor(this, 0x1015, L"cursor-default-alpha04", 1, 0, 0);
  AddCursor(this, 0x1016, L"cursor-default-alpha05", 1, 0, 0);
  AddCursor(this, 0x1017, L"cursor-default-alpha06", 1, 0, 0);
  AddCursor(this, 0x1018, L"cursor-default-alpha07", 1, 0, 0);
  AddCursor(this, 0x1019, L"cursor-default-alpha08", 1, 0, 0);
  AddCursor(this, 0x101a, L"cursor-default-alpha09", 1, 0, 0);
  AddCursor(this, 0x101b, L"STD_Center-alpha01", 1, 0, 0);
  AddCursor(this, 0x101c, L"STD_Center-alpha02", 1, 0, 0);
  AddCursor(this, 0x101d, L"STD_Center-alpha03", 1, 0, 0);
  AddCursor(this, 0x101e, L"STD_Center-alpha04", 1, 0, 0);
  AddCursor(this, 0x101f, L"STD_Center-alpha05", 1, 0, 0);
  AddCursor(this, 0x1020, L"STD_Center-alpha06", 1, 0, 0);
  AddCursor(this, 0x1021, L"STD_Center-alpha07", 1, 0, 0);
  AddCursor(this, 0x1022, L"STD_Center-alpha08", 1, 0, 0);
  AddCursor(this, 0x1023, L"STD_Center-alpha09", 1, 0, 0);
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00802910  cSPUIDebugConsole::Clear
// ---------------------------------------------------------------------------
void __cdecl DebugConsole_Clear(void* self) {
  (void)self;
}

// ---------------------------------------------------------------------------
// @ 0x00802950  cSPUIDebugConsole::Output
// ---------------------------------------------------------------------------
void __cdecl DebugConsole_Output(void* self, char* a, char* b) {
  (void)self; (void)a; (void)b;
}
// --- equivalence checker address annotations
    void RBTreeErase(...); // 0x00921880
    void operator_delete(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
