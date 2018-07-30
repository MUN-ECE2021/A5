#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include "SocialNetwork.cpp"
#include "User.cpp"
using namespace std;

//Command to Run Tests: c++ -std=c++11 main.cpp -lgtest -lgtest_main -lpthread

std::vector<User*> createFriendships(){
    User* Moe = new User("Moe");
    User* B = new User("b");
    User* C = new User("c");
    User* D = new User("d");
    User* E = new User("e");
    User* F = new User("f");
   User* G = new User("g");

    Moe->addFriend(*B);
    Moe->addFriend(*C);
    Moe->addFriend(*D);
    Moe->addFriend(*E);

    B->addFriend(*Moe);
    B->addFriend(*E);
    B->addFriend(*D);

    C->addFriend(*Moe);

    D->addFriend(*G);
    D->addFriend(*B);
    D->addFriend(*Moe);

    E->addFriend(*Moe);
    E->addFriend(*B);

    G->addFriend(*D);

    F->addFriend(*F);

    std::vector<User*> fakeNetwrok {Moe, B, C, D, E, F, G};

    return fakeNetwrok;


    
}

void deleteFriendships( std::vector<User*> users )
{
    for (size_t i = 0; i < users.size(); i++)
    {
        delete users[i];
    }
}

//Testing Constructor
TEST (User_Constructor,constructor){
    User me = User("Mohamed");
    EXPECT_EQ (me.id(), 0);

    User me2 = User("Mohamed");
    User me3 = User("Mohamed");
}

TEST (User,Id){
    std::vector<User> users;
    std::vector<User::ID> ids;

    for (int i = 0; i<10; i++){
        std::string name = "Moe" + std::to_string(i);
        users.emplace_back(User(name));
        //std::cout << "id: " << users[i].id() << "\n";
        ids.push_back(users[i].id());
    }


    for( auto i = users.begin(); i != users.end(); i++ )
    {
        User::ID count = 0;
        for (size_t j = 0; j < ids.size(); j++)
        {
            //std::cout << "ids: " << ids[j] <<" ";
            if (ids[j] == (*i).id())
                count++;
        }
        EXPECT_TRUE(count == 1);
    }
}



TEST (User, degree)
{
    std::vector<User*> users = createFriendships();
    //Moe
    size_t d = 4;
    EXPECT_EQ(users[0]->degree(), d);

    //B
    d = 3;
    EXPECT_EQ(users[1]->degree(), d);

    //C
    d = 1;
    EXPECT_EQ(users[2]->degree(), d);

    //D
    d = 3;
    EXPECT_EQ(users[3]->degree(), d);

    //E
    d = 2;
    EXPECT_EQ(users[4]->degree(), d);

    //F
    d = 0;
    EXPECT_EQ(users[5]->degree(), 0);

    //G
    d = 1;
    EXPECT_EQ(users[6]->degree(), 1);

    deleteFriendships(users);

}

