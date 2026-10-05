// Slice s006b18c0: SP save-area subsystem and App::LRUCache manager methods.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b18c0.h"

// @ 0x6b1d40
void SetSaveAreaFlag(uint8_t b) {
  g_16046d8 = b;
}

// @ 0x6b1f60
bool SP_IsSaveArea(void* p) {
  uint32_t* it = g_saveAreas.root;
  while (it != &g_saveAreas.head) {
    if (it[5] == (uint32_t)p) {
      return true;
    }
    it = (uint32_t*)RBTreeIncrement(it);
  }
  return false;
}

// @ 0x6b1f90
void* SP_GetSaveArea(uint32_t key) {
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out != &g_saveAreas.head) {
    return (void*)out[5];
  }
  return 0;
}

// @ 0x6b1fc0
void SP_FlushAllSaveAreas() {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[6];
    if (o != 0) {
      o->Call24();
    }
  }
}

// @ 0x6b2350
void SP_SomethingAllSaveAreas() {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    o->Call24();
  }
}

// @ 0x6b1d50
void SP_SaveResource(void* p, uint32_t val, char flag) {
  if (*(uint32_t*)((uint32_t)p + 0xc) == 0xb1b104) {
    PropertyMgr4* pm = SP_PropertyManager();
    pm->Call34(p, *(void**)((uint32_t)p + 8), *(void**)((uint32_t)p + 0x10));
  } else {
    FUN_006acfe0((void*)((uint32_t)p + 8), p);
  }
  if (flag != 0) {
    FUN_006b4b60(p, (void*)val, 0, 0);
    return;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  rm->Call20(p, 0, (void*)val, 0, 0);
}

// @ 0x6b2000
bool FUN_006b2000(void* p, char flag) {
  uint32_t key = 0x11ac19c;
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out == &g_saveAreas.head) {
    return false;
  }
  SaveObj* o = (SaveObj*)out[5];
  if (o == 0) {
    return false;
  }
  FUN_006acfe0((void*)((uint32_t)p + 8), p);
  if (flag != 0) {
    return FUN_006b4b60(p, o, 0, 0) != 0;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  return rm->Call20(p, 0, o, 0, 0) != 0;
}

// @ 0x6b2090
bool FUN_006b2090(void* p, char flag) {
  uint32_t key = 0x11ac1ac;
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out == &g_saveAreas.head) {
    return false;
  }
  SaveObj* o = (SaveObj*)out[5];
  if (o == 0) {
    return false;
  }
  if (flag != 0) {
    return FUN_006b4b60(p, o, 0, 0) != 0;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  return rm->Call20(p, 0, o, 0, 0) != 0;
}

// @ 0x6b22a0
void* SP_UpdateSaveAreas(void* p) {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    if (o->Call34(p, 0, (void*)1, (void*)6, (void*)1, 0)) {
      return o;
    }
  }
  return 0;
}

// @ 0x6b22f0
void* FUN_006b22f0(void* p) {
  ResourceMgr4* rm = ResourceMan_GetManager();
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    if (rm->Call30(p, 0, o) != 0) {
      return o;
    }
  }
  return 0;
}

// @ 0x6b1dc0
RefPair* RefPair::Ctor(RefA* x, RefB* y) {
  a = x;
  if (x != 0) {
    x->ref.AddRef();
  }
  b = y;
  if (y != 0) {
    y->AddRef();
  }
  return this;
}

// @ 0x6b1e20
void RefPair::Dtor() {
  if (b != 0) {
    b->Release();
  }
  if (a != 0) {
    a->ref.Release();
  }
}

// @ 0x6b1e90
RefPair* RefPair::CtorCopy(const RefPair* o) {
  a = o->a;
  if (a != 0) {
    a->ref.AddRef();
  }
  b = o->b;
  if (b != 0) {
    b->AddRef();
  }
  return this;
}

// @ 0x6b1ef0
RefPair* RefPair::Assign(const RefPair* o) {
  if (o->a != a) {
    if (o->a != 0) {
      o->a->ref.AddRef();
    }
    RefA* old = a;
    a = o->a;
    if (old != 0) {
      old->ref.Release();
    }
  }
  if (o->b != b) {
    if (o->b != 0) {
      o->b->AddRef();
    }
    RefB* old = b;
    b = o->b;
    if (old != 0) {
      old->Release();
    }
  }
  return this;
}

// @ 0x6b18c0  (partial)
void CacheMgr::Notify(void* ev) { (void)ev; }

// @ 0x6b19e0  (partial)
void CacheMgr::ReleaseArea(void* node) { (void)node; }

// @ 0x6b1ab0  (partial)
void CacheMgr::Destructor() {}

// @ 0x6b1b80  (partial)
void CacheMgr::Update() {}

// @ 0x6b2110  (partial)
void ReadExtensionMappingsFromPropFile() {}

// @ 0x6b2400  (partial)
void FUN_006b2400() {}

// @ 0x6b2620  (partial)
void FUN_006b2620() {}
