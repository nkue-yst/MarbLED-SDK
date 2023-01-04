/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#include "VoiceRecognition.gen.hpp"
#include "TLL.h"

#include <iostream>

VoiceRecognition::VoiceRecognition()
{
    std::cout << "Create VoiceRecognition instance." << std::endl;
}

VoiceRecognition::~VoiceRecognition()
{
    std::cout << "Delete VoiceRecognition instance." << std::endl;
}

void VoiceRecognition::init()
{
    tll::OscHandler::sendMessage("/tll/app/VoiceRecognition/init", "192.168.0.100", 3333);
}

void VoiceRecognition::run()
{

}

void VoiceRecognition::terminate()
{
    tll::OscHandler::sendMessage("/tll/app/VoiceRecognition/terminate", "192.168.0.100", 3333);
}

void VoiceRecognition::onTouched(tll::TouchInfo ti)
{

}

void VoiceRecognition::onMoved(tll::TouchInfo ti)
{

}

void VoiceRecognition::onReleased(tll::TouchInfo ti)
{

}

void VoiceRecognition::procOscMessage(const osc::ReceivedMessage& msg)
{
    if (strcmp(msg.AddressPattern(), "/tll/app/VoiceRecognition/bomb_notify") == 0)
    {
        tll::Video video = tll::loadVideo("bomb.mp4");
        video.play(0, 0, 22);
    }
}
