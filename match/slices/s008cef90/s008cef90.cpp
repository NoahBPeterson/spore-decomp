// Slice s008cef90: T2K (Type 2000 font scaler) sfnt.c / truetype.c helpers.
//
// Glyph counting and glyph loading for a scaled font, plus the small accessors that sit next to
// them (the cached advance-width table, the style callback installer, the SFNT metrics reader,
// the sfntClass destructor, the 8-byte map-record shell sort and the cmap2 char-index lookup).
// The module's TU is the one that also defines GetUPEM/GetTableDirEntry_sfntClass; those are
// calls here (cl did not inline them at these call sites).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject;
struct InputStream;
struct GlyphClass;
struct hmtxClass;
struct CMap2;

struct sfnt_DirectoryEntry {
    uint32 tag;           // +0x0
    uint32 checkSum;      // +0x4
    uint32 offset;        // +0x8
    uint32 length;        // +0xc
};

struct sfnt_OffsetTable {
    tsiMemObject* mem;           // +0x00
    int32 version;               // +0x04
    uint16 numOffsets;           // +0x08
    uint16 searchRange;          // +0x0a
    uint16 entrySelector;        // +0x0c
    uint16 rangeShift;           // +0x0e
    sfnt_DirectoryEntry* table;  // +0x10
};

struct ttcfClass {
    tsiMemObject* mem;      // +0x0
    uint32 version;         // +0x4
    uint32 directoryCount;  // +0x8
    uint32* tableOffsets;   // +0xc
};

struct headClass {
    tsiMemObject* mem;      // +0x00
    uint32 pad04[(0x38 - 4) / 4];
    int16 glyphDataFormat;  // +0x38 (2000 == 'T2K' scaler)
};

struct hheaClass {
    tsiMemObject* mem;           // +0x00
    int32 version;               // +0x04
    int16 Ascender;              // +0x08
    int16 Descender;             // +0x0a
    int16 LineGap;               // +0x0c
    uint16 advanceWidthMax;      // +0x0e
    int16 minLeftSideBearing;    // +0x10
    int16 minRightSideBearing;   // +0x12
    int16 xMaxExtent;            // +0x14
    int16 caretSlopeRise;        // +0x16
    int16 caretSlopeRun;         // +0x18
    int16 caretOffset;           // +0x1a
    int16 reserved2;             // +0x1c
    int16 reserved3;             // +0x1e
    int16 reserved4;             // +0x20
    int16 reserved5;             // +0x22
    int16 metricDataFormat;      // +0x24
    uint16 numberOfHMetrics;     // +0x26
};

struct maxpClass {
    tsiMemObject* mem;   // +0x00
    int32 version;       // +0x04
    uint16 numGlyphs;    // +0x08
};

struct hmtxClass {
    tsiMemObject* mem;       // +0x00
    int32 numGlyphs;         // +0x04
    int32 numberOfHMetrics;  // +0x08
    int16* lsb;              // +0x0c
    uint16* aw;              // +0x10
};

struct locaClass {
    tsiMemObject* mem;       // +0x0
    uint32* offsets;         // +0x4
    int32 n;                 // +0x8
    int16 indexToLocFormat;  // +0xc
};

struct slocClass {
    tsiMemObject* mem;       // +0x00
    uint32 pad04[2];
    void* sloc;              // +0x0c
};

struct T1Class {
    uint32 pad00[0xc];       // 0x00..0x2f
    int16 NumCharStrings;    // +0x30
    uint16 pad32;
    uint32 pad34[(0x1e8 - 0x34) / 4];
    uint16 m1e8;             // +0x1e8
    uint16 pad1ea;
    uint16 m1ec;             // +0x1ec
    uint16 pad1ee;
    uint16 m1f0;             // +0x1f0
    uint16 pad1f2;
    uint16 m1f4;             // +0x1f4
    uint16 pad1f6;
    int32 m1f8;              // +0x1f8
    uint16 m1fc;             // +0x1fc
    uint16 pad1fe;
    uint16 m200;             // +0x200
};

