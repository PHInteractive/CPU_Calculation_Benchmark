#include <iostream>
#include <thread>
#include <chrono>
#include <future>

bool ThreadExit = false;

void calculatePrimeNumber(std::promise<int>&& p);


int main() {
	//1 Thread Tets
	std::promise<int> Thread1FutureTest1;
	auto Thread1IntTest1 = Thread1FutureTest1.get_future();
	std::thread Thread1Test1(&calculatePrimeNumber, std::move(Thread1FutureTest1));
	std::this_thread::sleep_for(std::chrono::seconds(10));
	ThreadExit = true;
	Thread1Test1.join();

	std::cout << "_____________________________1 Thread_____________________________" << std::endl << std::endl;
	std::cout << "Prime Numbers found in Thread 1: " << Thread1IntTest1.get() << std::endl;
	std::cout << "__________________________________________________________________" << std::endl << std::endl;

	//2 Thread Test
	ThreadExit = false;
	std::promise<int> Thread1FutureTest2;
	std::promise<int> Thread2FutureTest2;
	auto Thread1IntTest2 = Thread1FutureTest2.get_future();
	auto Thread2IntTest2 = Thread2FutureTest2.get_future();
	std::thread Thread1Test2(&calculatePrimeNumber, std::move(Thread1FutureTest2));
	std::thread Thread2Test2(&calculatePrimeNumber, std::move(Thread2FutureTest2));
	std::this_thread::sleep_for(std::chrono::seconds(10));
	ThreadExit = true;
	Thread1Test2.join();
	Thread2Test2.join();

	std::cout << "_____________________________2 Thread_____________________________" << std::endl << std::endl;
	std::cout << "Prime Numbers found in Thread 1: " << Thread1IntTest2.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 2: " << Thread2IntTest2.get() << std::endl;
	std::cout << "__________________________________________________________________" << std::endl << std::endl;

	//4 Thread Test
	ThreadExit = false;
	std::promise<int> Thread1FutureTest4;
	std::promise<int> Thread2FutureTest4;
	std::promise<int> Thread3FutureTest4;
	std::promise<int> Thread4FutureTest4;
	auto Thread1IntTest4 = Thread1FutureTest4.get_future();
	auto Thread2IntTest4 = Thread2FutureTest4.get_future();
	auto Thread3IntTest4 = Thread3FutureTest4.get_future();
	auto Thread4IntTest4 = Thread4FutureTest4.get_future();
	std::thread Thread1Test4(&calculatePrimeNumber, std::move(Thread1FutureTest4));
	std::thread Thread2Test4(&calculatePrimeNumber, std::move(Thread2FutureTest4));
	std::thread Thread3Test4(&calculatePrimeNumber, std::move(Thread3FutureTest4));
	std::thread Thread4Test4(&calculatePrimeNumber, std::move(Thread4FutureTest4));
	std::this_thread::sleep_for(std::chrono::seconds(10));
	ThreadExit = true;
	Thread1Test4.join();
	Thread2Test4.join();
	Thread3Test4.join();
	Thread4Test4.join();

	std::cout << "_____________________________4 Thread_____________________________" << std::endl << std::endl;
	std::cout << "Prime Numbers found in Thread 1: " << Thread1IntTest4.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 2: " << Thread2IntTest4.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 3: " << Thread3IntTest4.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread4IntTest4.get() << std::endl;
	std::cout << "__________________________________________________________________" << std::endl << std::endl;

	//8 Thread Test
	ThreadExit = false;
	std::promise<int> Thread1FutureTest8;
	std::promise<int> Thread2FutureTest8;
	std::promise<int> Thread3FutureTest8;
	std::promise<int> Thread4FutureTest8;
	std::promise<int> Thread5FutureTest8;
	std::promise<int> Thread6FutureTest8;
	std::promise<int> Thread7FutureTest8;
	std::promise<int> Thread8FutureTest8;
	auto Thread1IntTest8 = Thread1FutureTest8.get_future();
	auto Thread2IntTest8 = Thread2FutureTest8.get_future();
	auto Thread3IntTest8 = Thread3FutureTest8.get_future();
	auto Thread4IntTest8 = Thread4FutureTest8.get_future();
	auto Thread5IntTest8 = Thread5FutureTest8.get_future();
	auto Thread6IntTest8 = Thread6FutureTest8.get_future();
	auto Thread7IntTest8 = Thread7FutureTest8.get_future();
	auto Thread8IntTest8 = Thread8FutureTest8.get_future();
	std::thread Thread1Test8(&calculatePrimeNumber, std::move(Thread1FutureTest8));
	std::thread Thread2Test8(&calculatePrimeNumber, std::move(Thread2FutureTest8));
	std::thread Thread3Test8(&calculatePrimeNumber, std::move(Thread3FutureTest8));
	std::thread Thread4Test8(&calculatePrimeNumber, std::move(Thread4FutureTest8));
	std::thread Thread5Test8(&calculatePrimeNumber, std::move(Thread5FutureTest8));
	std::thread Thread6Test8(&calculatePrimeNumber, std::move(Thread6FutureTest8));
	std::thread Thread7Test8(&calculatePrimeNumber, std::move(Thread7FutureTest8));
	std::thread Thread8Test8(&calculatePrimeNumber, std::move(Thread8FutureTest8));
	std::this_thread::sleep_for(std::chrono::seconds(10));
	ThreadExit = true;
	Thread1Test8.join();
	Thread2Test8.join();
	Thread3Test8.join();
	Thread4Test8.join();
	Thread5Test8.join();
	Thread6Test8.join();
	Thread7Test8.join();
	Thread8Test8.join();

	std::cout << "_____________________________8 Thread_____________________________" << std::endl << std::endl;
	std::cout << "Prime Numbers found in Thread 1: " << Thread1IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 2: " << Thread2IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 3: " << Thread3IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread4IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread5IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread6IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread7IntTest8.get() << std::endl;
	std::cout << "Prime Numbers found in Thread 4: " << Thread8IntTest8.get() << std::endl;
	std::cout << "__________________________________________________________________" << std::endl << std::endl;

	return 0;
}

void calculatePrimeNumber(std::promise<int> && p) {
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