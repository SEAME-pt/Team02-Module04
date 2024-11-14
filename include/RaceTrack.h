
#pragma once


class RaceTrack
{ 
    private:
        int _size;
        int _finishLine;

    public:
        RaceTrack();
        ~RaceTrack();

        void setSize(int size);
        void setFinishLine(int finishLine);
        int getSize();
        int getFinishLine();
};