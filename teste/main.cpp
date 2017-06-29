#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, string> dio;
    dio["12"] = "12";
    dio["21"] = "13";
    dio["12"] = "33";
    for(auto &par : dio)
        cout << par.first << ": " << par.second << endl;
    return 0;
}