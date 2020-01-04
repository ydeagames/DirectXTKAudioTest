//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// Mouse
	std::unique_ptr<DirectX::Mouse>			m_mouse;
	// Keyboard
	std::unique_ptr<DirectX::Keyboard>		m_keyboard;

	// <<4>> DirectXTK Audio エンジン
	std::unique_ptr<DirectX::AudioEngine> audEngine;

	// <<5>> 以下の2つは音がなり続けている間にdeleteされてはいけない(音が止まる)
	// 今回再生する音のファイル(同じ音を鳴らすなら使い回す)
	std::unique_ptr<DirectX::SoundEffect> soundEffect;
	// 今回再生する音そのもの(音を鳴らすたびに作る)
	std::unique_ptr<DirectX::SoundEffectInstance> soundEffectInstance;
};
