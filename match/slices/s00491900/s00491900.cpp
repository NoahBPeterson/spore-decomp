// Slice s00491900 (batch w1g0, slice 87), 0x00491900..0x00491b3f.
// /Od editor-region code. A free __cdecl routine that walks a vector of editor
// blocks and inserts each (with refcount) into a second vector, depending on the
// block's tracker / secondary-tracker links.

#include "types.h"

struct IRefCounted {
    virtual void Slot0();
    virtual void AddRef();
    virtual void Release();
};

struct cSPEditorBlock {
    char pad[0x3e0];
    void* tracker;                        // 0x3e0
    void* field3e4;                       // 0x3e4
};

struct Vec {
    void** begin;                         // 0
    void** end;                           // 4
    void Clear(void** a, void** b);
    void Insert(void** p);
};

// @ 0x00491900
int FUN_00491900(Vec* p1, Vec* p2) {
    p2->Clear(p2->begin, p2->end);
    int n = (int)(p1->end - p1->begin);
    for (int i = 0; i < n; ++i) {
        cSPEditorBlock* e = (cSPEditorBlock*)p1->begin[i];
        if (e != 0) {
            if (e->tracker == 0 && e->field3e4 == 0) {
                cSPEditorBlock* tmp = e;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                p2->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            } else if (e->tracker == 0) {
                if (e->field3e4 != 0) {
                    void* target = e->field3e4;
                    void** it = p2->begin;
                    void** end = p2->end;
                    while (it != end && *it != target)
                        ++it;
                    if (it == end) {
                        cSPEditorBlock* tmp = e;
                        if (tmp)
                            ((IRefCounted*)tmp)->AddRef();
                        p2->Insert((void**)&tmp);
                        if (tmp)
                            ((IRefCounted*)tmp)->Release();
                    }
                }
            } else {
                void* target = e->tracker;
                void** it = p2->begin;
                void** end = p2->end;
                while (it != end && *it != target)
                    ++it;
                if (it == end) {
                    cSPEditorBlock* tmp = e;
                    if (tmp)
                        ((IRefCounted*)tmp)->AddRef();
                    p2->Insert((void**)&tmp);
                    if (tmp)
                        ((IRefCounted*)tmp)->Release();
                }
            }
        }
    }
    return (int)(p2->end - p2->begin);
}
