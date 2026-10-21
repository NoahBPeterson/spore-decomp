// src/game/SPEditors/SPEditorResourceStream.cpp -- migrated from slice(s) s005cb060 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorResourceStream.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Message.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayout.h"
#include "cSPUIPropertyLayout.h"
#include "SP/cString.h"
#include <new>
#include <string.h>

// ---- items of slice s005cb060 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RefCountVTemplate_s005c_b060 {
 public:
  RefCountVTemplate_s005c_b060() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_b060() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_b060 {
 public:
  ~IUnknown32_s005c_b060() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual int GetTypeID() const;
  virtual void* Cast(uint32_t typeID) const = 0;  // +0xc
};  // namespace COM
}
}
struct HeapBlock {
  uint32_t mSize;
  uint32_t mFlags;
};
struct HeapFreeNode {
  uint32_t mSize;
  HeapBlock* mpBlock;
};
struct HeapHeader {
  uint32_t mMagic;
  uint32_t mCapacity;
  uint32_t mFreeSize;
  HeapFreeNode* mpFirstFree;
  uint32_t mFlags10;
};
class cStreamBuffer {
 public:
  cStreamBuffer();
  bool Open(void* target);                       // 0x004bd9f0
  int GetSize();                                 // 0x004bdbd0
  bool Write(const void* data, int size, bool flush);  // 0x004bdc60
  bool Finish();                                 // 0x004be5d0
  void Reset();                                  // 0x004bdae0
  void destroy_shared();                         // 0x004bca10
  ~cStreamBuffer() {
    if (mpHeap && (mpHeap->mFlags10 & 0x40000000))
      destroy_shared();
    mpHeap = 0;
  }
  HeapHeader* mpHeap;
  uint32_t mBuffer[0x42b4 / 4];
};
struct IStream { private:
 public:
  ~IStream() {}
  virtual int GetState();                          // +0x0
  virtual int GetSize();                           // +0x4
  virtual int GetValue(int which);                 // +0x8
  virtual int Matches(int value, int which);      // +0xc
  virtual bool Write(const void* data, int size);  // +0x10
  virtual bool Close();                            // +0x14
  virtual void Flush();                            // +0x18
};
class cBufferedStream : public EA::RefCountVTemplate_s005c_b060<int>, public IStream {
 public:
  cBufferedStream();
  virtual ~cBufferedStream();
  virtual int GetState();
  virtual int GetSize();
  virtual int GetValue(int which);
  virtual int Matches(int value, int which);
  virtual bool Write(const void* data, int size);
  virtual bool Close();
  bool Open(EA::COM::IUnknown32_s005c_b060* target);

  bool mbOpen;                        // +0xc
  bool mbOK;                          // +0xd
  int mPosition;                      // +0x10
  cStreamBuffer mBuffer;              // +0x14
  EA::COM::IUnknown32_s005c_b060* mpTarget;      // +0x42cc
};
// ---- items of slice s005cb060 end

// @ 0x005cbca0
int cBufferedStream::GetState()
{
  return mbOpen ? 2 : 0;
}

// @ 0x005cbcb0
int cBufferedStream::GetSize()
{
  if (mbOpen) {
    if (!mbOK)
      return mBuffer.GetSize();
    return 0;
  }
  return -2;
}

// @ 0x005cbcd0
int cBufferedStream::GetValue(int which)
{
  switch (which) {
    case 0:
      return mPosition;
    case 1:
      return 0;
    case 2:
      return -1;
  }
  return -1;
}

// @ 0x005cbd00
int cBufferedStream::Matches(int value, int which)
{
  if ((which == 0 && value == mPosition) || (which == 1 && value == 0))
    return 1;
  return 0;
}

// @ 0x005cbd90
bool cBufferedStream::Write(const void* data, int size)
{
  if (mbOpen && mpTarget) {
    mbOK = mBuffer.Write(data, size, false);
    mPosition += size;
    return mbOK;
  }
  return false;
}

// @ 0x005cbdd0
bool cBufferedStream::Close()
{
  if (mbOpen && mbOK) {
    mbOK = mBuffer.Write(0, 0, true);
    mbOK = mbOK && mBuffer.Finish();
  }
  mbOpen = false;
  if (mpTarget) {
    mpTarget->Release();
    mpTarget = 0;
  }
  mBuffer.Reset();
  return mbOK;
}
