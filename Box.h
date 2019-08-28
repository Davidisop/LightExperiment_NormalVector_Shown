#pragma once
#include "Object_Handling.h"

class Box : public Object_Handling
{

public:
	bool   Set_VertexData();
	bool   update_ConstantBuffer();
	bool   set_IndexData();

public:
	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile, const char*  pFuntionName_VS, const char*  pFuntionName_PS);

public:
	Box() {}
	virtual ~Box() {}
};

bool   Box::update_ConstantBuffer()
{
	g_pContext->UpdateSubresource(PipeLineSetup.m_pConstantBuffer, 0, NULL, &m_Constant_Data, 0, 0);

	return true;
}






bool  Box::Set_VertexData()
{
	m_VertexList.resize(8);
	int iner_index = 0;

	//�ո�
	
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 0.5f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// �޸�
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.5f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));


	m_icount_Vertexs = m_VertexList.size();

	return true;
}



bool   Box::set_IndexData()
{

	m_IndexList.resize(36);
	int iner_index = 0;

	//FRONT
	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 3;
	//BACK
	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 7;
	//RIGHT
	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 7;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 7;	m_IndexList[iner_index++] = 3;
	//LEFT
	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 4;
	//UP
	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 2;
	//DOWN
	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 3;	m_IndexList[iner_index++] = 7;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 7;	m_IndexList[iner_index++] = 4;

	m_icount_Indexes = m_IndexList.size();

	return true;
}







//
//bool  Box::Set_VertexData()
//{
//	m_VertexList.resize(24);
//	int iner_index = 0;
//
//	//�ո�
//
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.577350318, 0.577350318, 0.577350318),D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//
//	// �޸�
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
//
//	// ������
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//
//
//	// ����
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
//
//	// ����
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, -0.577350318), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(-0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.577350318, -0.577350318, 0.577350318), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//
//	// �Ʒ���
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, 0.577350318), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(-0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
//	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.577350318, 0.577350318, -0.577350318), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
//
//
//	m_icount_Vertexs = m_VertexList.size();
//
//	return true;
//}
//
//
//
//bool   Box::set_IndexData()
//{
//
//	m_IndexList.resize(36);
//	int iner_index = 0;
//
//	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 3;
//	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 7;
//	m_IndexList[iner_index++] = 8;	m_IndexList[iner_index++] = 9;	m_IndexList[iner_index++] = 10;	m_IndexList[iner_index++] = 8;	m_IndexList[iner_index++] = 10;	m_IndexList[iner_index++] = 11;
//	m_IndexList[iner_index++] = 12;	m_IndexList[iner_index++] = 13;	m_IndexList[iner_index++] = 14;	m_IndexList[iner_index++] = 12;	m_IndexList[iner_index++] = 14;	m_IndexList[iner_index++] = 15;
//	m_IndexList[iner_index++] = 16;	m_IndexList[iner_index++] = 17;	m_IndexList[iner_index++] = 18;	m_IndexList[iner_index++] = 16;	m_IndexList[iner_index++] = 18;	m_IndexList[iner_index++] = 19;
//	m_IndexList[iner_index++] = 20;	m_IndexList[iner_index++] = 21;	m_IndexList[iner_index++] = 22;	m_IndexList[iner_index++] = 20;	m_IndexList[iner_index++] = 22;	m_IndexList[iner_index++] = 23;
//
//	m_icount_Indexes = m_IndexList.size();
//
//	return true;
//
//}

bool    Box::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile, const char*  pFuntionName_VS, const char*  pFuntionName_PS)
{
	PipeLineSetup.LoadTexture(pd3dDevice, pTexFile);
	PipeLineSetup.SetBlendState(pd3dDevice);
	PipeLineSetup.CreateVertextBuffer(pd3dDevice, &m_VertexList.at(0), m_icount_Vertexs);
	PipeLineSetup.CreateIndexBuffer(pd3dDevice, &m_IndexList.at(0), m_icount_Indexes);
	PipeLineSetup.CreateConstantBuffer(pd3dDevice, &m_Constant_Data);
	PipeLineSetup.CreateConstantBuffer_2(pd3dDevice, &Light_Constant_Data);
	PipeLineSetup.CreateVertexShader(pd3dDevice, pVsFile, pFuntionName_VS);
	PipeLineSetup.CreateLayout(pd3dDevice);
	PipeLineSetup.CreatePixelShader(pd3dDevice, pPsFile, pFuntionName_PS);



	PipeLineSetup.ScreenViewPort_setting();
	PipeLineSetup.Create_RasterizerState();
	PipeLineSetup.CreateTexture2D_DepthStencilView();
	PipeLineSetup.CreateDepthStencilState();

	return true;
}