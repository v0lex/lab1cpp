#define _USE_MATH_DEFINES
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<iterator>
#include<memory>
#include<cmath>

const int MODULE = 9001;
const int N = 1000;
const int A = 3;
const int C = 5;
const int RN = 10;

std::vector<int> congruent(int,int, int = 0);
std::vector<int> fibonachi(int, int, int);
std::vector<int> reverseCongruent(int, int);
std::vector<int> unification(int, int, int);
std::vector<double> threeSigma(int, int);
std::vector<double> polarCoordinates(int, int);
std::vector<double> corelation(int, int);
std::vector<double> exp(int, int, double);
std::vector<double> arens(int, int, int);
std::vector<double> transformVector(std::vector<int>);
std::vector<double> getRanges(double=0., double = 1.);
std::vector<double> frequencyForRanges(std::vector<double>, std::vector<double>);
void printHistogram(std::vector<double>, std::vector<double>);
int findReverse(int);

int main() {
	int a;
	std::cout << std::fixed;
	while (true) {
		std::cout << "Choose method: " << std::endl;
		std::cout << "1 - Linear congruent" << std::endl;
		std::cout << "2 - Quadratic congruent" << std::endl;
		std::cout << "3 - Fibonacci numbers" << std::endl;
		std::cout << "4 - Reverse congruent" << std::endl;
		std::cout << "5 - Unification" << std::endl;
		std::cout << "6 - 3 sigma" << std::endl;
		std::cout << "7 - Polar coordinates" << std::endl;
		std::cout << "8 - Coralation" << std::endl;
		std::cout << "9 - Logarithm" << std::endl;
		std::cout << "10 - Arens" << std::endl;
		std::cout << "11 - Exit" << std::endl;
		std::cin >> a;
		switch (a) {
		case 1: {
			printHistogram(getRanges(), frequencyForRanges(getRanges(), transformVector(congruent(2, N))));
			break;
		}
		case 2: {
			printHistogram(getRanges(), frequencyForRanges(getRanges(), transformVector(congruent(2,N, MODULE))));
			break;
		}
		case 3: {
			printHistogram(getRanges(), frequencyForRanges(getRanges(), transformVector(fibonachi(5,9, N))));
			break;
		}
		case 4: {
			printHistogram(getRanges(), frequencyForRanges(getRanges(), transformVector(reverseCongruent(2, N))));
			break;
		}
		case 5: {
			printHistogram(getRanges(), frequencyForRanges(getRanges(), transformVector(unification(2, 3, N))));
			break;
		}
		case 6: {
			printHistogram(getRanges(-3, 3), frequencyForRanges(getRanges(-3, 3), threeSigma(5, N)));
			break;
		}
		case 7: {
			printHistogram(getRanges(-3, 3), frequencyForRanges(getRanges(-3, 3), polarCoordinates(15, N)));
			break;
		}
		case 8: {
			printHistogram(getRanges(-3, 3), frequencyForRanges(getRanges(-3, 3), corelation(15, N)));
			break;
		}
		case 9: {
			printHistogram(getRanges(0, 100), frequencyForRanges(getRanges(0, 100), exp(15, N, 20)));
			break;
		}
		case 10: {
			printHistogram(getRanges(0, 100), frequencyForRanges(getRanges(0, 100), arens(15, 50, N)));
			break;
		}
		case 11: {
			exit(1);
			break;
		}
		default: {
			std::cout << "Please enter the right number:)" << std::endl;
			break;
		}
		}
	}
}

std::vector<int> congruent(int x,int size, int d) {
	std::vector<int> res{ x };
	for (int i = 1; i < size; ++i) {
		x = (d * x * x + A * x + C) % 101;
		std::cout << x << std::endl;
		res.push_back(x);
	}
	return res;
}

std::vector<int> fibonachi(int x1, int x2, int size) {
	std::vector<int> res{ x1%MODULE, x2 % MODULE };
	res.resize(size);
	for (auto el = res.begin() + 2; el != res.end(); ++el) {
		*el = ( * (el - 2) + *(el - 1))%MODULE;
	}
	return res;
}

int findReverse(int num) {
	for (int i = 1; i < MODULE; i++) {
		if ((num * i) % MODULE == 1) return i;
	}
	return 0;
}

std::vector<int> reverseCongruent(int x, int size) {
	std::vector<int> res{ x };
	for (int i = 1; i < size; ++i) {
		x = (A*findReverse(x)+C) % MODULE;
		res.push_back(x);
	}
	return res;
}

