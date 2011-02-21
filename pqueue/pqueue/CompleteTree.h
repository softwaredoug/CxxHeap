//********************************************************************
//  FILE NAME:      CompleteTree.h
//
//  DESCRIPTION:    Contains implementation of complete tree templated
//					class. A complete tree is a tree where each level
//					is filled in from left to right before a node is
//					inserted on the next level.
//
//*********************************************************************
#ifndef COMPLETE_TREE_20100810_H
#define COMPLETE_TREE_20100810_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/cstdint.hpp>

#include "CompleteTreeIndex.h"

namespace pqueue
{

	//! Representns a tree that follows the completeness principle
	//! specified in the hw spec, ie that for any N, all trees of
	//! size N have the same layout. Trees are built up left-to-right on
	//! the current level until that level is filled. Then the next level
	//! will begin to be filled in left-to-right
	template <class T>
	class CCompleteTree  : public boost::noncopyable
	{
	public:

		// Responsible for representing a current location
		// within the complete tree
		class Iterator
		{
		private:
			// noncopyable
			boost::weak_ptr< std::vector<T> > m_parentTree;	//!< Access to the parent's tree
			CCompleteTreeIndex m_locationInTree;			//!< Where I am in the tree
		public:
			//! Exceptions encountered while traversing the tree	   
			class CIteratorInvalid {};
			class COutOfBounds {};

			//************************************************************************
			//! @details
			//!   Construct the iterator
			//! 
			//! @param[in] parentTree
			//!    pointer to the vector -- the internal reperesentation of the parent tree
			//! @param[in] locationInTree
			//!    the location of this iterator in the tree
			//! 
			//!************************************************************************
			Iterator(const boost::weak_ptr< std::vector<T> >& parentTree, 
				const CCompleteTreeIndex& locationInTree) : 
			  m_parentTree(parentTree),
			  m_locationInTree(locationInTree)
			{
			}

			//************************************************************************
			//! @details
			//!   Compare to iterators, return true if they point to the same location
			//! within the same tree.
			//!
			//! @param[in] lhs
			//!   the iterator to compare against.
			//! 
			//! @return bool
			//!   true if iterators point to the same location on the same tree, false
			//! otherwise
			//!************************************************************************
			bool operator ==(const Iterator& lhs) const
			{
				if (lhs.m_locationInTree.GetCurrentLocationInArray() == m_locationInTree.GetCurrentLocationInArray())
				{
					boost::shared_ptr<std::vector<T>> lhsTreePtr = lhs.m_parentTree.lock();
					boost::shared_ptr<std::vector<T>> thisTreePtr = m_parentTree.lock();
					if (lhsTreePtr == thisTreePtr)
					{
						return true;
					}
				}
				return false;

			}

			//************************************************************************
			//! @details
			//!   Point this iterator at it's right child. NOTE this could push you
			//!  out of the tree.
			//! 
			//!************************************************************************
			void GoRightChild()
			{
				m_locationInTree.MoveToRight();
			}

			//************************************************************************
			//! @details
			//!   Point this iterator at it's left child. NOTE this could push you
			//!  out of the tree.
			//! 
			//!************************************************************************
			void GoLeftChild()
			{
				m_locationInTree.MoveToLeft();
			}

			
			//************************************************************************
			//! @details
			//!   Point this iterator at it's parent. Performing this operation on
			//! the root node keeps you at the root node
			//!************************************************************************
			void GoUp()
			{
				m_locationInTree.MoveToParent();
			}

