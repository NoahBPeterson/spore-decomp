// EA::Audio::Command parameter accessors and the command queue writer.
// Object file: SPAudio/AudioCommandQueue.obj.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned int   u32;

// A command's parameters are packed as a three-word header (id, size, type) followed by
// a payload padded up to 4 bytes.  These are the type codes the accessors accept.
enum ParameterType {
    kTypeFloat    = 0,
    kTypeUint32   = 1,
    kTypeString8  = 3,
    kTypeVoidPtr  = 4,
    kTypeData     = 5,
    kTypeVector3  = 6,
    kTypeMatrix33 = 7,
};
enum {
    kParamHeaderSize = 0xc,          // three words: id, size, type
    kParamAlignMask  = 0xfffffffc,   // round a payload size down to a 4-byte boundary
};

// The queue's reader functions (still in nonmatching.txt) use the dev-only Load/Clear
// helpers, so this file keeps a stand-in for EA::Audio::Command that carries them; the
// parameter accessors below are defined on the canonical class (src/game/include/EA/Audio/Command.h).
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
};
}  // namespace Audio
}  // namespace EA

// Ring buffer of packed audio commands, laid out from the retail assembly.
struct CmdQueue {
    u32 mBegin, mEnd, mCap;      // +0 fixed vector: base, end, capacity
    u8  pad[0x14 - 0xc];         // +0xc reserved up to the embedded command
    EA::Audio::Command_s00a0_f350 mCmd;     // +0x14 command being read
    u32 mWrite;                  // +0x2c write cursor
    u32 mRead;                   // +0x30 read cursor
    u32 mCmdBase;                // +0x34 start of the command being written (0 = none)
    u32 mSizePtr;                // +0x38 address of the open command's size word
    u32 mCountPtr;               // +0x3c address of the open command's parameter count word
    u32 mNumCmds;                // +0x40 number of complete commands in the buffer
    u32 mCapacity;               // +0x44
    u32 mParamCount;             // +0x48 parameters in the open command
    u32 mReadIndex;              // +0x4c commands read so far

    void FinishCommand();
    void CancelCommand();
    bool ReadNext();
    void BeginRead();
};

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
    pos = pos + ((sz + 3U) & kParamAlignMask) + kParamHeaderSize;
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
            p = (u32*)((u8*)p + ((sz + 3U) & kParamAlignMask));
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
bool EA::Audio::Command_s00a0_f350::SetT1(int id, int* type, int* size)
{
    return Find(id, type, size) != 0;
}

// @ 0x00a0fa70
bool EA::Audio::Command_s00a0_f350::GetFloat(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeFloat)
        return false;
    *out = *p; return true;
}

// @ 0x00a0fab0
bool EA::Audio::Command_s00a0_f350::GetUint32(int id, u32* out)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeUint32)
        return false;
    *out = *p; return true;
}

// @ 0x00a0faf0
bool EA::Audio::Command_s00a0_f350::GetString8(int id, char* buf, u32* pSize)
{
    int type; int size;
    void* p = Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeString8)
        return false;
    if (pSize && (!buf || *pSize < (u32)size + 1)) {
        *pSize = size + 1;
        return false;
    }
    memcpy(buf, p, size);
    buf[size] = 0;
    return true;
}

// @ 0x00a0fb60
const char* EA::Audio::Command_s00a0_f350::GetString8(int id)
{
    int type; int size;
    const char* p = (const char*)Find(id, &type, &size);
    if (!p) return 0;
    return type == kTypeString8 ? p : 0;
}

// @ 0x00a0fb90
bool EA::Audio::Command_s00a0_f350::GetVoidPtr(int id, void** out)
{
    int type; int size;
    void** p = (void**)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeVoidPtr)
        return false;
    *out = *p; return true;
}

// @ 0x00a0fbd0
void* EA::Audio::Command_s00a0_f350::GetData(int id, void** out)
{
    int type; int size;
    void* p = Find(id, &type, &size);
    if (!p)
        return 0;
    if (type != kTypeData)
        return 0;
    if (out) *out = (void*)size;
    return p;
}

// @ 0x00a0fc10
bool EA::Audio::Command_s00a0_f350::GetVector3(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeVector3)
        return false;
    float x = p[0], y = p[1], z = p[2];
    out[0] = x; out[1] = y; out[2] = z;
    return true;
}

// @ 0x00a0fc60
bool EA::Audio::Command_s00a0_f350::GetMatrix33(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeMatrix33)
        return false;
    float a = p[0], b = p[1], c = p[2], d = p[3], e = p[4], f = p[5], g = p[6], h = p[7], i = p[8];
    out[0] = a; out[1] = b; out[2] = c; out[3] = d; out[4] = e; out[5] = f; out[6] = g; out[7] = h; out[8] = i;
    return true;
}

// @ 0x00a0fcf0
bool EA::Audio::Command_s00a0_f350::SetUint64(int id, u32 v)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeUint32)
        return false;
    *p = v; return true;
}

// @ 0x00a0fd30
bool EA::Audio::Command_s00a0_f350::SetFloat(int id, float v)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != kTypeFloat)
        return false;
    *p = v; return true;
}

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
                    p[-3] = kInvalidId;   // Command::kInvalidId; marks the parameter deleted
                return;
            }
            i++;
            p = (u32*)((u8*)p + ((sz + 3U) & kParamAlignMask));
        } while (i < mNumParameters);
    }
}
