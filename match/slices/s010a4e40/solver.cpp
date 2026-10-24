// Havok 3.1.0 slice s010a4e40: hkConstraintSolverSetup jacobian-element builders.
//
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments).
// Flags: /vc71 /O2 /MD /Gy /TP
#pragma once
#include "types.h"

// ---------------------------------------------------------------------------
// hkBool: a 1-byte value returned by value (hidden sret pointer on x86).
struct hkBool
{
	unsigned char m_value;                        // +0x00
	hkBool() : m_value(0) {}
	hkBool(const hkBool& o) : m_value(o.m_value) {}
	hkBool& operator=(const hkBool& o) { m_value = o.m_value; return *this; }
	~hkBool() {}
};

// hkArray<T> as used by hkConstraintSolverSetup::internalAddJacobianElements.
// m_data / m_size / m_capacityAndFlags (bit 31: memory not owned).
template <typename T>
class hkArray
{
public:
	T*    m_data;                                 // +0x00
	int   m_size;                                 // +0x04
	int   m_capacityAndFlags;                     // +0x08

	void pushBack(const T& e)
	{
		if (m_size == (m_capacityAndFlags & 0x3fffffff)) {
			extern void hkArrayUtil_reserveMore(void* arrayBase, int elemSize);   // 0x0107F530
			hkArrayUtil_reserveMore(this, (int)sizeof(T));
		}
		m_data[m_size++] = e;
	}
};

struct hkConstraintSolverResources;
struct hkConstraintSchemaInfo
{
	int   m_instance;                             // +0x00
	int   m_offset;                               // +0x04
	float m_value;                                // +0x08
};

// The internal "builder object" reachable from an instance at +0x24; its
// members +0x04/+0x08 point at two solver buffers with a count at +0x58.
struct hkSolverBuffer
{
	int m_sizes[0x60 / 4];                        // ... +0x58 is the count
};

struct hkInstanceAux
{
	hkSolverBuffer* m_buf04;                      // +0x04
	hkSolverBuffer* m_buf08;                      // +0x08
	int m_w18;                                    // +0x18
};

// A constraint instance: a byte at +0x18 (the priority), a pointer at +0x24
// and an interface object pointer at +0x0c whose vtable slots +0x1c and +0x20
// are the two "gather sizes" calls.
struct hkConstraintInstance
{
	unsigned char      m_pad00[0x0c];
	void*              m_iface0c;                 // +0x0c
	unsigned char      m_pad10[0x08];
	unsigned char      m_priority18;              // +0x18
	unsigned char      m_pad19[0x0b];
	hkInstanceAux*     m_aux24;                   // +0x24
};

// The iface object's vtable, as called by both setup routines.
struct hkIfaceVtbl
{
	void* slot00;
	void* slot04;
	void* slot08;
	void* slot0c;
	void* slot10;
	void* slot14;
	void* slot18;
	void (*slot1c)(int* out3, void* rec);
	void (*slot20)(int* out);
};

// The solver resources block.  Absolute offsets matter (comments).
struct hkConstraintSolverResources
{
	int    m_w00;                                 // +0x00
	int    m_w04;                                 // +0x04
	void*  m_rec08;                               // +0x08 (0x48-byte record base)
	int    m_base0c;                              // +0x0c
	int    m_pad10[2];                            // +0x10
	int    m_limit18;                             // +0x18
	int    m_pad1c;                               // +0x1c
	int    m_limit20;                             // +0x20
	int    m_pad24;                               // +0x24
	int    m_limit28;                             // +0x28
	int*   m_p2c;                                 // +0x2c
	int    m_pad30[2];                            // +0x30
	int    m_limit38;                             // +0x38
	int*   m_p38;                                 // +0x3c
	int    m_pad40[2];                            // +0x40
	int    m_run48;                               // +0x48
	int    m_run4c;                               // +0x4c
};

// The record written into res->m_rec08.
struct hkJacobianElementRecord
{
	int   m_pad00[0x28 / 4];
	int   m_w28;                                  // +0x28
	int   m_w2c;                                  // +0x2c
	int   m_p30;                                  // +0x30
	int   m_p34;                                  // +0x34
	int   m_pad38[2];
	int   m_instance40;                           // +0x40
	int   m_w44;                                  // +0x44
};

extern "C" void hkArrayUtil_reserveMore(void* arrayBase, int elemSize);   // 0x0107F530

