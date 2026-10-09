// Slice s006b09b0: App::LRUCache subsystem (manager + per-key cache list).
// Compiled with /O2 /MD /Gy /EHsc /TP.
#include "s006b09b0.h"

static const char* kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x6b09b0  (partial: lock-free refcount/map update; see partial.txt)
extern void CacheSub60_Update(void*);
__declspec(noinline) void CacheSub60::Update(Key20* p) {
  CacheSub60_Update(p);
}

// @ 0x6b0ce0
void Cache::A(Key12* e, int v) {
  Key20 t;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.mode = 1;
  t.value = v;
  sub.Update(&t);
}

// @ 0x6b0d20
void Cache::B(Key12* e) {
  Key20 t;
  t.mode = 0;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.value = 0;
  sub.Update(&t);
}

// @ 0x6b0d60
void Cache::C(Key12* e) {
  Key20 t;
  t.mode = 2;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.value = 0;
  sub.Update(&t);
}

// @ 0x6b0b80
uint64_t CacheList::Remove(const Key12& k) {
  Entry* end = vec.end;
  Entry* it = vec.begin;
  if (it != end) {
    do {
      if (it->a == k.a && it->b == k.b && it->c == k.c) {
        uint32_t score = it->score;
        uint64_t rv = (uint64_t)(-(int64_t)score);
        Entry* p = it + 1;
        Entry* last = vec.end;
        if (p < last) {
          do { *it = *p; ++it; ++p; } while (p != last);
        }
        vec.end = (Entry*)((uint32_t)vec.end - 0x10);
        return rv;
      }
      ++it;
    } while (it != end);
  }
  return 0;
}

// @ 0x6b0f40
void CacheList::AddOrUpdate(const Key12& k, uint32_t score) {
  for (Entry* it = vec.begin; it != vec.end; ++it) {
    if (it->a == k.a && it->b == k.b && it->c == k.c) {
      uint32_t old = it->score;
      it->score = score;
      total += (int64_t)score - (int64_t)old;
      return;
    }
  }
  Entry tmp;
  tmp.a = k.a;
  tmp.b = k.b;
  tmp.c = k.c;
  tmp.score = score;
  if (vec.end < vec.cap) {
    *vec.end = tmp;
    ++vec.end;
  } else {
    vec.DoInsertValue(vec.end, tmp);
  }
  total += (int64_t)score;
}

// @ 0x6b0c00
Cache::Cache(int a, int b) {
  refcnt = 0;
  m0c = a;
  if (a != 0) {
    RefObj* r = (RefObj*)(a + 4);
    r->v0();
  }
  m10 = b;
  ((uint8_t*)this)[0x14] = 0;
  ((uint8_t*)this)[0x15] = 0;
  m1c = (uint32_t)&m1c;
  m20 = (uint32_t)&m1c;
  m24 = 0;
  m28 = 0;
  m2c = 0;
  nodeNext = (uint32_t)&nodeNext;
  nodePrev = (uint32_t)&nodeNext;
  m3c = 0;
  m40 = 0;
  m48 = 0;
  m4c = 0;
  capacity = 9000;
  stream = 0;
  job = 0;
  sub.Init();
}

// @ 0x6b0da0
void** Cache::Insert(void** out, uint32_t key, uint64_t val) {
  uint32_t payload = helper08a0(key, (uint32_t)val);
  uint32_t* node = (uint32_t*)EAlloc(0xc, "App", 0, 0, kAllocFile, 0xd1);
  if (node + 2 != 0) {
    node[2] = payload;
  }
  node[0] = (uint32_t)&nodeNext;
  node[1] = nodePrev;
  *(uint32_t*)nodePrev = (uint32_t)node;
  nodePrev = (uint32_t)node;
  *out = node;
  Key12 k;
  k.a = key;
  k.b = 0;
  k.c = (uint32_t)val;
  ((Map*)&m18)->Insert(&k, node, 0);
  ((uint8_t*)this)[0x15] = 1;
  return out;
}

// @ 0x6b0e40
void Cache::Clear() {
  ((Map*)&m18)->DoNukeSubtree(m24);
  m1c = (uint32_t)&m1c;
  m20 = (uint32_t)&m1c;
  m24 = 0;
  m28 = 0;
  m2c = 0;
  uint32_t base = (uint32_t)&nodeNext;
  m3c = base + 4;
  m40 = 0;
  m48 = 0;
  nodePrev = base + 4;
  while (nodeNext != base) {
    uint32_t node = nodeNext;
    uint32_t payload = *(uint32_t*)(node + 8);
    if (payload != 0) {
      uint32_t buf = *(uint32_t*)(payload + 0x10);
      if (buf != 0 && *(int*)(buf - 4) != 0) {
        EFree((void*)buf);
      }
      EFree((void*)payload);
    }
    uint32_t n = nodeNext;
    uint32_t prev = *(uint32_t*)(n + 4);
    uint32_t next = *(uint32_t*)n;
    *(uint32_t*)prev = next;
    *(uint32_t*)(next + 4) = prev;
    EFree((void*)n);
  }
  m40 = 0;
  m48 = 0;
  ((uint8_t*)this)[0x15] = 1;
}

