#include <iostream>
#include <string>
using namespace std;



//UNFINISHED


// template<class T>
// class Check{
//     public:
//     Check(){};
//     virtual void checking() = 0;
// };

// template<>
// class Check <int>{
//     public:
//     Check(){};
//     int checking(int x){
//         return 0;
//     }
// };

// template<>
// class Check <float>{
//     public:
//     Check(){};
//     float checking(float x){
//         cout<<"Please input integer";
//         return 1;
//     }
// };

// template<>
// class Check <double>{
//     public:
//     Check(){};
//     double checking(double x){
//         cout<<"Please input integer";
//         return 1;
//     }
// };

// template<>
// class Check <string>{
//     public:
//     Check(){};
//     string checking(string x){
//         cout<<"Please input integer";
//         return "1";
//     }
// };

// template<>
// class Check <char>{
//     public:
//     Check(){};
//     char checking(char x){
//         cout<<"Please input integer";
//         return '1';
//     }
// };

// void check(float val){
//     cout<<"Type float, please input an integer."<<endl;
// }

// void check(int val){
//     cout<<"Type integer, accepted."<<endl;
// }

// void check(double val){
//     cout<<"Type double, please input an integer."<<endl;
// }

// void check(string val){
//     cout<<"Type string, please input an integer."<<endl;
// }

// void check(char val){
//     cout<<"Type character, please input an integer."<<endl;
// }

class Graph{
    protected:
    int ymax,ymin,xmax,xmin,minx,miny,maxy;
    int origin,accepted;
    void Xspace(){
        for(int x=1;x<=10*minx;x++){
            cout<<"  ";
        }
    }
    public:
    Graph(){}
};

class Polynomial{
    protected:
        int degree;
        int val;
        int * newarr = new int[degree + 1];
    public:
    Polynomial(){}
    void Poly(){
        cout<<"Input Polynomial degree:"<<endl;
        cin>>degree;
        for(int i = degree; i>=0; i--){
            cout<<"Input coefficient of x raised to power "<<i<<": "<<endl;
            cin>>val;
            newarr[i] = val;
        }
        for(int i=degree; i>=0; i--){
            cout<<newarr[i]<<" ";
        }
        cout<<endl;
    }
};


class Plotting: public Polynomial, public Graph{
    protected:
    int * arrj = new int[20];
    int * arrk = new int[20];
    int * arrsum = new int[40];
    int rangeY = 0;
    public:
    Plotting(){}
    int retRangeY(){
        return rangeY;
    }
    ~Plotting(){
        cout<<xmin<<" "<<minx<<" "<<xmax<<endl<<ymin<<" "<<miny<<" "<<ymax<<endl;
        cout<<"@@@"<<rangeY<<endl;
        delete arrsum;
        delete arrk;
        delete arrj;
        delete newarr;
    }
    float powbase(int base, int power){
        if(power==0){
            return 1;
        }
        if(power > 0){
            return base * powbase(base,power-1);
        }
        if(power<0)
        {
            return powbase(base,power+1)*1/base;
        }
        else{
            return 1;
        }
    }

    void xvals(){
        cout<<"Input range of X values"<<endl;;

        cout<<"Xmin: ";
        cin>>xmin;

        cout<<"Xmax: ";
        cin>>xmax;

        minx = -1*xmin;
    }

    void plot(){
        for(int j = xmin;j<0;j++){
            int sumj = 0;
            for(int i = degree; i>=0;i--){
                sumj += newarr[i]*this->powbase(j,i);
            }
            arrj[j+minx] = sumj;
        }
        for(int k=0;k<=xmax;k++){ 
            int sumk = 0;
            for(int i = degree; i>=0; i--){
                sumk += newarr[i]*this->powbase(k,i);
            }
            arrk[k] = sumk;            
        }
        for(int index = 0; index<minx;index++){
            arrsum[index] = arrj[index];
            cout<<"#"<<arrsum[index]<<" ";
        }
        for(int index = 0; index<=xmax;index++){
            arrsum[index+minx] = arrk[index];
            cout<<"*"<<arrsum[index+minx]<<" ";
        }
        cout<<endl;
    }

        
    void display(){
        for(int i= 0;i<=(minx+xmax);i++){
            cout<<"When x is "<<i+xmin<<" y is "<<arrsum[i]<<endl;
        }
    }

    int ymaxv(){
        int max = 0;
        for(int i = 0;i<=(minx+xmax);i++){
            if(arrsum[i]>=max){
                max = arrsum[i];
            }
        }
        double number = max;
        int integer = number;
        double decimal = number - integer;

        if(number>=0){
            if(decimal>=0.5){
                integer++;
            }
        }
        else if(number < 0){
            if(decimal<=-0.5){
                integer--;
            }
        }
        
        return integer;
    }

    int yminv(){
            int min = 0;
            for(int i = 0;i<=(minx+xmax);i++){
                if(arrsum[i]<=min){
                    min = arrsum[i];
                }
            }
        double number = min;
        int integer = number;
        double decimal = number - integer;

        if(number>=0){
            if(decimal>=0.5){
                integer++;
            }
        }
        else if(number < 0){
            if(decimal<=-0.5){
                integer--;
            }
        }

        return integer;
    }


    void graphs(){

    ymin = this->yminv();
    ymax = this->ymaxv();


    miny = -1*ymin;
    
    rangeY = miny + ymax;
    }

    int getymin(){
        return ymin;
    }
    int getxmin(){
        return xmin;
    }    

    void Ymaxline(){
        if((minx+xmax)<=15){
            for(int i=1;i<=5*ymax;i++){
                Xspace();
            cout<<"|"<<endl;
            }
        }
    }
    void Xline(){
        if((minx+xmax)<=15){
            for(int a=1;a<=10*minx;a++){
            cout<<"--";
            }
            cout<<"|";
            for(int b=1;b<=10*xmax;b++){
            cout<<"--";
            }
            cout<<endl;
        }
    }
    void Yminline(){
        if((minx+xmax)<=15){
            for(int i=1;i<=5*miny;i++){
                Xspace();
            cout<<"|"<<endl;
            }
        }
    }
};


int main(){

    int inputformat;
    cout<<"Polynomial 1"<<endl<<"Conic 2"<<endl<<"exit 3"<<endl;
    cin>>inputformat;
    if(inputformat == 1){
        Plotting plot;
        plot.Poly();
        plot.xvals();
        plot.plot();
        plot.graphs();
        cout<<plot.retRangeY();
        if(plot.getxmin()<=0){
        // plot.Ymaxline();
        // plot.Xline();
        // plot.Yminline();
        }else if(plot.getxmin()>0){
            cout<<"Minimum value of x should be equal to or less than 0, but it is greater than 0.";
        }
        else{
            cout<<"Value of x is not a number!";
        }
        plot.display();
    }
    else if(inputformat == 2){
    }
    else if(inputformat == 3){
        cout<<"Program exited.";
    }
    else{
        cin>>inputformat;
    }


    return 0;
}