// The setup class whose two static helpers are the slice targets.
struct hkConstraintSolverSetup
{
	static void internalAddJacobianElements(hkConstraintSolverResources& res,
	                                        hkConstraintInstance** instances,
	                                        int count,
	                                        hkArray<hkConstraintSchemaInfo>& schemas);
	static hkBool internalIsMemoryOkForNewJacobianElements(hkConstraintSolverResources& res,
	                                                       hkConstraintInstance** instances,
	                                                       int count);
};

// @ 0x010a4e40
void hkConstraintSolverSetup::internalAddJacobianElements(
	hkConstraintSolverResources& res,
	hkConstraintInstance** instances,
	int count,
	hkArray<hkConstraintSchemaInfo>& schemas)
{
	int saved48 = res.m_run48;
	hkConstraintInstance** end = instances + count;
	hkJacobianElementRecord* rec = (hkJacobianElementRecord*)res.m_rec08;

	if (instances < end) {
		do {
			hkConstraintInstance* inst = *instances;
			unsigned char prio = inst->m_priority18;
			hkInstanceAux* aux = inst->m_aux24;
			hkSolverBuffer* b4 = aux->m_buf04;
			hkSolverBuffer* b8 = aux->m_buf08;
			hkSolverBuffer* s4 = *(hkSolverBuffer**)((char*)b4 + 0x58);
			hkSolverBuffer* s8 = *(hkSolverBuffer**)((char*)b8 + 0x58);

			rec->m_w28 = *(int*)((char*)s4 + 8) + res.m_base0c;
			rec->m_w2c = *(int*)((char*)s8 + 8) + res.m_base0c;
			rec->m_p30 = (int)((char*)s4 + 0x10);
			rec->m_p34 = (int)((char*)s8 + 0x10);
			rec->m_instance40 = (int)inst;
			rec->m_w44 = *(int*)((char*)aux + 0x18);

			if (schemas.m_size == (schemas.m_capacityAndFlags & 0x3fffffff))
				hkArrayUtil_reserveMore(&schemas, 0xc);

			hkConstraintSchemaInfo* e = &schemas.m_data[schemas.m_size];
			++schemas.m_size;
			e->m_instance = (int)inst;
			int* offsrc = (int*)((char*)&res + (prio == 4 ? 0x10 : 0) + 0x2c);
			e->m_offset = *offsrc;
			float f4 = *(float*)((char*)s4 + 0x3c);
			float f8 = *(float*)((char*)s8 + 0x3c);
			e->m_value = (f8 <= f4) ? f8 : f4;

			int local_18 = *offsrc;
			int local_10[3];
			hkIfaceVtbl* vt = *(hkIfaceVtbl**)inst->m_iface0c;
			vt->slot1c((int*)rec, &local_18);
			res.m_run48 = local_10[0];
			*(int*)rec = local_10[1];
			vt->slot20(&local_18);
			res.m_run4c += local_10[2] * 4;
			++instances;
		} while (instances < end);
	}

	*res.m_p2c = 0x400;
	*res.m_p38 = 0x400;
	(void)saved48;
}

// @ 0x010a4fb0
hkBool hkConstraintSolverSetup::internalIsMemoryOkForNewJacobianElements(
	hkConstraintSolverResources& res,
	hkConstraintInstance** instances,
	int count)
{
	int local_18[2];
	local_18[0] = (int)res.m_p2c;                 // +0x2c
	local_18[1] = (int)res.m_p38;                 // +0x3c
	unsigned run4c = (unsigned)res.m_run4c;       // +0x4c
	unsigned run48 = (unsigned)res.m_run48;       // +0x48

	hkConstraintInstance** end = instances + count;
	if (instances < end) {
		do {
			int out[4];
			hkConstraintInstance* inst = *instances;
			hkIfaceVtbl* vt = *(hkIfaceVtbl**)inst->m_iface0c;
			vt->slot20(out);
			run48 += (unsigned)out[0];
			run4c += (unsigned)out[2] * 4;
			int sel = (inst->m_priority18 > 3) ? 1 : 0;
			local_18[sel] += out[1];
			++instances;
		} while (instances < end);
	}

	hkBool r;
	if (run48 <= (unsigned)res.m_limit18 &&
	    run4c <= (unsigned)res.m_limit20 &&
	    (unsigned)(local_18[0] + 4) <= (unsigned)res.m_limit28 &&
	    (unsigned)(local_18[1] + 4) <= (unsigned)res.m_limit38)
		r.m_value = 1;
	else
		r.m_value = 0;
	return r;
}