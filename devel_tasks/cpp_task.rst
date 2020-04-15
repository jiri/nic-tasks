========
CPP TASK
========

Use: C++14 or newer, stl, boost libraries 1.67.0 or newer

Write a class ``DbValue`` representing a value retrieved from database in a form of text and a flag as a indication of ``NULL`` value. Internal representation is up to you.

For this class implement method:
  - ``bool is_null()``

which would return ``true`` if instance carries ``NULL`` value, otherwise ``false``.

and two template methods:
  - ``template<typename T> T as()``
  - ``template<typename T> void into(T&)``

which would convert internal string representation to following types:
  - ``int``
  - ``std::string``
  - ``boost::posix_time::ptime``
  - ``boost::optional<T>`` where ``T`` are all types above, explicitly:

    - ``boost::optional<int>``
    - ``boost::optional<std::string>``
    - ``boost::optional<boost::posix_time::ptime>``

Conversion requirements:
  - for cases when there is no meaningful conversion possible (for example ``DbValue("foo")`` to ``int``) throw exception
  - note that ``DbValue`` instance which carries a ``NULL`` value:

    -  cannot be converted to ``T`` and should throw exception
    -  can be conveted to ``boost::optional<T>`` and should return ``boost::optional<T>{boost::none}``

  - program with conversions for types which are not implemented should not build (compile or linker error).

Design your solution in a way that adding a new conversion is as simple as possible.

Usage examples:
::

    {
        const auto v = DbValue{"42"};
        v.is_null();  // false

        const auto c1 = v.as<int>();  // ok c1 == 42

        int c2{};
        v.into(c2);  // ok c2 == 42
    }

    {
        const auto v = DbValue{"foo"};
        const auto c = v.as<boost::optional<std::string>>();  // ok *c == "foo"
        static_cast<bool>(c);  // true

        v.as<int>();  // exception (cannot convert) }
    }

    {
        const auto v = DbValue{};
        v.is_null();  // true

        const auto c = v.as<boost::optional<std::string>>();  // ok
        static_cast<bool>(c);  // false

        v.as<std::string>();  // exception (value is null)
    }

    {
        const auto v = DbValue{"1.1"};
        const auto c = v.as<double>();  // build error (conversion not defined)
    }
