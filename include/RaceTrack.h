#pragma once

class RaceTrack
{ 
    private:
        int _width;
        int _height;
        int _finishLineX;
        int _finishLineY;

    public:
        RaceTrack();
        ~RaceTrack();

        void setWidth(int width);
        void setHeight(int height);
        void setFinishLineX(int finishLineX);
        void setFinishLineY(int finishLineY);

        int getWidth() const;
        int getHeight() const;
        int getFinishLineX();
        int getFinishLineY();
};