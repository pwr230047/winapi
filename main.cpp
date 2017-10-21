#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>

LPSTR NazwaKlasy = "Klasa123";
/* Prototypy funkcji */
LRESULT CALLBACK WndProc (HWND hwnd,
                          UINT msg,
                          WPARAM wParam,
                          LPARAM lParam );
double func(HWND handle);
void value(int x1, int y1, int x2, int y2, HWND *hText, HWND hWnd, HINSTANCE hInstance);
void symbole(int x1, int y1, int x2, int y2, HWND *hText, HWND hWnd, HINSTANCE hInstance);
void wstaw(HWND *hStatic, char *lancuch);
/* Variable */
HWND hText[6];
HWND hPrzycisk;
HWND hStatic[6];
HWND hS_text[6];
double liczba1, liczba2, liczba3, liczba4, liczba5;
double c_wynik, Xl_wynik;
char str_1[40];
char str_2[40];
char str_3[40];

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
    wc.lpfnWndProc = WndProc;      /* Wskaznik do procedury obslugujacej okno */
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
           800,                 /* The programs width */
           370,                 /* and height in pixels */
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
    value(100, 15, 100, 30, &hText[0], hWnd, hInstance);
    value(100, 55, 100, 30, &hText[1], hWnd, hInstance);
    value(100, 95, 100, 30, &hText[2], hWnd, hInstance);
    value(100, 135, 100, 30, &hText[3], hWnd, hInstance);
    value(100, 175, 100, 30, &hText[4], hWnd, hInstance);
    value(100, 215, 100, 30, &hText[5], hWnd, hInstance);

    /* Przycisk */
    hPrzycisk = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON",
                               "Oblicz", WS_CHILD | WS_VISIBLE,
                               240, 135, 100, 30, hWnd, NULL, hInstance, NULL);
    /* Static */
    symbole(10, 15, 60, 30, &hStatic[0], hWnd, hInstance);
    symbole(10, 55, 60, 30, &hStatic[1], hWnd, hInstance);
    symbole(10, 95, 60, 30, &hStatic[2], hWnd, hInstance);
    symbole(10, 135, 60, 30, &hStatic[3], hWnd, hInstance);
    symbole(10, 175, 60, 30, &hStatic[4], hWnd, hInstance);
    symbole(10, 215, 60, 30, &hStatic[5], hWnd, hInstance);

    /* Ustawienie tekstu */
    wstaw(&hStatic[0], "R[Ohm]=");
    wstaw(&hStatic[1], "L[H]=");
    wstaw(&hStatic[2], "f[Hz]=");
    wstaw(&hStatic[3], "XR[Ohm]=");
    wstaw(&hStatic[4], "XL[Ohm]=");
    wstaw(&hStatic[5], "Z[Ohm]=");

    /* Make the window visible on the screen */
    ShowWindow (hWnd, nCmdShow);
    UpdateWindow(hWnd);


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

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
            // Wyswietlenie obrazu
        case WM_PAINT:
        {
            PAINTSTRUCT ps; // deklaracja struktury
            HDC hdcOkno = BeginPaint( hwnd, & ps );
            HBITMAP hbmObraz;
            hbmObraz = (HBITMAP)LoadImage(NULL, "Obwod RL.bmp", IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
            HDC hdcNowy = CreateCompatibleDC(hdcOkno);
            BITMAP bmInfo;
            GetObject(hbmObraz, sizeof(bmInfo), &bmInfo);
            SelectObject(hdcNowy, hbmObraz);
            BitBlt(hdcOkno, 450, 20, 320, 280, hdcNowy, 0, 0, SRCCOPY);
            DeleteObject(hbmObraz);
            DeleteDC(hdcNowy);
            DeleteDC(hdcOkno);
            ReleaseDC( hwnd, hdcOkno );

            EndPaint( hwnd, & ps ); // zwalniamy hdc
            break;
        }
        case WM_COMMAND:
        {
            if(( HWND ) lParam == hPrzycisk )
            {
                liczba1 = func(hText[0]);
                liczba2 = func(hText[1]);
                liczba3 = func(hText[2]);
                Xl_wynik = 2*3.14*liczba3*liczba2;
                c_wynik = (liczba1 + Xl_wynik);
                itoa(liczba1, str_1, 10);
                itoa(Xl_wynik, str_2, 10);
                itoa(c_wynik, str_3, 10);
                wstaw(&hText[3], str_1);
                wstaw(&hText[4], str_2);
                wstaw(&hText[5], str_3);
            }
        break;
        }

    return 0;
    }
}
double func(HWND handle)
{
    // Pobiera ilosc znaku w polu
    DWORD length = GetWindowTextLength(handle);
    // Alokuje Pamiec dla tych znakow
    LPSTR buf = (LPSTR) GlobalAlloc(GPTR, length);
    // Pobiera tekst z okna i zapisuje je w buforze
    GetWindowText(handle, (LPSTR) buf, length + 1);
    double wynik = atoi(buf);
    GlobalFree( buf );
    return wynik;
}
void value(int x1, int y1, int x2, int y2, HWND *hText, HWND hWnd, HINSTANCE hInstance)
{
    *hText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT",
                               NULL, WS_CHILD | WS_VISIBLE ,
                               x1, y1, x2, y2, hWnd, NULL, hInstance, NULL);
}
void symbole(int x1, int y1, int x2, int y2, HWND *hStatic , HWND hWnd, HINSTANCE hInstance)
{
    *hStatic = CreateWindowEx(0, "STATIC",
                            NULL, WS_CHILD | WS_VISIBLE | SS_LEFT,
                            x1, y1, x2, y2, hWnd, NULL, hInstance, NULL);
}
void wstaw(HWND *hStatic, char *lancuch)
{
    SetWindowText(*hStatic, lancuch);
}
