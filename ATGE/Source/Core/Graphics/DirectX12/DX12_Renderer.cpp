#pragma once

#ifdef _WIN32

#include "Core/Platform/Windows/WindowsHandles.h"
#include "Core/Graphics/GraphicsRenderer.h"
#include "DX12_Handles.h"

#include <vector>

#ifdef new 
#pragma push_macro("new") 
#undef new 
#endif

#pragma warning( push )
#pragma warning( disable : 4244 ) // conversion from 'wchar_t' to 'char', possible loss of data
#pragma warning( disable : 5204 ) // class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
#pragma warning( disable : 4265 ) // class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
#pragma warning( disable : 6387 ) // could be '0' does not adhere to the specification for the function
#pragma warning( disable : 4365 ) // conversion from 'LONG' to 'UINT', signed/unsigned mismatch

// controls whether all the display information is displayed or not
// #define VERBOSE_DISPLAY_INFO

namespace ATGE
{
	using Microsoft::WRL::ComPtr;

	bool GraphicsRenderer::initGraphics(const void* pPlatform)
	{
		Logger::debug("Starting DirectX12...\n");

		DXHandles* handles = new DXHandles();
		this->m_pGraphicsHandles = handles;

#pragma region InitDirect3D
		HRESULT result;

#pragma region Enable the D3D12 debug layer.
#ifdef _DEBUG 
		{
			ComPtr<ID3D12Debug> debugController;
			
			result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
			ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to get DebugInterface.\n");

			debugController->EnableDebugLayer();
		}
#endif
#pragma endregion

#pragma region Try to create hardware device.

		result = CreateDXGIFactory1(IID_PPV_ARGS(&handles->m_dxgiFactory));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create DXGI Factory.\n");
		result = D3D12CreateDevice(
								nullptr,					// default adapter
								D3D_FEATURE_LEVEL_12_0,
								IID_PPV_ARGS(&handles->m_d3dDevice));

		// Fallback to WARP device.
		if (FAILED(result))
		{
			ComPtr<IDXGIAdapter> pWarpAdapter;
			result = handles->m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));			
			ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to init Adapter.\n");

			result = D3D12CreateDevice(
								pWarpAdapter.Get(),
								D3D_FEATURE_LEVEL_11_0,
								IID_PPV_ARGS(&handles->m_d3dDevice));

			ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to init dx Device.\n");
		}
#pragma endregion

#pragma region Create Fence
		result = handles->m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&handles->m_Fence));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create fence.\n");

		handles->m_RtvDescriptorSize = handles->m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		handles->m_DsvDescriptorSize = handles->m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		handles->m_CbvSrvUavDescriptorSize = handles->m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
#pragma endregion

#pragma region Check 4X MSAA quality support for our back buffer format.
		// Check 4X MSAA quality support for our back buffer format.
		// All Direct3D 11 capable devices support 4X MSAA for all render 
		// target formats, so we only need to check quality support.
		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
		msQualityLevels.Format = handles->m_BackBufferFormat;
		msQualityLevels.SampleCount = 4;
		msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
		msQualityLevels.NumQualityLevels = 0;
		result = handles->m_d3dDevice->CheckFeatureSupport(
								D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
								&msQualityLevels,
								sizeof(msQualityLevels));

		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to check feature support");

		handles->m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
		ATGE_ASSERT_MSG(handles->m_4xMsaaQuality > 0, "Unexpected MSAA quality level.");
#pragma endregion

