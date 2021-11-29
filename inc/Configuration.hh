#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH
#include "MobileObj.hh"
#include <map>
#include <string>
#include <vector>
#include <memory>

/*!
 * \file
 * \brief Definicja klasy Configuration.
 *
 * Plik zawiera definicję klasy Configuration, 
 * która przechowuje konfigurację sceny i listę bibliotek, 
 * odczytywana z pliku XML.
 */

class Configuration {

  /*!
   * \brief Lista obiektów mobilnych w postaci struktury mapy
   */
  std::map<std::string, MobileObj*> ObjectsList;
  /*!
   * \brief Lista nazw bibliotek
   */
  std::vector<std::string> LibraryList;

  public:
  ~Configuration(){ObjectsList.clear();}
  /*!
   * \brief Metoda dodaje obiekt mobilny odczytany z pliku konfiguracyjnego XML 
   *\param[in] LibraryName - nazwa biblioteki, która zostaje dodana do listy
   */
  void AddLibraryName(const std::string &LibraryName);
  /*!
   * \brief Metoda dodaje nazwę biblioteki odczytaną z pliku konfiguracyjnego XML
   *\param[in] ObjectName - nazwa obiektu, który zastaje dodany do listy
   * \param[in] Scale - wektor z wartościami skali obiektu
   * \param[in] RGB - napis z wartościami Red Green Blue obiektu
   */
 
  //void AddMobileObj(const std::string &ObjectName,const Vector3D &Scale, const std::string &RGB);
  void AddMobileObj(const std::string &ObjectName,const Vector3D &Scale,const std::string &RGB,const Vector3D &Shift,const Vector3D &RotXYZ,const Vector3D &Trans);

  /*!
  * \brief Metoda zwraca listę nazw bibliotek
  */
  std::vector<std::string> &getLibraryList() {return this->LibraryList;}
  /*!
   * \brief Metoda zwraca listę obiektów mobilnych
   */
  std::map<std::string, MobileObj*> &getObjectList(){return this->ObjectsList;}
  
};


#endif
