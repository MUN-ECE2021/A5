#include <iostream>
#include <algorithm>
#include "SocialNetwork.h"
#include "User.h"
using namespace std;

int main()
{
    //!Start Basic Tests
    SocialNetwork Term4;

    //test addUser()
    User::ID Glyn_George    = Term4.addUser("Glyn H. George");
    User::ID Liang          = Term4.addUser("Xiaodong Liang");
    User::ID Andrew_Vardy   = Term4.addUser("Andrew Vardy");
    User::ID Quaicoe        = Term4.addUser("John E. Quaicoe");
    User::ID Mashrura       = Term4.addUser("Mashrura Musharraf");
    User::ID Anderson       = Term4.addUser("Jonathan R. Anderson");
    User::ID Daniela        = Term4.addUser("Daniela Silvesan");


    //test addFriendship
    Term4.addFriendship(Andrew_Vardy, Anderson);
    Term4.addFriendship(Glyn_George,  Daniela);
    Term4.addFriendship(Liang,        Mashrura);
    Term4.addFriendship(Mashrura,     Daniela);
    Term4.addFriendship(Glyn_George,  Quaicoe);
    Term4.addFriendship(Andrew_Vardy, Quaicoe);
    Term4.addFriendship(Liang,        Quaicoe);
    Term4.addFriendship(Mashrura,     Quaicoe);
    Term4.addFriendship(Daniela,      Quaicoe);
    Term4.addFriendship(Andrew_Vardy, Mashrura);


    //test id()
    assert(Glyn_George  == Term4.getUser(Glyn_George).id());
    assert(Liang        == Term4.getUser(Liang).id());
    assert(Andrew_Vardy == Term4.getUser(Andrew_Vardy).id());
    assert(Quaicoe      == Term4.getUser(Quaicoe).id());
    assert(Mashrura     == Term4.getUser(Mashrura).id());
    assert(Anderson     == Term4.getUser(Anderson).id());
    assert(Daniela      == Term4.getUser(Daniela).id());


    //test degree()
    assert(Term4.getUser(Glyn_George).degree()  == 2);
    assert(Term4.getUser(Quaicoe).degree()      == 5);
    assert(Term4.getUser(Liang).degree()        == 2);
    assert(Term4.getUser(Mashrura).degree()     == 4);
    assert(Term4.getUser(Andrew_Vardy).degree() == 3);
    assert(Term4.getUser(Anderson).degree()     == 1);
    assert(Term4.getUser(Daniela).degree()      == 3);


    //test distance
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Andrew_Vardy)) == 1);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Quaicoe))      == 2);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Mashrura))     == 2);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Daniela))      == 3);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Liang))        == 3);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Glyn_George))  == 3);


    //test SocialNetwork Iterator
    int j = 1;
    for(auto i = Term4.begin(); i != Term4.end(); i++)
    {
        if(j < 8)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }


    //test find()
    auto i = Term4.find("Glyn H. George");
    assert((*i).id() == Term4.getUser(Glyn_George).id());

    i = Term4.find("J");
    assert((*i).id() == Term4.getUser(Anderson).id() or (*i).id() == Term4.getUser(Quaicoe).id());
    i++;
    assert((*i).id() == Term4.getUser(Anderson).id() or (*i).id() == Term4.getUser(Quaicoe).id());


    //test User Iterator
    j = 1;
    for(auto i = Term4.getUser(Quaicoe).begin(); i != Term4.getUser(Quaicoe).end(); i++)
    {
        if(j < 6)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }


    //test User friendsOfFriends()
    j = 1;
    for(auto i = Term4.getUser(Quaicoe).friendsOfFriends(); i != Term4.getUser(Quaicoe).end(); i++)
    {
        if(j < 7)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }

    j = 1;
    std::vector<User::ID> friendsFriends1;
    std::vector<User::ID> friendsFriends2;
    friendsFriends1.push_back(Andrew_Vardy);
    friendsFriends1.push_back(Quaicoe);
    friendsFriends1.push_back(Mashrura);
    for(auto i = Term4.getUser(Anderson).friendsOfFriends(); i != Term4.getUser(Anderson).end(); i++)
    {
        if(j < 4)
        {
            friendsFriends2.push_back((*i).id());
            j++;
        }
    }
    std::sort(friendsFriends1.begin(), friendsFriends1.end());
    std::sort(friendsFriends2.begin(), friendsFriends2.end());
    assert(friendsFriends1 == friendsFriends2);
    //!End Basic Tests


    //!Start Advanced Tests
    SocialNetwork Term3;

    Term3.addUser("Glyn H. George");
    Term3.addUser("Darlene Spracklin-Reid");
    Term3.addUser("Susan Caines");
    Term3.addUser("Ramachandran Venkatesan");
    Term3.addUser("John E. Quaicoe");
    Term3.addUser("Andrew House");
    Term3.addUser("Mykhaylo Evstigneev");


    //!End Advanced tests

    std::cout << "Congrats, you did it." << std::endl;
    return 0;
}
