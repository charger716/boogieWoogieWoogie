#include "SDL_Plotter.h"
#include "Bplustree.h"

using namespace std;

SDL_Plotter *g;

void drawRect(int, int);
void drawLine(int, int, int, int);
void drawNums(int, int, int);
void drawTree(Node*);
void drawNode(Node*, int, int, int);
void draw0(int, int);
void draw1(int, int);
void draw2(int, int);
void draw3(int, int);
void draw4(int, int);
void draw5(int, int);
void draw6(int, int);
void draw7(int, int);
void draw8(int, int);
void draw9(int, int);

//BPLUS VISUALS
int main(int argc, char **argv) {
    BPlusTree b;
    int x;
    char key;
    Node *root = b.getRoot();
    bool quit = false;
    g = new SDL_Plotter( 500, 1000);

    //DRAW LOOP
        while (!g->getQuit()) {

            g->update();
            if (g->kbhit()) {
                switch (g->getKey()) {
                    case 'I' :
                        cout << "Value to be inputted: ";
                        cin >> x;
                        cout << endl;
                        b.insert(x);
                        g->clear();
                        drawTree(b.getRoot());
                        break;
                    case 'R' :
                        cout << "Value to be deleted: ";
                        cin >> x;
                        cout << endl;
                        b.remove(x);
                        g->clear();
                        drawTree(b.getRoot());
                        break;
                    case 'Q' :
                        g->setQuit(true);
                        quit = true;
                        break;
                }
            }
        }

        delete g;
    return 0;
}

//draws rectangle using r's x and y values
void drawRect(int x, int y){

    if( x + 48 <= 999 && y + 16 <= 999 ) {
        for (int i = 0; i < 48; i++) {
            g->plotPixel(x + i, y, 0, 0, 0);
            g->plotPixel(x + i, y + 16, 0, 0, 0);
        }

        for (int i = 0; i < 16; i++) {
            g->plotPixel(x, y + i, 0, 0, 0);
            g->plotPixel(x + 48, y + i, 0, 0, 0);
        }
    }
}

void drawLine(int a1, int b1, int a2, int b2){
    double x1 = (double)a1;
    double y1 = (double)b1;
    double x2 = (double)a2;
    double y2 = (double)b2;

    double m = (y2 - y1) / (x2 - x1);

    if( m != 0.0 ) {
        while ((int) x1 != a2 || (int) y1 != b2) {

            if ((int) x1 != a2) {
                if( m < 0.0 )
                    x1--;
                else
                    x1++;
            }
            if ((int) y1 != b2) {
                y1 = (double) b1 + abs((x1 - (double) a1) * m);
            }

            g->plotPixel((int)x1, (int)y1, 0, 0, 0);
        }
    }

    else{
        while( (int)x1 != a2 ){
            x1 += 1.0;
            g->plotPixel((int)x1, (int)y1, 0, 0, 0);
        }
    }
}

void drawNums(int n, int x, int y ){
    int h, t, o;
    h = n / 100;
    t = ( n - h * 100 ) / 10;
    o = n % 10;

    switch( h ){
        case 1 : draw1(x, y);
            break;
        case 2 : draw2(x, y);
            break;
        case 3 : draw3(x, y);
            break;
        case 4 : draw4(x, y);
            break;
        case 5 : draw5(x, y);
            break;
        case 6 : draw6(x, y);
            break;
        case 7 : draw7(x, y);
            break;
        case 8 : draw8(x, y);
            break;
        case 9 : draw9(x, y);
            break;
        default: draw0(x, y);
            break;
    }

    switch( t ){
        case 1 : draw1(x+16, y);
            break;
        case 2 : draw2(x+16, y);
            break;
        case 3 : draw3(x+16, y);
            break;
        case 4 : draw4(x+16, y);
            break;
        case 5 : draw5(x+16, y);
            break;
        case 6 : draw6(x+16, y);
            break;
        case 7 : draw7(x+16, y);
            break;
        case 8 : draw8(x+16, y);
            break;
        case 9 : draw9(x+16, y);
            break;
        default: draw0(x+16, y);
            break;
    }

    switch( o ){
        case 1 : draw1(x+32, y);
            break;
        case 2 : draw2(x+32, y);
            break;
        case 3 : draw3(x+32, y);
            break;
        case 4 : draw4(x+32, y);
            break;
        case 5 : draw5(x+32, y);
            break;
        case 6 : draw6(x+32, y);
            break;
        case 7 : draw7(x+32, y);
            break;
        case 8 : draw8(x+32, y);
            break;
        case 9 : draw9(x+32, y);
            break;
        default: draw0(x+32, y);
            break;
    }

}

