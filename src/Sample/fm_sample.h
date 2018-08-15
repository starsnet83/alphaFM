#ifndef FM_SAMPLE_H_
#define FM_SAMPLE_H_

#include <string>
#include <vector>
#include "../Utils/str_util.h"

using namespace std;

const string spliter = " ";
const string innerSpliter = ":";


class fm_sample
{
public:
    int y;
    vector<pair<string, double> > x;
    fm_sample(const string& line);
    void parseLine(const string& line, vector<string> vec);
    void reset();
};

void fm_sample::reset() {
    this->y = 0;
    this->x.clear();
}

void fm_sample::parseLine(const string& line, vector<string> vec){
    this->x.clear();
    vec.clear();

    util::str_util::split(line, vec);
    int label = atoi(vec[0].c_str());
    this->y = label > 0 ? 1 : -1;
    for (int index = 1; index < vec.size(); ++index){
        this->x.push_back(make_pair(vec[index], 1));
    }
}

fm_sample::fm_sample(const string& line) 
{
    this->x.clear();
    size_t posb = line.find_first_not_of(spliter, 0);
    size_t pose = line.find_first_of(spliter, posb);
    int label = atoi(line.substr(posb, pose-posb).c_str());
    this->y = label > 0 ? 1 : -1;
    string key;
    double value;
    while(pose < line.size())
    {
        posb = line.find_first_not_of(spliter, pose);
        if(posb == string::npos)
        {
            break;
        }
        pose = line.find_first_of(innerSpliter, posb);
        if(pose == string::npos)
        {
            cout << "wrong line input\n" << line << endl;
            throw "wrong line input";
        }
        key = line.substr(posb, pose-posb);
        posb = pose + 1;
        if(posb >= line.size())
        {
            cout << "wrong line input\n" << line << endl;
            throw "wrong line input";
        }
        pose = line.find_first_of(spliter, posb);
        value = stod(line.substr(posb, pose-posb));
        if(value != 0)
        {
            this->x.push_back(make_pair(key, value));
        }
    }
}


#endif /*FM_SAMPLE_H_*/
