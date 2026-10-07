#pragma once
#include "types.h"

// Shared stubs for slice s0067d550 (declared here so both this slice and
// follow-up slices can reuse the shapes).
namespace EA {
namespace IO {

class IStream {
 public:
  IStream() {}
  virtual ~IStream() {}
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

// AutoRefCount<IStream>-shaped member: assign attaches (AddRef slot1, Release slot2).
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
  ~AutoRefT() {
    T* p = mpObject;
    if (p) p->Release();
  }
};

}  // namespace IO
}  // namespace EA

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
