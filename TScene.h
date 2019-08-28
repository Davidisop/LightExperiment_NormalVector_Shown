#include "Plane.h"
#include "Frustum_Box.h"
#include "Box.h"
#include "Line.h"
#include "Plane_for_SkyBox.h"
#include "Map.h"



int end_decision;

enum TSceneState
{
	GAME_SCENE_LOBBY = 0,
	GAME_SCENE_PLAY = 1,
	GAME_SCENE_END = 2,
};

class TScene
{
public:
	int		m_iSceneID;
	bool	m_bNextSceneStart;

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }

public:
	TScene()
	{
		m_bNextSceneStart = false;
	}
	virtual ~TScene() {}
};



class TSceneLobby : public TScene
{
public:

	Canon_Camera Main_Camera;
	Canon_Camera Right_Camera;
	Canon_Camera Top_Camera;
	Canon_Camera Beneath_Camera;

	void camera_operation();

public:
	//Frustum_Box Camera_Frustum_Box;

public:
	
	Plane_for_SkyBox up;
	Plane_for_SkyBox down;
	Plane_for_SkyBox left;
	Plane_for_SkyBox right;
	Plane_for_SkyBox front;
	Plane_for_SkyBox back;




public:

	Map		yang;


public:

	void Sun_Light_Rambert_Function()
	{
		// 조명계산
		D3DXVECTOR3 vLight(100, 100, 100); // 일부러 방향을 태양을 향하게 했다. 내적 결과가 양수가 나오게 하기 위해.
		D3DXVec3Normalize(&vLight, &vLight);
		for (int i = 0; i < yang.m_icount_Vertexs; i++)
		{
			float fDot =  D3DXVec3Dot(&yang.m_VertexList[i].n, &vLight);
			
			if (fDot < 0.1f) { fDot = 0.1f; }
			
			yang.m_VertexList[i].c.x = fDot;
			yang.m_VertexList[i].c.y = fDot;
			yang.m_VertexList[i].c.z = fDot;
		}
	}

public: // 노멀 벡타를 화면에 출력하기 위해

	Line_Axis_s Normal_lines;


public:

	
	Line_Axis_s F_Axis_s;


public:
	virtual bool Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneLobby();
	virtual ~TSceneLobby();
};

void TSceneLobby::camera_operation()
{

	D3DXVECTOR4   vYawPitchRoll(0, 0, 0, 0);


	// 요
	if (I_Input.Key('U'))
	{
		vYawPitchRoll.x += 0.1f*g_fSecPerFrame;
	}


	if (I_Input.Key('I'))
	{
		vYawPitchRoll.x -= 0.1f*g_fSecPerFrame;
	}

	// 피치

	if (I_Input.Key('J'))
	{
		vYawPitchRoll.y += 0.1f*g_fSecPerFrame;
	}

	if (I_Input.Key('K'))
	{
		vYawPitchRoll.y -= 0.1f*g_fSecPerFrame;
	}

	// 롤

	if (I_Input.Key('N'))
	{
		vYawPitchRoll.z += 0.1f*g_fSecPerFrame;
	}

	if (I_Input.Key('M'))
	{
		vYawPitchRoll.z -= 0.1f*g_fSecPerFrame;
	}


	// 스피드 부스터
	if (I_Input.Key('B'))
	{
		Main_Camera.SetSpeed(g_fSecPerFrame*3.0f);
		/*Right_Camera.SetSpeed(g_fSecPerFrame*3.0f);
		Top_Camera.SetSpeed(g_fSecPerFrame*3.0f);
		Beneath_Camera.SetSpeed(g_fSecPerFrame*3.0f);*/
	}

	// 위 아래 걸음


	if (I_Input.Key('Q'))
	{
		Main_Camera.Move_on_Up_line(-g_fSecPerFrame * 5.0f);
		/*Right_Camera.Move_on_Up_line(-g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Up_line(-g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Up_line(-g_fSecPerFrame * 5.0f);*/


	}

	if (I_Input.Key('W'))
	{
		Main_Camera.Move_on_Up_line(g_fSecPerFrame*5.0f);
		/*Right_Camera.Move_on_Up_line(g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Up_line(g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Up_line(g_fSecPerFrame * 5.0f);*/
	}



	// 앞,뒤 걸음

	if (I_Input.Key('A'))
	{
		Main_Camera.Move_on_Look_line(-g_fSecPerFrame * 5.0f);
	/*	Right_Camera.Move_on_Look_line(-g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Look_line(-g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Look_line(-g_fSecPerFrame * 5.0f);*/
	}

	if (I_Input.Key('S'))
	{
		Main_Camera.Move_on_Look_line(g_fSecPerFrame * 5.0f);
	/*	Right_Camera.Move_on_Look_line(g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Look_line(g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Look_line(g_fSecPerFrame * 5.0f);*/
	}

	// 양 옆 게 걸음

	if (I_Input.Key('Z'))
	{
		Main_Camera.Move_on_Right_line(-g_fSecPerFrame * 5.0f);
		/*Right_Camera.Move_on_Right_line(-g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Right_line(-g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Right_line(-g_fSecPerFrame * 5.0f);*/
	}

	if (I_Input.Key('X'))
	{
		Main_Camera.Move_on_Right_line(g_fSecPerFrame*5.0f);
	/*	Right_Camera.Move_on_Right_line(g_fSecPerFrame * 5.0f);
		Top_Camera.Move_on_Right_line(g_fSecPerFrame * 5.0f);
		Beneath_Camera.Move_on_Right_line(g_fSecPerFrame * 5.0f);*/
	}

	Main_Camera.ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);
	/*Right_Camera.ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);
	Top_Camera.ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);
	Beneath_Camera.ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);*/
}

