// Slice s009186e0 - EA::Callstack DWARF2 debug-info reader: the DWARF form readers (ReadTyped /
// ReadTypedAdd / ReadSpecial / Skip), the abbrev/record scanner (Scan, SetField, HandleRecord),
// the memory-stream section loaders, and the DWARF2File container ctor/dtor.
// Original compiler: VS2008 SP1 x86 (cl 15.00.30729.01), /O2 /MD /Gy /TP /GS-.
#include "types.h"

// ---- runtime helpers ---------------------------------------------------------
extern "C" void* __cdecl FUN_006abeb0(unsigned int size);   // 0x006abeb0  allocator
extern "C" void  __cdecl FUN_00f47380(void* p);             // 0x00f47380  operator delete

// ---- streams -----------------------------------------------------------------
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual int  GetSize();                       // 0x1c
    virtual int  s8();                            // 0x20
    virtual int  GetPosition(int mode);           // 0x24
    virtual bool SetPosition(int pos, int mode);  // 0x28
    virtual int  s11();                           // 0x2c
    virtual int  Read(void* buf, int n);          // 0x30
    virtual void s13();                           // 0x34
    virtual void s14();                           // 0x38
    virtual void v3c(void*);                      // 0x3c
    virtual void s16();                           // 0x40
    virtual void s17();                           // 0x44
    virtual void s18();                           // 0x48
    virtual bool v4c(int, int, int, int);         // 0x4c
};

struct FileStream : IStream {
    FileStream(const char* name);                 // 0x00931da0
    virtual ~FileStream();                        // 0x00931e70
    char pad[0x22c - 4];
};

struct MemStream : IStream {
    MemStream(void* data, unsigned int size, const char* name);   // 0x0093c270
    virtual ~MemStream();                                         // 0x0093bde0
    bool ReadVarU64(uint64_t* out);                               // 0x00918200
    bool ReadVarS64(int64_t* out);                                // 0x00918260
    bool ReadFixed(uint64_t id, void* out);                       // 0x009186a0
    bool SetData(void* data, unsigned int size, unsigned char a, unsigned char b, unsigned char c);
    char pad[0x24 - 4];
};

struct DWARF2File;

struct MemStreamBase30 : MemStream {
    DWARF2File* mDoc;      // 0x24
    void*       mBuf;      // 0x28
    unsigned int mSize;    // 0x2c
    MemStreamBase30() : MemStream(0, 0, "UTF/MemoryStream") { mDoc = 0; mBuf = 0; mSize = 0; }
    void InitA(DWARF2File* doc);                  // 0x009182d0
};

struct DbgSection {
    DbgSection();                                 // 0x00b90720
    bool Load(IStream* st);                       // 0x0091bd40
    bool Get(const char* name, void* out);        // 0x0091bdd0
    char pad[0x50];
};

struct B { virtual ~B(); };
B::~B() {}

// DWARF2 debug section descriptor filled in by DbgSection::Get (0x40 bytes).
struct SectionDesc {
    unsigned int pad00[6];
    unsigned int begin;      // +0x18
    unsigned int f1c;        // +0x1c
    unsigned int size;       // +0x20
    unsigned int pad24[7];
};

// DWARF attribute/abbrev record description (0x38 bytes).
struct Info {
    unsigned int flags;      // +0x00
    unsigned int f04;        // +0x04
    unsigned int f08, f0c;   // +0x08
    unsigned int f10, f14;   // +0x10
    unsigned int f18, f1c;   // +0x18
    unsigned int f20, f24;   // +0x20
    unsigned int f28, f2c;   // +0x28
    unsigned int f30, f34;   // +0x30
    bool HasFlag(unsigned int a1);                // 0x00918c50
};

struct Seg {                 // 32 bytes: mSeg at +0x48, mCur at +0x68
    uint64_t a;
    uint64_t b;
    uint64_t c;
    unsigned char d;
    unsigned char pad[7];
};

