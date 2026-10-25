// Slice s008dd0d0 (0x8dd0d0..0x8de020) - ResourceMan record streaming / database-copy helpers.
//
// Functions (VA, name):
//   008dd0d0  ResourceMan::PFRecordWrite::PFRecordWrite   (in-place ctor)
//   008dd1c0  EA::SharedLibrary::Release
//   008dd1f0  PFRecordWrite::_virtual_dtor
//   008dd250  EA::ResourceMan::CopyDatabaseRecord
//   008dd430  EA::ResourceMan::CopyDatabaseRecords
//   008dd510  Resource::FindEmbeddedPackageHeader
//   008dd7d0  FNV-1a hash over a lowercase wide string
//   008dd820  parse a fixed-hex token
//   008dd8d0  set name-from-key hooks
//   008dd8f0  key -> name
//   008ddb00  record read helper
//   008ddb90  record read helper
//   008ddc10  EA::ResourceMan::GetNameFromDatabaseKey
//   008ddc80  EA::ResourceMan::DefaultCreateNameFromKey
//   008ddde0  ReadInt32 wrapper
//   008dde10  cEditorResource::_scalar_dtor
//   008dde50  load editor resource
//   008ddf70  editor resource read
//   008ddfb0  cEditorResource::_scalar_deleting_dtor
//   008ddff0  cPropertyList ctor
//
// Callees are declared with their retail addresses; the rel32 call targets are masked during
// comparison, so only call arity / member-vs-free matters.

#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)

extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, const char* file, int line);
extern "C" void* __cdecl operator_new_arr(void* p, int a, int n);          // 0x11e073e
extern "C" void* __cdecl operator_delete__(void* p);                        // 0xf47380
// The global allocator (DAT_016c8b44) is a thiscall object: methods get it in ecx.
struct MemAlloc {
    void  Free(void* p);                            // 0x9276c0
    void* Alloc(int size, int a, int b, int c, int d, int e); // 0x9289f0 LockedAlloc
};
extern void* g_pMemAlloc;                           // 0x16c8b44
extern "C" void* __cdecl FUN_0093bd50(const char* name);                    // 0x93bd50
extern "C" void  __cdecl FUN_0093bb40(int a, float b);                      // 0x93bb40
extern "C" void  __cdecl FUN_0093be30(void* self, void* a, void* b, int c, int d, void* e); // 0x93be30
extern "C" void* __cdecl FUN_0093bde0(void* self);                          // 0x93bde0
extern "C" void* __cdecl FUN_00931da0(void* self, int a);                   // 0x931da0
extern "C" void* __cdecl FUN_00931e70(void* self);                          // 0x931e70 FileStream dtor
extern "C" char  __cdecl FUN_009318f0(void* self, int a, int b, int c, int d); // 0x9318f0 Open
extern "C" void  __cdecl FUN_00931810(void* self, const wchar_t* p);        // 0x931810 SetPath
extern "C" unsigned __cdecl FUN_00931ce0(void* self, void* buf, unsigned n);// 0x931ce0 Read
extern "C" void* __cdecl FUN_00931a70(void* self);                          // 0x931a70 GetStream
extern "C" void* __cdecl FUN_00931b70(void* self);                          // 0x931b70 GetDatabase
extern "C" void* __cdecl FUN_00609d90(void* a, void* b, void* c, void* d);  // 0x609d90 eastl::search
extern "C" int   __cdecl FUN_008d9170(void* a, int b, int c);              // 0x8d9170
extern "C" int   __cdecl FUN_008da920(int a, int b, int c, int d, int e);  // 0x8da920
extern "C" void* __cdecl FUN_008dcbf0(void* self);                          // 0x8dcbf0
extern "C" char FUN_008ddb90(void* self, int a2, int a3, int a4, int a5);  // 0x8ddb90
extern "C" int   __cdecl FUN_008de1a0(void);                                // 0x8de1a0 ObjectError
extern "C" void  __cdecl FUN_0041e050(void* out, const wchar_t* fmt, ...);  // 0x41e050 WStr_Format
extern "C" void  __cdecl FUN_00423650(void* self, const wchar_t* a, const wchar_t* b); // 0x423650 WString_Assign
extern "C" void* __cdecl FUN_006309e0(void* out, const void* a, const void* b); // 0x6309e0 operator+
extern "C" void  __cdecl FUN_00429580(void* self, const wchar_t* a, const wchar_t* b); // 0x429580 WStr::Append
extern "C" char  __cdecl FUN_0093a780(void* a, void* out, int n, void* b);  // 0x93a780
extern "C" void* __cdecl FUN_008d8770(void* self, void* out);               // 0x8d8770 GetKeyListSortedByPosition

