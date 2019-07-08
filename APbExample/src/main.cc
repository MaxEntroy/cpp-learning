#include <iostream>
#include "luacall.pb.h"
#include "profile.pb.h"

void Client(std::string* output) {
    std::cout << "Client called." << std::endl;
    std::string sep_line(32, '-');

    qqnews::LuaNewsInfo luanewsinfo;

    int lua_id = 1;
    std::cout << "lua_id: " << lua_id << std::endl;
    luanewsinfo.set_lua_id(lua_id);

    int test_field = 32;
    std::cout << "test_field: " << test_field << std::endl;
    //luanewsinfo.set_test_field(test_field);

    qqnews::KBUserInfo* user_info = luanewsinfo.mutable_user_info();

    std::cout << sep_line << std::endl;
    qqnews::CatProfile* cat_profile1 = user_info->add_cat_profile();

    std::string type("realtime_profile");
    //std::cout << "type: " << type << std::endl;
    //cat_profile1->set_type(type);

    std::string weight("0.3");
    //std::cout << "weight: " << weight << std::endl;
    //cat_profile1->set_weight(weight);

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

    std::cout << sep_line << std::endl;
    qqnews::CatProfile* cat_profile2 = user_info->add_cat_profile();

    type = "longtime_profile";
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
    std::cout << sep_line << std::endl;
}

void SendAndRecvRequest(const std::string& send_format_str, std::string* recv_format_str) {
    *recv_format_str = send_format_str;
}

void Server(const std::string& data) {
    std::cout << "Server called." << std::endl;
    std::string sep_line(32, '-');

    qqnews::LuaNewsInfo luanewsinfo;
    luanewsinfo.ParseFromString(data);

    int lua_id = 0;
    lua_id = luanewsinfo.lua_id();
    std::cout << "lua_id: " << lua_id << std::endl;

    int test_field = -1;
    test_field = luanewsinfo.test_field();
    std::cout << "test_field: " << test_field << std::endl;
    std::cout << sep_line << std::endl;

    const qqnews::KBUserInfo& user_info = luanewsinfo.user_info();
    const int cat_profile_sz = user_info.cat_profile_size();
    for(int i = 0; i < cat_profile_sz; ++i) {
        const qqnews::CatProfile& cat_profile = user_info.cat_profile(i);

        const std::string& type = cat_profile.type();
        if(type.empty()) {std::cout << "empty type" << std::endl;}
        std::cout << "type: " << type << std::endl;

        const std::string& weight = cat_profile.weight();
        if(weight.empty()) {std::cout << "empty weight" << std::endl;}
        std::cout << "weight: " << weight << std::endl;

        const std::string& lv1 = cat_profile.lv1();
        std::cout << "lv1: " << lv1 << std::endl;

        const std::string& lv2 = cat_profile.lv2();
        std::cout << "lv2: " << lv2 << std::endl;

        const std::string& lv3 = cat_profile.lv3();
        std::cout << "lv3: " << lv3 << std::endl;

        const std::string& lv4 = cat_profile.lv4();
        std::cout << "lv4: " << lv4 << std::endl;

        std::cout << sep_line << std::endl;
    }

}

void ServerWithReflection(const std::string& data) {
    std::cout << "ServerWithReflection called." << std::endl;
    std::string sep_line(32, '-');

    qqnews::LuaNewsInfo luanewsinfo;
    luanewsinfo.ParseFromString(data);

    // lua_id是固定字段，并不存在总是修改的情形，所以不用反射
    // 反射使用相对麻烦，如果不是刚需，建议不用
    int lua_id = 0;
    lua_id = luanewsinfo.lua_id();
    std::cout << "lua_id: " << lua_id << std::endl;

    int test_field = -1;
    test_field = luanewsinfo.test_field();
    std::cout << "test_field: " << test_field << std::endl;
    std::cout << sep_line << std::endl;

    const qqnews::KBUserInfo& user_info = luanewsinfo.user_info();
    const ::google::protobuf::Descriptor* pd = user_info.GetDescriptor();
    if (pd->FindFieldByName("cat_profile")) {
        std::cout << "cat_profile is a field" << std::endl;
    }else {
        std::cout << "no repeated field" << std::endl;
        return;
    }
    std::cout << sep_line << std::endl;

    const int cat_profile_sz = user_info.cat_profile_size();
    for(int i = 0; i < cat_profile_sz; ++i) {
        const qqnews::CatProfile& cat_profile = user_info.cat_profile(i);

        // CatProfile存在经常变更的情形
        // 如果每次pb修改，相应的解析部分都要修改
        // 由于不可能知道未来还有什么字段，所以，只能增加新字段，再增加解析函数，不灵活
        // 采用反射避免
        const ::google::protobuf::Descriptor* p_descriptor = cat_profile.GetDescriptor();
        const ::google::protobuf::Reflection* p_reflection = cat_profile.GetReflection();
        const ::google::protobuf::FieldDescriptor* p_field_descriptor = NULL;

        std::string name = p_descriptor->name();
        std::cout << "name: " << name << std::endl;

        int field_count = p_descriptor->field_count();
        for(int j = 0; j < field_count; ++j) {
            p_field_descriptor = p_descriptor->field(j);
            const ::google::protobuf::FieldDescriptor::CppType cpp_type = p_field_descriptor->cpp_type();

            std::string key = p_field_descriptor->name();
            std::string value;

            switch(cpp_type) {
                case ::google::protobuf::FieldDescriptor::CPPTYPE_STRING:
                    value = p_reflection->GetString(cat_profile, p_field_descriptor);
                    break;
                default:break;
            }

            std::cout << key << ": " << value << std::endl;
        }
        std::cout << sep_line << std::endl;
    }
}

int main(void) {

    std::string send_format_str;
    std::string recv_format_str;

    Client(&send_format_str);
    SendAndRecvRequest(send_format_str, &recv_format_str);
    Server(recv_format_str);
    ServerWithReflection(recv_format_str);

    return 0;
}
