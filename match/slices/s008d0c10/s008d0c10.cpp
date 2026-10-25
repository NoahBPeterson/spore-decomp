// slice s008d0c10 -- TSI font-engine memory handler + utility math.
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// Retail (dev-PDB) layouts of the TSI font objects.

struct tsiMemObject;
struct sfntClass;
struct T1Class;
struct CFFClass;
struct PFRClass;
struct kernSubTable;
struct hashEntry;

struct tsiMemHeader {          // 16-byte header in front of every user block
    unsigned long stamp1;      // +0x00  0xaa53c5aa
    unsigned long size;        // +0x04  user byte count
    long index;                // +0x08  slot in tsiMemObject::base
    unsigned long pad_0c;      // +0x0c
    unsigned char data[1];     // +0x10  user bytes, then 'Z', 0xf0 guard
};

struct tsiMemObject {          // size 0xb0
    unsigned long stamp1;      // +0x00
    long numPointers;          // +0x04
    long maxPointers;          // +0x08
    void** base;               // +0x0c
    int env[16];               // +0x10  setjmp buffer
    void* fast_base[7];        // +0x50
    unsigned long fast_size[7];// +0x6c
    int fast_free[7];          // +0x88
    unsigned long ii;          // +0xa4
    unsigned long state;       // +0xa8
    unsigned long stamp2;      // +0xac
};

struct hashEntry {             // size 0x4
    unsigned short key;        // +0x0
    unsigned short value;      // +0x2
};

struct hashClass {             // size 0x30
    tsiMemObject* mem;         // +0x00
    long x;                    // +0x04
    long numItems;             // +0x08
    long maxItems;             // +0x0c
    long enum_x;               // +0x10
    long m;                    // +0x14
    void* stringsAreEqual;     // +0x18
    void* privPtr;             // +0x1c
    hashEntry* hash;           // +0x20
    hashEntry* UE_hash;        // +0x24
    long first_UE_code;        // +0x28
    long num_UE_codes;         // +0x2c
};

struct CFF_Class {             // size 0x8
    unsigned long offset;      // +0x0
    unsigned long length;      // +0x4
};

struct DSIGClass {             // size 0x8
    unsigned long offset;      // +0x0
    unsigned long length;      // +0x4
};

struct kernSubTable {          // size 0x14
    tsiMemObject* mem;         // +0x00
    unsigned short version;    // +0x04
    long length;               // +0x08
    unsigned short coverage;   // +0x0c
    void* kernData;            // +0x10
};

struct kernData_t {            // kernData points at a format-0 header
    unsigned short field_0;    // +0x0
    unsigned short field_4;    // +0x4
};

struct kernClass {             // size 0x10
    tsiMemObject* mem;         // +0x00
    unsigned short version;    // +0x04
    long nTables;              // +0x08
    kernSubTable** table;      // +0x0c
};

struct headClass {             // size 0x3c
    tsiMemObject* mem;         // +0x00
    long version;              // +0x04
    long fontRevision;         // +0x08
    unsigned long checkSumAdjustment; // +0x0c
    unsigned long magicNumber; // +0x10
    unsigned short flags;      // +0x14
    unsigned short unitsPerEm; // +0x16
    long created_bc;           // +0x18
    long created_ad;           // +0x1c
    long modified_bc;          // +0x20
    long modified_ad;          // +0x24
    short xMin;                // +0x28
    short yMin;                // +0x2a
    short xMax;                // +0x2c
    short yMax;                // +0x2e
    unsigned short macStyle;   // +0x30
    unsigned short lowestRecPPEM; // +0x32
    short fontDirectionHint;   // +0x34
    short indexToLocFormat;    // +0x36
    short glyphDataFormat;     // +0x38
};

struct T1Class {               // size 0x224
    tsiMemObject* mem;         // +0x000
    unsigned char* dataInPtr;  // +0x004
    unsigned char* decryptedData; // +0x008
    long dataLen;              // +0x00c
    long eexecGO;              // +0x010
    long charstringsGO;        // +0x014
    long x;                    // +0x018
    long y;                    // +0x01c
    long flexOn;               // +0x020
    long flexCount;            // +0x024
    short lenIV;               // +0x028
    unsigned char* encoding;   // +0x02c
    short NumCharStrings;      // +0x030
    unsigned short* charCode;  // +0x034
    unsigned short* adobeCode; // +0x038
    unsigned char** charData;  // +0x03c
    short numSubrs;            // +0x040
    unsigned char** subrsData; // +0x044
    short gNumStackValues;     // +0x048
    long gStackValues[32];     // +0x04c
    unsigned char pad_0cc[0x210 - 0x0cc];
    long m11;                  // +0x210
    unsigned long isFixedPitch;// +0x214
    unsigned short firstCharCode; // +0x218
    unsigned short lastCharCode;  // +0x21a
};

