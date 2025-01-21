// background_clock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

void timer(std::chrono::seconds time) {
    std::this_thread::sleep_for(time);
    wchar_t file_path[] = L"C:\\Users\\sabar\\source\\repos\\clock\\ringtone.wav";

    PlaySound(file_path, NULL, SND_FILENAME | SND_SYNC);

    FILE* file;
    if (fopen_s(&file, "output.txt", "a") == 0) {
        fprintf(file, "Timer closed \n");
        fclose(file);
    }
}

int main(int argc, char* argv[])
{

    std::stringstream ss(argv[1]);
    int seconds;

    if (!(ss >> seconds)) {
        std::cerr << "first argument must be the time in seconds";
        return -1;
    }
    

    std::chrono::seconds time(seconds);
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    timer(time);
}