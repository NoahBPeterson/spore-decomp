// src/game/SPEngine/SPAppSplitModelDescription.cpp -- migrated from slice(s) s007e06b0, s007df780 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppSplitModelDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Swarm/cDescription.h"
#include "EA/ArgScript/cError.h"
#include "EA/ArgScript/cIParser.h"
#include <string.h>

// ---- items of slice s007df780 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s007d_f780 { float x, y, z; };
struct cError { cError(const char*); };
struct cSafeDynamicKernelStorage {
    int mKernelType;            // +0x0
    void* mKernelData;          // +0x4
    void* mKernelDataVariation; // +0x8

    void SetKernelType(int type);                              // 007e0340
    void SetNormal(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);  // 007e0420
    void SetOrigin(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);  // 007e0480
    void SetRadius(float a, float b);                          // 007e04f0
    void SetDirection(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);// 007e0570
    cSafeDynamicKernelStorage& operator=(const cSafeDynamicKernelStorage& o);  // 007e05e0
};
void EFree2(void*);   // 0x00f47380
void cSafeDynamicKernelStorage::SetNormal(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType != 0)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3_s007d_f780*)mKernelData = a;
    *(cSPVector3_s007d_f780*)mKernelDataVariation = b;
}
void cSafeDynamicKernelStorage::SetOrigin(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType == 1 || mKernelType == 2) {
        *(cSPVector3_s007d_f780*)mKernelData = a;
        *(cSPVector3_s007d_f780*)mKernelDataVariation = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}
void cSafeDynamicKernelStorage::SetRadius(float a, float b)
{
    if (mKernelType == 1) {
        *(float*)((char*)mKernelData + 0xc) = a;
        *(float*)((char*)mKernelDataVariation + 0xc) = b;
        return;
    }
    if (mKernelType == 2) {
        *(float*)((char*)mKernelData + 0x18) = a;
        *(float*)((char*)mKernelDataVariation + 0x18) = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}
void cSafeDynamicKernelStorage::SetDirection(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType != 2)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3_s007d_f780*)((char*)mKernelData + 0xc) = a;
    *(cSPVector3_s007d_f780*)((char*)mKernelDataVariation + 0xc) = b;
}
void* __cdecl EAllocSwarm(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct KernelData16 { uint32_t v[4]; };
struct cKernelError {
    uint32_t pad[4];
    cKernelError(const char* fmt, ...);        // 0x0052df30 (cdecl, `this` pushed)
    cKernelError(const cKernelError&);
};
// ---- items of slice s007df780 end

// ---- items of slice s007e06b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char* kSplitModelKernelTypeCommands;   // 0x0153f1c8
extern void* gCmdKeySplitSlider;                    // 0x0153f1e8
extern int g_01675c54, g_01675c58, g_01675c3c, g_01675c48, g_01675c4c;
extern int g_016763d4, g_016763dc, g_016763e0, g_016763e8, g_016763ec;
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                       // 0x00f47380 EASTL_allocator_deallocate
namespace eastl {
extern char gEmptyBuf[];                            // 0x01667bac
}
namespace eastl {
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    EString() : mpBegin(gEmptyBuf), mpEnd(gEmptyBuf), mpCapacity(gEmptyBuf + 1), mAllocator(0) {}
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    ~EString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EFree(mpBegin); }
};
}
struct cSPVector3_s007e_06b0 { float x, y, z; };
struct cError_s007e_06b0 {
    eastl::EString mMessage;
    cError_s007e_06b0(const char* fmt, ...);
    cError_s007e_06b0(const cError_s007e_06b0&);
};
namespace EA {
namespace ArgScript {
class cArguments_s007e_06b0 {
public:
    const char** MainArguments(int n);                              // 0x00838320
    const char** MainArguments(int* pCount, int min, int max);      // 0x00838020
    const char** OptionArguments(const char* name, int n);          // 0x00838330
};
}
}
namespace EA {
namespace ArgScript {
typedef cSPVector3_s007e_06b0 Vec3;
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s007e_06b0 {
virtual void  v00();
virtual void  v01();
virtual void  v02();
virtual void  v03();
virtual void  v04();
virtual void  v05();
virtual void  v06();
virtual void  v07();
virtual void  v08();
virtual void  v09();
virtual void  v10();
virtual void  v11();
virtual void  v12();
virtual void  v13();
virtual void  v14();
virtual void  v15();
virtual void  v16();
virtual void  v17();
virtual void  v18();
virtual void  v19();
virtual void  v20();
virtual void  v21();
virtual void  v22();
virtual void  v23();
virtual void  v24();
virtual void  v25();
virtual void  v26();
virtual void  v27();
virtual void  v28();
virtual void  v29();
virtual void  v30();
virtual void  v31();
virtual void  v32();
virtual void  v33();
virtual void  v34();
virtual void  v35(void* cmd);
    virtual void  v36();                                            // +0x90
    virtual void  v37();                                            // +0x94
    virtual float v38(const char* s);                               // +0x98
    virtual void  v39();                                            // +0x9c
    virtual int   v40(const char* s);                               // +0xa0
    virtual void  v41();                                            // +0xa4
    virtual Vec3  v42(const char* s);                               // +0xa8
    virtual void  v43();                                            // +0xac
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s007e_06b0 {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
    virtual void c4();
    virtual void AddCommand(void* key, void* cmd);                  // +0x18
    cIParser_s007e_06b0* mParser;      // +0x4
    int       mRefCount;    // +0x8
};
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase : cCommandBase_s007e_06b0 {
    void* mChildState;      // +0xc
    char  mCommands[0x20];  // +0x10
};
}
}
namespace EA {
namespace ArgScript {
uint32_t ParseEnum(const char* value, const char** table);          // 0x00840bb0
}
}
namespace EA {
namespace IO {
struct IStream_s007e_06b0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
    virtual void ReadRegion(void* p, unsigned size);                // +0x30
};
}
}
namespace EA {
namespace IO {
bool ReadInt32(IStream_s007e_06b0* s, int32_t* p, unsigned n, int endian);     // 0x0093a780
}
}
namespace EA {
namespace Swarm {
struct cDescription_s007e_06b0 {
    virtual void d0();
    virtual void d1();
    int mRefCount;      // +0x4
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser {
    void* GetInheritedDescription(void* argv, int count, int type); // 0x00a6f0d0
};
}
}
struct cSafeDynamicKernelStorage_s007e_06b0 {
    int   mKernelType;            // +0x0
    void* mKernelData;            // +0x4
    void* mKernelDataVariation;   // +0x8