struct CFFClass {
    uint32 pad00[3];         // 0x00..0x0b
    int32 NumCharStrings;    // +0x0c
    uint32 pad10[(0x224 - 0x10) / 4];
    uint16 m224;             // +0x224
    uint16 pad226;
    uint16 m228;             // +0x228
    uint16 pad22a;
    uint16 m22c;             // +0x22c
    uint16 pad22e;
    uint16 m230;             // +0x230
    uint16 pad232;
    int32 m234;              // +0x234
    uint32 pad238[(0x3a4 - 0x238) / 4];
    uint16 m3a4;             // +0x3a4
    uint16 pad3a6;
    uint16 m3a8;             // +0x3a8
};

struct PFRClass {
    uint32 pad00[0x108 / 4]; // 0x00..0x107
    int16 NumCharStrings;    // +0x108
    uint16 pad10a;
    uint32 pad10c[2];
    uint16 m114;             // +0x114
    uint16 pad116;
    uint16 m118;             // +0x118
    uint16 pad11a;
    uint16 m11c;             // +0x11c
    uint16 pad11e;
    uint16 m120;             // +0x120
    uint16 pad122;
    int32 m124;              // +0x124
};

struct GlyphClass {
    uint32 pad00[0x38 / 4];
    int16 pointCount;    // +0x38
    uint16 pad3a;
    uint32 pad3c[14];    // 0x3c..0x73
    uint16 f74;          // +0x74
    uint16 f76;          // +0x76
};

typedef void (*StyleMetricsFuncPtr)(hmtxClass* hmtx, tsiMemObject* mem, uint16 UPEM, int32* params);

struct sfntClass {
    sfnt_OffsetTable* offsetTable0;       // +0x00
    void* GetAWFuncPtr1;                  // +0x04
    void* GetAWParam1;                    // +0x08
    void* GetAWFuncPtr2;                  // +0x0c
    void* GetAWParam2;                    // +0x10
    uint16* awCache_hashKey;              // +0x14
    uint16* awCache_aw;                   // +0x18
    uint16 upem;                          // +0x1c
    T1Class* T1;                          // +0x20
    CFFClass* T2;                         // +0x24
    PFRClass* PFR;                        // +0x28
    slocClass* sloc;                      // +0x2c
    void* ffst;                           // +0x30
    void* ffhm;                           // +0x34
    void* bloc;                           // +0x38
    void* ebsc;                           // +0x3c
    uint32 bdatOffset;                    // +0x40
    void* t2kTT;                          // +0x44
    void* ffhint;                         // +0x48
    ttcfClass* ttcf;                      // +0x4c
    headClass* head;                      // +0x50
    maxpClass* maxp;                      // +0x54
    locaClass* loca;                      // +0x58
    void* gasp;                           // +0x5c
    hheaClass* hhea;                      // +0x60
    hheaClass* vhea;                      // +0x64
    hmtxClass* hmtx;                      // +0x68
    hmtxClass* vmtx;                      // +0x6c
    void* cmap;                           // +0x70
    void* kern;                           // +0x74
    uint32 CFF_offset;                    // +0x78
    uint32 CFF_length;                    // +0x7c
    uint32 DSIG_offset;                   // +0x80
    uint32 DSIG_length;                   // +0x84
    uint16 preferedPlatformID;            // +0x88
    uint16 preferedPlatformSpecificID;    // +0x8a
    int16 post_underlinePosition;         // +0x8c
    int16 post_underlineThickness;        // +0x8e
    uint32 isFixedPitch;                  // +0x90
    uint16 firstCharCode;                 // +0x94
    uint16 lastCharCode;                  // +0x96
    uint16 hintsAvailable;                // +0x98
    int32 xPPEm;                          // +0x9c
    int32 yPPEm;                          // +0xa0
    void* globalHintsCache;               // +0xa4
    void* StyleFunc;                      // +0xa8
    StyleMetricsFuncPtr StyleMetricsFunc; // +0xac
    int32 params[4];                      // +0xb0
    int32 xScale;                         // +0xc0
    int32 yScale;                         // +0xc4
    int useNativeHints;                   // +0xc8
    int strokeGlyph;                      // +0xcc
    int greyScaleLevel;                   // +0xd0
    int32 currentCoordinate[2];           // +0xd4
    InputStream* in;                      // +0xdc
    InputStream* in2;                     // +0xe0
    void* out;                            // +0xe4
    tsiMemObject* mem;                    // +0xe8
    void* model;                          // +0xec
    int32 numGlyphs;                      // +0xf0
    int32 numberOfLogicalFonts;           // +0xf4
};

