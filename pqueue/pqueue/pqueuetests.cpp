//********************************************************************
//  FILE NAME:      Pqueuetests.cpp
//
//  DESCRIPTION:    Contains tests for the major pqueue classes
//
//*********************************************************************

#include "stdafx.h"
#include "PqueueTests.h"
#include "CompleteTree.h"
#include "CompleteTreeIndex.h"
#include "Heap.h"
#include "HeapUtils.h"
#include "BasicHeapSortOrders.h"
#include "Pqueue.h"
#include <assert.h>
#include <functional>
#include <string>


namespace pqueue
{
	//************************************************************************
	//! @details
	//!   Run the complete tree index class through a series of tests
	//! 
	//!************************************************************************
	void TestCompleteTreeIndex()
	{
		CCompleteTreeIndex treeIdx(0);
		treeIdx.MoveToLeft();
		treeIdx.MoveToLeft();
		treeIdx.MoveToLeft();
		assert(treeIdx.GetCurrentLocationInArray() == 7);
		treeIdx.MoveToParent();
		assert(treeIdx.GetCurrentLocationInArray() == 3);
		treeIdx.MoveToRight();
		assert(treeIdx.GetCurrentLocationInArray() == 8);
	}

	//************************************************************************
	//! @details
	//!   Run the complete tree class through a series of tests
	//!************************************************************************
	void TestCompleteTree()
	{
		CCompleteTree<int> m_testTree;
		m_testTree.Append(1);
		m_testTree.Append(2);
		m_testTree.Append(3);
		m_testTree.Append(4);

		//          1   (0
		//        2   3  (1,2
		//       4 5 6 7  (3
		//      8 9
		CCompleteTree<int>::Iterator iter = m_testTree.GetRootNode();
		iter.GoLeftChild();
		iter.GoLeftChild();
		assert(iter.GetValue() == 4);
		iter.GoUp();
		assert(iter.GetValue() == 2);
		iter.GoUp();
		assert(iter.GetValue() == 1);
	}


