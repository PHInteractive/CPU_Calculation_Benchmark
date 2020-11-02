#include <iostream>
#include <thread>
#include <chrono>
#include <future>

int SystemThreads;
bool BenchmarkRun = false;
bool ThreadExit = false;
int secondsWait = 10;
void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations);
void RunBenchmark(int NumberofThreads);

int WinMain() {
	if (std::thread::hardware_concurrency() == 0) {
		std::cout << "cannot detect number of threads of this System" << std::endl;
		std::cout << "Using 8 Threads for testing" << std::endl;
		SystemThreads = 8;
	}
	else {
		std::cout << "detectet " << std::thread::hardware_concurrency() << " System Threads for benchmarking" << std::endl << std::endl << std::endl;
		SystemThreads = std::thread::hardware_concurrency();
	}
	RunBenchmark(1);
	if (SystemThreads >= 2) {
		if (SystemThreads == 2) {
			RunBenchmark(2);
		}
		else if (SystemThreads > 2) {
			RunBenchmark(2);
			RunBenchmark(SystemThreads);
		}
	}
	std::cout << "All Benchmarks are done" << std::endl;
	return 0;
}

void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations) {
	do {} while (BenchmarkRun == false);
	int currentcalculations = 0;
	int foundPrimeNumbers = 0;
	int count = 0;
	int currentIteration;
	int currentNumber = 0;
	do {
		for (currentIteration = 2; currentIteration <= currentNumber / 2; currentIteration++) {
			if (currentNumber % currentIteration == 0) {
				currentcalculations++;
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
	primeNumbers.set_value(foundPrimeNumbers);
	calculations.set_value(currentcalculations);
}

void RunBenchmark(int NumberofThreads) {
	std::promise<int>* PromisCalculations = new std::promise<int>[NumberofThreads];
	std::promise<int>* PromisePrimeNumbers = new std::promise<int>[NumberofThreads];
	std::future<int>* calculations = new std::future<int>[NumberofThreads];
	std::future<int>* CalculatetPrimeNumbers = new std::future<int>[NumberofThreads];
	for (int i = 0; i <= NumberofThreads - 1; i++) {
		calculations[i] = PromisCalculations[i].get_future();
		CalculatetPrimeNumbers[i] = PromisePrimeNumbers[i].get_future();
	}

	std::thread* testThreads = new std::thread[NumberofThreads];
	for (int i = 0; i <= NumberofThreads - 1; i++) {
		testThreads[i] = std::thread(&calculatePrimeNumber, std::move(PromisePrimeNumbers[i]), std::move(PromisCalculations[i]));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	BenchmarkRun = true;
	std::this_thread::sleep_for(std::chrono::seconds(secondsWait));
	ThreadExit = true;
	testThreads[NumberofThreads - 1].join();
	int totalCalculations = 0;
	int totalPrimeNumbersFound = 0;
	for (int i = 0; i <= NumberofThreads - 1; i++) {
		totalCalculations = totalCalculations + calculations[i].get();
		totalPrimeNumbersFound = totalPrimeNumbersFound + CalculatetPrimeNumbers[i].get();
	}
	std::cout << "_______________________________________________________________________________________________________________________" << std::endl;
	std::cout << NumberofThreads << " Thread Benchmark completet" << std::endl;
	std::cout << "Totoal Number of calculations on all Threads: " << totalCalculations << std::endl;
	if (NumberofThreads != 1) {
		std::cout << "Approximatley calculations per Thread:  " << totalCalculations / NumberofThreads << std::endl;
	}
	std::cout << "Totoal Number of Prime Numbers found on all Threads: " << totalPrimeNumbersFound << std::endl;
	if (NumberofThreads != 1) {
		std::cout << "Approximatley Prime Numbers found per Thread: " << totalPrimeNumbersFound / NumberofThreads << std::endl;

	}
	std::cout << "_______________________________________________________________________________________________________________________" << std::endl << std::endl;
	BenchmarkRun = false;
	ThreadExit = false;
}