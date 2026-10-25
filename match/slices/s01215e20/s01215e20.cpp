// Batch gold1 slice s01215e20, 0x01215e20-0x01217570.
//
// Every VA in this slice is a compiler-generated MSVC EH cleanup funclet: the entry
// reads the *caller's* frame via EBP ([ebp-N] locals / [ebp+N] args) and either tail-jumps
// into a RAII destructor/deallocator (eastl::basic_string<...>::~basic_string,
// SpVec::DeallocateSelf, eastl::vector<...>::~vector, AutoRefCount::release, Holder::~Holder,
// UTFWin::ILayoutElement::SetSerializer, ...) or calls operator_delete(ptr, file, line, ...)
// for arrays, then ends with `mov eax,<TI descriptor>; jmp 0x11e090c` (the C++ EH handler).
// They are the try/catch/scope-exit fragments of enclosing functions whose bodies are
// outside this slice, so the enclosing source cannot be reconstructed from the fragment
// alone.  Following the s0120ae50 precedent, every VA is modelled as the identical,
// ordered cleanup sequence applied to a pointer to the owning frame: the compiler-assigned
// local/argument slots are named by offset (the owning frame layout belongs to the
// out-of-slice function, so those slots cannot be given source field names).  The trailing
// `mov eax,<FuncInfo>; jmp __CxxFrameHandler3` record is not callable in isolation and is
// noted per function instead of being executed.  Every VA is recorded in nonmatching.txt.
#include "types.h"

// ---------------------------------------------------------------------------
// cleanup machinery reached by the fragments
// ---------------------------------------------------------------------------
extern "C" void __cdecl operator_delete__(void* p, const char* tag,
                                          int a, int b, int c, int d);       // 0x00f47410
extern "C" void __cdecl operator_delete_00926060(void* p, const char* tag,
                                                 int a, int b, int c, int d); // 0x00926060
extern "C" void __cdecl free_two_00c2e4e0(void* a, void* b);                 // 0x00c2e4e0

// type-name tags passed to the tagged deallocators
extern "C" const char g_tag13ebc58[];   // 0x013ebc58
extern "C" const char g_tag1412ecc[];   // 0x01412ecc
extern "C" const char g_tag1412ea8[];   // 0x01412ea8
extern "C" const char g_tag1412e84[];   // 0x01412e84
extern "C" const char g_tag1412e60[];   // 0x01412e60
extern "C" const char g_tag1412e3c[];   // 0x01412e3c
extern "C" const char g_tag1412e18[];   // 0x01412e18
extern "C" const char g_tag14134d0[];   // 0x014134d0
extern "C" const char g_tag14134c0[];   // 0x014134c0
extern "C" const char g_tag14134ac[];   // 0x014134ac
extern "C" const char g_tag1413498[];   // 0x01413498
extern "C" const char g_tag1413484[];   // 0x01413484
extern "C" const char g_tag141346c[];   // 0x0141346c
extern "C" const char g_tag1413454[];   // 0x01413454
extern "C" const char g_tag1413444[];   // 0x01413444
extern "C" const char g_tag141342c[];   // 0x0141342c
extern "C" const char g_tag141341c[];   // 0x0141341c
extern "C" const char g_tag1413404[];   // 0x01413404
extern "C" const char g_tag14133f0[];   // 0x014133f0
extern "C" const char g_tag14133dc[];   // 0x014133dc
extern "C" const char g_tag14133c8[];   // 0x014133c8
extern "C" const char g_tag14133b4[];   // 0x014133b4
extern "C" const char g_tag14133a0[];   // 0x014133a0
extern "C" const char g_tag1414554[];   // 0x01414554
extern "C" const char g_tag1414540[];   // 0x01414540
extern "C" const char g_tag141452c[];   // 0x0141452c
extern "C" const char g_tag1414518[];   // 0x01414518
extern "C" const char g_tag1414504[];   // 0x01414504
extern "C" const char g_tag14144ec[];   // 0x014144ec
extern "C" const char g_tag14144d4[];   // 0x014144d4
extern "C" const char g_tag14144bc[];   // 0x014144bc
extern "C" const char g_tag14144a8[];   // 0x014144a8
extern "C" const char g_tag1414490[];   // 0x01414490
extern "C" const char g_tag141447c[];   // 0x0141447c
extern "C" const char g_tag1414848[];   // 0x01414848
extern "C" const char g_tag1414830[];   // 0x01414830
extern "C" const char g_tag1414810[];   // 0x01414810
extern "C" const char g_tag14147f4[];   // 0x014147f4
extern "C" const char g_tag14147e0[];   // 0x014147e0
extern "C" const char g_tag141b18c[];   // 0x0141b18c