#pragma region Log Adapters
#ifdef _DEBUG
		std::vector<IDXGIAdapter*> adapterList;
		{
			UINT i = 0;
			IDXGIAdapter* adapter = nullptr;
			while (handles->m_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
			{
				DXGI_ADAPTER_DESC desc;
				adapter->GetDesc(&desc);

				std::wstring wText = L"***Adapter: ";
				wText += desc.Description;
				wText += L"\n";

				std::string text = std::string(wText.begin(), wText.end());

				Logger::log(LogLevel::LEVEL_DEBUG, text.c_str());

				adapterList.push_back(adapter);

				++i;
			}

		}

		for (const auto& adapter : adapterList)
		{
			{
				UINT i = 0;
				IDXGIOutput* output = nullptr;
				while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
				{
					DXGI_OUTPUT_DESC desc;
					output->GetDesc(&desc);
					
					// log device name
					{
						std::wstring wText = L"***Output: ";
						wText += desc.DeviceName;
						wText += L"\n";
					
						std::string text = std::string(wText.begin(), wText.end());
						Logger::log(LogLevel::LEVEL_DEBUG, text.c_str());
					}

#ifdef VERBOSE_DISPLAY_INFO
					{
						UINT count = 0;
						UINT flags = 0;

						// Call with nullptr to get list count.
						output->GetDisplayModeList(handles->m_BackBufferFormat, flags, &count, nullptr);

						std::vector<DXGI_MODE_DESC> modeList(count);
						output->GetDisplayModeList(handles->m_BackBufferFormat, flags, &count, &modeList[0]);

						for (auto& x : modeList)
						{
							UINT n = x.RefreshRate.Numerator;
							UINT d = x.RefreshRate.Denominator;
							std::wstring wText =
								L"Width = " + std::to_wstring(x.Width) + L" " +
								L"Height = " + std::to_wstring(x.Height) + L" " +
								L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) +
								L"\n";

							std::string text = std::string(wText.begin(), wText.end());
							Logger::log(LogLevel::LEVEL_DEBUG, text.c_str());
						}
					}
#endif

					output->Release();
					i++;
				}
			}

			adapter->Release();
		}
#endif
#pragma endregion
		
#pragma region Create Command Objects
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		result = handles->m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&handles->m_CommandQueue));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create command queue");

		result = handles->m_d3dDevice->CreateCommandAllocator(
								D3D12_COMMAND_LIST_TYPE_DIRECT,
								IID_PPV_ARGS(handles->m_DirectCmdListAlloc.GetAddressOf()));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create command allocator");

		result = handles->m_d3dDevice->CreateCommandList(
								0,
								D3D12_COMMAND_LIST_TYPE_DIRECT,
								handles->m_DirectCmdListAlloc.Get(), // Associated command allocator
								nullptr,                   // Initial PipelineStateObject
								IID_PPV_ARGS(handles->m_CommandList.GetAddressOf()));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create command list");

		// Start off in a closed state.  This is because the first time we refer 
		// to the command list we will Reset it, and it needs to be closed before
		// calling Reset.
		handles->m_CommandList->Close();
#pragma endregion

#pragma region Create Swap Chain
		// Release the previous swapchain we will be recreating.
		handles->m_SwapChain.Reset();

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = handles->m_ClientWidth;
		sd.BufferDesc.Height = handles->m_ClientHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = handles->m_BackBufferFormat;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SampleDesc.Count = handles->m_4xMsaaState ? 4u : 1u;
		sd.SampleDesc.Quality = handles->m_4xMsaaState ? (handles->m_4xMsaaQuality - 1) : 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = DXHandles::SwapChainBufferCount;
		sd.OutputWindow = ((PS_WindowsState*)pPlatform)->hwnd;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Note: Swap chain uses queue to perform flush.
		result = handles->m_dxgiFactory->CreateSwapChain(
						handles->m_CommandQueue.Get(),
						&sd,
						handles->m_SwapChain.GetAddressOf());

		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create swap chain");
#pragma endregion

#pragma region Create Rtv And Dsv Descriptor Heaps
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
		rtvHeapDesc.NumDescriptors = DXHandles::SwapChainBufferCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		rtvHeapDesc.NodeMask = 0;
		result = handles->m_d3dDevice->CreateDescriptorHeap(
						&rtvHeapDesc, IID_PPV_ARGS(handles->m_RtvHeap.GetAddressOf()));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create rtv descriptor heap");

		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
		dsvHeapDesc.NumDescriptors = 1;
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		dsvHeapDesc.NodeMask = 0;
		result = handles->m_d3dDevice->CreateDescriptorHeap(
						&dsvHeapDesc, IID_PPV_ARGS(handles->m_DsvHeap.GetAddressOf()));
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create dsv descriptor heap");
#pragma endregion

