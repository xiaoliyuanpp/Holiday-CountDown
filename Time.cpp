#include <bits/stdc++.h>
#include <windows.h>
#include <commctrl.h>
#include <windowsx.h>
using namespace std;
int date,godate;
LPSTR temp;
string show;
string RandomText(){
    srand(time(NULL));
    srand(rand());
    switch (rand()%8){
        case 0:return "��������Ҫ�еģ���һʵ�����أ�";
        case 1:return "�����~����";
        case 2:return "�㲻����ѧ����ʵ��ʦҲ�����ϰ�";
        case 3:return "��ʦ����˵�Լ����ã�����Ϊta�����ϰ�";
        case 4:return "����һ��ѧ���ڼ��ο����о͹�ȥ��";
        case 5:return "���Ǵ󲿷�ʱ����ʵ�����˷���";
        case 6:return "��ʵѧУ�ܶ�涨����Υ����";
        case 7:return "ѧ����һЩ��˾Ա�����ۣ���Ϊ����996Ҳ������Ҫ����";
    }
    return "NULL";
}
LRESULT CALLBACK WinSunProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    HDC         hdc;		//�豸�������;
    PAINTSTRUCT ps ;		//�����ͼ�������ݵĽṹ��;
    RECT        rect;		//�ͻ�������; 
	switch (uMsg){//ͨ���ж���Ϣ������Ϣ��Ӧ
        case WM_CLOSE:{
            cout<<date<<endl<<godate;
            DestroyWindow(hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ�����ǳ���û���˳�
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);//����WM_QUIT��Ϣ��������Ϣѭ��
            break;
        case WM_COMMAND:{
            godate++;
            string BoxText;
            if(date==godate) BoxText="�ţ��٣�����\n";
            else BoxText="��һ���ȥ�ˣ�\n";
            BoxText.append(RandomText());
            MessageBox(hwnd,BoxText.c_str(),"Well done!",MB_OK);
            cout<<date<<endl<<godate;
            DestroyWindow(hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ�����ǳ���û���˳�
            break;
        }
        default:return DefWindowProc(hwnd, uMsg, wParam, lParam);//�Բ�����Ȥ����Ϣ����ȱʡ���������иô��룬�������������
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    freopen("date.ini","r",stdin);
    cin>>date>>godate;
    if(date==0||date==godate){
        MessageBox(NULL,"����date.ini��������������һ���������֣�","��ʾ",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }
    freopen("date.ini","w",stdout);
    show="��ѧ���Ѿ�����";
    int tmp=godate;
    string ss;
    while(tmp!=0){
        ss+=tmp%10+'0';
        tmp/=10;
    }
    for(int i=ss.length()-1;i>=0;i--) show+=ss[i];
    if(godate==0) show+="0";
    show+="�죬��ʣ";
    tmp=date-godate;
    ss.clear();
    while(tmp!=0){
        ss+=tmp%10+'0';
        tmp/=10;
    }
    for(int i=ss.length()-1;i>=0;i--) show+=ss[i];
    show+="��\n";
    show+=RandomText();
    WNDCLASS MainWindow; //����һ��������
	MainWindow.cbClsExtra = 0;
	MainWindow.cbWndExtra = 0;
	MainWindow.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	MainWindow.hCursor = LoadCursor(NULL, IDC_APPSTARTING);//���ù��
	MainWindow.hIcon = LoadIcon(NULL, IDI_INFORMATION);//���ô������Ͻǵ�ͼ��
	MainWindow.hInstance = hInstance;//���ô���������Ӧ�ó���ʵ��
	MainWindow.lpfnWndProc = WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	MainWindow.lpszClassName = "MainWindow";//���ô��������
	MainWindow.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	MainWindow.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&MainWindow);//�����ϵͳע�ᴰ��
    HWND MainWindowShow = CreateWindow("MainWindow", "�żٵ���ʱ",WS_OVERLAPPEDWINDOW|WS_VISIBLE,1300,600,400,300,NULL,NULL,hInstance,NULL);
    CreateWindow("STATIC",show.c_str(),WS_CHILD|WS_VISIBLE,0,50,400,50,MainWindowShow,NULL,hInstance,NULL);
    CreateWindow("BUTTON","�ţ�ѧ������",WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,0,150,400,50,MainWindowShow,NULL,hInstance,NULL);//��ť
	UpdateWindow(MainWindowShow);//���´���
    MSG mainmsg;
	//��Ϣѭ��
	while (GetMessage(&mainmsg, NULL, 0, 0)){//�����Ϣ����WM_QUIT,���ط���ֵ�������Ϣ��WM_QUIT��������
		TranslateMessage(&mainmsg);//������Ϣ�����WM_KEYDOWN��WM_KEYUP�����һ��WM_CHAR��Ϣ
		DispatchMessage(&mainmsg);//�ɷ���Ϣ
	}
    return 0;
}