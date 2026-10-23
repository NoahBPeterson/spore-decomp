// slice s00cc4160 -- eastl vector<float> insert (grow + shift path)
// Flags: /O2 /MD /Gy /EHsc /TP

void* EAAllocate(unsigned int size, const char* name, int a, int b, void* alloc, int line);
void eaFree(void* p);
extern "C" {
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
void* __cdecl memmove(void* dst, const void* src, unsigned int n);
}

struct cc4160_vec {
    float* m_begin;
    float* m_end;
    float* m_cap;
    float* m_alloc;
    void insert(float* pos, const float* value);
};

// @ 0x00cc4160
void cc4160_vec::insert(float* pos, const float* value)
{
    float* end = m_end;
    if (end != m_cap) {
        if (pos <= value && value < end)
            ++value;
        if (end)
            *end = end[-1];
        int n = (int)((char*)(m_end - 1) - (char*)pos);
        memmove((char*)m_end - ((n >> 2) << 2), pos, (unsigned int)n);
        *pos = *value;
        m_end = m_end + 1;
        return;
    }
    int count = (int)(m_end - m_begin);
    int newCap = count == 0 ? 1 : count * 2;
    float* dst = 0;
    if (newCap != 0)
        dst = (float*)EAAllocate((unsigned int)(newCap * 4), "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
    memcpy(dst, m_begin, (unsigned int)((char*)pos - (char*)m_begin));
    float* p = dst + (pos - m_begin);
    if (p)
        *p = *value;
    float* q = (float*)memcpy(p + 1, pos, (unsigned int)((char*)m_end - (char*)pos));
    float* newEnd = q + (m_end - pos);
    if (m_begin != 0 && m_begin != m_alloc)
        eaFree(m_begin);
    m_begin = dst;
    m_end = newEnd;
    m_cap = dst + newCap;
}
