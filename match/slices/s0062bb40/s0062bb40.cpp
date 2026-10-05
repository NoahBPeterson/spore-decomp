// SP::cSPPlayMode methods. Region 0x62bb40-0x62ca73.
// Retail layout differs from the 2008 PDB; offsets taken from the disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef void  (__thiscall *TF0)(void*);
typedef void  (__thiscall *TF1)(void*, int);
typedef void  (__thiscall *TF4)(void*, int, int, int, int);
typedef void  (__thiscall *TF5)(void*, int, int, int, int, int);

struct Vec  { void erase(void* first, void* last); };
struct VecB { void DoInsertValue(void* dst, void* src, int n); };
struct SharedLibList { unsigned char FUN_0062f6c0(); };
struct EventInfo { void ctor(unsigned char b); };
struct Dance { bool IsDancingAnim(int a, int b); };
struct Creature { void FUN_00a04a90(int a); };
struct CreatureMgr {
  void* GetCreature(int idx);
  void* GetCreatureStructure(int idx);
  int   RunSkinPaintOnEditorModel(int a, int b);
  void  DestroyAnimatedCreature(int a, int b);
};
struct PMUI { void SetUIGroupVisible(unsigned int key, int b); };

struct PM {
  void FUN_0062bb40(int a, int b);   // @ 0x0062bb40
  void FUN_0062bec0();               // @ 0x0062bec0
  void FUN_0062bdb0();               // @ 0x0062bdb0
  void FUN_0062bf10(int a);          // @ 0x0062bf10
  void Stop();                       // @ 0x0062c340
  void Update(int a);                // @ 0x0062c550
  bool FUN_0062c7e0(int idx, int a); // @ 0x0062c7e0
  void FUN_0062c910();               // @ 0x0062c910
  void FUN_0062c990(int id);         // @ 0x0062c990
  int  GetLatestBabyID();
  void SetMomToFaceBaby(int id);
  void SetBabyIdleAnim(int id);
  bool IsEventForBaby(int id);
};

extern void* gPMGlobal;              // 0x15f7cf4
extern float gConst13fe160;          // 0x13fe160

// @ 0x0062bb40
__declspec(noinline) void PM::FUN_0062bb40(int, int) {}

// @ 0x0062bec0
void PM::FUN_0062bec0() {
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x80) - *(unsigned*)(s + 0x7c)) >> 2;
  Vec* vec = (Vec*)(s + 0x7c);
  unsigned i = 0;
  while (i < n) {
    int* arr = *(int**)vec;
    int o = arr[i];
    if (o != 0) {
      arr[i] = 0;
      ((TF0)(*(void**)(*(char**)o + 8)))((void*)o);
    }
    ++i;
  }
  vec->erase(*(void**)vec, *(void**)((char*)vec + 4));
}

// @ 0x0062bdb0
void PM::FUN_0062bdb0() {
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x68) - *(unsigned*)(s + 0x64)) >> 2;
  if (n == 0) return;
  int ids[8];
  for (int k = 0; k < 8; ++k) ids[k] = -1;
  unsigned cnt = 0;
  void* mgr = *(void**)((char*)*(void**)(s + 0x3614) + 0x360);
  for (unsigned i = 0; i < n; ++i) {
    int id = *(int*)(*(unsigned*)(s + 0x64) + i * 4);
    char* cr = (char*)((CreatureMgr*)mgr)->GetCreature(id);
    if (cr != 0 && (*(unsigned char*)(*(char**)(cr + 0x180) + 6) & 1)) {
      FUN_0062bb40(id, id != *(int*)((char*)*(void**)(s + 0x3614) + 0x364));
      ids[cnt++] = id;
    }
  }
  for (unsigned j = 0; j < cnt; ++j) {
    int* d = *(int**)(s + 0x64);
    int* e = *(int**)(s + 0x68);
    while (d != e) {
      if (ids[j] == *d) {
        if (d + 1 < e) {
          ((VecB*)(s + 0x64))->DoInsertValue(d, d + 1, (int)e - (int)(d + 1));
        }
        *(unsigned*)(s + 0x68) -= 4;
        break;
      }
      ++d;
    }
  }
}

// @ 0x0062bf10
__declspec(noinline) void PM::FUN_0062bf10(int) {}

// @ 0x0062c340
__declspec(noinline) void PM::Stop() {}

