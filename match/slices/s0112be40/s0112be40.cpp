// Spore slice s0112be40: Havok hkStructureLayout helpers (0112be40-0112c4f0) and
// RenderWare 4 rwaudio core System (0112c560-0112ce00), prebuilt library code inside
// SporeApp.exe (VC .NET 2003 / cl 13.10, /O2, /GL+/LTCG).
// Equivalence-only per symbols/renderware4_core.txt: only leaf functions can be byte-exact.
// compile with /vc71 /O2 /MD /Gy /EHsc /TP  (float leaves also want /arch:SSE)
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     s32;

extern "C" {
__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
__declspec(dllimport) void  __stdcall GetSystemInfo(void* info);
}

// =====================================================================================
// Havok packfile / structure layout stubs (x86 layouts recovered from the disassembly)
// =====================================================================================

class hkClass;
class hkClassMember;
struct hkTypeInfo;

class hkClassMember
{ public:
    u8  pad0[4];
    hkClass* mpClass;          // +0x4
    u8  pad1[4];
    u8  m_type;                // +0xc
    u8  m_subtype;             // +0xd
    u8  pad2[4];
    u16 m_offset;              // +0x12

    hkClass* getClass();                   // @ 0xfcc210
    u32      getSizeInBytes();             // @ 0x1080ce0
    u32      getCstyleArraySize();         // @ 0x1080cd0
    u32      getAlignment();               // @ 0x1080db0
};

class hkClass
{ public:
    u8  pad0[4];
    hkClass* mpParent;         // +0x4
    u8  pad1[4];
    int m_numMembers;          // +0xc
    u8  pad2[0xc];
    int m_numDeclared;         // +0x1c

    hkClass* getParent();                  // @ 0xfcc210
    int      getNumMembers();              // @ 0x1080330
    hkClassMember* getMember(int i);       // @ 0x1080350
    hkClassMember* getMemberThunk(int i);  // @ 0x10803a0
    hkClassMember* getDeclaredMember(int i); // @ 0x10803b0
    hkClassMember* getMemberByName(const char* name); // @ 0x10803c0
    u32      getStringLength();            // @ 0x93b6c0
    int      getNumDeclaredMembers();      // @ 0x985e40
    int      getNumInterfaces();           // @ 0xfc7e50
    void     setSize(u32 size);            // @ 0xfcc140
};

class hkPointerMap
{ public:
    u8  pad0[8];
    int m_threshold;           // +0x8

    void insert(hkClass* c, int value);    // @ 0x107de70
    int  get(hkClass* c);                  // @ 0x107def0
};

struct hkArrayClass
{
    hkClass** m_data;          // +0x0
    int      m_size;           // +0x4
    u32      m_capacity;       // +0x8

    void insertAt(int index, const hkArrayClass* value); // @ 0x10fbb80
};

class hkThreadMemory
{ public:
    void deallocateChunk(void* ptr, u32 size, int align); // @ 0x107db10
};

extern u32 g_hkThreadMemoryTls;   // @ 0x16e4174
extern u32 g_hkStructureLayoutVtbl; // @ 0x15ba42c

class hkMemory
{ public:
    virtual void v0();
    virtual void freePtr(void* p);                                // +0x4
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void freeChunk(void* p, u32 size, int align);         // +0x14
};

extern hkMemory* g_hkMemory;                              // @ 0x16e4178
extern char      g_vtbl_hkPackfileAllocatedData[];        // @ 0x14a710c
extern char      g_vtbl_hkPackfileAllocatedDataBase[];    // @ 0x13ef094

class hkOstream
{ public:
    void ctor(void* buffer, int size, int flag);      // @ 0x107ef80
    hkOstream& operator<<(const char* text);          // @ 0x107ee30
    void dtor();                                      // @ 0x107efd0
};

struct hkErrorHandler
{
    virtual void v0();
    virtual void v1();
    virtual void report(int severity, u32 id, void* stream,
                        const char* file, int line);  // +0x8
};

extern hkErrorHandler* g_hkErrorHandler;     // @ 0x16e4184

class hkStructureLayout
{ public:
    u32 m_flags;               // +0x0

    hkStructureLayout();       // @ 0x112bf90
};

class hkPackfileReader
{ public:
    static void convertClassVersion1Inplace(hkClass* cls); // @ 0x112be40

