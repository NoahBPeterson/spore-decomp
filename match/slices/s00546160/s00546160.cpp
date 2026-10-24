// Slice s00546160: SP::Feed::HandshakeParser element handlers + EASTL containers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <wchar.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- externals
unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int b); // 0x00932f30
short* FUN_00547900(const void* table, int a, int b);
short* FUN_00547970(const void* table, int a, int b);
void   FUN_004228e0(int a, unsigned int b);
int    FUN_00685520(int a);
int*   LowerBound(int* first, int* last, unsigned int* key, char cmp);
void   FUN_005481d0(int* pos, void* value);
void   FUN_00548e70(int* a);
void   StringResizeW(int n);

// element constructors / destructors (all thiscall)
struct FeedLink {                    // 0x34-byte vector element
    int  data[0x34 / 4];
    FeedLink* Ctor();                // 0x005476e0
    int       Destroy();             // 0x005477a0
};
struct FeedVec {                     // eastl::vector<FeedLink>
    FeedLink* begin;                 // +0x00
    FeedLink* end;                   // +0x04
    FeedLink* cap;                   // +0x08
};
struct FeedEntry {                   // 0x118-byte vector element
    int  data[0x118 / 4];
    int* Ctor();                     // 0x00546c20
    void Destroy();                  // 0x00546f80
};
struct E16 {                         // 0x10-byte vector element
    int  data[4];
    void Ctor(int a, int b);         // 0x00423820
};
struct WStrVal {                     // eastl::basic_string<wchar_t>
    int  data[3];
    WStrVal* Ctor(const wchar_t* first, const wchar_t* last); // 0x0047d390
};
struct MapValue {                    // eastl::pair<unsigned, WStrVal>
    unsigned key;
    WStrVal  str;
    void Destroy();                  // 0x005477e0
};
struct WStr {
    void Append(const wchar_t* first, const wchar_t* last); // 0x00429580
};

// hash-dispatched handlers (ellipsis keeps arity flexible)
void FUN_00545ad0(...); void FUN_00545aa0(...); void FUN_005459a0(...);
void FUN_00545ca0(...); void FUN_00545bd0(...); void FUN_00545dc0(...);
void FUN_00545b20(...); void FUN_00545bf0(...); void FUN_00545cc0(...);
void FUN_00545ce0(...); void FUN_00545d30(...); void FUN_00545d80(...);
void FUN_00545c10(...); void FUN_00545c60(...); void FUN_00545fa0(...);
void FUN_00546020(...); void FUN_00546050(...); void FUN_00546090(...);
void FUN_005460d0(...); void FUN_00546110(...);

extern char  gEmptyString[];        // @ 0x1667bac
extern short gFeedEndTable[];       // @ 0x13f3ae0

// sub-object helpers used by the 0x118-byte entry ctor (all thiscall)
struct AllocSub {                       // sp_vector_allocator
    void Ctor(void* tag);               // 0x429360  (allocator copy ctor)
};
struct VSetSub {                        // eastl::vector_set
    void Ctor(void* tag);               // 0x540470
};
struct Vec3Sub {                        // Vector3
    void SetZero();                     // 0x56dec0
};

// ---------------------------------------------------------------- object
struct Obj42 {
    char mPad[0x200];
    int* FUN_00546630();                       // ctor
    void FUN_00546800();                       // push_back 0x34
    int  FUN_00546880(int pos);                // erase one 0x34
    unsigned int* FUN_00546930(unsigned int* key); // vector_map operator[]
    void FUN_00546a60(void* value);            // push_back 0x10
    void FUN_00546b70();                       // push_back 0x118
    int* FUN_00546c20();                       // ctor of 0x118 entry
    void InsertLink(int* pos, void* value);    // 0x00547a10 (thiscall)
    int* InsertMap(int* pos, void* value);     // 0x00547d80 (thiscall)
    void Insert16(int* pos, void* value);      // 0x00547e90 (thiscall)
    void Insert118(int* pos, void* value);     // 0x00548450 (thiscall)
};

