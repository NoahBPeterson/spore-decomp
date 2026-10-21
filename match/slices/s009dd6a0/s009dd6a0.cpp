// Slice s009dd6a0 — frozen batch gold4 (slice 139)
//
// The "Gait" (Track2) animation block-connection builder family.  These functions walk the
// Track2 record layout (0xa4-byte per-block descriptor, containing dynamic arrays of 0x44-
// stride item headers, 0x58-stride cone groups and 0x1c-stride weight records), merge the
// per-block arrays into one flat "bingr" (GAIT) blob, and expose a handful of ArgScript
// command entry points that fill the same records from script arguments.
//
// Offsets were read straight from the retail disassembly; keep them in sync.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef int            i32;
typedef unsigned long  ulong;

extern "C" void* __cdecl operator_new(u32 size, const char* name, int a, int b, int c, int d); // 0x00f473a0 EAAllocate wrapper
extern "C" void  __cdecl operator_delete__(void* p);      // 0x00f47380

// --------------------------------------------------------------------------- helpers
namespace {

struct cArguments;                                        // EA::ArgScript::cArguments
struct Curve760 { void CopyInto(char* dst); };            // 0x009dc760
struct Track2;                                            // this type

void  FUN_009dc760(Curve760* c, char* dst);               // 0x009dc760  CopyInto
i32   Track2_TotalItems(Track2* t);                       // 0x009dc6a0  Track2::TotalItems
void  FUN_009dd780(Track2* t, void* p);                   // 0x009dd780  (defined below)
i32   FUN_009dd6a0(Track2* t);                            // 0x009dd6a0  (defined below)

// The ArgScript argument block.  MainArguments returns the raw 32-bit argument array.
struct cArguments {
    u32* MainArguments(int n);                            // 0x00838320
};

// The evaluated float object: picks the +0x98 vtable slot (a thiscall returning float).
struct FloatEval {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37();   // +0x94
    virtual float Eval(i32 v);                // +0x98
};

// A Track2 block descriptor (0xa4 bytes).  Only the touched members are named.
struct Block {
    u8  pad00[0x0c];
    i32 mHitTest;            // +0x0c  (0xffffffff = empty slot)
    i32 mPointsBegin;        // +0x10
    i32 mPointsEnd;          // +0x14
    u8  pad18[0x08];
    i32 mIdsBegin;           // +0x20
    i32 mIdsEnd;             // +0x24
    i32 mGroupsBegin;        // +0x28
    u32 mGroupsEnd;          // +0x2c
    u8  pad30[0x08];
    float mTime;             // +0x38
    float mCone[7];          // +0x3c .. +0x57
    u8  pad58[0x4c];
};

// The Track2 object.  `mBlockCount`/`mBlocks` prefix an inline data region; the walk uses
// 0xa4-byte strides.
struct Track2 {
    u8  pad00[0x18];
    u32 mCount;              // +0x18
    Block* mBlocks;          // +0x1c

    void Grids(void* p);                              // 0x009dd780
    i32  ItemCount();                                 // 0x009dd6a0
    i32  TotalItems();                                // 0x009dc6a0
};

// The evaluated-argument host: self+0xc is the track2/block owner chain, self+4 is the
// float-evaluator object whose +0x98 vtable slot converts script tokens to float.
struct Self {
    u8  pad00[0x04];
    FloatEval* mEval;        // +0x04
    u8  pad08[0x04];
    i32 mOwner;              // +0x0c

    void Cmd3(cArguments* a);                         // 0x009ddca0
    void Cmd4(cArguments* a);                         // 0x009ddcf0
    void CmdTable8(cArguments* a);                    // 0x009ddd70
    void CmdTable16(cArguments* a);                   // 0x009ddf80
};

}  // (anonymous)

