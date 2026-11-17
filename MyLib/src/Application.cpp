#include <windows.h>
#include <MyLib/Application.h>

namespace {
const wchar_t* kClassName = L"MyLibWindowsClass";

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp ) {
	switch ( msg ) {
	case WM_DESTROY:
		PostQuitMessage( 0 );//WM_QUITをメッセージに入れる
		return 0;
	}
	return DefWindowProcW( hwnd, msg, wp, lp );
}
}

bool MyLib::Application::Initialize( int width, int height, const std::wstring& title ) {
	WNDCLASSEXW wnd { };
	wnd.cbSize = sizeof(WNDCLASSEXW);
	wnd.lpfnWndProc = WndProc;
	wnd.hInstance = GetModuleHandleW( nullptr );
	wnd.lpszClassName = kClassName;
	RegisterClassExW( &wnd );

	RECT rc { 0,0,width,height };
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect( &rc, style, FALSE );
	//CreateWindowExWにはrc.right -rc.left,rc.bottom -rc.topを渡す。
	m_hwnd = CreateWindowExW( 0, kClassName, title.c_str( ), style, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, GetModuleHandleW( nullptr ), nullptr );
	ShowWindow( static_cast< HWND > ( m_hwnd ), SW_SHOW );
	return m_hwnd != nullptr;
}

void MyLib::Application::Run( ) {
	m_running = true;
	OnStart( );
	MSG msg { };
	while ( m_running ) {
		//溜まっているメッセージの処理
		while ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) ) {
		//while ( GetMessageW( &msg, nullptr, 0, 0 ) ) {
			if ( msg.message == WM_QUIT ) {
				m_running = false;
				break;
			}
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		if ( !m_running )break;

		OnUpdate( );
	}
	OnEnd( );
}

void MyLib::Application::Shutdown( ) {
	if ( IsWindow( static_cast< HWND >( m_hwnd ) ) ) {
		DestroyWindow( static_cast< HWND >( m_hwnd ) );
		UnregisterClassW( kClassName, GetModuleHandleW( nullptr ) );
	}
}