#include "textureclass.h"

TextureClass::TextureClass()
{
	m_texture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	// Load the texture in
	// D3DX11CreateShaderResourceViewFromFile: create a shader-resource view from a file
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
		return false;

	// The texture can now be used to render with
	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture resource
	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
