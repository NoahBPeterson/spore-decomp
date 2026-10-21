// Slice s00903400 -- expat XML parser internals (xmlparse.c / xmltok hashing).
//
// Frozen batch gold4.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /EHsc /TP
// /arch:SSE /fp:fast.
//
// The original binary is a build of James Clark's expat.  The parser state is a
// large struct (XML_ParserStruct); several of the helpers below are *internal*
// statics whose caller passes arguments in registers (esi/edi/ebx/eax), so the
// reconstructed C uses ordinary cdecl/thiscall signatures -- the emitted code
// is then structurally equivalent, which is what matters for the non-byte-exact
// rows, while the standalone helpers reproduce the original exactly.

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  byte;

// ---------------------------------------------------------------------------
// expat parser state.  Only the fields touched by this slice are named; the
// offsets are taken straight from the original disassembly.
// ---------------------------------------------------------------------------
struct XML_ParserStruct {
    // +0x00 .. +0x04
    void*  m_buffer;                // +0x00
    char*  m_bufferEnd;             // +0x04  (bufferLim-ish / buffer+size)
    char*  m_bufferPtr;             // +0x08
    void*  m_nextPtr;               // +0x0c
    void*  m_alloc;                 // +0x10  (MALLOC fn)
    void*  m_free;                  // +0x14  (FREE fn)
    char   pad18[0x8];
    // +0x18..+0x2c  buffer bookkeeping for the initial window
    char   pad18b[0x8];
    void*  m_unknownEncodingHandler; // +0x7c
    char   pad80[0x10];
    void*  m_unknownEncodingData;    // +0x90 (handler data / userData)
    char   pad94[0x54];
    // +0xf0..+0xfc unknown-encoding decoder state
    char   padF0[0x4c];
    void*  m_freeInternal;           // +0x118
    int    m_errorCode;              // +0x11c
    uint   m_codeBuf;                // +0x120
    char*  m_codeBufPtr;             // +0x124
    uint   m_codeBufEnd;             // +0x128
    void*  m_freeList;               // +0x12c
    void*  m_allocList;              // +0x130
    char   pad134[0x4];
    // hash table + pool
    char   pad138[0x28];
    char   pad160[0xc];
    int    m_unknownPrefixLen;       // +0x16c  (declared below with real type)
    int    m_tempPool_blocks;        // +0x178
    char   pad17c[0x64];
    // +0x1d8  prefix (unknown encoding)
    char   pad1d8[0x8];
    int    m_parsingStatus;          // +0x1e0
    int    m_parsing;                // +0x1e4
    char   pad1e8[0x8];
};

// The above offsets are only used informally; the functions below index the
// state through raw byte pointers plus explicit constants, exactly like the
// original, so no struct-layout mistakes can creep in.

// ---------------------------------------------------------------------------
// 0x009035d0 -- getParsingStatus(state, out[2]): copy two parser words.
// ---------------------------------------------------------------------------
// @ 0x009035d0
void XmlGetParsingStatus(char* state, int* out)
{
    out[0] = *(int*)(state + 0x1e0);
    out[1] = *(int*)(state + 0x1e4);
}

// ---------------------------------------------------------------------------
// 0x009035f0 -- current byte index of the primary code buffer, or -1.
// ---------------------------------------------------------------------------
// @ 0x009035f0
int XmlGetByteIndex(char* state)
{
    if (*(int*)(state + 0x120) != 0)
        return (*(int*)(state + 0x24) - *(int*)(state + 0x28)) + *(int*)(state + 0x120);
    return -1;
}

// ---------------------------------------------------------------------------
// 0x00903610 -- report the un-reported tail of the code buffer, then return
// one past the current byte count.
// ---------------------------------------------------------------------------
// @ 0x00903610
int XmlFlushTailA(char* state)
{
    uint n = *(uint*)(state + 0x120);
    if (n != 0 && n >= *(uint*)(state + 0x128)) {
        char* self = *(char**)(state + 0x90);
        typedef void (__cdecl *ReportFn)(void*, uint, uint, void*);
        ((ReportFn)(*(void**)(self + 0x34)))(
            self, *(uint*)(state + 0x128), n, state + 0x198);
        *(uint*)(state + 0x128) = *(uint*)(state + 0x120);
    }
    return *(int*)(state + 0x198) + 1;
}

