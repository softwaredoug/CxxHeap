//********************************************************************
//  FILE NAME:      pqueue_main.cpp
//
//  DESCRIPTION:    Main routine for pqueue program... tests library 
//					functions by invoking PqueueTest functions
//*********************************************************************

#include "stdafx.h"
#include "PqueueTests.h"



int main()
{
	using namespace pqueue;
	TestCompleteTreeIndex();
	TestCompleteTree();
	TestHeap();
	TestCompositeSort();
	TestPqueue();

	return 0;
}

