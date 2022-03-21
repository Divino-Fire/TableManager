/*
 example stringTable manipulation
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
