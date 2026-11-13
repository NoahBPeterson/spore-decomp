#include "game/types.h"

extern void __cdecl Free_00f47380(void*);

struct Member50_0088e800 {
    uint8_t pad[4];
    ~Member50_0088e800(); // 0x0088def0
};

struct Node_0088e800 {
    uint16_t* mpBegin;      // +0x00
    uint16_t* mpEnd;        // +0x04
    uint16_t* mpCapacity;   // +0x08
    uint8_t pad0c[0x44];
    Member50_0088e800 m50;  // +0x50
};

struct HashTable_0088e800 {
    uint8_t pad00[0x1c];
    Node_0088e800* mpFree;  // +0x1c
    uint32_t mUnk20;        // +0x20
    void* mpPoolBegin;      // +0x24
    void* mpPoolEnd;        // +0x28
    uint32_t mUnk2c;        // +0x2c
    Node_0088e800* mpSentinel; // +0x30

    // @ 0x0088e800
    void FreeNode(Node_0088e800* node);
};

// @ 0x0088e800
void HashTable_0088e800::FreeNode(Node_0088e800* node)
{
    node->m50.~Member50_0088e800();
    if (((int)((char*)node->mpCapacity - (char*)node->mpBegin) & ~1) > 2) {
        if (node->mpBegin) {
            Free_00f47380(node->mpBegin);
        }
    }
    if (node != mpSentinel) {
        if ((void*)node >= mpPoolBegin && (void*)node < mpPoolEnd) {
            node->mpBegin = (uint16_t*)mpFree;
            mpFree = node;
        } else {
            Free_00f47380(node);
        }
    }
}