			//************************************************************************
			//! @return bool
			//!   true if this iterator is within the bounds of the tree, false if
			//! we've wandered off the tree
			//!
			//! @throw
			//!   CIteratorInvalid if we are an iterator for a deleted tree
			//!************************************************************************
			bool IsStillInTree() const
			{
				boost::shared_ptr< std::vector<T> > parentTree = m_parentTree.lock();
				if (parentTree)
				{
					return (m_locationInTree.GetCurrentLocationInArray() < parentTree->size());
				}
				else
				{
					throw CIteratorInvalid();
				}
			}

			
			//************************************************************************
			//! @details
			//!   Access the contents pointed at by this iterator
			//! @return T
			//!   Data pointed at by this iterator
			//! @throw
			//!   COutOfBounds if this iterator is outside the bounds of the tree
			//!   CIteratorInvalid if this iterator is pointing into a tree that
			//!    no longer exists. Thrown by IsStillInTree()
			//!************************************************************************
			const T& GetValue() const
			{
				boost::shared_ptr< std::vector<T> > parentTree = m_parentTree.lock();
				if (IsStillInTree())
				{
					return (*parentTree)[m_locationInTree.GetCurrentLocationInArray()];
				}
				else
				{
					throw COutOfBounds();
				}
			}

			
			//************************************************************************
			//! @details
			//!  Set the value pointed at by this iterator
			//!  
			//! @param[in] val
			//!   The value to assign 
			//!
			//! @throw
			//!   COutOfBounds if outside the bounds of the tree
			//!   CIteratorInvalid if this iterator is pointing into a tree that
			//!    no longer exists. Thrown by IsStillInTree.
			//!************************************************************************
			void SetValue(const T& val)
			{
				boost::shared_ptr< std::vector<T> > parentTree = m_parentTree.lock();
				if (IsStillInTree())
				{
					(*parentTree)[m_locationInTree.GetCurrentLocationInArray()] = val;
				}
				else
				{
					throw COutOfBounds();
				}
			}
		};

		//************************************************************************
		//! @details
		//!   Construct a new complete tree.
		//!************************************************************************
		CCompleteTree() : m_tree(new std::vector<T>) {}


		//************************************************************************
		//! @details
		//!    Destroy a complete tree
		//!************************************************************************
		~CCompleteTree() {}


		//************************************************************************
		//! @details
		//!   Access an Iterator to the top-most node
		//! 
		//! @return Iterator
		//!   Iterator pointing at root node
		//!************************************************************************
		Iterator GetRootNode() const
		{
			const CCompleteTreeIndex rootNodeLocation(0);
			Iterator rVal(m_tree, rootNodeLocation);
			return rVal;
		}


		//************************************************************************
		//! @details
		//!   Access iterator to the last appended node. This will be the right
		//! most child of the bottom level.
		//! 
		//! @return Iterator
		//!   Iterator to last inserted node
		//!************************************************************************
		Iterator GetLastNode() const
		{
			const CCompleteTreeIndex lastInsertedNodeLocationInVector(m_tree->size() - 1);
			Iterator rVal(m_tree, lastInsertedNodeLocationInVector);
			return rVal;
		}

		class CCannotEraseFromEmptyCompleteTree {};

		//************************************************************************
		//! @details
		//!  Erase the last appended node. This will remove the right most child 
		//! on the bottom level
		//! 
		//! @throw
		//!   CCannotEraseFromEmptyCompleteTree if tree is empty
		//!************************************************************************
		void EraseLastNode()
		{
			if (GetSize() > 0)
			{
				m_tree->pop_back();
			}
			else
			{
				throw CCannotEraseFromEmptyCompleteTree();
			}
		}

		//************************************************************************
		//! @details
		//!   Place this value at the back of the complete tree -- the next place
		//! available for insertion will be on the bottom level in the next spot
		//! to the right.
		//!
		//! @param[in] val
		//!   Value to store
		//!
		//!************************************************************************
		void Append(const T& val)
		{
			m_tree->push_back(val);
		}

		//************************************************************************
		//! @details
		//!   Return the number of elements in the complete tree
		//! 
		//! @return std::size_t
		//!   Number of elements in the complete tree.
		//!************************************************************************
		std::size_t GetSize() const
		{
			return m_tree->size();
		}

	private:	
		boost::shared_ptr<std::vector<T>> m_tree;		//!< array representation of the tree

	};
}

#endif