// cmap sub-table object reached through sfntClass::cmap; the char-index dispatcher keeps the
// currently probed format in +0x1a and a small state in +0x20.
struct CMap2 {
    uint32 pad00[3];      // 0x00..0x0b
    uint32* f0c;          // +0x0c (array of sub-table records)
    uint32 f10;           // +0x10 (offset into the loaded table)
    uint32 pad14;         // +0x14
    int16 f18;            // +0x18 (sub-table index)
    uint16 f1a;           // +0x1a (format: 0/2/4/6/9999)
    uint32 pad1c;         // +0x1c
    uint16 f20;           // +0x20
};

struct Metrics {
    int32 flag;    // +0x00
    uint16 f04;    // +0x04
    uint16 f06;    // +0x06
    uint16 f08;    // +0x08
    uint16 f0a;    // +0x0a
    int32 f0c;     // +0x0c
    int32 f10;     // +0x10
    uint16 f14;    // +0x14
    uint16 f16;    // +0x16
};

struct Rec {
    uint32 key;    // +0x0
    uint16 v;      // +0x4
    uint16 pad;    // +0x6
};

extern "C" {
void* tsi_AllocMem(tsiMemObject* mem, int32 size);                                 // 0x008d1260
void  tsi_DeAllocMem(tsiMemObject* mem, void* p);                                  // 0x008d1440
void  tsi_EmergencyShutDown(tsiMemObject* mem);                                    // 0x008d1210
int32 util_FixSin(int32 x);                                                        // 0x008d1730
void* __cdecl memset(void* dst, int val, unsigned int n);                          // 0x011e073e
int   __cdecl setjmp3(void* jmpbuf, int arg);                                      // 0x011e0cac

void  FFT1HintClass_releaseMem(void* h);                                           // 0x008a8ff0
void  Delete_FFT1HintClass(void* h);                                               // 0x008a90f0
void* tsi_T1GetGlyphByIndex(void* t, uint16 idx, int16* outX, int16* outW, void* p5, int32 p6); // 0x008b8230
void* tsi_T2GetGlyphByIndex(void* t, uint16 idx, uint16* outAW, uint16* outLSB);   // 0x008bdca0
void* FUN_008b4cc0(void* t, uint16 idx, int16* outW, uint16* outH, void* reserved); // 0x008b4cc0
void* FUN_008b0480(tsiMemObject* mem, int32 a, int32 b, int32 c, int32 d);         // 0x008b0480
void* BuildGlyphT2KS(void* font, void* g, int32 idx, uint16* aw, int16* upem, void* p6, void* p7); // 0x008cb7f0
InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 off, uint32 len, int32 a, int* err); // 0x008cc330
void  Delete_InputStream(InputStream* in, int* err);                               // 0x008cc5d0
sfnt_DirectoryEntry* GetTableDirEntry_sfntClass(sfntClass* t, int32 tag);          // 0x008cebe0
GlyphClass* New_GlyphClass(tsiMemObject* mem, InputStream* in, char readHints, int32 lsb,
                           int32 aw, int32 tsb, int32 ah);                         // 0x008ce020
void* FUN_008b0560(tsiMemObject* mem, InputStream* in, int32 flag, int32 lsb, int32 aw,
                   int32 tsb, int32 ah, void* model);                              // 0x008b0560

