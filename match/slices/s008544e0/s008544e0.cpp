// Slice s008544e0 -- SP terrain-export state machine (vtable-driven export helper).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Most of these are cdecl free functions taking the export object as their first
// argument; three of them (FUN_008544e0, FUN_008548a0, FUN_00854990) are __thiscall
// vtable members in the original, where the compiler keeps `this` live in ESI for the
// whole body (so they begin with no prologue).  The object layout below models every
// offset touched by the slice; padding keeps offsets exact.
#include "types.h"

struct cTerrainExport;

// A small vptr-bearing "current job" record: [0]=vptr, +0x14=code, +0x18..+0x20=args.
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

// A "slot record" owned by the +0x144 block: [0..2]=handlers, then state counters.
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

// A per-level descriptor (the +0xf0 array entries), 0x54 bytes.
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

// ---------------------------------------------------------------------------------------------------
// The export object.  Offsets are exact; padding keeps them so.
// ---------------------------------------------------------------------------------------------------
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

// --------------------------------------------------------------------------------------------------
// The rest are plain cdecl functions taking the export object as their first argument (the original
// receives it on the stack, not in ECX).
// --------------------------------------------------------------------------------------------------
int __cdecl jdiv_round_up(int a, int b);           // lib_jpeg::jdiv_round_up @ 0x866850
void FUN_00854b60(cTerrainExport* p);
void FUN_00854d10(cTerrainExport* p);
void FUN_00854d40(cTerrainExport* p);
void FUN_00854db0(cTerrainExport* p, int a3);
void FUN_00854e70(cTerrainExport* p);
__declspec(noinline) void* FUN_00854ed0(cTerrainExport* p);
__declspec(noinline) void* FUN_00854f00(cTerrainExport* p);
void FUN_00854f30(cTerrainExport* p, int a1, int* a2, int a3, int a4);
void FUN_00855150(cTerrainExport* p);
void FUN_008552d0(cTerrainExport* p);

// ===================================================================================================
// 0x00854ed0  cdecl helper: allocate a 0x84-byte record and clear its +0x80 field.
// ===================================================================================================
// @ 0x00854ed0
__declspec(noinline) void* FUN_00854ed0(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[0];
    void* r = ((void*(__cdecl*)(cTerrainExport*, int, int))fn)(p, 0, 0x84);
    *(int*)((char*)r + 0x80) = 0;
    return r;
}

// ===================================================================================================
// 0x00854f00  cdecl helper: allocate a 0x118-byte record and clear its +0x114 field.
// ===================================================================================================
// @ 0x00854f00
__declspec(noinline) void* FUN_00854f00(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[0];
    void* r = ((void*(__cdecl*)(cTerrainExport*, int, int))fn)(p, 0, 0x118);
    *(int*)((char*)r + 0x114) = 0;
    return r;
}

// ===================================================================================================
// 0x00854d10  advance: reset slot 0xc, then call +0x154[2] and +0x154[3].
// ===================================================================================================
// @ 0x00854d10
void FUN_00854d10(cTerrainExport* p)
{
    ((cSlot*)p->m144)->m0C = 0;
    void* a = p->m154;
    void* f2 = *(void**)((char*)a + 8);
    ((void(__cdecl*)(cTerrainExport*))f2)(p);
    void* b = p->m154;
    void* f3 = *(void**)((char*)b + 0xc);
    ((void(__cdecl*)(cTerrainExport*))f3)(p);
}

// ===================================================================================================
// 0x00854d40  advance the slot state machine; calls +0x164[2] first.
// ===================================================================================================
// @ 0x00854d40
void FUN_00854d40(cTerrainExport* p)
{
    cSlot* s = (cSlot*)p->m144;
    void* base = p->m164;
    void* f = *(void**)((char*)base + 8);
    ((void(__cdecl*)(cTerrainExport*))f)(p);

    switch (s->m14) {
    case 0:
        s->m14 = 2;
        if (p->m0B0 != 0)
            goto tail18;
        goto tail20;
    case 1:
        s->m18 = s->m18 + 1;
        s->m14 = 2;
        return;
    case 2:
        if (p->m0B0 == 0)
            goto tail20;
        s->m20 = s->m20 + 1;
        s->m18 = s->m18 + 1;
        s->m14 = 1;
        return;
    default:
        goto tail18;
    }
tail20:
    s->m20 = s->m20 + 1;
tail18:
    s->m18 = s->m18 + 1;
}

// ===================================================================================================
// 0x00854e70  call alloc-slot +0x24 with arg 1, then set m010 from m00C != 0.
// ===================================================================================================
// @ 0x00854e70
void FUN_00854e70(cTerrainExport* p)
{
    void** vt = (void**)p->mAllocVtbl;
    void* fn = vt[9];
    ((void(__cdecl*)(cTerrainExport*, int))fn)(p, 1);
    p->m010 = (p->m00C != 0) ? 200 : 100;
}

