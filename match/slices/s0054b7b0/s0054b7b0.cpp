// Slice s0054b7b0: SP::Pollen::cAssetMetadataResourceFactory::WriteResource
// Serializes a cAssetMetadata to an EA::IO writer. Module flags:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------- externals
bool  WriteU32(void* writer, const void* p, int n, int flags);   // EA::IO::WriteUint32
bool  FUN_0093ab10(void* writer, const void* p, int n, int flags); // writes 8 bytes
void* FUN_00554140(int a);                                        // 0x554140
void* FUN_00550880();                                             // 0x550880
void* FUN_00414e10(int n);                                        // 0x414e10
void* FUN_005508c0(int n);                                        // 0x5508c0

struct IMeta {
    virtual void Init();      // vtable slot 0
    virtual void Delete();    // vtable slot 1
};
struct IObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void* GetWriter();  // vtable slot 6
};
struct IWriter {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual bool WriteBytes(const void* p, int n);  // vtable slot 14 (0x38)
};

// @ 0x0054b7b0
bool FUN_0054b7b0(int param_1, IObj* param_2, int* param_3, int param_4)
{
    bool ok;
    if (param_4 != 0x30bdee3) return false;
    int* m = (int*)FUN_00554140(param_1);
    if (m != 0) ((IMeta*)m)->Init();
    IWriter* w = (IWriter*)param_2->GetWriter();

    { int v = 0xd; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[6]; v[1] = m[7]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v = m[9]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[10]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[8]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xc]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xd]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = m[0xb]; ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0xe]; v[1] = m[0xf]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x10]; v[1] = m[0x11]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x12]; v[1] = m[0x13]; ok = FUN_0093ab10(w, v, 1, 0); }
    if (ok) { int v[2]; v[0] = m[0x14]; v[1] = m[0x15]; ok = FUN_0093ab10(w, v, 1, 0); }

    if (param_3 == 0) {
        if (ok) { int v = 0; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v[2]; v[0] = m[0x1a]; v[1] = m[0x1b]; ok = FUN_0093ab10(w, v, 1, 0); }
        void* str = FUN_00550880();
        int len;
        { uint16_t* p = (uint16_t*)str; while (*p) p++; len = (int)((char*)p - ((char*)str + 2)) >> 1; }
        if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
        if (ok) ok = w->WriteBytes(str, len << 1);
        int len2 = (m[0x1f] - m[0x1e]) >> 1;
        if (!(ok && len2 < 0x100)) ok = false;
        if (ok) { int v = len2; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { void* b = FUN_00414e10(len2 << 1); ok = w->WriteBytes(b, len2 << 1); }
        int len3 = (m[0x23] - m[0x22]) >> 1;
        if (!(ok && len3 < 0x1000)) ok = false;
        if (ok) { int v = len3; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { void* b = FUN_005508c0(len3 << 1); ok = w->WriteBytes(b, len3 << 1); }
    } else {
        if (ok) { int v = 0xffffffff; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[0]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[3]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[1]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[2]; ok = WriteU32(w, &v, 1, 0); }
    }

    if (ok) { int v = (m[0x27] - m[0x26]) >> 4; ok = WriteU32(w, &v, 1, 0); }
    int* p1 = (int*)m[0x26];
    int* e1 = (int*)m[0x27];
    for (; p1 != e1; p1 = p1 + 4) {
        int len = p1[1] - p1[0];
        if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
        if (ok) ok = w->WriteBytes((const void*)p1[0], len);
    }

    if (param_3 == 0 || param_3[4] == 0) {
        if (ok) { int v = 0; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = (m[0x2c] - m[0x2b]) >> 4; ok = WriteU32(w, &v, 1, 0); }
        int* p2 = (int*)m[0x2b];
        int* e2 = (int*)m[0x2c];
        for (; ok && p2 != e2; p2 = p2 + 4) {
            int len = (p2[1] - p2[0]) >> 1;
            if (ok) { int v = len; ok = WriteU32(w, &v, 1, 0); }
            if (ok) ok = w->WriteBytes((const void*)p2[0], len << 1);
        }
    } else {
        if (ok) { int v = 0xffffffff; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[4]; ok = WriteU32(w, &v, 1, 0); }
        if (ok) { int v = param_3[5]; ok = WriteU32(w, &v, 1, 0); }
    }

    if (ok) { int v = -((int)((char)m[0x1d] != 0)); ok = WriteU32(w, &v, 1, 0); }
    if (ok) { int v = (m[0x31] - m[0x30]) >> 2; ok = WriteU32(w, &v, 1, 0); }
    int* p3 = (int*)m[0x30];
    int* e3 = (int*)m[0x31];
    for (;;) {
        if (!ok || p3 == e3) {
            bool result = ok;
            if (m != 0) ((IMeta*)m)->Delete();
            return result;
        }
        if (ok) { int v = *p3; ok = WriteU32(w, &v, 1, 0); }
        p3 = p3 + 1;
    }
}
