// Slice s0046f2a0: SP::EditorUtils::DumpZPR (0x0046f2a0) and DumpZPR_M0 (0x0046f8a0).
// DumpZPR writes a ZPR ("Spore Baked Texture") file for a set of editor models: a header chunk (via
// DumpZPR_M0 = model geometry stream), the baked sprite texture as a chunk, "sporelicious.raw" as a debug
// dump, then the triangle/UV chunks (ExportModelTriangles, 0x0046ff00).
// Built unoptimized: /Od /Ob1 /arch:SSE /MD /Gy /TP (same module as s0046ff00).
#include "types.h"
#include <stdio.h>
#include <stddef.h>

void* operator new[](unsigned, const char*, int, int, int, int);   // 0x00f473a0
void operator delete[](void*);                                       // 0x00f47380

struct Stream {                 // vertex/index stream
    int count;                  // +0x00
    char* data;                 // +0x04
    uint16_t format;            // +0x08
    uint16_t stride;            // +0x0A
    int unk0c;                  // +0x0C
};

struct ModelStreamEntry {
    uint32_t pad[4];
    Stream stream;              // +0x10
};

struct StreamRef {
    short stream;
    short remap;
};

struct StreamVector {           // eastl::vector<Stream>, 0x10 bytes
    Stream* mpBegin;
    Stream* mpEnd;
    Stream* mpCapacity;
    int mAllocator;
    bool empty() const;                                 // 0x00526430 (out of line)
    Stream& operator[](int i) { return mpBegin[i]; }
};

struct Mesh {                   // 0x8C bytes
    Stream mIndices;            // +0x00
    uint32_t pad10;             // +0x10
    StreamRef* mStreamMap;      // +0x14
    uint32_t pad18[(0x44 - 0x18) / 4];
    StreamVector mRemaps;       // +0x44
    uint32_t pad54[(0x8c - 0x54) / 4];
};

struct MeshVector {
    Mesh* mpBegin;
    Mesh* mpEnd;
    Mesh* mpCapacity;
    int mAllocator;
    int size() const { return mpEnd - mpBegin; }
    Mesh& operator[](int i) { return mpBegin[i]; }
};

struct Model {
    uint32_t pad00[2];
    ModelStreamEntry* mStreams; // +0x08
    uint32_t pad0c[(0x1c - 0xc) / 4];
    MeshVector mMeshes;         // +0x1C
};

// cdecl callees
void __cdecl FUN_00733ed0(Model* m);                                   // 0x00733ed0
void __cdecl CreateClustersAndEdges(Model* m, int flag);               // 0x00735470 (cMeshClusterer::CreateClustersAndEdges)
Stream* __cdecl FUN_0071de40(Model* m, int a, int b, int c, int d);    // 0x0071de40 (returns the model's vertex-position stream)
bool __cdecl FindMeshStreams(Model* model, int meshIndex, int count, int* semantics, int* usageIndex,
                             int* formats, int* outIdx);               // 0x0071e110

// eastl::vector<intrusive_ptr<Model>> as a by-value parameter (0x14 bytes)
struct RefVector {
    Model** mpBegin;
    Model** mpEnd;
    Model** mpCapacity;
    int d3, d4;
    RefVector(const RefVector& o);                      // 0x0041eae0
    ~RefVector();                                       // 0x0041eb80
    Model*& operator[](int i) { return mpBegin[i]; }
};

// eastl::fixed_vector<int,16> (0x58 bytes)
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    ~VectorBase();                                      // 0x004c0b80
};
struct __declspec(align(4)) IntVector : VectorBase<int> {
    int mAllocFlags;
    int* mpBuf;
    int mAllocPad;
    int mBuffer[16];
    IntVector();                                        // 0x0041cfe0
    ~IntVector() { for (int* p = mpBegin; p < mpEnd; ++p) {} }
    void push_back(const int& v);                       // 0x00422380
};

