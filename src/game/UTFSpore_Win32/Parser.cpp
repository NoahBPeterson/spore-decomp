// src/game/UTFSpore_Win32/Parser.cpp -- migrated from slice(s) s00847200, s00845370, s00846280, s00843650, s00842620, s00841370, s00844270, s00840250 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Parser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cError.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cExpression.h"
#include "EA/ArgScript/cState.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cExprFunction.h"

// ---- items of slice s00840250 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cExprAccess { void EvalBoolParentheses(const char** p, char c); };  // 0x0083d240
// ---- items of slice s00840250 end

// ---- items of slice s00844270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl isalpha(int);
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern char gEmptyStr[2];   // 0x01667bac: shared empty-string storage
typedef unsigned int size_t_;
void* operator new(size_t_ n, const char* name, int flags, unsigned dbg, const char* file, int line);   // 0x00f473a0
void operator delete(void* p) throw();   // 0x00f47380
inline void* operator new(size_t_, void* p) { return p; }
inline void operator delete(void*, void*) throw() {}
inline unsigned CharStrlen(const char* p) {
    const char* pCurrent = p;
    while (*pCurrent++) {}
    return (unsigned)(pCurrent - p - 1);
}
static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
namespace eastl {
struct allocator_s0084_4270 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_4270 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0084_4270 mAllocator;

    __forceinline string8_s0084_4270(const char* b, const char* e) {
        unsigned n = e - b;
        unsigned cap = n + 1;
        char* d; char* c;
        if (cap > 1) {
            d = (char*)operator new(cap, "ArgScript", 0, 0, kAllocFile, 0xd1);
            c = d + cap;
        } else {
            d = gEmptyStr; c = gEmptyStr + 1;
        }
        mpBegin = d; mpCapacity = c;
        memcpy(d, b, n);
        mpEnd = d + n;
        *mpEnd = 0;
    }
    void RangeInitialize(unsigned n);                       // 0x00475ab0
    __forceinline string8_s0084_4270(const string8_s0084_4270& x) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        const char* e = x.mpEnd;
        const char* b = x.mpBegin;
        RangeInitialize(e - b + 1);
        char* d = mpBegin;
        memcpy(d, b, e - b);
        mpEnd = d + (e - b);
        *mpEnd = 0;
    }
    string8_s0084_4270() { mpBegin = gEmptyStr; mpEnd = gEmptyStr; mpCapacity = gEmptyStr + 1; }
    ~string8_s0084_4270() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
    string8_s0084_4270& append(const char* first, const char* last);   // 0x00455d60
    string8_s0084_4270& assign(const char* first, const char* last);   // 0x00454cb0
    void push_back(char c);                                 // 0x005306c0
    int  compare(unsigned pos, unsigned n, const char* s);  // 0x008417c0
    unsigned find(char c, unsigned pos) const;              // 0x00607580
    unsigned size() const { return mpEnd - mpBegin; }
};
}
namespace eastl {
template <typename T>
struct vec {
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(T* pos, const T& v);   // out-of-line grow path
    void push_back(const T& v) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s0084_4270 mAllocator;
    unsigned mExtra;   // retail sp_vector_allocator is 8 bytes
};
}
using eastl::string8_s0084_4270;
namespace EA {
namespace ArgScript {
struct cArguments_s0084_4270 {
    int NumArguments();                      // 0x00837f30
    const char* operator[](int i);           // 0x00837f20
    const char** MainArguments(int i);       // 0x00838320
    cArguments_s0084_4270();                            // 0x00837ff0
    void SplitIntoArguments(const char* s);  // 0x008383c0
    unsigned char pad[0x44];
};
}
}
namespace EA {
namespace ArgScript {
struct cError_s0084_4270 {
    cError_s0084_4270(const char* fmt, ...);            // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};
}
}
namespace EA {
namespace ArgScript {
void MakeCaseInsensitive(const char* s, string8_s0084_4270* out);   // 0x00840cc0 (cdecl)
}
}
namespace EA {
namespace ArgScript {
struct cMacroLine { int offset; int line; };
}
}
namespace EA {
namespace ArgScript {
struct cMacroDefinition {
    int mRefCount;                    // +0x00
    string8_s0084_4270 mName;                    // +0x04
    cArguments_s0084_4270 mParams;               // +0x14
    eastl::vec<char> mMacroText;      // +0x58
    eastl::vec<cMacroLine> mMacroBody;// +0x6c
    string8_s0084_4270 mPath;                    // +0x80
    int mStartLine;                   // +0x90

    cMacroDefinition();               // 0x00844860
    ~cMacroDefinition();              // 0x00841fd0
};
}
}
namespace EA {
namespace ArgScript {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& r) {
        mpObject = r.mpObject;
        if (mpObject) ++mpObject->mRefCount;
    }
    void Release() {
        T* p = mpObject;
        if (p) {
            if (p->mRefCount == 1) { p->~T(); operator delete(p); }
            else --p->mRefCount;
        }
    }
    ~AutoRefCount() { Release(); }
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0084_4270 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void EndBlock(bool b);   // +0x14
    virtual void EndMeta(bool b);    // +0x18
};
}
}
struct BoolVec {
    bool* mpBegin;
    bool* mpEnd;
    bool* mpCapacity;
    void DoInsertValue(bool* pos, const bool* v);   // 0x00843bc0
    void push_back(bool v) {
        bool* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};
struct MacroPair {
    string8_s0084_4270 first;
    EA::ArgScript::AutoRefCount<EA::ArgScript::cMacroDefinition> second;
    __declspec(noinline) MacroPair(const string8_s0084_4270& k, const EA::ArgScript::AutoRefCount<EA::ArgScript::cMacroDefinition>& v);   // 0x00844a00
    __declspec(noinline) MacroPair(const MacroPair& o);                                                                                  // 0x00844a60
    __declspec(noinline) ~MacroPair() {}
};
struct StrNode {
    string8_s0084_4270 key;
    string8_s0084_4270 value;
    StrNode* mpNext;
};
struct StrHashtable {
    void DoFreeNodes(StrNode** pNodeArray, unsigned n);
};
struct cParserIface {
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
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void ParseLine(const char* line);   // +0x40
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void ExpectEnd(void* cmd, const char* endName);   // +0x90
    virtual bool EvalCondition(const char* expr);   // +0x94
};
struct cMetaCommandBase {
    virtual void m0();
    cParserIface* mParser;   // +4
    int mRefCount;           // +8
    virtual ~cMetaCommandBase();     // 0x0083c7c0
};
struct cParser : cParserIface {
    unsigned char pad0[0x6c - 4];
    unsigned char mMacroDefinitions[0x20];   // +0x6c hashtable (bucketArray +0x70, bucketCount +0x74)
    unsigned char pad1[0xe0 - 0x8c];
    string8_s0084_4270 mCurrentPath;                    // +0xe0
    int mCurrentLine;                        // +0xf0
    unsigned char pad2[0x104 - 0xf4];
    int mBlockCommentDepth;                      // +0x104
    eastl::vec<EA::ArgScript::cICommand_s0084_4270*> mBlockCommandStack;   // +0x108
    struct cMetaEntry {
        EA::ArgScript::cICommand_s0084_4270* mCommand; int mLine;
        cMetaEntry(EA::ArgScript::cICommand_s0084_4270* c, int l) : mCommand(c), mLine(l) {}
        cMetaEntry(const cMetaEntry& o) : mCommand(o.mCommand), mLine(o.mLine) {}
    };
    eastl::vec<cMetaEntry> mMetaCommandStack;    // +0x11c
    string8_s0084_4270 mScope;                              // +0x130
    eastl::vec<int> mScopeOffsets;               // +0x140
    unsigned char pad5[0x1b0 - 0x150];
    string8_s0084_4270 mLCName;                             // +0x1b0

    int ParseEnd(bool bUnwind);                  // 0x00844ec0
    void InstantiateMacro(const char* name, EA::ArgScript::cArguments_s0084_4270* args);   // 0x00844fb0
    void PushScope(const char* name);            // 0x00845260
    void PushMeta(EA::ArgScript::cICommand_s0084_4270* c, int line);       // 0x00845320
};
struct MacroNode {
    string8_s0084_4270 key;
    EA::ArgScript::AutoRefCount<EA::ArgScript::cMacroDefinition> value;
    MacroNode* mpNext;
};
struct MacroIter { MacroNode* node; MacroNode** bucket; };
struct MacroTable {
    unsigned char pad[4];
    MacroNode** mpBucketArray;   // +4
    unsigned mnBucketCount;      // +8
    MacroIter find(const string8_s0084_4270& key);   // 0x007e2ea0
};
inline MacroTable* MacroTableOf(cParser* p) { return (MacroTable*)((char*)p + 0x6c); }
namespace {
struct cIfCommand : cMetaCommandBase {
    unsigned char pad[0x10 - 0xc];
    BoolVec mConditions;      // +0x10
    unsigned char pad2[0x38 - 0x1c];
    BoolVec mTaken;           // +0x38
    // @ 0x00844780
    virtual void Execute(EA::ArgScript::cArguments_s0084_4270& args);
};

}
namespace {
struct cDefineCommand : cMetaCommandBase {
    cParser* mFullParser;                      // +0xc
    EA::ArgScript::AutoRefCount<EA::ArgScript::cMacroDefinition> mpMacro;    // +0x10
    // @ 0x00844c40
    virtual void Execute(EA::ArgScript::cArguments_s0084_4270& args);
    // @ 0x00844e50: destructor body
};

}  // namespace
// ---- items of slice s00844270 end

// ---- items of slice s00841370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl ByteCopy(void* dst, const void* src, unsigned n);          // 0x011e0744
extern "C" char* __cdecl slab_search(const char* first, const char* last,
                                     const char* pfirst, const char* plast);        // 0x00609d90
extern "C" int   __cdecl CompareBytes(const char* a, const char* b, unsigned n);    // 0x005f7870
bool __cdecl String8Equals(const void* a, const void* b);                            // 0x00554fb0 (operator==)
void __cdecl Sprintf(void* out, const char* fmt, ...);                              // 0x00840c20
void __cdecl Output(int* pOut, const char* fmt, ...);                               // 0x00841000
bool __cdecl Text_WildcardMatch(const char* pStr, const char* pPattern, bool bCase); // 0x0093d5d0
inline unsigned CharStrlen_s0084_1370(const char* p)
{
    const char* pCurrent = p;
    const char* const pBase = p + 1;
    while (*pCurrent++) {}
    return (unsigned)(pCurrent - pBase);
}
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }
namespace eastl {
struct allocator_s0084_1370 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_1370 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0084_1370 mAllocator;

    string8_s0084_1370() {
        mpBegin = gEmptyStr;
        mpEnd = gEmptyStr;
        mpCapacity = gEmptyStr + 1;
    }
    __forceinline string8_s0084_1370(const string8_s0084_1370& x) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        char* e = x.mpEnd;
        char* b = x.mpBegin;
        unsigned n = (unsigned)(e - b);
        RangeInitialize(n + 1);
        ByteCopy(mpBegin, b, n);
        mpEnd = mpBegin + (e - b);
        *mpEnd = 0;
    }
    ~string8_s0084_1370() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    void RangeInitialize(unsigned n);                            // 0x00475ab0
    void append(const char* first, const char* last);            // 0x00455d60
    void assign(const char* first, const char* last);            // 0x00454cb0
    int  compare(unsigned pos, unsigned n, const char* p) const; // 0x008417c0
    int  find(const char* p, unsigned pos) const;                // 0x00841d00
    void erase(unsigned position, unsigned n = 0xffffffffu);     // inline (used by PopNamespace)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
}
namespace eastl {
template <typename T>
struct vec_s0084_1370 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
    ~vec_s0084_1370() {
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) ::operator delete(mpBegin);
    }
};
}
using eastl::string8_s0084_1370;
using eastl::vec_s0084_1370;
typedef string8_s0084_1370 string8;
namespace EA {
namespace ArgScript {
struct cArguments_s0084_1370;
}
}
namespace EA {
namespace ArgScript {
struct cExpression_s0084_1370;
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0084_1370;
}
}
namespace EA {
namespace ArgScript {
struct cState_s0084_1370 { unsigned mStateID; };
}
}
namespace EA {
namespace ArgScript {
struct cIBlockCommand_s0084_1370;
}
}
namespace EA {
namespace ArgScript {
struct cIMetaCommand;
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0084_1370 {
    virtual void Execute(cArguments_s0084_1370* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState_s0084_1370* pState);              // +0x08
    virtual int AddRef();                                                // +0x0c
    virtual int Release();                                               // +0x10
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0084_1370 : cICommand_s0084_1370 {
    cIParser_s0084_1370* mParser;   // +0x04
    int mRefCount;          // +0x08

    cCommandBase_s0084_1370();                                           // 0x0083c800
    virtual ~cCommandBase_s0084_1370();                                  // 0x0083c750
    virtual void OnRegister(void* pParser, cState_s0084_1370* pState);              // 0x0083c780
};
}
}
namespace EA {
namespace ArgScript {
struct cMetaCommandBase_s0084_1370 : cICommand_s0084_1370 {
    void* mParser;          // +0x04
    int mRefCount;          // +0x08

    virtual void OnRegister(void* pParser, cState_s0084_1370* pState);              // 0x0083c7f0
};
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase_s0084_1370 : cCommandBase_s0084_1370 {
    unsigned char pad0c[0x30 - 0x0c];
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0084_1370 {
    unsigned char pad[0x44];

    cArguments_s0084_1370();                                             // 0x00837ff0
    cArguments_s0084_1370(const char* pArgString);                       // 0x008386d0
    ~cArguments_s0084_1370();                                            // 0x00837fa0
    int NumArguments() const;                                            // 0x00837f30
    const char* operator[](int i) const;                                 // 0x00837f20
    const char* const* MainArguments(int start) const;                   // 0x00838320
    const char* const* MainArguments(int* pNum, int start, int count) const;  // 0x00838020
    bool HasFlag(const char* pFlag);                                     // 0x008380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cExpression_s0084_1370 {
    unsigned char pad[0x20];               // eastl::hash_map of functions

    void  EvalExpectCharThrow(const char*& p, char c);                   // 0x0083d240
    bool  EvalContinueChar(const char*& p, char c);                      // 0x0083d290
    void  EvalString(const char*& p, string8* pOut);                     // 0x0083dc00
    float EvalRealExpression(const char*& p);                            // 0x0083e470
    bool  operator==(const cExpression_s0084_1370& x) const { return true; }
};
}
}
namespace EA {
namespace ArgScript {
struct CommandNode_s0084_1370 {
    string8 key;            // +0x00
    void* mpCommand;        // +0x10 (AutoRefCount<cICommand>::mpObject)
    CommandNode_s0084_1370* mpNext;   // +0x14
};
}
}
namespace EA {
namespace ArgScript {
struct CommandTable_s0084_1370 {
    int mPad2c;                              // +0x00 (table object lives at cParser+0x2c)
    CommandNode_s0084_1370** mpBucketArray;  // +0x04
    unsigned mnBucketCount;                  // +0x08
};
}
}
namespace EA {
namespace ArgScript {
struct IntVec_s0084_1370 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned mAllocator[2];
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0084_1370 {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual bool Init();                                                 // +0x08
    virtual bool Shutdown();                                             // +0x0c
    virtual void SetState(cState_s0084_1370* pState);                               // +0x10
    virtual void RegisterCommand(const char* pName, void* pCommand);     // +0x14
    virtual bool UnregisterCommand(void* pCommand);                      // +0x18
    virtual bool UnregisterCommand(const char* pName);                   // +0x1c
    virtual void* Command(const char* pName) const;                      // +0x20
    virtual void SetFlag(int flag, bool value);                          // +0x24
    virtual void SetMinMaxVersion(int nMin, int nMax);                   // +0x28
    virtual int Version() const;                                         // +0x2c
    virtual void ParseBegin();                                           // +0x30
    virtual int ParseEnd(bool bUnwind);                                  // +0x34
    virtual void ParseFile(const char* pPath);                           // +0x38
    virtual void ParseStream(void* pStream);                             // +0x3c
    virtual void ParseCommand(const char* pCommand);                     // +0x40
    virtual void InstantiateMacro(const char* pName, cArguments_s0084_1370* pArgs);  // +0x44
    virtual void Slot48();                                               // +0x48
    virtual bool ParseFileNoThrow(const char* pPath);                    // +0x4c
    virtual bool ParseCommandNoThrow(const char* pCommand);              // +0x50
    virtual bool InstantiateMacroNoThrow(const char* pName, cArguments_s0084_1370* pArgs);  // +0x54
    virtual const char* LastErrorString() const;                         // +0x58
    virtual const char* LineLocationInfo();                              // +0x5c
    virtual void GetLineLocationInfo(string8* pInfo, int* pLine) const;  // +0x60
    virtual bool CommandExists(const char* pName) const;                 // +0x64
    virtual bool DefinitionExists(const char* pName) const;              // +0x68
    virtual void SetVariable(const char* pName, const char* pValue);     // +0x6c
    virtual const char* Variable(const char* pName) const;               // +0x70
    virtual void SetGlobalVariable(const char* pName, const char* pValue);  // +0x74
    virtual void SetGlobalVariableSet(void* pSet);                       // +0x78
    virtual void PushNamespace(const char* pName);                       // +0x7c
    virtual void PopNamespace();                                         // +0x80
    virtual void PurgeNamespace(const char* pName);                      // +0x84
    virtual const char* CurrentScope() const;                            // +0x88
    virtual void StartBlock(cIBlockCommand_s0084_1370* pCommand);                   // +0x8c
    virtual void StartMetaBlock(cIMetaCommand* pCommand, const char* pEndName);  // +0x90
    virtual bool ParseBool(const char* pText) const;                     // +0x94
    virtual float ParseFloat(const char* pText) const;                   // +0x98
    virtual int ParseInt(const char* pText) const;                       // +0x9c
    virtual unsigned ParseUint(const char* pText) const;                 // +0xa0
    virtual void ParseVector2(void* pOut, const char* pText) const;      // +0xa4
    virtual void ParseVector3(void* pOut, const char* pText) const;      // +0xa8
    virtual void ParseVector4(void* pOut, const char* pText) const;      // +0xac
    virtual void ParseRGB(void* pOut, const char* pText) const;          // +0xb0
    virtual void ParseRGBA(void* pOut, const char* pText) const;         // +0xb4
    virtual cExpression_s0084_1370& Expression();                        // +0xb8
    virtual void SetOutStream(void* pStream);                            // +0xbc
    virtual void SetTraceStream(void* pStream);                          // +0xc0
    virtual void* OutStream() const;                                     // +0xc4
    virtual void* TraceStream() const;                                   // +0xc8
};
}
}
namespace EA {
namespace ArgScript {
struct cParser_s0084_1370 : cIParser_s0084_1370 {
    unsigned char pad04[0x10 - 0x04];
    unsigned mFlags;                                     // +0x10
    unsigned char pad14[0x2c - 0x14];
    CommandTable_s0084_1370 mCommands;                   // +0x2c (bucket array +0x30, count +0x34)
    unsigned char pad38[0x4c - 0x38];
    cExpression_s0084_1370 mExpression;                  // +0x4c
    unsigned char pad6c[0xe0 - 0x6c];
    string8 mCurrentPath;                                // +0xe0
    int mCurrentLine;                                    // +0xf0
    string8 mLineLocation;                               // +0xf4
    unsigned char pad104[0x130 - 0x104];
    string8 mScope;                                      // +0x130
    IntVec_s0084_1370 mScopeOffsets;                     // +0x140

