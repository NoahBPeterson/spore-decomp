// src/game/UTFSpore_Win32/httppostbodystream.cpp -- migrated from slice(s) s00945ed0, s0060b730 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/httppostbodystream.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"
#include "EA/Internet/HTTPMultipartRelatedPostBodyStream.h"
#include "EA/Internet/IHTTPPostBodyStream.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "eastl/allocator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "evp_cipher_ctx_st.h"
#include "EA/Internet/HTTPFormURLEncodedPostBodyStream.h"
#include "EA/Internet/HTTPClient.h"
#include "EA/Internet/HTTPResponse.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Thread.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern char gEmptyString[];  // 0x01667bac
#pragma intrinsic(strlen)
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s0060b730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern char gEmptyString[];  // 0x01667bac
namespace eastl {
struct allocator_s0060_b730 {
  allocator_s0060_b730() {}
};
}
namespace eastl {
int CompareI(const char* p1, const char* p2, unsigned int n);  // 0x005f7870
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T, typename A = allocator_s0060_b730>
struct basic_string_s0060_b730 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_b730() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_b730(const basic_string_s0060_b730& x);  // 0x0057cb10
  __forceinline ~basic_string_s0060_b730() { DeallocateSelf(); }
  __forceinline void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline basic_string_s0060_b730(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelf(n + 1);
    T* const pDest = mpBegin;
    memcpy(pDest, p, n);
    mpEnd = pDest + n;
    *mpEnd = 0;
  }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string_s0060_b730& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
  basic_string_s0060_b730& assign(const T* p, size_type n);          // 0x0060bcd0
  basic_string_s0060_b730& assign(const T* p);                       // 0x006a4380
  basic_string_s0060_b730& append(const T* pBegin, const T* pEnd);   // 0x00455d60
  basic_string_s0060_b730& append(const T* p);                       // 0x0060c4e0
  basic_string_s0060_b730& sprintf(const T* pFormat, ...);           // 0x00472fe0
  void AllocateSelf(size_type n);                         // 0x00475ab0
  __forceinline basic_string_s0060_b730& operator=(const basic_string_s0060_b730& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  int compare(const basic_string_s0060_b730& x) const;                          // 0x00609fe0
  int comparei(const basic_string_s0060_b730& x) const;                         // 0x00609ee0
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  size_type rfind(T c, size_type position) const;                    // 0x00609f40
  size_type find(const basic_string_s0060_b730& x, size_type position) const;   // 0x00609f90
  size_type find(T c, size_type position) const;                     // 0x00607580
  basic_string_s0060_b730 substr(size_type position, size_type n) const;        // 0x006082a0
};
}
typedef eastl::basic_string_s0060_b730<char> string8;
namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt_s0060_b730 {
  AtomicInt_s0060_b730() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
}
}
struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};
namespace EA {
namespace IO {
class IStream_s0060_b730 {
 public:
  IStream_s0060_b730() {}
  virtual ~IStream_s0060_b730() {}
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;  // +0x24
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);  // +0x38
};
}
}
namespace EA {
namespace IO {
class MemoryStream_s0060_b730 : public IStream_s0060_b730 {
 public:
  MemoryStream_s0060_b730(void* pData, uint32_t nSize, const char* pName);  // 0x0093c270
  void SetOption(int option, float value);                       // 0x0093bb40
  char pad[0x24 - 4];
};
}
}
namespace EA {
namespace COM {
template <typename T>
class RefCountTemplateA {
 public:
  virtual ~RefCountTemplateA() {}
  T mRefCount;
};  // namespace COM
}
}
namespace EA {
namespace Internet {
class IHTTPPostBodyStream_s0060_b730 : public IO::IStream_s0060_b730 {
 public:
  virtual void pv3c();
  virtual bool GetContentTypeString(string8& sContentType);  // +0x40
  virtual bool Finalize();                                    // +0x44
  virtual bool SetBoundary(const char* pBoundary);            // +0x48
  virtual const char* GetBoundary() const;                    // +0x4c
  virtual void pv50();
  virtual bool AddFormData(const char* pName, const char* pValue);  // +0x54
  virtual bool AddFormDataXML(const char* pXML);                    // +0x58
  virtual void pv5c();
  virtual void WriteToStream(const char* pText, IO::IStream_s0060_b730* pStream);  // +0x60
  virtual bool WriteEndBoundary();                                      // +0x64
  virtual bool pv68();
};
}
}
namespace EA {
namespace Internet {
struct IStreamNode : public ListNodeBase {
  IO::IStream_s0060_b730* mpStream;
};
}
}
namespace EA {
namespace Internet {
struct IStreamList {
  IStreamList() {
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
  }
  ~IStreamList() { DoClear(); }
  ListNodeBase mNode;
  uint32_t mAllocator;
  void DoClear();  // 0x0060c4a0
};
}
}
namespace EA {
namespace Internet {
struct MemStreamRef {
  IO::MemoryStream_s0060_b730* mpObject;
  MemStreamRef() : mpObject(0) {}
  ~MemStreamRef() {
    if (mpObject) mpObject->Release();
  }
  MemStreamRef& operator=(IO::MemoryStream_s0060_b730* p) {
    IO::MemoryStream_s0060_b730* const pTemp = mpObject;
    if (p != pTemp) {
      if (p) p->AddRef();
      mpObject = p;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
};
}
}
namespace EA {
namespace Internet {
static __forceinline unsigned int InlineStrlen(const char* p) {
  const char* c = p;
  const char* const p1 = c + 1;
  while (*c++) {
  }
  return (unsigned int)(c - p1);
}
}
}
namespace EA {
namespace Internet {
class HTTPMultipartRelatedPostBodyStream_s0060_b730 : public IHTTPPostBodyStream_s0060_b730,
                                           public COM::RefCountTemplateA<Thread::AtomicInt_s0060_b730<int> > {
 public:
  enum eFormDataType { kText = 0, kStream = 1 };
  HTTPMultipartRelatedPostBodyStream_s0060_b730();
  ~HTTPMultipartRelatedPostBodyStream_s0060_b730();

  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;  // 0x0060c630 (EA::Internet::HTTPMultipartRelatedPostBodyStream::GetType)
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);  // 0x00946800 (EA::Internet::HTTPMultipartRelatedPostBodyStream::SetSize)
  virtual int GetPosition(int positionType) const;  // 0x0060c0b0 (EA::Internet::HTTPMultipartRelatedPostBodyStream::GetPosition)
  virtual bool SetPosition(int position, int positionType);  // 0x00946b30 (EA::Internet::HTTPMultipartRelatedPostBodyStream::SetPosition)
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);  // 0x0060c3f0 (EA::Internet::HTTPMultipartRelatedPostBodyStream::Read)
  virtual bool Flush();  // 0x0060c140 (EA::Internet::HTTPMultipartRelatedPostBodyStream::Flush)
  virtual bool Write(const void* pData, uint32_t nSize);  // 0x0060c150 (EA::Internet::HTTPMultipartRelatedPostBodyStream::Write)
  virtual bool GetContentTypeString(string8& sContentType);  // 0x0060c730 (EA::Internet::HTTPMultipartRelatedPostBodyStream::GetContentTypeString)
  virtual bool Finalize();  // 0x0060c160 (EA::Internet::HTTPMultipartRelatedPostBodyStream::Finalize)
  virtual bool SetBoundary(const char* pBoundary);  // 0x0060c6d0 (EA::Internet::HTTPMultipartRelatedPostBodyStream::SetBoundary)
  virtual const char* GetBoundary() const;
  virtual bool AddFormData(const char* pName, const char* pValue);
  virtual bool AddFormDataXML(const char* pXML);  // 0x0060c290 (EA::Internet::HTTPMultipartRelatedPostBodyStream::AddFormDataXML)
  virtual void WriteToStream(const char* pText, IO::IStream_s0060_b730* pStream);
  virtual bool WriteEndBoundary();  // 0x0060c360 (EA::Internet::HTTPMultipartRelatedPostBodyStream::WriteEndBoundary)

