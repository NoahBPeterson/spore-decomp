/* Slice s008bdb70 -- T2K / Font Fusion CFF reader (module "EA-UTF").
 *
 * 008bdb70 tsi_DeleteCFFClass        frees every CFF index / hash / table of a CFFClass
 * 008bdca0 tsi_T2GetGlyphByIndex     builds one glyph from the CharStrings index
 * 008bdec0 ShellSortT2Cmap           shell sort of the sidCode table (static, esi convention)
 * 008bdf80 T2_FindSID                binary search of the sidCode table (static, register conv)
 * 008bdfe0 T2_CharCodeToGlyphIndex   char code -> glyph index via CMAP table
 * 008be080 BuildT2MetricsEtc         derive upem/ascent/descent/lineGap from 'f'/'g'
 * 008be220 FF_GetAW_CFFClass         advance width of one glyph
 *
 * COMPILE AS C: "/O2 /MD /Gy /TC" (T2K is C, exactly like s008bb550 / s008be260).
 * Layouts are the 2008 dev-PDB structs (CFFClass, InputStream_t, TopDictInfo,
 * CFFIndexClass, GlyphClass), checked against the retail disassembly.
 */

typedef unsigned char  uint8;
typedef signed char    int8;
typedef unsigned short uint16;
typedef short          int16;
typedef unsigned long  uint32;
typedef long           int32;
typedef long           F16Dot16;

typedef struct tsiMemObject tsiMemObject;
typedef struct hashClass hashClass;

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest_ram, unsigned long offset, long numBytes);

typedef struct InputStream {             /* InputStream_t, size 0x23c */
    uint8*          privateBase;         /* +0x000 */
    PF_READ_TO_RAM  ReadToRamFunc;       /* +0x004 */
    void*           nonRamID;            /* +0x008 */
    uint8           tmp_ch;              /* +0x00c */
    uint8           cacheBase[512];      /* +0x00d */
    long            bytesLeftToPreLoad;  /* +0x210 */
    unsigned long   cacheCount;          /* +0x214 */
    unsigned long   cachePosition;       /* +0x218 */
    unsigned long   pos;                 /* +0x21c */
    unsigned long   maxPos;              /* +0x220 */
    unsigned long   posZero;             /* +0x224 */
    char            constructorType;     /* +0x228 */
    tsiMemObject*   mem;                 /* +0x22c */
    unsigned long   bitBufferIn;         /* +0x230 */
    unsigned long   bitCountIn;          /* +0x234 */
    uint8           decrypted;           /* +0x238 */
} InputStream;

typedef struct CFFIndexClass {           /* size 0x14 */
    tsiMemObject*   mem;                 /* +0x00 */
    unsigned long   baseDataOffset;      /* +0x04 */
    uint8           offSize;             /* +0x08 */
    unsigned long*  offsetArray;         /* +0x0c */
    uint16          count;               /* +0x10 */
} CFFIndexClass;

typedef struct TopDictInfo {             /* size 0x170 */
    uint16  version;                     /* +0x00 */
    uint16  Notice;                      /* +0x02 */
    uint16  FullName;                    /* +0x04 */
    uint16  FamilyName;                  /* +0x06 */
    uint16  Weight;                      /* +0x08 */
    long    UniqueId;                    /* +0x0c */
    long    bbox_xmin;                   /* +0x10 */
    long    bbox_ymin;                   /* +0x14 */
    long    bbox_xmax;                   /* +0x18 */
    long    bbox_ymax;                   /* +0x1c */
    unsigned long isFixedPitch;          /* +0x20 */
    long    italicAngle;                 /* +0x24 */
    int     UnderlinePosition;           /* +0x28 */
    int     UnderlineThickness;          /* +0x2c */
    uint8   CharstringType;              /* +0x30 */
    long    charset;                     /* +0x34 */
    long    Encoding;                    /* +0x38 */
    long    Charstrings;                 /* +0x3c */
    long    PrivateDictSize;             /* +0x40 */
    long    PrivateDictOffset;           /* +0x44 */
    int     numAxes;                     /* +0x48 */
    int     numMasters;                  /* +0x4c */
    int     lenBuildCharArray;           /* +0x50 */
    long*   buildCharArray;              /* +0x54 */
    long    defaultWeight[16];           /* +0x58 */
    uint16  NDV;                         /* +0x98 */
    uint16  CDV;                         /* +0x9a */
    long    reg_WeightVector[16];        /* +0x9c */
    long    reg_NormalizedDesignVector[16]; /* +0xdc */
    long    reg_UserDesignVector[16];    /* +0x11c */
    long    m00, m01, m10, m11;          /* +0x15c */
    uint8   isCIDKeyed;                  /* +0x16c */
} TopDictInfo;

