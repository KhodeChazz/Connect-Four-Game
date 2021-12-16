#include <iostream> // Mahdi Khaxar
#include <cstdlib>
#include <cstdio>
#include <ctime>
#define red "\x1B[31m"
#define reset "\033[0m"
#define blue "\x1B[34m"
#define green "\x1B[32m"
#define yellow "\x1B[33m"

using namespace std;


char get_char()
{
    char option = cin.get();
    while(option=='\n')
        option=cin.get();
    return option;
}

void error(int status)
{
    cout<<yellow<<endl;
    switch(status)
    {
        case 0 : cout << "unvalid input , try again : ";break;
        case 1 : cout << "number have to be between 1 to 7 , try again :";break;
        case 2 : cout << "column is full , try again : ";break;
        case 3 : cout << "number of players must be between 3 to 8 , try again :";break;
        default : "unknown error"; break ;
    }
    cout<<reset;
    return;
}
bool validation(char character , int status)
{
    switch(status)
    {
        case 1 :
        {
            if( 0 < int(character)-48 && int(character)-48 < 8)
                return true;
            else
                return false;
        }
        case 2 :
        {
            if( 2 < int(character)-48 && int(character)-48 < 9)
                return true;
            else
                return false;
        }
        default :
            return false;
    }
}
void show_match_array(int (&matchArray)[6][7]) 
{
    cout<<"\n";
    for(int row = 5 ; row > -1 ; row--)
    {
        cout<<endl<<endl;
        for(int column = 0 ; column < 7 ; column++)
        {
            if(matchArray[row][column] == 1)
                cout<<blue<<"O"<<reset;
            else if(matchArray[row][column] == 2)
                cout<<red<<"O"<<reset;
            else
                cout<<"O";

            cout<<"       ";
        }
    }
    cout<<yellow<<"\n\n1       2       3       4       5       6       7"<<reset; 
}

bool player_move(int (&matchArray)[6][7] , int playerMove , bool playerTurn)
{
    //this number can be 1 or 2 based on playerturn
    int number;
    if(playerTurn) number = 1;
    else number = 2;
    
    for(int row = 0 ; row < 6 ; row++)
    {
        if(matchArray[row][playerMove] == 0)
        {
            matchArray[row][playerMove] = number ;
            return true;
        }
    }
    return false ;
}

bool match_array_is_full(int (&matchArray)[6][7]) 
{
    for(int row = 0 ; row < 6 ; row++)
    {
        for(int column = 0 ; column < 7 ; column++)
        {
            if(matchArray[row][column] ==0 )
                return false;
        }
    }
    return true;
}

