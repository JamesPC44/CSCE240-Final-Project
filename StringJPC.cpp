/***************************************************************************
 * File: String.cpp
 * Author: James Coman
 * Function: methods and constructors for a custom string class
 * Input: char arrays
 * Output: string object                                         *
 ***************************************************************************/
#include<cstdlib>
#include<iostream>
#include "String.h"

String::String()
{   
  data = NULL;//data = new char[0];
  _length = 0;
}//Default constructor allocates no memory

String::String(int size)
{   
  _length = size;
  data = new char[size];
}//alternate constructor allocates appropriately sized block of memory

String::String(char str[])
{
  _length = getCharArraySize(str);
  data = new char[_length];
  for(int i = 0; i < _length; i++)
  {
    data[i] = str[i];//could use *(data+i)   
  }
}//creates array of needed size and fills with passed array

String::String(const String &two)
{
  _length = two.length();
  data = new char [_length];
  for (int i = 0; i < _length; i++)
  {
    data[i] = two.data[i];
  }
}//copy constructor creates identical String

String::~String()
{
  delete [] data;
}//Frees memory allocated for the String

int String::getCharArraySize(char arr[])const//array passed will have term character
{
  int size(0);
  for(int i = 0; arr[i] !='\0'; i++)
  {
    size++;
  }
  return size;
}//finds size of array dependent on term character.

//void String::set_length(int size)
//{
//  if(size >=0)
//  {
//    _length = size;
//  }
//  else
//  {
//     cout << "Invalid size" << endl;
//     exit(0);
//  }
//}//TODO use this?

int String::length() const
{
  return _length;
}//TODO functions as getter too?

ostream & operator<<(ostream &outStream, const String &two)
{
  if(two.length() == 0)
  {
    outStream << "NULL" << endl;
  }
  else
  {
    for(int i = 0; i < two.length(); i++)
    {
      outStream << two[i];
    }//iterates through and prints
    outStream << endl;
  }
  return outStream;
}//overrides << operator to ostream for printing

bool String::empty() const
{
  if(_length == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int String::find(char substr[], int startIndex) const
{
  int pos(-1);//absurd value used to check
  if(startIndex >= _length || startIndex < 0)
  {
    return pos;
  }
  for(int i = startIndex; i < _length; i++)
  {
    if(data[i]==substr[0])
    {
      for(int j = 1; j < getCharArraySize(substr); j++)
      {
        if(data[i+j] != substr[j])
        {
          pos = -1;
          break;//mismatch breaks loop
        }
        else
        {
          pos = i;//updated position
        }
      }
      if(pos != -1)
      {
        return pos;
      }
    }
  }
  return pos;//indicates not found
}//this does not work how it should

char String::operator[](int index) const
{
  if(index < _length && index >= 0)
  {
    return data[index];
  }
  else
  {
    cout << "Reference is beyond string." << endl;//TODO how handle exception?
    return '\0';//prevents memory leak
  }
}

bool String::operator==(const String &two) const
{
  if (_length == two.length())//lengths must match to be equal
  {
    for(int i = 0; i < _length; i++)
    {
      if(data[i] != two[i])
      {
        return false;
      }//checks characters to match
    }
    return true;
  }
  else
  {
    return false;
  }
}

void String::clear()//TODO better to return string?
{
  delete [] data;
  data = NULL;
  _length = 0;
}

String String::operator=(const String &two)
{//TODO make this better
  String tempS(two.length());
  _length = two.length();
  char *temp = new char[_length];//creates new array
  for(int i = 0; i < _length;i++)
  {
   tempS.data[i] = temp[i] = two[i];
  }//copies String data
  delete[] data;
  data = temp;//data is reassigned to the new array
  return tempS;
}

String String::operator+(const String &two)const
{
  String temp(_length + two.length());//new String made
  for (int i = 0; i < _length; i++)
  {
    temp.data[i] = data[i];
  }//this data moved in
  for (int i = 0; i < two.length(); i++)
  {
    temp.data[_length + i] = two[i];
  }//passed data moved in
  return temp;
}

void String::print() const
{//TODO call << ??
  if(_length == 0)
  {
    cout << "NULL" << endl;
  }
  else
  {
    for(int i = 0; i < _length; i++)
    {
      cout << data[i];
    }//iterates through and prints
    cout << endl;
  }
}

char String::at(int index) const
{
  //return this[index]//TODO why does this not work?
  if(index < _length && _length >= 0)//checks if index is in bounds
  {
     return data[index];
  }
  else
  {
    cout << "Reference is beyond string" << endl;//TODO how handle exception?
    exit(0);
  }
}

bool String::equal(const String &two) const
{
  //this==two;//TODO why does this not work
  if (_length == two.length())//lengths must match to be equal
  {
    for(int i = 0; i < _length; i++)
    {
      if(data[i] != two.at(i))
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool String::add(const String &two)
{//TODO any way to call other method?
  char *temp = new char[_length+two.length()];//new array
  for (int i = 0; i < _length; i++)
  {
    temp[i] = data[i];
  }//this data moved in
  for (int i = 0; i < two.length(); i++)
  {
    temp[_length + i] = two[i];
  }//passed data moved in
  delete[] data;//derefernence old array
  data = temp;//point to new memory
  return true;//this is unideal practice
}
