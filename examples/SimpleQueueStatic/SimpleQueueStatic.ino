/*
  Simple Queue Static
  Simple queue demonstration using static queue data array
  
  LIFO / FIFO implementations can be tested by changing IMPLEMENTATION

  This example code is in the public domain.

  created 15 November 2022
  by SMFSW
 */

#include <cppQueue.h>

#define	IMPLEMENTATION	LIFO


typedef struct strRec {
	uint16_t	entry1;
	uint16_t	entry2;
} Rec;

Rec tab[6] = {
	{ 0x1234, 0x3456 },
	{ 0x5678, 0x7890 },
	{ 0x90AB, 0xABCD },
	{ 0xCDEF, 0xEFDC },
	{ 0xDCBA, 0xBA09 },
	{ 0x0987, 0x8765 }
};

#define		NB_ITEMS	10

Rec			q_dat[NB_ITEMS];
cppQueue	q(sizeof(Rec), NB_ITEMS, IMPLEMENTATION, false, q_dat, sizeof(q_dat));	// Instantiate queue with static queue data arguments

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
	unsigned int i;
	
	for (i = 0 ; i < sizeof(tab)/sizeof(Rec) ; i++)
	{
		Rec rec = tab[i];
		q.push(&rec);
	}
	
	for (i = 0 ; i < sizeof(tab)/sizeof(Rec) ; i++)
	{
		Rec rec;
		q.pop(&rec);
		Serial.print(rec.entry1, HEX);
		Serial.print(" ");
		Serial.println(rec.entry2, HEX);
	}
	
	while(1);
}
