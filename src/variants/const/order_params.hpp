#ifndef ORDER_PARAMS_H
#define ORDER_PARAMS_H

#include <godot_cpp/variant/string.hpp>

namespace godot{

class OrderParams{

public:

    static String name(){
        return "OrderName";
    }

    static String descr(){
        return "OrderDescr";
    }

    static String fact_rank(){
        return "OrderFactRank";
    }

    static String placed_rank(){
        return "OrderPlacedRank";
    }

    static String img(){
        return "OrderImg";
    }
    
};

}

#endif // ORDER_PARAMS_H