typedef struct PrivateDictInfo {         /* size 0x10 */
    long Subr;                           /* +0x0 */
    long SubrOffset;                     /* +0x4 */
    long defaultWidthX;                  /* +0x8 */
    long nominalWidthX;                  /* +0xc */
} PrivateDictInfo;

typedef struct sidCode {                 /* one T2_CMAPTable entry */
    uint16 sid;                          /* +0 */
    uint16 glyphIndex;                   /* +2 */
} sidCode;

typedef struct GlyphClass {              /* size 0x78 */
    tsiMemObject* mem;                   /* +0x00 */
    short contourCountMax;               /* +0x04 */
    long  pointCountMax;                 /* +0x08 */
    long  colorPlaneCount;               /* +0x0c */
    long  colorPlaneCountMax;            /* +0x10 */
    short ctrBuffer[16];                 /* +0x14 */
    short curveType;                     /* +0x34 */
    short contourCount;                  /* +0x36 */
    short pointCount;                    /* +0x38 */
    short* sp;                           /* +0x3c */
    short* ep;                           /* +0x40 */
    short* oox;                          /* +0x44 */
    short* ooy;                          /* +0x48 */
    uint8* onCurve;                      /* +0x4c */
    long*  x;                            /* +0x50 */
    long*  y;                            /* +0x54 */
    short* componentData;                /* +0x58 */
    long  componentSize;                 /* +0x5c */
    long  componentSizeMax;              /* +0x60 */
    uint8* hintFragment;                 /* +0x64 */
    long  hintLength;                    /* +0x68 */
    short xmin;                          /* +0x6c */
    short ymin;                          /* +0x6e */
    short xmax;                          /* +0x70 */
    short ymax;                          /* +0x72 */
    char  dropOutControl;                /* +0x74 */
    uint16 myGlyphIndex;                 /* +0x76 */
} GlyphClass;

#define T2_MAX_STACK 64

typedef struct CFFClass {                /* size 0x520 */
    tsiMemObject*   mem;                 /* +0x000 */
    InputStream*    in;                  /* +0x004 */
    unsigned long   cffOffset;           /* +0x008 */
    long            NumCharStrings;      /* +0x00c */
    uint16          charCodeToSID[256];  /* +0x010 */
    sidCode*        T2_CMAPTable;        /* +0x210 */
    hashClass*      T2_StringsHash;      /* +0x214 */
    hashClass*      T2_SIDToCharCodeHash;/* +0x218 */
    long            upem;                /* +0x21c */
    long            maxPointCount;       /* +0x220 */
    long            ascent;              /* +0x224 */
    long            descent;             /* +0x228 */
    long            lineGap;             /* +0x22c */
    long            advanceWidthMax;     /* +0x230 */
    long            italicAngle;         /* +0x234 */
    long            fontNum;             /* +0x238 */
    F16Dot16        gStackValues[T2_MAX_STACK]; /* +0x23c */
    long            gNumStackValues;     /* +0x33c */
    GlyphClass*     glyph;               /* +0x340 */
    long            x;                   /* +0x344 */
    long            y;                   /* +0x348 */
    long            awy;                 /* +0x34c */
    long            awx;                 /* +0x350 */
    long            lsbx;                /* +0x354 */
    long            lsby;                /* +0x358 */
    int             numStemHints;        /* +0x35c */
    int             pointAdded;          /* +0x360 */
    int             widthDone;           /* +0x364 */
    int             stkClrOpCalled;      /* +0x368 */
    uint16          seed;                /* +0x36c */
    uint8           major;               /* +0x36e */
    uint8           minor;               /* +0x36f */
    uint8           hdrSize;             /* +0x370 */
    uint8           offSize;             /* +0x371 */
    CFFIndexClass*  name;                /* +0x374 */
    CFFIndexClass*  topDict;             /* +0x378 */
    TopDictInfo     topDictData;         /* +0x37c */
    CFFIndexClass*  string;              /* +0x4ec */
    CFFIndexClass*  gSubr;               /* +0x4f0 */
    long            gSubrBias;           /* +0x4f4 */
    CFFIndexClass*  CharStrings;         /* +0x4f8 */
    PrivateDictInfo privateDictData;     /* +0x4fc */
    CFFIndexClass*  lSubr;               /* +0x50c */
    long            lSubrBias;           /* +0x510 */
    unsigned long   isFixedPitch;        /* +0x514 */
    uint16          firstCharCode;       /* +0x518 */
    uint16          lastCharCode;        /* +0x51a */
    int             glyphExists;         /* +0x51c */
} CFFClass;

