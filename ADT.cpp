#include <iostream>
using namespace std;

//Doing a struct for vertices
struct vertex 
{
	int number; 
	struct vertex* next; 	
}; 

//Class of a singly linked list 
class SLL 
{
	private: 
		vertex *headPointer=NULL, *tailPointer=NULL; 
		int numVertices=0;  
	public: 
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
				numVertices++;  
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
		//ERROR: doesnt work if index is 0 or numVertices
		void insertAtIndex(int index, int number)
		{
			if (index < 0 || index > numVertices) return; 
			else if (index == 0) insertAtHead(number); 
			else if (index == numVertices) insertAtTail(number); 
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
			delete tailPointer; 
			tailPointer = temp;
			numVertices--; 
		}
		//ERROR: doesnt seem to delete properly
		void deleteFromIndex(int index)
		{
			if (index < 0 || index > numVertices) return;  
			else if (index == 0) deleteHead(); 
			else if (index = numVertices) deleteTail();  
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
			cout << "NumV = " << numVertices; 
			cout << endl; 
		}
}; 

int main(void)
{
	SLL mySLL; 
	mySLL.printSLL(); 
	mySLL.insertAtHead(1); 
		mySLL.printSLL();
	mySLL.insertAtTail(2);
		mySLL.printSLL(); 
	mySLL.insertAtHead(0);
		mySLL.printSLL(); 
	mySLL.insertAtIndex(1, 3);
		mySLL.printSLL(); 
	mySLL.insertAtIndex(3, 5); 
	mySLL.printSLL();
	mySLL.deleteFromIndex(1); 
		mySLL.printSLL();
	return 0; 
}