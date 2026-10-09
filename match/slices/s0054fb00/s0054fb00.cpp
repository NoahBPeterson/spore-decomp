// Slice s0054fb00: SP::Pollen::cAssetDirectory mapping persistence (RestoreMappings,
// PurgePendingAssets), Pollinator::cAssetMetadata ctor/dtor and small accessors.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---- externals -------------------------------------------------------------
int   Mutex_Lock(void* m, const void* p);            // thiscall fixed below
int   Mutex_Unlock(void* m);
int*  GetSaveArea(int id);                           // 0x6b1f90
struct MetaBase { void ctor(); };
void  FUN_004329e0();                                // base ctor (thiscall)
void  FUN_004e3590(void* a, void* b);
void  FUN_0054e250(int a, int b, void* c);
void  FUN_005526a0(void* k);
void  FUN_00553750(void* a, void* b, int c);
void  FUN_00552750();
void  FUN_00553b90(void* v);
void  FUN_00553e00(void* v);
void  FUN_00553fb0(void* v);
void  WString_FreeBuffer(void* self);                // 0x4237d0
void  DoFreeNodes(void* a, void* b);                 // 0x5687d0
void  FUN_004237d0(void* self);
void  FUN_00554020(void* v, void* k);
void  FUN_005540d0(void* v, void* k);
struct Map5 {
    void F4020(void* out, int* key);   // 0x554020
    void F40d0(int* key);              // 0x5540d0
};
void  FUN_00555980(void* out, void* k);
void  FUN_00552af0(void* v, void* k);
void  FUN_005531b0(void* v, void* k);
char  FUN_0054e460(int a, int b, void* c);            // GetLocalKey
int64_t FUN_005418c0(int a);
int*  ObjectTemplateDB();
int*  ObjectError(int a);                             // 0x8de1a0

extern void* vtbl_cAssetMetadata[];
extern void* vtbl_cPropertyList[];
extern void* vtbl_cEditorResource[]; // 0x013eb938
extern char  DAT_013ec47c[];
extern char  DAT_01667bac[];
extern char  DAT_015e3294;
extern char  DAT_013f3cb0;

struct Mtx {
    int Lock(const void* p);
    int Unlock();
};

// ---- objects ---------------------------------------------------------------
struct Meta {
    char pad[0x400];
    Meta();                       // 00550450
    void FUN_005506c0();          // dtor
    int64_t FUN_005508a0();
    void* FUN_00550910(unsigned idx);
    unsigned FUN_005509e0(unsigned idx);
    unsigned FUN_00550a60(unsigned idx);
    bool FUN_00550aa0(void* key);
    void FUN_00550b00(int key);
    void FUN_00550b30(int key);
    char FUN_00550b60(int key);
    Meta* Cast(int type);
};

struct CD {
    char pad[0x400];
    bool RestoreMappings();
    void PurgePendingAssets();
    int  FUN_00550210(int* key);
};

// @ 0x00550450
Meta::Meta()
{
    char* s = (char*)this;
    ((MetaBase*)s)->ctor();
    *(void**)s = (void*)vtbl_cAssetMetadata;
    *(int*)(s + 0x18) = 0xffffffff;
    *(int*)(s + 0x1c) = 0xffffffff;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x2c) = 0xffffffff;
    *(int*)(s + 0x30) = 0xffffffff;
    *(int*)(s + 0x34) = 0xffffffff;
    *(int*)(s + 0x38) = 0xffffffff;
    *(int*)(s + 0x3c) = 0xffffffff;
    *(int*)(s + 0x40) = 0xffffffff;
    *(int*)(s + 0x44) = 0xffffffff;
    *(int*)(s + 0x48) = 0;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x50) = 0;
    *(int*)(s + 0x54) = 0;
    *(int*)(s + 0x58) = 0; *(int*)(s + 0x5c) = 0; *(int*)(s + 0x60) = 0;
    *(int*)(s + 0x58) = (int)DAT_01667bac;
    *(int*)(s + 0x5c) = *(int*)(s + 0x58);
    *(int*)(s + 0x60) = *(int*)(s + 0x58) + 2;
    *(int*)(s + 0x68) = 0xfffffffe;
    *(int*)(s + 0x6c) = 0xffffffff;
    *(int*)(s + 0x70) = 0xffffffff;
    *(char*)(s + 0x74) = 1;
    *(int*)(s + 0x78) = 0; *(int*)(s + 0x7c) = 0; *(int*)(s + 0x80) = 0;
    *(int*)(s + 0x78) = (int)DAT_01667bac;
    *(int*)(s + 0x7c) = *(int*)(s + 0x78);
    *(int*)(s + 0x80) = *(int*)(s + 0x78) + 2;
    *(int*)(s + 0x88) = 0; *(int*)(s + 0x8c) = 0; *(int*)(s + 0x90) = 0;
    *(int*)(s + 0x88) = (int)DAT_01667bac;
    *(int*)(s + 0x8c) = *(int*)(s + 0x88);
    *(int*)(s + 0x90) = *(int*)(s + 0x88) + 2;
    *(int*)(s + 0x98) = 0; *(int*)(s + 0x9c) = 0; *(int*)(s + 0xa0) = 0;
    *(int*)(s + 0xac) = 0; *(int*)(s + 0xb0) = 0; *(int*)(s + 0xb4) = 0;
    *(int*)(s + 0xc0) = 0; *(int*)(s + 0xc4) = 0; *(int*)(s + 0xc8) = 0;
}

