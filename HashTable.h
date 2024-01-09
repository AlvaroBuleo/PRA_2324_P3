#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../Practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
	int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key){
		int sum = 0;
		for(int i = 0;i < key.length();i++){
			char letra = key.at(i);
			sum += int(letra);
		}
		int pos = sum % max;
		return pos;
	}	
		
    public:
	HashTable(int size){
		n = 0;
		max = size;
		table = new ListLinked<TableEntry<V>>[size];
	}

	~HashTable(){
		for(int i = 0;i < max;i++){
			table[i].~ListLinked();
		}
		delete[] table;
	}

	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "HashTable[entries: " << th.n << ", capacity: " << th.max << "]" << std::endl << "==============" << std::endl << std::endl;
		
		for(int i = 0;i < th.max;i++){
			out << "== Cubeta " << i  << "==\n" << std::endl;
			out << th.table[i] << std::endl << std::endl;
			out << "============\n";
		}

		return out;
		
	}
	
	V operator[](std::string key){
		int pos = table[h(key)].search(key);
		if(pos > max || pos < 0)
			throw std::runtime_error("Posición fuera de la tabla");
		V aux = table[h(key)].get(pos).value;
		return aux;
	}	

	void insert(std::string key,V value) override{
		int pos = table[h(key)].search(key);
		if(pos > 0 && pos < max)
			throw std::runtime_error("Ya introducido");
		TableEntry<V> aux(key,value);
		table[h(key)].prepend(aux);
		n++;
	}

	V search(std::string key) override{
		int hash = h(key);
		int pos = table[hash].search(key);
		if(pos < 0)
			throw std::runtime_error("No se encuentra en la lista");
		V aux = table[hash].get(pos).value;
		return aux;
	}

	V remove(std::string key) override{
		int hash = h(key);
		int pos = table[hash].search(key);
		if(pos < 0)
			throw std::runtime_error("No se encuentra en la lista");
		int aux = table[hash].remove(pos).value;
		n--;
		return aux;
	}
	
	int entries() override{
		return n;
	}
};

#endif
