// @ 0x0088bbb0
#include "game/types.h"
#include "EA/Text/FontServer.h"
#include "EA/IO/IStream.h"
#include <new>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_014281b8[];
extern "C" unsigned char g_0142e9fc[];

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
void* __cdecl AllocateFontStream(unsigned int, const char*, int, int, const char*, int);

namespace EA { namespace IO {
// The retail constructor has an additional allocation-name argument.
class MemoryStream : public IStream {
public:
    // Retail constructs it without an unwind frame: the ctor is declared nothrow.
    MemoryStream(void*, unsigned int, bool, bool, EA::Allocator::ICoreAllocator*, const char*) throw();
    unsigned char mStreamState[0x20];
};
} }

// @ 0x0088bbb0
bool EA::Text::FontServer::Init()
{
    // Retail has an extra word after the vptr, absent from the generated header.
    struct RetailPrefix {
        void* vtable;
        unsigned int reserved;
        bool mbInitialized;
        bool mbOTFEnabled;
        bool mbSmartFallbackEnabled;
        EA::Allocator::ICoreAllocator* mpCoreAllocator;
    };
    RetailPrefix* state = reinterpret_cast<RetailPrefix*>(this);
    void* mutex = reinterpret_cast<unsigned char*>(this) + 0x2fb0;
    EnterCriticalSection(mutex);
    if (!state->mbInitialized) {
        state->mbInitialized = true;
        const char* name = reinterpret_cast<const char*>(g_0142e9fc);
        void* memory = AllocateFontStream(0x24, name, 0, 0, 0, 0);
        EA::IO::MemoryStream* stream = memory ? new (memory) EA::IO::MemoryStream(
            reinterpret_cast<void*>(g_014281b8), 0x67c0, true, false,
            state->mpCoreAllocator, name) : 0;
        AddFace(stream, kFontTypeOutline);
    }
    LeaveCriticalSection(mutex);
    return true;
}
