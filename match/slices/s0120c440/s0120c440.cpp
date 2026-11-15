// Batch bfs4 slice s0120c440, 0x0120c440-0x0120e110.
//
// Every VA in this slice is a compiler-generated MSVC EH cleanup funclet: the entry
// reads the *caller's* frame via EBP ([ebp-N] locals / [ebp+4] args) and tail-jumps into
// RAII destructors (eastl::basic_string::DeallocateSelf, eastl::vector<...>::~vector,
// rbtree DoNukeSubtree, operator_delete, MutexLock::~MutexLock, ...). They are the
// try/catch/scope-exit fragments of enclosing functions whose bodies are outside this
// slice, so they cannot be reconstructed from the fragment alone. Each VA is modelled
// here as the identical cleanup sequence applied to the owning frame; see
// nonmatching.txt.
#include "types.h"

typedef void* Frame;

extern "C" {
void __cdecl operator_delete__(void* p, const char* tag, int a, int b, int c, int d);       // 0x00f47410
void __cdecl tagged_delete_00926060(void* p, const char* tag, int a, int b, int c, int d);  // 0x00926060
void __cdecl free_two_00c2e4e0(void* a, void* b);                                           // 0x00c2e4e0
void __cdecl ehvec_dtor_011e0b22(void* p, unsigned int elemSize, int count, void* dtor);    // 0x011e0b22

extern const char g_tag_1402f7c[];   // 0x01402f7c
extern const char g_tag_1402f4c[];   // 0x01402f4c
extern const char g_tag_1402f30[];   // 0x01402f30
extern const char g_tag_13ebc58[];   // 0x013ebc58
extern const char g_tag_13f09b4[];   // 0x013f09b4
extern const char g_tag_14037fc[];   // 0x014037fc
extern const char g_tag_1403858[];   // 0x01403858
extern const char g_tag_140816c[];   // 0x0140816c
extern const char g_tag_14082bc[];   // 0x014082bc
extern const char g_tag_1408270[];   // 0x01408270
extern const char g_tag_1408eb8[];   // 0x01408eb8
extern const char g_tag_1409138[];   // 0x01409138
extern const char g_tag_1409120[];   // 0x01409120
extern const char g_tag_1409108[];   // 0x01409108
extern const char g_tag_14090f4[];   // 0x014090f4
extern const char g_tag_1409528[];   // 0x01409528
extern const char g_tag_1409508[];   // 0x01409508
extern const char g_tag_1409548[];   // 0x01409548
}

struct T_931e70 { void d(); };
struct T_6855f0 { void d(); };
struct T_4a9b10 { void d(); };
struct T_540520 { void d(); };
struct T_7c6190 { void d(); };
struct T_69d350 { void d(); };
struct T_686320 { void d(); };
struct T_933960 { void d(); };
struct T_615bb0 { void d(); };
struct T_5f96c0 { void d(); };
struct T_57cb80 { void d(); };
struct T_6862f0 { void d(); };
struct T_553e00 { void d(); };
struct T_a16a20 { void d(); };
struct T_5725f0 { void d(); };
struct T_7a9610 { void d(); };
struct T_689810 { void d(); };
struct T_554b10 { void d(); };
struct T_571ee0 { void d(); };
struct T_6b05c0 { void d(); };
struct T_697b70 { void d(); };
struct T_530670 { void d(); };
struct T_68f420 { void d(); };
struct T_922130 { void d(); };
struct T_68a710 { void d(); };
struct T_a65a90 { void d(); };
struct T_685980 { void d(); };
struct T_69d1c0 { void d(); };
struct T_5725a0 { void d(); };
struct T_69eb40 { void d(); };
struct T_69eb50 { void d(); };
struct T_7455d0 { void d(); };
struct T_6b5240 { void d(); };
struct T_41e5d0 { void d(); };
struct T_4e1bf0 { void d(); };
struct T_553b90 { void d(); };
struct T_7a41a0 { void d(); };
struct T_837fa0 { void d(); };
struct T_4cddd0 { void d(); };
struct T_4748c0 { void d(); };
struct T_41e090 { void d(); };
struct T_41e730 { void d(); };
struct T_72a180 { void d(); };
struct T_421cf0 { void d(); };
struct T_6abf10 { void d(); };
struct T_6a5f40 { void d(); };
struct T_6aadd0 { void d(); };
struct T_6aae00 { void d(); };
struct T_93b5a0 { void d(); };
struct T_6abe00 { void d(); };
struct T_7c8490 { void d(); };
struct T_6abed0 { void d(); };
struct T_6ad580 { void d(); };
struct T_a21bf0 { void d(); };