// @ 0x005506c0
void Meta::FUN_005506c0()
{
    char* s = (char*)this;
    *(void**)s = (void*)vtbl_cAssetMetadata;
    FUN_00553fb0(s + 0xc0);
    FUN_00553e00(s + 0xac);
    FUN_00553b90(s + 0x98);
    WString_FreeBuffer(s + 0x88);
    WString_FreeBuffer(s + 0x78);
    WString_FreeBuffer(s + 0x58);
    *(void**)s = (void*)vtbl_cPropertyList;
    *(void**)s = (void*)vtbl_cEditorResource;
}

// @ 0x00550740
Meta* Meta::Cast(int param_2)
{
    if (param_2 == 0x30bdee3) return this;
    if (param_2 == 0x2269ed1) return this;
    if (param_2 == (int)0xee3f516e) return this;
    return 0;
}

// @ 0x005508a0
int64_t Meta::FUN_005508a0()
{
    return *(int64_t*)((char*)this + 0x68);
}

// @ 0x00550910
void* Meta::FUN_00550910(unsigned idx)
{
    char** v = (char**)((char*)this + 0x98);
    void* result;
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 4)) {
        void** p = (void**)(*(char**)((char*)this + 0x98) + (idx << 4));
        result = *p;
    } else {
        result = DAT_013ec47c;
    }
    return result;
}

// @ 0x005509e0
unsigned Meta::FUN_005509e0(unsigned idx)
{
    char** v = (char**)((char*)this + 0xac);
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 4)) {
        unsigned* p = (unsigned*)(*(char**)((char*)this + 0xac) + (idx << 4));
        unsigned result = *p;
        return result;
    }
    return 0;
}

// @ 0x00550a60
unsigned Meta::FUN_00550a60(unsigned idx)
{
    unsigned** v = (unsigned**)((char*)this + 0xc0);
    if (idx < (unsigned)(((char*)v[1] - (char*)v[0]) >> 2)) {
        return (*(unsigned**)((char*)this + 0xc0))[idx];
    }
    return 0;
}

// @ 0x00550aa0
bool Meta::FUN_00550aa0(void* key)
{
    char* s = (char*)this;
    int local_c;
    int local_8;
    FUN_00555980(&local_c, &key);
    int local_2c;
    if (local_c == local_8) {
        local_2c = *(int*)(s + 0xc4);
    } else {
        local_2c = local_c;
    }
    return local_2c != *(int*)(s + 0xc4);
}

// @ 0x00550b00
void Meta::FUN_00550b00(int key)
{
    char* s = (char*)this;
    char local_8[8];
    ((Map5*)(s + 0xc0))->F4020(local_8, &key);
}

// @ 0x00550b30
void Meta::FUN_00550b30(int key)
{
    char* s = (char*)this;
    ((Map5*)(s + 0xc0))->F40d0(&key);
}

// @ 0x00550b60
char Meta::FUN_00550b60(int key)
{
    char* s = (char*)this;
    int64_t v = FUN_005418c0(key);
    *(int64_t*)(s + 0x18) = v;
    if (((*(unsigned*)(s + 0x18) & *(unsigned*)(s + 0x1c)) != 0xffffffff)
        && (*(int*)(s + 0x18) != 0 || *(int*)(s + 0x1c) != 0)) {
        return 1;
    }
    return 0;
}

// @ 0x00550210
int CD::FUN_00550210(int* param_2)
{
    char* s = (char*)this;
    int* obj = ObjectError((int)s);
    int* result = 0;
    if (obj != 0) {
        result = (int*)((int(__thiscall*)(void*, void*))((*(void***)obj)[0x58 / 4]))(obj, param_2);
        if (result == 0) {
            int local_18[3];
            local_18[0] = param_2[0];
            local_18[1] = 0x1a99b06b;
            local_18[2] = param_2[2];
            result = (int*)((int(__thiscall*)(void*, void*))((*(void***)obj)[0x58 / 4]))(obj, local_18);
        }
        int* sa = GetSaveArea(0x11ac19d);
        if (result == sa) {
            return ((int(__thiscall*)(void*, void*))((*(void***)result)[0x40 / 4]))(result, param_2);
        }
    }
    return (int)result & 0xffffff00;
}

