#include "pch.h"
#include <stdio.h>   // sprintf_s 함수를 사용하기 위해!!
#include "tipsware.h"
 
struct AppData   // 프로그램에서 사용할 내부 데이터
{
	void *p_socket;  // 클라이언트 소켓을 사용하는 객체의 주소!
};

// 서버에 접속했거나 접속에 실패했을 때 호출되는 함수
void OnServerConnection(void *ap_this, int a_client_index)
{
	char temp_str[64];
	if (IsConnect(ap_this)) sprintf_s(temp_str, 64, "서버에 접속했습니다!!");
	else sprintf_s(temp_str, 64, "서버에 접속할 수 없습니다.!!");
	// 서버 접속 결과를 리스트 박스(컨트롤 아이디 1000번)에 추가한다.
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}

// 서버가 데이터를 전송하면 이 함수가 호출됨!!
int OnServerMessage(CurrentClientNetworkData *ap_data, void *ap_this, int a_client_index)
{
	if (ap_data->m_net_msg_id == 1) { // 채팅 데이터가 전달됨
		// 서버가 전달한 채팅 내용을 리스트 박스(컨트롤 아이디 1000번)에 추가한다.
		ListBox_InsertString(FindControl(1000), -1, ap_data->mp_net_body_data);
	}
	return 1;
}

// 서버와 접속 상태가 변경되면 이 함수가 호출됨
void OnCloseUser(void *ap_this, int a_error_flag, int a_client_index)
{
	char temp_str[64];
	if (a_error_flag == 1) sprintf_s(temp_str, 64, "서버에서 접속을 해제했습니다."); // 서버가 해제함!!
	else sprintf_s(temp_str, 64, "서버와 접속을 해제했습니다.");  // 클라이언트에서 해제함!!
	// 해제 상태를 리스트 박스(컨트롤 아이디 1000번)에 추가한다.
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}


// 서버에 접속을 시도합니다.
void OnConnectBtn(AppData *ap_data)
{
	if (ap_data->p_socket == NULL) {  // 클라이언트 소켓 객체가 만들어져 있는지 확인!
		// 객체가 만들어지기 전이라면 클라이언트 소켓 객체를 생성한다.
		// 이 객체 자신의 상태가 바뀌면 위에서 만든 OnServerConnection, OnServerMessage,
		// OnCloseUser 함수를 호출하여 작업을 진행한다.
		ap_data->p_socket = CreateClientSocket(OnServerConnection, OnServerMessage, OnCloseUser);
	}

	if (!IsConnect(ap_data->p_socket)) {  // 서버와의 접속 상태를 체크한다.
		// "127.0.0.1" 주소에서 25001번 포트로 서비스 중인 서버에 접속을 시도한다.
		// 접속의 결과는 ConnectionResult 함수를 통해서 알 수 있다.
		ConnectToServer(ap_data->p_socket, "58.233.158.38", 25120);
	}
}

// 서버와 연결을 해제합니다.
void OnDisconnectBtn(AppData *ap_data)
{
	if (ap_data->p_socket != NULL) {  // 객체가 만들어져 있는 경우!		
		DeleteClientSocket(ap_data->p_socket); // 소켓 클라이언트 객체를 제거한다.
		ap_data->p_socket = NULL;
	}
}

// 채팅 데이터를 서버로 전송합니다.
void SendChatData(AppData *ap_data)
{
	void *p_edit = FindControl(1020); // 에디트 컨트롤의 주소를 얻는다.
	char str[128]; // 선택된 항목의 문자열을 저장할 변수

	// 에디터 컨트롤에 입력된 문자열을 str 배열에 복사한다.
	GetCtrlName(p_edit, str, 128);
	SetCtrlName(p_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.

	// 클라이언트 소켓 객체가 만들어져 있고 서버와 접속상태인지 확인한다.
	if (ap_data->p_socket && IsConnect(ap_data->p_socket)) {
		// 입력된 채팅 내용을 서버로 전송한다. 이때 채팅 메시지 아이디는 1로 지정한다.
		SendFrameDataToServer(ap_data->p_socket, 1, str, strlen(str) + 1);
	}
}

// 컨트롤을 조작했을 때 호출할 함수 만들기
// 컨트롤의 아이디(a_ctrl_id), 컨트롤의 조작 상태(a_notify_code), 선택한 컨트롤 객체(ap_ctrl)
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl)
{
	AppData *p_data = (AppData *)GetAppData();  // 프로그램 내부 데이터의 주소를 가져온다.

		// '입력' 버튼을 누르거나 에디트 박스에서 '엔터' 키를 누른 경우!
	if (a_ctrl_id == 1013 || (a_ctrl_id == 1020 && a_notify_code == 1000)) SendChatData(p_data);
	else if (a_ctrl_id == 1011) OnConnectBtn(p_data);  // [접속] 버튼을 누른 경우!
	else if (a_ctrl_id == 1012) OnDisconnectBtn(p_data); // [해제] 버튼을 누른 경우!
}

// 버튼을 클릭했을 때 호출할 함수를 지정한다.
CMD_MESSAGE(OnCommand)

int main()
{
	// 프로그램이 내부적으로 사용할 메모리를 선언한다.
	AppData data ={ NULL };
	SetAppData(&data, sizeof(AppData));  // 지정한 변수를 내부 데이터로 저장한다.

	ChangeWorkSize(520, 180);  // 작업 영역을 설정한다.
	Clear(0, RGB(82, 97, 124)); // 윈도우의 배경을 RGB(82, 97, 124) 색으로 채운다!
	StartSocketSystem(); // 이 프로그램이 소켓 시스템을 사용하겠다고 설정한다.

	CreateListBox(10, 36, 500, 100, 1000);  // 채팅 목록!

	CreateButton("접속", 407, 3, 50, 28, 1011);     // [접속] 버튼 생성
	CreateButton("해제", 460, 3, 50, 28, 1012);     // [해제] 버튼 생성
	CreateButton("입력", 460, 140, 50, 28, 1013);   // [입력] 버튼 생성 

	void *p = CreateEdit(10, 143, 446, 24, 1020, 0);  // 문자열을 입력할 에디트 컨트롤을 생성!
	EnableEnterKey(p); // 에디트 컨트롤에 엔터키가 눌러지면 Notify Code(1000번)가 발생하게 설정

	SelectFontObject("굴림", 12); // 글꼴을 '굴림', 12 크기로 변경한다.	
	TextOut(15, 16, RGB(200, 255, 200), "사용자 채팅글 목록");  // 채팅 목록 리스트 박스의 제목을 출력

	ShowDisplay(); // 정보를 윈도우에 출력한다.
	return 0;
}