    class AllocatedData
    { public:
        void*  mpVtbl;         // +0x0
        u8     pad0[4];
        void** m_ptrs;         // +0x8
        int    m_numPtrs;      // +0xc
        u32    m_ptrFlags;     // +0x10
        u8*    m_base;         // +0x14
        int    m_numBase;      // +0x18
        u32    m_baseFlags;    // +0x1c

        ~AllocatedData();      // @ 0x112bec0
    };
};

// =====================================================================================
// RenderWare 4 / EA audio core stubs
// =====================================================================================

struct MutexParameters
{
    u8  pad[0x10];
    MutexParameters* ctor(int a, int b);   // @ 0x921e00
};

struct Mutex
{
    u8 m_data[0x30];

    Mutex* ctor(void* p, int recursive);   // @ 0x9222a0
    void   Lock(u32 id);                   // @ 0x9221b0
    void   Unlock();                       // @ 0x922270
    void   dtor();                         // @ 0x922130
    void   Init(const MutexParameters* p); // @ 0x922150
};

struct Voice
{
    u8    pad0[0x28];
    float m_f28;               // +0x28
    float m_f2c;               // +0x2c
    float m_f30;               // +0x30
    u8    pad1[0x47 - 0x34];
    u8    m_state;             // +0x47

    void Release(u32 flags);   // @ 0x112e600
    void Stop(int reason);     // @ 0x112e690
};

struct TimerManager
{
    u8   pad0[0x20];
    void ExecuteTimers(int reset);  // @ 0x112d9b0
    void Defragment();              // @ 0x112da30
    void Release();                 // @ 0x112da60
    void dtor();                    // @ 0xc2e4e0
};

struct ICoreAllocator
{
    virtual void  v0();
    virtual void* Alloc(u32 a1, u32 a2, int a3, u32 a4, int a5); // +0x4
    virtual void  v2();
    virtual void  Free(void* p, int a2);                         // +0xc
};

struct Cmd
{
    virtual void v0();
    virtual void exec(float f);    // +0x4

    void* mpNext;                  // +0x4
    u32   m_a8;                    // +0x8
    float m_fc;                    // +0xc
};

struct CompiledCmd
{
    int (*mpFn)(void*);        // +0x0
    void* mpThis;              // +0x4
    u32   m_a8;                // +0x8
    float m_fc;                // +0xc
};

extern void ThreadSleep(const int* ms);    // @ 0x921df0

struct System;

struct AudioObject
{
    u8      pad0[4];
    System* mpSystem;          // +0x4
    u32     m_a8;              // +0x8
    void*   m_ac;              // +0xc
    void*   m_a10;             // +0x10
    u8      pad1[0x10];
    u8      m_a20;             // +0x20
    u8      m_a21;             // +0x21

    void IsCommandComplete(u32 a, float f);   // @ 0x112ccf0
};

struct RtCommandHandler
{
    static u32 execute(CompiledCmd* cmd);     // @ 0x112ccd0
};

struct Node;

struct NodeList
{
    Node* m_head;              // +0x0
    Node* m_tail;              // +0x4
    int   m_count;             // +0x8
    u8    pad0[8];
    u8    m_tag;               // +0x14

    Node* find(u32 id);        // @ 0x112cd30
    Node* insert(Node* n);     // @ 0x112cd60
};

struct Node
{
    Node* pnext;               // +0x0
    u32   m_id;                // +0x4
    u8    pad1[0x1c];
};

struct System
{
    u8  pad00[0x14];
    ICoreAllocator* mpAllocator;   // +0x14
    u32 m_a18;                     // +0x18
    u32 m_a1c;                     // +0x1c
    void* mpCmdBuffer;             // +0x20
    u32 m_a24;                     // +0x24
    void* m_a28;                   // +0x28
    void* m_a2c;                   // +0x2c
    void* m_a30;                   // +0x30
    void* m_a34;                   // +0x34
    u32 m_a38;                     // +0x38
    u32 m_a3c;                     // +0x3c
    void* mpLockFn;                // +0x40
    void* mpUnlockFn;              // +0x44
    Mutex* mpMutexA;               // +0x48
    Mutex* mpMutexB;               // +0x4c
    void* mp_a50;                  // +0x50
    void* mp_a54;                  // +0x54
    void* mpVoiceNodes;            // +0x58
    void* mpCmdList;               // +0x5c
    u8  m_timer[0x50];             // +0x60 .. +0xb0
    u32 m_b0;                      // +0xb0
    u32 m_b4;                      // +0xb4
    u32 m_b8;                      // +0xb8
    float m_bc;                    // +0xbc
    float m_c0;                    // +0xc0
    float m_c4;                    // +0xc4
    float m_c8;                    // +0xc8
    u32 m_cc;                      // +0xcc
    u32 m_d0;                      // +0xd0
    u32 m_d4;                      // +0xd4
    u32 m_d8;                      // +0xd8
    u32 m_dc;                      // +0xdc
    u32 m_e0;                      // +0xe0
    u32 m_e4;                      // +0xe4
    u32 m_e8;                      // +0xe8
    u32 m_ec;                      // +0xec
    u16 m_f0;                      // +0xf0
    u16 m_f2;                      // +0xf2
    u8  m_f4;                      // +0xf4
    u8  m_f5;                      // +0xf5
    u8  m_f6;                      // +0xf6
    u8  m_f7[6];                   // +0xf7

