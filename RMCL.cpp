
#include <bits/stdc++.h>
using namespace std;
#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "raygui.h"
namespace winapi {
	#include <windows.h>
	#undef DrawText
	#undef LoadImage
}

typedef enum { MAIN, ABOUT } Screen;
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
"downloadSource": 1,
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

int tps=0;
bool ef=0,show=0,fj=0,fm=0;
string sstr,sts="Start";
void install_java(){
	show=1;
	sstr="Install MSJDK,MSVC";
	
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
	show=0;
	
}
void install_mod(){
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/nmDcB62a/versions/m83ZRQdk/modernfix-forge-5.19.4%2Bmc1.20.1.jar");
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/RTWpcTBp/versions/70dnR0Rh/mcwifipnp-1.6.9-1.20.1-forge.jar");
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/ordsPcFz/versions/9j6YaPp2/kotlinforforge-4.10.0-all.jar");
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/3sjzyvGR/versions/NuEoZJJF/ModernUI-Forge-1.20.1-3.10.1.4-universal.jar");
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/uXXizFIs/versions/DG5Fn9Sz/ferritecore-6.0.1-forge.jar");
	system("cd /d C:\\RMCL && echo 2 | cmcl mod --url=https://cdn.modrinth.com/data/qANg5Jrr/versions/bFG2YxbQ/e4mc-4.0.1%2B1.19.4-forge.jar");
	
}
void install_cmcl(){
	if(!is_e(R"(C:\RMCL\cmcl.exe)")){
		
		system(R"(powershell Start-BitsTransfer -Source "https://gitee.com/MrShiehX/console-minecraft-launcher/releases/download/2.2.1/cmcl.exe" -Destination "C:\RMCL\cmcl.exe)");	
	}
}
void install_minecraft(){
	show=1;
	tps=0;
	ef=0;
	
	sstr="Install CMCL";
	install_cmcl();
	//NBSMC 附加组件
	
	sstr="Install MC 0 %";
	system(R"(powershell Start-BitsTransfer -Source "https://github.moeyy.xyz/https://github.com/Github-liyifan202201/RMCL/raw/main/NBS_RMCL_add.zip" -Destination "C:\RMCL\NRA.zip")");
	tps=15;
	sstr="Install MC 15 %";
	system(R"(powershell Expand-Archive -Path C:\RMCL\NRA.zip -DestinationPath C:\RMCL\)");
	system(R"(del C:\RMCL\NRA.zip)");
	tps=20;
	
	sstr="Install MC 20 %";
	thread a([]{
		for(int i=0;i<70;i++){
			if(ef==1){
				break;
			}
			_sleep(8000);
			tps++;
			sstr="Install MC "+to_string(tps)+" %";
		}
	});
	//Minecraft
	system(R"(cd C:\RMCL & echo y | cmcl install 1.20.1 --forge=47.3.7 --optifine=HD_U_I6)");
	
	sstr="Install MC 90 %";
	tps=90;
	ef=1;
	install_mod();
	sstr="Install MC 100 %";
	tps=100;
	show=0;
	a.join();
	
}
void DrawStatusBar() {
	if (show) {
		// 绘制半透明黑色背景
		DrawRectangle(590, 20, 220, 60, Fade(BLACK, 0.7f));
		
		DrawText(sstr.c_str(), 600, 25, 20, WHITE);		
		
		// 绘制加载条
		if (tps > 1 && tps < 99) {
			float progress = static_cast<float>(tps) / 100.0f;
			DrawRectangle(600, 50, static_cast<int>(200 * progress), 20, GREEN);
			DrawRectangleLines(600, 50, 200, 20, WHITE);  // 进度条边框
		}
	}
}
void HandleUsernameInput() {
	static char usernameBuffer[64] = "New name"; // 初始用户名
	if(!is_e("C:/RMCL/cmcl.json"))
		json("Steve");
	Rectangle inputBox = { 664, 350, 150, 40 }; // 调整输入框位置和大小
	
	// 设置输入框背景颜色和边框颜色
	Color backgroundColor = Fade(GRAY, 0.7f); // 半透明灰色背景
	Color borderColor = WHITE; // 白色边框
	Color textColor = BLACK; // 黑色文字
	
	// 绘制半透明背景
	DrawRectangleRec(inputBox, backgroundColor);
	
	// 绘制输入框边框
	DrawRectangleLinesEx(inputBox, 2, borderColor);
	
	// 绘制用户名输入框
	if (GuiTextBox(inputBox, usernameBuffer, sizeof(usernameBuffer), true)) {
		std::string newUsername = std::string(usernameBuffer);
		json(newUsername); // 替换为实际的 json 调用逻辑
	}
	
}



void launch_minecraft(){
	install_mod();
	ofstream fout;
	fout.open("C:\\RMCL\\la.bat");
	fout<<"cd /d C:\\RMCL & (echo yy | cmcl 1.20.1) & exit";
	fout.close();
	winapi::WinExec("\"c:\\RMCL\\la.bat\"",SW_HIDE);
//	system("C:\\RMCL\\la.bat");
	
}
int main() {
	InitWindow(854, 480, "RMCL");
	
	// 设置窗口图标
	Image icon = LoadImage("RI.png");
	SetWindowIcon(icon);
	UnloadImage(icon); // 使用后卸载图标
	
	Image bg = LoadImage("wp.png");
	Texture2D t = LoadTextureFromImage(bg);
	UnloadImage(bg);
	
	Image hi = LoadImage("home.png");
	Texture2D ht = LoadTextureFromImage(hi);
	UnloadImage(hi);
	
	Image ai = LoadImage("about.png");
	Texture2D at = LoadTextureFromImage(ai);
	UnloadImage(ai);
	
	float w = GetScreenWidth(), h = GetScreenHeight();
	Rectangle sr = {0, 0, (float)t.width, (float)t.height}, dr = {0, 0, w, h};
	Vector2 o = {0, 0};
	float iw = 30.0f, ih = 30.0f;
	float cx = (50 - iw) / 2.0f;
	Rectangle hs = {0, 0, (float)ht.width, (float)ht.height};
	Rectangle hd = {cx, 30, iw, ih};
	Rectangle as = {0, 0, (float)at.width, (float)at.height};
	Rectangle ad = {cx, 70, iw, ih};
	
	Screen currentScreen = MAIN;
	
	while (!WindowShouldClose()) {
		Vector2 mp = GetMousePosition();
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexturePro(t, sr, dr, o, 0, WHITE);
		DrawRectangle(0, 0, 50, h, Color{0, 0, 0, 200});
		DrawTexturePro(ht, hs, hd, o, 0, WHITE);
		DrawTexturePro(at, as, ad, o, 0, WHITE);
		DrawText("RMCL", 5, 5, 18, WHITE); 
		DrawStatusBar();
		HandleUsernameInput();
		if (currentScreen == MAIN) {
			bool hvr = CheckCollisionPointRec(mp, ad);
			if (hvr && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = ABOUT;
			}
			
			// 使用 raygui 绘制按钮
			GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
			if (GuiButton((Rectangle){w - 190, h - 80, 150, 40}, sts.c_str()) and sts=="Start") {
				sts="Pending";
				fj=1;
				if(!is_e(R"(C:\Program Files\Microsoft\jdk-21.0.3.9-hotspot\bin\java.exe)")){
					fj=0;
					ef=0;
					thread a([]{
						install_java();
						ef=1;
						fj=1;
					});			
					a.detach();
				}
				fm=1;
				if (!is_e(R"(C:\RMCL\.minecraft\versions\1.20.1\1.20.1.jar)")) {
					system(R"(rmdir /Q /S C:\RMCL\.minecraft\)");
					fm=0;
					while(fj==0);
					ef=0;
					thread a([]{
						install_minecraft();
						ef=1;
						fm=1;
					});
					a.detach();
				}
				thread st([]{
					while(fm==0){
//						cout<<fm<<endl;
						_sleep(10);
					}
					launch_minecraft();
				});
				
				st.detach();
			}
		} 
		else if (currentScreen == ABOUT) {
			if (CheckCollisionPointRec(mp, hd) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = MAIN;
			}
			
			// 半透明的 About 界面
			DrawRectangle(50, 0, w - 50, h, Fade(BLACK, 0.7f));
			DrawText("About", 60, 20, 40, WHITE);
			DrawText("RMCL v2", 60, 80, 50, WHITE);
			DrawText("By NBS (New Block Studio)", 60, 150, 20, LIGHTGRAY);
			DrawText("Thanks", 500, 20, 30, WHITE);
			
			int yOffset = 60;
			const int lineSpacing = 30;
			DrawText("- CMCL", 500, yOffset, 20, RAYWHITE);
			DrawText("Give me RMCL the kernel of the initiator.", 500, yOffset + lineSpacing, 15, LIGHTGRAY);
			
			yOffset += 2 * lineSpacing;
			DrawText("- Raylib", 500, yOffset, 20, RAYWHITE);
			DrawText("Give me RMCL the beautiful UI.", 500, yOffset + lineSpacing, 15, LIGHTGRAY);
			
			yOffset += 2 * lineSpacing;
			DrawText("- Some OIers", 500, yOffset, 20, RAYWHITE);
			DrawText("Make me RMCL Better.", 500, yOffset + lineSpacing, 15, LIGHTGRAY);
			
			yOffset += 2 * lineSpacing;
			DrawText("liyifan202201", 500, yOffset + lineSpacing, 20, ORANGE);
			DrawText("GCSG01", 500, yOffset + 2 * lineSpacing, 20, RED);
			DrawText("xzq4121", 500, yOffset + 3 * lineSpacing, 20, GREEN);
			DrawText("shixuanzhe_ha", 500, yOffset + 4 * lineSpacing, 20, RED);
			DrawText("kind_aunt", 500, yOffset + 5 * lineSpacing, 20, ORANGE);
		}
		
		EndDrawing();
	}
	
	UnloadTexture(t);
	UnloadTexture(ht);
	UnloadTexture(at);
	CloseWindow();
	return 0;
}

