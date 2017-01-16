#ifndef ROW_H
#define ROW_H

#include "graph.h"

class graph;

class row
{
private:
	int* tab;
	int	onePos;
	int size;
public:
	row(): tab(0),onePos(0), size(0) {}
	row(int n, int pos) : onePos(pos), size(n){
		tab = new int[size];
		std::fill(tab, tab+size, 0);
		tab[onePos] = 1;
	}
	void create(int n, int pos){
		delete tab;
		tab = new int[n];
		size = n;
		std::fill(tab, tab+n, 0);
		tab[pos]=1;
		onePos=pos;
	}
	int operator[](int i) const {return tab[i];}
	friend int** operator*(row* const &tab, graph const &g);
	friend struct comparator;
	friend class graph;
};

struct comparator{
	bool operator()(const row &a,const row &b) const {
		return a.onePos < b.onePos;
	}
};

#endif // ROW_H
