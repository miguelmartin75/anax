// Copyright 2013 by Martin Moene
//
// lest is based on ideas by Kevlin Henney, see video at
// http://skillsmatter.com/podcast/agile-testing/kevlin-henney-rethinking-unit-testing-in-c-plus-plus
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LEST_LEST_H_INCLUDED
#define LEST_LEST_H_INCLUDED

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#ifndef lest_NO_SHORT_ASSERTION_NAMES
# define EXPECT           lest_EXPECT
# define EXPECT_THROWS    lest_EXPECT_THROWS
# define EXPECT_THROWS_AS lest_EXPECT_THROWS_AS
#endif

#define lest_EXPECT( expr ) \
    try \
    { \
        if ( ! (expr) ) \
            throw lest::failure{ lest_LOCATION, #expr }; \
    } \
    catch( lest::failure const & ) \
    { \
        throw ; \
    } \
    catch( std::exception const & e ) \
    { \
        throw lest::unexpected{ lest_LOCATION, #expr, lest::with_message( e.what() ) }; \
    } \
    catch(...) \
    { \
        throw lest::unexpected{ lest_LOCATION, #expr, "of unknown type" }; \
    }

#define lest_EXPECT_THROWS( expr ) \
    for (;;) \
    { \
        try { lest::serum( expr ); } catch (...) { break; } \
        throw lest::expected{ lest_LOCATION, #expr }; \
    }

#define lest_EXPECT_THROWS_AS( expr, excpt ) \
    for (;;) \
    { \
        try { lest::serum( expr ); } catch ( excpt & ) { break; } catch (...) {} \
        throw lest::expected{ lest_LOCATION, #expr, lest::of_type( #excpt ) }; \
    }

#define lest_LOCATION lest::location{__FILE__, __LINE__}

namespace lest {

struct test
{
    const std::string name;
    const std::function<void()> behaviour;
};

struct location
{
    const std::string file;
    const int line;

    location( std::string file, int line )
    : file{ file }, line{ line } {}
};

struct comment
{
    const std::string text;

    comment( std::string text ) : text{ text } {}
    explicit operator bool() { return text.length() > 0; }
};

struct message : std::runtime_error
{
    const std::string kind;
    const location where;
    const comment note;

    message( std::string kind, location where, std::string expr, std::string note = "" )
    : std::runtime_error{ expr }, kind{ kind }, where{ where }, note{ note } {}
};

struct failure : message
{
    failure( location where, std::string expr )
    : message{ "failed", where, expr } {}
};

struct expected : message
{
    expected( location where, std::string expr, std::string excpt = "" )
    : message{ "failed: didn't get exception", where, expr, excpt } {}
};

struct unexpected : message
{
    unexpected( location where, std::string expr, std::string note )
    : message{ "failed: got unexpected exception", where, expr, note } {}
};

inline bool serum( bool verum ) { return verum; }

inline std::string with_message( std::string text )
{
    return "with message \"" + text + "\"";
}

inline std::string of_type( std::string text )
{
    return "of type " + text;
}

inline std::string pluralise( int n, std::string text )
{
    return n == 1 ? text : text + "s";
}

inline std::ostream & operator<<( std::ostream & os, comment note )
{
    return os << (note ? " " + note.text : "" );
}

inline std::ostream & operator<<( std::ostream & os, location where )
{
#ifdef __GNUG__
    return os << where.file << ":" << where.line;
#else
    return os << where.file << "(" << where.line << ")";
#endif
}

inline void report( std::ostream & os, message const & e, std::string test )
{
    os << e.where << ": " << e.kind << e.note << ": " << test << ": " << e.what() << std::endl;
}

template<std::size_t N>
int run( test const (&specification)[N], std::ostream & os = std::cout )
{
    int failures = 0;

    for ( auto & testing : specification )
    {
		os << "testing: " << testing.name << '\n';
        try
        {
            testing.behaviour();
        }
        catch( message const & e )
        {
            ++failures;
            report( os, e, testing.name );
        }
    }

    if ( failures > 0 )
    {
        os << failures << " out of " << N << " " << pluralise(N, "test") << " failed." << std::endl;
    }

    return failures;
}

} // namespace lest

#endif // LEST_LEST_H_INCLUDED
