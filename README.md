# Table Manager

## Description
- An Arduino Library for csv table manipuation on strings made by Divino Fire, https://github.com//divinofire
- Easily manage your csv styled String table



## practical usage
read a small csv styled table from sd card to a String variable  
manipulate the table using this library  
dump the table back into the sd card

## note:
This library does not focuses on reading or writing to an sd card, for that, see arduino examples under **SD**

## installation
Download this project folder into arduino/libaries folder.

## usage
```c++

#include <TableManager.h>


//overall row size <---------------------- 60 ---------------------------------->

//cell size           20 (including ,)           20           20 (including \n) 
//sample table      :-------------------:-------------------:-------------------

String table   =   "id                 ,language           ,rating             \n"
                   "12                 ,lua 19             ,1021               \n" 
                   "13                 ,c++ 17             ,1523               \n";


void setup() {
  Serial.begin(9600);
  
  Serial.println(F("table: ")); Serial.println(table); 
  Serial.println(F("number of rows: ")); Serial.println(countRows(table));
  Serial.println(F("number of columns: ")); Serial.println(countCols(table));
  Serial.println(F("first row: ")); Serial.println(selectRow(0, table));
  Serial.println(F("last row: ")); Serial.println(selectRow(countRows(table)-1, table));
  Serial.println(F("first cell: ")); Serial.println(readData(0,0 ,table));
  Serial.println(F("last cell: ")); Serial.println(readData(countRows(table)-1, countCols(table)-1, table));
  writeData(0,0, "unique key", table); // update first cell
  writeData(countRows(table)-1, countCols(table)-1, "100", table); // update last cell
  writeData(1,2, String(parseNumber(readData(1,2,table))+1) , table); // increment value of cell 1,2
  appendRow(generateEmptyRow(countCols(table)), table); // append empty row to table
  writeData(countRows(table)-1, 1, "others are empty", table); // update middle cell in last column
  Serial.println(F("new table: ")); Serial.println(table);
}

void loop() {
  // put your main code here, to run repeatedly:
}

```

## Quirks:
 1. All cells must be evenly spaced - To minimize the possibility of error,use generateEmptyRow(), appendRow() and writeData() functions to input values to table rather than hard-coding them using appendRow only.
 2. The maximum cell size is 20-1 (19) characters - you can change this value in TableManager.h
 3. row and column indices begin from zero.
 
## Reference - functions
```c++
String selectRow(int rowN, String table); // extract a desired row from a table --> see example of how table must be
void writeData(int rowN, int colN, String xdata, String &table); // update cell data in a table
String readData(int rowN, int colN, String table); // read cell data in a table
int countRows(String table); // count the number of rows in a table
int countCols(String row); // count the number of columns in a row
String generateEmptyRow(int numCols); //generate a right-sized empty row
void appendRow(String row, String& table); // append a row to table
```

*Happy coding!!!*
