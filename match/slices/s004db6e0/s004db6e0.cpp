// slice s004db6e0 -- SP::cSpeciesCheat::Execute (3967 bytes, /Od /Ob1 /arch:SSE, no /EHsc)
//
// "species_query" cheat command.  Parses -<param> <min> <max> constraints into a
// vector<FunctionalMatch::Constraint>; with constraints present it asks the
// ObjectTemplateDB for matching resources and prints their paths.  With none, it
// handles three sub-commands: -dumpFull <param> (value + path per object),
// -dump <param> (value range) and -speciesDump (species_dump.csv through an
// EA::IO::FileStream: one row per object, one column per parameter).
//
// The EASTL containers are modelled as small local stubs (the original calls their
// out-of-line instantiations); behaviour and call order follow the machine code.

#include <string.h>
#include <stdlib.h>
#pragma intrinsic(strcmp)

typedef unsigned int uint32_t;

void operator delete[](void* p);       // 0x00f47380

extern wchar_t gEmptyWStr[];            // 0x01667bac, eastl empty-string sentinel

// ---- stub EASTL strings / vectors -------------------------------------------------
struct WString {                        // eastl::basic_string<wchar_t>, 12 bytes (+ empty allocator)
    wchar_t* b; wchar_t* e; wchar_t* cap;
    WString() { b = 0; e = 0; cap = 0; b = gEmptyWStr; e = b; cap = b + 1; }
    void FreeBuffer();                  // 0x004237d0
    void Ctor(const wchar_t* s, char* tag);   // 0x0041df50
    void Append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x00429580
};

struct CString {                        // eastl::basic_string<char>
    char* b; char* e; char* cap;
    CString() { b = 0; e = 0; cap = 0; b = (char*)gEmptyWStr; e = b; cap = b + 1; }
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    void Dtor();                        // 0x00530670
    void InlineFree() { if ((cap - b) > 1 && b) operator delete[](b); }
};

struct Tag { };                         // empty allocator-tag placeholder (passed by address)

struct Item12 { uint32_t a, b, c; };    // 12-byte resource key

struct VecF {                           // eastl::vector<float>
    float* b; float* e; float* cap;
    uint32_t alloc;
    void AllocCtor(char* tag);          // 0x00429360
    void Ctor(char* tag);               // 0x00540470
    void Reserve(uint32_t n);           // 0x004e0880
    void Dtor();                        // 0x00425990
};

struct VecK {                           // eastl::vector<Item12>
    Item12* b; Item12* e; Item12* cap;
    uint32_t alloc;
    void AllocCtor(char* tag);          // 0x00429360
    void Ctor(char* tag);               // 0x00540470
    void Reserve(uint32_t n);           // 0x0041e4d0
    bool Empty();                       // 0x00526430 (shared instantiation)
    void Dtor();                        // 0x005156b0
};

struct VecC {                           // eastl::vector<FunctionalMatch::Constraint>
    uint32_t* b; uint32_t* e; uint32_t* cap;
    void Ctor(char* tag);               // 0x00540470
    bool Empty();                       // 0x00526430
    void PushBack(void* constraint);    // 0x004e18e0
    void Dtor();                        // 0x004e1780 (applied to the Constraint's inner vector)
};

struct Constraint {                     // SP::FunctionalMatch::Constraint
    uint32_t pad[4];
    VecC inner;
    Constraint* Construct(uint32_t id, int zero, float mn, float mx);   // 0x005588f0
};

struct FloatVecNode { Item12 key; VecF vals; };   // rbtree value_type: pair<Item12, vector<float>>

struct RbIter {                         // rbtree_iterator
    void* node;
    void Ctor(void* n);                 // 0x00566c50
    FloatVecNode* Deref();              // 0x00564f50
    void Inc();                         // 0x00422c50
};

struct RbMap {                          // eastl::map<Item12, vector<float>>
    uint32_t pad[7];
    void Ctor(char* tag);               // 0x004b5980
    VecF* Index(Item12* key);           // 0x004e1a90
    void DoNuke(void* root);            // 0x004e4170
};

void PushBackFloat(VecF* v, float* val);  // 0x004547f0 (thiscall on vector<float>)

// ---- engine interfaces ----------------------------------------------------------------
struct IFileStream {
    virtual void v0();
    virtual void AddRef();              // +4
    virtual void Release();             // +8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Close();               // +0x18 (slot 6)
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void Flush();               // +0x34 (slot 13)
    virtual void Write(const void* p, uint32_t n);   // +0x38 (slot 14)
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18();
    virtual bool Open(int a, int b, int c, int d);   // +0x4c (slot 19)
};

struct cArguments {
    bool HasArgument(const char* name);                   // 0x00837ee0
    const char** OptionArguments(const char* name, int n);   // 0x00838330
};

struct IObjectTemplateDB {
    virtual void v0();
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void QueryMatches(VecK* out, VecC* constraints);   // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual bool GetParameterRange(uint32_t id, VecF* out);    // +0x44
    virtual void v18();
    virtual bool GetParameterValues(uint32_t id, VecF* values, VecK* items);   // +0x4c
};

