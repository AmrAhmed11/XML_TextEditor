#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void stringManipulate(string input, vector<string> &tag, vector<string> &tagend, vector<string> &data, vector<string> &attr){
    int index=0;
    int len= input.length();
    int line=0;
    string tagstr,tagendstr,datastr,attrstr;
    for (index=0; index<len;index++){
        if (input[index]=='<'){
            if (input[index+1]!='/'){
                for (int i=index;i<index+20;i++){
                    if (isspace(input[i])||input[i]=='>'){
                        i = i - index -1;
                        tagstr = input.substr(index+1, i); 
                        //function to create node with sub value and send(line,index)
                        //opening(sub,index+1,index+i+1)
                        tag.push_back(tagstr);
                        index+=i+1;
                        break;
                    }
                }
                if (input[index]==' '){
                    for (int i=index;i<index+300;i++){
                       if (input[i]=='>'){
                           if (input[i-1]=='/')
                           {
                            i = i - index -1;
                            attrstr = input.substr(index+1, i); 
                            //function to set attr with sub value
                            // closing(tagstr)
                            attr.push_back(attrstr);
                            index +=i+1;
                            break;
                           }
                            i = i - index -1;
                            attrstr = input.substr(index+1, i); 
                            //function to set attr with sub value
                            attr.push_back(attrstr);
                            index +=i+1;
                            break;
                        }
                    }
                }
            }
            // closing tag 
            else if (input[index+1]=='/'){
                for (int i=index;i<index+20;i++){
                    if (input[i]=='>'){
                        i = i - index-1;
                        tagendstr = input.substr(index+2, i-1); 
                        //function to finish node with sub value
                        tagend.push_back(tagendstr);
                        index +=(i+2);
                        break;
                    }
                }
            }
            //comments handling
            else if(input[index+1]!='!'){
                for (int i=index;i<index+2200;i++){
                    if (input[i]=='>'){
                        i = i - index;
                        datastr = input.substr(index, i+1); 
                        //function to set data with sub value
                        data.push_back(datastr);
                        index +=i;
                        break;
                    }
                }
            }
        }
        else if (input[index]=='\n'){continue;}
        else{
            for (int i=index;i<index+2200;i++){
                if (input[i]=='<'){
                    i = i - index-1;
                    datastr = input.substr(index, i+1); 
                    //function to set data with sub value
                    data.push_back(datastr);
                    index +=i;
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