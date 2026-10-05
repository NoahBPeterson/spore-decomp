// slice s005802f0 — editor name helpers and misc.
#include "types.h"

typedef unsigned int size_t;

void DoInsertValue(void* dst, void* src, int n);   // 0x011e0744 (cdecl)
void WStr_Format(void* out, const wchar_t* fmt, int value);   // 0x0041e050
void GetPropertyAsText(void* list, uint32_t id, void* out);  // 0x006a1360
void* FUN_00607a60();                              // AuthManager
void  EA_IO_MakeFileNameValid(const wchar_t* src, wchar_t* dst, int flags);  // 0x00931250
void  eastl_deallocate(void* p);                   // 0x00f47380
extern "C" wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, size_t n);

namespace eastl {
struct allocator {};
template <typename T, typename A = allocator>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAlloc;
};
} // namespace eastl

typedef eastl::basic_string<wchar_t> string16;

// 20-byte local string wrapper
struct cString {
    char mData[20];
    void Init();                 // 0x006b5060
    const wchar_t* c_str();      // 0x006b5240
    int GetValue();              // 0x006b55c0
};

struct cAppModeEditorBase {
    char pad0[0x24];
    void* mPropList;             // +0x24

    bool GetEditorName(string16* out);
    bool GetDefaultModelName(string16* out);
};

// @ 0x005805e0
bool cAppModeEditorBase::GetEditorName(string16* out)
{
    if (mPropList) {
        typedef bool (__thiscall *HasFn)(void*, uint32_t);
        HasFn has = *(HasFn*)(*(char**)mPropList + 0x1c);
        if (has(mPropList, 0x703e542f)) {
            cString s;
            s.Init();
            GetPropertyAsText(mPropList, 0x703e542f, &s);
            WStr_Format(out, L"", s.GetValue());
            s.c_str();
            return true;
        }
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// @ 0x00580670
bool cAppModeEditorBase::GetDefaultModelName(string16* out)
{
    if (mPropList) {
        typedef bool (__thiscall *HasFn)(void*, uint32_t);
        HasFn has = *(HasFn*)(*(char**)mPropList + 0x1c);
        if (has(mPropList, 0x4d92f82)) {
            cString s;
            s.Init();
            GetPropertyAsText(mPropList, 0x4d92f82, &s);
            WStr_Format(out, L"", s.GetValue());
            void TrimString(string16*);   // not used; placeholder
            out->mpBegin; // keep layout
            s.c_str();
            return true;
        }
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// @ 0x00580c10
void FUN_00580c10(wchar_t* out)
{
    void* auth = FUN_00607a60();
    typedef bool (__thiscall *IsOfflineFn)(void*);
    IsOfflineFn isOffline = *(IsOfflineFn*)(*(char**)auth + 0x24);
    if (isOffline(auth)) {
        wcsncpy(out, L"EditorOfflineUser", 0x100);
        return;
    }
    string16 name;
    name.mpBegin = (wchar_t*)0x01667bac; name.mpEnd = (wchar_t*)0x01667bac; name.mpCapacity = (wchar_t*)0x01667bae;
    typedef void* (__thiscall *GetNameFn)(void*);
    GetNameFn getName = *(GetNameFn*)(*(char**)auth + 0x30);
    WStr_Format(&name, L"EditorUser_%hs", *(int*)getName(auth));
    EA_IO_MakeFileNameValid(name.mpBegin, out, 4);
    if (((name.mpCapacity - name.mpBegin) & ~1) > 2 && name.mpBegin)
        eastl_deallocate(name.mpBegin);
}

// @ 0x005810a0
struct cBoolVec {
    void* mpBegin;
    void* mpEnd;
    void EraseAll();
};

void cBoolVec::EraseAll()
{
    void* begin = mpBegin;
    void* end = mpEnd;
    DoInsertValue(begin, end, 0);
    mpEnd = (char*)mpEnd + (((int)end - (int)begin) >> 2) * -4;
}

// ---------------------------------------------------------------------------------------------
// Not-yet-reconstructed functions (skeleton stubs; see partial.txt).
void FUN_005802f0() {}   // 0x005802f0  745 B
void FUN_00580700() {}   // 0x00580700  672 B
void FUN_005809a0() {}   // 0x005809a0  610 B
void FUN_00580cb0() {}   // 0x00580cb0  307 B
void FUN_00580df0() {}   // 0x00580df0  674 B