  IStreamList mFormDataList;       // +0xc
  string8 msBoundary;              // +0x18
  IStreamNode* mReadItr;           // +0x28
  long mnPosition;                 // +0x2c
  unsigned int mnSize;             // +0x30
  int mnState;                     // +0x34
  bool mbFinal;                    // +0x38
  eFormDataType mLastDataType;     // +0x3c
  unsigned int mnTextStart;        // +0x40
  MemStreamRef mpMemStream;        // +0x44
};
}
}
// ---- items of slice s0060b730 end

// ---- items of slice s00945ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl operator_delete__(void*) throw();   // 0x00f47380
namespace eastl {
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;
    void assign(const char* first, const char* last);
    void append(const char* first, const char* last);   // 0x00455d60
    void appendFixed(const char* first, const char* last);   // 0x0060a150 (fixed_string<char>::append)
    ~StrStub() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    const char* data() const { return mpBegin; }
};
}
namespace EA {
namespace Internet {
void __cdecl EncodeFormURL(const char* s, eastl::StrStub* out);
}
}
namespace EA {
namespace Internet {
struct IStr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual int  GetState();                        // 5  (+0x14)
    virtual void v6();
    virtual unsigned GetSize();                     // 7  (+0x1c)
    virtual void v8();
    virtual int  GetPos(int);                       // 9  (+0x24)
    virtual bool SetPos(int, int);                  // 10 (+0x28)
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual int  Write(const void*, unsigned);      // 14 (+0x38)
};
}
}
namespace EA {
namespace Internet {
struct IStreamBase {
    virtual ~IStreamBase() {}
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual int  VGetAvailable();                   // 11 (+0x2c)
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void WriteStr(const char*, IStr*);      // 22 (+0x58)
    virtual bool Finish();                          // 23 (+0x5c)
    virtual bool Finish2();                         // 24 (+0x60)
};
}
}
namespace EA {
namespace Internet {
struct RefCountBase {
    RefCountBase() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
    virtual ~RefCountBase() {}
    int mnRefCount;
};
}
}
namespace EA {
namespace Internet {
class HTTPFormURLEncodedPostBodyStream_s0094_5ed0 : public IStreamBase, public RefCountBase {
public:
    long mnPosition;            // +0xc
    int  mnState;               // +0x10
    eastl::StrStub msData;      // +0x14
    bool mbFinal;               // +0x24

