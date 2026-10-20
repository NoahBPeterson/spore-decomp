// Slice s0099cf50 -- Simulator file-IO stream helpers, a refcount/delete helper,
// a set-intersection routine, a recursive graph walk and the creature-anim
// "disable unused deforms" pass.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// The stream helpers are modelled as real C++ member functions of a small
// class so the this-pointer lands in ecx; FILE* is kept as an opaque pointer
// because the CRT import is reached through its IAT slot.
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef int            int32_t;
typedef long           int32_tl;
typedef unsigned long  uint32_tl;
typedef unsigned int   uintptr_t;
typedef unsigned int   size_t_;

struct FILE_;

// Byte-offset accessors.
#define F(o, off)  (*(uint32_t*)((uint8_t*)(o) + (off)))
#define B(o, off)  (*(uint8_t*)((uint8_t*)(o) + (off)))
#define S(o, off)  (*(uint16_t*)((uint8_t*)(o) + (off)))

// ---------------------------------------------------------------------------
// Callees.
// ---------------------------------------------------------------------------
extern "C" int    __cdecl FUN_0099c600(uint32_t, uint32_t);          // 0x99c600
extern "C" void   __cdecl FUN_0099c990(void*, void*, void*, void*);   // 0x99c990
extern "C" void*  __cdecl FUN_009fc310(void*);                        // 0x9fc310 (BehaviorLookup)
extern "C" void   __cdecl FUN_00f47380(void*);                        // 0xf47380 operator delete
extern "C" __declspec(dllimport) int    __cdecl fseek(FILE_*, int32_tl, int);      // msvcr90!fseek
extern "C" __declspec(dllimport) int32_tl __cdecl ftell(FILE_*);                  // msvcr90!ftell
extern "C" __declspec(dllimport) size_t_ __cdecl fread(void*, size_t_, size_t_, FILE_*); // msvcr90!fread
extern "C" __declspec(dllimport) size_t_ __cdecl fwrite(const void*, size_t_, size_t_, FILE_*); // msvcr90!fwrite

// ---------------------------------------------------------------------------
// The stream wrapper: a FILE* at +4.
// ---------------------------------------------------------------------------
struct FileStream {
    uint32_t unk0;                 // +0
    FILE_*   fp;                   // +4
    uint8_t  unk8;                 // +8

    // 0x0099cf50
    FileStream* __thiscall Ctor();
    // 0x0099cf70
    void  __thiscall Seek(int32_tl offset, int origin);
    // 0x0099cf90
    int32_tl __thiscall Tell();
    // 0x0099cfb0
    size_t_ __thiscall Read(void* dst, size_t_ count);
    // 0x0099cfe0
    size_t_ __thiscall Write(const void* src, size_t_ count);
    // 0x0099d010
    int32_tl __thiscall Size();
};

// @ 0x0099cf50
FileStream* __thiscall FileStream::Ctor()
{
    B(this, 8) = 0;
    B(this, 9) = 0;
    *(float*)((uint8_t*)this + 0) = 0.0f;
    *(float*)((uint8_t*)this + 4) = 0.0f;
    *(uint16_t*)((uint8_t*)this + 0xa) = 0;
    return this;
}


// @ 0x0099cf70
void __thiscall FileStream::Seek(int32_tl offset, int origin)
{
    if (fp != 0) {
        fseek(fp, offset, origin);
    }
}

// @ 0x0099cf90
int32_tl __thiscall FileStream::Tell()
{
    if (fp != 0) {
        return ftell(fp);
    }
    return -1;
}

// @ 0x0099cfb0
size_t_ __thiscall FileStream::Read(void* dst, size_t_ count)
{
    if (fp != 0) {
        return fread(dst, 1, count, fp);
    }
    return (size_t_)-1;
}

// @ 0x0099cfe0
size_t_ __thiscall FileStream::Write(const void* src, size_t_ count)
{
    if (fp != 0) {
        return fwrite(src, 1, count, fp);
    }
    return (size_t_)-1;
}

// @ 0x0099d010
int32_tl __thiscall FileStream::Size()
{
    if (fp != 0) {
        int32_tl saved = ftell(fp);
        fseek(fp, 0, 2);
        int32_tl end = ftell(fp);
        fseek(fp, saved, 0);
        return end;
    }
    return -1;
}

