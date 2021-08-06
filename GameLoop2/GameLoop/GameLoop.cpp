/**********************************************************************************
// GameLoop
//
// Cria��o:     19 Ago 2011
// Atualiza��o: 31 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descri��o: Esqueleto de um la�o de tempo real para criar um jogo.
//
**********************************************************************************/

#include <windows.h>        // inclui fun��es do windows
#include <windowsx.h>       // inclui fun��es extras do windows
#include "Resources.h"      // defini��es dos recursos utilizados

#include <random>
using namespace std;
// prot�tipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//
int randomNumber(int, int);

// -----------------------------------------------------------------------
// constantes, vari�veis e fun��es globais

int windowWidth = 960;     // largura da janela
int windowHeight = 540;     // altura da janela
bool fullScreen = false;    // tela cheia ou modo janela

bool vkKeys[256] = { 0 };   // estado das teclas do teclado
HWND hwnd;                  // identificador da janela


//Pintar tela
HDC hdc;

//Desenhar Imagem
HBITMAP image;
BITMAP bm;
HDC hdcImage;
int x, y = 0;


RECT rect;
int speedX,speedY;

// -----------------------------------------------------------------------
// fun��es do jogo

// inicializa o jogo alocando recursos
void GameInit()
{
	
	hdc = GetDC(hwnd);
	image = (HBITMAP)LoadImage(
		NULL,
		"Resources\\CarKara.bmp",
		IMAGE_BITMAP,
		0,//Pega tamanho original
		0,//Pega tamanho original
		LR_LOADFROMFILE
	);
	//le props de bitmap
	GetObject(image, sizeof(BITMAP), &bm);
	//pega contexto para bitmap
	hdcImage = CreateCompatibleDC(hdc);
	SelectObject(hdcImage, image);

	GetClientRect(hwnd, &rect);

	x = randomNumber(0, windowWidth - bm.bmWidth);
	y = randomNumber(0, windowHeight - bm.bmHeight);
	speedX = 5;
	speedY = 5;
}

// atualiza a l�gica do jogo
void GameUpdate()
{
	// sai com o pressionamento da tecla ESC
	if (vkKeys[VK_ESCAPE])
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	//Movimentar

	x+=speedX;
	y+=speedY;


	//Verificar colisao com Borda
	if (y + bm.bmHeight > windowHeight) {
		speedY = -speedY;
	}
	if (x + bm.bmWidth > windowWidth) {
		speedX = -speedX;
	}
	if (y < 0) {
		speedY = -speedY;
	}
	if (x  < 0) {
		speedX = -speedX;
	}
}

// desenha o pr�ximo quadro do jogo
void GameDraw(){

	//limpa janela
	FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
	//desenha img
	BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcImage, 0, 0, SRCCOPY);

	
}

// finaliza o jogo desalocando recursos
void GameFinalize()
{
	DeleteDC(hdcImage);
	DeleteObject((HBITMAP)image);
	ReleaseDC(hwnd, hdc);
}

// -----------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	MSG			msg;
	WNDCLASS	wndclass;

	// definindo uma classe de janela chamada "GameWindow" 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "GameWindow";

	// registrando "GameWindow"
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na cria��o da janela!", "Game", MB_ICONERROR);
		return 0;
	}

	int windowStyle = WS_OVERLAPPED | WS_SYSMENU;

	// tela cheia ou janela
	if (fullScreen)
	{
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		windowStyle = WS_POPUP;
	}

	// criando uma janela baseada na classe "GameWindow"
	// � necess�rio usar CreateWindowEx para usar AdjustWindowRectEx
	hwnd = CreateWindowEx(
		NULL,                           // estilos extras
		"GameWindow",                   // nome da "window class"
		"Game",                         // t�tulo da janela
		windowStyle,                    // estilo da janela
		CW_USEDEFAULT,                  // posi��o x inicial
		CW_USEDEFAULT,                  // posi��o y inicial
		windowWidth,                    // largura da janela
		windowHeight,                   // altura da janela
		NULL,                           // identificador do objeto pai
		NULL,                           // identificador do menu
		hInstance,                      // identificador da aplica��o
		NULL);                          // par�metros de cria��o

	if (!fullScreen)
	{
		// ret�ngulo com o tamanho da �rea cliente desejada
		RECT winRect = { 0, 0, windowWidth, windowHeight };

		// ajuste do tamanho da janela
		AdjustWindowRectEx(&winRect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd));

		// atualiza posi��o da janela
		int windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
		int windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

		// redimensiona janela com uma chamada a MoveWindow
		MoveWindow(
			hwnd,                           // identificador da janela
			windowPosX,                     // posi��o x
			windowPosY,                     // posi��o y
			winRect.right - winRect.left,   // largura
			winRect.bottom - winRect.top,   // altura
			TRUE);                          // repintar
	}

	// mostra e atualiza a janela
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	GameInit();

	// loop principal do jogo
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameUpdate();
			GameDraw();
			//Dormir
			Sleep(16);
		}
	} while (msg.message != WM_QUIT);

	GameFinalize();

	// fim do programa
	return int(msg.wParam);
}

// -----------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// processa teclas pressionadas
	case WM_KEYDOWN:
		vkKeys[wParam] = true;
		return 0;

		// processa teclas liberadas
	case WM_KEYUP:
		vkKeys[wParam] = false;
		return 0;

		// janela foi fechada
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

//Gerando numeros aleatorio em um range
int randomNumber(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}
// -----------------------------------------------------------------------