// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00b00520.
//
// Distance-sorted container helpers: vector teardown, entry reset, insertion
// sorts keyed on a reference position, nearest-of-three selection and binary
// heap insertion.

typedef unsigned int size_t;
typedef unsigned char uint8_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

// Object with the two reference slots used by the entry reset helper.
class IEntryRef {
public:
    virtual void v00();
    virtual void Release();      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void Reset();        // 0x38
};

// One 0x20-byte entry of the spatial container.
struct cSpatialEntry {
    int mpVtbl;                  // 0x00
    int mPad04;                  // 0x04
    int mField08;                // 0x08
    int mField0c;                // 0x0c
    IEntryRef* mpRef0;           // 0x10
    IEntryRef* mpRef1;           // 0x14
    int mField18;                // 0x18
    int mPad1c;                  // 0x1c
};

// Object whose position lives at 0x5c/0x60/0x64.
struct cPositionedObject {
    uint8_t mPad00[0x5c];        // 0x00
    float mX;                    // 0x5c
    float mY;                    // 0x60
    float mZ;                    // 0x64
};

// Object whose position lives at 0x10/0x14/0x18.
struct cNode {
    uint8_t mPad00[0x10];        // 0x00
    float mX;                    // 0x10
    float mY;                    // 0x14
    float mZ;                    // 0x18
};

// Element of the clump array (stride 0x19a8).
struct cTreeClumpData {
    uint8_t mPad00[0x08];        // 0x00
    uint8_t mBody[0x19a0];       // 0x08
};

class cTreeClump {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08(int bFlag);
    uint8_t mPad04[0x2c];
};

// The clump array is a counted buffer: the element count precedes the data.
struct cTreeClumpVector {
    cTreeClump** mpBegin;        // 0x00
    cTreeClump** mpEnd;          // 0x04
    int* mpCapacity;             // 0x08
};

void DestroyTreeClumpData(cTreeClumpData* pClump, const void* pType, const wchar_t* pName);
void operator_delete__(void* pMemory);

