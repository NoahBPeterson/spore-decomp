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
struct cICommand { virtual void ParseLine(const cArguments&) {} };

// cCommandBase: vtable, mParser, mRefCount, mState (0x10 bytes)
struct cCommandBase : public cICommand {
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
struct cBlockCommandBase : public cICommand {
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

struct cParser;
// expression functions: vtable, refcount, [parser]
struct cExprFunction {
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

struct cExpression {
    void AddFunction(const char* name, cExprFunction* fn);   // @ 0x83df90, ret 8
};

struct cParser {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void AddCommand(const char* name, cICommand* cmd);   // slot 5 (+0x14)
#define PV(n) virtual void v##n();
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
    PV(46)
    virtual void Reset(int arg);                                 // slot 47 (+0xbc)
    char pad0[8];
    bool mInitialized;                  // +0xc
    char pad1[0x3f];
    cExpression mExpression;            // +0x4c
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
}} // namespace
