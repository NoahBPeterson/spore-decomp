// src/game/UTFSpore_Win32/EAText.cpp -- EAText singleton access and float comparison.
// Singleton linkage/flow follows EAWebKit EAText.cpp; native offsets and calls are audited.
#include "EA/Text/FontServer.h"
#include "EA/Allocator/ICoreAllocator.h"
#include <new>
extern const char g_str_fontserver_name[];
namespace EA { namespace Text {
static FontServer* gpFontServer = 0;
static FontServer* gpFontServerAllocated = 0;
extern EA::Allocator::ICoreAllocator* gpCoreAllocator;
}}
// Allocator-aware placement construction, matching CORE_NEW's new/delete contract.
struct FontServerAllocation {
    FontServerAllocation() {}
};
inline void* operator new(size_t size, FontServerAllocation,
                          EA::Allocator::ICoreAllocator* allocator,
                          const char* name, unsigned flags,
                          unsigned alignment, unsigned offset) {
    return allocator->Alloc(size, name, flags, alignment, offset);
}
inline void operator delete(void* p, FontServerAllocation,
                            EA::Allocator::ICoreAllocator* allocator,
                            const char*, unsigned, unsigned, unsigned) {
    allocator->Free(p, 0);
}

// @ 0x008859f0
int FUN_008859f0(const float* a, const float* b)
{
    if (a[0] != b[0]) return b[0] > a[0];
    if (a[1] != b[1]) return b[1] > a[1];
    if (a[2] != b[2]) return b[2] > a[2];
    return b[3] > a[3];
}

// @ 0x00885a60
namespace EA { namespace Text {
FontServer* GetFontServer(bool bCreateIfNotFound)
{
    if (gpFontServer == 0 && bCreateIfNotFound) {
        if (gpFontServerAllocated == 0) {
            if (gpCoreAllocator == 0)
                gpCoreAllocator = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
            gpFontServerAllocated = new(FontServerAllocation(), gpCoreAllocator,
                                        g_str_fontserver_name, 0, 8, 0) FontServer(0);
        }
        gpFontServer = gpFontServerAllocated;
        gpFontServer->Init();
    }
    return gpFontServer;
}

}}
