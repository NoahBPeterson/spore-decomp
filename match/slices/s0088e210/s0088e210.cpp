// Slice s0088e210 -- SporeApp retail bytes (EA::Text::FontServer translation unit).
//
// This range is the EA::Text::FontServer TU.  The retail build interleaved the FontServer
// methods with the EASTL fixed_list / fixed_hash_map / hashtable COMDATs that
// <EAText/EATextFontServer.h> instantiates (FontList, FaceSourceList, mFaceMap, and the
// family-substitution map), so the slice mixes FontServer methods and container members.
//
// Everything below is the real upstream EAWebKit EATextFontServer.cpp source, #included
// verbatim; the container members are the EASTL instantiations that source forces (default
// eastl::allocator).  Compiled with EATEXT_THREAD_SAFETY_ENABLED (retail's FontServer has
// its mMutex in this object) plus a minimal EAThread shim (Futex / AutoFutex / AtomicInt32)
// under work/match/scratch_s0088e210_inc.
//
// Byte-exact: none.
//
// The retail image was built from a different revision of this source than the vendored
// EAWebKit drop: retail EnumerateFonts copies the whole FaceSource by value each iteration,
// retail does not inline list::DoCreateNode / DoInsert, and the EASTL fixed_pool_base member
// order differs (retail FaceSource = 0xe0 bytes; the vendored header's is 0xe8), which shifts
// every fixed-container and FontServer offset.  So every function in the slice differs from
// this build.  Per-VA diff + difftest verdict are in nonmatching.txt.
//
// Identity of each address (retail image; names from the image cards / PDB):
//   (0x0088e210)  eastl::fixed_list<EA::Text::Font*,4,true>::fixed_list(const fixed_list&)
//   (0x0088e2a0)  eastl::list<EA::Text::FontServer::FaceSource,
//                              eastl::fixed_node_allocator<224,4,4,0,1,eastl::allocator> >::erase
//   (0x0088e350)  EA::Text::FontServer::EnumerateFonts
//   (0x0088e510)  eastl::fixed_list<EA::Text::FontServer::FaceSource,4,true>::fixed_list()
//   (0x0088e5a0)  eastl::list<FaceSource,...>::DoCreateNode(const FaceSource&)
//   (0x0088e620)  eastl::list<FaceSource,...>::DoInsert<ListIterator<FaceSource,...> >(...)
//   (0x0088e670)  eastl::fixed_hash_map<string16,string16,4,5,1,...>::fixed_hash_map(const&)
//   (0x0088e740)  eastl::list<FaceSource,...>::DoAssign<ListIterator<FaceSource,...> >(...)
//   (0x0088e800)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoFreeNode
//   (0x0088e860)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoFreeNodes
//   (0x0088e8f0)  eastl::hashtable<string16,pair<const string16,Face>,...>::erase
//   (0x0088e980)  eastl::fixed_list<EA::Text::FontServer::FaceSource,4,true>::fixed_list(const&)
//   (0x0088ea20)  EA::Text::FontServer::Shutdown
//   (0x0088ec60)  EA::Text::FontServer::RemoveFace
//   (0x0088ed20)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoCreateNode (value ctor)
//   (0x0088ed90)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoAllocateNode
//   (0x0088ee00)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoCreateNode
//   (0x0088ee50)  EA::Text::FontServer::~FontServer
//   (0x0088ef30)  eastl::fixed_hash_map<string16,Face,8,9,1,...>::fixed_hash_map(const&)
//   (0x0088f000)  eastl::hashtable<string16,pair<const string16,Face>,...>::DoInsertValue
//   (0x0088f0f0)  EA::Text::FontServer::FontServer(EA::Allocator::ICoreAllocator*)
//
// Compile flags: /O2 /MT /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc /Iscratch_s0088e210_inc

#include "types.h"

// The retail SporeApp EASTL emits `memcpy` for trivially-copyable copy paths; the
// vendored headers route eastl::copy through memmove.  Redirect so the call site
// matches the game's in-image memcpy helper.
#ifndef memmove
    #define memmove memcpy
#endif

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_THREAD_SAFETY_ENABLED 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextFontServer.cpp"
