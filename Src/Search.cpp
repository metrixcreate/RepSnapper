/* -------------------------------------------------------- *
*
* Search.cpp
*
* Copyright 2009+ Michael Holm - www.kulitorum.com
*
* This file is part of RepSnapper and is made available under
* the terms of the GNU General Public License, version 2, or at your
* option, any later version, incorporated herein by reference.
*
* ------------------------------------------------------------------------- */
#include "stdafx.h"

#include "search.h"


// Placeholder for space-subdivision searching, to make stuff faster


/*
// returns 1=OK, 0=bad
bool Search::addPoint(const Vector3f &p)
{
	if(readyToBeSearched == false)
		return false;
	points.push_back(p);
	return true;
}

// Make ready - call after adding points
bool Search::Init()
{
	if(readyToBeSearched == true)
		return false;
	MaxPointCount = (int)points.size();

	queryPt = annAllocPt(dim);						// allocate query point
	dataPts = annAllocPts(MaxPointCount, dim);		// allocate data points


	int resultCount;
	resultCount = 10;
	nnIdx = new ANNidx[resultCount];				// allocate near neigh indices
	dists = new ANNdist[resultCount];				// allocate near neighbor dists


	nPts = 0;									// read data points
	kdTree = new ANNkd_tree(					// build search structure
					dataPts,					// the data points
					nPts,						// number of points
					dim);						// dimension of space

	if(kdTree != 0 && nPts != 0)
		{
		readyToBeSearched = true;
		return true;
		}
	return false;
}

int Search::search(const Vector3f &p)
{
	if(readyToBeSearched == false)
		return -1;

	int k=2;								// Number of neighbours wanted
	float eps = 0;

	kdTree->annkSearch(						// search
			queryPt,						// query point
			k,								// number of near neighbors
			nnIdx,							// nearest neighbors (returned)
			dists,							// distance (returned)
			eps);							// error bound

	for (int i = 0; i < k; i++)
		{
		dists[i] = sqrt(dists[i]);			// unsquare distance
		cout << "\t" << i << "\t" << nnIdx[i] << "\t" << dists[i] << "\n";
		}
	return nnIdx[1];
}


Search::~Search()
{
    delete [] nnIdx;							// clean things up
    delete [] dists;
    delete kdTree;
	annClose();									// done with ANN
}
*/