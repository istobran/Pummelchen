#pragma once

#include <stdio.h>

#include "d3dx9.h"
#include "CCallGate.h"


int m_Stride = 0;

DWORD dwOldZEnable = D3DZB_TRUE;

LPDIRECT3DTEXTURE9 texRed;
LPDIRECT3DTEXTURE9 texYellow;
LPDIRECT3DTEXTURE9 texBlue;
LPDIRECT3DTEXTURE9 texGreen;

const BYTE bBlue[60] =
{
	0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
};

const BYTE bGreen[60] =
{
	0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0xA0, 0x00, 0x00, 0xFF, 0xFF
};

const BYTE bRed[60] = 
{ 
    0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00 
}; 


const BYTE bYellow[60] =
{
	0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00
};


EXTDEFVFUNC(pCreateDevice, HRESULT, ( IDirect3D9 *pD3D9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface ));


HRESULT WINAPI CreateDevice( IDirect3D9 *pD3D9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface );


DEFVFUNC(pDrawIndexedPrimitive, HRESULT, ( IDirect3DDevice9 *pDevice, D3DPRIMITIVETYPE Type, int BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount ));
DEFVFUNC(pSetStreamSource, HRESULT, ( IDirect3DDevice9 *pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride ));
DEFVFUNC(pCreateDevice, HRESULT, ( IDirect3D9 *pD3D9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface ));


HRESULT WINAPI SetStreamSource( IDirect3DDevice9 *pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride )
{	
	HRESULT hRet = pSetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);

	if(StreamNumber == 0)
	{
		m_Stride = Stride;
	}

	return hRet;
}


HRESULT WINAPI DrawIndexedPrimitive( IDirect3DDevice9 *pDevice, D3DPRIMITIVETYPE Type, int BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount )
{
	// No Fog
	pDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
	
	// No Fog Textures
	if(m_Stride == 28)
	{
		pDevice->SetRenderState( D3DRS_ZFUNC, 1 );
	}		

	// No Sky Textures (441) + No Sun (4)
	if(m_Stride == 40)
	{	
		if(NumVertices == 4 || NumVertices == 441 )
		{	
			pDevice->SetRenderState( D3DRS_ZFUNC, 1 );
		}
	}	
	
	// Chams		
	if(m_Stride == 64)
	{			
		// Chams Claymores & Anti-Tank Mines
		if(NumVertices == 286 || NumVertices == 429)
		{
			pDevice->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable); 
            pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); 				
			                
			for (int i1 = 0; i1 < 4 ; i1++)
			{	
				pDevice->SetTexture(i1, texYellow);					
			}
            
			pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);				
            
			for (int i2 = 0; i2 < 4 ; i2++)
			{	
				pDevice->SetTexture(i2, texGreen);
			}
			
			return pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);			
		}		
	}	
		
	// Player Chams
	//if(m_Stride == 80)
	if(m_Stride == 56 || m_Stride == 80)
	{						
		pDevice->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable); 
	    pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); 
	    
		for (int i1 = 0; i1 < 4 ; i1++)
		{	
			pDevice->SetTexture(i1, texYellow);				
		}
	    
		pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
		pDevice->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);

		for (int i2 = 0; i2 < 4 ; i2++)
		{	
			pDevice->SetTexture(i2, texGreen);
		}
		
		return pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);			
	}
		
	// No Grass			
	if(m_Stride == 36)
	{
		pDevice->SetRenderState( D3DRS_ZFUNC, 1 );			
	}
	
	HRESULT hRet = pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);	
	return hRet;
}


HRESULT WINAPI CreateDevice(IDirect3D9 *pD3D9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface )
{
	HRESULT hRet = pCreateDevice(pD3D9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	if( SUCCEEDED(hRet) )
	{	
		static bool bHooked = false;
		if(!bHooked)
		{
			IDirect3DDevice9 *pDevice = (*ppReturnedDeviceInterface);
						
			HOOKD3DVFUNC(IDirect3DDevice9, pDevice, SetStreamSource, pSetStreamSource, SetStreamSource);
			HOOKD3DVFUNC(IDirect3DDevice9, pDevice, DrawIndexedPrimitive, pDrawIndexedPrimitive, DrawIndexedPrimitive);

			D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bRed,  60,  &texRed);
			D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bYellow, 60, &texYellow); 
			D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bBlue, 60, &texBlue);
			D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bGreen, 60, &texGreen);
						
			bHooked = true;
		}
	}

	return hRet;
}


bool WINAPI Pummelchen(HMODULE hDll, DWORD dwReason, PVOID pvReserved)
{	
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
		
		// Hook DirectX
		IDirect3D9 *pDirect3DCreate9 = Direct3DCreate9(D3D_SDK_VERSION);
		HOOKD3DVFUNC(IDirect3D9, pDirect3DCreate9, CreateDevice, pCreateDevice, CreateDevice);
		
		return true;
	}

	return true;
}