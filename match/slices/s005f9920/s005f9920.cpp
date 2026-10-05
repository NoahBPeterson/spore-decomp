// slice s005f9920 -- SP::Thumbnail::cImportExport image/import-table routines plus hashtable
// bucket teardown helpers. Large routines below are skeletons (partial); the two bucket-clear
// helpers are reconstructed attempts.
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

namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  void WriteAssetDataToImage();  // 0x005f9920
  void RestoreImportTable();     // 0x005fa290
};
}  // namespace Thumbnail
}  // namespace SP

// @ 0x005F9920
void SP::Thumbnail::cImportExport::WriteAssetDataToImage() { /* partial */ }
// @ 0x005FA100
void FUN_005fa100() { /* partial (hash insert) */ }
// @ 0x005FA290
void SP::Thumbnail::cImportExport::RestoreImportTable() { /* partial */ }