extern "C" unsigned __cdecl towlower(unsigned c);
extern "C" int      __cdecl iswctype(unsigned c, unsigned t);
extern "C" void*    __cdecl memmove(void* d, const void* s, unsigned n);

extern void* g_pfn_154c464;
extern void* g_pfn_154c468;

// ---------------------------------------------------------------------------
// 0x8dd0d0  ResourceMan::PFRecordWrite::PFRecordWrite
// ---------------------------------------------------------------------------
struct PFRecordWrite {
    void** vtbl;                 // +0x00
    int    mRefCount;            // +0x04
    int    mField08;             // +0x08
    int    mKey[3];              // +0x0c
    void*  mpDatabase;           // +0x18
    int    mField1c;             // +0x1c
    void** vtbl20;               // +0x20
    char   mMemStream[0x24];     // +0x24 (MemoryStream)
    char   mFileStream[0x22c];   // +0x48 (FileStream)

    void* ctor(int a2, int a3, int a4, void* a5, int a6);   // 0x8dd0d0
    void* _virtual_dtor(int flags);                          // 0x8dd1f0
};

// @ 0x008dd0d0
void* PFRecordWrite::ctor(int a2, int a3, int a4, void* a5, int a6)
{
    vtbl = (void**)0x13effa8;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    vtbl = (void**)0x140a2e0;
    mField08 = (int)0x12e4a892;
    int* k = (int*)a5;
    mKey[0] = k[0];
    mKey[1] = k[1];
    mKey[2] = k[2];
    mpDatabase = (void*)a6;
    mField1c = 3;
    vtbl20 = (void**)0x13f3a68;
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    ((void* (__thiscall*)(void*, void*))FUN_0093bd50)(mMemStream, (void*)0x140a390);
    ((void* (__thiscall*)(void*, int))FUN_00931da0)(mFileStream, 0);
    *((char*)this + 0x274) = 0;
    _InterlockedExchange((volatile long*)((char*)this + 0x278), 1);
    ((void (__thiscall*)(void*))(((void**)*(void**)mMemStream)[1]))(mMemStream);
    ((void (__thiscall*)(void*))(((void**)*(void**)mFileStream)[1]))(mFileStream);
    ((void (__thiscall*)(void*, int, float))FUN_0093bb40)(mMemStream, 1, 1.0f);
    void* db = mpDatabase;
    int u = ((int (__thiscall*)(void*))(((void**)*(void**)db)[0x48 / 4]))(db);
    ((void (__thiscall*)(void*, void*, void*, int, int, void*))FUN_0093be30)(
        mMemStream, (void*)a2, (void*)a3, a4, 1, (void*)u);
    return this;
}

// ---------------------------------------------------------------------------
// 0x8dd1c0  EA::SharedLibrary::Release
// ---------------------------------------------------------------------------
struct SharedLibrary {
    void** vtbl;      // +0x00
    int    mRef;      // +0x04
    int Release();    // 0x8dd1c0
};

// @ 0x008dd1c0
int SharedLibrary::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)((char*)this + 4), -1);
    --n;
    if (n == 0) {
        _InterlockedExchange((volatile long*)((char*)this + 4), 1);
        if (this != 0)
            ((void (__thiscall*)(void*, int))(*(void***)this)[0])(this, 1);
        n = 0;
    }
    return n;
}

