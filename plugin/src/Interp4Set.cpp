#include <iostream>
#include "Interp4Set.hh"
#include "unistd.h"
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
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  Vector3D new_position = pMobObj->GetPositoin_m();
  new_position[0] = this->_Cord_X;
  new_position[1] = this->_Cord_Y;
  pMobObj->SetPosition_m(new_position);

  pMobObj->SetAng_Roll_deg(this->_Angle_OX);
  pMobObj->SetAng_Pitch_deg(this->_Angle_OY);
  pMobObj->SetAng_Yaw_deg(this->_Angle_OZ);
  usleep(300000);
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