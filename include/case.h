#ifndef CASE_H
#define CASE_H


class Case
{
    public:
        Case():value(0),discovred(false),flag(false),boomb(false){};
        int getValue(){return this->value;}
        int setValue(int v){this->value=v;}
        int getBoomb(){return this->boomb;}
        int setBoomb(bool b){this->boomb=b;}
        int getDiscovred(){return this->discovred;}
        int setDiscovred(bool b){this->discovred=b;}
        int getFlag(){return flag;}
        int setFlag(bool f){this->flag=f;}

        virtual ~Case(){};

    protected:

    private:
        bool flag;
        bool discovred;
        int value;
        bool boomb;
};

#endif // CASE_H