// ===================================================================================================
// 0x00854db0  install the 3-entry slot table and initialise job bookkeeping.
// ===================================================================================================
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

// ===================================================================================================
// 0x008548a0  pick the per-level descriptor array, fill m0F0[] and the +0x134 group.
// ===================================================================================================
// @ 0x008548a0
void cTerrainExport::FUN_008548a0()
{
    if (m0A4 != 0) {
        int* q = (int*)((char*)m0A4 + ((cSlot*)m144)->m20 * 0x24);
        m0EC = q[0];
        if (q[0] > 0) {
            cLevel** dst = m0F0;
            int* src = q + 1;
            int i = 0;
            do {
                *dst = (cLevel*)(*src * 0x54 + m03C);
                src++;
                i++;
                dst++;
            } while (i < q[0]);
        }
        m134 = q[5];
        m138 = q[6];
        m13C = q[7];
        m140 = q[8];
        return;
    }
    if (m034 > 4) {
        cJob* j = mJob;
        j->m14 = 0x18;
        j->m18 = m034;
        j->m1C = 4;
        j->Error();
    }
    int n = m034;
    m0EC = n;
    if (n > 0) {
        cLevel** dst = m0F0;
        int off = 0;
        int i = 0;
        do {
            *dst = (cLevel*)(m03C + off);
            off += 0x54;
            i++;
            dst++;
        } while (i < n);
    }
    m134 = 0;
    m138 = 0x3f;
    m13C = 0;
    m140 = 0;
}

// ===================================================================================================
// 0x008544e0  validate the job table and stamp the per-level occupancy maps.
// ===================================================================================================
// @ 0x008544e0
void cTerrainExport::FUN_008544e0()
{
    int i;
    int local_a30[10];
    unsigned int auStack_a08[16 * 0x40];

    if (m0A0 < 1) {
        cJob* j = mJob;
        j->m14 = 0x11;
        j->m18 = 0;
        j->Error();
    }

    int* pj = m0A4;
    if (pj[5] == 0 && pj[6] == 0x3f) {
        m0DC = 0;
        if (m034 >= 1) {
            int n = m034;
            for (i = 0; i < n; i++)
                local_a30[i] = 0;
        }
    } else {
        m0DC = 1;
        if (m034 >= 1) {
            int n = m034 & 0xffffff;
            for (i = 0; i < (n << 6); i++)
                auStack_a08[i] = 0xffffffff;
        }
    }

    int job = 1;
    if (m0A0 < 1)
        goto done;
    do {
        int cnt = pj[0];
        if (cnt < 1 || cnt > 4) {
            cJob* j = mJob;
            j->m14 = 0x18;
            j->m18 = cnt;
            j->m1C = 4;
            j->Error();
        }
        for (i = 0; i < cnt; i++) {
            int lv = pj[i + 1];
            if (lv < 0 || m034 <= lv) {
                cJob* j = mJob;
                j->m14 = 0x11;
                j->m18 = job;
                j->Error();
            }
            if (i > 0 && lv <= pj[i]) {
                cJob* j = mJob;
                j->m14 = 0x11;
                j->m18 = job;
                j->Error();
            }
        }

        unsigned int u5 = (unsigned int)pj[5];
        int u6 = pj[6];
        unsigned int u2 = (unsigned int)pj[7];
        unsigned int u3 = (unsigned int)pj[8];

        if (m0DC == 0) {
            if (u5 != 0 || u6 != 0x3f || u2 != 0 || u3 != 0) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            int c2 = cnt;
            int* pp = pj;
            if (c2 > 0) {
                do {
                    int lv = pp[1];
                    if (local_a30[lv] != 0) {
                        cJob* j = mJob;
                        j->m14 = 0x11;
                        j->m18 = job;
                        j->Error();
                    }
                    c2--;
                    local_a30[lv] = 1;
                    pp++;
                } while (c2 != 0);
            }
        } else {
            if (u5 > 0x3f || (int)u6 < (int)u5 ||
                u6 > 0x3f || u2 > 0xd || (int)u3 < 0 || u3 > 0xd) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            if (u5 == 0) {
                if (u6 != 0) {
                    cJob* j = mJob;
                    j->m14 = 0xf;
                    j->m18 = job;
                    j->Error();
                }
            } else if (cnt != 1) {
                cJob* j = mJob;
                j->m14 = 0xf;
                j->m18 = job;
                j->Error();
            }
            int c3 = cnt;
            int* pp = pj;
            if (c3 > 0) {
                do {
                    pp++;
                    unsigned int* row = auStack_a08 + (*pp) * 0x40;
                    unsigned int k = u5;
                    if (u5 != 0 && (int)*row < 0) {
                        cJob* j = mJob;
                        j->m14 = 0xf;
                        j->m18 = job;
                        j->Error();
                    }
                    for (; (int)k <= u6; k++) {
                        if ((int)row[k] < 0) {
                            if (u2 != 0) {
                                cJob* j = mJob;
                                j->m14 = 0xf;
                                j->m18 = job;
                                j->Error();
                            }
                        } else if (u2 != row[k] || u3 != u2 - 1) {
                            cJob* j = mJob;
                            j->m14 = 0xf;
                            j->m18 = job;
                            j->Error();
                        }
                        row[k] = u3;
                    }
                    c3--;
                } while (c3 != 0);
            }
        }

        job++;
        pj += 9;
    } while (job <= m0A0);

done:
    i = 0;
    if (m0DC == 0) {
        if (m034 > 0) {
            do {
                if (local_a30[i] == 0) {
                    cJob* j = mJob;
                    j->m14 = 0x2c;
                    j->Error();
                }
                i++;
            } while (i < m034);
        }
    } else if (m034 > 0) {
        unsigned int* row = auStack_a08;
        do {
            if ((int)*row < 0) {
                cJob* j = mJob;
                j->m14 = 0x2c;
                j->Error();
            }
            i++;
            row += 0x40;
        } while (i < m034);
    }
}