// ---------------------------------------------------------------------------
// 0x00b00520  TreeClumpArray::DestroyAll
// ---------------------------------------------------------------------------
// @ 0x00b00520
int TreeClumpArrayDestroyAll(int bUnused, cTreeClumpVector* pVector)
{
    (void)bUnused;
    cTreeClumpData* pEnd = (cTreeClumpData*)pVector->mpEnd;
    for (cTreeClumpData* pCur = (cTreeClumpData*)pVector->mpBegin; pCur != pEnd;
         pCur = (cTreeClumpData*)((uint8_t*)pCur + sizeof(cTreeClumpData))) {
        DestroyTreeClumpData(pCur, &pVector->mpCapacity, L"cTreeClumpData");
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b00560  TreeClumpArray::Free
// ---------------------------------------------------------------------------
// @ 0x00b00560
void TreeClumpArrayFree(cTreeClumpVector* pVector)
{
    cTreeClump** pEnd = pVector->mpEnd;
    for (cTreeClump** pCur = pVector->mpBegin; pCur < pEnd; ++pCur)
        (*pCur)->v08(0);

    int* pBase = (int*)pVector->mpBegin;
    if (pBase != nullptr && pBase[-1] != 0)
        operator_delete__(pBase);
}

// ---------------------------------------------------------------------------
// 0x00b006f0  SpatialEntryResetRange
// ---------------------------------------------------------------------------
// @ 0x00b006f0
void SpatialEntryResetRange(cSpatialEntry* pFirst, cSpatialEntry* pLast)
{
    for (; pFirst < pLast; ++pFirst) {
        pFirst->mpVtbl = 0;
        pFirst->mField08 = 0;
        pFirst->mField0c = 0;

        IEntryRef* pRef0 = pFirst->mpRef0;
        if (pRef0 != nullptr) {
            pFirst->mpRef0 = nullptr;
            pRef0->Release();
        }
        IEntryRef* pRef1 = pFirst->mpRef1;
        if (pRef1 != nullptr) {
            pFirst->mpRef1 = nullptr;
            pRef1->Reset();
        }
        pFirst->mField18 = 0;
        if (pFirst->mpRef1 != nullptr)
            pFirst->mpRef1->Reset();
        if (pFirst->mpRef0 != nullptr)
            pFirst->mpRef0->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00b00820  InsertionSortByDistance_Positioned
// ---------------------------------------------------------------------------
// @ 0x00b00820
void InsertionSortByDistance_Positioned(cPositionedObject** pFirst, cPositionedObject** pLast,
                                        const Vec3* pReference)
{
    if (pFirst == pLast)
        return;

    for (cPositionedObject** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cPositionedObject* pValue = *pCur;
        cPositionedObject** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = pReference->mX - pValue->mX;
            float dy1 = pReference->mY - pValue->mY;
            float dz1 = pReference->mZ - pValue->mZ;
            do {
                cPositionedObject* pPrev = pSlot[-1];
                float dx2 = pReference->mX - pPrev->mX;
                float dy2 = pReference->mY - pPrev->mY;
                float dz2 = pReference->mZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// ---------------------------------------------------------------------------
// 0x00b008f0  InsertionSortByDistance_Positioned_FromRange
// ---------------------------------------------------------------------------
// @ 0x00b008f0
void InsertionSortByDistance_Positioned_FromRange(cPositionedObject** pFirst,
                                                  cPositionedObject** pLast,
                                                  const Vec3* pReference)
{
    if (pFirst == pLast)
        return;

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;
    do {
        cPositionedObject* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        cPositionedObject** pSlot = pFirst;
        cPositionedObject** pWrite = pFirst;
        for (;;) {
            --pSlot;
            cPositionedObject* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        ++pFirst;
        *pWrite = pValue;
    } while (pFirst != pLast);
}

// ---------------------------------------------------------------------------
// 0x00b009b0  InsertionSortByDistance_Node
// ---------------------------------------------------------------------------
// @ 0x00b009b0
void InsertionSortByDistance_Node(cNode** pFirst, cNode** pLast, float refX, float refY, float refZ)
{
    if (pFirst == pLast)
        return;

    for (cNode** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cNode* pValue = *pCur;
        cNode** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            do {
                cNode* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// ---------------------------------------------------------------------------
// 0x00b00a80  InsertionSortByDistance_Node_FromRange
// ---------------------------------------------------------------------------
// @ 0x00b00a80
void InsertionSortByDistance_Node_FromRange(cNode** pFirst, cNode** pLast, float refX, float refY,
                                            float refZ)
{
    for (; pFirst != pLast; ++pFirst) {
        cNode* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        cNode** pSlot = pFirst;
        cNode** pWrite = pFirst;
        for (;;) {
            --pSlot;
            cNode* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        *pWrite = pValue;
    }
}

// ---------------------------------------------------------------------------
// 0x00b00b40  InsertionSortVec3Pointers
// ---------------------------------------------------------------------------
// @ 0x00b00b40
void InsertionSortVec3Pointers(Vec3** pFirst, Vec3** pLast, float refX, float refY, float refZ)
{
    if (pFirst == pLast)
        return;

    for (Vec3** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        Vec3* pValue = *pCur;
        Vec3** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            do {
                Vec3* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// ---------------------------------------------------------------------------
// 0x00b00c10  InsertionSortVec3Pointers_FromRange
// ---------------------------------------------------------------------------
// @ 0x00b00c10
void InsertionSortVec3Pointers_FromRange(Vec3** pFirst, Vec3** pLast, float refX, float refY,
                                         float refZ)
{
    for (; pFirst != pLast; ++pFirst) {
        Vec3* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        Vec3** pSlot = pFirst;
        Vec3** pWrite = pFirst;
        for (;;) {
            --pSlot;
            Vec3* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        *pWrite = pValue;
    }
}

// ---------------------------------------------------------------------------
// 0x00b00cd0  NearestOfThree_Positioned
// ---------------------------------------------------------------------------
// @ 0x00b00cd0
cPositionedObject** NearestOfThree_Positioned(cPositionedObject** ppA, cPositionedObject** ppB,
                                              cPositionedObject** ppC, const Vec3* pReference)
{
    cPositionedObject* pA = *ppA;
    cPositionedObject* pB = *ppB;
    cPositionedObject* pC = *ppC;

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distB < distC)
            return ppC;
    } else {
        if (distC <= distB) {
            if (distC <= distA)
                return ppA;
            return ppC;
        }
    }
    return ppB;
}

// ---------------------------------------------------------------------------
// 0x00b00f50  NearestOfThree_Node
// ---------------------------------------------------------------------------
// @ 0x00b00f50
cNode** NearestOfThree_Node(cNode** ppA, cNode** ppB, cNode** ppC, float refX, float refY, float refZ)
{
    cNode* pA = *ppA;
    cNode* pB = *ppB;
    cNode* pC = *ppC;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distB < distC)
            return ppC;
    } else {
        if (distC <= distB) {
            if (distC <= distA)
                return ppA;
            return ppC;
        }
    }
    return ppB;
}

// ---------------------------------------------------------------------------
// 0x00b011f0  NearestOfThreeVec3
// ---------------------------------------------------------------------------
// @ 0x00b011f0
Vec3** NearestOfThreeVec3(Vec3** ppA, Vec3** ppB, Vec3** ppC, float refX, float refY, float refZ)
{
    Vec3* pA = *ppA;
    Vec3* pB = *ppB;
    Vec3* pC = *ppC;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distC <= distB)
            return ppB;
    } else {
        if (distB < distC)
            return ppB;
        if (distC <= distA)
            return ppA;
    }
    return ppC;
}

// ---------------------------------------------------------------------------
// 0x00b01470  SpatialEntryResetRangeWithOutput
// ---------------------------------------------------------------------------
// @ 0x00b01470
cSpatialEntry* SpatialEntryResetRangeWithOutput(cSpatialEntry* pFirst, cSpatialEntry* pLast,
                                                cSpatialEntry* pOut)
{
    if (pFirst == pLast)
        return pOut;

    do {
        pFirst->mpVtbl = 0;
        pFirst->mField08 = 0;
        pFirst->mField0c = 0;

        IEntryRef* pRef0 = pFirst->mpRef0;
        if (pRef0 != nullptr) {
            pFirst->mpRef0 = nullptr;
            pRef0->Release();
        }
        IEntryRef* pRef1 = pFirst->mpRef1;
        if (pRef1 != nullptr) {
            pFirst->mpRef1 = nullptr;
            pRef1->Reset();
        }
        pFirst->mField18 = 0;
        if (pFirst->mpRef1 != nullptr)
            pFirst->mpRef1->Reset();
        if (pFirst->mpRef0 != nullptr)
            pFirst->mpRef0->Release();

        ++pFirst;
        ++pOut;
    } while (pFirst != pLast);
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00b014f0  HeapInsertPositioned
// ---------------------------------------------------------------------------
// @ 0x00b014f0
void HeapInsertPositioned(cPositionedObject** ppHeap, int nRoot, int nIndex,
                          cPositionedObject* pValue, const Vec3* pReference)
{
    if (nIndex <= nRoot) {
        ppHeap[nIndex] = pValue;
        return;
    }

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;
    float vx = refX - pValue->mX;
    float vy = refY - pValue->mY;
    float vz = refZ - pValue->mZ;
    float distValue = vx * vx + vy * vy + vz * vz;

    for (;;) {
        int nParent = (nIndex - 1) >> 1;
        cPositionedObject* pParent = ppHeap[nParent];
        float px = refX - pParent->mX;
        float py = refY - pParent->mY;
        float pz = refZ - pParent->mZ;
        if (distValue <= px * px + py * py + pz * pz)
            break;
        ppHeap[nIndex] = pParent;
        nIndex = nParent;
        if (nParent <= nRoot)
            break;
    }
    ppHeap[nIndex] = pValue;
}

// ---------------------------------------------------------------------------
// 0x00b015c0  HeapInsertNode
// ---------------------------------------------------------------------------
// @ 0x00b015c0
void HeapInsertNode(cNode** ppHeap, int nRoot, int nIndex, cNode* pValue, float refX, float refY,
                    float refZ)
{
    if (nIndex <= nRoot) {
        ppHeap[nIndex] = pValue;
        return;
    }

    float vx = refX - pValue->mX;
    float vy = refY - pValue->mY;
    float vz = refZ - pValue->mZ;
    float distValue = vx * vx + vy * vy + vz * vz;

    for (;;) {
        int nParent = (nIndex - 1) >> 1;
        cNode* pParent = ppHeap[nParent];
        float px = refX - pParent->mX;
        float py = refY - pParent->mY;
        float pz = refZ - pParent->mZ;
        if (distValue <= px * px + py * py + pz * pz)
            break;
        ppHeap[nIndex] = pParent;
        nIndex = nParent;
        if (nParent <= nRoot)
            break;
    }
    ppHeap[nIndex] = pValue;
}
