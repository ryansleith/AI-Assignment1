#include "algorithm.h"

#define DATA_SIZE 250000

using namespace std;

struct Node {
    Puzzle *data;
    Node *next;
};

class Queue {
private:
    Node *front, *rear;
    int count;
    int maxSize;
public:
    Queue();
    ~Queue();
    void Join(Puzzle *newthing);
    void JoinFront(Puzzle *newthing);
    void Leave();
    Puzzle* Front();
    bool isEmpty();
    void PrintAllElements();
    int getCount(){ return count; }
    int getMaxSize() { return maxSize; }
};


Queue::Queue() {
    // constructor
    front = NULL;  rear = NULL; count = 0; maxSize = 0;
}

Queue::~Queue() {
    // destructor
}

void Queue::Join(Puzzle *newthing) {
    // place the new thing at the front of the queue
    Node *temp;
    temp = new Node;
    temp->data = newthing;
    temp->next = NULL;
    if (rear != NULL) { rear->next = temp; }
    rear = temp;
    if (front == NULL) { front = temp; }
    count++;
    if (count > maxSize) {
        maxSize = count;
    }
}

void Queue::JoinFront(Puzzle *newthing) {
    // place the new thing at the front of the dequeue
    Node *temp;
    temp = new Node;
    temp->data = newthing;
    temp->next = front;
    front=temp;
    if (rear == NULL) { rear = temp; }
    count++;
    if (count > maxSize) {
        maxSize = count;
    }
}


void Queue::Leave() {
    // remove the front item from the queue
    Node * temp;
    if (front == NULL) { return; }
    temp = front;
    front = front->next;
    if (front == NULL) { rear = NULL; }
    delete temp;
    count--;
}

Puzzle* Queue::Front() {
    // return the value of the front item
    if (front != NULL) {return front->data;}
    return NULL;
}

bool Queue::isEmpty() {
    // return true if the queue is empty
    if (front == NULL) { return true; }
    return false;
}

void Queue::PrintAllElements(){
    //cout<<"Linked-list: ";
    Node *current;
    current=front;
    cout << "Queue Elements: ";
    while(current!=NULL){
        cout << current->data->toString() << ", ";
        current=current->next;
    }
    cout<<"end of Queue\n";
}

////////////////////////////////////////////////////////////////////////
vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;

//class Heap {
//private:
//    unsigned int data[DATA_SIZE];
//    int last, comparison;
//public:
//    Heap() {
//        last = -1;
//        comparison = 0;
//        for (int i = 0; i < DATA_SIZE; ++i) {
//            data[i] = 0;
//        }
//    }
//    ~Heap() {}
//    void insertHeap(unsigned int mData);
//    int deleteRoot();
//    void printHeap();
//    int getComparison() { return comparison; }
//};
//
//void Heap::insertHeap(unsigned int mData) {
//    last++;
//    data[last] = mData;
//    int temp, swappingIndex = last, parentIndex=0;
//    if (last == 0) { return; }
//    bool swapping = true;
//    while (swapping) {
//        swapping = false;
//        // Find which side it is
//        if (swappingIndex % 2 == 0) {
//            parentIndex = (swappingIndex / 2) - 1; // right
//        } else {
//            parentIndex = (swappingIndex / 2); // left
//        }
//        // do the swap if needed
//        if (parentIndex >= 0) {
//            comparison++;
//            if (data[swappingIndex] > data[parentIndex]) {
//                temp = data[swappingIndex];
//                data[swappingIndex] = data[parentIndex];
//                data[parentIndex] = temp;
//                swapping = true;
//                swappingIndex = parentIndex;
//            }
//        }
//    }
//}
//
//void Heap::printHeap() {
//    for (int i = 0; i < last + 1; ++i) {
//        cout << data[i] << " ";
//    }
//    cout << endl;
//}
//
//int Heap::deleteRoot(){
//    if (last == 0) { last--; return data[0]; }
//    // Delete root from populated heap
//    int deleted = data[0];
//    data[0] = data[last];
//    data[last] = 0;
//    last--;
//    int temp, leftIndex, rightIndex;
//    int parentIndex = 0;
//    bool swapping = true;
//    // Fix the tree
//    while (swapping) {
//        leftIndex = (parentIndex * 2) + 1;
//        rightIndex = (parentIndex * 2) + 2;
//        // Increase Comparisons
//        if (data[leftIndex] > 0) { comparison++; }
//        if (data[rightIndex] > 0) { comparison++; }
//        // Get the parentIndex data to check against the left/right
//        temp = data[parentIndex];
//        // Fix the tree if needed
//        if (temp < data[leftIndex] || temp < data[rightIndex]) {
//            swapping = true;
//            if (data[rightIndex] < data[leftIndex]) {
//                data[parentIndex] = data[leftIndex];
//                data[leftIndex] = temp;
//                parentIndex = leftIndex;
//            } else if (data[leftIndex] < data[rightIndex]) {
//                data[parentIndex] = data[rightIndex];
//                data[rightIndex] = temp;
//                parentIndex = rightIndex;
//            }
//        }
//        // It's fixed
//        else { swapping = false; }
//    } return deleted;
//}
//
///* the char* filename is just for printing the name, the file is opened and dealt with in the main() */
//void heapsort(vector<int> &sortingvector,int number_of_elements, char* filename){
//    /* Heap myHeap; .//declare a Heap instance here */
//    Heap myHeap;
//    /* Using the sortingvector, INSERT elements into the Heap */
//    for (unsigned i=0; i<number_of_elements; i++){
//        myHeap.insertHeap(sortingvector.at(i));
//    }
//    cout<<"Heap before sorting: "<<filename<<endl;
//    myHeap.printHeap();
//    //cout<<endl;
//    /* After building the heap from the file, PRINT the current state of the heap before sorting */
//    /* STORE how many comparisons were made until this point */
//    int insertComparisons = myHeap.getComparison();
//    cout<<"InsertHeap: "<< insertComparisons<< " comparisons"<<endl;
//
//    /* DELETE elements from the Heap, copying it back to the vector in a way that it is sorted */
//    int sorted[number_of_elements];
//    for (int i = 0; i < number_of_elements; ++i) {
//        sorted[i] = myHeap.deleteRoot();
//    }
//    /* STORE how many comparisons were made for the deletion process */
//    int deleteComparisons = myHeap.getComparison() - insertComparisons;
//    cout<<"DeleteRoot: "<< deleteComparisons<< " comparisons"<<endl;
//    /* PRINT the number of comparisons for the Insert and Deletion tasks */
//
//    /* Print the state of the vector after sorting */
//    cout<<"Vector after sorting:"<<endl;
//    for (int i = number_of_elements - 1; i >= 0; --i) {
//        cout << sorted[i] << " ";
//        //else{cout << sorted[i];}
//    }
//    cout << endl;
//}