// ===========================================================================
// @ 0x009dd6a0
// Sums, over every block and every item header in it, the rounded-up sizes of the three
// sub-arrays (points/0x44, groups/0x58, weights/0x1c).  Returns the running total.
i32 Track2::ItemCount()
{
    i32 total = 0;
    u32 nb = mCount;
    if (nb != 0) {
        Block* b = (Block*)((u8*)mBlocks + 0x24);
        u32 bn = nb;
        for (;;) {
            i32 n = (*(i32*)((u8*)b + 4) - *(i32*)b) >> 6;
            if (n != 0) {
                i32* it = (i32*)(*(i32*)b + 0x30);
                u32 k = 0;
                do {
                    // sub-array counts at it-0x28/it-0x2c, it-0x14/it-0x18, it-0x0/it-0x4
                    total += ((*(it - 10) - *(it - 11)) / 0x44) * 0x44;
                    total += ((*(it - 5)  - *(it - 6))  / 0x58) * 0x58;
                    total += ((*(it)      - *(it - 1))  / 0x1c) * 0x1c;
                    total += 0xc;
                    ++k;
                    it += 0x10;
                } while (k < (u32)n);
            }
            b = (Block*)((u8*)b + 0xa4);
            if (--bn == 0) break;
        }
    }
    return total;
}

