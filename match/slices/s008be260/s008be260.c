/* Slice s008be260 -- 0x008be260 BuildT2CMAP (T2K / Font Fusion CFF reader, module "EA-UTF").
 *
 * Builds the CFF font's SID <-> glyph index table (t->T2_CMAPTable, one sidCode per
 * CharString) from the predefined charsets (ISOAdobe / Expert / ExpertSubset) or the
 * font's own charset (formats 0, 1, 2), then the 256-entry charCodeToSID map from the
 * standard/expert encoding or the font's custom encoding (formats 0, 1 plus the
 * supplement table), sorts the table by SID and, for CID-keyed fonts, records the
 * first/last SID.
 *
 * COMPILE AS C: "/O2 /MD /Gy /TC" (T2K is C; see s008bb550).  Layouts are the 2008
 * dev-PDB structs (CFFClass, InputStream_t, TopDictInfo, CFFIndexClass), checked
 * against the retail disassembly.
 *
 * ShellSortT2Cmap (0x008bdec0) is a static helper of the same file that receives the
 * table in esi; its body is reproduced here only so cl can give it that register
 * convention.
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
typedef struct GlyphClass GlyphClass;

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
    long Subr;
    long SubrOffset;
    long defaultWidthX;
    long nominalWidthX;
} PrivateDictInfo;

typedef struct sidCode {                 /* one T2_CMAPTable entry */
    uint16 sid;                          /* +0 */
    uint16 glyphIndex;                   /* +2 */
} sidCode;

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
    long            x, y, awy, awx, lsbx, lsby; /* +0x344 */
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

#define T2K_ERR_TRANS_FAIL 10024

void* tsi_AllocMem(tsiMemObject* t, unsigned long size);         /* 0x008d1260 */
void tsi_Error(tsiMemObject* t, int errcode);                    /* 0x008d10c0 */
void Seek_InputStream(InputStream* t, unsigned long offset);     /* 0x008cc580 */
void PrimeT2KInputStream(InputStream* t);                        /* 0x008cc0b0 */
int16 ReadInt16(InputStream* t);                                 /* 0x008cc190 */

/* Predefined charsets: {firstSID, lastSID} ranges ending with {0, 0}. */
extern const uint16 ISOAdobeSID[];      /* 0x014350e4 */
extern const uint16 ExpertSID[];        /* 0x014350f0 */
extern const uint16 ExpertSubsetSID[];  /* 0x01435138 */
/* Predefined encodings: {firstCode, lastCode, firstSID, lastSID} records up to code 255. */
typedef struct encodingRange { uint16 firstCode, lastCode, firstSID, lastSID; } encodingRange;
extern const encodingRange standardEncodingData[];  /* 0x01435198 */
extern const encodingRange expertEncodingData[];    /* 0x01435288 */

/* t2kstrm.h byte reader, fully expanded at each use (the stream expression is re-read). */
#define ReadUnsignedByteMacro(stream) ((uint8)((stream)->privateBase != 0 ? \
    ((stream)->ReadToRamFunc != 0 ? \
        ((((stream)->pos - (stream)->cachePosition + 1 > (stream)->cacheCount) ? PrimeT2KInputStream(stream) : (void)0), \
         (stream)->privateBase[((stream)->pos)++ - (stream)->cachePosition]) \
      : (stream)->privateBase[((stream)->pos)++]) \
    : ((stream)->ReadToRamFunc((stream)->nonRamID, &(stream)->tmp_ch, ((stream)->pos)++, 1) < 0 ? \
        (tsi_Error((stream)->mem, T2K_ERR_TRANS_FAIL), 0) : (stream)->tmp_ch)))

/* @ 0x008bdec0 (not part of this slice; needed for its esi register convention) */
static void ShellSortT2Cmap(sidCode* base, long num)
{
    long i, j, m;
    sidCode tmp;

    for (m = num / 2; m > 0; m /= 2) {
        for (j = m; j < num; j++) {
            for (i = j - m; i >= 0; i -= m) {
                if (base[i].sid <= base[i + m].sid)
                    break;
                tmp = base[i];
                base[i] = base[i + m];
                base[i + m] = tmp;
            }
        }
    }
}