// one placeholder per distinct destructor target (all out-of-slice)
struct T_4e1bf0 { void d(); };   // 0x004e1bf0
struct T_7a9610 { void d(); };   // 0x007a9610
struct T_7a4c90 { void d(); };   // 0x007a4c90
struct T_7051d0 { void d(); };   // 0x007051d0
struct T_7d4660 { void d(); };   // 0x007d4660
struct T_73a820 { void d(); };   // 0x0073a820
struct T_530670 { void d(); };   // 0x00530670
struct T_a21380 { void d(); };   // 0x00a21380
struct T_540520 { void d(); };   // 0x00540520
struct T_7c6190 { void d(); };   // 0x007c6190
struct T_4a9b10 { void d(); };   // 0x004a9b10
struct T_5a2300 { void d(); };   // 0x005a2300
struct T_5725f0 { void d(); };   // 0x005725f0
struct T_a16a20 { void d(); };   // 0x00a16a20
struct T_7e2680 { void d(); };   // 0x007e2680
struct T_7e3250 { void d(); };   // 0x007e3250
struct T_7c65e0 { void d(); };   // 0x007c65e0
struct T_7e27a0 { void d(); };   // 0x007e27a0
struct T_6aadd0 { void d(); };   // 0x006aadd0
struct T_4b5440 { void d(); };   // 0x004b5440
struct T_572ab0 { void d(); };   // 0x00572ab0
struct T_67e0f0 { void d(); };   // 0x0067e0f0
struct T_69d350 { void d(); };   // 0x0069d350
struct T_571ee0 { void d(); };   // 0x00571ee0
struct T_933960 { void d(); };   // 0x00933960
struct T_7c4000 { void d(); };   // 0x007c4000
struct T_931e70 { void d(); };   // 0x00931e70
struct T_7eb7b0 { void d(); };   // 0x007eb7b0
struct T_421cf0 { void d(); };   // 0x00421cf0
struct T_7455d0 { void d(); };   // 0x007455d0
struct T_a23920 { void d(); };   // 0x00a23920
struct T_936740 { void d(); };   // 0x00936740
struct T_553e00 { void d(); };   // 0x00553e00
struct T_7e6690 { void d(); };   // 0x007e6690
struct T_76e1e0 { void d(); };   // 0x0076e1e0
struct T_429480 { void d(); };   // 0x00429480
struct T_5477e0 { void d(); };   // 0x005477e0
struct T_83f8f0 { void d(); };   // 0x0083f8f0
struct T_6b5240 { void d(); };   // 0x006b5240

// the frame pointer handed to a cleanup funclet by the EH machinery
typedef void* Frame;

// read one compiler-assigned slot of the owning frame (negative = local,
// positive = incoming argument)
static inline void* Slot(Frame fp, int off)
{ return *(void**)((char*)fp + off); }

template <class T> static inline void Clean(Frame fp, int off)              // lea ecx,[ebp+N]; jmp dtor
{ ((T*)((char*)fp + off))->d(); }
template <class T> static inline void CleanPtr(Frame fp, int off)           // mov ecx,[ebp+N]; jmp dtor
{ ((T*)Slot(fp, off))->d(); }
template <class T> static inline void CleanPtrAdd(Frame fp, int off, int add)   // mov ecx,[ebp+N]; add ecx,M; jmp dtor
{ ((T*)((char*)Slot(fp, off) + add))->d(); }
static inline void Del(Frame fp, int off, const char* tag)                  // push 0 x4; push tag; push [ebp+N]; call
{ operator_delete__(Slot(fp, off), tag, 0, 0, 0, 0); }
static inline void DelOther(Frame fp, int off, const char* tag)
{ operator_delete_00926060(Slot(fp, off), tag, 0, 0, 0, 0); }

