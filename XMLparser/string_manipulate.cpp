#include "string_manipulate.h"
using namespace std;

string trim_extra_mid_spaces(string s) {
    string out = "";
    bool first_space = false;
    bool locked = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '"') {
            locked = !locked;
        }
        if (!locked) {
            if (s[i] == ' ' && first_space == false) {
                out += s[i];
                first_space = true;
            }
            else if (s[i] != ' ') {
                first_space = false;
                out += s[i];
            }
        }
        else {
            out += s[i];
        }
    }
    return out;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}


void stringManipulate(string input) {
    int index = 0;
    int len = input.length();
    int line = 0;
    string tagstr, tagendstr, datastr, attrstr;
    for (index = 0; index < len; index++) {
        if (input[index] == '<') {
            if (input[index + 1] != '/' && input[index + 1] != '!' && input[index + 1] != '?') {
                for (int i = index; i < index + 20; i++) {
                    if (isspace(input[i]) || input[i] == '>') {
                        i = i - index - 1;
                        tagstr = input.substr(index + 1, i);
                        tagstr = trim(tagstr);
                        opening(tagstr, index + 1);
                        index += i + 1;
                        break;
                    }
                }
                //attributes and self closing tag
                if (input[index] == ' ') {
                    for (int i = index; i < index + 300; i++) {
                        if (input[i] == '>') {
                            int selfclosing= i - 1;
                            i = i - index - 1;
                            attrstr = input.substr(index + 1, i);
                            attrstr = trim_extra_mid_spaces(attrstr);
                            attrstr = trim(attrstr);
                            // check if self closing
                            if (input[selfclosing] == '/')
                            {
                                setAttribute(attrstr, 1);
                                closing (tagstr);
                                index += i + 1;
                                break;
                            }
                            setAttribute(attrstr, 0);
                            index += i + 1;
                            break;
                        }
                    }
                }
            }
            // closing tag 
            else if (input[index + 1] == '/') {
                for (int i = index; i < index + 20; i++) {
                    if (input[i] == '>') {
                        i = i - index - 1;
                        tagendstr = input.substr(index + 2, i - 1);
                        tagendstr = trim(tagendstr);
                        //function to finish node with sub value
                        closing(tagendstr);
                        index += (i + 2);
                        break;
                    }
                }
            }
            //comments tag
            else if (input[index + 1] == '!') {
                opening("", index + 1);
                for (int i = index; i < index + 2200; i++) {
                    if (input[i] == '>') {
                        i = i - index;
                        datastr = input.substr(index + 1, i - 1);
                        //function to set data with sub value
                        datastr = trim(datastr);
                        setAttribute(datastr, 2);
                        closing("");
                        index += i;
                        break;
                    }
                }
            }
            //XML tag 
            else if (input[index + 1] == '?') {
                for (int i = index; i < index + 20; i++) {
                    if (isspace(input[i]) || input[i] == '>') {
                        i = i - index - 1;
                        tagstr = input.substr(index + 1, i);
                        tagstr = trim(tagstr);
                        opening(tagstr, index + 1);
                        index += i + 1;
                        break;
                    }
                }
                if (input[index] == ' ') {
                    for (int i = index; i < index + 300; i++) {
                        if (input[i] == '>') {
                            i = i - index - 1;
                            attrstr = input.substr(index + 1, i);
                            //function to set attr with sub value
                            attrstr = trim_extra_mid_spaces(attrstr);
                            attrstr = trim(attrstr);
                            setAttribute(attrstr, 4);
                            closing(tagstr);
                            index += i + 1;
                            break;
                        }
                    }
                }
            }
        }
        else if (input[index] == '\n' || isspace(input[index])) { continue; }
        else {
            for (int i = index; i < index + 2200; i++) {
                if (input[i] == '<') {
                    i = i - index - 1;
                    datastr = input.substr(index, i + 1);
                    datastr = trim(datastr);
                    setData(datastr);
                    index += i;
                    break;
                }
            }
        }
    }
}