#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if (t[0].coef == 0)
		return;

	if (t[0].expo == 0)
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (t[i].coef == 0)
			return;

		if (t[i].expo == 0)
			cout << " + " << t[i].coef;
		else
			cout << " + " << t[i].coef << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm terms[], int coef, int expo)
{
	// add your code here
	int CurTerm = 0, LastTerm = MAX_TERMS;

	if (coef != 0) { // 係數為零不用看
		while (terms[CurTerm].expo > expo)	// 找到插入的位置
			CurTerm++;

		if (terms[CurTerm].expo != expo) {
			// 題目要求有相同的冪次重覆輸入，則以最後輸入的係數為主。
			while (LastTerm-- > CurTerm) {
				// 為了要插入，因此把要插入位置後的都往後移
				terms[LastTerm].expo = terms[LastTerm - 1].expo;
				terms[LastTerm].coef = terms[LastTerm - 1].coef;
			}
		}
		// 放入次方項跟系數項
		terms[CurTerm].expo = expo;
		terms[CurTerm].coef = coef;
	}

	return;
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	// add your code here
	int TermA = 0, TermB = 0, TermD = 0; // 紀錄每個陣列的位置，初始值為零

	while (a[TermA].coef != 0 || b[TermB].coef != 0) {
		// 迴圈終止條件為係數不為0
		if (a[TermA].expo > b[TermB].expo) {
			// 由大排到小，所以先判定哪一個比較大，先存大的
			d[TermD].expo = a[TermA].expo;
			d[TermD].coef = a[TermA].coef;
			// 移動陣列位置
			TermA++;
			TermD++;
		}
		else if (a[TermA].expo == b[TermB].expo) {
			// 如果次方項一樣，將係數相加存入
			if (a[TermA].coef + b[TermB].coef != 0) {
				// 如果相加不為零再做處理
				d[TermD].coef = a[TermA].coef + b[TermB].coef;
				d[TermD].expo = a[TermA].expo;
				// 這時 Array D 再移動陣列位置
				TermD++;
			}
			// 不管如何 Array A&B 都要移動陣列位置
			TermA++;
			TermB++;
		}
		else if (a[TermA].expo < b[TermB].expo) {
			// 由大排到小，所以先判定哪一個比較大，先存大的
			d[TermD].expo = b[TermB].expo;
			d[TermD].coef = b[TermB].coef;
			// 移動陣列位置
			TermB++;
			TermD++;
		}
	}

	return;
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear(a); clear(b); clear(d);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(a, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(b, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);
		cout << "\n";
	}

	return 0;
}
