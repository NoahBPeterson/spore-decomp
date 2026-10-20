/* Slice s008c1910 -- T2K (Type 2000 font scaler) top-level API, module T2K (same object as
 * s008c0760 / s008bfc10, /O2 /MD /Gy /TP).
 *
 * 008c1910 T2K_GetSbits                 refresh the glyph bitmap cache for one char (795 B)
 * 008c1c30 T2K_RenderGlyph              render one glyph into the T2K target (485 B)
 * 008c1e20 T2K_SetNameString            (re)fetch the glyph/face name strings (255 B)
 * 008c1f20 DeleteT2K                    tear a T2K instance down (327 B)
 * 008c2070 T2K_GetGlyphIndex            char code -> glyph index (75 B)
 * 008c20d0 FF_GlyphExists               glyph present for a char code? also fetches the metrics (230 B)
 * 008c21c0 T2K_CastRaysOfLightAndDarkness  distance-field/edge pass over a pixel row (891 B)
 *
 * The T2K struct layout is not recovered, so every field is addressed by raw offset.  The five
 * functions that can fail wrap their body in the CRT setjmp and a tsi_EmergencyShutDown longjmp
 * handler: the object owns the jump buffer inside its allocator block (`*(void**)(p+4) + 0x10`),
 * and the error code is returned through the trailing `int* out` parameter.  Write those calls as
 * the CRT's `_setjmp`: cl's intrinsic expands it to `_setjmp3(env, 0)` and, exactly like the
 * original, keeps a frame pointer and homes every live local in memory across the call.
 * 008c1910 and 008c21c0 take their object in ESI/EAX (linker register ABI, see nonmatching.txt).
 */
#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define U32(p, o) (*(unsigned*)((char*)(p) + (o)))
#define I16(p, o) (*(short*)((char*)(p) + (o)))
#define U16(p, o) (*(unsigned short*)((char*)(p) + (o)))
#define I8(p, o) (*(char*)((char*)(p) + (o)))
#define U8(p, o) (*(unsigned char*)((char*)(p) + (o)))
#define PTR(p, o) (*(char**)((char*)(p) + (o)))

extern "C" {
int _setjmp(int* env);                                        // 0x011e0cac (cl intrinsic -> _setjmp3(env, 0))
void tsi_EmergencyShutDown(void* mem);                        // 0x008d1210
void tsi_Error(void* mem, int code);                          // 0x008d10c0
void tsi_DeAllocMem(void* mem, void* p);                      // 0x008d1440
void tsi_FreeFastMemBlocks(void* mem);                        // 0x008d1530
unsigned short GetSfntClassGlyphIndex(void* sfnt, int ch);    // 0x008d0b00
void Delete_GlyphClass(void* glyph);                          // 0x008b0280
void* GetT1NameProperty(void* t1, void* a, void* b);          // 0x008b87e0
void* GetT2NameProperty(void* t2, void* a, void* b);          // 0x008baee0
void* GetPFRNameProperty(void* pfr, void* a, void* b);        // 0x008b1980
void GetTTNameProperty(void* tt, void* a, void* b, void** out1, void** out2);   // 0x008cec20
int FUN_008c5320(void* g, unsigned a, unsigned b, unsigned idx, unsigned s28, unsigned s2c,
                 void* pts);                                  // 0x008c5320 (bitmap cache fill)
void FUN_008c6990(void* g, unsigned a, void* pts, unsigned b, unsigned c, int d, int e,
                  unsigned mask, unsigned flags);              // 0x008c6990 (bitmap blit)
void FUN_008bfc10(void);                                      // 0x008bfc10
void T2K_RenderGlyphInternal(char* t, int ch, unsigned depth, int p4, int p5, unsigned p6,
                             unsigned flags);                  // 0x008c0760
int FUN_008b3440(char* p, int a2, unsigned a5, unsigned u3);  // 0x008b3440
void FUN_008c39a0(char* p, unsigned v);                       // 0x008c39a0
void FUN_008c3580(char* p, unsigned v);                       // 0x008c3580
void FUN_008c3570(char* p);                                   // 0x008c3570
}

