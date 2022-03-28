/* 
 * PriorityQueue.h
 *
 * Description: Implementation of priority Queue ADT using BinaryMinHeap as CDT
 *              
 * Class invariant: Minimum Binary Heap, therefore smaller value go to the top and bigger go down.              
 * 
 *
 * Author: Hayato Koyama
 * Date: Mar 25, 2022
 */



#include "BinaryHeap.h"
#include "Event.h"
#pragma once
template<class ElementType>
class PriorityQueue
{
public:
 /******* Start of Priority Queue Public Interface *******/
    PriorityQueue();
    ~PriorityQueue();
   


// Description: Inserts newElement in this Priority Queue and 
   //              returns "true" if successful, otherwise "false".
   bool enqueue(ElementType& newElement);


   // Description: Returns "true" if this Priority Queue is empty, otherwise "false".
   // Postcondition: This Priority Queue is unchanged by this operation.
   // Time Efficiency: O(1)
   bool isEmpty() const;

   

   // Description: Removes (but does not return) the element with the next
   //              "highest" priority value from the Priority Queue.
   // Precondition: This Priority Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
   void dequeue();
   
   // Description: Returns (but does not remove) the element with the next 
   //              "highest" priority from the Priority Queue.
   // Precondition: This Priority Queue is not empty.
   // Postcondition: This Priority Queue is unchanged by this operation.
   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
   ElementType peek() const;  
   

 
/*******  End of Priority Queue Public Interface *******/

private:
    int elementCount;
    BinaryHeap<ElementType>* heap;

    
};
#include "PriorityQueue.cpp"

