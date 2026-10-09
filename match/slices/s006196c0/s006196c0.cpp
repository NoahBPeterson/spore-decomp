// Slice s006196c0: SP::Pollen::cModelUploadTransaction::ConstructRequest (3984 bytes).
//
// Builds the multipart/form-data upload request for a creation: form fields (TypeId, assetId,
// description, tags, traitguids), the "ModelData" file (served through a memory-stream
// GraphicsFactoryAsyncRequest), the "ThumbnailData" / "ImageData[_n]" PNG files looked up in the
// resource manager, then posts the HTTP request, tags it with parent ids / slurp / bound and
// attaches a cServerResponse handler.  Built /O2 /MD /Gy /TP (no /EHsc): every failure path
// frees the strings/ref-counted locals inline, which locals with inline dtors reproduce.
//
// Complete behaviorally-equivalent source; not byte-exact (vtable slot names are guesses, the
// original is one hand-flattened body).  Listed in nonmatching.txt.
#include "types.h"
#include <string.h>
#include <intrin.h>

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);                  // 0x00f473a0
void* operator new(unsigned size, const char* name, int a, int b, const char* file, int line);    // 0x00f473a0
void operator delete[](void* p);                                                                    // 0x00f47380

extern char gEmptyString8[];  // 0x01667bac, shared empty string storage

namespace eastl {
struct allocator {
  allocator() {}
};
template <typename T, typename A = allocator>
struct basic_string {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string() : mpBegin(gEmptyString8), mpEnd(gEmptyString8), mpCapacity(gEmptyString8 + 1) {}
  explicit basic_string(const char* s) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    unsigned n = (unsigned)strlen(s);
    mpBegin = (char*)operator new(n + 1, "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                  0xd1);
    mpCapacity = mpBegin + n + 1;
    memcpy(mpBegin, s, n + 1);
    mpEnd = mpBegin + n;
  }
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1) {
      if (mpBegin) operator delete[](mpBegin);
    }
  }
  static basic_string& sprintf(basic_string* s, const char* fmt, ...);         // 0x00472fe0 (cdecl)
  static basic_string& append_sprintf(basic_string* s, const char* fmt, ...);  // 0x005f9450 (cdecl)
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;

namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

// Intrusive smart pointer: slot 1 = AddRef, slot 2 = Release (0x572620 assign, 0x61df40 ctor).
template <typename T>
struct RefPtr {
  T* p;
  RefPtr() : p(0) {}
  RefPtr(T* v) : p(v) { if (v) v->AddRef(); }
  ~RefPtr() { if (p) p->Release(); }
  void assign(T* v) {
    T* old = p;
    if (v) v->AddRef();
    p = v;
    if (old) old->Release();
  }
  RefPtr* Reset() {  // 0x00c463d0: release and zero, return this (used as an out-parameter)
    T* o = p;
    if (o) {
      p = 0;
      o->Release();
    }
    return this;
  }
};

namespace Internet {
// vtable: 0 dtor, 1 AddRef, 2 Release, 6 Abort (also discards), 20 AddFile, 21 AddField
class HTTPMultipartFormDataPostBodyStream {
 public:
  HTTPMultipartFormDataPostBodyStream();  // 0x00946dc0
  virtual ~HTTPMultipartFormDataPostBodyStream() {}
  virtual int AddRef();
  virtual int Release();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void Abort();
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
  virtual void v18();
  virtual void v19();
  virtual bool AddFile(const char* field, void* data, const char* contentType, const char* fileName, int flags);
  virtual bool AddField(const char* field, const char* value);
};
}  // namespace Internet
}  // namespace EA

namespace SP {
namespace Pollen {
struct IResponseHandler {  // sub-object at cServerResponse+8 (slot 1 AddRef, slot 2 Release)
  virtual ~IResponseHandler() {}
  virtual int AddRef();
  virtual int Release();
};

class cServerResponse : public EA::RefCountVTemplate<int> {
 public:
  cServerResponse();  // 0x00615790
  bool Open();        // 0x00615450
  IResponseHandler mHandler;  // +8
};
}  // namespace Pollen
}  // namespace SP

