

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, 
		float nx, float ny, float nz, 
		float u, float v)
		: pos(x,y,z), normal(nx,ny,nz), texC(u,v){}

	Vertex(float x, float y, float z, 
		float tx, float ty, float tz,
		float nx, float ny, float nz, 
		float u, float v)
		: pos(x,y,z), tangent(tx, ty, tz), normal(nx,ny,nz), texC(u,v){}

	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 normal;
	D3DXCOLOR   diffuse;
	D3DXCOLOR   spec; // (r, g, b, specPower);
	D3DXVECTOR2 texC;
};

#endif // VERTEX_H