    enum tFlag { kFlagContinueAfterError = 0, kMaxFlags = 1 };

    void SetFlag(tFlag flag, bool value);                                // 0x00841490
    const char* LineLocationInfo();                                      // 0x008414d0
    float* ParseVector2(float* pOut, const char* pText);                 // 0x00841540
    float* ParseVector3(float* pOut, const char* pText);                 // 0x00841590
    float* ParseRGBA(float* pOut, const char* pText);                    // 0x00841610
    float* ParseRGB(float* pOut, const char* pText);                     // 0x008416b0
    void PopNamespace();                                                 // 0x00841c90
};
}
}
namespace EA {
namespace ArgScript {
typedef cParser_s0084_1370 cParser_s0084_1370;
}
}
namespace eastl {
inline void string8_s0084_1370::erase(unsigned position, unsigned n)
{
    unsigned count = min_alt(size() - position, n);
    char* pDest = mpBegin + position;
    char* pSrc = pDest + count;
    if (pDest != pSrc) {
        memmove(pDest, pSrc, (unsigned)(mpEnd - pSrc) + 1);
        mpEnd = pDest + (mpEnd - pSrc);
    }
}  // namespace eastl
}
using EA::ArgScript::cArguments_s0084_1370;
using EA::ArgScript::cParser_s0084_1370;
using EA::ArgScript::cState_s0084_1370;
typedef cArguments_s0084_1370 cArguments;
namespace {

// ---- cCommandStateT<cParser, cMetaCommandBase>: command + the parser it was registered for ----
struct cCommandStateMeta_s0084_1370 : EA::ArgScript::cMetaCommandBase_s0084_1370 {
    cParser_s0084_1370* mState;        // +0x0c
    void OnRegister(void* pParser, cState_s0084_1370* pState);      // 0x00841410
};

// ---- cCommandStateT<cParser, cBlockCommandBase> ----
struct cCommandStateBlock_s0084_1370 : EA::ArgScript::cBlockCommandBase_s0084_1370 {
    cParser_s0084_1370* mState;        // +0x30
    void OnRegister(void* pParser, cState_s0084_1370* pState);      // 0x00841440
};

// ---- plain commands built on cCommandBase: output stream at +0x04 ----
struct cOutputCommand_s0084_1370 {
    int mPad00;
    int* mOut;              // +0x04
};

struct cEvalCommand_s0084_1370 {
    int mPad00;
    cParser_s0084_1370* mParser;       // +0x04
    void Execute(cArguments* pArgs);                     // 0x008418b0
};

struct cSetECommand_s0084_1370 : EA::ArgScript::cCommandBase_s0084_1370 {
    int mPad0c;                 // +0x0c
    cArguments mArguments;      // +0x10

    cSetECommand_s0084_1370();                           // 0x00841900
};

struct cNamespaceCommand_s0084_1370 : EA::ArgScript::cBlockCommandBase_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x008419d0
    void OnEndBlock(bool bEnd);                          // 0x00841a10
};

struct cCreateCommand_s0084_1370 : cCommandStateMeta_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841a50
};

struct cSCreateCommand_s0084_1370 : cCommandStateMeta_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841ae0
};

struct cShowArgumentsCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841b70
};

struct cTraceCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841bf0
};

struct cHelpCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    int mPad08;             // +0x08
    cParser_s0084_1370* mState;        // +0x0c
    void Execute(cArguments* pArgs);                     // 0x00842080
};

struct cArrayCreateCommand_s0084_1370 {
    int mPad00;
    cParser_s0084_1370* mParser;       // +0x04
    void Execute(cArguments* pArgs);                     // 0x00842230
};

struct ExistFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser_s0084_1370* mParser;       // +0x08
};

struct cVariableExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser_s0084_1370* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842310
};

struct cDefinitionExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser_s0084_1370* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x008423c0
};

struct cCommandExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser_s0084_1370* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842470
};

struct cEqFunction_s0084_1370 {
    int mPad00;
    int mRefCount;          // +0x04
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842520
};

// ---- pair<string8, string8> (0x20) used by the variable table ----
struct StringPair_s0084_1370 {
    string8 first;          // +0x00
    string8 second;         // +0x10

    StringPair_s0084_1370(const string8& a, const string8& b);   // 0x00841d60
    StringPair_s0084_1370(const StringPair_s0084_1370& x);       // 0x00841f00
};

// ---- cMacroDefinition (0x90): name string8, argument spec, two vectors, body text ----
struct cMacroDefinition_s0084_1370 {
    int mRefCount;                      // +0x00
    string8 mName;                      // +0x04
    cArguments mArgs;                   // +0x14
    vec_s0084_1370<int> mArgNames;      // +0x58
    vec_s0084_1370<int> mArgDefaults;   // +0x6c
    string8 mBody;                      // +0x80

    ~cMacroDefinition_s0084_1370();     // 0x00841fd0
};

}  // namespace
// ---- items of slice s00841370 end

// ---- items of slice s00842620 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __cdecl fopen(const char* path, const char* mode);
extern "C" __declspec(dllimport) int   __cdecl feof(void* f);
extern "C" __declspec(dllimport) char* __cdecl fgets(char* buf, int n, void* f);
extern "C" __declspec(dllimport) int   __cdecl fclose(void* f);
extern "C" void* __cdecl CopyBytes(void* dst, const void* src, unsigned n);  // 0x011e0744
extern char gThrowInfo;
extern char g_1667bac[1];
extern char g_141b840[1];
extern char g_141b842[1];
extern char g_1401b70[1];
typedef unsigned int  uint32;
void __cdecl SP_cError(void* pBuf, const char* fmt, ...);                 // 0x0052df30
__declspec(noreturn) void __cdecl ThrowException(void* pObj, void* pThrowInfo);  // 0x011e0912
void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b,
                         const char* pFile, int line);                    // 0x00f473a0
void __cdecl MakeCaseInsensitiveChars(const char* pName, void* pTable);   // 0x00840cc0
unsigned __cdecl ReadLine(void* pStream, char* pBuf, unsigned n);         // 0x0093a8b0
void* __cdecl LogAppend(void* pDst, const char* pSrc);                    // 0x0061dea0
extern "C" unsigned __cdecl strlen(const char*);
#pragma intrinsic(strlen)
inline unsigned CharStrlen_s0084_2620(const char* p)
{
    const char* pBase = p + 1;
    while (*p++) {}
    return (unsigned)(p - pBase);
}
template <typename T>
inline const T& eastl_min(const T& a, const T& b) { return (b < a) ? b : a; }
namespace eastl {
struct allocator_s0084_2620 { unsigned char pad[4]; };
}
namespace eastl {
struct PackStr_s0084_2620 {
    void Insert(char* pDst, const char* first, const char* last);
};
}
namespace eastl {
struct string8_s0084_2620 : PackStr_s0084_2620 {
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    char* mpCapacity;               // +0x08
    allocator_s0084_2620 mAllocator;  // +0x0c

    string8_s0084_2620() {
        mpBegin = g_1667bac;
        mpEnd = g_1667bac;
        mpCapacity = g_1667bac + 1;
    }
    string8_s0084_2620(const string8_s0084_2620& x);          // 0x0057cb10 (out of line)
    string8_s0084_2620(const char* p) {
        unsigned n = CharStrlen_s0084_2620(p);
        RangeInitialize(n + 1);
        CopyBytes(mpBegin, p, n);
        mpEnd = mpBegin + n;
        mpEnd[0] = 0;
    }
    string8_s0084_2620(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first);
        RangeInitialize(n + 1);
        CopyBytes(mpBegin, first, n);
        mpEnd = mpBegin + n;
        mpEnd[0] = 0;
    }
    ~string8_s0084_2620() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    string8_s0084_2620& operator=(const string8_s0084_2620& x) {
        if (this != &x) assign(x.mpBegin, x.mpEnd);
        return *this;
    }

    // Inline allocator entry point (EASTL's allocator::allocate is folded in).
    void RangeInitialize(unsigned n) {
        if (n > 1) {
            mpBegin = (char*)EAAllocate(n, "ArgScript", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\"
                "Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = g_1667bac;
            mpCapacity = g_1667bac + 1;
        }
    }

    void assign(const char* first, const char* last);            // 0x00454cb0
    void append(const char* first, const char* last);            // 0x00455d60
    int  find_last_of(const char* p, unsigned pos) const;        // 0x0091bec0
    void erase(unsigned position, unsigned n);                   // 0x0061e200
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }

    // out of line so the 0x00842760 symbol is emitted
    string8_s0084_2620& insert(unsigned pos, const string8_s0084_2620& s);  // 0x00842760 (string8::insert)
};
}
namespace eastl {
inline void MakeRangeString(string8_s0084_2620* pOut, const char* first, const char* last)
{
    unsigned n = (unsigned)(last - first);
    pOut->RangeInitialize(n + 1);
    CopyBytes(pOut->mpBegin, first, n);
    pOut->mpEnd = pOut->mpBegin + n;
    pOut->mpBegin[n] = 0;
}
}
namespace eastl {
template <typename T>
struct vec_s0084_2620 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
};
}
namespace eastl {
template <typename T, int N>
struct fixed_vec_s0084_2620 {
    T* mpBegin;          // +0x00
    T* mpEnd;            // +0x04
    T* mpCapacity;       // +0x08
    unsigned mPad0c;     // +0x0c
    T* mpBuffer;         // +0x10
    unsigned mPad14;     // +0x14
    T mBuffer[N];        // +0x18

    fixed_vec_s0084_2620() {
        mpBuffer = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mpBuffer + N;
    }
    ~fixed_vec_s0084_2620() {
        if (mpBegin && mpBegin != mpBuffer) ::operator delete(mpBegin);
    }
};
}
using eastl::string8_s0084_2620;
typedef string8_s0084_2620 string8_s0084_2620;
struct FindResult_s0084_2620 {
    void* mpNode;    // +0x00
    void* mpExtra;   // +0x04

    FindResult_s0084_2620() {}
    FindResult_s0084_2620(const FindResult_s0084_2620& x) {
        mpNode = x.mpNode;
        mpExtra = x.mpExtra;
    }
};
namespace EA {
namespace ArgScript {
struct cArguments_s0084_2620;
}
}
namespace EA {
namespace ArgScript {
struct cExpression_s0084_2620;
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0084_2620;
}
}
namespace EA {
namespace ArgScript {
struct cState_s0084_2620 { unsigned mStateID; };
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0084_2620 {
    virtual void Execute(cArguments_s0084_2620* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState_s0084_2620* pState);              // +0x08
    virtual int AddRef();                                               // +0x0c
    virtual int Release();                                              // +0x10
    virtual void OnEndBlock(bool bEnd);                                  // +0x14
};
}
}
namespace EA {
namespace ArgScript {
class cIBlockCommand_s0084_2620 { public:
    virtual void Execute(cArguments_s0084_2620* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState_s0084_2620* pState);              // +0x08
    virtual int AddRef();                                               // +0x0c
    virtual int Release();                                              // +0x10
    virtual void OnEndBlock(bool bEnd);                                  // +0x14
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0084_2620 : cICommand_s0084_2620 {
    cIParser_s0084_2620* mParser;   // +0x04
    int mRefCount;                  // +0x08

    cCommandBase_s0084_2620();                                           // 0x0083c800
    virtual ~cCommandBase_s0084_2620();                                  // 0x0083c750
};
}
}
namespace EA {
namespace ArgScript {
struct cMetaCommandBase_s0084_2620 : cICommand_s0084_2620 {
    void* mParser;          // +0x04
    int mRefCount;          // +0x08

