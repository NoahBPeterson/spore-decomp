// Slice s006b09b0: App::LRUCache subsystem (manager + per-key cache list).
// Compiled with /O2 /MD /Gy /EHsc /TP.
#include "s006b09b0.h"

static const char* kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x6b09b0
// Lock-free ref-counted update of the +0x60 sub-object's map. The retail body
// performs a `lock cmpxchg8b` CAS loop over a 64-bit handle slot (see the
// AtomicRead64/AtomicExchange64 helpers at 0x68c140/0x68c1b0); that instruction
// cannot be emitted portably (no __asm allowed), so this remains a forwarding
// stub. __declspec(noinline) keeps Cache::A/B/C calling it (they are byte-exact).
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
    Entry* pos = vec.end;
    vec.end = pos + 1;
    if (pos != 0) *pos = tmp;
  } else {
    vec.DoInsertValue(vec.end, tmp);
  }
  total += (int64_t)score;
}

// @ 0x6b0c00
Cache::Cache(int a, int b) {
  vt0 = 0x014096c4;
  vt1 = 0x014096c0;
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
  m40 = 0;
  m48 = 0;
  m4c = 0;
  capacity = 9000;
  stream = 0;
  job = 0;
  sub.Init();
}

// @ 0x6b0da0
void** Cache::Insert(void** out, uint32_t key, uint32_t val) {
  uint32_t payload = helper08a0(key, val);
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
  k.b = val;
  k.c = (uint32_t)node;
  ((Map*)&m18)->Insert(&key, &k, (void*)((uint32_t)out & 0xffffff00));
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

// @ 0x6b1200
// Deserializes one per-key cache list from `s`. `p` points at the caller's
// remaining-byte counter and `q` receives the 64-bit running total read from the
// head of the blob. The entry count is the low 32 bits of the counter *pointer*
// (the engine reuses the argument slot as the loop counter), each entry consumes
// 12 stream bytes and the header consumes a fixed 12 bytes.
bool CacheList::Read(Stream* s, uint32_t* p, uint64_t* q) {
  uint32_t size = p[0];
  if (size < 0xc) return false;
  p[0] = size - 0xc;
  if (!IO_ReadBytes(s, &total, 1, 0)) return false;
  *q = (uint64_t)total;
  if (!IO_ReadInt32(s, p, 1, 0)) return false;
  uint32_t count = (uint32_t)p;
  uint32_t n = p[0];
  if (n < count * 12) return false;
  p[0] = n - count * 12;
  uint64_t sum = 0;
  vec.Reset();
  vec.Prepare(count);
  Entry tmp;
  tmp.a = m00;
  tmp.b = 0;
  tmp.c = 0;
  while (count != 0) {
    --count;
    if (!IO_ReadInt32(s, &tmp.c, 1, 0)) return false;
    if (!IO_ReadInt32(s, &tmp.b, 1, 0)) return false;
    if (!IO_ReadInt32(s, &tmp.score, 1, 0)) return false;
    if (vec.end < vec.cap) {
      Entry* pos = vec.end;
      vec.end = pos + 1;
      if (pos != 0) *pos = tmp;
    } else {
      vec.DoInsertValue(vec.end, tmp);
    }
    sum += tmp.score;
  }
  if (total != (int64_t)sum) return false;
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

// @ 0x6b15b0
// Rebuilds the per-world cache lists: asks the +0x0C provider for its 12-byte
// world records, skips the 0x2e5a9763 marker records, looks each key up in the
// map at +0x18, inserts a fresh list node when absent, and for keys not yet in
// the list creates a job whose score is folded into the running total at +0x40.
void Cache::Refresh() {
  Record12* begin = 0;
  Record12* end = 0;
  Record12* cap = 0;
  ((RecordProvider*)m0c)->GetRecords(&begin);

  Record12* endSaved = end;
  Record12* it = begin;
  if (it != endSaved) {
    do {
      if (it->b != 0x2e5a9763) {
        uint32_t raw = it->c;
        uint32_t cls = raw & 0xc0000000;
        uint32_t score = (cls == 0x40000000)
                             ? (((raw & 0xff0000) | cls) & 0xffff00ff)
                             : 0;

        Key12 key;
        key.a = it->a;
        key.b = 0;
        key.c = 0;
        void* found = 0;
        ((Map*)&m18)->Find((uint32_t*)&found, &key);
        uint32_t listHead = (uint32_t)&nodeNext;
        uint32_t node = (found != (void*)((uint32_t)&nodeNext - 0x18))
                            ? *(uint32_t*)((uint32_t)found + 0x18)
                            : listHead;
        if (node == listHead) {
          void* nodeOut = 0;
          Insert(&nodeOut, key.a, score);
          node = (uint32_t)nodeOut;
        }

        CacheList* cl = (node != listHead) ? (CacheList*)*(uint32_t*)(node + 8) : 0;
        if (cl != 0) {
          bool present = false;
          for (Entry* e = cl->vec.begin; e != cl->vec.end; ++e) {
            if (e->a == it->a && e->b == it->b && e->c == it->c) {
              present = true;
              break;
            }
          }
          if (present) goto next;
        }

        {
          RecordJob* job = 0;
          if (((RecordProvider*)m0c)->GetRecordJob(it, (void**)&job, 1, 6, 1, 0)) {
            job->Step();
            uint32_t v = job->Value();
            cl->AddOrUpdate(key, v);
            m40 += (int64_t)v;
            job->Release();
            if (node != listHead) {
              uint32_t head = (uint32_t)&nodeNext;
              uint32_t nxt = *(uint32_t*)node;
              if (head != node && head != nxt) {
                *(uint32_t*)(*(uint32_t*)(nxt + 4)) = head;
                *(uint32_t*)(*(uint32_t*)(node + 4)) = nxt;
                *(uint32_t*)(*(uint32_t*)(head + 4)) = node;
                *(uint32_t*)(node + 4) = *(uint32_t*)(nxt + 4);
                *(uint32_t*)(nxt + 4) = *(uint32_t*)(node + 4);
              }
            }
            ((uint8_t*)this)[0x15] = 1;
          }
        }
      }
    next:
      it = (Record12*)((char*)it + 0xc);
    } while (it != endSaved);
  }
  if (begin != 0 && ((uint32_t*)begin)[-1] != 0)
    EFree(begin);
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
