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
- Push stuff to the queue using q.push(void * rec)
  - returns _true_ if successfully pushed into queue
  - returns _false_ is queue is full
- Pop stuff from the queue using q.pop(void * rec) or q.pull(void * rec)
  - returns _true_ if successfully popped from queue
  - returns _false_ if queue is empty
- Peek stuff from the queue using q.peek(void * rec)
  - returns _true_ if successfully peeked from queue
  - returns _false_ if queue is empty
- Drop stuff from the queue using q.Drop(void)
  - returns _true_ if successfully dropped from queue
  - returns _false_ if queue is empty
- Other methods:
  - q.IsInitialized(): _true_ if initialized properly, _false_ otherwise
  - q.isEmpty(): _true_ if full, _false_ otherwise
  - q.isFull(): _true_ if empty, _false_ otherwise
  - q.getCount() or q.nbRecs(): number of records in the queue
  - q.clean() or q.flush(): remove all items in the queue

## Examples included

- SimpleQueue.ino: Simple queue example (both LIFO FIFO implementations can be tested)
- RolloverTest.ino: Simple test to test queue rollover (for lib testing purposes mainly)
- LibTst.ino: flexible test (for lib testing purposes mainly)

## Documentation

Doxygen doc can be generated for the class using "Doxyfile".

## License

The MIT License (MIT)

Copyright (c) 2017-2018 SMFSW (Sebastien Bizien)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
