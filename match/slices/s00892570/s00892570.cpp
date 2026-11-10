// Slice s00892570 -- EA::Text::PolygonFont stream helper.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---- stand-in classes -------------------------------------------------------
struct MemoryStream_0093c2c0 {
    uint32_t mData[0x24 / 4];                  // +0x00 .. +0x23

    MemoryStream_0093c2c0(void* pData, unsigned int nSize, int a, int b,
                          void* pName, const char* pFile);   // 0x0093c2c0
    void Destroy();                                          // 0x0093bde0
};

struct PolygonFont_00892570 {
    char    pad_000[0x16c];                    // +0x000 .. +0x16b
    void*   mp16c;                             // +0x16c

    bool ReadStream(void* pData, unsigned int nSize);        // 0x00892570
};

// @ 0x00892570
bool PolygonFont_00892570::ReadStream(void* pData, unsigned int nSize)
{
    MemoryStream_0093c2c0 stream(pData, nSize, 1, 0, mp16c, "EAText/PolygonFont");
    bool ok = ((bool (__thiscall*)(void*, void*))(*(void***)this)[0x60 / 4])(this, &stream);
    stream.Destroy();
    return ok;
}
