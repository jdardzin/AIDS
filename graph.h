#pragma once
#include <string>
#include <fstream>
#include <iostream>
class graph
{
public:
	graph();
	graph(const graph& other);
	graph(char* filename);
	graph(int** array, int size);
	graph(int size);
	~graph();
	graph& operator=(const graph &other);
	friend std::ostream &operator<<(std::ostream &input, const graph &g);
	//int** operator*(const graph &g);
	bool operator==(graph const &other) const;
	bool operator==(int** const &other) const;
	bool operator!=(graph const &other) const;
	bool operator!=(int** const &other) const;
	graph operator*(int** const &tab);
	friend int** operator*(int** const &tab, graph const &g);
//private:
	int vertices;
	int **adjMatrix;
};

int** matrixMultiply(int** const &first, int** const &second,int const size);
void printArray(int** const &tab, int const size);
int** multiplyTransposed(int ** const &first, int** const &transposed, int const size);