// ---------------------------------------------------------------------------
// 0x8dd1f0  PFRecordWrite::_virtual_dtor
// ---------------------------------------------------------------------------
// @ 0x008dd1f0
void* PFRecordWrite::_virtual_dtor(int flags)
{
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    if (mField1c != 0) {
        void* db = mpDatabase;
        ((void (__thiscall*)(void*, void*))(((void**)*(void**)db)[0x3c / 4]))(db, this);
    }
    FUN_008dcbf0(this);
    FUN_00931e70(mFileStream);
    FUN_0093bde0(mMemStream);
    vtbl20 = (void**)0x13f3a68;
    vtbl = (void**)0x13effb8;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x8dd250  EA::ResourceMan::CopyDatabaseRecord
// ---------------------------------------------------------------------------
// EA::ResourceMan support types used by this slice's two Copy functions.
namespace EA { namespace ResourceMan {

class Key {
 public:
    unsigned int mInstance;   // +0x00
    unsigned int mType;       // +0x04
    unsigned int mGroup;      // +0x08
};

// eastl::vector<Key, sp_vector_allocator>: 0x14 bytes.  The original free path
// checks the allocator header word at [mpBegin-1] before freeing.
struct sp_key_vector {
    Key*  mpBegin;     // +0x00
    Key*  mpEnd;       // +0x04
    void* mAlloc;      // +0x08
    Key*  mpEndCap;    // +0x0c
    void* mAllocator;  // +0x10

    Key* begin() const { return mpBegin; }
    Key* end()   const { return mpEnd; }
};

// The record object returned by OpenRecord.  Only the vtable slots this slice
// calls are named; slots in between are placeholders so the offsets line up.
class Record {
 public:
    virtual void v00();                                            // [0x00]
    virtual void v04();                                            // [0x04]
    virtual void Release();                                        // [0x08]
    virtual void v0c();                                            // [0x0c]
    virtual void v10();                                            // [0x10]
    virtual void v14();                                            // [0x14]
    virtual void* GetStream();                                     // [0x18]
    virtual unsigned int GetSize();                                // [0x1c]
    virtual void v20();                                            // [0x20]
    virtual void Unlock();                                         // [0x24]
    virtual void v28();                                            // [0x28]
    virtual void v2c();                                            // [0x2c]
    virtual unsigned int Read(void*, unsigned int);                // [0x30]
    virtual void v34();                                            // [0x34]
    virtual bool ReadInt(int*, unsigned int);                      // [0x38]
    virtual void v3c();                                            // [0x3c]
    virtual bool Close();                                          // [0x40]
};

// Database (a DatabasePackedFile in practice).  Only the vtable slots this
// slice calls are declared, in slot order, so the offsets line up:
//   0x0c GetDatabaseType   0x14 Lock(bool)   0x30 GetKeyList
//   0x34 OpenRecord        0x40 Close
class DatabasePackedFile {
 public:
    virtual void v04();
    virtual void v08();
    virtual unsigned int GetDatabaseType();                        // [0x0c]
    virtual void v10();
    virtual void Lock(bool);                                       // [0x14]
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual unsigned int GetKeyList(sp_key_vector*, void*);        // [0x30]
    virtual bool OpenRecord(Key const&, void*, int, int, int, void*);// [0x34]
    virtual bool v38();
    virtual void v3c();
    virtual bool Close(Key const&);                                // [0x40]

    // Non-virtual members of DatabasePackedFile:
    bool         ReadRecordRaw(Key const&, void*, unsigned int);   // 0x008d9170
    bool         WriteRecordRaw(Key const&, void*, unsigned int, int, int); // 0x008da920
    unsigned int GetKeyListSortedByPosition(sp_key_vector*);       // 0x008d8770
};

// The object OpenRecord writes into the caller's 0x10-byte local.  Only the
// first two dwords are read by this slice.
struct PFRecordInfoOut {
    Record*      mpRecord;        // +0x00
    unsigned int mnSize;          // +0x04
    unsigned int mnPosition;      // +0x08
    unsigned int mnExtra;         // +0x0c
};

}}  // namespace

extern "C" int FUN_008dd250(void* dst, void* src, void* pKey, char a4);

// @ 0x008dd250
extern "C" int FUN_008dd250(void* dst, void* src, void* pKey, char a4)
{
    EA::ResourceMan::DatabasePackedFile* pDst = (EA::ResourceMan::DatabasePackedFile*)dst;
    EA::ResourceMan::DatabasePackedFile* pSrc = (EA::ResourceMan::DatabasePackedFile*)src;
    EA::ResourceMan::Key& key = *(EA::ResourceMan::Key*)pKey;
    EA::ResourceMan::PFRecordInfoOut info;
    char result = 0;
    if (pDst->GetDatabaseType() == 0x2a43bd44 && pSrc->GetDatabaseType() == 0x2a43bd44) {
        if (pSrc->OpenRecord(key, 0, 1, 6, 0, &info)) {
            void* p = ((MemAlloc*)g_pMemAlloc)->Alloc((int)info.mnSize, 0, 0, 0, 0, 0);
            if (pSrc->ReadRecordRaw(key, p, info.mnSize) &&
                pDst->WriteRecordRaw(key, p, info.mnSize, info.mnPosition, info.mnExtra)) {
                if (!a4)
                    pSrc->Close(key);
                result = 1;
            }
            if (p)
                ((MemAlloc*)g_pMemAlloc)->Free(p);
            if (result)
                return result;
        }
    }
    info.mpRecord = 0;
    result = 0;
    if (pSrc->OpenRecord(key, 0, 1, 6, 1, &info)) {
        EA::ResourceMan::Record* rec = info.mpRecord;
        unsigned int n = rec->GetSize();
        void* p = ((MemAlloc*)g_pMemAlloc)->Alloc((int)n, 0, 0, 0, 0, 0);
        if (n == rec->Read(p, n))
            result = (char)FUN_008ddb90((void*)&key, (int)rec, (int)p, (int)n, 1);
        if (p)
            ((MemAlloc*)g_pMemAlloc)->Free(p);
        rec->Unlock();
    }
    if (info.mpRecord)
        info.mpRecord->Release();
    if (result && a4)
        pDst->Close(key);
    if (info.mpRecord)
        info.mpRecord->Release();
    return result;
}

// ---------------------------------------------------------------------------
// 0x8dd430  EA::ResourceMan::CopyDatabaseRecords
// ---------------------------------------------------------------------------
// @ 0x008dd430
extern "C" unsigned FUN_008dd430(EA::ResourceMan::DatabasePackedFile* pDst,
                                 EA::ResourceMan::DatabasePackedFile* pSrc,
                                 void* pFilter, char a4)
{
    unsigned int nCopied = 0;
    pDst->Lock(true);
    pSrc->Lock(true);
    EA::ResourceMan::sp_key_vector keys;
    keys.mpBegin = 0;
    keys.mpEnd = 0;
    keys.mAlloc = 0;
    keys.mpEndCap = 0;
    keys.mAllocator = 0;
    if (pSrc->GetDatabaseType() == 0x2a43bd44)
        pSrc->GetKeyListSortedByPosition(&keys);
    else
        pSrc->GetKeyList(&keys, pFilter);
    for (EA::ResourceMan::Key* it = keys.begin(); it != keys.end(); ++it) {
        if (FUN_008dd250(pDst, pSrc, it, a4))
            ++nCopied;
    }
    pSrc->Lock(false);
    pDst->Lock(false);
    if (keys.mpBegin != 0 && *((int*)keys.mpBegin - 1) != 0)
        operator_delete__(keys.mpBegin);
    return nCopied;
}

// ---------------------------------------------------------------------------
// 0x8dd510  Resource::FindEmbeddedPackageHeader
// ---------------------------------------------------------------------------
// @ 0x008dd510
extern "C" int FUN_008dd510(const wchar_t* path)
{
    char fs[0x22c];
    FUN_00931da0(fs, 0);
    FUN_00931810(fs, path);
    if (!FUN_009318f0(fs, 1, 6, 1, 0)) {
        FUN_00931e70(fs);
        return -1;
    }
    unsigned total = (unsigned)FUN_00931b70(fs);
    unsigned* buf = (unsigned*)operator_new(0x201, "EASTL", 0, 0, "", 0xd1);
    operator_new_arr(buf, 0, 0x200);
    *((char*)buf + 0x200) = 0;
    unsigned char* pat = (unsigned char*)operator_new(0x11, "EASTL", 0, 0, "", 0xd1);
    pat[0] = 0x7f; pat[1] = 0x9d; pat[2] = 0x88; pat[3] = 0xec;
    pat[4] = 0x8f; pat[5] = 0x24; pat[6] = 3;   pat[7] = 0x6c;
    pat[8] = 0xc9; pat[9] = 0xa6; pat[10] = 0x31; pat[11] = 0x56;
    pat[12] = 0x5b; pat[13] = 0xcf; pat[14] = 0x77; pat[15] = 0x20;
    pat[16] = 0;
    pat[0] = (unsigned char)~pat[0];
    int found = -1;
    unsigned filled = 0;
    if (total != 0) {
        unsigned patLen = (unsigned)(pat + 0x10 - pat);
        do {
            unsigned got = FUN_00931ce0(fs, (char*)buf + filled, 0x200 - filled);
            unsigned r = FUN_00609d90(buf, buf + 0x80, pat, pat + patLen) == buf + 0x80
                             ? (unsigned)((char*)buf + patLen - (char*)buf)
                             : 0xffffffff;
            if (r != 0xffffffff) {
                found = got - 0x10 < r ? -1 : (int)(r + 0x10 + filled);
                break;
            }
            memmove(buf, (char*)buf + 0x1f1, 0xf);
            filled += 0x1f1;
            if (filled >= total)
                break;
        } while (true);
    }
    FUN_00931a70(fs);
    operator_delete__(pat);
    if (buf != 0)
        operator_delete__(buf);
    FUN_00931e70(fs);
    return found;
}

// ---------------------------------------------------------------------------
// 0x8dd7d0  FNV-1a hash of a lowercase wide string
// ---------------------------------------------------------------------------
// @ 0x008dd7d0
extern "C" unsigned FUN_008dd7d0(const unsigned short* s, int count)
{
    unsigned h = 0x811c9dc5;
    while (count != 0) {
        --count;
        unsigned c = (unsigned short)towlower(*s);
        h = h * 0x1000193 ^ c;
        ++s;
    }
    return h;
}

// ---------------------------------------------------------------------------
// 0x8dd820  parse a fixed-width hex token
// ---------------------------------------------------------------------------
// @ 0x008dd820
extern "C" unsigned short* FUN_008dd820(unsigned short* p, unsigned short* end, char a3, char a4)
{
    unsigned short* start = p;
    if (a3 != 0) {
        for (; p != end; ++p)
            if (*p == 0x5f)
                start = p + 1;
    }
    if ((int)((end - start) & 0xfffffffe) < 0x10)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58))
        start += 2;
    else if (!iswctype(*start, 4))
        return 0;
    int n = 0;
    unsigned short* q = start;
    if (start != end) {
        do { if (!iswctype(*q, 0x80)) return 0; ++q; ++n; } while (q != end);
        if (n == 8 || (n == 0x10 && a4))
            return start;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x8dd8d0  set name-from-key hooks
// ---------------------------------------------------------------------------
// @ 0x008dd8d0
extern "C" void FUN_008dd8d0(void* a, void* b)
{
    g_pfn_154c464 = a;
    g_pfn_154c468 = b;
}

// ---------------------------------------------------------------------------
// 0x8dd8f0  key -> name
// ---------------------------------------------------------------------------
// wcslen is inlined by the original; declare it as an intrinsic.
extern "C" unsigned int __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)
extern "C" __declspec(dllimport) wchar_t* __cdecl wcschr(const wchar_t*, wchar_t);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern "C" void* __cdecl FUN_00422950(int holder);                 // 0x422950 QueryByHolder

