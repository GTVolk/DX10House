//=======================================================================================
// Box.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#include "..\Headers\TriangleBox.h"
#include "..\Headers\Vertex.h"

TriangleBox::TriangleBox()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
TriangleBox::~TriangleBox()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void TriangleBox::init(ID3D10Device* device, float x1, float y1, float x2, float y2,  float x3, float y3, float depth, float scale)
{
	md3dDevice = device;
 
	mNumVertices = 18;
	mNumFaces    = 8; // 2 per quad

	// Create vertex buffer
    Vertex v[18];
    
	// Fill in the front face vertex data.
	v[0] = Vertex( x1, y1, depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex( x2, y2, depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f, 0.0f);
	v[2] = Vertex( x3, y3, depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[3] = Vertex( x1, y1, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex( x2, y2, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f, 0.0f);
	v[5] = Vertex( x3, y3, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[6] = Vertex( x1, y1, depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[7] = Vertex( x1, y1, -depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[8] = Vertex( x3, y3, depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[9] = Vertex( x3, y3, -depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[10] = Vertex( x1, y1, depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[11] = Vertex( x1, y1, -depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[12] = Vertex( x2, y2, depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[13] = Vertex( x2, y2, -depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[14] = Vertex( x3, y3, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[15] = Vertex( x3, y3, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[16] = Vertex( x2, y2, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[17] = Vertex( x2, y2, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Scale the box.
	for(DWORD i = 0; i < mNumVertices; ++i)
		v[i].pos *= scale;


    D3D10_BUFFER_DESC vbd;
    vbd.Usage = D3D10_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * mNumVertices;
    vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = v;
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mVB));


	// Create the index buffer

	DWORD i[24];

	// Fill in the front face index data
	i[0] = 2; i[1] = 1; i[2] = 0;

	// Fill in the back face index data
	i[3] = 3; i[4]  = 4; i[5]  = 5;

	// Fill in the bottom face index data
	i[6] = 6; i[7] = 7; i[8] = 8;
	i[9] = 9; i[10] = 8; i[11] = 7;

	// Fill in the left face index data
	i[12] = 12; i[13] = 11; i[14] = 10;
	i[15] = 11; i[16] = 12; i[17] = 13;

	// Fill in the right face index data
	i[18] = 14; i[19] = 15; i[20] = 16;
	i[21] = 17; i[22] = 16; i[23] = 15;

	D3D10_BUFFER_DESC ibd;
    ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * mNumFaces*3;
    ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = i;
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));
}

void TriangleBox::draw()
{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(mNumFaces*3, 0, 0);
}