// @ 0x008c1910
// `idx` is volatile on purpose: the original receives p in ESI and (idx, a2, flags) on the stack,
// so cl must not promote idx into a register (see the byte-exact call site in T2K_RenderGlyph).
extern "C" static int FUN_008c1910(char* p, volatile unsigned idx, char a2, unsigned flags)
{
    int u3c = I32(PTR(p, 0x184), 0x3c);
    int changed = 0;
    char* g = PTR(PTR(p, 0x184), 0x38);   // glyph/sub-font scratch object
    if (I32(p, 0x1c) != 0 && g != 0 && I32(PTR(p, 0x184), 0x40) != 0) {
        unsigned short s2c = U16(p, 0x12c);
        unsigned short s28 = U16(p, 0x128);
        char* pts = g + 0x10;             // per-glyph point/metric record
        unsigned short glyph;
        if ((flags & 8) == 0)
            glyph = (unsigned short)GetSfntClassGlyphIndex(PTR(p, 0x184), (int)idx);
        else
            glyph = (unsigned short)idx;
        unsigned char cVar7;
        if (I32(g, 0xc) != 0)
            cVar7 = (unsigned char)I32(g, 0xc);
        else if (a2 != 0)
            cVar7 = (unsigned char)((I32(p, 0x48) != 0) + 7);
        else
            cVar7 = 1;
        if (U16(pts, 4) == glyph && U16(pts, 6) == s28 && U16(pts, 8) == s2c &&
            U16(pts, 0xa) == s28 && U16(pts, 0xc) == s2c && U8(pts, 0xe) == cVar7 &&
            I32(pts, 0) != 0) {
            changed = 1;
        } else {
            FUN_008c5320(g, (unsigned)u3c, U32(PTR(p, 0x184), 0xdc), glyph, s28, s2c, pts);
            if (U16(pts, 4) == glyph && U16(pts, 6) == s28 && U16(pts, 8) == s2c &&
                I32(pts, 0) != 0)
                changed = 1;
            else
                changed = 0;
        }
        int bits = I32(g, 0xc);
        if (bits == 0 || bits == (int)U8(g, 0x1f)) {
            if (changed != 0) {
                unsigned char mask;
                int save = a2;
                if (bits != 0) {
                    mask = (unsigned char)((1 << bits) - 1);
                    save = 0xff;
                } else if (a2 == 0) {
                    mask = 1;
                } else {
                    mask = (I32(p, 0x48) != 0) ? 0xff : 0x7e;
                }
                if ((flags & 0x20) != 0)
                    mask = 0;
                FUN_008c6990(g, (unsigned)u3c, pts, U32(PTR(p, 0x184), 0xdc),
                             U32(PTR(p, 0x184), 0x40), save, 0, mask, flags);
                if (I32(g, 0x3c) == 0) {
                    I32(p, 0x30) = 0;
                } else {
                    I32(p, 0x118) = I32(g, 0x3c);
                    I32(g, 0x3c) = 0;
                    I32(p, 0x30) = 1;
                }
                I16(p, 0x108) = (short)glyph;
                U8(p, 0x124) = U8(g, 0x1f);
                if ((flags & 0x20) == 0 && I32(p, 0x30) != 0 && I32(p, 0x28) != 0) {
                    char* q = ((char* (*)(void*, void*))PTR(p, 0x24))((void*)I32(p, 0x20),
                                                                      (void*)U32(g, 0x40));
                    if (q != 0) {
                        unsigned n = U32(g, 0x40);
                        unsigned k = 0;
                        if (n != 0) {
                            do {
                                q[k] = PTR(p, 0x118)[k];
                                k++;
                            } while (k < n);
                        }
                        tsi_DeAllocMem(PTR(p, 4), PTR(p, 0x118));
                        PTR(p, 0x118) = q;
                        I32(p, 0x30) = 0;
                    }
                }
            }
        } else {
            changed = 0;
        }
        I32(p, 0xd0) = (int)U16(g, 0x2c);
        I32(p, 0xd4) = 0;
        I32(p, 0x114) = I32(g, 0x38);
        I32(g, 0x38) = 0;
        I32(p, 0x10c) = (int)U16(g, 0x26);
        I32(p, 0x110) = (int)U16(g, 0x24);
        I32(p, 0xcc) = 1;
        I32(p, 0xe4) = (int)I16(g, 0x28) << 6;
        I32(p, 0xe0) = (int)I16(g, 0x2a) << 6;
        int hi = (int)(U32(g, 0x2c) << 0x10);
        I32(p, 0xd0) = hi;
        I32(p, 0xd8) = hi;
        I32(p, 0xe8) = 1;
        I32(p, 0xdc) = 0;
        I32(p, 0xd4) = 0;
        I32(p, 0x100) = (int)I16(g, 0x2e) << 6;
        I32(p, 0xfc) = (int)I16(g, 0x30) << 6;
        int hi2 = (int)(U32(g, 0x32) << 0x10);
        I32(p, 0xf0) = hi2;
        I32(p, 0xf8) = hi2;
        I32(p, 0xf4) = 0;
        I32(p, 0xec) = 0;
        if (I32(g, 0x34) != 0) {
            if ((U8(g, 0x20) & 1) == 0)
                I32(p, 0xcc) = 0;
            if ((U8(g, 0x20) & 2) == 0)
                I32(p, 0xe8) = 0;
        }
    }
    return changed;
}

