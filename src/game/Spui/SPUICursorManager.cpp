// src/game/Spui/SPUICursorManager.cpp -- migrated from slice(s) s008019f0, s007ffc70 by tools/migrate/rewrite.py
// Object file: Spui/SPUICursorManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_15435bc, g_15435c0;
#include <new>
#include <intrin.h>
#include "EA/IO/FileStream.h"

// ---- items of slice s007ffc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(p, off) (*(void***)(p))[((off) >> 2)]
void* __stdcall f_9512c0();
void* __cdecl f_9512d0(unsigned size, int align, const char* name, void* alloc);
void* __cdecl f_67dd00();                     // SP::AppSystem
void* __cdecl f_67dcf0();                     // SP::Canvas
void  __fastcall f_8027e0(void* self);
void  __cdecl f_804f10(float a, float b);
void  __cdecl f_804ed0(float* a, float* b);
bool  __cdecl f_806a60(void* a, void* b, int c, int d);
void* __cdecl f_805070(uint32_t id);          // SPUIHelpers::GetLayoutManager
void* __cdecl f_80620(void* manager);         // cSPUILayoutManager::GetWorldMainWindow
void* __cdecl f_962a10(void* p);              // UI::Window::Window
extern float g_15435bc, g_15435c0;
struct C_801360 { char pad[0x58]; int mCount; void Show(); void Hide(); };
struct C_8013d0 { char pad[0x40]; uint8_t m40; bool Set40(uint8_t v); };
struct C_8014c0 {
  char pad0[0x28];
  uint8_t m28;          // +0x28
  char pad29[0x23];
  void* m4c;            // +0x4c
  int Init();
};
struct C_8016e0 { char pad[0x48]; void* m48; void* m4c; void Move(float x, float y); };
struct C_8017f0 { char pad[0x48]; void* m48; void* m4c; bool Set(void* p); };
struct C_801950 { char pad[0x50]; void* m50; void* m54; bool Run(int a); };
struct C_801980 { char pad[0x44]; uint8_t m44; char pad45[0xb]; void* m50; void Set(bool v); };
// ---- items of slice s007ffc70 end

// ---- items of slice s008019f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char fac_a[], fac_b[];
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* f, int l);
struct C_801ac0 { int f(void* p2, void* p3, int p4, int p5); };
extern "C" void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" __declspec(dllimport) void* __stdcall LoadImageW(void* hinst, const wchar_t* name, unsigned type,
int cx, int cy, unsigned fuLoad);
extern char dc_a[];   // 0x01416fe8 (equiv t3)
extern char dc_b[];   // 0x01416fd4 (equiv t3)
extern char dc_c[];   // 0x013eb938 (equiv t3)
extern char dc_d[];   // 0x013effb8 (equiv t3)
extern char cc_a[], cc_b[], cc_c[];
void  __cdecl operator_delete(void* p);
unsigned __cdecl RBTreeIncrement(void* node);
void  __cdecl RBTreeErase(void* node, void* anchor); // 0x00921880
void*  __cdecl SP_PropertyManager();
float* __cdecl SP_GetPropertyAsFloat();
bool __stdcall Sub_8026b0(const wchar_t* name, void* info);
bool __stdcall Sub_8026e0(void* info);
struct MapBase {
  void Find(void** outIter, const uint32_t* key);   // 0x00E5C780
  void Erase(void** outIter, void* node);     // 0x00801E90
  void NukeSubtree(void* node);               // 0x00801EF0
};
struct WStr {
  void AllocateSelf(int n);                              // 0x00429760
};
void __cdecl DoInsertValue(void* dst, const void* src, unsigned n);  // 0x011E0744
struct RbtreeNode { void* DoCreateNode(void* value); };  // 0x00801C80
struct RCObj { virtual void r0(); virtual void Release(); };
struct Slice11 {
  void SetWindow(void* p);
  bool SetEnabled(bool v);
  bool Enable(int a);
};
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
  __declspec(noinline) bool DestroyEntry(void* it);     // 0x008027a0
  bool CheckEntry(void* it);       // 0x00802850
};
struct C_802870 { unsigned f(unsigned arg); };
unsigned C_802870::f(unsigned arg) {
  if (arg != 0x2f009dd0)
    return 0;
  return ((char*)this - 4) ? (unsigned)(unsigned)this : 0u;
}
void Sub_8019f0();
struct FileStream {
  uint32_t mData[0x22c / 4];
  FileStream(const wchar_t* path);        // 0x00931e10 (ret 4)
  ~FileStream();                          // 0x00931e70
  bool Open(int access, int disposition, int sharing, int usage);   // 0x009318f0 (ret 0x10)
  bool Write(const void* data, unsigned n);                          // 0x00931d30 (ret 8)
  bool Close();                           // 0x00931a70
};
void __cdecl CreateTempFile(wchar_t* path, int a, int b, int c);   // 0x00932580
bool __cdecl FileRemove(const wchar_t* path);                       // 0x00931fd0
struct VecBuf {
  int* mpBegin; int* mpEnd; int* mpCapacity; int mAlloc[2];
  int* Init(unsigned n, void* tag);       // 0x00686430 (ret 8)
};
struct IRecordSrc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
                    virtual struct IRecordObj* GetRecord(); };      // +0x18
