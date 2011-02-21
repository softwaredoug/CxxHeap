//********************************************************************
//  FILE NAME:      Heap.h
//
//  DESCRIPTION:    Representation of a heap. A heap is a data structure
//					where the "largest" item (as defined by a custom sort 
//					order) is on top.
//*********************************************************************
#ifndef HEAP_20100810_H
#define HEAP_20100810_H

#include "CompleteTree.h"
#include "CompleteTreeUtils.h"
#include "CustomSortPred.h"
#include <boost/noncopyable.hpp>

namespace pqueue
{
	//! Responsible for representing a heap and keeping the "largest" item
	//! on top
	template <class T>
	class CHeap : public boost::noncopyable
	{
	public:
		typedef boost::shared_ptr< ISortOrder< T > > ISortOrderPtr; //!< typedef for a sort order for T.

	public:
		//************************************************************************
		//! @details
		//!  Heap constructor
		//!  
		//! @param[in] sortOrder
		//!		sort order, defines how items are to be sorted. Using this the 
		//!		"largest" item will be placed on top
		//!************************************************************************
		CHeap(const ISortOrderPtr sortOrder) : m_sortOrder(sortOrder)  {}

		  //************************************************************************
		  //! @details
		  //!   Insert t into the heap. If t is the "largest" item in the heap it 
		  //!	will immediately move to the top.
		  //!  
		  //! @param[in] t
		  //!	item to insert into the heap
		  //!************************************************************************
		  void Insert(const T& t)
		  {
			  m_tree.Append(t);
			  TreeIter_t backOfCompleteTree = m_tree.GetLastNode();
			  BubbleUp(backOfCompleteTree);
		  }

		  //! Exception thrown if an empty heap is accessed
		  class CCannotAccessEmptyHeap {};

		  //************************************************************************
		  //! @details
		  //!   Peek at the top of the heap
		  //! 
		  //! @return const T&
		  //!    A reference to the top of the heap
		  //!
		  //! @throw CCannotAccessEmptyHeap
		  //!	thrown on access of empty heap, you can avoid this by checking size
		  //!	first.
		  //!************************************************************************
		  const T& PeekTop() const
		  {
			  if (m_tree.GetSize() == 0)
			  {
				  throw CCannotAccessEmptyHeap();
			  }
			  else
			  {
				  TreeIter_t root = m_tree.GetRootNode();
				  return root.GetValue();
			  }
		  }

		  //************************************************************************
		  //! @details
		  //!    Discard the top of the heap. The next "largest" item in the heap
		  //! will now be placed on top.
		  //!************************************************************************
		  void PopTop()
		  {
			  if (m_tree.GetSize() == 0)
			  {
				  throw CCannotAccessEmptyHeap();
			  }
			  else
			  {
				  TreeIter_t root = m_tree.GetRootNode();
				  TreeIter_t lastInserted = m_tree.GetLastNode();
				  SwapNodeValues<T>(root, lastInserted);
				  m_tree.EraseLastNode();
				  SiftDown(root);
			  }
		  }

		  //************************************************************************
		  //! @details
		  //!    Determine the number of elements stored in the heap
		  //! @return size_t
		  //!    the size of the heap
		  //!************************************************************************
		  std::size_t GetSize()
		  {
			  return m_tree.GetSize();
		  }


	private:
		CCompleteTree<T> m_tree;		//!< Representation of the heap as a complete tree
		typedef typename CCompleteTree<T>::Iterator TreeIter_t;
		CWrappedCustomSortPred<T> m_sortOrder;	//!< Sort order wrapped in a predicate for use with std::max, etc

		//************************************************************************
		//! @details
		//!   Determine if the parent and the child are in the correct sort order
		//!  (ie a parent should always be "larger" than the child)
		//!
		//! @param[in] parent
		//!   the parent node to consider
		//! @param[in] child
		//!	  the child node to consider
		//! @return bool
		//!    true if parent is "larger" than child, false otherwise
		//!************************************************************************
		bool AreNodesInSortOrder(const TreeIter_t& parent, const TreeIter_t& child) const
		{
			// if child < parent
			if (m_sortOrder(child.GetValue(), parent.GetValue()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//************************************************************************
		//! @details
		//!   Keep moving currLoc up until it is "less than" it's parent but "larger"
		//!	than it's child
		//!
		//! @param[in] currLoc
		//!   The node we are currently examining
		//!************************************************************************
		void BubbleUp(TreeIter_t& currLoc )
		{
			if (currLoc == m_tree.GetRootNode())
			{
				return;
			}
			else
			{
				TreeIter_t child = currLoc;
				TreeIter_t parent = currLoc;
				parent.GoUp();
				if (AreNodesInSortOrder(parent, child))
				{
					return;
				}
				else
				{
					SwapNodeValues<T>(parent, child);
					BubbleUp(parent);
				}
				
			}
		}

		//************************************************************************
		//! @details
		//!   Keep moving currLoc down until it is "less than" it's parent but "larger"
		//!	than it's child... or its at the bottom of the tree
		//!
		//! @param[in] currLoc
		//!   node to move down
		//!************************************************************************
		void SiftDown(TreeIter_t currLoc)
		{
			//! Get all the nodes
			TreeIter_t parent = currLoc;
			TreeIter_t leftChild = currLoc;
			TreeIter_t rightChild = currLoc;
			leftChild.GoLeftChild();
			rightChild.GoRightChild();

			// Between the three nodes, the "largest" needs to go on top
			TreeIter_t biggestNode = PickLargestIterator<T>(parent, leftChild, rightChild, m_sortOrder);
			if (biggestNode == parent)
			{
				return;
			}
			assert(biggestNode.IsStillInTree());
			SwapNodeValues<T>(parent, biggestNode);
			// after swap, biggestNode now holds the value of the parent and is no longer bigger
			SiftDown(biggestNode);
		}


	};
}
#endif