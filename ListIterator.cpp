#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
    //TODO - Implementation
    ListIterator::first();
}

void ListIterator::first(){
    //TODO - Implementation

    this->currentElement = this->list.nodes.head;
}

void ListIterator::next(){
    //TODO - Implementation
    if(!valid())
        throw exception();
    this->currentElement=this->list.nodes.nodes[this->currentElement].next;
}

bool ListIterator::valid() const{
    //TODO - Implementation
    //wenn die Position nicht stimmt (das Index besprict dem Intervall [0,cap) nicht oder wenn das Node aus dem array is null
    //ist es nict valid
    return this->currentElement!=-1 && this->currentElement!=this->list.nodes.cap
    && this->list.nodes.nodes[this->currentElement].info != NULL_TCOMP;
}

TComp ListIterator::getCurrent() const{
    //TODO - Implementation
    if(!valid())
        throw exception();
    return this->list.nodes.nodes[this->currentElement].info;
}

void ListIterator::modify(TComp value, TComp newValue) {

    if(!this->list.search(value).valid() ) {
        throw exception();
    }
    ListIterator pos=this->list.search(value);
//    for( auto it1 =*this; it1.valid(); it1.next()){
//        if(it1.currentElement==pos.currentElement)
//            it1.list.r
//    }
}
