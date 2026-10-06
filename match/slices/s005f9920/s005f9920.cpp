// slice s005f9920 -- SP::Thumbnail::cImportExport image/import-table routines plus hashtable
// bucket teardown helpers. Flags: /O2 /MD /Gy /TP /GS- (no EH frame, no cookie).
#include "types.h"

void EA_Deallocate(void* p);  // 0x00f47380

// @ 0x005FA1D0
void __stdcall ClearBucketsA(int** buckets, unsigned count) {
  for (unsigned i = 0; i < count; i++) {
    int* p = buckets[i];
    while (p) {
      int* cur = p;
      int* next = (int*)p[7];
      int s0 = cur[0];
      int d = (cur[2] - cur[0]) & 0xfffffffe;
      if (d > 2 && s0 != 0)
        EA_Deallocate((void*)s0);
      EA_Deallocate(cur);
      p = next;
    }
    buckets[i] = 0;
  }
}

// @ 0x005FA230
void __stdcall ClearBucketsB(int** buckets, unsigned count) {
  for (unsigned i = 0; i < count; i++) {
    int* p = buckets[i];
    while (p) {
      int* next = (int*)p[7];
      int* cur = p;
      int s3 = cur[3];
      int d = (cur[5] - cur[3]) & 0xfffffffe;
      if (d > 2 && s3 != 0)
        EA_Deallocate((void*)s3);
      EA_Deallocate(cur);
      p = next;
    }
    buckets[i] = 0;
  }
}

// ---------------------------------------------------------------------------------------------
// Shared stub types
extern char gEmptyString[];  // 0x01667bac (EASTL empty-string storage)

struct Str8 {  // eastl::basic_string<char> (3 pointers)
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  int mAllocator;
  Str8() {
    mpBegin = gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~Str8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EA_Deallocate(mpBegin);
  }
};

struct WStr {  // eastl::basic_string<wchar_t>
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  WStr() {
    mpBegin = (wchar_t*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  WStr(const WStr& o);  // 0x0056e2d0
  ~WStr() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EA_Deallocate(mpBegin);
  }
  void resize(unsigned n);                          // 0x00429520
  void assign(const wchar_t* b, const wchar_t* e);  // 0x00423650
};

struct Key3 {
  unsigned a, b, c;
  Key3() {}
  Key3(unsigned a_, unsigned b_, unsigned c_) : a(a_), b(b_), c(c_) {}
};

void __cdecl StrSprintf(Str8* s, const char* fmt, ...);        // 0x00472fe0
void __cdecl StrAppendSprintf(Str8* s, const char* fmt, ...);  // 0x005f9450
bool __cdecl Str16Equal(const void* a, const void* b);         // 0x0087d9a0

void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

struct IWriter {  // 0x0067da60 memory writer
  IWriter(int a, int b);  // ret 8
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual bool IsOk();  // +0x18
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual bool Write(const void* p, int n);  // +0x38
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual bool Attach(void* req, int n);  // +0x48
  char pad[0x2c];
};

struct IRequest {  // Graphics::GraphicsFactoryAsyncRequest
  IRequest(int a, int b, const char* name);  // 0x0093c270 (ret 0xc)
  void SetProperty(int id, float v);         // 0x0093bb40 (ret 8)
  int Describe(int sz);                      // 0x0093ba70 (ret 4)
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual int GetSize();  // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void Start(int a, int b);  // +0x28
  char pad[0x20];
};

struct IObj {  // 0x008e2380
  static void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00926020
  IObj(int a, IWriter* w, Key3* key, int c, int d);  // ret 0x14
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual Key3* GetInfo();  // +0x10
  char pad[0x20];
};

struct IRes {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual bool Place(void* a, IObj* o, int b, int c);  // +0x28
};

struct IMgr {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual IRes* Lookup(unsigned a, int b);  // +0x48
};
IMgr* __cdecl GetManager();  // 0x0067dcd0

struct cAssetMetadata {
  Key3* GetKey();                 // 0x005507c0
  unsigned long long* GetA();     // 0x005507a0
  unsigned long long* GetB();     // 0x00550840
  const wchar_t* GetNameW();      // 0x00550880
  unsigned long long GetAssetKey();  // 0x005508a0
  const wchar_t* GetNameW2();     // 0x00414e10
  const wchar_t* GetNameW3();     // 0x005508c0
  unsigned GetYCount();           // 0x005509b0
  const wchar_t* GetY(unsigned i);  // 0x005509e0
  unsigned GetZCount();           // 0x00550a30
  unsigned GetZ(unsigned i);      // 0x00550a60
};
namespace SP { namespace Pollen {
void __cdecl GetParentServerID(cAssetMetadata* m, unsigned long long* a, unsigned long long* b);  // 0x00552080
}}

struct JobLock {
  bool H3(int a);  // 0x0068eef0
  bool H(int a);   // 0x0068eca0
  bool H2(int a);  // 0x0068ed70
};

struct IStream {
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* GetReader();  // +0x18
  virtual void v7();
  virtual void v8();
  virtual void Close();  // +0x24
};
struct IReader {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual int Read(void* p, int n);  // +0x30
};
struct ISaveArea {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual bool Open(void* key, IStream** out, int a, int b, int c, int d);  // +0x34
};
ISaveArea* __cdecl GetSaveArea(int id);  // 0x006b1f90
void __cdecl FixPath(WStr* s);           // 0x005f7970

struct PathBuf {  // 0x0092fcc0
  char d[0x420];
  PathBuf();
  void AssignW(const wchar_t* p);        // 0x00930da0 (ret 4)
  void SetName(const wchar_t* p, int a);  // 0x00931100 (ret 8)
  const wchar_t* c_str();                // 0x00572590
};

struct PairWK {  // pair<wstring, key>   0x005f8690
  WStr s;
  Key3 k;
  PairWK(const WStr& a, const Key3& b);
};
struct ValueWK {  // pair<const wstring, key>   0x005f8320
  WStr s;
  Key3 k;
  ValueWK(const PairWK& p);
};
struct PairKW {  // 0x005f8700
  Key3 k;
  WStr s;
  PairKW(const Key3& a, const WStr& b);
};
struct ValueKW {  // 0x005f8390
  Key3 k;
  WStr s;
  ValueKW(const PairKW& p);
};
struct PairKK {
  Key3 a, b;
  PairKK(const Key3& x, const Key3& y) : a(x), b(y) {}
};

struct IterBool { int it[3]; };
struct MapWK {  // 0x005f9470
  char d[0x20];
  void Insert(IterBool* out, const ValueWK& v, bool b);
};
struct MapKW {  // 0x005f95a0
  char d[0x20];
  void Insert(IterBool* out, const ValueKW& v, bool b);
};
struct MapKK {  // 0x005f8170
  char d[0x20];
  void Insert(IterBool* out, const PairKK& v, bool b);
};
struct MapKK2 {  // 0x005f8240
  char d[0x20];
  void Insert(IterBool* out, const PairKK& v, bool b);
};

namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  bool WriteAssetDataToImage(cAssetMetadata* meta, void* a, int b);  // 0x005f9920
  bool RestoreImportTable();                                         // 0x005fa290
  void ResolveName(unsigned id, WStr* out);                          // 0x005f9230
  char pad0[4];
  MapWK mWK;      // +4
  MapKW mKW;      // +0x24
  unsigned mField44;
  MapKK mKK;      // +0x48
  MapKK2 mKK2;    // +0x68
  JobLock mLock;  // +0x88
};
}  // namespace Thumbnail
}  // namespace SP

