// slice s005f8fe0 -- SP::Thumbnail::cImportExport import/export helpers and eastl string/hash
// glue. Partial: bodies below are skeletons (signatures/names recovered, logic not reconstructed).
#include "types.h"

#include <stdarg.h>
namespace eastl {
template <typename T>
class basic_string {
 public:
  basic_string* append_sprintf(const char* fmt, ...);
  void append_sprintf_va_list(const char* fmt, va_list* args);  // 0x00475930
  char pad[16];
};
}  // namespace eastl

namespace EA {
namespace Locale {
bool MakeLocaleAvailable(const void* p, const void* q);  // 0x0087d9a0
}
}  // namespace EA

void FUN_005f8690(void* a, void* b);   // 0x005f8690
void FUN_005f8700(void* a, void* b);   // 0x005f8700
void FUN_005f8770();                    // 0x005f8770
void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, int c, int d);  // 0xf473a0
void EASTL_allocator_deallocate(void* p);  // 0x00f47380

namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  void SetupExportFolderPath();  // 0x005f9310
};
}  // namespace Thumbnail
}  // namespace SP

namespace eastl {
template class basic_string<char>;
// @ 0x005F9450
basic_string<char>* basic_string<char>::append_sprintf(const char* fmt, ...) {
  append_sprintf_va_list(fmt, (va_list*)(&fmt + 1));
  return this;
}
}  // namespace eastl

// @ 0x005F8FE0
void FUN_005f8fe0() {}
// @ 0x005F9080
void FUN_005f9080() {}
// @ 0x005F90C0
void FUN_005f90c0() {}
// @ 0x005F9100
void FUN_005f9100() {}
// @ 0x005F9230
void FUN_005f9230() {}
// @ 0x005F9310
void SP::Thumbnail::cImportExport::SetupExportFolderPath() {}
// @ 0x005F9470
void FUN_005f9470() {}
// @ 0x005F95A0
void FUN_005f95a0() {}
// @ 0x005F9680
void FUN_005f9680() {}
// @ 0x005F96C0
void FUN_005f96c0() {}
// @ 0x005F9760
void FUN_005f9760() {}
// @ 0x005F97C0
void FUN_005f97c0() {}