    void SetKernelType(int type);                              // 0x007e0340
    void SetNormal(const cSPVector3_s007e_06b0& a, const cSPVector3_s007e_06b0& b);  // 0x007e0420
    void SetOrigin(const cSPVector3_s007e_06b0& a, const cSPVector3_s007e_06b0& b);  // 0x007e0480
    void SetRadius(float a, float b);                          // 0x007e04f0
    void SetDirection(const cSPVector3_s007e_06b0& a, const cSPVector3_s007e_06b0& b);// 0x007e0570
    cSafeDynamicKernelStorage_s007e_06b0& operator=(const cSafeDynamicKernelStorage_s007e_06b0& o); // 0x007e05e0
    void Read(EA::IO::IStream_s007e_06b0* stream);                        // 0x007e06b0
};
struct cSplitModelKernelDescription : EA::Swarm::cDescription_s007e_06b0 {
    cSafeDynamicKernelStorage_s007e_06b0 mData;   // +0x8
    cSplitModelKernelDescription() { mRefCount = 0; mData.mKernelData = 0; mData.mKernelDataVariation = 0; mData.mKernelType = -1; }
};
struct KernelState {
    void* vtbl;                                  // +0x0
    cSplitModelKernelDescription mDesc;          // +0x4
};
extern const cSPVector3_s007e_06b0 gDefaultVector;             // 0x01638c48
struct cSplitControllerEffectCommand : EA::ArgScript::cBlockCommandBase {
    void* field30;                                  // +0x30  mpEffectsParser
    int   field34;                                  // +0x34
    EA::Swarm::cDescription_s007e_06b0 mDesc;                  // +0x38
    eastl::EString mName;                           // +0x40
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
    virtual ~cSplitControllerEffectCommand() {}
};
void FUN_007e0280();
void FUN_007dfbd0();
void FUN_007dfbf0();
void FUN_00c2e4e0();
struct cSplitModelKernelTypeCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelOffsetCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelRadiusCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelNormalCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelOriginCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelDirectionCommand : EA::ArgScript::cCommandBase_s007e_06b0 {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
struct cSplitModelKernelEffectCommand : EA::ArgScript::cBlockCommandBase {
    EA::Swarm::cEffectsParser* mpEffectsParser;   // +0x30
    int       field34;                            // +0x34
    char      pad38[8];                           // +0x38
    cSafeDynamicKernelStorage_s007e_06b0 mData;              // +0x40
    eastl::EString mName;                         // +0x4c
    void Execute(EA::ArgScript::cArguments_s007e_06b0& args);
};
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
// ---- items of slice s007e06b0 end

// @ 0x007dfed0
void FUN_007dfed0()
{ /* 564B */ }

// @ 0x007e0110
void FUN_007e0110()
{ /* 80B  ctor */ }

// @ 0x007e0160
void FUN_007e0160()
{ /* 49B */ }

// @ 0x007e01a0
void FUN_007e01a0()
{ /* 90B */ }

// @ 0x007e0200
void FUN_007e0200()
{ /* 126B */ }

// @ 0x007e0280
void FUN_007e0280()
{ /* 112B */ }

// @ 0x007e02f0
void FUN_007e02f0()
{ /* 65B  deleting dtor */ }

// @ 0x007e0340
void cSafeDynamicKernelStorage::SetKernelType(int type)
{
    if (mKernelData != 0) {
        EFree2(mKernelData);
        mKernelData = 0;
    }
    if (mKernelDataVariation != 0) {
        EFree2(mKernelDataVariation);
        mKernelDataVariation = 0;
    }
    switch (type) {
    case 0:
    case 1:
        mKernelData = EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        mKernelDataVariation = EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        break;
    case 2:
        mKernelData = EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        mKernelDataVariation = EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        break;
    default:
        if (type < 0) {
            mKernelType = type;
            mKernelData = 0;
            return;
        }
        throw cKernelError("Unknown split model kernel type.");
    }
    mKernelType = type;
}

// @ 0x007e05e0
cSafeDynamicKernelStorage& cSafeDynamicKernelStorage::operator=(const cSafeDynamicKernelStorage& o)
{
    SetKernelType(o.mKernelType);
    int t = o.mKernelType;
    if (t != 0 && t != 1) {
        if (t != 2) {
            if (mKernelData != 0) {
                EFree2(mKernelData);
                mKernelData = 0;
            }
            if (mKernelDataVariation != 0) {
                EFree2(mKernelDataVariation);
                mKernelDataVariation = 0;
            }
            mKernelData = 0;
            mKernelType = -1;
            return *this;
        }
        memcpy(mKernelData, o.mKernelData, 0x1c);
        memcpy(mKernelDataVariation, o.mKernelDataVariation, 0x1c);
        return *this;
    }
    KernelData16* d = (KernelData16*)mKernelData;
    KernelData16* s = (KernelData16*)o.mKernelData;
    d->v[0] = s->v[0];
    d->v[1] = s->v[1];
    d->v[2] = s->v[2];
    d->v[3] = s->v[3];
    d = (KernelData16*)mKernelDataVariation;
    s = (KernelData16*)o.mKernelDataVariation;
    d->v[0] = s->v[0];
    d->v[1] = s->v[1];
    d->v[2] = s->v[2];
    d->v[3] = s->v[3];
    return *this;
}

// @ 0x007e06b0
void cSafeDynamicKernelStorage_s007e_06b0::Read(EA::IO::IStream_s007e_06b0* stream)
{
    EA::IO::ReadInt32(stream, (int32_t*)&mKernelType, 1, 0);
    SetKernelType(mKernelType);
    switch (mKernelType) {
    case 0:
    case 1:
        stream->ReadRegion(mKernelData, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelData + 0xc), 1, 0);
        stream->ReadRegion(mKernelDataVariation, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelDataVariation + 0xc), 1, 0);
        break;
    case 2:
        stream->ReadRegion(mKernelData, 0xc);
        stream->ReadRegion((char*)mKernelData + 0xc, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelData + 0x18), 1, 0);
        stream->ReadRegion(mKernelDataVariation, 0xc);
        stream->ReadRegion((char*)mKernelDataVariation + 0xc, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelDataVariation + 0x18), 1, 0);
        break;
    }
}

