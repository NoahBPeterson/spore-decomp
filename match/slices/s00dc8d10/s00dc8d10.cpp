// 0x00dc8d10..0x00dc9765 -- SP::cMovingFormation per-tick vehicle handling
// (SPGonzago).  The block holds the formation's hash table copy-assignment, a
// large tick routine, an anonymous-namespace repark attempt, the repark tick
// wrapper and a couple of AutoRefCount list helpers.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"
#include <new>

struct CVehicle
{
    /* 000h */ uint8_t  mPad_000[0x2a4];
    /* 2a4h */ uint32_t mFlags_2a4;    // bit 1 = repark pending, bit 2 = reparked

    void OnMoveTick();                 // 0x00cacbe0
};

void AttemptRepark(CVehicle* pVeh);    // 0x00dc9430

// ---------------------------------------------------------------------------
// 0x00dc95b0: per-tick wrapper -- repark if bit 1 is set, otherwise let the
// normal move tick run when bit 2 is set.
// ---------------------------------------------------------------------------
// @ 0x00dc95b0
bool StandardVehicleMoveTick(CVehicle* pVeh)
{
    if (pVeh->mFlags_2a4 & 2)
    {
        AttemptRepark(pVeh);
        return true;
    }
    if (pVeh->mFlags_2a4 & 4)
        pVeh->OnMoveTick();
    return true;
}

// ---------------------------------------------------------------------------
// Ref-counted handle used by the locomotive list.
// ---------------------------------------------------------------------------
struct IRefCounted
{
    virtual void AddRef();
    virtual void Release();
};

struct AutoRefCount
{
    /* 000h */ IRefCounted* mpObject;

    AutoRefCount(IRefCounted* pObject) : mpObject(pObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    AutoRefCount(const AutoRefCount& other) : mpObject(other.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
};

// ---------------------------------------------------------------------------
// Growable pointer vector with out-of-line overflow insert.
// ---------------------------------------------------------------------------
template<class T>
class SPVector
{
public:
    /* 000h */ T* mpBegin;
    /* 004h */ T* mpEnd;
    /* 008h */ T* mpCapacity;

    void DoInsertPtr(T* pPos, const T& x);      // 0x00aea5d0

    void push_back(const T& x)
    {
        if (mpEnd < mpCapacity)
        {
            T* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                new (p) T(x);
        }
        else
        {
            DoInsertPtr(mpEnd, x);
        }
    }
};

SPVector<AutoRefCount> gLocomotiveList;         // 0x016a0058

// ---------------------------------------------------------------------------
// 0x00dc9680: push a locomotive onto the ready list, holding a reference for
// the duration of the insertion.
// ---------------------------------------------------------------------------
// @ 0x00dc9680
void FUN_00dc9680(IRefCounted* pObject)
{
    AutoRefCount ref(pObject);
    gLocomotiveList.push_back(ref);
}