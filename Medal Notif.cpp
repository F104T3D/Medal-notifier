#define PSAPI_VERSION 1
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <thread>
#include <chrono>
#include <cwchar>
#include <psapi.h>
#include <fstream>
#include <sstream>

std::wstring GetSteamGamePath() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return L"";

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
            if (hProcess) {
                wchar_t path[MAX_PATH];
                if (GetModuleFileNameExW(hProcess, NULL, path, MAX_PATH)) {
                    std::wstring exePath(path);

                    if (exePath.find(L"steamapps") != std::wstring::npos && exePath.find(L".exe") != std::wstring::npos) {

                        CloseHandle(hProcess);
                        CloseHandle(hSnap);
                        return exePath;
                    }
                }
                CloseHandle(hProcess);
            }
        } while (Process32Next(hSnap, &pe));
    }

    CloseHandle(hSnap);
    return L"";
}

bool IsProcessRunning(const std::wstring& processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
            std::string exeFile(pe.szExeFile);
            if (std::wstring(exeFile.begin(), exeFile.end()) == processName) {
                CloseHandle(hSnap);
                return true;
            }
        } while (Process32Next(hSnap, &pe));
    }

    CloseHandle(hSnap);
    return false;
}

void LaunchMedal() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);

    std::wstring exeDir(exePath);
    size_t lastSlash = exeDir.find_last_of(L"\\/");
    if (lastSlash != std::wstring::npos) {
        exeDir = exeDir.substr(0, lastSlash + 1);
    }

    std::wstring configPath = exeDir + L"medal_path.txt";

    std::wifstream file(configPath.c_str());
    if (!file.is_open()) {
        MessageBoxW(NULL, L"Could not open 'medal_path.txt'. Make sure it's in the same folder as this .exe.", L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();
    std::wstring medalPath = buffer.str();

    // Trim whitespace and newlines
    medalPath.erase(medalPath.find_last_not_of(L" \n\r\t") + 1);

    if (GetFileAttributesW(medalPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
        ShellExecuteW(NULL, L"open", medalPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    } else {
        MessageBoxW(NULL, (L"Invalid path in medal_path.txt:\n" + medalPath).c_str(), L"Error", MB_ICONERROR | MB_OK);
    }
}

void RestartSelf() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    ShellExecuteW(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);
    exit(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const std::wstring medalProcess = L"Medal.exe";

    while (true) {
        std::wstring gamePath = GetSteamGamePath();
        if (!gamePath.empty()) {
            if (!IsProcessRunning(medalProcess)) {
                LaunchMedal();
                //MessageBoxW(NULL, L"", L"", MB_ICONINFORMATION | MB_TOPMOST | MB_SYSTEMMODAL);
            }

            while (!GetSteamGamePath().empty()) {
                std::this_thread::sleep_for(std::chrono::seconds(60));
            }

            RestartSelf();
        }

        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
