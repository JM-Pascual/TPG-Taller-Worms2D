#ifndef WORMS2D_QUERY_CALLBACK_H
#define WORMS2D_QUERY_CALLBACK_H

#include <vector>

#include <box2d/box2d.h>

class Query_callback: public b2QueryCallback {
private:
    std::vector<b2Body*> foundBodies;

public:
    bool ReportFixture(b2Fixture* fixture) override;
    int found_bodies_size();
    b2Body* found_bodie_at(const int& i);
};


#endif  // WORMS2D_QUERY_CALLBACK_H
