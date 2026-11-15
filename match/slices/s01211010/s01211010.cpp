// Slice s01211010: compiler-generated MSVC 2008 /EHsc unwind/cleanup funclets from one large
// /O2 UI function (the cSPUILayoutElementBase-style element serializer at 0x01210e80..0x01212900).
// Every VA here starts mid-cleanup with `lea ecx,[ebp-N]; jmp <dtor|operator_delete>` or
// `push 0 x4; push <tag>; push [ebp-N]; call operator_delete__(0x00f47410); add esp,0x18; ret`,
// or a `??_M` vector-destructor iterator call. cl emits these while compiling the owning function,
// so no standalone C++ spelling yields the bare `lea ecx; jmp` thunk, and the implied __ehhandler
// FuncInfo records are unreachable from here too. The source below performs the identical cleanup
// sequence on the owning frame; see nonmatching.txt.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

// ---- cleanup helpers ------------------------------------------------------------------------------------
// EA allocator free: operator_delete__(p, tag, a, b, c, d)
extern "C" void __cdecl operator_delete__(void* p, const char* tag, int a, int b, int c, int d);   // 0x00f47410

// ??_M@YGXPAXIHP6EX0@Z@Z : _eh_vector_destructor_iterator_(ptr, elemSize, count, dtor)
extern "C" void __stdcall eh_vector_destructor_iterator(void* p, unsigned elemSize, int count, void (*dtor)(void*));   // 0x011e0b22

// __CxxFrameHandler3 tail (mov eax,FuncInfo; jmp __CxxFrameHandler3)
extern "C" int __cdecl eh_cxx_frame_handler(void* frame, void* record, void* context, void* dispatcher);   // 0x011e090c

// Tags pushed by the operator_delete__ chains.
extern "C" const char g_tagUI13eb8a4[];   // 0x013eb8a4
extern "C" const char g_tagUI140d6d0[];   // 0x0140d6d0
extern "C" const char g_tagUI140d6f4[];   // 0x0140d6f4

// ---- destructor / cleanup targets (one stub class per distinct address) ---------------------------------
struct T_72a180 { void d(); };   // 0x0072a180  eastl::VectorBase<Text::BmpTextureInfo*>::~VectorBase
struct T_6c12c0 { void d(); };   // 0x006c12c0
struct T_6c2ac0 { void d(); };   // 0x006c2ac0
struct T_472520 { void d(); };   // 0x00472520
struct T_4a9b10 { void d(); };   // 0x004a9b10  SP::AutoRefCountV<SP::cVirtualRefCounted>::~AutoRefCountV
struct T_a21bf0 { void d(); };   // 0x00a21bf0
struct T_c2e4e0 { void d(); };   // 0x00c2e4e0  UTFWin::ILayoutElement::SetSerializer
struct T_7a9610 { void d(); };   // 0x007a9610
struct T_7a41a0 { void d(); };   // 0x007a41a0
struct T_5725f0 { void d(); };   // 0x005725f0
struct T_73fdc0 { void d(); };   // 0x0073fdc0
struct T_7455d0 { void d(); };   // 0x007455d0
struct T_745340 { void d(); };   // 0x00745340
struct T_74a910 { void d(); };   // 0x0074a910
struct T_a16a20 { void d(); };   // 0x00a16a20
struct T_4e1bf0 { void d(); };   // 0x004e1bf0
struct T_7c6190 { void d(); };   // 0x007c6190
struct T_73a820 { void d(); };   // 0x0073a820
struct T_6ae110 { void d(); };   // 0x006ae110
struct T_41eb80 { void d(); };   // 0x0041eb80  RefVector::~RefVector

// ----------------------------------------------------------------------------------------------------------
// A representative funclet body: the operator_delete__ tail used by most of this slice. The owning
// function calls one of these per local that needs freeing on an unwind path.
// The frame pointer is the owning function's ebp; the object to free is at fp + offset.
typedef void* Frame;

