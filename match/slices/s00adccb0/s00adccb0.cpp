// Simulator ArgScript message commands, the editor-resource attachment they carry,
// and the game-state fade walker of the same module.
//
// Retail layouts recovered from the neighbouring PDB-name slices:
//   Msg (0x40)  vptr +0, refcount +4, four 8-byte message arguments +8..+0x27,
//               tag +0x30, flags +0x38
//   EditorRes (0x34) two vtables at +0 and +8, source resource at +0xc,
//               offset/extraOffset +0x10..+0x24, flag bytes +0x28..+0x2e,
//               target/owner id +0x30
//   HTbl (0x10)  bucket array +4, bucket count +8, element count +0xc
//
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------- allocator / externs
void* operator new(unsigned int size, const char* name, int a, int b,
                   const char* file, int line);              // 0x00f473a0
void __cdecl operator_delete(void* p);                       // 0x00f47380

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);

extern char g_emptyString[];                                 // 0x013ec47c
extern char g_simulatorName[];                               // 0x013f09b4 "Simulator"

void __cdecl SetMessageString8(void* msg, int index, const char* text);  // 0x00618bd0

// ---------------------------------------------------------------- argument parser
namespace EA { namespace ArgScript {
class cArguments
{
public:
    const char** MainArguments(int count);                       // 0x00838320
    const char** MainArguments(int* count, int min, int max);    // 0x00838020
    const char** OptionArguments(const char* name, int count);   // 0x00838330
    bool HasFlag(const char* name);                              // 0x008380b0
};
} }

struct Vector3
{
    float x, y;
    union
    {
        float z;
        struct
        {
            uint8_t za, zb, fadeOn, zd;   // +0x08..+0x0b, alias z
        };
    };
};

// ArgScript value parser reached through a command's +4 field.
class IArgParser
{
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void p36(); virtual void p37();
    virtual float ParseF(const char* text);                       // 0x98
    virtual void  p39();
    virtual int   ParseI(const char* text);                       // 0xa0
    virtual void  p41();
    virtual Vector3* ParseV(Vector3* out, const char* text);      // 0xa8
};

// ---------------------------------------------------------------- message object
struct MsgData
{
    int m_arg0a, m_arg0b;      // +0x08
    int m_arg1a, m_arg1b;      // +0x10
    int m_arg2a, m_arg2b;      // +0x18
    int m_arg3a, m_arg3b;      // +0x20
    int m_f28, m_f2c;          // +0x28
    int m_tag;                 // +0x30
    MsgData() : m_tag(0) {}
};

struct RefBase
{
    virtual void v00();
    virtual void AddRef();      // slot 1
    virtual void Release();     // slot 2
    long m_refCount;            // +0x04
    RefBase() { _InterlockedExchange(&m_refCount, 0); }
};

struct Msg : MsgData, RefBase
{
    int m_f34;                  // +0x34
    int m_flags;                // +0x38
    int m_f3c;                  // +0x3c
    Msg() : MsgData(), m_flags(0) {}
};

// ---------------------------------------------------------------- editor-resource payload
class IEditorRef
{
public:
    virtual void AddRef();                       // +0
    virtual void Release();                      // +4
    virtual void v08();                          // +0x8
    virtual void SetSomething(bool on);          // +0xc
    virtual bool IsValid();                      // +0x10
};

struct EditorRes
{
    void* m_vptr;                // +0x00
    int   m_refCount;            // +0x04
    void* m_editorVptr;          // +0x08 (IRef sub-object vtable)
    void* m_resource;            // +0x0c
    Vector3 m_offset;            // +0x10
    Vector3 m_extra;             // +0x1c
    uint8_t m_attached;          // +0x28
    uint8_t m_noWait;            // +0x29
    uint8_t m_softStop;          // +0x2a
    uint8_t m_pinToSurface;      // +0x2b
    uint8_t m_persist;           // +0x2c
    uint8_t m_useRadius;         // +0x2d
    uint8_t m_useHeight;         // +0x2e
    uint8_t m_pad2f;             // +0x2f
    int   m_target;              // +0x30

    EditorRes();
    EditorRes* copyCtor(EditorRes* src);                     // 0x00ad7ca0
    IEditorRef* EditorRef() { return (IEditorRef*)&m_editorVptr; }
    void AddRef() { EditorRef()->AddRef(); }
    void Release() { EditorRef()->Release(); }
};

// ---------------------------------------------------------------- eastl hash table
struct BigNode;
struct HTbl
{
    uint32_t m_f00;              // +0x00
    BigNode** m_bucketArray;     // +0x04
    uint32_t m_bucketCount;      // +0x08
    uint32_t m_size;             // +0x0c

    void DoFreeNodes(void* nodes, unsigned count);           // 0x007611f0
};

struct BigNode
{
    uint32_t m_key;              // +0x00
    EditorRes m_value;           // +0x04 (0x34 bytes)
    BigNode* m_next;             // +0x38
};

