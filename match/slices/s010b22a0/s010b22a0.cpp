// Slice s010b22a0: Havok 3.1 GSK contact-solver iteration at 0x010b22a0 (1513 bytes).
//
// The routine runs one solver pass over a contact list:
//   1. for every contact of the list it evaluates the linearised relative velocity of the two
//      vertices the contact references (vertex +0x10 / +0x20 pushed against the row's cached
//      velocity at +0x10 / +0x20, scaled by the contact weights) and stores the resulting
//      impulse into the trailing float array of the row block;
//   2. it then walks the contacts backwards, integrates each impulse into both vertices
//      (linear +0x10, angular +0x20, contact direction +0x30 weighted by +0x3c) and accumulates
//      the impulse into the per-contact accumulator array.
// The original is pure x87 (no calls, and esp,-0x10 frame) and is 1513 bytes; the
// reconstruction below keeps the data layout and both passes, but the impulse expression is
// written in vector form, so the codegen cannot be reproduced.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (the retail body is x87; it does not match).

typedef float hkReal;

// One solver vertex (stride 0x40): the two velocity accumulators of the two bodies the vertex
// takes part in, the contact direction and its inverse mass.
struct GskVertex
{
    char   pad00[0x10];
    hkReal m_linear[3];      // +0x10 body 0 linear velocity
    hkReal m_pad1c;
    hkReal m_angular[3];     // +0x20 body 0 angular velocity
    hkReal m_pad2c;
    hkReal m_direction[3];   // +0x30 contact direction
    hkReal m_invMass;        // +0x3c
};

// The contact list (param 3): vertex index pairs at +0x10.
struct GskContactList
{
    char   pad00[0x04];
    int    m_count;          // +0x04 number of contacts
    hkReal m_weight0;        // +0x08
    hkReal m_weight1;        // +0x0c
    int    m_vertexIndex[1]; // +0x10 two vertex indices per contact
};

// One solver row (stride 0x3c).  The last float of a row is the first float of the trailing
// accumulator array, which is why the original indexes the block as one flat run of floats.
struct GskRow
{
    hkReal m_pad00[3];       // +0x00
    hkReal m_mass;           // +0x0c
    hkReal m_vel0[3];        // +0x10 cached velocity of the first vertex
    hkReal m_pad1c;
    hkReal m_vel1[3];        // +0x20 cached velocity of the second vertex
    hkReal m_pad2c;
    hkReal m_normal[3];      // +0x30
    hkReal m_impulse;        // +0x3c
};

struct GskSolverConfig
{
    char   pad00[0x40];
    hkReal m_invMassScale;   // +0x40
};

// @ 0x010b22a0
void __cdecl GskSolver_Iterate(const GskSolverConfig* pConfig, GskVertex* pVertices,
                               const GskContactList* pContacts, GskRow* pRows,
                               hkReal* pAccumulators)
{
    const int count = pContacts->m_count;
    hkReal* pImpulses = (hkReal*)((char*)pRows + count * 0x3c);
    const hkReal massScale = pContacts->m_weight0 * pConfig->m_invMassScale;
    const hkReal dt = pContacts->m_weight1;

    // ---- forward pass: solve for every contact's impulse -------------------------------
    for (int i = 0; i < count; ++i)
    {
        const GskRow* pRow = &pRows[i];
        const GskVertex* pA = &pVertices[pContacts->m_vertexIndex[2 * i]];
        const GskVertex* pB = &pVertices[pContacts->m_vertexIndex[2 * i + 1]];

        // relative velocity of the pair along the contact direction
        hkReal relVel = 0.0f;
        hkReal response = 0.0f;
        for (int c = 0; c < 3; ++c)
        {
            hkReal dv = (pA->m_linear[c] - pRow->m_vel0[c]) -
                        (pB->m_linear[c] - pRow->m_vel1[c]);
            relVel += dv * pRow->m_normal[c];
            response += (pA->m_direction[c] * massScale + pB->m_direction[c]) *
                        (pA->m_linear[c] + pB->m_linear[c]) * dt;
        }

        // the accumulated impulse of the previous contact feeds back into this one
        hkReal impulse = ((relVel * massScale + response) -
                          (i > 0 ? pImpulses[i - 1] * pRow[0].m_impulse : 0.0f)) /
                         pRow->m_impulse;
        pImpulses[i] = impulse;
    }

    // ---- backward pass: integrate the impulses back into the vertices -------------------
    for (int i = count - 1; i >= 0; --i)
    {
        GskRow* pRow = &pRows[i];
        GskVertex* pA = &pVertices[pContacts->m_vertexIndex[2 * i]];
        GskVertex* pB = &pVertices[pContacts->m_vertexIndex[2 * i + 1]];
        hkReal impulse = pImpulses[i];

        for (int c = 0; c < 3; ++c)
        {
            pA->m_linear[c] += impulse * pA->m_invMass * pRow->m_normal[c];
            pB->m_linear[c] -= impulse * pB->m_invMass * pRow->m_normal[c];
            pA->m_angular[c] += impulse * pA->m_direction[c] * pRow->m_vel0[c];
            pB->m_angular[c] += impulse * pB->m_direction[c] * pRow->m_vel1[c];
        }
        pAccumulators[i] += impulse;
    }
}
