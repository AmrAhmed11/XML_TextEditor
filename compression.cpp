#include "compression.h"
using namespace std;
vector <int> compress(string content){
    string previous,current;
    previous += content[0];
    int entry=256;
    unordered_map <string, int> table;
    vector<int> output;
    int len = content.length();

    for (int i = 0; i < entry; i++) {
		string temp;
		temp += char(i);
		table[temp] = i;
	}

    for (int i = 0; i < len; i++) {    
		if (i != len - 1)
			current += content[i + 1];
		if (table.find(previous + current) != table.end()) {
			previous = previous + current;
		}
		else {
			output.push_back(table[previous]);
			table[previous + current] = entry;
			entry++;
			previous = current;
		}
		current = "";
	}
    output.push_back(table[previous]);
	return output;
}
string decompress(string directory_of_file){
    std::fstream myinfile(directory_of_file, std::ios_base::in);
    int a,index=0;
    vector<int> input;
    while (myinfile >> a)
    {
        input.push_back(a);
    }
    string output,next,current;
    unordered_map<int, string> table;
    int entry=256,old=input[0],n;
    int len=input.size();
    for (int i = 0; i < entry; i++) {
		string temp = "";
		temp += char(i);
		table[i] = temp;
	}
    next = table[old];
    current += next[0];
	output+=next;
    for (int i = 0; i < len- 1; i++) {
		n = input[i + 1];
		if (table.find(n) == table.end()) {
			next = table[old];
			next = next + current;
		}
		else {
			next = table[n];
		}
		output+=next;
		current = "";
		current += next[0];
		table[entry] = table[old] + current;
		entry++;
		old = n;
	}
    return output;
}
