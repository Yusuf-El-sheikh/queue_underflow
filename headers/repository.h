#include <memory>
#include <vector>

template <typename T>
class repository
{
public:
    virtual unique_ptr<T> find_by_id(int id) = 0;
    virtual vector<T> find_all() = 0;
    virtual void save(const T &object) = 0;
    virtual void remove(const int id) = 0;

    virtual ~repository() = default;
};