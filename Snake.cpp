#include <conio.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#define m *1000000

// for supporting the other classes
class supportx
{
public:
    // for checking if number n is present in array arr
    bool check_array(int arr[], unsigned int size, int n)
    {
        // unsigned int size = sizeof(arr) / sizeof(arr[0]);
        for (unsigned int i = 0; i < size; i++)
        {
            if (arr[i] == n)
                return false;
        }
        return true;
    }

    // for giving space
    void space(unsigned int spac = 40)
    {
        for (unsigned int i = 0; i < spac; i++)
            cout << " ";
    }

    // for giving line space
    void line_space(unsigned int spac = 5)
    {
        for (unsigned int i = 0; i < spac; i++)
            cout << endl;
    }
    
    // for checking if all element of the bool array are true
    bool check(bool arr[], unsigned int size)
    {
        // unsigned int size = sizeof(arr) / sizeof(arr[0]);
        for (unsigned int i = 0; i < size; i++)
        {
            if (arr[i] == 0)
                return false;
        }
        return true;
    }

    // sorting the array 'arr'
    void bubble_sort(int arr[], unsigned int size)
    {
        // unsigned int size=sizeof(arr)/sizeof(arr[0]);
        for (unsigned int i = 0; i < size - 1; i++)
        {
            for (unsigned int j = 0; j < size; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
};

class snake
{
    unsigned int horizontal_length, vertical_length; // maximum horizontal and vertical length
    unsigned int snake_size;                         // size of the snake
    unsigned int snake_head_position;                // position of snake head
    int gravity;                                     // for defining which side does snake goes
    // for gravity 1 is up, 2 is left, 3 is right and 4 is down
    bool mode; // for defining the background to show or not
    // float speed; // for defining the speed of the snake

    // for giving the background of the game default size of y is (this is the function that really prints the game . Other function of direction are just making changes in the array)
    //arr (the array that stores the positions of the elements in the game)
    //background_show (mode to see the numbers in the game or like a snake game) (0 for snake game,1 for numbers int the game space is not shown 0 but blank)
    void background(unsigned int arr[], bool background_show = 0, char snake_skin = '*', char snake_head = '*', string space_skin = " ", char horizontal_border = '#', char vertical_border = '|')
    {
        // for the upper border line of the game
        for (unsigned int i = 0; i < horizontal_length + 2; i++)
            cout << horizontal_border;
        cout << endl;

        // output information of game from the array (j in y-axis)
        for (unsigned int j = 0; j < vertical_length; j++)
        {
            // for the left border of the background
            cout << vertical_border;

            // for the game background (i in x-axis)
            for (unsigned int i = 0; i < horizontal_length; i++)
            {
                if (background_show == 0)
                {
                    if (arr[j * horizontal_length + i] == 1)
                        cout << snake_head;
                    else if (arr[j * horizontal_length + i] != 0)
                        cout << snake_skin;
                    else
                        cout << space_skin;
                }
                else
                {
                    if (arr[j * horizontal_length + i] == 0)
                        cout << space_skin;
                    else
                        cout << arr[j * horizontal_length + i] % 10;
                }
            }

            // for the right border of the game
            cout << vertical_border << endl;
        }
        // for the bottom border line of the game
        for (unsigned int i = 0; i < horizontal_length + 2; i++)
            cout << horizontal_border;
        cout << endl;
    }

    // for giving the snake array vertical movement in up side
    bool up_vertical_movement(unsigned int arr[])
    {
        if (gravity == 4)
        {
            cout << "\nNot possible to go in this particular direction.\n";
            return 0;
        }

        gravity = 1;
        for (unsigned int j = 0; j < vertical_length; j++)
        {
            for (unsigned int i = 0; i < horizontal_length; i++)
            {
                unsigned int index = j * horizontal_length + i;
                if (arr[index] == snake_size)
                    arr[index] = 0;
                else if (arr[index] == 1)
                {
                    if (j == 0)
                    {
                        arr[index] = 2;
                        snake_head_position = (vertical_length - 1) * horizontal_length + i; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                    else
                    {
                        arr[index] = 2;
                        snake_head_position = index - horizontal_length; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                }
                else if (arr[index] != 0) // body
                    arr[index]++;
            }
        }
        return 1;
    }

    // for giving the snake array horizontal movement in left side
    bool left_horizontal_movement(unsigned int arr[])
    {
        if (gravity == 3)
        {
            cout << "\nNot possible to go in this particular direction.\n";
            return 0;
        }

        gravity = 2;
        for (unsigned int j = 0; j < vertical_length; j++)
        {
            for (unsigned int i = 0; i < horizontal_length; i++)
            {
                unsigned int index = j * horizontal_length + i;
                // tail
                if (arr[index] == snake_size)
                    arr[index] = 0;
                else if (arr[index] == 1) // head
                {
                    if (i == 0)
                    {
                        arr[index] = 2;
                        snake_head_position = index + horizontal_length - 1; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                    else
                    {
                        arr[index] = 2;
                        snake_head_position = index - 1; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                }
                else if (arr[index] != 0) // body
                    arr[index]++;
            }
        }
        return 1;
    }

    // for giving the snake array horizontal movement in right side
    bool right_horizontal_movement(unsigned int arr[])
    {
        if (gravity == 2)
        {
            cout << "\nNot possible to go in this particular direction.\n";
            return 0;
        }

        gravity = 3;
        for (unsigned int j = 0; j < vertical_length; j++)
        {
            for (unsigned int i = 0; i < horizontal_length; i++)
            {
                unsigned int index = j * horizontal_length + i;

                // for the tail
                if (arr[index] == snake_size)
                    arr[index] = 0;
                else if (arr[index] == 1) // for the head
                {
                    if (i == horizontal_length - 1)
                    {
                        arr[index] = 2;
                        snake_head_position = index - horizontal_length + 1; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                    else
                    {
                        arr[index] = 2;
                        snake_head_position = index + 1; // snake head position change
                        arr[snake_head_position] = 1;
                        i++; // because this index is already 1
                    }
                }
                else if (arr[index] != 0) // the body other than head or tail
                    arr[index]++;
            }
        }
        return 1;
    }

    // for giving the snake array vertical movement in down side
    bool down_vertical_movement(unsigned int arr[])
    {
        if (gravity == 1)
        {
            cout << "\nNot possible to go in this particular direction.\n";
            return 0;
        }

        gravity = 4;
        bool one = 0; // variable to keep in check that one gets changed only once
        for (unsigned int j = 0; j < vertical_length; j++)
        {
            for (unsigned int i = 0; i < horizontal_length; i++)
            {
                unsigned int index = j * horizontal_length + i;
                if (arr[index] == snake_size)
                    arr[index] = 0;
                else if (arr[index] == 1)
                {
                    if (j == vertical_length - 1)
                    {
                        arr[index] = 2;
                        snake_head_position = i; // snake head position change
                        arr[snake_head_position] = 1;
                    }
                    else if (one == 0)
                    {
                        arr[index] = 2;
                        snake_head_position = index + horizontal_length; // snake head position change
                        arr[snake_head_position] = 1;
                        one = 1; // blocking from again entering this fuction
                    }
                }
                else if (arr[index] != 0) // body
                    arr[index]++;
            }
        }
        return 1;
    }

    // for checking if the snake bit itself
    bool check_game(unsigned int arr[])
    {
    }

    // for setting the starting position of the snake
    void starting_position(unsigned int arr[])
    {
        int index = snake_head_position;
        int numbering = 1; // for numbering the body of the snake
        for (unsigned int k = 0; k < snake_size; k++)
        {
            arr[index] = numbering++;
            index--;
        }
        background(arr);
    }

    // for setting the movement of the snake in any direction ,any number of times
    void movement(unsigned int arr[], int direction = 3, unsigned int loop_times = 100, float speed = 0.1)
    {
        for (unsigned int i = 0; i < loop_times; i++)
        {
            usleep(speed m);

            if (direction == 3)
                right_horizontal_movement(arr);
            else if (direction == 2)
                left_horizontal_movement(arr);
            else if (direction == 1)
                up_vertical_movement(arr);
            else if (direction == 4)
                down_vertical_movement(arr);
            else
                cout << "\nNo such direction possible.\n";

            system("cls");
            background(arr, mode);
        }
    }

    // for setting the movement of the snake in any direction until condition
    void movement_infinite(unsigned int arr[], float speed = 0.1)
    {
        int w=119,a=97,s=115,d=100;
        int esc=27;//escaping the snake movement
        usleep(speed m);
        int key = w;
        int prev_key=w;
        bool work=1;
        while (key!=esc)
        {
            if (_kbhit())
            {
                prev_key=key;
                key = _getch();
                usleep(speed m);
            }
            
            // up
            if (key == w)
            {
                work = up_vertical_movement(arr);
                if (!work) key=prev_key;
            }

            // left
            if (key == a)
            {
                work =left_horizontal_movement(arr);
                if (!work) key=prev_key;
            }

            // right
            if (key == d)
            {
                work =right_horizontal_movement(arr);
                if (!work) key=prev_key;
            }

            // down
            if (key == s)
            {
                work =down_vertical_movement(arr);
                if (!work) key=prev_key;
            }

            system("cls");
            background(arr, mode);
        }
    }

public:
    //used to make the appropiate initiliazations for the game
    snake(unsigned int x = 100, unsigned int y = 25)
    {
        horizontal_length = x;
        vertical_length = y;
        snake_size = 50;
        mode = 0;
        snake_head_position = (horizontal_length * vertical_length) / 2;
        // speed = 0.25;
    }
    
    //this is the actual movements of the snake
    void start()
    {
        unsigned int input[horizontal_length * vertical_length] = {};

        // stating position
        starting_position(input);

        movement_infinite(input);
    }
    
    //this is the actual game with the control panel
    void game(){
        int key=0;
        int esc=27;
        //options in control panel
        //1.start
        //2.options
        //3.how to play
        //4.quit
        while(key!=4){
            cout<<"press :\n1.start\n2.options\n3.how to play\n4.quit\n";
            cin>>key;
            system("cls");
            
            switch(key){
                //game sequence
                case 1: 
                start();
                system("cls");
                break;
                
                //options
                case 2:
                break;

                //how to play
                case 3:
                break;

            }
        }
    }
};

int main()
{
    snake s;
    s.game();
    return 0;
}