std::vector<int> unification(int x, int y, int size) {
	std::vector<int> xs = congruent(x, size);
	std::vector<int> ys = congruent(y, size);
	std::vector<int> zs;
	for (int i = 0; i < size; ++i) {
		int z = (xs.at(i) - ys.at(i))% MODULE;
		zs.push_back((z < 0) ? (z + MODULE) : z);
	}
	return zs;
}

std::vector<double> transformVector(std::vector<int> x) {
	std::vector<double> y;
	std::transform(x.begin(), x.end(), std::back_inserter(y), [](int el) {
		return (double)el / MODULE;
		});
	return y;
};

std::vector<double> getRanges(double a, double b) {
	std::vector<double> ranges{};
	double h = (b - a) / RN;
	while (a <= b) {
		ranges.push_back(a);
		a += h;
	}
	ranges.push_back(a);
	return ranges;
}

std::vector<double> frequencyForRanges(std::vector<double>ranges, std::vector<double> x) {
	std::vector<double> freq;
	for (int i = 1; i <= RN; ++i) {
		freq.push_back((double)std::count_if(x.begin(), x.end(), [ranges, i](double el) { return (el >= ranges[i - 1]) && (el <= ranges[i]); }) / x.size());
	}
	return freq;
}

void printHistogram(std::vector<double> ranges, std::vector<double> freqs) {
	std::cout << std::setw(15) << "Interval" << std::setw(15) << "Frequency" << std::endl;
	for (int i = 1; i <= RN; i++) {
		std::cout << "[" << std::setw(6) << std::setprecision(2)<< ranges.at(i - 1) << ";" << std::setw(6) << std::setprecision(2) << ranges.at(i) << "]" << std::setw(15) << std::setprecision(2) << freqs.at(i-1) << std::endl;
	}
	std::cout << std::endl;
}

std::vector<double> threeSigma(int num, int size) {
	int newSize = 12 * size;
	std::vector<int> xs = congruent(num, newSize);
	std::vector<double> xsd = transformVector(xs);
	std::vector<double> res;
	double sum = 0;
	for (int i = 1; i < newSize; ++i) {
		sum += xsd.at(i);
		if (!(i % 12)) {
			res.push_back((sum - 6));
			sum = 0;
		}
	}
	return res;
}

std::vector<double> polarCoordinates(int num, int size) {
	std::vector<int> xs = congruent(num, size);
	std::vector<double> xsd = transformVector(xs);
	std::vector<double> res;
	for (auto p = xsd.begin(); p != xsd.end(); p += 2) {
		double v1 = (*p) * 2 - 1;
		double v2 = (*(p+1)) * 2 - 1;
		double s = pow(v1, 2) + pow(v2, 2);
		if (s >= 1) continue;
		res.push_back(v1 * pow((-2 * log(s) / s), 1. / 2));
		res.push_back(v2 * pow((-2 * log(s) / s), 1. / 2));
	}
	return res;
}

std::vector<double> corelation(int num, int size) {
	std::vector<int> xs = congruent(num, size);
	std::vector<double> xsd = transformVector(xs);
	std::vector<int> us = reverseCongruent(num, size);
	std::vector<double> usd = transformVector(us);
	std::vector<double> res;
	double coef = sqrt(8 / M_E);
	for (int i = 0; i < size; ++i) {
		if (usd.at(i)) {
			double x = coef * ((xsd.at(i) - 1./2) / usd.at(i));
			if (x * x <= (-4 * log(usd.at(i)))) res.push_back(x);
		}
	}
	return res;
}

std::vector<double> exp(int num, int size, double y) {
	std::vector<int> xs = congruent(num, size);
	std::vector<double> xsd = transformVector(xs);
	std::vector<double> res;
	for (auto p = xsd.begin(); p != xsd.end(); ++p){
		if (*p) {
			res.push_back(-y * log(*p));
		}
	}
	return res;
}

std::vector<double> arens(int num, int a, int size) {
	std::vector<int> xs = congruent(num, size);
	std::vector<double> xsd = transformVector(xs);
	std::vector<int> vs = reverseCongruent(num, size);
	std::vector<double> vsd = transformVector(vs);
	std::vector<double> res;
	for (int i = 0; i < size; ++i) {
		double y = tan(M_PI * xsd.at(i));
		double x = sqrt(2 * a - 1) * y + a - 1;
		if (x <= 0) continue;
		if ((vsd.at(i)) <= (1 + y * y) * exp((a - 1) * log(x / (a - 1)) - sqrt(2 * a - 1) * y)) {
			res.push_back(x);
		}
	}
	return res;
}





	