struct CFFClass {              // size 0x520
    tsiMemObject* mem;         // +0x000
    void* in;                  // +0x004
    unsigned long cffOffset;   // +0x008
    long NumCharStrings;       // +0x00c
    unsigned short charCodeToSID[256]; // +0x010
    void* T2_CMAPTable;        // +0x210
    void* T2_StringsHash;      // +0x214
    void* T2_SIDToCharCodeHash;// +0x218
    long upem;                 // +0x21c
    unsigned char pad_220[0x510 - 0x220];
    long lSubrBias;            // +0x510
    unsigned long isFixedPitch;// +0x514
    unsigned short firstCharCode; // +0x518
    unsigned short lastCharCode;  // +0x51a
};

struct PFRClass {              // size 0x1f0
    tsiMemObject* mem;         // +0x000
    void* in;                  // +0x004
    unsigned char pfrType;     // +0x008
    void* charMap;             // +0x00c
    unsigned long directoryCount; // +0x010
    unsigned short fontNumber; // +0x014
    unsigned short physFontNumber; // +0x016
    unsigned short outlineRes; // +0x018
    unsigned short metricsRes; // +0x01a
    char verticalEscapement;   // +0x01c
    unsigned char pad_01d[3];  // +0x01d
    unsigned char* pAuxData;   // +0x020
    long nAuxBytes;            // +0x024
    long xyScale;              // +0x028
    long firstGpsOffset;       // +0x02c
    long totalGpsSize;         // +0x030
    unsigned char contourOpen; // +0x034
    unsigned char shortScaleFactors; // +0x035
    unsigned char bmapFlags;   // +0x036
    unsigned char pad_037;     // +0x037
    unsigned short nBmapStrikes; // +0x038
    unsigned char pad_03a[2];  // +0x03a
    void* bmapStrikes;         // +0x03c
    unsigned char pad_040[0x100 - 0x040];
    struct hmtxClass* hmtx;    // +0x100
    struct hmtxClass* noDelete_hmtx; // +0x104
    short NumCharStrings;      // +0x108
    long upem;                 // +0x10c
    unsigned char pad_110[0x128 - 0x110];
    kernClass* kern;           // +0x128
    unsigned char pad_12c[0x1e4 - 0x12c];
    unsigned long isFixedPitch;// +0x1e4
    unsigned short firstCharCode; // +0x1e8
    unsigned short lastCharCode;  // +0x1ea
    int glyphExists;           // +0x1ec
};

struct hmtxClass {             // size 0x14
    tsiMemObject* mem;         // +0x00
    long numGlyphs;            // +0x04
    long numberOfHMetrics;     // +0x08
    short* lsb;                // +0x0c
    unsigned short* aw;        // +0x10
};

struct FFT1HintClass;          // opaque here

