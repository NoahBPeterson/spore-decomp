// src/game/SPEngine/EACompressionStreamZLib.cpp -- migrated from slice(s) s0067d550, s0067c450 by tools/migrate/rewrite.py
// Object file: SPEngine/EACompressionStreamZLib.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"

// ---- items of slice s0067c450 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct z_stream_s {
  const uint8_t* next_in;
  uint32_t avail_in;
  uint32_t total_in;
  uint8_t* next_out;
  uint32_t avail_out;
  uint32_t total_out;
  char* msg;
  void* state;
  void* zalloc;
  void* zfree;
  void* opaque;
  int data_type;
  uint32_t adler;
  uint32_t reserved;
};
namespace EA {
namespace IO {
enum eCompressedFormat { kCompressedFormatZLib = 0, kCompressedFormatGZip = 1 };
}
}
namespace EA {
namespace IO {
extern "C" void __cdecl eaFree(void* p);
}
}
namespace EA {
namespace IO {
class StreamCompressionZLib {
 public:
  bool SetCompressedFormat(eCompressedFormat fmt);   // @ 0x0067d280
  bool SetBufferSize(unsigned int size);             // @ 0x0067d2a0
  bool SetCompressionHint(int hint);                 // @ 0x0067d2e0
  int GetAccessFlags() const;                        // @ 0x0067d300
  int GetState() const;                              // @ 0x0067d310
  bool InitPointers();                               // @ 0x0067d330
  unsigned int GetPosition(int positionType) const;  // @ 0x0067d3f0

  unsigned int mGap00[3];          // +0x00
  void* mpOutputStream;            // +0x0c
  bool mbOpen;                     // +0x10
  bool mbInited;                   // +0x11
  z_stream_s* mpZLibStream;        // +0x14
  eCompressedFormat mFormat;       // +0x18
  int mHint;                       // +0x1c
  unsigned char* mpOutputBuffer;   // +0x20
  unsigned int mnOutputBufferSize; // +0x24
  unsigned int mInputCRC;          // +0x28
  unsigned int mInputSize;         // +0x2c
};
}
}
namespace EA {
namespace IO {
class StreamDecompressionZLib {
 public:
  bool SetCompressedFormat(eCompressedFormat fmt);   // @ 0x0067d410
  bool SetBufferSize(unsigned int size);             // @ 0x0067d420
  int GetAccessFlags() const;                        // @ 0x0067d460
  int GetState() const;                              // @ 0x0067d470
  bool InitPointers();                               // @ 0x0067d490
  unsigned int GetPosition(int positionType) const;  // @ 0x0067d530

  unsigned int mGap00[3];          // +0x00
  void* mpInputStream;             // +0x0c
  eCompressedFormat mFormat;       // +0x10
  bool mbOpen;                     // +0x14
  bool mbEOF;                      // +0x15
  bool mbInited;                   // +0x16
  z_stream_s* mpZLibStream;        // +0x18
  unsigned char* mpInputBuffer;    // +0x1c
  unsigned int mnInputBufferSize;  // +0x20
};
}
}
// ---- items of slice s0067c450 end

// ---- items of slice s0067d550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __fastcall _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __fastcall _InterlockedDecrement(long volatile*);
extern "C" uint32_t __cdecl crc32(uint32_t crc, const uint8_t* buf, uint32_t len);
#pragma intrinsic(_InterlockedExchange_s0067_d550)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedDecrement)
namespace EA {
namespace IO {
class IStream_s0067_d550 {
 public:
  IStream_s0067_d550() {}
  virtual ~IStream_s0067_d550();
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);        // +0x30
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);     // +0x38
};
}
}
namespace EA {
namespace IO {
template <typename T>
class AutoRefT {
 public:
  T* mpObject;
  AutoRefT() : mpObject(0) {}
  AutoRefT& operator=(T* pObject) {
    if (pObject != mpObject) {
      pObject->AddRef();
      T* pOld = mpObject;
      mpObject = pObject;
      if (pOld) pOld->Release();
    }
    return *this;
  }
  ~AutoRefT();
};
}
}
extern "C" long __fastcall _InterlockedExchange_s0067_d550(long volatile*, long);
extern "C" int __cdecl deflate(z_stream_s*, int);
extern "C" int __cdecl deflateReset(z_stream_s*);
extern "C" int __cdecl deflateInit2_(z_stream_s*, int level, int method, int windowBits,
                                     int memLevel, int strategy, const char* version, int streamSize);
