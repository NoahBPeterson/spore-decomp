// Slice s00934260 - EA::IO::IniFile::WriteEntry (EAIO, retail layout; fields addressed per the disassembly).
// Flags /O2 /MD /Gy /TP /GS- (no /EHsc: the original has no EH frame).
#include "types.h"
#include <string.h>

extern wchar_t gEmptyWString[];   // 0x01667bac

struct Alloc { };                 // eastl::allocator (empty tag, passed by reference)

struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    WString() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    WString(const wchar_t* p, const Alloc& a);        // 0x0041df50
    ~WString() { DeallocateSelf(); }
    void DeallocateSelf();                            // 0x00933960
    void make_lower();                                // 0x005e8e80
    void ltrim();                                     // 0x00554170
    void rtrim();                                     // 0x005541e0
    void trim();                                      // 0x0057eda0
    unsigned find(wchar_t c, unsigned pos);           // 0x004f6ab0
    void append(const WString& s, unsigned pos, unsigned n);   // 0x006ab800
    void erase(unsigned pos, unsigned n);             // 0x004228e0
    void assign(const wchar_t* begin, const wchar_t* end);     // 0x00423650
    void AllocateSelf(int n);                         // 0x00429760
    int length() const { return (int)(mpEnd - mpBegin); }
};

void __cdecl WStr_Format(WString* dst, const wchar_t* fmt, ...);   // 0x0041e050
bool __cdecl WStr_Equal(const WString& a, const WString& b);       // 0x0087d9a0
bool __cdecl FileExists(const wchar_t* path);                      // 0x00931fa0

void* operator new[](unsigned, const char*, int, int, int, int);   // 0x00f473a0
__forceinline void* operator new(unsigned, void* p) { return p; }  // placement new
void  __cdecl operator delete[](void*);                            // 0x00f47380

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
    WString first; long second;
    PairPos(const WString& a, const long& b);     // 0x008d6580
    ~PairPos() { first.DeallocateSelf(); }
};
struct PairStr {                                  // pair<const WString, WString>
    WString first; WString second;
    PairStr(const WString& a, const WString& b);  // 0x0088c0d0
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
    WString  mKey;                                // +0x10
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
    Iter   find(const WString& k);                // 0x005e96f0
    InsRes insert(const PairPos& v);              // 0x00934390
    char*  end() { return (char*)&mpAnchorSelf; }
    void   DoNukeSubtree(MapNode* node);          // 0x00934460
};
struct NameNode {                                // eastl::map<WString,WString> rbtree node
    NameNode* mpLeft;                             // +0x00
    NameNode* mpRight;                            // +0x04
    NameNode* mpParent;                           // +0x08
    uint32_t  mColor;                             // +0x0c
    WString   mKey;                               // +0x10
    WString   mValue;                             // +0x20
};
struct NameIter { NameNode* p; };

struct NameMap {                                  // eastl::map<WString,WString>
    uint32_t mPad00[3];                           // +0x00
    NameNode* mpRoot;                             // +0x0c
    uint32_t mPad10[3];                           // +0x10
    InsRes insert(const PairStr& v);              // 0x00615050
    NameIter find(const WString& k);              // 0x005e96f0
    void   DoNukeSubtree(NameNode* node);         // 0x00615110
    char*  end() { return (char*)&mPad00[1]; }
};

struct ListNode {                                 // eastl::list<WString> node
    ListNode* mpNext;                             // +0x00
    ListNode* mpPrev;                             // +0x04
    WString   mValue;                             // +0x08
};
struct ListAnchor {
    ListNode* mpNext;                             // +0x00
    ListNode* mpPrev;                             // +0x04
    void Clear();                                 // 0x0091a750
};

MapNode* __cdecl RBTreeIncrement(MapNode* node);  // 0x00921580

struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
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

class IniFile {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual bool Close();                         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual bool OpenForWrite(int mode);          // +0x48
    virtual void v19();
    virtual bool CacheSections(int mode);         // +0x50
    virtual void v21(); virtual void v22();
    virtual bool GetFileLine(WString* out);       // +0x5c
    virtual void WriteString(const wchar_t* s, int n);   // +0x60
    ~IniFile();                                    // 0x00935040

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