// ---------------------------------------------------------------------------
// reconstructed cleanup chains
// ---------------------------------------------------------------------------

// @ 0x01215e20  (fragments: two destructor thunks, FuncInfo 0x01503d94)
void Unwind_01215e20(Frame fp)
{
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x64);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0xa0);
}

// @ 0x01215ef0  (two-pointer free, FuncInfo 0x01503e7c)
void Unwind_01215ef0(Frame fp)
{
    free_two_00c2e4e0(Slot(fp, -0x10), Slot(fp, 0x0c));
}

// @ 0x01215f30  (four tagged deletes, four destructor thunks, FuncInfo 0x01503ecc and 0x01503f28)
void Unwind_01215f30(Frame fp)
{
    Del(fp, 0x10, g_tag13ebc58);
    Clean<T_7a9610>(fp, 0x14);
    Del(fp, -0x54, g_tag13ebc58);
    Clean<T_7d4660>(fp, -0x4c);
    Del(fp, 0x10, g_tag13ebc58);
    Clean<T_73a820>(fp, 0x10);
    Clean<T_73a820>(fp, -0x24);
}

// @ 0x01216090  (two destructor thunks, FuncInfo 0x01504068 and 0x01504094)
void Unwind_01216090(Frame fp)
{
    Clean<T_530670>(fp, -0xc0);
    Clean<T_a21380>(fp, -0xa8);
    Clean<T_4e1bf0>(fp, -0x40);
}

// @ 0x01216110  (three destructor thunks and a tagged delete, FuncInfo 0x01504130)
void Unwind_01216110(Frame fp)
{
    Clean<T_540520>(fp, -0x20);
    Clean<T_7c6190>(fp, -0x38);
    Clean<T_4a9b10>(fp, -0x4c);
    Del(fp, -0x44, g_tag13ebc58);
}

// @ 0x01216170  (seven destructor thunks, FuncInfo 0x01504188)
void Unwind_01216170(Frame fp)
{
    Clean<T_4e1bf0>(fp, -0x48);
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_4e1bf0>(fp, -0x48);
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_4e1bf0>(fp, -0x48);
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_4e1bf0>(fp, -0x34);
}

// @ 0x012161c0  (seven destructor thunks, FuncInfo 0x015041e4)
void Unwind_012161c0(Frame fp)
{
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_4e1bf0>(fp, -0x48);
    Clean<T_4e1bf0>(fp, -0x70);
    Clean<T_4e1bf0>(fp, -0x84);
    Clean<T_4e1bf0>(fp, -0x5c);
    Clean<T_4e1bf0>(fp, -0x34);
    Clean<T_4e1bf0>(fp, -0x98);
}

// @ 0x01216210  (eleven destructor thunks off one object pointer, FuncInfo 0x01504240)
void Unwind_01216210(Frame fp)
{
    CleanPtr<T_5a2300>(fp, -0x10);
    CleanPtrAdd<T_5725f0>(fp, -0x10, 0x08);
    CleanPtrAdd<T_4a9b10>(fp, -0x10, 0x10);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x14);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x30);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x44);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x58);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x6c);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x80);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x138);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x14c);
}

// @ 0x012162a0  (six tagged deletes of the first argument, FuncInfo 0x015042bc)
void Unwind_012162a0(Frame fp)
{
    Del(fp, 0x08, g_tag1412ecc);
    Del(fp, 0x08, g_tag1412ea8);
    Del(fp, 0x08, g_tag1412e84);
    Del(fp, 0x08, g_tag1412e60);
    Del(fp, 0x08, g_tag1412e3c);
    Del(fp, 0x08, g_tag1412e18);
}