/* @ 0x008be260 */
void BuildT2CMAP(CFFClass* t)
{
    long i, j, k;
    long code;
    uint8 count, ch, first, nLeft;
    const uint16* p;
    uint8 format;

    t->NumCharStrings = t->CharStrings->count;
    t->T2_CMAPTable = (sidCode*)tsi_AllocMem(t->mem, t->NumCharStrings * sizeof(sidCode));
    for (i = 0; i < 256; i++)
        t->charCodeToSID[i] = 0xffff;

    if (t->topDictData.charset < 3) {
        p = 0;
        switch (t->topDictData.charset) {
        case 0:
            p = ISOAdobeSID;
            break;
        case 1:
            p = ExpertSID;
            break;
        case 2:
            p = ExpertSubsetSID;
            break;
        }
        t->T2_CMAPTable[0].sid = t->T2_CMAPTable[0].glyphIndex = 0;
        for (i = 1; i < t->NumCharStrings; p += 2) {
            uint16 firstSID = p[0];
            uint16 lastSID = p[1];
            if (firstSID == 0 && lastSID == 0)
                break;
            for (code = firstSID; code <= lastSID && i < t->NumCharStrings; code++, i++) {
                t->T2_CMAPTable[i].glyphIndex = (uint16)i;
                t->T2_CMAPTable[i].sid = (uint16)code;
            }
        }
    } else {
        Seek_InputStream(t->in, t->cffOffset + t->topDictData.charset);
        format = ReadUnsignedByteMacro(t->in);
        t->T2_CMAPTable[0].sid = t->T2_CMAPTable[0].glyphIndex = 0;
        i = 1;
        if (format == 0) {
            for (; i < t->NumCharStrings; i++) {
                uint16 sid = ReadInt16(t->in);
                t->T2_CMAPTable[i].glyphIndex = (uint16)i;
                t->T2_CMAPTable[i].sid = sid;
            }
        } else if (format == 1 || format == 2) {
            while (i < t->NumCharStrings) {
                long firstSID = (uint16)ReadInt16(t->in);
                uint16 left;
                if (format == 1)
                    left = ReadUnsignedByteMacro(t->in);
                else
                    left = ReadInt16(t->in);
                for (j = 0; j <= left && i < t->NumCharStrings; j++, i++) {
                    t->T2_CMAPTable[i].glyphIndex = (uint16)i;
                    t->T2_CMAPTable[i].sid = (uint16)(j + firstSID);
                }
            }
        }
    }

    if (!t->topDictData.isCIDKeyed && t->topDictData.Encoding < 2) {
        uint16 firstCode, lastCode, firstSID, lastSID;
        const encodingRange* r = t->topDictData.Encoding == 0 ? standardEncodingData : expertEncodingData;
        k = 0;
        do {
            firstCode = r[k].firstCode;
            lastCode = r[k].lastCode;
            firstSID = r[k].firstSID;
            lastSID = r[k].lastSID;
            k++;
            if (firstSID == lastSID) {
                for (code = firstCode; code <= lastCode; code++)
                    t->charCodeToSID[code] = firstSID;
            } else {
                for (j = 0, code = firstCode; code <= lastCode; code++, j++)
                    t->charCodeToSID[code] = (uint16)(firstSID + j);
            }
        } while (lastCode < 255);
    } else if (!t->topDictData.isCIDKeyed) {
        Seek_InputStream(t->in, t->topDictData.Encoding + t->cffOffset);
        format = ReadUnsignedByteMacro(t->in);
        if ((format & 0x7f) == 0) {
            count = ReadUnsignedByteMacro(t->in);
            for (i = 0; i < count; i++) {
                ch = ReadUnsignedByteMacro(t->in);
                t->charCodeToSID[ch] = t->T2_CMAPTable[i + 1].sid;
            }
        } else if ((format & 0x7f) == 1) {
            count = ReadUnsignedByteMacro(t->in);
            k = 0;
            for (i = 0; i < count && k < 255; i++) {
                first = ReadUnsignedByteMacro(t->in);
                nLeft = ReadUnsignedByteMacro(t->in);
                for (j = 0; j <= nLeft && k < 255; j++) {
                    t->charCodeToSID[(uint8)(first + j)] = t->T2_CMAPTable[k + 1].sid;
                    k++;
                }
            }
        }
        if (format & 0x80) {
            count = ReadUnsignedByteMacro(t->in);
            for (i = 0; i < count; i++) {
                ch = ReadUnsignedByteMacro(t->in);
                t->charCodeToSID[ch] = ReadInt16(t->in);
            }
        }
    }

    ShellSortT2Cmap(t->T2_CMAPTable, t->NumCharStrings);
    if (t->topDictData.isCIDKeyed) {
        t->firstCharCode = t->T2_CMAPTable[0].sid;
        t->lastCharCode = t->T2_CMAPTable[t->NumCharStrings - 1].sid;
    }
}
