// Slice s00c19b60. Region 0x00c19b60.
// eastl::wstring "list" serialisation helper, the 0x24-stride sibling of the
// list<AutoRefCount> writer at 0x00c6c390: writes an opening element, one entry per
// element through the generic element writer, then a closing element.
//
// The element name is a conditional temporary: retail constructs the string in the
// taken arm (0x93c5a0 returns it by value for a real name, 0x579a90 default-constructs
// the empty one), copy-constructs the function-scope string from it (0x56e2d0) and only
// then destroys the temporary, which is what the is-this-temporary-live mask in ebx and
// its test bl,2 / test bl,1 pair are.
//
// 0x93c5a0 returns the string slot in eax (the MSVC struct-return convention), which is
// why retail passes the temporary straight to the copy constructor with no lea.
//
// The function-scope string only ever needs its copy constructor: retail's closing
// cleanup is written against the cached begin pointer (ebp) rather than the object, so
// the two types are kept apart (the arm temporaries own their block, the copy does not).
//
// Flags: /O2 /MD /Gy /TP /arch=SSE /fp=fast
#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_013f58ac[];

#pragma warning(disable : 4100)

typedef unsigned char u8;

// Compiler-only barrier (no code emitted). Retail keeps the begin pointer in a
// callee-saved register from the first Begin to the final cleanup; without pinning the
// load cl 15 copies the freshly loaded value into that register
// (`mov eax,[esp+0x28]; mov ebp,eax`) and then re-reads the vtable in a different order.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" {
void  __cdecl FUN_0056e2d0(void* dst, const void* src);            // 0x0056e2d0 eastl::wstring copy ctor
void  __cdecl FUN_00579a90(void* self, int n);                     // 0x00579a90 eastl::wstring::range_initialize
void  __cdecl FUN_00f47380(void* p);                               // 0x00f47380 operator delete
char  __cdecl FUN_00ac8050(void* ser, const wchar_t* name, void* elem); // 0x00ac8050 generic element writer
}

// 0x0056e2d0 and 0x00579a90 are __thiscall: destination in ecx, the
// source/size on the stack and popped by the callee.
typedef void (__thiscall* WStrCopyCtor)(void* dst, const void* src);
typedef void (__thiscall* WStrRangeInit)(void* self, int n);

// The game's string as the stack frame shows it: 16 bytes, begin/end/cap plus a
// trailing word the constructors here never touch, an out-of-line empty literal
// (0x013f58ac) and a heap block freed only when longer than one character.
struct WStr
{
    wchar_t* begin;
    wchar_t* end;
    wchar_t* cap;
    void*    alloc;

    __forceinline WStr()
    {
        begin = 0;
        end = 0;
        cap = 0;
        ((WStrRangeInit)FUN_00579a90)(this, 0);
    }

    __forceinline ~WStr()
    {
        if (((char*)cap - (char*)begin & ~1) > 2 && begin)
            FUN_00f47380(begin);
    }
};

// The function-scope copy of that string: same layout, copy construction only.
struct WStrKey
{
    wchar_t* begin;
    wchar_t* end;
    wchar_t* cap;
    void*    alloc;

    __forceinline WStrKey(const WStr& other)
    {
        ((WStrCopyCtor)FUN_0056e2d0)(this, &other);
    }
};

// 0x0093c5a0 EA::ConvertToString16: formats the int into a new string and returns it by
// value (the caller passes the result slot as the hidden first argument).
WStr __cdecl FUN_0093c5a0(int name, int n);

// ---------------------------------------------------------------------------------------------
// 0x00c19b60 -- write a list whose elements are 0x24 bytes each.
// ---------------------------------------------------------------------------------------------
// @ 0x00c19b60
u8 __cdecl FUN_00c19b60(void** serializer, int name, void** list)
{
    bool ok = true;
    if (list[0] != list[1]) {
        WStrKey key = name != 0 ? FUN_0093c5a0(name, -1) : WStr();

        // The writer is read into a register before the name pointer: retail's frame shows
        // `mov edi,[esp+0x4c]; mov ebp,[esp+0x28]`, and this read is the one the rest of
        // the body (both calls, the element loop) keeps in edi.
        void** writer = *(void** volatile*)&serializer;

        // The element name pointer is read once; both element calls and the final cleanup
        // use it, while the empty() test re-reads key.end out of the frame each time.
        const wchar_t* nm = key.begin;
        _ReadWriteBarrier();

        // Two separate calls rather than a conditional argument: cl folds `c ? nm : lit`
        // into one register select, while the original keeps the callee setup hoisted and
        // pushes each arm separately (`cmp ebp,[esp+0x2c]; je; push ebp; jmp; push lit;
        // call edx`). Writing both calls out makes cl merge their common tail that way.
        if (nm != key.end)
            (*(void(__thiscall**)(void**, const wchar_t*))(*(char**)writer))
                (writer, nm);
        else
            (*(void(__thiscall**)(void**, const wchar_t*))(*(char**)writer))
                (writer, (const wchar_t*)g_013f58ac);

        char* it = (char*)list[0];
        char* end = (char*)list[1];
        for (; it != end; it += 0x24) {
            // Retail shares the && short-circuit's false block with the result store, so the
            // update compiles to "store 1; test al,al; jne; store 0" rather than setne.
            ok = ok && FUN_00ac8050(writer, 0, it) != 0;
        }

        if (nm != key.end)
            (*(void(__thiscall**)(void**, const wchar_t*))(*(char**)writer + 4))
                (writer, nm);
        else
            (*(void(__thiscall**)(void**, const wchar_t*))(*(char**)writer + 4))
                (writer, (const wchar_t*)g_013f58ac);

        // Cleanup of the copy, through the cached begin pointer.
        if (((char*)key.cap - (char*)nm & ~1) > 2 && nm)
            FUN_00f47380((void*)nm);
    }
    return ok;
}
