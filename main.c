#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

int main() {
    const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(INVALID_HANDLE_VALUE == hSnapshot) {
        MessageBox(0, L"Error while getting processes", L"Err", 0);
        return 1;
    }
    HANDLE STD_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
    TCHAR szBuf[1024];
    DWORD dwTemp;
    PROCESSENTRY32 hProc;
    hProc.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &hProc);
    do {
        wsprintf(szBuf, "=== %08X %s ===\r\n",
             hProc.th32ProcessID, hProc.szExeFile); // в объекте hProc имеем всю информацию об процессе
        WriteConsole(STD_OUT, szBuf, lstrlen(szBuf), &dwTemp, NULL);
    } while (Process32Next(hSnapshot, &hProc)); // итерируем
    CloseHandle(hSnapshot);
    ExitProcess(0);
}

