#include <iostream>
#include <thread>
#include <chrono>
#include <future>

int SystemThreads;
bool RunBenchmark = false;
bool ThreadExit = false;
int secondsWait = 10;
void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations);

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

	std::promise<int>* Threads = new std::promise<int>[SystemThreads];
	std::promise<int>* Threads2 = new std::promise<int>[SystemThreads];
	std::future<int> *calculations = new std::future<int> [SystemThreads];
	std::future<int> *primes = new std::future<int> [SystemThreads];
	for (int i = 0; i <= SystemThreads - 1; i++) {
		calculations[i] = Threads[i].get_future();
		primes[i] = Threads2[i].get_future();
	}

	std::thread *testThreads = new std::thread[SystemThreads] ;
	for (int i = 0; i <= SystemThreads - 1; i++) {
		testThreads[i] = std::thread(&calculatePrimeNumber, std::move(Threads2[i]), std::move(Threads[i]));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	RunBenchmark = true;
	std::this_thread::sleep_for(std::chrono::seconds(secondsWait));
	ThreadExit = true;
	testThreads[SystemThreads - 1].join();
	int totalCalcs = 0;
	int totalPrimes = 0;
	for (int i = 0; i <= SystemThreads - 1; i++) {
		totalCalcs = totalCalcs + calculations[i].get();
		totalPrimes = totalPrimes + primes[i].get();
	}
	std::cout << "Totoal Number of calculations on all Threads: " << totalCalcs << std::endl;
	std::cout << "Approximatley calculations per Thread:  " << totalCalcs / SystemThreads << std::endl;
	std::cout << "Totoal Number of Prime Numbers found on all Threads: " << totalPrimes << std::endl;
	std::cout << "Approximatley Number of Prime Numbers found per Thread: " << totalPrimes / SystemThreads << std::endl;
	return 0;
}

void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations) {
	do {} while (RunBenchmark == false);
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