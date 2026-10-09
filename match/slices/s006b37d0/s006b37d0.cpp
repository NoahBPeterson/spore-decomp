// Slice s006b37d0: SP default save areas / save-area job holder.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b37d0.h"

// @ 0x6b42f0
bool Counter40::Inc() {
  if (m40 != 0) {
    ++m40;
    return true;
  }
  return false;
}

// @ 0x6b4390
uint32_t FUN_006b4390(ObjSec6** p) {
  ObjSec6* o = *p;
  if (o != 0) {
    return o->sec.Call0c(0x6492c5f);
  }
  return 0;
}

// @ 0x6b43b0
JobHolder6::JobHolder6() : mutex(0, 1) {}

// @ 0x6b4340
JobHolder6::~JobHolder6() {}

JobPtr6::~JobPtr6() {
  if (p != 0) {
    ((Job6*)p)->GetStatus();
  }
}

// @ 0x6b4730
void FUN_006b4730() {
  g_1604b80 = 1;
  new (&g_jobHolder6) JobHolder6();
}

// @ 0x6b4780
void FUN_006b4780() {
  g_jobHolder6.~JobHolder6();
  g_1604b80 = 0;
}

#define REL6(s) do { if (s) { out.p = 0; (s)->ref.Release(); } } while (0)
#define SAVE_DIR6(root, nm, key) \
  ok = CreateDirectorySave(root, nm, &out.p, key); s = out.p; if (ok) RegisterSaveArea(key, s, 0)

// @ 0x6b37d0
void SP_CreateDefaultSaveAreas() {
  cString6 str;
  SaveRef6 out;
  Ref6b out2;
  SaveObj6* s;
  bool ok;

  str.Load(0x19f76d11, 0x5ca8d99, L"Pictures");
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac196);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac196, s, 0);
  str.Load(0x19f76d11, 0x5ca8d98, L"Movies");
  REL6(s);
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac197);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac197, s, 0);
  str.Load(0x19f76d11, 0x5ca8d9a, L"Animations");
  REL6(s);
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac198);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac198, s, 0);
  REL6(s);
  ok = CreateDirectorySave(0xa02151, L"Games/Game0", &out.p, 0x4729a47);
  s = out.p;
  if (ok) RegisterSaveArea(0x4729a47, s, 0);
  REL6(s);
  ok = CreateDirectorySave(0xa02151, L"Preferences", &out.p, 0x11ac192);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac192, s, 0);

  if (g_editorMode6 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"Creatures", 0x11ac199);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Buildings", 0x11ac19a);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Vehicles", 0x11ac19b);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Cells", 0x90368ea3);
    REL6(s);
    SAVE_DIR6(0xa02151, L"UFOs", 0x90368ea2);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Plants", 0x90368ea0);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Adventures", 0x86ca01c9);
  } else {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"EditorSaves", &out.p, 0x11ac199, 1);
    s = out.p;
    if (ok) {
      RegisterSaveArea(0x11ac199, s, 0);
      RegisterSaveArea(0x11ac19a, s, 0);
      RegisterSaveArea(0x11ac19b, s, 0);
      RegisterSaveArea(0x90368ea3, s, 0);
      RegisterSaveArea(0x90368ea2, s, 0);
      RegisterSaveArea(0x90368ea0, s, 0);
      RegisterSaveArea(0x86ca01c9, s, 0);
    }
  }

  if (g_appProps6->desc->flag118 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"CityMusic", 0x500efc6);
  }

  if (g_serverMode6 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"Cache", 0x11ac19c);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Server", 0x11ac19d);
  } else {
    if (g_appProps6->desc->flag118 == 0) {
      REL6(s);
      ok = CreatePackageSave(0xa02151, g_dir13ec468, L"Pollination.package", &out.p);
    } else {
      REL6(s);
      ok = CreateServerCacheSave(0xa02151, g_dir13ec468, L"ServerCache.package", &out.p);
    }
    s = out.p;
    if (ok) {
      RegisterSaveArea(0x11ac19c, s, 0);
      RegisterSaveArea(0x11ac19d, s, 0);
    }
  }

  if (g_appProps6->desc->flag118 == 0) {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"Planets", &out.p, 0x31389b5, g_serverMode6);
    s = out.p;
    if (ok) RegisterSaveArea(0x31389b5, s, 0);
  }
  REL6(s);
  ok = CreateLocationSave(0xa02151, L"RigblockInfo", &out.p, 0x49a3d83, g_serverMode6);
  s = out.p;
  if (ok) RegisterSaveArea(0x49a3d83, s, 0);

  if (g_gfxMode6 == 0) {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"GraphicsCache", &out.p, 0x11ac1ac, g_serverMode6);
    if (!ok) goto done;
  } else {
    if (g_serverMode6 == 0) {
      REL6(s);
      ok = CreateGraphicsDir(0xa02151, L"GraphicsCache", &out.p, &out2.p, 0xb1e36ca3, 0x11ac1ac);
    } else if (g_appProps6->GetDescription(FNV1_String8("UseBigPackedDatabases", 0x811c9dc5, 1))) {
      REL6(s);
      ok = CreateCachedDirectorySave(0xa02151, g_dir13ec468, L"GraphicsCache.package", &out.p, &out2.p, 0xb1e36ca3);
    } else {
      REL6(s);
      ok = CreateGraphicsPackage(0xa02151, g_dir13ec468, L"GraphicsCache.package", &out.p, &out2.p, 0xb1e36ca3);
    }
    if (!ok) goto done;
  }
  RegisterSaveArea(0x11ac1ac, out.p, out2.p);
done:;
}

