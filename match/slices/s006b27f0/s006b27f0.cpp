// Slice s006b27f0: SP save-area registration / teardown.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b27f0.h"

void* __cdecl operator new(size_t, const char*, int, int, int, int);   // EA::Allocator::ZoneObject::operator_new (0x926020)
void __cdecl operator delete(void* p);                                 // 0x00f47380

// @ 0x6b2aa0
void SaveMap5::Nuke(RBNode5* n) {
  while (n != 0) {
    Nuke(n->left);
    RBNode5* right = n->right;
    if (n->val.b != 0) {
      n->val.b->Release();
    }
    if (n->val.a != 0) {
      n->val.a->ref.Release();
    }
    EFree5(n);
    n = right;
  }
}

// @ 0x6b3610
void FUN_006b3610() {
  for (uint32_t* it = (uint32_t*)g_m5.root; it != &g_m5.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    ((SaveObj5*)it[5])->Call1c();
    ((SaveObj5*)it[5])->Call08();
  }
  g_m5.Nuke((RBNode5*)g_m5.nukep);
  g_m5.head = (uint32_t)&g_m5.head;
  g_m5.root = (uint32_t)&g_m5.head;
  g_m5.nukep = 0;
  *(uint8_t*)&g_m5.f10 = 0;
  g_m5.f14 = 0;
}

// @ 0x6b27f0
// SP::cAppSystem::CreateHTTPServer
bool __cdecl SP_cAppSystem_CreateHTTPServer(uint32_t id, const wchar_t* sub, IRef6** outServer, IRef6** outCache,
                                            uint32_t cacheArg, uint32_t extraGroup) {
    WStrA dir(GetDirFromID(id));
    dir.Append(sub, WStrEnd(sub));
    DbDirFiles* files = new("App", 0, 0, 0, 0) DbDirFiles(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files == 0) {
        return false;
    }
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        files->ref.Release();
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv == 0) {
        cache->Release();
        files->ref.Release();
        return false;
    }
    srv->Release();
    ReadExtensionMappingsFromPropFile(0x1c7ac81, files);
    if (extraGroup) {
        files->SetMappingFile(extraGroup);
        ReadExtensionMappingsFromPropFile(extraGroup, files);
    }
    if (srv->Start(3, 4, 0)) {
        if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
            *outServer = (IRef6*)srv;
            *outCache = cache;
            files->ref.Release();
            return true;
        }
        srv->Stop();
    }
    srv->Shutdown();
    srv->ref.Release();
    cache->Release();
    files->ref.Release();
    return false;
}

// @ 0x6b2b30
// OpenPreCommitFile
bool __cdecl OpenPreCommitFile(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outServer, IRef6** outCache,
                      uint32_t cacheArg) {
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbPackedFile* files = new("App", 0, 0, 0, 0) DbPackedFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    files->SetOption(0x12, g_13eb95c);
    files->Open(0);
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        if (files) {
            files->ref.Release();
        }
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv) {
        srv->Release();
        if (srv->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
                *outServer = (IRef6*)srv;
                *outCache = cache;
                if (files) {
                    files->ref.Release();
                }
                return true;
            }
            srv->Stop();
        }
        srv->Shutdown();
        srv->ref.Release();
    }
    cache->Release();
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x6b2dc0
// SP::CreateCachedDirectorySave
bool __cdecl SP_CreateCachedDirectorySave(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outServer, IRef6** outCache,
                      uint32_t cacheArg) {
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbXFile* files = new("App", 0, 0, 0, 0) DbXFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    files->SetOption(0x12, g_13eb95c);
    files->Open(0);
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        if (files) {
            files->ref.Release();
        }
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv) {
        srv->Release();
        if (srv->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
                *outServer = (IRef6*)srv;
                *outCache = cache;
                if (files) {
                    files->ref.Release();
                }
                return true;
            }
            srv->Stop();
        }
        srv->Shutdown();
        srv->ref.Release();
    }
    cache->Release();
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x6b3050
// `anonymous namespace'::cDirectoriesCheat::Execute
bool __cdecl cDirectoriesCheat_Execute(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outFile) {
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbPackedFile* files = new("App", 0, 0, 0, 0) DbPackedFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files) {
        files->SetOption(0x12, g_13eb95c);
        files->Open(0);
        ((IRef6*)files)->Release();
        if (((DbService*)files)->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, files, 1000)) {
                *outFile = (IRef6*)files;
                files->ref.AddRef();
                files->ref.Release();
                return true;
            }
            ((DbService*)files)->Stop();
        }
        ((DbService*)files)->Shutdown();
    }
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x6b3240
// SP::CreatePackageSave
bool __cdecl SP_CreatePackageSave(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outFile) {
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbXFile* files = new("App", 0, 0, 0, 0) DbXFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files) {
        files->SetOption(0x12, g_13eb95c);
        files->Open(0);
        ((IRef6*)files)->Release();
        if (((DbService*)files)->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, files, 1000)) {
                *outFile = (IRef6*)files;
                files->ref.AddRef();
                files->ref.Release();
                return true;
            }
            ((DbService*)files)->Stop();
        }
        ((DbService*)files)->Shutdown();
    }
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x6b3430
// SP::CreateLocationSave: with `package` set the path gets ".package" appended and goes through the
// directories cheat path, otherwise it is a plain directory save.
bool __cdecl SP_CreateLocationSave(uint32_t id, const wchar_t* name, IRef6** out, void* extra, bool package) {
    if (package) {
        WStrA path(name);
        path.Append(L".package", WStrEnd(L".package"));
        return cDirectoriesCheat_Execute(id, kEmpty13ec468, path.mpBegin, out);
    }
    return CreateDirectorySave(id, name, out, extra);
}

// @ 0x6b3680
// eastl::map<unsigned, cSPSaveArea>::operator[]
RefPair5& SaveMap5::Index(const uint32_t& key) {
  RBNode5* end = (RBNode5*)&head;
  RBNode5* pRangeEnd = end;
  RBNode5* pCurrent = (RBNode5*)nukep;
  while (pCurrent) {
    if (!(pCurrent->m10 < key)) {
      pRangeEnd = pCurrent;
      pCurrent = pCurrent->right;
    } else {
      pCurrent = pCurrent->left;
    }
  }
  RBNode5* it = pRangeEnd;
  if (it == end || key < it->m10) {
    RefPair5 tmp;
    SavePair p(key, tmp);
    SavePairResult r;
    DoInsertValue(&r, it, p, TrueTag5());
    it = r.node;
  }
  return it->val;
}

// @ 0x6b3760
// SP::RegisterSaveArea: g_m5[key] = RefPair(a, b)
void __cdecl SP_RegisterSaveArea(uint32_t key, void* a, void* b) {
  g_m5.Index(key) = RefPair5(a, b);
}
