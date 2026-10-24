// Slice s008ce020: T2K (Type 2000 font scaler) New_GlyphClass: reads one TrueType 'glyf' entry
// (simple or composite) from an InputStream into a GlyphClass, then appends the 4 phantom points.
// The original receives mem in ECX and the stream in EAX: cl's register convention for a static
// function whose only caller (GetGlyphByIndex, 0x008cefe0) is in the same TU. A stand-in caller
// below reproduces it. Module flags: /O2 /MD /Gy /TP.
#include "types.h"

typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject;

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);

struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject* mem;             // +0x22c
};

struct GlyphClass {
    tsiMemObject* mem;      // +0x00
    int16 contourCount;     // +0x04
    int16 pad06;
    int32 pointCount32;     // +0x08
    int32 x0c;              // +0x0c
    int32 x10;              // +0x10
    int16 spBuffer[16];     // +0x14 (sp[8] + ep[8] for small glyphs)
    int16 x34;              // +0x34
    int16 contourCountMax;  // +0x36
    int16 pointCount;       // +0x38
    int16 pad3a;
    int16* sp;              // +0x3c
    int16* ep;              // +0x40
    int16* oox;             // +0x44
    int16* ooy;             // +0x48
    uint8* onCurve;         // +0x4c
    void* x50;              // +0x50
    void* x54;              // +0x54
    int16* componentData;   // +0x58
    int32 componentSize;    // +0x5c
    int32 componentSizeMax; // +0x60
    uint8* hintFragment;    // +0x64
    int32 hintLength;       // +0x68
    int16 xmin;             // +0x6c
    int16 ymin;             // +0x6e
    int16 xmax;             // +0x70
    int16 ymax;             // +0x72
    int32 x74;              // +0x74
};

extern "C" {
void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 tag);
void* tsi_AllocMem(tsiMemObject* mem, int32 size);
void* tsi_ReAllocMem(tsiMemObject* mem, void* p, int32 size);
void tsi_Error(tsiMemObject* mem, int32 code);
int16 ReadInt16(InputStream* in);
InputStream* New_InputStream2(tsiMemObject* mem, int32 fileID, int32 offset, int32 length, int32 refArg,
                             int32 closeFile);                  // 0x008cc330
void Delete_InputStream(InputStream* in, int32 closeFile);      // 0x008cc5d0
void ReadSegment(InputStream* in, uint8* dest, int32 numBytes); // 0x008cc220 (card names it PeekInt16)
uint32 Tell_InputStream(InputStream* in);
void Seek_InputStream(InputStream* in, uint32 pos);
void PrimeT2KInputStream(InputStream* in);
void AllocGlyphPointMemory(GlyphClass* t, int32 pointCount);
}

#define T2K_ERR_TRANS_FAIL 10024

static __inline int ReadUnsignedByteSlow(InputStream* in)
{
    int error = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, in->pos++, 1);
    if (error < 0) {
        tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        return 0;
    }
    return in->tmp_ch[0];
}

#define ReadUnsignedByteMacro2(stream) \
    ((int)(((stream)->pos - (stream)->posZero + 1 > (stream)->cacheCount ? PrimeT2KInputStream(stream) : (void)0), \
             (stream)->privateBase[(stream)->pos++ - (stream)->posZero]))

#define ReadUnsignedByteMacro(stream) \
    ((uint8)((stream)->privateBase != 0 \
                 ? ((stream)->ReadToRamFunc != 0 ? ReadUnsignedByteMacro2(stream) \
                                                 : (stream)->privateBase[(stream)->pos++]) \
                 : ReadUnsignedByteSlow(stream)))

// composite glyph flags
#define ARG_1_AND_2_ARE_WORDS 0x0001
#define WE_HAVE_A_SCALE 0x0008
#define MORE_COMPONENTS 0x0020
#define WE_HAVE_AN_X_AND_Y_SCALE 0x0040
#define WE_HAVE_A_TWO_BY_TWO 0x0080
#define WE_HAVE_INSTRUCTIONS 0x0100

