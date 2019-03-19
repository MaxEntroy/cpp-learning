#include <iostream>
#include "luacall.pb.h"
#include "profile.pb.h"

void Client(std::string* output) {
    std::cout << "Client called." << std::endl;
    
    qqnews::LuaNewsInfo luanewsinfo;

    int lua_id = 1;
    std::cout << "lua_id: " << lua_id << std::endl;
    luanewsinfo.set_lua_id(lua_id);

    qqnews::KBUserInfo* user_info = luanewsinfo.mutable_user_info();
    
    qqnews::CatProfile* cat_profile1 = user_info->add_cat_profile();

    std::string type("");
    std::cout << "type: " << type << std::endl;
    cat_profile1->set_type(type);

    std::string weight("0.3");
    std::cout << "weight: " << weight << std::endl;
    cat_profile1->set_weight(weight);

    std::string lv1("sports");
    std::cout << "lv1: " << lv1 << std::endl;
    cat_profile1->set_lv1(lv1);

    std::string lv2("nba");
    std::cout << "lv2: " << lv2 << std::endl;
    cat_profile1->set_lv2(lv2);

    std::string lv3("playoffs");
    std::cout << "lv3: " << lv3 << std::endl;
    cat_profile1->set_lv3(lv3);

    std::string lv4("final games");
    std::cout << "lv4: " << lv4 << std::endl;
    cat_profile1->set_lv4(lv4);

    qqnews::CatProfile* cat_profile2 = user_info->add_cat_profile();

    type = "";
    std::cout << "type: " << type << std::endl;
    cat_profile2->set_type(type);

    weight = "0.4";
    std::cout << "weight: " << weight << std::endl;
    cat_profile2->set_weight(weight);

    lv1 = "football";
    std::cout << "lv1: " << lv1 << std::endl;
    cat_profile2->set_lv1(lv1);

    lv2 = "premier";
    std::cout << "lv2: " << lv2 << std::endl;
    cat_profile2->set_lv2(lv2);

    lv3 = "normal match";
    std::cout << "lv3: " << lv3 << std::endl;
    cat_profile2->set_lv3(lv3);

    lv4 = "midtern";
    std::cout << "lv4: " << lv4 << std::endl;
    cat_profile2->set_lv4(lv4);

    luanewsinfo.SerializeToString(output);
}

void SendAndRecvRequest(const std::string& send_format_str, std::string* recv_format_str) {
    *recv_format_str = send_format_str;
    std::cout << "-------------------" << std::endl;
}

void Server(const std::string& data) {
    std::cout << "Server called." << std::endl;

    qqnews::LuaNewsInfo luanewsinfo;
    luanewsinfo.ParseFromString(data);

    int lua_id = 0;
    lua_id = luanewsinfo.lua_id();
    std::cout << "lua_id: " << lua_id << std::endl;

    const qqnews::KBUserInfo& user_info = luanewsinfo.user_info();
    const int cat_profile_sz = user_info.cat_profile_size();
    for(int i = 0; i < cat_profile_sz; ++i) {
        const qqnews::CatProfile& cat_profile = user_info.cat_profile(i);
        
        const std::string& lv1 = cat_profile.lv1();
        std::cout << "lv1: " << lv1 << std::endl;

        const std::string& lv2 = cat_profile.lv2();
        std::cout << "lv2: " << lv2 << std::endl;
    }

}

int main(void) {

    std::string send_format_str;
    std::string recv_format_str;

    Client(&send_format_str);
    SendAndRecvRequest(send_format_str, &recv_format_str);
    Server(recv_format_str);

    return 0;
}
