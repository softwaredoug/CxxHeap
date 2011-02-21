//********************************************************************
//  FILE NAME:      CustomSortPred.h
//
//  DESCRIPTION:    Contains the declaration of the custom sort 
//					predicate
//*********************************************************************

#ifndef CUSTOM_SORT_PRED_20100814_H
#define CUSTOM_SORT_PRED_20100814_H

namespace pqueue
{

	// Interface for a sort of T
	template <class T>
	class ISortOrder
	{
	public:
		//! What the heap uses to determine what is "larger" so if lhs < rhs, rhs will
		//! appear higher up in the heap
		virtual bool LessThan(const T& lhs, const T& rhs) const = 0;
	};

	// Wrapper for the above interface to use in templates such
	// as std::max, etc. By default these won't work through a virtual interface
	// because they pass the predicate by value, not by reference
	template <class T>
	class CWrappedCustomSortPred
	{
	private:
		typedef boost::shared_ptr< ISortOrder<T> > ISortOrderPtr;
		ISortOrderPtr m_customizedSort;	//!< wrapped sort
	public:
		//************************************************************************
		//! @details
		//!   Construct wrapped predicate 
		//!
		//! @param[in] customSort
		//!	  pointer to sort to wrap
		//!************************************************************************
		CWrappedCustomSortPred(const ISortOrderPtr& customSort) : 
		  m_customizedSort(customSort)
		{
		}

		//************************************************************************
		//! @details
		//!		Change the custom sort being wrapped to the input class
		//! @param[in] customSort
		//!		new custom sort to wrap
		//!************************************************************************
		void SetCustomSort(const ISortOrderPtr& customSort)
		{
			m_customizedSort = customSort;
		}

		//************************************************************************
		//! @details
		//!	  Evaluate whether lhs is "<" rhs   
		//!
		//! @param[in] lhs - lhs of the < operator
		//! @param[in] rhs - rhs of the < operator
		//! 
		//! @return bool
		//!  true if lhs < rhs
		//!************************************************************************
		bool operator()(const T& lhs, const T& rhs) const
		{
			return m_customizedSort->LessThan(lhs, rhs);
		}
	};
}

#endif