    bool WriteEntry(const wchar_t* pSection, const wchar_t* pKey, const wchar_t* pValue);
    int  EnumerateSections(SectionCallback callback, void* param);   // 0x00934d00
};

// @ 0x009344b0  EA::IO::IniFile::WriteEntry
bool IniFile::WriteEntry(const wchar_t* pSection, const wchar_t* pKey, const wchar_t* pValue)
{
    if (!mpStream || !pSection || !pSection[0] || !pKey || !pKey[0])
        return false;

    WString sEntry;
    WString sSection;

    if (!(mpStream->GetAccessFlags() & 2)) {
        if ((void*)mpStream != (void*)&mFileStream)
            return false;
        if (!FileExists(mPath)) {
            mbReadEntryCacheReady = false;
            if (!OpenForWrite(3))
                return false;
            WStr_Format(&sSection, L"[%s]%s", pSection, L"\r\n");
            WStr_Format(&sEntry, L"%ls = %ls%ls", pKey, pValue, L"\r\n");
            WriteString(sSection.mpBegin, sSection.length());
            WriteString(sEntry.mpBegin, sEntry.length());
            if (!mbLeaveFileOpen)
                Close();
            return true;
        }
    }

    if (!mbReadEntryCacheReady) {
        if (!CacheSections(3))
            return false;
    }
    if (!mbFileIsOpenForWriting) {
        if (!mpStream->GetState())
            mpStream->Open();
    }
    if (mpStream->GetState()) {
        if (!OpenForWrite(3))
            return false;
    }

    Alloc alloc;
    WString sLowerSection(pSection, alloc);
    sLowerSection.make_lower();
    WString sLowerKey(pKey, alloc);
    sLowerKey.make_lower();

    Iter it = mSectionPositionMap.find(sLowerSection);
    if ((char*)it.p == mSectionPositionMap.end()) {
        // Section does not exist yet: append "[section]" and the entry at the end of the file.
        mpStream->SetPosition(0, 2);
        bool bEndsWithNewline = false;
        if (mpStream->GetPosition(0) > 0) {
            uint32_t ch = 0;
            mpStream->SetPosition(-2, 1);
            if (mpStream->Read(&ch, 2) == 2) {
                if ((uint16_t)ch == 0xd || (uint16_t)ch == 0xa)
                    bEndsWithNewline = true;
            }
        }
        if (mpStream->Size() > 0 && !bEndsWithNewline)
            WStr_Format(&sSection, L"%s", L"\r\n");
        WriteString(sSection.mpBegin, sSection.length());
        long position = mpStream->GetPosition(0);
        WStr_Format(&sSection, L"[%s]%s", pSection, L"\r\n");
        WriteString(sSection.mpBegin, sSection.length());
        WStr_Format(&sEntry, L"%ls = %ls%ls", pKey, pValue, L"\r\n");
        WriteString(sEntry.mpBegin, sEntry.length());
        mSectionPositionMap.insert(PairPos(sLowerSection, position));
        {
            WString sOrig(pSection, alloc);
            mSectionNameMap.insert(PairStr(sLowerSection, sOrig));
        }
        if (!mbLeaveFileOpen)
            Close();
        return true;
    }

    unsigned sectionPos = it.p->value;
    if (sectionPos >= mpStream->Size() || !mpStream->SetPosition(sectionPos, 0)) {
        if (!mbLeaveFileOpen)
            Close();
        return false;
    }

    {
        WString sLhs;
        WString sKeyLower(pKey, alloc);
        WString sLine;
        sKeyLower.make_lower();

        if (!GetFileLine(&sLine)) {
            if (!mbLeaveFileOpen)
                Close();
            return false;
        }

        int startPos = mpStream->GetPosition(0);
        while (GetFileLine(&sLine)) {
            sLine.ltrim();
            if (sLine.length() != 0 && sLine.mpBegin[0] != L';') {
                if (sLine.mpBegin[0] == L'[') {
                    // Next section reached: insert the new entry before it.
                    unsigned n = mpStream->Size() - startPos;
                    wchar_t* buf = new ("EAIniFile", 0, 0, 0, 0) wchar_t[n];
                    mpStream->SetPosition(startPos, 0);
                    int r = mpStream->Read(buf, n);
                    if (r != -1) {
                        mpStream->SetPosition(startPos, 0);
                        WStr_Format(&sEntry, L"%ls = %ls%ls", pKey, pValue, L"\r\n");
                        WriteString(sEntry.mpBegin, sEntry.length());
                        mpStream->Write(buf, r);
                        mpStream->SetSize(mpStream->GetPosition(0));
                    }
                    delete[] buf;
                    mbReadEntryCacheReady = false;
                    if (!mbLeaveFileOpen)
                        Close();
                    return true;
                }
                unsigned pos = sLine.find(L'=', 0);
                if (pos != (unsigned)-1) {
                    sLhs.append(sLine, 0, pos);
                    sLhs.rtrim();
                    sLhs.make_lower();
                    if (sLhs.mpBegin != sLhs.mpEnd) {
                        sLine.erase(0, pos + 1);
                        sLine.trim();
                    }
                }
                if (WStr_Equal(sLhs, sKeyLower)) {
                    // Replace the existing entry line.
                    int p = mpStream->GetPosition(0);
                    unsigned n = mpStream->Size() - p;
                    wchar_t* buf = new ("EAIniFile", 0, 0, 0, 0) wchar_t[n];
                    int r = mpStream->Read(buf, n);
                    if (r != -1) {
                        mpStream->SetPosition(startPos, 0);
                        WStr_Format(&sEntry, L"%ls = %ls%ls", pKey, pValue, L"\r\n");
                        WriteString(sEntry.mpBegin, sEntry.length());
                        WriteString(L"\r\n", (int)wcslen(L"\r\n"));
                        mpStream->Write(buf, r);
                        mpStream->SetSize(mpStream->GetPosition(0));
                    }
                    delete[] buf;
                    mbReadEntryCacheReady = false;
                    if (!mbLeaveFileOpen)
                        Close();
                    return true;
                }
            }
            startPos = mpStream->GetPosition(0);
        }

        // Entry not found in the section: append it at the end of the file.
        mpStream->SetPosition(0, 2);
        WStr_Format(&sEntry, L"%ls = %ls%ls", pKey, pValue, L"\r\n");
        WriteString(sEntry.mpBegin, sEntry.length());
        if (!mbLeaveFileOpen)
            Close();
    }
    return true;
}