TEST (User, distance)
{
    std::vector<User*> users = createFriendships();
    //distance between Moe * B, C, D, E, F, G
    size_t d = 1;
    EXPECT_EQ(users[0]->distance(*users[1]), d);
    d = 1;
    EXPECT_EQ(users[0]->distance(*users[2]), d);
    d = 1;
    EXPECT_EQ(users[0]->distance(*users[3]), d);
    d = 1;
    EXPECT_EQ(users[0]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[0]->distance(*users[5]), d);
    d = 2;
    EXPECT_EQ(users[0]->distance(*users[6]), d);
    d = 0;
    EXPECT_EQ(users[0]->distance(*users[0]), d);

    //distance between B * Moe, C, D, E, F, G
    d = 1;
    EXPECT_EQ(users[1]->distance(*users[0]), d);
    d = 2;
    EXPECT_EQ(users[1]->distance(*users[2]), d);
    d = 1;
    EXPECT_EQ(users[1]->distance(*users[3]), d);
    d = 1;
    EXPECT_EQ(users[1]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[1]->distance(*users[5]), d);
    d = 2;
    EXPECT_EQ(users[1]->distance(*users[6]), d);
    d = 0;
    EXPECT_EQ(users[1]->distance(*users[1]), d);


//distance between C * Moe B, D, E, F, G, C
    d = 2;
    EXPECT_EQ(users[2]->distance(*users[1]), d);
    d = 0;
    EXPECT_EQ(users[2]->distance(*users[2]), d);
    d = 2;
    EXPECT_EQ(users[2]->distance(*users[3]), d);
    d = 2;
    EXPECT_EQ(users[2]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[2]->distance(*users[5]), d);
    d = 3;
    EXPECT_EQ(users[2]->distance(*users[6]), d);
    d = 1;
    EXPECT_EQ(users[2]->distance(*users[0]), d);


//distance between D * B, C, Moe, D, E, F, G
    d = 1;
    EXPECT_EQ(users[3]->distance(*users[1]), d);
    d = 2;
    EXPECT_EQ(users[3]->distance(*users[2]), d);
    d = 0;
    EXPECT_EQ(users[3]->distance(*users[3]), d);
    d = 2;
    EXPECT_EQ(users[3]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[3]->distance(*users[5]), d);
    d = 1;
    EXPECT_EQ(users[3]->distance(*users[6]), d);
    d = 1;
    EXPECT_EQ(users[3]->distance(*users[0]), d);


//distance between E * B, C, D, Moe, E, F, G
    d = 1;
    EXPECT_EQ(users[4]->distance(*users[1]), d);
    d = 2;
    EXPECT_EQ(users[4]->distance(*users[2]), d);
    d = 2;
    EXPECT_EQ(users[4]->distance(*users[3]), d);
    d = 0;
    EXPECT_EQ(users[4]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[4]->distance(*users[5]), d);
    d = 3;
    EXPECT_EQ(users[4]->distance(*users[6]), d);
    d = 1;
    EXPECT_EQ(users[4]->distance(*users[0]), d);

//distance between F * B, C, D, Moe, E, F, G
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[1]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[2]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[3]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[4]), d);
    d = 0;
    EXPECT_EQ(users[5]->distance(*users[5]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[6]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[5]->distance(*users[0]), d);

//distance between G * B, C, D, Moe, E, F, G
    d = 2;
    EXPECT_EQ(users[6]->distance(*users[1]), d);
    d = 3;
    EXPECT_EQ(users[6]->distance(*users[2]), d);
    d = 1;
    EXPECT_EQ(users[6]->distance(*users[3]), d);
    d = 3;
    EXPECT_EQ(users[6]->distance(*users[4]), d);
    d = SIZE_MAX;
    EXPECT_EQ(users[6]->distance(*users[5]), d);
    d = 0;
    EXPECT_EQ(users[6]->distance(*users[6]), d);
    d = 2;
    EXPECT_EQ(users[6]->distance(*users[0]), d);

}

TEST (User_addFriend, addManyFriends)
{
    std::vector<User> users;
    //create 10 users
    for(int i = 0; i < 10; i++)
    {
        std::string name = "MBtex" + std::to_string(i);
        users.emplace_back(User(name));
    }

    for (size_t i = 0; i < users.size(); i++)
    {
        for(size_t j = (users.size()-1); j > i; j-- ){
            users[j].addFriend(users[i]);
        }

    }
    for(size_t i = 0; i < users.size(); i++)
    {
        //std::cout<< "users degree: "<< users[i].degree() << "\n";
        EXPECT_TRUE(users[i].degree() == i);
    }

}

TEST(User_addFriend,FriendYourself )
{
    User u1 = User("mbtex");
    
    u1.addFriend(u1);
    u1.addFriend(u1);
    u1.addFriend(u1);
    u1.addFriend(u1);
    size_t d = 0;
    EXPECT_EQ(u1.degree(), d);
}

TEST(User, addSameFriendAgain)
{
    User u1 = User("mbtex");
    User u2 = User("MbTec");
    
    u1.addFriend(u2);
    u1.addFriend(u2);
    u1.addFriend(u2);
    u1.addFriend(u2);
    u1.addFriend(u2);
    u1.addFriend(u1);
    size_t d = 1;
    EXPECT_EQ(u1.degree(), d);
}

//////TODO: Check Again!
TEST (User, begin)
{
    std::vector<User*> users = createFriendships();

    std::set<User::ID> friends;

    //Moe
    for (size_t j =0; j < users.size(); j++)
    {
        std::cout<< users[j]->name() <<"\' friends are:\n";
        for (auto i = users[j]->begin(); i != users[j]->end(); i++)
        {
            std::cout << (*i).name() <<"-";
        }
        std::cout<<"\n";
    } 

    deleteFriendships(users);
}

