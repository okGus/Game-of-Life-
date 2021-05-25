#include <SFML/Graphics.hpp>
#include <vector>
#include <experimental/random>
#include <iostream>
#include <unistd.h>
#include <iomanip>

using type = std::vector<std::vector<int>>;
type makeGrid(int col, int row);
int setup();
void display(type &v);
void test();

int main()
{
    //test();

    return setup();
}

type makeGrid(int col, int row)
{
    type matrix(col, std::vector<int>(row));
    return matrix;
}

void display(type &v)
{
    for (int r{0}; r < v.size(); r++)
    {
        for (int c{0}; c < v[r].size(); c++)
        {
            std::cout << v[r][c] << " ";
        }
        std::cout << "\n";
    }
}

int setup()
{
    int res{28};
    int col{20};                         //{window_width / res};
    int row{20};                         //{window_height / res};
    int window_width = col * (res + 2);  //sf::VideoMode::getDesktopMode().width;
    int window_height = row * (res + 2); //sf::VideoMode::getDesktopMode().height;
    auto grid = makeGrid(row, col);      //2d vector;

    // randomize each index
    for (int r{0}; r < grid.size(); r++)
    {
        for (int c{0}; c < grid[r].size(); c++)
        {
            grid[r][c] = std::experimental::randint(0, 1);
        }
    }
    // test Beacon (period 2)
    // grid[1][1] = 1;
    // grid[2][2] = 1;
    // grid[2][1] = 1;
    // grid[1][2] = 1;
    // grid[3][3] = 1;
    // grid[4][4] = 1;
    // grid[4][3] = 1;
    // grid[3][4] = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Game of Life C++");
    //sf::RectangleShape square(sf::Vector2f(res, res));

    // console output
    // for (const auto i : grid)
    // {
    //     for (const auto e : i)
    //     {
    //         std::cout << e << " ";
    //     }
    //     std::cout << '\n';
    // }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // start rendering to window
        window.clear(sf::Color(132, 132, 132, 255));

        // draw squares
        for (int r{0}; r < grid.size(); r++)
        {
            for (int c{0}; c < grid[r].size(); c++)
            {
                std::cout << grid[r][c] << " ";
                if (grid[r][c] == 1)
                {
                    int x{r * (res + 2)};
                    int y{c * (res + 2)};
                    sf::RectangleShape square(sf::Vector2f(res, res));
                    square.setFillColor(sf::Color::White);
                    square.setPosition(x + 2, y + 2);
                    window.draw(square);
                }
                if (grid[r][c] == 0)
                {
                    int x{r * (res + 2)};
                    int y{c * (res + 2)};
                    sf::RectangleShape square(sf::Vector2f(res, res));
                    square.setFillColor(sf::Color::Black);
                    square.setPosition(x + 2, y + 2);
                    window.draw(square);
                }
            }
            std::cout << "\n";
        }

        std::cout << std::setfill('-') << std::setw(grid[0].size() * 2) << '\n';

        // end current frame and display
        window.display();

        // game of life rules
        auto next = makeGrid(row, col);
        int sum{};
        for (int r{0}; r < grid.size(); r++)
        {
            for (int c{0}; c < grid[r].size(); c++)
            {
                int state = grid[r][c];

                if (r - 1 >= 0)
                { // above
                    if (grid[r - 1][c] == 1)
                        sum++;
                }
                if (r + 1 < grid.size())
                { // below
                    if (grid[r + 1][c] == 1)
                        sum++;
                }
                if (c - 1 >= 0)
                { // left
                    if (grid[r][c - 1] == 1)
                        sum++;
                }
                if (c + 1 < grid[r].size())
                { // right
                    if (grid[r][c + 1] == 1)
                        sum++;
                }
                if (r - 1 >= 0 && c - 1 >= 0)
                { // top left
                    if (grid[r - 1][c - 1] == 1)
                        sum++;
                }
                if (r - 1 >= 0 && c + 1 < grid[r].size())
                { // top right
                    if (grid[r - 1][c + 1] == 1)
                        sum++;
                }
                if (r + 1 < grid.size() && c - 1 >= 0)
                { // bottom left
                    if (grid[r + 1][c - 1] == 1)
                        sum++;
                }
                if (r + 1 < grid.size() && c + 1 < grid[r].size())
                { // bottom right
                    if (grid[r + 1][c + 1] == 1)
                        sum++;
                }

                if (sum < 2 || sum > 3)
                {
                    next[r][c] = 0;
                }
                else if (state == 0 && sum == 3)
                {
                    next[r][c] = 1;
                }
                else
                {
                    next[r][c] = state;
                }

                sum = 0;
            }
        }

        grid = next;

        sf::Time delay = sf::seconds(1.0f);
        sf::sleep(delay);
    }

    return EXIT_SUCCESS;
}

void test()
{
    auto vec = makeGrid(20, 20);

    for (int r{0}; r < vec.size(); r++)
    {
        for (int c{0}; c < vec[r].size(); c++)
        {
            vec[r][c] = std::experimental::randint(0, 1);
        }
    }

    display(vec);
    int sum{};
    for (int r{0}; r < vec.size(); r++)
    {
        for (int c{0}; c < vec[r].size(); c++)
        {
            if (r - 1 >= 0)
            { // above
                if (vec[r - 1][c] == 1)
                    sum++;
            }
            if (r + 1 < vec.size())
            { // below
                if (vec[r + 1][c] == 1)
                    sum++;
            }
            if (c - 1 >= 0)
            { // left
                if (vec[r][c - 1] == 1)
                    sum++;
            }
            if (c + 1 < vec[r].size())
            { // right
                if (vec[r][c + 1] == 1)
                    sum++;
            }
            if (r - 1 >= 0 && c - 1 >= 0)
            { // top left
                if (vec[r - 1][c - 1] == 1)
                    sum++;
            }
            if (r - 1 >= 0 && c + 1 < vec[r].size())
            { // top right
                if (vec[r - 1][c + 1] == 1)
                    sum++;
            }
            if (r + 1 < vec.size() && c - 1 >= 0)
            { // bottom left
                if (vec[r + 1][c - 1] == 1)
                    sum++;
            }
            if (r + 1 < vec.size() && c + 1 < vec[r].size())
            { // bottom right
                if (vec[r + 1][c + 1] == 1)
                    sum++;
            }

            if (sum == 0)
                vec[r][c] = 0;
            if (sum == 1)
                vec[r][c] = 0;

            sum = 0;

            system("clear");
            display(vec);
            usleep(10000);
        }
    }
}