// @ 0x01216400  (sixteen tagged deletes of the first argument, FuncInfo 0x015043d0)
void Unwind_01216400(Frame fp)
{
    Del(fp, 0x08, g_tag14134d0);
    Del(fp, 0x08, g_tag14134c0);
    Del(fp, 0x08, g_tag14134ac);
    Del(fp, 0x08, g_tag1413498);
    Del(fp, 0x08, g_tag1413484);
    Del(fp, 0x08, g_tag141346c);
    Del(fp, 0x08, g_tag1413454);
    Del(fp, 0x08, g_tag1413444);
    Del(fp, 0x08, g_tag141342c);
    Del(fp, 0x08, g_tag141341c);
    Del(fp, 0x08, g_tag1413404);
    Del(fp, 0x08, g_tag14133f0);
    Del(fp, 0x08, g_tag14133dc);
    Del(fp, 0x08, g_tag14133c8);
    Del(fp, 0x08, g_tag14133b4);
    Del(fp, 0x08, g_tag14133a0);
}

// @ 0x012166f0  (sixteen destructor thunks off one object pointer, FuncInfo 0x01504648)
void Unwind_012166f0(Frame fp)
{
    CleanPtr<T_a16a20>(fp, -0x10);
    CleanPtrAdd<T_7c6190>(fp, -0x10, 0x04);
    CleanPtrAdd<T_5725f0>(fp, -0x10, 0x08);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x18);
    CleanPtrAdd<T_7e2680>(fp, -0x10, 0x2c);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x90);
    CleanPtrAdd<T_7e3250>(fp, -0x10, 0xa4);
    CleanPtrAdd<T_7c65e0>(fp, -0x10, 0xb8);
    CleanPtrAdd<T_7e27a0>(fp, -0x10, 0xd8);
    CleanPtrAdd<T_6aadd0>(fp, -0x10, 0xf8);
    CleanPtrAdd<T_4b5440>(fp, -0x10, 0x118);
    CleanPtrAdd<T_4b5440>(fp, -0x10, 0x12c);
    CleanPtrAdd<T_572ab0>(fp, -0x10, 0x140);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x154);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x158);
    CleanPtrAdd<T_67e0f0>(fp, -0x10, 0x15c);
}

// @ 0x01216810  (nine destructor thunks off one object pointer, FuncInfo 0x01504754)
void Unwind_01216810(Frame fp)
{
    CleanPtr<T_a16a20>(fp, -0x10);
    CleanPtrAdd<T_7c6190>(fp, -0x10, 0x04);
    CleanPtrAdd<T_5725f0>(fp, -0x10, 0x08);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x18);
    CleanPtrAdd<T_7e2680>(fp, -0x10, 0x2c);
    CleanPtrAdd<T_4e1bf0>(fp, -0x10, 0x90);
    CleanPtrAdd<T_7e3250>(fp, -0x10, 0xa4);
    CleanPtrAdd<T_7c65e0>(fp, -0x10, 0xb8);
    CleanPtrAdd<T_7e27a0>(fp, -0x10, 0xd8);
}

// @ 0x01216890  (six tagged deletes, FuncInfo 0x015047c0)
void Unwind_01216890(Frame fp)
{
    Del(fp, -0x10, g_tag13ebc58);
    Del(fp, -0x10, g_tag13ebc58);
    Del(fp, -0x10, g_tag13ebc58);
    Del(fp, -0x10, g_tag13ebc58);
    Del(fp, -0x10, g_tag13ebc58);
    Del(fp, 0x04, g_tag13ebc58);
}

// @ 0x01216960  (five tagged deletes, three destructor thunks, one more tagged
//                delete, then three tagged deletes of the first argument;
//                FuncInfo 0x01504840)
void Unwind_01216960(Frame fp)
{
    Del(fp, -0x30, g_tag13ebc58);
    Del(fp, -0x30, g_tag13ebc58);
    Del(fp, -0x30, g_tag13ebc58);
    Del(fp, -0x30, g_tag13ebc58);
    Del(fp, -0x30, g_tag13ebc58);
    Clean<T_69d350>(fp, -0x3c);
    Del(fp, -0x3c, g_tag13ebc58);
    Clean<T_4a9b10>(fp, -0x38);
    Clean<T_571ee0>(fp, -0x20);
    Del(fp, 0x04, g_tag13ebc58);
    Del(fp, 0x04, g_tag13ebc58);
    Del(fp, 0x04, g_tag13ebc58);
}