    cMetaCommandBase_s0084_2620();                                       // 0x0083c840
    virtual ~cMetaCommandBase_s0084_2620();                              // 0x0083c7c0
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0084_2620 {
    unsigned char pad[0x44];

    cArguments_s0084_2620();                                             // 0x00837ff0
    ~cArguments_s0084_2620();                                            // 0x00837fa0
    const char* const* MainArguments(int start) const;                   // 0x00838320
    bool HasFlag(const char* pFlag);                                     // 0x008380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cExpression_s0084_2620 {
    unsigned char pad[0x20];

    void EvalExpectCharThrow(const char*& p, char c);                    // 0x0083d240
    void EvalString(const char*& p, string8_s0084_2620* pOut);                      // 0x0083dc00
};
}
}
namespace EA {
namespace ArgScript {
struct CmdNode_s0084_2620 {                      // value is a pointer at +0x10
    string8_s0084_2620 key;                                 // +0x00
    void* mpValue;                               // +0x10
    CmdNode_s0084_2620* mpNext;                  // +0x14
};
}
}
namespace EA {
namespace ArgScript {
struct StrNode_s0084_2620 {                      // value is a string8 at +0x10
    string8_s0084_2620 key;                                 // +0x00
    string8_s0084_2620 value;                               // +0x10
    StrNode_s0084_2620* mpNext;                  // +0x20
};
}
}
namespace EA {
namespace ArgScript {
struct CmdTable_s0084_2620 {
    int mPad;                                    // +0x00
    CmdNode_s0084_2620** mpBucketArray;          // +0x04
    unsigned mnBucketCount;                      // +0x08
    unsigned char pad0c[0x20 - 0x0c];            // +0x0c
    FindResult_s0084_2620 find(const void* pKey) const;   // 0x007e2ea0
};
}
}
namespace EA {
namespace ArgScript {
struct StrTable_s0084_2620 {
    int mPad;                                    // +0x00
    StrNode_s0084_2620** mpBucketArray;          // +0x04
    unsigned mnBucketCount;                      // +0x08
    unsigned char pad0c[0x20 - 0x0c];            // +0x0c
    FindResult_s0084_2620 find(const void* pKey) const;   // 0x00842790
};
}
}
namespace EA {
namespace ArgScript {
struct IntVec_s0084_2620 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned mAllocator[2];
};
}
}
namespace EA {
namespace ArgScript {
struct MetaEntry_s0084_2620 { void* mpCommand; void* mpName; };
}
}
namespace EA {
namespace ArgScript {
struct cIncludeHandler_s0084_2620 {
    virtual void* Resolve(const char* pName);    // +0x00
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0084_2620 {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual bool Init();                                                 // +0x08
    virtual bool Shutdown();                                             // +0x0c
    virtual void SetState(cState_s0084_2620* pState);                               // +0x10
    virtual void RegisterCommand(const char* pName, void* pCommand);     // +0x14
    virtual bool UnregisterCommand(void* pCommand);                      // +0x18
    virtual bool UnregisterCommand(const char* pName);                   // +0x1c
    virtual void* Command(const char* pName) const;                      // +0x20
    virtual void SetFlag(int flag, bool value);                          // +0x24
    virtual void SetMinMaxVersion(int nMin, int nMax);                   // +0x28
    virtual int Version() const;                                         // +0x2c
    virtual void ParseBegin();                                           // +0x30
    virtual int ParseEnd(bool bUnwind);                                  // +0x34
    virtual void ParseFile(const char* pPath);                           // +0x38
    virtual void ParseStream(void* pStream);                             // +0x3c
    virtual void ParseCommand(const char* pCommand);                     // +0x40
    virtual void InstantiateMacro(const char* pName, cArguments_s0084_2620* pArgs);  // +0x44
    virtual void Slot48();                                               // +0x48
    virtual bool ParseFileNoThrow(const char* pPath);                    // +0x4c
    virtual bool ParseCommandNoThrow(const char* pCommand);              // +0x50
    virtual bool InstantiateMacroNoThrow(const char* pName, cArguments_s0084_2620* pArgs);  // +0x54
    virtual const char* LastErrorString() const;                         // +0x58
    virtual const char* LineLocationInfo();                              // +0x5c
    virtual void GetLineLocationInfo(string8_s0084_2620* pInfo, int* pLine) const;  // +0x60
    virtual bool CommandExists(const char* pName) const;                 // +0x64
    virtual bool DefinitionExists(const char* pName) const;              // +0x68
    virtual void SetVariable(const char* pName, const char* pValue);     // +0x6c
    virtual const char* Variable(const char* pName) const;               // +0x70
    virtual void SetGlobalVariable(const char* pName, const char* pValue);  // +0x74
    virtual void SetGlobalVariableSet(void* pSet);                       // +0x78
    virtual void PushNamespace(const char* pName);                       // +0x7c
    virtual void PopNamespace();                                         // +0x80
    virtual void PurgeNamespace(const char* pName);                      // +0x84
    virtual const char* CurrentScope() const;                            // +0x88
    virtual void StartBlock(cIBlockCommand_s0084_2620* pCommand);                   // +0x8c
    virtual void StartMetaBlock(cIMetaCommand* pCommand, const char* pEndName);  // +0x90
    virtual bool ParseBool(const char* pText) const;                     // +0x94
    virtual float ParseFloat(const char* pText) const;                   // +0x98
    virtual int ParseInt(const char* pText) const;                       // +0x9c
    virtual unsigned ParseUint(const char* pText) const;                 // +0xa0
    virtual cExpression_s0084_2620& Expression();                        // +0xb8
};
}
}
namespace EA {
namespace ArgScript {
struct cParser_s0084_2620 : cIParser_s0084_2620 {
    unsigned char pad04[0x10 - 0x04];
    unsigned mFlags;                                     // +0x10
    void* mLogTarget;                                    // +0x14
    unsigned char pad18[0x1c - 0x18];
    int mMinVersion;                                     // +0x1c
    int mMaxVersion;                                     // +0x20
    int mCurrentVersion;                                 // +0x24
    unsigned char pad28[0x2c - 0x28];
    CmdTable_s0084_2620 mCommands;                       // +0x2c (bucket array +0x30, count +0x34)
    unsigned char pad38[0x6c - 0x4c];
    CmdTable_s0084_2620 mTable6c;                        // +0x6c (bucket array +0x70, count +0x74)
    StrTable_s0084_2620 mTable8c;                        // +0x8c (bucket array +0x90, count +0x94)
    StrTable_s0084_2620 mTableAc;                        // +0xac (bucket array +0xb0, count +0xb4)
    cIncludeHandler_s0084_2620* mIncludeHandler;         // +0xcc
    string8_s0084_2620 mIncludeBaseDir;                             // +0xd0
    string8_s0084_2620 mCurrentPath;                                // +0xe0
    int mCurrentLine;                                    // +0xf0
    unsigned char padf4[0x108 - 0xf4];
    eastl::vec_s0084_2620<void*> mBlockCommandStack;     // +0x108 (4-byte elements)
    eastl::vec_s0084_2620<MetaEntry_s0084_2620> mMetaCommandStack;  // +0x11c (8-byte elements)
    string8_s0084_2620 mScope;                                      // +0x130
    IntVec_s0084_2620 mScopeOffsets;                     // +0x140
    string8_s0084_2620 mLastErrorString;                            // +0x154
    unsigned char mErrorFlag;                            // +0x164
    unsigned char pad165[0x1b0 - 0x165];
    char mCaseInsensitive[0x40];                         // +0x1b0

    void  ParseFile(const char* pPath);                  // 0x00842c60
    void  ParseStream(void* pStream);                    // 0x00842f50
    void* Command(const char* pName) const;              // 0x00842c10
    bool  DefinitionExists(const char* pName) const;     // 0x00843280
    bool  HasName6c(const char* pName) const;            // 0x008432d0
    void  GetLineLocationInfo(string8_s0084_2620* pInfo, int* pLine) const;   // 0x00843240
    const char* LookupName(const char* pName) const;     // 0x00843320
};
}
}
namespace EA {
namespace ArgScript {
typedef cParser_s0084_2620 cParser_s0084_2620;
}
}
namespace EA {
namespace ArgScript {
typedef cArguments_s0084_2620 cArguments_s0084_2620;
}
}
namespace EA {
namespace ArgScript {
typedef cExpression_s0084_2620 cExpression_s0084_2620;
}
}
using EA::ArgScript::cArguments_s0084_2620;
using EA::ArgScript::cExpression_s0084_2620;
using EA::ArgScript::cParser_s0084_2620;
using EA::ArgScript::cIBlockCommand_s0084_2620;

// ---- cEndCommand ----
struct cEndCommand_s0084_2620 : EA::ArgScript::cMetaCommandBase_s0084_2620 {
    cParser_s0084_2620* mState;                                     // +0x0c
    void Execute(cArguments_s0084_2620* pArgs);                     // 0x00842910
};

namespace {

// ---- cMatchFunction: value-matching expression function ----
struct cMatchFunction_s0084_2620 {
    int mPad00;
    int mPad04;

    int  EvalInt(const char** p, cExpression_s0084_2620* pExpr);    // 0x00842620
    void EvalReal();                                     // 0x00842a90
};

// ---- cPurgeCommand ----
struct cPurgeCommand_s0084_2620 : EA::ArgScript::cCommandBase_s0084_2620 {
    void Execute(cArguments_s0084_2620* pArgs);                     // 0x00842980
};

// ---- cVersionCommand ----
struct cVersionCommand_s0084_2620 : EA::ArgScript::cCommandBase_s0084_2620 {
    cParser_s0084_2620* mState;                                     // +0x0c
    void Execute(cArguments_s0084_2620* pArgs);                     // 0x00842a00
};

// ---- ArgScript::If (0x90): two fixed vectors plus a cArguments ----
struct If_s0084_2620 : EA::ArgScript::cMetaCommandBase_s0084_2620 {
    int mPad0c;                                              // +0x0c
    eastl::fixed_vec_s0084_2620<char, 16> mVec1;             // +0x10
    eastl::fixed_vec_s0084_2620<char, 16> mVec2;             // +0x38
    cArguments_s0084_2620 mArgs;                                        // +0x60

    If_s0084_2620();                                         // 0x00842ac0
    ~If_s0084_2620();                                        // 0x00842b70
    virtual void Execute(cArguments_s0084_2620* pArgs);
    virtual void OnEndParse(bool bEnd);                      // 0x00842b50
};

// ---- eastl::pair<string8 const, string8> ----
struct StringStringPair_s0084_2620 {
    const string8_s0084_2620 first;     // +0x00
    string8_s0084_2620 second;          // +0x10

    ~StringStringPair_s0084_2620();                          // 0x00842720
};

// The "stream" object passed to ParseStream (an IOStream with a virtual interface).
struct IOStream_s0084_2620 {
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual void Slot08();                          // +0x08
    virtual void Slot0c();                          // +0x0c
    virtual bool IsValid();                         // +0x10
    virtual bool IsEOF();                           // +0x14
    virtual void Slot18();                          // +0x18
    virtual void Slot1c();                          // +0x1c
    virtual void Slot20();                          // +0x20
    virtual void Slot24();                          // +0x24
    virtual void Slot28();                          // +0x28
    virtual bool HasData();                         // +0x2c
};

// strip the file name off a path, leaving the directory (with trailing separator).
}  // namespace
// ---- items of slice s00842620 end

// ---- items of slice s00843650 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA { namespace ArgScript { struct cParser_s0084_3650; } }
extern "C" __declspec(dllimport) int  __cdecl _stat64i32(const char*, void*);
extern char gEmptyA[1];       // 0x01667bac: the shared empty string
extern char gEmptyB[1];       // 0x01667bad
bool __cdecl StripCommentsAndWhiteSpace(char* pText, void* pOut, int* pDepth);  // 0x00840ec0
inline unsigned CharStrlen_s0084_3650(const char* p)
{
    const char* pBase = p + 1;
    while (*p++) {}
    return (unsigned)(p - pBase);
}
namespace eastl {
struct allocator_s0084_3650 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_3650 {
    char* mpBegin;                     // +0x00
    char* mpEnd;                       // +0x04
    char* mpCapacity;                  // +0x08
    allocator_s0084_3650 mAllocator;   // +0x0c

    string8_s0084_3650() { mpBegin = gEmptyA; mpEnd = gEmptyA; mpCapacity = gEmptyA + 1; }
    string8_s0084_3650(const char* p) {
        unsigned n = (unsigned)(CharStrlen_s0084_3650(p));
        if (n + 1 > 1) {
            mpBegin = (char*)EAAllocate(n + 1, "ArgScript", 0, 0, kAllocFile, 0xd1);
            mpCapacity = mpBegin + n + 1;
        } else {
            mpBegin = gEmptyA;
            mpCapacity = gEmptyA + 1;
        }
        if (n) CopyBytes(mpBegin, p, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~string8_s0084_3650() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    string8_s0084_3650& append(const char* first, const char* last);   // 0x00455d60
    string8_s0084_3650& assign(const char* first, const char* last);   // 0x00454cb0
    int  compare(unsigned pos, unsigned n, const char* s) const;       // 0x008417c0
    int  find(const char* pStr, unsigned pos) const;                   // 0x00841d00
    void clearContents();                                              // 0x00478930
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
}
namespace eastl {
bool operator==(const string8_s0084_3650& a, const string8_s0084_3650& b);
}
namespace eastl {
bool operator==(const string8_s0084_3650& a, const char* pB);
}
namespace eastl {
struct bool_vec_s0084_3650 {
    bool* mpBegin;      // +0x00
    bool* mpEnd;        // +0x04
    bool* mpCapacity;   // +0x08
    unsigned mPad0c;    // +0x0c
    bool* mpBuffer;     // +0x10
    unsigned mPad14;    // +0x14
    bool mStorage[16];  // +0x18

    void DoInsertValue(bool* pPosition, const bool* pValue);    // 0x00843bc0 (pos, value)
};
}
namespace eastl {
struct VecPtr_s0084_3650 {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned mAllocator[2];

    void** DoInsertValue(void** pos, void** const* pValue);   // 0x00843ab0
};
}
namespace eastl {
template <typename T>
struct vec_s0084_3650 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
};
}
namespace eastl {
struct HashNode_s0084_3650 {
    string8_s0084_3650 key;         // +0x00
    void* mpValue;                  // +0x10
    void* mpValue2;                 // +0x14
    unsigned mPad18;                // +0x18
    unsigned mHash;                 // +0x1c
    HashNode_s0084_3650* mpNext;    // +0x20
};
}
namespace eastl {
struct FindResult_s0084_3650 {
    HashNode_s0084_3650* mpNode;        // +0x00
    HashNode_s0084_3650** mppBucket;    // +0x04

    FindResult_s0084_3650() {}
    FindResult_s0084_3650(const FindResult_s0084_3650& r)
        : mpNode(r.mpNode), mppBucket(r.mppBucket) {}
};
}
namespace eastl {
struct InsertResult_s0084_3650 {
    HashNode_s0084_3650* mpNode;        // +0x00
    HashNode_s0084_3650** mppBucket;    // +0x04
    bool mbInserted;                    // +0x08

    InsertResult_s0084_3650() {}
    InsertResult_s0084_3650(const InsertResult_s0084_3650& r)
        : mpNode(r.mpNode), mppBucket(r.mppBucket), mbInserted(r.mbInserted) {}
};
}
namespace eastl {
struct RehashLocal_s0084_3650 {
    bool mbGrown;            // +0x00
    unsigned mnNewCount;     // +0x04
};
}
namespace eastl {
struct HashTable_s0084_3650 {
    unsigned mPad00;                       // +0x00
    HashNode_s0084_3650** mpBucketArray;   // +0x04
    unsigned mnBucketCount;                // +0x08
    unsigned mnNodeCount;                  // +0x0c
    unsigned char mPad10[0x10];            // +0x10 (the allocator)

    FindResult_s0084_3650 find(const string8_s0084_3650* pKey) const;              // 0x007e2ea0
    InsertResult_s0084_3650 insert(const string8_s0084_3650* pKey,
                                   RehashLocal_s0084_3650* pRehash);               // 0x008439b0
};
}
namespace eastl {
void* __fastcall ConstructMacroNode(void* pTable, int, const string8_s0084_3650* pKey);
}
namespace eastl {
void __fastcall GrowMacroTable(void* pAllocator, int, RehashLocal_s0084_3650* pOut,
                               unsigned nBucketCount, unsigned nNodeCount, int bOne);
}
namespace eastl {
void __fastcall FreeMacroBuckets(void* pTable, int, unsigned nCount);
}
using eastl::string8_s0084_3650;
typedef string8_s0084_3650 string8_s0084_3650;
namespace EA {
namespace ArgScript {
class cError_s0084_3650 { public:
    cError_s0084_3650(const char* fmt, ...);   // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0084_3650 {
    void SplitIntoArguments(const char* pText);   // 0x008383c0
    const char** MainArguments(int index);        // 0x00838320
    int NumArguments();                           // 0x00837f30
    const char* operator[](int index);            // 0x00837f20
    void Advance();                               // 0x00837ed0
    void FindUnprocessed();                       // 0x00837f40
    unsigned char pad[0x44];
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0084_3650 {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
    virtual void RunFile(const char* pPath);      // +0x38
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser2_s0084_3650 {                      // the same object, its +0x94 slot
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
    virtual void s36();
    virtual bool EvalCondition(const char* pExpr);  // +0x94
};
}
}
namespace EA {
namespace ArgScript {
struct cIParserExpr_s0084_3650 {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual const char* LookupVariable(const char* pName);   // +0x70
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0084_3650 {
    virtual void Execute(cArguments_s0084_3650* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_3650& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c
};
}
}
namespace EA {
namespace ArgScript {
// 8-byte entry pushed on cParser::mMetaCommandStack.
struct cMetaEntry_s0084_3650 {
    cICommand_s0084_3650* mCommand;         // +0x00
    const string8_s0084_3650* mpEndToken;   // +0x04
};

// vec<cMetaEntry, sp_vector_allocator>
struct cMetaStack_s0084_3650 {
    cMetaEntry_s0084_3650* mpBegin;      // +0x00
    cMetaEntry_s0084_3650* mpEnd;        // +0x04
    cMetaEntry_s0084_3650* mpCapacity;   // +0x08
    unsigned mAllocator[2];              // +0x0c
};

// The state object hanging off a command: its current-directory string sits at +0xd0.
struct cState_s0084_3650 {
    unsigned char mPad0[0xd0];
    string8_s0084_3650 mCurrentDir;    // +0xd0
};

// The cICommand layout with the fields these command classes share:
// vptr(+0) / parser(+4) / refcount(+8).
struct cCommandBase_s0084_3650 {
    virtual void Execute(cArguments_s0084_3650* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_3650& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c

    cIParser_s0084_3650* mParser;      // +0x04
    int mRefCount;                     // +0x08
};

// Commands that run a script file (state pointer at +0x0c).
struct cIncludeCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cState_s0084_3650* mState;         // +0x0c

    void ExecuteBody(cArguments_s0084_3650* pArgs);      // 0x00843cc0
};

struct cIncludeIfExistsCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cState_s0084_3650* mState;         // +0x0c

    void ExecuteBody(cArguments_s0084_3650* pArgs);      // 0x00843e50
};

// The if meta-command: two byte-flag vectors then the condition arguments.
struct cIfCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cParser_s0084_3650* mFullParser;           // +0x0c
    eastl::bool_vec_s0084_3650 mTakenVector;   // +0x10 (mpEnd at +0x14)
    eastl::bool_vec_s0084_3650 mCondVector;    // +0x38 (mpEnd at +0x3c)
    cArguments_s0084_3650 mArgs;               // +0x60

    bool ParseBody(const string8_s0084_3650& line);   // 0x00843ff0
};

struct CmdNode_s0084_3650 {
    unsigned char mPad0[0x10];
    void* mpValue;                     // +0x10
};

// mCommands: bucket array at +0x04, bucket count at +0x08, keyed on a case-insensitive string.
struct CmdTable_s0084_3650 {
    unsigned mPad00;                          // +0x00
    CmdNode_s0084_3650** mpBucketArray;       // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned char mPad0c[0x20 - 0x0c];        // +0x0c

    eastl::FindResult_s0084_3650 find(const string8_s0084_3650* pKey) const;   // 0x007e2ea0
};

}
}
typedef EA::ArgScript::cArguments_s0084_3650      cArguments_s0084_3650;
struct EA::ArgScript::cParser_s0084_3650 {
    virtual void v00();                                     // vptr at +0x00
    unsigned char mPad0004[0x100];
    int mBlockCommentDepth;                                 // +0x104
    eastl::vec_s0084_3650<void*> mBlockCommandStack;        // +0x108
    EA::ArgScript::cMetaStack_s0084_3650 mMetaCommandStack; // +0x11c
    string8_s0084_3650 mScope;                              // +0x130
    eastl::vec_s0084_3650<int> mScopeOffsets;               // +0x140
    string8_s0084_3650 mLastError;                          // +0x154
    unsigned mPad164;                                       // +0x164
    int mNesting;                                           // +0x168
    cArguments_s0084_3650 mArgs;                                       // +0x16c
    char mLCNameStorage[0x1c];                              // +0x1b0 (case-insensitive command name)

