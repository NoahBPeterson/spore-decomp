// Slice s00a0f350 - cSPCreatureAnimManager init/message handler, audio allocator wrappers,
// EA::Audio::Command parameter accessors and the command queue writer.
#include "types.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl operator new(size_t, const char*, int, int, int, int);

// ---------------------------------------------------------------------------
// cSPCreatureAnimManager::Init (0xa0f350) and HandleMessage (0xa0f610)
// ---------------------------------------------------------------------------
struct AnimMgr;

struct IServer {                 // EA::Messaging::Server
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void AddHandler(void* handler, u32 msgId);          // +0x24
};

struct IMaterialMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void* GetMaterial(u32 id);                           // +0x28
};

struct IRefObj {
    virtual void v0();
    virtual void Release();                                      // +4
};

struct IPropData {               // property value
    u32* mData;                  // +0
    u8   pad[0xc];
    u8   mFlags;                 // +0x10
    u8   pad2;
    u16  mType;                  // +0x12
};

struct IPropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual IPropData* GetProperty(u32 id);                      // +0x28
};

struct IPropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(u32 id, int, IRefObj** out);    // +0x2c
};

struct ICheatMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void AddCommand(const char* name, void* cmd, int);   // +0x18
};

struct IResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void* GetResource(u32 id, int, int);                 // +0x20
};

struct PtrVec {
    u32** mBegin;
    u32** mEnd;
    u32** mCap;
    void DoInsertValue(u32** pos, u32* const& v);
    void push_back(u32* const& v) {
        if (mEnd < mCap) { u32** p = mEnd++; if (p) *p = v; }
        else DoInsertValue(mEnd, v);
    }
};
struct AnimRefHolder {           // object at [mgr+0x84], vector at +8
    u8 pad[8];
    PtrVec mVec;
};

struct RefA { RefA(); u8 pad[0x1c]; };                 // 0x77d1d0
struct RefB { RefB(); void InsertResource(int, void*); u8 pad[0x70]; };   // 0x40d010 / 0x77cb10
struct RefC {                                          // 0x432cf0
    RefC();
    u8 pad[0xc];
    u8 mKind; u8 pad1[3];
    float mA, mB, mC, mD;
};

struct CmdBase { CmdBase(); virtual void Run() = 0; u8 pad[0xc]; };
struct BlocksModeCmd : CmdBase {
    AnimMgr* mMgr;
    virtual void Run() {}
};

struct AutoHandlerRec {
    IServer* mServer; void* mHandler; const u32* mIds; u32 mCount; u32 mFlag;
};

extern u32 g_animMsgIds[2];            // 0x155182c
extern u32 g_defaultPropVal[];         // 0x15d1164
extern AnimMgr* g_animMgr;             // 0x166cc08
extern struct SomeObj { bool Prep(); } g_obj_166c058;
extern struct SomeObj2 { void Fn(void*, int); } *g_obj_166c084;

IMaterialMgr* GetMaterialManager();
IResMgr*      GetResMgr();
IPropMgr*     GetPropertyManager();
IServer*      GetMessageServer();
ICheatMgr*    GetCheatManager();
void          FUN_00a059d0(AnimMgr*);
void*         FUN_009a37a0(void*);
void          FUN_009a4020(void*, int);
struct RefSlot { void Assign(void* p); };            // 0x41d8b0

struct AnimMgr {
    u8     pad0[0x4c];
    IPropList* mPropertyList;    // +0x50
    AutoHandlerRec mAuto;        // +0x54
    u8     pad1[0x80 - 0x68];
    void*  mMaterial;            // +0x80? see Init
    AnimRefHolder* mHolder;      // +0x84

    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void SetAppMode(u32 mode);                 // +0x3c

    void ReadAnimList(int);
    bool Init(bool flag);
};

