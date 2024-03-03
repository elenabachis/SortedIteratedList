#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    //TODO - Implementation
    this->relation = r;
    this->nodes.cap = 10;
    this->nodes.nodes = new DLLANode[this->nodes.cap];
    this->nodes.size = 0;
    this->nodes.head = -1;
    this->nodes.tail = -1;
    this->nodes.firstEmpty = this->nodes.size;
}

int SortedIteratedList::size() const {
    //TODO - Implementation
    return this->nodes.size;
}

bool SortedIteratedList::isEmpty() const {
    //TODO - Implementation
    return this->nodes.size==0;

}

ListIterator SortedIteratedList::first() const {
    //TODO - Implementation
    ListIterator it(*this);
    it.first();
    return it;
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
    //TODO - Implementation
    if(!poz.valid()) {
        throw exception();
    }
    return poz.getCurrent();
}

///Komplexitat:O(size)
///best case: theta(1) wenn man das erste Element loscht
///worst case: theta(size) wenn man das letzte Element loscht
TComp SortedIteratedList::remove(ListIterator& poz) {
    if(!poz.valid())
        throw std::runtime_error("Invalid iterator");

    TComp elementToRemove = poz.getCurrent();
    DLLANode* nodeToRemove = nullptr; //ich setze das Node auf null
    //ich suche das Element auf pos in dem Array
    for (int i = this->nodes.head; i != -1; i = this->nodes.nodes[i].next) {
        if (this->nodes.nodes[i].info == elementToRemove) {
            nodeToRemove = &this->nodes.nodes[i];

        }
    }
    if (nodeToRemove == nullptr) { //das Element war nicht gefunden
        throw std::runtime_error("Element not found");
    }

    if (nodeToRemove->prev != -1) {
        this->nodes.nodes[nodeToRemove->prev].next = nodeToRemove->next;
    } else {
        this->nodes.head = nodeToRemove->next; //wenn ich das erste Element losche
    }

    if (nodeToRemove->next != -1) {
        this->nodes.nodes[nodeToRemove->next].prev = nodeToRemove->prev;
    } else {
        this->nodes.tail = nodeToRemove->prev; //wenn ich das letzte Element losche
    }


    TComp removed = nodeToRemove->info; //ich speichere die Wert
    poz.next();
    nodeToRemove->next = this->nodes.firstEmpty;
    nodeToRemove->prev = -1;


    this->nodes.size--;

    return removed;
}

///Komplexitat:O(size)
///best case: theta(1) wenn man e auf dem ersten Position ist
///worst case: theta(size) wenn e auf dem letzten Position ist
ListIterator SortedIteratedList::search(TComp e) const{
    //TODO - Implementation
    ListIterator it=first();
    while(it.valid()){
        if(it.getCurrent()==e) //ich habe e in dem array gefunden
            return it;
        it.next();
    }

    return ListIterator(*this);

}


///Komplexitat:O(size)
///best case: theta(1) wenn man auf dem ersten Position e einfugt
///worst case: theta(size) wenn man auf dem letzten Position e einfugt
void SortedIteratedList::add(TComp e) {

    //resize
    //wenn das List voll ist, soll man eine neues Array allokieren
    if (this->nodes.size == this->nodes.cap) {
        DLLANode* newNodes = new DLLANode[this->nodes.cap * 2]; //die Kapazitat muss verdoppelt sein
        for (int i = 0; i < this->nodes.cap; i++) {
            newNodes[i] = this->nodes.nodes[i]; //es kopiert die existierenden Knoten
        }
        delete[] this->nodes.nodes; //es deallokiert das alte Array
        this->nodes.nodes = newNodes;
        this->nodes.cap *= 2;
    }

    //es sucht die Position auf der sie eingefugt sein konnte
    int current = this->nodes.head;
    while (current != -1 && this->relation(this->nodes.nodes[current].info, e)) {
        current = this->nodes.nodes[current].next;
    }

    int newNodePos = this->nodes.firstEmpty;
    this->nodes.firstEmpty = this->nodes.nodes[this->nodes.firstEmpty].next;
    this->nodes.nodes[newNodePos].info = e;
    this->nodes.nodes[newNodePos].prev = -1;
    this->nodes.nodes[newNodePos].next = -1;

    if (current == -1) {
        if (this->nodes.size == 0) { //wenn die Liste leer ist
            this->nodes.head = newNodePos;
            this->nodes.tail = newNodePos;
        } else { //wenn e das letzte Element sein muss
            this->nodes.nodes[newNodePos].prev = this->nodes.tail;
            this->nodes.nodes[this->nodes.tail].next = newNodePos;
            this->nodes.tail = newNodePos;
        }
    } else {
        if (this->nodes.nodes[current].prev == -1) {
            this->nodes.head = newNodePos; //wenn e das erste Element sein muss
        } else {
            this->nodes.nodes[newNodePos].prev = this->nodes.nodes[current].prev;
            this->nodes.nodes[this->nodes.nodes[current].prev].next = newNodePos;
        }
        this->nodes.nodes[current].prev = newNodePos;
        this->nodes.nodes[newNodePos].next = current;
    }

    this->nodes.size++;
}


SortedIteratedList::~SortedIteratedList() {
    //TODO - Implementation
    delete[] this->nodes.nodes;
}
