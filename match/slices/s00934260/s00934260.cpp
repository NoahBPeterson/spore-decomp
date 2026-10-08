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
    int length() const { return (int)(mpEnd - mpBegin); }
};

void __cdecl WStr_Format(WString* dst, const wchar_t* fmt, ...);   // 0x0041e050
bool __cdecl WStr_Equal(const WString& a, const WString& b);       // 0x0087d9a0
bool __cdecl FileExists(const wchar_t* path);                      // 0x00931fa0

void* operator new[](unsigned, const char*, int, int, int, int);   // 0x00f473a0
void  __cdecl operator delete[](void*);                            // 0x00f47380

struct PairPos {                                  // pair<WString, long>
    WString first; long second;
    PairPos(const WString& a, const long& b);     // 0x008d6580
    ~PairPos() { first.DeallocateSelf(); }
};
struct PairStr {                                  // pair<const WString, WString>
    WString first; WString second;
    PairStr(const WString& a, const WString& b);  // 0x0088c0d0
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
struct PosMap {                                   // eastl::map<WString,long>, 0x1c bytes
    char pad[4]; char anchor[0x18];
    Iter   find(const WString& k);                // 0x005e96f0
    InsRes insert(const PairPos& v);              // 0x00934390
    char* end() { return anchor; }
};
struct NameMap {                                  // eastl::map<WString,WString>
    char pad[0x1c];
    InsRes insert(const PairStr& v);              // 0x00615050
};

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

class IniFile {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual void Close();                         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual bool OpenForWrite(int mode);          // +0x48
    virtual void v19();
    virtual bool CacheSections(int mode);         // +0x50
    virtual void v21(); virtual void v22();
    virtual bool GetFileLine(WString* out);       // +0x5c
    virtual void WriteString(const wchar_t* s, int n);   // +0x60

    wchar_t  mPath[260];                          // +0x004
    char     mFileStream[0x22c];                  // +0x20c
    IStream* mpStream;                            // +0x438
    int      mEncoding;                           // +0x43c
    bool     mbFileIsOpenForWriting;              // +0x440
    bool     mbLeaveFileOpen;                     // +0x441
    bool     mbReadEntryCacheReady;               // +0x442
    char     pad443;
    PosMap   mSectionPositionMap;                 // +0x444
    NameMap  mSectionNameMap;                     // +0x460

    bool WriteEntry(const wchar_t* pSection, const wchar_t* pKey, const wchar_t* pValue);
};

// @ 0x009344b0  EA::IO::IniFile::WriteEntry
bool IniFile::WriteEntry(const wchar_t* pSection, const wchar_t* pKey, const wchar_t* pValue)
{
    if (!mpStream || !pSection || !pSection[0] || !pKey || !pKey[0])
        return false;

    WString sEntry;
    WString sSection;

    if (!(mpStream->GetAccessFlags() & 2)) {
        if ((void*)mpStream != (void*)mFileStream)
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
