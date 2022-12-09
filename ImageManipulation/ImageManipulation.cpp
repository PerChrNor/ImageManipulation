#include <iostream>
#include <fstream>
#include <sstream>



int main()
{
    std::ofstream newimage;
    std::ifstream image;

    image.open("apollo.ppm");
    newimage.open("newimage.ppm");


    std::string type = "", width = "", height = "", RGB = "";

    image >> type;
    image >> width;
    image >> height;
    image >> RGB;

    newimage << type << std::endl;
    newimage << width << " " << height << std::endl;
    newimage << RGB << std::endl;

    std::string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;

    std::stringstream widthstream(width);
    int widthValue;
    widthstream >> widthValue;
    std::stringstream heightstream(height);
    int heightValue;
    heightstream >> heightValue;
    int TotalPixels = widthValue * heightValue;
    int PixelNr = 0;

    std::cout << TotalPixels << " Pixels" << std::endl;
    std::cout << "SELECT FILTER:" << std::endl;
    std::cout << "Normal" << ", " << "Grayscale" << ", " << "Red-shade" << ", " << "Green-shade" << ", " << "Blue-shade" << ", " << "Border" << std::endl;

    std::string choice = "";
    std::cin >> choice;

    enum Filters
    {
        Normal, Grayscale, RedShade, GreenShade, BlueShade, Border, Other
    };

    int choiceNr = 0;

    if (choice == "Normal" || choice == "normal")
    {
        choiceNr = Normal;
    };

    if (choice == "Grayscale" || choice == "grayscale")
    {
        choiceNr = Grayscale;
    };
    
    if (choice == "Red-shade" || choice == "red-shade" || choice == "Red-Shade" || choice == "red-Shade")
    {
        choiceNr = RedShade;
    };

    if (choice == "Green-shade" || choice == "green-shade" || choice == "Green-Shade" || choice == "green-Shade")
    {
        choiceNr = GreenShade;
    };

    if (choice == "Blue-shade" || choice == "blue-shade" || choice == "Blue-Shade" || choice == "blue-Shade")
    {
        choiceNr = BlueShade;
    };

    if (choice == "Border")
    {
        choiceNr = Border;
    };
    
    std::cout << "Starting" << std::endl;

    while (!image.eof()) {

        image >> red;
        image >> green;
        image >> blue;

        std::stringstream redstream(red);
        std::stringstream greenstream(green);
        std::stringstream bluestream(blue);

        redstream >> r;
        greenstream >> g;
        bluestream >> b;
        
        if (PixelNr == TotalPixels * 0.25) {
            std::cout << "25%" << std::endl;
        }
        if (PixelNr == TotalPixels * 0.5) {
            std::cout << "50%" << std::endl;
        }
        if (PixelNr == TotalPixels * 0.75) {
            std::cout << "75%" << std::endl;
        }
        if (PixelNr == TotalPixels) {
            std::cout << "100%" << std::endl;
        }

        switch (choiceNr)
        {
        case Grayscale:
            if (r > g && r > b) {
                g = r;
                b = r;
            }
            else if (g > r && g > b) {
                r = g;
                b = g;
            }
            else if (b > r && b > g) {
                r = b;
                g = b;
            }
            break;

        case RedShade:
            if (r + 50 >= 255) {
                r = 255;
            }
            else {
                r += 50;
            }
            break;

        case GreenShade:
            if (g + 50 >= 255) {
                g = 255;
            }
            else {
                g += 50;
            }
            break;

        case BlueShade:
            if (b + 50 >= 255) {
                b = 255;
            }
            else {
                b += 50;
            }
            break;

        case Border:
            if (PixelNr < 10000) {
                r = 0;
                g = 0;
                b = 255;
            }
            else if (TotalPixels - 10000 < PixelNr) {
                r = 0;
                g = 0;
                b = 255;
            }
            
            break;
        default:
            break;
        }
        
        PixelNr++;
        newimage << r << " " << g << " " << b << std::endl;
    }
    std::cout << "Done!" << std::endl;
    image.close();
    newimage.close();

    return 0;
}

