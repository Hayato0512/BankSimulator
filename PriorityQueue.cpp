/* 
 * PriorityQueue.cpp
 *
 * Description: Implementation of priority Queue ADT using BinaryMinHeap as CDT
 *              
 * Class invariant: Minimum Binary Heap, therefore smaller value go to the top and bigger go down.              
 * 
 *
 * Author: Hayato Koyama
 * Date: Mar 25, 2022
 */


#include "PriorityQueue.h"
#include "BinaryHeap.h"
#include <iostream>
using namespace std;

//Ctor
template<class ElementType>
PriorityQueue<ElementType>::PriorityQueue()
{    elementCount = 0;
     heap = new BinaryHeap<ElementType>;

}

//Dtor to prevent memory leak
template<class ElementType>
PriorityQueue<ElementType>::~PriorityQueue()
{   
    delete heap;
}

   
    /******* Start of Priority Queue Public Interface *******/

   // Description: Returns "true" if this Priority Queue is empty, otherwise "false".
   // Postcondition: This Priority Queue is unchanged by this operation.
   // Time Efficiency: O(1)
   template<class ElementType>
   bool PriorityQueue<ElementType>::isEmpty() const{
       if(elementCount==0)
        return true;
       return false;
   }

   // Description: Inserts newElement in this Priority Queue and 
   //              returns "true" if successful, otherwise "false".
   //PostCondition: the Event object exists in the heap in the correct position.
    template<class ElementType>
    bool PriorityQueue<ElementType>::enqueue(ElementType& newElement){
        bool ableToEnqueue = false;                 
        ableToEnqueue = heap->insert(newElement);       //call insert() from BinaryHeap
        elementCount++;                                 //increment elementCount;
        return ableToEnqueue;

    }

   // Description: Removes (but does not return) the element with the next
   //              "highest" priority value from the Priority Queue.
   // Precondition: This Priority Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
   template<class ElementType>
   void PriorityQueue<ElementType>::dequeue(){
       try {
            heap->remove();                     //call remove() from BinaryHeap
        }                                       //use try/catch block to detect Exception.
        catch ( EmptyDataCollectionException& anException ) {
            cout<<"detected exception because "<< anException.what()<<endl;
        }
       elementCount--;                          //decrement elementCount;

   }
   
   // Description: Returns (but does not remove) the element with the next 
   //              "highest" priority from the Priority Queue.
   // Precondition: This Priority Queue is not empty.
   // Postcondition: This Priority Queue is unchanged by this operation.
   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
   template<class ElementType>
   ElementType PriorityQueue<ElementType>::peek() const{
        
       try {                                            
            return heap->retrieve();                //call retrieve() from BinaryHeap.
        }
        catch ( EmptyDataCollectionException& anException ) {
            cout<<"detected exception because "<< anException.what()<<endl;
        }
        return heap->retrieve();
   }

   /*
   Below is the print function used to test this program. it is not needed to complete simulator, 
   but if you want to use it, it is here so go ahead.
   */


   /*   template<class ElementType>
   void PriorityQueue<ElementType>::printPriorityQueue() const{
       heap->printHeap();
   }*/
   
   
   
   