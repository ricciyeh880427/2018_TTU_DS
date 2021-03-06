#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr)
{
	linkedPolynomialTerm *tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
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

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo)
{
	linkedPolynomialTerm *tmpPtr;
	// 先將要儲存的係數跟次方存入結構
	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;
	
	// add your code here
	if (polyPtr == nullptr) {	// 第一件事情，先確定傳進來的鏈表是空的嗎? 是空的就直接賦值進去
		polyPtr = tmpPtr;
		polyPtr->nextTermPtr = nullptr;
	}
	else {						// 第二件事情，插入賦值
		linkedPolynomialTerm *CurPolyPtr, *PrePolyPtr;
		CurPolyPtr = polyPtr;	// 目前位置在polyPtr的第一位
		PrePolyPtr = nullptr;	// 前一個位置設在空位置

		while (CurPolyPtr != NULL && CurPolyPtr->expo > expo) {
			// CurPolyPtr還不到鏈表的末端，同時次方項的值得小於次方項的值(由大排到小)
			PrePolyPtr = CurPolyPtr;	// 紀錄位置，這是等等插入值的前面一個Node
			CurPolyPtr = CurPolyPtr->nextTermPtr;	// 移到下面一位
		}
		
		if (PrePolyPtr != NULL) {
			// 代表插入的值在表列的中間
			if (CurPolyPtr != nullptr && CurPolyPtr->expo == tmpPtr->expo) {
				// CurPolyPtr != nullptr，意思是如果有存過了，那地址就不會為nullptr
				// 題目要求有相同的冪次重覆輸入，則以最後輸入的係數為主。
				// 將CurPolyPtr的係數直接取代
				CurPolyPtr->coef = tmpPtr->coef;
			}
			else {
				// 舉例: 如果現在是 3 -> 1, 2 要插入
				//		 3 = PrePolyPtr, 1 = CurPolyPtr, 2 = tmpPtr;
				//		 將 3 的後面接上 2 ，變 3 -> 2。 3 分離
				//		 將 2 的後面接上 1 ，變 3 -> 2 -> 1。完成
				PrePolyPtr->nextTermPtr = tmpPtr;
				// 把下一個地址存到上一個節點的nextTermPtr
				tmpPtr->nextTermPtr = CurPolyPtr;
				// 將目前節點的下一個節點位置存入現在節點
			}
		}
		else {
			// 否則將成為開頭
			if (tmpPtr->expo == CurPolyPtr->expo) {
				// 題目要求有相同的冪次重覆輸入，則以最後輸入的係數為主。
				CurPolyPtr->coef = tmpPtr->coef;
				// 將現在節點的係數取代掉
			}
			else {
				// 舉例: 如果現在是 2 -> 1, 3 要變開頭
				//		 2 = CurPolyPtr, 3 = tmpPtr;
				//		 將 3 的後面接上 2 ，變 3 -> 2。
				//		 再將 3 的地址存回去鏈表polyPtr。完成。
				tmpPtr->nextTermPtr = CurPolyPtr;
				// 將tmpPtr作為開頭
				polyPtr = tmpPtr;	// 存回去鏈表polyPtr
			}
		}
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

linkedPolynomialTerm *attach(linkedPolynomialTerm *pCurrent, linkedPolynomialTerm *dCurrent)
{
	// 先將要儲存的係數跟次方存入結構
	linkedPolynomialTerm *tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = pCurrent->coef;
	tmpPtr->expo = pCurrent->expo;
	tmpPtr->nextTermPtr = nullptr;
	
	dCurrent->nextTermPtr = tmpPtr;	// 將現在要儲存的節點接入現在的節點
	
	return dCurrent->nextTermPtr; // 回傳儲存的節點的位置
}

linkedPolynomialTerm *addLinkBasedPoly(linkedPolynomialTerm *aPtr, linkedPolynomialTerm *bPtr)
{
	linkedPolynomialTerm *dPtr = nullptr;
	// add your code here
	// ==========另有多寫attach做處理，在181行==========
	linkedPolynomialTerm *aCurrent, *bCurrent, *dCurrent;	// 紀錄每個鏈表的位置
	aCurrent = aPtr;	// 紀錄 aCurrent 的起始位置
	bCurrent = bPtr;	// 紀錄 bCurrent 的起始位置

	while (aCurrent != nullptr && bCurrent != nullptr) {
		// 迴圈終止條件為只要有一個鏈表不是空位置，那等迴圈結束最後再去存剩下的
		if (aCurrent->expo > bCurrent->expo) {
			// 先判定哪一個指數比較大，先存大的，這邊處理 aPtr
			if (!dPtr) {	// 若鏈表 dPtr 是空的
				linkedPolynomialTerm *tmpPtr = new linkedPolynomialTerm;	// 設一個新的節點 tmpPtr 暫時存入
				tmpPtr->coef = aCurrent->coef;	// 存入係數
				tmpPtr->expo = aCurrent->expo;	// 存入指數
				dPtr = tmpPtr;		// 將 dPtr 的開頭設為 tmpPtr
				dCurrent = dPtr;	// 現在 dPtr 的位置用 dCurrent 紀錄
				tmpPtr = nullptr;	// 將 tmpPtr 設為 nullptr
			}
			else
				dCurrent = attach(aCurrent, dCurrent);	// 在鏈表尾端接入節點，並且移位
			aCurrent = aCurrent->nextTermPtr;	// 移動節點位置
		}
		else if (aCurrent->expo == bCurrent->expo) {
			// 指數一樣，要將係數相加存入
			if (aCurrent->coef + bCurrent->coef != 0) {
				// 如果係數相加不為零再做處理
				linkedPolynomialTerm *tmpPtr = new linkedPolynomialTerm;	// 設一個新的節點 tmpPtr 暫時存入
				tmpPtr->coef = aCurrent->coef + bCurrent->coef;	// 存入係數
				tmpPtr->expo = aCurrent->expo;	// 存入指數
				
				if (!dPtr) {			// 若鏈表 dPtr 是空的
					dPtr = tmpPtr;		// 將 dPtr 的開頭設為 tmpPtr
					dCurrent = dPtr;	// 現在 dPtr 的位置用 dCurrent 紀錄
					tmpPtr = nullptr;	// 將 tmpPtr 設為 nullptr
				}
				else
					dCurrent = attach(tmpPtr, dCurrent);	// 在鏈表尾端接入節點，並且移位
			}
			aCurrent = aCurrent->nextTermPtr;	// 移動節點位置
			bCurrent = bCurrent->nextTermPtr;	// 移動節點位置
		}
		else if (aCurrent->expo < bCurrent->expo) {
			// 先判定哪一個指數比較大，先存大的，這邊處理 bPtr
			if (!dPtr) {	// 若鏈表 dPtr 是空的
				linkedPolynomialTerm *tmpPtr = new linkedPolynomialTerm;	// 設一個新的節點 tmpPtr 暫時存入
				tmpPtr->coef = bCurrent->coef;	// 存入係數
				tmpPtr->expo = bCurrent->expo;	// 存入指數
				dPtr = tmpPtr;		// 將 dPtr 的開頭設為 tmpPtr
				dCurrent = dPtr;	// 現在 dPtr 的位置用 dCurrent 紀錄
				tmpPtr = nullptr;	// 將 tmpPtr 設為 nullptr
			}
			else
				dCurrent = attach(bCurrent, dCurrent);	// 在鏈表尾端接入節點，並且移位
			bCurrent = bCurrent->nextTermPtr;	// 移動節點位置
		}
	}

	// 因為不知道剛剛的鏈表是哪一個沒跑到尾端，因此都輪一遍
	while (aCurrent) {
		dCurrent = attach(aCurrent, dCurrent);	// 在鏈表尾端接入節點，並且移位
		aCurrent = aCurrent->nextTermPtr;		// 移動節點位置
	}
	while (bCurrent) {
		dCurrent = attach(bCurrent, dCurrent);	// 在鏈表尾端接入節點，並且移位
		bCurrent = bCurrent->nextTermPtr;		// 移動節點位置
	}
	
	dCurrent->nextTermPtr = nullptr;	// 將下一個節點設為空的，視為結束
	
	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if (terms[0].coef == 0)
		return;

	if (terms[0].expo == 0)
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (terms[i].coef == 0)
			return;

		if (terms[i].expo == 0)
			cout << " + " << terms[i].coef;
		else
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr = polyPtr;

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
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}