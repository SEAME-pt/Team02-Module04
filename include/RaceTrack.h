
#pragma once


class RaceTrack
{ 
    private:
        int _width;
        int _height;
        int _finishLine;

    public:
        RaceTrack();
        ~RaceTrack();

        void setWidth(int width);
        void setHeight(int height);
        void setFinishLine(int finishLine);

        int getWidth() const;
        int getHeight() const;
        int getFinishLine();
};