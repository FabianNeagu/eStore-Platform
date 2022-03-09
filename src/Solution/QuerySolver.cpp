#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a()
{
	list<Product*>::iterator it;
	list<Product*> lista;
	for(it=server->getProductsList().begin();it!=server->getProductsList().end();++it)
	{
		if((*it)->getProductType()=="REDUS"&&(((*it)->getId()/10)%10==9||((*it)->getId()/100)%10==9))
			lista.push_back((*it));
	}
	return lista;
}

list<User*> QuerySolver::Query_3b()
{
	list<User*> lista;
	list<User*>::iterator it;
	for(it=server->getUsersList().begin();it!=server->getUsersList().end();++it)
	{
		if((*it)->getUserType()=="NONPREMIUM"&&(*it)->getTransportCost()<11.5)
			lista.push_back((*it));
	}
	return lista;
}

list<Product*> QuerySolver::Query_3c()
{
	list<Product*>::iterator it;
	list<Product*> lista;
	for(it=server->getProductsList().begin();it!=server->getProductsList().end();++it)
	{
		if((*it)->getProductType()=="RESIGILAT")
		{
			ReturnedProduct *it2 = dynamic_cast<ReturnedProduct *>(*it);
			if(it2!=NULL)
				if(it2->getReason()=="lipsa_accesorii")
					{
						lista.push_back(*it);
					}
		}
	}
	lista.sort(Utility::compareProductPrice);
	return lista;
}

list<Product*> QuerySolver::Query_3d()
{
	list<Product*>::iterator it;
	list<Product*> lista;
	for(it=server->getProductsList().begin();it!=server->getProductsList().end();++it)
	{
			if((*it)->getProductType()=="ALIMENTAR")
				lista.push_back(*it);
	}
	lista.sort(Utility::compareFoodProduct);
	return lista;
}

list<User*> QuerySolver::Query_3e()
{
	list<User*>::iterator it;
	list<User*>::iterator it1;
	list<User*>::iterator it2;
	list<User*> lista;
	int max=0;
	int nr;
	string aux;
	for(it=server->getUsersList().begin();it!=server->getUsersList().end();it++)
	{
		nr=0;
		for(it1=server->getUsersList().begin();it1!=server->getUsersList().end();it1++)
		if((*it1)->getDeliveryData().getCounty()==(*it)->getDeliveryData().getCounty())
			nr++;
		if(nr>max)
		{
			max=nr;
			aux=(*it)->getDeliveryData().getCounty();
		}
	}
	for(it=server->getUsersList().begin();it!=server->getUsersList().end();++it)
	if((*it)->getDeliveryData().getCounty()==aux&&(*it)->getDeliveryData().getBlock()=="-"&&(*it)->getDeliveryData().getApartment()==0&&(*it)->getBillingData().getBlock()=="-"&&(*it)->getBillingData().getApartment()==0)
			lista.push_back(*it);

	lista.sort(Utility::compareUserId);
	return lista;
}

list<User*> QuerySolver::Query_3f()
{
	list<User*>::iterator it;
	list<User*> lista;
	for(it=server->getUsersList().begin();it!=server->getUsersList().end();it++)
	{
		if((*it)->getUserType()=="PREMIUM")
		{
			int ok=0;
			PremiumUser *it1 = dynamic_cast<PremiumUser *>(*it);
			map<int,int>::iterator it2;
			for(it2=(it1)->getDiscounts().begin();it2!=(it1)->getDiscounts().end();it2++)
			{
				list<Product*>::iterator it3;
				for(it3=server->getProductsList().begin();it3!=server->getProductsList().end();it3++)
				{
					if(it2->first==(*it3)->getId())
					{
						if(((*it3)->getCategory()=="imprimanta"||(*it3)->getCategory()=="telefon")&&ok==0)
						{
							lista.push_back((*it));
							ok=1;
						}
					}
				}
			}
		}
	}
	return lista;
}
