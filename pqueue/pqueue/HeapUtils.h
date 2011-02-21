//********************************************************************
//  FILE NAME:      HeapUtils.h
//
//  DESCRIPTION:    Set of utility functions to be applied
//					on heaps
//*********************************************************************
#ifndef HEAP_UTILS_20100823_H
#define HEAP_UTILS_20100823_H

namespace pqueue
{
	//************************************************************************
	//! @details
	//!   Empty one heap and place it's elements into the destination heap 
	//!
	//! @param[in,out] src
	//!		src heap that will be emptied
	//! @param[out] dest
	//!		dest heap that will hold all of src's elems
	//! 
	//! @return void
	//! 
	//!************************************************************************
	template <class T>
	void Reheapify(CHeap<T>&dest, CHeap<T>&src)
	{
		//! @remark
		//! get the size first, if we are stupidly reheapifying to
		//! ourselves and are doing while (src.GetSize() > 0) then
		//! we will go into an infinite loop because we constantly
		//! pop and reinsert into ourselves
		unsigned int currSize = src.GetSize();
		while (currSize > 0)
		{
			dest.Insert( src.PeekTop() );
			src.PopTop();
			--currSize;
		}
	}
}

#endif