struct IRecordObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
                    virtual unsigned GetSize();                      // +0x1c
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
                    virtual void Read(void* dst, unsigned n); };    // +0x30
struct EmptyTag801d80 {};
struct C_801d80 {
  bool SetCursor(const wchar_t* path, void* info);   // 0x008026b0 (ret 8; ecx unused)
  uint8_t f(IRecordSrc* src, void* info, int c, int type);
};
struct CursorTable {
  uint32_t AddCursor(void* self, uint32_t id, const wchar_t* name, char load, int a, int b);
  int AddStandardCursors();
};
// ---- items of slice s008019f0 end

// @ 0x00801330
int __stdcall f_801330(void* p, unsigned n)
{
  if (p) {
    if (n < 1)
      return 0;
    *(uint32_t*)p = 0x2393756;
  }
  return 1;
}

// @ 0x00801360
void C_801360::Show()
{
  if (++mCount == 1) {
    f_8027e0(this);
    void* a = f_67dd00();
    ((void (__thiscall*)(void*, int))VFN(a, 0x40))(a, 1);
  }
}

// @ 0x00801380
void C_801360::Hide()
{
  if (mCount > 0) {
    if (--mCount == 0) {
      void* a = f_67dd00();
      ((void (__thiscall*)(void*, int))VFN(a, 0x40))(a, 0);
      f_8027e0(this);
    }
  }
}

// @ 0x008013d0
bool C_8013d0::Set40(uint8_t v)
{
  if (m40 != v) {
    m40 = v;
    void* c = f_67dcf0();
    ((void (__thiscall*)(void*, uint32_t))VFN(c, 0x78))(c, m40);
  }
  return true;
}

// @ 0x00801420
void __stdcall f_801420(int a, int b)
{
  f_804f10((float)a, (float)b);
}

// @ 0x00801450
void __stdcall f_801450(int* p1, int* p2)
{
  float x, y;
  f_804ed0(&y, &x);
  *p1 = (int)x;
  *p2 = (int)y;
}

// @ 0x008014c0
int C_8014c0::Init()
{
  if (m28)
    return 1;
  void* mem = f_9512d0(0x20c, 4, "UI/UI/Cursor info parent window", f_9512c0());
  void* win = 0;
  if (mem) {
    f_962a10(mem);
    *(void**)mem = (void*)0;
    *(void**)((char*)mem + 4) = (void*)0;
    win = mem;
  }
  void* old = m4c;
  if (win != old) {
    if (win)
      ((void (__thiscall*)(void*))VFN(win, 0))(win);
    m4c = win;
    if (old)
      ((void (__thiscall*)(void*))VFN(old, 4))(old);
  }
  ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 0x10, 1);
  ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 0);
  ((void (__thiscall*)(void*, int))VFN(m4c, 0xac))(m4c, 0);
  void* mainWin = f_80620(f_805070(0x5b598fa));
  ((void (__thiscall*)(void*, void*))VFN(mainWin, 0xd8))(mainWin, m4c);
  ((void (__thiscall*)(void*, float, float))VFN(m4c, 0x68))(m4c, 1.0f, 1.0f);
  m28 = 1;
  return 1;
}

// @ 0x008016e0
void C_8016e0::Move(float x, float y)
{
  if (!m4c)
    return;
  float px = g_15435bc + x;
  float py = g_15435c0 + y;
  void* mainWin = f_80620(f_805070(0x5b598fa));
  if (m48) {
    void* w = (void*)((void* (__thiscall*)(void*))VFN(m48, 0x18))(m48);
    if (w) {
      void* a = (void*)((void* (__thiscall*)(void*))VFN(w, 0x18))(w);
      void* b = (void*)((void* (__thiscall*)(void*))VFN(mainWin, 0x34))(mainWin);
      void* c = (void*)((void* (__thiscall*)(void*))VFN(a, 0x38))(a);
      float cw = *(float*)((char*)c + 8) + px;
      if (*(float*)((char*)b + 8) <= cw && cw != *(float*)((char*)b + 8))
        px = x - (*(float*)((char*)c + 8) + g_15435bc);
      float ch = *(float*)((char*)b + 0xc) - (*(float*)((char*)c + 0xc) + py);
      if (ch < 0.0f)
        py = ch + py;
    }
  }
  ((void (__thiscall*)(void*, float, float))VFN(m4c, 0x64))(m4c, px, py);
  ((void (__thiscall*)(void*, void*))VFN(mainWin, 0xe8))(mainWin, m4c);
}