// @ 0xa0f350
bool AnimMgr::Init(bool flag)
{
    g_animMgr = this;
    if (!g_obj_166c058.Prep())
        return false;
    ReadAnimList(1);
    if (!mMaterial && GetMaterialManager())
        mMaterial = GetMaterialManager()->GetMaterial(0xb660f636);
    if (!mHolder && GetResMgr()) {
        RefA* a = new("Anim", 0, 0, 0, 0) RefA();
        ((RefSlot*)&mHolder)->Assign(a);
        RefB* b = new("Anim", 0, 0, 0, 0) RefB();
        b->InsertResource(0, GetResMgr()->GetResource(0xbd77bb98, 0, 0));
        RefC* c = new("Anim", 0, 0, 0, 0) RefC();
        c->mA = 20.0f;
        c->mKind = 6;
        c->mB = 0.0f;
        c->mC = 1.0f;
        c->mD = 0.0f;
        u32* tv = (u32*)b;
        mHolder->mVec.push_back(tv);
        tv = (u32*)c;
        mHolder->mVec.push_back(tv);
    }
    IPropMgr* pm = GetPropertyManager();
    if (mPropertyList) {
        IPropList* old = mPropertyList;
        mPropertyList = 0;
        ((IRefObj*)old)->Release();
    }
    pm->GetPropertyList(0x1347ba4d, 0, (IRefObj**)&mPropertyList);
    IServer* srv = GetMessageServer();
    u32 off = 0;
    if (srv) {
        void* handler = (u8*)this + 4;
        mAuto.mServer = srv;
        mAuto.mHandler = handler;
        mAuto.mIds = g_animMsgIds;
        mAuto.mCount = 2;
        mAuto.mFlag = 0;
        if (handler) {
            do {
                srv->AddHandler(handler, *(u32*)((u8*)g_animMsgIds + off));
                off += 4;
            } while (off < 8);
        }
    }
    if (flag)
        FUN_00a059d0(this);
    IPropData* pd = mPropertyList->GetProperty(0x213eb74f);
    u16 type = pd->mType;
    u32* v;
    if (type == 10 || type == 16) {
        if (pd->mFlags & 0x30)
            v = pd->mData;
        else
            v = (u32*)(-(u32)(type != 0) & (u32)pd);
    } else {
        v = g_defaultPropVal;
    }
    SetAppMode(*v);
    ICheatMgr* cm = GetCheatManager();
    if (cm) {
        BlocksModeCmd* cmd = new("Anim", 0, 0, 0, 0) BlocksModeCmd();
        if (cmd) cmd->mMgr = this;
        cm->AddCommand("blocksmode", cmd, 0);
    }
    return true;
}

struct Msg { u8 pad[8]; u32 mSel; u8 pad2[0xc]; void* mData; };
struct AnimHandler {
    u8 pad[0x78]; u32 mAppMode;
    void Do08ba0();
    bool HandleMessage(u32 id, Msg* m);
};