// lea ecx,[ebp+N]; jmp <dtor>
template <class T> static inline void Clean(Frame fp, int off)
{ ((T*)((char*)fp + off))->d(); }

// mov ecx,[ebp+N]; jmp <dtor>
template <class T> static inline void CleanPtr(Frame fp, int off)
{ ((T*)*(void**)((char*)fp + off))->d(); }

// mov ecx,[ebp+N]; add ecx,M; jmp <dtor>
template <class T> static inline void CleanPtrAdd(Frame fp, int off, int add)
{ ((T*)((char*)*(void**)((char*)fp + off) + add))->d(); }

// push 0 x4; push tag; push [ebp+N]; call operator_delete__ 0x00f47410
static inline void Del(Frame fp, int off, const char* tag)
{ operator_delete__(*(void**)((char*)fp + off), tag, 0, 0, 0, 0); }

// push 0 x4; push tag; push [ebp+N]; call 0x00926060
static inline void DelTagged(Frame fp, int off, const char* tag)
{ tagged_delete_00926060(*(void**)((char*)fp + off), tag, 0, 0, 0, 0); }

// @ 0x0120c440  (FuncInfo 0x014f9b0c)
void FUN_0120c440(Frame fp)
{
    Clean<T_931e70>(fp, -0x238);
    DelTagged(fp, -0x240, g_tag_1402f7c);
    Clean<T_6855f0>(fp, -0x240);
    DelTagged(fp, -0x23c, g_tag_1402f4c);
    Del(fp, -0x23c, g_tag_1402f30);
}

// @ 0x0120c550  (FuncInfo 0x014f9c28)
void FUN_0120c550(Frame fp)
{
    Clean<T_4a9b10>(fp, -0x2d0);
    Clean<T_540520>(fp, -0x26c);
    Clean<T_7c6190>(fp, -0x290);
    Clean<T_69d350>(fp, -0x2c4);
    Del(fp, -0x2c0, g_tag_13ebc58);
    Clean<T_69d350>(fp, -0x2c8);
    Clean<T_686320>(fp, -0x24c);
    Clean<T_933960>(fp, -0x2ac);
    Clean<T_933960>(fp, -0x27c);
}

// @ 0x0120c5d0  (FuncInfo 0x014f9c94)
void FUN_0120c5d0(Frame fp)
{
    Clean<T_69d350>(fp, -0x34);
    DelTagged(fp, 8, g_tag_1402f4c);
    Clean<T_615bb0>(fp, -0x30);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x1c);
}

// @ 0x0120c640  (FuncInfo 0x014f9d2c)
void FUN_0120c640(Frame fp)
{
    Clean<T_5f96c0>(fp, -0x270);
    Clean<T_57cb80>(fp, -0x220);
    DelTagged(fp, -0x274, g_tag_1402f4c);
    Clean<T_615bb0>(fp, -0x274);
}

// @ 0x0120c690  (FuncInfo 0x014f9d50)
void FUN_0120c690(Frame fp)
{
    Clean<T_6862f0>(fp, -0x13c);
    Clean<T_6862f0>(fp, -0xa4);
    Clean<T_933960>(fp, -0x15c);
    Clean<T_933960>(fp, -0x15c);
    Clean<T_933960>(fp, -0x15c);
    DelTagged(fp, -0x148, g_tag_13ebc58);
    Clean<T_615bb0>(fp, -0x148);
}

// @ 0x0120c700  (FuncInfo 0x014f9dac)
void FUN_0120c700(Frame fp)
{
    Clean<T_933960>(fp, -0x78);
    Clean<T_933960>(fp, -0x68);
    Clean<T_933960>(fp, -0x58);
    Clean<T_553e00>(fp, -0x20);
    Clean<T_553e00>(fp, -0x8c);
    Clean<T_553e00>(fp, -0x48);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0xb4);
    Clean<T_933960>(fp, -0x30);
}

