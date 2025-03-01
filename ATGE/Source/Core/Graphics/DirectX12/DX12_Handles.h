#pragma once
#ifdef _WIN32

#ifdef new 
#pragma push_macro("new") 
#undef new 
#endif

#include "Core/Tools/ATGEAssert.h"

#include <array>

// d3d12 Includes
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <WindowsX.h>
#include "d3dx12.h"

// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

namespace ATGE
{
	using Microsoft::WRL::ComPtr;

	class DXHandles
	{
	public:
		static const uint SwapChainBufferCount = 2;

		std::array<ComPtr<ID3D12Resource>, SwapChainBufferCount> m_SwapChainBuffer;

		ComPtr<IDXGIFactory4> m_dxgiFactory;
		ComPtr<IDXGISwapChain> m_SwapChain;
		ComPtr<ID3D12Device> m_d3dDevice;

		ComPtr<ID3D12Fence> m_Fence;

		ComPtr<ID3D12CommandQueue> m_CommandQueue;
		ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;

		ComPtr<ID3D12Resource> m_DepthStencilBuffer;

		ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
		ComPtr<ID3D12DescriptorHeap> m_DsvHeap;
		ulong m_CurrentFence = 0;

		D3D12_VIEWPORT m_ScreenViewport;
		D3D12_RECT m_ScissorRect;

		UINT m_RtvDescriptorSize = 0;
		UINT m_DsvDescriptorSize = 0;
		UINT m_CbvSrvUavDescriptorSize = 0;

		// Set true to use 4X MSAA (§4.1.8).  The default is false.
		UINT      m_4xMsaaQuality = 0;      // quality level of 4X MSAA

		int m_CurrBackBuffer = 0;

		// Derived class should set these in derived constructor to customize starting values.
		D3D_DRIVER_TYPE m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
		DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
		uint m_ClientWidth = 800;
		uint m_ClientHeight = 600;

		bool      m_4xMsaaState = false;    // 4X MSAA enabled
	};
}

#endif