    void SubstituteVariables(string8_s0084_3650* pLine, int bFlag);   // 0x00843650
    cICommand_s0084_3650* CommandLookup(const char* pName);           // 0x00843920
    void ParseCommand(const char* pText);                             // 0x008440d0
};
inline EA::ArgScript::CmdTable_s0084_3650* CmdTableOf(void* p)
{
    return (EA::ArgScript::CmdTable_s0084_3650*)((char*)p + 0x2c);
}
// ---- items of slice s00843650 end

// ---- items of slice s00846280 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA { namespace ArgScript { struct cParser_s0084_6280; } }
extern "C" __declspec(dllimport) int  __cdecl memcmp(const void*, const void*, unsigned int);
extern "C" __declspec(dllimport) char* __cdecl _ltoa(long value, char* buffer, int radix);
void  __cdecl PoolFree(void* p);                                          // 0x00f47380
int   __cdecl Snprintf8(char* pOut, unsigned nSize, const char* pFmt, ...);       // 0x009384e0
inline unsigned CharStrlen_s0084_6280(const char* p)
{
    const char* pBase = p + 1;
    while (*p++) {}
    return (unsigned)(p - pBase);
}
namespace eastl {
struct allocator_s0084_6280 { unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_6280 {
    char* mpBegin;                     // +0x00
    char* mpEnd;                       // +0x04
    char* mpCapacity;                  // +0x08
    allocator_s0084_6280 mAllocator;   // +0x0c

    string8_s0084_6280() { mpBegin = gEmptyA; mpEnd = gEmptyA; mpCapacity = gEmptyA + 1; }
    __forceinline string8_s0084_6280(const char* p)
        : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        RangeInitialize(p, p + CharStrlen_s0084_6280(p));
    }
    __forceinline void RangeInitialize(const char* pBegin, const char* pEnd) {
        unsigned n = (unsigned)(pEnd - pBegin);
        AllocateSelf(n + 1);  // 0x00616aa0 (string8::AllocateSelf)
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    __forceinline void AllocateSelf(unsigned n) {
        if (n > 1) {
            mpBegin = (char*)EAAllocate(n, "ArgScript", 0, 0, kAllocFile, 0xd1);
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = gEmptyA;
            mpCapacity = gEmptyA + 1;
        }
    }
    __forceinline static char* CharStringUninitializedCopy(const char* pSource,
                                                           const char* pSourceEnd,
                                                           char* pDestination) {
        CopyBytes(pDestination, pSource, (unsigned)(pSourceEnd - pSource));
        return pDestination + (pSourceEnd - pSource);
    }
    __forceinline ~string8_s0084_6280() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::PoolFree(mpBegin);
    }
    string8_s0084_6280& assign(const char* first, const char* last);   // 0x00454cb0
    string8_s0084_6280& append(const char* first, const char* last);   // 0x00455d60
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
}
namespace eastl {
bool operator==(const string8_s0084_6280& a, const string8_s0084_6280& b);
}
namespace eastl {
struct StrNode_s0084_6280 {
    string8_s0084_6280 key;         // +0x00
    void* mpPayload;                // +0x10
    unsigned mHash;                 // +0x14
    unsigned char mPad18[8];        // +0x18
    StrNode_s0084_6280* mpNext;     // +0x20
};
}
// the macro-table node: a MacroPair (string8 key + refcounted value) followed by the bucket chain link
struct MacroHashNode { MacroPair mValue; MacroHashNode* mpNext; };
void __fastcall MacroPair_dtor(MacroPair* p);
namespace eastl {
struct FindResult_s0084_6280 {
    StrNode_s0084_6280* mpNode;
    StrNode_s0084_6280** mppBucket;
    FindResult_s0084_6280() {}
    FindResult_s0084_6280(const FindResult_s0084_6280& r) : mpNode(r.mpNode), mppBucket(r.mppBucket) {}
};
}
namespace eastl {
struct StrHashtable_s0084_6280 {
    unsigned mPad00;                          // +0x00
    StrNode_s0084_6280** mpBucketArray;       // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnNodeCount;                     // +0x0c
    unsigned char mAllocator[0x14 - 0x10];    // +0x10

    FindResult_s0084_6280 find(const string8_s0084_6280* pKey) const;   // 0x007e2ea0
    void* FindByHash(unsigned nHash, const string8_s0084_6280* pKey);    // 0x00846530
    void* EraseNode(StrNode_s0084_6280** ppSlot);   // not 0x00846c00: that is MacroHashtable::erase(iterator)
    void DoFreeNodes(MacroHashNode** pBucketArray, unsigned nBucketCount);   // 0x00846630
    void DoRehash(unsigned nNewBucketCount);                            // 0x00847120
};
}
namespace eastl {
struct char_vec_s0084_6280 {
    char* mpBegin;    // +0x00
    char* mpEnd;      // +0x04
    char* mpCapacity; // +0x08
};
}
namespace eastl {
void __cdecl AppendRange(char* pFirst, char* pLast, const char* pSrcFirst, const char* pSrcLast);
}
namespace eastl {
void __cdecl CharVecInsert(void* pVec, char* pWhere, unsigned nLength,
                           const char* pSrcFirst, const char* pSrcLast);
}
namespace eastl {
struct hash_map_s0084_6280 {
    StrHashtable_s0084_6280 mTable;    // +0x00
    void* operator[](const string8_s0084_6280* pKey);   // 0x00847060
};
}
namespace eastl {
extern StrNode_s0084_6280** mpNewBucketArray_probe;
}
namespace eastl {
void __cdecl DoFreeNodesTable(void* pTable, int nBucketCount);
}
namespace eastl {
void __cdecl ExprTableClear(void* pTable);
}
eastl::StrNode_s0084_6280** eastl::mpNewBucketArray_probe = 0;
using eastl::string8_s0084_6280;
typedef string8_s0084_6280 string8_s0084_6280;
namespace EA {
namespace ArgScript {
class cError_s0084_6280 { public:
    cError_s0084_6280(const char* fmt, ...);   // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0084_6280 {
    void SplitIntoArguments(const char* pText);   // 0x008383c0
    const char** MainArguments(int index);        // 0x00838320
    const char** MainArguments(int* pCount, int a, int b);   // 0x00838020
    unsigned char pad[0x44];
};
}
}
namespace EA {
namespace ArgScript {

// The parser interface as seen by the commands (slots used here: +0x94,+0x98,+0x9c,+0xa4,+0xa8,+0xac,+0xb4).
struct cCmdParser_s0084_6280 {
    virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
    virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
    virtual void s08();  virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();  virtual void s15();
    virtual void s16();  virtual void s17();  virtual void s18();  virtual void s19();
    virtual void s20();  virtual void s21();  virtual void s22();  virtual void s23();
    virtual void s24();  virtual void s25();  virtual void s26();  virtual void s27();
    virtual void s28();  virtual void s29();  virtual void s30();  virtual void s31();
    virtual void s32();  virtual void s33();  virtual void s34();  virtual void s35();
    virtual void s36();
    virtual bool        EvalCondition(const char* pExpr);   // +0x94
    virtual double      EvalFloat(const char* pExpr);        // +0x98
    virtual long        EvalInt(const char* pExpr);          // +0x9c
    virtual void        s3a();                                                  // +0xa0
    virtual void        EvalV2(float* pOut, const char* pExpr);   // +0xa4
    virtual void        EvalV3(float* pOut, const char* pExpr);   // +0xa8
    virtual void        EvalV4(float* pOut, const char* pExpr);   // +0xac
    virtual void        s40();                                                  // +0xb0
    virtual void        EvalColor(float* pOut, const char* pExpr);   // +0xb4
};

// ---- the cSet* command base: vptr / parser(+4) / refcount(+8) / full parser(+0xc) -------------
struct cSetCmdBase_s0084_6280 {
    virtual void Execute(cArguments_s0084_6280* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_6280& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c

    cCmdParser_s0084_6280* mParser;    // +0x04
    int mRefCount;                     // +0x08
    cParser_s0084_6280* mFullParser;   // +0x0c
    cArguments_s0084_6280 mArgs;       // +0x10
};

struct cSetCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846680
};
struct cSetECommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008466b0
};
struct cSetBCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846770
};
struct cSetICommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008467c0
};
struct cSetFCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846810
};
struct cSetCCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846870
};
struct cSetV2Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008468f0
};
struct cSetV3Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846960
};
struct cSetV4Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008469d0
};
struct cUndefineCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846c80
};

// The macro-definition hash_map node payload: an AutoRefCount<cMacroDefinition>.
struct cMacroDefinition_s0084_6280 {
    virtual void md00();  virtual void md01();  virtual void md02();  virtual void md03();
};
}
}
struct EA::ArgScript::cParser_s0084_6280 {
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
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
    virtual void v52();

    unsigned char mPad0004[0x08];   // +0x04
    unsigned char mBool0c;          // +0x0c
    unsigned char mPad0d[0x07];     // +0x0d
    void* mpTable14;                // +0x14
    void* mpTable18;                // +0x18
    char* mpMacroState0c;           // (the +0xc-driven state pointer used by 0x00846a50)
    char* mpMacroState10;           // (the +0x10-driven state pointer used by 0x00846a50)
    unsigned mInt24;                // +0x24
    eastl::hash_map_s0084_6280 mCommands;         // +0x2c (mCommands bucket table)
    unsigned char mPad4c[0x20];                   // +0x4c expression table
    eastl::hash_map_s0084_6280 mMacros;           // +0x6c (macro hash_map)
    eastl::StrHashtable_s0084_6280 mMacroNodes;   // +0x8c? (separate node table used by Shutdown)

    void DefineMacro(const char* pName, const char* pBody);   // 0x00846280
    const char* LookupMacroText(const char* pName);           // 0x00846420
    bool InsertMacroName(const string8_s0084_6280* pName);    // 0x00846a50
    void SetVariableNoSubstitution(const char* pName, const char* pValue);   // 0x00846160
    void SubstituteVariables(string8_s0084_6280* pLine, int bFlag);          // 0x00843650
    void Shutdown();                                          // 0x00846db0
    void ParseBegin();                                        // 0x00846f10
    void DefineMacroLine(const char* pName, const char* pLine);   // 0x00846b00
};
// ---- items of slice s00846280 end

// ---- items of slice s00845370 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace EA {
namespace ArgScript {
struct cArguments_s0084_5370;
}
}
namespace EA {
namespace ArgScript {
class cParser_s0084_5370;
}
}
namespace EA {
namespace ArgScript {
struct cParserIsState { uint32_t m[2]; };
}
}
namespace EA {
namespace ArgScript {
class cICommand_s0084_5370 { public:
    virtual void v0() {}
    virtual void v1() {}
    virtual void Attach(cParser_s0084_5370*, void*) {}       // slot 2 (+0x8)
    virtual int  AddRef() { return 0; }           // slot 3 (+0xc)
    virtual int  Release() { return 0; }          // slot 4 (+0x10)
    virtual void ParseLine(const cArguments_s0084_5370&) {}
};
}
}
namespace EA {
namespace ArgScript {
extern "C" void  __cdecl FUN_00f47380(void* p);                                    // operator delete
}
}
namespace EA {
namespace ArgScript {
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned size);  // memcpy
}
}
namespace EA {
namespace ArgScript {
void MakeCaseInsensitiveChars(char* src, int* dst);                                // 0x00840cc0
}
}
namespace EA {
namespace ArgScript {
struct string8_s0084_5370 {
    char* mpBegin;                          // +0
    char* mpEnd;                            // +4
    char* mpCapacity;                       // +8
    uint32_t mPad;                          // +0xc

    string8_s0084_5370()
    {
        mpBegin = (char*)0x01667bac;
        mpEnd = (char*)0x01667bac;
        mpCapacity = (char*)0x01667bad;
    }
    __forceinline string8_s0084_5370(const char* first, const char* last)
    {
        uint32_t n = (uint32_t)(last - first);
        if (n + 1 > 1) {
            mpBegin = (char*)operator new[](n + 1, "ArgScript", 0, 0, (const char*)0x013ebb38, 0xd1);
            mpCapacity = mpBegin + n + 1;
        } else {
            mpBegin = (char*)0x01667bac;
            mpCapacity = (char*)0x01667bad;
        }
        FUN_011e0744(mpBegin, first, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~string8_s0084_5370()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            FUN_00f47380(mpBegin);
    }
    string8_s0084_5370& append(const char* first, const char* last);    // 0x00455d60
    string8_s0084_5370& assign(const char* first, const char* last);    // 0x00454cb0
};
}
}
namespace EA {
namespace ArgScript {
bool String8Equal(const string8_s0084_5370& a, const string8_s0084_5370& b);       // 0x00554fb0
}
}
namespace EA {
namespace ArgScript {
struct PairB {
    string8_s0084_5370    mKey;        // +0
    cICommand_s0084_5370* mpObject;    // +0x10
    ~PairB();               // 0x0067e830
};
}
}
namespace EA {
namespace ArgScript {
struct CommandNode : PairB {
    CommandNode* mpNext;    // +0x14
};
}
}
namespace EA {
namespace ArgScript {
struct PairSS {
    string8_s0084_5370 mKey;           // +0
    string8_s0084_5370 mValue;         // +0x10
    PairSS(const string8_s0084_5370& k, const string8_s0084_5370& v);   // 0x00841d60
};
}
}
namespace EA {
namespace ArgScript {
struct StringNode : PairSS {
    StringNode* mpNext;     // +0x20
};
}
}
namespace EA {
namespace ArgScript {
struct InsertResult { StringNode* mpNode; void** mpBucketPtr; };
}
}
namespace EA {
namespace ArgScript {
struct CmdIter {
    CommandNode*  mpNode;
    CommandNode** mpBucketPtr;
    bool operator!=(const CmdIter& o) const { return mpNode != o.mpNode; }
    CmdIter& operator++()
    {
        CommandNode* n = mpNode->mpNext;
        while (!n) { ++mpBucketPtr; n = *mpBucketPtr; }
        mpNode = n;
        return *this;
    }
};
}
}
namespace EA {
namespace ArgScript {
struct CommandMap {
    uint32_t       mField00;            // +0
    CommandNode**  mpBucketArray;       // +4
    uint32_t       mnBucketCount;       // +8
    uint32_t       mnElementCount;      // +0xc
    uint32_t       mPad10[4];           // +0x10
    cICommand_s0084_5370*& operator[](const string8_s0084_5370& key);   // 0x0083cb70
    CmdIter find(const string8_s0084_5370& key);             // 0x007e2ea0
    CmdIter erase(CmdIter pos);                   // 0x00845460
    CmdIter begin()
    {
        CmdIter it;
        it.mpBucketPtr = mpBucketArray;
        CommandNode* n = *it.mpBucketPtr;
        while (!n) { ++it.mpBucketPtr; n = *it.mpBucketPtr; }
        it.mpNode = n;
        return it;
    }
    CmdIter end()
    {
        CmdIter it;
        it.mpBucketPtr = mpBucketArray + mnBucketCount;
        it.mpNode = *it.mpBucketPtr;
        return it;
    }
};
}
}
namespace EA {
namespace ArgScript {
struct StrIter {
    StringNode*  mpNode;
    StringNode** mpBucketPtr;
    bool operator!=(const StrIter& o) const { return mpNode != o.mpNode; }
};
}
}
namespace EA {
namespace ArgScript {
struct StringMap {
    uint32_t      mField00;             // +0
    StringNode**  mpBucketArray;        // +4
    uint32_t      mnBucketCount;        // +8
    uint32_t      mnElementCount;       // +0xc
    uint32_t      mPad10[4];            // +0x10
    string8_s0084_5370& operator[](const string8_s0084_5370& key);                  // 0x00845370
    StrIter find(const string8_s0084_5370& key);                         // 0x007e2ea0
    StrIter erase(StrIter pos);                               // 0x008455c0
    int erase(const string8_s0084_5370& key);                            // 0x008454e0
    InsertResult insert(const PairSS* value, void* rehash);   // 0x008439b0
    StrIter end()
    {
        StrIter it;
        it.mpBucketPtr = mpBucketArray + mnBucketCount;
        it.mpNode = *it.mpBucketPtr;
        return it;
    }
};
}
}
namespace EA {
namespace ArgScript {
class cExprFunction_s0084_5370 { public:
    virtual void Eval() {}
    int mRefCount;
    cExprFunction_s0084_5370() : mRefCount(0) {}
};
}
}
namespace EA {
namespace ArgScript {
class cExpression_s0084_5370 { public:
    void AddFunction(const char* name, cExprFunction_s0084_5370* fn);   // @ 0x83df90, ret 8
};
}
}
namespace EA {
namespace ArgScript {
class cParser_s0084_5370 { public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void AddCommand(const char* name, cICommand_s0084_5370* cmd);   // slot 5 (+0x14)
#define PV(n) virtual void v##n();
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
    PV(46)
    virtual void Reset(int arg);                                 // slot 47 (+0xbc)
    cParserIsState mStateDefault;       // +0x04
    bool mInitialized;                  // +0x0c
    char pad1[0x1b];                    // +0x0d..+0x27
    cParserIsState* mState;             // +0x28
    CommandMap mCommands;               // +0x2c (0x20)
    cExpression_s0084_5370 mExpression;            // +0x4c
    char pad50[0x3f];                   // +0x4d..+0x8b
    StringMap mVariables;               // +0x8c (0x20)
    char padAC[0x84];                   // +0xac..+0x12f
    string8_s0084_5370 mScope;                     // +0x130
    char pad140[0x70];                  // +0x140..+0x1af
    string8_s0084_5370 mNameBuf;                   // +0x1b0
    void RegisterCommand(const char* name, cICommand_s0084_5370* cmd);              // 0x00846000
    bool UnregisterCommand(cICommand_s0084_5370* cmd);                              // 0x00846070
    bool UnregisterCommand(const char* name);                            // 0x008460f0
    void SetVariableNoSubstitution(const char* name, const char* value); // 0x00846160
    bool Init();                        // @ 0x8456e0
};
}
}
// ---- items of slice s00845370 end

// ---- items of slice s00847200 begin (TODO(rewrite): local stubs, replace by canonical classes)

extern void* gEmptyBucketArray[1]; // 0x0154df28
void __cdecl Delete_s0084_7200(void* p);   // 0x00f47380: operator delete without the TU-wide throw() so these destructors keep their EH states
namespace eastl {
class allocator_s0084_7200 { public: unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_7200 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0084_7200 mAllocator;