/* ---- callees (address in the comment) ---- */
void tsi_DeAllocMem(tsiMemObject* mem, void* p);              // 0x008d1440
void Delete_hashClass(hashClass* h);                          // 0x008d1cb0
GlyphClass* New_EmptyGlyph(tsiMemObject* mem, int a, int b, int c, int d); // 0x008b0480
int util_FixDiv(int a, int b);                                // 0x008d16d0
void Seek_InputStream(InputStream* t, unsigned long offset);  // 0x008cc580
void Type2BuildChar(CFFClass* t, InputStream* in, long byteCount, long recursionLevel); // 0x008bb550
void glyph_CloseContour(GlyphClass* g);                       // 0x008afde0
void FlipContourDirection(GlyphClass* g);                     // 0x008b6920
void Delete_GlyphClass(GlyphClass* g);                        // 0x008b0280

/* ------------------------------------------------------------------ */
// @ 0x008bdb70
void tsi_DeleteCFFClass(CFFClass* t)
{
    CFFIndexClass* p;

    if (t == 0)
        return;
    p = t->name;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    tsi_DeAllocMem(t->mem, t->topDictData.buildCharArray);
    p = t->topDict;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    p = t->string;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    p = t->gSubr;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    p = t->CharStrings;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    p = t->lSubr;
    if (p != 0) {
        tsi_DeAllocMem(p->mem, p->offsetArray);
        tsi_DeAllocMem(p->mem, p);
    }
    Delete_hashClass(t->T2_StringsHash);
    Delete_hashClass(t->T2_SIDToCharCodeHash);
    tsi_DeAllocMem(t->mem, t->T2_CMAPTable);
    tsi_DeAllocMem(t->mem, t);
}

