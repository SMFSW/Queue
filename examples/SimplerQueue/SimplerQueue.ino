/*
  Simpler Queue
  Simpler queue demonstration

  Created: Apr 27, 2022 - by wrybread
*/

#include <cppQueue.h>

typedef struct strRec {
  char  url[300];
  char  misc1[255];
} Rec;

cppQueue  queue1(sizeof(Rec), 10, LIFO, true); 

void setup() {
  Serial.begin(115200); 
  
  // Put a sample record into the queue
  Rec test = {"http://google.com", "some stuff"};
  queue1.push(&test);

}

void loop() {  

  // iterate through the queue
  while (!queue1.isEmpty())
  {
    Rec rec;
    queue1.pop(&rec);
    Serial.println("There's something in the queue!");
    Serial.println();
    Serial.print(rec.url);
    Serial.print(" ");
    Serial.print(rec.misc1);

    Serial.println();
    String url = rec.url;
    Serial.println("URL = " + url);
    
    Serial.println();
  }   
  delay(1000);
}