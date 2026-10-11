// Slice s008884b0 (0x8884b0..0x8894xx) -- SporeApp retail bytes.
//
// This address range is part of the EA shared framework (dev PDB UTFSpore_Win32.lib:
// EASTL / EA::Text / ResourceMan).  The linker placed EA::Text::EATextBreak functions
// next to EASTL container COMDATs instantiated by UTFSpore, so the slice is a mix:
//
//   * real EAWebKit EATextBreak.cpp source  (GetPrevCharBreak / GetNextLineBreak /
//     GetNextSoutheastAsianLineBreak) -- vendored read-only under
//     work/ext/EAWebKitSupportPackages; #included below.
//
//   * EASTL 3.02 template members instantiated by Spore with
//     EA::Allocator::EASTLCoreAllocator / CoreAllocatorAdapter<ICoreAllocator>.
//     Instead of transcribing compiler output we include the real EASTL headers and
//     explicitly instantiate the exact containers the game used; the compiler emits
//     the identical member functions.
//
//   * two Spore-local helpers that are not part of stock EASTL (0x888860, and the two
//     wrapper copy-constructors at 0x889400 / 0x889450), written out below.
//
// The retail build links the static CRT (/MT), which is what makes the memcpy/memmove
// call sites in the EASTL members resolve to the in-image helpers rather than the
// msvcr90 import table.  Compile flags: /O2 /MT /GS- /GR- /TP /arch:SSE
//
// Per-VA accounting is in manifest.txt / nonmatching.txt.
//
// ---- VA -> emitted symbol map -------------------------------------------------------
//  (0x8884b0)  EA::Text::CharacterBreakIterator::GetPrevCharBreak
//  (0x888500)  eastl::hashtable<uint, pair<const uint, String>, ...>::DoRehash
//  (0x8885b0)  eastl::basic_string<wchar_t, EASTLCoreAllocator>::RangeInitialize
//  (0x888620)  eastl::VectorBase<Node*, EASTLCoreAllocator>::VectorBase(size_type, allocator)
//  (0x888680)  eastl::basic_string<wchar_t, EASTLCoreAllocator>::append
//  (0x8887a0)  eastl::uninitialized_copy_impl<generic_iterator<String*>>
//  (0x888800)  eastl::uninitialized_copy_impl<String *, false_type>   (near miss)
//  (0x888860)  DestroyStringSpan (Spore helper)                       (byte-exact)
//  (0x888940)  eastl::vector<String, EASTLCoreAllocator>::DoDestroyValues
//  (0x888980)  eastl::vector<String, EASTLCoreAllocator>::DoRealloc
//  (0x8889d0)  eastl::copy_impl<0>::do_copy<String*>
//  (0x888a10)  eastl::copy_backward_impl<0>::do_copy<String*>
//  (0x888a50)  EA::Text::LineBreakIterator::GetNextSoutheastAsianLineBreak   (nonmatching)
//  (0x888ef0)  EA::Text::LineBreakIterator::GetNextLineBreak
//  (0x8891a0)  eastl::vector<String, EASTLCoreAllocator>::~vector
//  (0x8891f0)  eastl::vector<Node*, EASTLCoreAllocator>::DoInsertValue       (near miss)
//  (0x889300)  eastl::vector<String, EASTLCoreAllocator>::vector(const vector&)
//  (0x889380)  eastl::hashtable<...>::DoFreeNodes (hash_map<uint,vector<uint>>)  (byte-exact)
//  (0x889400)  eastl::pair<const uint, vector<uint>> copy-constructor            (byte-exact)
//  (0x889450)  eastl::pair<const uint, vector<uint>>(key, vector) constructor    (byte-exact)
// ------------------------------------------------------------------------------------

#include "types.h"

// The retail SporeApp EASTL emits `memcpy` for the trivially-copyable copy paths that
// this slice contains.  The vendored headers here route `eastl::copy` through `memmove`
// instead; redirect it so the emitted call matches the game's in-image memcpy helper.
#ifndef memmove
    #define memmove memcpy
#endif

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

