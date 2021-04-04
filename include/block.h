#include <iostream>

class Block{
    private:
        //color
        int r,g,b;
        //ubicacion
        int x,y;
        bool state; //false when grounded
                    //true when moving
    public:
        Block();
        Block(int,int,int,int,int);
        ~Block();
        void setColor(int,int,int);
        void setPosition(int,int);
        void setState(bool);

        int* getColor();
        int getX();
        int getY();

        void rotate();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
};