    bool Fn9467b0(int);
    bool Fn9467c0();
    bool Fn9467d0(int, int);
    bool Close();  // 0x00946810 (EA::Internet::HTTPFormURLEncodedPostBodyStream::Close)
    int  GetSize();  // 0x00946830 (EA::Internet::HTTPFormURLEncodedPostBodyStream::GetSize)
    int  GetPosition(int origin);
    bool SetPosition(int pos, int origin);
    int  GetAvailable();  // 0x00946900 (EA::Internet::HTTPFormURLEncodedPostBodyStream::GetAvailable)
    int  Read(void* buf, unsigned n);
    bool GetContentTypeString(eastl::StrStub* out);  // 0x00946d20 (EA::Internet::HTTPFormURLEncodedPostBodyStream::GetContentTypeString)
    bool Write(const char* name, const char* value);
    bool Fn946cc0();
    HTTPFormURLEncodedPostBodyStream_s0094_5ed0();
};
}
}
namespace EA {
namespace Internet {
HTTPFormURLEncodedPostBodyStream_s0094_5ed0::HTTPFormURLEncodedPostBodyStream_s0094_5ed0() {
    mnPosition = 0;
    mnState = 0;
    _ReadWriteBarrier();
    msData.mpBegin = (char*)0x1667bac;
    msData.mpEnd = (char*)0x1667bac;
    msData.mpCapacity = (char*)0x1667bad;
    mbFinal = false;
}
}
}
namespace EA {
namespace Internet {
struct ListNode {
    ListNode* next;
    ListNode* prev;
};
}
}
namespace EA {
namespace Internet {
struct StreamNode : ListNode {
    IStr*     stream;
};
}
}
namespace EA {
namespace Internet {
class HTTPMultipartFormDataPostBodyStream_s0094_5ed0 : public IStreamBase, public RefCountBase {
public:
    ListNode mListAnchor;       // +0xc
    int      mListSize;         // +0x14
    eastl::StrStub msBoundary;  // +0x18
    ListNode* mReadItr;         // +0x28
    long     mnPosition;        // +0x2c
    unsigned mnSize;            // +0x30
    int      mnState;           // +0x34
    bool     mbFinal;           // +0x38
    int      mLastDataType;     // +0x3c
    unsigned mnTextStart;       // +0x40
    IStr*    mpMemStream;       // +0x44

    int  GetSize();  // 0x009467e0 (EA::Internet::HTTPMultipartFormDataPostBodyStream::GetSize)
    bool Finalize();  // 0x00946970 (EA::Internet::HTTPMultipartFormDataPostBodyStream::Finalize)
    bool WriteField(const char* name, const char* value);
    bool WriteEndBoundary();  // 0x00946aa0 (EA::Internet::HTTPMultipartFormDataPostBodyStream::WriteEndBoundary)
};
}
}
namespace EA {
namespace Internet {
class HTTPMultipartRelatedPostBodyStream_s0094_5ed0 : public IStreamBase, public RefCountBase {
public:
    ListNode mListAnchor;       // +0xc
    int      mListSize;         // +0x14
    eastl::StrStub msBoundary;  // +0x18
    ListNode* mReadItr;         // +0x28
    long     mnPosition;        // +0x2c
    unsigned mnSize;            // +0x30
    int      mnState;           // +0x34
    bool     mbFinal;           // +0x38
    int      mLastDataType;     // +0x3c
    unsigned mnTextStart;       // +0x40
    IStr*    mpMemStream;       // +0x44

