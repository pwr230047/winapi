#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

LPSTR NazwaKlasy = "Klasa123";
/* Prototypy funkcji */
LRESULT CALLBACK WndProc (HWND hwnd,
                          UINT msg,
                          WPARAM wParam,
                          LPARAM lParam );
void func(HWND handle);
void text(int x1, int y1, int x2, int y2, HWND *hText, HWND hWnd, HINSTANCE hInstance);

//HWND hText;
HWND hText1;
HWND hPrzycisk;

int WINAPI WinMain (HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
    WNDCLASSEX wc;
    MSG messages;
    /* The Window structure */
    wc.hInstance = hInstance;
    wc.lpszClassName = NazwaKlasy;
    wc.lpfnWndProc = WndProc;      /* WskaŸnik do procedury obs³uguj¹cej okno */
    wc.style = 0;                 /* Catch double-clicks */
    wc.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;                 /* No menu */
    wc.lpszClassName = NazwaKlasy;          // Nazwa klasy, któr¹ tworzymy
    wc.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wc.cbWndExtra = 0;                      /* structure or the window instance */
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    /* Use Windows's default colour as the background of the window */
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wc))
        return 0;

    /* The class is registered, let's create the program*/
    HWND hWnd = CreateWindowEx (
           WS_EX_WINDOWEDGE,        // Styl okna
           NazwaKlasy,              // Nazwa klasy
           "Kalkulator Obwodu RL", // Nazwa okienka
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1000,                 /* The programs width */
           700,                 /* and height in pixels */
           NULL, NULL,               /* No menu */
           hInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    if( hWnd == NULL )
    {
        MessageBox( NULL, "Okno nie moze zostac otworzone!", "BLAD", MB_ICONEXCLAMATION );
        return 1;
    }
    /* Pole Tekstowe 1 */
    text(5, 5, 100, 30, &hText1, hWnd, hInstance);
    /* Przycisk */
    hPrzycisk = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON",
                               "przycisk", WS_CHILD | WS_VISIBLE,
                               5, 10, 100, 30, hWnd, NULL, hInstance, NULL);

    /* Make the window visible on the screen */
    ShowWindow (hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Wyswietlenie obrazu
    HBITMAP hbmObraz;
    hbmObraz = (HBITMAP)LoadImage(NULL, "Obwod RL.bmp", IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
    HDC hdcOkno = GetDC(hWnd);
    HDC hdcNowy = CreateCompatibleDC(hdcOkno);
    BITMAP bmInfo;
    GetObject(hbmObraz, sizeof(bmInfo), &bmInfo);
    SelectObject(hdcNowy, hbmObraz);
    BitBlt(hdcOkno, 450, 20, 320, 280, hdcNowy, 0, 0, SRCCOPY);
    DeleteObject(hbmObraz);
    DeleteDC(hdcNowy);
    DeleteDC(hdcOkno);
    ReleaseDC( hWnd, hdcOkno );
    //
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)                  /* handle the messages */
    {
        /* Okna */
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        case WM_PAINT:
        {
            PAINTSTRUCT ps; // deklaracja struktury
            HDC hdc = BeginPaint( hwnd, & ps );
            // instukcje rysuj¹ce coœ na oknie
            // ...
            EndPaint( hwnd, & ps ); // zwalniamy hdc
            break;
        }
    }
    return 0;
}
void func(HWND handle)
{
    // Pobiera ilosc znaku w polu
    DWORD length = GetWindowTextLength(handle);
    // Alokuje Pamiec dla tych znakow
    LPSTR buf = (LPSTR) GlobalAlloc(GPTR, length);
    // Pobiera tekst z okna i zapisuje je w buforz
    GetWindowText(handle, buf, length + 1);
}
void text(int x1, int y1, int x2, int y2, HWND *hText, HWND hWnd, HINSTANCE hInstance)
{
    *hText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT",
                               NULL, WS_CHILD | WS_VISIBLE ,
                               x1, y1, x2, y2, hWnd, NULL, hInstance, NULL);
}
