#include "pch.h"
#include <stdio.h>   // sprintf_s 함수를 사용하기 위해!!
#include "tipsware.h"

// 서버에 접속하는 사용자를 관리하기 위한 구조체!! (1명에 해당하는 정보만 구성)
struct UserData
{
	unsigned int h_socket;   // 소켓 핸들
	char ip_address[16];     // 접속한 클라이언트의 주소
};

// 새로운 클라이언트가 접속을 하면 이 함수가 호출됨!! 
// ap_user_data에는 접속한 클라이언트 정보가 이미 구성되어 있음!
// ap_server에는 서버 객체에 대한 주소가 들어있음!
void OnNewUser(UserData *ap_user_data, void *ap_server, int a_server_index)
{
	char temp_str[64];
	sprintf_s(temp_str, 64, "새로운 사용자가 %s에서 접속을 했습니다!", ap_user_data->ip_address);
	// 접속된 클라이언트 주소가 담긴 문자열을 리스트 박스(컨트롤 아이디 1000번)에 추가한다.
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}

// 클라이언트가 데이터를 전송하면 이 함수가 호출됨!!
int OnClientMessage(CurrentServerNetworkData *ap_data, void *ap_server, int a_server_index)
{
	// 전달된 사용자 정보를 자신이 선언한 구조체로 형 변환해서 사용!
	// 서버가 만들어질 때 Sizeof(UserData) 크기로 만들어 달라고 지정했기 때문에 내부적으로
	// 사용자 정보는 UserData 형식으로 관리되고 있음
	UserData *p_user_data = (UserData *)ap_data->mp_net_user;
	char temp_str[128];
	if (ap_data->m_net_msg_id == 1) { // 채팅 데이터가 전달됨 (1번 아이디는 개발자가 정한 것임)
		// 누가 전송했는지 확인 하기 위해서 채팅을 전송한 클라이언트의 인터넷 주소를 채팅 데이터 앞에 
		// 붙여서 채팅 내용을 재구성한다.
		sprintf_s(temp_str, 128, "%s : %s", p_user_data->ip_address, ap_data->mp_net_body_data);
		// 재구성된 채팅 내용을 리스트 박스(컨트롤 아이디 1000번)에 추가한다.
		ListBox_InsertString(FindControl(1000), -1, temp_str);
		// 접속한 모든 클라이언트에게 채팅 내용을 다시 전송한다.
		BroadcastFrameData(ap_server, 1, temp_str, strlen(temp_str) + 1);
	}
	return 1;
}

// 클라이언트가 접속을 해제하면 이 함수가 호출됨!!
void OnCloseUser(UserData *ap_user_data, void *ap_server, int a_error_flag, int a_server_index)
{
	char temp_str[64];
	if (a_error_flag == 1) {  // 오류로 인한 클라이언트 해제!!
		sprintf_s(temp_str, 64, "%s에서 접속한 사용자를 강제로 접속 해제했습니다.", ap_user_data->ip_address);
	} else {  // 정상적인 클라이언트 해제!!
		sprintf_s(temp_str, 64, "%s에서 사용자가 접속을 해제하였습니다!", ap_user_data->ip_address);
	}
	// 클라이언트의 해제 상태를 리스트 박스((컨트롤 아이디 1000번))에 추가한다.
	ListBox_InsertString(FindControl(1000), -1, temp_str);
}

// 이 프로그램은 특별한 메시지를 사용하지 않는다!
NOT_USE_MESSAGE

int main()
{
	ChangeWorkSize(620, 240); // 작업 영역을 설정한다.
	Clear(0, RGB(72, 87, 114)); // 윈도우의 배경을 RGB(72, 87, 114) 색으로 채운다!
	StartSocketSystem();  // 이 프로그램이 소켓 시스템을 사용하겠다고 설정한다.

	// UserData 구조체를 사용하는 서버를 생성한다. 이 서버는 자신의 상태에 따라 위에서 정의한
	// OnNewUser, OnClientMessage, OnCloseUser 함수를 호출해서 작업을 진행한다.
	void *p_server = CreateServerSocket(sizeof(UserData), OnNewUser, OnClientMessage, OnCloseUser);
	// "127.0.0.1"에서 25001번 포트로 서버 서비스를 시작한다. (ip는 ipconfig)
	StartListenService(p_server, "127.0.0.1", 25001);

	CreateListBox(10, 30, 600, 200, 1000); // 1000번 아이디를 가진 리스트 박스를 생성한다.
	SelectFontObject("굴림", 12); // 글꼴을 '굴림', 12 크기로 변경한다.
	TextOut(15, 10, RGB(200, 255, 200), "사용자 채팅글 목록");  // 리스트 박스의 제목을 출력한다.

	ShowDisplay(); // 정보를 윈도우에 출력한다.
	return 0;
}