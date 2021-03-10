#include <ArduinoUnitTests.h>
#include "../src/cppQueue.h"

#define  IMPLEMENTATION  FIFO
#define OVERWRITE    true

#define NB_PUSH      14
#define NB_PULL      11
#define Q_SIZE       10

typedef struct strRec {
  uint16_t  entry1;
  uint16_t  entry2;
} Rec;

unittest(LibTst)
{
  Rec tab[6] = {
    { 0x1234, 0x3456 },
    { 0x5678, 0x7890 },
    { 0x90AB, 0xABCD },
    { 0xCDEF, 0xEFDC },
    { 0xDCBA, 0xBA09 },
    { 0x0987, 0x8765 }
  };

  Queue  q(sizeof(Rec), Q_SIZE, IMPLEMENTATION, OVERWRITE);  // Instantiate queue
  assertEqual(40, q.sizeOf());
  assertEqual(0, q.getCount());

  int i;
  for (i = 0 ; i < NB_PUSH ; i++)
  {
    Rec rec = tab[i % (sizeof(tab)/sizeof(Rec))];
    q.push(&rec);
    assertEqual(min(Q_SIZE, i + 1),       q.getCount());
    assertEqual(max(0, (Q_SIZE - 1) - i), q.getRemainingCount());
    assertEqual((i + 1) >= Q_SIZE,        q.isFull());
  }

  assertFalse(q.isEmpty());
  assertEqual(10, q.getCount());

  for (i = 0 ; i < NB_PULL+1 ; i++)
  {
    // account for the behavior of the test in the example,
    // where at an odd spot we peek instead of pop.
    bool canPop = i <= Q_SIZE;       // note allowance for the peek -- 'i' can be 10
    bool didPeek = i <= NB_PULL / 2; // matches logic of conditional
    int offset = didPeek ? 4 : 3;    // adjust offset in tab
    int idx = (i + offset) % (sizeof(tab)/sizeof(Rec)); // index of tab
    Rec rec = {0xffff,0xffff};
    if (i != NB_PULL / 2)
    {
      assertEqual(canPop, q.pop(&rec));
    }
    else
    {
      assertTrue(q.peek(&rec));
    }

    assertEqual(canPop ? tab[idx].entry1 : 0xffff, rec.entry1);
    assertEqual(canPop ? tab[idx].entry2 : 0xffff, rec.entry2);
  }

  assertTrue(q.isEmpty());
  assertEqual(0, q.getCount());
}


unittest_main()
