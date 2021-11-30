#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <string>
#include "Vector3D.hh"
#include <sstream>

/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */

/*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    */
class MobileObj
{
        /*!
        * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OZ.
	*
	* Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
        */
        double _Ang_Yaw_deg = 0;

        /*!
        * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OY.
	*
	* Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
        */
        double _Ang_Pitch_deg = 0;

        /*!
        * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OX.
	*
	* Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
        */
        double _Ang_Roll_deg = 0;

        /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
        Vector3D _Position_m;

        /*!
        * \brief Nazwa obiektu, która go indentyfikuje.
        *
        * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
        * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
        */
        std::string _Name;

        Vector3D _Scale;

        Vector3D _Shift;

        int color[3];



public:
        /*!
         * \brief Zwraca informację o stanie obiektu
         * 
         * \return ciag znaków zawierający informacje o obiekcie.
         */
        std::string ActualPosition()
        {
                char buffer[100];
                int len = sprintf(buffer, " Name=%s RotXYZ_deg=(%f,%f,%f)\n", this->_Name.c_str(), this->_Ang_Yaw_deg, this->_Ang_Pitch_deg, this->_Ang_Roll_deg);
                std::string result(buffer, len);

                return result;
        }
        
        /*!
         * \brief Zwraca informację o stanie obiektu
         * 
         * \return ciag znaków zawierający informacje o obiekcie.
         */
        std::string returnParameters()
        {
                char buffer[200];
                int length = sprintf(buffer, "Name=%s RGB=(%d,%d,%d) Scale=(%f,%f,%f) Shift=(%f,%f,%f) RotXYZ_deg=(%f,%f,%f) Trans_m=(%f,%f,%f)\n",
                this->_Name.c_str(), this->color[0], this->color[1], this->color[2],this->_Scale[0],this->_Scale[1],this->_Scale[2],
                this->_Shift[0],this->_Shift[1],this->_Shift[2],this->_Ang_Roll_deg,this->_Ang_Pitch_deg,this->_Ang_Yaw_deg,this->_Position_m[0], this->_Position_m[1],this->_Position_m[2]);
                std::string result(buffer, length);
                std::string message = result;
                // Ta instrukcja to tylko uproszczony przykład
                // cout << objectPointer->movingState;
                return message; // Tu musi zostać wywołanie odpowiedniej                  // metody/funkcji gerującej polecenia dla serwera
        }
        /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
        double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
        /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
        double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
        /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
        double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }

        /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
        void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
        /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
        void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
        /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
        void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }

        /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
        const Vector3D &GetPositoin_m() const { return _Position_m; }
        /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
        Vector3D &UsePosition_m() { return _Position_m; }
        /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
        void SetPosition_m(const Vector3D &rPos_m) { _Position_m = rPos_m; }

        /*!
       * \brief Zmienia nazwę obiektu.
       *
       *  Zmienia nazwę obiektu.
       *  \param[in] sName - nowa nazwa obiektu.
       */
        void SetName(const char *sName) { _Name = sName; }
        /*!
        * \brief Udostępnia nazwę obiektu.
	*
	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
        */
        const std::string &GetName() const { return _Name; }

        /*!
         * \brief Zmienia wielkość obiektu
         * 
         * \param[in] Scale - wektor3D z wartościami skali XYZ
         */
        void SetScale(const Vector3D &Scale) { _Scale = Scale; }

        /*!
         * \brief Zmienia kolor obiektu.
         * 
         * \param[in] RGB - kolor w postaci RGB
         */
        void setColor(const std::string RGB)
        {
                std::istringstream IStrm;
                IStrm.str(RGB);
                IStrm >> this->color[0] >> this->color[1] >> this->color[2];
        }

        void setShift(const Vector3D &Shift) { _Shift = Shift;}
};

#endif
