# Queue
Queue handling library (designed on Arduino)

This library was designed for Arduino, yet may be compiled without change with gcc for other purporses/targets

## Usage

- Include library with _#include <cppQueue.h>_
- Declare a Queue instance _(uint16_t size_rec, uint16_t nb_recs=20, QueueType type=FIFO, overwrite=false)_ (called _q_ below):
  - size_rec - size of a record in the queue
  - nb_recs - number of records in the queue
  - type - Queue implementation type: _FIFO_, _LIFO_
  - overwrite - Overwrite previous records when queue is full if set to _true_
- Push stuff to the queue using _q.push(void * rec)
  - returns _true_ if succefully pushed into queue
  - returns _false_ is queue is full
- Pop stuff from the queue using _q.pop(void * rec)
  - returns _true_ if succefully popped from queue
  - returns _false_ if queue is empty
- Peek stuff from the queue using _q.peek(void * rec)
  - returns _true_ if succefully peeked from queue
  - returns _false_ if queue is empty
- Drop stuff from the queue using _q.Drop(void)
  - returns _true_ if succefully dropped from queue
  - returns _false_ if queue is empty
- Other methods:
  - q.isEmpty(): _true_ if full, _false_ otherwise
  - q.isFull(): _true_ if empty, _false_ otherwise
  - q.nbRecs(): number of records in the queue
  - q.clean(): resets the queue

## Examples included

- SimpleQueue.ino: Simple queue example (both LIFO FIFO implementations can be tested)
- RolloverTest.ino: Simple test to test queue rollover (for lib testing purposes mainly)
- LibTst.ino: flexible test (for lib testing purposes mainly)

## Misc

Doxygen doc can be generated for the class using doxyfile.

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:

- issues encountered
- optimisations
- improvements & new functionalities