// @ 0x005F9920
bool SP::Thumbnail::cImportExport::WriteAssetDataToImage(cAssetMetadata* meta, void* a, int b) {
  Str8 s;
  Str8 t;
  IRequest* req = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IRequest(0, 0, "UTF/MemoryStream");
  if (req)
    req->AddRef();
  req->SetProperty(1, 1.0f);
  req->SetProperty(2, 2.0f);
  req->Start(0, 0);
  IWriter* w = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IWriter(0, -1);
  if (w)
    w->AddRef();
  bool result;
  bool ok = w->Attach(req, -1);
  if (!ok) {
    result = false;
    goto done;
  }
  ok = w->Write("spore", 5);
  StrSprintf(&s, "%04d", 6);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->b);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->c);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->a);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", mField44);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  {
    unsigned long long* pa = meta->GetA();
    StrSprintf(&s, "%016llx", *pa);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  {
    unsigned long long parent = (unsigned long long)-1;
    unsigned long long server = (unsigned long long)-1;
    SP::Pollen::GetParentServerID(meta, &parent, &server);
    StrSprintf(&s, "%016llx", parent);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  {
    unsigned long long* pb = meta->GetB();
    StrSprintf(&s, "%016llx", *pb);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  StrSprintf(&t, "%ls", meta->GetNameW());
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  StrSprintf(&s, "%016llx", meta->GetAssetKey());
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&t, "%ls", meta->GetNameW2());
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  StrSprintf(&t, "%ls", meta->GetNameW3());
  StrSprintf(&s, "%03x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  {
    unsigned n = meta->GetYCount();
    if (n != 0) {
      StrSprintf(&t, "%ls", meta->GetY(0));
      for (unsigned i = 1; i < n; i++)
        StrAppendSprintf(&t, ", %ls", meta->GetY(i));
    } else if (t.mpBegin != t.mpEnd) {
      *t.mpBegin = 0;
      t.mpEnd = t.mpBegin;
    }
  }
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  {
    unsigned zc = meta->GetZCount();
    StrSprintf(&s, "%02x", zc);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
    unsigned i = 0;
    if (ok) {
      do {
        if (i >= zc)
          break;
        StrSprintf(&s, "%08x", meta->GetZ(i));
        ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
        i++;
      } while (ok);
    }
  }
  {
    IMgr* mgr = GetManager();
    IRes* res = mgr->Lookup(meta->GetKey()->b, -1);
    if (ok && res) {
      IObj* obj = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IObj(0, w, meta->GetKey(), 0, 0);
      if (obj)
        obj->AddRef();
      ok = res->Place(a, obj, 0, obj->GetInfo()->b) != 0;
      obj->Release();
    } else {
      ok = false;
    }
  }
  if (w->IsOk() && ok) {
    result = true;
    if (!mLock.H3(b))
      goto done;
    int sz = req->GetSize();
    if (mLock.H(req->Describe(sz)) && mLock.H2(1)) {
      result = true;
      goto done;
    }
  }
  result = false;
done:
  w->Release();
  req->Release();
  return result;
}

