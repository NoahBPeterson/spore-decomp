// src/game/UTFSpore_Win32/EAInifile.cpp -- migrated from slice(s) s009350f0, s00934260, s00933320, s009323c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAInifile.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/IStream.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern void FreeMem(void*);

// ---- items of slice s009323c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern void FreeMem(void*);
int __cdecl DetectEncoding(const void*, unsigned, int, int);
namespace EA {
namespace IO {
bool FileExists(const wchar_t* path);
}
}
namespace EA {
namespace Thread {
void ThreadSleep(uint32_t* ms);
}
}
struct IStream_s0093_23c0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual uint32_t s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual uint32_t s9(int);
    virtual void s10(int, int);
    virtual void s11();
    virtual uint32_t s12(void*, unsigned int);
    virtual void s13();
    virtual void s14();
    virtual void s15(const wchar_t*);
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual bool s19(unsigned int, int, int, int);
};
class EA_IO_IniFile {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual uint32_t v19();

    wchar_t  mPath[260];         // +0x004
    char     mFileStream[0x22c]; // +0x20c
    void*    mpStream;           // +0x438
    uint32_t m43c;               // +0x43c
    uint8_t  m440;               // +0x440
    uint8_t  m441;               // +0x441
    uint8_t  m442;               // +0x442
    uint8_t  m443;               // +0x443
    char     m444[0x1c];         // +0x444
    char     m460[0x1c];         // +0x460

    int GetOption(int option);
    void SetOption(int option, int value);
    bool SetPath(const wchar_t* path);
    bool SetStream(void* stream);
    bool Open(uint32_t flags);
    int  GetEncoding();
};
class StackArrayChar256 {
public:
    char  mBuf[0x100];   // +0x000
    char* mpData;        // +0x100
    char* mpEnd;         // +0x104
    int   mnSize;        // +0x108
    char* Init(char* p, int n);
};
// ---- items of slice s009323c0 end

// ---- items of slice s00933320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new_ea(unsigned, const char*, int, int, const char*, int);
extern "C" wchar_t* __cdecl wcsncpy_f(wchar_t*, const wchar_t*, unsigned);
extern "C" unsigned Vsnprintf16(wchar_t*, unsigned, const wchar_t*, void*);
extern "C" int EA_Text_ConvertBinaryDataToASCIIArray(void*, unsigned, void*);
extern "C" int EA_Text_GetCharacterSize(int);
extern "C" void EA_Text_ConvertEncoding(void*, int, int, void*, int*, int);
extern "C" void WString_copy(void*, const void*, unsigned);
extern "C" int Vsscanf16(void*, void*, void*);
extern "C" int  EA_Text_ConvertEncoding8(void*, int, int, void*);
extern "C" void CharString_append(void*, const char*, const char*);
extern "C" int  WString_compare(const void*, const void*);
extern "C" void* RBTreeInsert(void*, void*, void*, int);
extern "C" void* RbtreeFind(void* tree, const void* key);
typedef unsigned short char16_t;
char gEmptyString16;
char gEmptyString16B;
void* operator new[](unsigned, const char*, int, int, int, int);
void  operator delete[](void*);
template <typename T, int N>
struct StackArray {
    T mData[N];
    T* mpData;
    T* mpDataEnd;
    unsigned mCapacity;
    void Resize(unsigned n);
};
template struct StackArray<wchar_t, 256>;
struct WString {
    char16_t* mpBegin;      // +0x00
    char16_t* mpEnd;        // +0x04
    char16_t* mpCapacity;   // +0x08
    void*     mpAlloc;      // +0x0c
    void DeallocateSelf();
    WString* Assign(const WString& s);
    void Reset();
};
template struct StackArray<char, 256>;
struct IniFile {
    void*   vtbl;           // +0x000
    char    pad[0x434];     // +0x004
    void*   mpEncodingSrc;  // +0x438
    int     mEncoding;      // +0x43c
    char    m_b440;         // +0x440
    char    m_b441;         // +0x441
    char    m_b442;         // +0x442
    char    m_b443;         // +0x443
    void*   mpTree;         // +0x444
    void*   mpTreeEnd;      // +0x448

    void* V(int off) const { return ((void**)vtbl)[off / 4]; }

    int   ReadEntryRaw(void* a, wchar_t* b);
    bool  WriteEntryFormatted(void* a, unsigned n, void* args);
    int   ReadBinary(void* a, void* b);
    bool  WriteBinary(void* a, unsigned n, void* b);
    bool  ConvertAndWriteStream(void* a, int n);
    bool  GetFileLine(WString* out);
    bool  GetFileLine8To8(WString* out);
    bool  GetFileLine16To16(WString* out);
    int   ReadEntry(void* a, void* b, WString* c);
    bool  SectionExists(wchar_t* name);
};
extern "C" int WStr_AllocateSelf(WString*, int);
extern "C" void WString_RangeInitialize(WString*, const wchar_t*);
extern "C" int  WString_makeLower(WString*);
extern "C" void WString_AssignRange(WString*, const char16_t*, const char16_t*);
extern "C" void WStr_Append(WString*, const char16_t*, const char16_t*);
// ---- items of slice s00933320 end