    System* ctor0();                          // @ 0x11341c0
    void Lock();                              // @ 0x112c600
    void Unlock();                            // @ 0x112c620
    bool someCheck(u32 v);                    // @ 0x112c640
    void updateVoices();                      // @ 0x112c690
    void pump();                              // @ 0x112c6e0
    __declspec(noinline) void* Alloc(u32 size, u32 flags, int align, ICoreAllocator* a); // @ 0x112c820
    void  Free(void* ptr, ICoreAllocator* a); // @ 0x112c850
    void  shutdown();                         // @ 0x112c880
    static System* CreateInstance(ICoreAllocator* alloc, u32 cmdBufBytes); // @ 0x112c9e0
    void lockVoiceList();                     // @ 0x112c560
    void setValue(u32* v);                    // @ 0x112c5f0

    TimerManager* timer() { return (TimerManager*)m_timer; }
};

class hkVtableClassRegistry
{ public:
    virtual void v0();                                            // +0x0
    virtual void v1();                                            // +0x4
    virtual void registerOne(void* typeInfo, const hkClass* cls); // +0x8
    void registerClass(hkClass* cls, hkPointerMap* map);          // @ 0x112c4c0
    void registerList(hkTypeInfo const* const* types,
                      hkClass const* const* classes);             // @ 0x112c4f0
};

struct AttributeSet
{
    u8  pad0[0xc];
    void* m_array;             // +0xc

    void getFloat(int i, float* out);   // @ 0x112cc80
    void getDouble(int i, double* out); // @ 0x112cca0
};

struct AllocNode
{
    System* mpSystem;          // +0x10
    void freeSelf();           // @ 0x112cdf0
};

struct AVoiceNode
{
    void dtorA();              // @ 0x1133ea0
};

struct VoiceList
{
    u8  pad0[0x28];
    void* m_a28;               // +0x28
    void* getOrCreate();       // @ 0x112ce00
};

struct Factory
{
    virtual void v0();                       // +0x0
    void* m_pad4;                            // +0x4
    bool (*mpCreate)(void* obj, u32 arg);    // +0x8
};

struct BaseObject
{
    virtual void dtor();                     // +0x0
    virtual void v1();
    virtual void v2();
    virtual void release(int);               // +0xc
};

extern System* g_audioSystem;   // @ 0x16e61a8

// =====================================================================================
// 0112be40  hkPackfileReader::convertClassVersion1Inplace
// =====================================================================================
// @ 0x112be40
void hkPackfileReader::convertClassVersion1Inplace(hkClass* cls)
{
    u32 off = cls->getMemberByName("hasVtable")->m_offset;

    hkClass* p = cls;
    hkClass* q = p->getParent();
    while (q)
    {
        *(u32*)((char*)p + off) = 0;
        p = q;
        q = p->getParent();
    }
    if (*(u8*)((char*)p + off) != 0)
    {
        hkClassMember* m = p->getMemberByName("numImplementedInterfaces");
        ++*(int*)((char*)p + m->m_offset);
    }
    *(u32*)((char*)p + off) = 0;
}

// =====================================================================================
// 0112bec0  hkPackfileReader::AllocatedData::~AllocatedData
// =====================================================================================
// @ 0x112bec0
hkPackfileReader::AllocatedData::~AllocatedData()
{
    mpVtbl = (void*)&g_vtbl_hkPackfileAllocatedData;
    hkMemory* mem = g_hkMemory;
    for (int i = 0; i < m_numPtrs; ++i)
        mem->freePtr(m_ptrs[i]);

    for (int i = 0; i < m_numBase; ++i)
    {
        u32* e = (u32*)(m_base + i * 0xc);
        mem->freeChunk((void*)e[0], e[1], e[2]);
    }
    if ((m_baseFlags & 0x80000000u) == 0)
    {
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_base, (m_baseFlags & 0x3fffffffu) * 0xc, 0x14);
    }
    if ((m_ptrFlags & 0x80000000u) == 0)
    {
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_ptrs, (m_ptrFlags & 0x3fffffffu) * 4, 0x14);
    }
    mpVtbl = (void*)&g_vtbl_hkPackfileAllocatedDataBase;
}