    bool SetSize(int);  // 0x00946800 (EA::Internet::HTTPMultipartRelatedPostBodyStream::SetSize)
    bool SetPosition(int pos, int origin);  // 0x00946b30 (EA::Internet::HTTPMultipartRelatedPostBodyStream::SetPosition)
};
}
}
// ---- items of slice s00945ed0 end

// @ 0x0060c0f0
unsigned int EA::Internet::HTTPMultipartFormDataPostBodyStream::GetAvailable() const
{
  if (!mbFinal) return (uint32_t)-1;
  if (mnState != 0) return (uint32_t)-1;
  return mnSize - mnPosition;
}

// @ 0x0060c110
namespace EA { namespace Internet {
void HTTPMultipartRelatedPostBodyStream_s0060_b730::WriteToStream(const char* pText, IO::IStream_s0060_b730* pStream)
{
  const uint32_t nLength = InlineStrlen(pText);
  pStream->Write(pText, nLength);
}
}}  // namespace EA::Internet

// @ 0x009467b0
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::SetSize(unsigned int a0)
{ mnState = -1; return false; }

// @ 0x009467c0
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::Flush()
{ mnState = -1; return false; }

// @ 0x009467d0
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::Write(void const * a0, unsigned int a1)
{ mnState = -1; return false; }

// @ 0x009467e0
unsigned int EA::Internet::HTTPMultipartFormDataPostBodyStream::GetSize() const
{
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return mnSize;
}

// @ 0x00946800
bool EA::Internet::HTTPMultipartRelatedPostBodyStream::SetSize(unsigned int a0)
{
    mnState = -1;
    return false;
}

// @ 0x00946810
namespace EA { namespace Internet {
bool HTTPFormURLEncodedPostBodyStream_s0094_5ed0::Close()
{
    mnState = -2;
    _ReadWriteBarrier();
    if (msData.mpBegin != msData.mpEnd) {
        *msData.mpBegin = 0;
        msData.mpEnd = msData.mpBegin;
    }
    return true;
}
}}  // namespace EA::Internet

// @ 0x00946830
unsigned int EA::Internet::HTTPFormURLEncodedPostBodyStream::GetSize() const
{
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return (int)(msData.mpEnd - msData.mpBegin);
}

// @ 0x00946850
long EA::Internet::HTTPFormURLEncodedPostBodyStream::GetPosition(EA::IO::PositionType origin) const
{
    int r = -1;
    if (mbFinal && mnState == 0) {
        if (origin == 0)
            return mnPosition;
        if (origin == 1)
            return 0;
        if (origin == 2)
            r = mnPosition - (int)msData.mpEnd + (int)msData.mpBegin;
    }
    return r;
}

// @ 0x00946890
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::SetPosition(long pos, EA::IO::PositionType origin)
{
    unsigned p = 0;
    if (!mbFinal)
        mbFinal = true;
    if (origin == 0)
        p = pos;
    else if (origin == 1)
        p = mnPosition + pos;
    else if (origin == 2)
        p = (msData.mpEnd - msData.mpBegin) + pos;
    else
        mnState = -1;
    if (p > (unsigned)(msData.mpEnd - msData.mpBegin) || (int)p < 0)
        mnState = -1;
    if (mnState != 0)
        return false;
    mnPosition = p;
    return true;
}

// @ 0x00946900
unsigned int EA::Internet::HTTPFormURLEncodedPostBodyStream::GetAvailable() const
{
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return (msData.mpEnd - mnPosition) - msData.mpBegin;
}

// @ 0x00946920
namespace EA { namespace Internet {
int HTTPFormURLEncodedPostBodyStream_s0094_5ed0::Read(void* buf, unsigned n)
{
    int r = -1;
    if (buf == 0)
        mnState = r;
    if (!mbFinal)
        mbFinal = true;
    if (mnState == 0) {
        unsigned avail = (unsigned)VGetAvailable();
        n = n > avail ? avail : n;
        memcpy(buf, msData.mpBegin + mnPosition, n);
        mnPosition += n;
        return n;
    }
    return r;
}
}}  // namespace EA::Internet