// @ 0x00934460  eastl::rbtree<WString,pair<const WString,long>>::DoNukeSubtree
void PosMap::DoNukeSubtree(MapNode* node)
{
    while (node) {
        DoNukeSubtree(node->mpLeft);
        MapNode* next = node->mpRight;
        WString& key = node->mKey;
        if (((int)((char*)key.mpCapacity - (char*)key.mpBegin) & ~1) > 2 && key.mpBegin)
            operator delete[](key.mpBegin);
        operator delete[](node);
        node = next;
    }
}

// @ 0x00935040  EA::IO::IniFile::~IniFile
IniFile::~IniFile()
{
    VTableHeader* pHeader = (VTableHeader*)this;
    NameMap* pNameMap = &mSectionNameMap;
    pHeader->mpVTable = (void*)0x143e7d8;
    pNameMap->DoNukeSubtree(pNameMap->mpRoot);
    PosMap* pMap = &mSectionPositionMap;
    pMap->DoNukeSubtree(pMap->mpRoot);
    mFileStream.Dtor();
}

struct ArrayCookie { uint32_t mSize; };           // operator new[] cookie before the payload

// @ 0x00934ef0  eastl::vector<PairStr>::insert
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

// @ 0x00934d00  EA::IO::IniFile::EnumerateSections
int IniFile::EnumerateSections(SectionCallback callback, void* param)
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

// @ 0x00935080  EA::IO::IniFile::Close
bool IniFile::Close()
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
