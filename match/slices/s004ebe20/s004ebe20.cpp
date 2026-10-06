// slice s004ebe20 -- SP::EditorValidity::InitializeValidityData (byte-exact).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
//
// One-time loader for the editor validity tables: reads the validity property
// list (0xcc271289), fills the 128-bit "legal model type" bitsets from int-array
// properties (-1 = "everything the parent set allows"), then fills the legal
// part / paint maps from every editor config's property list.

#include "types.h"

// ---- property lists ----------------------------------------------------------
struct PropertyList {
    virtual int AddRef();                  // +0
    virtual int Release();                 // +4
};

struct PropertyListPtr {                   // EA intrusive_ptr<PropertyList>
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    explicit PropertyListPtr(PropertyList* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyListPtr& Reset();              // 0x0041d870 (out of line)
    PropertyListPtr& ResetInline()
    {
        if (mpObject) {
            PropertyList* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return *this;
    }
    PropertyList* get() const { return mpObject; }
    PropertyListPtr& Out() { return Reset(); }
};

struct cPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& pDst);   // +0x2c
    virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyListPtr& pDst);               // +0x30
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

struct WString16 {                         // eastl::basic_string<wchar_t>
    uint32_t mData[4];
    void push_back(wchar_t c);             // 0x004f6510
};

struct ValidityBits {                      // eastl::bitset<128>
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i, bool value = true)
    {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
    void operator|=(const ValidityBits& x)
    {
        for (uint32_t i = 0; i < 4; i++)
            mWord[i] |= x.mWord[i];
    }
    ValidityBits& flip();                  // 0x004f65d0 (out of line)
};

struct KeyVector;
struct KeyMap {                            // eastl::map<uint32_t, vector<ResourceKey-ish>>
    KeyVector& operator[](const uint32_t& key);   // 0x004f6720
};

struct cDirectPropertyList;

// Reserved-but-unused /Od frame space of inline callees that cl declined to inline.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace SP {
cPropManager* PropertyManager();                                                       // 0x0067de30
bool GetPropertyAsUInt(PropertyList* p, uint32_t id, uint32_t* out);                   // 0x00410370
bool GetPropertyAsString16(PropertyList* p, uint32_t id, WString16* out);              // 0x006a1400
bool GetPropertyAsIntArray(PropertyList* p, uint32_t id, uint32_t* count, int** out);  // 0x006a07d0
bool GetPropertyAsKey(PropertyList* p, uint32_t id, ResourceKey* out);                 // 0x006a1250
extern cDirectPropertyList* sAppProperties;                                            // 0x015fd918
// Debug-only use of the app property list; only the load survives in release.
inline void CheckAppProperties() { cDirectPropertyList* pAppProps = sAppProperties; }
namespace Editor { uint32_t GetConfigFromModelType(uint32_t modelType); }             // 0x00432f10

