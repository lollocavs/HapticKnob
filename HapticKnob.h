// HapticKnob.h
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

#ifndef HAPTICKNOB_H
#define HAPTICKNOB_H

#include <EEPROM.h>
#include "DB.h"
#include "BraillePad.h"

#define IDX_TBL 1
#define DELAY_INTERACTION 200
struct IDX {
  int ok;
  int back;
  int next;
  int previous;
};

class HapticKnob {

public:
HapticKnob(int OK, int BACK, int Encoder1, int Encoder2, BraillePad &BPad);
~HapticKnob() {delete BP;}
void SetGlobalParameter (int  butFlag,int rotFlag, int deltaR);
int GetViewID(int viewID,int buttonFlag, int rotFlag, int deltaR);

//Management Routine of Knob
int getCurrentViewID();
void OK_ButtonRoutine();
void BACK_ButtonRoutine();
void doEncoder1();
void doEncoder2();
//DB support
void createRecord (DB &db,int ok, int back, int next, int prev);

//POSIZIONE PROVVISORIA PER NON RISCRIVERE LE FUNZIONI DI RACCORDO
BraillePad *BP;
IDX idx;
DB db_screen;

private:
int DeltaR; //not used: Default value
int DeltaGranularity=5;
int RotFlag;
int ButtonFlag;
int ViewID;
int ViewID_prev;
//Pins
int OKpin;
int BACKpin;
int Encoder1pin;
int Encoder2pin;

};
#endif