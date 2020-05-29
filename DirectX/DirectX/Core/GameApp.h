#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "Utils/LightHelper.h"

class GameApp : public D3DApp
{
public:

	struct VertexPosColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
	};

	struct VSConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
		DirectX::XMMATRIX worldInvTranspose;
	};


	struct PSConstantBuffer
	{
		DirectionalLight dirLight;
		PointLight pointLight;
		SpotLight spotLight;
		Material material;
		DirectX::XMFLOAT4 eyePos;
	};

public:

	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:

	bool InitEffect();
	bool InitResource();

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// 顶点输入布局 Vertex input layout
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		// 顶点缓冲区 Vertex buffer
	ComPtr<ID3D11Buffer> m_pIndexBuffer;		// 索引缓冲区 Index Buffer
	ComPtr<ID3D11Buffer> m_pConstantBuffer;		// 常量缓冲区 Constant buffer


	ComPtr<ID3D11VertexShader> m_pVertexShader;	// 顶点着色器 vertex Shader
	ComPtr<ID3D11PixelShader> m_pPixelShader;	// 像素着色器 ps shader
	ConstantBuffer m_CBuffer;					// 用于修改GPU常量缓冲区的变量 modify the GPU constant buffer
	VSConstantBuffer m_VSConstantBuffer;			// 用于修改用于VS的GPU常量缓冲区的变量
	PSConstantBuffer m_PSConstantBuffer;			// 用于修改用于PS的GPU常量缓冲区的变量

	DirectionalLight m_DirLight;					// 默认环境光
	PointLight m_PointLight;						// 默认点光
	SpotLight m_SpotLight;						    // 默认汇聚光
};


#endif