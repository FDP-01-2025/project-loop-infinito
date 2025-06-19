#pragma once

// estados de del jugador
enum class PlayerStatus {
    HEALTHY,
    SICK
};

class Player {
public:
    PlayerStatus status;
    int turnsRemaining;
    int tasksCompleted;

    Player(); //constructor

    void cure();
    void getInfected();
};