// @ 0x008c1c30
// `uVar3` is homed (declared and initialised before _setjmp) so cl keeps it in memory across the
// setjmp exactly as the original does; and the longjmp handler is written last (`if (r == 0) {
// ...; return; } shutdown();`) so it lands out-of-line at the function end.
extern "C" void T2K_RenderGlyph(char* p, int a2, int a3, int a4, unsigned a5, unsigned short a6,
                                int* out)
{
    unsigned uVar3 = a6;
    int r = _setjmp((int*)(PTR(p, 4) + 0x10));
    *out = r;
    if (r == 0) {
        if (I32(PTR(p, 4), 0xa8) != (int)0xaa005501)
            tsi_Error(PTR(p, 4), 0x2723);
        I32(PTR(p, 0x184), 0xc8) = uVar3 & 0x80;
        I32(PTR(p, 0x184), 0xcc) = 1;
        I32(PTR(p, 0x184), 0xd0) = (unsigned char)a5;
        uVar3 &= 0xfffe;
        int uVar2;
        if (I32(p, 0x24) == 0 || I32(p, 0x40) != 0 || (uVar3 & 0x100) != 0)
            uVar2 = 0;
        else
            uVar2 = 1;
        I32(p, 0x28) = uVar2;
        I32(p, 0x2c) = (int)(~(uVar3 >> 8) & 1);
        if (I32(PTR(p, 0x184), 0x28) != 0 && I32(p, 0x17c) != 0 && (uVar3 & 2) != 0) {
            if (FUN_008b3440(p, a2, a5, uVar3) != 0) {
                I32(p, 0x120) = 1;
                goto tail;
            }
        }
        if (I32(p, 0x17c) != 0 && (uVar3 & 2) != 0) {
            if (FUN_008c1910(p, (unsigned)a2, (char)a5, uVar3) != 0) {
                I32(p, 0x120) = 1;
                goto tail;
            }
        }
        I32(p, 0x120) = 0;
        FUN_008bfc10();
        T2K_RenderGlyphInternal(p, a2, 0, a3, a4, a5, uVar3);
        I32(p, 0xcc) = 1;
        I32(p, 0xe8) = 0;
    tail:
        if (PTR(p, 0x40) != 0)
            ((void (*)(char*, void*))PTR(p, 0x40))(p, PTR(p, 0x44));
        unsigned short uVar4 = (unsigned short)(uVar3 & 0x1000);
        if (uVar4 == 0x1000 || (uVar3 & 0x2000) != 0)
            FUN_008c3580(p, uVar3);
        else if ((uVar3 & 0xc000) != 0)
            FUN_008c39a0(p, uVar3);
        if (uVar4 != 0x1000 && (uVar3 & 0xe000) == 0 && (uVar3 & 0x100) != 0)
            FUN_008c3570(p);
        return;
    }
    tsi_EmergencyShutDown(PTR(p, 4));
}

// @ 0x008c1e20
extern "C" void T2K_SetNameString(char* p, void* a2, void* a3, int* out)
{
    void* sfnt = PTR(p, 0x184);
    int r = _setjmp((int*)(PTR(p, 4) + 0x10));
    *out = r;
    if (r == 0) {
        tsi_DeAllocMem(PTR(p, 4), PTR(p, 0x50));
        PTR(p, 0x50) = 0;
        tsi_DeAllocMem(PTR(p, 4), PTR(p, 0x54));
        PTR(p, 0x54) = 0;
        if (I32(sfnt, 0x20) != 0) {
            PTR(p, 0x50) = (char*)GetT1NameProperty(PTR(sfnt, 0x20), a2, a3);
            return;
        }
        if (I32(sfnt, 0x24) != 0 && I32(sfnt, 0x7c) == 0) {
            PTR(p, 0x50) = (char*)GetT2NameProperty(PTR(sfnt, 0x24), a2, a3);
            return;
        }
        if (I32(sfnt, 0x28) != 0) {
            PTR(p, 0x50) = (char*)GetPFRNameProperty(PTR(sfnt, 0x28), a2, a3);
            return;
        }
        GetTTNameProperty(sfnt, a2, a3, (void**)(p + 0x50), (void**)(p + 0x54));
        return;
    }
    tsi_EmergencyShutDown(PTR(p, 4));
}