// @ 0x0120c7c0  (FuncInfo 0x014f9e74)
void FUN_0120c7c0(Frame fp)
{
    int flags = *(int*)((char*)fp - 0x10);
    if ((flags & 1) != 0)
    {
        *(int*)((char*)fp - 0x10) = flags & ~1;
        CleanPtr<T_933960>(fp, 4);
    }
}

// @ 0x0120c7f0  (FuncInfo 0x014f9e98)
void FUN_0120c7f0(Frame fp)
{
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x3c);
    Clean<T_933960>(fp, -0x4c);
    Clean<T_933960>(fp, -0x1c);
    DelTagged(fp, -0x58, g_tag_13f09b4);
    Clean<T_615bb0>(fp, -0x54);
    DelTagged(fp, -0x50, g_tag_13f09b4);
}

// @ 0x0120c860  (FuncInfo 0x014f9ef4)
void FUN_0120c860(Frame fp)
{
    Clean<T_933960>(fp, -0x3c);
    Clean<T_933960>(fp, -0x4c);
    Clean<T_933960>(fp, -0x6c);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x5c);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x1c);
}

// @ 0x0120c930  (FuncInfo 0x014fa00c)
void FUN_0120c930(Frame fp)
{
    CleanPtrAdd<T_a16a20>(fp, -0x10, 0);
    CleanPtrAdd<T_5725f0>(fp, -0x10, 4);
    CleanPtrAdd<T_a16a20>(fp, -0x14, 0);
    CleanPtrAdd<T_7a9610>(fp, -0x14, 0x20);
    CleanPtrAdd<T_689810>(fp, -0x10, 0x10);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x38);
}

// @ 0x0120c9c0  (FuncInfo 0x014fa0c8)
void FUN_0120c9c0(Frame fp)
{
    CleanPtr<T_554b10>(fp, -0x20);
    Clean<T_933960>(fp, -0x1c);
}

// @ 0x0120c9e0  (FuncInfo 0x014fa0f4)
void FUN_0120c9e0(Frame fp)
{
    free_two_00c2e4e0(*(void**)((char*)fp - 0x10),
                      (char*)*(void**)((char*)fp - 0x14) + 0x10);
}

// @ 0x0120cab0  (FuncInfo 0x014fa218)
void FUN_0120cab0(Frame fp)
{
    Clean<T_933960>(fp, -0x40);
    Clean<T_571ee0>(fp, -0x20);
    Clean<T_571ee0>(fp, -0x20);
    Clean<T_933960>(fp, -0x30);
}

// @ 0x0120cc30  (FuncInfo 0x014fa3d8)
void FUN_0120cc30(Frame fp)
{
    CleanPtrAdd<T_6b05c0>(fp, -0x10, 8);
    CleanPtrAdd<T_6b05c0>(fp, -0x10, 0x24);
}

// @ 0x0120cdd0  (FuncInfo 0x014fa5d8)
void FUN_0120cdd0(Frame fp)
{
    Clean<T_697b70>(fp, -0x14);
    Del(fp, -0x10, g_tag_14037fc);
}

// @ 0x0120ce00  (FuncInfo 0x014fa5fc)
void FUN_0120ce00(Frame fp)
{
    CleanPtr<T_68f420>(fp, -0x10);
    CleanPtrAdd<T_922130>(fp, -0x10, 8);
    CleanPtrAdd<T_a65a90>(fp, -0x10, 0x3c);
    CleanPtrAdd<T_a65a90>(fp, -0x10, 0x44);
    ehvec_dtor_011e0b22((char*)*(void**)((char*)fp - 0x10) + 0x4c, 8, 9,
                        (void*)0x00a65a90);
}

// @ 0x0120cea0  (FuncInfo 0x014fa6b8)
void FUN_0120cea0(Frame fp)
{
    Del(fp, -0x20, g_tag_1403858);
    Clean<T_697b70>(fp, -0x20);
    Clean<T_530670>(fp, -0x1c);
}