// @ 0x01216a90  (two destructor thunks, then thirty destructor thunks off one
//                object pointer; FuncInfo 0x01504900 and 0x01504924)
void Unwind_01216a90(Frame fp)
{
    Clean<T_933960>(fp, -0x190);
    Clean<T_7c4000>(fp, -0x180);
    CleanPtr<T_a16a20>(fp, -0x10);
    CleanPtrAdd<T_7c6190>(fp, -0x10, 0x04);
    CleanPtrAdd<T_5725f0>(fp, -0x10, 0x08);
    CleanPtrAdd<T_69d350>(fp, -0x10, 0x24);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x2c);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x30);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x34);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x3c);
    CleanPtrAdd<T_7a4c90>(fp, -0x10, 0x48);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x5c);
    CleanPtrAdd<T_7051d0>(fp, -0x10, 0x60);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x64);
    CleanPtrAdd<T_7455d0>(fp, -0x10, 0x88);
    CleanPtrAdd<T_a23920>(fp, -0x10, 0xa0);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0xc8);
    CleanPtrAdd<T_4a9b10>(fp, -0x10, 0xcc);
    CleanPtrAdd<T_936740>(fp, -0x10, 0xd0);
    CleanPtrAdd<T_933960>(fp, -0x10, 0x128);
    CleanPtrAdd<T_933960>(fp, -0x10, 0x138);
    CleanPtrAdd<T_933960>(fp, -0x10, 0x148);
    CleanPtrAdd<T_553e00>(fp, -0x10, 0x174);
    CleanPtrAdd<T_7e6690>(fp, -0x10, 0x18c);
    CleanPtrAdd<T_7a9610>(fp, -0x10, 0x190);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x194);
    CleanPtrAdd<T_530670>(fp, -0x10, 0x1a4);
}

// @ 0x01216c00  (four destructor thunks, FuncInfo 0x01504a30)
void Unwind_01216c00(Frame fp)
{
    Clean<T_933960>(fp, -0x3c);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_933960>(fp, -0x1c);
    Clean<T_530670>(fp, -0x1c);
}

// @ 0x01216c30  (eleven destructor thunks, FuncInfo 0x01504a54)
void Unwind_01216c30(Frame fp)
{
    Clean<T_933960>(fp, -0x1454);
    Clean<T_933960>(fp, -0x14c4);
    Clean<T_933960>(fp, -0x1474);
    Clean<T_933960>(fp, -0x14b4);
    Clean<T_933960>(fp, -0x14a4);
    Clean<T_933960>(fp, -0x14b4);
    Clean<T_933960>(fp, -0x1494);
    Clean<T_933960>(fp, -0x14b4);
    Clean<T_933960>(fp, -0x14b4);
    Clean<T_933960>(fp, -0x1484);
    Clean<T_933960>(fp, -0x1464);
}

// @ 0x01216cf0  (two destructor thunks, three tagged deletes of one slot through
//                two different deallocators, three more destructor thunks;
//                FuncInfo 0x01504afc)
void Unwind_01216cf0(Frame fp)
{
    Clean<T_933960>(fp, -0x270);
    Clean<T_933960>(fp, -0x250);
    Del(fp, -0x284, g_tag13ebc58);
    DelOther(fp, -0x284, g_tag13ebc58);
    Del(fp, -0x284, g_tag13ebc58);
    Clean<T_933960>(fp, -0x280);
    Clean<T_933960>(fp, -0x260);
    Clean<T_933960>(fp, -0x21c);
}

// @ 0x01216df0  (six destructor thunks, FuncInfo 0x01504be0)
void Unwind_01216df0(Frame fp)
{
    Clean<T_553e00>(fp, -0x34);
    Clean<T_4e1bf0>(fp, -0x20);
    Clean<T_4e1bf0>(fp, -0x34);
    Clean<T_4a9b10>(fp, 0x04);
    Clean<T_6b5240>(fp, -0x20);
    Clean<T_933960>(fp, -0x44);
}

