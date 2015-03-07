#ifndef CONNECTOR_H
#define CONNECTOR_H

enum Snakes
{
    ESnakeRight,
    ESnakeLeft
};

class MConnector
    {
public:
    virtual void Snaked(Snakes aSnake) = 0;
    };

#endif // CONNECTOR_H