// @ 0x0120cf90  (FuncInfo 0x014fa7bc)
void FUN_0120cf90(Frame fp)
{
    CleanPtrAdd<T_7a9610>(fp, -0x10, 4);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 8);
}

// @ 0x0120d0e0  (FuncInfo 0x014fa980)
void FUN_0120d0e0(Frame fp)
{
    Del(fp, -0x110, g_tag_140816c);
    Clean<T_933960>(fp, -0x154);
    Clean<T_57cb80>(fp, -0x144);
    Clean<T_57cb80>(fp, -0x144);
    Clean<T_57cb80>(fp, -0x144);
    Clean<T_57cb80>(fp, -0x144);
}

// @ 0x0120d190  (FuncInfo 0x014faa3c)
void FUN_0120d190(Frame fp)
{
    Clean<T_933960>(fp, -0x398);
    Clean<T_933960>(fp, -0x354);
    Clean<T_7c6190>(fp, -0x334);
    Clean<T_685980>(fp, -0x3ac);
    Clean<T_540520>(fp, -0x3c4);
    Clean<T_615bb0>(fp, -0x39c);
    Clean<T_5f96c0>(fp, -0x388);
    Clean<T_57cb80>(fp, -0x320);
    DelTagged(fp, -0x3d4, g_tag_1402f4c);
    Clean<T_615bb0>(fp, -0x3cc);
    Clean<T_615bb0>(fp, -0x3d4);
    DelTagged(fp, -0x3d4, g_tag_1402f4c);
    Clean<T_615bb0>(fp, -0x3d4);
    Clean<T_615bb0>(fp, -0x3cc);
    free_two_00c2e4e0(*(void**)((char*)fp - 0x3c8),
                      (char*)*(void**)((char*)fp - 0x3b0) + 8);
    Clean<T_57cb80>(fp, -0x388);
    Clean<T_57cb80>(fp, -0x388);
}

// @ 0x0120d2c0  (FuncInfo 0x014fab2c)
void FUN_0120d2c0(Frame fp)
{
    Clean<T_57cb80>(fp, -0x40);
    Clean<T_540520>(fp, -0x54);
    Clean<T_7a9610>(fp, 4);
}

// @ 0x0120d2f0  (FuncInfo 0x014fab70)
void FUN_0120d2f0(Frame fp)
{
    Del(fp, -0x10, g_tag_14082bc);
    Del(fp, -0x10, g_tag_1408270);
    Clean<T_7a9610>(fp, -0x14);
    Clean<T_7a9610>(fp, -0x10);
}

// @ 0x0120d5a0  (FuncInfo 0x014fae6c)
void FUN_0120d5a0(Frame fp)
{
    CleanPtrAdd<T_a16a20>(fp, -0x14, 0);
    CleanPtrAdd<T_69d1c0>(fp, -0x14, 4);
    CleanPtrAdd<T_5725a0>(fp, -0x14, 0x10);
    CleanPtrAdd<T_615bb0>(fp, -0x14, 0x18);
    CleanPtrAdd<T_7a9610>(fp, -0x14, 0x1c);
    Del(fp, -0x10, g_tag_13ebc58);
}

// @ 0x0120d620  (FuncInfo 0x014faf0c)
void FUN_0120d620(Frame fp)
{
    Clean<T_69eb40>(fp, -0x58);
    Clean<T_69eb50>(fp, -0x34);
    Clean<T_7a9610>(fp, -0x70);
    Clean<T_7455d0>(fp, -0x6c);
}

// @ 0x0120d750  (FuncInfo 0x014fb074)
void FUN_0120d750(Frame fp)
{
    Clean<T_530670>(fp, -0x1bc);
    Clean<T_933960>(fp, -0x1ac);
    Clean<T_6b5240>(fp, -0x58);
    Clean<T_571ee0>(fp, -0x84);
    Clean<T_571ee0>(fp, -0x174);
    Clean<T_571ee0>(fp, -0xd4);
    Clean<T_571ee0>(fp, -0x14c);
    Clean<T_571ee0>(fp, -0x19c);
    Clean<T_571ee0>(fp, -0x124);
    Clean<T_571ee0>(fp, -0xac);
    Clean<T_571ee0>(fp, -0xfc);
    Clean<T_571ee0>(fp, -0x98);
    Clean<T_571ee0>(fp, -0x188);
    Clean<T_571ee0>(fp, -0x160);
    Clean<T_571ee0>(fp, -0x138);
    Clean<T_571ee0>(fp, -0x110);
    Clean<T_571ee0>(fp, -0xe8);
    Clean<T_571ee0>(fp, -0xc0);
}

