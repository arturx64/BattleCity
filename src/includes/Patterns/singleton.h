#ifndef SINGLETON_H
#define SINGLETON_H

namespace BattleCity
{
namespace Patterns
{
template<typename T>
class CSingleton
{
public:
    static T& instance()
    {
        static T obj;
        return obj;

    }

private:
    CSingleton() {}

    /**@name NoCopy_NoMove
    /** @{*/
    CSingleton( const CSingleton& obj ) = delete;
    CSingleton& operator = ( const CSingleton& obj ) = delete;
    CSingleton( CSingleton&& obj ) = delete;
    CSingleton& operator = ( CSingleton&& obj ) = delete;
    /** @}*/

    virtual ~CSingleton() = 0 {}
};
}
}

#endif // SINGLETON_H
