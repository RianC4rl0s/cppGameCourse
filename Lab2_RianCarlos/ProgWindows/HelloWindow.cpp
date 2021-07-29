/**********************************************************************************
// HellowWindow
//
// Cria��o:     06 Mai 2011
// Atualiza��o: 24 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Esqueleto b�sico de cria��o de uma janela no Windows
//              usando a API Win32. Este esqueleto pode ser usado como ponto
//              de partida para cria��o de qualquer aplica��o.
//
**********************************************************************************/

// inclui tipos b�sicos e fun��es da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "Resources.h"


// prot�tipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	HWND hwnd;            // identificador da janela
	MSG msg;              // mensagem
	WNDCLASS wndclass;    // classe da janela

	// Definindo uma classe de janela chamada "BasicWindow" 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));		//Configurando icone da app
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));//Configurando Cursor da app
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "BasicWindow";

	// Registrando a classe "BasicWindow"
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na cria��o da janela!", "Aplica��o", MB_ICONERROR);
		return 0;
	}
	//Configura��es de janelas 

	//FULL SCREEN
	/*int windowHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowWidth = GetSystemMetrics(SM_CXSCREEN);*/

	//Janela nao Fixa
	int windowWidth = 960;
	int windowHeight = 540;

	//Centralizar janela SEM RECT
	int windowPositionX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	int windowPositionY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;


	// Criando uma janela baseada na classe "BasicWindow" 
	hwnd = CreateWindowEx(
		NULL,
		"BasicWindow",              // classe da janela
		"Aplica��o",                // t�tulo da janela
		//FUll SCREEN
		//WS_POPUP,                   // estilo da janela sem bodas
		//Janela n�o fixa
		//WS_OVERLAPPEDWINDOW,                   // estilo da janela com bordas e botoes de fechar e minimizar
		WS_OVERLAPPED | WS_SYSMENU, //janela sem borda s� com botao de fechar
		//windowPositionX,                          // posi��o x inicial
		0,
		//windowPositionY,                           // posi��o y inicial
		0,
		windowWidth,
		windowHeight,
		NULL,                       // identificador da janela pai
		NULL,                       // identificador do menu
		hInstance,                  // identificador da aplica��o
		NULL
	);                      // par�metros de cria��o
	//CRIANDO RECT da area do cliente
	RECT winRect = { 0, 0, windowWidth, windowHeight };

	//Ajusta o tamanho da tela para que a cliente fique do tamanho correto
	AdjustWindowRectEx(&winRect,
		GetWindowStyle(hwnd),
		GetMenu(hwnd) != NULL,
		GetWindowExStyle(hwnd)
	);
	//Centralizar janela com as novas medidas
	windowPositionX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
	windowPositionY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);


	//Redimensiona a janela
	MoveWindow(
		hwnd,
		windowPositionX,
		windowPositionY,
		winRect.right - winRect.left,
		winRect.bottom - winRect.top,
		TRUE
	);

	// Mostra e atualiza a janela
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Tratamento de mensagens destinadas a janela da aplica��o
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// fim do programa
	return int(msg.wParam);
}

//-------------------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------