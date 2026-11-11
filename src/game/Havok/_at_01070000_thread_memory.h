#ifndef SPORE_AT_01070000_THREAD_MEMORY_H
#define SPORE_AT_01070000_THREAD_MEMORY_H

class hkMemory;
class hkThreadMemory {
public:
    void* mpVtbl;          // +0x00
    char pad04[0x0c];      // +0x04..+0x0f pad
    hkMemory* mMemory;     // +0x10
    int mnRefCount;        // +0x14
    char pad18[8];         // +0x18..+0x1f
    int mStackBase;        // +0x20
    int mStackAlloc;       // +0x24
    int mStackCurrent;     // +0x28
    int mStackEnd;         // +0x2c
    int mStackSize;        // +0x30
    int mMaxRows;          // +0x34
    int mRows[0x11];       // +0x38..+0x7b (free list heads)
    int mRowCounts[0x11];  // +0x7c..+0xbf
    int mClassMax[0x11];   // +0xc0..+0x103 (largest size per class)
    signed char mClassForSize[0x204]; // +0x104..+0x307
    int mExtra[0x40];                  // +0x308..

    hkThreadMemory(hkMemory* memory, int stackSize);   // 0x0107d7e0
    void releaseCachedMemory();          // 0x0107d740
    void removeReference();              // 0x0107d790
    void setStackArea(void* p, int n);   // 0x0107d7a0
    void* allocateChunk(int size, int cls);     // 0x0107daa0
    void deallocateChunk(void* p, int size, int cls); // 0x0107db10
    void onStackUnderflow(void* p);      // 0x0107db90
    static void replaceInstance(hkThreadMemory* p);   // 0x0107dbd0
    void* onStackOverflow(int size);     // 0x0107dc10
};

#endif