struct sfntClass {             // size 0xf8
    void* offsetTable0;        // +0x00
    void* GetAWFuncPtr1;       // +0x04
    void* GetAWParam1;         // +0x08
    void* GetAWFuncPtr2;       // +0x0c
    void* GetAWParam2;         // +0x10
    unsigned short* awCache_hashKey; // +0x14
    unsigned short* awCache_aw;// +0x18
    unsigned short upem;       // +0x1c
    T1Class* T1;               // +0x20
    CFFClass* T2;              // +0x24
    PFRClass* PFR;             // +0x28
    void* sloc;                // +0x2c
    void* ffst;                // +0x30
    void* ffhm;                // +0x34
    void* bloc;                // +0x38
    void* ebsc;                // +0x3c
    unsigned long bdatOffset;  // +0x40
    void* t2kTT;               // +0x44
    FFT1HintClass* ffhint;     // +0x48
    void* ttcf;                // +0x4c
    headClass* head;           // +0x50
    void* maxp;                // +0x54
    void* loca;                // +0x58
    void* gasp;                // +0x5c
    void* hhea;                // +0x60
    void* vhea;                // +0x64
    hmtxClass* hmtx;           // +0x68
    hmtxClass* vmtx;           // +0x6c
    void* cmap;                // +0x70
    kernClass* kern;           // +0x74
    CFF_Class CFF;             // +0x78
    DSIGClass DSIG;            // +0x80
    unsigned short preferedPlatformID; // +0x88
    unsigned short preferedPlatformSpecificID; // +0x8a
    short post_underlinePosition;    // +0x8c
    short post_underlineThickness;   // +0x8e
    unsigned long isFixedPitch;// +0x90
    unsigned short firstCharCode; // +0x94
    unsigned short lastCharCode;  // +0x96
    unsigned short hintsAvailable;// +0x98
    long xPPEm;                // +0x9c
    long yPPEm;                // +0xa0
    void* globalHintsCache;    // +0xa4
    void* StyleFunc;           // +0xa8
    void* StyleMetricsFunc;    // +0xac
    long params[4];            // +0xb0
    long xScale;               // +0xc0
    long yScale;               // +0xc4
    int useNativeHints;        // +0xc8
    int strokeGlyph;           // +0xcc
    int greyScaleLevel;        // +0xd0
    long currentCoordinate[2]; // +0xd4
    void* in;                  // +0xdc
    void* in2;                 // +0xe0
    void* out;                 // +0xe4
    tsiMemObject* mem;         // +0xe8
    void* model;               // +0xec
    long numGlyphs;            // +0xf0
    long numberOfLogicalFonts; // +0xf4
};

// ---------------------------------------------------------------------------
// FreeType-style allocator hooks exported elsewhere.
void* ff_malloc(unsigned size);              // 0x008a7760  ?ff_malloc@@YAPAXI@Z
void  ff_free(void* p);                      // 0x008a7770  ?ff_free@@YAXPAX@Z
void* ff_realloc(void* p, unsigned size);    // 0x008a7780  ?ff_realloc@@YAPAXPAXI@Z

extern "C" __declspec(dllimport) __declspec(noreturn)
void __cdecl longjmp(void* env, int val);    // __imp_longjmp
extern "C" int _setjmp(int* env);            // 0x011e0cac (cl intrinsic -> _setjmp3(env, 0))

// ---- externals referenced by the sfnt class constructor ----------------
extern "C" int   FF_SetStyleCallbacks(sfntClass* self, void* style);   // 0x008cf330
extern "C" int   CacheKeyTables_sfntClass(void* in, void* stream);     // 0x008cffd0
extern "C" int   FUN_008cc2a0(int stream);                             // 0x008cc2a0
extern "C" void* tsi_NewT1Class(int mem, int stream, int size);        // 0x008b9e10
FFT1HintClass*   New_FFT1HintClass(tsiMemObject* mem, short upem);     // 0x008a7930
extern "C" void* GetEntireStreamIntoMemory(int stream, int size);      // 0x008cc2c0
extern "C" void* New_T1kernSubTable(T1Class* t1, int mem, void* buf);  // 0x008b9d90
extern "C" void  Delete_kernClass(kernClass* kern);                    // 0x008cd790
extern "C" void* tsi_NewPFRClass(int mem, int stream, int size);       // 0x008b5190
extern "C" void* FUN_008bf290(int mem, void* in, int stream);          // 0x008bf290
extern "C" void* FUN_008bf270(int mem, void* in, int stream, int off); // 0x008bf270
extern "C" int   GetUPEM(sfntClass* self, int* out = 0);               // 0x008ceb70
extern "C" int   FUN_008cef90(sfntClass* self);                        // 0x008cef90
extern "C" void  FUN_008b8c80();                                       // 0x008b8c80
extern "C" void  FUN_008be220();                                       // 0x008be220
extern "C" void  Get_Cached_AW();                                      // 0x008cf3b0
extern "C" void  FUN_008cf390();                                       // 0x008cf390
extern "C" void  FUN_008cf450();                                       // 0x008cf450
extern "C" void  FUN_008cb790();                                       // 0x008cb790

// Fast-memory-block helpers (defined below, used by the ctor).
extern "C" void* tsi_AllocMem(int tbl, int size);
extern "C" void  tsi_DeAllocMem(int tbl, char* p);
extern "C" void  tsi_EmergencyShutDown(int tbl);

