/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++)
        setVec.push_back(-1);
}

int DisjointSets::find(int elem){
    if(setVec[elem] < 0 || elem > (int)setVec.size())
        return elem;
    return setVec[elem] = find(setVec[elem]);
}

void DisjointSets::setunion(int a, int b){
    int x = find(a); int y = find(b);

    if(x == y)
        return;

    int size = setVec[x] + setVec[y];

    if(setVec[x] <= setVec[y]){
        setVec[y] = x;
        setVec[x] = size;
    }
    else{
        setVec[x] = y;
        setVec[y] = size;
    }
    return;
}
