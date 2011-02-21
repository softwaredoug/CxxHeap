//********************************************************************
//  FILE NAME:      Pqueue.h
//
//  DESCRIPTION:    Implentation of a priority queue
//*********************************************************************

#ifndef PQUEUE_20100810_H
#define PQUEUE_20100810_H

#include "HeapUtils.h"
#include "Heap.h"

namespace pqueue
{
	//! Class responsible for keeping elements in a queue in order 
	//! of priority
	template <class T>
	class CPqueue  : public boost::noncopyable
	{
	public:
		//************************************************************************
		//! @details
		//!   Construct a priority queue with an initial sort order
		//! @param[in] sortOrder
		//!    how to sort the queued elements
		//!************************************************************************
		CPqueue( const typename CHeap<T>::ISortOrderPtr& sortOrder) : m_heap(new CHeap<T>(sortOrder))
		{

		}

		//************************************************************************
		//! @details
		//!   Place a new item in line in the priority queue based on the current
		//!  sort order
		//!
		//! @param[in] newItem
		//!   
		//! @return void
		//! 
		//!************************************************************************
		void Push(const T& newItem)
		{
			m_heap->Insert(newItem);
		}

		//************************************************************************
		//! @details
		//!   Remove the front of the priority queue
		//! 
		//!************************************************************************
		void PopFront()
		{
			m_heap->PopTop();
		}

		//************************************************************************
		//! @details
		//!   Look at the front of the priority queue
		//! 
		//! @return const T&
		//!    the element in the front of the priority queue
		//!************************************************************************
		const T& PeekFront() const
		{
			return m_heap->PeekTop();
		}

		//************************************************************************
		//! @details
		//!   Rearrange the elements based on the new sort order 
		//!
		//! @param[in] sortOrder
		//!		new sort order to apply
		//!
		//!************************************************************************
		void ChangeSortOrder(const typename CHeap<T>::ISortOrderPtr& sortOrder)
		{
			// move everything to a new heap based on the sort order
			std::auto_ptr<CHeap<T>> newHeap(new CHeap<T>(sortOrder));
			Reheapify(*newHeap, *m_heap);
			// take ownership of this newly created ptr, release old heap
			// that is now empty
			m_heap = newHeap;
		}


	private:
		std::auto_ptr< CHeap<T> > m_heap;		//!< Heap containing all the elements


	};
}

#endif