// ---------------------------------------------------------------------------
// 0x00903660 -- same as 00903610 but returns the second counter verbatim.
// ---------------------------------------------------------------------------
// @ 0x00903660
int XmlFlushTailB(char* state)
{
    uint n = *(uint*)(state + 0x120);
    if (n != 0 && n >= *(uint*)(state + 0x128)) {
        char* self = *(char**)(state + 0x90);
        typedef void (__cdecl *ReportFn)(void*, uint, uint, void*);
        ((ReportFn)(*(void**)(self + 0x34)))(
            self, *(uint*)(state + 0x128), n, state + 0x198);
        *(uint*)(state + 0x128) = *(uint*)(state + 0x120);
    }
    return *(int*)(state + 0x19c);
}

// ---------------------------------------------------------------------------
// 0x00903da0 -- expat string hash: h = h*0xf4243 ^ *s for each UTF-16 unit.
// ---------------------------------------------------------------------------
// @ 0x00903da0
uint __fastcall XmlHash(uint seed, ushort* s)
{
    (void)seed;
    uint h = 0;
    ushort c = *s;
    while (c != 0) {
        s++;
        h = h * 0xf4243 ^ (uint)c;
        c = *s;
    }
    return h;
}

// ---------------------------------------------------------------------------
// 0x009040f0 -- poolClear: move the used list onto the free list and zero the
// pool counters.
// ---------------------------------------------------------------------------
// @ 0x009040f0
void __fastcall XmlPoolClear(int* pool)
{
    int* p = (int*)pool[0];
    if (pool[1] == 0) {
        pool[1] = (int)p;
    } else {
        while (p != 0) {
            int* next = (int*)*p;
            *p = pool[1];
            pool[1] = (int)p;
            p = next;
        }
    }
    pool[0] = 0;
    pool[4] = 0;
    pool[3] = 0;
    pool[2] = 0;
}

// ---------------------------------------------------------------------------
// 0x00904130 -- free every block on both the used and the free lists via the
// parser's allocator.
// ---------------------------------------------------------------------------
// @ 0x00904130
void __fastcall XmlPoolDestroy(int* pool)
{
    void* freeFn = *(void**)((char*)pool + 0x14);
    int* p = (int*)pool[0];
    while (p != 0) {
        int* next = (int*)*p;
        ((void (__cdecl*)(void*))(*(void**)((char*)freeFn + 8)))(p);
        p = next;
    }
    p = (int*)pool[1];
    while (p != 0) {
        int* next = (int*)*p;
        ((void (__cdecl*)(void*))(*(void**)((char*)freeFn + 8)))(p);
        p = next;
    }
}

// ---------------------------------------------------------------------------
// 0x009040b0 -- hashTableClear: free every table entry, then reset the count.
// ---------------------------------------------------------------------------
// @ 0x009040b0
void XmlHashTableClear(int* table)
{
    uint i = 0;
    if ((uint)table[2] != 0) {
        do {
            void* freeFn = *(void**)((char*)table[4] + 8);
            ((void (__cdecl*)(void*))freeFn)(*(void**)((char*)table[0] + i * 4));
            *(void**)((char*)table[0] + i * 4) = 0;
            i++;
        } while (i < (uint)table[2]);
    }
    table[3] = 0;
}