// @ 0x008017f0
bool C_8017f0::Set(void* p)
{
  void* cur = m48;
  if (p != cur) {
    if (cur) {
      void* w = (void*)((void* (__thiscall*)(void*))VFN(cur, 0x18))(cur);
      if (w) {
        ((void (__thiscall*)(void*, int, int))VFN(w, 0x7c))(w, 1, 0);
        ((void (__thiscall*)(void*, void*))VFN(m4c, 0xdc))(m4c, w);
      }
      ((void (__thiscall*)(void*))VFN(cur, 0x10))(cur);
    }
    ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 0);
    if (m48) {
      void* old = m48;
      m48 = 0;
      ((void (__thiscall*)(void*))VFN(old, 4))(old);
    }
    if (p) {
      if (((uint8_t (__thiscall*)(void*))VFN(p, 0xc))(p)) {
        void* t = (void*)((void* (__thiscall*)(void*))VFN(p, 0x18))(p);
        if (t) {
          m48 = p;
          ((void (__thiscall*)(void*, void*))VFN(m4c, 0xd8))(m4c, t);
          ((void (__thiscall*)(void*, float, float))VFN(t, 0x64))(t, 0.0f, 0.0f);
          ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 1);
          ((void (__thiscall*)(void*, int, int))VFN(t, 0x7c))(t, 1, 1);
          float x, y;
          f_804ed0(&x, &y);
          ((void (__thiscall*)(void*, float, float))VFN(this, 0x38))(this, x, y);
          return true;
        }
        ((void (__thiscall*)(void*))VFN(p, 0x10))(p);
      }
      return false;
    }
  }
  return true;
}

// @ 0x00801950
bool C_801950::Run(int a)
{
  if (m50 && m54)
    return f_806a60(m50, m54, a, -1);
  return false;
}

// @ 0x00801980
void C_801980::Set(bool v)
{
  m44 = (uint8_t)v;
  if (m50) {
    if (v) {
      int a;
      ((void (__thiscall*)(void*, int*, int*))VFN(this, 0x34))(this, (int*)&v, &a);
      ((void (__thiscall*)(void*, float, float))VFN(m50, 0x64))(m50, (float)a, (float)*(int*)&v);
    } else {
      f_8027e0(this);
    }
    ((void (__thiscall*)(void*, int, int))VFN(m50, 0x7c))(m50, 1, m44);
  }
}