int __fastcall FUN_008d1960(unsigned n);

// ---------------------------------------------------------------------------
// @ 0x008d0c10
void* FF_New_sfntClass(int param_1, short params, int param_3, int param_4,
                       int param_5, int param_6, int* out_err)
{
    sfntClass* o;
    hmtxClass* hmtx;
    int i2;
    if (out_err == 0)
        goto fail;

    i2 = _setjmp((int*)((char*)param_1 + 0x10));
    *out_err = i2;
    if (i2 != 0)
        goto fail;

    o = (sfntClass*)tsi_AllocMem(param_1, 0xf8);
    o->in = (void*)param_4;
    o->mem = (tsiMemObject*)param_1;
    o->in2 = (void*)param_5;
    o->out = 0;
    o->GetAWFuncPtr1 = 0;
    o->GetAWParam1 = 0;
    o->GetAWFuncPtr2 = 0;
    o->GetAWParam2 = 0;
    o->awCache_hashKey = 0;
    o->awCache_aw = 0;
    o->numberOfLogicalFonts = 1;
    o->offsetTable0 = 0;
    o->head = 0;
    o->hhea = 0;
    o->vhea = 0;
    o->hmtx = 0;
    o->vmtx = 0;
    o->maxp = 0;
    o->loca = 0;
    o->sloc = 0;
    o->ffst = 0;
    o->ffhm = 0;
    o->cmap = 0;
    o->kern = 0;
    o->gasp = 0;
    o->model = 0;
    o->bloc = 0;
    o->ebsc = 0;
    o->upem = 0;
    FF_SetStyleCallbacks(o, (void*)param_6);
    o->xPPEm = -1;
    o->yPPEm = -1;
    o->hintsAvailable = 0;
    o->globalHintsCache = 0;
    o->T1 = 0;
    o->T2 = 0;
    o->PFR = 0;
    o->t2kTT = 0;
    o->ffhint = 0;
    o->ttcf = 0;
    o->xScale = 0;
    o->yScale = 0;
    o->useNativeHints = 0;
    o->CFF.offset = 0;
    o->CFF.length = 0;
    o->DSIG.offset = 0;
    o->DSIG.length = 0;

    if (params == 7) {
        if (CacheKeyTables_sfntClass(o->in, (void*)param_3) == 0) {
            *out_err = 0x2729;
            return 0;
        }
    }

    if (params == 2 || params == 5 || (params == 7 && o->CFF.length == 0)) {
        if (params != 7 && CacheKeyTables_sfntClass(o->in, (void*)param_3) == 0) {
            *out_err = 0x2729;
            return 0;
        }
    } else if (params == 1) {
        int u4 = FUN_008cc2a0(param_3);
        o->T1 = (T1Class*)tsi_NewT1Class(param_1, param_3, u4);
        if (o->T1 == 0)
            goto dealloc;
        o->ffhint = New_FFT1HintClass((tsiMemObject*)param_1, (short)GetUPEM(o));
        if (param_5 != 0) {
            int u5 = FUN_008cc2a0(param_5);
            void* buf = GetEntireStreamIntoMemory(param_5, u5);
            o->kern = (kernClass*)New_T1kernSubTable(o->T1, param_1, buf);
            if (((kernData_t*)o->kern->table[0]->kernData)->field_4 == 0) {
                Delete_kernClass(o->kern);
                o->kern = 0;
            }
        }
        o->GetAWFuncPtr2 = (void*)&FUN_008b8c80;
        o->GetAWParam2 = o->T1;
        if (o->StyleMetricsFunc != 0) {
            int upem = GetUPEM(o, (int*)&o->params[0]);
            ((void (__cdecl*)(void*, void*, int))o->StyleMetricsFunc)(
                o->hmtx, o->mem, upem);
        }
        o->isFixedPitch = o->T1->isFixedPitch;
        o->firstCharCode = o->T1->firstCharCode;
        o->lastCharCode = o->T1->lastCharCode;
    } else if (params == 0x16 || (params == 7 && o->CFF.offset != 0)) {
        void* r;
        if (o->CFF.offset == 0)
            r = FUN_008bf290(param_1, o->in, param_3);
        else
            r = FUN_008bf270(param_1, o->in, param_3, (int)o->CFF.offset);
        o->T2 = (CFFClass*)r;
        o->GetAWFuncPtr2 = (void*)&FUN_008be220;
        o->GetAWParam2 = r;
        if (o->StyleMetricsFunc != 0) {
            int upem = GetUPEM(o, (int*)&o->params[0]);
            ((void (__cdecl*)(void*, void*, int))o->StyleMetricsFunc)(
                o->hmtx, o->mem, upem);
        }
        o->isFixedPitch = o->T2->isFixedPitch;
        o->firstCharCode = o->T2->firstCharCode;
        o->lastCharCode = o->T2->lastCharCode;
    } else {
        if (params != 3)
            goto dealloc;
        o->PFR = (PFRClass*)tsi_NewPFRClass(param_1, param_3, param_4);
        o->kern = o->PFR->kern;
        o->hmtx = o->PFR->hmtx;
        o->PFR->hmtx = 0;
        o->numberOfLogicalFonts = o->PFR->directoryCount;
        o->firstCharCode = o->PFR->firstCharCode;
        o->lastCharCode = o->PFR->lastCharCode;
        o->isFixedPitch = o->PFR->isFixedPitch;
        if (o->StyleMetricsFunc != 0) {
            int upem = GetUPEM(o, (int*)&o->params[0]);
            ((void (__cdecl*)(void*, void*, int))o->StyleMetricsFunc)(
                o->hmtx, o->mem, upem);
        }
        if (o->ffhint == 0)
            o->ffhint = New_FFT1HintClass((tsiMemObject*)param_1, (short)GetUPEM(o));
    }

    hmtx = o->hmtx;
    if (hmtx == 0) {
        o->GetAWFuncPtr1 = (void*)&Get_Cached_AW;
        o->GetAWParam1 = o;
    } else {
        o->GetAWFuncPtr1 = (void*)&FUN_008cf390;
        o->GetAWParam1 = hmtx;
    }

    o->numGlyphs = FUN_008cef90(o);
    if (o->head != 0 && o->head->glyphDataFormat == 0x7d2) {
        if (o->ffhm != 0) {
            o->GetAWFuncPtr2 = (void*)&FUN_008cb790;
            o->GetAWParam2 = o->ffhm;
        } else if (o->GetAWFuncPtr2 == 0 && hmtx != 0) {
            o->GetAWFuncPtr1 = (void*)&FUN_008cf450;
            o->GetAWParam1 = o;
        }
    }
    o->currentCoordinate[0] = 0x8000;
    o->currentCoordinate[1] = 0x8000;
    return o;

dealloc:
    tsi_DeAllocMem(param_1, (char*)o);
    *out_err = 0x2729;
    return 0;

fail:
    tsi_EmergencyShutDown(param_1);
    return 0;
}

