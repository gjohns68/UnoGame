#include "card.h"

Color Card::getColor() const{
    return color;
}

Type Card::getType() const{
    return type;
}
    
int Card::getNumber() const{
    return number;
}

void Card::setColor(Color c){
    color = c;
}

void Card::setNumber(int n){
    number = n;
}

void Card::setType(Type t){
    type = t;
}

NumberCard::NumberCard(Color c, int n, Type t) {
    setColor(c);
    setNumber(n);
    setType(t);
}

string NumberCard::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|     " <<  number << "     |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool NumberCard::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || number == discard->getNumber()){
        return true;
    } else {
        return false;
    }
}

WildCard::WildCard(Type t) {
    setNumber(-1);
    setType(t);
    setColor(NUM_COLORS);
}

string WildCard::render(int line) const{
    
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: return "|    WILD   |";
        case 3: 
        if(color != NUM_COLORS){
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        } else {
                return "|           |";
        }
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool WildCard::play(Card* discard, GameState &gameState) {
   return true;
}

SkipCard::SkipCard(Color c, Type t) {
    setType(t);
    setColor(c);
    setNumber(-1);
}

string SkipCard::render(int line) const{
    
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3: return "|    Skip   |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool SkipCard::play(Card* discard, GameState &gameState) {
   if(color == discard->getColor() || type == discard->getType()){
       return true;
   } else{
       return false;
   }
}

ReverseCard::ReverseCard(Color c, Type t) {
    setType(t);
    setColor(c);
    setNumber(-1);
}

string ReverseCard::render(int line) const{
    
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3: return "|  Reverse  |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool ReverseCard::play(Card* discard, GameState &gameState) {
   if(color == discard->getColor() || type == discard->getType()){
       return true;
   } else{
       return false;
   }
}

Plus2Card::Plus2Card(Color c, Type t) {
    setType(t);
    setColor(c);
    setNumber(-1);
}

string Plus2Card::render(int line) const{
    
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3: return "|     +2    |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool Plus2Card::play(Card* discard, GameState &gameState) {
   if(color == discard->getColor() || type == discard->getType()){
       return true;
   } else{
       return false;
   }
}