void  FUN_008cc020(void* p);                                                       // 0x008cc020
void  Delete_sfnt_OffsetTable(void* p);                                            // 0x008cd910
void  Delete_cmapClass(void* p);                                                   // 0x008cd520
void  Delete_kernClass(void* p);                                                   // 0x008cd790
void  FUN_008cd0f0(void* p);                                                       // 0x008cd0f0
int32 FUN_008cd260(void* ctx, uint32 code);                                        // 0x008cd260
int32 FUN_008cd350(void* ctx, uint32 code);                                        // 0x008cd350
uint16 FUN_008cd4b0(void* ctx, uint16 code);                                       // 0x008cd4b0
void  tsi_DeleteT1Class(void* p);                                                  // 0x008b9f20
void  tsi_DeleteCFFClass(void* p);                                                 // 0x008bdb70
void  tsi_DeletePFRClass(void* p);                                                 // 0x008b1520
void  Delete_blocClass(void* p);                                                   // 0x008c4000
}

// @ 0x008cef90
int32 GetNumGlyphs_sfntClass(sfntClass* t)
{
    int32 n;
    if (t->T1 != NULL) return t->T1->NumCharStrings;
    if (t->T2 != NULL) return t->T2->NumCharStrings;
    if (t->PFR != NULL) return t->PFR->NumCharStrings;
    n = t->maxp->numGlyphs;
    if (t->loca != NULL && t->loca->n <= n) n = t->loca->n - 1;
    return n;
}

// @ 0x008cefe0
GlyphClass* GetGlyphByIndex(sfntClass* t, int32 glyph, uint32 flag, uint16* outAW, uint16* outVAW)
{
    GlyphClass* g;
    sfnt_DirectoryEntry* de;
    InputStream* in;
    int32 m, lsb, aw, vlsb, vaw;
    uint32 lo, hi;

    *outAW = 0;
    *outVAW = 0;

    if (t->T1 != NULL) {
        m = 0;
        if (t->xPPEm != -1 && t->yPPEm != -1) {
            m = t->xPPEm;
            if (t->yPPEm <= t->xPPEm) m = t->yPPEm;
        }
        if ((uint8)flag == 0) {
            g = (GlyphClass*)tsi_T1GetGlyphByIndex(t->T1, (uint16)glyph, (int16*)outAW,
                                                   (int16*)outVAW, NULL, -1);
        } else {
            g = (GlyphClass*)tsi_T1GetGlyphByIndex(t->T1, (uint16)glyph, (int16*)outAW,
                                                   (int16*)outVAW, t->ffhint, m);
            if (g->pointCount == 0) {
                FFT1HintClass_releaseMem(t->ffhint);
            }
        }
        g->f76 = (uint16)glyph;
        return g;
    }
    if (t->T2 != NULL) {
        g = (GlyphClass*)tsi_T2GetGlyphByIndex(t->T2, (uint16)glyph, outAW, outVAW);
        g->f76 = (uint16)glyph;
        return g;
    }
    if (t->PFR != NULL) {
        if ((uint8)flag == 0) {
            g = (GlyphClass*)FUN_008b4cc0(t->PFR, (uint16)glyph, (int16*)outAW, outVAW, NULL);
        } else {
            g = (GlyphClass*)FUN_008b4cc0(t->PFR, (uint16)glyph, (int16*)outAW, outVAW, t->ffhint);
            if (g->pointCount == 0) {
                FFT1HintClass_releaseMem(t->ffhint);
            }
        }
        g->f76 = (uint16)glyph;
        return g;
    }
    if (t->head->glyphDataFormat == 2000) {
        g = (GlyphClass*)BuildGlyphT2KS(t, NULL, glyph, outAW, (int16*)outVAW, NULL, NULL);
        g->f76 = (uint16)glyph;
        return g;
    }
    de = GetTableDirEntry_sfntClass(t, 0x676c7966);
    if (de != NULL && t->loca != NULL && (t->hmtx != NULL || t->vmtx != NULL)
        && glyph >= 0 && glyph < t->numGlyphs) {
        lo = t->loca->offsets[glyph];
        hi = t->loca->offsets[glyph + 1];
        if (t->hmtx != NULL) {
            aw = t->hmtx->aw[glyph];
            lsb = t->hmtx->lsb[glyph];
        } else {
            aw = 0x800;
            lsb = 0;
        }
        if (t->vmtx != NULL) {
            vaw = t->vmtx->aw[glyph];
            vlsb = t->vmtx->lsb[glyph];
        } else {
            vaw = 0;
            vlsb = 0;
            if (t->hhea != NULL) {
                vaw = (uint16)(t->hhea->LineGap - t->hhea->Descender + t->hhea->Ascender);
                vlsb = vaw / 10;
            }
        }
        if (lo < hi) {
            in = New_InputStream2(t->mem, t->in, de->offset + lo, hi - lo, 2, NULL);
            if (t->head->glyphDataFormat == 2000) {
                g = (GlyphClass*)FUN_008b0560(t->mem, in, (int32)flag, lsb, aw, vlsb, vaw, t->model);
            } else {
                g = New_GlyphClass(t->mem, in, (char)flag, lsb, aw, vlsb, vaw);
            }
            Delete_InputStream(in, NULL);
        } else {
            g = (GlyphClass*)FUN_008b0480(t->mem, lsb, aw, vlsb, vaw);
        }
        *outAW = (uint16)aw;
        *outVAW = (uint16)vaw;
        g->f76 = (uint16)glyph;
        return g;
    }
    g = (GlyphClass*)FUN_008b0480(t->mem, 0, 0, 0, 0);
    g->f76 = (uint16)glyph;
    return g;
}

