#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <ctime>
#include <windows.h>


using namespace std;

vector <vector<pair <int, int>>> k;
priority_queue <pair <int, int>> T;
vector < vector<int>> vecForMatrix;
priority_queue <pair <int, int>> S;

void Deikstra();
void DeikstraForMatrix();
int maxSize;
void DenseGraphGeneration(int graphSize);
void SparseGraphGeneration(int graphSize);
void DenseGraphGenerationList(int graphSize);
void SparseGraphGenerationList(int graphSize);
int List(int graphSize);
int Matrix(int graphSize);

int main() // Ввод графа
{
   setlocale(LC_ALL, "Russian");
   int m, n, f, num;
   fstream fin("C://graph.txt");
   fstream fin2("C://graphmat.txt");
   if (!fin.is_open())
	  cout << "File not open";
   else
   {
	  cout << "1 - список смежности" << endl;
	  cout << "2 - матрица смежности" << endl;
	  cout << "3 - насыщенный граф(матрица смежности)" << endl;
	  cout << "4 - разряженный граф(матрица смежности)" << endl;
	  cout << "5 - насыщенный граф(список смежности)" << endl;
	  cout << "6 - разряженный граф(список смежности)" << endl;
	  cin >> num;
	  switch (num)
	  {
	  case 1:
	  {
		 fin >> maxSize; // количество рёбер
		 while (!fin.eof())
		 {
			fin >> m >> n >> f; // f - длина пути / m, n - вершины
			k.resize(maxSize);
			k[m].push_back(make_pair(f, n));
			k[n].push_back(make_pair(f, m));
		 }
		 clock_t start = clock();
		 Deikstra();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 break;
	  }
	  case 2:
	  {
		 fin2 >> maxSize; // размер матрицы maxSize * maxSize
		 vecForMatrix.resize(maxSize);
		 for (int i = 0; i < maxSize && !fin2.eof(); i++)
		 {
			vecForMatrix[i].resize(maxSize);
			for (int j = 0; j < maxSize; j++)
			{
			   fin2 >> m;
			   vecForMatrix[i][j] = m;
			}
		 }
		 clock_t start = clock();
		 DeikstraForMatrix();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 break;
	  }
	  case 3:
	  {
		 cout << "Введите размер графа" << endl;
		 cin >> maxSize;
		 DenseGraphGeneration(maxSize);
		 cout << Matrix(maxSize) << endl;
		 clock_t start = clock();
		 DeikstraForMatrix();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 fin.clear();
		 break;
	  }
	  case 4:
	  {
		 cout << "Введите размер графа" << endl;
		 cin >> maxSize;
		 SparseGraphGeneration(maxSize);
		 cout << Matrix(maxSize) << endl;
		 clock_t start = clock();
		 DeikstraForMatrix();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 fin.clear();
		 break;
	  }
	  case 5:
	  {
		 cout << "Введите размер графа" << endl;
		 cin >> maxSize;
		 DenseGraphGenerationList(maxSize);
		 cout << List(maxSize) << endl;
		 clock_t start = clock();
		 Deikstra();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 fin.clear();
		 break;
	  }
	  case 6:
	  {
		 cout << "Введите размер графа" << endl;
		 cin >> maxSize;
		 SparseGraphGenerationList(maxSize);
		 cout << List(maxSize) << endl;
		 clock_t start = clock();
		 Deikstra();
		 clock_t end = clock();
		 cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
		 fin.clear();
		 break;
	  }
	  }
   }
   fin.close();
}

void Deikstra()
{
   fstream fout;
   fout.open("C://out.txt");
   if (!fout.is_open())
	  cout << "File not open";
   else
   {
	  vector <int> dl(k.size(), 0), sel(k.size(), 0);
	  sel[0] = 0;
	  vector <bool> visited(k.size(), 0);
	  T.push(make_pair(0, 0));
	  while (!T.empty())
	  {
		 int f = T.top().second;
		 int cur = -T.top().first;
		 if (sel[f] != -1 && !visited[f] && f != 0)
			fout << f + 1 << " " << dl[f] << endl;
		 visited[f] = true;
		 T.pop();
		 for (int j = 0; j < k[f].size(); ++j)
		 {
			int i = k[f][j].second, len = k[f][j].first;
			if (!visited[i] && (dl[i] == 0 || dl[f] + len < dl[i]))
			{
			   dl[i] = dl[f] + len;
			   sel[i] = f;
			   T.push(make_pair(-dl[i], i));
			}
		 }
	  }
	  fout.close();
   }
}