    string8_s0084_7200() { mpBegin = gEmptyStr; mpEnd = gEmptyStr; mpCapacity = gEmptyStr + 1; }
    ~string8_s0084_7200() { if (mpCapacity - mpBegin > 1 && mpBegin) Delete_s0084_7200(mpBegin); }
};
}
namespace eastl {
struct Hashtable {
    unsigned   mUninit0;       // +0x00
    void**     mpBucketArray;  // +0x04
    unsigned   mnBucketCount;  // +0x08
    unsigned   mnElementCount; // +0x0c
    float      mfMaxLoad;      // +0x10
    float      mfGrowth;       // +0x14
    unsigned   mnNextResize;   // +0x18
    unsigned   mUninit1c;      // +0x1c

    Hashtable()
    {
        mfMaxLoad = 1.0f;
        mfGrowth = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mnElementCount = 0;
        mnNextResize = 0;
    }
    ~Hashtable()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1) Delete_s0084_7200(mpBucketArray);
    }
    void DoFreeNodes(void** pBucketArray, unsigned nBucketCount);
};
}
namespace eastl {
template <typename T>
struct vec_s0084_7200 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s0084_7200 mAllocator;
    unsigned mExtra;
    vec_s0084_7200() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vec_s0084_7200() { if (mpBegin && ((int*)mpBegin)[-1]) Delete_s0084_7200(mpBegin); }
};
}
using eastl::string8_s0084_7200;
using eastl::Hashtable;
using eastl::vec_s0084_7200;
namespace EA {
namespace ArgScript {
class cArguments_s0084_7200 {
    public: unsigned char pad[0x44];
    cArguments_s0084_7200();
    ~cArguments_s0084_7200();
    void** MainArguments(int);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
};
}
}
namespace EA {
namespace ArgScript {
class cExpression_s0084_7200 { public: Hashtable mFunctions; cExpression_s0084_7200(); ~cExpression_s0084_7200() {} };
}
}
namespace EA {
namespace ArgScript {
struct IStream { virtual void v0(); virtual void v1(); virtual void Release(); };
}
}
namespace EA {
namespace ArgScript {
template <typename T>
struct AutoRefCount_s0084_7200 {
    T* mpObject;
    AutoRefCount_s0084_7200() : mpObject(0) {}
    void Release() {
        T* p = mpObject;
        if (p) p->Release();
    }
    ~AutoRefCount_s0084_7200() { Release(); }
};
}
}
namespace EA {
namespace ArgScript {
class cIGlobalVariableSet { public: virtual void v0(); virtual void Release(); };
}
}
namespace EA {
namespace ArgScript {
struct cMetaEntry { void* mCommand; int mLine; };
}
}
namespace EA {
namespace ArgScript {
class cParser_s0084_7200 { public:
    void**   mvftable;          // +0x000
    unsigned mStateID;          // +0x004
    int      mRefCount;         // +0x008
    bool     mInitialized;      // +0x00c
    unsigned mFlags;            // +0x010
    AutoRefCount_s0084_7200<IStream> mOutStream;    // +0x014
    AutoRefCount_s0084_7200<IStream> mTraceStream;  // +0x018
    int      mMinVersion;       // +0x01c
    int      mMaxVersion;       // +0x020
    int      mScriptVersion;    // +0x024
    int      mUnknown28;        // +0x028
    Hashtable mCommands;        // +0x02c
    cExpression_s0084_7200 mExpression;    // +0x04c
    Hashtable mMacroDefinitions; // +0x06c
    Hashtable mVariables;       // +0x08c
    Hashtable mGlobalVariables; // +0x0ac
    AutoRefCount_s0084_7200<cIGlobalVariableSet> mGlobalVariableSet;  // +0x0cc
    string8_s0084_7200  mIncludeBaseDir;   // +0x0d0
    string8_s0084_7200  mCurrentPath;      // +0x0e0
    int      mCurrentLine;      // +0x0f0
    string8_s0084_7200  mLineLocation;     // +0x0f4
    int      mBlockCommentDepth;// +0x0104
    vec_s0084_7200<void*> mBlockCommandStack;   // +0x0108
    vec_s0084_7200<cMetaEntry> mMetaCommandStack; // +0x011c
    string8_s0084_7200  mScope;            // +0x0130
    vec_s0084_7200<int> mScopeOffsets;     // +0x0140
    string8_s0084_7200  mLastErrorString;  // +0x0154
    unsigned char mErrorStringHasFileQualification;  // +0x0164
    int      mTotalLinesParsed; // +0x0168
    cArguments_s0084_7200 mArgs;           // +0x016c
    string8_s0084_7200  mLCName;           // +0x01b0

    cParser_s0084_7200();
    ~cParser_s0084_7200();

    bool Shutdown();            // 0x00846db0
};
}
}
// ---- items of slice s00847200 end

// @ 0x00841130
float __fastcall ParserCall1ToFloat(int* self, int, int a, int b)
{
    int r = ((int(__thiscall*)(int*, int, int))(*(void***)self)[1])(self, a, b);
    return (float)r;
}

// @ 0x00841150
int __fastcall ParserArg1c(int* self, int, const char** p, void* expr)
{
    ((cExprAccess*)expr)->EvalBoolParentheses(p, '(');
    ((cExprAccess*)expr)->EvalBoolParentheses(p, ')');
    return *(int*)(self[2] + 0x1c);
}

// @ 0x00841190
int __fastcall ParserArg20(int* self, int, const char** p, void* expr)
{
    ((cExprAccess*)expr)->EvalBoolParentheses(p, '(');
    ((cExprAccess*)expr)->EvalBoolParentheses(p, ')');
    return *(int*)(self[2] + 0x20);
}

// @ 0x008411c0
int __fastcall cParser_Release(int* self)
{
    int* rc = self + 2;
    *rc = *rc - 1;
    int r = *rc;
    if (r == 0) {
        ((void(__thiscall*)(int*, int))(*(void***)self)[0xcc / 4])(self, 1);
        r = 0;
    }
    return r;
}

// @ 0x00841220
bool __fastcall ParserEvent38(int* self, int, void* arg)
{
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x38 / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}

// @ 0x00841290
bool __fastcall ParserEvent3c(int* self, int, void* arg)
{
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x3c / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}

// @ 0x00841300
bool __fastcall ParserEvent40(int* self, int, void* arg)
{
    try {
        ((void(__thiscall*)(int*, void*))(*(void***)self)[0x40 / 4])(self, arg);
    } catch (...) {
        return false;
    }
    return true;
}

// @ 0x00841370
bool __fastcall cParser_InstantiateMacroNoThrow(int* self, int, const char* pName, cArguments* pArgs)
{
    try {
        ((void(__thiscall*)(int*, const char*, cArguments*))(*(void***)self)[0x44 / 4])(self, pName, pArgs);
    } catch (...) {
        return false;
    }
    return true;
}

// @ 0x00841410
void cCommandStateMeta_s0084_1370::OnRegister(void* pParser, cState_s0084_1370* pState)
{
    mState = pState ? (cParser_s0084_1370*)((char*)pState - 4) : 0;
    EA::ArgScript::cMetaCommandBase_s0084_1370::OnRegister(pParser, pState);
}

// @ 0x00841440
void cCommandStateBlock_s0084_1370::OnRegister(void* pParser, cState_s0084_1370* pState)
{
    mState = pState ? (cParser_s0084_1370*)((char*)pState - 4) : 0;
    EA::ArgScript::cCommandBase_s0084_1370::OnRegister(pParser, pState);
}

// @ 0x00841490
void cParser_s0084_1370::SetFlag(tFlag flag, bool value)
{
    if ((unsigned)flag >= (unsigned)kMaxFlags) return;
    if (value) mFlags |= 1u << (flag & 0x1f);
    else mFlags &= ~(1u << (flag & 0x1f));
}

// @ 0x008414d0
const char* cParser_s0084_1370::LineLocationInfo()
{
    Sprintf(&mLineLocation, "%s:%d", mCurrentPath.mpBegin, mCurrentLine);
    return mLineLocation.mpBegin;
}

// @ 0x00841540
float* cParser_s0084_1370::ParseVector2(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ','))
        pOut[1] = pExpr->EvalRealExpression(pText);
    else
        pOut[1] = pOut[0];
    return pOut;
}

// @ 0x00841590
float* cParser_s0084_1370::ParseVector3(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ',')) {
        pOut[1] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[2] = pExpr->EvalRealExpression(pText);
    } else {
        pOut[1] = pOut[0];
        pOut[2] = pOut[0];
    }
    return pOut;
}

// @ 0x00841610
float* cParser_s0084_1370::ParseRGBA(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ',')) {
        pOut[1] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[2] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[3] = pExpr->EvalRealExpression(pText);
    } else {
        pOut[1] = pOut[0];
        pOut[2] = pOut[0];
        pOut[3] = pOut[0];
    }
    return pOut;
}

// @ 0x008416b0
float* cParser_s0084_1370::ParseRGB(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    pExpr->EvalExpectCharThrow(pText, ',');
    pOut[1] = pExpr->EvalRealExpression(pText);
    pExpr->EvalExpectCharThrow(pText, ',');
    pOut[2] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ','))
        pOut[3] = pExpr->EvalRealExpression(pText);
    else
        pOut[3] = 1.0f;
    return pOut;
}

// @ 0x008417c0
namespace eastl {
int string8_s0084_1370::compare(unsigned pos, unsigned n, const char* p) const
{
    const int n1 = (int)(mpEnd - mpBegin) - (int)pos;
    const int n2 = (int)CharStrlen_s0084_1370(p);
    const int nMin = (int)min_alt((unsigned)n1, n);
    const int r = CompareBytes(mpBegin + pos, p, (unsigned)min_alt(n2, nMin));
    return (r != 0) ? r : (nMin < n2 ? -1 : (nMin > n2 ? 1 : 0));
}
}  // namespace eastl

// @ 0x008418b0
void cEvalCommand_s0084_1370::Execute(cArguments* pArgs)
{
    mParser->ParseCommand(*pArgs->MainArguments(1));
}

// @ 0x00841900
cSetECommand_s0084_1370::cSetECommand_s0084_1370()
{
}

// @ 0x008419d0
void cNamespaceCommand_s0084_1370::Execute(cArguments* pArgs)
{
    mParser->StartBlock((EA::ArgScript::cIBlockCommand_s0084_1370*)this);
    mParser->PushNamespace(*pArgs->MainArguments(1));
}

// @ 0x00841a10
void cNamespaceCommand_s0084_1370::OnEndBlock(bool bEnd)
{
    mParser->PopNamespace();
}

// @ 0x00841a50
void cCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    cArguments args(pMain[1]);
    mState->InstantiateMacro(pMain[0], &args);
}

// @ 0x00841ae0
void cSCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    cArguments args(pMain[1]);
    mState->InstantiateMacroNoThrow(pMain[0], &args);
}

// @ 0x00841b70
void cShowArgumentsCommand_s0084_1370::Execute(cArguments* pArgs)
{
    Output(mOut, "Arguments:\n");
    for (int i = 0; i < pArgs->NumArguments(); ++i)
        Output(mOut, "%d: %s\n", i, (*pArgs)[i]);
}

// @ 0x00841bf0
void cTraceCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* pArg = *pArgs->MainArguments(1);
    Output(mOut, "%s\n", pArg);
}

// @ 0x00841c90
void cParser_s0084_1370::PopNamespace()
{
    mScope.erase(mScopeOffsets.mpEnd[-1]);
    mScopeOffsets.mpEnd -= 1;
}

// @ 0x00841d00
namespace eastl {
int string8_s0084_1370::find(const char* p, unsigned pos) const
{
    const unsigned plen = CharStrlen_s0084_1370(p);
    char* const pBegin = mpBegin;
    char* const pEnd = mpEnd;
    if ((unsigned)(pEnd - pBegin) < plen + pos) return -1;
    const char* pFound = slab_search(pBegin + pos, pEnd, p, p + plen);
    if (pFound != pEnd || plen == 0) return (int)(pFound - pBegin);
    return -1;
}
}  // namespace eastl

// @ 0x00841d60
StringPair_s0084_1370::StringPair_s0084_1370(const string8& a, const string8& b)
: first(a), second(b)
{
}

// @ 0x00841f00
StringPair_s0084_1370::StringPair_s0084_1370(const StringPair_s0084_1370& x)
: first(x.first), second(x.second)
{
}

// @ 0x00841fd0
cMacroDefinition_s0084_1370::~cMacroDefinition_s0084_1370()
{
}

// @ 0x00842080
void cHelpCommand_s0084_1370::Execute(cArguments* pArgs)
{
    int numMain;
    const char* const* pMain = pArgs->MainArguments(&numMain, 0, 1);
    const char* pPattern = "*";
    if (numMain > 0) pPattern = pMain[0];

    EA::ArgScript::CommandNode_s0084_1370** pBucket = mState->mCommands.mpBucketArray;
    EA::ArgScript::CommandNode_s0084_1370* pNode = *pBucket;
    int numMatches = 0;
    if (!pNode) {
        ++pBucket;
        while (!*pBucket) ++pBucket;
        pNode = *pBucket;
    }
    if (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]) {
        do {
            if (Text_WildcardMatch(pNode->key.mpBegin, pPattern, false)) ++numMatches;
            pNode = pNode->mpNext;
            if (!pNode) {
                do {
                    ++pBucket;
                    pNode = *pBucket;
                } while (!pNode);
            }
        } while (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]);

        if (numMatches > 0) {
            int helpType = 0;
            if (numMatches == 1) helpType = 1;
            if (pArgs->HasFlag("full")) helpType = 1;
            if (pArgs->HasFlag("html")) helpType = 2;

            pBucket = mState->mCommands.mpBucketArray;
            pNode = *pBucket;
            if (!pNode) {
                ++pBucket;
                while (!*pBucket) ++pBucket;
                pNode = *pBucket;
            }
            if (pNode == mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]) return;
            do {
                if (Text_WildcardMatch(pNode->key.mpBegin, pPattern, false)) {
                    EA::ArgScript::cICommand_s0084_1370* pCommand =
                        (EA::ArgScript::cICommand_s0084_1370*)pNode->mpCommand;
                    const char* pDescription = pCommand->Description(helpType);
                    if (!pDescription) pDescription = "no description";
                    Output(mOut, "%-20s: %s\n", pNode->key.mpBegin, pDescription);
                }
                pNode = pNode->mpNext;
                if (!pNode) {
                    do {
                        ++pBucket;
                        pNode = *pBucket;
                    } while (!pNode);
                }
            } while (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]);
            return;
        }
    }
    Output(mOut, "No matches! You may want to include wildcards. (*, ?, etc.)\n");
}

// @ 0x00842230
void cArrayCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    int numArrays = mParser->ParseInt(pMain[1]);
    for (int i = 0; i < numArrays; ++i) {
        string8 name;
        Sprintf(&name, "%s %s(%d %d)", "create", pMain[0], i, numArrays);
        mParser->ParseCommand(name.mpBegin);
    }
}

// @ 0x00842310
int cVariableExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->Variable(name.mpBegin) != 0;
}

// @ 0x008423c0
int cDefinitionExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->DefinitionExists(name.mpBegin) != 0;
}

// @ 0x00842470
int cCommandExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->CommandExists(name.mpBegin) != 0;
}

// @ 0x00842520
int cEqFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 a;
    string8 b;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &a);
    pExpr->EvalExpectCharThrow(*p, ',');
    pExpr->EvalString(*p, &b);
    pExpr->EvalExpectCharThrow(*p, ')');
    return String8Equals(&a, &b) != 0;
}

// @ 0x00842620
int cMatchFunction_s0084_2620::EvalInt(const char** p, cExpression_s0084_2620* pExpr)
{
    string8_s0084_2620 a;
    string8_s0084_2620 b;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &a);
    pExpr->EvalExpectCharThrow(*p, ',');
    pExpr->EvalString(*p, &b);
    pExpr->EvalExpectCharThrow(*p, ')');
    bool bMatch = Text_WildcardMatch(a.mpBegin, b.mpBegin, false);
    return bMatch != false;
}