// @ 0x00546160  SP::Feed::HandshakeParser::StartElementHandler
void FUN_00546160(int param_1, const wchar_t* name, int* attrs)
{
    StringResizeW(0);
    unsigned int u = FNV1_String16(name, 0x811c9dc5, 0);
    if (u < 0x8231a2b4) {
        if (u == 0x8231a2b3) { FUN_00545ad0(); return; }
        if (0x5cca0010 < u) {
            if (u == 0x603ddcb1) { FUN_00545ca0(*(int*)(param_1 + 0x24), 0x603ddcb1); return; }
            if (u != 0x725b8629) return;
            if ((char)FUN_00685520(2) == 0) return;
            FUN_00545ca0(*(int*)(param_1 + 0x24), 0x725b8629);
            return;
        }
        if (u == 0x5cca0010) { FUN_005459a0(); return; }
        if (u == 0x820aba1) { FUN_00545dc0(attrs); return; }
        if (u != 0xedb4507) return;
    } else {
        if (u < 0xe1c70ecf) {
            if (u == 0xe1c70ece) { FUN_00545dc0(attrs); return; }
            if (u != 0xc3753dfe) {
                if (u != 0xca02b5a2) return;
                FUN_00545ca0(*(int*)(param_1 + 0x28), 0xca02b5a2);
                return;
            }
            FUN_00545ad0();
            return;
        }
        if (u != 0xecce3150) {
            if (u != 0xffb4ae9f) return;
            FUN_00545ca0(*(int*)(param_1 + 0x20), 0xffb4ae9f);
            return;
        }
    }
    FUN_00545bd0();
}

// @ 0x005462f0  SP::Feed::HandshakeParser::EndElementHandler
void FUN_005462f0(int param_1, const wchar_t* name)
{
    short* local_14 = gFeedEndTable;
    while (*local_14 != 0) local_14 = local_14 + 1;
    unsigned int uVar1 = (unsigned int)FUN_00547900(gFeedEndTable, 0, (int)(local_14 - gFeedEndTable));
    FUN_004228e0(0, uVar1);
    short* local_20 = gFeedEndTable;
    while (*local_20 != 0) local_20 = local_20 + 1;
    uVar1 = 0xffffffff;
    int iVar2 = (int)FUN_00547970(gFeedEndTable, -1, (int)(local_20 - gFeedEndTable));
    FUN_004228e0(iVar2 + 1, uVar1);

    unsigned int u = FNV1_String16(name, 0x811c9dc5, 0);
    if (0x714baa66 < u) {
        if (u < 0xce191a63) {
            if (u != 0xce191a62) {
                if (u < 0x97bbab5d) {
                    if (u == 0x97bbab5c) { FUN_00545c60(); return; }
                    if (u == 0x725b8629) { FUN_00545cc0(); return; }
                    if (u != 0x8231a2b3) {
                        if (u != 0x845b3524) return;
                        FUN_00546050(); return;
                    }
                } else if (u != 0xc3753dfe) {
                    if (u != 0xcb74142a) return;
                    FUN_00546020(); return;
                }
                FUN_00545b20(); return;
            }
        } else {
            if (0xe647c99b < u) {
                if (u == 0xecce3150) { FUN_00545bf0(); return; }
                if (u != 0xffb4ae9f) return;
                FUN_00545cc0(); return;
            }
            if (u == 0xe647c99b) { FUN_00546110(); return; }
            if (u != 0xd6360d71) {
                if (u != 0xdce0e62d) return;
                FUN_00545ce0(); return;
            }
        }
        FUN_00545d30(); return;
    }
    if (u == 0x714baa66) { FUN_00545d80(); return; }
    if (u < 0x2f8b3bf5) {
        if (u != 0x2f8b3bf4) {
            if (0x13f23f45 < u) {
                if (u != 0x1966dc85) { if (u != 0x1ea2edbc) return; FUN_00545ce0(); return; }
                FUN_00545fa0(); return;
            }
            if (u == 0x13f23f45) { FUN_00545d80(); return; }
            if (u == 0x214b72f) { FUN_00546020(); return; }
            if (u != 0x7319b23) { if (u != 0xedb4507) return; FUN_00545bf0(); return; }
        }
        FUN_00545c10();
    } else {
        if (u < 0x5cca0011) {
            if (u == 0x5cca0010) { FUN_00545aa0(); return; }
            if (u != 0x3b6a85ad) {
                if (u == 0x4cc1948a) { FUN_00546090(); return; }
                if (u != 0x5be92a85) return;
                FUN_005460d0(); return;
            }
            FUN_00545c60(); return;
        }
        if (u == 0x603ddcb1) { FUN_00545cc0(); return; }
        if (u != 0x687720a6) return;
        FUN_00545fa0();
    }
}