// @ 0x008d10c0
void tsi_Error(int param_1, int param_2)
{
    tsiMemObject* mem = (tsiMemObject*)param_1;
    if (mem != 0) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, param_2);
    }
}

// @ 0x008d10f0
void* tsi_NewCustomSizeMemhandler(int* out_err, int count)
{
    tsiMemObject* m;
    int i;
    *out_err = 0;
    m = (tsiMemObject*)ff_malloc(0xb0);
    if (m == 0)
        goto err;
    m->maxPointers = count;
    m->stamp1 = 0xab1500ff;
    m->state = 0xaa005501;
    m->stamp2 = 0xa5a55a5a;
    m->numPointers = 0;
    m->ii = 0;
    m->base = (void**)ff_malloc(count * 4);
    if (m->base != 0) {
        i = 0;
        if (m->maxPointers > 0) {
            do {
                m->base[i] = 0;
                ++i;
            } while (i < m->maxPointers);
        }
        m->fast_base[0] = 0;
        m->fast_size[0] = 0;
        m->fast_base[1] = 0;
        m->fast_size[1] = 0;
        m->fast_base[2] = 0;
        m->fast_size[2] = 0;
        m->fast_base[3] = 0;
        m->fast_size[3] = 0;
        m->fast_base[4] = 0;
        m->fast_size[4] = 0;
        m->fast_base[5] = 0;
        m->fast_size[5] = 0;
        m->fast_base[6] = 0;
        m->fast_size[6] = 0;
        m->fast_free[0] = 1;
        m->fast_free[1] = 1;
        m->fast_free[2] = 1;
        m->fast_free[3] = 1;
        m->fast_free[4] = 1;
        m->fast_free[5] = 1;
        m->fast_free[6] = 1;
        return m;
    }
    ff_free(m);
err:
    *out_err = 0x2718;
    return 0;
}

