/*
 * BankSimApp.cpp
 *
 * Description: Event-driven Bank Simulation application.
 *              This analize the performance of a bank with specific samples of customers arriving time.
 *              
 * Class invariant: input must be a sequence of integer separated by white space
 * 					
 *
 * Author: Hayato Koyama
 * Last Modified: March 25, 2022
 */



#include "BinaryHeap.h" 
#include "PriorityQueue.h"
#include <iostream>
#include "Event.h"
#include "Queue.h"
#include "EmptyDataCollectionException.h"
using namespace std;

int waitingTimeTotal = 0;  //to keep track of total waiting time. at last, it will be used to calculate average waiting time of customers.

void processArrival(Event& newEvent,PriorityQueue<Event>& eventPriorityQueue,Queue<Event>& bankLine, bool& tellerAvailable, int currentTime){
    eventPriorityQueue.dequeue();   
    
    Event customer = newEvent;              //get the customers information
    if(bankLine.isEmpty() && tellerAvailable){      //if there is no line and the teller is available, the customer recieve service right away
        cout<<"Processing an arrival event at time:    "<<customer.getTime()<<endl;
        int departureTime = newEvent.getTime() + newEvent.getLength();      //calculate when the customer leaves by adding currentTime and transaction length
        Event newDepartureEvent(Event::DEPARTURE, departureTime);           //make a new departure object to keep track of departure time of this customer
        eventPriorityQueue.enqueue(newDepartureEvent);                      
        tellerAvailable = false;                                            //now teller is unavailable
    }
    else{                                                                   //if there is a line or teller is unavailable , the customer goes to bankLine to wait
        cout<<"Processing an arrival event at time:    "<<currentTime<<endl;    
        bankLine.enqueue(customer);

    }
}

void processDeparture(Event& newEvent,PriorityQueue<Event>& eventPriorityQueue,Queue<Event>& bankLine, bool& tellerAvailable, int currentTime){
    cout<<"Processing a departure event at time:   "<<currentTime<<endl;
    eventPriorityQueue.dequeue();
    Event customer;
    if(!(bankLine.isEmpty())){                      //if bankline is not empty, get the front customer from the line
        try {
            customer = bankLine.peek();
        }
        catch ( EmptyDataCollectionException& anException ) {
            cout<<"detected exception because "<< anException.what()<<endl;
        }
       
        try {
            bankLine.dequeue();
        }
        catch ( EmptyDataCollectionException& anException ) {
            cout<<"detected exception because "<< anException.what()<<endl;
        }
        
        waitingTimeTotal += newEvent.getTime() - customer.getTime();    //calculate how long this new customer waited on the line
        int departureTime = currentTime + customer.getLength();         //calculate when this new customer leaves
        Event newDepartureEvent(Event::DEPARTURE, departureTime);       //make a new departure objects and enqueue into priority queue
        eventPriorityQueue.enqueue(newDepartureEvent);

    }
    else{
        tellerAvailable = true;                                         
    }
}


int main(){
    cout<<"Simulation Begins "<<endl;
    Queue<Event> bankLine;
    PriorityQueue<Event> eventPriorityQueue;

    bool tellerAvailable = true;
    int time;
    int length;
    float numberOfCustomers = 0;
    while (std::cin >> time >> length){                 //read input data until its end
        Event e(Event::ARRIVAL, time, length);          //and create Event objects with the given data
        eventPriorityQueue.enqueue(e);
        numberOfCustomers++;                            //keep track of # of customers.
         }
    

    while(!(eventPriorityQueue.isEmpty())){             
        Event newEvent = eventPriorityQueue.peek();     //get the most prioritized customer infomation

        int currentTime = newEvent.getTime();           //set the time from their arrivaltime

        if(newEvent.getType()== Event::ARRIVAL){        //if the Type is ARRIVAL,
            processArrival(newEvent,eventPriorityQueue,bankLine, tellerAvailable, currentTime); //process arival
        }
        else{
            processDeparture(newEvent,eventPriorityQueue,bankLine, tellerAvailable, currentTime); //process departure
        }
    }
    cout<<"Simulation Ends\n"<<endl;

    float averageWaitingTime = waitingTimeTotal/numberOfCustomers;  //calculate averageWaitingTime

    cout<<"Final Statistics: "<<endl<<endl;                         //summary of the performance of a bank 
    cout<<"    Total number of people processed: "<<numberOfCustomers<<endl;
    cout<<"    Average amount of time spent waiting: "<< averageWaitingTime<<endl<<endl;
    
    

}



