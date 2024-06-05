

#include <bits/stdc++.h>
#include "raylib.h"

namespace winapi {
#include <windows.h>
#undef DrawText
}


using namespace std;

//此函数由 GPT 3.5 生成
wstring targetTitle;
winapi::BOOL CALLBACK EnumWindowsProc(winapi::HWND hwnd, winapi::LPARAM lParam) {
	winapi::HWND* pFoundWindow = reinterpret_cast<winapi::HWND*>(lParam);
	
	const int titleLength = GetWindowTextLengthW(hwnd);
	if (titleLength == 0) {
		return TRUE;
	}
	
	vector<wchar_t> titleBuffer(titleLength + 1);
	GetWindowTextW(hwnd, titleBuffer.data(), titleLength + 1);
	
	if (wcsstr(titleBuffer.data(), targetTitle.c_str()) != NULL) {
		*pFoundWindow = hwnd;
		return FALSE;
	}
	
	return TRUE;
}
//此函数由 Web 搜索
wstring StringToWString(const string &str){
	wstring wstr(str.length(),L' ');
	copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}
winapi::HWND Get_HWND(string a){
	targetTitle=StringToWString(a);
	winapi::HWND foundWindow = NULL;
	EnumWindows(EnumWindowsProc, reinterpret_cast<winapi::LPARAM>(&foundWindow));
	return foundWindow;
}

bool is_e(const string& name) {
	FILE* file = fopen(name.c_str(), "r");
	if (file) {
		fclose(file);
		return true;
	} else {
		return false;
	}
}