namespace EA {
namespace Internet {
class HTTPRequest {
 public:
  virtual ~HTTPRequest();
  int mRefCount;      // +4
  uint32_t pad[0x362];
  RefPtr<SP::Pollen::IResponseHandler> mpHandler;  // +0xd90
  const void* mpCallbacks;                          // +0xd94
  void SetField(const char* name, const char* value);        // 0x00944660
  void SetFieldStr(const string8& name, const string8& value);  // 0x00944a10
  static bool CreateHTTPPostRequest(const char* url, HTTPMultipartFormDataPostBodyStream* body, int flags,
                                    struct HTTPRequestRef* out);  // 0x00945b20 (cdecl)
};

// Holder with refcount at +4 of the pointee; 0x0060d240 resets (returns this), 0x0060d210 releases.
struct HTTPRequestRef {
  HTTPRequest* p;
  HTTPRequestRef() : p(0) {}
  HTTPRequestRef* Reset() {
    HTTPRequest* o = p;
    if (o) {
      p = 0;
      if (_InterlockedExchangeAdd((volatile long*)&o->mRefCount, -1) == 1) delete o;
    }
    return this;
  }
  ~HTTPRequestRef() { Reset(); }
  void AddRef() { _InterlockedExchangeAdd((volatile long*)&p->mRefCount, 1); }
};
}  // namespace Internet
}  // namespace EA

// ---- resource manager / graphics side (vtable slots only) -----------------------------------
struct ResKey {
  uint32_t mInstance, mType, mGroup;
  ResKey() : mInstance(0), mType(0), mGroup(0) {}
};

struct IResource {  // slot 1 = Release
  virtual int v0();
  virtual int Release();
};

class IThumbData : public EA::RefCountVTemplate<int> {  // slot 6 returns the PNG buffer
 public:
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* GetBuffer();
};

class IRecordSource {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual bool ReadInto(IResource* res, struct ResourceReadRequest* req, int a, uint32_t type);  // slot 10
  virtual void v11(); virtual void v12();
  virtual bool GetThumb(const ResKey* key, EA::RefPtr<IThumbData>* out, int a, int b, int c, int d);  // slot 13
};

class IResourceManager {
 public:
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual bool GetResource(const ResKey* key, IResource** out, int a, int b, int c, int d);  // slot 3
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void SaveResource(void* resource, int a, int b, int c, int d);  // slot 8
  virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual IRecordSource* GetDatabase(uint32_t type, int group);  // slot 18
  virtual void v19(); virtual void v20(); virtual void v21();
  virtual IRecordSource* FindSource(const ResKey* key);  // slot 22
};

namespace EA { namespace ResourceMan { IResourceManager* GetManager(); } }  // 0x0067dcd0

namespace Graphics {
class GraphicsFactoryAsyncRequest : public EA::RefCountVTemplate<int> {
 public:
  GraphicsFactoryAsyncRequest(int a, int b, const char* name);  // 0x0093c270
  void SetProperty(int id, float v);                             // 0x0093bb40
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9();
  virtual void Start(int a, int b);  // slot 10
};
}  // namespace Graphics

struct ResourceReadRequest {  // 0x008e2380 ctor / 0x008e2350 dtor
  uint32_t pad[9];
  ResourceReadRequest(int a, Graphics::GraphicsFactoryAsyncRequest* gfar, const ResKey* key, bool f1, bool f2);  // 0x008e2380
  ~ResourceReadRequest();  // 0x008e2350
};

namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  void UpdateExportThumb(const ResKey* key);  // 0x005fb430
};
cImportExport* GetImportExport();  // 0x005f7930
}  // namespace Thumbnail

