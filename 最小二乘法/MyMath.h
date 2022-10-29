#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct complex {
	double im;
	double re;
};

int powm1(int tmp)
{
	if (tmp % 2 == 0)
	{
		return 1;
	}
	else {
		return -1;
	}
}

class matrix {
public:
	vector<vector<double>> value;
	matrix operator+(const matrix& b) {
		matrix tmp = b;
		if (value.size() != b.value.size())
		{
			return tmp;
		}
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i].size() != b.value[i].size())
			{
				return tmp;
			}
		}
		for (int i = 0; i < tmp.value.size(); i++)
		{
			for (int j = 0; j < tmp.value[i].size(); j++)
			{
				tmp.value[i][j] = value[i][j] + b.value[i][j];
			}
		}
		return tmp;
	}
	matrix operator*(const matrix& b)
	{
		matrix tmp = b;
		if (value[0].size() != b.value.size())
		{
			return tmp;
		}
		tmp.value.resize(value.size());
		for (int i = 0; i < tmp.value.size(); i++)
		{
			tmp.value[i].resize(b.value[0].size());
		}
		for (int i = 0; i < tmp.value.size(); i++)
		{
			for (int j = 0; j < tmp.value.size(); j++)
			{
				tmp.value[i][j] = 0;
				for (int k = 0; k < value[0].size(); k++)
				{
					tmp.value[i][j] += value[i][k] * b.value[k][j];
				}
			}
		}
		return tmp;
	}
	//matrix(int m, int n);
};

/*matrix::matrix(int m, int n)
{
	//string str;
	//cout << "Please input matrix" << endl;
	//cin >> str;
	value.resize(n);
	for (int i = 0; i < value.size(); i++)
	{
		value[i].resize(m);
	}
}*/

/*matrix::matrix()
{
	int m, n;
	cout << "Input the size of the row:";//行数
	cin >> m;
	cout << "Input the size of the column:";//列数
	cin >> n;
	value.resize(m);
	for (int i = 0; i < value.size(); i++)
	{
		value[i].resize(n);
	}
	for (int i = 0; i < value.size(); i++)
	{
		for (int j = 0; j < value[i].size(); j++)
		{
			printf("[%d,%d]:", i + 1, j + 1);
			cin >> value[i][j];
		}
	}
}*/

void print(matrix tmp)
{
	for (int i = 0; i < tmp.value.size(); i++)
	{
		cout << "{";
		for (int j = 0; j < tmp.value[i].size(); j++)
		{
			cout << tmp.value[i][j] << ",";
		}
		cout << "}" << endl;
	}
}

matrix T(matrix tmp)
{
	matrix tmp1 = tmp;
	tmp1.value.resize(tmp.value[0].size());
	for (int i = 0; i < tmp1.value.size(); i++)
	{
		tmp1.value[i].resize(tmp.value.size());
	}
	for (int i = 0; i < tmp1.value.size(); i++)
	{
		for (int j = 0; j < tmp1.value[i].size(); j++)
		{
			tmp1.value[i][j] = tmp.value[j][i];
		}
	}
	return tmp1;
}

matrix minorMatrix(matrix tmp_mtx, int m, int n)
{
	if (tmp_mtx.value.size() != tmp_mtx.value[0].size())
	{
		return tmp_mtx;
	}
	if (tmp_mtx.value.size() == 1)
	{
		return tmp_mtx;
	}
	matrix tmp_ans = tmp_mtx;
	tmp_ans.value.resize(tmp_mtx.value.size() - 1);
	for (int i = 0; i < tmp_ans.value.size(); i++)
	{
		tmp_ans.value[i].resize(tmp_mtx.value.size() - 1);
	}
	for (int i = 0; i < tmp_ans.value.size(); i++)
	{
		for (int j = 0; j < tmp_ans.value.size(); j++)
		{
			if (i < m - 1 && j < n - 1)
			{
				tmp_ans.value[i][j] = tmp_mtx.value[i][j];
			}
			else if (i >= m - 1 && j < n - 1)
			{
				tmp_ans.value[i][j] = tmp_mtx.value[i + 1][j];
			}
			else if (i < m - 1 && j >= n - 1)
			{
				tmp_ans.value[i][j] = tmp_mtx.value[i][j + 1];
			}
			else {
				tmp_ans.value[i][j] = tmp_mtx.value[i + 1][j + 1];
			}
		}
	}
	return tmp_ans;
}

double det(matrix tmp)
{
	if (tmp.value.size() != tmp.value[0].size())
	{
		cout << 0 << endl;
		return 0;
	}
	if (tmp.value.size() == 2)
	{
		return tmp.value[0][0] * tmp.value[1][1] - tmp.value[1][0] * tmp.value[0][1];
	}
	double tmp_ans = 0;
	for (int i = 0; i < tmp.value.size(); i++)
	{
		tmp_ans += tmp.value[0][i] * powm1(i) * det(minorMatrix(tmp, 1, i + 1));
	}
	return tmp_ans;
}