//TODO:
TEST (User, friendOfFriends)
{
    std::vector<User*> users = createFriendships();

    std::set<User::ID> friends;

    //Moe
    for (size_t j =0; j < users.size(); j++)
    {
        std::cout<< users[j]->name() <<"\' FOF- are:\n";
        for (auto i = users[j]->friendsOfFriends(); i != users[j]->end(); i++)
        {
            std::cout << (*i).name() <<"-";
        }
        std::cout<<"\n";
    } 
    auto i = users[0]-> friendsOfFriends();
    std::cout << users[0]->name() <<"\' f-o-f are: \n";
    std::cout<< (*i).name()<<"\n";
    i++;
    std::cout<< (*i).name()<<"\n";
    i++;
    std::cout<< (*i).name()<<"\n";
    i++;
    std::cout<< (*i).name()<<"\n";
    i++;
    std::cout<< (*i).name()<<"\n";
    i++;
    //std::cout<< (*i).name()<<"\n";

    deleteFriendships(users);

}



TEST(SocialNetwork, constructor)
{
    SocialNetwork SN;
}

TEST (SocialNetwork, addUser)
{
    SocialNetwork SN;
    //User me("Moe");

    User::ID ud1 = SIZE_MAX;
    ud1 = SN.addUser("mohamed");
    std::cout<< "userID: " << ud1<< "\n";
    EXPECT_NE(ud1, SIZE_MAX);
    User::ID ud2 = SIZE_MAX;
    ud2 = SN.addUser("Moe");
    std::cout<< "userID: " << ud2 << "\n";
    EXPECT_NE(ud2, SIZE_MAX);
    EXPECT_NE(ud2, ud1);
}

TEST (SocialNetwork, addFriendship)
{
    SocialNetwork SN;
    //User me("Moe");

    User::ID ud1 = SN.addUser("mohamed");
    User::ID ud2 = SN.addUser("M5");
    User::ID ud3 = SN.addUser("M4");
    User::ID ud4 = SN.addUser("M2");

    SN.addFriendship(ud1, ud2);
    SN.addFriendship(ud1, ud1);
    SN.addFriendship(ud2, ud3);
    SN.addFriendship(ud1, ud3);
    SN.addFriendship(ud4, ud4);

}

TEST (SocialNetwork, getUser)
{

    SocialNetwork SN;


    User::ID ud1 = SN.addUser("mohamed");
    User::ID ud2 = SN.addUser("M5");
    User::ID ud3 = SN.addUser("M4");
    User::ID ud4 = SN.addUser("M2");
    //std::cout << "u1 name: " << (SN.getUser(ud1)).name() <<"\n";

    EXPECT_TRUE("mohamed" == SN.getUser(ud1).name());
    EXPECT_TRUE("M5" == SN.getUser(ud2).name());
    EXPECT_TRUE("M4" == SN.getUser(ud3).name());
    EXPECT_TRUE("M2" == SN.getUser(ud4).name());

}

TEST (SocialNetwork, begin)
{
    SocialNetwork SN;


    User::ID ud1 = SN.addUser("mohamed");
    User::ID ud2 = SN.addUser("M5");
    User::ID ud3 = SN.addUser("M4");
    User::ID ud4 = SN.addUser("M2");

    //std::cout<< "testing begin\n";
    int count = 0;
    for( auto i = SN.begin(); i != SN.end(); i++ )
    {
        count++;
        //std::cout << (*i).name() <<" : " << (*i).id() <<"\n";
    }
    EXPECT_EQ(count, 4);

}

TEST (SocialNetwork, find)
{

    SocialNetwork SN;

    User::ID ud1 = SN.addUser("mohamed");
    User::ID ud2 = SN.addUser("M5");
    User::ID ud3 = SN.addUser("M4");
    User::ID ud4 = SN.addUser("M2");

    //std::cout<< "find who beign is \'mohamed\'\n";
    int count = 0;
    for(auto i = SN.find("mohamed"); i!= SN.end(); i++)
    {
        count++;
        //std::cout << (*i).name() <<" : " << (*i).id() <<"\n";
    }
    EXPECT_EQ(count, 1);

    //std::cout<< "find who beign is \'M\'\n
    
    count= 0;
    for(auto i = SN.find("M"); i!= SN.end(); i++)
    {
        count++;
        //std::cout << (*i).name() <<" : " << (*i).id() <<"\n";
    }
    EXPECT_EQ(count, 3);
    count = 0;
    //std::cout<< "find who beign is \'X\'\n";
    for(auto i = SN.find("X"); i!= SN.end(); i++)
    {
        count++;
        //std::cout << (*i).name() <<" : " << (*i).id() <<"\n";
    }
    EXPECT_EQ(count, 0);
}

int main(int argc, char **argv)

{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //return 0;
}



