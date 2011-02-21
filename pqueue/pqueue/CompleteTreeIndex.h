//********************************************************************
//  FILE NAME:      CompleteTreeIndex.h
//
//  DESCRIPTION:    Contains declaration for complete tree index class
//					which represents an index into a complete tree
//*********************************************************************

#ifndef COMPLETE_TREE_INDEX_20100811_H
#define COMPLETE_TREE_INDEX_20100811_H

#include <boost/cstdint.hpp>

namespace pqueue
{
	//! Responsible for representing an index in an array-based complete tree
	//! -- it will go on forever, the user must decide if the index has wandered off
	//! -- the tree
	class CCompleteTreeIndex
	{
	public:
		//! Construct a complete tree ind
		CCompleteTreeIndex(const boost::uint32_t& arrayIndex);
		~CCompleteTreeIndex();

		//! Return the index into the complete tree's array 
		boost::uint32_t GetCurrentLocationInArray() const;

		//! Change this index to be the index where it's left child would be
		void MoveToLeft();

		//! Change this index to be the index where it's right child would be
		void MoveToRight();

		//! Change this index to be the index where it's parent would be
		void MoveToParent();
	private:
		boost::uint32_t m_oneBasedIndex;		//! The index in the complete tree's ( internally stored as a 1-based index)


	};
}

#endif