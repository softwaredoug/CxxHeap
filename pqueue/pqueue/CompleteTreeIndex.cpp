//********************************************************************
//  FILE NAME:      CompleteTreeIndex.cpp
//
//  DESCRIPTION:    Contains definition of complete tree index class
//					which represents an index into a complete tree
//*********************************************************************
#include "stdafx.h"
#include "CompleteTreeIndex.h"
#include "assert.h"

namespace pqueue
{
	//************************************************************************
	//! @details
	//!   Constructor of the complete tree index.
	//!
	//! @param[in] arrayIndex
	//!   Index into an array representing the complete tree
	//!************************************************************************
	CCompleteTreeIndex::CCompleteTreeIndex(const boost::uint32_t& arrayIndex) : 
		m_oneBasedIndex(arrayIndex + 1)
	{
	}


	//************************************************************************
	//! @details
	//!   Destructor for the complete tree
	//!************************************************************************
	CCompleteTreeIndex::~CCompleteTreeIndex()
	{

	}

	//************************************************************************
	//! @details
	//!   Access the integer array index corresponding to the location of
	//! this index in the tree.
	//! 
	//! @return boost::uint32_t
	//!  0-based array index
	//!************************************************************************
	boost::uint32_t CCompleteTreeIndex::GetCurrentLocationInArray() const
	{
		assert(m_oneBasedIndex != 0); // its one based, this should never happen
		return m_oneBasedIndex - 1;
	}

	//************************************************************************
	//! @details
	//!   Set this index to be the index of it's left child
	//!************************************************************************
	void CCompleteTreeIndex::MoveToLeft()
	{
		m_oneBasedIndex *= 2;
	}

	//************************************************************************
	//! @details
	//!   Set this index to be the index of it's right child
	//!************************************************************************
	void CCompleteTreeIndex::MoveToRight()
	{
		m_oneBasedIndex *= 2;
		++m_oneBasedIndex;
	}

	//************************************************************************
	//! @details
	//!   Set this index to be the index of it's parent
	//!************************************************************************
	void CCompleteTreeIndex::MoveToParent()
	{
		m_oneBasedIndex /= 2;
	}
}