///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<breadthFirstSearch>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	maxQLength=0;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	return path;

}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search with VisitedList
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	return path;

}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int &maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;

    //algorithm implementation
    cout << "------------------------------" << endl;
    cout << "<<progressiveDeepeningSearch_No_VisitedList >>" << endl;
    cout << "------------------------------" << endl;

    Queue searchQueue;
    cout << "Inital State:" << initialState;

    Puzzle *searchState, *foundGoalState;
    int maxDepth, count;
    maxDepth = count = 1;
    bool goalFound = false;
    startTime = clock();
    while (!goalFound) {
        //Add start node to Queue to restart searching at deeper depth.
        Puzzle *startState = new Puzzle(initialState, goalState);
        searchState = startState;
        count = 0;
        cout << "Start State: " << searchState->toString() << endl;

        do {
            if (searchState->goalMatch()) {
                cout << "Goal Found!" << endl;
                foundGoalState = searchState;
                goalFound = true;
                break;
            }
            //cout << "Depth: " << searchState->getDepth() << endl;
            //cout << "Max-Depth: " << maxDepth << endl;
            if(searchState->getDepth() <= maxDepth) {
                //cout << "Search State No: " << count << endl;
                //searchState->printBoard();
                /*if (searchQueue.isEmpty()) {
                    cout << "Queue is empty" << endl;
                } else {
                    cout << "Queue is not empty" << endl;
                }*/
                //Calculate last state to save time
                if (searchState->canMoveUp(maxDepth)) {
                    //cout << "Move Up" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'D' || count == 0) {
                        searchQueue.JoinFront(searchState->moveUp());
                    }
                }
                if (searchState->canMoveRight(maxDepth)) {
                    //cout << "Move Right" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'L' || count == 0) {
                        searchQueue.JoinFront(searchState->moveRight());
                    }
                }
                if (searchState->canMoveDown(maxDepth)) {
                    //cout << "Move Down" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'U' || count == 0) {
                        searchQueue.JoinFront(searchState->moveDown());
                    }
                }
                if (searchState->canMoveLeft(maxDepth)) {
                    //cout << "Move Left" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'R' || count == 0) {
                        searchQueue.JoinFront(searchState->moveLeft());
                    }
                }
            }
            delete searchState;
            searchState = searchQueue.Front();
            searchQueue.Leave();
            count++;
            if (count % 1000000 == 0) {
                cout << "Searching..." << endl;
                searchQueue.PrintAllElements();
                cout << "Depth: " << searchState->getDepth() << endl;
            }
            //searchQueue.PrintAllElements();
            //cout << "SearchState: " << searchState->toString() << " startstate: " << startState->toString() << endl;
        } while(!searchQueue.isEmpty());
        maxDepth++;
        cout << "Incease search to depth: " << maxDepth << endl;
    }
    
    if (goalFound) {
        cout << "-----Goal Found!-----" << endl;
        cout << "State Number: " << count << endl;
        path = foundGoalState->getPath();  //this is just a dummy path for testing the function
    } else {
        cout << "-----No Goal Found!-----" << endl;
        path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
    }

	maxQLength=searchQueue.getMaxSize();
//]***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return path;
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;
    //add necessary variables here
    int depth = 1;

    //Call puzzle bitch at some point - Start State, Goal State needs to be sent

    //Call puzzle every time

    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_with_NonStrict_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU"; //this is just a dummy path for testing the function

	return path;

}


string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){

   string path;
   clock_t startTime;
   //int TestingGoalState = 123804765;
   //int TestingTestCase = 132084765

   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

   // call hFunction with number of tiles moved
   //create instance of puzzle and find heuristic value
   

   //find path of action
   //admissable heroustics f = g + h
   // f(node(S)) = g(node(S)) + h(node(S))
   // f(node(A)) = g(node(S+A)) + h(node(A))
   // f(node(B)) = g(node(S+B)) + h(node(A))
   //call heuristicFunction with numOfMisplacedTiles



    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;
	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU"; //this is just a dummy path for testing the function

	return path;

}