struct Parser : MemStreamBase30 {
    union {                       // +0x30: sub-stream pointer in the outer parser,
        Parser*      mSub;        //        section size in the loaded sub-stream
        unsigned int mSectionSize;
    };
    unsigned short f34;                            // +0x34
    unsigned short f36;                            // +0x36
    unsigned int   f38;                            // +0x38
    unsigned char  f3c, f3d;                       // +0x3c
    signed char    f3e;                            // +0x3e
    unsigned char  f3f, f40;                       // +0x3f..+0x40
    unsigned char  pad41[7];
    Seg            mSeg;                            // +0x48
    Seg            mCur;                            // +0x68
    unsigned char  f88;                             // +0x88
    unsigned char  pad89[3];
    unsigned int   f8c;                             // +0x8c

    Parser();
    bool ReadTyped(uint64_t id, int64_t* out);                    // 0x009186e0
    bool ReadTypedAdd(uint64_t id, int64_t* out);                 // 0x00918830
    bool ReadSpecial(uint64_t id, int64_t* out);                  // 0x00918990
    bool Skip(uint64_t id);                                       // 0x00918a40
    bool LoadFrom(DWARF2File* holder, Parser* stream);            // 0x00918c70
    bool Scan(uint64_t id, Info* info);                           // 0x00918cf0
    bool LoadSection(DWARF2File* holder, Info* info);             // 0x00918ff0
    void F919090(void* a1);                                       // 0x00919090
    bool SetField(void* a1, unsigned char tag);                   // 0x009192c0
    bool HandleRecord(void* a1, unsigned char tag, uint64_t value);  // 0x009193d0
};

struct DocData {
    unsigned int f2d8;
    unsigned int f2dc;
    unsigned int f2e0;
    unsigned int f2e4;
};

struct DWARF2File : B, FileStream {
    DbgSection  mDbg;             // 0x230
    unsigned char mbInit;         // 0x280
    unsigned char pad281[3];
    unsigned int mArangesBegin;   // 0x284
    unsigned int mArangesEnd;     // 0x288
    unsigned int mInfoBegin;      // 0x28c
    unsigned int mAbbrevBegin;    // 0x290
    unsigned int mAbbrevEnd;      // 0x294
    unsigned int mLineBegin;      // 0x298
    unsigned int mStrBegin;       // 0x29c
    unsigned int f2a0;            // 0x2a0
    unsigned int f2a4;            // 0x2a4
    MemStreamBase30 mSub;         // 0x2a8 (used as a Parser by the outer scanners)
    DocData     mData;            // 0x2d8

    DWARF2File();
    virtual ~DWARF2File();
    unsigned char Init(void* a1, void* a2);   // 0x00919110
};

// =============================================================================
// @ 0x009186e0  DWARF form reader: read a fixed-size value of the given form.
bool Parser::ReadTyped(uint64_t id, int64_t* out)
{
    unsigned char  b;
    unsigned short s;
    unsigned int   i;
    uint64_t       q;
    int64_t        sq;

    switch (id) {
    case 11:
        if (Read(&b, 1) != 1)
            return false;
        *out = b;
        return true;
    case 5:
        if (Read(&s, 2) != 2)
            return false;
        *out = s;
        return true;
    case 6:
        if (Read(&i, 4) != 4)
            return false;
        *out = i;
        return true;
    case 7:
        if (Read(&q, 8) != 8)
            return false;
        *out = q;
        return true;
    case 13:
        if (!ReadVarS64(&sq))
            return false;
        *out = sq;
        return true;
    case 15:
        if (!ReadVarU64(&q))
            return false;
        *out = q;
        return true;
    }
    return false;
}