namespace EditorValidity {
void ReadKeysFromFile(uint32_t instanceID, KeyVector& dst);                           // 0x004eb270
void ExpandValidity(ValidityBits* bits);                                               // 0x004eba00

extern bool sInitialized;                  // 0x015da6e4
extern uint32_t sValidityVersion;          // 0x015da6e0
extern WString16 sValidityChars;           // 0x015da7d4
extern ValidityBits sBits784;              // 0x015da784
extern ValidityBits sBits7c4;              // 0x015da7c4
extern ValidityBits sBits9c8;              // 0x015da9c8
extern ValidityBits sBits8e0;              // 0x015da8e0
extern ValidityBits sBitsb94;              // 0x015dab94
extern ValidityBits sBitsa40;              // 0x015daa40
extern ValidityBits sBits7ec;              // 0x015da7ec
extern ValidityBits sBitsc10;              // 0x015dac10
extern ValidityBits sBitsb18;              // 0x015dab18
extern ValidityBits sBits80c;              // 0x015da80c
extern ValidityBits sBits860;              // 0x015da860
extern KeyMap sLegalParts;                 // 0x015da960
extern KeyMap sLegalPaints;                // 0x015da884
extern uint32_t kGroupEditorConfigs;       // 0x015daa00
extern uint32_t kEditorModelTypes[];       // 0x0150ca00 (27 entries)

// @ 0x004ebe20
void InitializeValidityData()
{
    if (!sInitialized) {
        const uint32_t validityID = 0xcc271289;
        PropertyListPtr pValidityList(0);
        PropertyManager()->GetGlobalPropertyList(validityID, pValidityList.Out());
        ScratchSlots<11>();
        if (pValidityList.mpObject) {
            // Property IDs. The single-letter names are neutral on purpose: at /Od cl orders a
            // scope's locals by a hash of their names, and these reproduce the original frame.
            const uint32_t kL = 0x530593e;      // validity data version -> sValidityVersion
            const uint32_t kC = 0x56c4406;      // declared, never read
            const uint32_t kQ = 0x56c4407;      // -> sBits784
            const uint32_t kA = 0x56c4408;      // -> sBits7c4 (-1 = all of sBits784)
            const uint32_t kD = 0x14975ade;     // -> sBits9c8
            const uint32_t kK = 0x56c4409;      // -> sBitsb94 (-1 = all of sBits7c4)
            const uint32_t kF = 0x56c440a;      // -> sBitsa40 (-1 = all of sBitsb94)
            const uint32_t kG = 0x56c440b;      // -> sBits7ec
            const uint32_t kM = 0x665f744;      // -> sBits8e0
            const uint32_t kB = 0x6779140;      // -> sBitsc10
            const uint32_t kI = 0x6786653;      // -> sBitsb18
            const uint32_t kH = 0x67b80bc;      // -> sBits80c
            GetPropertyAsUInt(pValidityList.mpObject, kL, &sValidityVersion);
            const uint32_t kJ = 0x5304e04;      // extra characters string -> sValidityChars
            GetPropertyAsString16(pValidityList.mpObject, kJ, &sValidityChars);
            sValidityChars.push_back(L'"');
            sValidityChars.push_back(L'#');

            uint32_t numTypes;
            int* pTypes;

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kQ, &numTypes, &pTypes);
            for (int i = 0; i < (int)numTypes; i++) {
                if (pTypes[i] == -1) {     // "all" (-1) is ignored for this set
                } else {
                    sBits784.set(pTypes[i]);
                }
            }
            ExpandValidity(&sBits784);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kA, &numTypes, &pTypes);
            for (int j = 0; j < (int)numTypes; j++) {
                if (pTypes[j] == -1)
                    sBits7c4 |= sBits784;
                else
                    sBits7c4.set(pTypes[j]);
            }
            ExpandValidity(&sBits7c4);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kD, &numTypes, &pTypes);
            for (int k = 0; k < (int)numTypes; k++)
                sBits9c8.set(pTypes[k]);
            ExpandValidity(&sBits9c8);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kM, &numTypes, &pTypes);
            for (int l = 0; l < (int)numTypes; l++)
                sBits8e0.set(pTypes[l]);
            ExpandValidity(&sBits8e0);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kK, &numTypes, &pTypes);
            for (int m = 0; m < (int)numTypes; m++) {
                if (pTypes[m] == -1)
                    sBitsb94 |= sBits7c4;
                else
                    sBitsb94.set(pTypes[m]);
            }
            ExpandValidity(&sBitsb94);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kF, &numTypes, &pTypes);
            for (int n = 0; n < (int)numTypes; n++) {
                if (pTypes[n] == -1)
                    sBitsa40 |= sBitsb94;
                else
                    sBitsa40.set(pTypes[n]);
            }
            ExpandValidity(&sBitsa40);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kG, &numTypes, &pTypes);
            for (int o = 0; o < (int)numTypes; o++) {
                if (pTypes[o] == -1) {
                } else {
                    sBits7ec.set(pTypes[o]);
                }
            }
            ExpandValidity(&sBits7ec);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kB, &numTypes, &pTypes);
            for (int p = 0; p < (int)numTypes; p++) {
                if (pTypes[p] == -1) {
                } else {
                    sBitsc10.set(pTypes[p]);
                }
            }
            ExpandValidity(&sBitsc10);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kI, &numTypes, &pTypes);
            for (int q = 0; q < (int)numTypes; q++) {
                if (pTypes[q] == -1) {
                } else {
                    sBitsb18.set(pTypes[q]);
                }
            }
            ExpandValidity(&sBitsb18);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kH, &numTypes, &pTypes);
            for (int r = 0; r < (int)numTypes; r++) {
                if (pTypes[r] == -1) {
                } else {
                    sBits80c.set(pTypes[r]);
                }
            }
            ExpandValidity(&sBits80c);
            ScratchSlots<1>();

            sBits860.flip();
        }

        for (int typeIdx = 0, numModelTypes = 27; typeIdx < numModelTypes; typeIdx++) {
            uint32_t configID = Editor::GetConfigFromModelType(kEditorModelTypes[typeIdx]);
            PropertyListPtr pEditorConfig;
            if (PropertyManager()->GetPropertyList(configID, kGroupEditorConfigs, pEditorConfig.ResetInline())) {
                ResourceKey legalPartsKey;
                if (GetPropertyAsKey(pEditorConfig.get(), 0xf5cbe065, &legalPartsKey))
                    ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
                ScratchSlots<17>();
                ResourceKey legalPaintsKey;
                if (GetPropertyAsKey(pEditorConfig.get(), 0x7a926123, &legalPaintsKey))
                    ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
                ScratchSlots<17>();
                CheckAppProperties();
            }
        }

        uint32_t cfgID = 0xe46c381e;
        PropertyListPtr pList;
        if (PropertyManager()->GetPropertyList(cfgID, kGroupEditorConfigs, pList.ResetInline())) {
            ResourceKey legalPartsKey;
            if (GetPropertyAsKey(pList.get(), 0xf5cbe065, &legalPartsKey))
                ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
            ScratchSlots<17>();
            ResourceKey legalPaintsKey;
            if (GetPropertyAsKey(pList.get(), 0x7a926123, &legalPaintsKey))
                ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
            ScratchSlots<17>();
        }
        cfgID = 0xef18a560;
        if (PropertyManager()->GetPropertyList(cfgID, kGroupEditorConfigs, pList.ResetInline())) {
            ResourceKey legalPartsKey;
            if (GetPropertyAsKey(pList.get(), 0xf5cbe065, &legalPartsKey))
                ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
            ScratchSlots<18>();
            ResourceKey legalPaintsKey;
            if (GetPropertyAsKey(pList.get(), 0x7a926123, &legalPaintsKey))
                ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
            ScratchSlots<17>();
        }
        ScratchSlots<3>();
        sInitialized = true;
    }
}

} // namespace EditorValidity
} // namespace SP