	//************************************************************************
	//! @details
	//!   Run the heap class through a series of tests
	//!************************************************************************
	void TestHeap()
	{
		// Start with standard heap sort order, largest items on top
		CHeap<int>::ISortOrderPtr sortOrder(new CStdLessSortOrder<int>());
		CHeap<int> aHeap( sortOrder );
		aHeap.Insert(5);
		assert(aHeap.PeekTop() == 5);
		aHeap.Insert(13);
		assert(aHeap.PeekTop() == 13);
		aHeap.Insert(17);
		assert(aHeap.PeekTop() == 17);
		aHeap.Insert(15);
		assert(aHeap.PeekTop() == 17);
		aHeap.Insert(3);
		assert(aHeap.PeekTop() == 17);
		aHeap.Insert(17);
		assert(aHeap.PeekTop() == 17);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 17);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 15);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 13);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 5);
		aHeap.PopTop();
		aHeap.Insert(3);
		aHeap.Insert(4);
		assert(aHeap.PeekTop() == 4);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 3);
		aHeap.PopTop();
		assert(aHeap.PeekTop() == 3);
		aHeap.PopTop();

		aHeap.Insert(50);
		assert(aHeap.PeekTop() == 50);
		aHeap.Insert(45);
		assert(aHeap.PeekTop() == 50);
		aHeap.Insert(40);
		assert(aHeap.PeekTop() == 50);
		aHeap.Insert(35);
		assert(aHeap.PeekTop() == 50);
		aHeap.Insert(55);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(30);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(25);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(20);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(10);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(12);
		assert(aHeap.PeekTop() == 55);
		aHeap.Insert(12);
		assert(aHeap.PeekTop() == 55);

		// change the sort order to smallest items at top. The 
		// reheapified items go into the new heap
		CHeap<int>::ISortOrderPtr gtSortOrder(new CStdGreaterSortOrder<int>());
		CHeap<int> reheaped(gtSortOrder);
		Reheapify<int>(reheaped, aHeap);
		assert(reheaped.PeekTop() == 10);
		reheaped.PopTop();
		assert(reheaped.PeekTop() == 12);
		reheaped.PopTop();
		assert(reheaped.PeekTop() == 12);
		reheaped.PopTop();
		assert(reheaped.PeekTop() == 20);
		reheaped.PopTop();
		assert(reheaped.PeekTop() == 25);
		reheaped.PopTop();
		assert(reheaped.PeekTop() == 30);
	}

	//! The following classes are to test the composite sorting

	//!
	struct CTestStruct
	{
		unsigned int criteriaA;
		double criteriaB;
		std::string criteriaC;

		CTestStruct(const unsigned int& critA, const double& critB, const std::string& critC) :
		criteriaA(critA), criteriaB(critB), criteriaC(critC)
		{

		}
	};

	typedef boost::shared_ptr< ISortOrder<CTestStruct> > ISortOrderTestStructPtr;

	//! Sort on criteria A
	class CSortOnCriteriaA : public ISortOrder<CTestStruct>
	{
	public:
		CSortOnCriteriaA() {}

		bool LessThan(const CTestStruct& lhs, const CTestStruct& rhs) const
		{
			return lhs.criteriaA < rhs.criteriaA;
		}
	};
	
	//! Sort on criteria B
	class CSortOnCriteriaB : public ISortOrder<CTestStruct>
	{
	public:
		CSortOnCriteriaB() {}

		bool LessThan(const CTestStruct& lhs, const CTestStruct& rhs) const
		{
			return lhs.criteriaB < rhs.criteriaB;
		}
	};

	//! Sort on criteria C
	class CSortOnCriteriaC : public ISortOrder<CTestStruct>
	{
	public:
		CSortOnCriteriaC() {}

		bool LessThan(const CTestStruct& lhs, const CTestStruct& rhs) const
		{
			return lhs.criteriaC < rhs.criteriaC;
		}
	};

	//************************************************************************
	//! @details
	//!   Run the heap through a series of tests using a composite sort
	//! 
	//!************************************************************************
	void TestCompositeSort()
	{
		// Different ways to sort a test struct
		ISortOrderTestStructPtr  criteriaASort(new CSortOnCriteriaA());
		ISortOrderTestStructPtr  criteriaBSort(new CSortOnCriteriaB());
		ISortOrderTestStructPtr  criteriaCSort(new CSortOnCriteriaC());

		// Sort on C then A then B
		std::vector< ISortOrderTestStructPtr > m_sortCriteria;
		m_sortCriteria.push_back(criteriaCSort);
		m_sortCriteria.push_back(criteriaASort);
		m_sortCriteria.push_back(criteriaBSort);
		ISortOrderTestStructPtr sortByCthenAthenB(new CCompositeSortOrder<CTestStruct>(m_sortCriteria));

		m_sortCriteria.clear();
		m_sortCriteria.push_back(criteriaASort);
		m_sortCriteria.push_back(criteriaBSort);
		m_sortCriteria.push_back(criteriaCSort);
		ISortOrderTestStructPtr sortByAThenBThenC(new CCompositeSortOrder<CTestStruct>(m_sortCriteria));

		CHeap< CTestStruct > testStructHeap( sortByCthenAthenB );
		testStructHeap.Insert( CTestStruct(1, 2.0, "Hello") );
		assert(testStructHeap.PeekTop().criteriaC == "Hello");
		testStructHeap.Insert( CTestStruct(1, 2.0, "ZZZZZ") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		testStructHeap.Insert( CTestStruct(1, 3.0, "Hello") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		testStructHeap.Insert( CTestStruct(5, 2.0, "ZZZZZ") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		assert(testStructHeap.PeekTop().criteriaA == 5);

		testStructHeap.PopTop();
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		assert(testStructHeap.PeekTop().criteriaA == 1);
		assert(testStructHeap.PeekTop().criteriaB == 2.0);

		testStructHeap.PopTop();
		assert(testStructHeap.PeekTop().criteriaC == "Hello");
		assert(testStructHeap.PeekTop().criteriaA == 1);
		assert(testStructHeap.PeekTop().criteriaB == 3.0);

		testStructHeap.PopTop();
		assert(testStructHeap.PeekTop().criteriaC == "Hello");
		assert(testStructHeap.PeekTop().criteriaA == 1);
		assert(testStructHeap.PeekTop().criteriaB == 2.0);

		testStructHeap.Insert( CTestStruct(1, 2.0, "Hello") );
		assert(testStructHeap.PeekTop().criteriaC == "Hello");
		testStructHeap.Insert( CTestStruct(1, 2.0, "ZZZZZ") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		testStructHeap.Insert( CTestStruct(1, 3.0, "Hello") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		testStructHeap.Insert( CTestStruct(5, 2.0, "ZZZZZ") );
		assert(testStructHeap.PeekTop().criteriaC == "ZZZZZ");
		assert(testStructHeap.PeekTop().criteriaA == 5);

		CHeap<CTestStruct> reheapedTestStructHeap(sortByAThenBThenC);
		Reheapify(reheapedTestStructHeap, testStructHeap);		

		assert(reheapedTestStructHeap.PeekTop().criteriaA == 5);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "ZZZZZ");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 3.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "Hello");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "ZZZZZ");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "Hello");

		// Test reheapifying to myself, this might be dumb,
		// but we should make sure it doesn't break anything
		reheapedTestStructHeap.Insert( CTestStruct(1, 2.0, "Hello") );
		reheapedTestStructHeap.Insert( CTestStruct(1, 2.0, "ZZZZZ") );
		reheapedTestStructHeap.Insert( CTestStruct(1, 3.0, "Hello") );
		reheapedTestStructHeap.Insert( CTestStruct(5, 2.0, "ZZZZZ") );

		assert(reheapedTestStructHeap.PeekTop().criteriaA == 5);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "ZZZZZ");

		Reheapify(reheapedTestStructHeap, reheapedTestStructHeap);

		assert(reheapedTestStructHeap.PeekTop().criteriaA == 5);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "ZZZZZ");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 3.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "Hello");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "ZZZZZ");

		reheapedTestStructHeap.PopTop();
		assert(reheapedTestStructHeap.PeekTop().criteriaA == 1);
		assert(reheapedTestStructHeap.PeekTop().criteriaB == 2.0);
		assert(reheapedTestStructHeap.PeekTop().criteriaC == "Hello");



	}

	//************************************************************************
	//! @details
	//!   Run a bunch of tests on the priority queue class
	//!************************************************************************
	void TestPqueue()
	{
		// Different ways to sort a test struct
		ISortOrderTestStructPtr  criteriaASort(new CSortOnCriteriaA());
		ISortOrderTestStructPtr  criteriaBSort(new CSortOnCriteriaB());
		ISortOrderTestStructPtr  criteriaCSort(new CSortOnCriteriaC());

		// Sort on A then C then B
		std::vector< ISortOrderTestStructPtr > sortCriteria;
		sortCriteria.push_back(criteriaASort);
		sortCriteria.push_back(criteriaCSort);
		sortCriteria.push_back(criteriaBSort);
		ISortOrderTestStructPtr sortByAThenCThenB(new CCompositeSortOrder<CTestStruct>(sortCriteria));

		// Sort on C then B then A
		std::vector< ISortOrderTestStructPtr > sortCriteriaCBA;
		sortCriteriaCBA.push_back(criteriaCSort);
		sortCriteriaCBA.push_back(criteriaBSort);
		sortCriteriaCBA.push_back(criteriaASort);
		ISortOrderTestStructPtr sortByCThenBThenA(new CCompositeSortOrder<CTestStruct>(sortCriteriaCBA));

		pqueue::CPqueue<CTestStruct> pqueueOfTestStructs(sortByAThenCThenB);

		pqueueOfTestStructs.Push( CTestStruct(1/*A*/, 3.0/*B*/, "Tom"/*C*/));
		pqueueOfTestStructs.Push( CTestStruct(1/*A*/, 3.0/*B*/, "Dick"/*C*/));
		pqueueOfTestStructs.Push( CTestStruct(1/*A*/, 3.0/*B*/, "Harry"/*C*/));
		pqueueOfTestStructs.Push( CTestStruct(2/*A*/, 3.0/*B*/, "Harry"/*C*/));
		pqueueOfTestStructs.Push( CTestStruct(2/*A*/, 3.0/*B*/, "Sally"/*C*/));
		pqueueOfTestStructs.Push( CTestStruct(2/*A*/, 5.0/*B*/, "Sally"/*C*/));

		assert(pqueueOfTestStructs.PeekFront().criteriaA == 2);		
		assert(pqueueOfTestStructs.PeekFront().criteriaB == 5.0);
		assert(pqueueOfTestStructs.PeekFront().criteriaC == "Sally");

		pqueueOfTestStructs.PopFront(); // removes (2, 5.0, "Sally")
		assert(pqueueOfTestStructs.PeekFront().criteriaA == 2);		
		assert(pqueueOfTestStructs.PeekFront().criteriaB == 3.0);
		assert(pqueueOfTestStructs.PeekFront().criteriaC == "Sally");

		// Change sort order, now the best "C" should be shown
		pqueueOfTestStructs.ChangeSortOrder(sortByCThenBThenA);
		assert(pqueueOfTestStructs.PeekFront().criteriaA == 1);		
		assert(pqueueOfTestStructs.PeekFront().criteriaB == 3.0);
		assert(pqueueOfTestStructs.PeekFront().criteriaC == "Tom");

		pqueueOfTestStructs.PopFront(); // removes (1, 3.0, "Tom")
		assert(pqueueOfTestStructs.PeekFront().criteriaA == 2);		
		assert(pqueueOfTestStructs.PeekFront().criteriaB == 3.0);
		assert(pqueueOfTestStructs.PeekFront().criteriaC == "Sally");

		// Change sort order, now the best "A" then C should be shown
		pqueueOfTestStructs.ChangeSortOrder(sortByAThenCThenB);
		assert(pqueueOfTestStructs.PeekFront().criteriaA == 2);		
		assert(pqueueOfTestStructs.PeekFront().criteriaB == 3.0);
		assert(pqueueOfTestStructs.PeekFront().criteriaC == "Sally");



	}
}