// @ 0x0062c550
__declspec(noinline) void PM::Update(int) {}

// @ 0x0062c7e0
bool PM::FUN_0062c7e0(int idx, int a) {
  char* s = (char*)this;
  if (*(unsigned char*)(s + 0x36d0) >= 3) return false;
  void* mgr = *(void**)(s + 0x3614);
  if (!((CreatureMgr*)mgr)->RunSkinPaintOnEditorModel(1, a)) return false;
  ++*(unsigned char*)(s + 0x36d0);
  int id = GetLatestBabyID();
  if (id == -1) return true;
  char* cstr = (char*)((CreatureMgr*)*(void**)((char*)mgr + 0x360))->GetCreatureStructure(id);
  *(float*)(cstr + 0x74) = gConst13fe160;
  *(float*)(cstr + 0x78) = 0.0f;
  unsigned char b = ((SharedLibList*)(s + 0x3618))->FUN_0062f6c0();
  ((EventInfo*)cstr)->ctor(b);
  ((Creature*)((CreatureMgr*)*(void**)((char*)mgr + 0x360))->GetCreature(id))->FUN_00a04a90(1);
  SetMomToFaceBaby(id);
  *(unsigned char*)(s + 0x1f) = 1;
  *(int*)(s + idx * 4 + 0x36d8) = id;
  FUN_0062bb40(id, 1);
  char* puVar2 = (char*)*(void**)((char*)mgr + 0x360);
  void* cr2 = ((CreatureMgr*)puVar2)->GetCreature(*(int*)(puVar2 + 0x364));
  int local = 0;
  ((TF4)(*(void**)(*(char**)cr2 + 0x58)))(cr2, (int)&local, 0, 0, 0);
  if (((Dance*)(s + 0x11b0))->IsDancingAnim(local, 0)) SetBabyIdleAnim(id);
  return true;
}

// @ 0x0062c910
void PM::FUN_0062c910() {
  char* s = (char*)this;
  void* p = *(void**)(s + 0x94);
  if (p != 0) {
    *(void**)(s + 0x94) = 0;
    ((TF0)(*(void**)(*(char**)p + 4)))(p);
  }
  if (*(void**)(s + 0xc8) != 0) Stop();
  void* q = *(void**)(s + 0xcc);
  ((TF0)(*(void**)(*(char**)q + 8)))(q);
  {
    char* vt = *(char**)(s + 0x3588);
    ((TF0)(*(void**)(vt + 8)))(s + 0x3588);
  }
  *(void**)(s + 0xcc) = 0;
  void* g = *(void**)&gPMGlobal;
  if (g != 0) {
    *(void**)&gPMGlobal = 0;
    ((TF0)(*(void**)(*(char**)g + 8)))(g);
  }
  void* h = *(void**)(s + 0xc);
  if (h != 0) {
    *(void**)(s + 0xc) = 0;
    ((TF0)(*(void**)(*(char**)h + 4)))(h);
  }
}

// @ 0x0062c990
void PM::FUN_0062c990(int id) {
  char* s = (char*)this;
  if (id >= 0) {
    if (*(void**)(s + id * 4 + 0x36d8) == 0) {
      FUN_0062c7e0(id, 0);
      return;
    }
    IsEventForBaby(id);
    return;
  }
  void* mgr = *(void**)(s + 0x3614);
  if (*(unsigned char*)(s + 0x36d0) == 0) {
    ((CreatureMgr*)mgr)->RunSkinPaintOnEditorModel(1, 0);
    ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x4066678u, 1);
    ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x40666b8u, 1);
    *(unsigned char*)(s + 0x36d0) = 1;
    int bid = GetLatestBabyID();
    if (bid == -1) return;
    SetMomToFaceBaby(bid);
    *(unsigned char*)(s + 0x1f) = 1;
    return;
  }
  ((CreatureMgr*)mgr)->DestroyAnimatedCreature(1, 0);
  ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x4066678u, 0);
  ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x40666b8u, 0);
  void* edx = *(void**)(s + 0x3614);
  int off = *(int*)((char*)edx + 0x364);
  char* vt = *(char**)(s + 0x3588);
  *(unsigned char*)(s + 0x36d0) = 0;
  ((TF5)(*(void**)(vt + 0xc)))(s + 0x3588, off, 0x4373694, 0, 1, 0);
}
