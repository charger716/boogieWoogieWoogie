#include <iostream>
#include "SDL_Plotter.h"
#include "BplusTree.h"

using namespace std;

int main(int argc, char ** argv)
{
    BPlusTree test;

    SDL_Plotter g(1000,1000);
    bool stopped = false;
    bool colored = false;
    int x,y, xd, yd;
    int R,G,B;

    while (!g.getQuit())
    {
        if(!stopped){
            x = rand()%g.getCol();
            y = rand()%g.getRow();
            R = rand()%256;
            G = rand()%256;
            B = rand()%256;
            for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel( x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel( x + xd, y + yd, 0, G, 0);
                    }

                }
            }
        }

        if(g.kbhit()){
            if (g.getKey() == 'I'){
                test.insert(12);
            }
            if (g.getKey() == 'O'){
                test.insert(43);
            }
            if(g.getKey() == 'P'){
                test.insert(55);
            }
            if(g.getKey() == 'U'){
                test.insert(2);
            }
            if(g.getKey() == 'Y'){
                test.insert(24);
            }
        }

        if(g.getMouseClick(x,y)){
            stopped = !stopped;
        }

        g.update();
    }

    return 0;
}