// @ 0x008dd8f0
extern "C" bool FUN_008dd8f0(EA::ResourceMan::Key* pKey, const wchar_t* name,
                             unsigned int a3, unsigned int a4,
                             void* pManager, int* pHolder)
{
    if (name == 0 || name[0] == 0)
        return false;
    pKey->mType = a3;
    const wchar_t* pDot = 0;
    const wchar_t* p = wcschr(name, L'.');
    if (p != 0)
        pDot = p + 1;
    else
        p = name + wcslen(name);

    // Split [name, p) at the first '!' into group (before) and instance (after).
    const wchar_t* segStart = name;      // ebp
    const wchar_t* groupEnd = name;      // ebx
    unsigned int n = (unsigned int)(p - name);
    const wchar_t* q = name;
    while (n != 0) {
        if (*q == L'!') {
            groupEnd = q;
            segStart = q + 1;
            pKey->mGroup = 0xffffffff;
            break;
        }
        ++q;
        --n;
    }
    if (groupEnd == name && segStart == name)
        pKey->mGroup = a4;               // no '!' found

    // Instance: the part after the '!' (or the whole prefix) up to the dot.
    if (segStart != p) {
        const wchar_t* r = (const wchar_t*)FUN_008dd820((unsigned short*)segStart, (unsigned short*)p, 1, 1);
        if (r != 0)
            pKey->mInstance = wcstoul(r, 0, 0x10);
        else
            pKey->mInstance = FUN_008dd7d0((const unsigned short*)segStart, (int)(p - segStart));
    } else {
        pKey->mInstance = 0xffffffff;
    }

    // Group: [name, groupEnd).
    if (name != groupEnd) {
        const wchar_t* r = (const wchar_t*)FUN_008dd820((unsigned short*)name, (unsigned short*)groupEnd, 1, 0);
        if (r != 0)
            pKey->mGroup = wcstoul(r, 0, 0x10);
        else
            pKey->mGroup = FUN_008dd7d0((const unsigned short*)name, (int)(groupEnd - name));
    }

    // Type: the segment after the dot, only when not already supplied.
    if (pKey->mType == 0) {
        pKey->mType = 0xffffffff;
        if (pDot != 0 && pDot[0] != 0) {
            const wchar_t* e = pDot + wcslen(pDot);
            const wchar_t* r = (const wchar_t*)FUN_008dd820((unsigned short*)pDot, (unsigned short*)e, 0, 0);
            if (r != 0) {
                pKey->mType = wcstoul(r, 0, 0x10);
                return true;
            }
            if (pHolder != 0) {
                void* m = FUN_00422950((int)pHolder);
                if (m != 0) {
                    unsigned int v = ((unsigned int (__thiscall*)(void*, const wchar_t*))
                                      (((void**)*(void**)m)[0x5c / 4]))(m, pDot);
                    if (v != 0xffffffff) {
                        pKey->mType = v;
                        return true;
                    }
                }
            }
            if (pManager == 0)
                pManager = (void*)FUN_008de1a0();
            if (pManager != 0) {
                unsigned int v = ((unsigned int (__thiscall*)(void*, const wchar_t*))
                                  (((void**)*(void**)pManager)[0x88 / 4]))(pManager, pDot);
                if (v != 0xffffffff) {
                    pKey->mType = v;
                    return true;
                }
            }
            pKey->mType = FUN_008dd7d0((const unsigned short*)pDot, (int)(e - pDot));
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x8ddb00  record read helper
// ---------------------------------------------------------------------------
// @ 0x008ddb00
extern "C" unsigned FUN_008ddb00(void* self, int a2, int a3, int a4, int a5, int a6)
{
    void* io = 0;
    int r = ((char (__thiscall*)(void*, int, void**, int, int, int, int))
             (((void**)*(void**)self)[0x34 / 4]))(self, a2, &io, 1, 3, a5, a6);
    unsigned result = 0;
    if (r) {
        void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)io)[0x18 / 4]))(io);
        if (s != 0) {
            unsigned avail = ((unsigned (__thiscall*)(void*))(((void**)*(void**)s)[0x1c / 4]))(s);
            if (a4 < (int)avail)
                avail = (unsigned)a4;
            result = ((unsigned (__thiscall*)(void*, int, unsigned))(((void**)*(void**)s)[0x30 / 4]))(s, a6, avail);
            ((void (__thiscall*)(void*))(((void**)*(void**)io)[0x24 / 4]))(io);
        }
    }
    if (io != 0)
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[8 / 4]))(io);
    return result;
}

