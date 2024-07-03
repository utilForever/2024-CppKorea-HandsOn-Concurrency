#include <atomic>
#include <iostream>

struct doubleInt8
{
    std::int8_t v1, v2;
};

struct doubleInt16
{
    std::int16_t v1, v2;
};

struct doubleInt32
{
    std::int32_t v1, v2;
};

struct doubleInt64
{
    std::int64_t v1, v2;
};

int main()
{
    std::atomic<std::int8_t> aint8;
    std::cout << "int8 size: " << sizeof(aint8) << "bytes. is lock free? "
              << aint8.is_lock_free() << '\n';

    std::atomic<std::int16_t> aint16;
    std::cout << "int16 size: " << sizeof(aint16) << "bytes. is lock free? "
              << aint16.is_lock_free() << '\n';

    std::atomic<std::int32_t> aint32;
    std::cout << "int32 size: " << sizeof(aint32) << "bytes. is lock free? "
              << aint32.is_lock_free() << '\n';

    std::atomic<std::int64_t> aint64;
    std::cout << "int64 size: " << sizeof(aint64) << "bytes. is lock free? "
              << aint64.is_lock_free() << '\n';

    std::atomic<doubleInt8> adint8;
    std::cout << "doubleInt8 size: " << sizeof(adint8)
              << "bytes. is lock free? " << adint8.is_lock_free() << '\n';

    std::atomic<doubleInt16> adint16;
    std::cout << "doubleInt16 size: " << sizeof(adint16)
              << "bytes. is lock free? " << adint16.is_lock_free() << '\n';

    std::atomic<doubleInt32> adint32;
    std::cout << "doubleInt32 size: " << sizeof(adint32)
              << "bytes. is lock free? " << adint32.is_lock_free() << '\n';

    std::atomic<doubleInt64> adint64;
    std::cout << "doubleInt64 size: " << sizeof(adint64)
              << "bytes. is lock free? " << adint64.is_lock_free() << '\n';
}