// ---- items of slice s009350f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" unsigned __int64 __rdtsc(void);
extern "C" void __cdecl EASTL_allocator_deallocate(void* p);     // 0x00f47380
extern void* IniFile_vtable;   // 0x0143e7d8
#pragma intrinsic(_InterlockedExchange, _InterlockedDecrement, _InterlockedIncrement, _InterlockedExchangeAdd)
#pragma intrinsic(__rdtsc)
struct FileStreamStub { void ctor(int a); void dtor(); };
struct RBTreeStub {
    void* m0;             // +0x00 (empty compare)
    void* mpNodeRight;    // +0x04
    void* mpNodeLeft;     // +0x08
    void* mpNodeParent;   // +0x0c
    void DoNukeSubtree(void* root);
};
class EA_IO_IniFile_s0093_50f0 {
public:
    EA_IO_IniFile_s0093_50f0* ctor(int path, uint8_t flag);
    EA_IO_IniFile_s0093_50f0* scalar_deleting_destructor(uint8_t flag);
    bool     SetPath(const wchar_t* path);   // 0x00933040
    void*    vftable;             // +0x000
    wchar_t  mPath[260];          // +0x004
    char     mFileStream[0x22c];  // +0x20c
    void*    mpStream;            // +0x438
    uint32_t mEncodingSrc;        // +0x43c
    uint8_t  m440;                // +0x440
    uint8_t  m441;                // +0x441
    uint8_t  m442;                // +0x442
    uint8_t  m443;                // +0x443
    char     mMapPos[0x1c];       // +0x444
    char     mMapName[0x1c];      // +0x460
};
// ---- items of slice s009350f0 end