// =====================================================================================
// 0112bf90  hkStructureLayout::hkStructureLayout
// =====================================================================================
// @ 0x112bf90
hkStructureLayout::hkStructureLayout()
{
    m_flags = g_hkStructureLayoutVtbl;
}

// =====================================================================================
// 0112bfa0  hkStructureLayout::getMemberSize(member, data, type)
// =====================================================================================
// @ 0x112bfa0
u32 hkStructureLayout_getMemberSize(hkClassMember* m, const u8* data, u32 type)
{
    switch (type)
    {
    case 1: case 2: case 3: case 4: case 5: case 6:
    case 7: case 8: case 9: case 10: case 11: case 12:
    case 13: case 14: case 15: case 16: case 17: case 18:
    case 24:
        return m->getSizeInBytes();

    case 19:
        return hkStructureLayout_getMemberSize(m, data, m->m_subtype);

    case 20:
    case 21:
        {
            u32 n = data[0];
            if (m->getCstyleArraySize())
                return m->getCstyleArraySize() * n;
            return n;
        }

    case 22:
        return (u32)data[0] + 8;

    case 23:
        return 0;

    case 25:
        {
            u32 len = m->getClass()->getStringLength();
            if (m->getCstyleArraySize())
                return m->getCstyleArraySize() * len;
            return len;
        }

    case 26:
        return (u32)data[0] + 4;

    case 27:
        return (u32)data[0] * 2 + 4;

    case 28:
        return (u32)data[0] * 2;

    default:
        {
            char buffer[0x200];
            hkOstream out;
            out.ctor(buffer, 0x200, 1);
            out << "Unknown class member type in structureLayout::getMemberSize().";
            g_hkErrorHandler->report(3, 0x50a18b58, &out,
                                     ".\\util\\hkStructureLayout.cpp", 0xb9);
            out.dtor();
            return 0;
        }
    }
}

// =====================================================================================
// 0112c150  hkStructureLayout::getMemberAlignment(member, type, align)
// =====================================================================================
// @ 0x112c150
int hkStructureLayout_getMemberAlignment(hkClassMember* m, u32 type, int align)
{
    for (;;)
    {
        switch (type)
        {
        case 0: case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9: case 10: case 11:
        case 12: case 13: case 14: case 15: case 16: case 17:
        case 18: case 24:
            return (int)m->getAlignment();

        case 19:
            type = m->m_subtype;
            continue;

        case 20: case 21: case 22:
        case 26: case 27: case 28:
            return align;

        case 25:
            {
                int best = 1;
                hkClass* cls = m->getClass();
                for (int i = 0; i < cls->getNumMembers(); ++i)
                {
                    hkClassMember* mm = cls->getMember(i);
                    int v = hkStructureLayout_getMemberAlignment(mm, mm->m_type, align);
                    if (v > best)
                        best = v;
                }
                return best;
            }

        default:
            return -1;
        }
    }
}

