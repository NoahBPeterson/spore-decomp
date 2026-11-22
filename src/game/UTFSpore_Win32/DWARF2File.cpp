// src/game/UTFSpore_Win32/DWARF2File.cpp -- migrated from slice(s) s00919620, s009186e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DWARF2File.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/IStream.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_006abeb0(unsigned int size);   // 0x006abeb0  allocator

// ---- items of slice s009186e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_006abeb0(unsigned int size);   // 0x006abeb0  allocator
struct IStream {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
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
// ---- items of slice s009186e0 end

// ---- items of slice s00919620 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
#pragma inline_depth(0)
__declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
void __cdecl EA_free(void* p);                                                          // 0x00f47380 operator delete[]
struct StrBase {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator; char* mpPoolBegin;
    StrBase() {}
    StrBase(const StrBase& o);                       // 0x00886780
    void DeallocateSelf()                            // 0x00919a40
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPoolBegin)
            EA_free(mpBegin);
    }
    ~StrBase() { DeallocateSelf(); }
    StrBase& assign(const char* first, const char* last);  // 0x009199c0
    char* erase(char* f, char* l) { if (f != l) { memmove(f, l, (mpEnd - l) + 1); mpEnd -= (l - f); } return f; }
    void append(const char* first, const char* last);  // 0x00942e50
    StrBase& append(uint32_t c);                       // 0x00924c60
    StrBase* AppendRet(uint32_t c);                    // 0x00919c10
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void reserve(unsigned n);                          // 0x00886560
    StrBase& operator=(const StrBase& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
struct FixedString : StrBase {
    char mBuf[0x100];
    FixedString();                                   // 0x00919a60
    void swap(FixedString& o);                       // 0x00919a80
};
struct StrPair {
    FixedString a;     // +0
    FixedString b;     // +0x114
    StrPair();         // 0x00919b20
    ~StrPair();        // 0x00919b70
};
struct Ctx : StrPair {
    uint64_t f228;
    uint64_t f230;
    uint64_t f238;
};
struct IStream_s0091_9620 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
    virtual int  GetSize();                       // 0x1c
    virtual int  s8();                            // 0x20
    virtual int  GetPosition(int mode);           // 0x24
    virtual bool SetPosition(int pos, int mode);  // 0x28
    virtual int  s11();                           // 0x2c
    virtual int  Read(void* buf, int n);          // 0x30
};
struct Seg_s0091_9620 {
    uint64_t a;      // +0
    uint64_t b;      // +8  (record count)
    uint64_t c;      // +0x10
    uint8_t  d;      // +0x18
    uint8_t  pad[7];
};
struct Info_s0091_9620 {        // 0x38 bytes
    uint32_t flags;
    uint32_t f4;
    uint32_t f8;
    uint32_t fc, f10, f14, f18, f1c;
    uint64_t size;   // +0x20
    uint32_t f28, f2c, f30, f34;
    bool F918c50(void* a1);                       // 0x00918c50
};
struct MemStream_s0091_9620 : IStream_s0091_9620 {
    MemStream_s0091_9620(int a, int b, const char* name);    // 0x0093c270
    ~MemStream_s0091_9620();                                 // 0x0093bde0
    int  Pos(int mode);                           // 0x0093b920
    int  Size();                                  // 0x00fc7e50
    bool F918620(void* holder);                   // 0x00918620
    bool F918c70(void* holder, MemStream_s0091_9620* other); // 0x00918c70
    bool F918200(uint64_t* out);                  // 0x00918200
    bool F918cf0(uint32_t lo, uint32_t hi, void* arg);  // 0x00918cf0
    bool F918260(uint64_t* out);                  // 0x00918260
    virtual void vslot();
    char pad[0x20];
};
struct MemStreamBase30_s0091_9620 : MemStream_s0091_9620 {
    uint32_t m24, m28, m2c;
    MemStreamBase30_s0091_9620() : MemStream_s0091_9620(0, 0, "UTF/MemoryStream") { m24 = 0; m28 = 0; m2c = 0; }
    virtual void vslot();
};
struct MemStream2 : MemStreamBase30_s0091_9620 {
    MemStream2() {}
    virtual void vslot();
};
struct MemStream3 : MemStreamBase30_s0091_9620 {
    MemStream3() {}
    virtual void vslot();
};
struct Parser_s0091_9620 : MemStream2 {
    uint32_t f30;
    uint16_t f34;
    uint16_t pad36;
    uint32_t f38;
    uint8_t  f3c, f3d, f3e, f3f, f40;
    uint8_t  pad41[7];
    Seg_s0091_9620      seg;           // +0x48
    int64_t  f68;
    uint64_t f70;
    int64_t  f78;
    uint8_t  f80;
    uint8_t  pad81[7];
    uint8_t  f88;
    uint8_t  pad89[3];
    int      f8c;
    Parser_s0091_9620();                                    // 0x00919270
    bool F919750(void* a1, Seg_s0091_9620* out);
    bool F919ca0(void* a1, Ctx* ctx);
    bool F919090(void* a1);                      // 0x00919090
    bool F9192c0(void* a1, uint32_t tag);        // 0x009192c0
    bool F9193d0(void* a1, uint32_t b, uint32_t lo, uint32_t hi);  // 0x009193d0
    bool F918ff0(void* holder, Info_s0091_9620* info);      // 0x00918ff0
};
struct Holder {
    int vptr0;
    IStream_s0091_9620 sub4;                                // stream at +4 (vtable only used)
    char pad[0x280 - 8];
    uint8_t f280;
    char pad281[0x2a8 - 0x281];
    struct Sub { bool F918350(void* a1, void* out); } f2a8;   // 0x00918350
    char pad2a9[0x2d8 - 0x2a8 - 1];
    char f2d8[0x10];
    bool F919620(void* a1, Info_s0091_9620* info);          // 0x00919620
    bool F919bc0(StrPair* p, FixedString* out);  // 0x00919bc0
    bool F919c30(Info_s0091_9620* p, FixedString* out);     // 0x00919c30
    uint32_t F91a010(uint8_t flags, void* a2, StrPair* out, uint32_t* arg4);
    bool F919c10dummy();
};
// ---- items of slice s00919620 end

