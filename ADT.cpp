/*
Implementing a few ADTs to learn while doing
Author: Saif
*/

//TODO: 
//Fix the errors
//Figure out how to use "template" so that the ADTs can be more dynamic
//Change Priority_queue to a vector again later

#include <iostream>
#include <array>
#include <queue>

using namespace std;

//Class of a singly linked list
class SLL 
{
	private: 
		//Doing a struct for vertices
		struct vertex 
		{
			int number; 
			struct vertex* next; 	
		};   
		vertex *headPointer, *tailPointer; 
		int numVertices;
	public: 
		SLL()
		{
			tailPointer = headPointer=NULL;
			numVertices = 0;  
		}
		int getSize()
		{
			return numVertices; 
		}
		vertex* getHead()
		{ 
			return headPointer; 
		}
		vertex* getTail()
		{
			return tailPointer; 
		}
		void insertAtHead(int number)
		{
			if (numVertices == 0)
			{
			headPointer = new vertex;
			tailPointer = headPointer;
			headPointer->number = number; 
			tailPointer->number = number;   
			}	
			else 
			{
				vertex *temp = new vertex; 
				temp->next = headPointer; 
				temp->number = number; 
				headPointer = temp; 
			}
			numVertices++;  
		}
		void insertAtTail(int number)
		{
			if (numVertices == 0)
			{
				headPointer = new vertex;
				tailPointer = headPointer;  
				headPointer->number = number; 
				tailPointer->number = number;   
			}
			else 
			{
				vertex *temp = new vertex; 
				temp->number = number; 
				tailPointer->next = temp; 
				tailPointer = temp; 
			}
			numVertices++;
		}
		void insertAtIndex(int index, int number)
		{
			if (index < 0 || index > numVertices) return; 
			else if (index == 0) {insertAtHead(number); return;} 
			else if (index == numVertices) {insertAtTail(number); return;} 
			else 
			{	
				vertex *tempOld=headPointer; 
				for (int i=0; i<index-1; i++)
					tempOld = tempOld->next; 
				vertex *tempNew = new vertex; 
				tempNew->number = number; 
				tempNew->next = tempOld->next; 
				tempOld->next = tempNew; 
			}
			numVertices++; 
		}
		void deleteHead()
		{
			vertex *temp = headPointer; 
			headPointer = headPointer->next; 
			delete temp; 
			numVertices--; 
		}
		void deleteTail()
		{
			vertex *temp = headPointer; 
			for (int i=0; i<numVertices-1; i++)
				temp = temp->next; 
			tailPointer = temp;
			temp = temp->next; 
			delete temp; 
			numVertices--; 
		}
		void deleteFromIndex(int index)
		{
			if (index < 0 || index >= numVertices) return;  
			else if (index == 0) 
			{
				deleteHead();  
				return;
			}
			else 
			{
				vertex *tempOld = headPointer; 
				for (int i=0; i<index-1; i++)
					tempOld = tempOld->next; 
				vertex *tempDel = tempOld->next; 
				tempOld->next = tempDel->next; 
				delete tempDel;
			}
			numVertices--; 
		}
		void printSLL()
		{
			vertex *temp = headPointer; 
			for (int i=0; i<numVertices; i++)
			{
				cout << temp->number << " "; 
				temp = temp->next; 
			}
			cout << endl; 
		}
}; 

