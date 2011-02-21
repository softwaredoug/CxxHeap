//********************************************************************
//  FILE NAME:      CompleteTreeUtils.h
//
//  DESCRIPTION:    Contains utilities that can be used on the 
//					complete tree data structure.
//
//*********************************************************************

#ifndef COMPLETE_TREE_UTILS_20100810_H
#define COMPLETE_TREE_UTILS_20100810_H

#include "CompleteTree.h"

namespace pqueue 
{

	//************************************************************************
	//! @details
	//!   From a complete tree of T, use an instance of CompareT to figure out
	//!  which of the two iterators comes first
	//! 
	//! @param[] iter1
	//! @param[] iter2
	//! @param[] compPred
	//! 
	//! @return ::Iterator
	//! 
	//!************************************************************************
	template <class T, class CompareT>
	typename CCompleteTree<T>::Iterator PickLargestIterator(const typename CCompleteTree<T>::Iterator& iter1, const typename CCompleteTree<T>::Iterator& iter2, const CompareT& compPred)
	{
		if (iter1.IsStillInTree() && iter2.IsStillInTree())
		{
			T bestT = std::max<T>(iter1.GetValue(), iter2.GetValue(), compPred);
			// use the predicate to determine equality
			bool isEqual = !(compPred(bestT, iter1.GetValue()) || compPred(iter1.GetValue(), bestT));
			if (isEqual)
			{
				return iter1;
			}
			else
			{
				return iter2;
			}
		}
		else if (iter1.IsStillInTree())
		{
			return iter1;
		}
		else if (iter2.IsStillInTree())
		{
			return iter2;
		}
		else
		{
			return iter1;
		}

	}

	//************************************************************************
	//! @details
	//!   Out of 3 iterators, pick the iterator with the "largest" value based
	//!  on the comparison predicate.
	//!
	//! @param[in] iter1 - first item to compare
	//! @param[in] iter2 - second item to compare
	//! @param[in] iter3 - third item to compare
	//! @param[in] compPred
	//!		predicate used for comparison
	//!
	//! @return ::Iterator
	//!     The "largest" of the 3 iterators
	//!************************************************************************
	template <class T, class CompareT>
	typename CCompleteTree<T>::Iterator PickLargestIterator(const typename CCompleteTree<T>::Iterator& iter1, const typename CCompleteTree<T>::Iterator& iter2, const typename CCompleteTree<T>::Iterator& iter3, const CompareT& compPred)
	{
		return PickLargestIterator<T>(PickLargestIterator<T>(iter1, iter2, compPred), iter3, compPred);
	}

	//************************************************************************
	//! @details
	//!   Given two iterators into a complete tree, swap the node values 
	//!
	//! @param[in,out] iter1
	//!		first iterator to swap. After this function this will contain
	//!		the value in iter2.
	//! @param[in,out] iter2
	//!	    second iterator to swap After this function, this will contain
	//      the value in iter1
	//!************************************************************************
	template <class T>
	void SwapNodeValues(typename CCompleteTree<T>::Iterator& iter1, typename CCompleteTree<T>::Iterator& iter2)
	{
		T temp = iter1.GetValue();
		iter1.SetValue(iter2.GetValue());
		iter2.SetValue(temp);
	}

}

#endif