#pragma endregion

		this->onResize();

		Logger::debug("DirectX12 Initialized!!\n");

		return true;
	}
	
	void GraphicsRenderer::shutdown()
	{
		if (((DXHandles*)this->m_pGraphicsHandles)->m_d3dDevice != nullptr)
			this->flush();

		delete this->m_pGraphicsHandles;

		Logger::debug("DirectX12 Successfully Shutdown!!\n");
	}

	void GraphicsRenderer::renderFrame()
	{
		DXHandles* handles = static_cast<DXHandles*>(m_pGraphicsHandles);
		HRESULT result = S_OK;

		// Reset the command allocator.
		result = handles->m_DirectCmdListAlloc->Reset();
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to reset command allocator.");

		// Reset the command list; no initial pipeline state object.
		result = handles->m_CommandList->Reset(handles->m_DirectCmdListAlloc.Get(), nullptr);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to reset command list.");

		// Set the viewport and scissor rectangle.
		handles->m_CommandList->RSSetViewports(1, &handles->m_ScreenViewport);
		handles->m_CommandList->RSSetScissorRects(1, &handles->m_ScissorRect);

		// Get the current back buffer resource.
		ID3D12Resource* currBackBuffer = handles->m_SwapChainBuffer[handles->m_CurrBackBuffer].Get();

		// Transition the back buffer from PRESENT to RENDER_TARGET.
		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
						currBackBuffer,
						D3D12_RESOURCE_STATE_PRESENT,
						D3D12_RESOURCE_STATE_RENDER_TARGET);

		handles->m_CommandList->ResourceBarrier(1, &barrier);

		// Obtain the current render target view handle.
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(handles->m_RtvHeap->GetCPUDescriptorHandleForHeapStart());
		rtvHandle.Offset(handles->m_CurrBackBuffer, handles->m_RtvDescriptorSize);

		// Clear the render target view with a solid background color.
		const float clearColor[4] = { 0.69f, 0.77f, 0.87f, 1.0f }; // LightSteelBlue.
		handles->m_CommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

		// Clear the depth/stencil view.
		handles->m_CommandList->ClearDepthStencilView(
			handles->m_DsvHeap->GetCPUDescriptorHandleForHeapStart(),
			D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
			1.0f,
			0,
			0,
			nullptr);

		// Set the render target.
		auto cpuDesc = handles->m_DsvHeap->GetCPUDescriptorHandleForHeapStart();
		handles->m_CommandList->OMSetRenderTargets(1, &rtvHandle, true, &cpuDesc);

		// [Mesh rendering code would normally go here, but it is omitted for now.]

		// Transition the back buffer from RENDER_TARGET back to PRESENT.
		barrier = CD3DX12_RESOURCE_BARRIER::Transition(
				currBackBuffer,
				D3D12_RESOURCE_STATE_RENDER_TARGET,
				D3D12_RESOURCE_STATE_PRESENT);
		handles->m_CommandList->ResourceBarrier(1, &barrier);

		// Close the command list.
		result = handles->m_CommandList->Close();
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to close command list.");

		// Execute the command list.
		ID3D12CommandList* cmdLists[] = { handles->m_CommandList.Get() };
		handles->m_CommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

		// Present the swap chain.
		result = handles->m_SwapChain->Present(0, 0);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to present swap chain.");

		// Update the current back buffer index.
		handles->m_CurrBackBuffer = (handles->m_CurrBackBuffer + 1) % DXHandles::SwapChainBufferCount;

		// Wait until frame commands are complete.
		this->flush();
	}

	void GraphicsRenderer::onResize()
	{
		// Retrieve our DX12 handles.
		DXHandles* handles = static_cast<DXHandles*>(m_pGraphicsHandles);

		ATGE_ASSERT_MSG(handles->m_d3dDevice, "DirectX device not initialized.");
		ATGE_ASSERT_MSG(handles->m_SwapChain, "Swap chain not initialized.");
		ATGE_ASSERT_MSG(handles->m_DirectCmdListAlloc, "Command allocator not initialized.");

		// Flush the GPU queue before changing any resources.
		this->flush();

		HRESULT result = S_OK;

		// Reset the command list to prepare for resource changes.
		result = handles->m_CommandList->Reset(handles->m_DirectCmdListAlloc.Get(), nullptr);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to reset command list.");

		// Release previous render target resources.
		for (auto& buff : handles->m_SwapChainBuffer)
		{
			buff.Reset();
		}
		handles->m_DepthStencilBuffer.Reset();

		// Resize the swap chain buffers.
		result = handles->m_SwapChain->ResizeBuffers(
			DXHandles::SwapChainBufferCount,
			handles->m_ClientWidth, handles->m_ClientHeight,
			handles->m_BackBufferFormat,
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to resize swap chain buffers.");

		handles->m_CurrBackBuffer = 0;

		// Recreate render target views.
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(handles->m_RtvHeap->GetCPUDescriptorHandleForHeapStart());
		for (UINT i = 0; i < DXHandles::SwapChainBufferCount; i++)
		{
			result = handles->m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&handles->m_SwapChainBuffer[i]));
			ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to get swap chain buffer.");
			handles->m_d3dDevice->CreateRenderTargetView(handles->m_SwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
			rtvHeapHandle.Offset(1, handles->m_RtvDescriptorSize);
		}

		// Set up the depth/stencil buffer description.
		D3D12_RESOURCE_DESC depthStencilDesc = {};
		depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depthStencilDesc.Alignment = 0;
		depthStencilDesc.Width = handles->m_ClientWidth;
		depthStencilDesc.Height = handles->m_ClientHeight;
		depthStencilDesc.DepthOrArraySize = 1;
		depthStencilDesc.MipLevels = 1;
		// Use a typeless format so that both SRV and DSV can be created.
		depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		depthStencilDesc.SampleDesc.Count = handles->m_4xMsaaState ? 4 : 1;
		depthStencilDesc.SampleDesc.Quality = handles->m_4xMsaaState ? (handles->m_4xMsaaQuality - 1) : 0;
		depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		// Set the clear value.
		D3D12_CLEAR_VALUE optClear = {};
		optClear.Format = handles->m_DepthStencilFormat;
		optClear.DepthStencil.Depth = 1.0f;
		optClear.DepthStencil.Stencil = 0;

		CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		// Create the depth/stencil buffer resource.
		result = handles->m_d3dDevice->CreateCommittedResource(
					&heapProperties,
					D3D12_HEAP_FLAG_NONE,
					&depthStencilDesc,
					D3D12_RESOURCE_STATE_COMMON,
					&optClear,
					IID_PPV_ARGS(handles->m_DepthStencilBuffer.GetAddressOf()));

		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to create depth/stencil buffer resource.");

		// Create the depth/stencil view.
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Format = handles->m_DepthStencilFormat;
		dsvDesc.Texture2D.MipSlice = 0;
		handles->m_d3dDevice->CreateDepthStencilView(
			handles->m_DepthStencilBuffer.Get(),
			&dsvDesc,
			handles->m_DsvHeap->GetCPUDescriptorHandleForHeapStart());

		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(handles->m_DepthStencilBuffer.Get(),
					D3D12_RESOURCE_STATE_COMMON,
					D3D12_RESOURCE_STATE_DEPTH_WRITE);

		// Transition the depth/stencil buffer to a writable state.
		handles->m_CommandList->ResourceBarrier(1, &barrier);

		// Close the command list and execute the resize commands.
		result = handles->m_CommandList->Close();
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to close command list.");
		ID3D12CommandList* cmdLists[] = { handles->m_CommandList.Get() };
		handles->m_CommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

		// Wait until the GPU has completed the resize operations.
		this->flush();

		// Update the viewport and scissor rectangle to match the new window size.
		handles->m_ScreenViewport.TopLeftX = 0;
		handles->m_ScreenViewport.TopLeftY = 0;
		handles->m_ScreenViewport.Width = static_cast<float>(handles->m_ClientWidth);
		handles->m_ScreenViewport.Height = static_cast<float>(handles->m_ClientHeight);
		handles->m_ScreenViewport.MinDepth = 0.0f;
		handles->m_ScreenViewport.MaxDepth = 1.0f;

		handles->m_ScissorRect = { 0, 0, static_cast<LONG>(handles->m_ClientWidth), static_cast<LONG>(handles->m_ClientHeight) };
	}

	void GraphicsRenderer::flush()
	{
		DXHandles* handles = static_cast<DXHandles*>(m_pGraphicsHandles);
		HRESULT result = S_OK;

		// Advance the fence value to mark commands up to this fence point.
		handles->m_CurrentFence++;

		// Signal the command queue with the new fence value.
		result = handles->m_CommandQueue->Signal(handles->m_Fence.Get(), handles->m_CurrentFence);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to signal fence.");

		// If the GPU hasn't finished processing commands up to this fence point, wait.
		if (handles->m_Fence->GetCompletedValue() < handles->m_CurrentFence)
		{
			HANDLE eventHandle = CreateEventEx(nullptr, 0, 0, EVENT_ALL_ACCESS);
			result = handles->m_Fence->SetEventOnCompletion(handles->m_CurrentFence, eventHandle);
			ATGE_ASSERT_MSG(SUCCEEDED(result), "Failed to set event on fence completion.");

			// Wait until the GPU has completed processing.
			WaitForSingleObject(eventHandle, INFINITE);
			CloseHandle(eventHandle);
		}
	}
}

#pragma warning( pop ) 
#endif