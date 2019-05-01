#ifndef COMMON_H_
#define COMMON_H_

class ArticleInfo {
public:
    ArticleInfo() : id_(-1) {}
    int id() const {return id_;}
private:
    int id_;
};

class ShortVideoInfo {
public:
    ShortVideoInfo() : id_(-1) {}
    int id() const {return id_;}
private:
    int id_;
};

#endif
