//=======================================================================================
// Box.h by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#ifndef TRI_H
#define TRI_H

#include "d3dUtil.h"

class TriangleBox
{
public:

	TriangleBox();
	~TriangleBox();

	void init(ID3D10Device* device, float x1, float y1, float x2, float y2,  float x3, float y3, float depth, float scale);
	void draw();

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};

#endif // BOX_H
