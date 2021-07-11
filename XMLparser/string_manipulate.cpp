#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void stringManipulate(string input, vector<string> &tag, vector<string> &tagend, vector<string> &data, vector<string> &attr){
    int index=0;
    int len= input.length();
    int line=0;
    for (index=0; index<len;index++){
        if (input[index]=='<'){
            if (input[index+1]!='/'){
                for (int i=index;i<index+20;i++){
                    if (isspace(input[i])||input[i]=='>'){
                        string sub = input.substr(index+1, i); 
                        //function to create node with sub value and send(line,index)
                        cout << sub <<" "<<index+1<<'\n';
                        tag.push_back(sub);
                        index=i;
                        break;
                    }
                }
                if (input[index]==' '){
                    for (int i=index;i<index+300;i++){
                       if (input[i]=='>'){
                            string sub = input.substr(index+1, i); 
                            //function to set attr with sub value
                            attr.push_back(sub);
                            index=i;
                            break;
                        }
                    }
                }
            }
            else if (input[index+1]!='/'){
                for (int i=index;i<index+20;i++){
                    if (input[i]=='>'){
                        string sub = input.substr(index+2, i); 
                        //function to finish node with sub value
                        tagend.push_back(sub);
                        index=i-1;
                        break;
                    }
                }
            }
            
        }
        else if (input[index]=='\n'){continue;}
        else{
            for (int i=index;i<index+2200;i++){
                if (input[i]=='<'){
                    string sub = input.substr(index, i); 
                    //function to set data with sub value
                    data.push_back(sub);
                    index=i-1;
                    break;
                }
            }
        }
    }
}
int main(int argc, char** argv)
{

    ifstream ifs("data.xml");
    string content( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()));
    vector<string> tag;
    vector<string> tagend;
    vector<string> data;
    vector<string> attr;
    stringManipulate(content,tag,tagend,data,attr);
  return 0;
}