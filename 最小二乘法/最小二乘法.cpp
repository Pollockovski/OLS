#include"MyMath.h"
#include<Windows.h>
using namespace std;
double pi = 3.1415927;
double e = 2.71828183;
double dx = 0.0001;
int num = 0;
vector<double>x;
vector<double>y;
vector<double>xdx;
vector<double>ydy;
vector<double>errx;
vector<double>erry;
vector<double>xy;
vector<double>errxy;
vector<double>xx;
vector<double>errxx;

double k = 0, b = 0, errk = 0, errb = 0;
double a21, a22, a23;

double p2(double tmp_p2)
{
	return(tmp_p2 * tmp_p2);
}

vector<double> muiltipleVector(vector<double> a, vector<double> b)
{
	vector<double>tmp_vct;
	tmp_vct.resize(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		tmp_vct[i] = a[i] * b[i];
	}
	return tmp_vct;
}

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

double fk(vector<double> x1, vector<double> x2)
{
	return (num * sum(muiltipleVector(x1, x2)) - sum(x1) * sum(x2)) / (num * sum(muiltipleVector(x1, x1)) - sum(x1) * sum(x1));
}

double fkdx()
{
	return (fk(xdx, y) - fk(x, y)) / dx;
}

double fkdy()
{
	return (fk(x, ydy) - fk(x, y)) / dx;
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
	char blerrx = 'y';
	cout << "是否考虑x的误差？(Y/N)";
	vector<double>x;
	vector<double>y;
	vector<double>xdx;
	vector<double>ydy;
	vector<double>errx;
	vector<double>erry;
	vector<double>xy;
	vector<double>errxy;
	vector<double>xx;
	vector<double>errxx;
	matrix D2, D21, D22, D23;
	double S = 0; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout << "若考虑，则误差仅供参考，尚未验证！" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin >> blerrx;
	cout << "请输入有多少个数据:";//请输入有多少个数据:
	cin >> num;
	x.resize(num);
	y.resize(num);
	xy.resize(num);
	xx.resize(num);
	errxy.resize(num);
	errxx.resize(num);
	errx.resize(num);
	erry.resize(num);
	xdx.resize(num);
	ydy.resize(num);
	cout << "请依次输入x:" << endl;//请依次输入x
	for (int i = 0; i < x.size(); i++)
	{
		cin >> x[i];
	}
	if (blerrx == 'Y' || blerrx == 'y')
	{
		cout << "请依次输入x的误差:" << endl;//请依次输入x的误差
		for (int i = 0; i < errx.size(); i++)
		{
			cin >> errx[i];
		}
	}
	else {
		for (int i = 0; i < errx.size(); i++)
		{
			errx[i] = 0;
		}
	}
	cout << "请依次输入y:" << endl;//请依次输入y
	for (int i = 0; i < y.size(); i++)
	{
		cin >> y[i];
	}
	cout << "请依次输入y的误差:" << endl;//请依次输入y的误差
	for (int i = 0; i < erry.size(); i++)
	{
		cin >> erry[i];
	}
	for (int i = 0; i < xy.size(); i++)
	{
		xy[i] = x[i] * y[i];
	}
	for (int i = 0; i < errxy.size(); i++)
	{
		errxy[i] = sqrtf(x[i] * x[i] * erry[i] * erry[i] + y[i] * y[i] * errx[i] * errx[i]);
	}
	for (int i = 0; i < xx.size(); i++)
	{
		xx[i] = x[i] * x[i];
	}
	for (int i = 0; i < errxx.size(); i++)
	{
		errxx[i] = sqrtf(2 * x[i] * x[i] * errx[i] * errx[i]);
	}
	for (int i = 0; i < xdx.size(); i++)
	{
		xdx[i] = x[i] + dx;
	}
	for (int i = 0; i < ydy.size(); i++)
	{
		ydy[i] = y[i] + dx;
	}
	cout << xdx[0] << endl;
	//线性拟合
	k = (num * sum(xy) - sum(x) * sum(y)) / (num * sum(xx) - sum(x) * sum(x));
	errk = 0;
	for (int i = 0; i < x.size(); i++)
	{
		errk += p2(erry[i] * (num * x[i] - sum(x)) / (sum(xx) - p2(sum(x)))) + p2(errx[i] * (num * y[i] - sum(y) * (num * sum(xx) - p2(sum(x))) - (num * sum(xy) - sum(x) * sum(y)) * (2 * num * x[i] - 2 * sum(x))) / p2(num * sum(xx) - p2(sum(x))));
	}
	errk = sqrtf(errk);
	//double errka, errkb, errkc, errkd;
	//errka = num * sum(errxy) / (num * sum(xx) - sum(x) * sum(x));
	//errkb = -sum(erry) * sum(x) / (num * sum(xx) - sum(x) * sum(x));
	//errkd = (-sum(x) * sum(x) * sum(y) + 2 * num * sum(xy) * sum(x) - num * sum(xx) * sum(y))*sum(errx) / ((num * sum(xx) - sum(x) * sum(x)) * (num * sum(xx) - sum(x) * sum(x)));
	//errkc = -num * (num * sum(xy) - sum(x) * sum(y))*sum(errxx) / ((num * sum(xx) - sum(x) * sum(x)) * (num * sum(xx) - sum(x) * sum(x)));
	//errk = sqrtf(errka * errka + errkb * errkb + errkc * errkc + errkd * errkd);
	//errk = fkdx();//sqrtf(fkdx() * fkdx() * avr(errx) * avr(errx) + fkdy() * fkdy() * avr(erry) * avr(erry));
	//errk = sum(errxy) + sum(errxx) + sum(errx) + sum(erry);
	b = avr(y) - k * avr(x);
	errb = sqrtf(avr(erry) * avr(erry) + errk * errk * avr(x) * avr(x) + avr(errx) * avr(errx) * k * k);
	if (b >= 0)
	{
		printf("y=%fx+%f\n", k, b);
	}
	else {
		printf("y=%fx-%f\n", k, -b);
	}
	printf("k=%f±%f,\nb=%f±%f,\n", k, errk, b, errb);
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