// ===========================================================================
// @ 0x009dd780
// Serialises the Track2 blocks into the flat GAIT blob.  `dst` points at the scratch header
// whose +0x18 follows an array of pointers; the +0x10 field holds the current pointer-array
// count and is used to skip past it.
void __thiscall Track2::Grids(void* dstp)
{
    u8*  dst = (u8*)dstp;
    u8*  cur;
    u32  bi;

    *(i32*)(dst + 0x14) = (i32)mCount;
    cur = dst + 0x18 + *(i32*)(dst + 0x10) * 8;
    bi = 0;
    if (mCount == 0) return;

    for (;;) {
        Block* b = (Block*)((u8*)mBlocks + bi * 0xa4);
        u8*  tmp = cur;

        if (b->mHitTest == -1) goto next;

        // header copy: 0x1c words
        {
            u8* s = (u8*)b;
            *(u32*)(cur + 0x00) = *(u32*)(s + 0x00);
            *(u32*)(cur + 0x04) = *(u32*)(s + 0x04);
            *(u32*)(cur + 0x08) = *(u32*)(s + 0x08);
            *(u32*)(cur + 0x0c) = *(u32*)(s + 0x38);
            *(u32*)(cur + 0x10) = *(u32*)(s + 0x3c);
            *(u32*)(cur + 0x14) = *(u32*)(s + 0x40);
            *(u32*)(cur + 0x18) = *(u32*)(s + 0x44);
            *(u32*)(cur + 0x1c) = *(u32*)(s + 0x48);
            *(u32*)(cur + 0x20) = *(u32*)(s + 0x4c);
            *(u32*)(cur + 0x24) = *(u32*)(s + 0x50);
            *(u32*)(cur + 0x28) = *(u32*)(s + 0x54);
            *(u32*)(cur + 0x2c) = *(u32*)(s + 0x58);
            *(u32*)(cur + 0x30) = *(u32*)(s + 0x5c);
            *(u32*)(cur + 0x34) = *(u32*)(s + 0x60);
            *(u32*)(cur + 0x38) = *(u32*)(s + 0x64);
            *(u32*)(cur + 0x3c) = *(u32*)(s + 0x68);
            *(u32*)(cur + 0x40) = *(u32*)(s + 0x6c);
            *(u32*)(cur + 0x44) = *(u32*)(s + 0x70);
            *(u32*)(cur + 0x48) = *(u32*)(s + 0x74);
            *(u32*)(cur + 0x4c) = *(u32*)(s + 0x78);
            *(u32*)(cur + 0x50) = *(u32*)(s + 0x7c);
            *(u32*)(cur + 0x54) = *(u32*)(s + 0x80);
            *(u32*)(cur + 0x58) = *(u32*)(s + 0x84);
            *(u32*)(cur + 0x5c) = *(u32*)(s + 0x88);
            *(u32*)(cur + 0x60) = *(u32*)(s + 0x8c);
            *(u32*)(cur + 0x64) = *(u32*)(s + 0x90);
            *(u32*)(cur + 0x68) = *(u32*)(s + 0x94);
            *(u32*)(cur + 0x6c) = *(u32*)(s + 0x98);
            *(u32*)(cur + 0x70) = *(u32*)(s + 0x9c);
        }

        // point-pair count and the static pair array (0x74 = (end-begin)/0xc)
        {
            i32 n = (*(i32*)((u8*)b + 0x14) - *(i32*)((u8*)b + 0x10)) / 0xc;
            i32* ptr = (i32*)((u8*)b + 0x10);
            i32* dst74 = (i32*)(cur + 0x74);
            *dst74 = n;
            tmp = (u8*)b + 0x7c;
            if (n != 0) {
                i32 j = 0;
                u8* o = (u8*)cur + 0x7c;
                for (i32 i = 0; i < n; ++i) {
                    *(float*)o = *(float*)(*ptr + j);
                    *(float*)(o + 4) = *(float*)(*ptr + j + 4);
                    o += 8;
                    j += 0xc;
                }
                tmp = o;
            }
            (void)dst74;
        }

        // item-group count (+0x78 = (end-begin)>>6)
        {
            i32 ngroups = (*(i32*)((u8*)b + 0x28) - *(i32*)((u8*)b + 0x24)) >> 6;
            *(i32*)(cur + 0x78) = ngroups;
            u32 gi = 0;
            u8* out = tmp;
            if (ngroups == 0) goto after_groups;

            for (;;) {
                u8* g = (u8*)(*(i32*)((u8*)b + 0x24) + gi * 0x40);
                i32 na, nb, nc;
                *(i32*)out = (*(i32*)(g + 8) - *(i32*)(g + 4)) / 0x44;
                *(i32*)(out + 4) = (*(i32*)(g + 0x1c) - *(i32*)(g + 0x18)) / 0x58;
                *(i32*)(out + 8) = (*(i32*)(g + 0x30) - *(i32*)(g + 0x2c)) / 0x1c;
                na = *(i32*)out;
                nb = *(i32*)(out + 4);
                nc = *(i32*)(out + 8);

                u8* p = out + 0xc;                        // item array start

                // item headers: 0x44 bytes each, 0x11 dwords copied
                for (i32 i = 0; i < na; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 4) + i * 0x44);
                    u8* d = p + i * 0x44;
                    *(u32*)(d + 0x00) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x18);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x1c);
                    *(u32*)(d + 0x1c) = *(u32*)(src + 0x20);
                    *(u32*)(d + 0x20) = *(u32*)(src + 0x24);
                    *(u32*)(d + 0x24) = *(u32*)(src + 0x28);
                    *(u32*)(d + 0x28) = *(u32*)(src + 0x2c);
                    *(u32*)(d + 0x2c) = *(u32*)(src + 0x30);
                    *(u32*)(d + 0x30) = *(u32*)(src + 0x34);
                    *(u32*)(d + 0x34) = *(u32*)(src + 0x38);
                    *(u32*)(d + 0x38) = *(u32*)(src + 0x3c);
                    *(u32*)(d + 0x3c) = *(u32*)(src + 0x40);
                    *(u32*)(d + 0x40) = *(u32*)(src + 0x44);
                }
                p += na * 0x44;

                // cone groups: 0x58 bytes each, 0x16 dwords copied
                for (i32 i = 0; i < nb; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 0x18) + i * 0x58);
                    u8* d = p + i * 0x58;
                    *(u32*)(d + 0x00) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x18);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x1c);
                    *(u32*)(d + 0x1c) = *(u32*)(src + 0x20);
                    *(u32*)(d + 0x20) = *(u32*)(src + 0x24);
                    *(u32*)(d + 0x24) = *(u32*)(src + 0x28);
                    *(u32*)(d + 0x28) = *(u32*)(src + 0x2c);
                    *(u32*)(d + 0x2c) = *(u32*)(src + 0x30);
                    *(u32*)(d + 0x30) = *(u32*)(src + 0x34);
                    *(u32*)(d + 0x34) = *(u32*)(src + 0x38);
                    *(u32*)(d + 0x38) = *(u32*)(src + 0x3c);
                    *(u32*)(d + 0x3c) = *(u32*)(src + 0x40);
                    *(u32*)(d + 0x40) = *(u32*)(src + 0x44);
                    *(u32*)(d + 0x44) = *(u32*)(src + 0x48);
                    *(u32*)(d + 0x48) = *(u32*)(src + 0x4c);
                    *(u32*)(d + 0x4c) = *(u32*)(src + 0x50);
                    *(u32*)(d + 0x50) = *(u32*)(src + 0x54);
                }
                p += nb * 0x58;

                // weight records: 0x1c bytes each, header at p, 4 dwords after a 2-dword gap
                for (i32 i = 0; i < nc; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 0x2c) + i * 0x1c);
                    u8* d = p + i * 0x1c;
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x18);
                }
                p += nc * 0x1c;

                out = p;
                if (++gi >= (u32)ngroups) break;
            }
            tmp = out;
        }

    after_groups:
        cur = tmp;

    next:
        if (++bi >= mCount) break;
    }
    return;
}

