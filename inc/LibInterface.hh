#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <map>
#include <dlfcn.h>
#include <iostream>

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Klasa ma na celu obsługę interfejsu bibliotek
 */
class LibInterface
{
private:
    void *handler;//!<uchwyt do biblioteki

public:

    std::string _Lib_Name;//!<pole przechowuje nazwę polecenia
    /*!
    * \brief Kontruktor
    *
    * param[in] path - Ścieżka do pliku biblioteki dynamicznej
    */
    LibInterface(std::string path);
    /*!
    * \brief Destruktor
    *
    * Zamyka biblioteke przed usunięcięm obiektu
    */
    ~LibInterface();
    /*!
    * \brief Metoda tworzy obiekt klasy Interp4Command, który służy do modelowanai polecenia
    */
    Interp4Command *(*pCreateCmd)(void);
};
#endif