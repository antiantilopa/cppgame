#pragma once

namespace CppGame {
    
class Updateable {
public:

    virtual ~Updateable() = default;

    virtual void preupdate() {};
    virtual void update() {};
    virtual void postupdate() {};
};

}