// @ 0xa0f610
bool AnimHandler::HandleMessage(u32 id, Msg* m)
{
    switch (id) {
    case 0xf62add: {
        void* data = m->mData;
        switch (m->mSel) {
        case 0x25df0112:
            Do08ba0();
            break;
        case 0x4aeb6bc6:
            ((AnimMgr*)((char*)this - 4))->ReadAnimList(1);
            return false;
        case 0xee17c6ad: {
            void* p = FUN_009a37a0(data);
            if (p) {
                FUN_009a4020(p, -1);
                g_obj_166c084->Fn(p, -1);
            }
            return true;
        }
        }
        break;
    }
    case 0x22d1adc:
        mAppMode = m->mSel;
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Audio allocator wrappers (AudioAllocator.cpp). The original callees receive the pool
// name in esi (a register convention MSVC cannot express), modeled as an extra argument.
// ---------------------------------------------------------------------------
struct MemPool {
    void* LockedAlloc(int a, int b, int zero, const char* name, int c, int d);
    void* LockedAligned(int a, int b, int c, int d, int zero, const char* name, int e, int f);
    void  Free(void* p);
};
extern MemPool* g_memPool;       // 0x16c8b44

// @ 0xa0f6a0
static __declspec(noinline) void* AudioAlloc(int a, int b, int c, int d, const char* name)
{
    char buf[0x80];
    strcpy(buf, "Audio");
    if (name) {
        buf[5] = '/';
        buf[6] = 0;
        strncpy(buf + 6, name, 0x7a);
    }
    return g_memPool->LockedAlloc(a, b, 0, name, c, d);
}

// @ 0xa0f710
static __declspec(noinline) void* AudioAligned(int a, int b, int c, int d, int e, int f, const char* name)
{
    char buf[0x80];
    strcpy(buf, "Audio");
    if (name) {
        buf[5] = '/';
        buf[6] = 0;
        strncpy(buf + 6, name, 0x7a);
    }
    return g_memPool->LockedAligned(a, b, c, d, 0, name, e, f);
}

extern const char g_audioAllocatorFile[];

// @ 0xa0f790
void* __stdcall AudioAllocA(int a, const char* name, int c)
{
    return AudioAlloc(a, c, (int)g_audioAllocatorFile, 0x3c, name);
}

// @ 0xa0f7c0
void* __stdcall AudioAlignedA(int a, const char* name, int c, int d, int e)
{
    return AudioAligned(a, d, e, c, (int)g_audioAllocatorFile, 0x42, name);
}

// @ 0xa0f7f0
void __stdcall AudioFree(void* p, int)
{
    g_memPool->Free(p);
}

struct AudioBlock { void* mPtr; int a, b, c; };

// @ 0xa0f810
void __stdcall AudioBlockAlloc(AudioBlock* out, const int* in, const char* name)
{
    void* p = AudioAligned(in[0], in[1], 0, 0, (int)g_audioAllocatorFile, 0x53, name);
    out->mPtr = 0;
    out->a = 0;
    out->b = 0;
    out->c = 0;
    out->mPtr = p;
}

// @ 0xa0f860
void __stdcall AudioFreeBlock(void** pp)
{
    g_memPool->Free(*pp);
}

// ---------------------------------------------------------------------------
// EA::Audio::Command
// ---------------------------------------------------------------------------
namespace EA { namespace Audio {

class Command {
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
    u8*  EnumParameter(u32* pos, u32* id, u32* type, int* size);
    void* Find(int id, int* type, int* size);
    bool SetT1(int id, int* type, int* size);
    bool GetFloat(int id, float* out);
    bool GetUint32(int id, u32* out);
    bool GetString8(int id, char* buf, u32* pSize);
    const char* GetString8(int id);
    bool GetVoidPtr(int id, void** out);
    void* GetData(int id, void** out);
    bool GetVector3(int id, float* out);
    bool GetMatrix33(int id, float* out);
    bool SetUint64(int id, u32 v);
    bool SetFloat(int id, float v);
    void DeleteParameter(int id);
};

// @ 0xa0f880
u8* Command::EnumParameter(u32* pos, u32* id, u32* type, int* size)
{
    u32 p = *pos;
    if (p >= mCommandSize)
        return 0;
    u32* q = (u32*)(mCommandPtr + p);
    u32 rid = *q++;
    u32 sz = *q++;
    u32 ty = *q++;
    if (id) *id = rid;
    if (type) *type = ty;
    if (size) *size = sz;
    *pos = *pos + ((sz + 3U) & 0xfffffffc) + 0xc;
    return (u8*)q;
}

// @ 0xa0f8e0
void* Command::Find(int id, int* type, int* size)
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

// @ 0xa0fa50
bool Command::SetT1(int id, int* type, int* size)
{
    return Find(id, type, size) != 0;
}

// @ 0xa0fa70
bool Command::GetFloat(int id, float* out)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 0)
        return false;
    *out = *p; return true;
}

// @ 0xa0fab0
bool Command::GetUint32(int id, u32* out)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 1)
        return false;
    *out = *p; return true;
}

// @ 0xa0faf0
bool Command::GetString8(int id, char* buf, u32* pSize)
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

// @ 0xa0fb60
const char* Command::GetString8(int id)
{
    int type; int size;
    const char* p = (const char*)Find(id, &type, &size);
    if (!p) return 0;
    return type == 3 ? p : 0;
}