// POD mirror of EditorRes used for stack locals: retail copy-constructs into
// uninitialised storage, so this type deliberately has no constructor.
struct EditorValue
{
    void* m_vptr;                // +0x00
    int   m_refCount;            // +0x04
    void* m_editorVptr;          // +0x08
    void* m_resource;            // +0x0c
    Vector3 m_offset;            // +0x10
    Vector3 m_extra;             // +0x1c
    uint8_t m_attached;          // +0x28
    uint8_t m_noWait;            // +0x29
    uint8_t m_softStop;          // +0x2a
    uint8_t m_pinToSurface;      // +0x2b
    uint8_t m_persist;           // +0x2c
    uint8_t m_useRadius;         // +0x2d
    uint8_t m_useHeight;         // +0x2e
    uint8_t m_pad2f;             // +0x2f
    int   m_target;              // +0x30

    EditorValue* copyCtor(void* src);                          // 0x00ad7ca0
};

struct IterA { BigNode* m_node; BigNode** m_bucket; };

struct GameEventTable : HTbl
{
    IterA* eraseA(IterA* out, IterA pos);                        // 0x00adc9f0
    BigNode* head() { return m_bucketArray[0]; }
    BigNode* end() { return m_bucketArray[m_bucketCount]; }
};

// ---------------------------------------------------------------- command objects
class cAppState
{
public:
    void AddMessage(EA::ArgScript::cArguments* args, Msg* msg, char flag); // 0x007e4190
};

struct SimCommand
{
    void* m_vptr;                // +0x00
    IArgParser* m_parser;        // +0x04
    uint32_t m_pad08;            // +0x08
    cAppState* m_appState;       // +0x0c

    void ExecAttached(EA::ArgScript::cArguments* args);          // 0x00adcd10
    void ExecSoftFlag(EA::ArgScript::cArguments* args);          // 0x00adcfc0
    void ExecPlain(EA::ArgScript::cArguments* args);             // 0x00add060
    void ExecList(EA::ArgScript::cArguments* args);              // 0x00add0f0
};

struct cGameState
{
    uint8_t m_pad00[0xd0];
    GameEventTable m_events;     // +0xd0
    void FadeFromBlack();        // 0x00adda70
};

// ---------------------------------------------------------------- globals
extern void* g_vtbl_145b81c;     // 0x0145b81c
extern void* g_vtbl_145b80c;     // 0x0145b80c
extern void* g_vtbl_13ec458;     // 0x013ec458
extern void* g_vtbl_13eb938;     // 0x013eb938
extern void* g_vtbl_13eb90c;     // 0x013eb90c
extern void* g_vtbl_13eb844;     // 0x013eb844
extern void* g_vtbl_145b2f8;     // 0x0145b2f8
extern void* g_vtbl_145b2ec;     // 0x0145b2ec

EditorRes::EditorRes()
{
    m_refCount = 0;
    *(void* volatile*)&m_editorVptr = &g_vtbl_13eb938;
    m_vptr = &g_vtbl_145b2f8;
    m_editorVptr = &g_vtbl_145b2ec;
    m_resource = 0;
}

// ---------------------------------------------------------------- 0x00adccb0
struct NodeOwner
{
    void* m_vptrA;               // +0x00
    uint32_t m_pad04;            // +0x04
    void* m_vptrB;               // +0x08
    uint32_t m_pad0c;            // +0x0c
    HTbl m_table;                // +0x10

    void* Destroy(uint8_t flags); // 0x00adccb0
};

// @ 0x00adccb0
void* NodeOwner::Destroy(uint8_t flags)
{
    HTbl* table = &m_table;

    m_vptrA = &g_vtbl_145b81c;
    m_vptrB = &g_vtbl_145b80c;

    table->DoFreeNodes(table->m_bucketArray, table->m_bucketCount);

    uint32_t bucketCount = table->m_bucketCount;
    table->m_size = 0;
    if (bucketCount > 1)
        operator_delete(table->m_bucketArray);

    m_vptrB = &g_vtbl_13ec458;
    m_vptrA = &g_vtbl_13eb938;

    if (flags & 1)
        operator_delete(this);
    return this;
}