// @ 0x008c1f20
extern "C" void DeleteT2K(char* p, int* out)
{
    int r = _setjmp((int*)(PTR(p, 4) + 0x10));
    *out = r;
    if (r == 0) {
        if (I32(p, 0) != (int)0x5a1234a5 || I32(p, 0xa30) != (int)0xa5fedc5a)
            tsi_Error(PTR(p, 4), 0x2717);
        Delete_GlyphClass((void*)I32(p, 0x104));
        int bits = I32(p, 0x118);
        I32(p, 0x104) = 0;
        if (bits != 0 && I32(p, 0x30) != 0) {
            char* mem = PTR(p, 4);
            if (bits == I32(mem, 0x64))
                I32(mem, 0x9c) = 1;
            else
                tsi_DeAllocMem(mem, (void*)bits);
            I32(p, 0x118) = 0;
        }
        if (I32(p, 0x11c) != 0 && I32(p, 0x34) != 0) {
            tsi_DeAllocMem(PTR(p, 4), (void*)I32(p, 0x11c));
            I32(p, 0x11c) = 0;
        }
        tsi_DeAllocMem(PTR(p, 4), (void*)I32(PTR(p, 0x184), 0xa4));
        I32(PTR(p, 0x184), 0xa4) = 0;
        tsi_DeAllocMem(PTR(p, 4), PTR(p, 0x50));
        tsi_DeAllocMem(PTR(p, 4), PTR(p, 0x54));
        char* blk = PTR(p, 0x18);
        if (blk != 0) {
            tsi_DeAllocMem(PTR(blk, 0), PTR(blk, 0x10));
            tsi_DeAllocMem(PTR(blk, 0), blk);
        }
        tsi_FreeFastMemBlocks(PTR(p, 4));
        tsi_DeAllocMem(PTR(p, 4), p);
        return;
    }
    tsi_EmergencyShutDown(PTR(p, 4));
}

// @ 0x008c2070
extern "C" unsigned short T2K_GetGlyphIndex(char* p, int ch, int* out)
{
    int r = _setjmp((int*)(PTR(p, 4) + 0x10));
    *out = r;
    if (r == 0)
        return GetSfntClassGlyphIndex((void*)I32(p, 0x184), ch);
    tsi_EmergencyShutDown(PTR(p, 4));
    return 0;
}

// @ 0x008c20d0
extern "C" int FF_GlyphExists(char* p, int ch, unsigned flags, int* out)
{
    int result = 0;
    short s = 0;
    *out = 0;
    if ((flags & 8) != 0) {
        if (ch < I32(PTR(p, 0x184), 0xf0)) {
            s = (short)ch;
            result = 1;
        }
    } else {
        int r = _setjmp((int*)(PTR(p, 4) + 0x10));
        *out = r;
        if (r == 0) {
            s = (short)(unsigned short)GetSfntClassGlyphIndex((void*)I32(p, 0x184), ch);
            if (s != 0) {
                I16(p, 0x108) = s;
                return 1;
            }
            char* sfnt = PTR(p, 0x184);
            result = 0;
            if (I32(sfnt, 0x20) != 0)
                result = I32(PTR(sfnt, 0x20), 0x220);
            if (I32(sfnt, 0x24) != 0 && I32(sfnt, 0x7c) == 0)
                result = I32(PTR(sfnt, 0x24), 0x51c);
            if (I32(sfnt, 0x28) != 0) {
                result = I32(PTR(sfnt, 0x28), 0x1ec);
                I16(p, 0x108) = s;
                return result;
            }
        } else {
            tsi_EmergencyShutDown(PTR(p, 4));
        }
    }
    I16(p, 0x108) = s;
    return result;
}