static void __forceinline cleanup_delete(void* object, const char* tag)
{
    operator_delete__(object, tag, 0, 0, 0, 0);
}

// The `mov eax, FuncInfo; jmp __CxxFrameHandler3` handler record that follows a group of funclets. It is the
// last thing in such a function, and the original never runs a `ret` of its own after it.
static void __forceinline eh_handler_tail(void* funcInfo)
{
    eh_cxx_frame_handler(funcInfo, 0, 0, 0);
}

// What a call of a no-return function (the handler record's last instruction) leaves in eax. The
// owning function's own `ret` after it is never reached, so the source returns it.
extern "C" void RET_NOT_REACHED(int suppressed_and_therefore_unmangled);
void* RET_NOT_REACHED_V(int suppressed_and_therefore_unmangled);   // the same address, value result

// The two-argument entry of operator_delete__ (push p; mov edx,[esp+8]; push edx; call free): the tail
// an inlined `delete` leaves once the other four argument pushes are folded away.
extern "C" void __cdecl operator_delete_inline(void* p, const char* tag);   // 0x00f4740d

// ============================================================================================================
// @ 0x01211010  eastl::VectorBase<Text::BmpTextureInfo*> unwind chain
void* __cdecl s01211010_cleanup(Frame fp)
{
    ((T_72a180*)((char*)fp - 0x8c))->d();
    ((T_72a180*)((char*)fp - 0x54))->d();
    ((T_72a180*)((char*)fp - 0xc4))->d();
    ((T_6c12c0*)((char*)fp - 0x24c))->d();
    ((T_472520*)((char*)fp - 0x208))->d();
    ((T_4a9b10*)((char*)fp - 0x1b0))->d();
    ((T_a21bf0*)((char*)fp - 0x124))->d();
    ((T_6c2ac0*)((char*)fp - 0x24c))->d();
    ((T_c2e4e0*)((char*)fp - 0x20c))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211270
void* __cdecl s01211270_cleanup(Frame fp)
{
    ((T_7a41a0*)((char*)fp - 0x16c))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211360
void* __cdecl s01211360_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x54))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x01211400
void* __cdecl s01211400_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x4c))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x01211470
void* __cdecl s01211470_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x4c))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x012114d0  ~VectorBase at [ebp-0x20], then the -0x30 sub-object (three funclets)
void* __cdecl s012114d0_cleanup(Frame fp)
{
    ((T_4e1bf0*)((char*)fp - 0x20))->d();
    ((T_4e1bf0*)((char*)fp - 0x30))->d();
    ((T_4e1bf0*)((char*)fp - 0x30))->d();
    ((T_4e1bf0*)((char*)fp - 0x30))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211500
void* __cdecl s01211500_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x28))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x01211540  operator_delete__ on [ebp-0x20] (tag "Graphics"), then the -0x1c sub-object
void* __cdecl s01211540_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x20))[0], g_tagUI13eb8a4);
    ((T_4e1bf0*)((char*)fp - 0x1c))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211600
void* __cdecl s01211600_cleanup(Frame fp)
{
    ((T_7a41a0*)((char*)fp - 0x38))->d();
    return 0;
}

// ============================================================================================================
// @ 0x012116a0  three funclets in a row: inline dtor tails (mov ecx,[ebp-N]; jmp dtor) at -0x34
// and -0x30, then the handler record (mov eax,FuncInfo; jmp __CxxFrameHandler3).
void* __cdecl s012116a0_cleanup(Frame fp)
{
    ((T_7a41a0*)((char*)fp - 0x34))->d();
    ((T_7a41a0*)((char*)fp - 0x30))->d();
    eh_handler_tail((void*)0x014ff308);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01211750
void* __cdecl s01211750_cleanup(Frame fp)
{
    ((T_7a41a0*)((char*)fp - 0xac))->d();
    return 0;
}

// ============================================================================================================
// @ 0x012118d0
void* __cdecl s012118d0_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x14))[0];
    ((T_5725f0*)p)->d();
    ((T_7a41a0*)(p + 0x14))->d();
    ((T_73fdc0*)(p + 0x28))->d();
    ((T_7a41a0*)(p + 0x3c))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211980  ~T_6c12c0 at -0x44, then the operator_delete__ on [ebp-0x48] (tag "Graphics")
