#include <iostream>
#include "experimentClass.h"
using namespace std;


int main(){

    int age;
    int favoriteNumber;
    int age2;
    int favoriteNumber2;

    
    std::cin >> age;
    std::cin >> favoriteNumber;
    std::cin >> age2;
    std::cin >> favoriteNumber2;
    experimentClass a(age, favoriteNumber);
    experimentClass b(age2, favoriteNumber2);



}