// @ 0x00842720
StringStringPair_s0084_2620::~StringStringPair_s0084_2620()
{
}

// @ 0x00842760
string8_s0084_2620& string8_s0084_2620::insert(unsigned pos, const string8_s0084_2620& s)
{
    Insert(mpBegin + pos, s.mpBegin, s.mpEnd);
    return *this;
}

// @ 0x008428b0
void FindParentDir(const char* pPath, string8_s0084_2620* pOut)
{
    pOut->assign(pPath, pPath + strlen(pPath));
    int pos = pOut->find_last_of("/\\", 0xffffffffu);
    if (pos != -1)
        pOut->erase((unsigned)(pos + 1), 0xffffffffu);
    else
        pOut->assign(g_141b840, g_141b842);
}

// @ 0x00842910
void cEndCommand_s0084_2620::Execute(cArguments_s0084_2620* pArgs)
{    pArgs->MainArguments(0);
    eastl::vec_s0084_2620<void*>& stack = mState->mBlockCommandStack;
    if (stack.mpBegin == stack.mpEnd) {
        char buf[16];
        SP_cError(buf, "Not inside a block");
        ThrowException(buf, &gThrowInfo);
    }
    _ReadWriteBarrier();
    cParser_s0084_2620* state = mState;
    cIBlockCommand_s0084_2620* pBlock = (cIBlockCommand_s0084_2620*)state->mBlockCommandStack.mpEnd[-1];
    _ReadWriteBarrier();
    --state->mBlockCommandStack.mpEnd;
    return pBlock->OnEndBlock(false);}

// @ 0x00842980
void cPurgeCommand_s0084_2620::Execute(cArguments_s0084_2620* pArgs)
{
    cParser_s0084_2620* pParser = (cParser_s0084_2620*)mParser;
    const char* pName = *pArgs->MainArguments(1);
    const char* p = pName;
    unsigned len = CharStrlen_s0084_2620(p);
    if (len > 1 && pName[len - 1] == ':') {
        pParser->PurgeNamespace(pName);
    } else {
        char buf[16];
        SP_cError(buf, "Bad scope '%s' specified", pName);
        ThrowException(buf, &gThrowInfo);
    }
}

// @ 0x00842a00
void cVersionCommand_s0084_2620::Execute(cArguments_s0084_2620* pArgs)
{
    const char* const* ppVer = pArgs->MainArguments(1);
    int version = ((cParser_s0084_2620*)mParser)->ParseInt(*ppVer);
    mState->mCurrentVersion = version;
    if (version < mState->mMinVersion) {
        char buf[16];
        SP_cError(buf,
                  "Script version no longer supported: have %d, need at least %d",
                  version, mState->mMinVersion);
        ThrowException(buf, &gThrowInfo);
    }
    if (version > mState->mMaxVersion) {
        char buf[16];
        SP_cError(buf,
                  "Script version more recent than code: have %d, can only handle up to %d",
                  version, mState->mMaxVersion);
        ThrowException(buf, &gThrowInfo);
    }
}

// @ 0x00842a90
void cMatchFunction_s0084_2620::EvalReal()
{
    char buf[16];
    SP_cError(buf, "boolean function");
    ThrowException(buf, &gThrowInfo);
}

// @ 0x00842ac0
If_s0084_2620::If_s0084_2620()
{
}

// @ 0x00842b50
void If_s0084_2620::OnEndParse(bool bEnd)
{
    if (mVec1.mpBegin != mVec1.mpEnd) {
        char* volatile& firstEnd = mVec1.mpEnd;
        firstEnd -= 1;
        mVec2.mpEnd -= 1;
    }
}

// @ 0x00842c10
void* cParser_s0084_2620::Command(const char* pName) const
{
    ::MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    const CmdTable_s0084_2620& cmds = mCommands;
    FindResult_s0084_2620 r = cmds.find(mCaseInsensitive);
    if (r.mpNode != cmds.mpBucketArray[cmds.mnBucketCount])
        return ((CmdNode_s0084_2620*)r.mpNode)->mpValue;
    return 0;
}

// @ 0x00842c60
void EA::ArgScript::cParser_s0084_2620::ParseFile(const char* pPath)
{
    void* f = fopen(pPath, "r");
    if (!f) {
        Sprintf(&mLastErrorString, "File not found: '%s'", pPath);
        char buf[16];
        SP_cError(buf, mLastErrorString.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    string8_s0084_2620 savedBaseDir(mIncludeBaseDir);
    FindParentDir(pPath, &mIncludeBaseDir);
    const int blockCount = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin);
    const int metaCount  = (int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin);
    int line = 1;
    for (;;) {
        if (feof(f))
            break;
        char buf[0x800];
        buf[0] = 0;
        fgets(buf, 0x800, f);
        try {
            mCurrentPath.assign(pPath, pPath + CharStrlen_s0084_2620(pPath));
            mCurrentLine = line;
            ParseCommand(buf);
        } catch (...) {
            if (!mErrorFlag) {
                string8_s0084_2620 msg;
                Sprintf(&msg, "%s(%d): error: ", pPath, line);
                mLastErrorString.insert(0, msg);
            }
            if (!(mFlags & 1)) {
                mErrorFlag = 1;
                fclose(f);
                char buf2[16];
                SP_cError(buf2, mLastErrorString.mpBegin);
                ThrowException(buf2, &gThrowInfo);
            }
            if (mLogTarget) {
                LogAppend(LogAppend(LogAppend(mLogTarget, g_1401b70),
                                    mLastErrorString.mpBegin), g_1401b70);
            }
        }
        line++;
    }
    fclose(f);
    if ((int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) != blockCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced block command in '%s': too many or two few 'end's.\n", pPath);
        ThrowException(buf, &gThrowInfo);
    }
    if ((int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin) != metaCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced meta command in '%s': look for missing close tag "
                       "(e.g. endif/enddef)\n", pPath);
        ThrowException(buf, &gThrowInfo);
    }
    mIncludeBaseDir = savedBaseDir;
}

// @ 0x00842f50
void EA::ArgScript::cParser_s0084_2620::ParseStream(void* pStream)
{
    IOStream_s0084_2620* p = (IOStream_s0084_2620*)pStream;
    if (!p || !p->IsValid()) {
        mLastErrorString.assign("Bad input stream", "Bad input stream" + 16);
        char buf[16];
        SP_cError(buf, mLastErrorString.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    string8_s0084_2620 stream;
    {
        // The original inlines this six-byte literal (EAAllocate + two movs, no CopyBytes),
        // so spell the construction out to keep the call trace identical.
        char* pStream = (char*)EAAllocate(7, "ArgScript", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\"
            "Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        stream.mpBegin = pStream;
        stream.mpCapacity = pStream + 7;
        pStream[0] = 's'; pStream[1] = 't'; pStream[2] = 'r';
        pStream[3] = 'e'; pStream[4] = 'a'; pStream[5] = 'm';
        pStream[6] = 0;
        stream.mpEnd = pStream + 6;
    }
    const int blockCount = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin);
    const int metaCount  = (int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin);
    int line = 1;
    for (;;) {
        if (p->IsEOF())
            break;
        if (!p->HasData())
            break;
        char buf[0x800];
        buf[0] = 0;
        ReadLine(p, buf, 0x800);
        try {
            mCurrentPath.assign(stream.mpBegin, stream.mpEnd);
            mCurrentLine = line;
            ParseCommand(buf);
        } catch (...) {
            if (!mErrorFlag) {
                string8_s0084_2620 msg;
                Sprintf(&msg, "%s(%d): error: ", stream.mpBegin, line);
                mLastErrorString.insert(0, msg);
            }
            if (!(mFlags & 1)) {
                mErrorFlag = 1;
                char buf2[16];
                SP_cError(buf2, mLastErrorString.mpBegin);
                ThrowException(buf2, &gThrowInfo);
            }
            if (mLogTarget) {
                LogAppend(LogAppend(LogAppend(mLogTarget, g_1401b70),
                                    mLastErrorString.mpBegin), g_1401b70);
            }
        }
        line++;
    }
    if ((int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) != blockCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced block command in '%s': too many or two few 'end's.\n",
                  stream.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    if ((int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin) != metaCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced meta command in '%s': look for missing close tag "
                       "(e.g. endif/enddef)\n", stream.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
}

// @ 0x00843240
void cParser_s0084_2620::GetLineLocationInfo(string8_s0084_2620* pInfo, int* pLine) const
{
    if (pInfo) {
        const string8_s0084_2620* src = &mCurrentPath;
        if (src != pInfo)
            pInfo->assign(src->mpBegin, src->mpEnd);
    }
    if (pLine)
        *pLine = mCurrentLine;
}

// @ 0x00843280
bool cParser_s0084_2620::DefinitionExists(const char* pName) const
{
    ::MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    const CmdTable_s0084_2620& t = mCommands;
    CmdNode_s0084_2620* pEnd = t.mpBucketArray[t.mnBucketCount];
    return t.find(mCaseInsensitive).mpNode != pEnd;
}

// @ 0x008432d0
bool cParser_s0084_2620::HasName6c(const char* pName) const
{
    ::MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    const CmdTable_s0084_2620& t = mTable6c;
    CmdNode_s0084_2620* pEnd = t.mpBucketArray[t.mnBucketCount];
    return t.find(mCaseInsensitive).mpNode != pEnd;
}

// @ 0x00843320
const char* EA::ArgScript::cParser_s0084_2620::LookupName(const char* pName) const
{
    const char* pResult = 0;
    bool bFound = false;

    if (*pName == ':') {
        string8_s0084_2620 name;
        eastl::MakeRangeString(&name, pName + 1, pName + 1 + CharStrlen_s0084_2620(pName + 1));
        FindResult_s0084_2620 r = mTable8c.find(&name);
        if (r.mpNode != mTable8c.mpBucketArray[mTable8c.mnBucketCount]) {
            pResult = *(const char**)((char*)r.mpNode + 0x10);
            bFound = true;
        }
    } else {
        const unsigned len = CharStrlen_s0084_2620(pName);
        string8_s0084_2620 name(mScope);
        name.append(pName, pName + len);
        FindResult_s0084_2620 r = mTable8c.find(&name);
        int i = (int)(mScopeOffsets.mpEnd - mScopeOffsets.mpBegin) - 1;
        while (r.mpNode == mTable8c.mpBucketArray[mTable8c.mnBucketCount] && i >= 0) {
            unsigned off = (unsigned)mScopeOffsets.mpBegin[i];
            unsigned sz  = (unsigned)(mScope.mpEnd - mScope.mpBegin);
            unsigned n   = eastl_min(off, sz);
            name.assign(mScope.mpBegin, mScope.mpBegin + n);
            name.append(pName, pName + len);
            r = mTable8c.find(&name);
            i--;
        }
        if (r.mpNode != mTable8c.mpBucketArray[mTable8c.mnBucketCount]) {
            pResult = *(const char**)((char*)r.mpNode + 0x10);
            bFound = true;
        }
    }

    if (!bFound) {
        string8_s0084_2620 bare;
        eastl::MakeRangeString(&bare, pName, pName + CharStrlen_s0084_2620(pName));
        FindResult_s0084_2620 r = mTableAc.find(&bare);
        if (r.mpNode != mTableAc.mpBucketArray[mTableAc.mnBucketCount]) {
            return *(const char**)((char*)r.mpNode + 0x10);
        }
    } else {
        return pResult;
    }

    if (mIncludeHandler) {
        void* pv = mIncludeHandler->Resolve(pName);
        if (pv)
            return (const char*)pv;
    }
    return 0;
}

// @ 0x00843650
void EA::ArgScript::cParser_s0084_3650::SubstituteVariables(string8_s0084_3650* pLine, int bFlag)
{
    char* pText = pLine->mpBegin;
    unsigned total = (unsigned)(pLine->mpEnd - pText);
    if (total == 0)
        return;

    char* pDollar = pText;
    char* const pEnd = pText + total;
    while (pDollar != pEnd && *pDollar != '$')
        ++pDollar;
    unsigned start = (unsigned)(pDollar - pText);
    if (start == total)
        return;

    if (total > 0x7ff) {
        cError_s0084_3650 err("buffer overflow");
        ThrowException(&err, &gThrowInfo);
    }

    char buf[2048];
    CopyBytes(buf, pText, total + 1);
    pLine->clearContents();

    unsigned idx = 0;
    while (idx < total) {
        pLine->append(buf + idx, buf + idx + (start - idx));
        if (start == total)
            return;

        unsigned j = start + 1;
        bool bBrace = buf[j] == '{';
        if (bBrace)
            ++j;
        if (j >= total) {
            cError_s0084_3650 err("missing variable name");
            ThrowException(&err, &gThrowInfo);
        }
        char ch = buf[j];
        if (!(isalpha((int)ch) || isdigit((int)ch) || ch == '_' || ch == ':') ||
            isdigit((int)buf[j])) {
            cError_s0084_3650 err("bad variable name");
            ThrowException(&err, &gThrowInfo);
        }
        unsigned k = j + 1;
        while (k < total) {
            char d = buf[k];
            if (!(isalpha((int)d) || isdigit((int)d) || d == '_' || d == ':'))
                break;
            ++k;
        }
        if (bBrace && (k >= total || buf[k] != '}')) {
            cError_s0084_3650 err("missing '}'");
            ThrowException(&err, &gThrowInfo);
        }

        char saved = buf[k];
        buf[k] = 0;
        const char* pValue = ((cIParserExpr_s0084_3650*)this)->LookupVariable(buf + j);
        if (pValue == 0) {
            cError_s0084_3650 err("Unknown variable: '%s'", buf + j);
            ThrowException(&err, &gThrowInfo);
        }
        buf[k] = saved;

        if (!bBrace && bFlag != 0)
            pLine->append(gEmptyB, gEmptyB + 1);
        pLine->append(pValue, pValue + CharStrlen_s0084_3650(pValue));
        if (bBrace)
            k = k + 1;
        else if (bFlag != 0)
            pLine->append(gEmptyA, gEmptyA + 1);

        char* pNext = buf + k;
        while (pNext != buf + total && *pNext != '$')
            ++pNext;
        start = (unsigned)(pNext - buf);
        if (k >= total)
            return;
        idx = k;
    }
}

// @ 0x00843920
EA::ArgScript::cICommand_s0084_3650* EA::ArgScript::cParser_s0084_3650::CommandLookup(const char* pName)
{
    char* pLCName = mLCNameStorage;
    ::MakeCaseInsensitiveChars(pName, pLCName);
    int i = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) - 1;
    for (; i >= 0; --i) {
        cICommand_s0084_3650* pCmd = (cICommand_s0084_3650*)mBlockCommandStack.mpBegin[i];
        if (pCmd->MatchName(pLCName))
            return pCmd;
    }
    EA::ArgScript::CmdTable_s0084_3650* pTable = CmdTableOf(this);
    eastl::FindResult_s0084_3650 r = pTable->find((string8_s0084_3650*)pLCName);
    if ((void*)r.mpNode != (void*)pTable->mpBucketArray[pTable->mnBucketCount])
        return (cICommand_s0084_3650*)((EA::ArgScript::CmdNode_s0084_3650*)r.mpNode)->mpValue;
    return 0;
}

// @ 0x008439b0
eastl::InsertResult_s0084_3650 eastl::HashTable_s0084_3650::insert(const string8_s0084_3650* pKey, eastl::RehashLocal_s0084_3650* pRehash)
{
    unsigned hash = 0x811c9dc5;
    const unsigned char* p = (const unsigned char*)pKey->mpBegin;
    for (unsigned char c = *p; c != 0; c = *++p)
        hash = (hash * 0x1000193) ^ c;

    unsigned bucket = hash % mnBucketCount;
    HashNode_s0084_3650** ppBucket = mpBucketArray + bucket;
    HashNode_s0084_3650* pNode = *ppBucket;
    for (; pNode != 0; pNode = pNode->mpNext) {
        if (operator==(*pKey, pNode->key))
            return InsertResult_s0084_3650();
    }

    pRehash->mbGrown = false;
    unsigned nNewCount = 0;
    GrowMacroTable((char*)this + 0x10, 0, pRehash, mnBucketCount, mnNodeCount, 1);
    nNewCount = pRehash->mnNewCount;
    HashNode_s0084_3650* pNew = (HashNode_s0084_3650*)ConstructMacroNode(this, 0, pKey);
    if (pRehash->mbGrown)
        FreeMacroBuckets(this, 0, pRehash->mnNewCount);

    InsertResult_s0084_3650 result;
    result.mpNode = pNew;
    result.mppBucket = 0;
    (void)nNewCount;
    pNew->mpNext = mpBucketArray[bucket];
    mpBucketArray[bucket] = pNew;
    ++mnNodeCount;
    result.mppBucket = mpBucketArray + bucket;
    result.mbInserted = true;
    return result;
}

// @ 0x00843ab0
void** eastl::VecPtr_s0084_3650::DoInsertValue(void** pos, void** const* pValue)
{
    void** pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        void** pSource = *pValue;
        if (*pValue >= pEnd && *pValue < mpCapacity)
            pSource = *pValue + 1;
        if (pEnd != 0)
            *pEnd = pEnd[-1];
        void** pDst = pEnd - 1;
        pDst = pDst - pDst + pos;
        unsigned n = (unsigned)((char*)(pEnd - 1) - (char*)pos);
        ::memmove(pDst, pos, n);
        *pos = *pSource;
        ++mpEnd;
        return pos;
    }

    unsigned nPrev = (unsigned)(pEnd - mpBegin);
    unsigned nNew;
    if (nPrev != 0) {
        nNew = nPrev * 2;
    } else {
        nNew = 1;
    }
    void** pNew = nNew != 0
        ? (void**)EAAllocate(nNew * 4, "ArgScript", 0, 0, kAllocFile, 0xd1)
        : 0;
    void** pMid = pNew;
    if (pNew) {
        CopyBytes(pNew, mpBegin, (unsigned)((char*)*pValue - (char*)mpBegin));
        pMid = pNew + (*pValue - mpBegin);
        *pMid = *pValue;
    }
    void** pNewEnd = (void**)CopyBytes(pMid + 1, *pValue, (unsigned)((char*)mpEnd - (char*)*pValue));
    pNewEnd += (mpEnd - *pValue);
    if (mpBegin != 0 && mpBegin[-1] != 0)
        ::operator delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacity = pNew + nNew;
    return pNew;
}

// @ 0x00843bc0
void eastl::bool_vec_s0084_3650::DoInsertValue(bool* pPosition, const bool* pValue)
{
    bool* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const bool* pSource = pValue;
        if (pValue >= pPosition && pValue < pEnd)
            ++pSource;
        if (pEnd != 0)
            *pEnd = pEnd[-1];
        bool* pLast = mpEnd - 1;
        ::memmove(pPosition + (mpEnd - pLast), pPosition, (unsigned)(pLast - pPosition));
        *pPosition = *pSource;
        ++mpEnd;
        return;
    }

    unsigned nPrev = (unsigned)(pEnd - mpBegin);
    unsigned nNew = nPrev != 0 ? nPrev * 2 : 1;
    bool* pNew = nNew != 0
        ? (bool*)EAAllocate(nNew, "ArgScript", 0, 0, kAllocFile, 0xd1)
        : 0;
    unsigned nHead = (unsigned)(pPosition - mpBegin);
    bool* pMid = (bool*)CopyBytes(pNew, mpBegin, nHead);
    pMid += nHead;
    if (pMid != 0)
        *pMid = *pValue;
    unsigned nTail = (unsigned)(mpEnd - pPosition);
    bool* pNewEnd = (bool*)CopyBytes(pMid + 1, pPosition, nTail);
    pNewEnd += nTail;
    if (mpBegin != 0 && mpBegin != mpBuffer)
        ::operator delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacity = pNew + nNew;
}

// @ 0x00843cc0
void EA::ArgScript::cIncludeCommand_s0084_3650::ExecuteBody(cArguments_s0084_3650* pArgs)
{
    const char* const* pName = pArgs->MainArguments(1);
    string8_s0084_3650 fileName(*pName);

    bool bRelative;
    if (fileName.size() >= 2 && fileName.mpBegin[1] == ':' && isalpha(fileName.mpBegin[0]))
        bRelative = false;
    else
        bRelative = fileName.find("\\", 0) != 0;

    if (bRelative)
        fileName.assign(mState->mCurrentDir.mpBegin, mState->mCurrentDir.mpEnd);

    fileName.append(*pName, *pName + CharStrlen_s0084_3650(*pName));
    ((cIParser_s0084_3650*)mParser)->RunFile(fileName.mpBegin);
}

// @ 0x00843e50
void EA::ArgScript::cIncludeIfExistsCommand_s0084_3650::ExecuteBody(cArguments_s0084_3650* pArgs)
{
    const char* const* pName = pArgs->MainArguments(1);
    string8_s0084_3650 fileName(*pName);

    bool bRelative;
    if (fileName.size() >= 2 && fileName.mpBegin[1] == ':' && isalpha(fileName.mpBegin[0]))
        bRelative = false;
    else
        bRelative = fileName.find("\\", 0) != 0;

    if (bRelative)
        fileName.assign(mState->mCurrentDir.mpBegin, mState->mCurrentDir.mpEnd);

    fileName.append(*pName, *pName + CharStrlen_s0084_3650(*pName));
    char statBuf[0x30];
    if (_stat64i32(fileName.mpBegin, statBuf) == 0)
        ((cIParser_s0084_3650*)mParser)->RunFile(fileName.mpBegin);
}

// @ 0x00843ff0
bool EA::ArgScript::cIfCommand_s0084_3650::ParseBody(const string8_s0084_3650& line)
{
    if (line.compare(0, 2, "if") == 0)
        return false;

    if (eastl::operator==(line, "else")) {
        if (mCondVector.mpEnd[-1] == 0) {
            mTakenVector.mpEnd[-1] = 1;
            mCondVector.mpEnd[-1] = 1;
            return true;
        }
        mTakenVector.mpEnd[-1] = 0;
        return true;
    }

    if (line.compare(0, 6, "elseif") == 0) {
        if (mTakenVector.mpEnd[-1] != 0) {
            mTakenVector.mpEnd[-1] = 0;
            return true;
        }
        mFullParser->SubstituteVariables((string8_s0084_3650*)&line, 1);
        mArgs.SplitIntoArguments(line.mpBegin);
        mArgs.Advance();
        char bResult = (char)((cIParser2_s0084_3650*)mParser)->EvalCondition(*mArgs.MainArguments(1));
        mTakenVector.mpEnd[-1] = bResult;
        mCondVector.mpEnd[-1] = bResult;
        return true;
    }

    return mTakenVector.mpEnd[-1] == 0;
}

// @ 0x008440d0
void EA::ArgScript::cParser_s0084_3650::ParseCommand(const char* pText)
{
    ++mNesting;
    string8_s0084_3650 line;
    try {
        if (StripCommentsAndWhiteSpace((char*)pText, &line, &mBlockCommentDepth)) {
            if (mMetaCommandStack.mpBegin != mMetaCommandStack.mpEnd) {
                EA::ArgScript::cMetaEntry_s0084_3650* pEntry = mMetaCommandStack.mpEnd - 1;
                if (line.compare(0, pEntry->mpEndToken->size(), pEntry->mpEndToken->mpBegin) == 0) {
                    pEntry->mCommand->EndMeta(false);
                    mMetaCommandStack.mpEnd -= 1;
                } else if (!pEntry->mCommand->Parse(line)) {
                    goto parse;
                }
            } else {
            parse:
                SubstituteVariables(&line, 1);
                mArgs.SplitIntoArguments(line.mpBegin);
                if (mArgs.NumArguments() != 0) {
                    cICommand_s0084_3650* pCmd = CommandLookup(mArgs[0]);
                    if (pCmd == 0) {
                        cError_s0084_3650 err("Unknown command");
                        ThrowException(&err, &gThrowInfo);
                    }
                    mArgs.Advance();
                    pCmd->Execute(&mArgs);
                    mArgs.FindUnprocessed();
                }
            }
        }
    } catch (cError_s0084_3650& err) {
        Sprintf(&mLastError, "%s: %s", err.mMessage, line.mpBegin);
        cError_s0084_3650 rethrow(mLastError.mpBegin);
        ThrowException(&rethrow, &gThrowInfo);
    }
}

// @ 0x00844270
void SubstituteParameters(EA::ArgScript::cArguments_s0084_4270* params, EA::ArgScript::cArguments_s0084_4270* values, string8_s0084_4270* text)
{
    unsigned size = text->size();
    if (size == 0) return;
    // find first '&'
    const char* p = text->mpBegin;
    while (p != text->mpEnd && *p != '&') ++p;
    if (p == text->mpEnd) return;
    unsigned amp = p - text->mpBegin;
    if (amp == (unsigned)-1) return;

    string8_s0084_4270 result;
    unsigned start = 0;
    do {
        unsigned total = text->size() - start;
        unsigned len = amp - start;
        const char* b = text->mpBegin;
        result.append(b + start, b + start + (total < len ? total : len));
        if (amp == (unsigned)-1) break;
        ++amp;
        bool brace = text->mpBegin[amp] == '{';
        if (brace) ++amp;
        if (amp >= text->size()) throw EA::ArgScript::cError_s0084_4270("missing parameter name");
        unsigned char c = text->mpBegin[amp];
        if (!(isalpha(c) || isdigit(c) || c == '_') || isdigit((unsigned char)text->mpBegin[amp]))
            throw EA::ArgScript::cError_s0084_4270("bad parameter name");
        start = amp + 1;
        while (start < text->size()) {
            unsigned char d = text->mpBegin[start];
            if (!(isalpha(d) || isdigit(d) || d == '_')) break;
            ++start;
        }
        if (brace && (start >= text->size() || text->mpBegin[start] != '}'))
            throw EA::ArgScript::cError_s0084_4270("missing '}'");
        int i = 0;
        if (params->NumArguments() > 0) {
            unsigned nameLen = start - amp;
            do {
                if (text->compare(amp, nameLen, (*params)[i]) == 0) {
                    if (!brace) result.push_back('(');
                    const char* v = (*values)[i];
                    const char* e = v + CharStrlen(v);
                    result.append(v, e);
                    if (!brace) result.push_back(')');
                    break;
                }
                ++i;
            } while (i < params->NumArguments());
        }
        if (i == params->NumArguments()) {
            string8_s0084_4270 msg;
            msg.append("Unknown parameter: ", "Unknown parameter: " + 19);
            unsigned total = text->size() - amp;
            unsigned len = start - amp;
            msg.append(text->mpBegin + amp, text->mpBegin + amp + (total < len ? total : len));
            throw EA::ArgScript::cError_s0084_4270(msg.mpBegin);
        }
        if (brace) ++start;
        amp = text->find('&', start);
    } while (start < text->size());

    if (&result != text) text->assign(result.mpBegin, result.mpEnd);
}

// @ 0x00844680
void __fastcall MacroPair_dtor(MacroPair* p)
{ p->~MacroPair(); }

// @ 0x00844700
void StrHashtable::DoFreeNodes(StrNode** pNodeArray, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        StrNode* pNode = pNodeArray[i];
        while (pNode) {
            StrNode* pTemp = pNode;
            pNode = pNode->mpNext;
            pTemp->~StrNode();
            operator delete(pTemp);
        }
        pNodeArray[i] = 0;
    }
}