// @ 0x0099d060
// Refcount decrement; deletes the object when the count drops to zero.
extern "C" int __fastcall FUN_0099d060(uint32_t* self)
{
    int local[2];
    int v = (int)F(self, 0x114) - 1;
    local[1] = 0;
    local[0] = v;
    int* p = (v > 0) ? &local[0] : &local[1];
    int r = *p;
    F(self, 0x114) = (uint32_t)r;
    if (r <= 0) {
        F(self, 0x114) = 1;
        FUN_00f47380(self);
        r = 0;
    }
    return r;
}

// @ 0x0099d0b0
// Set intersection: for each of the `count` 64-bit keys in `keys`, OR together the
// fields of the ranges whose tag byte matches, then AND the accumulated masks
// across keys.  Returns the AND-reduced pair through `out`, or a match code.
extern "C" int __cdecl FUN_0099d0b0(uint32_t* owner, uint32_t* keys, uint32_t count, uint32_t* out)
{
    if (owner == 0 || keys == 0 || count == 0) {
        return -1;
    }

    uint32_t accLo = 0xffffffff;
    uint32_t accHi = 0xffffffff;
    uint8_t  anyFlag = 0;
    uint32_t i = 0;

    for (;;) {
        uint32_t orLo = 0;
        uint32_t orHi = 0;
        int n = (int)((F(owner, 0x20) - F(owner, 0x1c)) >> 4);
        if (n != 0) {
            uint8_t* p = *(uint8_t**)((uint8_t*)owner + 0x1c);
            do {
                if (B(p, 0xb) != 0) {
                    anyFlag = 1;
                }
                if ((uint32_t)B(p, 0xc) == keys[i * 2]
                    && (uint32_t)B(p, 0xb) == keys[i * 2 + 1]) {
                    orLo |= F(p, 0);
                    orHi |= F(p, 4);
                }
                p += 0x10;
            } while (--n != 0);
        }

        accLo &= orLo;
        accHi &= orHi;

        if (accLo == 0 && accHi == 0) {
            if (out != 0) {
                out[0] = 0;
                out[1] = 0;
            }
            return (int)anyFlag - 3;
        }

        if (++i >= count) break;
    }

    if (out != 0) {
        out[0] = accLo;
        out[1] = accHi;
    }
    return FUN_0099c600(-accLo & accLo, -(accHi + (accLo != 0)) & accHi);
}

// Recursive walk over the deform graph: for slot `index`, resolve the current
// entry's id, clear it if it collides with an earlier slot, then either bump
// per-slot counters (last slot) or recurse into the next slot.
//
// Slot records live at self+0x21c with a 0x28 stride: +0 = id, +0x8 = begin,
// +0xc = end, +0x14 = counter, and the slot count is at self+0xc18.
struct DeformSlot {
    uint32_t id;          // +0x00
    uint32_t pad04;       // +0x04
    uint32_t counter;     // +0x08
    uint32_t pad0c;       // +0x0c
    uint32_t begin;       // +0x10
    uint32_t end;         // +0x14
    uint32_t pad18;       // +0x18
    uint32_t pad1c;       // +0x1c
    uint32_t pad20;       // +0x20
    uint32_t pad24;       // +0x24
};

struct DeformWalk {
    // 0x0099d1f0
    void __thiscall Walk(uint32_t index);
};

// @ 0x0099d1f0
void __thiscall DeformWalk::Walk(uint32_t index)
{
    uint8_t* self = (uint8_t*)this;
    DeformSlot* slots = (DeformSlot*)(self + 0x21c);
    DeformSlot* cur = slots + index;

    int count = (int)((int)cur->end - (int)cur->begin) >> 2;
    uint32_t i = 0;
    do {
        int id;
        if (count == 0) {
            id = -1;
        } else {
            id = *(int*)(cur->begin + i * 4);
        }

        int s = (int)index - 1;
        if (s >= 0) {
            DeformSlot* q = slots + s;
            do {
                if ((int)q->id == id) {
                    id = -1;
                    break;
                }
                --s;
                --q;
            } while (s >= 0);
        }
        cur->id = (uint32_t)id;

        if (index == F(self, 0xc18) - 1) {
            if (F(self, 0xc18) != 0) {
                uint32_t c = 0;
                DeformSlot* p = slots;
                do {
                    if ((int)p->id == -1) {
                        /* skip */
                    } else {
                        p->counter = p->counter + 1;
                    }
                    ++c;
                    ++p;
                } while (c < F(self, 0xc18));
            }
        } else {
            Walk(index + 1);
        }
        ++i;
    } while (i < (uint32_t)count);
}

