// src/game/UTFSpore_Win32/red_black_tree.cpp -- migrated from slice(s) s009215c0, s009205e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/red_black_tree.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>
#include <stddef.h>
#include <string.h>

// ---- items of slice s009205e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RBNode { RBNode* mpRight; RBNode* mpLeft; RBNode* mpParent; };
// ---- items of slice s009205e0 end

// ---- items of slice s009215c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
#define EASTL_API
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
namespace eastl {
enum { kRBTreeColorRed = 0, kRBTreeColorBlack = 1 };
}
namespace eastl {
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
}
namespace eastl {
rbtree_node_base* RBTreeGetMinChild(const rbtree_node_base* p){ while (p->mpNodeLeft) p = p->mpNodeLeft; return const_cast<rbtree_node_base*>(p); }
}
namespace eastl {
rbtree_node_base* RBTreeGetMaxChild(const rbtree_node_base* p){ while (p->mpNodeRight) p = p->mpNodeRight; return const_cast<rbtree_node_base*>(p); }
}
namespace eastl {
template <class T> void swap(T& a, T& b){ T t = a; a = b; b = t; }
}
// ---- items of slice s009215c0 end

// @ 0x00921580
RBNode* RBTreeIncrement(RBNode* n)
{
    if (n->mpRight != 0) {
        n = n->mpRight;
        while (n->mpLeft != 0)
            n = n->mpLeft;
        return n;
    }
    RBNode* p = n->mpParent;
    while (n == p->mpRight) {
        n = p;
        p = p->mpParent;
    }
    if (n->mpRight != p)
        n = p;
    return n;
}

// @ 0x009215c0
namespace eastl {
rbtree_node_base* RBTreeDecrement(const rbtree_node_base* pNode)
{
    if (pNode->mpNodeParent->mpNodeParent == pNode && pNode->mColor == kRBTreeColorRed)
        return pNode->mpNodeRight;
    if (pNode->mpNodeLeft)
        return RBTreeGetMaxChild(pNode->mpNodeLeft);
    rbtree_node_base* p = pNode->mpNodeParent;
    while (pNode == p->mpNodeLeft) { pNode = p; p = p->mpNodeParent; }
    return p;
}
}  // namespace eastl

// @ 0x00921600
namespace eastl {
rbtree_node_base* RBTreeRotateLeft(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
{
    rbtree_node_base* const pNodeTemp = pNode->mpNodeRight;
    pNode->mpNodeRight = pNodeTemp->mpNodeLeft;
    if (pNodeTemp->mpNodeLeft) pNodeTemp->mpNodeLeft->mpNodeParent = pNode;
    pNodeTemp->mpNodeParent = pNode->mpNodeParent;
    if (pNode == pNodeRoot) pNodeRoot = pNodeTemp;
    else if (pNode == pNode->mpNodeParent->mpNodeLeft) pNode->mpNodeParent->mpNodeLeft = pNodeTemp;
    else pNode->mpNodeParent->mpNodeRight = pNodeTemp;
    pNodeTemp->mpNodeLeft = pNode;
    pNode->mpNodeParent = pNodeTemp;
    return pNodeRoot;
}
}  // namespace eastl

// @ 0x00921650
namespace eastl {
rbtree_node_base* RBTreeRotateRight(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
{
    rbtree_node_base* const pNodeTemp = pNode->mpNodeLeft;
    pNode->mpNodeLeft = pNodeTemp->mpNodeRight;
    if (pNodeTemp->mpNodeRight) pNodeTemp->mpNodeRight->mpNodeParent = pNode;
    pNodeTemp->mpNodeParent = pNode->mpNodeParent;
    if (pNode == pNodeRoot) pNodeRoot = pNodeTemp;
    else if (pNode == pNode->mpNodeParent->mpNodeRight) pNode->mpNodeParent->mpNodeRight = pNodeTemp;
    else pNode->mpNodeParent->mpNodeLeft = pNodeTemp;
    pNodeTemp->mpNodeRight = pNode;
    pNode->mpNodeParent = pNodeTemp;
    return pNodeRoot;
}
}  // namespace eastl

// @ 0x009216a0
namespace eastl {
EASTL_API void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, RBTreeSide insertionSide)
{
		rbtree_node_base*& pNodeRootRef = pNodeAnchor->mpNodeParent;

		// Initialize fields in new node to insert.
		pNode->mpNodeParent = pNodeParent;
		pNode->mpNodeRight  = NULL;
		pNode->mpNodeLeft   = NULL;
		pNode->mColor       = kRBTreeColorRed;

		// Insert the node.
		if(insertionSide == kRBTreeSideLeft)
		{
			pNodeParent->mpNodeLeft = pNode; // Also makes (leftmost = pNode) when (pNodeParent == pNodeAnchor)

			if(pNodeParent == pNodeAnchor)
			{
				pNodeAnchor->mpNodeParent = pNode;
				pNodeAnchor->mpNodeRight = pNode;
			}
			else if(pNodeParent == pNodeAnchor->mpNodeLeft)
				pNodeAnchor->mpNodeLeft = pNode; // Maintain leftmost pointing to min node
		}
		else
		{
			pNodeParent->mpNodeRight = pNode;

			if(pNodeParent == pNodeAnchor->mpNodeRight)
				pNodeAnchor->mpNodeRight = pNode; // Maintain rightmost pointing to max node
		}

		// Rebalance the tree.
		while((pNode != pNodeRootRef) && (pNode->mpNodeParent->mColor == kRBTreeColorRed)) 
		{
			
			rbtree_node_base* const pNodeParentParent = pNode->mpNodeParent->mpNodeParent;

			if(pNode->mpNodeParent == pNodeParentParent->mpNodeLeft) 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeRight;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					if(pNode->mpNodeParent && pNode == pNode->mpNodeParent->mpNodeRight) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateLeft(pNode, pNodeRootRef);
					}

					
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateRight(pNodeParentParent, pNodeRootRef);
				}
			}
			else 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeLeft;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					

