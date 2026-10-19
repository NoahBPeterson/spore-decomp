// src/game/SPEditors/SPHTTPPostBodyStream.cpp -- migrated from slice(s) s0060c780, s0060b730 by tools/migrate/rewrite.py
// Object file: SPEditors/SPHTTPPostBodyStream.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPMultipartRelatedPostBodyStream.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"
#include "EA/Internet/IHTTPPostBodyStream.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "eastl/allocator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "evp_cipher_ctx_st.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern char gEmptyString[];  // 0x01667bac
#pragma intrinsic(strlen)
#pragma intrinsic(_InterlockedExchange)
#include "eastl/string.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cJobResultMessage.h"
#include "SP/cPollinator.h"
#include "SP/cPollinatorCheat.h"

// ---- items of slice s0060b730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(unsigned int, void* p) { return p; }
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

// ---- items of slice s0060c780 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
namespace eastl {
struct allocator_s0060_c780 {
  allocator_s0060_c780() {}
};
}
namespace eastl {
template <typename T, typename A = allocator_s0060_c780>
struct basic_string_s0060_c780 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_c780() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_c780(const basic_string_s0060_c780& x);  // 0x0057cb10
  __forceinline ~basic_string_s0060_c780() { DeallocateSelf(); }
  __forceinline void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline basic_string_s0060_c780(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelf(n + 1);
    T* const pDest = mpBegin;
    memcpy(pDest, p, n);
    mpEnd = pDest + n;
    *mpEnd = 0;
  }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string_s0060_c780& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
  basic_string_s0060_c780& assign(const T* p, size_type n);          // 0x0060bcd0
  basic_string_s0060_c780& assign(const T* p);                       // 0x006a4380
  basic_string_s0060_c780& append(const T* pBegin, const T* pEnd);   // 0x00455d60
  basic_string_s0060_c780& append(const T* p);                       // 0x0060c4e0
  basic_string_s0060_c780& sprintf(const T* pFormat, ...);           // 0x00472fe0
  void AllocateSelf(size_type n);                         // 0x00475ab0
  __forceinline basic_string_s0060_c780& operator=(const basic_string_s0060_c780& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  int compare(const basic_string_s0060_c780& x) const;                          // 0x00609fe0
  int comparei(const basic_string_s0060_c780& x) const;                         // 0x00609ee0
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  size_type rfind(T c, size_type position) const;                    // 0x00609f40
  size_type find(const basic_string_s0060_c780& x, size_type position) const;   // 0x00609f90
  size_type find(T c, size_type position) const;                     // 0x00607580
  basic_string_s0060_c780 substr(size_type position, size_type n) const;        // 0x006082a0
};
}
typedef eastl::basic_string_s0060_c780<char> string8_s0060_c780;
namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt_s0060_c780 {
  AtomicInt_s0060_c780() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
}
}
namespace EA {
namespace IO {
class IStream_s0060_c780 {
 public:
  IStream_s0060_c780() {}
  virtual ~IStream_s0060_c780() {}
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;       // +0x1c
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;  // +0x24
  virtual bool SetPosition(int position, int positionType);  // +0x28
  virtual uint32_t GetAvailable() const;  // +0x2c
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);  // +0x38
};
}
}
namespace EA {
namespace IO {
class MemoryStream_s0060_c780 : public IStream_s0060_c780 {
 public:
  MemoryStream_s0060_c780(void* pData, uint32_t nSize, const char* pName);  // 0x0093c270
  char pad[0x24 - 4];
};
}
}
namespace EA {
namespace IO {
class SubStream : public IStream_s0060_c780 {
 public:
  SubStream(IStream_s0060_c780* pSource, uint32_t nStart, uint32_t nSize);  // 0x0093b7d0
  char pad[0x1c - 4];
};
}
}
namespace EA {
namespace Internet {
class IHTTPPostBodyStream_s0060_c780 : public IO::IStream_s0060_c780 {
 public:
  virtual void pv3c();
  virtual bool GetContentTypeString(string8_s0060_c780& sContentType);  // +0x40
  virtual bool Finalize();                                    // +0x44
  virtual bool SetBoundary(const char* pBoundary);            // +0x48
  virtual const char* GetBoundary() const;                    // +0x4c
  virtual bool AddFormData(const char* pName, const char* pValue);  // +0x54
  virtual bool AddFormData(const char* pName, IO::IStream_s0060_c780* pStream, const char* pContentType,
                           const char* pFileName, const char* pTransferEncoding);  // +0x50
  virtual bool AddFormDataXML(const char* pXML);  // +0x58
  virtual bool AddFormDataVideo(const char* pContentType, const char* pTransferEncoding, IO::IStream_s0060_c780* pStream);  // +0x5c
  virtual void WriteToStream(const char* pText, IO::IStream_s0060_c780* pStream);  // +0x60
  virtual bool WriteEndBoundary();                                      // +0x64
  virtual bool CommitTextSegment();                                     // +0x68
};
}
}
namespace EA {
namespace Internet {
struct IStreamNode_s0060_c780 : public ListNodeBase {
  IO::IStream_s0060_c780* mpStream;
};
}
}
namespace EA {
namespace Internet {
template <typename T>
struct StreamRef {
  T* mpObject;
  StreamRef() : mpObject(0) {}
  StreamRef(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~StreamRef() {
    if (mpObject) mpObject->Release();
  }
  StreamRef& operator=(T* p);  // 0x00572620
};
}
}
namespace EA {
namespace Internet {
class HTTPMultipartRelatedPostBodyStream_s0060_c780 : public IHTTPPostBodyStream_s0060_c780,
                                           public COM::RefCountTemplateA<Thread::AtomicInt_s0060_c780<int> > {
 public:
  enum eFormDataType { kText = 0, kStream = 1 };
  virtual bool AddFormData(const char* pName, const char* pValue);
  virtual bool AddFormData(const char* pName, IO::IStream_s0060_c780* pStream, const char* pContentType,
                           const char* pFileName, const char* pTransferEncoding);
  virtual bool AddFormDataVideo(const char* pContentType, const char* pTransferEncoding, IO::IStream_s0060_c780* pStream);  // 0x0060c9c0 (EA::Internet::HTTPMultipartRelatedPostBodyStream::AddFormDataVideo)
  virtual bool CommitTextSegment();

  IStreamList mFormDataList;       // +0xc
  string8_s0060_c780 msBoundary;              // +0x18
  IStreamNode_s0060_c780* mReadItr;           // +0x28
  long mnPosition;                 // +0x2c
  unsigned int mnSize;             // +0x30
  int mnState;                     // +0x34
  bool mbFinal;                    // +0x38
  eFormDataType mLastDataType;     // +0x3c
  unsigned int mnTextStart;        // +0x40
  IO::MemoryStream_s0060_c780* mpMemStream;   // +0x44
};
}
}
namespace StreamDeque {
using EA::IO::IStream_s0060_c780;
}
namespace StreamDeque {
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
}
// ---- items of slice s0060c780 end

// @ 0x0060c0b0
long EA::Internet::HTTPMultipartRelatedPostBodyStream::GetPosition(EA::IO::PositionType positionType) const
{
  int nResult = -1;
  if (mbFinal && mnState == 0) {
    if (positionType == 0) return mnPosition;
    if (positionType == 1) return 0;
    if (positionType == 2) nResult = mnPosition - mnSize;
  }
  return nResult;
}

// @ 0x0060c140
bool EA::Internet::HTTPMultipartRelatedPostBodyStream::Flush()
{
  mnState = -1;
  return false;
}

// @ 0x0060c150
bool EA::Internet::HTTPMultipartRelatedPostBodyStream::Write(void const * a0, unsigned int a1)
{
  mnState = -1;
  return false;
}

// @ 0x0060c160
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_b730::Finalize()
{
  if (!mbFinal && mnState != -1) {
    if (mpMemStream.mpObject->GetPosition(0) > 0) {
      mbFinal = WriteEndBoundary();
      mnPosition = 0;
      return mbFinal;
    }
    mbFinal = true;
    mnPosition = 0;
  }
  return mbFinal;
}
}}  // namespace EA::Internet

