#include "Object_Handling.h"


struct MapDesc
{
	int   i_per_row_total_Collums_numbers;
	int   i_per_collum_total_Rows_numbers;
	float   Distance_from_A_Cell_to_side_Cell_in_Raw;//m_Distance_from_ACell_to_sideCell
	float   Distance_from_A_Cell_to_side_Cell_in_Collum;//m_Distance_from_ACell_to_sideCell

	float  fScaleHeight;

	MapDesc() {}
	MapDesc(int i_per_row_total_Collums_numbers_in, int i_per_collum_total_Rows_numbers_in,
		float Distance_from_A_Cell_to_side_Cell_in_Raw_in, float   Distance_from_A_Cell_to_side_Cell_in_Collum_in, float fScaleHeight_in)
	{

		i_per_row_total_Collums_numbers= i_per_row_total_Collums_numbers_in;
		i_per_collum_total_Rows_numbers= i_per_collum_total_Rows_numbers_in;
		Distance_from_A_Cell_to_side_Cell_in_Raw = Distance_from_A_Cell_to_side_Cell_in_Raw_in;
		Distance_from_A_Cell_to_side_Cell_in_Collum = Distance_from_A_Cell_to_side_Cell_in_Collum_in;
		fScaleHeight= fScaleHeight_in;
	}
};


 
struct IndexTable_For_Faces_Finally_to_Get_VetexNormal
{
	int faceIndex[6];

	IndexTable_For_Faces_Finally_to_Get_VetexNormal()
	{
		faceIndex[0] = -1;
		faceIndex[1] = -1;
		faceIndex[2] = -1;
		faceIndex[3] = -1;
		faceIndex[4] = -1;
		faceIndex[5] = -1;
	}
};

class Map : public Object_Handling
{
	MapDesc   m_MapDesc;
	int		m_per_collum_total_Rows_numbers;
	int		m_per_row_total_Collums_numbers;//�� ���� ��ռ� =i_per_row_total_Collums_numbers
	int		m_per_collum_total_Cells_numbers;//m_per_collum_total_Cells_numbers
	int		m_per_row_total_Cells_numbers;//m_per_row_total_Cells_numbers
	int	    m_total_faces_numbers;//m_total_faces_numbers
	int     m_total_Vertices_numbers; //m_total_Vertices_numbers
	float   m_Distance_from_A_Cell_to_side_Cell_in_Raw;//m_Distance_from_ACell_to_sideCell
	float   m_Distance_from_A_Cell_to_side_Cell_in_Collum;//m_Distance_from_ACell_to_sideCell
	float   m_Length_of_Raw;//m_Distance_from_ACell_to_sideCell
	float   m_Length_of_Collum;//m_Distance_from_ACell_to_sideCell
	float   m_fScaleHeight;

public: // ���̸��� ���� �߰��� ��.

	vector<float> m_fHeightList;

public: // ���� ����� ���ϱ� ���� �߰��Ȱ�.

	vector<D3DXVECTOR3> m_Face_NormalVector_List;
	vector<IndexTable_For_Faces_Finally_to_Get_VetexNormal> m_Normal_Lookup_Table;

public:

	bool Cell_distance_input_x_z_HighScale(float x, float z, float Highscale)
	{
		m_Distance_from_A_Cell_to_side_Cell_in_Raw = x;
		m_Distance_from_A_Cell_to_side_Cell_in_Collum = z;

		m_Length_of_Raw = m_Distance_from_A_Cell_to_side_Cell_in_Raw * m_per_row_total_Cells_numbers;
		m_Length_of_Collum = m_Distance_from_A_Cell_to_side_Cell_in_Collum * m_per_collum_total_Cells_numbers;

		m_fScaleHeight = Highscale;

		return true;
	}

	bool Map_DESC_DATA_Load(MapDesc MapDesc_in)
	{
		m_per_collum_total_Rows_numbers = MapDesc_in.i_per_collum_total_Rows_numbers;
		m_per_row_total_Collums_numbers = MapDesc_in.i_per_row_total_Collums_numbers;
		m_per_collum_total_Cells_numbers = m_per_collum_total_Rows_numbers - 1;
		m_per_row_total_Cells_numbers = m_per_row_total_Collums_numbers - 1;

		m_total_Vertices_numbers = m_per_collum_total_Rows_numbers * m_per_row_total_Collums_numbers;
		m_total_faces_numbers = m_per_collum_total_Cells_numbers * m_per_row_total_Cells_numbers * 2;
		m_Distance_from_A_Cell_to_side_Cell_in_Raw = MapDesc_in.Distance_from_A_Cell_to_side_Cell_in_Raw;
		m_Distance_from_A_Cell_to_side_Cell_in_Collum = MapDesc_in.Distance_from_A_Cell_to_side_Cell_in_Collum;

		return true;
	}


