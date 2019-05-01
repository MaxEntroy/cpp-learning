#include "inc/common.h"
#include "inc/meta_indexer.h"

int main(void) {
    ArticleInfo a;
    lua_State* L = NULL;
    MetaIndexer::tag_cms_parser(L, a);
    return 0;
}
