// Slice s0120ae50 -- Havok hkMatrix6 helpers, hkUnaryAction/hkBinaryAction, and
// RenderWare DocMessage debug-output helpers.
//
// The hkMatrix6 float kernels (582/260/347/1384 B) and the exception-cleanup
// fragments at 0x0120bcb0..0x0120c360 are recorded as partial; the action and
// formatting functions are reconstructed.
#include "types.h"

extern "C" {
__declspec(dllimport) int __cdecl _vsnprintf(char*, unsigned int, const char*, void*);
__declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
}

void FUN_01086030(void*);          // hkWorld::removeActionImmediately
void* hkReferencedObject_addReference(void*);   // 0x01082590
void  hkWorldObject_removeReference(void*);     // 0x0109ae60
void FUN_011e090c();
void FUN_00680930(void*);
void FUN_00680730(void*);
void FUN_0067e0f0();
void FUN_00472540(void*);
void FUN_00f47410(void*, const char*, int, int, int, int);

#define HK_ARRAY_CAPACITY_MASK 0x3fffffff
void hkArrayUtil_reserveMore(void* a, int elemSize);   // 0x0107f530

template <typename T>
struct hkArray
{
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
    void pushBack(const T& t)
    {
        if (m_size == getCapacity())
            hkArrayUtil_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
};

struct hkEntity
{
    virtual ~hkEntity();
    void addReference();      // 0x01082590
    void removeReference();   // 0x0109ae60
};

struct hkReferencedObject
{
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(void*) const {}
    short m_memSizeAndFlags;   // +4
    short m_referenceCount;    // +6
    hkReferencedObject() { m_referenceCount = 1; }
};

struct hkAction : hkReferencedObject
{
    int m_pad8;                // +8
    int m_padc;                // +0xc
    unsigned int m_userData;   // +0x10
    int m_pad14;               // +0x14
    virtual void getEntities(hkArray<hkEntity*>&) {}
};

struct hkUnaryAction : hkAction
{
    hkEntity* m_entity;        // +0x18
    hkUnaryAction(hkEntity* e, unsigned int u);
    ~hkUnaryAction();
    void getEntities(hkArray<hkEntity*>& out);
    void removeFromWorld();
};

struct hkBinaryAction : hkAction
{
    hkEntity* m_entityA;       // +0x18
    hkEntity* m_entityB;       // +0x1c
    hkBinaryAction(hkEntity* a, hkEntity* b, unsigned int u);
    ~hkBinaryAction();
    void getEntities(hkArray<hkEntity*>& out);
};

// @ 0x0120b890
hkUnaryAction::hkUnaryAction(hkEntity* e, unsigned int u)
{
    m_pad8 = 0;
    m_padc = 0;
    m_userData = u;
    m_pad14 = 0;
    m_entity = e;
    if (e)
        e->addReference();
}

// @ 0x0120b8d0
void hkUnaryAction::removeFromWorld()
{
    if (m_pad8 != 0)
        FUN_01086030(this);
}

// @ 0x0120b8f0
hkUnaryAction::~hkUnaryAction()
{
    if (m_entity)
    {
        hkWorldObject_removeReference(m_entity);
        m_entity = 0;
    }
}

// @ 0x0120b920
void hkUnaryAction::getEntities(hkArray<hkEntity*>& out)
{
    out.pushBack(m_entity);
}

// @ 0x0120b960
hkBinaryAction::hkBinaryAction(hkEntity* a, hkEntity* b, unsigned int u)
{
    m_pad8 = 0;
    m_padc = 0;
    m_userData = u;
    m_pad14 = 0;
    m_entityA = a;
    m_entityB = b;
    if (a)
        a->addReference();
    if (b)
        b->addReference();
}

// @ 0x0120b9c0
hkBinaryAction::~hkBinaryAction()
{
    if (m_entityA)
    {
        hkWorldObject_removeReference(m_entityA);
        m_entityA = 0;
    }
    if (m_entityB)
    {
        hkWorldObject_removeReference(m_entityB);
        m_entityB = 0;
    }
}

// @ 0x0120ba00
void hkBinaryAction::getEntities(hkArray<hkEntity*>& out)
{
    out.pushBack(m_entityA);
    out.pushBack(m_entityB);
}

// @ 0x0120bbf0
void __cdecl f_0120bc40(char* buf, unsigned int size, const char* fmt, void* args);
void f_0120bbf0(const char* fmt, void* va)
{
    char buf[0x100];
    f_0120bc40(buf, 0x100, fmt, va);
    if (buf[0] != 0)
    {
        OutputDebugStringA(buf);
        OutputDebugStringA("\n");
    }
}

// @ 0x0120bc40
void __cdecl f_0120bc40(char* buf, unsigned int size, const char* fmt, void* args)
{
    _vsnprintf(buf, size, fmt, args);
    buf[size - 1] = 0;
}

// ---- partial: not reconstructed -----------------------------------------
void f_0120ae50() {}   // @ 0x0120ae50  hkMatrix6 multiply
void f_0120b0a0() {}   // @ 0x0120b0a0  hkMatrix6 set-mul
void f_0120b1b0() {}   // @ 0x0120b1b0  hkMatrix6 set-transpose
void f_0120b310() {}   // @ 0x0120b310  hkMatrix6::setInvert
void f_0120bb70() {}   // @ 0x0120bb70  rw::DocMessage::Send
void f_0120bcb0() {}   // @ 0x0120bcb0  EH cleanup fragment
void f_0120bd30() {}   // @ 0x0120bd30  EH cleanup fragment
void f_0120be20() {}   // @ 0x0120be20  EH cleanup fragment
void f_0120be90() {}   // @ 0x0120be90  EH cleanup fragment
void f_0120bf00() {}   // @ 0x0120bf00  EH cleanup fragment
void f_0120bfc0() {}   // @ 0x0120bfc0  EH cleanup fragment
void f_0120c0f0() {}   // @ 0x0120c0f0  EH cleanup fragment
void f_0120c2a0() {}   // @ 0x0120c2a0  EH cleanup fragment
void f_0120c330() {}   // @ 0x0120c330  EH cleanup fragment
void f_0120c360() {}   // @ 0x0120c360  EH cleanup fragment