// ---- items of slice s00934260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];   // 0x01667bac
struct Alloc { };                 // eastl::allocator (empty tag, passed by reference)
struct WString_s0093_4260 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    WString_s0093_4260() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    WString_s0093_4260(const wchar_t* p, const Alloc& a);        // 0x0041df50
    ~WString_s0093_4260() { DeallocateSelf(); }
    void DeallocateSelf();                            // 0x00933960
    void make_lower();                                // 0x005e8e80
    void ltrim();                                     // 0x00554170
    void rtrim();                                     // 0x005541e0
    void trim();                                      // 0x0057eda0
    unsigned find(wchar_t c, unsigned pos);           // 0x004f6ab0
    void append(const WString_s0093_4260& s, unsigned pos, unsigned n);   // 0x006ab800
    void erase(unsigned pos, unsigned n);             // 0x004228e0
    void assign(const wchar_t* begin, const wchar_t* end);     // 0x00423650
    void AllocateSelf(int n);                         // 0x00429760
    int length() const { return (int)(mpEnd - mpBegin); }
};
__forceinline void* operator new(unsigned, void* p) { return p; }  // placement new
struct PairStr;
PairStr* __cdecl uninitialized_move(PairStr* first, PairStr* last, PairStr* dest);  // 0x00933a50
PairStr* __cdecl move_commit(PairStr* first, PairStr* last, PairStr* dest);         // 0x00933a90
PairStr* __cdecl copy_backward(PairStr* first, PairStr* last, PairStr* dest);       // 0x00933b00
struct PairVec {                                  // eastl::vector<PairStr>
    PairStr* mpBegin;                             // +0x00
    PairStr* mpEnd;                               // +0x04
    PairStr* mpCapacity;                          // +0x08
    void insert(PairStr* position, const PairStr& value);   // 0x00934ef0
};
struct PairPos {                                  // pair<WString, long>
    WString_s0093_4260 first; long second;
    PairPos(const WString_s0093_4260& a, const long& b);     // 0x008d6580
    ~PairPos() { first.DeallocateSelf(); }
};
struct PairStr {                                  // pair<const WString, WString>
    WString_s0093_4260 first; WString_s0093_4260 second;
    PairStr(const WString_s0093_4260& a, const WString_s0093_4260& b);  // 0x0088c0d0
    PairStr(const PairStr& o);                    // 0x00614990
    ~PairStr();                                   // 0x00614c00
};
struct Node { char pad[0x20]; long value; };
struct Iter {
    Node* p;
    Iter() {}
    Iter(const Iter& o) { p = o.p; }
};
struct InsRes {
    Node* p; bool inserted;
    InsRes() {}
    InsRes(const InsRes& o) { p = o.p; inserted = o.inserted; }
};
struct MapNode {                                  // eastl::map<WString,long> rbtree node
    MapNode* mpLeft;                              // +0x00
    MapNode* mpRight;                             // +0x04
    MapNode* mpParent;                            // +0x08
    uint32_t mColor;                              // +0x0c
    WString_s0093_4260  mKey;                                // +0x10
    long     mValue;                              // +0x20
};
struct PosMap {                                   // eastl::map<WString,long>, 0x1c bytes
    uint32_t mPad00;                              // +0x00
    MapNode* mpAnchorSelf;                        // +0x04
    MapNode* mpAnchorParent;                      // +0x08
    MapNode* mpRoot;                              // +0x0c
    uint8_t  mColor;                              // +0x10
    char     mPad11[3];                           // +0x11
    uint32_t mSize;                               // +0x14
    uint32_t mPad18;                              // +0x18
    Iter   find(const WString_s0093_4260& k);                // 0x005e96f0
    InsRes insert(const PairPos& v);              // 0x00934390
    char*  end() { return (char*)&mpAnchorSelf; }
    void   DoNukeSubtree(MapNode* node);          // 0x00934460
};
struct NameNode {                                // eastl::map<WString,WString> rbtree node
    NameNode* mpLeft;                             // +0x00
    NameNode* mpRight;                            // +0x04
    NameNode* mpParent;                           // +0x08
    uint32_t  mColor;                             // +0x0c
    WString_s0093_4260   mKey;                               // +0x10
    WString_s0093_4260   mValue;                             // +0x20
};
struct NameIter { NameNode* p; };
struct NameMap {                                  // eastl::map<WString,WString>
    uint32_t mPad00[3];                           // +0x00
    NameNode* mpRoot;                             // +0x0c
    uint32_t mPad10[3];                           // +0x10
    InsRes insert(const PairStr& v);              // 0x00615050
    NameIter find(const WString_s0093_4260& k);              // 0x005e96f0
    void   DoNukeSubtree(NameNode* node);         // 0x00615110
    char*  end() { return (char*)&mPad00[1]; }
};
struct ListNode {                                 // eastl::list<WString> node
    ListNode* mpNext;                             // +0x00
    ListNode* mpPrev;                             // +0x04
    WString_s0093_4260   mValue;                             // +0x08
};
struct ListAnchor {
    ListNode* mpNext;                             // +0x00
    ListNode* mpPrev;                             // +0x04
    void Clear();                                 // 0x0091a750
};
MapNode* __cdecl RBTreeIncrement(MapNode* node);  // 0x00921580
struct IStream {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual int  GetAccessFlags();                // +0x10
    virtual int  GetState();                      // +0x14
    virtual void Open();                          // +0x18
    virtual unsigned Size();                      // +0x1c
    virtual void SetSize(unsigned n);             // +0x20
    virtual int  GetPosition(int type);           // +0x24
    virtual bool SetPosition(int pos, int type);  // +0x28
    virtual int  s11();                           // +0x2c
    virtual int  Read(void* buf, unsigned n);     // +0x30
    virtual int  s13();                           // +0x34
    virtual bool Write(const void* buf, unsigned n);  // +0x38
};
struct FileStream : IStream {
    char mData[0x22c - 4];                        // +0x004 .. +0x22b
    void Dtor();                                  // 0x00931e70
};
struct VTableHeader { void* mpVTable; };          // object header slot at +0x00
typedef bool (__cdecl *SectionCallback)(const wchar_t* name, uint32_t* reserved, void* param);
class IniFile_s0093_4260 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool Close();                         // +0x1c 0x00935080
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual bool OpenForWrite(int mode);          // +0x48
    virtual void v19();
    virtual bool CacheSections(int mode);         // +0x50
virtual void v21();
virtual void v22();
    virtual bool GetFileLine(WString_s0093_4260* out);       // +0x5c 0x00933980
    virtual void WriteString(const wchar_t* s, int n);   // +0x60
    ~IniFile_s0093_4260();                                    // 0x00935040

    wchar_t  mPath[260];                          // +0x004
    FileStream mFileStream;                       // +0x20c
    IStream* mpStream;                            // +0x438
    int      mEncoding;                           // +0x43c
    bool     mbFileIsOpenForWriting;              // +0x440
    bool     mbLeaveFileOpen;                     // +0x441
    bool     mbReadEntryCacheReady;               // +0x442
    char     pad443;
    PosMap   mSectionPositionMap;                 // +0x444
    NameMap  mSectionNameMap;                     // +0x460

    bool WriteEntry(const wchar_t* pSection, const wchar_t* pKey, const wchar_t* pValue);  // 0x009344b0 (IniFile::WriteEntry)
    int  EnumerateSections(SectionCallback callback, void* param);   // 0x00934d00
};
struct ArrayCookie { uint32_t mSize; };           // operator new[] cookie before the payload
// ---- items of slice s00934260 end

