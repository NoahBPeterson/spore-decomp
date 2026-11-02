// src/game/SPMovie/bufferedwriter.cpp -- migrated from slice(s) s00fc8450, s00fc7430 by tools/migrate/rewrite.py
// Object file: SPMovie/bufferedwriter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ICoreAllocator.h"

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace movie {
struct BufferedWriter {
  uint8_t mPad00[8];   // +0x00
  void*   mpBuffer08;  // +0x08
  int     mSize0c;     // +0x0c
  int     mOffset10;   // +0x10

  void SetBuffer(void* buf, int size);  // 0x00fc8390
};
}
}
typedef void (__cdecl* FnCB5)(int, int, int, int, int);
struct Writer {
  FnCB5 mpCallback;    // +0x00
  int   mField04;      // +0x04
  int   mField08;      // +0x08
  int   mField0c;      // +0x0c
  int   mField10;      // +0x10
  int   mField14;      // +0x14
  int   mField18;      // +0x18
  int   mField1c;      // +0x1c

  void Flush();        // 0x00fc83b0
};
// ---- items of slice s00fc7430 end

// ---- items of slice s00fc8450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);
extern "C" void* __cdecl memset(void* dst, int value, unsigned int size);
#define SP_MIN(a, b) ((a) <= (b) ? (a) : (b))
namespace rw {
namespace movie {
struct BufferedWriter_s00fc_8450 {
    char           pad00[8];
    unsigned char* mBuffer;                     // +0x08
    int            mCapacity;                   // +0x0c
    int            mPos;                        // +0x10
    int            mBase;                       // +0x14
    int            mEnd;                        // +0x18

    void Flush();                                                     // 0x00fc83b0
    void Seek(int offset, int origin);                                // 0x00fc8450
    void Write(const void* data, int count);                          // 0x00fc84b0
    void WriteFill(unsigned char value, int count);                   // 0x00fc8500
    void Write16(unsigned short value);                               // 0x00fc8550
    void Write32(unsigned int value);                                 // 0x00fc8580
};
}
}
// ---- items of slice s00fc8450 end

// @ 0x00fc8390
void rw::movie::BufferedWriter::SetBuffer(void* buf, int size)
{
  mpBuffer08 = buf;
  mSize0c = size;
  mOffset10 = 0;
}

// @ 0x00fc83b0
void Writer::Flush()
{
  FnCB5 cb = mpCallback;
  if (cb == 0)
    return;

  int delta = mField1c;
  if (delta == mField14) {
    if (delta == 0) {
      cb(mField08, mField10, 0, 1, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    } else if (delta == mField18) {
      cb(mField08, mField10, 0, 2, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    } else {
      cb(mField08, mField10, 0, 3, mField04);
      delta = mField10;
      mField1c = mField1c + delta;
    }
  } else {
    cb(mField08, mField10, mField14 - delta, 3, mField04);
    delta = mField10;
    mField1c = mField14 + delta;
  }

  if (mField1c > mField18)
    mField18 = mField1c;
  mField14 = mField14 + delta;
  mField10 = 0;
}

// @ 0x00fc8450
namespace rw { namespace movie {
void BufferedWriter_s00fc_8450::Seek(int offset, int origin)
{
    int delta = offset;
    if (origin == 1) {
        delta = offset - mBase - mPos;
    } else if (origin == 2) {
        delta = mEnd - mBase - mPos + offset;
    }
    if (delta == 0)
        return;
    int newPos = mPos + delta;
    if (newPos > 0 && newPos < mCapacity && mBase == mEnd) {
        mPos = newPos;
        return;
    }
    Flush();
    mBase += delta;
}
}}  // namespace rw::movie

// @ 0x00fc84b0
namespace rw { namespace movie {
void BufferedWriter_s00fc_8450::Write(const void* data, int count)
{
    while (count > 0) {
        int n = SP_MIN(mCapacity - mPos, count);
        memcpy(mBuffer + mPos, data, n);
        mPos += n;
        if (mPos == mCapacity)
            Flush();
        count -= n;
        data = (const char*)data + n;
    }
}
}}  // namespace rw::movie

// @ 0x00fc8500
namespace rw { namespace movie {
void BufferedWriter_s00fc_8450::WriteFill(unsigned char value, int count)
{
    while (count > 0) {
        int n = SP_MIN(mCapacity - mPos, count);
        memset(mBuffer + mPos, value, n);
        mPos += n;
        if (mPos == mCapacity)
            Flush();
        count -= n;
    }
}
}}  // namespace rw::movie

// @ 0x00fc8550
namespace rw { namespace movie {
void BufferedWriter_s00fc_8450::Write16(unsigned short value)
{
    if (mCapacity - mPos < 2)
        Flush();
    *(unsigned short*)(mBuffer + mPos) = value;
    mPos += 2;
}
}}  // namespace rw::movie

// @ 0x00fc8580
namespace rw { namespace movie {
void BufferedWriter_s00fc_8450::Write32(unsigned int value)
{
    if (mCapacity - mPos < 4)
        Flush();
    *(unsigned int*)(mBuffer + mPos) = value;
    mPos += 4;
}
}}  // namespace rw::movie
