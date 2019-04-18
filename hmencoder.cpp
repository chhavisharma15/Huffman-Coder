/**
 * Written by - Chhavi Sharma
 * UID - 3035452599
 * Code is written in C++11
 * Compiled with: g++ -std=c++11 hmencoder.cpp -o hmencoder
**/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Node {
    public:
        int freq;
        string bits;
};

class Nodes {
    public:
        int frequency;
        string chars;
};

bool compare(const Nodes a,  const Nodes b);
char findMinASCII(string str);

int main(int argm, char *argv[]) 
    {
    ifstream instream;
    instream.open(argv[1]);

    if(instream.fail() == true) 
    {
        cout<<"File cannot be opened!!" <<endl;
        exit(1);
    }
    string text="";
    string line="";

    while(instream.good() == true) 
    {
        getline(instream, line);
        text+=line;
    }

    string fullText = text;

    vector<Nodes> tree;
    map<char, Node> data;


     for(int i=0;i<fullText.length();i++)
       {
        if(data.count(fullText[i]) != 0)
            {
                data[fullText[i]].freq++;
            }
        else if(data.count(fullText[i]) == 0)
            { 
                Node input;
                input.freq = 1;
                input.bits = "";
                data[fullText[i]] = input;
            }
       }

    map<char,Node>::iterator itr;
    for(itr = data.begin();itr!=data.end();itr++)
    {
        Nodes input;
        input.chars = (*itr).first;
        input.frequency = (*itr).second.freq;
        tree.push_back(input);
    }

    while(tree.size() >1) 
    {
        sort(tree.begin(), tree.end(), compare);

        Nodes add;
        Nodes l = tree[0];
        Nodes r = tree[1];

        char minASCII1 = findMinASCII(l.chars);
        char minASCII2 = findMinASCII(r.chars);

        string node1 = l.chars;
        string node2 = r.chars;

        if(minASCII1 > minASCII2 )
        {
            string temp = node1;
            node1 = node2;
            node2 = temp;
        }

        add.chars = node1 + node2;
        add.frequency = l.frequency + r.frequency;
        
        tree.push_back (add);

        for(int j =0; j<node1.length() ; j++) 
        {
            char bit;
            bit = node1[j];
            data[bit].bits = "0" + data[bit].bits;
        }

        for(int k=0; k<node2.length(); k++) 
        {
            char bit;
            bit = node2[k];
            data[bit].bits = "1" + data[bit].bits;
        }

        tree.erase(tree.begin(), tree.begin()+2);
    }
        double total = 0;
        for(int j=0; j<fullText.length(); j++) 
        {
            total += data[fullText[j]].bits.length();
        }

        double average = total/(fullText.length());
        
        ofstream outstream;
        outstream.open("encodemsg.txt");
        string encode="";
        for(int j=0; j<fullText.length(); j++) 
        {
            encode += data[fullText[j]].bits;
        }
        bool finish = true;
        while (finish == true) 
        {
            if(encode.length() > 80) 
            {
                string shortstr = encode.substr(0,80);
                outstream<<shortstr<<endl;
                encode.replace(0,80,"");
            }
            else 
            {
                outstream<<encode;
                finish = false;
            }
        }

        ofstream outstream1;
        outstream1.open("code.txt");
        map<char, Node>::iterator itr1;
        for(itr1=data.begin(); itr1!=data.end(); itr1++) 
        {
            if((*itr1).first != ' ') 
            {
                outstream1<<(*itr1).first<< ": "<< (*itr1).second.bits<<endl;

            }
            else if((*itr1).first == ' ') 
            {
                outstream1 << "Space: " << (*itr1).second.bits<<endl;
            }
        }

        outstream1 <<"Ave = "<<setprecision(3)<<average<<" bits per symbol";

        outstream.close();
        outstream1.close();
        
        return 0;

    
}
    bool compare(const Nodes a, const Nodes b) 
    {
        if (a.frequency != b.frequency) 
        {
            return a.frequency < b.frequency;
        }
        else if(a.frequency == b.frequency) 
        {
            return findMinASCII(a.chars) < findMinASCII(b.chars);
        }
    }


    char findMinASCII(string str) 
    {
        char minASCII = str[0];
        for(int i=0; i<str.length(); i++) 
        {
            if(minASCII > str[i]) 
            {
                minASCII = str[i];
            }
        }
        return minASCII;
    }





