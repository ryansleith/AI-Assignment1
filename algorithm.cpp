#include "algorithm.h"

#include <string>

#define DATA_SIZE 250000

/////////////////////////////////////////////////////////////////////////////////

using namespace std;

struct Node {
    Puzzle *data;
    Node *next;
};

///////////////////////////-------QUEUE-----/////////////////////////////////////

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
    // place the new thing at the rear of the queue??
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
        cout << current->data->toString() << " " << current->data->getDepth() << ", ";
        current=current->next;
    }
    cout<<"end of Queue\n";
}

///////////////////////////------HASH TABLE-----/////////////////////////////////

class HashTable {
private:
    int size;
    vector<Node> table;
    map<int, int> hashedValues;
public:
    HashTable();
    ~HashTable();
    //calculate and return hash index
    int Hash(string key);
    //insert element into hash table using the Hash function, also update map
    int Insert(Puzzle *data);
    Node* GetElement(string key);
    //When the looping has been completed and all elements processed check for most hashed values and their count
    void printTopHashElements();
};


HashTable::HashTable() {
    // Constructor
    size = 9*8*7*6*5*4*3*2*1;
    for (int i = 0; i < size; i++) {
        Node temp;
        temp.data = NULL;
        temp.next = NULL;
        table.push_back(temp);
    }
    cout << "Hash table filled with default values, size: " << size << endl;
}

HashTable::~HashTable() {
    table.clear();
}

int HashTable::Hash(string key) {
    int iKey = atoi(key.c_str());
    iKey = iKey % size;
    return iKey;
}

int HashTable::Insert(Puzzle *data) {
    int index = Hash(data->toString());
    //cout << "Index: " << index << " Value: " << data->toString();
    //check vector for element if index exists
    if (table[index].data == NULL) {
        //No Element already holds this space, set to first element
        //cout << " is a new element" << endl;
        table[index].data = data;
        table[index].next = NULL;
        hashedValues[index] = 1;
        return index;
    } else if(table[index].data != NULL) {
        //Find next Node with free next pointer for collission
        //cout << "is a collission" << endl;
        
        //Check if first collission is the passed Puzzle state
        if (data->toString() == table[index].data->toString()) {
            //cout << "Element " << data->toString() << " with depth: " << data->getDepth() << " FOUND " << table[index].data->toString() << " " << table[index].data->getDepth();
            if(data->getDepth() < table[index].data->getDepth()) {
                //cout << "Which is shallower and now added to visited list!" << endl;
                delete table[index].data;
                //Possibly delete from Queue???
                table[index].data = data;
                hashedValues[index]++;
                return index;
            } else {
                //cout << "Which is equal/deeper so not added to visited list!" << endl;
                return -1;
            }
        }
        
        //Traverse the list of collissions looking for the passed Puzzle State
        Node *temp;
        temp = new Node;
        temp->data = data;
        temp->next = NULL;
        if(table[index].next == NULL) {
            //No collissions set, set first collission to temp
            //cout << " at the initial level" << endl;
            hashedValues[index]++;
            table[index].next = temp;
        } else {
            //Now iterate the linked list of collissions
            Node *searchNode = new Node;
            searchNode = table[index].next;
            //cout << "Needs to be found!" << endl;
            while(searchNode->next != NULL) {
                //cout << "Traversing collissions" << endl;
                if (searchNode->data->toString() == data->toString()) {
                    //cout << "Element " << data->toString() << " with depth: " << data->getDepth() << " FOUND " << table[index].data->toString() << " " << table[index].data->getDepth();
                    //Delete temp as it won't be used
                    delete temp;
                    if(data->getDepth() < searchNode->data->getDepth()) {
                        //Passed State is shallower, update the list accordingly
                        //cout << " And is shallower! Replacing previous Puzzle element" << endl;
                        delete searchNode->data;
                        //Possibly delete from Queue???
                        searchNode->data = data;
                        hashedValues[index]++;
                        return index;
                    } else {
                        //cout << " And is equal/Deeper! Ignoring element" << endl;
                        return -1;
                    }
                }
                searchNode = searchNode->next;
            }
            //Update temp with Node passed if it isn't found in the linked list
            //cout << "Element wasn't already in collission list, added to end!" << endl;
            searchNode->next = temp;
            //Update Map to record collissions
            hashedValues[index]++;
            return index;
        }
    }
}

