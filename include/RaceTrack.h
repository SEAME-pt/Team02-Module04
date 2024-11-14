
#pragma once


class RaceTrack
{ 
    private:
        int _size = 0;
        int _finishLine = 0;

    public:
        RaceTrack();
        ~RaceTrack();

        void setSize(int size);
        void setFinishLine(int finishLine);
        int getSize();
        int getFinishLine();
};