// eastl::basic_string<char> with the shared empty-string sentinel
extern char gEmptyStr8[];                               // 0x01667bac
struct EStr {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAllocator;
    EStr() : mpBegin(0), mpEnd(0), mpCapacity(0) { mpBegin = gEmptyStr8; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    const char* c_str() const { return mpBegin; }
    ~EStr();                                            // 0x00530670
    int sprintf(const char* fmt, ...);                  // 0x00472fe0 (cdecl, this pushed first)
};

// The baked sprite texture description handed to DumpZPR
struct SpriteTexture {
    char pad0[0xc];
    uint16_t mWidth;            // +0x0C
    uint16_t mHeight;           // +0x0E
    uint8_t mBitsPerPixel;      // +0x10
    char pad11[0x13 - 0x11];
    uint16_t GetWidth() const { return mWidth; }
    uint16_t GetHeight() const { return mHeight; }
    uint8_t GetBitsPerPixel() const { return mBitsPerPixel; }
    int __thiscall FillSpriteTexture(void* pixels, unsigned int bytes, int zero);   // 0x011f0440
};

void ExportModelTriangles(FILE* file, RefVector models, const int& triangleCount,
                          const IntVector& vertexBase, const IntVector& triangleBase, bool perModelID);  // 0x0046ff00
void DumpZPR_M0(FILE* file, RefVector models, int& triangleCount, IntVector& vertexBase,
                IntVector& triangleBase);                                                        // 0x0046f8a0

extern "C" size_t __cdecl strlen(const char*);
#pragma intrinsic(strlen)

// @ 0x0046f2a0
bool DumpZPR(RefVector meshesIn, SpriteTexture* tex, const wchar_t* fullPath)
{
    const char* kZPRTextureName = "Spore Baked Texture";
    unsigned int textureNameLen = strlen(kZPRTextureName);
    char kZPRTextureMapsBlockType = 0x1e;
    int numPrimTris = 0;
    int blockSize;
    IntVector vertOffsets;
    IntVector primOffsets;
    EStr fullPath8;
    fullPath8.sprintf("%ls", fullPath);
    FILE* f = fopen(fullPath8.c_str(), "wb");
    if (f) {
        DumpZPR_M0(f, meshesIn, numPrimTris, vertOffsets, primOffsets);
        if (tex) {
            int height = tex->GetHeight();
            int width = tex->GetWidth();
            char kZPRRepeatFlag = 1;
            int numTextures = 1;
            blockSize = (textureNameLen + width * 3 * height + 0xe) * numTextures + 9;
            fwrite(&kZPRTextureMapsBlockType, 1, 1, f);
            fwrite(&blockSize, 1, 4, f);
            fwrite(&numTextures, 1, 4, f);
            fwrite(&textureNameLen, 1, 4, f);
            fwrite(kZPRTextureName, textureNameLen, 1, f);
            fwrite(&width, 1, 4, f);
            fwrite(&height, 1, 4, f);
            fwrite(&kZPRRepeatFlag, 1, 1, f);
            fwrite(&kZPRRepeatFlag, 1, 1, f);
            int bytes = width * height * tex->GetBitsPerPixel() / 8;
            unsigned char* pixels = new("Editor", 0, 0, 0, 0) unsigned char[bytes];
            if (pixels) {
                if (tex->FillSpriteTexture(pixels, bytes, 0)) {
                    FILE* f2 = fopen("sporelicious.f2", "wb");
                    if (f2) {
                        for (int y = 0; y < height; y++) {
                            for (int x = 0; x < width; x++) {
                                unsigned char* px = pixels + (y * width + x) * 4;
                                unsigned char r = px[0];
                                unsigned char g = px[1];
                                unsigned char cb = px[2];
                                fwrite(&cb, 1, 1, f2);
                                fwrite(&g, 1, 1, f2);
                                fwrite(&r, 1, 1, f2);
                            }
                        }
                        fclose(f2);
                    }
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            unsigned char* px = pixels + (y * width + x) * 4;
                            unsigned char r = px[0];
                            unsigned char g = px[1];
                            unsigned char cb = px[2];
                            fwrite(&cb, 1, 1, f);
                            fwrite(&g, 1, 1, f);
                            fwrite(&r, 1, 1, f);
                        }
                    }
                }
            }
            if (pixels) {
                delete[] pixels;
            }
        }
        ExportModelTriangles(f, meshesIn, numPrimTris, vertOffsets, primOffsets, false);
    }
    return true;
}

