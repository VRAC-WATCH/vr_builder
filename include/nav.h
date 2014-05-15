/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2007 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _OSG_NAVIGATER_H
#define _OSG_NAVIGATER_H

#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>

#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>
#include <plugins/ApplicationDataManager/UserData.h>

/** Class to wrap the navigation matrix to share across cluster.
 */
class NavData : public vpr::SerializableObject
{
public:
   /**
    * De-serializes this object using the data in the given object reader.
    *
    * @param reader The object reader used for de-serializing this object.
    *
    * @throw vpr::IOException is thrown if object de-serialization fails.
    */
   virtual void readObject(vpr::ObjectReader* reader)
   {
      float pos_data[16];
      for ( unsigned n=0;n<16;n++ )
      {
         pos_data[n] = reader->readFloat();
      }
	  mCurPos.set(pos_data);
   }

   /**
    * Serializes this object into the given object writer.
    *
    * @param writer The object reader used for serializing this object.
    *
    * @throw vpr::IOException is thrown if object serialization fails.
    */
   virtual void writeObject(vpr::ObjectWriter* writer)
   {
      const float* pos_data = mCurPos.getData();
      for ( int n=0;n<16;n++ )
      {
         writer->writeFloat(pos_data[n]);
      }
   }

public:
   gmtl::Matrix44f mCurPos;      /**< Current position */
};

/**
 * Class to control all navigation. 
 */
class OsgNavigator
{
public:
	/** Navigation mode */
	enum NavMode
	{
		WALK,       /**< Constrain to x,y trans and y rotations. */
		FLY         /**< No restrictions */
	};
	
   // Constructor
   OsgNavigator() : mActive(false), mMode(WALK)
   {;}
	
	void init()
	{
		mActive = true;
		
		vpr::GUID nav_guid("CDE75A39-0D69-4BB1-AF0D-E4CB5F0BAADD");
		vpr::GUID tilt_guid("c573c2c9-a1a5-45c2-9e8f-2b009f410c5d");
		mNavData.init(nav_guid);
		mTiltData.init(tilt_guid);
	}

   void setWalkMode(bool walk_mode)
   {
      if (walk_mode)
      {
         mMode = WALK;
      }
      else
      {
         mMode = FLY;
      }
   }
   
   NavMode getWalkMode()
	{
		return mMode;
	}

   void setVelocity(const gmtl::Vec3f& vel)
   {
      mVelocity = vel;
   }
   void setRotationalVelocity(const gmtl::Matrix44f& rot_vel)
   {
      mRotVelocity = rot_vel;
   }
	void setTiltVelocity(const gmtl::Matrix44f& tilt_vel)
	{
		mTiltVelocity = tilt_vel;
	}
   void update()
   {
      // Only update if we are the master node
      if (!mNavData.isLocal())
      {
         return;
      }
	  
      // Clamp delta
	  float delta = 1.0f;

      // ---------- ROTATION ----------- //
      // Scale the rotation velocity (slerp) to get a time based change
      gmtl::Quatf qrot = gmtl::make<gmtl::Quatf>(mRotVelocity);
      gmtl::Quatf scaled_qrot, src_rot;   // scaled rotation and Identity rotation
      gmtl::Matrix44f delta_rot;          // The delta rotation to use

      // Only compute if we don't have identity rotation
      if (!gmtl::isEqual(gmtl::MAT_IDENTITY44F, mRotVelocity, 0.001f))
      {
         gmtl::slerp(scaled_qrot, delta, src_rot, qrot);
         gmtl::set(delta_rot, scaled_qrot);
      }

      if (mMode == WALK)
      {
         gmtl::EulerAngleXYZf euler( 0.0f, gmtl::makeYRot(delta_rot), 0.0f );// Only allow Yaw (rot y)
         delta_rot = gmtl::makeRot<gmtl::Matrix44f>( euler );
      }
      gmtl::postMult(mNavData->mCurPos, delta_rot);

      // ------- TRANSLATION ---- //
      gmtl::Vec3f trans_delta;
      if (mMode == WALK)
      {
         mVelocity[1] = 0.0f;
      }
      trans_delta =  mVelocity * delta;

      // Post multiply the delta translation
      gmtl::Matrix44f trans_matrix = gmtl::makeTrans<gmtl::Matrix44f>(trans_delta);
      gmtl::postMult(mNavData->mCurPos, trans_matrix);
	  
	  // ------- TILT ROTATION ---- //
	   // Scale the rotation velocity (slerp) to get a time based change
	   gmtl::Quatf qrotTilt = gmtl::make<gmtl::Quatf>(mTiltVelocity);
	   gmtl::Quatf scaled_qrotTilt, src_rotTilt;   // scaled rotation and Identity rotation
	   gmtl::Matrix44f delta_rotTilt;          // The delta rotation to use
	   
	   // Only compute if we don't have identity rotation
	   if (!gmtl::isEqual(gmtl::MAT_IDENTITY44F, mTiltVelocity, 0.001f))
	   {
		   gmtl::slerp(scaled_qrotTilt, delta, src_rotTilt, qrotTilt);
		   gmtl::set(delta_rotTilt, scaled_qrotTilt);
	   }
	   gmtl::postMult(mTiltData->mCurPos, delta_rotTilt);

      // Reset velocity vectors
      mVelocity = gmtl::Vec3f(0.0, 0.0, 0.0);
      mRotVelocity = gmtl::MAT_IDENTITY44F;
      mTiltVelocity = gmtl::MAT_IDENTITY44F;
   }

   gmtl::Matrix44f getCurPos()
   {
      if (!mActive)
      {
         return gmtl::Matrix44f();
      }
      else
      {
         return mNavData->mCurPos;
      }
   }

   void setCurPos(const gmtl::Matrix44f pos)
   {
      if (mActive)
      {
         mNavData->mCurPos = pos;
      }
   }
   
	gmtl::Matrix44f getTiltMatrix()
	{
		if (!mActive)
		{
			return gmtl::Matrix44f();
		}
		else
		{
			return mTiltData->mCurPos;
		}
	}
	
	void setTiltMatrix()
	{
		if (mActive)
		{
			mTiltData->mCurPos = gmtl::MAT_IDENTITY44F;
		}
	}

private:
   bool                   mActive;      /**< True if we have been initialized */
   NavMode                mMode;        /**< Current navigation mode */

   /** Current postion (as userdate for sharing across cluster */
   cluster::UserData< NavData >  mNavData;
   cluster::UserData< NavData >  mTiltData;

   gmtl::Vec3f             mVelocity;        /**< Current trans velocity */
   gmtl::Matrix44f         mRotVelocity;     /**< Current angular velocity */
	gmtl::Matrix44f mTiltVelocity;
};

#endif /* _OSG_NAVIGATE_H */