// @ 0x00932ff0
int EA_IO_IniFile::GetOption(int option)
{
    int b = 0;
    if (option == 1)
        b = m441 != 0;
    return b;
}

// @ 0x00933010
void EA_IO_IniFile::SetOption(int option, int value)
{
    if (option == 1) {
        bool b = value != 0;
        if (m441 != b) {
            m441 = b;
            if (!b)
                v7();
        }
    }
}

// @ 0x00933040
bool EA_IO_IniFile::SetPath(const wchar_t* path)
{
    if (path != 0 && *path != 0) {
        if (m442 == 0)
            mpStream = 0;
        if (mpStream == 0) {
            const wchar_t* s = path;
            wchar_t* d = mPath;
            while ((*d++ = *s++) != 0)
                ;
            ((IStream_s0093_23c0*)(void*)mFileStream)->s15(path);
            mpStream = mFileStream;
            return true;
        }
    }
    return false;
}

// @ 0x009330c0
bool EA_IO_IniFile::SetStream(void* stream)
{
    if (stream != 0 && m442 == 0 && mpStream != 0) {
        ((IStream_s0093_23c0*)mpStream)->s6();
        mpStream = 0;
    }
    if (mpStream == 0) {
        mpStream = stream;
        mPath[0] = 0;
        return true;
    }
    return false;
}

// @ 0x00933120
bool EA_IO_IniFile::Open(uint32_t flags)
{
    if (mpStream == 0)
        return false;
    uint32_t access = flags;
    if (flags & 2)
        access |= 1;
    if (((IStream_s0093_23c0*)mpStream)->s4() == access) {
        m440 = (uint8_t)((access >> 1) & 1);
    } else {
        if ((void*)((char*)this + 0x20c) != mpStream)
            return false;
        __int64 start = _time64(0) + 3;
        for (;;) {
            __int64 now = _time64(0);
            if (now >= start)
                return false;
            uint32_t ms = 250;
            EA::Thread::ThreadSleep(&ms);
            if (((IStream_s0093_23c0*)mpStream)->s19(access, (flags & 2) ? 3 : 2,
                                          ~(access >> 1) & 1, 0)) {
                m440 = (uint8_t)((access >> 1) & 1);
                break;
            }
            if (!EA::IO::FileExists(mPath))
                return false;
        }
    }
    m43c = v19();
    return true;
}

// @ 0x00933250
int EA_IO_IniFile::GetEncoding()
{
    uint8_t buf[0x80];
    int enc = 8;
    int saved = ((IStream_s0093_23c0*)mpStream)->s9(0);
    uint32_t n = ((IStream_s0093_23c0*)mpStream)->s12(buf, 0x80);
    if (n != 0xffffffff && n >= 2)
        enc = DetectEncoding(buf, n, 0, 0);
    ((IStream_s0093_23c0*)mpStream)->s10(saved, 0);
    return enc;
}

// @ 0x009332d0
char* StackArrayChar256::Init(char* p, int n)
{
    char* old = mpData;
    if (old == p)
        return old;
    if (p == 0)
        return old;
    if (n == 0)
        return old;
    if (old != (char*)this && mpEnd != old) {
        FreeMem(old);
        mpData = (char*)this;
    }
    mpData = p;
    mnSize = n;
    return p;
}

// @ 0x00933320
template <typename T, int N> void StackArray<T, N>::Resize(unsigned n)
{
    T* old = mpData;
    if (n > mCapacity) {
        if (old != mData && mpDataEnd != old) {
            operator delete[](old);
            mpData = mData;
        }
        mpData = new ("EAIniFile", 0, 0, 0, 0) T[n];
        mCapacity = n;
    }
}

// @ 0x009333f0
bool IniFile::WriteEntryFormatted(void* a, unsigned n, void* args)
{
    StackArray<wchar_t, 256> buf;
    buf.mpData = buf.mData;
    buf.mpDataEnd = 0;
    buf.mCapacity = 0x100;
    unsigned len = Vsnprintf16(buf.mpData, 0x100, (const wchar_t*)a, args);
    if (len > buf.mCapacity) {
        buf.Resize(len);
        Vsnprintf16(buf.mpData, buf.mCapacity, (const wchar_t*)a, args);
    }
    bool r = ((bool(__fastcall*)(void*, void*))V(0x2c))(this, buf.mpData) != 0;
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return r;
}

// @ 0x009334d0
int IniFile::ReadBinary(void* a, void* b)
{
    StackArray<wchar_t, 256> wb;
    wb.mpData = wb.mData; wb.mpDataEnd = 0; wb.mCapacity = 0x100;
    int n = ((int(__fastcall*)(void*, void*, void*, int))V(0x20))(this, a, b, 0x100);
    if (n > (int)wb.mCapacity) {
        wb.Resize(n + 1);
        ((int(__fastcall*)(void*, void*, void*, int))V(0x20))(this, a, b, n);
    }
    StackArray<char, 256> cb;
    cb.mpData = cb.mData; cb.mpDataEnd = 0; cb.mCapacity = 0x100;
    return n;
}