// simple glyph flags
#define ONCURVE 0x01
#define XSHORT 0x02
#define YSHORT 0x04
#define REPEAT_FLAGS 0x08
#define SHORT_X_IS_POS 0x10
#define NEXT_X_IS_ZERO 0x10
#define SHORT_Y_IS_POS 0x20
#define NEXT_Y_IS_ZERO 0x20

#define T2K_FB_HINTS 3

// @ 0x008ce020
static GlyphClass* New_GlyphClass(tsiMemObject* mem, InputStream* in, char readHints, int16 lsb, uint16 aw,
                                  int16 tsb, uint16 ah)
{
    int i, k;
    int numberOfContours;
    int pointCount;
    int16* oox;
    int16* ooy;
    GlyphClass* t = (GlyphClass*)tsi_FastAllocN(mem, sizeof(GlyphClass), 0);

    t->mem = mem;
    t->ep = 0;
    t->sp = 0;
    t->componentData = 0;
    t->x54 = 0;
    t->x50 = 0;

    numberOfContours = ReadInt16(in);
    t->contourCountMax = (int16)numberOfContours;
    t->xmin = ReadInt16(in);
    t->ymin = ReadInt16(in);
    t->xmax = ReadInt16(in);
    t->ymax = ReadInt16(in);

    pointCount = 0;
    t->componentSize = 0;
    t->hintLength = 0;
    t->hintFragment = 0;
    t->x0c = 0;
    t->x10 = 0;
    t->x34 = 2;
    t->contourCount = 0;
    t->pointCount32 = 0;

    if (numberOfContours < 0) {
        // composite glyph
        int16 flags;
        int weHaveInstructions;
        int16* componentData;
        k = 0;
        t->componentSizeMax = 1024;
        componentData = (int16*)tsi_AllocMem(t->mem, 1024 * sizeof(int16));
        do {
            if (k >= t->componentSizeMax - 10) {
                t->componentSizeMax += t->componentSizeMax / 2;
                componentData = (int16*)tsi_ReAllocMem(t->mem, componentData, t->componentSizeMax * sizeof(int16));
            }
            flags = ReadInt16(in);
            weHaveInstructions = (flags & WE_HAVE_INSTRUCTIONS) != 0;
            componentData[k++] = flags;
            componentData[k++] = ReadInt16(in); // glyphIndex
            if (flags & ARG_1_AND_2_ARE_WORDS) {
                componentData[k++] = ReadInt16(in);
                componentData[k++] = ReadInt16(in);
            } else {
                componentData[k++] = ReadInt16(in);
            }
            if (flags & WE_HAVE_A_SCALE) {
                componentData[k++] = ReadInt16(in);
            } else if (flags & WE_HAVE_AN_X_AND_Y_SCALE) {
                componentData[k++] = ReadInt16(in);
                componentData[k++] = ReadInt16(in);
            } else if (flags & WE_HAVE_A_TWO_BY_TWO) {
                componentData[k++] = ReadInt16(in);
                componentData[k++] = ReadInt16(in);
                componentData[k++] = ReadInt16(in);
                componentData[k++] = ReadInt16(in);
            }
        } while (flags & MORE_COMPONENTS);

        t->hintLength = 0;
        if (weHaveInstructions) {
            t->hintLength = ReadInt16(in);
            if (readHints) {
                if (t->hintLength > 0) {
                    t->hintFragment = (uint8*)tsi_FastAllocN(t->mem, t->hintLength, T2K_FB_HINTS);
                    ReadSegment(in, t->hintFragment, t->hintLength);
                }
            } else {
                Seek_InputStream(in, Tell_InputStream(in) + t->hintLength);
                t->hintLength = 0;
            }
        }
        AllocGlyphPointMemory(t, 0);
        oox = t->oox;
        ooy = t->ooy;
        t->componentSize = k;
        t->componentData = componentData;
    } else if (numberOfContours > 0) {
        // simple glyph
        uint8* flags;
        uint8 flag;
        uint16 val; // running end point, then the running x and y coordinate (one variable in the original)
        val = 0;
        if (numberOfContours <= 8) {
            t->sp = t->spBuffer;
            t->ep = t->sp + 8;
        } else {
            t->sp = (int16*)tsi_AllocMem(t->mem, numberOfContours * 2 * sizeof(int16));
            t->ep = t->sp + numberOfContours;
        }
        for (i = 0; i < numberOfContours; i++) {
            t->sp[i] = val;
            t->ep[i] = val = ReadInt16(in);
            val++;
        }
        pointCount = (int16)val;

        t->hintLength = ReadInt16(in);
        if (readHints) {
            if (t->hintLength > 0) {
                t->hintFragment = (uint8*)tsi_FastAllocN(t->mem, t->hintLength, T2K_FB_HINTS);
                ReadSegment(in, t->hintFragment, t->hintLength);
            }
        } else {
            Seek_InputStream(in, Tell_InputStream(in) + t->hintLength);
            t->hintLength = 0;
        }

        AllocGlyphPointMemory(t, pointCount);
        oox = t->oox;
        ooy = t->ooy;
        flags = t->onCurve;
        t->contourCount = numberOfContours;
        t->pointCount32 = (int16)pointCount;

        for (i = 0; i < pointCount;) {
            flags[i++] = flag = ReadUnsignedByteMacro(in);
            if (flag & REPEAT_FLAGS) {
                int count = ReadUnsignedByteMacro(in);
                while (count-- > 0) {
                    if (i >= pointCount) break;
                    flags[i++] = flag;
                }
            }
        }

        val = 0;
        for (i = 0; i < pointCount; i++) {
            flag = flags[i];
            if (flag & XSHORT) {
                if (flag & SHORT_X_IS_POS) {
                    val = val + ReadUnsignedByteMacro(in);
                } else {
                    val = val - ReadUnsignedByteMacro(in);
                }
            } else if (!(flag & NEXT_X_IS_ZERO)) {
                int16 stmp = (int16)(ReadUnsignedByteMacro(in) << 8);
                stmp = stmp | ReadUnsignedByteMacro(in);
                val = val + stmp;
            }
            oox[i] = val;
        }

        val = 0;
        for (i = 0; i < pointCount; i++) {
            flag = flags[i];
            flags[i] = (uint8)(flag & ONCURVE);
            if (flag & YSHORT) {
                if (flag & SHORT_Y_IS_POS) {
                    val = val + ReadUnsignedByteMacro(in);
                } else {
                    val = val - ReadUnsignedByteMacro(in);
                }
            } else if (!(flag & NEXT_Y_IS_ZERO)) {
                int16 stmp = (int16)(ReadUnsignedByteMacro(in) << 8);
                stmp = stmp | ReadUnsignedByteMacro(in);
                val = val + stmp;
            }
            ooy[i] = val;
        }
    } else {
        t->pointCount = 0;
        return t;
    }

    // phantom points: left side bearing, advance width, top side bearing, advance height
    ooy[pointCount] = 0;
    oox[pointCount] = (int16)(t->xmin - lsb);
    ooy[pointCount + 1] = 0;
    oox[pointCount + 1] = (int16)(oox[pointCount] + aw);
    {
        int mid = (oox[pointCount] + oox[pointCount + 1]) >> 1;
        ooy[pointCount + 2] = (int16)(t->ymax + tsb);
        oox[pointCount + 2] = (int16)mid;
        ooy[pointCount + 3] = (int16)(ooy[pointCount + 2] - ah);
        oox[pointCount + 3] = (int16)mid;
    }
    t->pointCount = (int16)pointCount;
    return t;
}