// =============================================================================
// @ 0x00918830  DWARF form reader that accumulates into a running base value.
bool Parser::ReadTypedAdd(uint64_t id, int64_t* out)
{
    unsigned char  b;
    unsigned short s;
    unsigned int   i;
    uint64_t       q;

    if (id == 0x10) {
        unsigned int n = ((unsigned char*)&mDoc->mData.f2dc)[2];
        return Read(out, n) == n;
    }
    *out = mDoc->mData.f2e0;
    switch (id) {
    case 0x11:
        if (Read(&b, 1) != 1)
            return false;
        *out += b;
        return true;
    case 0x12:
        if (Read(&s, 2) != 2)
            return false;
        *out += s;
        return true;
    case 0x13:
        if (Read(&i, 4) != 4)
            return false;
        *out += i;
        return true;
    case 0x14:
        if (Read(&q, 8) != 8)
            return false;
        *out += q;
        return true;
    case 0x15:
        if (!ReadVarU64(&q))
            return false;
        *out += q;
        return true;
    }
    return false;
}

// =============================================================================
// @ 0x00918990  DWARF form reader for the string forms (string / strp).
bool Parser::ReadSpecial(uint64_t id, int64_t* out)
{
    if (id == 8) {
        unsigned char c;
        *out = GetPosition(0) + mDoc->mData.f2e0 + 0xb;
        do {
            if (Read(&c, 1) != 1)
                return false;
        } while (c != 0);
        return true;
    }
    if (id == 0xe) {
        unsigned int off;
        if (Read(&off, 4) != 4)
            return false;
        *out = (int64_t)(int)mDoc->mStrBegin;
        *out += off;
        return true;
    }
    return false;
}

// =============================================================================
// @ 0x00918a40  Skip the payload of one DWARF form.
bool Parser::Skip(uint64_t id)
{
    unsigned short s;
    unsigned int   i;
    uint64_t       q;
    unsigned char  c;
    bool           ok;

    switch (id) {
    case 1:
    case 0x10:
        ok = SetPosition(((unsigned char*)&mDoc->mData.f2dc)[2], 1);
        break;
    case 3:
        if (Read(&s, 2) != 2)
            return false;
        ok = SetPosition(s, 1);
        break;
    case 4:
        if (Read(&i, 4) != 4)
            return false;
        ok = SetPosition(i, 1);
        break;
    case 5:
        ok = SetPosition(2, 1);
        break;
    case 6:
        ok = SetPosition(4, 1);
        break;
    case 7:
        ok = SetPosition(8, 1);
        break;
    case 8:
        do {
            if (Read(&c, 1) != 1)
                return false;
        } while (c != 0);
        return true;
    case 9:
        if (!ReadVarU64(&q))
            return false;
        ok = SetPosition((unsigned int)q, 1);
        break;
    case 10:
        if (Read(&c, 1) != 1)
            return false;
        ok = SetPosition(c, 1);
        break;
    case 0xb:
    case 0xc:
        ok = SetPosition(1, 1);
        break;
    case 0xd:
        ok = ReadVarS64((int64_t*)&q);
        break;
    case 0xe:
    case 0x13:
        ok = SetPosition(4, 1);
        break;
    case 0xf:
        ok = ReadVarU64(&q);
        break;
    case 0x11:
        ok = SetPosition(1, 1);
        break;
    case 0x12:
        ok = SetPosition(2, 1);
        break;
    case 0x14:
        ok = SetPosition(8, 1);
        break;
    case 0x15:
        ok = ReadVarU64(&q);
        break;
    default:
        return false;
    }
    if (ok)
        return true;
    return false;
}

// =============================================================================
// @ 0x00918c50
bool Info::HasFlag(unsigned int a1)
{
    if ((flags & 6) != 0 && f18 < a1 && f10 >= a1)
        return true;
    return false;
}