namespace Pollen {
class cAssetMetadata {
 public:
  const uint64_t* GetAssetID();               // 0x005507a0
  const wchar_t* GetName();                   // 0x00414e10
  const wchar_t* GetSummary();                // 0x005508c0
  unsigned GetTagCount();                     // 0x005509b0
  const wchar_t* GetTag(unsigned i);          // 0x005509e0
  unsigned GetTraitCount();                   // 0x00550a30
  unsigned GetTrait(unsigned i);              // 0x00550a60
  const uint64_t* GetParentAssetID();         // 0x00550800
  const uint64_t* GetOriginalParentAssetID(); // 0x00550820
  void SetParentAssetID(uint64_t id);         // 0x00551b60
  void SetOriginalParentAssetID(uint64_t id); // 0x00551b80
};
struct cAssetDirectory;  // opaque

void GetParentServerID(cAssetMetadata* meta, uint64_t* parentId, uint64_t* originalParentId);  // 0x00552080 (cdecl)
void MapLookup(uint32_t hash, string8* out);                                                    // 0x00621460 (cdecl)

class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

extern const void* const kResponseCallbacks;  // 0x015206f0

class cModelUploadTransaction : public cITransaction {
 public:
  ResKey mKey;                     // +0x8
  cAssetMetadata* mpAssetMetadata; // +0x14
  cAssetDirectory* mpAssetDir;     // +0x18
  uint64_t mnNextAssetID;          // +0x20
  bool mbSlurp;                    // +0x28
  bool mbBound;                    // +0x29
  void OnFailure();                // 0x00615db0
  bool ConstructRequest(EA::Internet::HTTPRequest** ppRequest);
};

// @ 0x006196c0
bool cModelUploadTransaction::ConstructRequest(EA::Internet::HTTPRequest** ppRequest) {
  mnNextAssetID = *mpAssetMetadata->GetAssetID();
  if (mpAssetMetadata) {
    const uint64_t* idp = mpAssetMetadata->GetAssetID();
    if ((uint32_t)*idp != 0xffffffff || (uint32_t)(*idp >> 32) != 0xffffffff) {
      EA::Internet::HTTPMultipartFormDataPostBodyStream* stream =
          new ("Pollinator", 0, 0, 0, 0) EA::Internet::HTTPMultipartFormDataPostBodyStream;
      if (stream) stream->AddRef();

      uint32_t typeCode = mKey.mType;
      const char* contentType = "text/xml";
      unsigned numImages = 1;
      if (typeCode == 0x366a930d) {
        typeCode = 0xe22261b7;
        contentType = "application/x-gzip";
        numImages = 4;
      }

      string8 typeStr;
      string8 summaryStr;
      string8 nameStr;
      string8::sprintf(&nameStr, "%ls", mpAssetMetadata->GetName());
      string8::sprintf(&summaryStr, "%ls", mpAssetMetadata->GetSummary());
      string8::sprintf(&typeStr, "0x%08x", mKey.mType);

      if (!stream->AddField("TypeId", typeStr.mpBegin)) {
        OnFailure();
        return false;
      }

      bool idFailed;
      {
        string8 idStr;
        uint64_t id = *mpAssetMetadata->GetAssetID();
        string8::sprintf(&idStr, "%llu", id);
        idFailed = !stream->AddField("assetId", idStr.mpBegin);
      }
      if (idFailed) {
        OnFailure();
        return false;
      }

      if (summaryStr.mpBegin != summaryStr.mpEnd) {
        if (!stream->AddField("description", summaryStr.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      unsigned tagCount = mpAssetMetadata->GetTagCount();
      if (tagCount > 0) {
        string8 tags;
        string8::sprintf(&tags, "%ls", mpAssetMetadata->GetTag(0));
        for (unsigned i = 1; i < tagCount; ++i)
          string8::append_sprintf(&tags, ", %ls", mpAssetMetadata->GetTag(i));
        if (!stream->AddField("tags", tags.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      unsigned traitCount = mpAssetMetadata->GetTraitCount();
      if (traitCount > 0) {
        string8 traits;
        string8::sprintf(&traits, "0x%08x", mpAssetMetadata->GetTrait(0));
        for (unsigned i = 1; i < traitCount; ++i)
          string8::append_sprintf(&traits, ", 0x%08x", mpAssetMetadata->GetTrait(i));
        if (!stream->AddField("traitguids", traits.mpBegin)) {
          OnFailure();
          return false;
        }
      }

      IResourceManager* mgr = EA::ResourceMan::GetManager();
      IResource* pRes = 0;
      if (!mgr->GetResource(&mKey, &pRes, 0, 0, 0, 0)) {
        OnFailure();
        if (pRes) pRes->Release();
        return false;
      }

      EA::RefPtr<Graphics::GraphicsFactoryAsyncRequest> gfar;
      {
        Graphics::GraphicsFactoryAsyncRequest* g =
            new ("Pollinator", 0, 0, 0, 0) Graphics::GraphicsFactoryAsyncRequest(0, 0, "UTF/MemoryStream");
        gfar.assign(g);
      }
      Graphics::GraphicsFactoryAsyncRequest* gf = gfar.p;
      gf->SetProperty(1, 1.0f);
      gf->SetProperty(2, 2.0f);
      gf->Start(0, 0);

      void* ready = 0;
      {
        ResKey zeroKey;
        ResourceReadRequest req(0, gf, &zeroKey, false, false);
        IRecordSource* db = mgr->GetDatabase(mKey.mType, -1);
        if (db && db->ReadInto(pRes, &req, 0, typeCode)) {
          gf->Start(0, 0);
          ready = gf;
        }
      }
      if (!ready || !stream->AddFile("ModelData", ready, contentType, nameStr.mpBegin, 0)) {
        stream->Abort();
        OnFailure();
        if (pRes) pRes->Release();
        return false;
      }

      EA::RefPtr<IThumbData> pThumb;
      ResKey thumbKey = mKey;
      thumbKey.mType = 0x2f7d0004;
      IRecordSource* src = mgr->FindSource(&thumbKey);
      if (!src || !src->GetThumb(&thumbKey, pThumb.Reset(), 1, 6, 1, 0)) {
        stream->Abort();
        OnFailure();
        return false;
      }
      if (!stream->AddFile("ThumbnailData", pThumb.p->GetBuffer(), "image/png", nameStr.mpBegin, 0)) {
        stream->Abort();
        OnFailure();
        return false;
      }

      for (unsigned i = 0; i < numImages;) {
        ResKey imgKey;
        imgKey.mInstance = mKey.mInstance;
        imgKey.mType = mKey.mType;
        unsigned n = i + 1;
        imgKey.mGroup = mKey.mGroup ^ ((n ^ mKey.mGroup) & 0xff);
        imgKey.mType = 0x2f7d0004;
        IRecordSource* isrc = mgr->FindSource(&imgKey);
        bool have = isrc && isrc->GetThumb(&imgKey, pThumb.Reset(), 1, 6, 1, 0);
        if (!have && i == 0) {
          IRecordSource* fb = mgr->FindSource(&thumbKey);
          if (!fb || !fb->GetThumb(&thumbKey, pThumb.Reset(), 1, 6, 1, 0)) {
            stream->Abort();
            OnFailure();
            return false;
          }
          have = true;
        }
        if (have) {
          void* data = pThumb.p->GetBuffer();
          string8 field("ImageData");
          if (i != 0) string8::append_sprintf(&field, "_%d", n);
          if (!stream->AddFile(field.mpBegin, data, "image/png", nameStr.mpBegin, 0)) {
            stream->Abort();
            OnFailure();
            return false;
          }
        }
        i = n;
      }

      string8 url;
      MapLookup(0x5387572, &url);
      EA::Internet::HTTPRequestRef request;
      if (!EA::Internet::HTTPRequest::CreateHTTPPostRequest(url.mpBegin, stream, 0, request.Reset())) {
        stream->Abort();
        // locals unwind (request, url, ...), then the common failure tail below
      } else {
        request.AddRef();
        uint64_t parentId = 0xffffffffffffffffULL;
        uint64_t origParentId = 0xffffffffffffffffULL;
        GetParentServerID(mpAssetMetadata, &parentId, &origParentId);
        if ((uint32_t)parentId != 0xffffffff || (uint32_t)(parentId >> 32) != 0xffffffff) {
          if (parentId != mnNextAssetID) {
            string8 parentField("parent");
            string8 parentVal;
            request.p->SetFieldStr(parentField, string8::sprintf(&parentVal, "%llu", parentId));
          }
        }
        if (mpAssetMetadata) {
          const uint64_t* pp = mpAssetMetadata->GetParentAssetID();
          bool same = parentId == *pp;
          if (same) same = origParentId == *mpAssetMetadata->GetOriginalParentAssetID();
          if (!same) {
            mpAssetMetadata->SetParentAssetID(parentId);
            mpAssetMetadata->SetOriginalParentAssetID(origParentId);
            EA::ResourceMan::GetManager()->SaveResource(mpAssetMetadata, 0, 0, 0, 0);
            SP::Thumbnail::cImportExport* ie = SP::Thumbnail::GetImportExport();
            if (ie) ie->UpdateExportThumb(&mKey);
          }
        }
        request.p->SetField("slurp", mbSlurp ? "1" : "0");
        if (mbBound) request.p->SetField("bound", "1");

        cServerResponse* resp = new ("Pollinator", 0, 0, 0, 0) cServerResponse;
        EA::RefPtr<cServerResponse> respPtr(resp);
        resp->Open();
        request.p->mpHandler.assign(resp ? &resp->mHandler : 0);
        request.p->mpCallbacks = kResponseCallbacks;
        *ppRequest = request.p;
        return true;
      }
    }
  }
  OnFailure();
  return false;
}
}  // namespace Pollen
}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct ResourceReadRequest {
    ~ResourceReadRequest(); // 0x008e2350
    ResourceReadRequest(int, void*, void*, bool, bool); // 0x008e2380
};
}
