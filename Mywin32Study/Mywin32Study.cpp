#include "pch.h"
#include "framework.h"


class CClientDC 
{
protected:
    HDC mh_dc;
    HWND mh_wnd; // m_hWnd

public:
    CClientDC(HWND ah_wnd)
    {
        mh_dc = GetDC(ah_wnd);
        mh_wnd = ah_wnd;
    }

   virtual ~CClientDC()
    {
       ReleaseDC(mh_wnd, mh_dc);
    }

   void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey)
   {
       ::Rectangle(mh_dc, a_sx, a_sy, a_ex, a_ey);
   }
 };






int g_x=-30, g_y=-30;
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC h_dc = BeginPaint(hWnd, &ps);

        HPEN h_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HBRUSH h_brush = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ h_old_brush = SelectObject(h_dc, h_brush);
        HGDIOBJ h_old_pen = SelectObject(h_dc, h_pen);       
        Rectangle(h_dc, g_x-10, g_y-10, g_x+10,  g_y+10);
        SelectObject(h_dc, h_old_pen);
        SelectObject(h_dc, h_old_brush);
        DeleteObject(h_pen); //DeleteObject(SelectObject(h_dc, h_old_pen));
        DeleteObject(h_brush);
        EndPaint(hWnd, &ps);

        return 1;
    }else if (uMsg == WM_LBUTTONDOWN)
    {            
        CClientDC dc(hWnd);
        dc.Rectangle(10, 10, 100, 100);

        g_y = HIWORD(lParam); // (lParam >> 16) & 0x0000FFFF;
        g_x = LOWORD(lParam); // lParam & 0x0000FFFF;
        InvalidateRect(hWnd, NULL, FALSE);       

    } else if (uMsg == WM_DESTROY) {   // WM_CLOSE 처리후에 들어오는 메시지
        PostQuitMessage(0);  // 자신의 메시지 큐에 WM_QUIT 메시지를 넣는다!
    }
    

    // 개발자가 처리하지 않은 메시지들을 처리한다!
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 윈도우 클래스 등록 작업!!
    WNDCLASS wc;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;     // 배경색 지정
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);                // 커서 지정
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);   // 응용 프로그램 로고 아이콘 지정
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;    // 기본 메시지 처리기 함수 지정
    wc.lpszClassName = L"tipssoft";    // 윈도우 클래스 이름 지정
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);    // 윈도우 클래스 등록

    // 윈도우 생성!
    HWND hWnd = CreateWindowW(L"tipssoft", L"www.tipssoft.com",
        WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);   // 윈도우를 화면에 어떻게 출력할 것인가 지정!
    UpdateWindow(hWnd);    // WM_PAINT 메시지가 대기 상태에 있다면 즉시 수행하도록 한다!

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {   // WM_QUIT 메시지가 발생할때까지 반복한다.
        TranslateMessage(&msg);   // 키보드 메시지 발생시에 추가 메시지를 발생할지 여부 체크
        DispatchMessage(&msg);   // 발생된 메시지를 처리한다!
    }
    return msg.wParam;
}
