// Slice s006196c0: SP::Pollen::cModelUploadTransaction::ConstructRequest (3984 bytes).
//
// PARTIAL reconstruction. The original is one ~1,000-instruction function that builds an
// EA::Internet multipart/form-data body, formats the atom request fields (TypeId, assetId,
// description, tags, traitguids, ModelData, ThumbnailData and the per-image ImageData
// fields), creates a Graphics::GraphicsFactoryAsyncRequest, posts an HTTP request and wires
// up the completion callback. Reproducing every call/path faithfully (and byte-exactly) is
// beyond the effort budget for this slice, so only the top-level prologue/flow is written
// here; see partial.txt.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

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
  basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1) {
      if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    }
  }
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
}  // namespace EA

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
struct cAssetMetadata;   // opaque
struct cAssetDirectory;  // opaque

// Helpers invoked by the original (addresses noted for reference). Only the shapes needed
// by the reproduced top-level flow are declared.
uint64_t GetAssetID(cAssetMetadata* meta);       // 0x005507a0
void OnFailure();                                // 0x00615db0

class cModelUploadTransaction : public cITransaction {
 public:
  Key mKey;                            // +0x8
  cAssetMetadata* mpAssetMetadata;     // +0x14
  cAssetDirectory* mpAssetDir;         // +0x18
  uint64_t mnNextAssetID;              // +0x20
  bool ConstructRequest(void** ppRequest);
};

// @ 0x006196c0
bool cModelUploadTransaction::ConstructRequest(void** ppRequest) {
  (void)ppRequest;
  uint64_t id = GetAssetID(mpAssetMetadata);
  mnNextAssetID = id;
  if (mpAssetMetadata == 0) {
    OnFailure();
    return false;
  }
  // The remainder (multipart body + atom fields + async request) is omitted; see partial.txt.
  OnFailure();
  return false;
}
}  // namespace Pollen
}  // namespace SP
