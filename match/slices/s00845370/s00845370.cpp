// Slice s00845370: EA::ArgScript::cParser::Init (0x8456e0), which registers the built-in
// commands (include, set, if, define, ...) and expression functions (varExists, ...).
#include "types.h"

typedef unsigned int size_t;
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

namespace EA { namespace ArgScript {

struct cArguments;
class cParser;
struct cParserIsState { uint32_t m[2]; };

class cICommand { public:
    virtual void v0() {}
    virtual void v1() {}
    virtual void Attach(cParser*, void*) {}       // slot 2 (+0x8)
    virtual int  AddRef() { return 0; }           // slot 3 (+0xc)
    virtual int  Release() { return 0; }          // slot 4 (+0x10)
    virtual void ParseLine(const cArguments&) {}
};

// ---- eastl stand-ins ---------------------------------------------------------------------------
extern "C" void  __cdecl FUN_00f47380(void* p);                                    // operator delete
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned size);  // memcpy
void MakeCaseInsensitiveChars(char* src, int* dst);                                // 0x00840cc0

// eastl::basic_string<char, eastl::allocator> (16 bytes: three pointers + pad)
struct string8 {
    char* mpBegin;                          // +0
    char* mpEnd;                            // +4
    char* mpCapacity;                       // +8
    uint32_t mPad;                          // +0xc

