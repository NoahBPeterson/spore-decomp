// @ 0x00894be0
#include "game/types.h"

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void*);

namespace EA {
namespace Allocator { class ICoreAllocator; }
namespace Text {
Allocator::ICoreAllocator* GetAllocator(); // 0x008859d0

// The retail fixed hash map occupies 0xf0 bytes. Its constructor is
// external, so its internal buckets and node pool remain opaque here.
struct StyleMap {
    struct Hash {};
    struct Equal {};
    StyleMap(const Hash&, const Equal&); // 0x00894b10
    unsigned char storage[0xf0];
};

class StyleManager {
public:
    StyleManager(Allocator::ICoreAllocator* pCoreAllocator);
    virtual ~StyleManager();
private:
    unsigned int mReserved;
    Allocator::ICoreAllocator* mpCoreAllocator;
    StyleMap mStyleMap;
    unsigned int mnNextStyleId;
    unsigned char mMutex[24];
};

// @ 0x00894be0
// Both stateless map policies are constructed in the dead stack slot of
// pCoreAllocator in retail: the two reference arguments are that one address.
// Each policy is empty, so the second one is modelled at the same slot with its
// byte offset spelled out (sizeof(Hash) then back by sizeof(Equal), both 1);
// that keeps the second address a separate expression, as in the original,
// instead of letting the compiler reuse the first one.
StyleManager::StyleManager(Allocator::ICoreAllocator* pCoreAllocator)
    : mpCoreAllocator(pCoreAllocator ? pCoreAllocator : GetAllocator()),
      mStyleMap(*(StyleMap::Hash*)&pCoreAllocator,
                *(StyleMap::Equal*)((char*)&pCoreAllocator - sizeof(StyleMap::Hash) + sizeof(StyleMap::Equal))),
      mnNextStyleId(1)
{
    InitializeCriticalSection(mMutex);
}
}}
