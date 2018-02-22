//=======================================================================================
// Box.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#include "..\Headers\WindowedBox.h"
#include "..\Headers\Vertex.h"

WindowedBox::WindowedBox()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
WindowedBox::~WindowedBox()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void WindowedBox::init(ID3D10Device* device, float width, float height, float wwidth, float wheight, float depth, float scale)
{
	md3dDevice = device;
 
	mNumVertices = 48;
	mNumFaces    = 32; // 2 per quad

	// Create vertex buffer
    Vertex v[48];

	float tdxp = (width - wwidth) / (width * 2);
	float tdyp = (height - wheight) / (height * 2);
	float tdxm = (width + wwidth) / (width * 2);
	float tdym = (height + wheight) / (height * 2);
	
    
	// 1 Fill in the front face vertex data.
	v[0] = Vertex(-width, -height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-width, height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex( width, height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = Vertex( width, -height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// 2 Fill in the back face vertex data.
	v[4] = Vertex(-width, -height, depth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = Vertex( width, -height, depth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = Vertex( width, height, depth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = Vertex(-width, height, depth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// 3 Fill in the top face vertex data.
	v[8]  = Vertex(-width, height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[9]  = Vertex(-width, height, depth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex( width, height, depth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex( width, height, -depth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// 4 Fill in the bottom face vertex data.
	v[12] = Vertex(-width, -height, -depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex( width, -height, -depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[14] = Vertex( width, -height, depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex(-width, -height, depth, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// 5 Fill in the left face vertex data.
	v[16] = Vertex(-width, -height, depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[17] = Vertex(-width, height, depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[18] = Vertex(-width, height, -depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[19] = Vertex(-width, -height, -depth, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// 6 Fill in the right face vertex data.
	v[20] = Vertex( width, -height, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = Vertex( width, height, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[22] = Vertex( width, height, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[23] = Vertex( width, -height, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	
	// 7 Fill in the front face window vertex data.
	v[24] = Vertex( -wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxp, tdym);
	v[25] = Vertex( -wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxp, tdyp);
	v[26] = Vertex( wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxm, tdyp);
	v[27] = Vertex( wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxm, tdym);
	
	// 8 Fill in the back face window vertex data.
	v[28] = Vertex( -wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxm, tdym);
	v[29] = Vertex( wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxp, tdym);
	v[30] = Vertex( wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxp, tdyp);
	v[31] = Vertex( -wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, tdxm, tdyp);
	
	// 9 Fill in the top face window vertex data.
	v[32] = Vertex( -wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[33] = Vertex( -wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[34] = Vertex( wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[35] = Vertex( wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	// 10 Fill in the bottom face window vertex data.
	v[36] = Vertex( -wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[37] = Vertex( wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[38] = Vertex( wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[39] = Vertex( -wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	// 11 Fill in the left face window vertex data.
	v[40] = Vertex( -wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[41] = Vertex( -wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[42] = Vertex( -wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[43] = Vertex( -wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	// 12 Fill in the right face window vertex data.
	v[44] = Vertex( wwidth, -wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[45] = Vertex( wwidth, wheight, -depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[46] = Vertex( wwidth, wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[47] = Vertex( wwidth, -wheight, depth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

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

	DWORD i[96];

	// 1 Fill in the front face index data
	i[0] = 24; i[1] = 1; i[2] = 25;
	i[3] = 25; i[4] = 1; i[5] = 2;
	i[6] = 25; i[7] = 2; i[8] = 26;
	i[9] = 26; i[10] = 2; i[11] = 27;
	i[12] = 27; i[13] = 2; i[14] = 3;
	i[15] = 0; i[16] = 27; i[17] = 3;
	i[18] = 0; i[19] = 24; i[20] = 27;
	i[21] = 0; i[22] = 1; i[23] = 24;

	// 2 Fill in the back face index data
	i[24] = 7; i[25] = 28; i[26] = 31;
	i[27] = 7; i[28] = 31; i[29] = 6;
	i[30] = 31; i[31] = 30; i[32] = 6;
	i[33] = 30; i[34] = 29; i[35] = 6;
	i[36] = 6; i[37] = 29; i[38] = 5;
	i[39] = 4; i[40] = 5; i[41] = 29;
	i[42] = 28; i[43] = 4; i[44] = 29;
	i[45] = 7; i[46] = 4; i[47] = 28;

	// 3 Fill in the top face index data
	i[48] = 8; i[49] =  9; i[50] = 10;
	i[51] = 8; i[52] = 10; i[53] = 11;

	// 4 Fill in the bottom face index data
	i[54] = 12; i[55] = 13; i[56] = 14;
	i[57] = 12; i[58] = 14; i[59] = 15;

	// 5 Fill in the left face index data
	i[60] = 16; i[61] = 17; i[62] = 18;
	i[63] = 16; i[64] = 18; i[65] = 19;

	// 6 Fill in the right face index data
	i[66] = 20; i[67] = 21; i[68] = 22;
	i[69] = 20; i[70] = 22; i[71] = 23;
	
	// 7 Fill in the window top face index data
	i[72] = 32; i[73] =  34; i[74] = 33;
	i[75] = 32; i[76] = 35; i[77] = 34;

	// 8 Fill in the window bottom face index data
	i[78] = 36; i[79] = 38; i[80] = 37;
	i[81] = 36; i[82] = 39; i[83] = 38;

	// 9 Fill in the window left face index data
	i[84] = 40; i[85] = 42; i[86] = 41;
	i[87] = 40; i[88] = 43; i[89] = 42;

	// 10 Fill in the window right face index data
	i[90] = 47; i[91] = 45; i[92] = 44;
	i[93] = 47; i[94] = 46; i[95] = 45;

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

void WindowedBox::draw()
{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(mNumFaces*3, 0, 0);
}