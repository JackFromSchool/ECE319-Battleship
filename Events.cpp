#include "Events.h"

// Initialize Event Queue
EventQueue::EventQueue() {
    // TODO
    PutI = 0;
    GetI = 0;
    lastElement = STARTINGPRESS;
}

// Add event to the queue
bool EventQueue::put(enum Event event) {
    // TODO
    lastElement = event;
    if (full()){
        return false;
    }
    if(PutI == QUEUE_SIZE)
    {
        PutI = 0;
    }
    Buf[PutI] = event;
    PutI++;
    //printf("%d", event);
    return true; 
}

// Get an Event from the queue
bool EventQueue::get(enum Event * event) {
    // TODO
    if (empty()) {
        return false;
    }
    if(GetI == QUEUE_SIZE)
    {
        GetI = 0;
    }
    *event = Buf[GetI];
    GetI++;
    return true;
}

bool EventQueue::full() {
    // TODO
    return ((PutI + 1) % QUEUE_SIZE) == GetI;
}

bool EventQueue::empty() {
    // TODO
    return GetI == PutI;
}

void EventQueue::emptyContents() {
  GetI = PutI;
}

enum Event EventQueue::getLastElement()
{
  return lastElement;
}
/*
Queue::Queue(){
  // Constructor - set PutI and GetI as 0. 
  // We are assuming that for an empty Queue, both PutI and GetI will be equal
    // add code here to initialize on creation
  PutI = 0;
  GetI = 0;
  //Buf[FIFOSIZE];

}

// To check whether Queue is empty or not
bool Queue::IsEmpty(void){
  return GetI == PutI;
}

  // To check whether Queue is full or not
  /*
bool Queue::IsFull(void){
  return ((PutI + 1) % FIFOSIZE) == GetI;
}

  // Inserts an element in queue at rear end
bool Queue::Put(char x)
{
  if (IsFull()){
    return false;
  }
  if(PutI == FIFOSIZE)
  {
    PutI = 0;
  }
  Buf[PutI] = x;
  PutI++;
  return true;
}

  // Removes an element in Queue from front end. 
bool Queue::Get(char *pt){
  if (IsEmpty()) {
    return false;
  }
  if(GetI == FIFOSIZE)
  {
    GetI = 0;
  }
  *pt = Buf[GetI];
  GetI++;
  return true;
}

  /* 
     Printing the elements in queue from front to rear. 
     This function is only to test the code. 
     This is not a standard function for Queue implementation. 

void Queue::Print(void){
    // Finding number of elements in queue  
    // output to ST7735R
    char c;
    while (Get(&c)) {
      printf("%d\n", c);
    }
}
*/