void* __cdecl s01211980_cleanup(Frame fp)
{
    ((T_6c12c0*)((char*)fp - 0x44))->d();
    cleanup_delete(((void**)((char*)fp - 0x48))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x012119b0  dtor of the object passed in [ebp+4] (three funclets), then the handler record.
void* __cdecl s012119b0_cleanup(Frame fp)
{
    ((T_7a9610*)((char*)fp + 4))->d();
    ((T_7a9610*)((char*)fp + 4))->d();
    ((T_7a9610*)((char*)fp + 4))->d();
    eh_handler_tail((void*)0x014ff678);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01211a70
void* __cdecl s01211a70_cleanup(Frame fp)
{
    ((T_6c12c0*)((char*)fp - 0xa8))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211b60
void* __cdecl s01211b60_cleanup(Frame fp)
{
    ((T_41eb80*)((char*)fp - 0x90))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211ba0  operator_delete__ on [ebp-0x10] (tag "Graphics/ModelManager/Animations"), then
// the ~T_7a9610 at -0x10 (release the held object) and handler FuncInfo 0x014ff8cc
void* __cdecl s01211ba0_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x10))[0], g_tagUI140d6d0);
    ((T_7a9610*)((char*)fp - 0x10))->d();
    eh_handler_tail((void*)0x014ff8cc);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01211c30  element at fp-0x10, sub-object +8 then +0x9c vector
void* __cdecl s01211c30_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x10))[0];
    ((T_745340*)(p + 8))->d();
    eh_vector_destructor_iterator(p + 0x9c, 4, 6, (void (*)(void*))0x0073a820);
    return 0;
}

// ============================================================================================================
// @ 0x01211c60
void* __cdecl s01211c60_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x14))[0];
    ((T_745340*)(p + 8))->d();
    eh_vector_destructor_iterator(p + 0x9c, 4, 6, (void (*)(void*))0x0073a820);
    return 0;
}

// ============================================================================================================
// @ 0x01211d00
void* __cdecl s01211d00_cleanup(Frame fp)
{
    eh_vector_destructor_iterator((char*)fp - 0x24, 4, 6, (void (*)(void*))0x0073a820);
    return 0;
}

// ============================================================================================================
// @ 0x01211d60  ~T_7455d0 at -0x28, then the AutoRefCountV at [ebp-0x2c], the release of
// [(ebp-0x2c object)+0x18] through operator_delete__, then the handler record.
// The delete is the inlined `push ecx; mov edx,[ebp+4]; push edx; call operator_delete__(p,[ebp+4]);
// add esp,8` tail, so it is spelled as the two-argument operator_delete__ entry at 0x00f4740d.
void* __cdecl s01211d60_cleanup(Frame fp)
{
    ((T_7455d0*)((char*)fp - 0x28))->d();
    ((T_4a9b10*)((char*)((void**)((char*)fp - 0x2c))[0]))->d();
    operator_delete_inline(((void**)((char*)((void**)((char*)fp - 0x2c))[0] + 0x18))[0], (const char*)fp);
    eh_handler_tail((void*)0x015003b0);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01211e10
void* __cdecl s01211e10_cleanup(Frame fp)
{
    ((T_7a9610*)((char*)fp - 0xc0))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211e50
void* __cdecl s01211e50_cleanup(Frame fp)
{
    ((T_4a9b10*)((char*)fp - 0x18))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01211f40  element at fp-0x10: ~AutoRefCountV, +4 AutoRefCountV, +8 T_7c6190, +0xc AutoRefCountV
void* __cdecl s01211f40_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x10))[0];
    ((T_a16a20*)p)->d();
    ((T_a16a20*)(p + 4))->d();
    ((T_7c6190*)(p + 8))->d();
    ((T_a16a20*)(p + 0xc))->d();
    return 0;
}

