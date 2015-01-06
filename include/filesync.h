#ifndef filesync_H
#define filesync_H


class Filesystem
{
public:
    virtual ~Filesystem() = default;
    virtual void list() = 0;
};

#endif
