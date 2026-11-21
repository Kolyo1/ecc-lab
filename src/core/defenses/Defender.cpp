#include "Defender.h"

namespace ecc {
    void Defender::addDefense(std::shared_ptr<IDefense> d){
        defenses_.push_back(std::move(d));
    }

    void Defender::enable(const std::string& name){
        for(auto& n : defenses_){
            if(n->name() == name){
                n->apply();
            }
        }
    }

    void Defender::disable(const std::string& name){
        for(auto& n : defenses_){
            if(n->name() == name){
                n->remove();
            }
        }
    }
} // namespace ecc
