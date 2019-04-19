#include <iostream>
#include <string>
#include <map>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class ArticleDocInfo {
public:
    ArticleDocInfo() : id_(0) {}

    int id() const {return id_;}
private:
    int id_;
};


class ShortVideoDocInfo {
public:
    ShortVideoDocInfo() : id_(-1) {}

    int id() const {return id_;}
private:
    int id_;
};

class MetaIndexer {
public:
    MetaIndexer() {}

    static int id_parser(lua_State* L, const ArticleDocInfo& info) {return info.id();}
    static int vid_parser(lua_State* L, const ShortVideoDocInfo& info) {return info.id();}

    template<class T>
    static int common_parser(lua_State* L, const T& info) {return info.id();}
private:

};

typedef int (*article_parser)(lua_State*, const ArticleDocInfo&);
typedef int (*video_parser)(lua_State*, const ShortVideoDocInfo&);

// value类型可以绑定泛型
// 调用的时候 需要传递正确的类型 否则编译失败
static std::pair<std::string, article_parser> article_pair[] = {
    std::make_pair<std::string, article_parser>("id", MetaIndexer::common_parser),
};
static std::pair<std::string, video_parser> video_pair[] = {
    std::make_pair<std::string, video_parser>("id", MetaIndexer::common_parser),
};


int main(void) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    ArticleDocInfo info;
    article_parser parser = article_pair[0].second;
    std::cout << parser(L, info) << std::endl;

    ShortVideoDocInfo vinfo;
    video_parser vparser = video_pair[0].second;
    std::cout << vparser(L, vinfo) << std::endl;

    lua_close(L);
    return 0;
}
