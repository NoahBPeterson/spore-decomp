// Slice s0054c780: SP::Pollen::cAssetMetadataResourceFactory::ReadResource.
// PARTIAL: the version-gated deserializer is long and several branches depend on
// cString/AutoRefCount semantics that are not yet reproduced; the main control flow
// (version check, metadata alloc, field reads, cleanup) is present.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

bool  ReadInt32(void* reader, const void* p, int n, int flags);   // EA::IO::ReadInt32
bool  FUN_0093a800(void* reader, const void* p, int n, int flags);
void* FUN_00554140(int a);
void  FUN_00552800(void* p, int a);
void  FUN_005527a0(void* p, int a);
void  FUN_00553be0(int a);
void  FUN_00553e60(void* p);
int   FUN_00554b60(int a, int b);
int   FUN_00550bd0(void* p);
void  FUN_00554020(void* a, void* b);
void* FUN_00607a60();

struct Meta {
    virtual void Init();      // vtable slot 0
    virtual void Delete();    // vtable slot 1
};
struct IReader {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual int Skip(int a, int b);          // vtable slot 10 (0x28)
    virtual void v11();
    virtual int ReadBytes(void* p, int n);   // vtable slot 12 (0x30)
};
struct IObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void* GetReader();               // vtable slot 6 (0x18)
};

// @ 0x0054c780
bool FUN_0054c780(int* param_1, int param_2, int param_3, int param_4)
{
    if (param_4 != 0x30bdee3) return false;
    int* m = (int*)FUN_00554140(param_2);
    if (m != 0) ((Meta*)m)->Init();
    IReader* r = (IReader*)((IObj*)param_1)->GetReader();

    int ver = 0;
    bool ok = ReadInt32(r, &ver, 1, 0);
    if (!ok || (ver < 0x7 && 0xd < ver)) {
        if (m != 0) ((Meta*)m)->Delete();
        return false;
    }

    ok = FUN_0093a800(r, m + 6, 1, 0);
    if (ok) ok = ReadInt32(r, m + 9, 1, 0);
    if (ok) ok = ReadInt32(r, m + 10, 1, 0);
    if (ok) ok = ReadInt32(r, m + 8, 1, 0);
    if (ok) ok = ReadInt32(r, m + 0xc, 1, 0);
    if (ok) ok = ReadInt32(r, m + 0xd, 1, 0);
    if (ok) ok = ReadInt32(r, m + 0xb, 1, 0);
    if (9 < ver && ok) ok = FUN_0093a800(r, m + 0xe, 1, 0);
    if (0xb < ver && ok) ok = FUN_0093a800(r, m + 0x10, 1, 0);

    // Remaining version-gated field/array deserialization (cString Load, verb-icon
    // trays, property lists, sprite/array reads) is not reproduced here -- PARTIAL.
    if (m != 0) ((Meta*)m)->Delete();
    return ok;
}