extern "C" int __cdecl inflate(z_stream_s*, int);
extern "C" int __cdecl inflateInit_(z_stream_s*, const char* version, int streamSize);
extern "C" int __cdecl inflateReset(z_stream_s*);
namespace EA {
namespace IO {
struct AtomicIntT {
  volatile long mValue;
  AtomicIntT() { _InterlockedExchange_s0067_d550(&mValue, 0); }
};
}
}
namespace EA {
namespace IO {
class RefCountAtomicBase {
 public:
  RefCountAtomicBase() {}
  virtual ~RefCountAtomicBase() {}
  AtomicIntT mRefCount;
};
}
}
namespace EA {
namespace IO {
class StreamCompressionZLib_s0067_d550 : public IStream_s0067_d550, public RefCountAtomicBase {
 public:
  StreamCompressionZLib_s0067_d550(IStream_s0067_d550* pOutputStream, int nHint);   // @ 0x0067da60
  ~StreamCompressionZLib_s0067_d550();                                   // @ 0x0067db10

  bool InitPointers();                                        // 0x0067d330
  bool Open(IStream_s0067_d550* pStream, int nHint);                     // @ 0x0067d550 (direct call in ctor)
  bool Close();                                               // @ 0x0067d720
  bool WriteData(const void* pData, uint32_t nSize);          // @ 0x0067d680 (IStream::Write)

  AutoRefT<IStream_s0067_d550> mOutputStream;  // +0x0c
  bool mbOpen;                      // +0x10
  bool mbInited;                    // +0x11
  z_stream_s* mpZLibStream;         // +0x14
  eCompressedFormat mFormat;        // +0x18
  int mHint;                        // +0x1c
  uint8_t* mpOutputBuffer;          // +0x20
  uint32_t mnOutputBufferSize;      // +0x24
  uint32_t mInputCRC;               // +0x28
  uint32_t mInputSize;              // +0x2c
};
}
}
namespace EA {
namespace IO {
class StreamDecompressionZLib_s0067_d550 : public IStream_s0067_d550, public RefCountAtomicBase {
 public:
  StreamDecompressionZLib_s0067_d550(int unusedArg);   // @ 0x0067d800
  ~StreamDecompressionZLib_s0067_d550();               // @ 0x0067dbc0

  bool InitPointers();                      // 0x0067d490
  bool Open(IStream_s0067_d550* pStream);              // @ 0x0067d890
  bool Close();                              // @ 0x0067da10
  int ReadData(void* pData, uint32_t nSize); // @ 0x0067d960 (IStream::Read)

  AutoRefT<IStream_s0067_d550> mInputStream;   // +0x0c
  eCompressedFormat mFormat;        // +0x10
  bool mbOpen;                      // +0x14
  bool mbEOF;                       // +0x15
  bool mbInited;                    // +0x16
  z_stream_s* mpZLibStream;         // +0x18
  uint8_t* mpInputBuffer;           // +0x1c
  uint32_t mnInputBufferSize;       // +0x20
};  // namespace IO
}
}
namespace EA {
namespace Internet {
class RCAtomicBlock {
 public:
  virtual ~RCAtomicBlock() {}
  int Release();  // emitted for the RC base sub-object view (this = derived+4)
  volatile long mRefCount;
};
}
}
// ---- items of slice s0067d550 end

// @ 0x0067d280
namespace EA { namespace IO {
bool StreamCompressionZLib::SetCompressedFormat(eCompressedFormat fmt)
{
  if (fmt != kCompressedFormatZLib && fmt != kCompressedFormatGZip) return false;
  mFormat = fmt;
  return true;
}
}}  // namespace EA::IO

// @ 0x0067d2a0
namespace EA { namespace IO {
bool StreamCompressionZLib::SetBufferSize(unsigned int size)
{
  if (!mbOpen) {
    mnOutputBufferSize = size;
    if (mpOutputBuffer != 0) {
      eaFree(mpOutputBuffer);
      mpOutputBuffer = 0;
    }
    return true;
  }
  return false;
}
}}  // namespace EA::IO

// @ 0x0067d2e0
namespace EA { namespace IO {
bool StreamCompressionZLib::SetCompressionHint(int hint)
{
  if ((unsigned int)(hint + 1) <= 0xa) {
    mHint = hint;
    return true;
  }
  return false;
}
}}  // namespace EA::IO

// @ 0x0067d300
namespace EA { namespace IO {
int StreamCompressionZLib::GetAccessFlags() const
{
  return mbOpen ? 2 : 0;
}
}}  // namespace EA::IO