// @ 0x0054fb00
bool CD::RestoreMappings()
{
    char* self = (char*)this;
    Mtx* mtx = (Mtx*)(self + 0x8);
    mtx->Lock(&DAT_013f3cb0);
    int* sa = GetSaveArea(0x11ac19d);
    if (sa == 0) {
        mtx->Unlock();
        return false;
    }
    char ok = 1;
    int* obj = 0;
    int made = ((int(__thiscall*)(void*, void*, int*, int, int, int, int))
                    ((*(void***)sa)[0x34 / 4]))(sa, (void*)&DAT_015e3294, (int*)&obj, 1, 3, 1, 0);
    if (made != 0) {
        int* st = (int*)((int(__thiscall*)(void*))((*(void***)obj)[0x18 / 4]))(obj);
        unsigned ver = 0;
        int got = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &ver, 4);
        ok = got == 4;
        if (ver != 0x2198da60u) {
            if (obj != 0) ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))(obj);
            mtx->Unlock();
            return false;
        }
        unsigned count = 0;
        unsigned n = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &count, 4) == 4;
        // (rest: field/array reads are represented by the same stream Read calls)
        FUN_004e3590(*(void**)(self + 0x4c), *(void**)(self + 0x50));
        *(void**)(self + 0x50) = 0;
        if (ver > 2) {
            unsigned c2 = 0;
            int r = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &c2, 4);
            for (unsigned i = 0; ok && i < c2; i++) {
                int k1 = 0; int64_t v1 = 0;
                int a = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &k1, 4);
                int b = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &v1, 8);
                ok = (a == 4) && (b == 8);
                (void)r;
            }
        }
        if (ver > 5) {
            FUN_004e3590(*(void**)(self + 0xd4), *(void**)(self + 0xd8));
            *(void**)(self + 0xd8) = 0;
            if (ver > 2) {
                unsigned c2 = 0;
                ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &c2, 4);
                for (unsigned i = 0; ok && i < c2; i++) {
                    int k1 = 0; int64_t v1 = 0;
                    ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &k1, 4);
                    ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &v1, 8);
                }
            }
        }
        DoFreeNodes(*(void**)(self + 0xc4), *(void**)(self + 0xc8));
        *(int*)(self + 0xcc) = 0;
        if (ver > 3) {
            unsigned c3 = 0;
            ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &c3, 4);
            for (unsigned i = 0; ok && i < c3; i++) {
                int64_t k = 0;
                int r = ((int(__thiscall*)(void*, void*, int))((*(void***)st)[0x30 / 4]))(st, &k, 8);
                if (r == 8) {
                    FUN_00553750((void*)&k, &k, 0);
                }
                ok = r == 8;
            }
        }
        ((void(__thiscall*)(void*))((*(void***)obj)[0x24 / 4]))(obj);
        (void)ok;
    }
    char r = ok;
    if (obj != 0) ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))(obj);
    mtx->Unlock();
    return r != 0;
}

// @ 0x005502b0
void CD::PurgePendingAssets()
{
    char* self = (char*)this;
    int* piVar3 = *(int**)(self + 0x80);
    int* puVar1 = (int*)*piVar3;
    if (puVar1 == 0) {
        FUN_00552750();
    }
    int* local_10 = (int*)(*(int*)(self + 0x80) + *(int*)(self + 0x84) * 4);
    int* local_14 = (int*)*local_10;
    int* local_c = puVar1;
    int* local_8 = piVar3;
    while (local_c != local_14) {
        int local_20 = 0, local_1c = 0, local_18 = 0;
        char cVar2 = FUN_0054e460(local_c[0], local_c[1], &local_20);
        (void)cVar2;
        FUN_00552af0(local_c, 0);
        FUN_005531b0(&local_20, 0);
        int* db = ObjectTemplateDB();
        ((void(__thiscall*)(void*, void*, int))((*(void***)db)[0x78 / 4]))(db, &local_20, 0);
        int* sa = GetSaveArea(0x11ac19d);
        ((void(__thiscall*)(void*, void*))((*(void***)sa)[0x40 / 4]))(sa, &local_20);
        local_1c = 0x30bdee3;
        ((void(__thiscall*)(void*, void*))((*(void***)sa)[0x40 / 4]))(sa, &local_20);
        local_c = (int*)local_c[2];
        while (local_c == 0) {
            local_8 = local_8 + 1;
            local_c = (int*)*local_8;
        }
    }
    DoFreeNodes(*(void**)(self + 0x80), *(void**)(self + 0x84));
    *(int*)(self + 0x88) = 0;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