// @ 0x005FA100
struct StrNode {
  WStr key;
  unsigned pad;
  StrNode* next;
};
struct StrTable {
  unsigned pad0;
  StrNode** mBuckets;  // +4
  unsigned mBucketCount;  // +8
  int mSize;  // +0xc
  unsigned erase(const WStr* key);
};
unsigned StrTable::erase(const WStr* key) {
  unsigned h = 0x811c9dc5;
  const unsigned short* p = (const unsigned short*)key->mpBegin;
  unsigned c = *p;
  while (c) {
    h = (h * 0x1000193) ^ c;
    p++;
    c = *p;
  }
  StrNode** pp = &mBuckets[h % mBucketCount];
  int before = mSize;
  if (*pp) {
    do {
      StrNode* n = *pp;
      if (Str16Equal(key, n))
        break;
      pp = &n->next;
    } while (*pp);
    while (*pp) {
      StrNode* n = *pp;
      if (!Str16Equal(key, n))
        break;
      *pp = n->next;
      if ((n->key.mpCapacity - n->key.mpBegin) > 1 && n->key.mpBegin)
        EA_Deallocate(n->key.mpBegin);
      EA_Deallocate(n);
      mSize--;
    }
  }
  return before - mSize;
}

// @ 0x005FA290
bool SP::Thumbnail::cImportExport::RestoreImportTable() {
  ISaveArea* save = GetSaveArea(0x11ac19d);
  if (!save)
    return false;
  IStream* stream = 0;
  if (!save->Open((void*)0x151c9e0, 0, 1, 6, 1, 0)) {
    if (stream)
      stream->Release();
    return true;
  }
  if (stream) {
    IStream* t = stream;
    stream = 0;
    t->Release();
  }
  if (!save->Open((void*)0x151c9e0, &stream, 1, 3, 1, 0)) {
    if (stream)
      stream->Release();
    return true;
  }
  IReader* r = (IReader*)stream->GetReader();
  unsigned version, count, len;
  bool ok;
  if (r->Read(&version, 4) && version <= 3 && r->Read(&count, 4))
    ok = true;
  else
    ok = false;
  WStr str;
  if (ok) {
    while (count-- != 0) {
      bool got;
      if (ok && r->Read(&len, 4)) {
        str.resize(len);
        got = r->Read(str.mpBegin, len * 2) != 0;
      } else {
        got = false;
      }
      Key3 k;
      k.a = 0;
      k.b = 0;
      k.c = 0;
      if (!got || !r->Read(&k.b, 4) || !r->Read(&k.c, 4) || !r->Read(&k.a, 4)) {
        ok = false;
        break;
      }
      ok = true;
      if (version < 3) {
        WStr tmp;
        ResolveName(k.b, &tmp);
        PathBuf pb;
        pb.AssignW(tmp.mpBegin);
        pb.SetName(str.mpBegin, 0);
        const wchar_t* p = pb.c_str();
        const wchar_t* e = p;
        while (*e)
          e++;
        str.assign(p, e);
        FixPath(&str);
      }
      {
        PairWK pa(WStr(str), Key3(k.a, k.b, k.c));
        ValueWK va(pa);
        IterBool ib;
        mWK.Insert(&ib, va, false);
      }
      {
        PairKW pb2(Key3(k.a, k.b, k.c), WStr(str));
        ValueKW vb(pb2);
        IterBool ib;
        mKW.Insert(&ib, vb, false);
      }
    }
  }
  if (version >= 2) {
    if (!ok || !r->Read(&count, 4)) {
      ok = false;
    } else {
      ok = true;
      while (count-- != 0) {
        Key3 k;
        k.a = 0;
        k.b = 0;
        k.c = 0;
        Key3 y;
        if (!r->Read(&k.b, 4) || !r->Read(&k.c, 4) || !r->Read(&k.a, 4) ||
            !r->Read(&y.a, 4) || !r->Read(&y.b, 4) || !r->Read(&y.c, 4)) {
          ok = false;
          break;
        }
        {
          PairKK p1(y, k);
          IterBool ib;
          mKK.Insert(&ib, p1, false);
        }
        {
          PairKK p2(k, y);
          IterBool ib;
          mKK2.Insert(&ib, p2, false);
        }
        ok = true;
      }
    }
  }
  stream->Close();
  if (stream)
    stream->Release();
  return ok;
}
