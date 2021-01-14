/*
  Serial Queue
  Serial queue demonstration

  Print characters received from Serial to Serial after reception of EOT char

  This example code is in the public domain.

  created 14 Jan 2021
  by SMFSW
 */

#include <cppQueue.h>

#define	MAX_LENGTH		50
#define	EOT_CHAR		';'		// Contents will be written to serial upon End Of Transmission character reception

// Instantiate queue (with possible overwriting to ensure treatment of EOT_CHAR even if message longer than queue)
cppQueue	q(sizeof(char), MAX_LENGTH, FIFO, true);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
	/*** RECEPTION ***/
	if (Serial.available())					// Ensure Serial is available
	{
		char rcv = (char) Serial.read();	// Read char from Serial

		if (rcv != -1)						// If no character received: -1 (do not push)
		{
			q.push(&rcv);					// Push char to cppQueue
		}
	}

	/*** cppQueue HANDLING ***/
	// Note, as characters are get sequentially one by one from Serial before cppQueue handling,
	// no particular care has to be taken for more characters available in serial buffer
	if (!q.isEmpty())				// Only if q is not empty
	{
		char snd;
		q.peekPrevious(&snd);
		if (snd == EOT_CHAR)		// Only if end of transmission character is received
		{
			String str;
			while (q.pop(&snd))		// While characters are available in q
			{
				str += snd;
			}
			Serial.println(str);
		}
	}
}