// @ 0x009186e0
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

// @ 0x00918830
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

// @ 0x00918a40
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

// @ 0x00918cf0
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

// @ 0x00918ff0
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

// @ 0x00919090
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

// @ 0x009192c0
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

// @ 0x009193d0
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

// @ 0x00919620
bool Holder::F919620(void* a1, Info_s0091_9620* info)
{
    if (!f2a8.F918350(a1, f2d8))
        return false;
    MemStream2 s1;
    if (!s1.F918620(this))
        return false;
    MemStream3 s2;
    if (!s2.F918c70(this, &s1))
        return false;
    bool ok = false;
    for (;;) {
        if (!(s1.Pos(0) < s1.Size()))
            break;
        uint64_t v;
        if (!s1.F918200(&v))
            break;
        if (v == 0)
            continue;
        if (!s2.F918cf0((uint32_t)v, (uint32_t)(v >> 32), info))
            break;
        if (info->F918c50(a1)) {
            ok = true;
            break;
        }
    }
    return ok;
}

// @ 0x00919750
bool Parser_s0091_9620::F919750(void* a1, Seg_s0091_9620* out)
{
    if (!SetPosition(f38 + 6, 0))
        return false;
    seg.a = 0;
    seg.b = 1;
    seg.c = 1;
    seg.d = 0;
    f68 = 0;
    f70 = 1;
    f78 = 1;
    f80 = 1;
    f88 = 0;
    if (!(GetPosition(0) < GetSize()))
        return false;
    for (;;) {
        uint32_t tag;
        if (Read(&tag, 1) != 1)
            return false;
        bool good = true;
        switch ((uint8_t)tag) {
        case 0: {
            uint64_t t;
            if (!F918200(&t)) return false;
            if (Read(&tag, 1) != 1) return false;
            good = F9193d0(a1, tag, (uint32_t)t, (uint32_t)(t >> 32));
            if (!good) return false;
            break;
        }
        case 1:
            F919090(a1);
            break;
        case 2: {
            uint64_t t;
            if (!F918200(&t)) return false;
            f68 += (int64_t)f3c * (int64_t)t;
            break;
        }
        case 3: {
            uint64_t t2;
            if (!F918260(&t2)) return false;
            f78 += t2;
            break;
        }
        case 4: {
            uint64_t t;
            if (!F918200(&t)) return false;
            f70 = t;
            break;
        }
        case 5: {
            uint64_t t;
            if (!F918200(&t)) return false;
            break;
        }
        case 6:
        case 7:
            break;
        case 8:
            f68 += ((255 - f40) / f3f) * f3c;
            break;
        case 9: {
            uint16_t w;
            if (Read(&w, 2) != 2) return false;
            f68 += w;
            break;
        }
        default:
            if (!F9192c0(a1, tag)) return false;
            break;
        }
        if (f88 != 0) {
            *out = seg;
            return true;
        }
        if (!(GetPosition(0) < GetSize()))
            return false;
    }
}

