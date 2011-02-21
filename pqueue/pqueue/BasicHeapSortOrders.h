//********************************************************************
//  FILE NAME:      BasicHeapSortOrders.h
//
//  DESCRIPTION:    Contains the basic sort orders used in a heap,
//					the less than sort order, greater than sort order
//					and the composite sort order.
//*********************************************************************
#ifndef BASIC_HEAP_SORT_ORDERS_20100814_H
#define BASIC_HEAP_SORT_ORDERS_20100814_H

#include "CustomSortPred.h"

namespace pqueue
{

	//! Sort that sorts how you would expect it to sort
	//! by putting the largest on top based on std::less
	template <class T>
	class CStdLessSortOrder : public ISortOrder<T>
	{
	public:
		//************************************************************************
		//! @details
		//!   Implement LessThan how it would be expected to work for a given T 
		//!
		//! @param[in] lhs - lhs of the < operator
		//! @param[in] rhs - rhs of the < operator
		//! 
		//! @return bool
		//!  true if lhs < rhs based on evaluation of std::less, false otherwise
		//!************************************************************************
		bool LessThan(const T& lhs, const T& rhs) const
		{
			std::less<T> stdLessPred;
			return stdLessPred(lhs, rhs);
		}
	};

	//! Sort that sorts probably the opposite you would expect
	//! by putting the smallest on top based on std::greater
	template <class T>
	class CStdGreaterSortOrder : public ISortOrder<T>
	{
	public:
		//************************************************************************
		//! @details
		//!   Implement LessThan the opposite of how it would be expected to 
		//!  work for a given T 
		//!
		//! @param[in] lhs - lhs of the < operator
		//! @param[in] rhs - rhs of the < operator
		//! 
		//! @return bool
		//!  true if rhs < lhs based on evaluation of std::greater, false otherwise
		//!************************************************************************
		bool LessThan(const T& lhs, const T& rhs) const
		{
			std::greater<int> stdGreaterPred;
			return stdGreaterPred(lhs, rhs);
		}
	};

	//! Uses a list of sort orders to sort on multiple criteria
	//! comparison occurs by checking the first value, if that
	//! is equal, check the second value, etc
	template <class T>
	class CCompositeSortOrder : public ISortOrder<T>
	{
	private: 
		typedef boost::shared_ptr< ISortOrder<T> > ISortOrderPtr;
		std::vector< ISortOrderPtr > m_sortCriteria;
	public:
		//************************************************************************
		//! @details
		//!   Construct the composite sort order with a vector of other sort
		//!  orders.
		//!
		//! @param[in] sorts
		//!   sort orders to use 
		//!************************************************************************
		CCompositeSortOrder(const std::vector< ISortOrderPtr >& sorts) : 
		  m_sortCriteria(sorts)
		{
		}

		//************************************************************************
		//! @details
		//!		Compare lhs and rhs first by comparing the first item in the 
		//!	comparison criteria, than the second, than the 3rd
		//!
		//! @param[in] lhs
		//!		lhs of the "<" operation
		//! @param[in] rhs
		//!		rhs of the "<" operation
		//!
		//! @return bool
		//!   true if lhs < rhs based on the definition of this sort order
		//!************************************************************************
		bool LessThan(const T& lhs, const T& rhs) const
		{
			std::vector< ISortOrderPtr >::const_iterator currSort = m_sortCriteria.begin();
			for (; currSort != m_sortCriteria.end(); ++currSort)
			{
				// If lhs < rhs for this sort then return true
				if ((*currSort)->LessThan(lhs, rhs))
				{
					return true;
				}
				// if lhs > rhs, then return falze
				else if ((*currSort)->LessThan(rhs, lhs))
				{
					return false;
				}
				// if neither, they are equal, continue to the next 
				// item to consider
			}
			// if we got here, all sorts are equal, return false
			return false;

		}
	};
};



#endif