// @ 0x0099d2b0
extern "C" void __cdecl FUN_0099d2b0(uint32_t self, uint32_t a, uint32_t b)
{
    FUN_0099c990(*(void**)(uintptr_t)(self + 0xe0), *(void**)(uintptr_t)(self + 0xdc), (void*)a, (void*)b);
}

// A deform-slot descriptor: 0x20 bytes per entry.
struct DeformEntry {
    uint32_t flags;    // +0   low nibble = index, bits 6/7 set from the type byte
    uint32_t unk4;     // +4
    uint32_t unk8;     // +8
    uint32_t unkc;     // +0xc
    int      slot;     // +0x10  resolved table index or -1
    uint32_t unk14;    // +0x14
    uint32_t unk18;    // +0x18
    uint32_t unk1c;    // +0x1c
};

// @ 0x0099d2e0
extern "C" void __cdecl FUN_0099d2e0(uint32_t self)
{
    uint32_t table[0x48 / 4];
    {
        const uint32_t* src = (const uint32_t*)0x1446cb8;
        for (int k = 0; k < 0x48; k += 4) {
            *(uint32_t*)((uint8_t*)table + k)     = src[k / 4];
        }
    }

    uint32_t numAnim = F(self, 0x144);
    for (uint32_t i = 0; i < numAnim; ++i) {
        uint32_t obj = *(uint32_t*)(*(uint32_t*)(uintptr_t)(self + 0x148) + i * 4);
        uint32_t* found = (uint32_t*)FUN_009fc310((void*)(uintptr_t)(obj + 0x8c));

        uint32_t nfound = (found[1] - found[0]) >> 4;
        if (nfound != 0) {
            uint32_t src = 0;
            uint32_t* dst = (uint32_t*)((uint8_t*)table + 0x64);
            do {
                *dst = *(uint32_t*)(uintptr_t)(src + found[0]);
                src += 0x10;
                dst += 8;
            } while (--nfound != 0);
        }

        uint32_t ncents = F(obj, 0xdc);
        for (uint32_t j = 0; j < ncents; ++j) {
            uint8_t* cent = (uint8_t*)(uintptr_t)(F(obj, 0xe0) + j * 0x20);
            uint32_t tag  = F(cent, 0);
            uint32_t hi   = F(cent, 4);
            uint32_t m = 0;
            uint32_t* q = table + 1;
            for (;;) {
                if ((q[-1] & 0xf) == (tag & 0xf) && *q != 0
                    && (*q == hi || hi == 0xffffffff)) {
                    uint32_t* slot = table + m * 8;
                    if (slot != 0) {
                        uint32_t idx = slot - table;
                        F(cent, 0x10) = idx;
                        if ((tag & 0xf) == 3) {
                            uint32_t k = (idx - 3) * 0x10;
                            if ((*(uint8_t*)(uintptr_t)(found[0] + 0xc + k) & 2) == 0) {
                                F(cent, 0) = tag & 0xffffffbf;
                            } else {
                                F(cent, 0) = tag | 0x40;
                            }
                            if ((*(uint8_t*)(uintptr_t)(found[0] + 0xc + k) & 1) == 0) {
                                F(cent, 0) = F(cent, 0) & 0xffffff7f;
                            } else {
                                F(cent, 0) = F(cent, 0) | 0x80;
                            }
                        }
                        goto next;
                    }
                    break;
                }
                ++m;
                q += 8;
                if (m >= 9) break;
            }
            F(cent, 0x10) = 0xffffffff;
            F(cent, 0) = tag & 0xffffffef;
        next:
            ;
        }
    }
}
