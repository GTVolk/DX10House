//=======================================================================================
// Box.h by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#ifndef WINB_H
#define WINB_H

#include "d3dUtil.h"

class WindowedBox
{
public:

	WindowedBox();
	~WindowedBox();

	void init(ID3D10Device* device, float width, float height, float wwidth, float wheight, float depth, float scale);
	void draw();

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};

#endif // BOX_H
