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
"loginMethod": 2,
"selected": true
}],
"printStartupInfo": false
})";
		fout.close();
	}
}

void install_java(){
	//自动安装MSVC运行库
	system("powershell Start-BitsTransfer https://aka.ms/vs/17/release/vc_redist.x64.exe");
	system("vc_redist.x64.exe /install /quiet");
	system("del vc_redist.x64.exe");
	
	//自动安装JDK运行库
	
	if(!is_e(R"(C:\RMCL\jdki.msi)")){	
		
		system(R"(powershell Start-BitsTransfer -Source "https://aka.ms/download-jdk/microsoft-jdk-21.0.3-windows-x64.msi" -Destination "C:\RMCL\jdki.msi)");
	}
	
	system(R"(start C:\RMCL\jdki.msi /passive)"); 
	winapi::HWND test;
	int ti=time(0);
	while(1){
		if(time(0)-ti>=8){
			
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
	
	
	system(R"(del C:\RMCL\jdki.msi)");
	
}
void install_cmcl(){
	if(!is_e(R"(C:\RMCL\cmcl.exe)")){
		
		system(R"(powershell Start-BitsTransfer -Source "https://gitee.com/MrShiehX/console-minecraft-launcher/releases/download/2.2.1/cmcl.exe" -Destination "C:\RMCL\cmcl.exe)");	
	}
}
int tps=0;
bool ef=0;
void install_minecraft(){
	install_cmcl();
	//NBSMC 附加组件
	system(R"(powershell Start-BitsTransfer -Source "https://github.moeyy.cn/https://github.com/Github-liyifan202201/RMCL/raw/main/NBS_RMCL_add.zip" -Destination "C:\RMCL\NRA.zip")");
	tps=15;
	system(R"(powershell Expand-Archive -Path C:\RMCL\NRA.zip -DestinationPath C:\RMCL\)");
	system(R"(del C:\RMCL\NRA.zip)");
	tps=20;
	thread a([]{
		for(int i=0;i<70;i++){
			if(ef==1){
				break;
			}
			_sleep(9000);
			tps++;
		}
	});
	//Minecraft
	system(R"(cd C:\RMCL & echo y | cmcl install 1.20.1 --forge=47.3.5 --optifine=HD_U_I6)");
	tps=90;
	ef=1;
	for(int i=1;i<=2;i++){
		system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/ordsPcFz/versions/9j6YaPp2/kotlinforforge-4.10.0-all.jar");
		system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/qANg5Jrr/versions/bFG2YxbQ/e4mc-4.0.1%2B1.19.4-forge.jar");
		system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/RTWpcTBp/versions/70dnR0Rh/mcwifipnp-1.6.9-1.20.1-forge.jar");
		system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/3sjzyvGR/versions/NuEoZJJF/ModernUI-Forge-1.20.1-3.10.1.4-universal.jar");
	}
	tps=100;
	a.join();
	
}
void launch_minecraft(){
	ofstream fout;
	fout.open("c:\\RMCL\\la.bat");
	fout<<"cd /d C:\\RMCL & (echo yy | cmcl 1.20.1) & exit";
	fout.close();
	cout<<"Start Mc!";
//	winapi::WinExec("\"c:\\RMCL\\la.bat\"",SW_HIDE);
//	system("C:\\RMCL\\la.bat");
	
}

bool exitf=0;
int main() {
	st:;
	if(Get_HWND("Debug")==NULL)
		winapi::ShowWindow(winapi::GetConsoleWindow(),SW_HIDE);
	
	system("md c:\\RMCL");
	// 创建一个854*480的窗口
	InitWindow(854, 480, "RMCL");
	
	SetTargetFPS(60);
	
	// 创建一个文本
	const char* SM = "NBS";
	const char* RM = "RMCL D1.1.5";
	Vector2 STS = MeasureTextEx(GetFontDefault(), SM, 60, 1);
	Vector2 RTS = MeasureTextEx(GetFontDefault(), RM, 60, 1);
	Vector2 STP = {(float)(854 / 2 - STS.x / 2), (float)(480 / 2 - STS.y / 2)};
	Vector2 RTP = {(float)(854 / 2 - RTS.x / 2), (float)(480 / 2 - RTS.y / 2)};
	int PG = 0;
	
	launch_minecraft();
	// 启动动画
	while (PG <= 120) {
		
		if(WindowShouldClose()){
			system("taskkill /f /im consolepauser.exe");
			exit(0);
		}
		// 在这里绘制启动动画
		PG++;
		if (PG <= 60) {
			BeginDrawing();
			ClearBackground(RED);
			DrawText(SM, (int)STP.x, (int)STP.y, 60, WHITE);
			DrawText("RMCL Dev 1.1.5 By NBS", 570, 450, 20, RAYWHITE);
			EndDrawing();
			PG++;
			continue;
		} 
		
		
		// 显示RMCL文本和进度条1秒
		if (PG <= 120) {
			BeginDrawing();
			ClearBackground(RED);
			DrawText(RM, (int)RTP.x, (int)RTP.y, 60, WHITE);
			DrawText("RMCL Dev 1.1.5 By NBS", 570, 450, 20, RAYWHITE);
			EndDrawing();
			PG++;
			
			continue;
		}
		if(!is_e(R"(C:\RMCL\.minecraft\versions\1.20.1\1.20.1.jar)")){	
			// 结束启动动画
			break;
		}
		else{
			winapi::HWND mc=Get_HWND("Minecraft");
			while(mc==NULL){
				
				if(WindowShouldClose()){
					system("taskkill /f /im consolepauser.exe");
					exit(0);
				}
				mc=Get_HWND("Minecraft");
				BeginDrawing();
				EndDrawing();
			}
			break;
		}
		
	}
	/*
	自动更新
	system("curl curl -O https://github.moeyy.xyz/https://github.com/Github-liyifan202201/RMCL/releases/download/v1.2/RMCL.exe");
	ifstream fin;
	fin.open("RMCL.exe");
	string a;
	fin>>a;
	if(a!="Not"){
	cout<<"请更新版本";
	}
	*/
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
			DrawRectangle((int)inputBoxPosition.x, (int)inputBoxPosition.y, 400, 40, RAYWHITE);
			DrawText(name.c_str(), (int)inputBoxPosition.x + 10, (int)inputBoxPosition.y + 10, 20, BLACK);
			
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
	//下载Java
	SetTargetFPS(3);
	if(!is_e(R"(C:\Program Files\Microsoft\jdk-21.0.3.9-hotspot\bin\java.exe)")){
		exitf=0;
		thread a([]{
			install_java();
			system("java --version");
			
			exitf=1;
		});
		
		
		while(!exitf){
			if(WindowShouldClose()){
				system("taskkill /f /im consolepauser.exe");
				exit(0);
			}
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
				
				install_minecraft();
				
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
			string s="Installation Progress ("+to_string(tps)+"%)";
			DrawText(s.c_str(), 550, 450, 20, RAYWHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			
			DrawText("Install Minecraft..", 250, 200, 40, WHITE);
			s="Installation Progress ("+to_string(tps)+"%)";
			DrawText(s.c_str(), 550, 450, 20, RAYWHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			
			DrawText("Install Minecraft...", 250, 200, 40, WHITE);
			s="Installation Progress ("+to_string(tps)+"%)";
			DrawText(s.c_str(), 550, 450, 20, RAYWHITE);
			EndDrawing();
			
			BeginDrawing();
			ClearBackground(RED);
			DrawText("Install Minecraft", 250, 200, 40, WHITE);
			s="Installation Progress ("+to_string(tps)+"%)";
			DrawText(s.c_str(), 550, 450, 20, RAYWHITE);
			EndDrawing();
		}
		a.join();
		
	}
	goto st;
	
	system("taskkill /f /im consolepauser.exe");
	return 0;
}
