
#include "types.h"

#define PV(n) virtual void pv##n();

struct ISpatialObject {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    PV(24) PV(25) PV(26) PV(27)
    PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43)
    PV(44) PV(45)

    virtual void* AsInterface(unsigned int id);
};

struct IStreamInner {
    PV(0) PV(1) PV(2)
    PV(3) PV(4) PV(5)

    virtual void* GetWriter();
};

struct IStreamWrite {
    PV(0) PV(1) PV(2) PV(3)
    PV(4) PV(5) PV(6)

    virtual void EndSequence();
    virtual IStreamInner* GetStream();

    PV(9) PV(10)

    virtual void WriteObject(void* object);
};

struct SpatialObjectVector {
    ISpatialObject** mpBegin;
    ISpatialObject** mpEnd;
    ISpatialObject** mpCapacity;
};

bool __cdecl WriteUint32(
    void* stream,
    const unsigned int* value,
    unsigned int count,
    int flags
);

// Keep the count as a by-value parameter.
// Obtain the writer inside the same inline operation.
__forceinline void WriteCount(
    IStreamInner* inner,
    unsigned int count
)
{
    void* writer = inner->GetWriter();
    WriteUint32(writer, &count, 1, 0);
}

// @ 0x00c43790
void __cdecl WriteSTLSequenceT(
    IStreamWrite* stream,
    SpatialObjectVector* objects
)
{
    unsigned int count =
        (unsigned int)(objects->mpEnd - objects->mpBegin);

    IStreamInner* inner = stream->GetStream();

    WriteCount(inner, count);

    ISpatialObject** current = objects->mpBegin;
    ISpatialObject** end = objects->mpEnd;

    while (current != end) {
        ISpatialObject* object = *current;
        void* value = 0;

        if (object) {
            value = object->AsInterface(0x0179C807);
        }

        stream->WriteObject(value);
        ++current;
    }

    stream->EndSequence();
}
