// src/game/SPAudio/_at_00a00000.cpp -- migrated from slice(s) s00a0f350 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureAnimManager.h"
#include "EA/ArgScript/cCommandBase.h"
#include <string.h>

// ---- items of slice s00a0f350 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
namespace EA {
namespace Audio {
class Command_s00a0_f350 {
public:
    u8* mCommandStart;
    u8* mCommandEnd;
    u8* mCommandPtr;
    u32 mCommandId;
    u32 mCommandSize;
    u32 mNumParameters;

    void Clear() {
        mCommandStart = 0; mCommandEnd = 0; mCommandPtr = 0;
        mCommandId = 0; mCommandSize = 0; mNumParameters = 0;
    }
    void Load(u32* p) {
        mCommandStart = (u8*)p;
        mCommandId = *p++;
        mCommandSize = *p++;
        mNumParameters = *p++;
        mCommandPtr = (u8*)p;
        mCommandEnd = mCommandPtr + mCommandSize;
    }
    u8*  EnumParameter(u32* pos, u32* id, u32* type, int* size);  // 0x00a0f880 (EA::Audio::Command::EnumParameter)
    void* Find(int id, int* type, int* size);  // 0x00a0f8e0 (EA::Audio::Command::Find)
    bool SetT1(int id, int* type, int* size);
    bool GetFloat(int id, float* out);
    bool GetUint32(int id, u32* out);  // 0x00a0fab0 (EA::Audio::Command::GetUint32)
    bool GetString8(int id, char* buf, u32* pSize);  // 0x00a0faf0 (EA::Audio::Command::GetString8)
    const char* GetString8(int id);  // 0x00a0fb60 (EA::Audio::Command::GetString8)
    bool GetVoidPtr(int id, void** out);  // 0x00a0fb90 (EA::Audio::Command::GetVoidPtr)
    void* GetData(int id, void** out);  // 0x00a0fbd0 (EA::Audio::Command::GetData)
    bool GetVector3(int id, float* out);  // 0x00a0fc10 (EA::Audio::Command::GetVector3)
    bool GetMatrix33(int id, float* out);  // 0x00a0fc60 (EA::Audio::Command::GetMatrix33)
    bool SetUint64(int id, u32 v);  // 0x00a0fcf0 (EA::Audio::Command::SetUint64)
    bool SetFloat(int id, float v);  // 0x00a0fd30 (EA::Audio::Command::SetFloat)
    void DeleteParameter(int id);  // 0x00a0fd70 (EA::Audio::Command::DeleteParameter)
};
}  // namespace
}
template <class T> inline void swap(T& a, T& b) { T t = a; a = b; b = t; }
struct FVec {                    // fixed-buffer vector; heap-owned when begin[-1] != 0
    u32* mBegin; u32* mEnd; u32* mCap;
    FVec(const FVec& o);         // 0x473140
    void assign(const FVec& o);  // 0x6f6770
    ~FVec() { if (mBegin && ((int*)mBegin)[-1] != 0) delete[] (char*)mBegin; }
    void Swap(FVec& o);
};
struct CmdQueue {
    u32 mBegin, mEnd, mCap;      // +0 (fixed vector)
    u8  pad[0x14 - 0xc];
    EA::Audio::Command_s00a0_f350 mCmd;     // +0x14
    u32 mWrite;                  // +0x2c
    u32 mRead;                   // +0x30
    u32 mCmdBase;                // +0x34
    u32 mSizePtr;                // +0x38
    u32 mCountPtr;               // +0x3c
    u32 mNumCmds;                // +0x40
    u32 mCapacity;               // +0x44
    u32 mParamCount;             // +0x48
    u32 mReadIndex;              // +0x4c

    CmdQueue();
    void Swap(CmdQueue* o);
    void Grow(u32 n);
    void ResizeBuffer(u32 n);   // 0x4c0410
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
    void Ensure4() { if ((u32)((mBegin - mWrite) + mCapacity) < 4) Grow((mEnd - mBegin) * 2); }
    void Put(u32 v) { Ensure4(); *(u32*)mWrite = v; mWrite += 4; }
};
// ---- items of slice s00a0f350 end

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
{
    mBegin = 0; mEnd = 0; mCap = 0;
    mWrite = 0; mRead = 0; mCmdBase = 0; mSizePtr = 0; mCountPtr = 0;
    mNumCmds = 0; mCapacity = 0; mParamCount = 0; mReadIndex = 0;
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

// @ 0x00a0ff50
void CmdQueue::Grow(u32 n)
{
    if (mWrite) mWrite -= mBegin;
    if (mRead) mRead -= mBegin;
    if (mCmdBase) mCmdBase -= mBegin;
    if (mSizePtr) mSizePtr -= mBegin;
    if (mCountPtr) mCountPtr -= mBegin;
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
            mWrite += (size + 3) & ~3u;
            return;
        }
        memcpy((void*)mWrite, data, size);
    }
    mWrite += (size + 3) & ~3u;
}
