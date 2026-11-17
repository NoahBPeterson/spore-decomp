// src/game/SPAudio/_at_00a00000.cpp
// The SPAudio command queue: a byte buffer of 4-byte-aligned command records that is written, swapped and read back.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int u32;

void __cdecl FVec_free(void*) throw();   // 0x00f47380

// Fixed-buffer vector; the buffer is heap-owned when the word before begin is non-zero.
struct FVec {
    u32* mBegin;
    u32* mEnd;
    u32* mCap;
    u32 mFixedBegin, mFixedEnd;   // +0x0c: fixed-buffer bookkeeping, not touched by Swap
    FVec(const FVec& o);         // 0x473140
    void assign(const FVec& o);  // 0x6f6770
    ~FVec() { if (mBegin && ((int*)mBegin)[-1] != 0) FVec_free(mBegin); }
    void Swap(FVec& o);
};

struct CmdQueue {
    u32 mBegin, mEnd, mCap;                 // +0x00: the FVec part
    u8  pad0c[0x14 - 0x0c];
    EA::Audio::Command mCmd;                // +0x14
    u32 mWrite;                             // +0x2c
    u32 mRead;                              // +0x30
    u32 mCmdBase;                           // +0x34
    u32 mSizePtr;                           // +0x38
    u32 mCountPtr;                          // +0x3c
    u32 mNumCmds;                           // +0x40
    u32 mCapacity;                          // +0x44
    u32 mParamCount;                        // +0x48
    u32 mReadIndex;                         // +0x4c

    CmdQueue();
    void Swap(CmdQueue* o);
    void Grow(u32 n);
    void ResizeBuffer(u32 n);               // 0x4c0410
    void Append(const void* data, u32 size);
    void AddFloat(u32 id, u32 v);
    void AddUint32(u32 id, u32 v);
    void AddVoidPtr(u32 id, u32 v);
    bool Reset(u32 n);
    void FinishCommand();
    void CancelCommand();
    bool ReadNext();
    void BeginRead();
    void RewindRead();
    void Clear();
};

// Exchanges two values of the same type.
template <class T> inline void swap(T& a, T& b) { T t = a; a = b; b = t; }

// @ 0x00a0fdc0
void CmdQueue::RewindRead()
{
    mReadIndex = 0;
    mRead = mBegin;
}

// @ 0x00a0fdd0
void CmdQueue::Clear()
{
    mWrite = mBegin;
    mCmdBase = 0;
    mSizePtr = 0;
    mCountPtr = 0;
    mNumCmds = 0;
    mParamCount = 0;
    mRead = 0;
    mReadIndex = 0;
}

// @ 0x00a0fdf0
CmdQueue::CmdQueue()
    : mBegin(0), mEnd(0), mCap(0),
      mWrite(0), mRead(0), mCmdBase(0), mSizePtr(0), mCountPtr(0),
      mNumCmds(0), mCapacity(0), mParamCount(0), mReadIndex(0)
{
}

// @ 0x00a0fe20
void FVec::Swap(FVec& o)
{
    u32* a = mBegin;
    if ((a == 0 || ((int*)a)[-1] != 0) && (o.mBegin == 0 || ((int*)o.mBegin)[-1] != 0)) {
        swap(mBegin, o.mBegin);
        swap(mEnd, o.mEnd);
        swap(mCap, o.mCap);
    } else {
        FVec tmp(*this);
        assign(o);
        o.assign(tmp);
    }
}

// @ 0x00a0fee0
void CmdQueue::Swap(CmdQueue* o)
{
    ((FVec*)this)->Swap(*(FVec*)o);
    swap(mWrite, o->mWrite);
    if (mWrite == mEnd) mWrite = mBegin;
    swap(mCmdBase, o->mCmdBase);
    swap(mSizePtr, o->mSizePtr);
    swap(mCountPtr, o->mCountPtr);
    swap(mNumCmds, o->mNumCmds);
    swap(mCapacity, o->mCapacity);
}

// Command records are padded to a multiple of 4 bytes.
static inline u32 Align4(u32 n) { return (n + 3) & ~3u; }

// Turns a non-null buffer pointer into an offset from the buffer start.
static inline void ToOffset(u32& p, u32 base) { if (p) p -= base; }

// @ 0x00a0ff50
void CmdQueue::Grow(u32 n)
{
    ToOffset(mWrite, mBegin);
    ToOffset(mRead, mBegin);
    ToOffset(mCmdBase, mBegin);
    ToOffset(mSizePtr, mBegin);
    ToOffset(mCountPtr, mBegin);
    ResizeBuffer(n);
    mCapacity = n;
    if (mWrite) mWrite = mBegin + mWrite;
    if (mRead) mRead = mBegin + mRead;
    if (mCmdBase) mCmdBase = mBegin + mCmdBase;
    if (mSizePtr) mSizePtr = mBegin + mSizePtr;
    if (mCountPtr) mCountPtr = mBegin + mCountPtr;
}

// @ 0x00a0fff0
void CmdQueue::Append(const void* data, u32 size)
{
    if ((u32)((mCapacity - mWrite) + mBegin) < size)
        Grow((mEnd - mBegin) * 2);
    if (data) {
        if (size <= 4) {
            *(u32*)mWrite = *(const u32*)data;
            mWrite += Align4(size);
            return;
        }
        memcpy((void*)mWrite, data, size);
    }
    mWrite += Align4(size);
}
