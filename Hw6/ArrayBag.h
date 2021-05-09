//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Header file for an array-based implementation of the ADT bag.
 @file ArrayBag.h */

 //#ifndef _ARRAY_BAG
 //#define _ARRAY_BAG

#include "BagInterface.h"
#include <cstddef>
#include <string>

template<class ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 6; // Small size to test for a full bag
	ItemType items[DEFAULT_CAPACITY];      // Array of bag items
	int itemCount;                         // Current count of bag items
	int maxItems;                          // Max capacity of the bag

	// Returns either the index of the element in the array items that
	// contains the given target or -1, if the array does not contain
	// the target.
	int getIndexOf(const ItemType& target) const;

public:
	ArrayBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool addFirst(const ItemType& newEntry);
	bool insertFirst(const ItemType& newEntry);
	bool deleteFirst();
	bool removeFirst();
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
}; // end ArrayBag


template<class ItemType>
ArrayBag<ItemType>::ArrayBag() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}  // end if

	return hasRoomToAdd;
}  // end add

/*
// STUB
 template<class ItemType>
 bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
 {
	return false; // STUB
 }  // end remove
*/

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
	int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if

	return canRemoveItem;
}  // end remove

/*
 // STUB
 template<class ItemType>
 void ArrayBag<ItemType>::clear()
 {
	// STUB
 }  // end clear
*/

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int curIndex = 0;       // Current array index
	while (curIndex < itemCount)
	{
		if (items[curIndex] == anEntry)
		{
			frequency++;
		}  // end if

		curIndex++;          // Increment to next entry
	}  // end while

	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}  // end contains

/* ALTERNATE 1: First version
template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& target) const
{
   return getFrequencyOf(target) > 0;
}  // end contains

// ALTERNATE 2: Second version
template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   int curIndex = 0;        // Current array index
   while (!found && (curIndex < itemCount))
   {
	  if (anEntry == items[curIndex])
	  {
		 found = true;
	  } // end if

	  curIndex++;           // Increment to next entry
   }  // end while

   return found;
}  // end contains
*/

template<class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);

	return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
	bool found = false;
	int result = -1;
	int searchIndex = 0;

	// If the bag is empty, itemCount is zero, so loop is skipped
	while (!found && (searchIndex < itemCount))
	{
		if (items[searchIndex] == target)
		{
			found = true;
			result = searchIndex;
		}
		else
		{
			searchIndex++;
		}  // end if
	}  // end while

	return result;
}  // end getIndexOf

template<class ItemType>
bool ArrayBag<ItemType>::addFirst(const ItemType& newEntry)
{
	/*
		1.  �P�_�O�_�٦��Ŷ����J
			itemCount < maxItems
		2.  �p�G���Ŷ�
			�D�حn�D:
				�s����Ĥ@��
				�Ĥ@�ө�̫�@��

			�ҥH�n���N
			items[itemCount] = items[0];
			items[0] = �s��;
			itemCount++;
			return true;
		3.  else
			return false;
	*/
	if(itemCount < maxItems){ // �O�_�٦��Ŷ����J
		items[itemCount] = items[0]; // �Ĥ@�ө�̫�@��
		items[0] = newEntry; // �s����Ĥ@��
		itemCount++;

		return true;
	}
	return false;
}  // end addFirst

template<class ItemType>
bool ArrayBag<ItemType>::insertFirst(const ItemType& newEntry)
{
	/*
		1.  �P�_�O�_�٦��Ŷ����J
			itemCount < maxItems
		2.  �p�G���Ŷ�
			�D�حn�D:
				�s����b�Ĥ@��
			��L�����Ჾ

			�ҥH�n���N
			items[1] ~ items[itemCount] �����Ჾ�@��
			items[0] = �s��;
			itemCount++;
			return true;
		3.  else
			return false;
	*/
	if(itemCount < maxItems){ // �O�_�٦��Ŷ����J
		// ��L�����Ჾ
		for (int locatedIndex = itemCount; locatedIndex > 0; locatedIndex--)
			items[locatedIndex] = items[locatedIndex - 1];

		items[0] = newEntry; // �s����b�Ĥ@��
		itemCount++;

		return true;
	}
	return false;
}  // end insertFirst

template<class ItemType>
bool ArrayBag<ItemType>::removeFirst()
{
	/*
		1.  �P�_�O�_���F��i�H����
			!isEmpty()
		2.  �p�G�i�H����
			�D�حn�D:
				�̫�@�����Ĥ@��

			�ҥH�n���N
			items[0] = items[itemCount]
			itemCount--;
			return true;
		3.  else
				return false;
	*/
	if(!isEmpty()){
		// itemCount �� 6 array �� index �� 5
		items[0] = items[itemCount-1];
		itemCount--;
		// �o��س��i�H
		/*
		itemCount--;
		items[0] = items[itemCount];
		*/
		return true;
	}
	return false;
}  // end removeFirst

template<class ItemType>
bool ArrayBag<ItemType>::deleteFirst()
{
	/*
		1.  �P�_�O�_���F��i�H����
		!isEmpty()
		2.  �p�G�i�H����
			�D�حn�D:
				�N�Ĥ@�Ӳ���
				�᭱�����e��
			return true;
		3.  else
			return false;
	*/
	if(!isEmpty()){
		// �p�ߤ��n�W�X�d��
		itemCount--;
		for (int i = 0; i < itemCount; i++){
			items[i] = items[i+1];
		}

		// �o��س��i�H
		/*
		itemCount--;

		for (int locatedIndex = 1; locatedIndex <= itemCount; locatedIndex++)
			items[locatedIndex - 1] = items[locatedIndex];
		*/
		return true;
	}
	return false;
}  // end deleteFirst

//#endif