#ifndef META_INDEXER_H_
#define META_INDEXER_H_
extern "C" {
#include "lua.h"
}


class MetaIndexer {
public:
    MetaIndexer() {}

    template<class T>
    static int tag_cms_parser(lua_State* L, const T& info);

};

#endif

