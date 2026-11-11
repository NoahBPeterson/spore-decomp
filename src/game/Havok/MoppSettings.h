#ifndef HAVOK_MOPP_SETTINGS_H
#define HAVOK_MOPP_SETTINGS_H

#include "game/types.h"

struct hkMoppSettingsPartA {                          // 20 bytes, at settings+4
    float m_f0; int32_t m_i1; int32_t m_i2; int32_t m_i3; int32_t m_i4;
    __declspec(noinline) hkMoppSettingsPartA* init(int preset);   // 0x011037e0 (returns this in eax)
};
struct hkMoppSettingsPartB {                          // 24 bytes, at settings+0x18
    float m_f[5]; float m_f5;
    __declspec(noinline) hkMoppSettingsPartB* init(int preset);   // 0x01103830 (returns this in eax)
};
struct hkMoppSettings {
    void* m_result;                                     // +0  (hkMoppCode*)
    hkMoppSettingsPartA m_a;                            // +4
    hkMoppSettingsPartB m_b;                            // +0x18
    float m_c0, m_c1, m_c2;                             // +0x30,+0x34,+0x38
    uint32_t m_c3;                                      // +0x3c (never touched by the setters)
    float m_d0, m_d1, m_d2; uint32_t m_d3; int32_t m_d4;   // +0x40..+0x50
    hkMoppSettings* construct(int preset);              // 0x01103610
    void setA(const uint32_t* a);                       // 0x01103590 (5 dwords -> +4)
    void setB(const uint32_t* b);                       // 0x011035c0 (6 dwords -> +0x18)
    void setC(const uint32_t* c);                       // 0x011037a0
    int getScratchSize(struct hkMoppSource* src) const; // 0x011035f0
    void* build(struct hkMoppSource* src, void* buffer, int bufferSize);   // 0x01103670
};
struct hkMoppSource {
    virtual void m0();
    virtual void m1();
    virtual int getNumPrimitives();                    // +8
    virtual void setScratchBuffer(void* buffer);       // +0xc
    virtual void m4();
};

#endif