// ------------------------------------------------------------------------------------
// Part 1 -- the real EAWebKit EATextBreak implementation.
// Reproduces 0x008884b0 (GetPrevCharBreak), 0x00888ef0 (GetNextLineBreak) and, as a
// retail variant, 0x00888a50 (GetNextSoutheastAsianLineBreak).
// ------------------------------------------------------------------------------------
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextBreak.cpp"

// ------------------------------------------------------------------------------------
// Part 2 -- explicit EASTL template instantiations.
//
// These are the exact container instantiations the UTFSpore translation units used:
//   * eastl::vector<EA::Text::String>     (String = basic_string<wchar_t, EASTLCoreAllocator>)
//   * eastl::vector<Node*>                (ResourceMan InternalDatabaseList::mDeleted)
//   * eastl::hash_map<uint, String>       (ResourceMan name database)
//   * eastl::basic_string<wchar_t>
// and the free algorithms uninitialized_copy / copy / copy_backward on String*.
// ------------------------------------------------------------------------------------
#include <EASTL/functional.h>
#include <EASTL/hash_map.h>
#include <EASTL/memory.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>

namespace RM
{
    struct Node;
}

typedef EA::Allocator::EASTLICoreAllocator RTAlloc;
typedef EA::Text::String RTString;
typedef eastl::vector<RTString, RTAlloc> RTStringVector;
typedef eastl::vector<RM::Node*, RTAlloc> RTNodeVector;
typedef eastl::hash_map<unsigned int, RTString, eastl::hash<unsigned int>,
                        eastl::equal_to<unsigned int>, RTAlloc> RTNameHashMap;

template class eastl::basic_string<EA::Text::Char, RTAlloc>;
template class eastl::vector<RTString, RTAlloc>;
template class eastl::vector<RM::Node*, RTAlloc>;
template class eastl::hash_map<unsigned int, RTString, eastl::hash<unsigned int>,
                               eastl::equal_to<unsigned int>, RTAlloc>;

// The word-break dictionary in this translation unit also instantiates a hash map whose
// value is a 4-byte-element vector, which produces the DoFreeNodes at 0x00889380.
typedef eastl::vector<unsigned int, RTAlloc> RTUintVector;
typedef eastl::hash_map<unsigned int, RTUintVector, eastl::hash<unsigned int>,
                        eastl::equal_to<unsigned int>, RTAlloc> RTUintMap;
typedef eastl::hash_map<unsigned int, RTNodeVector, eastl::hash<unsigned int>,
                        eastl::equal_to<unsigned int>, RTAlloc> RTNodeMap;
template class eastl::vector<unsigned int, RTAlloc>;
template class eastl::hash_map<unsigned int, RTUintVector, eastl::hash<unsigned int>,
                               eastl::equal_to<unsigned int>, RTAlloc>;
template class eastl::hash_map<unsigned int, RTNodeVector, eastl::hash<unsigned int>,
                               eastl::equal_to<unsigned int>, RTAlloc>;

// Force the plain (non-iterator-wrapper) uninitialized_copy<String*, String*>
// instantiation that the game emitted at 0x00888800.
template RTString* eastl::uninitialized_copy<RTString*, RTString*>(
    RTString*, RTString*, RTString*);

// ------------------------------------------------------------------------------------
// Part 3 -- Spore-local helper that stock EASTL does not expose as a symbol.
// ------------------------------------------------------------------------------------
namespace RT
{
    // @ 0x00888860
    // Used by eastl::vector<EA::Text::String>::erase on the multi-element path: walks
    // [first, last), destroys each String in place, and advances the destination cursor
    // by one element.  Returns the final destination pointer.
    RTString* DestroyStringSpan(RTString* first, RTString* last, RTString* dest)
    {
        for(; first != last; ++first, ++dest)
            first->~RTString();
        return dest;
    }
}

// ------------------------------------------------------------------------------------
// Address annotations for the library members above that are emitted by the explicit
// template instantiations (used by tools/difftest/equiv.py to locate the object symbol
// when the function is not byte-exact and therefore absent from manifest.txt).
//   @ 0x00888800  eastl::uninitialized_copy_impl        (raw String* iterator, near miss)
//   @ 0x00888a50  GetNextSoutheastAsianLineBreak         (EATextBreak retail variant)
//   @ 0x008891f0  DoInsertValue                          (vector<Node*>, near miss)
// ------------------------------------------------------------------------------------