int check_match_array(int (&matchArray)[6][7])
{
    int counter = 0 ,memory = 0;
    for(int column = 0 ; column < 7 ; column++) //this for loop will check game array in columns so if there is 4 pieces of a kind near eachother
    {
        counter = 0;
        for(int row = 0 ; row < 5 ; row++)
        {
            memory = matchArray[row][column];
            if(memory == matchArray[row+1][column] && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }

    for(int row = 0 ; row < 6 ; row++)//this for loop will check game array in rows so if there is 4 pieces of a kind near eachother
    {
        counter = 0 ;
        for(int column = 0 ; column < 6 ; column++)
        {
            memory = matchArray[row][column];
            if(matchArray[row][column+1]==memory && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }

    for(int column = 1 ; column < 4 ; column++)
    {
        counter = 0;
        for(int row = 0 ; row < 7 - column ; row++)
        {
            memory = matchArray[row][column+row];
            if(matchArray[row+1][column+row+1]==memory && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }
    for(int row = 0 ; row < 3 ; row++)
    {
        counter = 0;
        for(int column = 0 ; column < 6 - row ; column++)
        {
            memory = matchArray[row+column][column];
            if(matchArray[row+column+1][column+1]==memory && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }

    for(int column = 3 ; column < 6 ; column++)
    {
        counter = 0;
        for(int row = 0 ; row < column + 1 ; row++)
        {
            memory = matchArray[row][column-row];
            if(matchArray[row+1][column-row-1]==memory && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }
    for(int row = 0 ; row < 3 ; row++)
    {
        counter = 0 ;
        for(int column = 6 ; column > row ; column--)
        {
            memory = matchArray[row+(6-column)][column];
            if(matchArray[row+(6-column)+1][column-1]==memory && memory != 0)
                counter++;
            else
                counter = 0;

            if(counter == 3)
                return memory;
        }
    }

    //if we are here means that ther was no 4 pieces of a kind near eachother , so no one wins the game yet
    return 0;
}

int start_match(string playerOne , string playerTwo) 
{
    int matchArray[6][7];
    for(int row = 0 ; row < 6 ; row++)
        for(int column = 0 ; column < 7 ; column++)
            matchArray[row][column] = 0 ;

    //this variable show whose turn is it , if its true mean its first player turn to play and if its false means that its second player turn
    bool playerTurn = true ;
    char playerMove ;
    int winnerOfGame ;
    while(true){

        system("cls");
        cout<<"quik match\n\n";
        cout << "player one : " << blue << playerOne << reset <<endl<<endl ;
        cout << "player two : " << red << playerTwo << reset <<endl ;

        show_match_array(matchArray);

        cout<<endl<<endl<< "its ";
        if(playerTurn)
        cout<<blue<<playerOne<<reset;
        else
            cout<<red<<playerTwo<<reset;
        cout<<"'s turn, please enter a number between 1 and 7 : ";

        while(true)
        {
            playerMove = get_char();
            if(validation(playerMove,1))
            {
                if(player_move(matchArray , playerMove-49 , playerTurn))
                    break;
                else
                    error(2);
            }
            else
                error(1);
        }

        //if its 0 means no one winns the game yet , if its 1 means first player wins and if its 2 means second player win
        winnerOfGame = check_match_array(matchArray);
        if(winnerOfGame == 0)
        {
            if(match_array_is_full(matchArray))
                return 0;
        }
        else if(winnerOfGame == 1)
            break ;
        else if(winnerOfGame == 2)
            break ;
        else
        {
            error(-1);
            return -1;
        }
        //switch player turn
        playerTurn = !playerTurn;
    }

    system("cls");
    show_match_array(matchArray);
    if(winnerOfGame == 1) return 1;
    else return 2;

}
void show_winner(string firstPlayerName , string secondPlayerName , int winnerOfTheGame)
{
    if(winnerOfTheGame == 0)
        cout<<endl<<endl<<yellow<<"game have no winner ! "<<reset;
    else if(winnerOfTheGame == 1)
        cout<<endl<<endl<<"winner of the game is "<<blue<<firstPlayerName<<reset<<" !";
    else if(winnerOfTheGame == 2)
        cout<<endl<<endl<<"winner of the game is "<<red<<secondPlayerName<<reset<<" !";
    else error(-1);
    cout<<endl<<green<<"enter a character to continue : "<<reset;
    get_char();
    return ;
}

void quick_match()
{
    system("cls");
    string firstPlayerName , secondPlayerName ;
    cout <<"Please enter first player's name : ";
    cin>>firstPlayerName;
    cout<<"Please enter second player's name : ";
    cin>>secondPlayerName;

    //if winnerOfTheGame become true means first player won the game and if winnerOfTheGame become false means second player won the game
    int winnerOfTheGame = start_match(firstPlayerName , secondPlayerName);
    show_winner(firstPlayerName , secondPlayerName , winnerOfTheGame);
    return;
}
void show_league(string players[] ,int playersStatus[][2] , int numberOfPlayers)
{
    string temp;
    system("cls");
    cout<<endl;
    for(int i = 0  ; i < numberOfPlayers ; i++)
    {
        temp = players[playersStatus[i][0]];
        cout<<temp<<"\t\t"<<(playersStatus[i][1]>=1 ? temp : "")<<"\t\t"<<(playersStatus[i][1]>=2 ? temp : "")<<"\t\t"<<(playersStatus[i][1]>=3 ? temp : "");
        cout<<endl;
        if(i%2==1)cout<<endl;
    }
    cout<<endl<<green<<"enter a character to continue : "<<reset;
    get_char();
    return ;
    return;
}

int start_league(string players[] , int numberOfPlayers)
{
    srand(time(0));
    int temp ,counter , winnerOfMatch;
    bool unique ;
    //playersStatus[numberOfPlayers][1] will contain players index and playersStatus[numberOfPlayers][1] will contain players status in league
    int playersStatus[numberOfPlayers][2];

    for(int i = 0 ; i < numberOfPlayers ; i++)
    {
        playersStatus[i][0] = -1 ;
        playersStatus[i][1] = 0 ;
    }

    //lets make a random list of players so we can have random matches between them
    for(int i = 0 ; i < numberOfPlayers ; i++)
    {
        while(true)
        {
            unique = true;
            temp = (rand() % (numberOfPlayers));
            for(int j = 0 ; j < numberOfPlayers ; j++)
            {
                if( playersStatus[j][0] == temp )
                    unique = false;
            }
            if(unique)
            {
                playersStatus[i][0] = temp;
                break;
            }
        }
    }
    show_league(players , playersStatus , numberOfPlayers);

    //lets start first round of league
    for(int i = 0 ; i < numberOfPlayers-1 ; i+=2)
    {
        counter = 0 ;
        while(true)
        {
            winnerOfMatch = start_match(players[playersStatus[i][0]] ,players[playersStatus[i+1][0]]);
            if(winnerOfMatch == 1)
                break;
            else if(winnerOfMatch == 2)
                break;
            else if(winnerOfMatch == 0)
            {
                counter++;
                show_winner( players[playersStatus[i][0]] , players[playersStatus[i+1][0]] , winnerOfMatch );
            }
            else
                error(-1);
            if(counter == 3)
                break;
        }
        if(winnerOfMatch == 0)
            winnerOfMatch = (rand() % (2) + 1);
        if(winnerOfMatch == 2)
            playersStatus[i+1][1] = 1 ;
        else if(winnerOfMatch == 1)
             playersStatus[i][1] = 1 ;
        else error(-1);

        show_winner( players[playersStatus[i][0]] , players[playersStatus[i+1][0]] , winnerOfMatch );
        show_league(players , playersStatus , numberOfPlayers);
    }

    //esterahate bazikon
    if(numberOfPlayers % 2 == 1)
    {
        playersStatus[numberOfPlayers-1][1] = 1;
        show_league(players , playersStatus , numberOfPlayers);

    }

    //lets be ready for the second round , we have to make an array of second round players
    int secondRoundPlayersNumber = (numberOfPlayers+1)/2 ;
    int secondRoundPlayers[secondRoundPlayersNumber];
    counter = 0;
    for(int i = 0 ; i < numberOfPlayers ; i++)
    {
        if(playersStatus[i][1]==1)
        {
            secondRoundPlayers[counter] = playersStatus[i][0];
            counter++;
        }
    }
    counter = 0;

    //lets start second round of league
    for(int i = secondRoundPlayersNumber-1 ; i > 0 ; i-=2)
    {
        counter = 0;
        while(true)
        {
            winnerOfMatch = start_match(players[secondRoundPlayers[i]] , players[secondRoundPlayers[i-1]]);
            if(winnerOfMatch == 1)
                break;
            else if(winnerOfMatch == 2)
                break;
            else if(winnerOfMatch == 0)
            {
                counter++;
                show_winner( players[secondRoundPlayers[i]] , players[secondRoundPlayers[i-1]], winnerOfMatch );
            }
            else
                error(-1);
            if(counter == 3)
                break;
        }
        if(winnerOfMatch == 0)
            winnerOfMatch = (rand() % (2) + 1);

        if(winnerOfMatch == 1)
        {
            for(int j = 0 ; j < numberOfPlayers ; j++)
            {
                if(playersStatus[j][0]==secondRoundPlayers[i])
                    playersStatus[j][1]=2;
            }
        }
        else if(winnerOfMatch == 2)
        {
            for(int k = 0 ; k < numberOfPlayers ; k++)
            {
                if(playersStatus[k][0]==secondRoundPlayers[i-1])
                    playersStatus[k][1]=2;
            }
        }
        else error(-1);

        show_winner( players[secondRoundPlayers[i]] , players[secondRoundPlayers[i-1]] , winnerOfMatch );
        show_league(players , playersStatus , numberOfPlayers);

    }


    //esterahat bazikon
    if(numberOfPlayers == 5 || numberOfPlayers == 6)
    {
        for(int i = 0 ; i < numberOfPlayers ; i++)
        {
            if(playersStatus[i][0]==secondRoundPlayers[0])
                playersStatus[i][1]=2;
        }
        show_league(players , playersStatus , numberOfPlayers);

    }

    if(numberOfPlayers < 5)
    {
        for(int i = 0 ; i < numberOfPlayers ; i++)
        {
            if(playersStatus[i][1]==2)return playersStatus[i][0];
        }
    }

    //lets be ready for the third round , we have to make an array of third round players
    int thirdRoundPlayersNumber = 2;
    int thirdRoundPlayers[thirdRoundPlayersNumber];
    counter = 0;
    for(int i = 0 ; i < numberOfPlayers ; i++)
    {
        if(playersStatus[i][1]==2)
        {
            thirdRoundPlayers[counter] = playersStatus[i][0];
            counter++;
        }
    }

    //lets start third round of league
    counter = 0;
    while(true)
    {
        winnerOfMatch = start_match(players[thirdRoundPlayers[0]] , players[thirdRoundPlayers[1]]);
        if(winnerOfMatch == 1)
            break;
        else if(winnerOfMatch == 2)
            break;
        else if(winnerOfMatch == 0)
        {
            counter++;
            show_winner(players[thirdRoundPlayers[0]] , players[thirdRoundPlayers[1]], winnerOfMatch );
        }
        else
            error(-1);
        if(counter == 3)
            break;
    }
    if(winnerOfMatch == 0)
        winnerOfMatch = (rand() % (2) + 1);
    if(winnerOfMatch == 2)
        playersStatus[thirdRoundPlayers[1]][1] = 3 ;
    else if(winnerOfMatch == 1)
            playersStatus[thirdRoundPlayers[0]][1] = 3 ;
    else error(-1);

    show_winner( players[thirdRoundPlayers[0]] , players[thirdRoundPlayers[1]] , winnerOfMatch );
    show_league(players , playersStatus , numberOfPlayers);

    for(int i = 0 ; i < numberOfPlayers ; i++)
        {
            if(playersStatus[i][1]==3)return playersStatus[i][0];
        }

    return -1;
}

void league()
{
    system("cls");

    //lets get number of players in the league
    char numberOfPlayersCHAR ;
    int numberOfPlayers ;
    cout<<"\nplease enter number of players : ";
    while(true)
    {
        numberOfPlayersCHAR = get_char();
        if(validation(numberOfPlayersCHAR , 2))
            break;
        else
            error(3);
    }
    numberOfPlayers = numberOfPlayersCHAR - 48 ;
    string players[numberOfPlayers];
   system("cls");

    //lets get all players name in this for loop
    for(int i = 0 ; i < numberOfPlayers ; i++)
    {
        cout<<"\n please enter player "<<i+1<<" name : ";
        cin>>players[i];
    }
    //define an array in size of players so we can store their name in it
    int winnerOfTheLeague = start_league(players , numberOfPlayers);
    if(winnerOfTheLeague == -1)
    {
        error(-1);
        cout<<green<<"\n\nplease enter a character to continue : "<<reset;
        get_char();
        return;
    }
    system("cls");
    cout<<"----------------------------------------------\n";
    cout<<green<<"WINNER OF THE LEAGUE IS : ";
    cout<<yellow<<players[winnerOfTheLeague];
    cout<<"\n----------------------------------------------";
    cout<<green<<"\n\nplease enter a character to continue : "<<reset;
    get_char();
    return;
}
char menu() //starting menu of the game
{
    system("cls");

    cout<<"\nlets play : \n";
    cout<<"\n1. quick match\n2. league\n3 . exit\n\nplz choose one option : ";
    return get_char();
}

int main()
{	
    while(true)
    {
        switch(menu())
            {
                case '1': quick_match();break;
                case '2': league();break;
                case '3': return 0;
                default : error(0);return 0;
            }
    }
    cout<<endl;
    return 0;
}

