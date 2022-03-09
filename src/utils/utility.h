#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"
#include "../Solution/User/User.h"

class Utility{

public:
	static bool compareProductPrice(Product *, Product *);
	static bool compareFoodProduct(Product *&,Product *&);
	static bool compareUserId(User *,User *);
};
