#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	list<User *>::iterator it;
	for(it=usr.begin();it!=usr.end();it++)
	{
		int u;
		ShoppingCart *p=new ShoppingCart;
		u=(*it)->getUserID();
		pair<int, ShoppingCart *> aux(u,p);
		__UserID__ProductsCart__.insert(aux);
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{

	if(quantity<=0)
		return false;
	list<User*>::iterator it;
	int ok=0;
	for(it=usr.begin();it!=usr.end();it++)
		if((*it)->getUserID()==userID)
			ok=1;
	if(ok==0)
		return false;
	list<Product*>::iterator it1;
	int ok1=0;
	for(it1=prod.begin();it1!=prod.end();it1++)
		if((*it1)->getId()==productID)
			ok1=1;
	if(ok1==0)
		return false;
	int ok4=0;
	for(it1=prod.begin();it1!=prod.end();it1++)
		if((*it1)->getId()==productID)
			if((*it1)->getQuantity()>=quantity)
				ok4=1;
	if(ok4==0)
		return false;
	map<int,int> shop=__UserID__ProductsCart__[userID]->getShoppingCart();
	map<int,int>::iterator i;
	int ok3=0;
	for(i=shop.begin();i!=shop.end();i++)
		if(i->first==productID)
			ok3=1;
	if(ok3==0)
	{
		__UserID__ProductsCart__[userID]->addProduct(productID,quantity);
		for(it1=prod.begin();it1!=prod.end();it1++)
			if((*it1)->getId()==productID)
				(*it1)->decreaseQuantity(quantity);
	}
	if(ok3==1)
	{
		__UserID__ProductsCart__[userID]->raiseQuantity(productID,quantity);
		for(it1=prod.begin();it1!=prod.end();it1++)
			if((*it1)->getId()==productID)
				(*it1)->decreaseQuantity(quantity);

	}
	return true;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if(quantity<=0)
		return false;
	list<User*>::iterator it;
	int ok=0;
	for(it=usr.begin();it!=usr.end();it++)
		if((*it)->getUserID()==userID)
			ok=1;
	if(ok==0)
		return false;
	list<Product*>::iterator it1;
	int ok1=0;
	for(it1=prod.begin();it1!=prod.end();it1++)
		if((*it1)->getId()==productID)
			ok1=1;
	if(ok1==0)
		return false;
	map<int,int> shop=__UserID__ProductsCart__[userID]->getShoppingCart();
	map<int,int>::iterator i;
	int ok3=0;
	for(i=shop.begin();i!=shop.end();i++)
		if(i->first==productID)
			ok3=1;
	if(ok3==0)
		return false;
	if(ok3==1)
	{
		if(__UserID__ProductsCart__[userID]->getQuantity(productID)<quantity)
		{
			for(it1=prod.begin();it1!=prod.end();it1++)
				if((*it1)->getId()==productID)
					(*it1)->increaseQuantity(__UserID__ProductsCart__[userID]->getQuantity(productID));
			__UserID__ProductsCart__[userID]->lowerQuantity(productID,__UserID__ProductsCart__[userID]->getQuantity(productID));
		}
		else
		{
			__UserID__ProductsCart__[userID]->lowerQuantity(productID,quantity);
			for(it1=prod.begin();it1!=prod.end();it1++)
				if((*it1)->getId()==productID)
					(*it1)->increaseQuantity(quantity);
		}
	}
	return true;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}