	bool   update_ConstantBuffer()
	{
		g_pContext->UpdateSubresource(PipeLineSetup.m_pConstantBuffer, 0, NULL, &m_Constant_Data, 0, 0);
		g_pContext->UpdateSubresource(PipeLineSetup.m_pConstantBuffer_2, 0, NULL, &Light_Constant_Data, 0, 0);
		return true;
	}


	bool Extract_Height_Map_Datas_R_0255_G_0255_B_0255_A0255_From_looking_GrayScale_TextureFile_Resource_Using_CPU(ID3D11Device* pDevice,	ID3D11DeviceContext* pContext,		T_STR szName)
	{
		HRESULT hr;
		D3DX11_IMAGE_INFO image_info;
		ID3D11Resource* pLoadTexture_ResourceStage = NULL;
		D3DX11_IMAGE_LOAD_INFO image_load_info;

		ZeroMemory(&image_load_info, sizeof(image_load_info));
		image_load_info.MipLevels = 1;//���� �𸣰ھ�. ������ ���ذ�.
		image_load_info.Usage = D3D11_USAGE_STAGING;//CPU GPU �Ѵ� �а��� ����
		image_load_info.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		image_load_info.Format = DXGI_FORMAT_FROM_FILE;
		image_load_info.pSrcInfo = &image_info;

		

		if (FAILED(hr = D3DX11CreateTextureFromFile(pDevice, szName.c_str(), &image_load_info, NULL, &pLoadTexture_ResourceStage, NULL)))
		{			return false;		}



		ID3D11Texture2D* pTexture2D = nullptr;

		
		if (FAILED(pLoadTexture_ResourceStage->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
		{			return false;}
		pLoadTexture_ResourceStage->Release();
		


		D3D11_TEXTURE2D_DESC texture2D_desc;
		pTexture2D->GetDesc(&texture2D_desc);
	
		m_fHeightList.resize(texture2D_desc.Height*texture2D_desc.Width);
		m_per_collum_total_Rows_numbers = texture2D_desc.Height; // �̰� �ٽ��̴�.
		m_per_row_total_Collums_numbers = texture2D_desc.Width; // �� �̰͸� �Ѿ�´�.

		m_per_collum_total_Cells_numbers = m_per_collum_total_Rows_numbers - 1;
		m_per_row_total_Cells_numbers = m_per_row_total_Collums_numbers - 1;

		m_total_Vertices_numbers = m_per_collum_total_Rows_numbers * m_per_row_total_Collums_numbers;
		m_total_faces_numbers = m_per_collum_total_Cells_numbers * m_per_row_total_Cells_numbers * 2;
		
		

		D3D11_MAPPED_SUBRESOURCE mapped_subresounce; // structure : Provides access to subresource data.    void *pData;		UINT RowPitch;		UINT DepthPitch;

		UINT index = D3D11CalcSubresource(0, 0, 1);

		if (SUCCEEDED(pContext->Map(pTexture2D, index, D3D11_MAP_READ, 0, &mapped_subresounce)))  
			//pTexture2D=A pointer to a ID3D11Resource interface. ����Ʈ�� �߾ ���ҽ���.
			//index=Index number of the subresource.
			//A D3D11_MAP-typed value that specifies the CPU's read and write permissions for a resource.
			//Flag that specifies what the CPU does when the GPU is busy. This flag is optional.
			//A pointer to the D3D11_MAPPED_SUBRESOURCE structure for the mapped subresource. See the Remarks section regarding NULL pointers.
		{

			UCHAR* pTexels = (UCHAR*)mapped_subresounce.pData; // pData �̰� �Ƹ� ���� �������ΰ���. // UCHAR : 0~255 ���� ���� ����

			for (UINT iRow = 0; iRow < texture2D_desc.Height; iRow++)// �и��� �� Row�ϱ� �� �׸��� xy�� 2���� ���ذ�.
			{
				UINT rowStart = iRow * mapped_subresounce.RowPitch; // �� ROW�� ���� Ȥ��, ��... ���Ұ�����.

				for (UINT iCol = 0; iCol < texture2D_desc.Width; iCol++)   // �ݷ� �Ѱ��� �ȴ´�. �׸��� xy�� 2���� ���ذ�.
				{
					UINT colStart = iCol * 4; // �� �̰� ���ϱ� 4��? RGBA��. �� GRay_scale�� ���߳�? �װ� �ǹ� �ֳ�?

					UCHAR uRed = pTexels[rowStart + colStart + 0]; //UCHAR �� 0~255��. // �̰� ���� ���صǾ���.
										
					m_fHeightList[iRow*texture2D_desc.Width + iCol] = uRed;//iRow �� ��ȣ *texture2D_desc.Width ���� ���� + iCol �ݷ���ϱ� �´�.
				}
			}
			pContext->Unmap(pTexture2D, index);
		}
		return true;
	}

public:
	bool Set_VertexData()
	{


		m_icount_Vertexs = m_total_Vertices_numbers;
		m_VertexList.resize(m_total_Vertices_numbers);

		float f_per_oneRow_Half_of_total_Collums_numbers = (m_per_row_total_Collums_numbers - 1) / 2.0f;
		float f_per_oneCollum_Half_of_total_Rows_numbers = (m_per_collum_total_Rows_numbers - 1) / 2.0f;

		float fOffsetU = 1.0f / (m_per_row_total_Collums_numbers - 1);//������ �����ϰ� �ؾ� �Ѵ�
		float fOffsetV = 1.0f / (m_per_collum_total_Rows_numbers - 1);//������ �����ϰ� �ؾ� �Ѵ�

		for (int iRow = 0; iRow < m_per_collum_total_Rows_numbers; iRow++) //0��° �����
		{
			for (int iCol = 0; iCol < m_per_row_total_Collums_numbers; iCol++) // 0��° ������
			{
				int iIndex = iRow * m_per_row_total_Collums_numbers + iCol; //0��,0������. ���α��� ��. 
																			//���ؽ� �ε�����.
				m_VertexList[iIndex].p.x = (iCol - f_per_oneRow_Half_of_total_Collums_numbers)*m_Distance_from_A_Cell_to_side_Cell_in_Raw; // �Ǻ��� (0,0,0)�̱� ������, ������ ��ġ�� x���� -�̴�.
				m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex); // �ϴ� ����� 0.0f�� �������.
				m_VertexList[iIndex].p.z = -((iRow - f_per_oneCollum_Half_of_total_Rows_numbers)*m_Distance_from_A_Cell_to_side_Cell_in_Collum); // �Ǻ��� (0,0,0)�̰�, ������ ��ġ�� z���� +�̴�.
				m_VertexList[iIndex].n = GetNormalOfVertex(iIndex); // ������ ������ �ϴ� ����� 1.0f�� �س���.
				m_VertexList[iIndex].c = GetColorOfVertex(iIndex); // �ϴ��� ���ؽ� Į��� �� ������� �س���.
				m_VertexList[iIndex].t = GetTextureOfVertex(fOffsetU*iCol, fOffsetV*iRow); //�ش� ������ uv ���̴�.
			}
		}
		m_icount_Vertexs = m_VertexList.size();
		return true;
	}


	bool   set_IndexData()
	{
		m_icount_Indexes = m_total_faces_numbers * 3;
		m_IndexList.resize(m_icount_Indexes);
		int iIndex = 0;
		for (int iRow = 0; iRow < m_per_collum_total_Cells_numbers; iRow++) //���� �������� 1�� ����.
		{
			for (int iCol = 0; iCol < m_per_row_total_Cells_numbers; iCol++) // ���� �������� 1�� ����
			{
				// 0     1(4)   
				// 2(3)   5   
				int iNextRow = iRow + 1;
				m_IndexList[iIndex + 0] = iRow * m_per_row_total_Collums_numbers + iCol;
				m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] + 1;
				m_IndexList[iIndex + 2] = iNextRow * m_per_row_total_Collums_numbers + iCol;
				m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
				m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
				m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2] + 1;
				iIndex += 6;
			}
		}

