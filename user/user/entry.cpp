#include "library/globals.h"

HWND g_targetWnd = nullptr;
HWND g_button = nullptr;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void StartWindowSelection(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"MELLSTROYs";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"MELLSTROY HWND", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        g_button = CreateWindow(L"BUTTON", L"Select Target", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 40, 200, 40, hwnd, (HMENU)100, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 100)
        {
            EnableWindow(g_button, FALSE);
            SetWindowText(g_button, L"Waiting window...");
            if (!service_is_load())
            {
                MessageBox(hwnd, L"Driver is not loaded...", L"MELLSTROY HWND", MB_ICONERROR);
                break;
            }
            StartWindowSelection(hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void StartWindowSelection(HWND owner)
{
    SetCursor(LoadCursor(nullptr, IDC_CROSS));
    SetCapture(owner);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (msg.message == WM_LBUTTONDOWN)
        {
            POINT pt = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
            ClientToScreen(owner, &pt);
            g_targetWnd = WindowFromPoint(pt);
            ReleaseCapture();
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    NTSTATUS status = protect_sprite_content_ex(g_targetWnd, WDA_EXCLUDEFROMCAPTURE);

    SetWindowText(g_button, L"Window selected :)");
    Sleep(750);
    EnableWindow(g_button, TRUE);
    SetWindowText(g_button, L"Select Target");
}