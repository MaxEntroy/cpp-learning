#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <gflags/gflags.h>

/* 声明：demo 参照https://blog.csdn.net/jcjc918/article/details/50876613
 * 侵删
 * */

DEFINE_string(host, "127.0.0.1", "the server host");
DEFINE_int32(port, 6035, "the server port");

DEFINE_string(index_conf, "", "[index_name,index_type]");

static bool legal(char ch) { return ch != ',';}
static bool illegal(char ch) { return !legal(ch);}

static void SplitString(const std::string& txt, std::vector<std::string>* pstrings) {
    typedef std::string::const_iterator const_iter;
    const_iter b = txt.begin();
    const_iter e = txt.end();
    while(b != e) {
        b = find_if(b, e, legal);
        if (b != e) {
            const_iter after = find_if(b, e, illegal);
            pstrings->push_back(std::string(b, after));
            b = after;
        }
    }
}

static bool legal1(char ch) { return ch != ':';}
static bool illegal1(char ch) { return !legal1(ch);}

static void SplitString1(const std::string& txt, std::vector<std::string>* pstrings) {
    typedef std::string::const_iterator const_iter;
    const_iter b = txt.begin();
    const_iter e = txt.end();
    while(b != e) {
        b = find_if(b, e, legal1);
        if (b != e) {
            const_iter after = find_if(b, e, illegal1);
            pstrings->push_back(std::string(b, after));
            b = after;
        }
    }
}

static void Test1() {
    std::cout << "Server host: " << FLAGS_host << std::endl
        << "Server port: " << FLAGS_port << std::endl;
}

static void Test2() {
    std::vector< std::pair<std::string, std::string> > index_conf;
    std::vector<std::string> index_conf_list;
    SplitString(FLAGS_index_conf, &index_conf_list);

    int sz = index_conf_list.size();
    for(int i = 0; i < sz; ++i) {
        std::vector<std::string> a_conf;
        SplitString1(index_conf_list[i], &a_conf);
        index_conf.push_back(std::make_pair(a_conf[0], a_conf[1]));
    }

    sz = index_conf.size();
    for(int i = 0; i < sz; ++i) {
        std::cout << index_conf[i].first << ":" << index_conf[i].second << std::endl;
    }
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    Test2();
    return 0;
}