void DeikstraForMatrix()
{
   fstream fout;
   fout.open("C://output.txt");
   if (!fout.is_open())
	  cout << "File not open";
   else
   {
	  vector <int> dl(maxSize, 0), sel(maxSize, -1);
	  sel[0] = 0;
	  vector <bool> visited(maxSize, 0);
	  S.push(make_pair(vecForMatrix[0][0], 0));
	  while (!S.empty())
	  {
		 int f = S.top().second;
		 int cur = -S.top().first;
		 if (sel[f] != -1 && !visited[f] && f != 0)
			fout << f + 1 << " " << dl[f] << endl;
		 visited[f] = 1;
		 S.pop();
		 for (int j = 0; j < vecForMatrix[f].size(); ++j)
		 {
			int len = vecForMatrix[f][j], i = j;
			if (vecForMatrix[f][j] != 0)
			{
			   if (!visited[i] && (dl[i] == 0 || dl[f] + len < dl[i]))
			   {
				  dl[i] = dl[f] + len;
				  sel[i] = f;
				  S.push(make_pair(-dl[i], i));
			   }
			}
		 }
		 f++;
	  }
	  fout.close();
   }
}

void DenseGraphGeneration(int graphSize)
{
   vecForMatrix.resize(graphSize);
   srand(time(nullptr));
   int cur = 0;
   for (int i = 0; i < graphSize; i++)
   {
	  vecForMatrix[i].resize(graphSize);
	  for (int j = 0; j < graphSize; j++)
	  {
		 if (i == 0 && j == 0) // выполняется один раз
		 {
			cur = 1 + rand() % (graphSize - 2);
			vecForMatrix[i][cur] = 100 + rand() % 100;// сделать чтобы соединяло с рандомной
		 }
		 else
		 {
			if (i == j || i == 0 && j != cur)
			   vecForMatrix[i][j] = 0;
			else
			   vecForMatrix[i][j] = 100 + rand() % 100;
		 }
	  }
   }
}

void SparseGraphGeneration(int graphSize)
{
   vecForMatrix.resize(graphSize);
   srand(time(nullptr));
   for (int i = 0; i < graphSize; i++)
   {
	  vecForMatrix[i].resize(graphSize);
	  for (int j = 0; j < graphSize; j++)
	  {
		 if (i == j)
			vecForMatrix[i][j] = 0;
		 else
		 {
			if (i + 1 == j)
			   vecForMatrix[i][j] = rand() % 100;
			else
			   vecForMatrix[i][j] = 0;
		 }
	  }
   }
}

void DenseGraphGenerationList(int graphSize)
{
   srand(time(NULL));
   k.resize(graphSize);
   for (int i = 0; i < graphSize; i++)
   {
	  k[i].resize(graphSize);
	  for (int j = 0; j < graphSize; j++)
	  {
		 if (i != j)
		 {
			int f = rand() % 100;
			if (f != 0)
			{
			   k[i].push_back(make_pair(f + 1, j));
			   k[j].push_back(make_pair(f + 1, i));
			}
		 }
	  }
   }
}

void SparseGraphGenerationList(int graphSize)
{
   srand(time(0));
   k.resize(graphSize);
   for (int i = 0; i < graphSize; i++)
   {
	  k[i].resize(graphSize);
	  for (int j = 0; j < graphSize; j++)
	  {
		 if (i + 1 == j)
		 {
			int f = rand() % 100;
			if (f != 0)
			{
			   k[i].push_back(make_pair(f, j));
			   k[j].push_back(make_pair(f, i));
			}
		 }
	  }
   }
}

int List(int graphSize)
{
   int result = 0;
   for (int i = 0; i < graphSize; i++)
   {
	  result += k[i].size();
   }
   return result / graphSize;
}

int Matrix(int graphSize)
{
   int result = 0;
   for (int i = 0; i < graphSize; i++)
   {
	  for (int j = 0; j < graphSize; j++)
	  {
		 if (vecForMatrix[i][j] != 0)
			result += k[i].size();
	  }
   }
   return result / graphSize;
}
