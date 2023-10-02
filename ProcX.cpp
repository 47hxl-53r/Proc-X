/*
 * Copyright (c) 2023 47hxl-53r
 * All rights reserved. See the MIT License for details:
 * https://opensource.org/licenses/MIT
 */

#include <windows.h>
#include <wchar.h>


HWND mainWindowHandler;
HWND editHandle;
HWND buttonHandle;
HFONT fontHandle;


void killButtonClicked() {
    wchar_t pidText[128];
    GetWindowTextW(editHandle, pidText, sizeof(pidText) / sizeof(wchar_t));


    DWORD pid = _wtoi(pidText);
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess != NULL) {
        if (TerminateProcess(hProcess, 0)) {
            MessageBoxW(mainWindowHandler, L"Process terminated successfully.", L"Success", MB_ICONINFORMATION);
        } else {
            MessageBoxW(mainWindowHandler, L"Error while terminating the process.", L"Error", MB_ICONERROR);
        }
        CloseHandle(hProcess);
    } else {
        MessageBoxW(mainWindowHandler, L"Error while opening the process.", L"Error", MB_ICONERROR);
    }
}




// Main window 
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            CreateWindowW(L"STATIC", L"ProcX", WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 10, 380, 30, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Developed by: 47hxl-53r", WS_CHILD | WS_VISIBLE, 10, 50, 380, 20, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"GitHub: 47hxl-53r", WS_CHILD | WS_VISIBLE, 10, 70, 380, 20, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Description: Kill processes using PID", WS_CHILD | WS_VISIBLE, 10, 90, 380, 20, hwnd, NULL, NULL, NULL);
            editHandle = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 120, 280, 30, hwnd, NULL, NULL, NULL);
            buttonHandle = CreateWindowW(L"BUTTON", L"Kill", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 160, 280, 40, hwnd, NULL, NULL, NULL);
            fontHandle = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
            SendMessageW(buttonHandle, WM_SETFONT, (WPARAM)fontHandle, TRUE);
            SetFocus(editHandle);
            break;
        }


        case WM_SIZE: {
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);

            int centerX = (rcClient.right - rcClient.left) / 2;
            int editWidth = 280;
            int editHeight = 30;
            int buttonWidth = 280;
            int buttonHeight = 40;
            int editX = centerX - (editWidth / 2);
            int editY = rcClient.bottom - (buttonHeight + editHeight + 20);
            int buttonX = centerX - (buttonWidth / 2);
            int buttonY = editY + editHeight + 10;

            MoveWindow(editHandle, editX, editY, editWidth, editHeight, TRUE);
            MoveWindow(buttonHandle, buttonX, buttonY, buttonWidth, buttonHeight, TRUE);
            break;



        }
        case WM_COMMAND: {
            if (HIWORD(wParam) == BN_CLICKED) {
                if ((HWND)lParam == buttonHandle) {
                    killButtonClicked();}
            }break;
        }



        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }


        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }


        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = L"MainWindowClass";
    RegisterClassW(&wc);


    mainWindowHandler = CreateWindowExW(0, L"MainWindowClass", NULL, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);
    ShowWindow(mainWindowHandler, nCmdShow);
    UpdateWindow(mainWindowHandler);

    MSG hehe;
    while (GetMessage(&hehe, NULL, 0, 0)) {
        TranslateMessage(&hehe);
        DispatchMessage(&hehe);
    }

    DeleteObject(fontHandle);
    return (int)hehe.wParam;
}
