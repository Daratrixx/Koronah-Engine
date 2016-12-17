/* 
 * File:   Buff.h
 * Author: ANTOINE
 *
 * Created on 22 novembre 2016, 14:49
 */

#ifndef BUFF_H
#define BUFF_H

#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef UNIT_H
#include "Unit.h"
#endif

#ifndef TRIGGERABLE_H
#include "Triggerable.h"
#endif

class Buff : public Triggerable {
    
};

class BuffInstance {
    friend class Buff;
    Buff* m_buffModel;
};

#endif /* BUFF_H */