// @ 0xa0fb90
bool Command::GetVoidPtr(int id, void** out)
{
    int type; int size;
    void** p = (void**)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 4)
        return false;
    *out = *p; return true;
}

// @ 0xa0fbd0
void* Command::GetData(int id, void** out)
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

// @ 0xa0fc10
bool Command::GetVector3(int id, float* out)
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

// @ 0xa0fc60
bool Command::GetMatrix33(int id, float* out)
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

// @ 0xa0fcf0
bool Command::SetUint64(int id, u32 v)
{
    int type; int size;
    u32* p = (u32*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 1)
        return false;
    *p = v; return true;
}

// @ 0xa0fd30
bool Command::SetFloat(int id, float v)
{
    int type; int size;
    float* p = (float*)Find(id, &type, &size);
    if (!p)
        return false;
    if (type != 0)
        return false;
    *p = v; return true;
}

// @ 0xa0fd70
void Command::DeleteParameter(int id)
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

}} // namespace

// ---------------------------------------------------------------------------
// Command queue (writer + reader). Layout recovered from the asm.
// ---------------------------------------------------------------------------
template <class T> inline void swap(T& a, T& b) { T t = a; a = b; b = t; }

struct FVec {                    // fixed-buffer vector; heap-owned when begin[-1] != 0
    u32* mBegin; u32* mEnd; u32* mCap;
    FVec(const FVec& o);         // 0x473140
    void assign(const FVec& o);  // 0x6f6770
    ~FVec() { if (mBegin && ((int*)mBegin)[-1] != 0) delete[] (char*)mBegin; }
    void Swap(FVec& o);
};

// @ 0xa0fe20
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

struct CmdQueue {
    u32 mBegin, mEnd, mCap;      // +0 (fixed vector)
    u8  pad[0x14 - 0xc];
    EA::Audio::Command mCmd;     // +0x14
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

// @ 0xa0f940
void CmdQueue::FinishCommand()
{
    *(u32*)mSizePtr = (mWrite - mCountPtr) - 4;
    mNumCmds++;
    mCmdBase = 0;
    mSizePtr = 0;
    mCountPtr = 0;
    mParamCount = 0;
}

// @ 0xa0f960
void CmdQueue::CancelCommand()
{
    if (mCmdBase != 0) {
        mWrite = mCmdBase;
        mCmdBase = 0;
        mSizePtr = 0;
        mCountPtr = 0;
    }
}

// @ 0xa0f9a0
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

// @ 0xa0f9f0
void CmdQueue::BeginRead()
{
    mCmd.Clear();
    if (mCmdBase != 0) {
        *(u32*)mSizePtr = (mWrite - mCountPtr) - 4;
        mCmd.Load((u32*)mCmdBase);
    }
}

// @ 0xa0fdc0
void CmdQueue::RewindRead()
{
    mReadIndex = 0;
    mRead = mBegin;
}

// @ 0xa0fdd0
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

// @ 0xa0fdf0
CmdQueue::CmdQueue()
{
    mBegin = 0; mEnd = 0; mCap = 0;
    mWrite = 0; mRead = 0; mCmdBase = 0; mSizePtr = 0; mCountPtr = 0;
    mNumCmds = 0; mCapacity = 0; mParamCount = 0; mReadIndex = 0;
}

// @ 0xa0fee0
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

// @ 0xa0ff50
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

// @ 0xa0fff0
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

// @ 0xa10060
void CmdQueue::AddFloat(u32 id, u32 v)
{
    Put(id); Put(4); Put(0); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0xa10120
void CmdQueue::AddUint32(u32 id, u32 v)
{
    Put(id); Put(4); Put(1); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0xa101e0
void CmdQueue::AddVoidPtr(u32 id, u32 v)
{
    Put(id); Put(4); Put(4); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0xa102a0
bool CmdQueue::Reset(u32 n)
{
    mWrite = 0;
    Grow(n);
    mCmdBase = 0;
    mSizePtr = 0;
    mCountPtr = 0;
    mNumCmds = 0;
    mParamCount = 0;
    mRead = 0;
    mReadIndex = 0;
    mWrite = mBegin;
    return true;
}