struct IResourceManager {
    virtual void pad0();                // slots 0..0x1e filled below
};
struct IResourceManagerFull {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30();
    virtual void GetPath(Item12* key, WString* out);   // +0x7c (slot 31)
};

struct ParamDef { uint32_t id; const char* name; };
extern ParamDef gSpeciesParams[26];     // 0x013f07e8

IObjectTemplateDB* ObjectTemplateDB();          // 0x0067cb40
IResourceManagerFull* GetManager();             // 0x0067dcd0
void  ArgScriptOutput(void* parser, const char* fmt, ...);   // EA::ArgScript::Output 0x00841000
void  AppendFormat(WString* s, const wchar_t* fmt, ...);     // 0x004e0850 (append sprintf)
void  Format(WString* s, const wchar_t* fmt, ...);           // 0x0041e050 (sprintf)
void  GetDataPath(uint32_t id, WString* out, int flag);      // 0x00688830
void* NewObject(uint32_t size);                              // 0x006abeb0
IFileStream* FileStreamCtor(void* mem, const wchar_t* path); // EA::IO::FileStream::FileStream 0x00931e10
WString* ConvertToString16(WString* out, const char* s, int n);   // EA::ConvertToString16 0x0093c5a0
CString* ConvertToString8(CString* out, WString* s);              // EA::ConvertToString8  0x0093c570
void  OpenFile(const wchar_t* path);                         // EA::Process::OpenFile 0x00935e60
extern wchar_t gNewlineW[];                                  // L"\n" at 0x013f0ce0

