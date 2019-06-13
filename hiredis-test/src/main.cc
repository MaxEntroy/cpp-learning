#include <iostream>
#include <gflags/gflags.h>
extern "C" {
#include "hiredis/hiredis.h"
}

DEFINE_string(host, "", "the server host");
DEFINE_int32(port, 6379, "the server port");
DEFINE_string(pwd, "", "the server host");

void RedisTest(const std::string& ip, uint32_t port, const std::string& pwd) {
    redisContext* predis = redisConnect(ip.c_str(), port);
    if(!predis || predis->err) {
        std::cerr << predis->errstr << std::endl;
        redisFree(predis);
        return;
    }

    const std::string space = " ";
    const std::string auth = "auth" + space + pwd;
    const std::string key1 = "105";
    const std::string key2 = "102";
    const std::string cmd = "mget" + space + key1 + space + key2;
    std::cout  << "cmd:"<< cmd << std::endl;
    redisReply* preply = NULL;

    preply = static_cast<redisReply*>( redisCommand(predis, auth.c_str()) );
    if(!preply) {
        std::cerr << "redisReply error" << std::endl;
        redisFree(predis);
        return;
    }
    freeReplyObject(preply);

    preply = static_cast<redisReply*>( redisCommand(predis, cmd.c_str()) );
    if(!preply) {
        std::cerr << "redisReply error" << std::endl;
        redisFree(predis);
        return;
    }
    if(preply->type == REDIS_REPLY_ERROR) {
        std::cerr << "reply:" << preply->str << std::endl;
    }
    else if(preply->type != REDIS_REPLY_ARRAY) {
        std::cerr << "unexpected type: " << preply->type << std::endl;
    }
    else {
        int sz = preply->elements;
        for(int i = 0; i < sz; ++i) {
            redisReply* pchild_reply = preply->element[i];
            if(!pchild_reply) {
                std::cerr << "redisReply error" << std::endl;
                redisFree(predis);
                return;
            }
            else if(pchild_reply->type != REDIS_REPLY_STRING) {
                std::cerr << "unexpected type: " << preply->type << std::endl;
            }
            else{
                std::cout << pchild_reply->str << std::endl;
            }
        }
    }
    freeReplyObject(preply);

    redisFree(predis);
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    RedisTest(FLAGS_host, static_cast<uint32_t>(FLAGS_port), FLAGS_pwd);
    return 0;
}