// @ 0x0120d840  (FuncInfo 0x014fb164)
void FUN_0120d840(Frame fp)
{
    CleanPtr<T_554b10>(fp, -0x20);
    Clean<T_530670>(fp, -0x1c);
}

// @ 0x0120d860  (FuncInfo 0x014fb188)
void FUN_0120d860(Frame fp)
{
    Clean<T_530670>(fp, -0x380);
    Clean<T_933960>(fp, -0x450);
    Clean<T_933960>(fp, -0x3f0);
    Clean<T_571ee0>(fp, -0x500);
    Clean<T_41e5d0>(fp, -0x678);
    Clean<T_571ee0>(fp, -0x5dc);
    Clean<T_4e1bf0>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x5b4);
    Clean<T_4e1bf0>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x618);
    Clean<T_4e1bf0>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x5a0);
    Clean<T_553b90>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x58c);
    Clean<T_553e00>(fp, -0x69c);
    Clean<T_933960>(fp, -0x4b0);
    Clean<T_571ee0>(fp, -0x53c);
    Clean<T_7a41a0>(fp, -0x69c);
    Clean<T_837fa0>(fp, -0x65c);
    Clean<T_933960>(fp, -0x4c0);
    Clean<T_571ee0>(fp, -0x564);
    Clean<T_540520>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x604);
    Clean<T_4cddd0>(fp, -0x678);
    Clean<T_571ee0>(fp, -0x5f0);
    Clean<T_540520>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x5c8);
    Clean<T_4748c0>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x578);
    Clean<T_540520>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x550);
    Clean<T_7a41a0>(fp, -0x69c);
    Clean<T_571ee0>(fp, -0x514);
    Clean<T_41e090>(fp, -0x678);
    Clean<T_837fa0>(fp, -0x65c);
    Clean<T_571ee0>(fp, -0x4ec);
    Clean<T_41e730>(fp, -0x678);
    Clean<T_837fa0>(fp, -0x2a0);
    Clean<T_571ee0>(fp, -0x528);
}

// @ 0x0120da20  (FuncInfo 0x014fb2e4)
void FUN_0120da20(Frame fp)
{
    Clean<T_7c6190>(fp, -0x4038);
    Clean<T_685980>(fp, -0x4088);
    Clean<T_72a180>(fp, -0x4024);
    Clean<T_540520>(fp, -0x4054);
    Clean<T_7a9610>(fp, -0x4040);
    Clean<T_69d350>(fp, -0x4098);
    Clean<T_4a9b10>(fp, -0x4058);
    Del(fp, -0x4090, g_tag_1408eb8);
    Clean<T_4a9b10>(fp, -0x4094);
}

// @ 0x0120dac0  (FuncInfo 0x014fb37c)
void FUN_0120dac0(Frame fp)
{
    Clean<T_530670>(fp, -0x88);
    Clean<T_933960>(fp, -0xc8);
    Clean<T_530670>(fp, -0x98);
    Clean<T_6b5240>(fp, -0xc8);
    Clean<T_6b5240>(fp, -0xc8);
    Clean<T_933960>(fp, -0xc8);
    Clean<T_530670>(fp, -0xa8);
}

// @ 0x0120db60  (FuncInfo 0x014fb424)
void FUN_0120db60(Frame fp)
{
    Clean<T_4a9b10>(fp, -0x10);
    Clean<T_571ee0>(fp, -0x8c);
    Clean<T_421cf0>(fp, -0x50);
    Clean<T_530670>(fp, -0x8c);
    Clean<T_530670>(fp, -0x60);
    Clean<T_530670>(fp, -0x70);
    Clean<T_421cf0>(fp, -0x50);
}