// =====================================================================================
// 0112c220  hkStructureLayout::computeMemberOffsets(class, data, map)
// =====================================================================================
// @ 0x112c220
void hkStructureLayout_computeMemberOffsets(hkClass* cls, u8* data, hkPointerMap* map)
{
    map->insert(cls, 0);

    int numMembers = cls->getNumMembers();
    for (int i = 0; i < numMembers; ++i)
    {
        hkClassMember* m = cls->getMemberThunk(i);
        if (m->mpClass != 0)
        {
            hkClass* mc = m->getClass();
            if (map->get(mc) > map->m_threshold)
                hkStructureLayout_computeMemberOffsets(mc, data, map);
        }
    }

    hkArrayClass arr;
    arr.m_data = 0;
    arr.m_size = 0;
    arr.m_capacity = 0x80000000u;

    for (hkClass* c = cls; c != 0; )
    {
        hkClass* slot = c;
        hkArrayClass tmp;
        tmp.m_data = &slot;
        tmp.m_size = 1;
        tmp.m_capacity = 0x80000001u;
        arr.insertAt(0, &tmp);
        c = c->getParent();
    }

    u32 baseAlign = data[0];
    int maxAlign = 1;
    int size = 0;

    for (int k = 0; k < arr.m_size; ++k)
    {
        hkClass* c = arr.m_data[k];

        int nInterfaces = c->getNumInterfaces();
        for (int i = 0; i < nInterfaces; ++i)
        {
            if ((size % (int)baseAlign) != 0)
                size += (int)baseAlign - (size % (int)baseAlign);
            size += (int)baseAlign;
            if ((int)baseAlign > maxAlign)
                maxAlign = (int)baseAlign;
        }

        int nDeclared = c->getNumDeclaredMembers();
        for (int i = 0; i < nDeclared; ++i)
        {
            hkClassMember* m = c->getDeclaredMember(i);

            if (size == 0 && k != 0 && data[3] == 0)
                size = 1;

            int a = hkStructureLayout_getMemberAlignment(m, m->m_type, (int)data[0]);
            u8 t = m->m_type;
            if (t == 0x14 || t == 0x16 || t == 0x1a || t == 0x1b || t == 0x1c)
                a = (int)data[0];
            else if (t == 0x13)
            {
                u8 st = m->m_subtype;
                if (st == 0x14 || st == 0x16 || st == 0x1a || st == 0x1b || st == 0x1c)
                    a = (int)data[0];
            }

            if (a > maxAlign)
                maxAlign = a;

            if ((size % a) != 0)
                size += a - (size % a);

            m->m_offset = (u16)size;
            size += hkStructureLayout_getMemberSize(m, data, m->m_type);
        }

        int rounded = size;
        if ((rounded % maxAlign) != 0)
            rounded = maxAlign - (rounded % maxAlign) + rounded;
        if (rounded == 0)
            rounded = 1;
        c->setSize((u32)rounded);
        if (data[2] == 0)
            size = rounded;
    }

    if ((arr.m_capacity & 0x80000000u) == 0)
    {
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(arr.m_data, (arr.m_capacity & 0x3fffffffu) * 4, 0x14);
    }
}

// =====================================================================================
// 0112c4c0  hkVtableClassRegistry::registerClass
// =====================================================================================
// @ 0x112c4c0
void hkVtableClassRegistry::registerClass(hkClass* cls, hkPointerMap* map)
{
    int v = map->get(cls);
    if (v > map->m_threshold)
        hkStructureLayout_computeMemberOffsets(cls, (u8*)this, map);
}

// =====================================================================================
// 0112c4f0  hkVtableClassRegistry::registerList
// =====================================================================================
// @ 0x112c4f0
void hkVtableClassRegistry::registerList(hkTypeInfo const* const* types,
                                         hkClass const* const* classes)
{
    if (*types == 0)
        return;
    int delta = (int)((const char*)classes - (const char*)types);
    hkTypeInfo const* const* p = types;
    for (;;)
    {
        hkClass* c = *(hkClass**)((const char*)p + delta);
        if (c == 0)
            return;
        hkTypeInfo* ti = (hkTypeInfo*)*p;
        registerOne(*(void**)((char*)ti + 8), c);
        hkTypeInfo const* nxt = p[1];
        ++p;
        if (nxt == 0)
            return;
    }
}

// =====================================================================================
// 0112c560  System::lockVoiceList
// =====================================================================================
// @ 0x112c560
void System::lockVoiceList()
{
    mpMutexA->Lock(0x14a7c44);
}

// =====================================================================================
// 0112c5a0  command: release all voices
// =====================================================================================
// @ 0x112c5a0
u32 audio_cmd_releaseVoices(void* cmd)
{
    u8* n = *(u8**)((char*)cmd + 4);
    while (*(u16*)(n + 0xf0) != 0)
    {
        Voice* v = *(Voice**)*(void**)(n + 0x58);
        v->Release(0);
    }
    u8* q = *(u8**)(n + 0x10);
    if (q != 0)
    {
        do
        {
            Voice* v = (Voice*)(q - 0x1c);
            q = *(u8**)q;
            v->Release(0);
        } while (q != 0);
    }
    return 8;
}

// =====================================================================================
// 0112c5f0  System::setValue
// =====================================================================================
// @ 0x112c5f0
void System::setValue(u32* v)
{
    *(u32*)mp_a54 = *v;
}