class priority_queue_c
{
	private: 
		array <int, 1000001> arr; 
		int numVertices;
	public: 
		priority_queue_c(){numVertices = 0; arr[0] = -1;}
		int size()
		{
			return numVertices; 
		}
		int top()
		{ 
			if (numVertices == 0) return -1; 
			return arr[1]; 
		}
		void push(int number)
		{
			numVertices++;
			int curIdx = numVertices; 
			arr[numVertices] = number; 
			while ((curIdx > 1) && (arr[curIdx/2] < arr[curIdx]))
			{
				swap(arr[curIdx/2], arr[curIdx]); 
				curIdx = curIdx/2; 
			} 
		}
		int pop()
		{
			int temp; 
			if (numVertices==0) return -1;  
			else 
			{
				temp = arr[1]; 
				int curIdx = 1; 
				arr[curIdx] = -1;
				bool swapped; 
				swap(arr[numVertices], arr[curIdx]);  
				do {
					swapped = false; 

					if (curIdx*2<numVertices && curIdx*2+1<numVertices)
					{
						if (arr[curIdx*2] > arr[curIdx*2+1]) 
						{
							if (arr[curIdx*2] > arr[curIdx]) {swap(arr[curIdx], arr[curIdx*2]); curIdx=curIdx*2;swapped = true;}
						}
						else if (arr[curIdx*2+1] > arr[curIdx]) {swap(arr[curIdx], arr[curIdx*2+1]); curIdx=curIdx*2+1; swapped = true;} 
					}
					else if (curIdx*2<numVertices && arr[curIdx*2] > arr[curIdx]) {swap(arr[curIdx], arr[curIdx*2]); curIdx=curIdx*2;swapped = true; }
					else if (curIdx*2+1<numVertices && arr[curIdx*2+1] > arr[curIdx]) {swap(arr[curIdx], arr[curIdx*2+1]); curIdx=curIdx*2+1; swapped = true; }
				} while (swapped); 
			} 
			numVertices--;
			return temp; 
		}
		void printPQ()
		{
			for (int i=1; i<numVertices+1; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl; 
		}
}; 


class stack
{
	private: 
		SLL mySll; 	//Using class composition
	public: 
		void push(int number)
		{
			mySll.insertAtHead(number); 
		}
		//ERROR: How to check against popping when there is no element?
		int pop()
		{
	 		int lastElem = (mySll.getHead())->number; 
			mySll.deleteHead(); 
			return lastElem; 
		}
		int getSize()
		{
			return mySll.getSize(); 
		}
		//ERROR: How to check against peeking when there is no element? 
		int peek()
		{
			return (mySll.getHead())->number; 
		}
		void printStack()
		{
			cout << "top of stack is here: "; 
			mySll.printSLL(); 
		}
};

class queue 
{
	private: 
		SLL mySll; 
	public: 
		void enqueue(int number)
		{
			mySll.insertAtTail(number); 
		}
		//ERROR: How to stop from dequeue-ing an empty queue?
		int dequeue()
		{
			int Elem = (mySll.getHead())->number;
			mySll.deleteHead(); 
			return Elem; 
		}
		int getSize()
		{
			return mySll.getSize(); 
		}
		//ERROR: How to stop from peeking at empty queue?
		int peek()
		{
			return (mySll.getHead())->number;
		}
		void printQueue()
		{
			cout << "Head of Queue here: "; 
			mySll.printSLL(); 
		}
}; 

int main(void)
{ 
	priority_queue_c PQ_c; 
	PQ_c.push(1); 
	PQ_c.push(3); 
	PQ_c.push(2);
 	PQ_c.pop(); 
 	PQ_c.push(4);
 	PQ_c.pop(); 
 	PQ_c.push(1);
 	PQ_c.push(5); 
 	PQ_c.push(2); 
 	PQ_c.pop(); 
 	PQ_c.push(1); 
 	while (PQ_c.size() != 0) {cout << PQ_c.top(); PQ_c.pop(); cout << PQ_c.size();}
 	cout << endl; 

 	priority_queue <int> PQ; 
 	PQ.push(1); 
 	PQ.push(3); 
 	PQ.push(2); 
 	PQ.pop();
 	PQ.push(4);
 	PQ.pop();
 	PQ.push(1);
 	PQ.push(5);
 	PQ.push(2);
 	PQ.pop();
 	PQ.push(1); 
 	while (PQ.size() != 0) {cout << PQ.top(); PQ.pop(); cout << PQ.size();}   
 	cout << endl; 

 	return 0; 
}