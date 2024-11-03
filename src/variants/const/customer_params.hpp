#ifndef CUSTOMER_PARAMS_H
#define CUSTOMER_PARAMS_H

#include <godot_cpp/variant/string.hpp>

namespace godot{

class CustomerParams{

public:

    static String name(){
        return "CustomerName";
    }

    static String display_lvl(){
        return "CustomerDisplayLevel";
    }

    static String fact_lvl(){
        return "CustomerFactLevel";
    }

    static String min_req_lvl(){
        return "CustomerMinReqLevel";
    }

    static String dialogue_id(){
        return "CustomerDialogueId";
    }
    
};

}

#endif // CUSTOMER_PARAMS_H