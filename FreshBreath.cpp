#include <iostream>
using namespace std;
class Polynomial{
    protected:
    int degree;
    int val;
    int * newarr = new int[degree + 1];
    int ymax,ymin,xmax,xmin,minx,miny,rangeX;
    int origin,accepted;
    public:
    Polynomial(){}
    void Poly(){
        cin>>degree;        
        for(int i = degree; i>=0; i--){
            cout<<"Input coefficient of x raised to power "<<i<<": "<<endl;
            cin>>val;
            newarr[i] = val;
        }
        for(int i=degree; i>=0; i--){
            cout<<newarr[i]<<" ";
        }  
    }

    void xvals(){
        cout<<"Input range of X values"<<endl;;

        cout<<"Xmin: ";
        cin>>xmin;

        cout<<"Xmax: ";
        cin>>xmax;

        minx = -1*xmin;
        rangeX = minx + xmax;
    }
};


class Plotting: public Polynomial{
    protected:
    int * arrj = new int[xmin];
    int * arrk = new int[xmax+1];
    int * arrsum = new int[rangeX+1];
    int rangeY = 0;
    public:
    Plotting(){}
    int retRangeY(){
        return rangeY;
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
        }
        for(int index = 0; index<=xmax;index++){
            arrsum[index+minx] = arrk[index];
        }
        cout<<endl;
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
};


class Round{
    private:
    double nd;
    int ni;
    double rem;
    double vald;
    int vali;
    double rm;
    double roundd;
    int roundi;
    double workWith;
    double finalVal;
    public:
    Round(){}
    double runRound(double num){
        this->round(num);
        finalVal = ni+workWith;
        return finalVal;
    }

    double remInt(double num){
        nd = num;
        ni = nd;
        rem =  nd - ni;
        return rem;
    }

    double mul(double num, int i){
        vald = num * powbase(10,i);
        vali = vald;
        rm = vald - vali;
        if(rm>=0.5){
            vali++;
        }
        vald = vali;
        return vald/powbase(10,i);
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


    void round(double num){
        roundd = num*1000;
        roundi = roundd;
        
        roundd = roundi;
        roundd = roundd/1000;

        workWith = remInt(roundd);

        for(int i=2;i>1;i--){
            workWith = mul(workWith,i);
        }
    }
};

class Combine: public Round, public Plotting {
    protected:
    double numVal = 40;
    double valz = 0;
    double valy = 0;
    double conversion = 0;
    int nums = 0;
    double *graphingArr = new double [(rangeY+1)];
    public:
    void runCombine(){//Number should not be greater than 80,000,000 (Eighty Million).
        nums = rangeY;
        if(nums<=numVal){
            valz = numVal/nums;
            conversion = this->runRound(valz);
            valy = this->adjust(nums,conversion);
        }
        else{
            valz = numVal/nums;
            conversion = this->runRound(valz);
            valy = this->adjust(nums,conversion);
        }
        cout<<"***"<<conversion<<"***"<<endl;
        this->finalgraph();
    }


    int roundDown(double num){
        int sgn = 1;
        if(num<0){
            num = -num;
            sgn = -sgn;
        }
        int ns = num;
        double rem = num - ns;

        if(rem>=0.5){
            ns++;
        }

        if(ns>numVal){
            ns = numVal;
        }
        return ns*sgn;
    }

    int adjust(double num,double mul){
        double valz = num*mul;
        int valx = valz;
        double remz = valz - valx;
        if(remz>0.5){
            valx++;
        }
    return valx;
    }

    void finalgraph(){
        for(int i=0;i<=(minx+xmax);i++){
            graphingArr[i] = conversion * arrsum[i];
            cout<<"When x is "<<i+xmin<<" y is "<<arrsum[i]<<" and "<<graphingArr[i]<<" in graph units and "<<this->roundDown(graphingArr[i])<<" when rounded down."<<endl;
        }
    }
};



class FinalClass: public Combine{
    protected:
    int range = 0;
    public:
    FinalClass(){
        range = minx+xmax;
    }
    ~FinalClass(){
        delete [] newarr;
        delete [] arrj;
        delete [] arrk;
        delete [] arrsum;
        delete [] graphingArr;
    }
    void runFinalClass(){
        int inputformat;
        cout<<"Polynomial 1"<<endl<<"Conic 2"<<endl<<"exit 3"<<endl;
        cin>>inputformat;
        if(inputformat == 1){
            cout<<"Input Polynomial degree (Value of degree should not be less than one):"<<endl;
            this->Poly();
            if(degree>0){
                this->xvals();
                this->plot();
                this->graphs();
                if(this->getxmin()<=0){
                // this->Ymaxline();
                // this->Xline();
                // this->Yminline();
                this->runCombine();
                }else if(this->getxmin()>0){
                    cout<<"Minimum value of x should be equal to or less than 0, but it is greater than 0.";
                }
                else{
                    cout<<"Value of x is not a number!";
                }
            }
            else{
                cout<<"Program exited.";
            }
        }
        else if(inputformat == 2){
        }
        else if(inputformat == 3){
            cout<<"Program exited.";
        }
    }

};

int main(){
    FinalClass final;
    final.runFinalClass();
    return 0;
}