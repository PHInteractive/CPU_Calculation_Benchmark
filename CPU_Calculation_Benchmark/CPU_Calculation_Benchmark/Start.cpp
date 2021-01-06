#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <string>

//variable declaration
const char* localVersion = "0.0.1";
int SystemThreads = 0;
int secondsWait = 0;
bool BenchmarkRun = false;
bool ThreadExit = false;
//function declaration
void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations);
void RunBenchmark(int NumberofThreads);

int main(int argc, char *argv[]) {
	if (argc > 1) {
		//loop though all arguments (expect argument 0) passed to the application
		for (int currentArgument = 1; currentArgument <= argc - 1; currentArgument++) {
			if (strcmp(argv[currentArgument], "-v") == 0 or strcmp(argv[currentArgument], "-version") == 0) {
				std::cout << "CPU Calculation Benchmark" << std::endl;
				std::cout << "Version: " << localVersion << std::endl;
				return 0;
			}
			else if (strcmp(argv[currentArgument], "-h") == 0 or strcmp(argv[currentArgument], "-help") == 0) {
				std::cout << "CPU Calculation Benchmark Help" << std::endl;
				std::cout << "-h  -help			shows this Help Page" << std::endl;
				std::cout << "-v  -version			displays the current Version of the Program" << std::endl;
				std::cout << "-t  -threads [number]		this sets the number of threads used in the Benchamrk." << std::endl;
				std::cout << "-a  -UseAllThreads		this uses all threads that are usable for the Benchmark." << std::endl;
				std::cout << "-d  -duration [number]		this sets the time in seconds the Benchmark(s) is/are running." << std::endl;
				return 0;
			}
			else if (strcmp(argv[currentArgument], "-t") == 0 or strcmp(argv[currentArgument], "-threads") == 0) {
				std::string SpecifiedNumberOfThreads = "0";
				if (SystemThreads == 0) {
					if (currentArgument + 1 <= argc - 1) {
						SpecifiedNumberOfThreads = argv[currentArgument + 1];
					}
					else {
						std::cout << "No Value for the Argument specified!" << std::endl;
						return 1;
					}
					if (SpecifiedNumberOfThreads.find_first_not_of("0123456789") != std::string::npos) {
						std::cout << "Value is not a number" << std::endl;
						return 1;
					}
					else {
						std::cout << "Using " << argv[currentArgument + 1] << " Threads" << std::endl;
						if (std::stoi(SpecifiedNumberOfThreads) <= 0) {
							std::cout << "Minimum number of Threads is 1!" << std::endl;
							return 1;
						}
						else {
							SystemThreads = std::stoi(SpecifiedNumberOfThreads);
							currentArgument++;
						}
					}
				}
				else {
					std::cout << "Already set Threads for Benchmarking!" << std::endl;
					return 1;
				}
			} 
			else if (strcmp(argv[currentArgument], "-a") == 0 or strcmp(argv[currentArgument], "-UseAllThreads") == 0) {
				std::string SpecifiedNumberOfThreads = "0";
				if (SystemThreads == 0) {
					if (std::thread::hardware_concurrency() == 0) {
						std::cout << "Funtion to detect logical Cores failed, please set Thread-Count with -t or -threads" << std::endl;
						return 1;
					}
					else {
						SystemThreads = std::thread::hardware_concurrency();
					}
				}
				else {
					std::cout << "Already set Threads for Benchmarking!" << std::endl;
					return 1;
				}
			}
			else if (strcmp(argv[currentArgument], "-d") == 0 or strcmp(argv[currentArgument], "-duration") == 0) {
				std::string SpecifiedNumberOfSeconds = "0";
				if (secondsWait == 0) {
					if (currentArgument + 1 <= argc - 1) {
						SpecifiedNumberOfSeconds = argv[currentArgument + 1];
					}
					else {
						std::cout << "No Value for the Argument specified!" << std::endl;
						return 1;
					}
					if (SpecifiedNumberOfSeconds.find_first_not_of("0123456789") != std::string::npos) {
						std::cout << "Value is not a number" << std::endl;
						return 1;
					}
					else {
						std::cout << "Running " << argv[currentArgument + 1] << " seconds per Test" << std::endl;
						if (std::stoi(SpecifiedNumberOfSeconds) <= 0) {
							std::cout << "Minimum number of duration in seconds is 1!" << std::endl;
							return 1;
						}
						else {
							secondsWait = std::stoi(SpecifiedNumberOfSeconds);
							currentArgument++;
						}
					}
				}
				else {
					std::cout << "Already set Duration for Benchmarking!" << std::endl;
					return 1;
				}
			}
			else {
				std::cout << "ERROR !" << std::endl;
				std::cout << "Argument " << currentArgument << " (\"" << argv[currentArgument] << "\") is invalid." << std::endl;
				return 1;
			}
		}
	}
	//setup secondsWait (the time the Benchmark is activly running) for Benchmarking when none is specified through launch parameters
	if (secondsWait == 0) {
		secondsWait = 10;
	}
	//setup systemThreads for Benchmarking when none are specified through launch parameters
	if (SystemThreads == 0) {
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
	}
	//run Benchmark with specified Thread-Count when launched with -t/-threads
	else {
		RunBenchmark(SystemThreads);
	}
	return 0;
}

void calculatePrimeNumber(std::promise<int>&& primeNumbers, std::promise<int>&& calculations) {
	do {} while (BenchmarkRun == false);	//used to stop function from continuing before all threads are created
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
	//dynamicly create variables to store results in
	for (int i = 0; i <= NumberofThreads - 1; i++) {
		calculations[i] = PromisCalculations[i].get_future();
		CalculatetPrimeNumbers[i] = PromisePrimeNumbers[i].get_future();
	}
	//dynamicly create and spawn threads
	std::thread* testThreads = new std::thread[NumberofThreads];
	for (int i = 0; i <= NumberofThreads - 1; i++) {
		testThreads[i] = std::thread(&calculatePrimeNumber, std::move(PromisePrimeNumbers[i]), std::move(PromisCalculations[i]));
	}
	//wait a short time to make sure, all threads are created and running
	std::this_thread::sleep_for(std::chrono::seconds(1));
	BenchmarkRun = true;
	std::this_thread::sleep_for(std::chrono::seconds(secondsWait));
	//Exit function in the created threads
	ThreadExit = true;
	//Wait until all threads are finfished
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
	//Prepare Variables for potential next Benchmark run
	BenchmarkRun = false;
	ThreadExit = false;
}