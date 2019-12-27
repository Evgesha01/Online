// kursach time!!111!
/*Приветствую, unreg_user
Автор программы: Исаков, гр.#9309
Курсовая работа версия 1.1.17
Начата: 1 декабря
Закончена: tbd */
#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>
using namespace std; 
char st_out(float **X, float **Y, char inerr, ofstream *out, int N)
{
	int i, j;
	//cout << "st_out entered" << endl;
	cout << "Greetings, unreg_user" << endl << "Program by: Isakov, gr.#9309" << endl;
	cout << "Task: Find amount of convex quadrangles, based on dots from file" << endl;
	cout << "ver. 1.3.14" << endl;
	cout << "Started: 1 dec." << endl << "Completed: tbd " << endl;
	cout << "Open kursach_out.txt for results" << endl;
	cout << "Open process.txt for processed data";
	*out << "Found amount of dots: " << N << endl;
	*out << "The dots are following:" << endl;
	for (i = 0; i < N; i++)
	{
		if (j %6 == 0)
		{
			*out << '(' << *(*X + i) << " ; " << *(*Y + i) << ')' << endl;
		}
		else *out << '(' << *(*X + i) << " ; " << *(*Y + i) << ")  ";
		if (i == N - 1) *out << endl;
		j++;
	}
}
char input(float **X, float **Y, int *N)
{
	int c = 0;
	char s;
	float t;
	ifstream in;
	in.open("k_in_4.txt");
	
	if (in.is_open())
	{
		in >> *N;
		*X = new float[*N];
		*Y = new float[*N];
		if (*N >= 4)
		{
			while ((c <= *N) && (!in.eof()))
			{
				in >> skipws >> s;
				if (s == '(')
				{
					do 
					{
						in >> noskipws >> s;
						if ((s == '0')||(s == '1')||(s == '2')||(s == '3')||(s == '4')||(s == '5')||(s == '6')||(s == '7')||(s == '8')||(s == '9')||(s == '-'))
						{
							in.putback(s);
							in >> skipws >> t;
							*(*X + c) = t;
							//cout << "Pre-break situation 1" << endl;
							break;	
						}
					}
					while (1);
					do 
					{
						in >> noskipws >> s;
						if ((s == '0')||(s == '1')||(s == '2')||(s == '3')||(s == '4')||(s == '5')||(s == '6')||(s == '7')||(s == '8')||(s == '9')||(s == '-'))
						{
							in.putback(s);
							in >> skipws >> t;
							*(*Y + c) = t;
							c++;
							//cout << "Pre-break situation 2" << endl;
							break;	
						}
					}
					while (1);
				}
			}
		}
		else 
		{
			in.close();
			return 'l'; // less input then needed
		}	
		in.close();
	}
	else 
	{
		in.close();
		return 'i'; // input file error
	}
	//cout << "Input exited" << endl;
}
char intersect(float **X, float **Y, int i, int j, int k, int m, float Eps, ofstream *p)
{
	//cout << "intersect entered" << endl;
	/*cout << "	i = " << i << endl;
	cout << "	j = " << j << endl;
	cout << "	k = " << k << endl;
	cout << "	m = " << m << endl;*/
	float z1, z2, z3, z4;
	z1 = (*(*X + k) - *(*X + i)) * (*(*Y + j) - *(*Y + i)) - (*(*Y + k) - *(*Y + i)) * (*(*X + j) - *(*X + i));
	//cout << "	z1 = " << z1 << endl;
	z2 = (*(*X + m) - *(*X + i)) * (*(*Y + j) - *(*Y + i)) - (*(*Y + m) - *(*Y + i)) * (*(*X + j) - *(*X + i));
	//cout << "	z2 = " << z2 << endl;
	z3 = (*(*X + i) - *(*X + k)) * (*(*Y + m) - *(*Y + k)) - (*(*Y + i) - *(*Y + k)) * (*(*X + m) - *(*X + k));
	//cout << "	z3 = " << z3 << endl;
	z4 = (*(*X + j) - *(*X + k)) * (*(*Y + m) - *(*Y + k)) - (*(*Y + j) - *(*Y + k)) * (*(*X + m) - *(*X + k));
	//cout << "	z4 = " << z4 << endl;
	if (!(z1 * z2 > 0) && !(z3 * z4 > 0))
	{
		*p << "Lines " << "( " << *(*X + i) << " , " << *(*Y + i) << " )" << "( "<< *(*X + j) << " , " << *(*Y + j) << " )" << " and " << "( "<< *(*X + k) << " , " << *(*Y + k) << " )" << "( "<< *(*X + m) << " , " << *(*Y + m) << " )" << " cross" << endl << endl;
		{
			if (!(fabs((*(*X + k) - *(*X + i)) * (*(*Y + j) - *(*Y + i)) - (*(*Y + k) - *(*Y + i)) * (*(*X + j) - *(*X + i))) < Eps))
			{
				if (!(fabs((*(*X + m) - *(*X + i)) * (*(*Y + j) - *(*Y + i)) - (*(*Y + m) - *(*Y + i)) * (*(*X + j) - *(*X + i))) < Eps))
				{	
					if (!(fabs((*(*X + i) - *(*X + k)) * (*(*Y + m) - *(*Y + k)) - (*(*Y + i) - *(*Y + k)) * (*(*X + m) - *(*X + k))) < Eps))
					{
						if (!(fabs((*(*X + j) - *(*X + k)) * (*(*Y + m) - *(*Y + k)) - (*(*Y + j) - *(*Y + k)) * (*(*X + m) - *(*X + k))) < Eps))
						{
							*p << "Dots: " << "( "<< *(*X + i) << " , " << *(*Y + i) << " )" << "( "<< *(*X + m) << " , " << *(*Y + m) << " )" << "( "<< *(*X + j) << " , " << *(*Y + j) << " )" << "( "<< *(*X + k) << " , " << *(*Y + k) << " ) " << "create a convex quadrangle" << endl << endl;
							return 'y';
						}
					}
				}
			}
				*p << "Dots: " << "( "<< *(*X + i) << " , " << *(*Y + i) << " )" << "( "<< *(*X + m) << " , " << *(*Y + m) << " )" << "( "<< *(*X + j) << " , " << *(*Y + j) << " )" << "( "<< *(*X + k) << " , " << *(*Y + k) << " ) " << "do not create a convex quadrangle" << endl << endl;
				//cout << "intersect exited" << endl;
				return 'n';
		}
	}
	else *p <<  "Lines " << "( "<< *(*X + i) << " , " << *(*Y + i) << " )" << "( "<< *(*X + j) << " , " << *(*Y + j) << " )" << " and " << "( "<< *(*X + k) << " , " << *(*Y + k) << " )" << "( "<< *(*X + m) << " , " << *(*Y + m) << " )" << " do not cross" << endl;
	//cout << "intersect exited" << endl;
}
char analysys(float **X, float **Y, int N, float Eps, int *i, int *j, int *k, int *m, ofstream *out)
{
	//cout << "Analysys entered" << endl;
	char oc;
	int fl1 = 0, fl2;
	ofstream p;
	p.open("process.txt");
	if (p.is_open())
	{
		p << "This is processing file. Processed data as follows:" << endl << endl;
		for (*i = 0; *i < N - 3; *i += 1)
		{
			//cout << "i= " << *i << endl;
			for (*j = *i + 1; *j < N; *j += 1)
			{
				//cout << "j= " << *j << endl;
				if ((fabs(*(*X +*i)- *(*X +*j)) < Eps) && (fabs(*(*Y +*i) - *(*Y +*j)) < Eps))
				{
					fl1++;
					p << "Error: Dots " << *i << " and " << *j << " are too close" << endl;
					if (fl1 > N - 2)
					{
						p << "Error: all given dots are too close" << endl;
						return 'a'; 
					}
					else 
					{
						continue;
					}
				}
				else
				{
					fl2 = 0;
					for (*k = *i + 1; *k < N; *k += 1)
					{
						if ((*k == *i) || (*k == *j))
						{
							*k += 1;
							if (*k == N)
							{
								continue;
							}
						}
						//cout << "k = " << *k << endl;
						for (*m = *k + 1; *m < N ; *m += 1)
						{
							if ((*m == *i) || (*m == *j)) 
							{
								*m += 1;
								if (*m == N)
								{
									continue;
								}
							}
							//cout << "m = " << *m << endl;
							//cout << "Abstract of m - k = " << fabs( (*(*X + *m)) - (*(*X + *k))) << endl;
							if (((fabs( *(*X + *m) - *(*X + *k))) < Eps) && (fabs( *(*Y +*m) - *(*Y +*k))) < Eps)
							{
								fl2 = fl1 + 1;
								p << "Error: Dots " << *m << " and " << *k << " are too close" << endl;
								if (fl2 > N - 2) 
								{
									p << "Error: all given dots are too close" << endl;
									return 'a'; 
								}
								if ((fl1 + fl2) > N - 2) 
								{
									p << "Error: all given dots are too close" << endl;
									return 'a'; 
								}
								continue;
							}
							else 
							{
								oc = intersect(X, Y, *i, *j, *k, *m, Eps, &p);
								if (oc == 'y')
								{
									//cout << "Got to the out point" << endl;
									*out << "Dots: " << "( " << *(*X + *i) << " , " << *(*Y + *i) << " )" << "( "<< *(*X + *m) << " , " << *(*Y + *m) << " )" << "( "<< *(*X + *j) << " , " << *(*Y + *j) << " )" << "( "<< *(*X + *k) << " , " << *(*Y + *k) << " ) " << "create a convex quadrangle" << endl;
								}
							}
						}
					}
				}
			}
		}
	p.close();
	}
	else 
	{	
		p.close();
		return 'p'; //process file error
	}
}
int main(void)
{
	int i = 0, j = 0, k = 0, m = 0, N; 
	float Eps = 1e-3;
	float *X; 
	float *Y;
	char inerr, err;
	ofstream out;
	out.open("kursach_out.txt");
	if (out.is_open())
	{
		inerr = input (&X, &Y, &N);
		if (inerr == 'l')
		{
			cout << "Error: less than 4 dots found" << endl;
			out << "Error: less than 4 dots found" << endl;
		}
		else if(inerr == 'i')
		{
			cout << "Error: input error occured" << endl;
			out << "Error: input error occured" << endl;
		}
		else
		{
			st_out(&X, &Y, inerr, &out, N);
			err = analysys (&X, &Y, N, Eps, &i, &j, &k, &m, &out);
			if (err == 'a') return 0;
		}
		out.close();
	}
	else cout << "Output file error" <<endl;
	delete[]X; X = NULL;
	delete[]Y; Y = NULL;
}