// @ 0x0120dbb0  (FuncInfo 0x014fb480)
void FUN_0120dbb0(Frame fp)
{
    Clean<T_4a9b10>(fp, -0x3c);
    Del(fp, -0x3c, g_tag_1409138);
    Del(fp, -0x3c, g_tag_1409120);
    Del(fp, -0x3c, g_tag_1409108);
    Del(fp, -0x3c, g_tag_14090f4);
    Clean<T_933960>(fp, -0x1c);
    Clean<T_530670>(fp, -0x2c);
    Del(fp, -0x3c, g_tag_13ebc58);
    Del(fp, -0x3c, g_tag_13ebc58);
}

// @ 0x0120dc70  (FuncInfo 0x014fb50c)
void FUN_0120dc70(Frame fp)
{
    Clean<T_69d350>(fp, -0x48);
    Clean<T_530670>(fp, -0x40);
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_530670>(fp, -0x30);
}

// @ 0x0120dce0  (FuncInfo 0x014fb598)
void FUN_0120dce0(Frame fp)
{
    CleanPtrAdd<T_6abf10>(fp, -0x10, 4);
    CleanPtrAdd<T_7c6190>(fp, -0x10, 0xc);
    CleanPtrAdd<T_68a710>(fp, -0x10, 0x20);
    CleanPtrAdd<T_686320>(fp, -0x10, 0x3c);
    CleanPtrAdd<T_6a5f40>(fp, -0x10, 0x74);
    CleanPtrAdd<T_6aadd0>(fp, -0x10, 0x94);
    CleanPtrAdd<T_6aae00>(fp, -0x10, 0xb4);
    CleanPtrAdd<T_6aadd0>(fp, -0x10, 0xd4);
    CleanPtrAdd<T_6aae00>(fp, -0x10, 0xf4);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x114);
    CleanPtrAdd<T_6aadd0>(fp, -0x10, 0x128);
    CleanPtrAdd<T_6aae00>(fp, -0x10, 0x148);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x168);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x178);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x17c);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x180);
}

// @ 0x0120ddc0  (FuncInfo 0x014fb660)
void FUN_0120ddc0(Frame fp)
{
    Clean<T_933960>(fp, -0x28);
    Clean<T_530670>(fp, -0x3c);
    Clean<T_69d350>(fp, -0x14);
    Clean<T_93b5a0>(fp, -0x70);
}

// @ 0x0120de80  (FuncInfo 0x014fb774)
void FUN_0120de80(Frame fp)
{
    free_two_00c2e4e0(*(void**)((char*)fp - 0x10),
                      (char*)*(void**)((char*)fp - 0x14) + 8);
}

// @ 0x0120df00  (FuncInfo 0x014fb824)
void FUN_0120df00(Frame fp)
{
    Clean<T_7a9610>(fp, -0x2c);
    Clean<T_6abe00>(fp, 4);
    Clean<T_7a9610>(fp, 8);
    Clean<T_a21bf0>(fp, -0x1c);
}

// @ 0x0120df50  (FuncInfo 0x014fb8b4)
void FUN_0120df50(Frame fp)
{
    Clean<T_7c8490>(fp, -0x424);
    Clean<T_6abe00>(fp, -0x444);
}

// @ 0x0120dfb0  (FuncInfo 0x014fb950)
void FUN_0120dfb0(Frame fp)
{
    CleanPtr<T_6abf10>(fp, -0x30);
    Clean<T_6abed0>(fp, -0x2c);
    CleanPtrAdd<T_6ad580>(fp, -0x30, 0xc);
}

// @ 0x0120e0a0  (FuncInfo 0x014fba98)
void FUN_0120e0a0(Frame fp)
{
    Clean<T_6855f0>(fp, -0x14);
    DelTagged(fp, -0x10, g_tag_1409528);
    Del(fp, -0x10, g_tag_1409508);
}

// @ 0x0120e110  (FuncInfo 0x014fbb08)
void FUN_0120e110(Frame fp)
{
    Clean<T_697b70>(fp, -0x14);
    Del(fp, -0x10, g_tag_1409548);
    Clean<T_7a9610>(fp, 0xc);
}