// @ 0x008d1210
void tsi_EmergencyShutDown(int param_1)
{
    int i;
    int n;
    int* tbl;
    if (param_1 == 0)
        return;
    n = *(int*)(param_1 + 8);
    tbl = *(int**)(param_1 + 0xc);
    i = 0;
    if (n > 0) {
        do {
            int p = tbl[i];
            if (p != 0)
                ff_free((void*)p);
            ++i;
        } while (i < n);
    }
    ff_free(tbl);
    ff_free((void*)param_1);
}

// @ 0x008d1260
void* tsi_AllocMem(int param_1, int param_2)
{
    tsiMemObject* mem = (tsiMemObject*)param_1;
    tsiMemHeader* h;
    long n;
    unsigned long slot;
    int cnt;
    h = (tsiMemHeader*)ff_malloc(param_2 + 0x12);
    if (h == 0 && mem != 0) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x2718);
    }
    h->stamp1 = 0xaa53c5aa;
    h->size = param_2;
    h->data[param_2] = 0x5a;
    h->data[param_2 + 1] = 0xf0;
    n = mem->maxPointers;
    if (mem->numPointers >= n) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x271c);
    }
    slot = mem->ii;
    cnt = 0;
    {
    void** base = mem->base;
    if (n > 0) {
        do {
            if (base[slot] == 0) {
                base[slot] = h;
                h->index = (long)slot;
                ++mem->numPointers;
                break;
            }
            ++cnt;
            slot = (slot + 1) % n;
        } while (cnt < n);
    }
    }
    mem->ii = slot;
    if (cnt >= n) {
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x2721);
    }
    return h->data;
}

// @ 0x008d1330
void* tsi_ReAllocMem(int param_1, char* param_2, int param_3)
{
    if (param_2 != 0) {
        tsiMemObject* mem = (tsiMemObject*)param_1;
        tsiMemHeader* base = (tsiMemHeader*)(param_2 - 0x10);
        tsiMemHeader* np;
        void** tbl;
        long nPtr;
        long slot;
        if (base->stamp1 != 0xaa53c5aa && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != 0x5a && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        if (base->data[sz + 1] != 0xf0 && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        nPtr = mem->numPointers;
        tbl = mem->base;
        if (nPtr <= 0)
            goto badptr;
        if (nPtr > mem->maxPointers)
            goto badptr;
        goto ptr_ok;
    badptr:
        mem->state = 0x5500aaff;
        longjmp(mem->env, 0x271d);
    ptr_ok:
        slot = base->index;
        np = (tsiMemHeader*)ff_realloc(base, param_3 + 0x12);
        tbl[slot] = np;
        if (np == 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271e);
        }
        if (np->stamp1 != 0xaa53c5aa) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        np->size = param_3;
        np->data[param_3] = 0x5a;
        np->data[param_3 + 1] = 0xf0;
        if (slot >= mem->maxPointers) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271f);
        }
        return np->data;
    }
    return 0;
}

// @ 0x008d1440
void tsi_DeAllocMem(int param_1, char* param_2)
{
    if (param_2 != 0) {
        tsiMemObject* mem = (tsiMemObject*)param_1;
        tsiMemHeader* base = (tsiMemHeader*)(param_2 - 0x10);
        long slot;
        void** tbl;
        if (base->stamp1 != 0xaa53c5aa && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        unsigned long sz = base->size;
        if (base->data[sz] != 0x5a && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        if (base->data[sz + 1] != 0xf0 && mem != 0) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x2719);
        }
        tbl = mem->base;
        slot = base->index;
        if (tbl[slot] != (void*)base) {
            mem->state = 0x5500aaff;
            longjmp(mem->env, 0x271f);
        }
        tbl[slot] = 0;
        --mem->numPointers;
        ff_free(base);
    }
}

