 /*
 Table manager
 do basic table manipulations on a string
 
 DIVINO-FIRE, a github user.
 20th of March, 2022.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software...
 to deal in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <Arduino.h>
#include "TableManager.h"


//----------------get index of the nth appearance of character in stream ---------------------
//warning: positionx starts from 1
int nthCharIndex(char charx, uint8_t positionx, String stream){
  int counterx = 0;
  int posCount = 0;
  for (auto i:stream){
    if (i==charx) posCount++;
    if (posCount == positionx)  return counterx; 
    counterx++;   
  }
  return -1;
}


//----------------------------select the nth Row in Table-----------------------------------
String selectRow(int rowN, String table){
  
  String row = "";
  int start = 0, stop = 0;

  // select index of line start
  if (rowN > 0) start = nthCharIndex(ENDL, rowN, table);
  else {start = -1;}
  // Serial.print("start: "); Serial.println(start);
  // select index of line stop
  stop = nthCharIndex(ENDL, rowN+1, table);
   //Serial.print("stop: "); Serial.println(stop);
  int j=0;
  for(auto i : table){
    if ((j>start) and (j<=stop)) {row += String(i);}
    //Serial.print(j);Serial.print(" row: "); Serial.println(row);
    j++;
  }

  return row;
  
}


//-----------------------------------------------write data-------------------------------------------------
void writeData(int rowN, int colN, String xdata, String &table){
 String row = selectRow(rowN, table);
 int numCols = countCols(row);
 
 int start = 0, stop=0;
 int j=0;
 //String newRow = "";
 String newData = "";

//select start of column index
 start = nthCharIndex(DIL, colN, row);

//----------fix extreme conditions------
//if the user wishes to select for example cell [0,0], set start before 0 index
  if (colN==0) start=-1; 
  
  if (colN == (numCols-1)) newData = fitStringN(xdata, CELL_LENGTH);
  else newData = fitStringD(xdata, CELL_LENGTH);

  //writing in row from start to stop
  updateString(start+1, newData, row);

  //write new row to table
  int index = CELL_LENGTH*numCols*rowN;
  updateString(index, row, table);
}

//----------------------------count rows in table  ------------------------------------------------
int countRows(String table){
  int rows = 0;
  for (auto i: table){
    if (i == ENDL) rows++;
  }
  return rows;
}

//----------------------------get the number of Columns in a row --------------------------
int countCols(String row){
  String rowx = selectRow(0, row);
  int cols = 0;
  for (auto i: rowx){
     if ((i == DIL) or (i == ENDL))cols++;
    }
  return cols;
 }

void updateString(int index, String data, String& string){
    int j=0;
    for (int i = 0; i<string.length(); i++){
        if (i>=index){
          string[i] = data[j]; 
          j++;
          if (data.length()==j) return;
          }
      }
  }

long parseNumber(String string){
  string.trim();
  return string.toInt();
  }

  //-------------------------------------------read data---------------------------------------
String readData(int rowN, int colN, String table){

     String row = selectRow(rowN, table);
     int numCols = countCols(row);
     
     
     String data = "";
     int start = 0, stop=0;
     int j=0;
     
    start = nthCharIndex(DIL, colN, row);
    stop = nthCharIndex(DIL, colN+1, row);

    //read from start to stop
    //------------------fix extreme conditions-----------------------
    
    if (colN==0) start = -1; //if the user wishes to select for example cell [0,0], set start before 0 index
    //if the user selects a column that marks the end of a line, get stop to be the position of '\n' instead of ','
    else if (colN==(numCols-1)) stop = nthCharIndex(ENDL, 1, row);

    j=0;
    for(auto i : row){
      if ((j>start) and (j<stop)) {data += String(i);}
      j++;
    }
    return data;
 }

 //----------------------------empty a buffer------------------------------------------------
 void emptyBuffer(char buffer[CUSTOM_MAX_BUFFER_SIZE], uint16_t len){
    memset(buffer, 0, len);
  }


  //----------------------------fit String  ------------------------------------------------
//add space or remove chars till size is met
String fitString(String ss, int size){
        String s = ss;
       if (s.length()==size) return s;
       while (s.length()!= size){
          if (s.length( )> size) s.remove(s.length( )-1);
          else if (s.length()>size) s += " ";
          
        }
        return s;
  }

//----------------------------fit String N ------------------------------------------------
//format data cell in the last column: add space or remove chars till size is met
// add "\n" after that
String fitStringN(String ss, int _size){
      String s = ss;
       int size = _size-1;
       if (s.length()==size) return s;
       while (s.length()!=size){
          if (s.length()> size) s.remove(s.length()-1);
          else if (s.length()<size) s += STRING_PAD;
     }
      s += ENDL;
      return s;
      
  }
  
//----------------------------fit String D ------------------------------------------------
//format data cell not in the last column: add space or remove chars till size is met
// add ", " after that
String fitStringD(String ss, int _size){
      String s = ss;
       int size = _size-1;
       if (s.length()==size) return s;
       while (s.length()!=size){
          if (s.length( )> size) s.remove(s.length( )-1);
          else if (s.length()<size) s += STRING_PAD;
      }
      s += DIL;
      return s;
      
  }

  String generateEmptyRow(int numCols){
      String emptyCell = repeatString(" ", CELL_LENGTH-1); // empty cell data
      String emptyRow = emptyCell + DIL; // empty cell
      emptyRow = repeatString(emptyRow, numCols-1); // empty row with last cell
      emptyRow += (emptyCell + ENDL); // complete empty row
      return emptyRow;
  }

  void appendRow(String row, String& table){
    table+=row;
  }

  String repeatString(String string, uint8_t ntimes){
      
      String repeatedString = string;
      for (int i = 0; i < ntimes-1; ++i)
      {
        repeatedString+=string;
      }

      return repeatedString;
  }