void drawTree(Node* n){
    Node* b = n;
    int x = 500 - (n->size * 24);
    int tempX;
    int amt = 0;
    int alpha;
    while( b->children[amt] != nullptr )
        amt++;

    for( int i = 0; i < b->size; i++ ){
        drawRect(x+i*48, 1);
        drawNums(b->data[i], x+i*48, 1);
    }

    alpha = 1 + amt;
    tempX = 1000 / alpha;

    for( int i = 0; b->children[i] != nullptr; i++ ) {
        drawLine( x+(24*n->size), 16, tempX * (i+1), 100);
        drawNode(b->children[i], 1, i + 1, amt);
    }
}

void drawNode(Node* n, int level, int childNum, int chAmt){
    int alpha = (level + chAmt);
    int x = 1000 / alpha;
    x = x * childNum * level - n->size * 24;
    int cx, ca;

    int amt = 0;
    while( n->children[amt] != nullptr )
        amt++;

    for( int j = 0; j < n->size; j++ ){
        drawRect(x+48*j, 100*level);
        drawNums(n->data[j], x+48*j, 100*level);
    }

    ca = (level + 1) + ((amt+1) *3);
    for( int i = 0; n->children[i] != nullptr; i++ ) {
        cx = (1000 / ca) * (childNum + childNum + i - 1) * (level + 1) -
                n->children[i]->size * 24;
        drawLine( x+(24*n->size), (100 * level) + 16,  cx, 100 * (level + 1));
        drawNode(n->children[i], level + 1, childNum + childNum + i - 1, (amt + 1) * 3);
    }
}

//number draw functions
void draw0(int a, int b){
    int x = a;
    int y = b;
    for(int i = 0; i < 8; i++){
        g->plotPixel(x+4+i, y+1, 0, 0, 0);
    }

    for(int i = 0; i < 10; i++ ){
        g->plotPixel(x+3,y+2, 0, 0, 0);
    }

    for(int i = 0; i < 11; i++){
        for( int j = 0; j < 2; j++){
            g->plotPixel(x+3+j, y+3+i, 0, 0, 0);
        }
    }

    for(int i = 0; i < 11; i++){
        for( int j = 0; j < 2; j++){
            g->plotPixel(x+11+j, y+3+i, 0, 0, 0);
        }
    }

    for(int i = 0; i < 10; i++ ){
        g->plotPixel(x+3,y+14, 0, 0, 0);
    }

    for(int i = 0; i < 8; i++){
        g->plotPixel(x+4+i, y+15, 0, 0, 0);
    }

    y = y + 11;
    for(int i = 0; i < 6; i++ ){
        for( int j = 0; j < 3; j++ ){
            g->plotPixel(x+5+i, y-j, 0, 0, 0);
        }
        y--;
    }
}