/* ------------------------------------------------------------------ */
// @ 0x008bdca0
__declspec(noinline)
GlyphClass* tsi_T2GetGlyphByIndex(CFFClass* t, unsigned short glyphIndex,
                                  unsigned short* outAwx, unsigned short* outSomething)
{
    int numCharStrings = t->CharStrings->count;
    GlyphClass* glyph = New_EmptyGlyph(t->mem, 0, 0, 0, 0);

    t->glyph = glyph;
    glyph->curveType = 3;
    t->gNumStackValues = 0;
    if (glyphIndex < numCharStrings) {
        short mn;
        short pc;
        short* oox;
        long i, len;
        unsigned long off;

        t->awx = t->privateDictData.defaultWidthX;
        t->awy = 0;
        t->lsbx = 0;
        t->lsby = 0;
        t->x = 0;
        t->y = 0;
        t->numStemHints = 0;
        t->pointAdded = 0;
        t->widthDone = 0;
        t->stkClrOpCalled = 0;

        off = t->CharStrings->offsetArray[glyphIndex];
        len = t->CharStrings->offsetArray[glyphIndex + 1] - off;
        Seek_InputStream(t->in, t->CharStrings->baseDataOffset + off);
        Type2BuildChar(t, t->in, len, 0);
        glyph_CloseContour(t->glyph);

        oox = t->glyph->oox;
        mn = oox[0];
        pc = t->glyph->pointCount;
        for (i = 1; i < pc; i++)
            if (oox[i] < mn)
                mn = oox[i];
        t->lsbx = mn;
    }

    {
        GlyphClass* g = t->glyph;
        unsigned short upem = (unsigned short)t->upem;
        unsigned short maxy;
        short midx;
        long i;

        g->ooy[g->pointCount] = 0;
        g->oox[g->pointCount] = 0;
        g->ooy[g->pointCount + 1] = (short)t->awy;
        g->oox[g->pointCount + 1] = (short)t->awx;
        *outAwx = (unsigned short)t->awx;
        midx = (short)((g->oox[g->pointCount] + g->oox[g->pointCount + 1]) >> 1);
        maxy = (unsigned short)g->ooy[0];
        for (i = 1; i < g->pointCount; i++)
            if (g->ooy[i] > maxy)
                maxy = g->ooy[i];
        g->ooy[g->pointCount + 2] = (short)(maxy + upem / 10);
        g->oox[g->pointCount + 2] = midx;
        g->ooy[g->pointCount + 3] = (short)(g->ooy[g->pointCount + 2] - upem);
        g->oox[g->pointCount + 3] = midx;
        *outSomething = upem;
        t->glyph = 0;
        FlipContourDirection(g);
        return g;
    }
}

/* ------------------------------------------------------------------ */
// @ 0x008bdec0
static __declspec(noinline) void ShellSortT2Cmap(sidCode* base, long num)
{
    long m, i, j;

    for (m = num / 2; m > 0; m /= 2) {
        if (m >= num)
            continue;
        for (i = m; i < num; i++) {
            for (j = i - m; j >= 0; j -= m) {
                uint16 a, b;
                if (base[j].sid <= base[j + m].sid)
                    break;
                a = base[j].sid;
                b = base[j].glyphIndex;
                base[j].sid = base[j + m].sid;
                base[j].glyphIndex = base[j + m].glyphIndex;
                base[j + m].sid = a;
                base[j + m].glyphIndex = b;
            }
        }
    }
}