// @ 0x0060c1b0
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_b730::AddFormData(const char* pName, const char* pValue)
{
  if (mbFinal) mnState = -1;
  if (!pName) mnState = -1;
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Disposition: form-data; name=\"", mpMemStream.mpObject);
    WriteToStream(pName, mpMemStream.mpObject);
    WriteToStream("\"\r\n\r\n", mpMemStream.mpObject);
    WriteToStream(pValue, mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0)
      mnState = -1;
    else
      return true;
  }
  return false;
}
}}  // namespace EA::Internet

// @ 0x0060c290
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_b730::AddFormDataXML(const char* pXML)
{
  if (mbFinal) mnState = -1;
  if (!pXML) mnState = -1;
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Type: application/atom+xml; charset=UTF-8", mpMemStream.mpObject);
    WriteToStream("\r\n\r\n", mpMemStream.mpObject);
    WriteToStream(pXML, mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0)
      mnState = -1;
    else
      return true;
  }
  return false;
}
}}  // namespace EA::Internet

// @ 0x0060c360
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_b730::WriteEndBoundary()
{
  if (mpMemStream.mpObject) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("--\r\n", mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0) {
      mnState = -1;
    } else {
      mLastDataType = kText;
      return pv68();
    }
  }
  return false;
}
}}  // namespace EA::Internet