    string8()
    {
        mpBegin = (char*)0x01667bac;
        mpEnd = (char*)0x01667bac;
        mpCapacity = (char*)0x01667bad;
    }
    __forceinline string8(const char* first, const char* last)
    {
        uint32_t n = (uint32_t)(last - first);
        if (n + 1 > 1) {
            mpBegin = (char*)operator new(n + 1, "ArgScript", 0, 0, (const char*)0x013ebb38, 0xd1);
            mpCapacity = mpBegin + n + 1;
        } else {
            mpBegin = (char*)0x01667bac;
            mpCapacity = (char*)0x01667bad;
        }
        FUN_011e0744(mpBegin, first, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~string8()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            FUN_00f47380(mpBegin);
    }
    string8& append(const char* first, const char* last);    // 0x00455d60
    string8& assign(const char* first, const char* last);    // 0x00454cb0
};

bool String8Equal(const string8& a, const string8& b);       // 0x00554fb0

// node of hashtable<string8, AutoRefCount<cICommand>>
struct PairB {
    string8    mKey;        // +0
    cICommand* mpObject;    // +0x10
    ~PairB();               // 0x0067e830
};
struct CommandNode : PairB {
    CommandNode* mpNext;    // +0x14
};

// node of hashtable<string8, string8>
struct PairSS {
    string8 mKey;           // +0
    string8 mValue;         // +0x10
    PairSS(const string8& k, const string8& v);   // 0x00841d60
};
struct StringNode : PairSS {
    StringNode* mpNext;     // +0x20
};

struct InsertResult { StringNode* mpNode; void** mpBucketPtr; };

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

// hashtable<string8, AutoRefCount<cICommand>>, 0x20 bytes
struct CommandMap {
    uint32_t       mField00;            // +0
    CommandNode**  mpBucketArray;       // +4
    uint32_t       mnBucketCount;       // +8
    uint32_t       mnElementCount;      // +0xc
    uint32_t       mPad10[4];           // +0x10
    cICommand*& operator[](const string8& key);   // 0x0083cb70
    CmdIter find(const string8& key);             // 0x007e2ea0
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

struct StrIter {
    StringNode*  mpNode;
    StringNode** mpBucketPtr;
    bool operator!=(const StrIter& o) const { return mpNode != o.mpNode; }
};

// hashtable<string8, string8>, 0x20 bytes
struct StringMap {
    uint32_t      mField00;             // +0
    StringNode**  mpBucketArray;        // +4
    uint32_t      mnBucketCount;        // +8
    uint32_t      mnElementCount;       // +0xc
    uint32_t      mPad10[4];            // +0x10
    string8& operator[](const string8& key);                  // 0x00845370
    StrIter find(const string8& key);                         // 0x007e2ea0
    StrIter erase(StrIter pos);                               // 0x008455c0
    int erase(const string8& key);                            // 0x008454e0
    InsertResult insert(const PairSS* value, void* rehash);   // 0x008439b0
    StrIter end()
    {
        StrIter it;
        it.mpBucketPtr = mpBucketArray + mnBucketCount;
        it.mpNode = *it.mpBucketPtr;
        return it;
    }
};

// cCommandBase: vtable, mParser, mRefCount, mState (0x10 bytes)
class cCommandBase : public cICommand { public:
    void* mParser;
    int mRefCount;
    int mState;
    cCommandBase();                       // @ 0x83c800
};
// cCommandBase variant with an extra pointer after the base (0x83c840), 0x14 bytes
struct cCommandBase2 : public cICommand {
    void* mParser;
    int mRefCount;
    int mState;
    int mExtra;
    cCommandBase2();                      // @ 0x83c840
};
// Block command base (0x83cdd0), 0x34 bytes
class cBlockCommandBase : public cICommand { public:
    char pad[0x30];
    cBlockCommandBase();                  // @ 0x83cdd0
};
struct cIf : public cICommand {           // 0xa4 bytes
    char pad[0xa0];
    cIf();                                // @ 0x842ac0
    void ParseLine(const cArguments&) {}
};
struct cSetE : public cICommand {         // 0x54 bytes
    char pad[0x50];
    cSetE();                              // @ 0x841900
    void ParseLine(const cArguments&) {}
};

#define CMD(N) struct N : public cCommandBase { void ParseLine(const cArguments&) {} };
CMD(cInclude) CMD(cSinclude) CMD(cEnd) CMD(cHelp) CMD(cEval) CMD(cSet) CMD(cSetB) CMD(cSetI)
CMD(cSetF) CMD(cSetC) CMD(cSetV2) CMD(cSetV3) CMD(cSetV4) CMD(cPurge) CMD(cUndefine) CMD(cCreate)
CMD(cSCreate) CMD(cArrayCreate) CMD(cShowArguments) CMD(cVersion) CMD(cTrace)
struct cNamespace : public cBlockCommandBase { void ParseLine(const cArguments&) {} };
struct cDefine : public cCommandBase2 {
    cDefine() { mExtra = 0; }
    void ParseLine(const cArguments&) {}
};

class cParser;
// expression functions: vtable, refcount, [parser]
class cExprFunction { public:
    virtual void Eval() {}
    int mRefCount;
    cExprFunction() : mRefCount(0) {}
};
struct cVarExists : public cExprFunction { cParser* mParser; cVarExists(cParser* p) { mParser = p; } void Eval() {} };
struct cDefExists : public cExprFunction { cParser* mParser; cDefExists(cParser* p) { mParser = p; } void Eval() {} };
struct cCommandExists : public cExprFunction { cParser* mParser; cCommandExists(cParser* p) { mParser = p; } void Eval() {} };
struct cEq : public cExprFunction { void Eval() {} };
struct cMatch : public cExprFunction { void Eval(int) {} };
struct cMinVersion : public cExprFunction { cParser* mParser; cMinVersion(cParser* p) { mParser = p; } void Eval() {} };
struct cMaxVersion : public cExprFunction { cParser* mParser; cMaxVersion(cParser* p) { mParser = p; } void Eval() {} };

class cExpression { public:
    void AddFunction(const char* name, cExprFunction* fn);   // @ 0x83df90, ret 8
};

class cParser { public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void AddCommand(const char* name, cICommand* cmd);   // slot 5 (+0x14)
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
    cExpression mExpression;            // +0x4c
    char pad50[0x3f];                   // +0x4d..+0x8b
    StringMap mVariables;               // +0x8c (0x20)
    char padAC[0x84];                   // +0xac..+0x12f
    string8 mScope;                     // +0x130
    char pad140[0x70];                  // +0x140..+0x1af
    string8 mNameBuf;                   // +0x1b0
    void RegisterCommand(const char* name, cICommand* cmd);              // 0x00846000
    bool UnregisterCommand(cICommand* cmd);                              // 0x00846070
    bool UnregisterCommand(const char* name);                            // 0x008460f0
    void SetVariableNoSubstitution(const char* name, const char* value); // 0x00846160
    bool Init();                        // @ 0x8456e0
};

// @ 0x008456e0
bool cParser::Init()
{
    if (!mInitialized) {
    mInitialized = true;
    Reset(0);
    AddCommand("include", new("ArgScript/Include", 0, 0, 0, 0) cInclude());
    AddCommand("sinclude", new("ArgScript/Sinclude", 0, 0, 0, 0) cSinclude());
    AddCommand("end", new("ArgScript/End", 0, 0, 0, 0) cEnd());
    AddCommand("help", new("ArgScript/Help", 0, 0, 0, 0) cHelp());
    AddCommand("eval", new("ArgScript/Eval", 0, 0, 0, 0) cEval());
    AddCommand("set", new("ArgScript/Set", 0, 0, 0, 0) cSet());
    AddCommand("sete", new("ArgScript/SetE", 0, 0, 0, 0) cSetE());
    AddCommand("setb", new("ArgScript/SetB", 0, 0, 0, 0) cSetB());
    AddCommand("seti", new("ArgScript/SetI", 0, 0, 0, 0) cSetI());
    AddCommand("setf", new("ArgScript/SetF", 0, 0, 0, 0) cSetF());
    AddCommand("setc", new("ArgScript/SetC", 0, 0, 0, 0) cSetC());
    AddCommand("setv2", new("ArgScript/SetV2", 0, 0, 0, 0) cSetV2());
    AddCommand("setv3", new("ArgScript/SetV3", 0, 0, 0, 0) cSetV3());
    AddCommand("setv4", new("ArgScript/SetV4", 0, 0, 0, 0) cSetV4());
    AddCommand("namespace", new("ArgScript/Namespace", 0, 0, 0, 0) cNamespace());
    AddCommand("purge", new("ArgScript/Purge", 0, 0, 0, 0) cPurge());
    AddCommand("if", new("ArgScript/If", 0, 0, 0, 0) cIf());
    AddCommand("define", new("ArgScript/Define", 0, 0, 0, 0) cDefine());
    AddCommand("undefine", new("ArgScript/Undefine", 0, 0, 0, 0) cUndefine());
    AddCommand("create", new("ArgScript/Create", 0, 0, 0, 0) cCreate());
    AddCommand("screate", new("ArgScript/SCreate", 0, 0, 0, 0) cSCreate());
    AddCommand("arrayCreate", new("ArgScript/ArrayCreate", 0, 0, 0, 0) cArrayCreate());
    AddCommand("showArguments", new("ArgScript/ShowArguments", 0, 0, 0, 0) cShowArguments());
    AddCommand("version", new("ArgScript/Version", 0, 0, 0, 0) cVersion());
    AddCommand("trace", new("ArgScript/Trace", 0, 0, 0, 0) cTrace());
    mExpression.AddFunction("varExists", new("ArgScript", 0, 0, 0, 0) cVarExists(this));
    mExpression.AddFunction("defExists", new("ArgScript", 0, 0, 0, 0) cDefExists(this));
    mExpression.AddFunction("commandExists", new("ArgScript", 0, 0, 0, 0) cCommandExists(this));
    mExpression.AddFunction("eq", new("ArgScript", 0, 0, 0, 0) cEq());
    mExpression.AddFunction("match", new("ArgScript", 0, 0, 0, 0) cMatch());
    mExpression.AddFunction("minVersion", new("ArgScript", 0, 0, 0, 0) cMinVersion(this));
    mExpression.AddFunction("maxVersion", new("ArgScript", 0, 0, 0, 0) cMaxVersion(this));
    return true;
    }
    return false;
}

// @ 0x00845460
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

// @ 0x008455c0
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

// @ 0x008454e0
int StringMap::erase(const string8& key)
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

// @ 0x00845370
string8& StringMap::operator[](const string8& key)
{
    StrIter it = find(key);
    if (it != end())
        return it.mpNode->mValue;
    string8 def;
    PairSS pair(key, def);
    InsertResult res = insert(&pair, 0);
    return res.mpNode->mValue;
}

// @ 0x00846000
void cParser::RegisterCommand(const char* name, cICommand* cmd)
{
    MakeCaseInsensitiveChars((char*)name, (int*)&mNameBuf);
    cICommand*& slot = mCommands[mNameBuf];
    cICommand* old = slot;
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

// @ 0x00846070
bool cParser::UnregisterCommand(cICommand* cmd)
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

// @ 0x008460f0
bool cParser::UnregisterCommand(const char* name)
{
    MakeCaseInsensitiveChars((char*)name, (int*)&mNameBuf);
    CmdIter it = mCommands.find(mNameBuf);
    if (it != mCommands.end()) {
        it = mCommands.erase(it);
        return true;
    }
    return false;
}

// @ 0x00846160
void cParser::SetVariableNoSubstitution(const char* name, const char* value)
{
    string8 key(mScope.mpBegin, mScope.mpEnd);
    const char* nameEnd = name;
    while (*nameEnd)
        ++nameEnd;
    key.append(name, nameEnd);
    string8& slot = mVariables[key];
    const char* valueEnd = value;
    while (*valueEnd)
        ++valueEnd;
    slot.assign(value, valueEnd);
}
}} // namespace