/* ------------------------------------------------------------------ */
// @ 0x008bdf80
static __declspec(noinline) unsigned char T2_FindSID(CFFClass* t, uint16 key, uint16* out)
{
    long lo = 0;
    long hi = t->NumCharStrings - 1;

    while (hi >= lo) {
        long mid = (lo + hi) / 2;
        uint16 sid = t->T2_CMAPTable[mid].sid;
        short c;
        if (key == sid)
            c = 0;
        else if (key < sid) {
            hi = mid - 1;
            continue;
        } else
            c = 1;
        lo = mid + 1;
        if (c == 0) {
            *out = t->T2_CMAPTable[mid].glyphIndex;
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
// @ 0x008bdfe0
/* Plain cdecl with two stack arguments (the caller in BuildT2MetricsEtc pushes
 * `code` then `t`), so it is deliberately NOT a TU-local static. */
__declspec(noinline)
uint16 T2_CharCodeToGlyphIndex(CFFClass* t, uint16 code)
{
    uint16 out = 0;

    t->glyphExists = 1;
    if (t->topDictData.isCIDKeyed == 0) {
        if (code >= 0x100) {
            t->glyphExists = 0;
            goto fail;
        }
        if (t->charCodeToSID[code] == 0)
            goto fail;
        if (T2_FindSID(t, t->charCodeToSID[code], &out) != 0)
            goto found;
    } else {
        if (code == 0)
            goto fail;
        if (T2_FindSID(t, code, &out) != 0)
            goto found;
    }
fail:
    t->glyphExists = 0;
    return 0;
found:
    return out;
}

/* ------------------------------------------------------------------ */
/* glyph y-extent helpers (0x008b68c0 / 0x008b68f0); static copies so
 * this TU gives them the eax register convention like the original.  */
static __declspec(noinline) short GlyphMaxY(GlyphClass* g)
{
    short* ooy = g->ooy;
    long n = g->pointCount;
    short mx = ooy[0];
    long i;

    for (i = 1; i < n; i++)
        if (ooy[i] > mx)
            mx = ooy[i];
    return mx;
}

static __declspec(noinline) short GlyphMinY(GlyphClass* g)
{
    short* ooy = g->ooy;
    long n = g->pointCount;
    short mn = ooy[0];
    long i;

    for (i = 1; i < n; i++)
        if (ooy[i] < mn)
            mn = ooy[i];
    return mn;
}

/* ------------------------------------------------------------------ */
// @ 0x008be080
static __declspec(noinline) void BuildT2MetricsEtc(CFFClass* t)
{
    uint16 g1, g2;
    uint16 awx, tmp;
    F16Dot16 scale;

    t->NumCharStrings = t->CharStrings->count;
    t->upem = util_FixDiv(0x3e80000, t->topDictData.m00) >> 16;
    scale = t->topDictData.m00;
    t->topDictData.m00 = util_FixDiv(scale, scale);
    t->topDictData.m01 = util_FixDiv(t->topDictData.m01, scale);
    t->topDictData.m10 = util_FixDiv(t->topDictData.m10, scale);
    t->topDictData.m11 = util_FixDiv(t->topDictData.m11, scale);
    t->maxPointCount = 0;
    t->ascent = 0x7fff;
    t->descent = 0x7fff;
    t->italicAngle = t->topDictData.italicAngle;
    g1 = T2_CharCodeToGlyphIndex(t, 0x66);
    g2 = T2_CharCodeToGlyphIndex(t, 0x67);
    if (t->ascent == 0x7fff && g1 != 0) {
        GlyphClass* g = tsi_T2GetGlyphByIndex(t, g1, &awx, &tmp);
        if (g != 0) {
            t->ascent = GlyphMaxY(g);
            Delete_GlyphClass(g);
        }
    }
    if (t->descent == 0x7fff && g2 != 0) {
        GlyphClass* g = tsi_T2GetGlyphByIndex(t, g2, &awx, &tmp);
        if (g != 0) {
            t->descent = GlyphMinY(g);
            Delete_GlyphClass(g);
        }
    }
    t->advanceWidthMax = t->upem;
    t->maxPointCount = 0x20;
    if (t->ascent == 0x7fff)
        t->ascent = 0x2ee;
    if (t->descent == 0x7fff)
        t->descent = 0xffffff06;
    t->lineGap = t->upem - t->ascent + t->descent;
    if (t->lineGap < 0)
        t->lineGap = 0;
}

/* ------------------------------------------------------------------ */
// @ 0x008be220
unsigned short FF_GetAW_CFFClass(CFFClass* t, unsigned short glyphIndex)
{
    /* The original compiler homed the advance-width output in the slot of the
     * (dead-after-the-call) first parameter, so the receiver is aliased to it. */
    unsigned short awx = 0;
    unsigned short tmp;
    GlyphClass* g = tsi_T2GetGlyphByIndex(t, glyphIndex, (unsigned short*)&t, &tmp);

    if (g != 0) {
        awx = (unsigned short)(unsigned long)t;
        Delete_GlyphClass(g);
    }
    return awx;
}

/* ------------------------------------------------------------------ */
/* same-TU stand-in callers so the static helpers above are emitted with
 * the register conventions the original TU gave them.                 */
void ShellSortStandin(CFFClass* t)                 /* original caller 0x8bec65 */
{
    ShellSortT2Cmap(t->T2_CMAPTable, t->NumCharStrings);
}
void BuildT2MetricsEtc_Standin(CFFClass* t)        /* original caller 0x8bf0ab */
{
    BuildT2MetricsEtc(t);
}
