#include "graph.h"
#include "row.h"


graph::graph(): vertices(0)
{
	adjMatrix = new int*();
}

graph::graph(char* filename)
{
	std::string name(filename);
	std::fstream file;
	file.open(name, std::ios::in);
	file >> vertices;
	adjMatrix = new int*[vertices];
	for (int i = 0; i < vertices; ++i) {
		adjMatrix[i] = new int[vertices];
		std::fill(adjMatrix[i], adjMatrix[i] + vertices, 0);
	}
	int a, b;
	while (file >> a >> b)
		adjMatrix[a][b] = adjMatrix[b][a] = 1;
	file.close();
}

graph::graph(int** tab, int size): vertices(size)
{
	adjMatrix = new int*[size];
	for (int i = 0; i < size; ++i) {
		adjMatrix[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			adjMatrix[i][j] = tab[i][j];
		}
	}
}

graph::graph(int size) : vertices(size)
{
	adjMatrix = new int*[size];
	for (int i = 0; i < vertices; ++i) {
		adjMatrix[i] = new int[vertices];
		std::fill(adjMatrix[i], adjMatrix[i] + vertices, 0);
	}
}

bool graph::operator==(graph const &other) const
{
	if (vertices != other.vertices)
		return false;
	else {
		return adjMatrix == other.adjMatrix;
	}
}

bool graph::operator==(int** const &tab) const
{
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			if (adjMatrix[i][j] != tab[i][j])
				return false;
		}
	}
	return true;
}

bool graph::operator!=(graph const &other) const
{
	return !(*this == other);
}

bool graph::operator!=(int** const &tab) const
{
	return !(*this == tab);
}

std::ostream &operator<<(std::ostream &input, const graph &g)
{
	for (int i = 0; i < g.vertices; ++i)
	{
		for (int j = 0; j < g.vertices; ++j)
		{
			input << g.adjMatrix[i][j] << " ";
		}
		input << "\n";
	}
	return input;
}

graph::graph(const graph &other) : vertices(other.vertices)
{
	adjMatrix = new int*[vertices];
	for (int i = 0; i < vertices; ++i)
	{
		adjMatrix[i] = other.adjMatrix[i];
	}
}

graph& graph::operator=(const graph &other)
{
	if (this != &other) {
		for (int i = 0; i < vertices; ++i) {
			delete[] adjMatrix[i];
		}
		vertices = other.vertices;
		for (int i = 0; i < vertices; ++i) {
			adjMatrix[i] = other.adjMatrix[i];
		}
	}
	return *this;
}

graph::~graph()
{
	for (int i = 0; i < vertices; ++i)
		adjMatrix[i] = nullptr;
	delete adjMatrix;
}

graph graph::operator*(row* const &tab)
{
	int** result = new int*[vertices];
	for (int i = 0; i < vertices; ++i) {
		result[i] = new int[vertices];
		std::fill(result[i], result[i] + vertices, 0);
	}
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			for (int k = 0; k < vertices; ++k)
				result[i][j] += adjMatrix[i][k] * tab[j][k];
		}
	}
	return graph(result, vertices);
}
graph graph::operator*(int** const &tab)
{
	graph result(multiplyTransposed(adjMatrix, tab, vertices), vertices);
	*this = result;
	return *this;
}

int** operator*(int** const &tab, graph const &g)
{
	return matrixMultiply(tab, g.adjMatrix, g.vertices);
}

int** operator*(row* const &tab, graph const &g)
{
	int** result = new int*[g.vertices];
	for (int i = 0; i < g.vertices; ++i) {
		result[i] = new int[g.vertices];
		std::fill(result[i], result[i] + g.vertices, 0);
	}
	for (int i = 0; i < g.vertices; ++i) {
		for (int j = 0; j < g.vertices; ++j) {
			for (int k = 0; k < g.vertices; ++k)
				result[i][j] += tab[i][k] * g.adjMatrix[k][j];
		}
	}
	return result;
}

int** matrixMultiply(int** const &first, int** const &second, int const size)
{
	int** result = new int*[size];
	for (int i = 0; i < size; ++i) {
		result[i] = new int[size];
		std::fill(result[i], result[i] + size, 0);
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k)
				result[i][j] += first[i][k] * second[k][j];
		}
	}
	return result;
}

int** multiplyTransposed(int ** const &first, int** const &transposed, int const size)
{
	int** result = new int*[size];
	for (int i = 0; i < size; ++i) {
		result[i] = new int[size];
		std::fill(result[i], result[i] + size, 0);
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k)
				result[i][j] += first[i][k] * transposed[j][k];
		}
	}
	return result;
}

void printArray(int** const &tab, int const size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cout << tab[i][j] << " ";
		}
		std::cout << "\n";
	}
}


bool graph::isIsomorphic(graph &g)
{
	row* arr;
	arr = new row[vertices];
	for(int i=0; i<vertices; i++){
		arr[i] = row(vertices, i);
	}
	while(std::next_permutation(arr, arr+vertices, comparator())) {
		if(*this == arr*(g*arr))
		{
			std::cout<<"IZOMORFICZNE\n";
			for(int i=0; i<vertices; i++){
				std::cout<<i<<"->"<<arr[i].onePos<<std::endl;
			}
			return true;
		}
	}
	std::cout<<"NIEIZOMORFICZNE\n";
	return false;
}