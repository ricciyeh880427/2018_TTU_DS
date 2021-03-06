#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};                                                                          /////

class ArrayPolynomial {                                        /////
public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) /////
	{
		// add your code here
		int CurTerm = 0, LastTerm = MAX_TERMS;

		if (coef != 0) {
			while (terms[CurTerm].expo > expo)
				CurTerm++;

			if (terms[CurTerm].expo != expo) {
				while (LastTerm-- > CurTerm) {
					terms[LastTerm].expo = terms[LastTerm - 1].expo;
					terms[LastTerm].coef = terms[LastTerm - 1].coef;
				}
			}
			terms[CurTerm].expo = expo;
			terms[CurTerm].coef = coef;
		}
		return;
	}

	void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b) /////
	{
		// add your code here
		int TermA = 0, TermB = 0, TermD = 0;

		while (a.terms[TermA].coef != 0 || b.terms[TermB].coef != 0) {
			if (a.terms[TermA].expo > b.terms[TermB].expo) {
				terms[TermD].expo = a.terms[TermA].expo;
				terms[TermD].coef = a.terms[TermA].coef;
				TermA++;
				TermD++;
			}
			else if (a.terms[TermA].expo == b.terms[TermB].expo) {
				if (a.terms[TermA].coef + b.terms[TermB].coef != 0) {
					terms[TermD].coef = a.terms[TermA].coef + b.terms[TermB].coef;
					terms[TermD].expo = a.terms[TermA].expo;
					TermD++;
				}
				TermA++;
				TermB++;
			}
			else if (a.terms[TermA].expo < b.terms[TermB].expo) {
				terms[TermD].expo = b.terms[TermB].expo;
				terms[TermD].coef = b.terms[TermB].coef;
				TermB++;
				TermD++;
			}
		}

		return;
	}

	void reverseArrayBasedPoly() /////
	{
		// add your code here
		int CurTerm = 0, LastTerm = MAX_TERMS - 1, TempCoef, TempExpo;
		while (terms[LastTerm].coef == 0)
			LastTerm--;
		while (LastTerm > CurTerm) {
			// 兩數互換
			TempCoef = terms[LastTerm].coef;
			TempExpo = terms[LastTerm].expo;

			terms[LastTerm].coef = terms[CurTerm].coef;
			terms[LastTerm].expo = terms[CurTerm].expo;

			terms[CurTerm].coef = TempCoef;
			terms[CurTerm].expo = TempExpo;

			LastTerm--;
			CurTerm++;
		}

		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x)
	{
		// add your code here
		int CurTerm = 0, LastTerm = MAX_TERMS, Number = 0;
		// CurTerm 記錄當前方程式位置、LastTerm 為方程式末端、Number 為算的值
		while (CurTerm < MAX_TERMS && terms[CurTerm].coef != 0) {
			// 迴圈終止條件: CurTerm 未到尾端並且係數不為 0
			int CountX = 1, CurrentExpo = terms[CurTerm].expo;
			while (CurrentExpo--)
				CountX *= x;
			Number += CountX * terms[CurTerm].coef;

			CurTerm++;
		}
		return Number;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm *polyPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polyPtr != nullptr) {
			tmpPtr = polyPtr;
			polyPtr = polyPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
		LinkedPolynomialTerm *tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;

		// add your code here 
		if (polyPtr == nullptr) {
			polyPtr = tmpPtr;
			polyPtr->nextTermPtr = nullptr;
		}
		else {
			LinkedPolynomialTerm *CurPolyPtr, *PrePolyPtr;
			CurPolyPtr = polyPtr;
			PrePolyPtr = nullptr;

			while (CurPolyPtr != NULL && CurPolyPtr->expo > expo) {
				PrePolyPtr = CurPolyPtr;
				CurPolyPtr = CurPolyPtr->nextTermPtr;
			}

			if (PrePolyPtr != NULL) {
				if (CurPolyPtr != nullptr && CurPolyPtr->expo == tmpPtr->expo) {
					CurPolyPtr->coef = tmpPtr->coef;
				}
				else {
					PrePolyPtr->nextTermPtr = tmpPtr;
					tmpPtr->nextTermPtr = CurPolyPtr;
				}
			}
			else {
				if (tmpPtr->expo == CurPolyPtr->expo) {
					CurPolyPtr->coef = tmpPtr->coef;
				}
				else {
					tmpPtr->nextTermPtr = CurPolyPtr;
					polyPtr = tmpPtr;
				}
			}
		}

		return;
	}
	void attach(LinkedPolynomialTerm *pCurrent, LinkedPolynomialTerm *&dCurrent)
	{
		LinkedPolynomialTerm *tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = pCurrent->coef;
		tmpPtr->expo = pCurrent->expo;
		tmpPtr->nextTermPtr = nullptr;

		if (!polyPtr) {
			polyPtr = tmpPtr;
			dCurrent = tmpPtr;
		}

		else {
			dCurrent->nextTermPtr = tmpPtr;
			dCurrent = dCurrent->nextTermPtr;
		}
	}

	void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) /////
	{
		// add your code here
		LinkPolynomial aCurrent, bCurrent;
		aCurrent = aPol;
		bCurrent = bPol;
		LinkedPolynomialTerm *dCurrent = nullptr;

		while (aCurrent.polyPtr != nullptr && bCurrent.polyPtr != nullptr) {
			if (aCurrent.polyPtr->expo > bCurrent.polyPtr->expo) {
				attach(aCurrent.polyPtr, dCurrent);

				aCurrent.polyPtr = aCurrent.polyPtr->nextTermPtr;
			}
			else if (aCurrent.polyPtr->expo == bCurrent.polyPtr->expo) {
				if (aCurrent.polyPtr->coef + bCurrent.polyPtr->coef != 0) {
					LinkedPolynomialTerm *tmpPtr;
					tmpPtr = new LinkedPolynomialTerm;
					tmpPtr->coef = aCurrent.polyPtr->coef + bCurrent.polyPtr->coef;
					tmpPtr->expo = aCurrent.polyPtr->expo;

					attach(tmpPtr, dCurrent);
				}
				aCurrent.polyPtr = aCurrent.polyPtr->nextTermPtr;
				bCurrent.polyPtr = bCurrent.polyPtr->nextTermPtr;
			}
			else if (aCurrent.polyPtr->expo < bCurrent.polyPtr->expo) {
				attach(bCurrent.polyPtr, dCurrent);

				bCurrent.polyPtr = bCurrent.polyPtr->nextTermPtr;
			}
		}
		while (aCurrent.polyPtr != nullptr) {
			attach(aCurrent.polyPtr, dCurrent);

			aCurrent.polyPtr = aCurrent.polyPtr->nextTermPtr;
		}
		while (bCurrent.polyPtr != nullptr) {
			attach(bCurrent.polyPtr, dCurrent);

			bCurrent.polyPtr = bCurrent.polyPtr->nextTermPtr;
		}

		if(dCurrent!= nullptr)
			dCurrent->nextTermPtr = nullptr;

		return;
	}

	void reverseLinkBasedPoly() /////
	{
		// add your code here
		if (polyPtr != nullptr) {
			LinkedPolynomialTerm *PreviousPtr, *CurrentPtr, *NextPtr;
			PreviousPtr = nullptr;
			CurrentPtr = polyPtr;
			NextPtr = polyPtr->nextTermPtr;

			while (NextPtr != nullptr) {
				// 舉例: 如果現在是 1 -> 2 -> 3 要反轉
				//		 1 = CurPolyPtr, 2 = NextPtr, nullptr = PreviousPtr;
				//		 將 CurPolyPtr(1) 的後面接上 PreviousPtr(nullptr) ，變 nullptr <- 1, 2 - > 3。
				//		 將 CurPolyPtr(2) 的後面接上 PreviousPtr(1) ，變 nullptr <- 1 <- 2, 3。
				CurrentPtr->nextTermPtr = PreviousPtr;	// 將 CurrentPtr 指向上一個
				PreviousPtr = CurrentPtr;
				CurrentPtr = NextPtr;
				NextPtr = NextPtr->nextTermPtr;
			}
			// 將 CurPolyPtr(3) 的後面接上 PreviousPtr(2) ，變 nullptr <- 1 <- 2 <- 3。
			CurrentPtr->nextTermPtr = PreviousPtr;
			polyPtr = CurrentPtr; // 更新開頭位置
		}
		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm *termPtr = polyPtr; /////

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	int compute(int x)
	{
		// add your code here
		int Number = 0;
		LinkedPolynomialTerm *dCurrent = polyPtr;
		// dCurrent 記錄當前方程式位置
		while (dCurrent != nullptr) {
			// 迴圈終止條件: dCurrent 未到尾端
			int CountX = 1, CurrentExpo = dCurrent->expo;
			while (CurrentExpo--)
				CountX *= x;
			Number += CountX * dCurrent->coef;

			dCurrent = dCurrent->nextTermPtr;
		}

		return Number;
	}
};

int main()
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

	// aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
					  // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////

		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}