// @ 0x00933640
bool IniFile::WriteBinary(void* a, unsigned n, void* b)
{
    StackArray<wchar_t, 256> buf;
    buf.mpData = buf.mData; buf.mpDataEnd = 0; buf.mCapacity = 0x100;
    unsigned need = n * 2 + 1;
    if (need > buf.mCapacity) buf.Resize(need);
    EA_Text_ConvertBinaryDataToASCIIArray(a, n, buf.mpData);
    bool r = ((bool(__fastcall*)(void*, void*, void*))V(0x2c))(this, buf.mpData, b) != 0;
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return r;
}

// @ 0x00933700
bool IniFile::ConvertAndWriteStream(void* a, int n)
{
    StackArray<char, 256> buf;
    buf.mpData = buf.mData; buf.mpDataEnd = 0; buf.mCapacity = 0x100;
    int charSize = mEncoding;
    int bytes = n * 2;
    if (charSize != 0x10) {
        charSize = EA_Text_GetCharacterSize(charSize);
        if (buf.mCapacity < (unsigned)(charSize * n)) {
            buf.Resize(charSize * n);
        }
        int outLen = n;
        EA_Text_ConvertEncoding(a, n, 0x10, buf.mpData, &outLen, mEncoding);
        bytes = outLen * charSize;
    }
    if (mpEncodingSrc != 0 && buf.mpData != 0 && bytes != 0) {
        ((void(__fastcall*)(void*, void*, int))V(0x38))(this, buf.mpData, bytes);
    }
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return true;
}

// @ 0x009337f0
WString* WString_ctor(WString* dst, const WString* src)
{
    dst->mpBegin = 0; dst->mpEnd = 0; dst->mpCapacity = 0;
    int n = (int)((char*)src->mpEnd - (char*)src->mpBegin) >> 1;
    WStr_AllocateSelf(dst, n + 1);
    WString_copy(dst->mpBegin, src->mpBegin, n * 2);
    dst->mpEnd = (char16_t*)((char*)dst->mpBegin + n * 2);
    *dst->mpEnd = 0;
    *(void**)((char*)dst + 0x10) = *(void**)((const char*)src + 0x10);
    return dst;
}

// @ 0x00933850
int IniFile::ReadEntryRaw(void* a, wchar_t* b)
{
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    int r = ((int(__fastcall*)(void*, void*, void*, void*))V(0x24))(this, a, b, loc);
    if (r >= 0) {
        int n = (int)(size_t)a;
        if (n > r) n = r;
        wcsncpy_f(b, (const wchar_t*)a, n);
        b[n - 1] = 0;
    }
    if ((int)((int)loc[1] - (int)loc[0] & 0xfffffffeU) > 2 && loc[0]) operator delete[](loc[0]);
    return r;
}

// @ 0x009338e0
int IniFile::ReadEntry(void* a, void* b, WString* c)
{
    (void)c;
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    int r = 0;
    int rv = ((int(__fastcall*)(void*, void*, void*))V(0x24))(this, a, loc);
    if (rv != 0) {
        r = Vsscanf16(loc[0], this, b);
    }
    if ((int)((int)loc[1] - (int)loc[0] & 0xfffffffeU) > 2 && loc[0]) operator delete[](loc[0]);
    return r;
}

// @ 0x00933960
void WString::DeallocateSelf()
{
    char16_t* p = mpBegin;
    if ((int)((int)mpCapacity - (int)p & 0xfffffffeU) > 2 && p != 0) {
        operator delete[](p);
    }
}

// @ 0x00933980
bool IniFile::GetFileLine(WString* out)
{
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    int cs = EA_Text_GetCharacterSize(mEncoding);
    if (cs == 2) {
        return ((bool(__fastcall*)(void*, WString*))V(0x58))(this, out) != 0;
    }
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    char ok = (char)((int(__fastcall*)(void*, void*))V(0x54))(this, loc);
    if (ok) {
        EA_Text_ConvertEncoding8(loc[0], (int)((char*)loc[1] - (char*)loc[0]), 8, out);
        if ((int)((int)loc[1] - (int)loc[0]) > 1 && loc[0]) operator delete[](loc[0]);
        return true;
    }
    if ((int)((int)loc[1] - (int)loc[0]) > 1 && loc[0]) operator delete[](loc[0]);
    return false;
}

// @ 0x00933a90
void* eastl_do_move_commit(WString* first, WString* last, WString* out)
{
    if (first != last) {
        do {
            WString* hi = (WString*)((char*)first + 0x10);
            char16_t* p2 = hi->mpBegin;
            if ((int)((int)hi->mpCapacity - (int)p2 & 0xfffffffeU) > 2 && p2 != 0) operator delete[](p2);
            char16_t* p1 = first->mpBegin;
            if ((int)((int)first->mpCapacity - (int)p1 & 0xfffffffeU) > 2 && p1 != 0) operator delete[](p1);
            first += 2;
            out += 2;
        } while (first != last);
        return out;
    }
    return out;
}

