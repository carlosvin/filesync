#ifndef filesync_H
#define filesync_H


class Filesystem
{
public:
    virtual ~Filesystem() = default;
    virtual void list() = 0;
};

// the types of the class factories
typedef Filesystem* create_t();
typedef void destroy_t(Filesystem*);

#endif
