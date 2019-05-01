#include "inc/meta_indexer.h"
extern "C" {
#include "lua.h"
}
#include <iostream>
#include "inc/common.h"

template<>
int MetaIndexer::tag_cms_parser(lua_State* L, const ShortVideoInfo& info) {
    std::cout << info.id() << std::endl;
    return 0;
}

template<>
int MetaIndexer::tag_cms_parser(lua_State* L, const ArticleInfo& info) {
    std::cout << info.id() << std::endl;
    return 0;
}