// ===================================================================================================
// 0x00854b60  per-tile driver: dispatch on the slot state and drive the pipeline.
// ===================================================================================================
// @ 0x00854b60
void FUN_00854b60(cTerrainExport* p)
{
    cSlot* s = (cSlot*)p->m144;
    int st = s->m14;

    if (st == 0) {
        p->FUN_008548a0();
        p->FUN_00854990();
        if (p->m0A8 == 0) {
            ((void(__cdecl*)(cTerrainExport*))p->m158)(p);
            ((void(__cdecl*)(cTerrainExport*))p->m15C)(p);
            ((void(__cdecl*)(cTerrainExport*, int))p->m14C)(p, 0);
        }
        ((void(__cdecl*)(cTerrainExport*))p->m160)(p);
        ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, p->m0B0);
        ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, s->m1C < 2 ? 3 : 2);
        ((void(__cdecl*)(cTerrainExport*, int))p->m148)(p, 0);
        s->m0C = (p->m0B0 == 0);
    } else if (st == 1) {
        p->FUN_008548a0();
        p->FUN_00854990();
        if (p->m134 != 0 || p->m13C == 0 || p->m0AC != 0) {
            ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, 1);
            ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, 2);
            s->m0C = 0;
            goto tail;
        }
        s->m18 = s->m18 + 1;
        s->m14 = 2;
    } else if (st != 2) {
        cJob* j = p->mJob;
        j->m14 = 0x2f;
        j->Error();
        goto tail;
    }

    if (p->m0B0 == 0) {
        p->FUN_008548a0();
        p->FUN_00854990();
    }
    ((void(__cdecl*)(cTerrainExport*, int))p->m164)(p, 0);
    ((void(__cdecl*)(cTerrainExport*, int))p->m150)(p, 2);
    if (s->m20 == 0)
        ((void(__cdecl*)(cTerrainExport*))((void**)p->m154)[2])(p);
    ((void(__cdecl*)(cTerrainExport*))((void**)p->m154)[3])(p);
    s->m0C = 0;

tail:
    s->m10 = (s->m18 == s->m1C - 1);
    if (p->m008 != 0) {
        *(int*)((char*)p->m008 + 0xc) = s->m18;
        *(int*)((char*)p->m008 + 0x10) = s->m1C;
    }
}

// @ 0x00854f30
void FUN_00854f30(cTerrainExport* p, int a1, int* a2, int a3, int a4)
{
    if (p->m010 != 100) {
        cJob* j = p->mJob;
        j->m14 = 0x12;
        j->m18 = p->m010;
        j->Error();
    }
    int* slots = &p->m040;
    if (slots[a1] == 0)
        slots[a1] = (int)FUN_00854ed0(p);

    unsigned short* out = (unsigned short*)slots[a1];
    int* src = a2;
    int off = 0;
    do {
        int v;
        v = (src[0] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 0] = (unsigned short)v;

        v = (src[1] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 1] = (unsigned short)v;

        v = (src[2] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 2] = (unsigned short)v;

        v = (src[3] * a3 + 0x32) / 100;
        if (v < 1) v = 1;
        else if (v > 0x7fff) v = 0x7fff;
        if (a4 != 0 && v > 0xff) v = 0xff;
        out[off + 3] = (unsigned short)v;

        off += 4;
        src += 4;
    } while (off < 0x40);

    slots[a1] = slots[a1];
    ((int*)slots[a1])[0x80 / 4] = 0;
}