// @ 0x007e07a0
cSplitModelKernelDescription* SplitModelKernelRead(EA::IO::IStream_s007e_06b0* stream)
{
    cSplitModelKernelDescription* p =
        new ("Swarm", 0, 0, 0, 0) cSplitModelKernelDescription();
    p->mData.Read(stream);
    return p;
}

// @ 0x007e07f0
void cSplitControllerEffectCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 3);
    const char* s = av[0];
    const char* e = s;
    while (*e) ++e;
    mName.assign(s, e);
    if (count > 1)
        ((EA::Swarm::cEffectsParser*)field30)->GetInheritedDescription(av, count, 0x29);
    mParser->v35(this);
}

// @ 0x007e0850
void SplitControllerAddCommands(void* self, void* server)
{
    int* cmdVtbl = (int*)server;
    cSplitControllerEffectCommand* effect = 0;
    if (server) {
        effect = new ("ArgScript/SplitControllerEffect", 0, 0, 0, 0) cSplitControllerEffectCommand();
        effect->field34 = 0x30aa211;
        effect->mDesc.mRefCount = 0;
    }
    ((void(__thiscall*)(void*, void*, void*))cmdVtbl[0x14 / 4])(server, gCmdKeySplitSlider, effect);
    cSplitControllerEffectCommand* group = 0;
    if (server) {
        group = new ("ArgScript/GroupSplitController", 0, 0, 0, 0) cSplitControllerEffectCommand();
    }
    ((void(__thiscall*)(void*, void*, void*))cmdVtbl[0x18 / 4])(server, gCmdKeySplitSlider, group);
}