// =====================================================================================
// 0112c600  System::Lock
// =====================================================================================
// @ 0x112c600
void System::Lock()
{
    void* fn = mpLockFn;
    if (fn == 0)
    {
        mpMutexB->Lock(0x14a7c44);
        return;
    }
    ((void (__fastcall*)(System*))fn)(this);
}

// =====================================================================================
// 0112c620  System::Unlock
// =====================================================================================
// @ 0x112c620
void System::Unlock()
{
    void* fn = mpUnlockFn;
    if (fn == 0)
    {
        mpMutexB->Unlock();
        return;
    }
    ((void (__fastcall*)(System*))fn)(this);
}

// =====================================================================================
// 0112c640  System::someCheck
// =====================================================================================
// @ 0x112c640
bool System::someCheck(u32 v)
{
    Mutex m;
    m.ctor(0, 1);
    m.Lock(0x14a7c44);
    u32 x = m_e0;
    m.Unlock();
    m.dtor();
    return x > v;
}

// =====================================================================================
// 0112c690  System::updateVoices
// =====================================================================================
// @ 0x112c690
void System::updateVoices()
{
    for (int i = 0; i < (int)m_f0; ++i)
    {
        Voice* v = *(Voice**)((char*)*(void**)((char*)this + 0x58) + i * 8);
        if (v->m_state == 1)
        {
            float f = v->m_f28;
            if (f > v->m_f30)
                v->m_f30 = f;
            if (v->m_f2c >= v->m_f30)
                v->Stop(3);
        }
    }
}

// =====================================================================================
// 0112c6e0  System::pump
// =====================================================================================
// @ 0x112c6e0
void System::pump()
{
    Lock();

    void* p = mpCmdList;
    if (p != 0)
    {
        Cmd* c = (Cmd*)((char*)p - 4);
        while (c != 0)
        {
            void* np = *(void**)((char*)c + 4);
            Cmd* next = np ? (Cmd*)((char*)np - 4) : 0;
            c->exec(m_bc);
            c = next;
        }
    }

    timer()->ExecuteTimers(0);
    Unlock();

    updateVoices();
    m_dc = 0;
    Lock();

    u8* cmd = (u8*)mpCmdBuffer;
    u8* end = cmd + m_b4;
    while (cmd < end)
    {
        int sz = ((int (__cdecl*)(void*))*(void**)cmd)(cmd);
        cmd += sz;
        if (cmd >= end)
            break;
    }

    if (m_b4 > m_b8)
        m_b8 = m_b4;
    ++m_e0;
    m_b4 = 0;
    m_d0 = 0;
    Unlock();

    Lock();
    timer()->ExecuteTimers(1);
    timer()->Defragment();
    m_d4 = 0;
    Unlock();
}

// =====================================================================================
// 0112c820  System::Alloc
// =====================================================================================
// @ 0x112c820
void* System::Alloc(u32 size, u32 flags, int align, ICoreAllocator* a)
{
    if (a == 0)
        a = mpAllocator;
    return a->Alloc(size, flags, 1, (u32)align, 0);
}

// =====================================================================================
// 0112c850  System::Free
// =====================================================================================
// @ 0x112c850
__declspec(noinline) void System::Free(void* ptr, ICoreAllocator* a)
{
    if (a == 0)
        a = mpAllocator;
    a->Free(ptr, 0);
}

// =====================================================================================
// 0112c880  System::shutdown
// =====================================================================================
// @ 0x112c880
void System::shutdown()
{
    Lock();
    {
        u8* slot = (u8*)mpCmdBuffer + m_b4;
        m_b4 += 8;
        *(void**)slot = (void*)&audio_cmd_releaseVoices;
        *(void**)(slot + 4) = this;
    }
    Unlock();

    mpMutexA->Lock(0x14a7c44);
    while (m_b4 != 0 || (int)m_e4 > 0)
    {
        pump();
        int one = 1;
        ThreadSleep(&one);
    }
    mpMutexA->Unlock();

    Lock();

    if (m_a28 != 0)
        ((AllocNode*)m_a28)->freeSelf();
    if (m_a2c != 0)
        ((AVoiceNode*)m_a2c)->dtorA();
    if (m_a30 != 0)
        ((AVoiceNode*)m_a30)->dtorA();
    if (m_a34 != 0)
        (*(void (__fastcall**)(void*))*(void**)m_a34)((void*)m_a34);

    timer()->Release();
    Unlock();

    if (mpCmdBuffer != 0)
        mpAllocator->Free(mpCmdBuffer, 0);
    if (mpVoiceNodes != 0)
        mpAllocator->Free(mpVoiceNodes, 0);

    {
        TimerManager* t = (TimerManager*)((char*)this + 0x98);
        for (int i = 1; i >= 0; --i)
        {
            t = (TimerManager*)((char*)t - 0x1c);
            t->dtor();
        }
    }

    mpAllocator->Free(this, 0);
    g_audioSystem = 0;
}

