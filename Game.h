//
// Created by joeyt on 9/25/2023.
//

#ifndef CHESS_PROJ_GAME_H
#define CHESS_PROJ_GAME_H

//Using Singleton design pattern as we only want one game running at a time (presumably)
class Game {
public:
    static Game* instance();
protected:
    Game() {};
private:
    static Game* _instance;
};


#endif //CHESS_PROJ_GAME_H
