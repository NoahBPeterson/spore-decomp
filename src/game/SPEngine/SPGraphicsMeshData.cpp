// src/game/SPEngine/SPGraphicsMeshData.cpp -- migrated from slice(s) s0071e390, s0071d550 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMeshData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"

// ---- items of slice s0071e390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; int mAllocPad; int* mpFixed;
    void DoInsertValues(int* position, unsigned n, const int* value);   // 0x0071e870
    void DoInsertValue(int* position, const int& value);               // 0x004558a0
    void reserve(unsigned n);                                          // 0x004e0880
    void resize(unsigned n);                                           // 0x0071ef50
    int* erase(int* first, int* last);                                 // 0x004ce270
    void push_back(const int& v)
    {
        if (mpEnd < mpCapacity) {
            int* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct Prim14 {                     // 0x14 bytes
    int mType;                      // +0x00
    int mEntry;                     // +0x04
    int mStart;                     // +0x08
    int mEnd;                       // +0x0c
    int mAux;                       // +0x10
};
struct Mesh {
    char pad_00[8];
    char* mpVertBegin;              // +0x08  (Vertex20)
    char* mpVertEnd;                // +0x0c
    char pad_10[0x1c - 0x10];
    char* mpEntryBegin;             // +0x1c  (Entry8c)
    char* mpEntryEnd;               // +0x20
    char pad_24[0x30 - 0x24];
    Prim14* mpPrimBegin;            // +0x30
    Prim14* mpPrimEnd;              // +0x34
};
struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void Write(const void* data, unsigned size);        // +0x38
};
bool WriteUint16(IStream* s, const void* data, unsigned count, int endian);   // 0x0093a9d0
void WriteUint32(IStream* s, const void* data, unsigned count, int endian);   // 0x0093aa70
void WriteBytes(IStream* s, const void* data, unsigned count);                // 0x0093a9a0 (operator<<)
void WriteHandle(IStream* s, const void* handle);                             // 0x0071dbf0
struct MeshPrims {
    char pad_00[0x30];
    Prim14* mpPrimBegin;            // +0x30
    Prim14* mpPrimEnd;              // +0x34
};
// ---- items of slice s0071e390 end

// @ 0x0071e230
bool Obj13_e230(const void* v, int limit, const int* keys, int* out)
{
    (void)v; (void)limit; (void)keys; (void)out;
    return false;
}

// @ 0x0071e290
void Obj13_e290(void* self, void* a)
{ (void)self; (void)a; }

// @ 0x0071e320
void Obj13_e320(void* self, void* a, void* b)
{ (void)self; (void)a; (void)b; }

// @ 0x0071e390
bool WriteMesh(IStream* stream, Mesh* mesh)
{
    int local_4;
    int local_8;
    int local_c;
    unsigned char local_10[4];

    local_4 = 4;
    if (!WriteUint16(stream, &local_4, 1, 0))
        return false;

    local_4 = (int)(mesh->mpVertEnd - mesh->mpVertBegin) >> 5;
    WriteUint32(stream, &local_4, 1, 0);

    int nVerts = (int)(mesh->mpVertEnd - mesh->mpVertBegin) >> 5;
    if (nVerts > 0) {
        int off = 0;
        local_c = nVerts;
        do {
            char* v = mesh->mpVertBegin + off;
            local_10[0] = *(unsigned char*)v;
            char* v2 = mesh->mpVertBegin + off;
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 4);
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 8);
            WriteBytes(stream, local_10, 1);
            local_10[0] = *(unsigned char*)(v2 + 0xc);
            WriteBytes(stream, local_10, 1);
            WriteHandle(stream, v2 + 0x10);
            off += 0x20;
            --local_c;
        } while (local_c != 0);
    }

    local_4 = (int)(mesh->mpEntryEnd - mesh->mpEntryBegin) / 0x8c;
    WriteUint32(stream, &local_4, 1, 0);

    local_4 = (int)(mesh->mpEntryEnd - mesh->mpEntryBegin) / 0x8c;
    if (local_4 > 0) {
        local_c = 0;
        do {
            char* e = mesh->mpEntryBegin + local_c;
            WriteHandle(stream, e);
            local_8 = *(int*)(e + 0x10);
            WriteUint32(stream, &local_8, 1, 0);
            local_10[0] = (unsigned char)((*(int*)(e + 0x18) - *(int*)(e + 0x14)) >> 2);
            WriteBytes(stream, local_10, 1);
            WriteUint16(stream, (void*)*(int*)(e + 0x14), ((*(int*)(e + 0x18) - *(int*)(e + 0x14)) >> 2) * 2, 0);
            local_10[0] = (unsigned char)((*(int*)(e + 0x48) - *(int*)(e + 0x44)) >> 4);
            WriteBytes(stream, local_10, 1);
            int n16 = (*(int*)(e + 0x48) - *(int*)(e + 0x44)) >> 4;
            if (n16 > 0) {
                int o16 = 0;
                local_8 = n16;
                do {
                    WriteHandle(stream, (char*)*(int*)(e + 0x44) + o16);
                    o16 += 0x10;
                    --local_8;
                } while (local_8 != 0);
            }
            local_c += 0x8c;
            --local_4;
        } while (local_4 != 0);
    }

    local_4 = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
    WriteUint32(stream, &local_4, 1, 0);
    stream->Write(mesh->mpPrimBegin, (unsigned)(mesh->mpPrimEnd - mesh->mpPrimBegin) * sizeof(Prim14));
    return true;
}

// @ 0x0071ee10
void FindPrimitives(MeshPrims* mesh, VecInt* out, int typeEntry, int start, int aux)
{
    out->reserve((unsigned)(mesh->mpPrimEnd - mesh->mpPrimBegin));
    if (start == 0 && aux < 0) {
        int n = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
        for (int i = 0; i < n; ++i) {
            if (mesh->mpPrimBegin[i].mEntry == typeEntry)
                out->push_back(i);
        }
    } else {
        int n = (int)(mesh->mpPrimEnd - mesh->mpPrimBegin);
        for (int i = 0; i < n; ++i) {
            if ((typeEntry == -1 || mesh->mpPrimBegin[i].mEntry == typeEntry)
                && (start == 0 || mesh->mpPrimBegin[i].mType == start)
                && (aux == -1 || mesh->mpPrimBegin[i].mAux == aux))
                out->push_back(i);
        }
    }
}
