#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include "getopt.h"

void stopwatch();

int main(int argc, char* argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    std::wstring executable_path = L"C:\\Users\\sabar\\source\\repos\\clock\\x64\\Debug\\background_clock.exe";

    int optidx;
    char c;

    std::string mode;
    std::string time;

    while ((c = getopt(argc, argv, "hm:t:")) != -1) {
        switch (c) {
        case 'h':
            std::cout << "Usage: entrypoint -m [ stopwatch | timer | alarm ] -t [<seconds> | <time>]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -m <mode>    Specify the mode of the clock. Available modes are:" << std::endl;
            std::cout << "               stopwatch - Starts a stopwatch." << std::endl;
            std::cout << "               timer     - Starts a timer. Requires -t <seconds> argument." << std::endl;
            std::cout << "               alarm     - Sets an alarm. Requires -t <time> argument in HH:MM format." << std::endl;
            std::cout << "  -t <time>    Specify the time for the timer or alarm." << std::endl;
            std::cout << "               For timer, provide the time in seconds." << std::endl;
            std::cout << "               For alarm, provide the time in HH:MM format." << std::endl;
            return 0;
        case 'm':
            mode = optarg;
            break;
        case 't':
            time = optarg;
            break;
        default:
            std::cerr << "Unknown option: " << c << std::endl;
            return 1;
        }
    }

    if (mode.empty()) {
        std::cerr << "Mode is required. Use -h for help." << std::endl;
        return 1;
    }

    if ((mode == "timer" || mode == "alarm") && time.empty()) {
        std::cerr << "Time is required for mode " << mode << ". Use -h for help." << std::endl;
        return 1;
    }

    // handling each mode
    if (mode == "stopwatch") {
        stopwatch();
    } else if (mode == "timer") {
		executable_path += L" " + std::wstring(time.begin(), time.end());

        std::cout << "Timer Set!\n";
    }
	else if (mode == "alarm") {
        // convert the HH:MM string to actual time
		int hours, minutes;
        if (sscanf_s(time.c_str(), "%d:%d", &hours, &minutes) != 2) {
            std::cerr << "Invalid time format. Use HH:MM format." << std::endl;
            return 1;
        }

		// convert the hours nd minutes to chrono time of this day
	    
		auto now = std::chrono::system_clock::now();
		auto now_c = std::chrono::system_clock::to_time_t(now);
		tm tm_now;
		localtime_s(&tm_now, &now_c);

		tm alarm_time = tm_now;
		alarm_time.tm_hour = hours;
		alarm_time.tm_min = minutes;

		alarm_time.tm_sec = 0;

		auto alarm_time_t = std::chrono::system_clock::from_time_t(mktime(&alarm_time));
		auto duration = alarm_time_t - now;

		if (duration.count() < 0) {
			std::cerr << "Invalid time. Alarm time should be in the future." << std::endl;
			return 1;
		}

		// convert the duration to seconds
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

		executable_path += L" " + std::to_wstring(seconds);
		std::cout << "Alarm Set!\n";
    }
	else {
		std::cerr << "Unknown mode: " << mode << std::endl;
		return 1;
	}

    if (mode == "alarm" || mode == "timer") {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(
            NULL,
            &executable_path[0],
            NULL,
            NULL,
            FALSE,
            DETACHED_PROCESS,
            NULL,
            NULL,
            &si,
            &pi
        )) {
            std::cerr << "Could not create a background process (" << GetLastError() << "). \n";
        }

        // Close process and thread handles. 
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::cout << "Closing the parent process\n";
    }

    return 0;
}
