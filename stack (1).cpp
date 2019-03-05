/*
  Name:		Parker Tuck, parkertuck@my.unt.edu , 11107228, prt0049
  Class:	CSCE 3110 - Data Structures and Algorithms
  Instructor:	Oleg Kolgushev
  Description:	Stack
*/

#include <iostream>

using namespace std;

template <typename data>
class Stack {

private:

	struct node {
	  data value;	//TODO int
	  struct node *next;
	};
	struct node *headPtr, *tailPtr;
	int numOfItems;

public:

	Stack();
	~Stack();
	void Push(data val);
	data Pop();
	data Peek();
	bool IsEmpty();

	void print();

};

template <typename data>
Stack<data>::Stack() {
	this->headPtr = NULL;
	this->tailPtr = NULL;
	this->numOfItems = 0;
}

template <typename data>
Stack<data>::~Stack() {
	for ( int idx = 0; idx < numOfItems; idx++ ) {
		this->Pop();
	}
}

/*
 * Add node to end of queue
 */
template <typename data>
void Stack<data>::Push(data val) {

	struct node *newNodePtr = new node;
	newNodePtr->value = val;

  // still good
	if ( numOfItems == 0 ) {
		this->headPtr = newNodePtr;
		this->tailPtr = newNodePtr;
    newNodePtr->next = NULL;
		this->numOfItems++;
		return;
	}

  newNodePtr->next = this->headPtr;
  this->headPtr = newNodePtr;
  
	//this->tailPtr->next = newNodePtr;
	//this->tailPtr = newNodePtr;
	this->numOfItems++;

}

/*
 * Remove node from front of queue
 */
template <typename data>
data Stack<data>::Pop() {
	if ( numOfItems == 0 )
		return 0;

	data returnVal = this->headPtr->value;

	// remove head node, assign next node as head, delete old head, decrease number of items in queue
	struct node *tempNode = this->headPtr;	// tempNode = node being removed
	this->headPtr = tempNode->next;			// assign the next node in queue as the headPtr
	delete tempNode;						// delete the old head node
	this->numOfItems--;						// decrease number of items in queue by one

	return returnVal;
}

/*
 * See what node/value is at top without removing it
 */
template <typename data>
data Stack<data>::Peek() {
	if ( numOfItems == 0 ) {
		return 0;
	}
	return this->headPtr->value;
}

/*
 * Returns true if empty
 */
template <typename data>
bool Stack<data>::IsEmpty() {
	return (this->numOfItems == 0);
}

/*
 *
 */
template <typename data>
void Stack<data>::print() {

	if ( this->numOfItems == 0) {
		cout << "Stack is empty.";
		return;
	}

	struct node *tempPtr;
	tempPtr = this->headPtr;
	while ( tempPtr != NULL ) {
		cout << tempPtr->value << ", ";
		tempPtr = tempPtr->next;
	}

}


int main() {

  int choice = 0;
  Stack<int> myStack;
  
  while ( 1 ) {
    cout << "Would you like to: Push (1), Pop (2), Peek (3), IsEmpty (4), or Exit (5)?: ";
    cin >> choice; cin.ignore();  // clear buffer
    int temp = 0;
    
    if ( choice ==  1 ) {
      cout << "What integer value would you like to add to the stack?: ";
      cin >> temp; cin.ignore();
      myStack.Push(temp);
    }
    else if ( choice == 2 ) {
      temp = myStack.Pop();
      if ( temp == 0 ) 
        cout << "Stack is empty.";
      else
        cout << "Item popped: " << temp;
    }
    else if ( choice == 3 ) {
      temp = myStack.Peek();
      if ( temp == 0 )
        cout << "Stack is empty.";
      else
        cout << "Item at top of stack is: " << temp;
    }
    else if ( choice == 4 ) {
      if ( myStack.IsEmpty() )
        cout << "Stack is empty.";
      else
        cout << "Stack is not empty.";
    } 
    else if ( choice == 5 ) {
      cout << "Exiting program.";
      return 0;
    }
    else {
      cout << "Invalid option. Try again.";
    }
    cout << endl;
    myStack.print();
    cout << endl << endl;
  }
  
  return 0;
}