bool	TSceneLobby::Init()
{


	Main_Camera.Set_View_Matrix(D3DXVECTOR3(400.0f, 2300.0f, -200.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Main_Camera.Set_Projection_Matrix(0.25, 1, 1, 100);

	/*Right_Camera.Set_View_Matrix(D3DXVECTOR3(250.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Right_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);*/



	/*Camera_Frustum_Box.Set_VertexData(); Camera_Frustum_Box.set_IndexData();
	Camera_Frustum_Box.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/bitmap1.bmp", "PSLine");*/


/*
	FSphere.Set_VertexData(); FSphere.set_IndexData();
	FSphere.transposition(D3DXVECTOR3(-3.0f,0.0f,0.0f));
	FSphere.Create(g_pd3dDevice, L"HLSL.vsh", "VS_NoMatrix", L"HLSL.psh", L"GeometryShader.hlsl", L"../../data/main_start_sel.bmp");
	*/
	

	
	yang.Extract_Height_Map_Datas_R_0255_G_0255_B_0255_A0255_From_looking_GrayScale_TextureFile_Resource_Using_CPU(g_pd3dDevice, g_pContext, L"../../data/map/HEIGHT_CASTLE.bmp");
	yang.Cell_distance_input_x_z_HighScale(3, 3,1);
	yang.Set_VertexData();
	yang.set_IndexData();
	yang.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/map/castle.jpg", "VS_Basic_Light", "PS_LIGHT");


	//

	
	yang.Light_Constant_Data.g_vLightDir = D3DXVECTOR3(40, 40, 40)*(-1);
	
	//



	up.Set_VertexData(); up.set_IndexData();
	up.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_up.bmp",0, "VS_SKY", "PS_SKY");


	down.Set_VertexData(); down.set_IndexData();
	down.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_down.bmp",0, "VS_SKY", "PS_SKY");


	left.Set_VertexData(); left.set_IndexData();
	left.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_left.bmp",0, "VS_SKY", "PS_SKY");


	right.Set_VertexData(); right.set_IndexData();
	right.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_right.bmp",0, "VS_SKY", "PS_SKY");


	front.Set_VertexData(); front.set_IndexData();
	front.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_front.bmp",0, "VS_SKY", "PS_SKY");


	back.Set_VertexData(); back.set_IndexData();
	back.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/st00_cm_back.bmp",0, "VS_SKY", "PS_SKY");
	


	//

	Normal_lines.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));	Normal_lines.set_IndexData();
	Normal_lines.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg", "VS", "PSLine");


	//


	F_Axis_s.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));	F_Axis_s.set_IndexData();
	F_Axis_s.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg","VS", "PSLine");





	return true;
};

 
bool	TSceneLobby::Frame()
{

	camera_operation();
	//Camera_Frustum_Box.total_Vertex_Update_for_Frustum(&Main_Camera.m_matView, &Main_Camera.m_matProj);

	Main_Camera.camera_position;
	D3DXMATRIX mTranslate_following_camera;
	D3DXMatrixTranslation(&mTranslate_following_camera, Main_Camera.camera_position.x, Main_Camera.camera_position.y, Main_Camera.camera_position.z);


	//float t = g_fGameTimer * D3DX_PI;

	D3DXMATRIX mTranslate_front; 	D3DXMATRIX mTranslate_down; D3DXMATRIX mTranslate_right; D3DXMATRIX mTranslate_up; D3DXMATRIX mTranslate_left; D3DXMATRIX mTranslate_back;
	D3DXMATRIX mSpin_up; D3DXMATRIX mSpin_down; D3DXMATRIX mSpin_right; D3DXMATRIX mSpin_left; D3DXMATRIX mSpin_front; D3DXMATRIX mSpin_back;
	D3DXMATRIX mScale; D3DXMATRIX mScale_2;

	D3DXMatrixScaling(&mScale, 100.0f, 100.0f, 0.0f);
	D3DXMatrixScaling(&mScale_2, 50.0f, 50.0f, 50.0f);

	//UP
	D3DXMatrixRotationX(&mSpin_up, -D3DX_PI/2);
	D3DXMatrixTranslation(&mTranslate_up, 0.0f, 100.0f, 0.0f); // 트랜스래잇 행렬
	up.m_matWorld = mScale * mSpin_up * mTranslate_up*mTranslate_following_camera;

	//DOWN
	D3DXMatrixRotationX(&mSpin_down, D3DX_PI / 2);
	D3DXMatrixTranslation(&mTranslate_down, 0.0f, -100.0f, 0.0f); // 트랜스래잇 행렬
	down.m_matWorld = mScale * mSpin_down * mTranslate_down*mTranslate_following_camera;

	//RIGHT															  
	D3DXMatrixRotationY(&mSpin_right, D3DX_PI / 2);
	D3DXMatrixTranslation(&mTranslate_right, 100.0f, 0.0f, 0.0f); // 트랜스래잇 행렬
	right.m_matWorld = mScale* mSpin_right*mTranslate_right*mTranslate_following_camera;


	//LEFT													 
	D3DXMatrixRotationY(&mSpin_left, -D3DX_PI / 2);
	D3DXMatrixTranslation(&mTranslate_left, -100.0f, -0.0f, 0.0f); // 트랜스래잇 행렬
	left.m_matWorld = mScale * mSpin_left*mTranslate_left*mTranslate_following_camera;
	
	//FRONT
	//D3DXMatrixRotationY(&mSpin_front, -D3DX_PI);
	D3DXMatrixTranslation(&mTranslate_front, 0.0f, 0.0f, +100.0f); // 트랜스래잇 행렬
	front.m_matWorld = mScale * mTranslate_front*mTranslate_following_camera;

	//BACK
	D3DXMatrixRotationY(&mSpin_back, -D3DX_PI);
	D3DXMatrixTranslation(&mTranslate_back, 0.0f, 0.0f, -100.0f); // 트랜스래잇 행렬
	back.m_matWorld = mScale  * mSpin_back*mTranslate_back*mTranslate_following_camera;

	
	



	////

	

	//D3DXMatrixTranslation(&mTranslate, 0.0f, 3.0f, 0.0f); // 트랜스래잇 행렬
	//D3DXMatrixRotationZ(&earth_mOrbit, t*0.2);


	//D3DXMatrixTranslation(&mTranslate_2, 0.0f, 0.0f, 3.0f); // 트랜스래잇 행렬
	//D3DXMatrixRotationX(&moon_Orbit, t*0.5);



	//FSphere.m_matWorld = mScale * mTranslate * earth_mOrbit;
	


	return true;
};