// @ 0x6b0ed0
Cache* Cache_Create(uint32_t a, uint32_t b) {
  return new ("App/LRUCache", 0, 0, 0, 0) Cache(a, b);
}

// @ 0x6b1000
uint64_t CacheList::Flush(Callback40* cb) {
  for (Entry* it = vec.begin; it != vec.end; ++it) {
    if (it->b == 0xb1b104) {
      SP_PropertyManager()->Call3c(1, it);
    }
    cb->Call40(it);
  }
  uint64_t rv = (uint64_t)total;
  total = 0;
  Entry* src = vec.end;
  Entry* dst = vec.begin;
  while (src != vec.end) {
    *dst = *src;
    ++dst;
    ++src;
  }
  int n = (int)((uint32_t)vec.end - (uint32_t)vec.begin) >> 4;
  vec.end = (Entry*)((uint32_t)vec.end + ((-n) << 4));
  return rv;
}

// @ 0x6b10a0
bool CacheList::Load(Callback38* cb) {
  Key12 local[16];
  uint32_t n = 0;
  for (Entry* it = vec.begin; it != vec.end; ++it) {
    if (cb->Call38(it) != 0) {
      return true;
    }
    if (it->b == 0xb1b104) {
      local[n++] = *reinterpret_cast<Key12*>(it);
    } else {
      if (ResourceMan_GetManager()->Call14(it, 0)) {
        return true;
      }
    }
  }
  if (n != 0) {
    if (SP_PropertyManager()->Call44((int)n, local)) {
      return true;
    }
  }
  return false;
}

// @ 0x6b1200  (partial)
bool CacheList::Read(Stream* s, uint32_t* p, uint64_t* q) {
  uint32_t cnt = p[0];
  if (cnt < 0xc) return false;
  p[0] = cnt - 0xc;
  if (!IO_ReadBytes(s, &m00, 1, 0)) return false;
  q[0] = *(uint64_t*)&m00;
  if (!IO_ReadInt32(s, &p[1], 1, 0)) return false;
  return true;
}

// @ 0x6b13b0
bool Cache::ReadStream(Stream* s) {
  int magic = 0;
  if (!IO_ReadInt32(s, &magic, 1, 0) || magic != 0x4c525531) return false;
  int count = 0;
  if (!IO_ReadInt32(s, &count, 1, 0)) return false;
  if ((uint32_t)count + 4 > s->GetSize()) return false;
  if (!s->SetPosition(count, 0)) return false;
  uint32_t n = 0;
  if (!IO_ReadInt32(s, &n, 1, 0)) return false;
  if (n > s->Get2()) return false;
  while (n != 0) {
    if (n < 8) return false;
    n -= 8;
    Key12 k;
    if (!IO_ReadBytes(s, &k, 1, 0)) return false;
    void* nodeOut = 0;
    Insert(&nodeOut, k.a, 0);
    uint32_t node = (uint32_t)nodeOut;
    CacheList* cl = 0;
    if (node != (uint32_t)&nodeNext) {
      cl = (CacheList*)*(uint32_t*)(node + 8);
    }
    uint64_t v = 0;
    if (!cl->Read(s, &n, &v)) return false;
    m40 += v;
  }
  return true;
}

// @ 0x6b14f0
void Cache::Load() {
  Clear();
  uint32_t obj = 0;
  uint32_t key[4];
  key[0] = 0;
  key[1] = 0x2e5a9763;
  key[2] = 0x2e5a9763;
  key[3] = 0;
  RefObj* src = (RefObj*)m0c;
  if (src->Call34(0, &obj, 1, 3, 1)) {
    if (!ReadStream((Stream*)obj)) {
      Clear();
    }
    ((RefObj*)obj)->Call24();
  }
  if (obj != 0) {
    ((RefObj*)obj)->Call18();
  }
}

// @ 0x6b15b0  (partial)
void Cache::Refresh() {
}

// @ 0x6b17a0
void Cache::Init() {
  MemStream* s = (MemStream*)EAlloc(0x24, "App/LRUCache/MemoryStream", 0, 0, 0, 0);
  if (s != 0) {
    s->Ctor("LRUCache/MemoryStream");
  } else {
    s = 0;
  }
  if (s != (MemStream*)stream) {
    if (s != 0) {
      s->AddRef();
    }
    MemStream* old = (MemStream*)stream;
    stream = (RefObj*)s;
    if (old != 0) {
      old->Release();
    }
  }
  SetSomething(1, 1.0f);
  Load();
  Refresh();
  helperafdd0();
  ((uint8_t*)this)[0x14] = 1;
  ((uint8_t*)this)[0x15] = 0;
}

// @ 0x6b1860
void Cache::Shutdown() {
  ((uint8_t*)this)[0x14] = 0;
  if (job != 0) {
    job->m0((void*)1);
    if (job != 0) {
      Job* j = job;
      job = 0;
      j->GetStatus();
    }
    ((uint8_t*)this)[0x15] = 1;
  }
  if (((uint8_t*)this)[0x15] != 0) {
    helperafdd0();
    helperafe80();
  }
  Clear();
  RefObj* s = stream;
  if (s != 0) {
    stream = 0;
    s->Release();
  }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
