// scratch: spellings of the 0xad5ec0 ctor (not compiled by the manifest)
typedef unsigned char byte;
struct Vec3 { float x, y, z; };
struct ResKey { unsigned a, b, c; };
struct IntVec { void* begin; void* end; void* cap; };
extern char vtbl_ResBase[];
extern char vtbl_ResRefCount[];
extern char vtbl_RefCountBase[];
extern char vtbl_VigInfo[];
extern char vtbl_RefCountV[];
extern float g_v4bc;
extern float g_v4c0;
extern float g_v4c4;
char* __fastcall ResCtor30(char* self);

struct VigInfo0 {
    virtual int v0(); virtual int v1();
    int   mRef;      // +0x08
    int   mHash;     // +0x0c
    IntVec mVec10;   // +0x10
    char  mPad1c[0x5c];  // +0x1c .. +0x70
    int   mF78;      // +0x78
    int   mFourCC;   // +0x7c
};

// @ 0x00ad5ec0
VigInfo0* __fastcall VA(VigInfo0* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_ResBase;
    *(void**)(self + 4) = (void*)&vtbl_ResRefCount;
    *(int*)(self + 0xc) = 0;
    *(void**)(self + 0x10) = self + 0x28;
    *(void**)(self + 0x14) = self + 0x28;
    *(int*)(self + 0x24) = 0;
    *(void**)(self + 0x18) = (char*)*(void**)(self + 0x10) + 8;
    ResCtor30((char*)*(void**)(self + 0x18));
    *(int*)(self + 0x78) = 0;
    *(int*)(self + 0x7c) = 3;
    return p;
}

// @ 0x00ad5ec0
VigInfo0* __fastcall VB(VigInfo0* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_ResBase;
    *(void**)(self + 4) = (void*)&vtbl_ResRefCount;
    *(int*)(self + 0xc) = 0;
    *(void**)(self + 0x10) = self + 0x28;
    *(void**)(self + 0x14) = self + 0x28;
    *(int*)(self + 0x24) = 0;
    ResCtor30(self + 0x30);
    *(int*)(self + 0x78) = 0;
    *(int*)(self + 0x7c) = 3;
    return p;
}

// @ 0x00ad5ec0
VigInfo0* __fastcall VC(VigInfo0* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_ResBase;
    *(void**)(self + 4) = (void*)&vtbl_ResRefCount;
    *(int*)(self + 0xc) = 0;
    ResCtor30(self + 0x30);
    *(void**)(self + 0x10) = self + 0x28;
    *(void**)(self + 0x14) = self + 0x28;
    *(int*)(self + 0x24) = 0;
    *(void**)(self + 0x18) = self + 0x30;
    *(int*)(self + 0x78) = 0;
    *(int*)(self + 0x7c) = 3;
    return p;
}

struct VigInfo {
    virtual int v0(); virtual int v1();
    int    mRef;      // +0x08
    int    mHash;     // +0x0c
    int    mHash2;    // +0x10
    ResKey mKey;      // +0x14
    Vec3   mPos;      // +0x20
    Vec3   mPos2;     // +0x2c
    int    mI38;      // +0x38
    int    mI3c;      // +0x3c
    int    mI40;      // +0x40
    int    mI44;      // +0x44
    byte   mB48;      // +0x48
    int    mMode;     // +0x4c
    int    mI50;      // +0x50
};

// @ 0x00ad6320
VigInfo* __fastcall KA(VigInfo* p) {
    char* self = (char*)p;
    *(void* volatile*)(self + 4) = (void*)&vtbl_RefCountBase;
    *(int* volatile*)(self + 8) = 0;
    *(void**)self = (void*)&vtbl_VigInfo;
    *(void**)(self + 4) = (void*)&vtbl_RefCountV;
    *(int*)(self + 0x14) = 0;
    *(int*)(self + 0x18) = 0;
    *(int*)(self + 0x1c) = 0;
    *(float*)(self + 0x20) = g_v4bc;
    *(float*)(self + 0x24) = g_v4c0;
    *(float*)(self + 0x28) = g_v4c4;
    *(float*)(self + 0x2c) = g_v4bc;
    *(float*)(self + 0x30) = g_v4c0;
    *(float*)(self + 0x34) = g_v4c4;
    *(int*)(self + 0x38) = 1;
    *(int*)(self + 0x3c) = 0;
    *(int*)(self + 0x40) = 0;
    *(int*)(self + 0x44) = 0;
    *(byte*)(self + 0x48) = 0;
    *(int*)(self + 0x4c) = 3;
    *(int*)(self + 0x50) = -1;
    return p;
}