// @ 0x007e09a0
void FUN_007e09a0(void)
{
    g_01675c54 = 2;
    g_01675c58 = 2;
    g_01675c3c = (int)&FUN_007e0280;
    g_01675c48 = (int)&SplitModelKernelRead;
    g_01675c4c = (int)&FUN_007dfbd0;
    g_016763d4 = (int)&SplitControllerAddCommands;
    g_016763dc = (int)&FUN_007dfbf0;
    g_016763e0 = (int)&FUN_00c2e4e0;
    g_016763e8 = 1;
    g_016763ec = 1;
}

// @ 0x007e0a00
void cSplitModelKernelTypeCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    if (mState->mDesc.mData.mKernelType >= 0)
        throw cError_s007e_06b0("Type already specified.");
    mState->mDesc.mData.SetKernelType(
        EA::ArgScript::ParseEnum(av[0], &kSplitModelKernelTypeCommands));
}

// @ 0x007e0a60
void cSplitModelKernelOffsetCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    float a = mParser->v38(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        float b = mParser->v38(ov[0]);
        if (mState->mDesc.mData.mKernelType != 0)
            throw cError_s007e_06b0("Either type not specified or type does not support this parameter");
        *(float*)((char*)mState->mDesc.mData.mKernelData + 0xc) = a;
        *(float*)((char*)mState->mDesc.mData.mKernelDataVariation + 0xc) = b;
    } else {
        if (mState->mDesc.mData.mKernelType != 0)
            throw cError_s007e_06b0("Either type not specified or type does not support this parameter");
        *(float*)((char*)mState->mDesc.mData.mKernelData + 0xc) = a;
        *(float*)((char*)mState->mDesc.mData.mKernelDataVariation + 0xc) = 0.0f;
    }
}

// @ 0x007e0b50
void cSplitModelKernelRadiusCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    float a = mParser->v38(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    float b;
    if (ov)
        b = mParser->v38(ov[0]);
    else
        b = 0.0f;
    mState->mDesc.mData.SetRadius(a, b);
}

// @ 0x007e0bc0
void cSplitModelKernelNormalCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    cSPVector3_s007e_06b0 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3_s007e_06b0 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetNormal(a, b);
    } else {
        mState->mDesc.mData.SetNormal(a, gDefaultVector);
    }
}

// @ 0x007e0c90
void cSplitModelKernelOriginCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    cSPVector3_s007e_06b0 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3_s007e_06b0 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetOrigin(a, b);
    } else {
        mState->mDesc.mData.SetOrigin(a, gDefaultVector);
    }
}

// @ 0x007e0d60
void cSplitModelKernelDirectionCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    const char** av = args.MainArguments(1);
    cSPVector3_s007e_06b0 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3_s007e_06b0 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetDirection(a, b);
    } else {
        mState->mDesc.mData.SetDirection(a, gDefaultVector);
    }
}

// @ 0x007e0e30
void cSplitModelKernelEffectCommand::Execute(EA::ArgScript::cArguments_s007e_06b0& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 3);
    const char* s = av[0];
    const char* e = s;
    while (*e) ++e;
    mName.assign(s, e);
    cSafeDynamicKernelStorage_s007e_06b0 tmp;
    tmp.mKernelType = -1;
    tmp.mKernelData = 0;
    tmp.mKernelDataVariation = 0;
    mData = tmp;
    if (count > 1) {
        void* got = mpEffectsParser->GetInheritedDescription(av, count, 0x10);
        if (got)
            mData = *(cSafeDynamicKernelStorage_s007e_06b0*)((char*)got + 8);
    }
    mParser->v35(this);
}
