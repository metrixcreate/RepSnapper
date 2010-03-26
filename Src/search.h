/* -------------------------------------------------------- *
*
* Search.h
*
* Copyright 2009+ Michael Holm - www.kulitorum.com
*
* This file is part of RepSnapper and is made available under
* the terms of the GNU General Public License, version 2, or at your
* option, any later version, incorporated herein by reference.

THIS CODE IS AS OF YET UNUSED

*
* ------------------------------------------------------------------------- */
#pragma once

#include <vmmlib/vmmlib.h>
#include <vector>

#include <ANN/ANN.h>

using namespace std;					// make std:: accessible
using namespace vmml;


class Search{
public:
	Search(){dim = 3; nnIdx = 0; dists = 0; kdTree = 0; readyToBeSearched = false;}
	~Search();
	
	bool addPoint(const Vector3f &p);			// returns 1=OK, 0=bad
	bool Init();								// Make ready - call after adding points
	int search(const Vector3f &p);				// returns index of nearest point or -1 for error

private:
	bool readyToBeSearched;
	std::vector<Vector3f> points;				// temp buffer for points
	int					dim;					// Dimension to work in, usually 2 or 3
	int					MaxPointCount;			// Max n_points
	int					nPts;					// actual number of data points
	ANNpointArray		dataPts;				// data points
	ANNpoint			queryPt;				// query point
	ANNidxArray			nnIdx;					// near neighbor indices
	ANNdistArray		dists;					// near neighbor distances
	ANNkd_tree*			kdTree;					// search structure
};