// @ 0x0060c3f0
namespace EA { namespace Internet {
uint32_t HTTPMultipartRelatedPostBodyStream_s0060_b730::Read(void* pData, uint32_t nSize)
{
  if (!mbFinal) return (uint32_t)-1;
  if (mnState != 0) return (uint32_t)-1;
  if (!pData) {
    mnState = -1;
    return (uint32_t)-1;
  }
  if (mnPosition == 0 && (IStreamNode*)&mFormDataList == mReadItr) mReadItr = (IStreamNode*)mFormDataList.mNode.mpNext;
  uint32_t nRead = 0;
  while (nRead < nSize) {
    if (mReadItr == (IStreamNode*)&mFormDataList) break;
    const uint32_t n = mReadItr->mpStream->Read((char*)pData + nRead, nSize - nRead);
    if (n == (uint32_t)-1) {
      nRead = (uint32_t)-1;
      break;
    }
    mnPosition += n;
    nRead += n;
    if (mReadItr->mpStream->GetAvailable() == 0) {
      mReadItr = (IStreamNode*)mReadItr->mpNext;
      if (mReadItr == (IStreamNode*)&mFormDataList) break;
    }
  }
  return nRead;
}
}}  // namespace EA::Internet

// @ 0x0060c4e0
template <> string8& string8::append(const char* p)
{
  const char* const p1 = p + 1;
  const char* q = p;
  while (*q++) {
  }
  return append(p, p + (q - p1));
}

// @ 0x0060c510
namespace EA { namespace Internet {
HTTPMultipartRelatedPostBodyStream_s0060_b730::HTTPMultipartRelatedPostBodyStream_s0060_b730()
: msBoundary("EA_HTTP_REQUEST_SIMPLE_BOUNDARY"),
      mnPosition(-1),
      mnSize(0),
      mnState(0),
      mbFinal(false),
      mLastDataType(kStream),
      mnTextStart(0) {
  mReadItr = (IStreamNode*)&mFormDataList;
  mpMemStream = new ("Pollinator", 0, 0, 0, 0) IO::MemoryStream_s0060_b730(0, 0, "UTF/MemoryStream");
  mpMemStream.mpObject->SetOption(1, 1.0f);
  mpMemStream.mpObject->SetOption(2, 0.0f);
  mpMemStream.mpObject->SetOption(3, 1024.0f);
}
}}  // namespace EA::Internet

// @ 0x0060c660
namespace EA { namespace Internet {
HTTPMultipartRelatedPostBodyStream_s0060_b730::~HTTPMultipartRelatedPostBodyStream_s0060_b730()
{}
}}  // namespace EA::Internet

// @ 0x0060c6d0
bool EA::Internet::HTTPMultipartRelatedPostBodyStream::SetBoundary(char const * pBoundary)
{
  if (pBoundary && InlineStrlen(pBoundary) <= 0x46 && InlineStrlen(pBoundary) >= 1 &&
      mFormDataList.mNode.mpNext == &mFormDataList.mNode) {
    msBoundary.assign(pBoundary);
    return true;
  }
  mnState = -1;
  return false;
}

