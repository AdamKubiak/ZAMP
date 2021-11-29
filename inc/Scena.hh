#pragma once


#include "MobileObj.hh"
#include <string>
#include <map>
#include <vector>
#include "AccessControl.hh"
/*!
 * \file
 * \brief Definicja klasy Scene.
 *
 * Plik zawiera definicję klasy Scene, przechowującej listę obiektów mobilnych w postaci struktury map.
 */

class Scena:public AccessControl
{
private:
    /*!
     * \brief Mapa wskaźników na obiekty klasy MobileObj
     */
    std::map<std::string, MobileObj*> _Object_List;
public:
    /*!
     * \brief Konstruktor klasy 
     */
    Scena();
    /*!
     * \brief Konstruktor klasy 
     */
    Scena(std::map<std::string, MobileObj*> &List);
    /*!
     * \brief Destruktor klasy
     */
    ~Scena(){_Object_List.clear();};
    /*!
     * \brief Wyszukuje i zwraca wskaźnik na obiekt o nazwie podanej w parametrze
     * 
     * \param[in] sName - nazwa obiektu mobilnego do wyszukania na scenie
     * \return Zwraca wskaźnik na znaleziony obiekt lub nullptr, gdy obiekt nie zostanie znaleziony
     */
    MobileObj* FindMobileObj(std::string sName);

    /*!
     * \brief Dodaje obiekt o padanej nazwie do listy obiektów
     * 
     * \param[in] sName - nazwa obiektu mobilnego do dodania do sceny
     */
    void AddMobileObj(std::string sName);
    /*!
     * \brief zwraca  na liste obiektów
     * 
     * 
     * \return Pole _Object_List klasy Scena
     */
    std::map<std::string, MobileObj*> getObjList(){return this->_Object_List;}
    std::vector<MobileObj*> getObjects();
   
    
};