// @ 0x0067d310
namespace EA { namespace IO {
int StreamCompressionZLib::GetState() const
{
  if (mbOpen && mpZLibStream != 0) return mpZLibStream->msg ? -1 : 0;
  return -2;
}
}}  // namespace EA::IO

// @ 0x0067d3f0
namespace EA { namespace IO {
unsigned int StreamCompressionZLib::GetPosition(int positionType) const
{
  if (positionType == 0 && mbOpen && mpZLibStream != 0) return mpZLibStream->total_in;
  return 0xffffffff;
}
}}  // namespace EA::IO

// @ 0x0067d410
namespace EA { namespace IO {
bool StreamDecompressionZLib::SetCompressedFormat(eCompressedFormat fmt)
{
  return fmt == kCompressedFormatZLib;
}
}}  // namespace EA::IO

// @ 0x0067d420
namespace EA { namespace IO {
bool StreamDecompressionZLib::SetBufferSize(unsigned int size)
{
  if (!mbOpen) {
    mnInputBufferSize = size;
    if (mpInputBuffer != 0) {
      eaFree(mpInputBuffer);
      mpInputBuffer = 0;
    }
    return true;
  }
  return false;
}
}}  // namespace EA::IO

// @ 0x0067d460
namespace EA { namespace IO {
int StreamDecompressionZLib::GetAccessFlags() const
{
  return mbOpen != false;
}
}}  // namespace EA::IO

// @ 0x0067d470
namespace EA { namespace IO {
int StreamDecompressionZLib::GetState() const
{
  if (mbOpen && mpZLibStream != 0) return mpZLibStream->msg ? -1 : 0;
  return -2;
}
}}  // namespace EA::IO

// @ 0x0067d530
namespace EA { namespace IO {
unsigned int StreamDecompressionZLib::GetPosition(int positionType) const
{
  if (positionType == 0 && mbOpen && mpZLibStream != 0) return mpZLibStream->total_out;
  return 0xffffffff;
}
}}  // namespace EA::IO

// @ 0x0067d550
bool EA::IO::StreamCompressionZLib_s0067_d550::Open(IStream_s0067_d550* pStream, int nHint)
{
  bool result = false;
  if (pStream) {
    if (nHint != -1) mHint = nHint;
    mOutputStream = pStream;
    bool wasInited = mbInited;
    if (InitPointers()) {
      if (!wasInited) {
        if (mFormat == kCompressedFormatGZip) {
          deflateInit2_(mpZLibStream, mHint, 8, -15, 8, 1, "1.2.3", sizeof(z_stream_s));
          uint8_t hdr[10];
          hdr[0] = 0x1f;
          hdr[1] = 0x8b;
          hdr[2] = 8;
          hdr[3] = 0;
          hdr[4] = 0;
          hdr[5] = 0;
          hdr[6] = 0;
          hdr[7] = 0;
          hdr[8] = 0;
          hdr[9] = 3;
          mOutputStream.mpObject->Write(hdr, 10);
          mInputSize = 0;
          mInputCRC = crc32(0, 0, 0);
          result = (mFormat == kCompressedFormatGZip);
        } else {
          result = (deflateInit2_(mpZLibStream, mHint, 8, 15, 8, 1, "1.2.3",
                                  sizeof(z_stream_s)) == 0);
        }
      } else {
        result = (deflateReset(mpZLibStream) == 0);
      }
    }
  }
  mbOpen = result;
  return result;
}

// @ 0x0067d680
bool EA::IO::StreamCompressionZLib_s0067_d550::WriteData(const void* pData, uint32_t nSize)
{
  bool result = mbOpen;
  if (result) {
    mpZLibStream->avail_in = nSize;
    mpZLibStream->next_in = (const uint8_t*)pData;
    do {
      if (mpZLibStream->avail_in == 0) break;
      int r = deflate(mpZLibStream, 0);
      result = (r != -2);
      if (mpZLibStream->avail_out == 0) {
        mOutputStream.mpObject->Write(mpOutputBuffer, mnOutputBufferSize);
        mpZLibStream->avail_out = mnOutputBufferSize;
        mpZLibStream->next_out = mpOutputBuffer;
      }
    } while (result);
    if (mFormat == kCompressedFormatGZip) {
      mInputSize += nSize;
      mInputCRC = crc32(mInputCRC, (const uint8_t*)pData, nSize);
    }
  }
  return result;
}