// ---------------------------------------------------------------------------
// 0x8ddb90  record read helper
// ---------------------------------------------------------------------------
// @ 0x008ddb90
extern "C" char FUN_008ddb90(void* self, int a2, int a3, int a4, int a5)
{
    void* io = 0;
    char result = 0;
    int r = ((char (__thiscall*)(void*, int, void**, int, int, int, int))
             (((void**)*(void**)self)[0x34 / 4]))(self, a2, &io, 2, 2, a5, 0);
    if (r) {
        void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)io)[0x18 / 4]))(io);
        if (s != 0)
            result = ((char (__thiscall*)(void*, int, int))(((void**)*(void**)s)[0x38 / 4]))(s, a3, a4);
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[0x24 / 4]))(io);
    }
    if (io != 0)
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[8 / 4]))(io);
    return result;
}

// ---------------------------------------------------------------------------
// 0x8ddc10  EA::ResourceMan::GetNameFromDatabaseKey
// ---------------------------------------------------------------------------
// @ 0x008ddc10
struct Str { void append(const wchar_t* s); };

extern "C" char FUN_008ddc10(int a1, void* out, void* pKey)
{
    wchar_t buf[0x104];
    if (pKey == 0)
        return 0;
    if (((int (__thiscall*)(void*))(((void**)*(void**)pKey)[0x0c / 4]))(pKey) != 0x34728492)
        return 0;
    if (!((char (__thiscall*)(void*, int, void*))(((void**)*(void**)pKey)[0x64 / 4]))(pKey, a1, buf))
        return 0;
    ((Str*)out)->append(buf);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x8ddc80  EA::ResourceMan::DefaultCreateNameFromKey
// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator>: 0x14 bytes here.
struct WStr16 {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpEndCap;   // +0x08
    void*    mpAlloc;    // +0x0c
    void*    mpAllocator;// +0x10
    void assign(const wchar_t* first, const wchar_t* last);  // 0x423650
    void append(const wchar_t* first, const wchar_t* last);  // 0x429580
};

extern wchar_t gEmptyString16;                     // 0x1667bac (sentinel)
extern const wchar_t g_nameSepUnderscore;          // 0x13fe614 (L"_")

// @ 0x008ddc80
extern "C" void FUN_008ddc80(const EA::ResourceMan::Key* pKey, WStr16* pOut,
                             void* pManager, void* pDatabase, const wchar_t* pName)
{
    unsigned int id = 0;
    if (pDatabase != 0 &&
        ((unsigned int (__thiscall*)(void*))(((void**)*(void**)pDatabase)[0x0c / 4]))(pDatabase) == 0x34728492) {
        id = ((unsigned int (__thiscall*)(void*, unsigned int))
              (((void**)*(void**)pDatabase)[0x60 / 4]))(pDatabase, pKey->mType);
    } else {
        if (pManager == 0)
            pManager = (void*)FUN_008de1a0();
        if (pManager != 0)
            id = ((unsigned int (__thiscall*)(void*, unsigned int))
                  (((void**)*(void**)pManager)[0x8c / 4]))(pManager, pKey->mType);
    }

    WStr16 tmp;
    tmp.mpBegin = &gEmptyString16;
    tmp.mpEnd = &gEmptyString16;
    tmp.mpEndCap = &gEmptyString16 + 1;
    tmp.mpAlloc = 0;
    tmp.mpAllocator = 0;
    if (id != 0)
        FUN_0041e050(&tmp, L"0x%08x!0x%08x.%ls", pKey->mGroup, pKey->mInstance, id);
    else
        FUN_0041e050(&tmp, L"0x%08x!0x%08x.0x%08x", pKey->mGroup, pKey->mInstance, pKey->mType);

    if (pName != 0) {
        const wchar_t* e = pName + wcslen(pName);
        pOut->assign(pName, e);
        WStr16 cat;
        cat.mpBegin = &gEmptyString16;
        cat.mpEnd = &gEmptyString16;
        cat.mpEndCap = &gEmptyString16 + 1;
        cat.mpAlloc = 0;
        cat.mpAllocator = 0;
        FUN_006309e0(&cat, (const void*)&g_nameSepUnderscore, (const void*)&tmp);
        pOut->append(cat.mpBegin, cat.mpEnd);
        if ((unsigned int)((char*)cat.mpEndCap - (char*)cat.mpBegin) > 2 && cat.mpBegin != 0)
            operator_delete__(cat.mpBegin);
    } else {
        if (&tmp != pOut)
            pOut->assign(tmp.mpBegin, tmp.mpEnd);
    }
    if ((unsigned int)((char*)tmp.mpEndCap - (char*)tmp.mpBegin) > 2 && tmp.mpBegin != 0)
        operator_delete__(tmp.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x8ddde0  ReadInt32 wrapper
// ---------------------------------------------------------------------------
// @ 0x008ddde0
extern "C" int FUN_008ddde0(void* a1, void* a2)
{
    int local;
    if (FUN_0093a780(a1, &local, 1, a2))
        return local;
    return -1;
}

// ---------------------------------------------------------------------------
// 0x8dde10  cEditorResource::_scalar_dtor
// ---------------------------------------------------------------------------
struct EditorResource {
    void** vtbl;        // +0x00
    char   d[0x10];     // +0x04
    void*  mpData;      // +0x14
    int    mSize;       // +0x18
    void   dtor();      // 0x8dde10
    void*  deleting_dtor(int flags); // 0x8ddfb0
};

// @ 0x008dde10
void EditorResource::dtor()
{
    void* p = mpData;
    vtbl = (void**)0x1436a00;
    if (p != 0)
        ((MemAlloc*)g_pMemAlloc)->Free(p);
    vtbl = (void**)0x13eb938;
}

// ---------------------------------------------------------------------------
// 0x8dde50  load editor resource
// ---------------------------------------------------------------------------
// @ 0x008dde50
extern "C" char __stdcall FUN_008dde50(void* self, EditorResource* dst, char* a3, int unused)
{
    char result = 0;
    if (self == 0 || dst == 0)
        return 0;
    void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)self)[0x18 / 4]))(self);
    if (s == 0)
        return 0;
    char flag = a3 != 0 ? *a3 : 0;
    unsigned size = ((unsigned (__thiscall*)(void*))(((void**)*(void**)s)[0x1c / 4]))(s);
    size -= (unsigned)(-(int)(flag != 0) & 4);
    void* info = ((void* (__thiscall*)(void*))(((void**)*(void**)self)[0x10 / 4]))(self);
    unsigned* iv = (unsigned*)info;
    dst->d[0x04] = 0;
    *(unsigned*)((char*)dst + 8) = iv[0];
    *(unsigned*)((char*)dst + 0xc) = iv[1];
    *(unsigned*)((char*)dst + 0x10) = iv[2];
    if (dst->mpData != 0)
        ((MemAlloc*)g_pMemAlloc)->Free(dst->mpData);
    dst->mpData = (void*)((MemAlloc*)g_pMemAlloc)->Alloc((int)size, 0, 0, 0, 0, 0);
    if (dst->mpData != 0 && (flag == 0 || FUN_008ddde0(s, 0) != -1)) {
        unsigned got = ((unsigned (__thiscall*)(void*, void*, unsigned))(((void**)*(void**)s)[0x30 / 4]))(s, dst->mpData, size);
        if (got == size) {
            dst->mSize = (int)got;
            result = 1;
        } else {
            ((MemAlloc*)g_pMemAlloc)->Free(dst->mpData);
            dst->mpData = 0;
        }
    }
    dst->mSize = -(int)(dst->mpData != 0) & (int)size;
    return result;
}