bool	TSceneLobby::Render()
{

	// 1번 뷰포트
	/*
	FSphere.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FSphere.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);		FSphere.update_ConstantBuffer();
	FBox.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FBox.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);			FBox.update_ConstantBuffer();*/
	


	
	
	yang.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&yang.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	yang.update_ConstantBuffer();
	
	up.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&up.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	up.update_ConstantBuffer();
	down.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&down.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	down.update_ConstantBuffer();
	left.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&left.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	left.update_ConstantBuffer();
	right.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&right.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	right.update_ConstantBuffer();
	front.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&front.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	front.update_ConstantBuffer();
	back.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&back.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	back.update_ConstantBuffer();

	F_Axis_s.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_s.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);	F_Axis_s.update_ConstantBuffer();
	Normal_lines.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&Normal_lines.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj); Normal_lines.update_ConstantBuffer();

	//


	up.Render(g_pContext, 0);
	down.Render(g_pContext, 0);
	left.Render(g_pContext, 0);
	right.Render(g_pContext, 0);
	front.Render(g_pContext, 0);
	back.Render(g_pContext, 0);

	//back.PipeLineSetup.CreateDepthStencilState(TRUE); g_pContext->OMSetDepthStencilState(back.PipeLineSetup.m_pDepthStencilState, 0);


	//







	//Camera_Frustum_Box.Render(g_pContext, 1);
	
	
	yang.Render(g_pContext, 0);

	



	//X축 랜더
	F_Axis_s.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10000.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	g_pContext->UpdateSubresource(F_Axis_s.PipeLineSetup.m_pVertextBuffer, 0, NULL, &F_Axis_s.m_VertexList[0], 0, 0);
	F_Axis_s.PreRender(g_pContext, 0);	F_Axis_s.PostRender(g_pContext);
	//Y축 랜더
	
	F_Axis_s.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10000.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
	g_pContext->UpdateSubresource(F_Axis_s.PipeLineSetup.m_pVertextBuffer, 0, NULL, &F_Axis_s.m_VertexList[0], 0, 0);
	F_Axis_s.PreRender(g_pContext, 0);	F_Axis_s.PostRender(g_pContext);
	//Z축 랜더

	F_Axis_s.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 10000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	g_pContext->UpdateSubresource(F_Axis_s.PipeLineSetup.m_pVertextBuffer, 0, NULL, &F_Axis_s.m_VertexList[0], 0, 0);
	F_Axis_s.PreRender(g_pContext, 0);	F_Axis_s.PostRender(g_pContext);



	// 노멀 벡터 라인들 출력


	for (int iVertex = 0; iVertex < yang.m_VertexList.size(); iVertex += 30)
	{
		D3DXVECTOR3 vNormal = yang.m_VertexList[iVertex].n;
		Normal_lines.Set_VertexData(yang.m_VertexList[iVertex].p, yang.m_VertexList[iVertex].p + vNormal * 100);
		//
		g_pContext->UpdateSubresource(Normal_lines.PipeLineSetup.m_pVertextBuffer, 0, NULL, &Normal_lines.m_VertexList[0], 0, 0);
		//
		Normal_lines.PreRender(g_pContext, 0); Normal_lines.PostRender(g_pContext);
	}










	///////////////////////////////////////////////////////////////////////////////////////

	//// 2번 뷰포트

	///*FSphere.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FSphere.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);		FSphere.update_ConstantBuffer();
	//FBox.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FBox.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);			FBox.update_ConstantBuffer();*/
	//
	//Camera_Frustum_Box.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&Camera_Frustum_Box.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);		Camera_Frustum_Box.update_ConstantBuffer();
	//F_Axis_s.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_s.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	F_Axis_s.update_ConstantBuffer();
	//F_Axis_y.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_y.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	F_Axis_y.update_ConstantBuffer();
	//F_Axis_z.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_z.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	F_Axis_z.update_ConstantBuffer();




	//up.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&up.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	up.update_ConstantBuffer();
	//down.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&down.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	down.update_ConstantBuffer();
	//left.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&left.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	left.update_ConstantBuffer();
	//right.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&right.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	right.update_ConstantBuffer();
	//front.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&front.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	front.update_ConstantBuffer();
	//back.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&back.m_matWorld, &Right_Camera.m_matView, &Right_Camera.m_matProj);	back.update_ConstantBuffer();


	//up.Render(g_pContext, 2);
	//down.Render(g_pContext, 2);
	//left.Render(g_pContext, 2);
	//right.Render(g_pContext, 2);
	//front.Render(g_pContext, 2);
	//back.Render(g_pContext, 2);

	//
	//F_Axis_s.PreRender(g_pContext, 2);	F_Axis_s.PostRender(g_pContext);
	//F_Axis_y.PreRender(g_pContext, 2);	F_Axis_y.PostRender(g_pContext);
	//F_Axis_z.PreRender(g_pContext, 2);	F_Axis_z.PostRender(g_pContext);
	//Camera_Frustum_Box.Render(g_pContext, 2);
	//
	//// 3번 뷰포트


	///*FSphere.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FSphere.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);		FSphere.update_ConstantBuffer();
	//FBox.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FBox.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);			FBox.update_ConstantBuffer();*/

	//Camera_Frustum_Box.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&Camera_Frustum_Box.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);		Camera_Frustum_Box.update_ConstantBuffer();
	//F_Axis_s.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_s.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);	F_Axis_s.update_ConstantBuffer();
	//F_Axis_y.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_y.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);	F_Axis_y.update_ConstantBuffer();
	//F_Axis_z.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_z.m_matWorld, &Top_Camera.m_matView, &Top_Camera.m_matProj);	F_Axis_z.update_ConstantBuffer();


	///*FSphere.Render(g_pContext, 3);
	//FBox.Render(g_pContext, 3);*/
	
	//F_Axis_s.PreRender(g_pContext, 3);	F_Axis_s.PostRender(g_pContext);
	//F_Axis_y.PreRender(g_pContext, 3);	F_Axis_y.PostRender(g_pContext);
	//F_Axis_z.PreRender(g_pContext, 3);	F_Axis_z.PostRender(g_pContext);



	//// 4번 뷰포트


	///*FSphere.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FSphere.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);		FSphere.update_ConstantBuffer();
	//FBox.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FBox.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);			FBox.update_ConstantBuffer();*/
	//
	//Camera_Frustum_Box.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&Camera_Frustum_Box.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);		Camera_Frustum_Box.update_ConstantBuffer();
	//F_Axis_s.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_s.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);	F_Axis_s.update_ConstantBuffer();
	//F_Axis_y.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_y.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);	F_Axis_y.update_ConstantBuffer();
	//F_Axis_z.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_z.m_matWorld, &Beneath_Camera.m_matView, &Beneath_Camera.m_matProj);	F_Axis_z.update_ConstantBuffer();




	///*FSphere.Render(g_pContext, 4);
	//FBox.Render(g_pContext, 4);*/
	//Camera_Frustum_Box.Render(g_pContext, 4);
	//F_Axis_s.PreRender(g_pContext, 4);	F_Axis_s.PostRender(g_pContext);
	//F_Axis_y.PreRender(g_pContext, 4);	F_Axis_y.PostRender(g_pContext);
	//F_Axis_z.PreRender(g_pContext, 4);	F_Axis_z.PostRender(g_pContext);






	return true;
};

