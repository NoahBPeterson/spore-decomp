// Slice s008894a0 (0x8894a0..0x88a50b) - EA::Text GlyphCache / FontServer support.
//
// This region is the original EAWebKit EAText source (vendored under
// work/ext/EAWebKitSupportPackages) plus the EASTL instantiations it forces. None of these
// functions reproduce the retail build byte-for-byte, because the vendored EAWebKit drop uses
// a different allocator/template configuration; the complete upstream implementations are
// included here and the residual byte diffs are recorded in nonmatching.txt.
//
// @ 0x008894a0  eastl::vector<GlyphTextureInfo>::operator= / assign
// @ 0x00889610  EA::Text::GlyphCache::TryAllocateTextureArea
// @ 0x008897a0  fixed_hash_map<string,string,...>::fixed_hash_map
// @ 0x00889880  basic_string<...>::RangeInitialize
// @ 0x00889900  EA::Text::FontServer::FontServer
// @ 0x008899b0  EA::Text::GlyphCache::TryAllocateTextureArea
// @ 0x00889b40  EA::Text::FontServer::AddFace
// @ 0x00889c10  list<FontServer::FaceSource>::erase
// @ 0x00889c80  EA::Text::GlyphCache::SetOption
// @ 0x00889d90  EA::Text::GlyphCache::TryAllocateTextureArea
// @ 0x00889f10  fixed_list<FontServer::FaceSource,...>::fixed_list
// @ 0x00889fc0  EA::IO::MemoryStream::`scalar deleting destructor'
// @ 0x0088a000  basic_string<...>::set_capacity
// @ 0x0088a0f0  EA::Text::FontServer::AddSubstitution
// @ 0x0088a240  EA::Text::GlyphCache::ClearTextureInternal
// @ 0x0088a2b0  EA::Text::GlyphCache::SetAllocator
// @ 0x0088a2c0  EA::Text::GlyphCache::Init
// @ 0x0088a330  fixed_hash_map<string,FontServer::Face,...>::fixed_hash_map
// @ 0x0088a420  EA::Text::GlyphCache::~GlyphCache

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

#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextCache.cpp"
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextFontServer.cpp"