// @ 0x00844780
void cIfCommand::Execute(EA::ArgScript::cArguments_s0084_4270& args)
{
    mParser->ExpectEnd(this, "endif");
    bool value = mParser->EvalCondition(*args.MainArguments(1));
    bool parentActive = mConditions.mpBegin == mConditions.mpEnd || mConditions.mpEnd[-1] != 0;
    mConditions.push_back(value && parentActive);
    mTaken.push_back(value || !parentActive);
}

// @ 0x00844860
EA::ArgScript::cMacroDefinition::cMacroDefinition()
    : mRefCount(0)
{
    mStartLine = -1;
}

// @ 0x00844a00
MacroPair::MacroPair(const string8_s0084_4270& k, const EA::ArgScript::AutoRefCount<EA::ArgScript::cMacroDefinition>& v) : first(k), second(v)
{
}

// @ 0x00844a60
MacroPair::MacroPair(const MacroPair& o) : first(o.first), second(o.second)
{
}

// @ 0x00844ac0
namespace eastl
{
struct false_type_ { false_type_() {} };
struct string_insert {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert(char* p, const char* first, const char* last, const struct false_type_&);
};
void string_insert::insert(char* p, const char* first, const char* last, const false_type_&)
{
    if (first == last) return;
    unsigned n = last - first;
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        unsigned nElementsAfter = mpEnd - p;
        char* pOldEnd = mpEnd;
        if (nElementsAfter > n) {
            char* pMoveSrc = pOldEnd - n;
            memcpy(pOldEnd, pMoveSrc, n);          // uninitialized_copy tail
            mpEnd += n;
            memmove(p + n, p, pMoveSrc - p);
            memmove(p, first, n);
        } else {
            const char* pMid = first + nElementsAfter;
            memcpy(pOldEnd, pMid, last - pMid);
            mpEnd += n - nElementsAfter;
            memcpy(mpEnd, p, nElementsAfter);
            mpEnd += nElementsAfter;
            memmove(p, first, pMid - first);
        }
    } else {
        unsigned nPrevSize = mpEnd - mpBegin;
        unsigned nNewCap = nPrevSize ? nPrevSize * 2 : 1;
        if (nNewCap < nPrevSize + n) nNewCap = nPrevSize + n;
        char* pNew = nNewCap ? (char*)operator new(nNewCap, "ArgScript", 0, 0, kAllocFile, 0xd1) : 0;
        unsigned nBefore = p - mpBegin;
        char* q = pNew;
        memcpy(q, mpBegin, nBefore);
        q += nBefore;
        memcpy(q, first, n);
        q += n;
        unsigned nAfter = mpEnd - p;
        memcpy(q, p, nAfter);
        q += nAfter;
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = q;
        mpCapacity = pNew + nNewCap;
    }
}
}

// @ 0x00844c40
void cDefineCommand::Execute(EA::ArgScript::cArguments_s0084_4270& args)
{
    const char** a = args.MainArguments(2);
    const char* name = a[0];
    const char* nameEnd = name + CharStrlen(name);
    MacroIter it;
    {
        string8_s0084_4270 key(name, nameEnd);
        it = MacroTableOf(mFullParser)->find(key);
    }
    MacroTable* t = MacroTableOf(mFullParser);
    if (it.node != (MacroNode*)t->mpBucketArray[t->mnBucketCount])
        throw EA::ArgScript::cError_s0084_4270("Already defined");
    mParser->ExpectEnd(this, "enddef");
    EA::ArgScript::cMacroDefinition* m = new ("ArgScript", 0, 0, 0, 0) EA::ArgScript::cMacroDefinition;
    EA::ArgScript::cMacroDefinition* old = mpMacro.mpObject;
    if (m != old) {
        if (m) ++m->mRefCount;
        mpMacro.mpObject = m;
        if (old) {
            if (old->mRefCount == 1) { old->~cMacroDefinition(); operator delete(old); }
            else --old->mRefCount;
        }
    }
    const char* s = a[0];
    const char* e = s + CharStrlen(s);
    mpMacro.mpObject->mName.assign(s, e);
    mpMacro.mpObject->mParams.SplitIntoArguments(a[1]);
    string8_s0084_4270* cur = &mFullParser->mCurrentPath;
    if (cur != &mpMacro.mpObject->mPath)
        mpMacro.mpObject->mPath.assign(cur->mpBegin, cur->mpEnd);
    mpMacro.mpObject->mStartLine = mFullParser->mCurrentLine;
}

// @ 0x00844ec0
int cParser::ParseEnd(bool bUnwind)
{
    if (bUnwind) {
        while (mMetaCommandStack.mpBegin != mMetaCommandStack.mpEnd) {
            mMetaCommandStack.mpEnd[-1].mCommand->EndMeta(bUnwind);
            mMetaCommandStack.mpEnd -= 1;
        }
        while (mBlockCommandStack.mpBegin != mBlockCommandStack.mpEnd) {
            mBlockCommandStack.mpEnd[-1]->EndBlock(bUnwind);
            mBlockCommandStack.mpEnd -= 1;
        }
    }
    if (mScope.mpBegin != mScope.mpEnd) {
        *mScope.mpBegin = 0;
        mScope.mpEnd = mScope.mpBegin;
    }
    int* last = mScopeOffsets.mpEnd;
    int* first = mScopeOffsets.mpBegin;
    memcpy(first, last, (char*)mScopeOffsets.mpEnd - (char*)last);
    *(int* volatile*)&mScopeOffsets.mpEnd += -(last - first);
    int r = *(volatile int*)((char*)this + 0x168);   // value left in eax by the original (mArgs storage field)
    mBlockCommentDepth = 0;
    return r;
}

// @ 0x00844fb0
void cParser::InstantiateMacro(const char* name, EA::ArgScript::cArguments_s0084_4270* args)
{
    EA::ArgScript::MakeCaseInsensitive(name, &mLCName);
    const char* nameEnd = name + CharStrlen(name);
    MacroTable* t = MacroTableOf(this);
    MacroIter it;
    {
        string8_s0084_4270 key(name, nameEnd);
        it = t->find(key);
    }
    if (it.node == (MacroNode*)t->mpBucketArray[t->mnBucketCount])
        throw EA::ArgScript::cError_s0084_4270("Unknown definition: '%s'", name);
    EA::ArgScript::cMacroDefinition* m = it.node->value.mpObject;
    if (m->mParams.NumArguments() != args->NumArguments())
        throw EA::ArgScript::cError_s0084_4270("Wrong number of arguments");
    string8_s0084_4270 line;
    EA::ArgScript::cMacroLine* end = m->mMacroBody.mpEnd;
    for (EA::ArgScript::cMacroLine* p = m->mMacroBody.mpBegin; p != end; ++p) {
        int lineNo = p->line;
        int relLine = lineNo - m->mStartLine;
        const char* s = m->mMacroText.mpBegin + p->offset;
        const char* e = s + CharStrlen(s);
        line.assign(s, e);
        SubstituteParameters(&m->mParams, args, &line);
        if (m->mStartLine) {
            if (&m->mPath != &mCurrentPath)
                mCurrentPath.assign(m->mPath.mpBegin, m->mPath.mpEnd);
            mCurrentLine = lineNo;
        }
        try {
            ParseLine(line.mpBegin);
        } catch (EA::ArgScript::cError_s0084_4270& err) {
            if (m->mStartLine)
                throw EA::ArgScript::cError_s0084_4270("\n%s(%d): %s\n      in definition '%s', line %d",
                             m->mPath.mpBegin, lineNo, err.mMessage, name, relLine);
            throw EA::ArgScript::cError_s0084_4270("%s\n  in definition '%s', line %d", err.mMessage, name, relLine);
        }
    }
}