// @ 0x008c21c0
extern "C" void T2K_CastRaysOfLightAndDarkness(unsigned* buf, int a2, int a3, int a4, int a5,
                                               unsigned* sel)
{
    unsigned colLo = ((U32(sel, 0x18) << 8 | U32(sel, 0x1c)) << 8) | U32(sel, 0x20);
    unsigned colHi = ((U32(sel, 0x24) << 8 | U32(sel, 0x28)) << 8) | U32(sel, 0x2c);
    int subFalse = 0;               // subtracted in the "both false" branch (orig [esp+0x38])
    int subTrue = 0;                // subtracted in the "both true" branch  (orig [esp+0x3c])
    unsigned colB = 0;              // colour mask held in [esp+0x14]
    unsigned colA = 0;              // colour mask held in [esp+0x18]
    if (I8(sel, 1) == 1) {
        subTrue = 0;
        subFalse = 1;
        colB = colLo;
        colA = colHi;
    } else if (I8(sel, 1) == 2) {
        subTrue = 1;
        subFalse = 0;
        colB = colHi;
        colA = colLo;
    }

    int i = 0;
    if (0 < a5) {
        do {
            unsigned v = buf[i];
            if (v != 0) {
                unsigned u = v << 0x18;
                if (u < 0x7f000000u)
                    u = u - 0x80000000u;
                buf[i] = u;
            }
            i++;
        } while (i < a5);
    }

    int span = a3;                  // local_28 = max(a2, a3)
    if (a3 < a2)
        span = a2;

    int pass = 0;                   // local_8
    do {
        int limit = a3;             // local_c: a3 on pass 0, a2 on pass 1
        int r = pass;
        if (pass != 0)
            limit = a2;
        for (; r < limit; r++) {
            int off;                    // orig [esp+0x1c]
            int col;                    // orig [esp+0x24]
            if (pass == 0) {
                off = 0;
                col = r;
            } else {
                col = 0;
                off = r;
            }
            int count = 0;              // orig [esp+0x10] (number of row pixels to walk)
            if (0 < span) {
                int n = 0;
                int c = col;
                do {
                    if (a2 <= (off - col) + c || a3 <= c)
                        break;
                    count++;
                    n++;
                    c++;
                } while (n < span);
            }
            int idx = 0;
            if (0 < count) {
                int base = 0;           // row offset at the start of the current run (orig [esp+0x44])
                int idxOff = 0;         // idx * a4 (orig [esp+0x30])
                int rowOff = col * a4;  // (col + idx) * a4 (orig [esp+0x48])
                bool prevIn = false;    // run currently open?
                int prevN = 0;          // first index of the current run
                bool prevVal = false;   // value at the run's previous sample
                int lastIdx = 0;        // last index seen in the current run
                do {
                    unsigned v = buf[rowOff + idx + off];
                    bool val = false;
                    int end;            // split point between the two colour spans
                    unsigned mask1 = 0; // colour mask for the first span  (orig [esp+0x20])
                    unsigned mask2 = 0; // colour mask for the second span (orig [esp+0x40])
                    if (prevIn) {
                        if (v < 0x80000000u) {
                            val = v != 0;
                        } else {
                            lastIdx = idx;
                            if (idx < count - 1)
                                goto next;
                            val = false;
                        }
                    } else if (v < 0x80000000u) {
                        prevVal = v != 0;
                        goto next;
                    } else {
                        prevIn = true;
                        base = idxOff;
                        prevN = idx;
                        lastIdx = idx;
                        if (idx < count - 1)
                            goto next;
                        val = false;
                    }
                    /* merge the run [prevN, lastIdx] using the two colours */
                    if ((int)prevVal < (int)val) {
                        mask1 = colA;
                    } else if ((int)val < (int)prevVal) {
                        mask1 = colB;
                    } else if (prevVal || val) {
                        mask1 = colB;
                        mask2 = colA;
                        end = (lastIdx + prevN) / 2 - subTrue;
                    } else {
                        mask1 = colA;
                        mask2 = colB;
                        end = (lastIdx + prevN) / 2 - subFalse;
                    }
                    if (prevN <= end) {
                        int p = prevN + off;
                        int q = col * a4 + base;  // base is the run's start row, not the current one
                        int k = (end - prevN) + 1;
                        do {
                            unsigned* slot = &buf[q + p];
                            q += a4;
                            p++;
                            k--;
                            *slot = (*slot - 0x80000000u) | mask1;
                        } while (k != 0);
                    }
                    end++;
                    if (end <= lastIdx) {
                        int p = end + off;
                        int q = (col + end) * a4;
                        int k = (lastIdx - end) + 1;
                        do {
                            unsigned* slot = &buf[q + p];
                            q += a4;
                            p++;
                            k--;
                            *slot = (*slot - 0x80000000u) | mask2;
                        } while (k != 0);
                    }
                    prevIn = false;
                    base = idxOff;
                    prevN = idx;
                    prevVal = val;
                next:
                    idxOff += a4;
                    rowOff += a4;
                    idx++;
                } while (idx < count);
            }
        }
        pass++;
        if (1 < pass) {
            i = 0;
            if (0 < a5) {
                do {
                    unsigned v = buf[i];
                    if (v != 0) {
                        unsigned hi = v >> 0x18;
                        if (0x7e < hi)
                            hi = 0x7e;
                        buf[i] = (hi * 0x40 + (hi & 0xffffffe0)) * 0x80000 | (v & 0xffffff);
                    }
                    i++;
                } while (i < a5);
            }
            return;
        }
    } while (1);
}