// ===========================================================================
// @ 0x009ddca0
// Reads 3 script args, evaluates each through the +0x98 slot, and stores the resulting
// float into the block payload at +0x84 (record base + 0x7c + 8).
void Self::Cmd3(cArguments* args)
{
    u32* a = args->MainArguments(3);
    i32 off = (i32)(*(u8**)((u8*)mOwner + 4) + 0x7c) - (i32)a;
    i32 n = 3;
    do {
        float f = mEval->Eval((i32)*a);
        *(float*)(off + (i32)a) = f;
        ++a;
        n = n - 1;
    } while (n != 0);
}

// @ 0x009ddcf0
// Same as above but 4 args into the block payload ending at +0x24.
void Self::Cmd4(cArguments* args)
{
    u32* a = args->MainArguments(4);
    i32 off = (i32)(*(u8**)((u8*)mOwner + 4) + 0x24) - (i32)a;
    i32 n = 4;
    do {
        float f = mEval->Eval((i32)*a);
        *(float*)(off + (i32)a) = f;
        ++a;
        n = n - 1;
    } while (n != 0);
}

// @ 0x009ddd70
// Fills a small fixed-size table inside the block currently selected by the +0xc4
// "layout mode": mode 0 -> 3 records of 2 bytes at 0x10 stride, mode 1 -> 4 records of
// 2 bytes, mode 2 -> 2 records of 1 byte.
void Self::CmdTable8(cArguments* args)
{
    u8*  base = *(u8**)((u8*)mOwner + 4);
    i32 mode = *(i32*)(base + 0xc4);

    if (mode == 0) {
        u32* a = args->MainArguments(6);
        u8*  p = base + (*(i32*)(base + 0xd8) - *(i32*)(base + 0xd4)) / 0x44 * 0x44
                    + *(i32*)(base + 0xd4) - 0x28;
        for (i32 r = 0; r < 3; ++r) {
            for (i32 c = 0; c < 2; ++c) {
                float f = mEval->Eval((i32)*a++);
                *(u8*)(p + c) = (u8)(i32)f;
            }
            p += 0x10;
        }
    } else if (mode == 1) {
        u32* a = args->MainArguments(8);
        u8*  p = base + (*(i32*)(base + 0xec) - *(i32*)(base + 0xe8)) / 0x58 * 0x58
                    + *(i32*)(base + 0xe8) - 0x38;
        for (i32 r = 0; r < 4; ++r) {
            for (i32 c = 0; c < 2; ++c) {
                float f = mEval->Eval((i32)*a++);
                *(u8*)(p + c) = (u8)(i32)f;
            }
            p += 0x10;
        }
    } else if (mode == 2) {
        u32* a = args->MainArguments(2);
        u8*  p = base + (*(i32*)(base + 0x100) - *(i32*)(base + 0xfc)) / 0x1c * 0x1c
                    + *(i32*)(base + 0xfc) - 0x1c;
        for (i32 c = 0; c < 2; ++c) {
            float f = mEval->Eval((i32)*a++);
            *(u8*)(p + 0x13 + c) = (u8)(i32)f;
        }
    }
}

// @ 0x009ddf80
// Same table fill but writing 16-bit values, and with the source layout recorded in the
// +0xc4 mode field.
void Self::CmdTable16(cArguments* args)
{
    u8*  base = *(u8**)((u8*)mOwner + 4);
    i32 mode = *(i32*)(base + 0xc4);

    if (mode == 0) {
        u32* a = args->MainArguments(3);
        u8*  p = base + (*(i32*)(base + 0xd8) - *(i32*)(base + 0xd4)) / 0x44 * 0x44
                    + *(i32*)(base + 0xd4) - 0x26;
        for (i32 i = 0; i < 3; ++i) {
            float f = mEval->Eval((i32)a[i]);
            *(u16*)(p + i * 0x10) = (u16)(i32)f;
        }
    } else if (mode == 1) {
        u32* a = args->MainArguments(4);
        u8*  p = base + (*(i32*)(base + 0xec) - *(i32*)(base + 0xe8)) / 0x58 * 0x58
                    + *(i32*)(base + 0xe8) - 0x36;
        for (i32 i = 0; i < 4; ++i) {
            float f = mEval->Eval((i32)a[i]);
            *(u16*)(p + i * 0x10) = (u16)(i32)f;
        }
    } else if (mode == 2) {
        u32* a = args->MainArguments(1);
        u8*  p = base + (*(i32*)(base + 0x100) - *(i32*)(base + 0xfc)) / 0x1c * 0x1c
                    + *(i32*)(base + 0xfc) - 6;
        float f = mEval->Eval((i32)a[0]);
        *(u16*)p = (u16)(i32)f;
    }
}