namespace SP {

struct cSpeciesCheat {
    uint32_t pad0;
    void*    mParser;               // +4: cCommandBase::mParser
    uint32_t pad[2];                // base cCommandStateT<...>, size 0x10
    void Execute(cArguments* pArguments);   // __thiscall, virtual override
    void GetFullPath(Item12* key, WString* out);   // 0x004dc660
};

// @ 0x004db6e0
void cSpeciesCheat::Execute(cArguments* pArguments)
{
    IObjectTemplateDB* pDB = ObjectTemplateDB();
    VecC constraints;
    char tagC;
    constraints.Ctor(&tagC);
    uint32_t nParams = 26;

    for (uint32_t i = 0; i < nParams; i = i + 1) {
        if (pArguments->HasArgument(gSpeciesParams[i].name)) {
            const char** pOpts = pArguments->OptionArguments(gSpeciesParams[i].name, 2);
            if (pOpts) {
                char* endp0;
                char* endp1;
                float fMin = (float)strtod(pOpts[0], &endp0);
                float fMax = (float)strtod(pOpts[1], &endp1);
                Constraint c;
                constraints.PushBack(c.Construct(gSpeciesParams[i].id, 0, fMin, fMax));
                c.inner.Dtor();
            } else {
                ArgScriptOutput(mParser, "Usage:\n species_query -%s  <min> <max>\n",
                                gSpeciesParams[i].name);
            }
        }
    }

    if (!constraints.Empty()) {
        char tagR;
        VecK results;
        results.Ctor(&tagR);
        pDB->QueryMatches(&results, &constraints);
        if (!results.Empty()) {
            Item12* pEnd = results.e;
            for (Item12* p = results.b; p != pEnd; p = p + 1) {
                WString path;
                GetManager()->GetPath(p, &path);
                ArgScriptOutput(mParser, "%ls\n", path.b);
                path.FreeBuffer();
            }
        }
        for (Item12* q = results.b; q < results.e; q = q + 1) { }
        results.Dtor();
        constraints.Dtor();
        return;
    }

    if (pArguments->HasArgument("dumpFull")) {
        bool bDone = false;
        const char** pOpts = pArguments->OptionArguments("dumpFull", 1);
        if (pOpts) {
            uint32_t k;
            for (k = 0; k < nParams; k = k + 1) {
                if (strcmp(gSpeciesParams[k].name, pOpts[0]) == 0) break;
            }
            if (k < nParams) {
                char tagI, tagF;
                VecK items;
                items.Ctor(&tagI);
                VecF floats;
                floats.Ctor(&tagF);
                if (pDB->GetParameterValues(gSpeciesParams[k].id, &floats, &items)) {
                    bDone = true;
                    WString path;
                    uint32_t n = (uint32_t)(((char*)items.e - (char*)items.b) / 12);
                    for (uint32_t a = 0; a < n; a = a + 1) {
                        float val = floats.b[a];
                        Item12* pItem = (Item12*)((char*)items.b + a * 12);
                        GetFullPath(pItem, &path);
                        ArgScriptOutput(mParser, "%f\t%ls\n", (double)val, path.b);
                    }
                    path.FreeBuffer();
                }
                for (float* q = floats.b; q < floats.e; q = q + 1) { }
                floats.Dtor();
                for (Item12* q = items.b; q < items.e; q = q + 1) { }
                items.Dtor();
            }
        }
        if (!bDone) {
            ArgScriptOutput(mParser, "Usage:\n species_query -dumpFull <parameter name>\n");
        }
    }
    else if (pArguments->HasArgument("dump")) {
        bool bDone = false;
        const char** pOpts = pArguments->OptionArguments("dump", 1);
        if (pOpts) {
            uint32_t k;
            for (k = 0; k < nParams; k = k + 1) {
                if (strcmp(gSpeciesParams[k].name, pOpts[0]) == 0) break;
            }
            if (k < nParams) {
                char tagF;
                VecF floats;
                floats.Ctor(&tagF);
                if (pDB->GetParameterRange(gSpeciesParams[k].id, &floats)) {
                    bDone = true;
                    float* pEnd = floats.e;
                    for (float* p = floats.b; p != pEnd; p = p + 1) {
                        ArgScriptOutput(mParser, "%f\n", (double)*p);
                    }
                }
                for (float* q = floats.b; q < floats.e; q = q + 1) { }
                floats.Dtor();
            }
        }
        if (!bDone) {
            ArgScriptOutput(mParser, "Usage:\n species_query -dump <parameter name>\n");
        }
    }
    else if (pArguments->HasArgument("speciesDump")) {
        pArguments->OptionArguments("speciesDump", 0);
        WString csvPath;
        WString dataDir;
        GetDataPath(0xa02150, &dataDir, 0);
        Format(&csvPath, L"%lsspecies_dump.csv", dataDir.b);

        IFileStream* pFile = (IFileStream*)NewObject(0x22c);
        if (pFile) {
            pFile = FileStreamCtor(pFile, csvPath.b);
        } else {
            pFile = 0;
        }
        IFileStream* pStream = pFile;
        if (pStream) pStream->AddRef();
        pStream->Open(3, 2, 1, 0);

        char tagH, tagM;
        WString line;
        line.Ctor(L"File,", &tagH);
        CString out8;
        WString rowPath;
        RbMap perItem;
        perItem.Ctor(&tagM);

        for (uint32_t p = 0; p < nParams; p = p + 1) {
            char tagA, tagB;
            VecK items;
            items.b = 0; items.e = 0; items.cap = 0;
            items.AllocCtor(&tagA);
            VecF floats;
            floats.b = 0; floats.e = 0; floats.cap = 0;
            floats.AllocCtor(&tagB);
            items.Reserve(100);
            floats.Reserve(100);
            if (pDB->GetParameterValues(gSpeciesParams[p].id, &floats, &items)) {
                WString name16;
                ConvertToString16(&name16, gSpeciesParams[p].name, -1);
                AppendFormat(&line, L"%ls,", name16.b);
                uint32_t n = (uint32_t)(floats.e - floats.b);
                for (uint32_t j = 0; j < n; j = j + 1) {
                    float val = floats.b[j];
                    Item12* pItem = (Item12*)((char*)items.b + j * 12);
                    PushBackFloat(perItem.Index(pItem), &val);
                }
                name16.FreeBuffer();
            }
            for (float* q = floats.b; q < floats.e; q = q + 1) { }
            floats.Dtor();
            for (Item12* q = items.b; q < items.e; q = q + 1) { }
            items.Dtor();
        }

        {   // header row
            const wchar_t* pe = gNewlineW;
            while (*pe) pe = pe + 1;
            line.Append(gNewlineW, gNewlineW + (pe - gNewlineW));
            CString tmp;
            CString* r = ConvertToString8(&tmp, &line);
            if (r != &out8) out8.assign(r->b, r->e);
            tmp.Dtor();
            pStream->Write(out8.b, (uint32_t)(out8.e - out8.b));
        }

        RbIter it;
        RbIter itEnd;
        it.Ctor(((void**)&perItem)[2]);                // begin (anchor.left)
        itEnd.Ctor(&((void**)&perItem)[1]);            // end (anchor)
        for (; it.node != itEnd.node; it.Inc()) {
            FloatVecNode* pNode = it.Deref();
            Item12* pKey = &pNode->key;
            VecF* pVals = &it.Deref()->vals;
            GetFullPath(pKey, &rowPath);
            Format(&line, L"%ls,", rowPath.b);
            float* pv = pVals->b;
            float* pvEnd = pVals->e;
            for (; pv != pvEnd; pv = pv + 1) {
                float val = *pv;
                AppendFormat(&line, L"%f,", (double)val);
            }
            const wchar_t* pe = gNewlineW;
            while (*pe) pe = pe + 1;
            line.Append(gNewlineW, gNewlineW + (pe - gNewlineW));
            CString tmp;
            CString* r = ConvertToString8(&tmp, &line);
            if (r != &out8) out8.assign(r->b, r->e);
            tmp.InlineFree();
            pStream->Write(out8.b, (uint32_t)(out8.e - out8.b));
        }
        pStream->Flush();
        pStream->Close();
        OpenFile(csvPath.b);
        perItem.DoNuke(((void**)&perItem)[3]);
        rowPath.FreeBuffer();
        out8.Dtor();
        line.FreeBuffer();
        if (pStream) pStream->Release();
        dataDir.FreeBuffer();
        csvPath.FreeBuffer();
    }

    constraints.Dtor();
}

} // namespace SP