// @ 0x0067d720
bool EA::IO::StreamCompressionZLib_s0067_d550::Close()
{
  bool result = true;
  if (mbOpen) {
    int r = deflate(mpZLibStream, 4);
    while (r == 0) {
      mOutputStream.mpObject->Write(mpOutputBuffer, mnOutputBufferSize);
      mpZLibStream->avail_out = mnOutputBufferSize;
      mpZLibStream->next_out = mpOutputBuffer;
      r = deflate(mpZLibStream, 4);
    }
    result = (r == 1);
    if (result) {
      result = mOutputStream.mpObject->Write(mpOutputBuffer,
                                             mnOutputBufferSize - mpZLibStream->avail_out);
      if (mFormat == kCompressedFormatGZip) {
        struct Tail {
          uint32_t crc;
          uint32_t size;
        } tail;
        tail.crc = mInputCRC;
        tail.size = mInputSize;
        result = result && mOutputStream.mpObject->Write(&tail, 8);
      }
    }
    mbOpen = false;
  }
  if (mOutputStream.mpObject) {
    IStream_s0067_d550* p = mOutputStream.mpObject;
    mOutputStream.mpObject = 0;
    p->Release();
  }
  return result;
}

// @ 0x0067d800
EA::IO::StreamDecompressionZLib_s0067_d550::StreamDecompressionZLib_s0067_d550(int unusedArg)
{
  (void)unusedArg;
  mInputStream.mpObject = 0;
  mFormat = kCompressedFormatZLib;
  mbOpen = false;
  mbEOF = false;
  mbInited = false;
  mpZLibStream = 0;
  mpInputBuffer = 0;
  mnInputBufferSize = 0x2000;
}

// @ 0x0067d890
bool EA::IO::StreamDecompressionZLib_s0067_d550::Open(IStream_s0067_d550* pStream)
{
  bool result = false;
  if (pStream) {
    mInputStream = pStream;
    bool wasInited = mbInited;
    if (InitPointers()) {
      uint32_t nRead = mInputStream.mpObject->Read(mpInputBuffer, mnInputBufferSize);
      mpZLibStream->avail_in = nRead;
      mpZLibStream->next_in = mpInputBuffer;
      mbEOF = (mpZLibStream->avail_in != mnInputBufferSize);
      result = (nRead != (uint32_t)-1);
      if (result) {
        if (wasInited) {
          mbOpen = (inflateReset(mpZLibStream) == 0);
          return mbOpen;
        }
        result = (inflateInit_(mpZLibStream, "1.2.3", sizeof(z_stream_s)) == 0);
      }
    }
  }
  mbOpen = result;
  return result;
}

// @ 0x0067d960
int EA::IO::StreamDecompressionZLib_s0067_d550::ReadData(void* pData, uint32_t nSize)
{
  bool ok = mbOpen;
  if (ok) {
    mpZLibStream->avail_out = nSize;
    mpZLibStream->next_out = (uint8_t*)pData;
    int r;
    do {
      if (mpZLibStream->avail_in == 0) {
        uint32_t nRead = mInputStream.mpObject->Read(mpInputBuffer, mnInputBufferSize);
        mpZLibStream->avail_in = nRead;
        ok = (nRead != (uint32_t)-1);
        mpZLibStream->next_in = mpInputBuffer;
      }
      r = inflate(mpZLibStream, 0);
      ok = ok && (r != -2);
      mbEOF = (r == 1);
      if (!ok) return -1;
    } while (mpZLibStream->avail_out != 0 && r != 1);
    if (ok) return nSize - mpZLibStream->avail_out;
  }
  return -1;
}

// @ 0x0067da10
bool EA::IO::StreamDecompressionZLib_s0067_d550::Close()
{
  mbOpen = false;
  IStream_s0067_d550* p = mInputStream.mpObject;
  if (p) {
    mInputStream.mpObject = 0;
    p->Release();
  }
  return true;
}

// @ 0x0067da30
int EA::Internet::RCAtomicBlock::Release()
{
  if (_InterlockedDecrement(&mRefCount) == 0) {
    _InterlockedExchange_s0067_d550(&mRefCount, 1);
    delete this;
  }
  return 0;
}

// @ 0x0067da60
EA::IO::StreamCompressionZLib_s0067_d550::StreamCompressionZLib_s0067_d550(IStream_s0067_d550* pOutputStream, int nHint)
{
  mOutputStream.mpObject = 0;
  mbOpen = false;
  mbInited = false;
  mpZLibStream = 0;
  mFormat = kCompressedFormatZLib;
  mHint = nHint;
  mpOutputBuffer = 0;
  mnOutputBufferSize = 0x2000;
  if (pOutputStream) Open(pOutputStream, nHint);
}