		Generate_VertexNormals();

		return true;
	}


	D3DXVECTOR2 GetTextureOfVertex(float fU, float fV)
	{
		return D3DXVECTOR2(fU , fV );
	}
	
	D3DXVECTOR3 GetNormalOfVertex(int iIndex)
	{
		return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	D3DXVECTOR4 GetColorOfVertex(int iIndex)
	{
		return D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float       GetHeightOfVertex(int iIndex)
	{
		return m_fHeightList[iIndex] * m_fScaleHeight;
	}

public:
	Map() { m_fScaleHeight = 1; }
	virtual ~Map() {}




	bool   Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile, const char*  pFuntionName_VS, const char*  pFuntionName_PS)
	{
		PipeLineSetup.LoadTexture(pd3dDevice, pTexFile);
		PipeLineSetup.SetBlendState(pd3dDevice);
		PipeLineSetup.CreateVertextBuffer(pd3dDevice, &m_VertexList.at(0), m_icount_Vertexs);
		PipeLineSetup.CreateIndexBuffer(pd3dDevice, &m_IndexList.at(0), m_icount_Indexes);
		PipeLineSetup.CreateConstantBuffer(pd3dDevice, &m_Constant_Data);
		PipeLineSetup.CreateVertexShader(pd3dDevice, pVsFile, pFuntionName_VS);
		PipeLineSetup.CreateLayout(pd3dDevice);
		PipeLineSetup.CreatePixelShader(pd3dDevice, pPsFile, pFuntionName_PS);



		PipeLineSetup.ScreenViewPort_setting();
		PipeLineSetup.Create_RasterizerState();
		PipeLineSetup.CreateTexture2D_DepthStencilView();
		PipeLineSetup.CreateDepthStencilState();

		return true;
	}

	//
	bool Generate_VertexNormals() // �����Լ��ε�
	{
		Determine_theNumberof_FaceNormals();
		GenNormalLookupTable();
		Calcularation_VertexNormal_Using_FastLookup();
		return true;
	}


	void Determine_theNumberof_FaceNormals()
	{
		m_Face_NormalVector_List.resize(m_total_faces_numbers); //m_Face_Normal_List�� Face �� ��ŭ ������ǿ�.
	}






	void GenNormalLookupTable()
	{
		m_Normal_Lookup_Table.resize(m_total_Vertices_numbers);//�������� Table�� �ִ� �ǵ�, 6���� �ִ°ſ���.

		for (int iFace = 0; iFace < m_total_faces_numbers; iFace++) // ���̽����� ���ٶ�� �ؾ� �س�?
		{
			for (int iVertex = 0; iVertex < 3; iVertex++) // ���ؽ� 3�� ����. �׷���, �� Face���� ����
			{
				for (int iTable = 0; iTable < 6; iTable++)  // ���̺���� ���ٴ� �ſ���. 0~6����. �� ������ �߽����� ���� ���� �ִ°ſ���. 6�� ���̽���.
				{
					int iIndex = m_IndexList[iFace * 3 + iVertex]; // �� ������ Index List��.

					if (m_Normal_Lookup_Table[iIndex].faceIndex[iTable] == -1) // �� [iTable]�ΰ�. �� ���ؽ��� ����, ���̺��� �Ű����ϱ�. �̰� ��ü���ΰſ���.
					{
						m_Normal_Lookup_Table[iIndex].faceIndex[iTable] = iFace; // ���⼭ �߿��Ѱ�, Face�� �ȹٲ���. �׳� 5���� ��, �׳� �Ȱ��� Face����.����
						                                                      // �׷� �̰� ���� �ǹ̳�. Face�� ���� Face Number�� ����. �״ϱ�, �� Face�� ���°ſ���.
																// Face ���� �� �۾��� �ϰ� �ִ°ſ���. 
						break;
					}
				}
			}
		}
	}


	void CalcFaceNormals()
	{
		int iFaceIndex = 0;
		for (int iIndex = 0; iIndex < m_IndexList.size(); iIndex += 3)
		{
			DWORD i0 = m_IndexList[iIndex];
			DWORD i1 = m_IndexList[iIndex + 1];
			DWORD i2 = m_IndexList[iIndex + 2];
			m_Face_NormalVector_List[iFaceIndex++] = Compute_to_get_FaceNormalVector(i0, i1, i2); // �ε��� 3���� 1���� Traingle�� �����ȴ�.
		}
	}

	D3DXVECTOR3 Compute_to_get_FaceNormalVector(DWORD i0, DWORD i1, DWORD i2)
	{
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 v0 = m_VertexList[i1].p - m_VertexList[i0].p;
		D3DXVECTOR3 v1 = m_VertexList[i2].p - m_VertexList[i0].p;
		D3DXVec3Cross(&vNormal, &v0, &v1);
		D3DXVec3Normalize(&vNormal, &vNormal);
		return vNormal;
	}

	void Calcularation_VertexNormal_Using_FastLookup()
	{
		CalcFaceNormals();
		for (int iVertex = 0; iVertex < m_Normal_Lookup_Table.size(); iVertex++)
		{
			D3DXVECTOR3 avgNormal(0, 0, 0);
			int iFace = 0;
			for (iFace = 0; iFace < 6; iFace++)
			{
				if (m_Normal_Lookup_Table[iVertex].faceIndex[iFace] != -1)
				{
					int iFaceIndex = m_Normal_Lookup_Table[iVertex].faceIndex[iFace];

					avgNormal += m_Face_NormalVector_List[iFaceIndex];
				}
				else
				{
					break;
				}
			}
			D3DXVec3Normalize(&m_VertexList[iVertex].n, &avgNormal);


			//// ������
			//D3DXVECTOR3 vLight(100, 100, 100);
			//D3DXVec3Normalize(&vLight, &vLight);
			//float fDot = D3DXVec3Dot(&m_VertexList[iVertex].n, &vLight);
			//m_VertexList[iVertex].c.x = fDot;
			//m_VertexList[iVertex].c.y = fDot;
			//m_VertexList[iVertex].c.z = fDot;
		}
	}

};