// Slice s007b87f0 - cThumbnailManager filter-chain/large-image helpers.

void operator delete[](void*);

struct Pair2 { int a, b; };

void __stdcall GrowVec(Pair2* e, Pair2* p);    // out-of-line vector grow (006ec390)

struct RawVec {
    Pair2* begin;
    Pair2* end;
    Pair2* cap;
    void push_back(Pair2* p);
};

struct VecPair {
    char pad0[0x24];
    RawVec v;                           // +0x24
    void Push(Pair2* p);
};

void RawVec::push_back(Pair2* p)
{
    Pair2* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *p;
    } else {
        GrowVec(e, p);
    }
}

// @ 0x007b9690
void VecPair::Push(Pair2* p)
{
    v.push_back(p);
}

// ---------------------------------------------------------------------------
// Remaining functions are large cThumbnailManager filter-chain helpers;
// recorded as partial skeletons in partial.txt.
// ---------------------------------------------------------------------------

struct ShutdownViewer {
    void Destroy1();                    // 007c3ba0
    void Destroy2();                    // 007c4000
};

struct SimpleVec {
    int* mpBegin;
    int* mpEnd;
    void erase(int* first, int* last);
};

struct ViewerBox {
    char pad0[0x18];
    int* m_p18;                         // +0x18
    char pad1[0x24 - 0x1c];
    int* m_vecBegin;                    // +0x24
    int* m_vecEnd;                      // +0x28
    char pad2[0x38 - 0x2c];
    ShutdownViewer* m_viewer;           // +0x38
    char pad3[0x80 - 0x3c];
    bool m_flag;                        // +0x80
    void Shutdown();
};

// @ 0x007b9620
void ViewerBox::Shutdown()
{
    if (!m_flag)
        return;
    if (m_viewer) {
        m_viewer->Destroy1();
        ShutdownViewer* v = m_viewer;
        if (v) {
            v->Destroy2();
            operator delete[](v);
        }
        m_viewer = 0;
    }
    if (m_p18)
        m_p18 = 0;
    if (m_vecBegin != m_vecEnd) {
        SimpleVec* vec = (SimpleVec*)((char*)this + 0x24);
        vec->erase(vec->mpBegin, vec->mpEnd);
    }
    m_flag = false;
}

void operator delete[](void*);

// @ 0x007b87f0  (partial)
void partial_007b87f0(void) {}
// @ 0x007b8b30  (partial)
void partial_007b8b30(void) {}
// @ 0x007b8be0  (partial)
void partial_007b8be0(void) {}
// @ 0x007b8cb0  (partial)
void partial_007b8cb0(void) {}
// @ 0x007b91f0  (partial)
void partial_007b91f0(void) {}
// @ 0x007b9420  (partial)
void partial_007b9420(void) {}
// @ 0x007b9510  (partial)
void partial_007b9510(void) {}
// @ 0x007b96d0  (partial)
void partial_007b96d0(void) {}
// @ 0x007b9750  (partial)
void partial_007b9750(void) {}