// ---------------------------------------------------------------------------
// 0x8ddf70  editor resource read
// ---------------------------------------------------------------------------
// @ 0x008ddf70
extern "C" char __stdcall FUN_008ddf70(int self, void* other, int a3, int a4)
{
    char result = 0;
    void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)other)[0x18 / 4]))(other);
    if (s != 0) {
        int v = *(int*)(self + 0x14);
        if (v != 0)
            result = ((char (__thiscall*)(void*, int, int))(((void**)*(void**)s)[0x38 / 4]))(
                s, v, *(int*)(self + 0x18));
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x8ddfb0  cEditorResource::_scalar_deleting_dtor
// ---------------------------------------------------------------------------
// @ 0x008ddfb0
void* EditorResource::deleting_dtor(int flags)
{
    void* p = mpData;
    vtbl = (void**)0x1436a00;
    if (p != 0)
        ((MemAlloc*)g_pMemAlloc)->Free(p);
    vtbl = (void**)0x13eb938;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x8ddff0  Editor::cPropertyList ctor
// ---------------------------------------------------------------------------
struct PropertyList {
    PropertyList* ctor();      // 0x8ddff0
};

// @ 0x008ddff0
PropertyList* PropertyList::ctor()
{
    char* p = (char*)this;
    *(void**)p = (void*)0x13ebcdc;
    _InterlockedExchange((volatile long*)(p + 4), 0);
    *(int*)(p + 8) = 0;
    *(int*)(p + 0xc) = 0;
    *(int*)(p + 0x10) = 0;
    *(void**)p = (void*)0x1436a00;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    return this;
}
