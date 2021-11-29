#include "Scena.hh"
#include <vector>
Scena::Scena(){}

Scena::Scena(std::map<std::string, MobileObj*> &List): _Object_List(List)
{
    std::cout << "Stworzono scene z " <<_Object_List.size() << " obiektami"<< std::endl;
}


MobileObj* Scena::FindMobileObj(std::string sName)
{
    std::map<std::string, MobileObj *>::iterator Iter = this->_Object_List.find(sName);

    if(Iter == this->_Object_List.end()) return nullptr;

    else return Iter->second;
}

void Scena::AddMobileObj(std::string sName)
{
    MobileObj *pMobObj = new MobileObj;
    this->_Object_List.insert({sName,pMobObj});
}

std::vector<MobileObj*> Scena::getObjects()
{
    std::vector<MobileObj*> result;
    std::map<std::string, MobileObj *>::iterator Iter;

    for(Iter = _Object_List.begin(); Iter!=_Object_List.end(); Iter++)
    {
        result.push_back(Iter->second);
    }

    return result; 
}