// =====================================================================================
// 0112c9e0  System::CreateInstance
// =====================================================================================
// @ 0x112c9e0
System* System::CreateInstance(ICoreAllocator* alloc, u32 cmdBufBytes)
{
    MutexParameters params;
    params.ctor(1, 0);

    // The original loads the allocator's vtable slot into a register before the call
    // (mov edx,[eax+4]; call edx).  Model that explicitly with an __fastcall thunk:
    // ecx = this, edx = scratch, remaining arguments on the stack exactly as pushed.
    typedef void* (__fastcall* AllocFn)(void* self, int edxArg, u32 size,
                                        u32 flags, int one, u32 align, int zero);
    AllocFn fn = *(AllocFn*)(*(u32**)alloc + 1);
    System* s = (System*)fn(alloc, 0, 0x16c, (u32)"rw::audio::core::System", 1, 0x10, 0);
    if (s == 0)
        return 0;

    s = s->ctor0();

    u8* p = (u8*)(((u32)s + 0x107) & ~7u);
    s->mpCmdBuffer = 0;
    s->mpVoiceNodes = 0;
    s->m_c4 = 1.0f;
    g_audioSystem = s;
    s->mpAllocator = alloc;
    s->m_a18 = 0;
    s->m_a1c = 0;
    s->mpMutexB = (Mutex*)p;
    s->mpMutexB = p ? ((Mutex*)p)->ctor(0, 1) : 0;

    p = (u8*)(((u32)(p + 0x37)) & ~7u);
    s->mpMutexA = (Mutex*)p;
    s->mpMutexA = p ? ((Mutex*)p)->ctor(0, 1) : 0;

    s->mp_a50 = (void*)(((u32)(p + 0x37)) & ~7u);
    s->mp_a54 = (void*)((((u32)s->mp_a50) + 0xb) & ~7u);

    s->mpMutexB->Init(&params);
    s->mpMutexA->Init(&params);

    *(u32*)((char*)s + 0xf7) = 0x1010101;
    *(u16*)((char*)s + 0xfb) = 0x101;
    *(double*)((char*)s + 8) = 0.0;
    s->m_c0 = 0.0f;
    s->m_e4 = 0;
    s->m_a24 = 0;
    s->m_a28 = 0;
    s->m_c8 = 90.0f;
    s->m_cc = 0;
    s->m_d0 = 0;
    s->m_d4 = 0;
    s->m_d8 = 0;
    s->m_dc = 0;

    s->mpVoiceNodes = alloc->Alloc(8, (u32)"rw::audio::core::System::mpVoiceListNodes", 1, 0x10, 0);
    if (s->mpVoiceNodes == 0)
        goto cleanup;

    s->m_f0 = 0;
    s->m_b0 = cmdBufBytes;
    s->m_f2 = 0;
    s->m_e0 = 1;
    s->m_b8 = 0;
    s->m_b4 = 0;

    s->mpCmdBuffer = alloc->Alloc(cmdBufBytes, (u32)"rw::audio::core::CommandBuffer", 1, 4, 0);
    if (s->mpCmdBuffer == 0)
        goto cleanup;

    s->m_a2c = 0;
    s->m_a30 = 0;
    s->m_a34 = 0;
    s->m_a38 = 0;
    s->mpLockFn = 0;
    s->mpUnlockFn = 0;
    s->m_a3c = 0;

    {
        u8 si[0x24];
        GetSystemInfo(si);
        s->m_ec = 0;
        s->m_f6 = (u8)(si[0x14] - 1);
    }
    s->m_e8 = 0xf;
    return s;

cleanup:
    if (s->mpCmdBuffer != 0)
        alloc->Free(s->mpCmdBuffer, 0);
    if (s->mpVoiceNodes != 0)
        alloc->Free(s->mpVoiceNodes, 0);

    {
        TimerManager* t = (TimerManager*)((char*)s + 0x98);
        for (int i = 1; i >= 0; --i)
        {
            t = (TimerManager*)((char*)t - 0x1c);
            t->dtor();
        }
    }
    alloc->Free(s, 0);
    return 0;
}

