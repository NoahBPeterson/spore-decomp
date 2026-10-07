// Slice s0046ff00: editor-model collision/triangle exporter (writes a chunked binary file:
// a 0x14 "triangle" chunk of position indices and a 0x32 "uv" chunk, then closes the file).
// Built unoptimized: /Od /Ob1 /arch:SSE /MD /Gy /TP (no /EHsc: the by-value vector parameter
// is destroyed at the end without an EH frame).
#include "types.h"
#include <stdio.h>

extern uint32_t gIndexMask[];   // 0x013EEC84: per-stream-format index mask (0xff, 0xffff, ...)

// A vertex/index stream: element i lives at data + stride*i.
struct Stream {
    int count;          // +0x00
    char* data;         // +0x04
    uint16_t format;    // +0x08 (index into gIndexMask)
    uint16_t stride;    // +0x0A
    int unk0c;          // +0x0C
};

struct ModelStreamEntry {
    uint32_t pad[4];
    Stream stream;      // +0x10
};

struct StreamRef {
    short stream;       // index into Model::mStreams
    short remap;        // index into Mesh::mRemaps
};

struct StreamVector {   // eastl::vector<Stream>
    Stream* mpBegin;
    Stream* mpEnd;
    Stream* mpCapacity;
    int mAllocator;
    bool empty() const;                                  // 0x00526430 (out of line)
    Stream& operator[](int i) { return mpBegin[i]; }
};

struct Mesh {           // 0x8C bytes
    Stream mIndices;            // +0x00
    uint32_t pad10;             // +0x10
    StreamRef* mStreamMap;      // +0x14
    uint32_t pad18[(0x44 - 0x18) / 4];
    StreamVector mRemaps;       // +0x44
    uint32_t pad54[(0x8c - 0x54) / 4];
};

struct MeshVector {     // eastl::vector<Mesh>
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

// cdecl 0x0071E110: find the mesh's streams for the requested semantics; outIdx[k] indexes mStreamMap.
bool FindMeshStreams(Model* model, int meshIndex, int count, int* semantics, int* usageIndex,
                     int* formats, int* outIdx);

struct ModelRefVector {  // eastl::vector<intrusive_ptr<Model>>, passed by value
    Model** mpBegin;
    Model** mpEnd;
    Model** mpCapacity;
    int mAllocator;
    ~ModelRefVector();                                   // 0x0041EB80 (RefVector::~RefVector)
    int size() const { return mpEnd - mpBegin; }
    Model*& operator[](int i) { return mpBegin[i]; }
};

struct IntVector {       // eastl::vector<int>
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int mAllocator;
};

struct Vector2 {
    float x, y;
    Vector2(const Vector2& o) { x = o.x; y = o.y; }
};

static inline uint32_t ReadIndex(Stream* s, uint32_t i)
{
    return *(uint32_t*)(s->data + s->stride * i) & gIndexMask[s->format];
}

// @ 0x0046ff00
void ExportModelTriangles(FILE* file, ModelRefVector models, int unused, const int& triangleCount,
                          const IntVector& vertexBase, const IntVector& triangleBase, bool perModelID)
{
    int semantics[2] = { 1, 8 };
    int formats[2] = { 3, 2 };
    int usage[2] = { 0, 0 };
    char chunkTris = 0x14;
    char zero = 0;
    char chunkEnd = 0x28;
    char chunkUVs = 0x32;
    int modelID = 0;

    int chunkSize = triangleCount * 0x13 + 5;
    fwrite(&chunkTris, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    for (int m = 0, nModels = models.size(); m < nModels; m++) {
        Model* model = models[m];
        for (int i = 0, nMeshes = model->mMeshes.size(); i < nMeshes; i++) {
            int idx[2];
            if (FindMeshStreams(model, i, 2, semantics, usage, formats, idx)) {
                Stream* pos = &model->mStreams[model->mMeshes[i].mStreamMap[idx[0]].stream].stream;
                Stream* uv = &model->mStreams[model->mMeshes[i].mStreamMap[idx[1]].stream].stream;
                Stream* posRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[0]].remap] : NULL;
                Stream* uvRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[1]].remap] : NULL;
                Stream* indices = model->mMeshes[i].mIndices.data == NULL ? NULL : &model->mMeshes[i].mIndices;
                int nTris = (indices ? indices->count : pos->count) / 3;
                uint32_t next = 0;
                for (int t = 0; t < nTris; t++) {
                    uint32_t a = next++;
                    uint32_t b = next++;
                    uint32_t c = next++;
                    if (indices) {
                        a = ReadIndex(indices, a);
                        b = ReadIndex(indices, b);
                        c = ReadIndex(indices, c);
                    }
                    if (posRemap) {
                        a = ReadIndex(posRemap, a);
                        b = ReadIndex(posRemap, b);
                        c = ReadIndex(posRemap, c);
                    }
                    a += vertexBase.mpBegin[m];
                    b += vertexBase.mpBegin[m];
                    c += vertexBase.mpBegin[m];
                    int tri = t + triangleBase.mpBegin[m];
                    fwrite(&a, 1, 4, file);
                    fwrite(&b, 1, 4, file);
                    fwrite(&c, 1, 4, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&tri, 1, 4, file);
                }
                (void)uv;
                (void)uvRemap;
            }
        }
    }

    chunkSize = 5;
    fwrite(&chunkEnd, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    chunkSize = triangleCount * 0x1c + 5;
    fwrite(&chunkUVs, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    for (int m = 0, nModels = models.size(); m < nModels; m++) {
        Model* model = models[m];
        if (perModelID)
            modelID = m;
        for (int i = 0, nMeshes = model->mMeshes.size(); i < nMeshes; i++) {
            int idx[2];
            if (FindMeshStreams(model, i, 2, semantics, usage, formats, idx)) {
                Stream* pos = &model->mStreams[model->mMeshes[i].mStreamMap[idx[0]].stream].stream;
                Stream* uv = &model->mStreams[model->mMeshes[i].mStreamMap[idx[1]].stream].stream;
                Stream* posRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[0]].remap] : NULL;
                Stream* uvRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[1]].remap] : NULL;
                Stream* indices = model->mMeshes[i].mIndices.data == NULL ? NULL : &model->mMeshes[i].mIndices;
                int nTris = (indices ? indices->count : uv->count) / 3;
                uint32_t next = 0;
                for (int t = 0; t < nTris; t++) {
                    uint32_t a = next++;
                    uint32_t b = next++;
                    uint32_t c = next++;
                    if (indices) {
                        a = ReadIndex(indices, a);
                        b = ReadIndex(indices, b);
                        c = ReadIndex(indices, c);
                    }
                    if (uvRemap) {
                        a = ReadIndex(uvRemap, a);
                        b = ReadIndex(uvRemap, b);
                        c = ReadIndex(uvRemap, c);
                    }
                    Vector2 uvA = *(Vector2*)(uv->data + uv->stride * a);
                    Vector2 uvB = *(Vector2*)(uv->data + uv->stride * b);
                    Vector2 uvC = *(Vector2*)(uv->data + uv->stride * c);
                    fwrite(&modelID, 1, 4, file);
                    fwrite(&uvA.x, 1, 4, file);
                    fwrite(&uvB.x, 1, 4, file);
                    fwrite(&uvC.x, 1, 4, file);
                    fwrite(&uvA.y, 1, 4, file);
                    fwrite(&uvB.y, 1, 4, file);
                    fwrite(&uvC.y, 1, 4, file);
                }
                (void)pos;
                (void)posRemap;
            }
        }
    }

    fclose(file);
}
