// HapticKnob.cpp
/*
  HapticKnob library for Arduino 
  Written by Lorenzo Cavalieri, PhD Student at UNIVPM (Italy)
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "HapticKnob.h"

HapticKnob::HapticKnob(int OK, int BACK, int Encoder1, int Encoder2, BraillePad &BPad) {

DeltaR = 1; //not used: Default value
RotFlag = -1;
ButtonFlag = -1;
ViewID = 1;

OKpin = OK;
BACKpin = BACK;
Encoder1pin = Encoder1;
Encoder2pin = Encoder2;

pinMode(OKpin, INPUT);
pinMode(BACKpin, INPUT);
pinMode(Encoder1pin,INPUT);
pinMode(Encoder2pin,INPUT);
pinMode(13,OUTPUT); // Notification LED

if (&BPad) BP = &BPad;

//Caricamento del database
  db_screen.create(IDX_TBL, sizeof(idx));  
  db_screen.open(IDX_TBL);
  
    //------- START DATABASE LOADING ------------//
  // Recording data on database
  // ok - back - next - previous
  //HOME
  createRecord(db_screen,5,1,2,4);     //ID:1 *
  createRecord(db_screen,14,2,3,1);    //ID:2 *
  createRecord(db_screen,3,3,4,2);     //ID:3 * *
  createRecord(db_screen,9,4,1,3);     //ID:4 *
  //Experience
  createRecord(db_screen,40,1,6,8);    //ID:5
  createRecord(db_screen,6,1,7,5);     //ID:6 *
  createRecord(db_screen,7,1,6,8);     //ID:7 *
  createRecord(db_screen,8,1,5,7);     //ID:8 *
  //Standard
  createRecord(db_screen,17,4,10,13);  //ID:9
  createRecord(db_screen,21,4,9,11);   //ID:10
  createRecord(db_screen,25,4,10,12);  //ID:11
  createRecord(db_screen,12,4,11,13);  //ID:12 *
  createRecord(db_screen,29,4,9,12);   //ID:13
  //Setup
  createRecord(db_screen,14,2,15,16);   //ID:14 *
  createRecord(db_screen,15,2,16,14);   //ID:15 *
  createRecord(db_screen,16,2,14,15);   //ID:16 *
  //Doccia
  createRecord(db_screen,17,9,18,20);   //ID:17 *
  createRecord(db_screen,21,9,19,17);   //ID:18
  createRecord(db_screen,19,9,20,18);   //ID:19 *
  createRecord(db_screen,20,9,17,19);   //ID:20 *
  //Musica
  createRecord(db_screen,36,10,22,24);   //ID:21
  createRecord(db_screen,22,10,23,21);   //ID:22 *
  createRecord(db_screen,23,10,24,22);   //ID:23 *
  createRecord(db_screen,24,10,21,23);   //ID:24 *
  //Luci
  createRecord(db_screen,9,11,26,28);   //ID:25
  createRecord(db_screen,9,11,27,25);   //ID:26
  createRecord(db_screen,9,11,28,26);   //ID:27
  createRecord(db_screen,9,11,25,27);   //ID:28
  //Acqua
  createRecord(db_screen,9,13,30,35);   //ID:29
  createRecord(db_screen,9,13,31,29);   //ID:30
  createRecord(db_screen,9,13,32,30);   //ID:31
  createRecord(db_screen,9,13,33,31);   //ID:32
  createRecord(db_screen,9,13,34,32);   //ID:33
  createRecord(db_screen,9,13,35,33);   //ID:34
  createRecord(db_screen,9,13,29,34);   //ID:35
  
  //Playlist
  createRecord(db_screen,9,21,37,39);   //ID:36
  createRecord(db_screen,9,21,38,36);   //ID:37
  createRecord(db,9,21,39,37);   //ID:38
  createRecord(db,9,21,36,38);   //ID:39
  
  //Ex PLalist
  createRecord(db_screen,44,5,41,43);   //ID:40
  createRecord(db_screen,44,5,42,40);   //ID:41
  createRecord(db_screen,44,5,43,41);   //ID:42
  createRecord(db_screen,44,5,40,42);   //ID:43
  
  //Ex doccia
  createRecord(db_screen,44,40,45,47);   //ID:44 *
  createRecord(db_screen,5,40,46,44);   //ID:45
  createRecord(db_screen,44,40,47,45);   //ID:46 *
  createRecord(db_screen,44,40,44,46);   //ID:47 *
  //------- END DATABASE LOADING ---------------//
}

void HapticKnob::SetGlobalParameter (int  butFlag,int rotFlag, int deltaR){
ButtonFlag = butFlag;
RotFlag = rotFlag;
DeltaR = deltaR;
}

int HapticKnob::GetViewID(int viewID,int buttonFlag, int rotFlag, int deltaR){

  int i=0;
  int columnTable = -1;
  Serial.print("rotFlag: ");
  Serial.println(rotFlag);
  Serial.print("buttonFlag: ");
  Serial.println(buttonFlag);
  switch (rotFlag) {
    case 0:
    columnTable = 3;
    break;
    case 1:
    columnTable = 2;
    default:
    columnTable = buttonFlag;
    break;
  }
  Serial.print("columnTable: ");
  Serial.println(columnTable);
  db_screen.read(viewID, DB_REC idx);
 
   switch (columnTable) {
     case 0:
     //DEBUG MODE
     Serial.print("new ID: ");
	 Serial.print(idx.ok);
	 Serial.println(" - OK");
	 Serial.println("----------");
	 //---------------------
     return idx.ok;
     
     break;
     case 1:
     //DEBUG MODE
     Serial.print("new ID: ");
	 Serial.print(idx.ok);
	 Serial.println(" - BACK");
	 Serial.println("----------");
	 //---------------------
     return idx.back;
     break;
     case 2:
     //DEBUG MODE
     Serial.print("new ID: ");
	 Serial.print(idx.ok);
	 Serial.println(" - NEXT");
	 Serial.println("----------");
	 //---------------------
     return idx.next;
     case 3:
     //DEBUG MODE
     Serial.print("new ID: ");
	 Serial.print(idx.ok);
	 Serial.println(" - PREVIOUS");
	 Serial.println("----------");
	 //---------------------
     return idx.previous;
     break;
   }


}

int HapticKnob::getCurrentViewID(){
return ViewID;
}
//DB support
void HapticKnob::createRecord (DB &db,int ok, int back, int next, int prev){
idx.ok = ok;
idx.back = back;
idx.next = next;
idx.previous = prev;

db_screen.append(DB_REC idx);
}

//Management Routine of Knob
void HapticKnob::OK_ButtonRoutine(){
    digitalWrite(13,HIGH);
    SetGlobalParameter (0,-1,0);
    ViewID = GetViewID(ViewID, ButtonFlag, RotFlag,DeltaR);
    Serial.write(ViewID);
    
   if (BP) BP->writeSequence("OK",3);

   delay(DELAY_INTERACTION); //Delay to avoid repeated trasmission
   digitalWrite(13,LOW);
}

void HapticKnob::BACK_ButtonRoutine(){
   digitalWrite(13,HIGH);
   SetGlobalParameter (1,-1,0);
   ViewID = GetViewID(ViewID, ButtonFlag, RotFlag,DeltaR);
   Serial.write(ViewID);
  
   if (BP) BP->writeSequence("BACK",5);
  
   delay(DELAY_INTERACTION); //Delay to avoid repeated trasmission
   digitalWrite(13,LOW);

}

void HapticKnob::doEncoder1(){

digitalWrite(13,HIGH);
int flag=-1;
int delta=0;
  // look for a low-to-high on channel A
  if (digitalRead(Encoder1pin) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(Encoder2pin) == LOW) {  
      delta++;         // CW
      flag=1;
    } 
    else {
      delta--;         // CCW
      flag=0;
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(Encoder2pin) == HIGH) {   
      delta++;          // CW
      flag=1;
    } 
    else {
      delta--;          // CCW
      flag=0;
      
    }
  }
    
    delta=delta%DeltaGranularity;
    SetGlobalParameter (-1,flag,delta);
    ViewID = GetViewID(ViewID, ButtonFlag, RotFlag,DeltaR);
    Serial.write(ViewID);
    
    //Braille Writing
    if (RotFlag==1) 
    {
    if (BP) BP->writeSequence("NEXT",5);
    }
    else
    {
    if (BP) BP->writeSequence("PREV",5);
    }
	delay(DELAY_INTERACTION);
    digitalWrite(13,LOW);
}

void HapticKnob::doEncoder2(){
digitalWrite(13,HIGH);
int flag=-1;
int delta=0;
  // look for a low-to-high on channel B
  if (digitalRead(Encoder2pin) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(Encoder1pin) == HIGH) {  
      delta++;         // CW
      flag=1;
    } 
    else {
      delta--;         // CCW
      flag=0;
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(Encoder2pin) == LOW) {   
      delta++;          // CW
      flag=1;
    } 
    else {
     delta--;          // CCW
     flag=0;
    }
  }

    delta=delta%DeltaGranularity;
    SetGlobalParameter (-1,flag,delta);
    ViewID = GetViewID(ViewID, ButtonFlag, RotFlag,DeltaR);
    Serial.write(ViewID);
    
    //Braille Writing
    if (RotFlag==1) 
    {
		if (BP) BP->writeSequence("NEXT",5);
    }
    else
    {
		if (BP) BP->writeSequence("PREV",5);
    }
	delay(DELAY_INTERACTION);
    digitalWrite(13,LOW);
}