// @ 0x01216e30  (three tagged deletes and two destructor thunks, FuncInfo 0x01504c34)
void Unwind_01216e30(Frame fp)
{
    Del(fp, -0x30, g_tag13ebc58);
    Clean<T_933960>(fp, -0x2c);
    Clean<T_530670>(fp, -0x1c);
    Del(fp, 0x04, g_tag13ebc58);
    Del(fp, 0x04, g_tag13ebc58);
}

// @ 0x01216ea0  (two destructor thunks then one more, FuncInfo 0x01504c90 and 0x01504cbc)
void Unwind_01216ea0(Frame fp)
{
    Clean<T_933960>(fp, -0x248);
    Clean<T_931e70>(fp, -0x238);
    CleanPtr<T_7eb7b0>(fp, -0x10);
}

// @ 0x01216ee0  (one tagged delete and a destructor thunk, FuncInfo 0x01504cf0)
void Unwind_01216ee0(Frame fp)
{
    Del(fp, -0x50, g_tag13ebc58);
    Clean<T_421cf0>(fp, -0x4c);
}

// @ 0x01216fe0  (eleven tagged deletes of the first argument, FuncInfo 0x01504e20)
void Unwind_01216fe0(Frame fp)
{
    Del(fp, 0x08, g_tag1414554);
    Del(fp, 0x08, g_tag1414540);
    Del(fp, 0x08, g_tag141452c);
    Del(fp, 0x08, g_tag1414518);
    Del(fp, 0x08, g_tag1414504);
    Del(fp, 0x08, g_tag14144ec);
    Del(fp, 0x08, g_tag14144d4);
    Del(fp, 0x08, g_tag14144bc);
    Del(fp, 0x08, g_tag14144a8);
    Del(fp, 0x08, g_tag1414490);
    Del(fp, 0x08, g_tag141447c);
}

// @ 0x01217240  (five tagged deletes of the first argument, FuncInfo 0x01504ff8)
void Unwind_01217240(Frame fp)
{
    Del(fp, 0x08, g_tag1414848);
    Del(fp, 0x08, g_tag1414830);
    Del(fp, 0x08, g_tag1414810);
    Del(fp, 0x08, g_tag14147f4);
    Del(fp, 0x08, g_tag14147e0);
}

// @ 0x01217330  (clears bit 0 of the global at 0x0163a2ac, FuncInfo 0x015050ac)
extern uint32_t g_ehFlags0163a2ac;   // 0x0163a2ac
void Unwind_01217330(Frame)
{
    g_ehFlags0163a2ac &= ~1u;
}

// @ 0x01217470  (twelve destructor thunks and one two-pointer free, FuncInfo 0x0150524c)
void Unwind_01217470(Frame fp)
{
    Clean<T_530670>(fp, -0xdc);
    Clean<T_530670>(fp, -0xcc);
    Clean<T_76e1e0>(fp, -0xb8);
    Clean<T_76e1e0>(fp, -0xb8);
    Clean<T_530670>(fp, -0x3c);
    Clean<T_429480>(fp, -0x84);
    Clean<T_530670>(fp, -0x1c);
    Clean<T_530670>(fp, -0x4c);
    Clean<T_5477e0>(fp, -0xb8);
    free_two_00c2e4e0(Slot(fp, -0xe0), Slot(fp, -0xbc));
    Clean<T_530670>(fp, -0x2c);
    Clean<T_530670>(fp, -0x94);
}

// @ 0x01217570  (one tagged delete and five destructor thunks, FuncInfo 0x015053c4)
void Unwind_01217570(Frame fp)
{
    Clean<T_76e1e0>(fp, -0x20);
    Clean<T_530670>(fp, -0x40);
    Del(fp, 0x04, g_tag141b18c);
    Clean<T_83f8f0>(fp, 0x08);
    Clean<T_530670>(fp, -0x50);
    Clean<T_933960>(fp, -0x30);
}
