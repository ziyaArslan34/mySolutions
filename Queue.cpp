#include <iostream>

class Queue {
	private:
		int *arr;
		int arrSize;
		int tailQueue;
		int headQueue;
		int queueSize;

	public:
		Queue(int arrSize) {
			this->arrSize = arrSize;
			arr = new int[this->arrSize];
			headQueue = arr[0];
			tailQueue = arr[0];
			queueSize = 0;
		}

		int *expand(int *arr, int *size) {
			int *newArr = new int[(*size)*2];
			for(int i=0;i<*size;i++) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			*size *= 2;
			return newArr;
		}

		bool deQueue() {
			if(queueSize == 0) { return false; }

			for(int i=0;i<queueSize;i++) {
				arr[i] = arr[i+1];
			}

			tailQueue = arr[queueSize];

			queueSize--;
			return true;
		}

		bool enQueue(int num) {
			if(queueSize == arrSize) {
				arr = expand(arr, &arrSize);
				arr[queueSize] = num;
				queueSize++;
				return true;
			}

			arr[queueSize] = num;
			tailQueue = arr[queueSize];

			queueSize++;
			return true;
		}

		void display() {
			for(int i=0;i<queueSize;i++) {
				std::cout<<arr[i]<<"\n";
			}
		}
};

int main() {
	Queue q(5);

	q.enQueue(25);
	q.enQueue(34);
	q.enQueue(100);
	q.enQueue(200);
	q.enQueue(300);
	q.enQueue(400);
	q.display();
	q.deQueue();
	q.deQueue();
	q.deQueue();
	std::cout<<std::endl;
	q.display();
}
