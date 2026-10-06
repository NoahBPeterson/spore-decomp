// Slice s00aea5d0 (bfs2 #45).
//
// A "space tool" holding an eastl::vector of refcounted 0xa0-byte entries
// (EA::AutoRefCount<Entry>) at +0x24, a selected reference at +0x20, a
// hashtable at +0x40 and a bool at +0x60. The slice also contains a second
// vector instantiation with 0xc-byte elements, a hash-bucket free helper and a
// field serializer.
//
// Reconstructed from the calls: SP::EventLog / cSPUIEventLog::RemoveEvent,
// cStarMap::RemoveVisual, SP::NounManager, cTerrainEditor::GetCurrentTerrainSphere.
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

extern "C" void* op_new(u32 size, const char* name, int a, int b, const char* file, int line);
extern "C" void op_del(void* p);

// ---- generic virtual dispatch helpers (masked targets) --------------------
typedef void* (__thiscall *tc0_t)(void*);
typedef void* (__thiscall *tc1_t)(void*, int);
typedef void* (__thiscall *tc3_t)(void*, int, int, int);
typedef void* (__thiscall *tc4_t)(void*, int, int, int, int);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline void* vt3(void* p, int slot, int a, int b, int c) { return ((tc3_t*)(*(void***)p))[slot](p, a, b, c); }
static inline void* vt4(void* p, int slot, int a, int b, int c, int d) { return ((tc4_t*)(*(void***)p))[slot](p, a, b, c, d); }

static inline void addref(void* p) { if (p) vt0(p, 0); }
static inline void relref(void* p) { if (p) vt0(p, 1); }

// ---- external helpers (masked callees) ------------------------------------
extern "C" void  eastl_move_backward(void* position, void* last, void* dest);   // 0xac97a0
extern "C" void* eastl_uninit_copy(void* dest, const void* first, u32 nbytes);  // 0x11e0744
extern "C" void  eastl_copy_impl(void* first, void* last, void* dest);          // 0x6782c0
extern "C" void* vec12_ucopy(const void* first, const void* last, void* dest);  // 0xae97e0
extern "C" void  vec12_destroy(const void* first, const void* last, void* dest); // 0xae9830
extern "C" void* vec12_move(void* first, void* last, void* dest);               // 0xae9870
extern "C" void  vec12_move2(void* first, void* last, void* dest);              // 0xae98d0

// ---- named game objects ---------------------------------------------------
struct CEventLog { void RemoveEvent(int id, int a); };          // 0xdd6d10 thiscall
struct CStarMap  { void RemoveVisual(int id, int a); };         // 0x1045a60 thiscall
struct CTerrainEditor { void* GetCurrentTerrainSphere(); };     // 0xf67d90 thiscall
struct CUILayout { void classify(); };                          // 0xdd3d30 thiscall
struct CWriter { virtual void Field(const wchar_t*); virtual void EndField(const wchar_t*); };

CEventLog* SP_EventLog(int id, int a);              // 0xb3d3e0
CStarMap*  GetStarMapFromId(int id, int b);         // 0x1046fc0
void*      SP_NounManager();                        // 0xb3d300
void       terrain_sphere_update(void* p);          // 0xc77bf0
void*      SP_MessageServer();                      // 0x67dcc0
void*      FUN_00aed4d0();                          // 0xaed4d0
void       FUN_00aed3d0();                          // 0xaed3d0
void*      SP_SpaceGameGet();                       // 0x1002bd0
void       FUN_010762d0(void* p);                   // 0x10762d0
CUILayout* ctor_UILayout();                         // 0xdd1ca0
int        FUN_00ac8050(CWriter* w, int a, const void* e);  // 0xac8050
void*      ctor_Entry();                            // 0xaea250

// ===========================================================================
// 4-byte element vector (EA::AutoRefCount<Entry>)
// ===========================================================================
struct PtrVec {
  void** mpBegin;      // +0x00
  void** mpEnd;        // +0x04
  void** mpCapacity;   // +0x08
  void DoInsertValue(void** position, void* const& value);
  void erase(void** first, void** last);   // 0xe25bd0
};

