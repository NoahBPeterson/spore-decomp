// Slice s00f9ee90 -- copy a w x w 16-bit image layer into the rectangle [left,right) x [top,bottom)
// of a locked surface (0x00f9f200). Fractional rect bounds are floored after scaling by w.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct LockInfo {                      // 7 dwords written by Surface::Lock; data pointer at +0
    void* data;
    int   rest[6];
};

class Surface {
public:
    bool Lock(int flags, int zero, LockInfo* out);   // 0x011ef750 (thiscall, ret 0xc)
    void Unlock(LockInfo* out);                      // 0x011ef880 (thiscall, ret 4)
};

struct SrcImage {
    char  pad0[8];
    int   width;                       // +8
    char  pad1[4];
    char* data;                        // +0x10
};

// Floor for a float via round-to-nearest cvtss2si, corrected down when it rounded up (cmovb).
#pragma warning(disable : 4035)   // FloorF returns through eax
static __forceinline int FloorF(float x) {
    __asm {
        movss   xmm0, x
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov     ecx, eax
        sub     ecx, 1
        ucomiss xmm0, xmm1
        cmovb   eax, ecx
    }
}

bool __cdecl CopyImageRectToSurface(Surface* a1, const SrcImage* p2, int p3, const float* p4) {
    LockInfo out;
    bool ok = false;
    if (a1->Lock(2, 0, &out)) {

    int w = p2->width;
    float fw = (float)w;
    int left   = FloorF(p4[0] * fw);
    int right  = FloorF(p4[2] * fw);
    int top    = FloorF(p4[1] * fw);
    int bottom = FloorF(p4[3] * fw);

    char* srcBase = p2->data + (w * w * p3) * 2;
    char* dstBase = (char*)out.data;

    if (top < bottom) {
        int rows = bottom - top;
        short* dst = (short*)dstBase + (top * w + left);
        int stride = w * 2;
        do {
            if (left < right) {
                int n = right - left;
                char* d = (char*)dst;
                do {
                    *(short*)d = *(short*)(d + (srcBase - dstBase));
                    d += 2;
                    n = n - 1;
                } while (n != 0);
            }
            dst = (short*)((char*)dst + stride);
            rows = rows - 1;
        } while (rows != 0);
    }

    a1->Unlock(&out);
        return true;
    }
    return ok;
}