// =============================================================================
// @ 0x00918c70  Load the abbreviation table out of the file into this memory stream.
bool Parser::LoadFrom(DWARF2File* holder, Parser* stream)
{
    mSub = stream;
    mDoc = holder;
    unsigned int off  = holder->mData.f2e4;
    unsigned int size = holder->mAbbrevEnd - off;
    mSize = size;
    mBuf  = (unsigned char*)FUN_006abeb0(size);
    IStream* st = (IStream*)((char*)holder + 4);
    if (st->SetPosition(off, 0)) {
        if (st->Read(mBuf, mSize) == (int)mSize) {
            SetData(mBuf, mSize, 1, 1, 0);
            return true;
        }
    }
    return false;
}

// =============================================================================
// @ 0x00918cf0  Scan the abbreviation stream for one record id and fill in Info.
bool Parser::Scan(uint64_t id, Info* info)
{
    uint64_t      a, b, v1, v2;
    unsigned char found = 0;

    if (!SetPosition(0, 0))
        return false;
    while (GetPosition(0) < GetSize()) {
        if (!ReadVarU64(&v1))
            return false;
        if (v1 == 0)
            return false;
        if (!ReadVarU64(&v2))
            return false;
        if (!SetPosition(1, 1))
            return false;
        if (v1 == id) {
            found = 1;
            if (!ReadVarU64(&a))
                return false;
            if (!ReadVarU64(&b))
                return false;
            if (a == 0)
                return found;
            for (;;) {
                if (b == 0)
                    return found;
                if (b == 0x16) {
                    if (!mSub->ReadVarU64(&b))
                        return false;
                } else {
                    switch ((int)a) {
                    case 3:
                        if (!mSub->ReadSpecial(b, (int64_t*)&info->f08))
                            return false;
                        info->flags |= 1;
                        break;
                    case 0x10:
                        if (!mSub->ReadTyped(b, (int64_t*)&info->f20))
                            return false;
                        info->flags |= 8;
                        break;
                    case 0x11:
                        if (!mSub->ReadFixed(b, &info->f18))
                            return false;
                        info->flags |= 4;
                        break;
                    case 0x12:
                        if (!mSub->ReadFixed(b, &info->f10))
                            return false;
                        info->flags |= 2;
                        break;
                    case 0x31:
                        if (!mSub->ReadTypedAdd(b, (int64_t*)&info->f28))
                            return false;
                        info->flags |= 0x10;
                        break;
                    case 0x47:
                        if (!mSub->ReadTypedAdd(b, (int64_t*)&info->f30))
                            return false;
                        info->flags |= 0x20;
                        break;
                    default:
                        if (!mSub->Skip(b))
                            return false;
                        break;
                    }
                    if (!ReadVarU64(&a))
                        return false;
                    if (!ReadVarU64(&b))
                        return false;
                }
                if (a == 0)
                    return found;
            }
        }
        do {
            if (!ReadVarU64(&a))
                return false;
            if (!ReadVarU64(&b))
                return false;
        } while (a != 0 && b != 0);
    }
    return found;
}

// =============================================================================
// @ 0x00918ff0  Load one debug section (its description says so) into this stream.
bool Parser::LoadSection(DWARF2File* holder, Info* info)
{
    mDoc = holder;
    if (((info->flags >> 4) & 1) == 0)
        return false;
    IStream* st = (IStream*)((char*)holder + 4);
    if (!st->SetPosition(holder->mLineBegin + info->f20, 0))
        return false;
    if (st->Read(&mSectionSize, 4) != 4)
        return false;
    unsigned int size = mSectionSize;
    mSize = size;
    mBuf  = (unsigned char*)FUN_006abeb0(size);
    if (st->Read(mBuf, mSize) != (int)mSize)
        return false;
    SetData(mBuf, mSize, 1, 1, 0);
    return true;
}

// =============================================================================
// @ 0x00919090  Update the current segment; flag the address as seen when it lands in it.
void Parser::F919090(void* a1)
{
    if (a1 == (void*)mCur.a) {
        f88 = 1;
    } else if (mSeg.d != 0 && a1 >= (void*)mSeg.a && a1 < (void*)mCur.a) {
        f88 = 1;
        return;
    }
    mSeg = mCur;
}

