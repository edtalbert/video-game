#include <SDL.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int error(string s){
    cerr << s << SDL_GetError()<<endl;
    return -1;
}

#include "mediaManager.hpp"
#include "character.hpp"
#include "game.hpp"
#include "myGame.hpp"

MediaManager mm;

int main(int argc, char* args[]) {
    cout <<"game starting..."<<endl;
    MyGame m;
    m.run();
    return 0;
}