void json(string a) {
	fstream fout;
	fout.open("C:/RMCL/cmcl.json", ios::out);
	if (fout.is_open()) {
		fout << R"({
	"exitWithMinecraft": false,
	"javaPath": "C:\\Program Files\\Microsoft\\jdk-21.0.3.9-hotspot\\bin\\java.exe",
	"windowSizeWidth": 854,
	"windowSizeHeight": 480,
	"language": "zh",
	"downloadSource": 0,
	"checkAccountBeforeStart": false,
	"accounts": [{
		"playerName": ")" << a << R"(",
		"loginMethod": 0,
		"selected": true
	}],
	"printStartupInfo": false
})";
		fout.close();
	}
}
void out(string s){
	for(auto i:s){
		cout<<i;
		_sleep(50);
	}
}
void install_java(){
	if(!is_e(R"(C:\RMCL\jdki.msi)")){	
		out("正在下载java...\n");
		system(R"(powershell Start-BitsTransfer -Source "https://aka.ms/download-jdk/microsoft-jdk-21.0.3-windows-x64.msi" -Destination "C:\RMCL\jdki.msi)");
	}
	out("正在安装java...\n");
	system(R"(start C:\RMCL\jdki.msi /passive)"); 
	winapi::HWND test;
	int ti=time(0);
	while(1){
		if(time(0)-ti>=8){
			out("请确定你的电脑是否支持Powershell\n安装失败\n");
			exit(0);
		}
		test=Get_HWND("JDK"); 
		if(test!=NULL){
			ShowWindow(test, SW_HIDE); 
			break;
		}
		test=Get_HWND("Windows Installer"); 
		if(test!=NULL){
			ShowWindow(test, SW_HIDE); 
			break;
		}
	}
	while(!is_e(R"(C:\Program Files\Microsoft\jdk-21.0.3.9-hotspot\bin\java.exe)"))
		_sleep(10);
	_sleep(1000);
	out("Jre 21 安装完成\n");
	
	system(R"(del C:\RMCL\jdki.msi)");
	
}
void install_cmcl(){
	if(!is_e(R"(C:\RMCL\cmcl.exe)")){
		out("正在安装CMCL内核\n");
		system(R"(powershell Start-BitsTransfer -Source "https://gitee.com/MrShiehX/console-minecraft-launcher/releases/download/2.2.1/cmcl.exe" -Destination "C:\RMCL\cmcl.exe)");	
	}
}
void install_minecraft(){
	install_cmcl();
	//NBSMC 附加组件
	system(R"(powershell Start-BitsTransfer -Source "https://gitee.com/lyf202201/image/raw/main/a.zip" -Destination "C:\RMCL\fk.zip")");
	cout<<endl;
	system(R"(powershell Expand-Archive -Path C:\RMCL\fk.zip -DestinationPath C:\RMCL\)");
	system(R"(del C:\RMCL\fk.zip)");
	//Minecraft
	system(R"(cd C:\RMCL & cmcl install 1.20.1 --forge=47.2.0 --optifine=HD_U_I6)");
	system("cd /d C:\\RMCL && cmcl mod --url=https://cdn.modrinth.com/data/ordsPcFz/versions/9j6YaPp2/kotlinforforge-4.10.0-all.jar");
	system("cd /d C:\\RMCL && cmcl mod --url=https://cdn.modrinth.com/data/qANg5Jrr/versions/bFG2YxbQ/e4mc-4.0.1%2B1.19.4-forge.jar");
	system("cd /d C:\\RMCL && cmcl mod --url=https://cdn.modrinth.com/data/RTWpcTBp/versions/70dnR0Rh/mcwifipnp-1.6.9-1.20.1-forge.jar");
	
}
void launch_minecraft(){
	system(R"(cd C:\\RMCL & cmcl 1.20.1)");
}

bool exitf=0;
int main() {
	
	winapi::ShowWindow(winapi::GetConsoleWindow(),SW_MINIMIZE);
	system("md c:\\RMCL");
	// 创建一个854*480的窗口
	InitWindow(854, 480, "RMCL");
	
	SetTargetFPS(60);
	
	// 创建一个文本
	const char* studioMessage = "NBS";
	const char* rmclMessage = "RMCL";
	Vector2 studioTextSize = MeasureTextEx(GetFontDefault(), studioMessage, 60, 1);
	Vector2 rmclTextSize = MeasureTextEx(GetFontDefault(), rmclMessage, 60, 1);
	Vector2 studioTextPosition = {(float)(854 / 2 - studioTextSize.x / 2), (float)(480 / 2 - studioTextSize.y / 2)};
	Vector2 rmclTextPosition = {(float)(854 / 2 - rmclTextSize.x / 2), (float)(480 / 2 - rmclTextSize.y / 2)};
	Rectangle progressBar = {(float)(854 / 4), (float)(480 / 2 + 50), (float)(854 / 2), 20};
	int progress = 0;
	int maxProgress = 160;
	
	
	// 启动动画
	while (progress <= maxProgress) {
		
		if(WindowShouldClose()){
			system("taskkill /f /im consolepauser.exe");
			exit(0);
		}
		// 在这里绘制启动动画
		progress++;
		if (progress <= 60) {
			BeginDrawing();
			ClearBackground(RED);
			DrawText(studioMessage, (int)studioTextPosition.x, (int)studioTextPosition.y, 60, WHITE);
			EndDrawing();
			progress++;
			continue;
		}
		
		
		// 显示RMCL文本和进度条1秒
		if (progress <= 160) {
			BeginDrawing();
			ClearBackground(RED);
			DrawText(rmclMessage, (int)rmclTextPosition.x, (int)rmclTextPosition.y, 60, WHITE);
			DrawRectangle((int)progressBar.x, (int)progressBar.y, (int)(progressBar.width * ((float)progress - 60) / 100), (int)progressBar.height, WHITE);
			EndDrawing();
			progress++;
			continue;
		}
		
		// 结束启动动画
		break;
	}
	
	// 检查文件是否存在
	if (!is_e("C:/RMCL/cmcl.json")) {
		// 如果文件不存在，则创建一个居中的输入框
		string name;
		Vector2 inputBoxPosition = {(float)(854 / 2 - 200), (float)(480 / 2 - 50)};
		Vector2 checkmarkPosition = {(float)(854 / 2 + 170), (float)(480 / 2 - 50)};
		const char* inputPrompt = "Please input your name:";
		
		// 主循环
		while (1) {
			if(WindowShouldClose()){
				system("taskkill /f /im consolepauser.exe");
				exit(0);
			}
			// 显示输入提示和输入框
			BeginDrawing();
			ClearBackground(RED);
			DrawText(inputPrompt, (int)inputBoxPosition.x, (int)inputBoxPosition.y - 30, 20, WHITE);
			DrawRectangle((int)inputBoxPosition.x, (int)inputBoxPosition.y, 400, 40, LIGHTGRAY);
			DrawText(name.c_str(), (int)inputBoxPosition.x + 10, (int)inputBoxPosition.y + 10, 20, WHITE);
			
			// 绘制勾
			DrawText("OK", (int)checkmarkPosition.x - 14, (int)checkmarkPosition.y + 5, 30, GREEN);
			EndDrawing();
			
			// 获取鼠标状态
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				Vector2 mousePosition = GetMousePosition();
				// 如果点击了 "OK" 按钮
				if (CheckCollisionPointRec(mousePosition, { checkmarkPosition.x - 14, checkmarkPosition.y + 5, 30, 30 })) {
					// 输入结束，退出循环
					cout<<"OK!";
					json(name);
					if(name!="")
						break;
				}
			}
			// 获取键盘字符并添加到名称中
			int key = GetKeyPressed();
			if ((key >= 32) && (key <= 125)) {
				name += static_cast<char>(key);
			} else if (IsKeyPressed(KEY_BACKSPACE) && name.length() > 0) {
				// 如果按下了删除键且名称不为空，则删除最后一个字符
				if(name.size())
					name.pop_back();
			}
		}
	}
	
	SetTargetFPS(3);
	if(!is_e(R"(C:\Program Files\Microsoft\jdk-21.0.3.9-hotspot\bin\java.exe)")){
		exitf=0;
		thread a([]{
			install_java();
			system("java --version");
			out("OK\n");
			exitf=1;
		});
		
		if(WindowShouldClose()){
			system("taskkill /f /im consolepauser.exe");
			exit(0);
		}
		while(!exitf){
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install MS-JDK-21.", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install MS-JDK-21..", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install MS-JDK-21...", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install MS-JDK-21", 250, 200, 40, WHITE);
			EndDrawing();
		}
		
		a.join();
	}
	if (!is_e(R"(C:\RMCL\.minecraft\versions\1.20.1\1.20.1.jar)")) {
		exitf=0;
		thread a([]{
			cout<<"Install Minecraft...";
			if(!is_e(R"(C:\RMCL\.minecraft\versions\1.20.1\1.20.1.jar)")){
				out("正在安装Minecraft 1.20.1 (NBS MC 3.0)\n---\n");
				install_minecraft();
				out("OK\n");
			}
			exitf=1;
		});
		while(!exitf){
			
			if(WindowShouldClose()){
				system("taskkill /f /im consolepauser.exe");
				exit(0);
			}
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install Minecraft.", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install Minecraft..", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install Minecraft...", 250, 200, 40, WHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install Minecraft", 250, 200, 40, WHITE);
			EndDrawing();
		}
		a.join();
		
	}
	launch_minecraft();
	while (Get_HWND("Minecraft")==NULL) {
		
		if(WindowShouldClose()){
			system("taskkill /f /im consolepauser.exe");
			exit(0);
		}
		BeginDrawing();
		ClearBackground(RED);
		DrawText("NBS - Minecraft", 250, 200, 40, WHITE);
		EndDrawing();
	}
	CloseWindow();
	system("taskkill /f /im consolepauser.exe");
	return 0;
}