void draw1(int a, int b){
    int x = a;
    int y = b;

    for(int i = 0; i < 11; i++ ){
        for( int j = 0; j < 2; j++ ){
            g->plotPixel(x+3+i, y+14+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 14; j++){
            g->plotPixel(x+8+i, y+j, 0, 0, 0);
        }
    }

    g->plotPixel(x+4, y+4, 0, 0, 0);
    g->plotPixel(x+4, y+5, 0, 0, 0);

    y += 3;

    for( int i = 0; i < 3; i++ ){
        for( int j = 0; j < 3; j++ ){
            g->plotPixel(x+5+i, y+j, 0, 0, 0);
        }
        y--;
    }
}

void draw2(int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 11; j++){
            g->plotPixel(x+2+j, y+14+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 8; i++ ){
        for( int j = 0; j < 2; j++ ){
            g->plotPixel(x+3+i+j, y+13-i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 6; i++ )
        g->plotPixel(x+5+i, y, 0, 0, 0);

    for( int i = 0; i < 8; i++ )
        g->plotPixel(x+4+i, y+1, 0, 0, 0);

    for( int i = 0; i < 3; i++ ){
        for( int j = 0; j < 2; j++ ){
            g->plotPixel(x+11+j, y+3+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 3; j++ ){
            g->plotPixel(x+2+j, y+3-i, 0, 0, 0);
        }
    }

    g->plotPixel(x+2, y+4, 0, 0, 0);
    g->plotPixel(x+3, y+4, 0, 0, 0);
    g->plotPixel(x+10, y+2, 0, 0, 0);
    g->plotPixel(x+11, y+2, 0, 0, 0);
    g->plotPixel(x+12, y+2, 0, 0, 0);
}

void draw3(int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+3+j, y+i, 0, 0, 0);
        }
    }

    g->plotPixel(x+11, y+1, 0, 0, 0);
    g->plotPixel(x+10, y+2, 0, 0, 0);

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+11+i, y+2+j, 0, 0, 0);
        }
    }

    g->plotPixel(x+10, y+6, 0, 0, 0);

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 9; j++ ){
            g->plotPixel(x+3+j, y+7+i, 0, 0, 0);
        }
    }

    g->plotPixel(x+10, y+9, 0, 0, 0);

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+11+i, y+9+j, 0, 0, 0);
        }
    }

    g->plotPixel(x+10, y+13, 0, 0, 0);
    g->plotPixel(x+11, y+14, 0, 0, 0);

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+3+j, y+14+i, 0, 0, 0);
        }
    }
}

void draw4(int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 16; j++ ){
            g->plotPixel(x+11+i, y+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 12; j++ ){
            g->plotPixel(x+2+j, y+8+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 5; i++ ){
        for( int j = 0; j < 3; j++ ){
            g->plotPixel(x+3+i+j, y+7-i, 0, 0, 0);
        }
    }

    g->plotPixel(x+10, y+1, 0, 0, 0);
    g->plotPixel(x+9, y+2, 0, 0, 0);
    g->plotPixel(x+10, y+2, 0, 0, 0);
}

void draw5(int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 10; j++ ){
            g->plotPixel(x+3+j, y+1+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 4; j++ ){
            g->plotPixel(x+3+i, y+3+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 9; j++ ){
            g->plotPixel(x+3+j, y+7+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 7; j++ ){
            g->plotPixel(x+11+i, y+8+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+14+i, 0, 0, 0);
        }
    }

    g->plotPixel(x+3, y+13, 0, 0, 0);
    g->plotPixel(x+4, y+13, 0, 0, 0);
    g->plotPixel(x+3, y+14, 0, 0, 0);
}

void draw6( int a, int b ){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 13; j++ ){
            g->plotPixel(x+3+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for ( int j = 0; j < 8; j++ ){
            g->plotPixel( x+4+j, y+1+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 4; j++ ){
            g->plotPixel(x+11+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 7; j++ ){
            g->plotPixel( x+5+j, y+8+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 6; j++ ){
            g->plotPixel( x+11+i, y+9+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel( x+4+j, y+14+i, 0, 0, 0);
        }
    }
}

void draw7( int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+7+i, y+11+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 4; i++ ){
        for( int j = 0; j < 3; j++ ){
            g->plotPixel( x+7+i+j, y+10-i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+11+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 9; j++ ){
            g->plotPixel(x+3+j, y+1+i, 0, 0, 0);
        }
    }
}

void draw8(int a, int b){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+1+i,0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+3+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 5; j++ ){
            g->plotPixel(x+11+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+7+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 6; j++ ){
            g->plotPixel(x+3+i, y+9+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 6; j++ ){
            g->plotPixel(x+11+i, y+9+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+14+i, 0, 0, 0);
        }
    }
}

void draw9( int a, int b ){
    int x = a;
    int y = b;

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+1+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 6; j++ ){
            g->plotPixel(x+3+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 7; j++ ){
            g->plotPixel(x+4+j, y+7+i, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 13; j++ ){
            g->plotPixel(x+11+i, y+2+j, 0, 0, 0);
        }
    }

    for( int i = 0; i < 2; i++ ){
        for( int j = 0; j < 8; j++ ){
            g->plotPixel(x+4+j, y+14+i, 0, 0, 0);
        }
    }

    g->plotPixel(x+3,y+14, 0, 0, 0);
    g->plotPixel(x+4, y+14, 0, 0, 0);
    g->plotPixel(x+3, y+15, 0, 0, 0);
}