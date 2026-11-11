// hkMoppCode cleanup isolated from the mixed-toolchain _at_010f0000.cpp.
// Flags: /vc71 /O2 /MD /Gy /TP.
#include "game/types.h"
#include <stddef.h>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern uint32_t g_hkThreadMemoryTls; // 0x016e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(uint32_t index);

class hkThreadMemory {
public:
    void deallocateChunk(void* data, int size, int memoryClass); // 0x0107db10
};

struct hkMoppCodeCodeInfo {
    float m_offset[4];
};

// Retail field view from Havok reflection and MoppCodeWriter::getCode.
// The inherited vptr is explicit; no replacement C++ vtable is emitted here.
class hkMoppCode {
public:
    void* m_vtable;                         // +0x00
    uint16_t m_memSizeAndFlags;             // +0x04
    int16_t m_referenceCount;               // +0x06
    uint32_t m_pad08[2];                    // +0x08
    hkMoppCodeCodeInfo m_info;              // +0x10
    struct ByteArray {
        uint8_t* m_data;
        int m_size;
        int m_capacityAndFlags;
    } m_data;                              // +0x20; hkArray<hkUint8>
    uint32_t m_pad2c;                       // +0x2c

    ~hkMoppCode();
};

typedef char hkMoppCodeSizeCheck[(sizeof(hkMoppCode) == 0x30) ? 1 : -1];
typedef char hkMoppCodeArrayOffsetCheck[(offsetof(hkMoppCode, m_data) == 0x20) ? 1 : -1];

// @ 0x010f0120
hkMoppCode::~hkMoppCode()
{
    m_vtable = (void*)0x014a59b4;
    _ReadWriteBarrier();
    if ((m_data.m_capacityAndFlags & 0x80000000u) == 0) {
        hkThreadMemory* memory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        memory->deallocateChunk(m_data.m_data, m_data.m_capacityAndFlags & 0x3fffffff, 0x14);
    }
    m_vtable = (void*)0x013ef094;
}