// =====================================================================================
// 0112cc10  create object from a factory
// =====================================================================================
struct InitData
{
    u8  m_a0;
    u8  pad0[7];
    u8  m_a8;
};

// @ 0x112cc10
u8* audio_createObject(u8* obj, u32 a2, Factory* factory, const InitData* init, u8 flag)
{
    *(u32*)(obj + 8) = a2;
    *(float*)(obj + 0x14) = 0.0f;
    *(float*)(obj + 0x18) = 0.0f;
    *(u32*)(obj + 0x1c) = 0;
    *(u32*)(obj + 0x10) = (u32)factory;
    *(u32*)(obj + 4) = (u32)g_audioSystem;
    obj[0x20] = flag;
    obj[0x21] = init->m_a8;

    bool ok = factory->mpCreate(obj, *(u32*)init);
    if (!ok)
    {
        ((BaseObject*)obj)->dtor();
        ((BaseObject*)obj)->release(0);
        return 0;
    }
    return obj;
}

// =====================================================================================
// 0112cc80  AttributeSet::getFloat
// =====================================================================================
// @ 0x112cc80
void AttributeSet::getFloat(int i, float* out)
{
    *out = *(float*)((char*)m_array + i * 8);
}

// =====================================================================================
// 0112cca0  AttributeSet::getDouble
// =====================================================================================
// @ 0x112cca0
void AttributeSet::getDouble(int i, double* out)
{
    *out = *(double*)((char*)m_array + i * 8);
}

// =====================================================================================
// 0112ccd0  command body: store attribute float
// =====================================================================================
// @ 0x112ccd0
u32 RtCommandHandler::execute(CompiledCmd* cmd)
{
    char* base = *(char**)((char*)cmd->mpThis + 0xc);
    *(float*)(base + cmd->m_a8 * 8) = cmd->m_fc;
    return 0x10;
}

// =====================================================================================
// 0112ccf0  AudioObject::IsCommandComplete
// =====================================================================================
// @ 0x112ccf0
void AudioObject::IsCommandComplete(u32 a, float f)
{
    System* s = mpSystem;
    CompiledCmd* c = (CompiledCmd*)((char*)s->mpCmdBuffer + s->m_b4);
    s->m_b4 += 0x10;
    c->mpFn = (int (__cdecl*)(void*))&RtCommandHandler::execute;
    c->mpThis = this;
    c->m_a8 = a;
    c->m_fc = f;
}

// =====================================================================================
// 0112cd30  NodeList::find
// =====================================================================================
// @ 0x112cd30
Node* NodeList::find(u32 id)
{
    Node* n = m_head;
    while (n != 0)
    {
        Node* base = (Node*)((char*)n - 0x24);
        Node* next = n->pnext;
        if (n->m_id == id)
            return base;
        n = next;
    }
    return 0;
}

// =====================================================================================
// 0112cd60  NodeList::insert
// =====================================================================================
// @ 0x112cd60
Node* NodeList::insert(Node* e)
{
    u32 id = *(u32*)((char*)e + 0x28);
    for (Node* n = m_head; n != 0; n = n->pnext)
    {
        if (n->m_id == id)
            return (Node*)((char*)n - 0x24);
    }

    Node* node = (Node*)((char*)e + 0x24);
    node->pnext = m_head;
    if (m_tail == 0)
        m_tail = node;
    ++m_count;
    m_head = node;
    *(u8*)((char*)e + 0x32) = m_tag;
    ++m_tag;
    return e;
}

// =====================================================================================
// 0112cdb0  allocate an audio node
// =====================================================================================
// @ 0x112cdb0
__declspec(noinline) u32* audio_allocNode(System* sys)
{
    u32* p = (u32*)sys->Alloc(0x18, 0, 0x10, 0);
    if (p != 0)
    {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        *(u8*)(p + 5) = 0;
        p[4] = (u32)sys;
        return p;
    }
    return 0;
}

// =====================================================================================
// 0112cdf0  AllocNode::freeSelf
// =====================================================================================
// @ 0x112cdf0
void AllocNode::freeSelf()
{
    System* s = (System*)*(void**)((char*)this + 0x10);
    s->Free(this, 0);
}

// =====================================================================================
// 0112ce00  VoiceList::getOrCreate
// =====================================================================================
// @ 0x112ce00
void* VoiceList::getOrCreate()
{
    if (m_a28 == 0)
        m_a28 = audio_allocNode(g_audioSystem);
    return m_a28;
}