// =============================================================================
// @ 0x00919110
unsigned char DWARF2File::Init(void* a1, void* a2)
{
    SectionDesc aranges, abbrev, info, line, str;

    if (!mbInit) {
        IStream* st = (IStream*)((char*)this + 4);
        st->v3c(a1);
        if (st->v4c(1, 6, 1, 0)
            && mDbg.Load(st)
            && mDbg.Get(".debug_aranges", &aranges)
            && mDbg.Get(".debug_info", &info)
            && mDbg.Get(".debug_abbrev", &abbrev)
            && mDbg.Get(".debug_line", &line)
            && mDbg.Get(".debug_str", &str)) {
            mArangesBegin = aranges.begin;
            mArangesEnd   = aranges.begin + aranges.size;
            mInfoBegin    = info.begin;
            mAbbrevBegin  = abbrev.begin;
            mAbbrevEnd    = abbrev.begin + abbrev.size;
            mLineBegin    = line.begin;
            mStrBegin     = str.begin;
            mSub.InitA(this);
            mbInit = 1;
        }
    }
    return mbInit;
}

// =============================================================================
// @ 0x00919270
Parser::Parser()
{
}

// =============================================================================
// @ 0x009192c0  Resolve one abbrev-spec field (tag below the fixed threshold, else computed).
bool Parser::SetField(void* a1, unsigned char tag)
{
    int           pos;
    unsigned char c;
    uint64_t      v;

    if (tag < f40) {
        pos = GetPosition(0);
        if (!SetPosition(tag + 0xa, 1))
            return false;
        if (Read(&c, 1) != 1)
            return false;
        if (!SetPosition(pos, 0))
            return false;
        while (c) {
            c--;
            if (!ReadVarU64(&v))
                return false;
        }
        return true;
    }
    int d = (unsigned char)(tag - f40);
    int q = d / f3f;
    int r = d % f3f;
    mCur.c += (int64_t)((int)f3e + r);
    mCur.a += (int64_t)((int)(unsigned char)f3c * q);
    F919090(a1);
    return true;
}

// =============================================================================
// @ 0x009193d0  Handle one abbrev record (tag 1/2/3, else plain reposition).
bool Parser::HandleRecord(void* a1, unsigned char tag, uint64_t value)
{
    switch (tag) {
    case 1:
        F919090(a1);
        mCur.a = 0;
        mCur.b = 1;
        mCur.c = 1;
        return true;
    case 2: {
        uint64_t n = value - 1;
        if (n == 4) {
            unsigned int v;
            if (Read(&v, 4) != 4)
                return false;
            mCur.a = v;
            mCur.b = 0;
            return true;
        }
        if (n == 8) {
            uint64_t v;
            if (Read(&v, 8) != 8)
                return false;
            mCur.a = v;
            return true;
        }
        return false;
    }
    case 3: {
        unsigned char c;
        do {
            if (Read(&c, 1) != 1)
                return false;
        } while (c != 0);
        uint64_t v;
        if (!ReadVarU64(&v))
            return false;
        if (!ReadVarU64(&v))
            return false;
        if (!ReadVarU64(&v))
            return false;
        return true;
    }
    default:
        if (!SetPosition((unsigned int)value, 1))
            return false;
        return true;
    }
}

// =============================================================================
// @ 0x00919510
DWARF2File::DWARF2File()
    : FileStream(0), mDbg(), mbInit(0), mArangesBegin(0), mArangesEnd(0), mInfoBegin(0),
      mAbbrevBegin(0), mAbbrevEnd(0), mLineBegin(0), mStrBegin(0), f2a0(0), f2a4(0),
      mSub(), mData()
{
}

// @ 0x009195c0  DWARF2File::~DWARF2File (also emits the scalar deleting destructor ??_G)
DWARF2File::~DWARF2File()
{
    if (mbInit)
        mbInit = 0;
}