// @ 0x00546600
void FUN_00546600(int self, const wchar_t* a, int b)
{
    int s = self;
    ((WStr*)(s + 0x10))->Append(a, a + b);
}

// @ 0x00546630
int* Obj42::FUN_00546630()
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0] = (int)gEmptyString; p[1] = p[0]; p[2] = p[0] + 2;
    p[4] = -1; p[5] = -1;
    int* q = p + 6;
    q[0] = 0; p[7] = 0; p[8] = 0;
    q[0] = (int)gEmptyString; p[7] = q[0]; p[8] = q[0] + 2;
    q = p + 10;
    q[0] = 0; p[0xb] = 0; p[0xc] = 0;
    q[0] = (int)gEmptyString; p[0xb] = q[0]; p[0xc] = q[0] + 2;
    p[0xe] = 0; p[0xf] = 0; p[0x10] = -1;
    q = p + 0x11;
    q[0] = 0; p[0x12] = 0; p[0x13] = 0;
    q[0] = (int)gEmptyString; p[0x12] = q[0]; p[0x13] = q[0] + 1;
    q = p + 0x15;
    q[0] = 0; p[0x16] = 0; p[0x17] = 0;
    q[0] = (int)gEmptyString; p[0x16] = q[0]; p[0x17] = q[0] + 1;
    p[0x19] = 0; p[0x1a] = 0;
    return p;
}

// @ 0x00546800
void Obj42::FUN_00546800()
{
    if ((unsigned int)((FeedVec*)this)->end < (unsigned int)((FeedVec*)this)->cap) {
        FeedLink* e = ((FeedVec*)this)->end;
        ((FeedVec*)this)->end = ((FeedVec*)this)->end + 1;
        (e != 0) ? e->Ctor() : 0;
    } else {
        FeedLink tmp;
        ((Obj42*)this)->InsertLink((int*)((FeedVec*)this)->end, tmp.Ctor());
        tmp.Destroy();
    }
}

// @ 0x00546880
int Obj42::FUN_00546880(int pos)
{
    int* p = (int*)this;
    if ((unsigned int)(pos + 0x34) < (unsigned int)p[1]) {
        int end = p[1];
        int cur = pos;
        while ((cur = cur + 0x34) != end)
            FUN_00548e70((int*)cur);
    }
    p[1] = p[1] - 0x34;
    ((FeedLink*)p[1])->Destroy();
    return pos;
}

// @ 0x00546930
unsigned int* Obj42::FUN_00546930(unsigned int* key)
{
    int* p = (int*)this;
    int* lb = LowerBound((int*)p[0], (int*)p[1], key, *(char*)((char*)p + 0x14));
    if (lb == (int*)p[1] || *key < *(unsigned int*)lb) {
        MapValue mv;
        mv.key = *key;
        mv.str.data[0] = 0;
        mv.str.data[1] = 0;
        mv.str.data[2] = 0;
        mv.str.Ctor((const wchar_t*)gEmptyString, (const wchar_t*)gEmptyString);
        lb = ((Obj42*)this)->InsertMap(lb, &mv);
        mv.Destroy();
    }
    return (unsigned int*)lb + 1;
}

// @ 0x00546a60
void Obj42::FUN_00546a60(void* value)
{
    int* p = (int*)this;
    if ((unsigned int)p[1] < (unsigned int)p[2]) {
        int* e = (int*)p[1];
        p[1] = p[1] + 0x10;
        if (e != 0) {
            e[0] = 0; e[1] = 0; e[2] = 0;
            ((E16*)e)->Ctor(((int*)value)[0], ((int*)value)[1]);
        }
    } else {
        ((Obj42*)this)->Insert16((int*)p[1], value);
    }
}

