#include "ShoppingCart.h"

ShoppingCart::ShoppingCart():shoppingCart()
{
	this->payMethod = "-";
}

ShoppingCart::ShoppingCart(const string &payMethod)
{
	this->payMethod=payMethod;
}

string &ShoppingCart::getPayMethod()
{
	return payMethod;
}

void ShoppingCart::setPayMethod(const string &payMethod)
{
	this->payMethod=payMethod;
}

void ShoppingCart::addProduct(int id, int quantity)
{
	shoppingCart[id]=quantity;
}

void ShoppingCart::raiseQuantity(int id, int quantity)
{
	shoppingCart[id] =shoppingCart[id] +quantity;
}

void ShoppingCart::lowerQuantity(int id, int quantity)
{
	shoppingCart[id] =shoppingCart[id]-quantity;
}

int ShoppingCart::getQuantity(int productID)
{
	if(shoppingCart[productID]>0)
		return shoppingCart[productID];
	else 
		return -1;
}

void ShoppingCart::deleteProduct(int productID)
{
	shoppingCart.erase(productID);
}

map<int, int> &ShoppingCart::getShoppingCart()
{
	return shoppingCart;
}

void ShoppingCart::displayShoppingCart()
{
	throw("undefined");
}

json ShoppingCart::toJSON()
{
  return json(*this);
}