// @ 0x008019f0
void Sub_8019f0()
{
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

// @ 0x00801ac0
int C_801ac0::f(void* param_2, void* param_3, int param_4, int param_5)
{
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

// @ 0x00801b60
bool CurMgr::FindGlobal(uint32_t k)
{
  uint32_t key = k;
  void* it;
  ((MapBase*)((char*)this + 0xc))->Find(&it, &key);
  void* found = (it != (void*)((char*)this + 0x10)) ? (void*)((char*)it + 0x14) : 0;
  if (found != *(void**)((char*)this + 0x30)) {
    *(void**)((char*)this + 0x30) = found;
    this->Refresh();
  }
  return found != 0;
}

// @ 0x00801bb0
bool CurMgr::FindLocal(uint32_t k)
{
  uint32_t key = k;
  void* it;
  ((MapBase*)((char*)this + 0xc))->Find(&it, &key);
  void* found = (it != (void*)((char*)this + 0x10)) ? (void*)((char*)it + 0x14) : 0;
  if (found && found != *(void**)((char*)this + 0x2c)) {
    *(void**)((char*)this + 0x2c) = found;
    this->Refresh();
  }
  return found != 0;
}

// @ 0x00801c10
bool CurMgr::FindCanvas(uint32_t k)
{
  uint32_t key = k;
  void* it;
  ((MapBase*)((char*)this + 0xc))->Find(&it, &key);
  void* found = (it != (void*)((char*)this + 0x10)) ? (void*)((char*)it + 0x14) : 0;
  if (found && found != *(void**)((char*)this + 0x34)) {
    *(void**)((char*)this + 0x34) = found;
    this->Refresh();
  }
  return found != 0;
}

// @ 0x00801c70
bool CurMgr::FindCanvasAdj(uint32_t k)
{
  return ((CurMgr*)((char*)this - 8))->FindCanvas(k);
}

// @ 0x00801c80
void* RbtreeNode::DoCreateNode(void* arg)
{
  void* node = this;
  *(void**)node = 0;
  *(void**)((char*)node + 4) = 0;
  *(void**)((char*)node + 8) = 0;
  const wchar_t* src = *(const wchar_t**)arg;
  int n = (int)(*(const wchar_t**)((char*)arg + 4) - src);
  ((WStr*)node)->AllocateSelf(n + 1);
  void* dst = *(void**)node;
  DoInsertValue(dst, (const void*)src, n * 2);
  void* end = (char*)dst + n * 2;
  *(void**)((char*)node + 4) = end;
  *(uint16_t*)end = 0;
  *(void**)((char*)node + 0x10) = *(void**)((char*)arg + 0x10);
  *(void**)((char*)node + 0x14) = *(void**)((char*)arg + 0x14);
  *(void**)((char*)node + 0x18) = *(void**)((char*)arg + 0x18);
  *(void**)((char*)node + 0x1c) = *(void**)((char*)arg + 0x1c);
  return node;
}

// @ 0x00801d80
uint8_t C_801d80::f(IRecordSrc* src, void* info, int c, int type)
{
  uint8_t result = 0;
  if (type == 0x2393756) {
    uint32_t pathbuf[0x208 / 4];
    CreateTempFile((wchar_t*)pathbuf, 0, 0, 0);
    FileStream fs((const wchar_t*)pathbuf);
    if (fs.Open(2, 6, 1, 0)) {
      IRecordObj* rec = src->GetRecord();
      unsigned n = rec->GetSize();
      EmptyTag801d80 tag;
      VecBuf vec;
      vec.Init(n, &tag);
      int* data = vec.mpBegin;
      rec->Read(data, n);
      fs.Write(data, n);
      fs.Close();
      result = (uint8_t)SetCursor((const wchar_t*)pathbuf, info);
      FileRemove((const wchar_t*)pathbuf);
      if (data && data[-1])
        operator_delete(data);
    }
  }
  return result;
}

// @ 0x00801e90
void MapBase::Erase(void** outIter, void* node)
{
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

// @ 0x00801ef0
void MapBase::NukeSubtree(void* node)
{
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

// @ 0x00801fd0
void __fastcall Sub_801fd0(void* self)
{
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

// @ 0x00802050
uint32_t CursorTable::AddCursor(void* self, uint32_t id, const wchar_t* name, char load, int a, int b)
{
  void* it = 0;
  uint32_t key = id;
  ((MapBase*)((char*)self + 0xc))->Find(&it, &key);
  if (it != (char*)self + 0x10)
    return 0;
  (void)name; (void)load; (void)a; (void)b;
  return 1;
}

// @ 0x00802160
int CursorTable::AddStandardCursors()
{
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

// @ 0x008024e0
bool CurMgr::Remove(uint32_t k)
{
  uint32_t key = k;
  void* it;
  ((MapBase*)((char*)this + 0xc))->Find(&it, &key);
  bool r = false;
  if (it != (void*)((char*)this + 0x10)) {
    void* info = (char*)it + 0x14;
    if (info == *(void**)((char*)this + 0x30)) *(void**)((char*)this + 0x30) = 0;
    if (info == *(void**)((char*)this + 0x2c)) *(void**)((char*)this + 0x2c) = 0;
    if (info == *(void**)((char*)this + 0x38)) *(void**)((char*)this + 0x38) = 0;
    if (info == *(void**)((char*)this + 0x34)) *(void**)((char*)this + 0x34) = 0;
    r = this->DestroyEntry(it);
    void* out = 0;
    ((MapBase*)((char*)this + 0xc))->Erase(&out, it);
    if (*(uint8_t*)((char*)this + 0x40) && *(void**)((char*)this + 0x38) != 0)
      this->Refresh();
  }
  return r;
}

// @ 0x00802580
bool CurMgr::Clear()
{
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

// @ 0x008025e0
void* __fastcall Sub_8025e0(void* self)
{
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

// @ 0x00802680
bool CurMgr::Shutdown()
{
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

// @ 0x008026b0
bool __stdcall Sub_8026b0(const wchar_t* name, void* info)
{
  void* h = LoadImageW(0, name, 2, 0, 0, 0x10);
  bool r = h != 0;
  *(void**)((char*)info + 0x14) = h;
  return r;
}

// @ 0x00802850  ecx carries the cursor manager into 0x008026e0 (thiscall form)
struct CurMgrStub { bool chk_008026e0(void* info); };
bool CurMgr::CheckEntry(void* it)
{
  if (it == (void*)((char*)this + 0x10))
    return false;
  bool r = ((CurMgrStub*)(void*)this)->chk_008026e0((char*)it + 0x14);
  _ReadWriteBarrier();
  return r;
}
