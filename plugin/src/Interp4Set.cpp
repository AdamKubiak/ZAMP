#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set():_Cord_X(0), _Cord_Y(0), _Angle_OX(0),_Angle_OY(0),_Angle_OZ(0)
  
  
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName()<<" " << _Cord_X << " " << _Cord_Y << " "  << _Angle_OX << " "  << _Angle_OY << " "  << _Angle_OZ << " "  << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Cord_X >> _Cord_Y >> _Angle_OX >> _Angle_OY >> _Angle_OZ;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  wsp_x[m]  wsp_y[m]  kat_OX[deg]  kat_OY[deg]  kat_OZ[deg]" << endl;
}