// @ 0x00aea5d0
void PtrVec::DoInsertValue(void** position, void* const& value) {
  void** pEnd = mpEnd;
  if (pEnd != mpCapacity) {
    void** pValue = (void**)&value;
    if (pValue >= position && pValue < pEnd)
      ++pValue;
    if (pEnd) {
      void* prev = pEnd[-1];
      *pEnd = prev;
      addref(prev);
    }
    eastl_move_backward(position, mpEnd - 1, mpEnd);
    void* v = *pValue;
    void* old = *position;
    if (v != old) {
      addref(v);
      *position = v;
      relref(old);
    }
    mpEnd = pEnd + 1;
    return;
  }
  int nSize = (int)(pEnd - mpBegin);
  int nNew;
  void** oldBegin = mpBegin;
  void** oldEnd = pEnd;
  void** pNewData;
  if (nSize == 0)
    nNew = 1;
  else {
    nNew = nSize * 2;
    if (nNew == 0) {
      pNewData = 0;
      goto have;
    }
  }
  pNewData = (void**)op_new(nNew * 4, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
have:;
  {
    u32 nPre = (u32)((char*)position - (char*)oldBegin);
    void** pos = (void**)((char*)eastl_uninit_copy(pNewData, oldBegin, nPre) + nPre);
    if (pos) {
      void* v = *position;
      *pos = v;
      addref(v);
    }
    u32 nPost = (u32)((char*)oldEnd - (char*)position);
    void** newEnd = (void**)((char*)eastl_uninit_copy(pos + 1, position, nPost) + nPost);
    if (oldBegin && *((int*)oldBegin - 1) != 0)
      op_del(oldBegin);
    mpBegin = pNewData;
    mpEnd = newEnd;
    mpCapacity = pNewData + nNew;
  }
}

// ===========================================================================
// 0xc-byte element vector
// ===========================================================================
struct E12 { u32 a; u32 b; void* p; };
struct Vec12 {
  E12* mpBegin;
  E12* mpEnd;
  E12* mpCapacity;
  void DoInsertValue(E12* position, const E12& value);
  E12* erase(E12* first, E12* last);
};

// @ 0x00aeae90
void Vec12::DoInsertValue(E12* position, const E12& value) {
  E12* pEnd = mpEnd;
  if (pEnd != mpCapacity) {
    const E12* pValue = &value;
    if (pValue >= position && pValue < pEnd)
      ++pValue;
    if (pEnd) {
      pEnd->a = pEnd[-1].a;
      pEnd->b = pEnd[-1].b;
      pEnd->p = pEnd[-1].p;
      addref(pEnd->p);
    }
    vec12_move2(position, mpEnd - 1, mpEnd);
    E12* v = (E12*)pValue;
    u32 a = v->a, b = v->b;
    void* pnew = v->p;
    position->a = a;
    position->b = b;
    void* old = position->p;
    if (pnew != old) {
      addref(pnew);
      position->p = pnew;
      relref(old);
    }
    mpEnd = pEnd + 1;
    return;
  }
  int nSize = (int)((char*)pEnd - (char*)mpBegin) / 0xc;
  int nNew;
  E12* oldBegin = mpBegin;
  E12* oldEnd = pEnd;
  E12* pNewData;
  if (nSize == 0)
    nNew = 1;
  else {
    nNew = nSize * 2;
    if (nNew == 0) { pNewData = 0; goto have; }
  }
  pNewData = (E12*)op_new(nNew * 0xc, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
have:;
  {
    E12* pos = (E12*)vec12_ucopy(oldBegin, position, pNewData);
    vec12_destroy(oldBegin, position, pNewData);
    if (pos) {
      void* p = position->p;
      pos->a = position->a;
      pos->b = position->b;
      pos->p = p;
      addref(p);
    }
    E12* end = (E12*)vec12_ucopy(position, oldEnd, pos + 1);
    vec12_destroy(position, oldEnd, pos + 1);
    if (oldBegin && *((int*)oldBegin - 1) != 0)
      op_del(oldBegin);
    mpBegin = pNewData;
    mpEnd = end;
    mpCapacity = (E12*)((char*)pNewData + nNew * 0xc);
  }
}

// @ 0x00aeae10
E12* Vec12::erase(E12* first, E12* last) {
  char* p = (char*)vec12_move(last, mpEnd, first);
  if (p < (char*)mpEnd) {
    int count = (int)(((char*)mpEnd - p) - 1) / 0xc + 1;
    char* q = p;
    for (int i = 0; i < count; ++i) {
      relref(*(void**)(q + 8));
      q += 0xc;
    }
  }
  int n = (int)((char*)last - (char*)first) / 0xc;
  mpEnd = (E12*)((char*)mpEnd + n * 0xc);
  return first;
}

// @ 0x00aeb030  hash bucket destructor
struct HashNode {
  char pad0[4];
  void* mp4;           // +0x04  owned buffer
  char pad8[0x10];
  HashNode* mp18;      // +0x18  next
};

void destroy_hash_buckets(HashNode** table, u32 count) {
  for (u32 i = 0; i < count; ++i) {
    HashNode* n = table[i];
    while (n) {
      void* p4 = n->mp4;
      HashNode* next = n->mp18;
      if (p4 && *((int*)p4 - 1) != 0)
        op_del(p4);
      op_del(n);
      n = next;
    }
    table[i] = 0;
  }
}

// ===========================================================================
// Entry (0xa0 bytes)
// ===========================================================================
#define E(e, off) (*(void**)((char*)(e) + (off)))
#define EI(e, off) (*(int*)((char*)(e) + (off)))

// ===========================================================================
// The space tool.
// ===========================================================================
struct SpaceTool {
  char pad00[0x20];
  void* mp20;            // +0x20
  PtrVec mVec;           // +0x24
  char pad30[0x10];      // +0x30
  char mHash[0x20];      // +0x40
  u8 mb60;               // +0x60

  bool CheckEntry(void* e);      // 0xaea3d0
  void OnShutdown0();            // 0xae9f50

  void RemoveMatching(int a, int b, int c);      // 0xaea720
  void RemoveByPtr(void* p);                     // 0xaea7f0
  void ReleaseSelected(void* p);                 // 0xaea850
  void Advance(int delta);                       // 0xaea8e0
  void RemoveByPtrAndUpdate(void* p);            // 0xaea9e0
  void RemoveMatching2(int a, int b, int c, int d);  // 0xaeaa80
  void RemoveByKey(int key);                     // 0xaeab40
  void Cleanup();                                // 0xaeb090
  void* AddEntry(int a1, int a2, int a3, int a4, void* a5, int a6, int a7);   // 0xaeb160
  void* CreateEntry(void* obj, void* a2, int a3, int a4, int a5, int a6);     // 0xaeb240
};

// @ 0x00aea720
void SpaceTool::RemoveMatching(int p2, int p3, int p4) {
  void** it = mVec.mpBegin;
  if (it == mVec.mpEnd)
    return;
  void** next = it + 1;
  do {
    void* e = *it;
    if (e != 0 && EI(e, 0xc) == 0 &&
        (p2 == -1 || EI(e, 0x18) == p2) &&
        (p3 == -1 || EI(e, 0x34) == p3) &&
        (p4 == 0 || (int)E(e, 0x40) == p4) &&
        mp20 != e) {
      if (*(u8*)((char*)e + 0x30) != 0) {
        int ev = EI(e, 0x14);
        SP_EventLog(ev, 0)->RemoveEvent(EI(e, 0x14), 0);
        GetStarMapFromId(EI(e, 0x10), 1)->RemoveVisual(EI(e, 0x10), 1);
      }
      if (next < mVec.mpEnd)
        eastl_copy_impl(next, mVec.mpEnd, it);
      mVec.mpEnd--;
      relref(*mVec.mpEnd);
    } else {
      it++;
      next++;
    }
  } while (it != mVec.mpEnd);
}

// @ 0x00aea7f0
void SpaceTool::RemoveByPtr(void* p) {
  void** it = mVec.mpBegin;
  if (it == mVec.mpEnd)
    return;
  void** next = it + 1;
  do {
    if (*it == p && mp20 != p) {
      if (next < mVec.mpEnd)
        eastl_copy_impl(next, mVec.mpEnd, it);
      mVec.mpEnd--;
      relref(*mVec.mpEnd);
    } else {
      it++;
      next++;
    }
  } while (it != mVec.mpEnd);
}

// @ 0x00aea850
void SpaceTool::ReleaseSelected(void* p) {
  if (!p)
    return;
  if (mp20 == p && mp20) {
    void* old = mp20;
    mp20 = 0;
    relref(old);
  }
  void** it = mVec.mpBegin;
  void** end = mVec.mpEnd;
  while (it != end && *it != p)
    it++;
  if (it + 1 < end)
    eastl_copy_impl(it + 1, end, it);
  mVec.mpEnd--;
  relref(*mVec.mpEnd);
}

// @ 0x00aea8e0
void SpaceTool::Advance(int param) {
  void** it = mVec.mpBegin;
  if (it == mVec.mpEnd) {
    mb60 = 0;
    return;
  }
  void** next = it + 1;
  do {
    void* e = *it;
    bool removed = false;
    if (EI(e, 0x48) != 0 && (EI(e, 0x4c) += param, (u32)EI(e, 0x4c) > (u32)EI(e, 0x48))) {
      if (next < mVec.mpEnd)
        eastl_copy_impl(next, mVec.mpEnd, it);
      mVec.mpEnd--;
      relref(*mVec.mpEnd);
      removed = true;
    }
    if (*(u8*)((char*)e + 0x30) == 0 || !CheckEntry(e)) {
      if (!removed) {
        it++;
        next++;
      }
    } else {
      int ev = EI(e, 0x14);
      SP_EventLog(ev, 0)->RemoveEvent(EI(e, 0x14), 0);
      GetStarMapFromId(EI(e, 0x10), 1)->RemoveVisual(EI(e, 0x10), 1);
      void* ts = ((CTerrainEditor*)SP_NounManager())->GetCurrentTerrainSphere();
      terrain_sphere_update(ts);
      if (next < mVec.mpEnd)
        eastl_copy_impl(next, mVec.mpEnd, it);
      mVec.mpEnd--;
      relref(*mVec.mpEnd);
    }
  } while (it != mVec.mpEnd);
  mb60 = 0;
}

// @ 0x00aea9e0
void SpaceTool::RemoveByPtrAndUpdate(void* p) {
  if (!p)
    return;
  void** it = mVec.mpBegin;
  void** end = mVec.mpEnd;
  while (it != end && *it != p)
    it++;
  if (it == end)
    return;
  void* e = *it;
  int ev = EI(e, 0x14);
  SP_EventLog(ev, 0)->RemoveEvent(EI(e, 0x14), 0);
  GetStarMapFromId(EI(e, 0x10), 1)->RemoveVisual(EI(e, 0x10), 1);
  if (it + 1 < mVec.mpEnd)
    eastl_copy_impl(it + 1, mVec.mpEnd, it);
  mVec.mpEnd--;
  relref(*mVec.mpEnd);
  void* ts = ((CTerrainEditor*)SP_NounManager())->GetCurrentTerrainSphere();
  terrain_sphere_update(ts);
}

// @ 0x00aeaa80
void SpaceTool::RemoveMatching2(int p2, int p3, int p4, int p5) {
  void** it = mVec.mpBegin;
  void** end = mVec.mpEnd;
  if (it == end)
    return;
  for (;;) {
    void* e = *it;
    if (*(u8*)((char*)e + 0x30) != 0 && EI(e, 0x18) == p2 && EI(e, 0x34) == p3 &&
        EI(e, 0x38) == p4 && EI(e, 0x3c) == p5)
      break;
    it++;
    if (it == end)
      return;
  }
  {
    void* e = *it;
    int ev = EI(e, 0x14);
    SP_EventLog(ev, 0)->RemoveEvent(EI(e, 0x14), 0);
    GetStarMapFromId(EI(e, 0x10), 1)->RemoveVisual(EI(e, 0x10), 1);
    if (it + 1 < mVec.mpEnd)
      eastl_copy_impl(it + 1, mVec.mpEnd, it);
    mVec.mpEnd--;
    relref(*mVec.mpEnd);
    void* ts = ((CTerrainEditor*)SP_NounManager())->GetCurrentTerrainSphere();
    terrain_sphere_update(ts);
  }
}

// @ 0x00aeab40
void SpaceTool::RemoveByKey(int key) {
  void** it = mVec.mpBegin;
  if (it == mVec.mpEnd)
    return;
  void** next = it + 1;
  do {
    void* e = *it;
    if (*(u8*)((char*)e + 0x30) != 0 && EI(e, 0x34) == key) {
      int ev = EI(e, 0x14);
      SP_EventLog(ev, 0)->RemoveEvent(EI(e, 0x14), 0);
      GetStarMapFromId(EI(e, 0x10), 1)->RemoveVisual(EI(e, 0x10), 1);
      if (next < mVec.mpEnd)
        eastl_copy_impl(next, mVec.mpEnd, it);
      mVec.mpEnd--;
      relref(*mVec.mpEnd);
      void* ts = ((CTerrainEditor*)SP_NounManager())->GetCurrentTerrainSphere();
      terrain_sphere_update(ts);
    } else {
      it++;
      next++;
    }
  } while (it != mVec.mpEnd);
}

// @ 0x00aeacc0  field serializer
struct WString {
  const wchar_t* mpBegin;
  const wchar_t* mpEnd;
  u32 mCap;
  bool empty() const { return mpBegin == mpEnd; }
};
WString ConvertToString16W(const char* s);
void WStringRangeInit(WString* out);

u8 SerializeList(CWriter* writer, const char* name, Vec12* list) {
  u8 ok = 1;
  if (list->mpBegin == list->mpEnd)
    return ok;
  WString str;
  if (name == 0)
    WStringRangeInit(&str);
  else
    str = ConvertToString16W(name);
  const wchar_t* field = str.empty() ? L"list" : str.mpBegin;
  ((tc1_t*)(*(void***)writer))[0](writer, (int)field);
  for (E12* p = list->mpBegin; p != list->mpEnd; p = (E12*)((char*)p + 0xc)) {
    if (!ok)
      break;
    if (!FUN_00ac8050(writer, 0, p))
      ok = 0;
  }
  ((tc1_t*)(*(void***)writer))[1](writer, (int)field);
  return ok;
}

// @ 0x00aeb090
void SpaceTool::Cleanup() {
  if (mp20 != 0) {
    OnShutdown0();
    vt4(SP_MessageServer(), 6, 0x490d429, 0, 0, 0);
  }
  vt0(FUN_00aed4d0(), 1);
  FUN_00aed3d0();
  {
    char* g = (char*)SP_SpaceGameGet();
    if (g && *(void**)(g + 0x18)) {
      g = (char*)SP_SpaceGameGet();
      FUN_010762d0(g + 0x18);
      g = (char*)SP_SpaceGameGet();
      void* t = *(void**)(g + 0x18);
      if (t) {
        *(void**)(g + 0x18) = 0;
        relref(t);
      }
    }
  }
  ctor_UILayout()->classify();
  mVec.erase(mVec.mpBegin, mVec.mpEnd);
  if (mp20) {
    void* old = mp20;
    mp20 = 0;
    relref(old);
  }
  vt3(SP_MessageServer(), 5, 0x69c3314, 0, 0);
}

// @ 0x00aeb160
void* SpaceTool::AddEntry(int a1, int a2, int a3, int a4, void* a5, int a6, int a7) {
  void* e = op_new(0xa0, "Simulator", 0, 0, 0, 0);
  e = e ? ctor_Entry() : 0;
  EI(e, 0x18) = a1;
  EI(e, 0xc) = 0;
  EI(e, 0x34) = a2;
  EI(e, 0x38) = a3;
  EI(e, 0x3c) = a4;
  {
    void* old = E(e, 0x40);
    if (a5 != old) {
      addref(a5);
      E(e, 0x40) = a5;
      relref(old);
    }
  }
  EI(e, 0x44) = a6;
  EI(e, 0x48) = a7;
  addref(e);
  void** end = mVec.mpEnd;
  if (end < mVec.mpCapacity) {
    mVec.mpEnd = end + 1;
    if (end) {
      *end = e;
      addref(e);
    }
  } else {
    void* tmp = e;
    mVec.DoInsertValue(end, tmp);
  }
  relref(e);
  return e;
}

// @ 0x00aeb240
void* SpaceTool::CreateEntry(void* obj, void* a2, int a3, int a4, int a5, int a6) {
  void* e = op_new(0xa0, "Simulator", 0, 0, 0, 0);
  e = e ? ctor_Entry() : 0;
  EI(e, 0xc) = 1;
  {
    void* ts = ((CTerrainEditor*)SP_NounManager())->GetCurrentTerrainSphere();
    terrain_sphere_update(ts);
  }
  void* r1 = 0;
  void* r2 = 0;
  if (obj != 0) {
    r2 = vt1(obj, 3, (int)0x901f1362);
    r1 = vt1(obj, 3, (int)0xee9b2232);
    if (r2 != 0) {
      void* old = E(e, 0x28);
      if (r2 != old) {
        addref(r2);
        E(e, 0x28) = r2;
        relref(old);
      }
    } else if (r1 != 0) {
      void* old = E(e, 0x20);
      if (r1 != old) {
        addref(r1);
        E(e, 0x20) = r1;
        relref(old);
      }
    }
  }
  {
    void* old = E(e, 0x24);
    if (a2 != old) {
      addref(a2);
      E(e, 0x24) = a2;
      relref(old);
    }
  }
  EI(e, 0x34) = a3;
  EI(e, 0x38) = a4;
  EI(e, 0x44) = a6;
  EI(e, 0x3c) = a5;
  addref(e);
  void** end = mVec.mpEnd;
  if (end < mVec.mpCapacity) {
    mVec.mpEnd = end + 1;
    if (end) {
      *end = e;
      addref(e);
    }
  } else {
    void* tmp = e;
    mVec.DoInsertValue(end, tmp);
  }
  relref(e);
  if (r1 != 0) {
    void* civ = vt0(r1, 19);          // cCity::GetCivilization()
    void* playerCiv = vt0(SP_NounManager(), 0);  // cGameNounManager::GetPlayerCivilization()
    if (civ != playerCiv) {
      void* planet = vt0(civ, 19);    // placeholder: GetActivePlanet + update
      (void)planet;
    }
  }
  return e;
}