					if(pNode == pNode->mpNodeParent->mpNodeLeft) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateRight(pNode, pNodeRootRef);
					}

					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateLeft(pNodeParentParent, pNodeRootRef);
				}
			}
		}

		
		pNodeRootRef->mColor = kRBTreeColorBlack;

	}
}  // namespace eastl

// @ 0x00921880
namespace eastl {
EASTL_API void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor)
{
		rbtree_node_base*& pNodeRootRef      = pNodeAnchor->mpNodeParent;
		rbtree_node_base*& pNodeLeftmostRef  = pNodeAnchor->mpNodeLeft;
		rbtree_node_base*& pNodeRightmostRef = pNodeAnchor->mpNodeRight;
		rbtree_node_base*  pNodeSuccessor    = pNode;
		rbtree_node_base*  pNodeChild        = NULL;
		rbtree_node_base*  pNodeChildParent  = NULL;

		if(pNodeSuccessor->mpNodeLeft == NULL)         // pNode has at most one non-NULL child.
			pNodeChild = pNodeSuccessor->mpNodeRight;  // pNodeChild might be null.
		else if(pNodeSuccessor->mpNodeRight == NULL)   // pNode has exactly one non-NULL child.
			pNodeChild = pNodeSuccessor->mpNodeLeft;   // pNodeChild is not null.
		else 
		{
			// pNode has two non-null children. Set pNodeSuccessor to pNode's successor. pNodeChild might be NULL.
			pNodeSuccessor = pNodeSuccessor->mpNodeRight;

			while(pNodeSuccessor->mpNodeLeft)
				pNodeSuccessor = pNodeSuccessor->mpNodeLeft;

			pNodeChild = pNodeSuccessor->mpNodeRight;
		}

		// Here we remove pNode from the tree and fix up the node pointers appropriately around it.
		if(pNodeSuccessor == pNode) // If pNode was a leaf node (had both NULL children)...
		{
			pNodeChildParent = pNodeSuccessor->mpNodeParent;  // Assign pNodeReplacement's parent.

			if(pNodeChild) 
				pNodeChild->mpNodeParent = pNodeSuccessor->mpNodeParent;

			if(pNode == pNodeRootRef) // If the node being deleted is the root node...
				pNodeRootRef = pNodeChild; // Set the new root node to be the pNodeReplacement.
			else 
			{
				if(pNode == pNode->mpNodeParent->mpNodeLeft) // If pNode is a left node...
					pNode->mpNodeParent->mpNodeLeft  = pNodeChild;  // Make pNode's replacement node be on the same side.
				else
					pNode->mpNodeParent->mpNodeRight = pNodeChild;
				// Now pNode is disconnected from the bottom of the tree (recall that in this pathway pNode was determined to be a leaf).
			}

			if(pNode == pNodeLeftmostRef) // If pNode is the tree begin() node...
			{
				// Because pNode is the tree begin(), pNode->mpNodeLeft must be NULL.
				// Here we assign the new begin() (first node).
				if(pNode->mpNodeRight && pNodeChild)
				{
					 // Logically pNodeChild should always be valid.
					pNodeLeftmostRef = RBTreeGetMinChild(pNodeChild); 
				}
				else
					pNodeLeftmostRef = pNode->mpNodeParent; // This  makes (pNodeLeftmostRef == end()) if (pNode == root node)
			}

			if(pNode == pNodeRightmostRef) // If pNode is the tree last (rbegin()) node...
			{
				// Because pNode is the tree rbegin(), pNode->mpNodeRight must be NULL.
				// Here we assign the new rbegin() (last node)
				if(pNode->mpNodeLeft && pNodeChild)
				{
					 // Logically pNodeChild should always be valid.
					pNodeRightmostRef = RBTreeGetMaxChild(pNodeChild);
				}
				else // pNodeChild == pNode->mpNodeLeft
					pNodeRightmostRef = pNode->mpNodeParent; // makes pNodeRightmostRef == &mAnchor if pNode == pNodeRootRef
			}
		}
		else // else (pNodeSuccessor != pNode)
		{
			// Relink pNodeSuccessor in place of pNode. pNodeSuccessor is pNode's successor.
			// We specifically set pNodeSuccessor to be on the right child side of pNode, so fix up the left child side.
			pNode->mpNodeLeft->mpNodeParent = pNodeSuccessor; 
			pNodeSuccessor->mpNodeLeft = pNode->mpNodeLeft;

			if(pNodeSuccessor == pNode->mpNodeRight) // If pNode's successor was at the bottom of the tree... (yes that's effectively what this statement means)
				pNodeChildParent = pNodeSuccessor; // Assign pNodeReplacement's parent.
			else
			{
				pNodeChildParent = pNodeSuccessor->mpNodeParent;

				if(pNodeChild)
					pNodeChild->mpNodeParent = pNodeChildParent;

				pNodeChildParent->mpNodeLeft = pNodeChild;

				pNodeSuccessor->mpNodeRight = pNode->mpNodeRight;
				pNode->mpNodeRight->mpNodeParent = pNodeSuccessor;
			}

			if(pNode == pNodeRootRef)
				pNodeRootRef = pNodeSuccessor;
			else if(pNode == pNode->mpNodeParent->mpNodeLeft)
				pNode->mpNodeParent->mpNodeLeft = pNodeSuccessor;
			else 
				pNode->mpNodeParent->mpNodeRight = pNodeSuccessor;

			// Now pNode is disconnected from the tree.

			pNodeSuccessor->mpNodeParent = pNode->mpNodeParent;
			swap(pNodeSuccessor->mColor, pNode->mColor);
		}

		// Here we do tree balancing as per the conventional red-black tree algorithm.
		if(pNode->mColor == kRBTreeColorBlack) 
		{ 
			while((pNodeChild != pNodeRootRef) && ((pNodeChild == NULL) || (pNodeChild->mColor == kRBTreeColorBlack)))
			{
				if(pNodeChild == pNodeChildParent->mpNodeLeft) 
				{
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeRight;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;
						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeRight;
					}

					if(((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor = kRBTreeColorRed;
							pNodeRootRef = RBTreeRotateRight(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeRight;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeRight) 
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						break;
					}
				} 
				else 
				{   
					// The following is the same as above, with mpNodeRight <-> mpNodeLeft.
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeLeft;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor        = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeLeft;
					}

					if(((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild       = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeLeft == NULL) || (pNodeTemp->mpNodeLeft->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor              = kRBTreeColorRed;

							pNodeRootRef = RBTreeRotateLeft(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeLeft;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeLeft) 
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						break;
					}
				}
			}

			if(pNodeChild)
				pNodeChild->mColor = kRBTreeColorBlack;
		}

	}
}  // namespace eastl