// @ 0x0060c780
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_c780::AddFormData(const char* pName, IO::IStream_s0060_c780* pStream, const char* pContentType, const char* pFileName, const char* pTransferEncoding)
{
  if (mbFinal) mnState = -1;
  if (pName && pStream && pContentType) {
    const int nSize = (int)pStream->GetSize();
    if (nSize != -1 && nSize != -2) goto lOk;
  }
  mnState = -1;
lOk:
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream);
    mpMemStream->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Disposition: form-data; name=\"", mpMemStream);
    WriteToStream(pName, mpMemStream);
    WriteToStream("\"", mpMemStream);
    if (pFileName) {
      WriteToStream("; filename=\"", mpMemStream);
      WriteToStream(pFileName, mpMemStream);
      WriteToStream("\"", mpMemStream);
    }
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Type: ", mpMemStream);
    WriteToStream(pContentType, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    if (pTransferEncoding) {
      WriteToStream("Content-Transfer-Encoding: ", mpMemStream);
      WriteToStream(pTransferEncoding, mpMemStream);
      WriteToStream("\r\n", mpMemStream);
    }
    WriteToStream("\r\n", mpMemStream);
    if (mpMemStream->GetState() == 0 && CommitTextSegment()) {
      StreamRef<IO::IStream_s0060_c780> ref(pStream);
      IStreamNode_s0060_c780* const pNode = (IStreamNode_s0060_c780*)EASTL_allocator_allocate(sizeof(IStreamNode_s0060_c780), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = ref.mpObject;
        if (ref.mpObject) ref.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += pStream->GetAvailable();
      mLastDataType = kStream;
      return true;
    }
    mnState = -1;
  }
  return false;
}
}}  // namespace EA::Internet

// @ 0x0060c9c0
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_c780::AddFormDataVideo(const char* pContentType, const char* pTransferEncoding, IO::IStream_s0060_c780* pStream)
{
  if (mbFinal) mnState = -1;
  if (pContentType && pTransferEncoding && pStream) {
    const int nSize = (int)pStream->GetSize();
    if (nSize != -1 && nSize != -2) goto lOk;
  }
  mnState = -1;
lOk:
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream);
    mpMemStream->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Type: ", mpMemStream);
    WriteToStream(pContentType, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Transfer-Encoding: ", mpMemStream);
    WriteToStream(pTransferEncoding, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    if (mpMemStream->GetState() == 0 && CommitTextSegment()) {
      StreamRef<IO::IStream_s0060_c780> ref(pStream);
      IStreamNode_s0060_c780* const pNode = (IStreamNode_s0060_c780*)EASTL_allocator_allocate(sizeof(IStreamNode_s0060_c780), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = ref.mpObject;
        if (ref.mpObject) ref.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += pStream->GetAvailable();
      mLastDataType = kStream;
      return true;
    }
    mnState = -1;
  }
  return false;
}
}}  // namespace EA::Internet

// @ 0x0060cb90
namespace EA { namespace Internet {
bool HTTPMultipartRelatedPostBodyStream_s0060_c780::CommitTextSegment()
{
  if (!mbFinal && mpMemStream && mLastDataType == kText) {
    StreamRef<IO::IStream_s0060_c780> pSegment;
    void* const pMem = operator new(0x1c, "Pollinator", 0, 0, 0, 0);
    IO::SubStream* pSub = 0;
    if (pMem) pSub = new (pMem) IO::SubStream(mpMemStream, mnTextStart, mpMemStream->GetPosition(0) - mnTextStart);
    pSegment = pSub;
    if (pSegment.mpObject) {
      pSegment.mpObject->SetPosition(0, 0);
      StreamRef<IO::IStream_s0060_c780> pTemp(pSegment.mpObject);
      IStreamNode_s0060_c780* const pNode = (IStreamNode_s0060_c780*)EASTL_allocator_allocate(sizeof(IStreamNode_s0060_c780), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = pTemp.mpObject;
        if (pTemp.mpObject) pTemp.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += mpMemStream->GetPosition(0) - mnTextStart;
      mnTextStart = mpMemStream->GetPosition(0);
      return true;
    }
  }
  mnState = -1;
  return false;
}
}}  // namespace EA::Internet
