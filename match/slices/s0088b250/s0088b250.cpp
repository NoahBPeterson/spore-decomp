// Slice s0088b250 (0x88b250..0x88c559) - EA::Text FontServer / Font / GlyphCache.
//
// This region is the original EAWebKit EAText/EAIO source (vendored under
// work/ext/EAWebKitSupportPackages), together with the EASTL container instantiations it
// forces. Two functions reproduce this retail build exactly (listed in manifest.txt); the
// remainder are present as the same complete upstream implementation but differ from retail
// because the vendored drop uses a different allocator/config (see nonmatching.txt).
//
// Byte-exact:  0088b850 (?IsFilePathSeparator@IO@EA@@YA_NH@Z)
//              0088b8a0 (?GetSystemFontDirectory@Text@EA@@YAIPA_WI@Z)
//
// @ 0x0088b250  EA::Text::GlyphCache::AddTextureInfo            (upstream source, non-identical)
// @ 0x0088b450  hashtable<string,pair<...>>::DoAllocateNode
// @ 0x0088b500  hashtable<string,pair<...>>::DoFreeNode
// @ 0x0088b560  eastl::allocator::deallocate
// @ 0x0088b580  pair<...,FontServer::Face>::~pair
// @ 0x0088b5b0  EA::Text::GetFontTypeFromFilePath
// @ 0x0088b600  fixed_node_allocator<...>::fixed_node_allocator
// @ 0x0088b640  EA::IO::EntryFindFirst
// @ 0x0088b850  EA::IO::IsFilePathSeparator                          BYTE-EXACT
// @ 0x0088b870  basic_string<...>::basic_string
// @ 0x0088b8a0  EA::Text::GetSystemFontDirectory                    BYTE-EXACT
// @ 0x0088b930  list<Font*>::DoAssign
// @ 0x0088b9a0  EA::IO::EATextFileStream::EATextFileStream
// @ 0x0088b9e0  EA::Text::FontServer::GetFontDescriptionScore
// @ 0x0088bb20  hashtable<...>::erase
// @ 0x0088bbb0  basic_string<...>::RangeInitialize
// @ 0x0088be70  hashtable<...>::DoRehash          (Face map)
// @ 0x0088bf40  hashtable<...>::DoRehash          (string map)
// @ 0x0088c010  hashtable<...>::DoFindNode
// @ 0x0088c050  fixed_list<Font*,4,1>::fixed_list
// @ 0x0088c0d0  basic_string<...>::assign
// @ 0x0088c170  EA::Text::FontServer::AddFace
// @ 0x0088c380  basic_string<...>::AllocateSelf
// @ 0x0088c500  list<Font*>::erase

#include "types.h"

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

#include "../../../work/ext/EAWebKitSupportPackages/EAIOEAWebKit/local/source/EAFileDirectory.cpp"
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextFontServer.cpp"
