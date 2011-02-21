//********************************************************************
//  FILE NAME:      Pqueuetests.cpp
//
//  DESCRIPTION:    Contains tests for the major pqueue classes
//
//*********************************************************************
#ifndef PQUEUE_TESTS_20100821_H
#define PQUEUE_TESTS_20100821_H

namespace pqueue
{
	//! Test the complete tree index class which does all the
	//! math for knowing where we are in a complete tree
	void TestCompleteTreeIndex();

	//! Test the complete tree data structure
	void TestCompleteTree();

	//! Test the heap data structure
	void TestHeap();

	//! Test the composite sort
	void TestCompositeSort();

	//! Test the pqueue class
	void TestPqueue();

}


#endif