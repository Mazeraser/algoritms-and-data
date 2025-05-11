#include"queue.h"
#include<iostream>
#include<fstream>

//TODO: ввод двух очередей(вручную и с файла)
//TODO: сложение с чередованием DONE

int main() {
	int choice = -1;
	while(choice!=3)
	{
		std::cout << "1. Write from keyboard." << std::endl;
		std::cout << "2. Write from file." << std::endl;
		std::cout << "3. Exit." << std::endl;
		std::cin >> choice;

		Queue<int>* first_queue=new Queue<int>(1);
		Queue<int>* second_queue = new Queue<int>(1);
		int length = 0;
		std::ifstream test_file("test.txt");
		switch (choice)
		{
		case(1):
			std::cout << "Enter a lenght of queue: ";
			std::cin >> length;
			first_queue = new Queue<int>(length);
			second_queue = new Queue<int>(length);
			for (int i = 0; i < length; i++) {
				int element;
				std::cout << "Enter an element of first queue: ";
				std::cin >> element;
				first_queue->enqueue(element);
			}
			for (int i = 0; i < length; i++) {
				int element;
				std::cout << "Enter an element of second queue: ";
				std::cin >> element;
				second_queue->enqueue(element);
			}
			break;
		case(2):
			if (test_file.is_open()) {
				test_file >> length;
				first_queue = new Queue<int>(length);
				second_queue = new Queue<int>(length);
				for (int i = 0; i < length; i++) {
					int element;
					test_file >> element;
					first_queue->enqueue(element);
				}
				for (int i = 0; i < length; i++) {
					int element;
					test_file >> element;
					second_queue->enqueue(element);
				}
			}
			break;
		default:
			continue;
		}

		std::cout << "Result: ";
		Queue<int> third_queue =  *first_queue + *second_queue;
		while (!third_queue.isEmpty()) {
			std::cout << third_queue.dequeue() << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}