// ---------------------------------------------------------------- 0x00adcd10
// @ 0x00adcd10
void SimCommand::ExecAttached(EA::ArgScript::cArguments* args)
{
    const char** av = args->MainArguments(2);

    Msg* msg = new (g_simulatorName, 0, 0, 0, 0) Msg();
    if (msg)
        msg->AddRef();
    msg->m_tag = 0x0440377c;
    SetMessageString8(msg, 0, av[0]);
    SetMessageString8(msg, 1, av[1]);

    EditorRes* res = new (g_simulatorName, 0, 0, 0, 0) EditorRes();
    if (res)
        res->AddRef();

    res->m_useRadius = 0;
    res->m_useHeight = 0;
    res->m_noWait = !args->HasFlag("noWait");
    if (args->HasFlag("useRadius"))
        res->m_useRadius = 1;
    if (args->HasFlag("useHeight"))
        res->m_useHeight = 1;
    res->m_attached = args->HasFlag("attached") != 0;
    res->m_softStop = !args->HasFlag("softStop");
    res->m_persist = args->HasFlag("persist") != 0;
    res->m_pinToSurface = args->HasFlag("pinToSurface") != 0;

    Vector3 value = { 0.0f, 0.0f, 0.0f };
    res->m_offset = value;

    const char** opt = args->OptionArguments("offset", 1);
    if (opt)
    {
        Vector3* v = m_parser->ParseV(&value, opt[0]);
        res->m_offset.x = v->x;
        res->m_offset.y = v->y;
        res->m_offset.z = v->z;
    }

    value.x = 0.0f;
    value.y = 0.0f;
    value.z = 0.0f;
    res->m_extra = value;

    opt = args->OptionArguments("extraOffset", 1);
    if (opt)
    {
        Vector3* v = m_parser->ParseV(&value, opt[0]);
        res->m_extra.x = v->x;
        res->m_extra.y = v->y;
        res->m_extra.z = v->z;
    }

    IEditorRef* attachment = res->EditorRef();
    if ((msg->m_flags & 4) != 0 && msg->m_arg2a != 0)
        ((IEditorRef*)msg->m_arg2a)->Release();

    msg->m_arg2a = (int)attachment;
    if (attachment)
        attachment->AddRef();
    msg->m_flags |= 4;

    opt = args->OptionArguments("target", 1);
    SetMessageString8(msg, 3, opt ? opt[0] : g_emptyString);

    m_appState->AddMessage(args, msg, 0);
    attachment->Release();
    msg->Release();
}

// ---------------------------------------------------------------- 0x00adcfc0
// @ 0x00adcfc0
void SimCommand::ExecSoftFlag(EA::ArgScript::cArguments* args)
{
    const char** av = args->MainArguments(1);

    Msg* msg = new (g_simulatorName, 0, 0, 0, 0) Msg();
    if (msg)
        msg->AddRef();
    msg->m_tag = 0x0449c44e;
    SetMessageString8(msg, 0, av[0]);

    msg->m_arg1a = args->HasFlag("soft") ? 1 : 0;

    m_appState->AddMessage(args, msg, 0);
    msg->Release();
}

// ---------------------------------------------------------------- 0x00add060
// @ 0x00add060
void SimCommand::ExecPlain(EA::ArgScript::cArguments* args)
{
    const char** av = args->MainArguments(1);

    Msg* msg = new (g_simulatorName, 0, 0, 0, 0) Msg();
    if (msg)
        msg->AddRef();
    msg->m_tag = 0x04485c77;
    SetMessageString8(msg, 0, av[0]);

    m_appState->AddMessage(args, msg, 0);
    msg->Release();
}

// ---------------------------------------------------------------- 0x00add0f0
// @ 0x00add0f0
void SimCommand::ExecList(EA::ArgScript::cArguments* args)
{
    int count = 0;
    const char** av = args->MainArguments(&count, 1, 5);

    Msg* msg = new (g_simulatorName, 0, 0, 0, 0) Msg();
    if (msg)
        msg->AddRef();
    msg->m_tag = 0x0750d599;

    for (int i = 0; i < count; ++i)
        SetMessageString8(msg, i, av[i]);

    m_appState->AddMessage(args, msg, 0);
    msg->Release();
}

// ---------------------------------------------------------------- 0x00adda70
// @ 0x00adda70
void cGameState::FadeFromBlack()
{
    BigNode** bucket = m_events.m_bucketArray;
    BigNode* node = *bucket;
    if (node == 0)
    {
        ++bucket;
        node = *bucket;
        while (node == 0)
        {
            ++bucket;
            node = *bucket;
        }
        node = *bucket;
    }

    BigNode* end = m_events.end();
    IEditorRef* ref;
    while (node != end)
    {
        EditorValue value;
        value.copyCtor(&node->m_value);

        ref = (IEditorRef*)value.m_resource;
        if (ref == 0 || !ref->IsValid())
        {
            node = node->m_next;
            while (node == 0)
            {
                ++bucket;
                node = *bucket;
            }
            if (ref != 0)
                ref->Release();
        }
        else
        {
            if (value.m_softStop)
                ref->SetSomething(true);
            else
                ref->SetSomething(false);
            if (ref != 0)
                ref->Release();

            IterA pos;
            pos.m_node = node;
            pos.m_bucket = bucket;
            IterA out;
            IterA* next = m_events.eraseA(&out, pos);
            node = next->m_node;
            bucket = next->m_bucket;
        }
    }
}