// @ 0x008cf330
void FF_SetStyleCallbacks(sfntClass* t, uint32* src)
{
    if (src != NULL) {
        t->StyleFunc = (void*)src[0];
        t->StyleMetricsFunc = (StyleMetricsFuncPtr)src[1];
        t->params[0] = (int32)src[2];
        t->params[1] = (int32)src[3];
        t->params[2] = (int32)src[4];
        t->params[3] = (int32)src[5];
    } else {
        t->StyleFunc = NULL;
        t->StyleMetricsFunc = NULL;
    }
}

// @ 0x008cf390
uint16 Get_HMTX_AW(hmtxClass* h, uint16 i)
{
    return h->aw[i];
}

// @ 0x008cf3b0
uint16 Get_Cached_AW(sfntClass* t, uint32 code)
{
    uint16 idx = (uint16)((uint16)code % 251);
    uint16 r;

    if (t->awCache_hashKey == NULL) {
        uint16* p = (uint16*)tsi_AllocMem(t->mem, 0x3ec);
        int32 i;
        t->awCache_aw = p + 251;
        t->awCache_hashKey = p;
        for (i = 0; i < 251; i++) p[i] = 0xffff;
    } else if (t->awCache_hashKey[idx] == (uint16)code) {
        return t->awCache_aw[idx];
    }
    r = ((uint16 (__cdecl*)(void*, uint32))t->GetAWFuncPtr2)(t->GetAWParam2, code);
    t->awCache_hashKey[idx] = (uint16)code;
    t->awCache_aw[idx] = r;
    return r;
}

// @ 0x008cf450
uint16 FF_GetUPEM(sfntClass* t)
{
    return t->upem;
}

