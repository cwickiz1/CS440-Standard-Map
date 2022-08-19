#include <iostream>
#include <utility>
#include <string>
#include <cassert>
#include "Map.hpp"

using namespace std;

void
print(const std::pair<const int, int> &p) {
    printf("%d, %d; ", p.first, p.second);
}

struct Person {
    friend bool operator<(const Person &p1, const Person &p2) {
        return p1.name < p2.name;
    }
    friend bool operator==(const Person &p1, const Person &p2) {
        return p1.name == p2.name;
    }
    Person(const char *n) : name(n) {}
    void print() const {
        printf("Name: %s\n", name.c_str());
    }
    const std::string name;
    Person &operator=(const Person &) = delete;
};

int main()
{
    cout << "---------------------Constructor Test--------------------------" << endl;
    cs540::Map<string,int> map;

    map.insert(make_pair("a",1));
    map.insert(make_pair("b",2));
    map.insert(make_pair("c",3));
    map.insert(make_pair("d",4));
    map.insert(make_pair("e",5));

    cout << "Initializer" << endl;

    cs540::Map<int,int> map2 = {{1,1},{2,2},{3,3},{4,4}};

    cout << "Copy" << endl;

    cs540::Map<string,int> map3 = map;

    cout << "Assignment" << endl;

    map = map;
    map = map3;



    cout << "---------------------Iterator Test--------------------------" << endl;
    for(cs540::Map<string,int>::Iterator it = map.begin(); it != map.end();it++){
      cout << (*it).first << endl;
    }
    cout << endl;

    for(cs540::Map<string,int>::ConstIterator it = map.begin(); it != map.end();it++){
      cout << (*it).first << endl;
    }
    cout << endl;

    for(cs540::Map<string,int>::ReverseIterator it = map.rbegin(); it != map.rend();it++){
      cout << (*it).first << endl;
    }
    cout << endl;

    cs540::Map<string,int>::Iterator it1 = map.begin();
    cs540::Map<string,int>::Iterator it2 = map.begin();
    cs540::Map<string,int>::ConstIterator it3 = map.begin();
    cs540::Map<string,int>::ConstIterator it4 = map.begin();


    assert(it1 == it2);
    assert(it1 == it3);
    assert(it3 == it1);
    assert(it3 == it4);
    ++it1;
    ++it3;
    assert(it1 != it2);
    assert(it1 != it4);
    assert(it4 != it1);
    assert(it3 != it4);

    assert(map==map3);
    //auto ins = map.insert(std::make_pair(10, 1435));
    //if(ins.second){
      //cout << "Bad Insert" << endl;
    //} else {
      //cout << "No new Insert" << endl;
    //}

    cout << "---------------------Find Test--------------------------" << endl;
    auto found = map.find("a");
    int foundp = map.at("c");
    found = map.find("e");

    cout << "---------------------Delete Test--------------------------" << endl;

    cs540::Map<string,int>::Iterator del = map.begin();
    map.erase(del);
    map.erase("d");
    //map.erase(8);
    assert(map<map3);
    map.clear();
    assert(map.empty());
    //int found2 = map.at(5);
    //cout << found2 << endl;
    cout << "END" << endl;
    return 0;
}