// @ 0x00845260
void cParser::PushScope(const char* name)
{
    int offset = mScope.mpEnd - mScope.mpBegin;
    mScopeOffsets.push_back(offset);
    const char* e = name + CharStrlen(name);
    mScope.append(name, e);
    mScope.append(":", ":" + 1);
}

// @ 0x00845320
void cParser::PushMeta(EA::ArgScript::cICommand_s0084_4270* c, int line)
{
    mMetaCommandStack.push_back(cMetaEntry(c, line));
}

// @ 0x00845370
namespace EA { namespace ArgScript {
string8_s0084_5370& StringMap::operator[](const string8_s0084_5370& key)
{
    StrIter it = find(key);
    if (it != end())
        return it.mpNode->mValue;
    string8_s0084_5370 def;
    PairSS pair(key, def);
    InsertResult res = insert(&pair, 0);
    return res.mpNode->mValue;
}
}}  // namespace EA::ArgScript

// @ 0x00845460
namespace EA { namespace ArgScript {
CmdIter CommandMap::erase(CmdIter pos)
{
    CmdIter next;
    next.mpNode = pos.mpNode->mpNext;
    next.mpBucketPtr = pos.mpBucketPtr;
    while (!next.mpNode) {
        ++next.mpBucketPtr;
        next.mpNode = *next.mpBucketPtr;
    }
    if (*pos.mpBucketPtr == pos.mpNode)
        *pos.mpBucketPtr = pos.mpNode->mpNext;
    else {
        CommandNode* p = *pos.mpBucketPtr;
        while (p->mpNext != pos.mpNode)
            p = p->mpNext;
        p->mpNext = pos.mpNode->mpNext;
    }
    ((PairB*)pos.mpNode)->~PairB();
    FUN_00f47380(pos.mpNode);
    --mnElementCount;
    return next;
}
}}  // namespace EA::ArgScript

// @ 0x008454e0
namespace EA { namespace ArgScript {
int StringMap::erase(const string8_s0084_5370& key)
{
    uint32_t h = 0x811c9dc5;
    const unsigned char* p = (const unsigned char*)key.mpBegin;
    uint32_t c = *p;
    while (c) {
        h *= 0x1000193;
        ++p;
        h ^= c;
        c = *p;
    }
    StringNode** link = mpBucketArray + h % mnBucketCount;
    uint32_t oldCount = mnElementCount;
    if (*link) {
        do {
            StringNode* n = *link;
            if (String8Equal(key, n->mKey))
                break;
            link = &n->mpNext;
        } while (*link);
        while (*link) {
            StringNode* node = *link;
            if (!String8Equal(key, node->mKey))
                break;
            *link = node->mpNext;
            delete node;
            --mnElementCount;
        }
    }
    return (int)(oldCount - mnElementCount);
}
}}  // namespace EA::ArgScript

// @ 0x008455c0
namespace EA { namespace ArgScript {
StrIter StringMap::erase(StrIter pos)
{
    StrIter next;
    next.mpNode = pos.mpNode->mpNext;
    next.mpBucketPtr = pos.mpBucketPtr;
    while (!next.mpNode) {
        ++next.mpBucketPtr;
        next.mpNode = *next.mpBucketPtr;
    }
    if (*pos.mpBucketPtr == pos.mpNode)
        *pos.mpBucketPtr = pos.mpNode->mpNext;
    else {
        StringNode* p = *pos.mpBucketPtr;
        while (p->mpNext != pos.mpNode)
            p = p->mpNext;
        p->mpNext = pos.mpNode->mpNext;
    }
    delete pos.mpNode;
    --mnElementCount;
    return next;
}
}}  // namespace EA::ArgScript

// @ 0x00846000
namespace EA { namespace ArgScript {
void cParser_s0084_5370::RegisterCommand(const char* name, cICommand_s0084_5370* cmd)
{
    MakeCaseInsensitiveChars((char*)name, (int*)&mNameBuf);
    cICommand_s0084_5370*& slot = mCommands[mNameBuf];
    cICommand_s0084_5370* old = slot;
    if (cmd != old) {
        if (cmd)
            cmd->AddRef();
        slot = cmd;
        if (old)
            old->Release();
    }
    cParserIsState* st = mState;
    if (!st)
        st = &mStateDefault;
    cmd->Attach(this, st);
}
}}  // namespace EA::ArgScript

// @ 0x00846070
namespace EA { namespace ArgScript {
bool cParser_s0084_5370::UnregisterCommand(cICommand_s0084_5370* cmd)
{
    CmdIter it = mCommands.begin();
    while (it != mCommands.end()) {
        if (it.mpNode->mpObject == cmd) {
            it = mCommands.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}
}}  // namespace EA::ArgScript

// @ 0x008460f0
namespace EA { namespace ArgScript {
bool cParser_s0084_5370::UnregisterCommand(const char* name)
{
    MakeCaseInsensitiveChars((char*)name, (int*)&mNameBuf);
    CmdIter it = mCommands.find(mNameBuf);
    if (it != mCommands.end()) {
        it = mCommands.erase(it);
        return true;
    }
    return false;
}
}}  // namespace EA::ArgScript

// @ 0x00846160
namespace EA { namespace ArgScript {
void cParser_s0084_5370::SetVariableNoSubstitution(const char* name, const char* value)
{
    string8_s0084_5370 key(mScope.mpBegin, mScope.mpEnd);
    const char* nameEnd = name;
    while (*nameEnd)
        ++nameEnd;
    key.append(name, nameEnd);
    string8_s0084_5370& slot = mVariables[key];
    const char* valueEnd = value;
    while (*valueEnd)
        ++valueEnd;
    slot.assign(value, valueEnd);
}
}}  // namespace EA::ArgScript

// @ 0x00846280
void EA::ArgScript::cParser_s0084_6280::DefineMacro(const char* pName, const char* pBody)
{
    if (pBody == 0) {
        // no body: just insert an empty macro into the map
        eastl::hash_map_s0084_6280* pMap = (eastl::hash_map_s0084_6280*)((char*)this + 0xac);
        (void)pMap;
        return;
    }
    string8_s0084_6280 key(pName);
    string8_s0084_6280 val(pBody);
    (void)key; (void)val;
}

// @ 0x00846420
const char* EA::ArgScript::cParser_s0084_6280::LookupMacroText(const char* pName)
{
    unsigned nName = CharStrlen_s0084_6280(pName);
    eastl::StrHashtable_s0084_6280* pTable = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x8c);
    eastl::StrNode_s0084_6280* pNode =
        pTable->mpBucketArray ? pTable->mpBucketArray[0] : 0;
    eastl::StrNode_s0084_6280** ppBucket = pTable->mpBucketArray;
    if (pNode == 0) {
        while (ppBucket[1] == 0) ppBucket += 1;
        pNode = ppBucket[1];
    }
    while ((void*)pNode != (void*)pTable->mpBucketArray[pTable->mnBucketCount]) {
        if (pNode->key.size() >= nName && memcmp(pNode->key.mpBegin, pName, nName) == 0)
            return (const char*)pNode->mpPayload;
        pNode = pNode->mpNext;
    }
    return 0;
}

// @ 0x00846530
void* eastl::StrHashtable_s0084_6280::FindByHash(unsigned nHash, const string8_s0084_6280* pKey)
{
    StrNode_s0084_6280* pEnd = mpBucketArray[mnBucketCount];
    unsigned nBucket = nHash % (mnBucketCount ? mnBucketCount : 1);
    for (StrNode_s0084_6280* pNode = mpBucketArray[nBucket]; pNode != pEnd; pNode = pNode->mpNext) {
        if (pNode->mHash == nHash && pNode->key.size() == pKey->size()
            && memcmp(pNode->key.mpBegin, pKey->mpBegin, pKey->size()) == 0)
            return pNode->mpPayload;
    }
    return 0;
}

// @ 0x00846630
void eastl::StrHashtable_s0084_6280::DoFreeNodes(MacroHashNode** pBucketArray, unsigned nBucketCount)
{
    for (unsigned i = 0; i < nBucketCount; ++i) {
        MacroHashNode* pNode = pBucketArray[i];
        while (pNode) {
            MacroHashNode* pTemp = pNode;
            pNode = pNode->mpNext;
            MacroPair_dtor(&pTemp->mValue);
            PoolFree(pTemp);
        }
        pBucketArray[i] = 0;
    }
}

// @ 0x00846680
void EA::ArgScript::cSetCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    mFullParser->SetVariableNoSubstitution(pArg[0], pArg[1]);
}

// @ 0x008466b0
void EA::ArgScript::cSetECommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(3);
    mArgs.SplitIntoArguments(pArg[2]);
    int nCount = 0;
    const char** ppNames = mArgs.MainArguments(&nCount, 1, 0x7fffffff);

    int i = 0;
    for (; i < nCount; ++i) {
        const char* pA = ppNames[i];
        const char* pB = pArg[1];
        while (*pA == *pB) {
            if (*pA == 0) break;
            if (pA[1] != pB[1]) { ++pA; ++pB; break; }
            pA += 2; pB += 2;
            if (pA[-1] == 0) break;
        }
        if (*pA != *pB) break;
    }
    if (i == nCount) {
        cError_s0084_6280 err("Unknown enum");
        ThrowException(&err, &gThrowInfo);
    }
    mFullParser->SetVariableNoSubstitution(pArg[0], pArg[1]);
}

extern "C" char g_13fc77c[];   // "true"
extern "C" char g_13fc778[];   // "false"

// @ 0x00846770
void EA::ArgScript::cSetBCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    const char** pArgFast = pArg;
    mFullParser->SetVariableNoSubstitution(pArgFast[0], mParser->EvalCondition(pArg[1]) ? g_13fc77c : g_13fc778);
}

// @ 0x008467c0
void EA::ArgScript::cSetICommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    char buf[12];
    _ltoa(mParser->EvalInt(pArg[1]), buf, 10);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x00846810
void EA::ArgScript::cSetFCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    double f = mParser->EvalFloat(pArg[1]);
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f", f);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x00846870
void EA::ArgScript::cSetCCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[4];
    mParser->EvalColor(v, pArg[1]);
    char buf[0x58];
    Snprintf8(buf, 0x20, "%f,%f,%f,%f", v[0], v[1], v[2], v[3]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x008468f0
void EA::ArgScript::cSetV2Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[2];
    mParser->EvalV2(v, pArg[1]);
    double d0 = v[0];
    double d1 = v[1];
    char buf[0x2c];
    Snprintf8(buf, 0x20, "%f,%f", d0, d1);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x00846960
void EA::ArgScript::cSetV3Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[3];
    mParser->EvalV3(v, pArg[1]);
    char buf[0x44];
    Snprintf8(buf, 0x20, "%f,%f,%f", v[0], v[1], v[2]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x008469d0
void EA::ArgScript::cSetV4Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[4];
    mParser->EvalV4(v, pArg[1]);
    char buf[0x58];
    Snprintf8(buf, 0x20, "%f,%f,%f,%f", v[0], v[1], v[2], v[3]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// @ 0x00846a50
bool EA::ArgScript::cParser_s0084_6280::InsertMacroName(const string8_s0084_6280* pName)
{
    eastl::char_vec_s0084_6280* pNames = (eastl::char_vec_s0084_6280*)((char*)mpMacroState0c + 0xf0);
    unsigned nLength = (unsigned)(pNames->mpEnd - pNames->mpBegin);
    string8_s0084_6280 lower(*pName);
    for (char* p = lower.mpBegin; p != lower.mpEnd; ++p) {
        if (*p >= 'A' && *p <= 'Z') *p = (char)(*p + 0x20);
    }
    eastl::AppendRange(pNames->mpEnd, pNames->mpEnd, lower.mpBegin, lower.mpEnd);   // 0x008448f0
    eastl::CharVecInsert((char*)mpMacroState10 + 0x58, pNames->mpEnd, nLength, lower.mpBegin, lower.mpEnd); // 0x00844ac0
    return true;
}

// @ 0x00846b00
void EA::ArgScript::cParser_s0084_6280::DefineMacroLine(const char* pName, const char* pLine)
{
    string8_s0084_6280 key(pLine);
    SubstituteVariables(&key, 0);
    SetVariableNoSubstitution(pName, key.mpBegin);
}

struct MacroHashIterator { MacroHashNode* mpNode; MacroHashNode** mpBucket; MacroHashIterator(MacroHashNode* n, MacroHashNode** b) : mpNode(n), mpBucket(b) {}
    void increment_bucket() { ++mpBucket; while (*mpBucket == 0) ++mpBucket; mpNode = *mpBucket; }
    void operator++() { mpNode = mpNode->mpNext; while (mpNode == 0) mpNode = *++mpBucket; } };
struct MacroHashtable { unsigned mPad00; MacroHashNode** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount;
    MacroHashIterator erase(MacroHashIterator i); };

// @ 0x00846c00
MacroHashIterator MacroHashtable::erase(MacroHashIterator i)
{
    MacroHashIterator iNext(i.mpNode, i.mpBucket);
    ++iNext;
    MacroHashNode* const pNode = i.mpNode;
    MacroHashNode* pNodeCurrent = *i.mpBucket;
    if (pNodeCurrent == pNode)
        *i.mpBucket = pNodeCurrent->mpNext;
    else {
        MacroHashNode* pNodeNext = pNodeCurrent->mpNext;
        while (pNodeNext != pNode) {
            pNodeCurrent = pNodeNext;
            pNodeNext = pNodeCurrent->mpNext;
        }
        pNodeCurrent->mpNext = pNodeNext->mpNext;
    }
    MacroPair_dtor(&pNode->mValue);
    PoolFree(pNode);
    --mnElementCount;
    return iNext;
}

// @ 0x00846c80
void EA::ArgScript::cUndefineCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(1);
    string8_s0084_6280 name(pArg[0]);
    eastl::FindResult_s0084_6280 r =
        ((eastl::StrHashtable_s0084_6280*)((char*)mFullParser + 0x6c))->find(&name);
    if ((void*)r.mpNode == (void*)((eastl::StrHashtable_s0084_6280*)((char*)mFullParser + 0x6c))
                                     ->mpBucketArray[((eastl::StrHashtable_s0084_6280*)
                                     ((char*)mFullParser + 0x6c))->mnBucketCount]) {
        cError_s0084_6280 err("Unknown definition %s", pArg[0]);
        ThrowException(&err, &gThrowInfo);
    }
}

// @ 0x00846db0
void EA::ArgScript::cParser_s0084_6280::Shutdown()
{
    if (mBool0c == 0)
        return;
    mBool0c = 0;
    eastl::StrHashtable_s0084_6280* pCmd = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x2c);
    eastl::DoFreeNodesTable(pCmd, (int)pCmd->mnBucketCount);
    pCmd->mnNodeCount = 0;
    eastl::ExprTableClear((char*)this + 0x4c);
    if (mpTable14) { void* p = mpTable14; mpTable14 = 0; (*(void(__thiscall**)(void*))(*(char**)p + 8))(p); }
    if (mpTable18) { void* p = mpTable18; mpTable18 = 0; (*(void(__thiscall**)(void*))(*(char**)p + 8))(p); }
    eastl::StrHashtable_s0084_6280* pMac = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x6c);
    pMac->DoFreeNodes((MacroHashNode**)pMac->mpBucketArray, pMac->mnBucketCount);
    pMac->mnNodeCount = 0;
}

// @ 0x00846f10
void EA::ArgScript::cParser_s0084_6280::ParseBegin()
{
    eastl::StrHashtable_s0084_6280* pMac = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x6c);
    pMac->DoFreeNodes((MacroHashNode**)pMac->mpBucketArray, pMac->mnBucketCount);
    pMac->mnNodeCount = 0;
}

// @ 0x00847060
void* eastl::hash_map_s0084_6280::operator[](const string8_s0084_6280* pKey)
{
    return (void*)mTable.find(pKey).mpNode;
}

// @ 0x00847120
void eastl::StrHashtable_s0084_6280::DoRehash(unsigned nNewBucketCount)
{
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        StrNode_s0084_6280* pNode = mpBucketArray[i];
        while (pNode) {
            StrNode_s0084_6280* pNext = pNode->mpNext;
            unsigned nBucket = pNode->mHash % (nNewBucketCount ? nNewBucketCount : 1);
            pNode->mpNext = mpNewBucketArray_probe[nBucket];   // reconstruction
            mpNewBucketArray_probe[nBucket] = pNode;
            pNode = pNext;
        }
    }
}

// @ 0x00847200
EA::ArgScript::cParser_s0084_7200::~cParser_s0084_7200()
{
    if (mInitialized)
        Shutdown();
}

// @ 0x00847490
EA::ArgScript::cParser_s0084_7200::cParser_s0084_7200()
{
    mStateID = 0x8ba83acb;
    mRefCount = 0;
    mInitialized = false;
    mFlags = 0;
    mMinVersion = -1;
    mMaxVersion = -1;
    mScriptVersion = -1;
    mUnknown28 = 0;
    mCurrentLine = 0;
    mBlockCommentDepth = 0;
    mErrorStringHasFileQualification = 0;
    mTotalLinesParsed = 0;
}
