/*Приветствую, unreg_user
Автор программы: Исаков, гр.#9309
Задание #5 версия 1.0.6
Начата: 6 октября
Закончена: tbd */
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
const int N = 10;
char in(float ***b, int *m, int *k, int *siz)
{
	ifstream in;
	int i = 0, j = 0, lmin = 100, cmin = 100, cycle = 1, z;
	char s;
	float t; 
	for (z = 0; z < 2; z++)
	{ 
		//cout << z << endl;
		in.open("in5.txt");
		if(in.is_open())
		{
			i = 0; j = 0;
			if (cycle) in >> *m >> *k;
			else 
			{
				in >> skipws >> *m >> *k;
				in >> s;
			}
			while ((i < N-1) && (!in.eof()))
			{
				in >> noskipws >> s;
				if ((s == '0')||(s == '1')||(s == '2')||(s == '3')||(s == '4')||(s == '5')||(s == '6')||(s == '7')||(s == '8')||(s == '9'))
				{
					in.putback(s);
					in >> skipws >> t;
					if (!cycle) 
					{
						if (j < cmin)
						{
						*(*(*b+i)+j) = t;
						cout << *(*(*b+i)+j) << endl;
						}
					}
					j++;
				}
				else switch (s)
				{
					case '\n': 
						if((i == 0)&&(j == 0))
						{
							break;	
						}
						else 
						{
							if (cycle) {if (j < cmin) cmin = j;} // mimum of colums 
							i++;
							if (cycle) lmin = i + 1; // minimum of lines
							j = 0;
							break;
						}
					default: 
						if (in.eof())
						{
							if (cycle)
							{
								cout << lmin << 'x' << cmin << endl;
								if (cmin > lmin) cmin = lmin;
								else if (lmin > cmin) lmin = cmin;
								else if (cmin == 100) 
								{
									in.close();
									return 'e'; // empty input file case
								}
								*siz = cmin;
								in.close();
								//c  cout << "before *" << endl;
								*b = new float*[cmin];
								//cout << "after *" << endl;
								if (*b == NULL) return 'm'; // memory error  
								for (i = 0; i < cmin; i++) 
								{
									(*b)[i] = new float[cmin];
									//cout << "after **" << endl;
									if ((*b)[i] == NULL) return 'm'; // memory error  
								}
								cycle = 0; 
								break;
							}
							else 
								{
									in.close();
									return 'r'; //right ending
								}
						}
		 		}
			}
		}
		else 
		{
			return 'i'; // input error
		}
	}
}
char out(fstream *f, float ***b, int m, int k, int siz, char inerr, float res)
{
		int i = 0, j = 0;
		switch (inerr)
		{
			case 'm': 
				*f << "Memory error occurred";
				cout << "Memory error occurred";
				return 'e';
			case 'e':
				*f << "No matrix elements detected";
				cout << "No matrix elements detected";
				return 'e';
			case 'i':
				*f << "Could not open input file";
				cout << "Could not open input file";
				return 'e';
			case 'r':
				cout << "Greetings, unreg_user" << endl << "Program by: Isakov, gr.#9309" << endl;
				cout << "Task: Find maximum value, based on matrix data from file" << endl;
				cout << "ver. 1.0.14" << endl;
				cout << "Started: 6 nov." << endl << "Completed: tbd " << endl;
				cout << "Open out.txt for results" << endl;
				*f << "Additional parameters:" << endl << "m = " << m << "  " << " k = " << k << endl;
				*f << "Size of sqare matrix: " << siz << 'x' << siz << endl;
				for (i = 0; i < siz; i++)
				{
					for (j = 0; j < siz; j++)
					{
						if (j == siz - 1) *f << *(*(*b+i)+j) << endl;
						else *f << *(*(*b+i)+j) << ' ';
					}
				}
				return 'f';
			default:
				*f << "Maximum value is " << res;
				return 'c';
		}	
	}
float proc(float ***b, int *m, int *k, int *siz)
{
	float max;
	int i = *siz - 2, j = 0;
	do
	{
		if (j = 0) max = *(*(*b+i)+j);
		else if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // diagonal check
		i++; j++;
	}
	while ((i <= 0)&&(j <= *siz - 2));
	i = *siz -1; j = *m - 1;
	do
	{
		if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // m column check
		i--;
	}
	while ((i <= *siz - j - 1) && (i >= 0));
	i = *k - 1; j = *siz -1;
	do
	{
		if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // k line check
		j--;
	}
	while ((j <= *siz - i - 1) && (j >= 0));
	return max;
}
int main(void)
{
	float **b;
	int m, k, siz;
	char inerr;
	float res;
	fstream f;
	f.open("out5.txt",ios::out);
	if (f.is_open())
	{
		inerr = in(&b , &m, &k, &siz);
		out(&f, &b, m, k, siz, inerr, res);
		//cout << "first call" << endl;
		if ((inerr == 'm')||(inerr == 'e')||(inerr == 'i')) return 0;
		res = proc(&b, &m, &k, &siz);
		inerr = 'g';
		//cout << "second call" << endl;
		out(&f, &b, m, k, siz, inerr, res);
		f.close();
		int i,j;
		for (i = 0; i <= siz; i++)
		{
			for (j = 0; j <= siz; j++)
				{
					delete[]b[i];
				}
		}
		delete[]b; b = NULL;
	}
	else cout << "Output file error" <<endl;	
}
