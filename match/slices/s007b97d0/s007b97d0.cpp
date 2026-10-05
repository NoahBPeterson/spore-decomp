// Slice s007b97d0 - cThumbnailManager timeline/terrain teardown + large-image helpers.

struct TerrainFilter {
    virtual void slot0();
    virtual void Release();             // vtable +4
    void InnerTeardown();               // 007b9620
};

struct Viewer {
    void Destroy1();                    // 007c3ba0
    void Destroy2();                    // 007c4000
};

struct TerrainMgr {
    char pad0[0x10d1];
    bool m_terrainFilterInitialized;    // +0x10d1
    TerrainFilter* m_filter0;           // +0x10d4
    TerrainFilter* m_filter1;           // +0x10d8
    TerrainFilter* m_filter2;           // +0x10dc
    Viewer* m_viewer;                   // +0x10e0
    void Teardown();
};

// @ 0x007b9e80
void TerrainMgr::Teardown()
{
    if (!m_terrainFilterInitialized)
        return;
    m_viewer->Destroy1();
    Viewer* v = m_viewer;
    if (v) {
        v->Destroy2();
        operator delete[](v);
    }
    m_viewer = 0;
    m_filter0->InnerTeardown();
    TerrainFilter* p0 = m_filter0;
    if (p0) {
        m_filter0 = 0;
        p0->Release();
    }
    m_filter1->InnerTeardown();
    TerrainFilter* p1 = m_filter1;
    if (p1) {
        m_filter1 = 0;
        p1->Release();
    }
    m_filter2->InnerTeardown();
    TerrainFilter* p2 = m_filter2;
    if (p2) {
        m_filter2 = 0;
        p2->Release();
    }
    m_terrainFilterInitialized = false;
}

// ---------------------------------------------------------------------------
// Remaining functions are large timeline/large-image helpers; recorded as
// partial skeletons in partial.txt.
// ---------------------------------------------------------------------------

// @ 0x007b97d0  (partial)
void partial_007b97d0(void) {}
// @ 0x007b9990  (partial)
void partial_007b9990(void) {}
// @ 0x007b9b00  (partial)
void partial_007b9b00(void) {}
// @ 0x007b9f30  (partial)
void partial_007b9f30(void) {}
// @ 0x007ba0b0  (partial)
void partial_007ba0b0(void) {}