// @ 0x008d14d0
void* tsi_FastAllocN(int param_1, unsigned param_2, int param_3)
{
    if (*(int*)(param_1 + 0x88 + param_3 * 4) != 0) {
        *(int*)(param_1 + 0x88 + param_3 * 4) = 0;
        if (param_2 > *(unsigned*)(param_1 + 0x6c + param_3 * 4)) {
            tsi_DeAllocMem(param_1, *(char**)(param_1 + 0x50 + param_3 * 4));
            *(void**)(param_1 + 0x50 + param_3 * 4) = tsi_AllocMem(param_1, param_2);
            *(unsigned*)(param_1 + 0x6c + param_3 * 4) = param_2;
        }
        return *(void**)(param_1 + 0x50 + param_3 * 4);
    }
    return tsi_AllocMem(param_1, param_2);
}

// @ 0x008d1530
void tsi_FreeFastMemBlocks(int param_1)
{
    int* p = (int*)(param_1 + 0x50);
    int n = 7;
    do {
        tsi_DeAllocMem(param_1, (char*)p[0]);
        p[0] = 0;
        p[7] = 0;
        p[0xe] = 1;
        ++p;
        --n;
    } while (n != 0);
}

// @ 0x008d1570
void tsi_DeleteMemhandler(int param_1)
{
    tsi_FreeFastMemBlocks(param_1);
    ff_free(*(void**)(param_1 + 0xc));
    ff_free((void*)param_1);
}

// @ 0x008d1590
int util_FixMul(int param_1, int param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = -param_2;
calc:
    {
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        unsigned hi2 = (param_2 >> 0x10) & 0xffff;
        unsigned lo1 = param_1 & 0xffff;
        unsigned lo2 = param_2 & 0xffff;
        return (int)(((lo1 * lo2) >> 0x10) + lo2 * hi1 + lo1 * hi2 + hi1 * hi2 * 0x10000) * sign;
    }
}

// @ 0x008d1600
int util_FixMulDiv(int param_1, int param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = -param_2;
calc:
    {
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        unsigned hi2 = (param_2 >> 0x10) & 0xffff;
        unsigned lo1 = (unsigned)param_1 & 0xffff;
        unsigned lo2 = (unsigned)param_2 & 0xffff;
        return (int)(((hi1 * 0x10000 + lo1) * hi2 + lo2 * hi1) * 0x400
                     + ((lo2 * lo1) >> 6)) * sign;
    }
}

// @ 0x008d1670
int util_ShortFracMul(int param_1, short param_2)
{
    int sign;
    if (param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if (param_2 >= 0)
            goto calc;
        sign = 1;
    } else {
        sign = 1;
        if (param_2 >= 0)
            goto calc;
        sign = -1;
    }
    param_2 = (short)-param_2;
calc:
    {
        unsigned u = (unsigned short)param_2;
        unsigned hi1 = (param_1 >> 0x10) & 0xffff;
        return (int)((((param_1 & 0xffff) * u + 0x2000) >> 0xe) + hi1 * u * 4) * sign;
    }
}

// @ 0x008d16d0
int util_FixDiv(unsigned param_1, unsigned param_2)
{
    unsigned q;
    unsigned rem;
    int sign;
    if ((int)param_1 < 0) {
        param_1 = -param_1;
        sign = -1;
        if ((int)param_2 >= 0)
            goto div;
        sign = 1;
    } else {
        sign = 1;
        if ((int)param_2 >= 0)
            goto div;
        sign = -1;
    }
    param_2 = -param_2;
div:
    q = param_1 / param_2;
    rem = param_1 % param_2;
    q = q * 0x10000;
    while (rem > 0xffff) {
        rem >>= 1;
        param_2 = (unsigned)((int)param_2 >> 1);
    }
    return (int)((rem << 0x10) / param_2 + q) * sign;
}

// @ 0x008d1730
int util_FixSin(int param_1)
{
    int d;
    int i1;
    int i3;
    if (param_1 > 0x5a0000)
        param_1 = 0x5a0000;
    else if (param_1 < 0)
        param_1 = 0;
    d = param_1 / 0x5a - 0x8000;
    i1 = (d * d) >> 0xf;
    i3 = (i1 * d) >> 0xf;
    {
        int r = ((((i1 * i1) >> 0xf) * 0x2c7) >> 0xf)
              + ((((i3 * i1) >> 0xf) * 0x72) >> 0xf)
              + ((d * 0x4716) >> 0xe)
              + ((i1 * -0x37cc) >> 0xf)
              + 0xb507
              + ((i3 * -0xe9e) >> 0xf);
        if (r > 0x10000)
            r = 0x10000;
        return r;
    }
}

