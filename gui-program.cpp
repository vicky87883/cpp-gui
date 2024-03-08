#include <windows.h>

// Step 1: Declare global variables
const char g_szClassName[] = "myWindowClass";
HINSTANCE g_hInstance;

// Step 2: Declare the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Step 3: Register the window class
BOOL RegisterMyWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassEx(&wc);
}

// Step 4: Create the window
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd = CreateWindow(
        g_szClassName, "My First GUI Program",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if(!hwnd)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}

// Step 5: Main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    g_hInstance = hInstance;
    if (!RegisterMyWindowClass(hInstance))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = InitInstance(hInstance, nCmdShow);

    if (!hwnd)
        return 0;

    MSG Msg;
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

