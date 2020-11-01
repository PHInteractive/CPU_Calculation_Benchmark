#include <iostream>
#include <thread>
#include <chrono>
#include <future>

int SystemThreads;
bool RunBenchmark = false;
bool ThreadExit = false;
int secondsWait = 10;
void calculatePrimeNumber(std::promise<int>&& p);

void testfunc() {
	std::cout << std::this_thread::get_id() << std::endl;
}

int main() {
	if (std::thread::hardware_concurrency() == 0) {
		std::cout << "cannot detect number of threads of this System" << std::endl;
		std::cout << "Using 8 Threads for testing" << std::endl;
		SystemThreads = 8;
	}
	else {
		std::cout << "detectet " << std::thread::hardware_concurrency() << " System Threads for benchmarking" << std::endl;
		SystemThreads = std::thread::hardware_concurrency();
	}

	std::thread *testThreads = new std::thread[SystemThreads*2] ;
	for (int i = 0; i <= SystemThreads - 1; i++) {
		testThreads[i] = std::thread(testfunc);
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
}

void calculatePrimeNumber(std::promise<int> && p) {
	do {} while (RunBenchmark == false);
	int foundPrimeNumbers = 0;
	int count = 0;
	int currentIteration;
	int currentNumber = 0;
	do {
		for (currentIteration = 2; currentIteration <= currentNumber / 2; currentIteration++) {
			if (currentNumber % currentIteration == 0) {
				count++;
				break;
			}
		}
		if (count == 0 and currentNumber != 1 and currentNumber != 0) {
			foundPrimeNumbers++;
		}
		currentNumber++;
		count = 0;
	} while (ThreadExit == false);
	p.set_value(foundPrimeNumbers);
}