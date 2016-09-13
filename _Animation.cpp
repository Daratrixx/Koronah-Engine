#include "Animation.h"


//
// Class Animation
//
Animation::Animation()
{
	m_Loop=false;
	m_KeyCount=0;
	m_KeyFrame=NULL;
}

Animation::~Animation()
{
	for(KeyFrame* i=m_KeyFrame;i<(m_KeyFrame+m_KeyCount);i++)
		delete i; // Delete all KeyFrame pointers

    std::ofstream FILE2;
    FILE2.open("log.txt",std::ofstream::out | std::ofstream::app);
    FILE2 << "Animation deleted;" << std::endl;
    FILE2.close();
}
bool Animation::loadAnimation(std::string data,std::string polygon,int polycount,int vertcount)
{
    m_VerticesCount=vertcount;
    
    std::ofstream FILE2;
    FILE2.open("log.txt",std::ofstream::out | std::ofstream::app);
    FILE2 << "Loading Animation with data:" << data << std::endl;
    
    std::string property=getData(data,"PROPERTY(",")PROPERTY"); // Load properties
    m_Name=getData(property,"name(",")name"); // Load name
    FILE2 << "Name:" << m_Name << std::endl;
    m_KeyCount=toInt2(getData(property,"keyframe(",")keyframe")); // Load keyframe count
    FILE2 << "KeyCount:" << m_KeyCount << std::endl;
    m_Duration=toFloat2(getData(property,"duration(",")duration")); // Load total animation duration
    FILE2 << "Duration:" << m_Duration << std::endl;
    if(getData(property,"loop(",")loop")=="true") // Decide if the animation is looped
		m_Loop=true;
	else
		m_Loop=false;
    FILE2 << "Loop:" << m_Loop << std::endl;
    
    float polyref[polycount*3];
    for(int i=0;i<polycount*3;i++)
    {
	    polyref[i]=toInt2(getUntil(polygon,";"));
        FILE2 << polyref[i] << "_";
    }
    FILE2 << std::endl;
	
	m_KeyFrame=new KeyFrame[m_KeyCount]; // init all keyframe for current animation
	for(int i=0;i<m_KeyCount;i++)
	{
	    float progression=toFloat2(getData(data,"progression(",")progression")); // progression in the current animation
	    std::string keycord=getData(data,"KEYFRAME(",")KEYFRAME"); // all keyframe cord in a string
		KeyFrame* temp=m_KeyFrame+i;
		//temp->loadKeyFrame(keycord,m_VerticesCount,progression); // create current keyframe
	}
	FILE2.close();
}
KeyFrame* Animation::getFirst(float &progress)
{
    std::ofstream FILE2;
    FILE2.open("log.txt",std::ofstream::out | std::ofstream::app);
    FILE2 << "Current anim:" << m_Name << std::endl;
    FILE2.close();
    return m_KeyFrame;
    if(progress>m_Duration) // check if requested time is out of animation duration
	{
		if(m_Loop) // try to loop
			progress-=m_Duration;
		else
			return NULL; // return NULL
	}
	for(KeyFrame* i=m_KeyFrame;i<(m_KeyFrame+m_KeyCount-1);i++)
	{
		if(progress<(i->getProgression())) // search corresponding keyframe
			return i-1; // return keyframe
	}
}
KeyFrame* Animation::getLast(float &progress)
{
	for(KeyFrame* i=m_KeyFrame;i<(m_KeyFrame+m_KeyCount-1);i++)
	{
		if(progress<(i->getProgression())) // search corresponding keyframe
			return i; // return keyframe
	}
}