// ===========================================================================
// @ 0x009de630
bool __fastcall FUN_009de630(void* self)
{
    u32* slot = (u32*)((u8*)self + 0xac);
    for (i32 pass = 0; pass < 2; ++pass, ++slot) {
        u32 arr = *slot;
        if (arr == 0) return false;
        u8* ap = (u8*)arr;
        i32 nb = (*(i32*)(ap + 0x24) - *(i32*)(ap + 0x20)) >> 6;
        if (nb == 0) return false;
        if (nb > 0) {
            i32* it = (i32*)(*(i32*)(ap + 0x20) + 0x1c);
            for (i32 i = 0; i < nb; ++i, it += 0x10) {
                if ((*(it - 5) - *(it - 6)) / 0x44 == 0) return false;
                if ((*(it)     - *(it - 1)) / 0x58 == 0) return false;
                if ((*(it + 5) - *(it + 4)) / 0x1c == 0) return false;
            }
        }
    }
    return true;
}

// ===========================================================================
// @ 0x009de6e0
bool __cdecl FUN_009de6e0(Track2* t, void* serializer)
{
    i32 n1 = t->ItemCount();
    i32 n2 = Track2_TotalItems(t);
    u32 nBlocks = t->mCount;
    u32 size = (u32)(0x18 + n1 + n2 + (i32)nBlocks * 8 + (i32)nBlocks * 0x7c);

    u8* p = (u8*)operator_new(size, "Anim/bingr", 0, 0, 0, 0);
    *(u32*)(p + 0x00) = 0x54494147;          // 'GAIT'
    *(u32*)(p + 0x04) = size;
    *(u32*)(p + 0x08) = 0xb;
    *(u32*)(p + 0x0c) = 1;

    FUN_009dc760((Curve760*)t, (char*)p);
    FUN_009dd780(t, p);

    u32 expect = *(u32*)(p + 4);
    void** vt = *(void***)serializer;
    i32 (*fn)(void*, u8*, u32) = (i32 (*)(void*, u8*, u32))vt[3];
    i32 got = fn(serializer, p, expect);

    operator_delete__(p);
    return got == (i32)expect;
}

// ===========================================================================
// @ 0x009de770
void __stdcall FUN_009de770(u8* begin, u8* end)
{
    while (begin < end) {
        u8* a = *(u8**)(begin + 0x2c);
        if (a != 0 && *(i32*)(a - 4) != 0) operator_delete__(a);
        u8* b = *(u8**)(begin + 0x18);
        if (b != 0 && *(i32*)(b - 4) != 0) operator_delete__(b);
        u8* c = *(u8**)(begin + 0x04);
        if (c != 0 && *(i32*)(c - 4) != 0) operator_delete__(c);
        begin += 0x40;
    }
}

// ===========================================================================
// @ 0x009de7d0
u8* __cdecl FUN_009de7d0(u8* src, u8* end, u8* dst)
{
    void* p = 0;
    if (src != end) {
        do {
            u8* a = *(u8**)(src + 0x2c);
            if (a != 0 && *(i32*)(a - 4) != 0) operator_delete__(a);
            u8* b = *(u8**)(src + 0x18);
            if (b != 0 && *(i32*)(b - 4) != 0) operator_delete__(b);
            u8* c = *(u8**)(src + 0x04);
            if (c != 0 && *(i32*)(c - 4) != 0) operator_delete__(c);
            src += 0x40;
            dst += 0x40;
        } while (src != end);
        p = dst;
    } else {
        p = dst;
    }
    return (u8*)p;
}