// @ 0x008cf460
void GetFontWideOutlineMetrics(sfntClass* t, Metrics* a, Metrics* b)
{
    int32 v;
    int32 i;

    b->flag = 0;
    a->flag = 0;
    a->f14 = 0;
    a->f16 = 0;
    b->f14 = 0;
    b->f16 = 0;

    if (t->T1 != NULL) {
        a->flag = 1;
        a->f04 = t->T1->m1e8;
        a->f06 = t->T1->m1ec;
        a->f08 = t->T1->m1f0;
        a->f0a = t->T1->m1f4;
        v = t->T1->m1f8;
        a->f0c = 0;
        a->f10 = 0x10000;
        if (v != 0) {
            if (v < 0) v = -v;
            a->f0c = util_FixSin(v);
            a->f10 = util_FixSin(0x5a0000 - v);
        }
        a->f14 = t->T1->m1fc;
        a->f16 = t->T1->m200;
        return;
    }
    if (t->T2 != NULL) {
        a->flag = 1;
        a->f04 = t->T2->m224;
        a->f06 = t->T2->m228;
        a->f08 = t->T2->m22c;
        a->f0a = t->T2->m230;
        v = t->T2->m234;
        a->f0c = 0;
        a->f10 = 0x10000;
        if (v != 0) {
            if (v < 0) v = -v;
            a->f0c = util_FixSin(v);
            a->f10 = util_FixSin(0x5a0000 - v);
        }
        a->f14 = t->T2->m3a4;
        a->f16 = t->T2->m3a8;
        return;
    }
    if (t->PFR != NULL) {
        a->flag = 1;
        a->f04 = t->PFR->m114;
        a->f06 = t->PFR->m118;
        a->f08 = t->PFR->m11c;
        a->f0a = t->PFR->m120;
        v = t->PFR->m124;
        a->f0c = 0;
        a->f10 = 0x10000;
        if (v != 0) {
            if (v < 0) v = -v;
            a->f0c = util_FixSin(v);
            a->f10 = util_FixSin(0x5a0000 - v);
        }
        return;
    }
    a->f14 = t->post_underlinePosition;
    a->f16 = t->post_underlineThickness;
    if (t->hhea != NULL) {
        a->flag = 1;
        a->f04 = t->hhea->Ascender;
        a->f06 = t->hhea->Descender;
        a->f08 = t->hhea->LineGap;
        a->f0a = t->hhea->advanceWidthMax;
        a->f0c = t->hhea->caretSlopeRun;
        a->f10 = t->hhea->caretSlopeRise;
        for (i = 0; i < 16; i++) {
            if (a->f0c >= 0x10000 || a->f0c <= -0x10000
                || a->f10 >= 0x10000 || a->f10 <= -0x10000) break;
            a->f0c *= 2;
            a->f10 *= 2;
        }
    }
    if (t->vhea != NULL) {
        b->flag = 1;
        b->f04 = t->vhea->Ascender;
        b->f06 = t->vhea->Descender;
        b->f08 = t->vhea->LineGap;
        b->f0a = t->vhea->advanceWidthMax;
        b->f0c = t->vhea->caretSlopeRun;
        b->f10 = t->vhea->caretSlopeRise;
        for (i = 0; i < 16; i++) {
            if (b->f0c >= 0x10000 || b->f0c <= -0x10000
                || b->f10 >= 0x10000 || b->f10 <= -0x10000) break;
            b->f0c *= 2;
            b->f10 *= 2;
        }
    }
}

// @ 0x008cf8d0
void FF_Delete_sfntClass(sfntClass* t, int* jmpbuf)
{
    tsiMemObject* mem;
    ttcfClass* ttcf;
    sfnt_OffsetTable* ot;
    slocClass* sloc;

    if (jmpbuf != NULL) {
        int r;
        mem = t->mem;
        r = setjmp3((char*)mem + 0x10, 0);
        *jmpbuf = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return;
        }
    }
    mem = t->mem;

    ttcf = t->ttcf;
    if (ttcf != NULL) {
        tsi_DeAllocMem(ttcf->mem, ttcf->tableOffsets);
        tsi_DeAllocMem(ttcf->mem, ttcf);
    }
    ot = t->offsetTable0;
    if (ot != NULL) {
        tsi_DeAllocMem(ot->mem, ot->table);
        tsi_DeAllocMem(ot->mem, ot);
    }
    if (t->head != NULL) tsi_DeAllocMem(t->head->mem, t->head);
    if (t->hhea != NULL) tsi_DeAllocMem(t->hhea->mem, t->hhea);
    if (t->vhea != NULL) tsi_DeAllocMem(t->vhea->mem, t->vhea);
    if (t->hmtx != NULL) {
        tsi_DeAllocMem(t->hmtx->mem, t->hmtx->lsb);
        tsi_DeAllocMem(t->hmtx->mem, t->hmtx->aw);
        tsi_DeAllocMem(t->hmtx->mem, t->hmtx);
    }
    if (t->vmtx != NULL) {
        tsi_DeAllocMem(t->vmtx->mem, t->vmtx->lsb);
        tsi_DeAllocMem(t->vmtx->mem, t->vmtx->aw);
        tsi_DeAllocMem(t->vmtx->mem, t->vmtx);
    }
    if (t->maxp != NULL) tsi_DeAllocMem(t->maxp->mem, t->maxp);
    if (t->loca != NULL) {
        tsi_DeAllocMem(t->loca->mem, t->loca->offsets);
        tsi_DeAllocMem(t->loca->mem, t->loca);
    }
    sloc = t->sloc;
    if (sloc != NULL) {
        tsi_DeAllocMem(sloc->mem, sloc->sloc);
        tsi_DeAllocMem(sloc->mem, sloc);
    }

    FUN_008cc020(t->ffst);
    Delete_sfnt_OffsetTable(t->ffhm);
    Delete_cmapClass(t->cmap);
    Delete_kernClass(t->kern);
    tsi_DeleteT1Class(t->T1);
    tsi_DeleteCFFClass(t->T2);
    tsi_DeletePFRClass(t->PFR);
    Delete_blocClass(t->bloc);
    Delete_sfnt_OffsetTable(t->ebsc);
    FUN_008cd0f0(t->t2kTT);
    Delete_FFT1HintClass(t->ffhint);

    tsi_DeAllocMem(mem, t->awCache_hashKey);
    tsi_DeAllocMem(mem, t);
}

