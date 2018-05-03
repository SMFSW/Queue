# Queue [![Build Status](https://travis-ci.org/SMFSW/Queue.svg?branch=master)](https://travis-ci.org/SMFSW/Queue)
Queue handling library (designed on Arduino)

This library was designed for Arduino, yet may be compiled without change with gcc for other purporses/targets

## Usage

- Include library with `#include <cppQueue.h>`
- Declare a Queue instance `(uint16_t size_rec, uint16_t nb_recs=20, QueueType type=FIFO, overwrite=false)` (called `q` below):
  - `size_rec` - size of a record in the queue
  - `nb_recs` - number of records in the queue
  - `type` - Queue implementation type: `FIFO`, `LIFO`
  - `overwrite` - Overwrite previous records when queue is full if set to `true`
- Push stuff to the queue using `q.push(void * rec)`
  - returns `true` if successfully pushed into queue
  - returns `false` is queue is full
- Pop stuff from the queue using `q.pop(void * rec)` or `q.pull(void * rec)`
  - returns `true` if successfully popped from queue
  - returns `false` if queue is empty
- Peek stuff from the queue using `q.peek(void * rec)`
  - returns `true` if successfully peeked from queue
  - returns `false` if queue is empty
- Drop stuff from the queue using `q.Drop(void)`
  - returns `true` if successfully dropped from queue
  - returns `false` if queue is empty
- Other methods:
  - `q.IsInitialized()`: `true` if initialized properly, `false` otherwise
  - `q.isEmpty()`: `true` if full, `false` otherwise
  - `q.isFull()`: `true` if empty, `false` otherwise
  - `q.getCount()` or `q.nbRecs()`: number of records in the queue
  - `q.clean()` or `q.flush()`: remove all items in the queue

## Examples included

- [SimpleQueue.ino](examples/SimpleQueue/SimpleQueue.ino): Simple queue example (both LIFO FIFO implementations can be tested)
- [RolloverTest.ino](examples/RolloverTest/RolloverTest.ino): Simple test to test queue rollover (for lib testing purposes mainly)
- [LibTst.ino](examples/LibTst/LibTst.ino): flexible test (for lib testing purposes mainly)

## Documentation

Doxygen doc can be generated for the class using "Doxyfile".

## See also
[cQueue](https://github.com/SMFSW/cQueue) - a C implementation of this library
