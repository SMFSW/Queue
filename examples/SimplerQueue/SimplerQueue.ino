/*
  Simpler Queue
  Simpler queue demonstration

  Created: Apr 27, 2022 - by wrybread
  Modified: 
  			- Aug 3, 2022 - Improved by jarboer
			- Jun, 23, 2023 - by jarboer
 */

#include <cppQueue.h>

// Define the structure
typedef struct strRec {
	/* Reduced both char array sizes significantly as they were extremely 
		large and causing the program to not work correctly */
	char url[50];
	char misc1[50];
} Record;

// Create a LIFO queue
cppQueue queue(sizeof(Record), 10, LIFO, false);

void setup() {
	Serial.begin(9600);

	// Create a record and push it
	Record test = { "http://google.com", "some stuff" };
	queue.push(&test);
}

void loop() {
	// Iterate through the queue
	while (!queue.isEmpty()) {
		// Create a record to store the data from the queue
		Record queueRecord;
		queue.pop(&queueRecord);

		// Display the record
		/* Surrounded the String in F() to move it from RAM 
		to the flash memory (which there is more of) */
		Serial.println(F("There's something in the queue!"));
		Serial.println();
		Serial.print(queueRecord.url);
		Serial.print(" ");
		Serial.print(queueRecord.misc1);

		/* NOTE: Using the String class increases the flash memory 
				and RAM usage */
		Serial.println();
		String url = queueRecord.url;
		Serial.print("URL = ");
		Serial.println(url);

		Serial.println();
	}

	delay(1000);
}