// ---------------------------------------------------------------------------------------------
// 0x008cec20: read one 'name' table entry out of the font file. The wanted name is selected by
// the face's platform/encoding ids plus the caller's language and name ids; an even-length entry
// is treated as UTF-16 unless its first 10 bytes contain a zero byte, the odd-length one as bytes.
// ---------------------------------------------------------------------------------------------
#define TT_TAG_name 0x6e616d65u

struct TTSfntRecord {
    uint32 tag;              // +0x00
    uint32 checksum;         // +0x04
    uint32 offset;           // +0x08
    uint32 length;           // +0x0c
};

struct TTSfntTable {
    uint32 pad00[2];         // +0x00
    uint16 numTables;        // +0x08
    uint16 pad0a;            // +0x0a
    uint32 pad0c;            // +0x0c
    TTSfntRecord* records;   // +0x10
};

struct TTFont {
    TTSfntTable* mpSfnt;     // +0x00
    uint32 pad04[(0x88 - 0x04) / 4];
    uint16 mPlatformID;      // +0x88
    uint16 mEncodingID;      // +0x8a
    uint32 pad8c[(0xdc - 0x8c) / 4];
    int32 mFileID;           // +0xdc
    uint32 padE0[(0xe8 - 0xe0) / 4];
    tsiMemObject* mpMem;     // +0xe8
};