// ============================================================================================================
// @ 0x012120a0
void* __cdecl s012120a0_cleanup(Frame fp)
{
    ((T_74a910*)((char*)fp - 0x3a4))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01212160  element at fp-0x10: sub-object +4, 8 non-POD elements of 0x50 bytes
void* __cdecl s01212160_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x10))[0];
    ((T_a16a20*)p)->d();
    eh_vector_destructor_iterator(p + 4, 0x50, 8, (void (*)(void*))0x00747270);
    return 0;
}

// ============================================================================================================
// @ 0x012122f0
void* __cdecl s012122f0_cleanup(Frame fp)
{
    ((T_4a9b10*)((char*)fp + 8))->d();
    return 0;
}

// ============================================================================================================
// @ 0x01212350  operator_delete__ on [ebp-0x1c] (tag "Graphics"), then the ~T_7a9610 at -0x1c
// and handler FuncInfo 0x015000a0
void* __cdecl s01212350_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x1c))[0], g_tagUI13eb8a4);
    ((T_7a9610*)((char*)fp - 0x1c))->d();
    eh_handler_tail((void*)0x015000a0);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01212410  element at fp-0x10: ~AutoRefCountV, +4 ~AutoRefCountV, 4 elements of 4 bytes at +0x44
void* __cdecl s01212410_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x10))[0];
    ((T_a16a20*)p)->d();
    ((T_5725f0*)(p + 4))->d();
    eh_vector_destructor_iterator(p + 0x44, 4, 4, (void (*)(void*))0x007a9610);
    return 0;
}

// ============================================================================================================
// @ 0x012124d0
void* __cdecl s012124d0_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp - 0x10))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x01212530
void* __cdecl s01212530_cleanup(Frame fp)
{
    char* p = (char*)((void**)((char*)fp - 0x14))[0];
    ((T_a16a20*)p)->d();
    ((T_5725f0*)(p + 4))->d();
    eh_vector_destructor_iterator(p + 0x44, 4, 4, (void (*)(void*))0x007a9610);
    return 0;
}

// ============================================================================================================
// @ 0x01212620
void* __cdecl s01212620_cleanup(Frame fp)
{
    ((T_a21bf0*)((char*)fp - 0x3c))->d();
    cleanup_delete(((void**)((char*)fp - 0x40))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x01212660  two funclets releasing the outgoing arguments' objects at [ebp+8] and [ebp+0xc],
// then handler FuncInfo 0x015003ac
void* __cdecl s01212660_cleanup(Frame fp)
{
    ((T_6ae110*)((char*)fp + 8))->d();
    ((T_6ae110*)((char*)fp + 0xc))->d();
    eh_handler_tail((void*)0x015003ac);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x012126a0
void* __cdecl s012126a0_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp + 4))[0], g_tagUI13eb8a4);
    return 0;
}

// ============================================================================================================
// @ 0x012126f0  operator_delete__ on [ebp+8] (tag "Graphics"), then the ~T_7a9610 at +8
// and handler FuncInfo 0x01500450
void* __cdecl s012126f0_cleanup(Frame fp)
{
    cleanup_delete(((void**)((char*)fp + 8))[0], g_tagUI13eb8a4);
    ((T_7a9610*)((char*)fp + 8))->d();
    eh_handler_tail((void*)0x01500450);
    return RET_NOT_REACHED_V(0);
}

// ============================================================================================================
// @ 0x01212740
void* __cdecl s01212740_cleanup(Frame fp)
{
    ((T_4a9b10*)((char*)fp + 0x1c))->d();
    cleanup_delete(((void**)((char*)fp - 0x18))[0], g_tagUI13eb8a4);
    return 0;
}
