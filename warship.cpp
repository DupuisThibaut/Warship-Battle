

class Ship {
    int length;
    bool isVertical;
    int posX;
    int posY;

    Ship(int length,bool isVertical,int posX,int posY){
        if(isVertical){
            if(length+posY >10 || posY<1){
                 cout << "Please select valid location." << endl;
                 return 1;
            }
        }
        else{
            if(length+posX >10 || posX<1){
                 cout << "Please select valid location." << endl;
                 return 1;
        }
            this.length = length;
            this.isVertical = isVertical;
            this.posX = posX;
            this.posY = posY;
        }
    }
}

class Grille{
    std::array<std::array<int,10>, 10> Cases; 
}

int main(){

    return 0;
}