Node* HashTable::GetElement(string key) {
    int index = Hash(key);
    //cout << "Searching for Key Hashed: " << index << endl;
    if (table[index].data != NULL) {
        //Traverse and send last element of the table
        if (table[index].data->toString() == key) {
            return &table[index];
        } else if (table[index].next != NULL) {
            Node *current = new Node;
            current = table[index].next;
            while (current != NULL) {
                if(current->data->toString() == key) {
                    return current;
                } else {
                    current = current->next;
                }
            }
            
        }
    }
    return NULL;
}

void HashTable::printTopHashElements() {
    int array[10][2];
    
    for(int i = 0; i < 10; i++) {
        array[i][0] = 0;
        array[i][1] = 0;
    }
    
    // output the results
    auto it = hashedValues.begin();
    while (it != hashedValues.end()) {
        cout << it->first << " has a value of " << it->second << endl;
        for(int i = 0; i < 10; i++) {
            if(it->second > array[i][1]) {
                array[i][0] = it->first;
                array[i][1] = it->second;
                //Break out of forloop
                break;
            }
        }
        ++it;
    }
}


///////////////////////////-------HEAP------/////////////////////////////////////
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
    
    //algorithm implementation
    // cout << "------------------------------" << endl;
    //    cout << "<<breadthFirstSearch>>" << endl;
    //    cout << "------------------------------" << endl;
    
    string path;
    
    Queue searchQueue;
    cout << "Inital State:" << initialState << endl;
    
    Puzzle *searchState, *foundGoalState;
    Puzzle *startState = new Puzzle(initialState, goalState);
    
    searchState = startState;
    clock_t startTime;
    startTime = clock();
    int count = 0;
    bool goalFound = false;
    do {
        if (searchState->goalMatch()) {
                foundGoalState = searchState;
                goalFound = true;
                break;
        }
        //Calculate last state to save time
        if (searchState->canMoveUp()) {
            //cout << "Move Up" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'D' || count == 0) {
                searchQueue.Join(searchState->moveUp());
            }
        }
        if (searchState->canMoveRight()) {
            //cout << "Move Right" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'L' || count == 0) {
                searchQueue.Join(searchState->moveRight());
            }
        }
        if (searchState->canMoveDown()) {
            //cout << "Move Down" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'U' || count == 0) {
                searchQueue.Join(searchState->moveDown());
            }
        }
        if (searchState->canMoveLeft()) {
            //cout << "Move Left" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'R' || count == 0) {
                searchQueue.Join(searchState->moveLeft());
            }
        }
            
        delete searchState;
        searchState = searchQueue.Front();
        searchQueue.Leave();
        //out << "Search State: " << searchState->toString() << endl;
        if (count % 1000000 == 0) {
            cout << "Searching..." << endl;
            //searchQueue.PrintAllElements();
        }
        count++;
    } while(searchState != NULL && searchState->getDepth() < 32);
    
    if (goalFound) {
        //searchQueue.PrintAllElements();
        cout << "-----Goal Found!-----" << endl;
        cout << "State Number: " << count << endl;
        cout << "" << foundGoalState->toString() <<endl;
        path = foundGoalState->getPath();  //this is just a dummy path for testing the function
    } else {
        // cout << "-----No Goal Found!-----" << endl;
        path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
    }
    
    maxQLength=searchQueue.getMaxSize();
    
    //***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
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
    
    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;
    
    string path;
    
    Queue searchQueue;
    HashTable visitedList;
    cout << "Inital State:" << initialState << endl;
    
    Puzzle *searchState, *foundGoalState;
    Puzzle *startState = new Puzzle(initialState, goalState);
    
    searchState = startState;
    clock_t startTime;
    startTime = clock();
    int count = 0;
    bool goalFound = false;
    do {
        if (searchState->goalMatch()) {
            foundGoalState = searchState;
            goalFound = true;
            break;
        }
        //Calculate last state to save time
        if (searchState->canMoveUp()) {
            //cout << "Move Up" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'D' || count == 0) {
                if (visitedList.GetElement(searchState->moveUp()->toString()) == NULL) {
                    visitedList.Insert(searchState->moveUp());
                    searchQueue.Join(searchState->moveUp());
                }
            }
        }
        if (searchState->canMoveRight()) {
            //cout << "Move Right" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'L' || count == 0) {
                if (visitedList.GetElement(searchState->moveRight()->toString()) == NULL) {
                    visitedList.Insert(searchState->moveRight());
                    searchQueue.Join(searchState->moveRight());
                }
            }
        }
        if (searchState->canMoveDown()) {
            //cout << "Move Down" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'U' || count == 0) {
                if (visitedList.GetElement(searchState->moveDown()->toString()) == NULL) {
                    visitedList.Insert(searchState->moveDown());
                    searchQueue.Join(searchState->moveDown());
                }
            }
        }
        if (searchState->canMoveLeft()) {
            //cout << "Move Left" << endl;
            if(searchState->getLastMove(searchState->getPathLength()-1) != 'R' || count == 0) {
                if (visitedList.GetElement(searchState->moveLeft()->toString()) == NULL) {
                    visitedList.Insert(searchState->moveLeft());
                    searchQueue.Join(searchState->moveLeft());
                }
            }
        }
        
        delete searchState;
        searchState = searchQueue.Front();
        searchQueue.Leave();
        //out << "Search State: " << searchState->toString() << endl;
        if (count % 1000000 == 0) {
            cout << "Searching..." << endl;
            //searchQueue.PrintAllElements();
        }
        count++;
    } while(searchState != NULL && searchState->getDepth() < 32);
    
    if (goalFound) {
        //searchQueue.PrintAllElements();
        cout << "-----Goal Found!-----" << endl;
        cout << "State Number: " << count << endl;
        cout << "" << foundGoalState->toString() <<endl;
        path = foundGoalState->getPath();  //this is just a dummy path for testing the function
    } else {
        // cout << "-----No Goal Found!-----" << endl;
        path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
    }
    
    maxQLength=searchQueue.getMaxSize();
    
    //***********************************************************************************************************
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
    while (!goalFound && maxDepth < 32) {
        //Add start node to Queue to restart searching at deeper depth.
        Puzzle *startState = new Puzzle(initialState, goalState);
        searchState = startState;
        count = 0;
        cout << "Start State: " << searchState->toString() << endl;

        do {
            //cout << "Depth: " << searchState->getDepth() << endl;
            //cout << "Max-Depth: " << maxDepth << endl;
            if (searchState->goalMatch()) {
                cout << "Goal Found!" << endl;
                foundGoalState = searchState;
                goalFound = true;
                break;
            }
            /*if (searchState->toString() == "364258071" || searchState->toString() == "364258701" || searchState->toString() == "364208751" || searchState->toString() == "304268751" || searchState->toString() == "340268751" || searchState->toString() == "348260751" || searchState->toString() == "348261750" || searchState->toString() == "348261705" || searchState->toString() == "348201765") {
                cout << searchState->toString() << " FOUND! At Depth: " << searchState->getDepth() << endl;
            }*/
            searchQueue.Leave();
            //searchQueue.PrintAllElements();
            
            if(searchState->getDepth() <= maxDepth) {
                //Calculate last state to save time
                if (searchState->canMoveLeft(maxDepth)) {
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'R' || count == 0) {
                        //cout << "Move Left" << endl;
                        searchQueue.JoinFront(searchState->moveLeft());
                    }
                }
                if (searchState->canMoveDown(maxDepth)) {
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'U' || count == 0) {
                        //cout << "Move Down" << endl;
                        searchQueue.JoinFront(searchState->moveDown());
                    }
                }
                if (searchState->canMoveRight(maxDepth)) {
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'L' || count == 0) {
                        //cout << "Move Right" << endl;
                        searchQueue.JoinFront(searchState->moveRight());
                    }
                }
                if (searchState->canMoveUp(maxDepth)) {
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'D' || count == 0) {
                        //cout << "Move Up" << endl;
                        searchQueue.JoinFront(searchState->moveUp());
                    }
                }
            }
            delete searchState;
            searchState = searchQueue.Front();
            //getchar();
            count++;
            if (count % 1000000 == 0) {
                cout << "Searching..." << endl;
                searchQueue.PrintAllElements();
                cout << "Depth: " << searchState->getDepth() << endl;
            }
            //cout << "SearchState: " << searchState->toString() << " startstate: " << startState->toString() << endl;
        } while(searchState != NULL);
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

    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_with_NonStrict_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;
    
    /* Progressive Ddpending Search With Non Strict Visited List concept
     
     A state of the Puzzle is what we want to put in the visited list, if we find that state again then we check if the instance of the state (searchState) is shallower than the instance in the visited list, If it is then we add the new version to the Queue as well as replacing the place of the deeper version from Visited List. If it is deeper than the version in the Visited List then we don't add the state to the Queue
     
        ??Do I need to remove the deeper instance of State from Queue as well??*/

    
    //Vector for the Visited List, reset each time the depth increases
    //Need a function to iterate the vector
    Queue searchQueue;
    cout << "Inital State:" << initialState << endl;
    
    Puzzle *searchState, *foundGoalState;
    int maxDepth, count;
    maxDepth = count = 1;
    bool goalFound = false;
    startTime = clock();
    while (!goalFound && maxDepth < 32) {
        //Add start node to Queue to restart searching at deeper depth.
        Puzzle *startState = new Puzzle(initialState, goalState);
        searchState = startState;
        HashTable visitedList;
        count = 0;
        cout << "Start State: " << searchState->toString() << endl;
        visitedList.Insert(searchState);
        
        do {
            if (searchState->goalMatch()) {
                cout << "Goal Found!" << endl;
                foundGoalState = searchState;
                goalFound = true;
                break;
            }
            searchQueue.Leave();
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
                if (searchState->canMoveLeft(maxDepth)) {
                    //cout << "Move Left" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'R' || count == 0) {
                        
                        //Only if the hashtable inserts element to the hashtable should we add a path expansion to the Queue
                        if (visitedList.Insert(searchState->moveLeft()) != -1) {
                            //The element was added to the visited List and should therefore be added the searchQueue
                            searchQueue.JoinFront(searchState->moveLeft());
                            //????
                            //Possibly need to distinguish if we need to delete any deeper elements from searchQueue than the shallower
                            //????
                        }
                    }
                }
                if (searchState->canMoveDown(maxDepth)) {
                    //cout << "Move Down" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'U' || count == 0) {
                        
                        //Only if the hashtable inserts element to the hashtable should we add a path expansion to the Queue
                        if (visitedList.Insert(searchState->moveDown()) != -1) {
                            //The element was added to the visited List and should therefore be added the searchQueue
                            searchQueue.JoinFront(searchState->moveDown());
                            //????
                            //Possibly need to distinguish if we need to delete any deeper elements from searchQueue than the shallower
                            //????
                        }
                    }
                }
                if (searchState->canMoveRight(maxDepth)) {
                    //cout << "Move Right" << endl;
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'L' || count == 0) {
                        
                        //Only if the hashtable inserts element to the hashtable should we add a path expansion to the Queue
                        if (visitedList.Insert(searchState->moveRight()) != -1) {
                            //The element was added to the visited List and should therefore be added the searchQueue
                            searchQueue.JoinFront(searchState->moveRight());
                            //????
                            //Possibly need to distinguish if we need to delete any deeper elements from searchQueue than the shallower
                            //????
                        }
                    }
                }
                if (searchState->canMoveUp(maxDepth)) {
                    if(searchState->getLastMove(searchState->getPathLength()-1) != 'D' || count == 0) {
                        
                        //Only if the hashtable inserts element to the hashtable should we add a path expansion to the Queue
                        if (visitedList.Insert(searchState->moveUp()) != -1) {
                            //The element was added to the visited List and should therefore be added the searchQueue
                            searchQueue.JoinFront(searchState->moveUp());
                            //????
                            //Possibly need to distinguish if we need to delete any deeper elements from searchQueue than the shallower
                            //????
                        }
                    }
                }
            }
            delete searchState;
            searchState = searchQueue.Front();
            count++;
            //cout << "Searching..." << endl;
            //searchQueue.PrintAllElements();
            //cout << "Depth: " << searchState->getDepth() << endl;
            //searchQueue.PrintAllElements();
            //cout << "SearchState: " << searchState->toString() << " startstate: " << startState->toString() << endl;
        } while(searchState != NULL);
        maxDepth++;
        cout << endl << "------------------Incease search to depth: " << maxDepth << "--------------------------" << endl << endl;
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


//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);

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
