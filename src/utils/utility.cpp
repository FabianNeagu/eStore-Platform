#include "utility.h"

bool Utility::compareProductPrice(Product *prod1,Product *prod2)
{
	NonFoodProduct *it1 = dynamic_cast<NonFoodProduct*>(prod1);
	NonFoodProduct *it2 = dynamic_cast<NonFoodProduct*>(prod2);
	if (it1->getPrice() < it2->getPrice()){return true;}
	if (it1->getPrice() > it2->getPrice()){return false;}
	return false;
}
bool Utility::compareFoodProduct(Product *&prod1,Product *&prod2)
{
	FoodProduct *it1 = dynamic_cast<FoodProduct*>(prod1);
	FoodProduct *it2 = dynamic_cast<FoodProduct*>(prod2);
	if (it1->getName() == it2->getName())
	{
		if(it1->getCountryOfOrigin()==it2->getCountryOfOrigin())
			{
				if (it1->getLeiPerKg() < it2->getLeiPerKg()){return true;}
				if (it1->getLeiPerKg() > it2->getLeiPerKg()){return false;}
			}
		else
		{
			if(it1->getCountryOfOrigin()<it2->getCountryOfOrigin()){return true;}
			if(it1->getCountryOfOrigin()>it2->getCountryOfOrigin()){return false;}
		}
	}
	else
	{
		if(it1->getName()<it2->getName()){return true;}
		if(it1->getName()>it2->getName()){return false;}
	}
	return false;
}
bool Utility::compareUserId(User *user1,User *user2)
{
	if(user1->getUserID()<user2->getUserID())
		return true;
	if(user1->getUserID()>user2->getUserID())
		return false;
	return false;
}
