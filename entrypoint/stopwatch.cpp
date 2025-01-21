#include <iostream>
#include <chrono>
#include <sstream>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#endif

void stopwatch() {
	bool running = false;
	auto startTime = std::chrono::high_resolution_clock::now();
	auto stopTime = std::chrono::high_resolution_clock::now();

	std::cout << "press 's' to start/stop, 'r' to reset, 'q' to quit" << std::endl;

	while (true) {
		if (true) {
			char c = _getch();
			if (c == 's') {
				if (running) {
					stopTime = std::chrono::high_resolution_clock::now();
					running = false;
					std::cout << "stopped stopwatch" << std::endl;

					// calculating the time difference
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

					// formatting and printing the output
					auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
					auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
					auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
					auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
					std::cout << "elapsed time: " << hours.count() << " : " << minutes.count() << " : " << seconds.count() << "." << milliseconds.count() << std::endl;

				}
				else {
					startTime = std::chrono::high_resolution_clock::now();
					running = true;
					std::cout << "started stopwatch" << std::endl;
				}
			}
			else if (c == 'r') {
				startTime = std::chrono::high_resolution_clock::now();
				stopTime = std::chrono::high_resolution_clock::now();
				running = false;
			}
			else if (c == 'q') {
				std::cout << "quitting stopwatch\n" << std::endl;
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return;
}