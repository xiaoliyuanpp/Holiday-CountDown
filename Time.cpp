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
        case 0:return "梦想总是要有的，万一实现了呢？";
        case 1:return "你干嘛~哈哈";
        case 2:return "你不想上学，其实老师也不想上班";
        case 3:return "老师故意说自己独裁，是因为ta不想上班";
        case 4:return "往往一个学段在几次考试中就过去了";
        case 5:return "我们大部分时间其实都被浪费了";
        case 6:return "其实学校很多规定都是违法的";
        case 7:return "学生比一些公司员工还累，因为别人996也不会需要早起";
    }
    return "NULL";
}
LRESULT CALLBACK WinSunProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    HDC         hdc;		//设备环境句柄;
    PAINTSTRUCT ps ;		//保存绘图环境数据的结构体;
    RECT        rect;		//客户区矩形; 
	switch (uMsg){//通过判断消息进行消息响应
        case WM_CLOSE:{
            cout<<date<<endl<<godate;
            DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环
            break;
        case WM_COMMAND:{
            godate++;
            string BoxText;
            if(date==godate) BoxText="放！假！辣！\n";
            else BoxText="又一天过去了！\n";
            BoxText.append(RandomText());
            MessageBox(hwnd,BoxText.c_str(),"Well done!",MB_OK);
            cout<<date<<endl<<godate;
            DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
            break;
        }
        default:return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    freopen("date.ini","r",stdin);
    cin>>date>>godate;
    if(date==0||date==godate){
        MessageBox(NULL,"请在date.ini中设置天数（第一行输入数字）","提示",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }
    freopen("date.ini","w",stdout);
    show="这学期已经过了";
    int tmp=godate;
    string ss;
    while(tmp!=0){
        ss+=tmp%10+'0';
        tmp/=10;
    }
    for(int i=ss.length()-1;i>=0;i--) show+=ss[i];
    if(godate==0) show+="0";
    show+="天，还剩";
    tmp=date-godate;
    ss.clear();
    while(tmp!=0){
        ss+=tmp%10+'0';
        tmp/=10;
    }
    for(int i=ss.length()-1;i>=0;i--) show+=ss[i];
    show+="天\n";
    show+=RandomText();
    WNDCLASS MainWindow; //创建一个窗体类
	MainWindow.cbClsExtra = 0;
	MainWindow.cbWndExtra = 0;
	MainWindow.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
	MainWindow.hCursor = LoadCursor(NULL, IDC_APPSTARTING);//设置光标
	MainWindow.hIcon = LoadIcon(NULL, IDI_INFORMATION);//设置窗体左上角的图标
	MainWindow.hInstance = hInstance;//设置窗体所属的应用程序实例
	MainWindow.lpfnWndProc = WinSunProc;//设置窗体的回调函数，暂时没写，先设置为NULL，后面补上
	MainWindow.lpszClassName = "MainWindow";//设置窗体的类名
	MainWindow.lpszMenuName = NULL;//设置窗体的菜单,没有，填NULL
	MainWindow.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
	RegisterClass(&MainWindow);//向操作系统注册窗体
    HWND MainWindowShow = CreateWindow("MainWindow", "放假倒计时",WS_OVERLAPPEDWINDOW|WS_VISIBLE,1300,600,400,300,NULL,NULL,hInstance,NULL);
    CreateWindow("STATIC",show.c_str(),WS_CHILD|WS_VISIBLE,0,50,400,50,MainWindowShow,NULL,hInstance,NULL);
    CreateWindow("BUTTON","放！学！辣！",WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,0,150,400,50,MainWindowShow,NULL,hInstance,NULL);//按钮
	UpdateWindow(MainWindowShow);//更新窗体
    MSG mainmsg;
	//消息循环
	while (GetMessage(&mainmsg, NULL, 0, 0)){//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
		TranslateMessage(&mainmsg);//翻译消息，如把WM_KEYDOWN和WM_KEYUP翻译成一个WM_CHAR消息
		DispatchMessage(&mainmsg);//派发消息
	}
    return 0;
}