// @ 0x00546b70
void Obj42::FUN_00546b70()
{
    int* p = (int*)this;
    if ((unsigned int)p[1] < (unsigned int)p[2]) {
        int e = p[1];
        p[1] = p[1] + 0x118;
        if (e != 0) ((FeedEntry*)e)->Ctor();
    } else {
        FeedEntry tmp;
        tmp.Ctor();
        ((Obj42*)this)->Insert118((int*)p[1], &tmp);
        tmp.Destroy();
    }
}

// @ 0x00546c20  SP::Feed::AtomEntry constructor (0x118-byte entry)
// Byte-exact reproduction is blocked by MSVC 2008 /Od frame slot allocation (slots are
// name-dependent: identical declaration order assigns different frame offsets for different
// local names).  This is a faithful, complete transcription of the original store/call schedule.
int* Obj42::FUN_00546c20()
{
    int* p = (int*)this;

    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0] = (int)gEmptyString; p[1] = p[0]; p[2] = p[0] + 1;
    p[4] = -1; p[5] = -1;

    int* l10 = p + 6;                               // +0x18
    l10[0] = 0; l10[1] = 0; l10[2] = 0;
    l10[0] = (int)gEmptyString; l10[1] = l10[0]; l10[2] = l10[0] + 2;

    p[10] = 0; p[0xb] = 0;
    p[0xc] = -1; p[0xd] = 0x7fffffff;
    p[0xe] = -1; p[0xf] = -1; p[0x10] = -1; p[0x11] = -1;

    int* l14 = p + 0x12;                            // +0x48
    l14[0] = 0; l14[1] = 0; l14[2] = 0;
    l14[0] = (int)gEmptyString; l14[1] = l14[0]; l14[2] = l14[0] + 2;

    p[0x16] = -1; p[0x17] = -1; p[0x18] = -1; p[0x19] = -1;

    int* l18 = p + 0x1a;                            // +0x68
    l18[0] = 0; l18[1] = 0; l18[2] = 0;
    l18[0] = (int)gEmptyString; l18[1] = l18[0]; l18[2] = l18[0] + 2;

    int* l1c = p + 0x1e;                            // +0x78 vector, allocator at +0x84
    l1c[0] = 0; l1c[1] = 0; l1c[2] = 0;
    char tag9;
    ((AllocSub*)((char*)l1c + 0xc))->Ctor(&tag9);

    int* l24 = p + 0x23;                            // +0x8c vector_set
    char tag1d;
    ((VSetSub*)l24)->Ctor(&tag1d);

    int* l2c = p + 0x29;                            // +0xa4 AutoRefCount
    l2c[0] = 0;
    if (l2c[0] != 0) {
        int* t = (int*)l2c[0];
        t[1] = t[1] + 1;
    }

    int* l30 = p + 0x2a;                            // +0xa8
    l30[0] = 0; l30[1] = 0; l30[2] = 0;
    l30[0] = (int)gEmptyString; l30[1] = l30[0]; l30[2] = l30[0] + 1;

    int* l34 = p + 0x2e;                            // +0xb8
    l34[0] = 0; l34[1] = 0; l34[2] = 0;
    l34[0] = (int)gEmptyString; l34[1] = l34[0]; l34[2] = l34[0] + 1;

    p[0x32] = 0; p[0x33] = 0;

    int* l38 = p + 0x34;                            // +0xd0
    l38[0] = 0; l38[1] = 0; l38[2] = 0;
    l38[0] = (int)gEmptyString; l38[1] = l38[0]; l38[2] = l38[0] + 2;

    int* l3c = p + 0x38;                            // +0xe0 vector_set
    char tag39;
    ((VSetSub*)l3c)->Ctor(&tag39);

    ((Vec3Sub*)((char*)p + 0xf8))->SetZero();       // +0xf8 Vector3
    *((char*)p + 0x110) = 0;
    return p;
}
// --- equivalence checker address annotations
    void FNV1_String16(...); // 0x00932f30

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
