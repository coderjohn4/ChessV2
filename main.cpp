// -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <tuple>
#include <iostream>
#include <fstream>
using namespace std;


class Piece
{
    public:
        std::string type, color;

        void drawPiece(int squareX, int squareY)
        {
            sf::Sprite spriteNew;
            spriteNew.setTexture(*textureptr);
            int cutX = 0;
            int cutY = 0;

            if(type == "rook"  ) cutX = 4;
            if(type == "knight") cutX = 3;
            if(type == "bishop") cutX = 2;
            if(type == "king"  ) cutX = 0;
            if(type == "queen" ) cutX = 1;
            if(type == "pawn"  ) cutX = 5;

            if(color == "white") cutY = 0;
            if(color == "black") cutY = 1;

            spriteNew.setTextureRect(sf::IntRect(spriteWidth*cutX, spriteHeight*cutY, spriteWidth, spriteHeight));            
            spriteNew.setPosition(sf::Vector2f(16+chessSquareWidth*squareX,6+chessSquareHeight*squareY));
            spriteNew.setScale(0.2f, 0.2f);
            windowptr->draw(spriteNew); 
        };

        
        Piece(sf::RenderWindow* window, sf::Texture* texture,  std::string p_color, std::string p_type)
        {    
            windowptr  = window;
            type       = p_type;
            color      = p_color;
            textureptr = texture;
        }

    private:

        sf::RenderWindow* windowptr;
        sf::Texture* textureptr;

        float spriteWidth       = 1280/6;
        float spriteHeight      = 427/2;
        float chessSquareWidth  = (352-16)/7; 
        float chessSquareHeight = (338-6)/7;
};



void writeStateToFile(string filename, Piece* p_chessboard[8][8])
{
    ofstream MyFile(filename);

        for(int y=0; y<8; y++)
        {
            for(int x = 0; x < 8; x++)
            {
                MyFile << x <<" "<<y<<" ";                    
   
                if(p_chessboard[x][y] != nullptr)
                {
                    MyFile << p_chessboard[x][y]->type<<" ";
                    MyFile << p_chessboard[x][y]->color<<endl;
                    // cout << p_chessboard[x][y]->type;
                    // chessboard[x][y]->drawPiece(x,y);    
                }
                else 
                {
                    MyFile <<"EMPTY"<<endl;
                    cout<<"EMPTY"<<endl;
                }

            }
        }
    MyFile.close();    
}

vector<string> split (string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) 
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void readStateToArray(string filename, Piece* p_chessboard[8][8],sf::RenderWindow* window, sf::Texture* texture)
{
    string color;
    string type;
    string squareLineText;
    vector<string> tokenLine;
    ifstream MyReadFile(filename);

    bool readStatus;

    while(getline(MyReadFile,squareLineText))
    {
        tokenLine = split(squareLineText, " ");
        cout<<tokenLine.size()<<" ";
        cout<<squareLineText<<endl;
        int x = stoi(tokenLine[0]);
        int y = stoi(tokenLine[1]);

        if(tokenLine.size() == 4)
        {   
            for(int i = 0; i < tokenLine.size(); i++) cout<<tokenLine[i]<<endl;           
            Piece* piece = new Piece(window, texture, tokenLine[3], tokenLine[2]);
            // Piece(sf::RenderWindow* window, sf::Texture* texture,  std::string p_color, std::string p_type)
            p_chessboard[x][y] = piece;
        }
        else
        {
            cout<<"Empty"<< endl;
            p_chessboard[x][y] = nullptr;
        }
    }   

    MyReadFile.close();

}


int main()
{
    // writeFile("Goblins_Hideout.txt", "In the northern village, the goblins lived in a civil war");

    sf::RenderWindow window(sf::VideoMode(400, 400), "Chess");
    sf::Vector2i windowPos(550,100);
    window.setPosition(windowPos);
    
    sf::Texture chessTexture;
    chessTexture.setSmooth(true);

    if (!chessTexture.loadFromFile("spritesheet.png")) 
    {
        std::cout << "[ERROR]" << endl;
        return 1;
    }

    Piece* chessboard[8][8] = {nullptr};


    // chessboard[0][0] = new Piece(&window, &chessTexture, "white","rook");
    // chessboard[1][0] = new Piece(&window, &chessTexture, "white","knight");
    // chessboard[2][0] = new Piece(&window, &chessTexture, "white","bishop");
    // chessboard[3][0] = new Piece(&window, &chessTexture, "white","king");
    // chessboard[4][0] = new Piece(&window, &chessTexture, "white","queen");
    // chessboard[5][0] = new Piece(&window, &chessTexture, "white","bishop");
    // chessboard[6][0] = new Piece(&window, &chessTexture, "white","knight");
    // chessboard[7][0] = new Piece(&window, &chessTexture, "white","rook");
    // for(int i = 0; i < 8; i++) chessboard[i][1] = new Piece(&window, &chessTexture, "white","pawn");

    // chessboard[0][7] = new Piece(&window, &chessTexture, "black","rook");
    // chessboard[1][7] = new Piece(&window, &chessTexture, "black","knight");
    // chessboard[2][7] = new Piece(&window, &chessTexture, "black","bishop");
    // chessboard[3][7] = new Piece(&window, &chessTexture, "black","king");
    // chessboard[4][7] = new Piece(&window, &chessTexture, "black","queen");
    // chessboard[5][7] = new Piece(&window, &chessTexture, "black","bishop");
    // chessboard[6][7] = new Piece(&window, &chessTexture, "black","knight");
    // chessboard[7][7] = new Piece(&window, &chessTexture, "black","rook");
    // for(int i = 0; i < 8; i++) chessboard[i][6] = new Piece(&window, &chessTexture, "black","pawn");
    // cout << chessboard[0][0]->color << chessboard[0][0]->type << endl;
    
    // writeStateToFile("chess.txt", chessboard);
    readStateToArray("chess.txt", chessboard, &window, &chessTexture);

    sf::Texture texture;
    if (!texture.loadFromFile("chessboard.png")) std::cout << "[ERROR]" << endl;
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while(window.isOpen())
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // if(chessboard){
                //     movePiece();
                // }
            }
        }

        window.clear();
        window.draw(sprite);

        for(int y=0; y<8; y++)
        {
            for(int x = 0; x < 8; x++)
            {   
                if(chessboard[x][y] != nullptr){
                    chessboard[x][y]->drawPiece(x,y);        
                }
            }
        }

        window.display();
    }

    return 0;

};



//cant make it so it goes over 7/7.
//use numbers only check. 
//take out null pointers.
//only be fixed strings(bishop, king, queen, pawn).
//only be white or black.
//check for not too many pieces.
//enum state checking, each piece a number.
//SVG file parsing to redraw image.