// --------------------------------------------------------------------------------------------------
// Blob copy helper used by the two table builders: those functions build four 0x118-byte records
// from four (header-dwords + byte, 0x40-dword table) global pairs.
// --------------------------------------------------------------------------------------------------
struct BlobTab { int v[0x40]; };

struct BlobSrc {
    int  h0, h1, h2, h3;             // +0x00 header dwords
    unsigned char b;                 // +0x10 header byte
    unsigned char pad[3];
    BlobTab tab;                     // +0x14 table (0x100 bytes)
};

static __forceinline void FillBlob(cTerrainExport* p, int* slot, BlobSrc* src)
{
    if (*slot == 0)
        *slot = (int)FUN_00854f00(p);
    {
        int* buf = (int*)*slot;
        buf[0] = src->h0;
        buf[1] = src->h1;
        buf[2] = src->h2;
        buf[3] = src->h3;
        *(unsigned char*)(buf + 4) = src->b;
    }
    *(BlobTab*)((char*)*slot + 0x11) = src->tab;
    *(int*)((char*)*slot + 0x114) = 0;
}

extern BlobSrc g141d010;
extern BlobSrc g141d050;
extern BlobSrc g141d030;
extern BlobSrc g141d10c;

// ===================================================================================================
// 0x00855150  build the four low table records from the 0x141d0xx global pairs.
// ===================================================================================================
// @ 0x00855150
void FUN_00855150(cTerrainExport* p)
{
    FillBlob(p, &p->m040 + 4, &g141d010);
    FillBlob(p, &p->m040 + 8, &g141d050);
    FillBlob(p, &p->m040 + 5, &g141d030);
    FillBlob(p, &p->m040 + 9, &g141d10c);
}

// ===================================================================================================
// 0x008552d0  build the four high table records from the 0x141d0xx global pairs.
// ===================================================================================================
// @ 0x008552d0
void FUN_008552d0(cTerrainExport* p)
{
    FillBlob(p, &p->m0B0 + 1, &g141d010);
    FillBlob(p, &p->m0B0 + 5, &g141d050);
    FillBlob(p, &p->m0B0 + 2, &g141d030);
    FillBlob(p, &p->m0B0 + 6, &g141d10c);
}

// ===================================================================================================
// 0x00854990  compute the per-level tile layout tables (m100/m104/m108/m10C) and m0C0.
// ===================================================================================================
// @ 0x00854990
void cTerrainExport::FUN_00854990()
{
    int e = m0EC;
    if (e == 1) {
        cLevel* lv = m0F0[0];
        m100 = lv->m1C;
        m104 = lv->m20;
        unsigned int a = (unsigned int)lv->m0C;
        unsigned int b = (unsigned int)lv->m20;
        unsigned int quo = b / a;
        unsigned int rem = b % a;
        lv->m34 = 1;
        lv->m38 = 1;
        lv->m3C = 1;
        lv->m40 = 8;
        lv->m44 = 1;
        if (rem == 0)
            rem = a;
        lv->m48 = (int)rem;
        m108 = 1;
        m10C[0] = 0;
        (void)quo;
    } else {
        if (e < 1 || e > 4) {
            cJob* j = mJob;
            j->m14 = 0x18;
            j->m18 = e;
            j->m1C = 4;
            j->Error();
        }
        m100 = jdiv_round_up(m018, m0E0 * 8);
        m104 = jdiv_round_up(m01C, m0E4 * 8);
        m108 = 0;
        if (e > 0) {
            int idx = 0;
            for (int i = 0; i < e; i++) {
                cLevel* lv = m0F0[i];
                unsigned int w = (unsigned int)lv->m08;
                lv->m40 = (int)(w * 8);
                unsigned int rem = (unsigned int)lv->m1C % w;
                unsigned int c = (unsigned int)lv->m0C;
                int prod = (int)(c * w);
                lv->m34 = (int)w;
                lv->m38 = (int)c;
                lv->m3C = prod;
                if (rem == 0)
                    rem = w;
                lv->m44 = (int)rem;
                unsigned int rem2 = (unsigned int)lv->m20 % c;
                if (rem2 == 0)
                    rem2 = c;
                lv->m48 = (int)rem2;
                if (m108 + prod > 10) {
                    cJob* j = mJob;
                    j->m14 = 0xb;
                    j->Error();
                }
                for (int k = prod; k > 0; k--) {
                    m10C[m108] = (void*)idx;
                    m108 = m108 + 1;
                }
                idx++;
            }
        }
    }
    if (m0C4 > 0) {
        int v = m100 * m0C4;
        if (v >= 0xffff)
            v = 0xffff;
        m0C0 = v;
    }
}
