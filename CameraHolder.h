/* 
 * File:   CameraHolder.h
 * Author: ANTOINE
 *
 * Created on 3 juillet 2016, 09:48
 */

#ifndef CAMERAHOLDER_H
#define	CAMERAHOLDER_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef CAMERA_H
#include "Camera.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif


class CameraHolder : public GameObject {
    public:
        CameraHolder();
        ~CameraHolder();
        
        void setCamera();
};

#endif	/* CAMERAHOLDER_H */