bool	TSceneLobby::Release()
{
	
	
	return true;
};
TSceneLobby::TSceneLobby()
{
	m_iSceneID = GAME_SCENE_LOBBY;
	m_bNextSceneStart = false;
}
TSceneLobby::~TSceneLobby()
{

}

















class TSceneGame : public TScene
{
public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

public:

	TSceneGame();
	virtual ~TSceneGame();
};



TSceneGame::TSceneGame()
{
	m_iSceneID = GAME_SCENE_PLAY;
	m_bNextSceneStart = false;
}

bool   TSceneGame::Init()
{

	return true;
};

bool    TSceneGame::Frame()
{

	return true;
}

bool   TSceneGame::Render()
{

	return true;
}

bool    TSceneGame::Release()
{
	return true;
}

TSceneGame::~TSceneGame()
{
}



class TSceneEnd : public TScene
{

public:

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:

	TSceneEnd();
	virtual ~TSceneEnd();
};




bool	TSceneEnd::Init()
{



	return true;
};
bool	TSceneEnd::Frame()
{


	return true;
};

bool	TSceneEnd::Render()
{

	return true;
};

bool	TSceneEnd::Release()
{
	return true;
};

TSceneEnd::TSceneEnd()
{
	m_iSceneID = GAME_SCENE_END;
	m_bNextSceneStart = false;
}

TSceneEnd::~TSceneEnd()
{}

