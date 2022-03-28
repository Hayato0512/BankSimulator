/* 
 * Queue.h
 *
 * Description: Implementation of an int sequence with enqueue/dequeue ...
 *              if the queue gets full, it will become double the size to accomodate more elements.
 *              if # of elements becomes less than 1/4 of the capacity, the queue shrinks to half the size.
 *FIFO
 * 
 * Author: Hayato Koyama
 * Date:   Mar 25, 2022
 */
#include "Event.h"
#include "EmptyDataCollectionException.h"
template<class ElementType>
class Queue {
	
    private:
        static unsigned const INITIAL_CAPACITY = 50; // Constant INITIAL_CAPACITY
        ElementType *elements;             // To do: replace this by int * elements -> Question 4.a)

        unsigned int  elementCount;                      // Number of elements in the Queue
        unsigned int capacity;                          // Actual capacity of the data structure (number of cells in the array)
        unsigned int frontindex;                        // Index the topmost element
        unsigned int backindex;                         // Index where the next element will be placed
        bool QueueIsFull();
        bool indexIsNotFlipped();
        bool indexIsFlipped();                     
        int getElementCount();
      
    public:
        // Description:  Constructor
        Queue();

        ~Queue();


        // Description: Inserts newElement at the "back" of this Queue 
        //              (not necessarily the "back" of its data structure) and 
        //              returns "true" if successful, otherwise "false".
        // Time Efficiency: O(1)
        void enqueue(ElementType x);


        // Description: Removes (but does not return) the element at the "front" of this Queue 
        //              (not necessarily the "front" of its data structure).
        // Precondition: This Queue is not empty.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
        // Time Efficiency: O(1)
        void dequeue();


        // Description: Returns (but does not remove) the element at the "front" of this Queue
        //              (not necessarily the "front" of its data structure).
        // Precondition: This Queue is not empty.
        // Postcondition: This Queue is unchanged by this operation.
        // Exception: Throws EmptyDataCollectionException if this Queue is empty.
        // Time Efficiency: O(1)
        ElementType& peek() const;


        // Description: Returns "true" if this Queue is empty, otherwise "false".
        // Postcondition: This Queue is unchanged by this operation.
        // Time Efficiency: O(1)
        bool isEmpty() const;

        
};

template<class ElementType>
Queue<ElementType>::Queue() : elementCount(0), capacity(INITIAL_CAPACITY), frontindex(0), backindex(0) {
    elements = new ElementType[INITIAL_CAPACITY];
} 
template<class ElementType>
Queue<ElementType>::~Queue() {
    delete [] elements;
}
//just a helper function
template<class ElementType>
bool Queue<ElementType>::QueueIsFull(){
    return capacity==elementCount;
}
//just a helper function
template<class ElementType>
bool Queue<ElementType>::indexIsNotFlipped(){
    return frontindex<backindex;
}
//just a helper function
template<class ElementType>
bool Queue<ElementType>::indexIsFlipped(){
    return frontindex<backindex;
}


// Description:  Inserts element x at the back (O(1))
// Precondition:  
// Postcondition: the queue has the input element.
//                if the queue becomes full, make the size double to accomodate a new element.
template<class ElementType>
void Queue<ElementType>::enqueue(ElementType x) {
    elementCount++;
    if(QueueIsFull()){                                  // if full,
        ElementType* toBeDeleted = elements;
        ElementType *newelements = new ElementType[capacity*2];  // make new allocated array(double the size of original array)

        if(indexIsNotFlipped()){                                // if frontindex < backindex,
            for(unsigned int i = frontindex;i<backindex;i++){   //just copy the elements to the new array to the same index. 
                newelements[i] = elements[i];
            }
            capacity = capacity*2;              //double the capacity
            delete[] toBeDeleted;               //delete the old array
            elements = newelements;             //the pointer elements now points to the new bigger array.
            


        }
        else if(indexIsFlipped()){                                      //if frontindex > backindex(this might happen because of the nature of circular array.)
                                                                        //e.g. index 0 1 2 3 4 5 
            for(unsigned int i =0;i<(elementCount-frontindex);i++){      //     elmts 3       1 2
                                                                        //           Back      Front
                newelements[frontindex+i]=elements[frontindex+i];       //first copy elements from frontindex to the end of array, into the new array,
            }                                                           
            for(unsigned int j = 0;j<frontindex;j++){                   //and move elements that are "pushed" to the beginning of the array.
                newelements[capacity+j] = elements[j];
            }
            backindex = backindex+capacity;                             //set the backindex after the last element in the new array
            capacity = capacity*2;
            delete[] toBeDeleted;
            elements = newelements;
            

        }






    }
    elements[backindex] = x;                                            //add the new element into the backindex of the queue
    backindex = (backindex + 1) % capacity;
} 


// Description:  Removes the frontmost element (O(1))
// Precondition:  Queue not empty
// Postcondition: remove the element from the top of the array.
//                if # of elements becomes less than 1/4 of the capacity, the array changes its size down to half.
template<class ElementType>
void Queue<ElementType>::dequeue() {
    if(elementCount==0){
        throw(EmptyDataCollectionException("dequeue() called with an empty Queue.")); 
    }
    elementCount--;
    if((elementCount < (capacity/4)) && (capacity > INITIAL_CAPACITY)){ //if # of elements is less than 1/4 of capacity and the capacity is not the initial capacity(6),
        ElementType* toBeRemoved = elements;
        ElementType *newelements = new ElementType[capacity/2];         //make dynamically allocated array whose size is half the current array.
        if(frontindex < backindex){                                     // if frontindex < backindex, 
            for(unsigned int i = 0;i<(backindex-frontindex);i++){
                newelements[i] = elements[frontindex+i];                // just copy the elements in order into the new one.

            }
            delete[] toBeRemoved;
            elements = newelements;
            
            backindex = backindex - frontindex;
            frontindex = 0;
            capacity = capacity/2;                                      //half the capacity
        }
        else if(frontindex > backindex){                                //if frontindex > backindex, (this might happen because of the nature of circular array.)

            for(unsigned int i = 0;i<(capacity-frontindex);i++){         //first move all the elements that are sitting from frontindex to the end of array,    
                newelements[i] = elements[frontindex+i];
            }
            for(unsigned int j = 0;j<((elementCount+1)-(capacity-frontindex));j++){ //and move elements that are pushed to the beginning of array into the new array.
                newelements[(capacity-frontindex)+j] = elements[j];
            }
             delete[] toBeRemoved;
            elements = newelements;
           
            frontindex = 0;
            backindex = elementCount+1;
            capacity = capacity/2;

        }



    }
    frontindex = (frontindex + 1) % capacity;
} 


// Description:  Returns a copy of the frontmost element (O(1))
// Precondition:  Queue not empty
// Postconditin: return the value of the first element in the queue
template<class ElementType>
ElementType& Queue<ElementType>::peek() const {
    if(elementCount==0){
        throw(EmptyDataCollectionException("peek() called with an empty Queue.")); 
    }

    return elements[frontindex];
} 


// Description:  Returns true if and only if queue empty (O(1))
template<class ElementType>
bool Queue<ElementType>::isEmpty() const {
    return elementCount == 0;
}
template<class ElementType>
int Queue<ElementType>::getElementCount(){
    return elementCount;
}