// @ 0x0046f8a0
void DumpZPR_M0(FILE* f, RefVector meshesIn, int& numPrimTris, IntVector& vertOffsets,
                IntVector& primOffsets)
{
    int ptSemantics[2] = { 1, 8 };
    int ptTypes[2] = { 3, 2 };
    int ptNumbers[2] = { 0, 0 };
    char kZPRFormat = (char)0xaa;
    char kZPRVersion = 1;
    const char* kZPRComment = "Created by Spore Editor";
    char kZPRColorMode = 2;
    char kZPRTextureMode = 2;
    char kZPRScaleBlockType = 0x3c;
    char kZPRVerticesBlockType = 0xa;
    float kZPRDefaultScale = 1.0f;
    char kZPRNullColor = 0;
    char kZPRFF = (char)0xff;
    int kZPRNullTexIndex = -1;
    unsigned int commentLen = strlen(kZPRComment);
    fwrite(&kZPRFormat, 1, 1, f);
    fwrite(&kZPRVersion, 1, 1, f);
    fwrite(&commentLen, 1, 4, f);
    fwrite(kZPRComment, commentLen, 1, f);
    fwrite(&kZPRColorMode, 1, 1, f);
    fwrite(&kZPRTextureMode, 1, 1, f);
    fwrite(&kZPRScaleBlockType, 1, 1, f);
    int blockSize = 9;
    fwrite(&blockSize, 1, 4, f);
    fwrite(&kZPRDefaultScale, 1, 4, f);
    int numVerts = 0;
    for (int i = 0, numMeshes = meshesIn.mpEnd - meshesIn.mpBegin; i < numMeshes; i++) {
        Model* mesh = meshesIn[i];
        FUN_00733ed0(mesh);
        CreateClustersAndEdges(mesh, 1);
        vertOffsets.push_back(numVerts);
        Stream* positions = FUN_0071de40(mesh, 1, 0, 3, 0xe);
        numVerts += positions->count;
        primOffsets.push_back(numPrimTris);
        for (int s = 0, ns = mesh->mMeshes.size(); s < ns; s++) {
            int formatIndices[2];
            if (FindMeshStreams(mesh, s, 2, ptSemantics, ptNumbers, ptTypes, formatIndices)) {
                Stream* pos = &mesh->mStreams[mesh->mMeshes[s].mStreamMap[formatIndices[0]].stream].stream;
                Stream* uv = &mesh->mStreams[mesh->mMeshes[s].mStreamMap[formatIndices[1]].stream].stream;
                Stream* posRemap = !mesh->mMeshes[s].mRemaps.empty()
                    ? &mesh->mMeshes[s].mRemaps[mesh->mMeshes[s].mStreamMap[formatIndices[0]].remap] : NULL;
                Stream* uvRemap = !mesh->mMeshes[s].mRemaps.empty()
                    ? &mesh->mMeshes[s].mRemaps[mesh->mMeshes[s].mStreamMap[formatIndices[1]].remap] : NULL;
                Stream* indices = mesh->mMeshes[s].mIndices.data == NULL ? NULL : &mesh->mMeshes[s].mIndices;
                numPrimTris += (indices ? indices->count : pos->count) / 3;
                (void)uv;
                (void)posRemap;
                (void)uvRemap;
            }
        }
    }
    blockSize = numVerts * 0x13 + 5;
    fwrite(&kZPRVerticesBlockType, 1, 1, f);
    fwrite(&blockSize, 1, 4, f);
    for (int i = 0, numMeshes = meshesIn.mpEnd - meshesIn.mpBegin; i < numMeshes; i++) {
        Model* mesh = meshesIn[i];
        Stream* positions = FUN_0071de40(mesh, 1, 0, 3, 0xe);
        int n = positions->count;
        for (int v = 0; v < n; v++) {
            fwrite(positions->data + positions->stride * v, 1, 0xc, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullTexIndex, 1, 4, f);
        }
    }
    (void)kZPRFF;
}