// @ 0x008d17d0
int util_EuclidianDistance(int param_1, int param_2)
{
    int x, y, t;
    if (param_1 < 0)
        param_1 = -param_1;
    if (param_2 < 0)
        param_2 = -param_2;
    if (param_1 == 0)
        return param_2;
    if (param_2 == 0)
        return param_1;
    if (param_1 > param_2)
        t = (param_2 >> 1) + param_1;
    else
        t = (param_1 >> 1) + param_2;
    {
        int u, v;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        t = (v + 1 + u + t) >> 1;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        t = (v + 1 + u + t) >> 1;
        u = util_FixMul(param_1, util_FixDiv(param_1, t));
        v = util_FixMul(param_2, util_FixDiv(param_2, t));
        return (v + 1 + u + t) >> 1;
    }
}

// @ 0x008d1890
void util_ComputeIntersection(short p1, short p2, short p3, short p4,
                              short p5, short p6, short p7, short p8,
                              short* o1, short* o2)
{
    int dx, dy;
    int num, den;
    dx = p3 - p1;
    dy = p4 - p2;
    den = (p7 - p5) * dy - (p8 - p6) * dx;
    if (den != 0) {
        int num2 = (p6 - p2) * dx - (p5 - p1) * dy;
        int u = util_FixDiv((unsigned)num2, (unsigned)den);
        *o1 = (short)(util_FixMul(p7 - p5, u) + p5);
        *o2 = (short)(util_FixMul(p8 - p6, u) + p6);
        return;
    }
    {
        int a = p3 + p5;
        *o1 = (short)((a - (a >> 31)) >> 1);
        a = p4 + p6;
        *o2 = (short)((a - (a >> 31)) >> 1);
    }
}

// @ 0x008d1960
int __fastcall FUN_008d1960(unsigned param_1)
{
    if ((param_1 & 1) == 0)
        return 0;
    if ((int)param_1 % 3 == 0)
        return 0;
    if ((int)param_1 % 5 == 0)
        return 0;
    if ((int)param_1 % 7 == 0)
        return 0;
    if ((int)param_1 > 0xb) {
        if ((int)param_1 % 0xb == 0)
            return 0;
        if ((int)param_1 > 0xd) {
            if ((int)param_1 % 0xd == 0)
                return 0;
        }
    }
    return 1;
}

// @ 0x008d1a00
int* New_hashClass(int param_1, int param_2, int param_3, int param_4)
{
    hashClass* h;
    int size;
    int i;
    h = (hashClass*)tsi_AllocMem(param_1, 0x30);
    h->maxItems = param_2;
    h->stringsAreEqual = (void*)param_3;
    h->privPtr = (void*)param_4;
    size = ((param_2 * 2 + 3) / 3 + 2 + param_2) >> 1;
    size = size * 2 + 3;
    h->mem = (tsiMemObject*)param_1;
    h->numItems = 0;
    h->enum_x = 0;
    h->UE_hash = 0;
    h->first_UE_code = 0x100;
    h->num_UE_codes = 0;
    i = FUN_008d1960((unsigned)size);
    while (i == 0) {
        size += 2;
        i = FUN_008d1960((unsigned)size);
    }
    h->m = size;
    h->hash = (hashEntry*)tsi_AllocMem(param_1, size * 4);
    i = 0;
    if (size > 0) {
        do {
            h->hash[i].key = 0xffff;
            h->hash[i].value = 0xffff;
            ++i;
        } while (i < size);
    }
    return (int*)h;
}

// @ 0x008d1ac0
int get_using_uint16_hashClass(int param_1, unsigned short param_2, unsigned short* out)
{
    int* tbl = *(int**)(param_1 + 0x20);
    int mod = *(int*)(param_1 + 0x14);
    unsigned idx = param_2;
    int slot;
    for (;;) {
        slot = (int)idx % mod;
        unsigned short v = *(unsigned short*)((char*)tbl + slot * 4);
        if (v == 0xffff && *(short*)((char*)tbl + slot * 4 + 2) == (short)0xffff)
            break;
        if (v == param_2) {
            *(int*)(param_1 + 4) = slot;
            *out = *(unsigned short*)((char*)tbl + slot * 4 + 2);
            return 1;
        }
        idx = slot + 1;
    }
    *(int*)(param_1 + 4) = slot;
    *out = 0xffff;
    return 0;
}
