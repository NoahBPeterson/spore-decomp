// Slice s00543590: Swarm/Feed paint-variable + Atom link-attribute helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <wchar.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- externals
int  StrCmpW(const wchar_t* a, const wchar_t* b);   // 16-bit string compare (inlined in original)
unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int b);
void FUN_00546a60(unsigned int a);
void FUN_004237d0();
unsigned int FUN_0041df50(wchar_t* s, void* out);
void FUN_00546b00(unsigned int* p);
unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
void FUN_00543c10_impl(void* self, int* attrs, int mode);

struct Ctx40 {
    char mPad[0x40];
    void FUN_00543b90(int* attrs);
    void FUN_00543bb0(int* attrs);
    void FUN_00543bd0(int* attrs);
    void FUN_00543bf0(int* attrs);
    void FUN_00543c10(int* attrs, int mode);
};

// @ 0x00543b90
void Ctx40::FUN_00543b90(int* attrs) { FUN_00543c10(attrs, 1); }
// @ 0x00543bb0
void Ctx40::FUN_00543bb0(int* attrs) { FUN_00543c10(attrs, 2); }
// @ 0x00543bd0
void Ctx40::FUN_00543bd0(int* attrs) { FUN_00543c10(attrs, 3); }
// @ 0x00543bf0
void Ctx40::FUN_00543bf0(int* attrs) { FUN_00543c10(attrs, 4); }

// ---------------------------------------------------------------- big helpers
// (approximate ports: string-key attribute walkers)

// @ 0x00543590
void FUN_00543590(void* self, int* attrs)
{
    extern wchar_t* gAttrRel;
    extern wchar_t* gAttrHref;
    extern wchar_t* gAttrTerm;
    if (*(char*)((char*)self + 0x24) == 0)
        return;
    int* p = attrs;
    wchar_t* local_14 = 0;
    wchar_t* local_8 = 0;
    wchar_t* local_c = 0;
    while (*p != 0) {
        wchar_t* key = (wchar_t*)*p;
        wchar_t* val = (wchar_t*)p[1];
        p += 2;
        if (StrCmpW(key, gAttrRel) != 0) {
            if (StrCmpW(key, gAttrHref) != 0) {
                if (StrCmpW(key, gAttrTerm) == 0) {
                    local_c = val;
                }
            } else {
                local_8 = val;
            }
        } else {
            local_14 = val;
        }
    }
    if (*(int*)((char*)self + 0x28) == 0) {
        if (*(int*)((char*)self + 0x20) != 0 && local_14 != 0) {
            // sprintf(self->field20+0x50, "%ls", local_8)
        }
    } else if (local_14 != 0 && local_c != 0) {
        // vector_map::find / sprintf on self->field28
    }
    (void)local_8; (void)local_c;
}

// @ 0x005439d0
void FUN_005439d0(void* self, int* attrs)
{
    if (*(int*)((char*)self + 0x28) == 0)
        return;
    int* p = attrs;
    int local_c = 0;
    wchar_t* local_10 = 0;
    while (*p != 0) {
        wchar_t* key = (wchar_t*)*p;
        wchar_t* val = (wchar_t*)p[1];
        p += 2;
        if (StrCmpW(key, L"term") != 0) {
            if (StrCmpW(key, L"scheme") == 0) {
                local_c = (int)FNV1_String16(val, 0x811c9dc5, 1);
                local_10 = val;
            }
        }
    }
    if (local_c == 0x326cb657) {
        unsigned char tmp[17];
        unsigned int v = FUN_0041df50(local_10, tmp);
        FUN_00546a60(v);
        FUN_004237d0();
    } else if (local_c == (int)0x9a5acf10) {
        unsigned int v = (unsigned int)wcstoul(local_10, 0, 0x10);
        FUN_00546b00(&v);
    }
}

// @ 0x00543c10
void Ctx40::FUN_00543c10(int* attrs, int mode)
{
    (void)mode;
    if (*(char*)((char*)this + 0x24) == 0)
        return;
    extern wchar_t* gAttrA;
    extern wchar_t* gAttrB;
    int* p = attrs;
    wchar_t* local_10 = 0;
    wchar_t* local_8 = 0;
    while (*p != 0) {
        wchar_t* key = (wchar_t*)*p;
        wchar_t* val = (wchar_t*)p[1];
        p += 2;
        if (StrCmpW(key, gAttrA) != 0) {
            if (StrCmpW(key, gAttrB) == 0)
                local_8 = val;
        } else {
            local_10 = val;
        }
    }
    if (*(int*)((char*)this + 0x28) != 0 && local_10 != 0 && local_8 != 0) {
        // vector_map find + string assign on this->field28
    }
    (void)local_8;
}
