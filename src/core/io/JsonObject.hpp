#ifndef JSONOBJECT_HPP_
#define JSONOBJECT_HPP_

#include "JsonUtils.hpp"

namespace Tungsten {

class JsonObject
{
    typedef rapidjson::Document::AllocatorType Allocator;

    Allocator &_allocator;
    rapidjson::Value _value;

    /* Terminator for variadic recursion */
    void add() {}

public:
    template<typename... Ts>
    JsonObject(Allocator &allocator, Ts &&... ts)
    : JsonObject(rapidjson::Value(rapidjson::kObjectType), allocator, std::forward<Ts>(ts)...)
    {
    }

    template<typename... Ts>
    JsonObject(rapidjson::Value value, Allocator &allocator, Ts &&... ts)
    : _allocator(allocator),
      _value(std::move(value))
    {
        add(std::forward<Ts>(ts)...);
    }

    operator rapidjson::Value()
    {
        return std::move(_value);
    }

    template<size_t N, typename T, typename... Ts>
    void add(const char (&key)[N], T &&value, Ts &&... ts)
    {
        _value.AddMember(rapidjson::StringRef(key, N - 1), JsonUtils::toJson(std::move(value), _allocator), _allocator);
        add(std::forward<Ts>(ts)...);
    }
};

}

#endif /* JSONOBJECT_HPP_ */