// @ 0x008cfac0
void FF_SortMapRecords(Rec* base, int32 n)
{
    int32 gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        int32 i;
        for (i = gap; i < n; i++) {
            int32 j;
            for (j = i - gap; j >= 0; j -= gap) {
                uint32 a = base[j].key;
                uint32 b = base[j + gap].key;
                if (a <= b) break;
                uint16 va = base[j].v;
                base[j].key = b;
                base[j].v = base[j + gap].v;
                base[j + gap].v = va;
                base[j + gap].key = a;
            }
        }
    }
}

// @ 0x008cfb70
int32 __fastcall cmap2_char_index(uint32 unused, CMap2* cmap, uint32 code)
{
    uint8* pb;
    uint8* p;
    uint8* p2;
    int32 n;
    int32 start;
    int32 result = 0;
    uint32 u;

    pb = (uint8*)(*(uint32*)(*(uint32*)(cmap->f0c + (int16)cmap->f18) + 4) + cmap->f10 + 6);
    p = pb + (((code >> 8) & 0xff) * 2);
    n = (int16)((uint16)p[0] * 0x100 + p[1]);
    p2 = pb + n + 0x200;

    start = (int16)((uint16)p2[0] * 0x100 + p2[1]);
    if ((int32)(code & 0xff) < start) {
        cmap->f20 = 2;
        return 0;
    }
    if (*(uint16*)p == 0) {
        cmap->f20 = 1;
        if ((uint16)code > 0xff) return 0;
        if (*(int16*)(pb + (code & 0xff) * 2) != 0) return 0;
    }
    u = (uint8)((uint8)code - p2[1]);
    if ((int32)u < (int32)(int16)((uint16)p2[2] * 0x100 + p2[3])) {
        uint8* q;
        uint8* r;
        cmap->f20 = 2;
        q = p2 + 6 + (int16)((uint16)p2[6] * 0x100 + p2[7]);
        r = q + u * 2;
        if (*(int16*)(q + u * 2) != 0) {
            return (uint16)((uint16)((uint16)r[0] + p2[4]) * 0x100 + p2[5] + r[1]);
        }
    }
    return result;
}

// @ 0x008cfcb0
uint16 __fastcall cmap_char_index(uint32 code, CMap2* cmap)
{
    uint16 fmt = cmap->f1a;
    cmap->f20 = 2;
    if (fmt == 0) {
        if ((uint16)code >= 0x100) return 0;
        return *(uint8*)(*(uint32*)(*(uint32*)(cmap->f0c + (int16)cmap->f18) + 4)
                         + cmap->f10 + 6 + (code & 0xffff));
    }
    if (fmt == 2) return (uint16)cmap2_char_index(code, cmap, code);
    if (fmt == 4) return (uint16)FUN_008cd350(cmap, code);
    if (fmt == 6) return (uint16)FUN_008cd4b0(cmap, (uint16)code);
    if (fmt == 0x270f) return (uint16)FUN_008cd260(cmap, code);
    return 0;
}