// @ 0x00933b00
void* eastl_do_copy_backward(WString* first, WString* last, WString* out)
{
    if (first == last) return out;
    WString* o = out;
    WString* ol = out + 1;
    WString* l = last;
    WString* ll = last + 1;
    do {
        l = (WString*)((char*)l - 0x20);
        o = (WString*)((char*)o - 0x20);
        ll = (WString*)((char*)ll - 0x20);
        ol = (WString*)((char*)ol - 0x20);
        if (l != o) WString_AssignRange(o, l->mpBegin, l->mpEnd);
        if (ll != ol) WString_AssignRange(ol, ll->mpBegin, ll->mpEnd);
    } while (l != first);
    return o;
}

// @ 0x00933b70
bool IniFile::GetFileLine8To8(WString* out)
{
    char buf[0x44];
    int pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
    bool done = false;
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    for (;;) {
        int n = ((int(__fastcall*)(void*, void*, int))V(0x30))(this, buf, 0x40);
        if (n == 0 || n == -1) break;
        int i = 0;
        for (; i < n; ++i) {
            if (buf[i] == '\r' || buf[i] == '\n') {
                done = true;
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, pos + i, 0);
                for (;;) {
                    char c;
                    if (((int(__fastcall*)(void*, void*, int))V(0x30))(this, &c, 1) != 1) goto append;
                    if (c != '\r' && c != '\n') break;
                }
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, -1, 1);
                goto append;
            }
        }
    append:
        CharString_append(buf, buf, buf + i);
        pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
        if (done) break;
    }
    return done;
}

// @ 0x00933c80
bool IniFile::GetFileLine16To16(WString* out)
{
    char16_t buf[0x80];
    int pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
    bool done = false;
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    for (;;) {
        int n = ((int(__fastcall*)(void*, void*, int))V(0x30))(this, buf, 0x100);
        if (n == 0 || n == -1) break;
        int i = 0;
        for (; i < n; ++i) {
            if (buf[i] == '\r' || buf[i] == '\n') {
                done = true;
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, pos + i, 0);
                for (;;) {
                    char16_t c;
                    if (((int(__fastcall*)(void*, void*, int))V(0x30))(this, &c, 2) != 2) goto append;
                    if (c != '\r' && c != '\n') break;
                }
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, -2, 1);
                goto append;
            }
        }
    append:
        WStr_Append(out, buf, buf + i);
        pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
        if (done) break;
        if (mEncoding == 0x4b0) continue;
        int cnt = (int)(out->mpEnd - out->mpBegin) >> 1;
        unsigned short* q = out->mpBegin;
        for (int k = 0; k < cnt; ++k) { q[k] = (unsigned short)((q[k] >> 8) | (q[k] << 8)); }
    }
    return done;
}

// @ 0x00933df0
void __stdcall DestroyPairRange(WString* first, WString* last)
{
    for (; first < last; first += 2) {
        WString* s2 = (WString*)((char*)first + 0x10);
        char16_t* p2 = s2->mpBegin;
        if ((int)((int)s2->mpCapacity - (int)p2 & 0xfffffffeU) > 2 && p2 != 0) operator delete[](p2);
        char16_t* p1 = first->mpBegin;
        if ((int)((int)first->mpCapacity - (int)p1 & 0xfffffffeU) > 2 && p1 != 0) operator delete[](p1);
    }
}

