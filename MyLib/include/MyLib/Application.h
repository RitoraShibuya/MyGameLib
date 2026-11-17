#pragma once
#include <string>

namespace MyLib {

class Application {
public:
	Application( ) = default;
	virtual ~Application( ) = default;

	//ウィンドウを作る
	bool Initialize( int width, int height, const std::wstring& title );
	//ゲームループ
	void Run( );
	//後片付け
	void Shutdown( );

protected:
	//使う側の上書き
	virtual void OnStart( ) {}
	virtual void OnUpdate( ) {}
	virtual void OnEnd( ) {}

private:
	void* m_hwnd = nullptr;//ウィンドウハンドル（HWND）
	bool m_running = false;
};
};