// @ 0x00946970
namespace EA { namespace Internet {
bool HTTPMultipartFormDataPostBodyStream_s0094_5ed0::Finalize()
{
    if (!mbFinal && mnState != -1) {
        if (mpMemStream->GetPos(0) > 0) {
            mbFinal = Finish();
            mnPosition = 0;
            return mbFinal;
        }
        mbFinal = true;
        mnPosition = 0;
    }
    return mbFinal;
}
}}  // namespace EA::Internet

// @ 0x009469c0
namespace EA { namespace Internet {
bool HTTPMultipartFormDataPostBodyStream_s0094_5ed0::WriteField(const char* name, const char* value)
{
    if (mbFinal)
        mnState = -1;
    if (name == 0)
        mnState = -1;
    if (mnState == 0) {
        unsigned pos = mpMemStream->GetPos(0);
        if (mLastDataType == 1) {
            mnTextStart = pos;
            mLastDataType = 0;
        }
        WriteStr((const char*)0x13fb644, mpMemStream);
        mpMemStream->Write(msBoundary.data(), msBoundary.size());
        WriteStr((const char*)0x13fb618, mpMemStream);
        WriteStr(name, mpMemStream);
        WriteStr((const char*)0x13fb610, mpMemStream);
        WriteStr(value, mpMemStream);
        if (mpMemStream->GetState() != 0)
            mnState = -1;
        else
            return true;
    }
    return false;
}
}}  // namespace EA::Internet

// @ 0x00946aa0
namespace EA { namespace Internet {
bool HTTPMultipartFormDataPostBodyStream_s0094_5ed0::WriteEndBoundary()
{
    if (mpMemStream) {
        unsigned pos = mpMemStream->GetPos(0);
        if (mLastDataType == 1) {
            mnTextStart = pos;
            mLastDataType = 0;
        }
        WriteStr((const char*)0x13fb644, mpMemStream);
        mpMemStream->Write(msBoundary.data(), msBoundary.size());
        WriteStr((const char*)0x13fb688, mpMemStream);
        if (mpMemStream->GetState() != 0)
            mnState = -1;
        else {
            mLastDataType = 0;
            return Finish2();
        }
    }
    return false;
}
}}  // namespace EA::Internet

// @ 0x00946b30
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0094_5ed0::SetPosition(int pos, int origin)
{
    if (mnState != 0)
        return false;
    if (!mbFinal)
        mbFinal = true;
    unsigned target;
    if (origin == 0)
        target = pos;
    else if (origin == 1)
        target = mnPosition + pos;
    else if (origin == 2)
        target = mnSize + pos;
    else {
        mnState = -1;
        return false;
    }
    if (target > mnSize || (int)target < 0) {
        mnState = -1;
        return false;
    }
    ListNode* end = &mListAnchor;
    ListNode* node = mListAnchor.next;
    unsigned total = 0;
    if (((StreamNode*)node)->stream->GetSize() < target) {
        do {
            total += ((StreamNode*)node)->stream->GetSize();
            node = node->next;
            if (node == end) {
                mnState = -1;
                return false;
            }
        } while (((StreamNode*)node)->stream->GetSize() + total < target);
    }
    if (!((StreamNode*)node)->stream->SetPos(target - total, 0)) {
        mnState = -1;
        return false;
    }
    ListNode* cur = node;
    node = node->next;
    while (node != end) {
        if (!((StreamNode*)node)->stream->SetPos(0, 0)) {
            mnState = -1;
            return false;
        }
        node = node->next;
    }
    mReadItr = cur;
    mnPosition = target;
    return true;
}
}}  // namespace EA::Internet

// @ 0x00946cc0
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::Finalize()
{ mbFinal = true; return true; }

// @ 0x00946d20
bool EA::Internet::HTTPFormURLEncodedPostBodyStream::GetContentTypeString(eastl::basic_string<char, eastl::allocator> & out)
{
    static const char s[] = "application/x-www-form-urlencoded";
    out.assign(s, s + 33);
    return true;
}

// @ 0x00946d40
namespace EA { namespace Internet {
bool HTTPFormURLEncodedPostBodyStream_s0094_5ed0::Write(const char* name, const char* value)
{
    int neg = -1;
    if (mbFinal)
        mnState = neg;
    if (name == 0)
        mnState = neg;
    if (mnState != 0)
        return false;
    eastl::StrStub& d = msData;
    if (d.mpBegin != d.mpEnd)
        d.append("&", "&" + 1);
    EncodeFormURL(name, &d);
    d.append("=", "=" + 1);
    if (value)
        EncodeFormURL(value, &d);
    return true;
}
}}  // namespace EA::Internet