// @ 0x00933e50
void RbtreeInsertHelper(char* tree, void** out, char* hint, WString* key, char flag)
{
    int less = 0;
    if (flag == 0 && hint != tree + 4) {
        if (WString_compare(key, hint + 0x10) >= 0) less = 1;
    }
    void* node = operator_new_ea(0x24, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    if (node) WString_ctor((WString*)((char*)node + 0x10), key);
    RBTreeInsert(tree + 4, hint, node, less);
    ++*(int*)(tree + 0x14);
    *out = node;
}

// @ 0x00933ef0
int IniFile_ReadEntry(IniFile* self, WString* key, WString* out)
{
    if (self->mpEncodingSrc == 0 || key == 0 || key->mpBegin == 0 || *key->mpBegin == 0) return -1;
    if (out == 0 || out->mpBegin == 0 || *out->mpBegin == 0) return -1;
    if (self->m_b442 == 0) {
        char c = (char)((int(__fastcall*)(void*, int))self->V(0x50))(self, 1);
        if (c == 0) {
            if (self->m_b441 == 0) ((void(__fastcall*)(void*))self->V(0x1c))(self);
            return -1;
        }
    }
    ((void(__fastcall*)(void*))self->V(0x1c))(self);
    return -1;
}

// @ 0x009341b0
bool IniFile::SectionExists(wchar_t* name)
{
    if (m_b442 == 0) {
        char c = (char)((int(__fastcall*)(void*, int))V(0x50))(this, 1);
        if (c == 0) return false;
    }
    WString local;
    local.mpBegin = 0; local.mpEnd = 0; local.mpCapacity = 0;
    WString_RangeInitialize(&local, name);
    WString_makeLower(&local);
    if (m_b441 == 0) ((void(__fastcall*)(void*))V(0x1c))(this);
    void** node = (void**)RbtreeFind((char*)this + 0x444, &local);
    bool r = *node != (char*)this + 0x448;
    local.DeallocateSelf();
    return r;
}

// @ 0x00934460
void PosMap::DoNukeSubtree(MapNode* node)
{
    while (node) {
        DoNukeSubtree(node->mpLeft);
        MapNode* next = node->mpRight;
        WString_s0093_4260& key = node->mKey;
        if (((int)((char*)key.mpCapacity - (char*)key.mpBegin) & ~1) > 2 && key.mpBegin)
            operator delete[](key.mpBegin);
        operator delete[](node);
        node = next;
    }
}

// @ 0x00934d00
int IniFile_s0093_4260::EnumerateSections(SectionCallback callback, void* param)
{
    int result = 0;
    if (!mbReadEntryCacheReady) {
        if (!CacheSections(1)) {
            result = -1;
            goto done;
        }
    }

    {
        ListAnchor anchor;
        anchor.mpNext = (ListNode*)&anchor;
        anchor.mpPrev = (ListNode*)&anchor;
        MapNode* node = mSectionPositionMap.mpRoot;
        MapNode* posAnchor = (MapNode*)&mSectionPositionMap.mpAnchorSelf;
        NameNode* nameAnchor = (NameNode*)mSectionNameMap.end();
        while (node != posAnchor) {
            NameIter it = mSectionNameMap.find(node->mKey);
            NameNode* nameNode = it.p;
            if (nameNode == nameAnchor) {
                ListNode* pList = (ListNode*)operator new[](0x18, "EASTL", 0, 0,
                    (int)"c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                pList->mValue.mpBegin = 0;
                pList->mValue.mpEnd = 0;
                pList->mValue.mpCapacity = 0;
                int len = (int)(node->mKey.mpEnd - node->mKey.mpBegin);
                pList->mValue.AllocateSelf(len + 1);
                memcpy(pList->mValue.mpBegin, node->mKey.mpBegin, len * 2);
                pList->mValue.mpEnd = pList->mValue.mpBegin + len;
                *pList->mValue.mpEnd = 0;
                ++result;
                pList->mpNext = (ListNode*)&anchor;
                pList->mpPrev = anchor.mpPrev;
                anchor.mpPrev->mpNext = pList;
                anchor.mpPrev = pList;
            } else {
                ListNode* pList = (ListNode*)operator new[](0x18, "EASTL", 0, 0,
                    (int)"c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                pList->mValue.mpBegin = 0;
                pList->mValue.mpEnd = 0;
                pList->mValue.mpCapacity = 0;
                int len = (int)(nameNode->mValue.mpEnd - nameNode->mValue.mpBegin);
                pList->mValue.AllocateSelf(len + 1);
                memcpy(pList->mValue.mpBegin, nameNode->mValue.mpBegin, len * 2);
                pList->mValue.mpEnd = pList->mValue.mpBegin + len;
                *pList->mValue.mpEnd = 0;
                ++result;
                pList->mpNext = (ListNode*)&anchor;
                pList->mpPrev = anchor.mpPrev;
                anchor.mpPrev->mpNext = pList;
                anchor.mpPrev = pList;
            }
            node = RBTreeIncrement(node);
        }

        uint32_t local = 0;
        for (ListNode* p = anchor.mpNext; p != (ListNode*)&anchor; p = p->mpNext) {
            if (!callback(p->mValue.mpBegin, &local, param))
                break;
        }
        anchor.Clear();
    }

done:
    if (!mbLeaveFileOpen)
        Close();
    return result;
}

// @ 0x00934ef0
void PairVec::insert(PairStr* position, const PairStr& value)
{
    if (mpEnd != mpCapacity) {
        PairStr* pValue = (PairStr*)&value;
        if (position <= pValue && pValue < mpEnd)
            ++pValue;
        if (mpEnd)
            new (mpEnd) PairStr(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        if (pValue != position)
            position->first.assign(pValue->first.mpBegin, pValue->first.mpEnd);
        if (&pValue->second != &position->second)
            position->second.assign(pValue->second.mpBegin, pValue->second.mpEnd);
        mpEnd = mpEnd + 1;
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    volatile int newCap;
    PairStr* volatile newBuf;
    if (oldSize <= 0) {
        newCap = 1;
    } else {
        newCap = oldSize * 2;
        if (newCap == 0) {
            newBuf = 0;
            goto have_buffer;
        }
    }
    newBuf = (PairStr*)operator new[](newCap << 5, "EASTL", 0, 0,
        (int)"c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
have_buffer:
    PairStr* newPos = uninitialized_move(mpBegin, position, newBuf);
    move_commit(mpBegin, position, newBuf);
    if (newPos)
        new (newPos) PairStr(value);
    PairStr* newEnd = uninitialized_move(position, mpEnd, newPos + 1);
    move_commit(position, mpEnd, newPos + 1);
    if (mpBegin && ((ArrayCookie*)mpBegin)[-1].mSize != 0)
        operator delete[](mpBegin);
    mpBegin = newBuf;
    mpEnd = newEnd;
    mpCapacity = newBuf + newCap;
}

// @ 0x00935040
IniFile_s0093_4260::~IniFile_s0093_4260()
{
    VTableHeader* pHeader = (VTableHeader*)this;
    NameMap* pNameMap = &mSectionNameMap;
    pHeader->mpVTable = (void*)0x143e7d8;
    pNameMap->DoNukeSubtree(pNameMap->mpRoot);
    PosMap* pMap = &mSectionPositionMap;
    pMap->DoNukeSubtree(pMap->mpRoot);
    mFileStream.Dtor();
}

// @ 0x00935080
bool IniFile_s0093_4260::Close()
{
    if (mpStream) {
        if (mpStream == &mFileStream) {
            if (mpStream->GetAccessFlags())
                mpStream->Open();
        }
        PosMap* pMap = &mSectionPositionMap;
        pMap->DoNukeSubtree(pMap->mpRoot);
        pMap->mpAnchorParent = (MapNode*)&pMap->mpAnchorSelf;
        pMap->mpRoot = 0;
        pMap->mColor = 0;
        pMap->mSize = 0;
        pMap->mpAnchorSelf = (MapNode*)&pMap->mpAnchorSelf;
        mbReadEntryCacheReady = false;
    }
    return true;
}

// @ 0x009350f0
int IniFile_LoadSectionNames(EA_IO_IniFile_s0093_50f0* self, int param_2)
{
    (void)self;
    (void)param_2;
    return 0;
}

// @ 0x00935450
EA_IO_IniFile_s0093_50f0* EA_IO_IniFile_s0093_50f0::ctor(int path, uint8_t flag)
{
    this->vftable = &IniFile_vtable;
    ((FileStreamStub*)this->mFileStream)->ctor(0);
    this->mpStream = 0;
    this->mEncodingSrc = 8;
    this->m440 = 0;
    this->m442 = 0;
    this->m441 = flag & 1;
    *(uint32_t*)((char*)this + 0x44c) = 0;
    *(uint32_t*)((char*)this + 0x450) = 0;
    *(uint32_t*)((char*)this + 0x454) = 0;
    uint32_t eax = (uint32_t)((char*)this + 0x448);
    *(uint32_t*)eax = eax;
    *(uint32_t*)((char*)this + 0x44c) = eax;
    *(uint32_t*)((char*)this + 0x450) = 0;
    *(uint8_t*)((char*)this + 0x454) = 0;
    *(uint32_t*)((char*)this + 0x458) = 0;
    *(uint32_t*)((char*)this + 0x468) = 0;
    eax = (uint32_t)((char*)this + 0x464);
    *(uint32_t*)((char*)this + 0x46c) = 0;
    *(uint32_t*)((char*)this + 0x470) = 0;
    *(uint32_t*)eax = eax;
    *(uint32_t*)((char*)this + 0x468) = eax;
    *(uint32_t*)((char*)this + 0x46c) = 0;
    *(uint8_t*)((char*)this + 0x470) = 0;
    *(uint32_t*)((char*)this + 0x474) = 0;
    this->mPath[0] = 0;
    this->SetPath((const wchar_t*)path);
    return this;
}

// @ 0x00935510
EA_IO_IniFile_s0093_50f0* EA_IO_IniFile_s0093_50f0::scalar_deleting_destructor(uint8_t flag)
{
    this->vftable = &IniFile_vtable;
    RBTreeStub* nameMap = (RBTreeStub*)((char*)this + 0x460);
    nameMap->DoNukeSubtree(nameMap->mpNodeParent);
    RBTreeStub* posMap = (RBTreeStub*)((char*)this + 0x444);
    posMap->DoNukeSubtree(posMap->mpNodeParent);
    ((FileStreamStub*)this->mFileStream)->dtor();
    if (flag & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x00935560
int IniFile_EnumEntries(EA_IO_IniFile_s0093_50f0* self, int a, void* cb, int d)
{
    (void)self;
    (void)a;
    (void)cb;
    (void)d;
    return 0;
}