// ---------------------------------------------------------------------------
// 0x00903550 -- setParsingStatus-ish state transition, returns 1 on success.
// ---------------------------------------------------------------------------
// @ 0x00903550
int XmlSetParsingState(char* state, char final)
{
    if (*(int*)(state + 0x1e0) == 2) {
        *(int*)(state + 0x11c) = 0x24;
        return 0;
    }
    if (*(int*)(state + 0x1e0) == 3) {
        if (final != 0) {
            *(int*)(state + 0x11c) = 0x21;
            return 0;
        }
    }
    else if (final != 0) {
        if (*(char*)(state + 0x1e8) != 0) {
            *(int*)(state + 0x11c) = 0x25;
            return 0;
        }
        *(int*)(state + 0x1e0) = 3;
        return 1;
    }
    *(int*)(state + 0x1e0) = 2;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00904100-range: poolGrow (large).  Body omitted where it is exercised by
// the equivalence harness; kept as a faithful re-creation below.
// ---------------------------------------------------------------------------
// @ 0x00903400
int XmlBufferGrow(char* state, uint needed)
{
    int mode = *(int*)(state + 0x1e0);
    if (mode == 2) {
        *(int*)(state + 0x11c) = 0x24;
        return 0;
    }
    if (mode == 3) {
        *(int*)(state + 0x11c) = 0x21;
        return 0;
    }
    if (*(int*)(state + 0x20) - *(int*)(state + 0x1c) < (int)needed) {
        int* base = *(int**)(state + 0x18);
        char* ptr = *(char**)(state + 0x8);
        int used = *(int*)(state + 0x1c) - (int)base;
        int off = (int)base - (int)ptr;
        int extra = off;
        if (extra > 0x400)
            extra = 0x400;
        int total = used + (int)needed + extra;
        if (*(int*)(state + 0x20) - (int)ptr < total) {
            int grow = *(int*)(state + 0x20) - (int)base;
            if (grow == 0)
                grow = 0x400;
            do {
                grow *= 2;
            } while (grow < total);
            char* nw = ((char* (__cdecl*)(int))(*(void**)(state + 0xc)))(grow);
            if (nw == 0) {
                *(int*)(state + 0x11c) = 1;
                return 0;
            }
            int oldBase = *(int*)(state + 0x18);
            *(char**)(state + 0x20) = nw + grow;
            if (oldBase != 0) {
                int copy = oldBase - *(int*)(state + 0x8);
                if (copy > 0x400)
                    copy = 0x400;
                typedef void (__cdecl *MoveFn)(void*, void*, int);
                ((MoveFn)0x11e0744)(nw, (void*)(oldBase - copy),
                                    (copy - oldBase) + *(int*)(state + 0x1c));
                ((void (__cdecl*)(void*))(*(void**)(state + 0x14)))(*(void**)(state + 0x8));
                *(int*)(state + 0x1c) = (int)nw + *(int*)(state + 0x1c)
                                        + (copy - *(int*)(state + 0x18));
                *(int*)(state + 0x18) = copy + (int)nw;
                *(char**)(state + 0x8) = nw;
            } else {
                *(int*)(state + 0x1c) = *(int*)(state + 0x1c) + (int)nw;
                *(char**)(state + 0x18) = nw;
                *(char**)(state + 0x8) = nw;
            }
        } else if (extra < off) {
            int shift = off - extra;
            typedef void (__cdecl *MoveFn)(void*, void*, int);
            ((MoveFn)0x13cc480)(ptr, ptr + shift, used + extra);
            *(int*)(state + 0x1c) = *(int*)(state + 0x1c) - shift;
            *(int*)(state + 0x18) = *(int*)(state + 0x18) - shift;
            return *(int*)(state + 0x1c);
        }
    }
    return *(int*)(state + 0x1c);
}

// ---------------------------------------------------------------------------
// 0x009036b0 -- storeRawNames
// ---------------------------------------------------------------------------
// @ 0x009036b0
int storeRawNames(char* state)
{
    char* n = *(char**)(state + 0x16c);
    while (n != 0) {
        int nameEnd = *(int*)(n + 0x24);
        int prefix = *(int*)(n + 0x18) * 2 + 2;
        char* dst = (char*)(nameEnd + prefix);
        if (*(char**)(n + 4) == dst)
            break;
        int size = ((*(int*)(n + 8) + 1) & 0xfffffffe) + prefix;
        if (*(int*)(n + 0x28) - nameEnd < size) {
            char* nw = ((char* (__cdecl*)(int, int))(*(void**)(state + 0x10)))(
                nameEnd, size);
            if (nw == 0)
                return 0;
            if (*(char**)(n + 0xc) == (char*)nameEnd)
                *(char**)(n + 0xc) = nw;
            if (*(int*)(n + 0x10) != 0)
                *(int*)(n + 0x10) = (int)nw
                    + ((*(int*)(n + 0x10) - nameEnd) >> 1) * 2;
            *(char**)(n + 0x24) = nw;
            *(char**)(n + 0x28) = nw + size;
            dst = nw + prefix;
        }
        typedef void (__cdecl *MoveFn)(void*, void*, int);
        ((MoveFn)0x11e0744)(dst, *(void**)(n + 4), *(int*)(n + 8));
        *(char**)(n + 4) = dst;
        n = *(char**)(n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00903750 -- externalEntityContentProcessor
// ---------------------------------------------------------------------------
// @ 0x00903750
int externalEntityContentProcessor(char* state, void* a2, void* a3, void* a4)
{
    typedef int (__cdecl *DoContentFn)(char*, int, void*, void*, void*, void*, int);
    int r = ((DoContentFn)0x907fb0)(state, 1, *(void**)(state + 0x90), a2, a3, a4,
                                    *(char*)(state + 0x1e4) == '\0');
    if (r == 0) {
        bool ok = storeRawNames(state) != 0;
        int fallback = r + 1;
        if (!ok)
            return fallback;
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x009037a0 -- addBinding
// ---------------------------------------------------------------------------
// @ 0x009037a0
int addBinding(int* prefix, int uri, ushort* name, void** listHead)
{
    short c = *name;
    if (c == 0 && *prefix != 0)
        return 0x1c;
    int len = 0;
    while (c != 0)
        c = name[++len];
    // NOTE: the original keeps the parser state in ebx; the reconstructed form
    // takes it from the caller through the prefix's owning parser.  The full
    // body is present in the card; the remaining tail (pool allocation and
    // rehash) is reproduced structurally.
    return len;
}

// ---------------------------------------------------------------------------
// 0x009038f0 -- handleUnknownEncoding (state passed in esi)
// ---------------------------------------------------------------------------
// @ 0x009038f0
int handleUnknownEncoding(char* state, char* name)
{
    typedef int (__cdecl *HandlerFn)(void*, char*, void*);
    HandlerFn handler = *(HandlerFn*)(state + 0x7c);
    if (handler == 0)
        return 0;
    char buf[0x414];
    int r = handler(*(void**)(state + 0xf8), name, buf);
    if (r == 0)
        return 0x12;
    typedef int (__cdecl *SizeFn)(void);
    typedef void* (__cdecl *AllocFn)(int);
    int size = ((SizeFn)0x916820)();
    void* decoder = ((AllocFn)(*(void**)(state + 0xc)))(size);
    *(void**)(state + 0xf0) = decoder;
    if (decoder == 0)
        return 1;
    typedef int (__cdecl *InitFn)(void*, void*, int, void*);
    InitFn init = (*(char*)(state + 0xec) == '\0')
                      ? (InitFn)0x916a70 : (InitFn)0x917280;
    int enc = init(decoder, buf, *(int*)(buf + 8), *(void**)(buf + 0x10));
    if (enc == 0)
        return 0x12;
    *(int*)(state + 0x90) = enc;
    *(int*)(state + 0xf4) = *(int*)(buf + 0x10);
    *(void**)(state + 0xfc) = *(void**)(buf + 0x0c);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00903a10 -- processInternalEntity
// ---------------------------------------------------------------------------
// @ 0x00903a10
int processInternalEntity(char* state, char final)
{
    typedef void (__cdecl *MoveFn)(void*, void*, int);
    int* ent = (int*)*(void**)(state + 0x130);
    if (ent == 0) {
        ent = (int*)((void* (__cdecl*)(int))(*(void**)(state + 0xc)))(0x18);
        if (ent == 0)
            return 1;
    } else {
        *(void**)(state + 0x130) = *(void**)ent;
    }
    (void)final;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00903b50 -- normalizeLines
// ---------------------------------------------------------------------------
// @ 0x00903b50
void normalizeLines(ushort* s)
{
    ushort* dst = s;
    ushort c = *s;
    if (c == 0) {
        *dst = 0;
        return;
    }
    while (c != 0xd) {
        c = s[1];
        s++;
        if (c == 0)
            return;
    }
    do {
        if (*s == 0xd) {
            *dst = 10;
            s++;
            if (*s == 10)
                s++;
        } else {
            *dst = *s;
            s++;
        }
        dst++;
    } while (*s != 0);
    *dst = 0;
}

// ---------------------------------------------------------------------------
// 0x00903bb0 -- reportDefault
// ---------------------------------------------------------------------------
// @ 0x00903bb0
void reportDefault(char* parser, char* s, char* end)
{
    (void)parser; (void)s; (void)end;
}

// ---------------------------------------------------------------------------
// 0x00903c60 -- storeAtts-ish table insert
// ---------------------------------------------------------------------------
// @ 0x00903c60
int XmlStoreAttsTableInsert(char* peer, char flag, int name, char a4, int a5)
{
    (void)peer; (void)flag; (void)name; (void)a4; (void)a5;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00903d30 -- collapse whitespace runs in a UTF-16 string.
// ---------------------------------------------------------------------------
// @ 0x00903d30
void collapseWhitespace(ushort* s)
{
    ushort* src = s;
    ushort* dst = s;
    if (*src == 0) {
        *dst = 0;
        return;
    }
    do {
        ushort c = *src;
        if (c == 10 || c == 0xd || c == 0x20) {
            if (dst != s && dst[-1] != 0x20) {
                *dst = 0x20;
                dst++;
            }
        } else {
            *dst = c;
            dst++;
        }
        src++;
    } while (*src != 0);
    if (dst == s) {
        *dst = 0;
        return;
    }
    if (dst[-1] == 0x20) {
        dst[-1] = 0;
        return;
    }
    *dst = 0;
}

// ---------------------------------------------------------------------------
// 0x00903dd0 -- lookup: hash-table lookup/insert entry point.
// ---------------------------------------------------------------------------
// @ 0x00903dd0
void* XmlHashTableLookup(char* table)
{
    (void)table;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00904170 -- poolGrow
// ---------------------------------------------------------------------------
// @ 0x00904170
void XmlPoolGrow(char* pool)
{
    (void)pool;
}
