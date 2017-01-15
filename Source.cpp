#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "graph.h"

inline int Factorial(int x) {
	return (x == 1 ? x : x * Factorial(x - 1));
}
int main(int argc, char *argv[])
{
	graph a("graph1.txt"), b("graph2.txt");
	int** x = new int*[4];
	for (int i = 0; i < 4; ++i) {
		x[i] = new int[4];
		std::fill(x[i], x[i] + 4, 0);
		x[i][i] = 1;
	}
	for(int i = 0; i<Factorial(4); ++i) {
		std::next_permutation(x, x + 4);
		std::cout << a << std::endl;
		//printArray(x, 4);
		int **tmp = x*(b*x);
		printArray(x*(b*x), 4);
		std::cout << std::endl;
		printArray(tmp, 4);
		if (a == tmp)
		{	

			std::cout << "znalazlem\n";
			printArray(x, 4);
			break;
		}
	}
	/*int tab[3]{ 1,2,3 };
	do {
		for (int i = 0; i < 3; ++i)
			std::cout << tab[i] << " ";
		std::cout << std::endl;
	} while (std::next_permutation(tab, tab + 3));*/
	std::cin.get();
}

