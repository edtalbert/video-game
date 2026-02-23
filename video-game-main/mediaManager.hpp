#include <map>
#include <string>
using namespace std;

class MediaManager{
    map<string,SDL_Texture *> images;
    public:
    SDL_Texture* read(SDL_Renderer *renderer,string fname,int &w,int &h){
        if (images.find(fname)==images.end()){
          SDL_Surface* character=SDL_LoadBMP(fname.c_str());
          if (character==NULL) throw "Could not read image.bmp file";

        // Make black (0,0,0) transparent
    SDL_SetColorKey(
        character,
        SDL_TRUE,
        SDL_MapRGB(character->format, 0, 0, 0)
    );

          SDL_Texture* charText=SDL_CreateTextureFromSurface(renderer,character);
          SDL_FreeSurface(character);
          if(charText==NULL) throw "Failed to create texture";
          images[fname]=charText;
        }
        SDL_Texture *result=images[fname];
        SDL_QueryTexture(result,NULL,NULL,&w,&h);
        return result;
    }
    ~MediaManager() {
        for (auto entry:images) SDL_DestroyTexture(entry.second);
    }
};