// @ 0x008CEC20
void GetTTNameProperty(TTFont* font, int16 languageID, int16 nameID, char** outAscii, char** outUnicode)
{
    int16 platformID = (int16)font->mPlatformID;
    int16 encodingID = (int16)font->mEncodingID;
    int32 fileID = font->mFileID;
    TTSfntTable* sfnt = font->mpSfnt;
    int32 index;

    *outAscii = 0;
    *outUnicode = 0;

    int32 tableCount = sfnt->numTables;
    for (index = 0; index < tableCount; ++index) {
        if (sfnt->records[index].tag == TT_TAG_name)
            break;
    }
    if (index >= tableCount)
        return;
    TTSfntRecord* rec = &sfnt->records[index];
    if (rec == 0)
        return;

    int32 namedShort = 0;
    InputStream* in = New_InputStream2(font->mpMem, fileID, rec->offset, rec->length, 0, 0);

    ReadInt16(in);                                    // format
    int32 nameCount = (uint16)ReadInt16(in);
    uint16 stringOffset = (uint16)ReadInt16(in);

    uint32 recordPos;
    int32 r;
    for (r = 0; r < nameCount; ++r) {
        recordPos = Tell_InputStream(in);
        if (ReadInt16(in) == platformID && ReadInt16(in) == encodingID && ReadInt16(in) == languageID &&
            ReadInt16(in) == nameID)
            break;
        Seek_InputStream(in, recordPos + 0xc);
    }
    if (r == nameCount) {
        Delete_InputStream(in, 0);
        return;
    }

    uint16 nameLength = (uint16)ReadInt16(in);
    uint16 nameOffset = (uint16)ReadInt16(in);
    Seek_InputStream(in, stringOffset + nameOffset);
    uint8* buffer = (uint8*)tsi_AllocMem(font->mpMem, nameLength + 2);

    if ((nameLength & 1) == 0) {
        // even length: an entry that terminates within 10 bytes is plain text, not UTF-16
        int32 n = nameLength > 10 ? 10 : (int32)nameLength;
        while (n > 0) {
            --n;
            if (ReadUnsignedByteMacro(in) == 0) {
                namedShort = 1;
                break;
            }
        }
        Seek_InputStream(in, nameLength);
    }

    int32 len;
    if (namedShort) {
        *outUnicode = (char*)buffer;
        len = 0;
        if (nameLength > 0) {
            int32 chars = (((int32)nameLength - 1) >> 1) + 1;
            len = chars * 2;
            int16* p = (int16*)buffer;
            do {
                *p++ = ReadInt16(in);
            } while (--chars != 0);
        }
    } else {
        *outAscii = (char*)buffer;
        len = 0;
        if (nameLength > 0) {
            do {
                buffer[len] = ReadUnsignedByteMacro(in);
                ++len;
            } while (len < (int32)nameLength);
        }
    }
    buffer[len] = 0;
    buffer[len + 1] = 0;

    Delete_InputStream(in, 0);
}

// Stand-in for the only caller, GetGlyphByIndex (0x008cefe0), so cl emits New_GlyphClass with the
// same register convention (mem in ECX, stream in EAX).
extern "C" GlyphClass* s008ce020_NewGlyphCaller(tsiMemObject* mem, InputStream* in, char readHints, int16 lsb,
                                                uint16 aw, int16 tsb, uint16 ah)
{
    return New_GlyphClass(mem, in, readHints, lsb, aw, tsb, ah);
}
