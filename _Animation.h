#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <fstream>
#include <string>

#include "KeyFrame.h"


class Animation
{
    public:
		Animation();
        ~Animation();
        bool loadAnimation(std::string data,std::string polygon,int polycount,int vertcount);
        KeyFrame* getFrame(int frame);
        KeyFrame* getFirst(float &progress);
        KeyFrame* getLast(float &progress);

    private:
        std::string m_Name;
        float m_Duration;
        KeyFrame* m_KeyFrame;
		int m_KeyCount;
		
		int m_VerticesCount;
		
        bool m_Loop;
};

#endif