// @ 0x00919a60
FixedString::FixedString()
{
    char* p = mBuf;
    mpPoolBegin = p;
    _ReadWriteBarrier();
    mpEnd = p;
    mpBegin = p;
    mpCapacity = p + 0x100;
    *p = 0;
}

// @ 0x00919a80
void FixedString::swap(FixedString& o)
{
    if (&mAllocator == &o.mAllocator) {
        char* t;
        t = mpBegin; mpBegin = o.mpBegin; o.mpBegin = t;
        t = mpEnd; mpEnd = o.mpEnd; o.mpEnd = t;
        t = mpCapacity; mpCapacity = o.mpCapacity; o.mpCapacity = t;
        return;
    }
    StrBase temp(*this);
    StrBase::operator=(o);
    o.StrBase::operator=(temp);
}

// @ 0x00919b20
StrPair::StrPair()
{
}

// @ 0x00919ca0
bool Parser_s0091_9620::F919ca0(void* a1, Ctx* ctx)
{
    ctx->a.clear();
    ctx->b.clear();
    ctx->f228 = 0;
    ctx->f230 = 0;
    ctx->f238 = 0;
    if (!SetPosition(0, 0)) return false;
    if (Read(&f34, 2) != 2 || f34 != 2) return false;
    if (Read(&f38, 4) != 4) return false;
    if (Read(&f3c, 1) != 1) return false;
    if (Read(&f3d, 1) != 1) return false;
    if (Read(&f3e, 1) != 1) return false;
    if (Read(&f3f, 1) != 1) return false;
    if (Read(&f40, 1) != 1) return false;
    if (!SetPosition(f40 - 1, 1)) return false;
    uint32_t ch;
    if (Read(&ch, 1) != 1) return false;
    while ((uint8_t)ch != 0) {
        do {
            if (Read(&ch, 1) != 1) return false;
        } while ((uint8_t)ch != 0);
        if (Read(&ch, 1) != 1) return false;
    }
    f8c = GetPosition(0);
    Seg_s0091_9620 sg;
    if (!F919750(a1, &sg)) return false;
    if (!SetPosition(f8c, 0)) return false;
    uint64_t t = 0;
    uint32_t i = 0;
    if (sg.b > 0) {
        do {
            ctx->a.clear();
            do {
                if (Read(&ch, 1) != 1) return false;
                if ((uint8_t)ch == 0) break;
                ctx->a.AppendRet(ch);
            } while ((uint8_t)ch != 0);
            if (!F918200(&t)) return false;
            if (!F918200(&ctx->f228)) return false;
            if (!F918200(&ctx->f230)) return false;
            i++;
        } while (i < sg.b);
    }
    if (!SetPosition(f40 + 10, 0)) return false;
    i = 0;
    if (t > 0) {
        do {
            ctx->b.clear();
            do {
                if (Read(&ch, 1) != 1) return false;
                if ((uint8_t)ch == 0) break;
                ctx->b.AppendRet(ch);
            } while ((uint8_t)ch != 0);
            i++;
        } while (i < t);
    }
    ctx->f238 = sg.c;
    return true;
}