// @ 0x6b4010
bool SP_SaveNamedResource(KeyRef6* key, const wchar_t* name, Res6* res) {
  if (res == 0) return false;
  ResMgr6* mgr = GetResMgr6();
  WStr6 str;
  Key3 k;
  int dot;
  k.inst = key->inst;
  k.type = key->type;
  k.group = key->group;
  str.b = str.e = str.cap = 0;
  str.Init(name);
  dot = str.rfind(L'.', -1);
  Res6* r2 = 0;
  if (res->GetKind() == 0x34728492) {
    k.group = res->GetGroup();
    r2 = res;
  }
  if (dot == -1 && r2) {
    const wchar_t* ext = r2->GetName(k.type);
    if (ext == 0) {
      ext = mgr->GetExt(k.type);
      if (ext) r2->SetName(ext, k.type);
    }
    str.push_back(L'.');
    if (ext) str.append(ext);
    else FormatHex6(&str, L"0x%08x", k.type);
  }
  SPKeyFromName(&k.inst, str.b, k.type, k.group);
  if (r2) {
    wchar_t buf[256];
    if (r2->GetPath(&k.inst, buf)) {
      if (_wcsicmp(buf, str.b) != 0) return false;
    } else {
      mgr->SetName(&k.inst, str.b);
    }
  }
  key->inst = k.inst;
  key->type = k.type;
  key->group = k.group;
  Fmt6* fmt = (Fmt6*)mgr->GetFormat(k.type, -1);
  if (fmt == 0) return false;
  IStream6* strm = 0;
  if (res->Open(&k.inst, &strm, 2, 2, 1, 0)) {
    bool r = fmt->Write(key, strm, 0, k.type);
    strm->Close();
    if (strm) strm->Release();
    return r;
  }
  if (strm) strm->Release();
  return false;
}

// @ 0x6b4400
Job6B::~Job6B() {}

// @ 0x6b4490
bool Job6B::Prepare(JobCtx6* c) {
  void* data = strm.GetData();
  m50 = strm.Size();
  m54 = 0;
  m48 = 0;
  m4c = 0;
  switch (m14) {
  case 0x2f7d0002:
  case 0x2f7d0004:
  case 0x2f7d0007:
    break;
  default: {
    SvcBase6* svc;
    bool ok;
    char r;
    if (m1c.p) {
      SvcA6* a = (SvcA6*)m1c.p->sec.Query(0x226a25b);
      svc = a;
      if (a) {
        if (!a->Check(&m10, m50)) goto fail;
        r = a->Pack(data, m50, &m48, &m4c, &m54);
        goto common;
      }
    }
    if (m1c.p) {
      SvcB6* b = (SvcB6*)m1c.p->sec.Query(0x6492c5f);
      svc = b;
      if (b) {
        if (!b->Check(&m10, m50)) goto fail;
        r = b->Pack(data, m50, &m48, &m4c, &m54);
        goto common;
      }
    }
    goto fallback;
  common:
    ok = true;
    if (r) goto detach;
  fail:
    ok = false;
  detach:
    uint32_t d = svc->Detach();
    if (ok) {
      strm.Attach(0, 0);
      strm.SetData(m48, m4c, 1, 1, d);
      c->Done(0);
      return true;
    }
  }
  }
fallback:
  m48 = (uint32_t)data;
  m4c = m50;
  m54 = 0;
  c->Done(0);
  return true;
}

// @ 0x6b4610
bool Job6B::Finish(JobCtx6* c) {
  bool ok = false;
  SvcA6* a = 0;
  if (m1c.p) a = (SvcA6*)m1c.p->sec.Query(0x226a25b);
  if (a) {
    ok = a->Unpack(&m10, m48, m4c, m50, m54);
  } else if (m1c.p) {
    SvcB6* b = (SvcB6*)m1c.p->sec.Query(0x6492c5f);
    if (b) ok = b->Unpack(&m10, m48, m4c, m50, m54);
    else goto tail;
  } else {
    goto tail;
  }
  if (ok && m1c.p) {
    AllocHolder6* h = (AllocHolder6*)m1c.p->sec.Query(0x498d9c1);
    if (h) h->GetAllocator()->Free(&m10, m4c);
  }
tail:
  m48 = 0;
  strm.Flush();
  if (m0c.p) { IRefC* t = m0c.p; m0c.p = 0; t->Release(); }
  if (m1c.p) { ProvObj6* t = m1c.p; m1c.p = 0; t->sec.Release(); }
  c->Done(0);
  return ok;
}
// --- equivalence checker address annotations
    void CreateDirectorySave(...); // 0x006b2620
    void GetResMgr6(...); // 0x0067dcd0
    void RegisterSaveArea(...); // 0x006b3760

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct WStr6 {
    void rfind(wchar_t, int); // 0x0041dfc0
    void Init(wchar_t*); // 0x00579a90
    void push_back(wchar_t); // 0x004f6510
    void append(wchar_t*); // 0x00599bb0
};
struct SvcA6 {
    void Pack(void*, unsigned int, unsigned int*, unsigned int*, unsigned short*); // 0x008d9850
    void Check(void*, unsigned int); // 0x008d8570
};
struct SvcB6 {
    void Pack(void*, unsigned int, unsigned int*, unsigned int*, unsigned short*); // 0x006bd580
    void Check(void*, unsigned int); // 0x006bc3e0
};
struct cString6 {
    void GetText(); // 0x006b55c0
    void Load(unsigned int, unsigned int, wchar_t*); // 0x006b54b0
    cString6(); // 0x006b5060
};
struct Stream6 {
    void GetData(); // 0x0093ba70
};
}
