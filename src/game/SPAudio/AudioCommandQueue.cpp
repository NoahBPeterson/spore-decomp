// src/game/SPAudio/AudioCommandQueue.cpp -- migrated from slice(s) s00a0f350 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioCommandQueue.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
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

// @ 0x00a0f880
void const * EA::Audio::Command::EnumParameter(unsigned int & pos, unsigned int * id, unsigned int * type, unsigned int * size) const
{
    u32 p = pos;
    if (p >= mCommandSize)
        return 0;
    u32* q = (u32*)(mCommandPtr + p);
    u32 rid = *q++;
    u32 sz = *q++;
    u32 ty = *q++;
    if (id) *id = rid;
    if (type) *type = ty;
    if (size) *size = sz;
    pos = pos + ((sz + 3U) & 0xfffffffc) + 0xc;
    return (u8*)q;
}

// @ 0x00a0f8e0
void * EA::Audio::Command::Find(unsigned int id, unsigned int * type, unsigned int * size) const
{
    u32* p = (u32*)mCommandPtr;
    u32 i = 0;
    if (mNumParameters > 0) {
        do {
            u32 pid = *p++;
            u32 sz = *p++;
            u32 ty = *p++;
            if (id == (int)pid) {
                if (type) *type = ty;
                if (size) *size = sz;
                return p;
            }
            i++;
            p = (u32*)((u8*)p + ((sz + 3U) & 0xfffffffc));
        } while (i < mNumParameters);
    }
    return 0;
}

// @ 0x00a0f940
void CmdQueue::FinishCommand()
{
    *(u32*)mSizePtr = (mWrite - mCountPtr) - 4;
    mNumCmds++;
    mCmdBase = 0;
    mSizePtr = 0;
    mCountPtr = 0;
    mParamCount = 0;
}

// @ 0x00a0f960
void CmdQueue::CancelCommand()
{
    if (mCmdBase != 0) {
        mWrite = mCmdBase;
        mCmdBase = 0;
        mSizePtr = 0;
        mCountPtr = 0;
    }
}

// @ 0x00a0f9a0
bool CmdQueue::ReadNext()
{
    if (mReadIndex >= mNumCmds)
        return false;
    u32* p = (u32*)mRead;
    mCmd.mCommandStart = (u8*)p;
    mCmd.mCommandId = *p++;
    mCmd.mCommandSize = *p++;
    mCmd.mNumParameters = *p++;
    mCmd.mCommandPtr = (u8*)p;
    mCmd.mCommandEnd = mCmd.mCommandPtr + mCmd.mCommandSize;
    mReadIndex++;
    mRead = (u32)mCmd.mCommandEnd;
    return mReadIndex <= mNumCmds;
}

// @ 0x00a0f9f0
void CmdQueue::BeginRead()
{
    mCmd.Clear();
    if (mCmdBase != 0) {
        *(u32*)mSizePtr = (mWrite - mCountPtr) - 4;
        mCmd.Load((u32*)mCmdBase);
    }
}

// @ 0x00a0fa50
namespace EA { namespace Audio {
bool Command_s00a0_f350::SetT1(int id, int* type, int* size)
{
    return Find(id, type, size) != 0;
}
}}  // namespace EA::Audio

// @ 0x00a0fa70
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetFloat(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 0)
        return false;
    *out = *p; return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fab0
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetUint32(int id, u32* out)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 1)
        return false;
    *out = *p; return true;
}
}}  // namespace EA::Audio

// @ 0x00a0faf0
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetString8(int id, char* buf, u32* pSize)
{
    int type; int size;
    void* p = Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 3)
        return false;
    if (pSize && (!buf || *pSize < (u32)size + 1)) {
        *pSize = size + 1;
        return false;
    }
    memcpy(buf, p, size);
    buf[size] = 0;
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fb60
namespace EA { namespace Audio {
const char* Command_s00a0_f350::GetString8(int id)
{
    int type; int size;
    const char* p = (const char*)Find(id, &type, &size);
    if (!p) return 0;
    return type == 3 ? p : 0;
}
}}  // namespace EA::Audio

// @ 0x00a0fb90
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetVoidPtr(int id, void** out)
{
    int type; int size;
    void** p = (void**)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 4)
        return false;
    *out = *p; return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fbd0
namespace EA { namespace Audio {
void* Command_s00a0_f350::GetData(int id, void** out)
{
    int type; int size;
    void* p = Find(id, &type, &size);
    if (!p)
        return 0;
    if (type != 5)
        return 0;
    if (out) *out = (void*)size;
    return p;
}
}}  // namespace EA::Audio

// @ 0x00a0fc10
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetVector3(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 6)
        return false;
    float a = p[0], b = p[1], c = p[2];
    out[0] = a; out[1] = b; out[2] = c;
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fc60
namespace EA { namespace Audio {
bool Command_s00a0_f350::GetMatrix33(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 7)
        return false;
    float a = p[0], b = p[1], c = p[2], d = p[3], e = p[4], f = p[5], g = p[6], h = p[7], i = p[8];
    out[0] = a; out[1] = b; out[2] = c; out[3] = d; out[4] = e; out[5] = f; out[6] = g; out[7] = h; out[8] = i;
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fcf0
namespace EA { namespace Audio {
bool Command_s00a0_f350::SetUint64(int id, u32 v)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 1)
        return false;
    *p = v; return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fd30
namespace EA { namespace Audio {
bool Command_s00a0_f350::SetFloat(int id, float v)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 0)
        return false;
    *p = v; return true;
}
}}  // namespace EA::Audio

// @ 0x00a0fd70
void EA::Audio::Command::DeleteParameter(unsigned int id)
{
    u32* p = (u32*)mCommandPtr;
    u32 i = 0;
    if (mNumParameters > 0) {
        do {
            u32 pid = *p++;
            u32 sz = *p++;
            p++;
            if (id == (int)pid) {
                if (p != 0)
                    p[-3] = 0xffffffff;
                return;
            }
            i++;
            p = (u32*)((u8*)p + ((sz + 3U) & 0xfffffffc));
        } while (i < mNumParameters);
    }
}
