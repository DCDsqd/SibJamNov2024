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

    static String sprite_id(){
        return "CustommerSpriteId";
    }

    static String request_quest(){
        return "CustomerRequestQuest";
    }

    static String state(){
        return "CustomerState";
    }

    static String tech_name(){
        return "CustomerTechName";
    }

    static String stage_var(){
        return "CustommerStageVar";
    }

    static String death_var(){
        return "CustommerDeathVar";
    }
    
};

}

#endif // CUSTOMER_PARAMS_H