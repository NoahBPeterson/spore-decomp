// src/game/UTFSpore_Win32/jccolor.cpp -- migrated from slice(s) s008544e0, s0084faf0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/jccolor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void FUN_00852ff0(void*);           // 0x00852ff0

// ---- items of slice s0084faf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_00852ff0(void*);           // 0x00852ff0
// ---- items of slice s0084faf0 end

// ---- items of slice s008544e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTerrainExport;
struct cJob {
    void** mVtbl;                    // +0x00
    int    m04;
    int    m08;
    int    m0C;
    int    m10;
    int    m14;                      // error code
    int    m18;                      // error arg0
    int    m1C;                      // error arg1
    int    m20;                      // error arg2
    void   Error() { ((void(__thiscall*)(cJob*))mVtbl[0])(this); }
};
struct cSlot {
    void* pfn0;                      // +0x00 = 0x00854b60
    void* pfn4;                      // +0x04 = 0x00854d10
    void* pfn8;                      // +0x08 = 0x00854d40
    int   m0C;                       // +0x0c
    int   m10;                       // +0x10
    int   m14;                       // +0x14  state
    int   m18;                       // +0x18  progress
    int   m1C;                       // +0x1c  total
    int   m20;                       // +0x20  extra counter
};
struct cLevel {
    int  m00;
    int  m04;
    int  m08;
    int  m0C;
    int  m10;
    int  m14;
    int  m18;
    int  m1C;
    int  m20;
    int  m24;
    int  m28;
    int  m2C;
    int  m30;
    int  m34;
    int  m38;
    int  m3C;
    int  m40;
    int  m44;
    int  m48;
};
struct cTerrainExport
{
    cJob*  mJob;                     // +0x000  (vtable-bearing error reporter)
    void** mAllocVtbl;               // +0x004  allocator vtable: slots called as Ty(this,...)
    void*  m008;                     // +0x008  optional progress sink
    int    m00C;                     // +0x00c
    int    m010;                     // +0x010
    int    m014;                     // +0x014
    int    m018;                     // +0x018
    int    m01C;                     // +0x01c
    int    m020;                     // +0x020
    int    m024;                     // +0x024
    int    m028;                     // +0x028
    int    m02C;                     // +0x02c
    int    m030;                     // +0x030
    int    m034;                     // +0x034  level count
    int    m038;                     // +0x038
    int    m03C;                     // +0x03c  base pointer for level stride
    int    m040;                     // +0x040
    int    m044[23];                 // +0x044 .. +0x09f
    int    m0A0;                     // +0x0a0  job count
    int*   m0A4;                     // +0x0a4  per-job descriptor array (0x24 bytes each)
    int    m0A8;                     // +0x0a8
    int    m0AC;                     // +0x0ac
    int    m0B0;                     // +0x0b0
    int    m0B4;                     // +0x0b4
    int    m0B8;                     // +0x0b8
    int    m0BC;                     // +0x0bc
    int    m0C0;                     // +0x0c0
    int    m0C4;                     // +0x0c4
    int    m0C8;                     // +0x0c8
    int    m0CC;                     // +0x0cc
    int    m0D0;                     // +0x0d0
    int    m0D4;                     // +0x0d4
    int    m0D8;                     // +0x0d8
    int    m0DC;                     // +0x0dc
    int    m0E0;                     // +0x0e0
    int    m0E4;                     // +0x0e4
    int    m0E8;                     // +0x0e8
    int    m0EC;                     // +0x0ec  level count in use
    cLevel* m0F0[4];                 // +0x0f0  per-level pointers (max 4)
    int    m100;                     // +0x100
    int    m104;                     // +0x104
    int    m108;                     // +0x108  running count
    void*  m10C[10];                 // +0x10c  filled level table (+0x10c..+0x133)
    int    m134;                     // +0x134
    int    m138;                     // +0x138
    int    m13C;                     // +0x13c
    int    m140;                     // +0x140
    cSlot* m144;                     // +0x144  slot block (vtbl-carrier)
    void*  m148;                     // +0x148
    int    m14C;                     // +0x14c
    int    m150;                     // +0x150
    void*  m154;                     // +0x154  fn-pointer table (slots at +8/+0xc)
    void*  m158;                     // +0x158
    void*  m15C;                     // +0x15c
    void*  m160;                     // +0x160
    void*  m164;                     // +0x164  fn-pointer table (slot at +8)

    // __thiscall vtable members of the export object
    void FUN_008544e0();
    void FUN_008548a0();
    void FUN_00854990();
};
void FUN_00854db0(cTerrainExport* p, int a3);
// ---- items of slice s008544e0 end

// @ 0x00850380
void SetTableNext(int* cinfo, int value)
{
    if (cinfo[0x10] != 0)
        *(int*)(cinfo[0x10] + 0x80) = value;
    if (cinfo[0x11] != 0)
        *(int*)(cinfo[0x11] + 0x80) = value;
    if (cinfo[0x12] != 0)
        *(int*)(cinfo[0x12] + 0x80) = value;
    if (cinfo[0x13] != 0)
        *(int*)(cinfo[0x13] + 0x80) = value;

    int* p = cinfo + 0x18;
    int k = 4;
    do {
        if (p[-4] != 0)
            *(int*)(p[-4] + 0x114) = value;
        if (p[0] != 0)
            *(int*)(p[0] + 0x114) = value;
        ++p;
        --k;
    } while (k != 0);
}

// @ 0x00850570
void jpeg_finish_compress2(int* cinfo, int a2)
{
    if (cinfo[4] != 100) {
        *(int*)(cinfo[0] + 0x14) = 0x12;
        *(int*)(cinfo[0] + 0x18) = cinfo[4];
        ((void (*)(int*))*(int*)(cinfo[0]))(cinfo);
    }
    if (a2 != 0)
        SetTableNext(cinfo, 0);
    ((void (*)(int*))*(int*)(cinfo[0] + 0x10))(cinfo);
    ((void (*)(int*))*(int*)(cinfo[5] + 8))(cinfo);
    FUN_00852ff0(cinfo);
    ((void (*)(int*))*(int*)(cinfo[0x51]))(cinfo);
    cinfo[0x36] = 0;
    cinfo[4] = (cinfo[0x2a] != 0) + 0x65;
}

// @ 0x00854db0
void FUN_00854db0(cTerrainExport* p, int a3)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[0];
    cSlot* s = (cSlot*)((void*(__cdecl*)(cTerrainExport*, int, int))fn)(p, 1, 0x24);
    p->m144 = s;
    s->pfn0 = (void*)0x00854b60;
    s->pfn4 = (void*)0x00854d10;
    s->pfn8 = (void*)0x00854d40;
    s->m10 = 0;
    ((void(__cdecl*)(cTerrainExport*))0x00854300)(p);
    if (p->m0A4 == 0) {
        p->m0DC = 0;
        p->m0A0 = 1;
    } else {
        p->FUN_008544e0();
    }
    if (p->m0DC != 0)
        p->m0B0 = 1;
    if (a3 == 0)
        s->m14 = 0;
    else
        s->m14 = 2 - (p->m0B0 != 0 ? 1 : 0);
    s->m20 = 0;
    s->m18 = 0;
    if (p->m0B0 != 0)
        s->m1C = p->m0A0 * 2;
    else
        s->m1C = p->m0A0;
}
