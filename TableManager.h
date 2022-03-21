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


#ifndef TABLE_MANGER_H
#define TABLE_MANGER_H

#include <Arduino.h>

#define ENDL '\n'
#define DIL ','
#define EOF '\0'
#define CUSTOM_MAX_BUFFER_SIZE 100
#define STRING_PAD " "
#define CELL_LENGTH 20

int nthCharIndex(char charx, uint8_t positionx, String stream); // get index of the position of nth appearance of a character in a string
String selectRow(int rowN, String table); // extract a desired row from a table --> see example of how table must be
void writeData(int rowN, int colN, String xdata, String &table); // update cell data in a table
String readData(int rowN, int colN, String table); // read cell data in a table
int countRows(String table); // count the number of rows in a table
int countCols(String row); // count the number of columns in a row
void updateString(int index, String data, String& string); //rewrite a portion of a string from a desired index
long parseNumber(String string); //take a string and parse it into a number
void emptyBuffer(char buffer[CUSTOM_MAX_BUFFER_SIZE], uint16_t len); // empty a c buffer
String fitString(String ss, int size); // pad a string with empty spaces to the right till a desired size is gotten
String fitStringN(String ss, int _size); //pad a string with empty spaces to the right till a desired size-1 is gotten, then add '\n' to the end
String fitStringD(String ss, int _size); //pad a string with empty spaces to the right till a desired size-1 is gotten, then add ',' to the end
String generateEmptyRow(int numCols); //generate a right-sized empty row
void appendRow(String row, String& table); // append a row to table
String repeatString(String string, uint8_t ntimes); // repeat a string
//some of these functions are not for users of this library
// but are placed here just in case the user finds some other use for them


#endif // TABLE_MANGER_H
