# Author: Paolo Di Prodi
# email: paolo@robomotic.com
# Copyright 2013 Robomotic ltd

/*
This file is part of Various Google Challenges.

Various Google Challenges is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Various Google Challenges is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar. If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <vector>
#include <stdexcept>      // std::out_of_range

// Boost header needed:
#include <boost/lexical_cast.hpp>



#define C11

#ifdef C11
//Various method to convert integers to string
void integer_to_string()
{
    int number = 123;
    string text = to_string(number);
    cout<<endl;
    cout<<"Conversion of 123 to string is "<<text<<endl;
    text=text+'1';
    number = stoi(text);
    cout<<"Conversion of "<<text<<" to int "<<number<<endl;

    // Number to string conversion:
    text = boost::lexical_cast<string>(number);

    // String to number conversion:
    number = boost::lexical_cast<int>(text);

}
#endif

/*
void looping()
{

Looping through the characters of a std::string, using a range-based for loop (it's from C++11,
 already supported in recent releases of GCC, clang, and the VC11 beta):
std::string str = ???;
for(char& c : str) {
    do_things_with(c);
}


Looping through the characters of a std::string with an old-fashioned for-loop:
for(std::string::size_type i = 0; i < str.size(); ++i) {
    do_things_with(str[i]);
}
Looping through the characters of a null-terminated character array:
char* str = ???;
for(char* it = str; *it; ++it) {
    do_things_with(*it);
}

}

*/



//Separate a string for example AABBCC::DD:R::AAAA
// Output a vector with {AABBCC,DD,R,AAAA}
vector<string> split(const string &input,const string &separator)
{
    vector<string> output;
    string temporary="";
    string current=input;
    int token_size=separator.length();
    int temp_size=0;
    if(input.length()>0)
    {

        for(std::string::const_iterator it = input.begin(); it != input.end(); ++it)
        {
            //attach at the end
            temporary=temporary+*it;
            temp_size++;
            //check if the last elements in the "stack" are equal to teh separator
            if(temp_size>=token_size)
            {
                try
                {
                    std::string candidate = temporary.substr(temp_size-token_size);
                    if(candidate==separator)
                    {
                        output.push_back(temporary.substr(0,temp_size-token_size));
                        temporary="";
                        temp_size=0;

                    }
                }
                catch (const std::out_of_range& oor)
                {
                    std::cerr << "Out of Range error: " << oor.what() << '\n';
                }
            }

        }
        //flush the last elements as usual!
        if(temp_size>0)
            output.push_back(temporary);
    }
    return output;
}

/*
* Input: AAAABBCC
* Output:4A2B2C
*/
string compress_naive_for(const string &input)
{
    char last_char=0x00;
    int last_count=0;
    string output="";
    if(input.length()>0)
    {
        for(char c : input)
        {
            if(last_char==0x00)
            {
                last_char=input[0];
                last_count=1;
            }
            else if(c == last_char)
            {
                last_count++;
            }
            else if(c!= last_char)
            {
                output=output+to_string(last_count)+last_char;
                last_char=c;
                last_count=1;
            }
        }//end for
        //flush out the stuff if last char left
        if(last_count>0)
            output=output+to_string(last_count)+last_char;

    }
    return output;

}
void test_naive()
{
    string test1="ABCD";
    cout<<"\nCompress "<<test1<<endl;
    cout<<compress_naive_for(test1);

    string test2="A";
    cout<<"\nCompress "<<test2<<endl;
    cout<<compress_naive_for(test2);

    string test3="AAAA";
    cout<<"\nCompress "<<test3<<endl;
    cout<<compress_naive_for(test3);

    string test4="AABBC";
    cout<<"\nCompress "<<test4<<endl;
    cout<<compress_naive_for(test4);

    string test5="AABB;;CC;;DD";
    cout<<"\nSplitting "<<test5<<endl;
    vector<string> result=split(test5,";;");
    for(string s: result)
    {
        cout<<s<< " ";
    }
    cout<<endl;

    string test6="AABB;;CC;;DD;EF";
    cout<<"\nSplitting "<<test6<<endl;
    result=split(test6,";;");
    for(string s: result)
    {
        cout<<s<< " ";
    }
    cout<<endl;
}
#endif // ALGORITHM_H_INCLUDED
