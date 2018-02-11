/*
Implementing a few ADTs.
Learn by coding!
Author: Psyf
*/

//TO DO:
//Implement DLL and Deque

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//Class of a singly linked list
template <class T>
class SLL 
{
	private: 
		//Doing a struct for vertices
		struct vertex 
		{
			T element; 
			struct vertex* next; 	
		};   
		vertex *headPointer, *tailPointer; 
		int numVertices;
	public: 
		SLL()
		{
			tailPointer=headPointer=NULL;
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
		void insertAtHead(T element)
		{
			if (numVertices == 0)
			{
			headPointer = new vertex;
			tailPointer = headPointer;
			headPointer->element = element; 
			tailPointer->element = element;   
			}	
			else 
			{
				vertex *temp = new vertex; 
				temp->next = headPointer; 
				temp->element = element; 
				headPointer = temp; 
			}
			numVertices++;  
		}
		void insertAtTail(T element)
		{
			if (numVertices == 0)
			{
				headPointer = new vertex;
				tailPointer = headPointer;  
				headPointer->element = element; 
				tailPointer->element = element;   
			}
			else 
			{
				vertex *temp = new vertex; 
				temp->element = element; 
				tailPointer->next = temp; 
				tailPointer = temp; 
			}
			numVertices++;
		}
		void insertAtIndex(int index, T element)
		{
			if (index < 0 || index > numVertices) return; 
			else if (index == 0) {insertAtHead(element); return;} 
			else if (index == numVertices) {insertAtTail(element); return;} 
			else 
			{	
				vertex *tempOld=headPointer; 
				for (int i=0; i<index-1; i++)
					tempOld = tempOld->next; 
				vertex *tempNew = new vertex; 
				tempNew->element = element; 
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
				cout << temp->element << " "; 
				temp = temp->next; 
			}
			cout << endl; 
		}
}; 

template <class T>
class priority_queue
{
	private: 
		vector <T> arr;  
		int numVertices;
	public: 
		priority_queue() {numVertices = 0; arr.reserve(1000000); arr[0] = -1;}
		int size()
		{
			return numVertices; 
		}
		T top()
		{ 
			if (numVertices == 0) return -1; 
			return arr[1]; 
		}
		void push(T element)
		{
			numVertices++;
			int curIdx = numVertices; 
			arr[numVertices] = element; 
			while ((curIdx > 1) && (arr[curIdx/2] < arr[curIdx]))
			{
				swap(arr[curIdx/2], arr[curIdx]); 
				curIdx = curIdx/2; 
			} 
		}
		T pop()
		{
			T temp; 
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

template <class T>
class stack
{
	private: 
		SLL <T> mySll; 	//Using class composition
	public: 
		void push(T element)
		{
			mySll.insertAtHead(element); 
		}
		T pop()
		{
			if (mySll.getSize() == 0) {cout << "INVALID OPERATION: No element in stack.\n"; exit(EXIT_FAILURE);} 
	 		T lastElem = (mySll.getHead())->element; 
			mySll.deleteHead(); 
			return lastElem; 
		}
		int getSize()
		{
			return mySll.getSize(); 
		}
		T peek()
		{
			if (mySll.getSize() == 0) {cout << "INVALID OPERATION: No element in stack.\n"; exit(EXIT_FAILURE);} 	
			return (mySll.getHead())->element; 
		}
		void printStack()
		{
			cout << "top of stack is here: "; 
			mySll.printSLL(); 
		}
};

template <class T>
class queue 
{
	private: 
		SLL <T> mySll; 
	public: 
		void enqueue(int element)
		{
			mySll.insertAtTail(element); 
		}
		T dequeue()
		{
			if (mySll.getSize() == 0) {cout << "INVALID OPERATION: No element in queue.\n"; exit(EXIT_FAILURE);} 		
			int Elem = (mySll.getHead())->element;
			mySll.deleteHead(); 
			return Elem; 
		}
		int getSize()
		{
			return mySll.getSize(); 
		}
		T peek()
		{
			if (mySll.getSize() == 0) {cout << "INVALID OPERATION: No element in queue.\n"; exit(EXIT_FAILURE);} 	
			return (mySll.getHead())->element;
		}
		void printQueue()
		{
			cout << "Head of Queue here: "; 
			mySll.printSLL(); 
		}
}; 


int main(void)
{  
	return 0; 
}