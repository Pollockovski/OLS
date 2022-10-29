#include"MyMath.h"
using namespace std;
double pi = 3.1415927;
double e = 2.71828183;

double k = 0, b = 0;
double a21, a22, a23;

double sum(vector<double>tmp)//从i=1开始
{
	double tmp_ans = 0;
	for (int i = 0; i < tmp.size(); i++)
	{
		tmp_ans += tmp[i];
	}
	return tmp_ans;
}

double avr(vector<double>tmp)
{
	double tmp_ans = 0;
	for (int i = 0; i < tmp.size(); i++)
	{
		tmp_ans += tmp[i];
	}
	return tmp_ans / tmp.size();
}

double f1(double x)//y=ax+b
{
	return k * x + b;
}

double S1(vector<double>tmp_x, vector<double>tmp_y)
{
	double tmp_ans = 0;
	for (int i = 0; i < tmp_x.size(); i++)
	{
		tmp_ans += (tmp_y[i] - f1(tmp_x[i])) * (tmp_y[i] - f1(tmp_x[i]));
	}
	tmp_ans /= tmp_x.size();
	tmp_ans = sqrt(tmp_ans);
	return tmp_ans;
}

double f2(double x)//y=a1x^2+a2x+a3
{
	return a21 * x * x + a22 * x + a23;
}

double S2(vector<double>tmp_x, vector<double>tmp_y)
{
	double tmp_ans = 0;
	for (int i = 0; i < tmp_x.size(); i++)
	{
		tmp_ans += (tmp_y[i] - f2(tmp_x[i])) * (tmp_y[i] - f2(tmp_x[i]));
	}
	tmp_ans /= tmp_x.size();
	tmp_ans = sqrt(tmp_ans);
	return tmp_ans;
}

void main()
{
	vector<double>x;
	vector<double>y;
	vector<double>xy;
	vector<double>xx;
	matrix D2, D21, D22, D23;
	int num = 0;
	double S = 0;
	cout << "请输入有多少个数据:";//请输入有多少个数据:
	cin >> num;
	x.resize(num);
	y.resize(num);
	xy.resize(num);
	xx.resize(num);
	cout << "请依次输入x:" << endl;//请依次输入x
	for (int i = 0; i < x.size(); i++)
	{
		cin >> x[i];
	}
	cout << "请依次输入y:" << endl;//请依次输入y
	for (int i = 0; i < y.size(); i++)
	{
		cin >> y[i];
	}
	for (int i = 0; i < xy.size(); i++)
	{
		xy[i] = x[i] * y[i];
	}
	for (int i = 0; i < xx.size(); i++)
	{
		xx[i] = x[i] * x[i];
	}
	//线性拟合
	k = (num * sum(xy) - sum(x) * sum(y)) / (num * sum(xx) - sum(x) * sum(x));
	b = avr(y) - k * avr(x);
	if (b >= 0)
	{
		printf("y=%fx+%f\n", k, b);
	}
	else {
		printf("y=%fx-%f\n", k, -b);
	}
	printf("S=%f\n", S1(x, y));
	//二次函数拟合
	vector<double>xxx, xxxx, yxx;
	xxx.resize(num);
	xxxx.resize(num);
	yxx.resize(num);
	for (int i = 0; i < xxx.size(); i++)
	{
		xxx[i] = xx[i] * x[i];
	}
	for (int i = 0; i < xxxx.size(); i++)
	{
		xxxx[i] = xxx[i] * x[i];
	}
	for (int i = 0; i < yxx.size(); i++)
	{
		yxx[i] = xy[i] * x[i];
	}
	D2.value = { {sum(xx),sum(x),double(num)},{sum(xxx),sum(xx),sum(x)},{sum(xxxx),sum(xxx),(sum(xx))} };
	D21.value = { {sum(y),sum(x),double(num)},{sum(xy),sum(xx),sum(x)},{sum(yxx),sum(xxx),(sum(xx))} };
	D22.value = { {sum(xx),sum(y),double(num)},{sum(xxx),sum(xy),sum(x)},{sum(xxxx),sum(yxx),(sum(xx))} };
	D23.value = { {sum(xx),sum(x),sum(y)},{sum(xxx),sum(xx),sum(xy)},{sum(xxxx),sum(xxx),sum(yxx)} };
	a21 = det(D21) / det(D2);
	a22 = det(D22) / det(D2);
	a23 = det(D23) / det(D2);
	printf("y=%fx^2", a21);
	if (a22 > 0)
	{
		cout << "+";
	}
	cout << a22 << "x";
	if (a23 > 0)
	{
		cout << "+";
	}
	cout << a23 << "x" << endl;
	printf("S=%f\n", S2(x, y));
	system("pause");
}